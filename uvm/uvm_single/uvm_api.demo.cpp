/**
* lua module injector header in uvm
*/

#include <uvm/lprefix.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string>
#include <sstream>
#include <utility>
#include <list>
#include <map>
#include <unordered_map>
#include <memory>
#include <mutex>
#include <uvm/uvm_api.h>
#include <uvm/uvm_lib.h>
#include <uvm/uvm_lutil.h>
#include <uvm/lobject.h>
#include <uvm/lstate.h>
#include "uvm_api.demo.h"

namespace uvm {
	namespace lua {
		namespace api {
			// demo，API

			static int has_error = 0;

			static std::string get_file_name_str_from_contract_module_name(std::string name)
			{
				std::stringstream ss;
				ss << "uvm_contract_" << name;
				return ss.str();
			}

			/**
			* whether exception happen in L
			*/
			bool DemoUvmChainApi::has_exception(lua_State *L)
			{
				return has_error ? true : false;
			}

			/**
			* clear exception marked
			*/
			void DemoUvmChainApi::clear_exceptions(lua_State *L)
			{
				has_error = 0;
			}

			/**
			* when exception happened, use this api to tell uvm
			* @param L the lua stack
			* @param code error code, 0 is OK, other is different error
			* @param error_format error info string, will be released by lua
			* @param ... error arguments
			*/
			void DemoUvmChainApi::throw_exception(lua_State *L, int code, const char *error_format, ...)
			{
				has_error = 1;
				char *msg = (char*)malloc(sizeof(char)*(LUA_VM_EXCEPTION_STRNG_MAX_LENGTH +1));
				if(!msg)
				{
					perror("malloc error");
					return;
				}
				memset(msg, 0x0, LUA_VM_EXCEPTION_STRNG_MAX_LENGTH +1);

				va_list vap;
				va_start(vap, error_format);
				// printf(error_format, vap);
				// const char *msg = luaO_pushfstring(L, error_format, vap);
				vsnprintf(msg, LUA_VM_EXCEPTION_STRNG_MAX_LENGTH, error_format, vap);
				va_end(vap);
				lua_set_compile_error(L, msg);
				printf("%s\n", msg);
				free(msg);
				// luaL_error(L, error_format); // notify lua error
			}

			/**
			* check whether the contract apis limit over, in this lua_State
			* @param L the lua stack
			* @return TRUE(1 or not 0) if over limit(will break the vm), FALSE(0) if not over limit
			*/
			int DemoUvmChainApi::check_contract_api_instructions_over_limit(lua_State *L)
			{
				return 0;
			}

			int DemoUvmChainApi::get_stored_contract_info(lua_State *L, const char *name, std::shared_ptr<UvmContractInfo> contract_info_ret)
			{
				if (uvm::util::starts_with(name, "@"))
				{
					perror("wrong contract name\n");
					exit(1);
				}
				if(contract_info_ret)
				{
					contract_info_ret->contract_apis.push_back("init");
					contract_info_ret->contract_apis.push_back("start");
				}
				return 1;
			}
			int DemoUvmChainApi::get_stored_contract_info_by_address(lua_State *L, const char *contract_id, std::shared_ptr<UvmContractInfo> contract_info_ret)
			{
				if (uvm::util::starts_with(contract_id, "@"))
				{
					perror("wrong contract address\n");
					exit(1);
				}
				if (contract_info_ret)
				{
					contract_info_ret->contract_apis.push_back("init");
					contract_info_ret->contract_apis.push_back("start");
				}
				return 1;
			}

			std::shared_ptr<UvmModuleByteStream> DemoUvmChainApi::get_bytestream_from_code(lua_State *L, const uvm::blockchain::Code& code)
			{
				return nullptr;
			}

			void DemoUvmChainApi::get_contract_address_by_name(lua_State *L, const char *name, char *address, size_t *address_size)
			{
				std::string name_str(name);
				if (name_str == std::string("not_found"))
					return;
				if(uvm::util::starts_with(name_str, std::string(STREAM_CONTRACT_PREFIX)))
				{
					name_str = name_str.substr(strlen(STREAM_CONTRACT_PREFIX));
				}
				std::string addr_str = std::string("id_") + name_str;
				strcpy(address, addr_str.c_str());
				if(address_size)
					*address_size = addr_str.size() + 1;
			}
            
            bool DemoUvmChainApi::check_contract_exist_by_address(lua_State *L, const char *address)
            {
                return true;
            }

			bool DemoUvmChainApi::check_contract_exist(lua_State *L, const char *name)
			{
				std::string filename = std::string("uvm_modules") + uvm::util::file_separator_str() + "uvm_contract_" + name;
				FILE *f = fopen(filename.c_str(), "rb");
				bool exist = false;
				if (nullptr != f)
				{
					exist = true;
					fclose(f);
				}
				return exist;
			}

			/**
			* load contract lua byte stream from uvm api
			*/
			std::shared_ptr<UvmModuleByteStream> DemoUvmChainApi::open_contract(lua_State *L, const char *name)
			{
              uvm::lua::lib::increment_lvm_instructions_executed_count(L, CHAIN_GLUA_API_EACH_INSTRUCTIONS_COUNT - 1);
				bool is_bytes = true;
				std::string filename = std::string("uvm_modules") + uvm::util::file_separator_str() + "uvm_contract_" + name;
				FILE *f = fopen(filename.c_str(), "rb");
				if (nullptr == f)
				{
					std::string origin_filename(filename);
					filename = origin_filename + ".lua";
					f = fopen(filename.c_str(), "rb");
					if (!f)
					{
						filename = origin_filename + ".glua";
						f = fopen(filename.c_str(), "rb");
						if(nullptr == f)
							return nullptr;
					}
					is_bytes = false;
				}
				auto stream = std::make_shared<UvmModuleByteStream>();
                if(nullptr == stream)
                    return nullptr;
				fseek(f, 0, SEEK_END);
				auto file_size = ftell(f);
				stream->buff.resize(file_size);
				fseek(f, 0, 0);
				file_size = (long) fread(stream->buff.data(), file_size, 1, f);
				fseek(f, 0, SEEK_END); // seek to end of file
				file_size = ftell(f); // get current file pointer
				stream->is_bytes = is_bytes;
				stream->contract_name = name;
				stream->contract_id = std::string("id_") + std::string(name);
				fclose(f);
				if (!is_bytes)
					stream->buff[stream->buff.size()-1] = '\0';
				return stream;
			}
            
			std::shared_ptr<UvmModuleByteStream> DemoUvmChainApi::open_contract_by_address(lua_State *L, const char *address)
            {
				if (uvm::util::starts_with(address, "id_"))
				{
					std::string address_str = address;
					auto name = address_str.substr(strlen("id_"));
					if(name.length()>=6 && name[0]>='0' && name[0]<='9')
					{
						// stream
						auto addr_pointer = std::atoll(name.c_str());
						auto stream = (UvmModuleByteStream*)addr_pointer;
						auto result_stream = std::make_shared<UvmModuleByteStream>();
						*result_stream = *stream;
						return result_stream;
					}
					return open_contract(L, name.c_str());
				}
                return open_contract(L, "pointer_demo");
            }

            // storage,mapkey contract_id + "$" + storage_name
            // TODO: lua_closepost_callback，
            static std::map<lua_State *, std::shared_ptr<std::map<std::string, UvmStorageValue>>> _demo_chain_storage_buffer;

			UvmStorageValue DemoUvmChainApi::get_storage_value_from_uvm(lua_State *L, const char *contract_name, std::string name)
			{
              // fetch storage value from uvm
              if (_demo_chain_storage_buffer.find(L) == _demo_chain_storage_buffer.end()) {
                if (_demo_chain_storage_buffer.size() > 5)
                {
                  _demo_chain_storage_buffer.clear();
                }
                _demo_chain_storage_buffer[L] = std::make_shared<std::map<std::string, UvmStorageValue>>();
              }
              auto cache = _demo_chain_storage_buffer[L];
              // auto key = std::string(contract_address) + "$" + name;
              auto key = std::string("demo$") + name; // democontract_idid_+，
              if (cache->find(key) != cache->end())
              {
                return (*cache)[key];
              }
              UvmStorageValue value;
              value.type = uvm::blockchain::StorageValueTypes::storage_value_null;
              value.value.int_value = 0;
              (*cache)[key] = value;
              return value;
			}

			UvmStorageValue DemoUvmChainApi::get_storage_value_from_uvm_by_address(lua_State *L, const char *contract_address, std::string name)
			{
				// fetch storage value from uvm
                if (_demo_chain_storage_buffer.find(L) == _demo_chain_storage_buffer.end()) {
                  if (_demo_chain_storage_buffer.size() > 5)
                  {
                    _demo_chain_storage_buffer.clear();
                  }
                    _demo_chain_storage_buffer[L] = std::make_shared<std::map<std::string, UvmStorageValue>>();
                }
                auto cache = _demo_chain_storage_buffer[L];
                // auto key = std::string(contract_address) + "$" + name;
                auto key = std::string("demo$") + name; // democontract_idid_+，
                if (cache->find(key) != cache->end())
                {
                  return (*cache)[key];
                }
				UvmStorageValue value;
				value.type = uvm::blockchain::StorageValueTypes::storage_value_null;
				value.value.int_value = 0;
                (*cache)[key] = value;
				return value;
			}

			bool DemoUvmChainApi::commit_storage_changes_to_uvm(lua_State *L, AllContractsChangesMap &changes)
			{
				// printf("commited storage changes to uvm\n");
                if (_demo_chain_storage_buffer.find(L) == _demo_chain_storage_buffer.end()) {
                  if (_demo_chain_storage_buffer.size() > 5)
                  {
                    _demo_chain_storage_buffer.clear();
                  }
                  _demo_chain_storage_buffer[L] = std::make_shared<std::map<std::string, UvmStorageValue>>();
                }
                auto cache = _demo_chain_storage_buffer[L];
                for (const auto &change : changes)
                {
                  auto contract_id = change.first;
                  for (const auto &change_info : *(change.second))
                  {
                    auto name = change_info.first;
                    auto change_item = change_info.second;
                    // auto key = contract_id + "$" + name;
                    auto key =  std::string("demo$") + name; // democontract_idid_+，
                    // FIIXME: merge
                    UvmStorageValue value = change_item.after;
                    (*cache)[key] = value;
                  }
                }
				return true;
			}

			intptr_t DemoUvmChainApi::register_object_in_pool(lua_State *L, intptr_t object_addr, UvmOutsideObjectTypes type)
			{
				auto node = uvm::lua::lib::get_lua_state_value_node(L, GLUA_OUTSIDE_OBJECT_POOLS_KEY);
				// Map<type, Map<object_key, object_addr>>
				std::map<UvmOutsideObjectTypes, std::shared_ptr<std::map<intptr_t, intptr_t>>> *object_pools = nullptr;
				if(node.type == UvmStateValueType::LUA_STATE_VALUE_nullptr)
				{
					node.type = UvmStateValueType::LUA_STATE_VALUE_POINTER;
					object_pools = new std::map<UvmOutsideObjectTypes, std::shared_ptr<std::map<intptr_t, intptr_t>>>();
					node.value.pointer_value = (void*)object_pools;
					uvm::lua::lib::set_lua_state_value(L, GLUA_OUTSIDE_OBJECT_POOLS_KEY, node.value, node.type);
				} 
				else
				{
					object_pools = (std::map<UvmOutsideObjectTypes, std::shared_ptr<std::map<intptr_t, intptr_t>>> *) node.value.pointer_value;
				}
				if(object_pools->find(type) == object_pools->end())
				{
					object_pools->emplace(std::make_pair(type, std::make_shared<std::map<intptr_t, intptr_t>>()));
				}
				auto pool = (*object_pools)[type];
				auto object_key = object_addr;
				(*pool)[object_key] = object_addr;
				return object_key;
			}

			intptr_t DemoUvmChainApi::is_object_in_pool(lua_State *L, intptr_t object_key, UvmOutsideObjectTypes type)
			{
				auto node = uvm::lua::lib::get_lua_state_value_node(L, GLUA_OUTSIDE_OBJECT_POOLS_KEY);
				// Map<type, Map<object_key, object_addr>>
				std::map<UvmOutsideObjectTypes, std::shared_ptr<std::map<intptr_t, intptr_t>>> *object_pools = nullptr;
				if (node.type == UvmStateValueType::LUA_STATE_VALUE_nullptr)
				{
					return 0;
				}
				else
				{
					object_pools = (std::map<UvmOutsideObjectTypes, std::shared_ptr<std::map<intptr_t, intptr_t>>> *) node.value.pointer_value;
				}
				if (object_pools->find(type) == object_pools->end())
				{
					object_pools->emplace(std::make_pair(type, std::make_shared<std::map<intptr_t, intptr_t>>()));
				}
				auto pool = (*object_pools)[type];
				return (*pool)[object_key];
			}

			void DemoUvmChainApi::release_objects_in_pool(lua_State *L)
			{
				auto node = uvm::lua::lib::get_lua_state_value_node(L, GLUA_OUTSIDE_OBJECT_POOLS_KEY);
				// Map<type, Map<object_key, object_addr>>
				std::map<UvmOutsideObjectTypes, std::shared_ptr<std::map<intptr_t, intptr_t>>> *object_pools = nullptr;
				if (node.type == UvmStateValueType::LUA_STATE_VALUE_nullptr)
				{
					return;
				}
				object_pools = (std::map<UvmOutsideObjectTypes, std::shared_ptr<std::map<intptr_t, intptr_t>>> *) node.value.pointer_value;
				// TODO: object_pools，
				for(const auto &p : *object_pools)
				{
					auto type = p.first;
					auto pool = p.second;
					for(const auto &object_item : *pool)
					{
						auto object_key = object_item.first;
						auto object_addr = object_item.second;
						if (object_addr == 0)
							continue;
						switch(type)
						{
						case UvmOutsideObjectTypes::OUTSIDE_STREAM_STORAGE_TYPE:
						{
							auto stream = (uvm::lua::lib::UvmByteStream*) object_addr;
							delete stream;
						} break;
						default: {
							continue;
						}
						}
					}
				}
				delete object_pools;
				UvmStateValue null_state_value;
				null_state_value.int_value = 0;
				uvm::lua::lib::set_lua_state_value(L, GLUA_OUTSIDE_OBJECT_POOLS_KEY, null_state_value, UvmStateValueType::LUA_STATE_VALUE_nullptr);
			}

			bool DemoUvmChainApi::register_storage(lua_State *L, const char *contract_name, const char *name)
			{
				// printf("registered storage %s[%s] to uvm\n", contract_name, name);
				return true;
			}

			lua_Integer DemoUvmChainApi::transfer_from_contract_to_address(lua_State *L, const char *contract_address, const char *to_address,
				const char *asset_type, int64_t amount_str)
			{
              uvm::lua::lib::increment_lvm_instructions_executed_count(L, CHAIN_GLUA_API_EACH_INSTRUCTIONS_COUNT - 1);
				printf("contract transfer from %s to %s, asset[%s] amount %ld\n", contract_address, to_address, asset_type, amount_str);
				return 0;
			}

			lua_Integer DemoUvmChainApi::transfer_from_contract_to_public_account(lua_State *L, const char *contract_address, const char *to_account_name,
				const char *asset_type, int64_t amount)
			{
              uvm::lua::lib::increment_lvm_instructions_executed_count(L, CHAIN_GLUA_API_EACH_INSTRUCTIONS_COUNT - 1);
				printf("contract transfer from %s to %s, asset[%s] amount %ld\n", contract_address, to_account_name, asset_type, amount);
				return 0;
			}

			int64_t DemoUvmChainApi::get_contract_balance_amount(lua_State *L, const char *contract_address, const char* asset_symbol)
			{
              uvm::lua::lib::increment_lvm_instructions_executed_count(L, CHAIN_GLUA_API_EACH_INSTRUCTIONS_COUNT - 1);
				return 0;
			}

			int64_t DemoUvmChainApi::get_transaction_fee(lua_State *L)
			{
              uvm::lua::lib::increment_lvm_instructions_executed_count(L, CHAIN_GLUA_API_EACH_INSTRUCTIONS_COUNT - 1);
				return 0;
			}

			uint32_t DemoUvmChainApi::get_chain_now(lua_State *L)
			{				
              uvm::lua::lib::increment_lvm_instructions_executed_count(L, CHAIN_GLUA_API_EACH_INSTRUCTIONS_COUNT - 1);
				return 0;
			}

			uint32_t DemoUvmChainApi::get_chain_random(lua_State *L)
			{
              uvm::lua::lib::increment_lvm_instructions_executed_count(L, CHAIN_GLUA_API_EACH_INSTRUCTIONS_COUNT - 1);
				return 0;
			}

			std::string DemoUvmChainApi::get_transaction_id(lua_State *L)
			{
              uvm::lua::lib::increment_lvm_instructions_executed_count(L, CHAIN_GLUA_API_EACH_INSTRUCTIONS_COUNT - 1);
				return "";
			}

			uint32_t DemoUvmChainApi::get_header_block_num(lua_State *L)
			{
              uvm::lua::lib::increment_lvm_instructions_executed_count(L, CHAIN_GLUA_API_EACH_INSTRUCTIONS_COUNT - 1);
				return 0;
			}

			uint32_t DemoUvmChainApi::wait_for_future_random(lua_State *L, int next)
			{
              uvm::lua::lib::increment_lvm_instructions_executed_count(L, CHAIN_GLUA_API_EACH_INSTRUCTIONS_COUNT - 1);
				return 0;
			}

			int32_t DemoUvmChainApi::get_waited(lua_State *L, uint32_t num)
			{
              uvm::lua::lib::increment_lvm_instructions_executed_count(L, CHAIN_GLUA_API_EACH_INSTRUCTIONS_COUNT - 1);
				return num;
			}

			void DemoUvmChainApi::emit(lua_State *L, const char* contract_id, const char* event_name, const char* event_param)
			{
              uvm::lua::lib::increment_lvm_instructions_executed_count(L, CHAIN_GLUA_API_EACH_INSTRUCTIONS_COUNT - 1);
				printf("emit called\n");
			}

			bool DemoUvmChainApi::is_valid_address(lua_State *L, const char *address_str)
			{
				return true;
			}

			bool DemoUvmChainApi::is_valid_contract_address(lua_State *L, const char *address_str)
			{
				return true;
			}

			const char * DemoUvmChainApi::get_system_asset_symbol(lua_State *L)
			{
				return "COIN";
			}

			uint64_t DemoUvmChainApi::get_system_asset_precision(lua_State *L)
			{
				return 10000;
			}

		}
	}
}
