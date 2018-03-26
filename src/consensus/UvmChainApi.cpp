/**
 * lua module injector header in cdcchain
 */

#include "uvm/lprefix.h"
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
#include "uvm/uvm_api.h"
#include "uvm/uvm_lib.h"
#include "uvm/uvm_lutil.h"
#include "uvm/lstate.h"
#include "uvm/lobject.h"

#include <consensus/UvmChainApi.hpp>
#include <consensus/address/Address.hpp>
#include <consensus/chainstate/ChainInterface.hpp>
#include <consensus/operation/StorageOperations.hpp>
#include <consensus/transaction/TransactionEvaluationState.hpp>
#include <consensus/Exceptions.hpp>
#include "wallet/Wallet.hpp"
#include "consensus/operation/BalanceOperations.hpp"
#include "consensus/operation/ContractOperations.hpp"
#include "consensus/Types.hpp"


namespace cdcchain {
    namespace lua {
        namespace api {
            static int has_error = 0;


            static std::string get_file_name_str_from_contract_module_name(std::string name)
            {
                std::stringstream ss;
                ss << "cdcchain_contract_" << name;
                return ss.str();
            }

            /**
            * whether exception happen in L
            */
            bool UvmChainApi::has_exception(lua_State *L)
            {
                return has_error ? true : false;
            }

            /**
            * clear exception marked
            */
            void UvmChainApi::clear_exceptions(lua_State *L)
            {
                has_error = 0;
            }

            /**
            * when exception happened, use this api to tell cdcchain
            * @param L the lua stack
            * @param code error code, 0 is OK, other is different error
            * @param error_format error info string, will be released by lua
            * @param ... error arguments
            */
            void UvmChainApi::throw_exception(lua_State *L, int code, const char *error_format, ...)
            {
				if (has_error)
					return;
                has_error = 1;
                char *msg = (char*)lua_malloc(L, LUA_EXCEPTION_MULTILINE_STRNG_MAX_LENGTH);
                memset(msg, 0x0, LUA_EXCEPTION_MULTILINE_STRNG_MAX_LENGTH);

                va_list vap;
                va_start(vap, error_format);
                // printf(error_format, vap);
                // const char *msg = luaO_pushfstring(L, error_format, vap);
                vsnprintf(msg, LUA_EXCEPTION_MULTILINE_STRNG_MAX_LENGTH, error_format, vap);
                va_end(vap);
                if (strlen(msg) > LUA_EXCEPTION_MULTILINE_STRNG_MAX_LENGTH - 1)
                {
                    msg[LUA_EXCEPTION_MULTILINE_STRNG_MAX_LENGTH - 1] = 0;
                }
                //perror(msg);
                //printf("\n");
                // luaL_error(L, error_format); // notify lua error
                //FC_THROW(msg);

                lua_set_compile_error(L, msg);

                //如果上次的exception code为CDCCORE_API_LVM_LIMIT_OVER_ERROR, 不能被其他异常覆盖
                //只有调用clear清理后，才能继续记录异常
                int last_code = uvm::lua::lib::get_lua_state_value(L, "exception_code").int_value;
                if (last_code == UVM_API_LVM_LIMIT_OVER_ERROR
                    && code != UVM_API_LVM_LIMIT_OVER_ERROR)
                {
                    return;
                }

                UvmStateValue val_code;
                val_code.int_value = code;

                UvmStateValue val_msg;
                val_msg.string_value = msg;

                uvm::lua::lib::set_lua_state_value(L, "exception_code", val_code, UvmStateValueType::LUA_STATE_VALUE_INT);
				uvm::lua::lib::set_lua_state_value(L, "exception_msg", val_msg, UvmStateValueType::LUA_STATE_VALUE_STRING);
            }

            /**
            * check whether the contract apis limit over, in this lua_State
            * @param L the lua stack
            * @return TRUE(1 or not 0) if over limit(will break the vm), FALSE(0) if not over limit
            */
            int UvmChainApi::check_contract_api_instructions_over_limit(lua_State *L)
            {
                return 0; // FIXME: need fill by cdcchain api
            }

            int UvmChainApi::get_stored_contract_info(lua_State *L, const char *name, std::shared_ptr<UvmContractInfo> contract_info_ret)
            {
                cdcchain::consensus::TransactionEvaluationState* pevaluate_state = (cdcchain::consensus::TransactionEvaluationState*)uvm::lua::lib::get_lua_state_value(L, "evaluate_state").pointer_value;
                // name = lua::lib::unwrap_any_contract_name(name).c_str();
                cdcchain::consensus::oContractEntry entry = pevaluate_state->_current_state->get_contract_entry(name);
                if (!entry.valid())
                    return 0;

                std::string addr_str = entry->id.AddressToString(AddressType::contract_address);

                return get_stored_contract_info_by_address(L, addr_str.c_str(), contract_info_ret);
            }

            int UvmChainApi::get_stored_contract_info_by_address(lua_State *L, const char *address, std::shared_ptr<UvmContractInfo> contract_info_ret)
            {
                cdcchain::consensus::TransactionEvaluationState* pevaluate_state = (cdcchain::consensus::TransactionEvaluationState*)uvm::lua::lib::get_lua_state_value(L, "evaluate_state").pointer_value;
                cdcchain::consensus::oContractEntry entry = pevaluate_state->_current_state->get_contract_entry(cdcchain::consensus::Address(std::string(address), AddressType::contract_address));

                if (!entry.valid())
                    return 0;

                uvm::blockchain::Code& code = entry->code;
                contract_info_ret->contract_apis.clear();

                std::copy(code.abi.begin(), code.abi.end(), std::back_inserter(contract_info_ret->contract_apis));
                std::copy(code.offline_abi.begin(), code.offline_abi.end(), std::back_inserter(contract_info_ret->contract_apis));

                return 1;
            }

            void UvmChainApi::get_contract_address_by_name(lua_State *L, const char *name, char *address, size_t *address_size)
            {
                /*
                std::string addr_str = std::string("id_") + std::string(name);
                strcpy(address, addr_str.c_str());
                *address_size = addr_str.size() + 1;
                */
                cdcchain::consensus::TransactionEvaluationState* eval_state_ptr =
                    (cdcchain::consensus::TransactionEvaluationState*)
                    (uvm::lua::lib::get_lua_state_value(L, "evaluate_state").pointer_value);

                if (!eval_state_ptr)
                {
                    return;
                }

                cdcchain::consensus::ChainInterface* cur_state = eval_state_ptr->_current_state;

                oContractEntry entry = cur_state->get_contract_entry(std::string(name));

                if (entry.valid())
                {
                    string address_str = entry->id.AddressToString(AddressType::contract_address);
                    *address_size = address_str.length();
                    strncpy(address, address_str.c_str(), CONTRACT_ID_MAX_LENGTH - 1);
                    address[CONTRACT_ID_MAX_LENGTH - 1] = '\0';
                }
            }

            bool UvmChainApi::check_contract_exist_by_address(lua_State *L, const char *address)
            {
                cdcchain::consensus::TransactionEvaluationState* eval_state_ptr =
                    (cdcchain::consensus::TransactionEvaluationState*)
                    (uvm::lua::lib::get_lua_state_value(L, "evaluate_state").pointer_value);

                if (!eval_state_ptr)
                    return NULL;

                cdcchain::consensus::ChainInterface* cur_state = eval_state_ptr->_current_state;

                oContractEntry entry = cur_state->get_contract_entry(cdcchain::consensus::Address(std::string(address), AddressType::contract_address));

                return entry.valid();
            }

            bool UvmChainApi::check_contract_exist(lua_State *L, const char *name)
            {
                /*
                char *filename = lutil_concat_str4("cdcchain_lua_modules", file_separator_str(), "cdcchain_contract_", name);
                FILE *f = fopen(filename, "rb");
                bool exist = false;
                if (NULL != f)
                {
                exist = true;
                fclose(f);
                }
                free(filename);
                return exist;
                */

                cdcchain::consensus::TransactionEvaluationState* eval_state_ptr =
                    (cdcchain::consensus::TransactionEvaluationState*)
                    (uvm::lua::lib::get_lua_state_value(L, "evaluate_state").pointer_value);

                if (!eval_state_ptr)
                    return NULL;

                cdcchain::consensus::ChainInterface* cur_state = eval_state_ptr->_current_state;

                oContractEntry entry = cur_state->get_contract_entry(std::string(name));

                return entry.valid();
            }

            std::shared_ptr<UvmModuleByteStream> UvmChainApi::get_bytestream_from_code(lua_State *L, const uvm::blockchain::Code& code)
            {
                if (code.byte_code.size() > LUA_MODULE_BYTE_STREAM_BUF_SIZE)
                    return NULL;
                auto p_luamodule = std::make_shared<UvmModuleByteStream>();
                p_luamodule->is_bytes = true;
                p_luamodule->buff.resize(code.byte_code.size());
                memcpy(p_luamodule->buff.data(), code.byte_code.data(), code.byte_code.size());
                p_luamodule->contract_name = "";

                p_luamodule->contract_apis.clear();
                std::copy(code.abi.begin(), code.abi.end(), std::back_inserter(p_luamodule->contract_apis));

                p_luamodule->contract_emit_events.clear();
                std::copy(code.offline_abi.begin(), code.offline_abi.end(), std::back_inserter(p_luamodule->offline_apis));

                p_luamodule->contract_emit_events.clear();
                std::copy(code.events.begin(), code.events.end(), std::back_inserter(p_luamodule->contract_emit_events));

                p_luamodule->contract_storage_properties.clear();
                std::copy(code.storage_properties.begin(), code.storage_properties.end(), std::inserter(p_luamodule->contract_storage_properties, p_luamodule->contract_storage_properties.begin()));

                return p_luamodule;
            }
            /**
            * load contract lua byte stream from cdcchain api
            */
            std::shared_ptr<UvmModuleByteStream> UvmChainApi::open_contract(lua_State *L, const char *name)
            {
                // FXIME
                /*
                bool is_bytes = true;
                char *filename = lutil_concat_str4("cdcchain_lua_modules", file_separator_str(), "cdcchain_contract_", name);
                FILE *f = fopen(filename, "rb");
                if (NULL == f)
                {
                filename = lutil_concat_str(filename, ".lua");
                f = fopen(filename, "rb");
                if (NULL == f)
                {
                return NULL;
                }
                is_bytes = false;
                }
                UvmModuleByteStream *stream = (UvmModuleByteStream*)malloc(sizeof(UvmModuleByteStream));
                stream->len = fread(stream->buff, 1024 * 1024, 1, f);
                fseek(f, 0, SEEK_END); // seek to end of file
                stream->len = ftell(f); // get current file pointer
                stream->is_bytes = is_bytes;
                fclose(f);
                if (!is_bytes)
                stream->buff[stream->len] = '\0';
                free(filename);
                return stream;
                */
              uvm::lua::lib::increment_lvm_instructions_executed_count(L, CHAIN_GLUA_API_EACH_INSTRUCTIONS_COUNT - 1);

                cdcchain::consensus::TransactionEvaluationState* eval_state_ptr =
                    (cdcchain::consensus::TransactionEvaluationState*)
                    (uvm::lua::lib::get_lua_state_value(L, "evaluate_state").pointer_value);

                if (!eval_state_ptr)
                    return NULL;

                cdcchain::consensus::ChainInterface* cur_state = eval_state_ptr->_current_state;

                oContractEntry entry = cur_state->get_contract_entry(std::string(name));
                if (entry.valid() && (entry->code.byte_code.size() <= LUA_MODULE_BYTE_STREAM_BUF_SIZE))
                {
                    return get_bytestream_from_code(L, entry->code);
                }

                return NULL;
            }

            std::shared_ptr<UvmModuleByteStream> UvmChainApi::open_contract_by_address(lua_State *L, const char *address)
            {
              uvm::lua::lib::increment_lvm_instructions_executed_count(L, CHAIN_GLUA_API_EACH_INSTRUCTIONS_COUNT - 1);
                cdcchain::consensus::TransactionEvaluationState* eval_state_ptr =
                    (cdcchain::consensus::TransactionEvaluationState*)
                    (uvm::lua::lib::get_lua_state_value(L, "evaluate_state").pointer_value);

                if (!eval_state_ptr)
                    return NULL;

                cdcchain::consensus::ChainInterface* cur_state = eval_state_ptr->_current_state;

                oContractEntry entry = cur_state->get_contract_entry(cdcchain::consensus::Address(std::string(address), AddressType::contract_address));
                if (entry.valid() && (entry->code.byte_code.size() <= LUA_MODULE_BYTE_STREAM_BUF_SIZE))
                {
                    return get_bytestream_from_code(L, entry->code);
                }

                return NULL;
            }

            /**
            * store contract lua module byte stream to cdcchain api
            */
            //need to delete
            /*
            int save_contract(const char *name, UvmModuleByteStream *stream)
            {
            return 0;
            }
            */

            /*
            void free_contract_storage(lua_State *L, UvmStorageValue* storage)
            {
            if (storage)
            {
            if (storage->type == UvmStorageValueType::LVALUE_INTEGER ||
            storage->type == UvmStorageValueType::LVALUE_NUMBER ||
            storage->type == UvmStorageValueType::LVALUE_BOOLEAN)
            {
            ;
            }
            else if (storage->type == UvmStorageValueType::LVALUE_STRING)
            {
            if (storage->value.string_value)
            free(storage->value.string_value);
            }
            else if (storage->type == UvmStorageValueType::LVALUE_TABLE)
            {
            UvmTableMap* p_lua_table = storage->value.table_value;

            if (p_lua_table && !p_lua_table->empty())
            {
            UvmStorageValue first_base_storage = p_lua_table->begin()->second;
            if (first_base_storage.type == UvmStorageValueType::LVALUE_INTEGER ||
            first_base_storage.type == UvmStorageValueType::LVALUE_NUMBER ||
            first_base_storage.type == UvmStorageValueType::LVALUE_BOOLEAN)
            {
            ;
            }
            else if (first_base_storage.type == UvmStorageValueType::LVALUE_STRING)
            {
            for (const auto& item: *p_lua_table)
            {
            if (item.second.value.string_value)
            free(item.second.value.string_value);

            }
            }
            delete p_lua_table;
            }

            }
            free(storage);
            }
            }
            */

            UvmStorageValue UvmChainApi::get_storage_value_from_uvm(lua_State *L, const char *contract_name, std::string name)
            {
                UvmStorageValue null_storage;
                null_storage.type = cdcchain::consensus::StorageValueTypes::storage_value_null;

                cdcchain::consensus::TransactionEvaluationState* eval_state_ptr =
                    (cdcchain::consensus::TransactionEvaluationState*)
                    (uvm::lua::lib::get_lua_state_value(L, "evaluate_state").pointer_value);

                if (!eval_state_ptr)
                    return null_storage;

                cdcchain::consensus::ChainInterface* cur_state = eval_state_ptr->_current_state;

                oContractEntry entry = cur_state->get_contract_entry(std::string(contract_name));
                if (!entry.valid())
                {
                    return null_storage;
                }
                return get_storage_value_from_uvm_by_address(L, entry->id.AddressToString(AddressType::contract_address).c_str(), name);
            }

            UvmStorageValue UvmChainApi::get_storage_value_from_uvm_by_address(lua_State *L, const char *contract_address, std::string name)
            {
                UvmStorageValue null_storage;
                null_storage.type = cdcchain::consensus::StorageValueTypes::storage_value_null;

                cdcchain::consensus::TransactionEvaluationState* eval_state_ptr =
                    (cdcchain::consensus::TransactionEvaluationState*)
                    (uvm::lua::lib::get_lua_state_value(L, "evaluate_state").pointer_value);

                if (!eval_state_ptr)
                    return null_storage;

                cdcchain::consensus::ChainInterface* cur_state = eval_state_ptr->_current_state;

                oContractStorage entry = cur_state->get_contractstorage_entry(Address(std::string(contract_address), AddressType::contract_address));
                if (NOT entry.valid())
                    return null_storage;

                auto iter = entry->contract_storages.find(std::string(name));
                if (iter == entry->contract_storages.end())
                    return null_storage;

                cdcchain::consensus::StorageDataType storage_data = iter->second;

                return cdcchain::consensus::StorageDataType::create_lua_storage_from_storage_data(L, storage_data);
            }

            bool UvmChainApi::commit_storage_changes_to_uvm(lua_State *L, AllContractsChangesMap &changes)
            {
                cdcchain::consensus::TransactionEvaluationState* eval_state_ptr =
                    (cdcchain::consensus::TransactionEvaluationState*)
                    (uvm::lua::lib::get_lua_state_value(L, "evaluate_state").pointer_value);

                if (!eval_state_ptr)
                    return false;

                for (auto all_con_chg_iter = changes.begin(); all_con_chg_iter != changes.end(); ++all_con_chg_iter)
                {
                    StorageOperation storage_op;
                    std::string contract_id = all_con_chg_iter->first;
                    ContractChangesMap contract_change = *(all_con_chg_iter->second);

                    storage_op.contract_id = Address(contract_id, AddressType::contract_address);

                    for (auto con_chg_iter = contract_change.begin(); con_chg_iter != contract_change.end(); ++con_chg_iter)
                    {
                        std::string contract_name = con_chg_iter->first;

                        StorageDataChangeType storage_change;
                        storage_change.storage_before = StorageDataType::get_storage_data_from_lua_storage(con_chg_iter->second.before);
                        storage_change.storage_after = StorageDataType::get_storage_data_from_lua_storage(con_chg_iter->second.after);

                        storage_op.contract_change_storages.insert(make_pair(contract_name, storage_change));
                    }

                    eval_state_ptr->p_result_trx.push_storage_operation(storage_op);
                }

                return true;
            }

            //not use
            bool UvmChainApi::register_storage(lua_State *L, const char *contract_name, const char *name)
            {
                // TODO
                printf("registered storage %s[%s] to cdcchain\n", contract_name, name);
                return true;
            }

            intptr_t UvmChainApi::register_object_in_pool(lua_State *L, intptr_t object_addr, UvmOutsideObjectTypes type)
			{
				auto node = uvm::lua::lib::get_lua_state_value_node(L, GLUA_OUTSIDE_OBJECT_POOLS_KEY);
				// Map<type, Map<object_key, object_addr>>
				std::map<UvmOutsideObjectTypes, std::shared_ptr<std::map<intptr_t, intptr_t>>> *object_pools = nullptr;
				if (node.type == UvmStateValueType::LUA_STATE_VALUE_nullptr)
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
				if (object_pools->find(type) == object_pools->end())
				{
					object_pools->emplace(std::make_pair(type, std::make_shared<std::map<intptr_t, intptr_t>>()));
				}
				auto pool = (*object_pools)[type];
				auto object_key = object_addr;
				(*pool)[object_key] = object_addr;
				return object_key;
			}

            intptr_t UvmChainApi::is_object_in_pool(lua_State *L, intptr_t object_key, UvmOutsideObjectTypes type)
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

            void UvmChainApi::release_objects_in_pool(lua_State *L)
			{
				auto node = uvm::lua::lib::get_lua_state_value_node(L, GLUA_OUTSIDE_OBJECT_POOLS_KEY);
				// Map<type, Map<object_key, object_addr>>
				std::map<UvmOutsideObjectTypes, std::shared_ptr<std::map<intptr_t, intptr_t>>> *object_pools = nullptr;
				if (node.type == UvmStateValueType::LUA_STATE_VALUE_nullptr)
				{
					return;
				}
				object_pools = (std::map<UvmOutsideObjectTypes, std::shared_ptr<std::map<intptr_t, intptr_t>>> *) node.value.pointer_value;
				// 对于object_pools中不同类型的对象，分别释放
				for (const auto &p : *object_pools)
				{
					auto type = p.first;
					auto pool = p.second;
					for (const auto &object_item : *pool)
					{
						auto object_key = object_item.first;
						auto object_addr = object_item.second;
						if (object_addr == 0)
							continue;
						switch (type)
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

            lua_Integer UvmChainApi::transfer_from_contract_to_address(lua_State *L, const char *contract_address, const char *to_address,
                const char *asset_type, int64_t amount)
            {
				uvm::lua::lib::increment_lvm_instructions_executed_count(L, CHAIN_GLUA_API_EACH_INSTRUCTIONS_COUNT - 1);
                //printf("contract transfer from %s to %s, asset[%s] amount %ld\n", contract_address, to_address, asset_type, amount_str);
                //return true;

                if (amount <= 0)
                    return -6;
                cdcchain::consensus::TransactionEvaluationState* eval_state_ptr =
                    (cdcchain::consensus::TransactionEvaluationState*)
                    (uvm::lua::lib::get_lua_state_value(L, "evaluate_state").pointer_value);

                if (!eval_state_ptr)
                {
                    L->force_stopping = true;
                    L->exit_code = LUA_API_INTERNAL_ERROR;
                    return -1;
                }


                string to_addr;
                string to_sub;
                wallet::Wallet::accountsplit(to_address, to_addr, to_sub);

                try
                {
                    if (!Address::is_valid(contract_address, CONTRACT_ADDRESS_PREFIX))
                        return -3;
                    if (!Address::is_valid(to_addr, CDC_ADDRESS_PREFIX))
                        return -4;

                    eval_state_ptr->transfer_asset_from_contract(amount, asset_type,
                        Address(string(contract_address), AddressType::contract_address), Address(to_addr, AddressType::cdc_address));

					eval_state_ptr->_contract_balance_remain -= amount;

                }
                catch (const fc::exception& err)
                {
                    switch (err.code())
                    {
                    case 31302:
                        return -2;
                    case 31003: //unknown balance entry
                        return -5;
                    case 31004:
                        return -5;
                    default:
                        L->force_stopping = true;
                        L->exit_code = LUA_API_INTERNAL_ERROR;
						return -1;
                    }
                }
                return 0;

            }

            lua_Integer UvmChainApi::transfer_from_contract_to_public_account(lua_State *L, const char *contract_address, const char *to_account_name,
                const char *asset_type, int64_t amount)
            {
				uvm::lua::lib::increment_lvm_instructions_executed_count(L, CHAIN_GLUA_API_EACH_INSTRUCTIONS_COUNT - 1);
                cdcchain::consensus::TransactionEvaluationState* eval_state_ptr =
                    (cdcchain::consensus::TransactionEvaluationState*)
                    (uvm::lua::lib::get_lua_state_value(L, "evaluate_state").pointer_value);

                if (!eval_state_ptr || !eval_state_ptr->_current_state)
                {
                    L->force_stopping = true;
                    L->exit_code = LUA_API_INTERNAL_ERROR;
                    return -1;
                }
                if (!eval_state_ptr->_current_state->is_valid_account_name(to_account_name))
                    return -7;
                auto acc_entry = eval_state_ptr->_current_state->get_account_entry(to_account_name);
                if (!acc_entry.valid())
                    return -7;
                return transfer_from_contract_to_address(L, contract_address, acc_entry->owner_address().AddressToString().c_str(), asset_type, amount);
            }

            int64_t UvmChainApi::get_contract_balance_amount(lua_State *L, const char *contract_address, const char* asset_symbol)
            {
				uvm::lua::lib::increment_lvm_instructions_executed_count(L, CHAIN_GLUA_API_EACH_INSTRUCTIONS_COUNT - 1);
                try{
                    cdcchain::consensus::TransactionEvaluationState* eval_state_ptr =
                        (cdcchain::consensus::TransactionEvaluationState*)
                        (uvm::lua::lib::get_lua_state_value(L, "evaluate_state").pointer_value);
                    cdcchain::consensus::ChainInterface* cur_state;
                    if (!eval_state_ptr || (cur_state = eval_state_ptr->_current_state) == NULL)
                    {
                        FC_CAPTURE_AND_THROW(lua_executor_internal_error, (""));
                    }

                    const auto asset_rec = cur_state->get_asset_entry(asset_symbol);
                    if (!asset_rec.valid() || asset_rec->id != 0)
                    {
                        FC_CAPTURE_AND_THROW(unknown_asset_id, ("Only CDC Allowed"));
                    }

                    BalanceIdType contract_balance_id = cur_state->get_balanceid(Address(string(contract_address), AddressType::contract_address), WithdrawBalanceTypes::withdraw_contract_type);
                    oBalanceEntry balance_entry = cur_state->get_balance_entry(contract_balance_id);

                    //if (!balance_entry.valid())
                    //    FC_CAPTURE_AND_THROW(unknown_balance_entry, ("Get balance entry failed"));

                    if (!balance_entry.valid())
                        return 0;

                    oAssetEntry asset_entry = cur_state->get_asset_entry(balance_entry->asset_id());
                    if (!asset_entry.valid() || asset_entry->id != 0)
                        FC_CAPTURE_AND_THROW(unknown_asset_id, ("asset error"));

                    Asset asset = balance_entry->get_spendable_balance(cur_state->now());

                    return asset.amount;
                }
                catch (const fc::exception& e)
                {
                    switch (e.code())
                    {
                    case 30028://invalid_address
                        return -2;
                    //case 31003://unknown_balance_entry
                    //    return -3;
                    case 31303:
                        return -1;
                    default:
                        L->force_stopping = true;
                        L->exit_code = LUA_API_INTERNAL_ERROR;
                        return -4;
                        break;
                    }
                }
            }

            int64_t UvmChainApi::get_transaction_fee(lua_State *L)
            {
				uvm::lua::lib::increment_lvm_instructions_executed_count(L, CHAIN_GLUA_API_EACH_INSTRUCTIONS_COUNT - 1);
                try{
                    cdcchain::consensus::TransactionEvaluationState* eval_state_ptr =
                        (cdcchain::consensus::TransactionEvaluationState*)
                        (uvm::lua::lib::get_lua_state_value(L, "evaluate_state").pointer_value);
                    ChainInterface*  db_interface = NULL;
                    if (!eval_state_ptr || !(db_interface = eval_state_ptr->_current_state))
                    {
                        FC_CAPTURE_AND_THROW(lua_executor_internal_error, (""));
                    }

                    Asset  fee = eval_state_ptr->_current_state->get_transaction_fee();
                    oAssetEntry ass_res = db_interface->get_asset_entry(fee.asset_id);
                    if (!ass_res.valid() || ass_res->precision == 0)
                        return -1;
                    return fee.amount;

                }
                catch (fc::exception e)
                {
                    L->force_stopping = true;
                    L->exit_code = LUA_API_INTERNAL_ERROR;
                    return -2;
                }
            }

            uint32_t UvmChainApi::get_chain_now(lua_State *L)
            {
				uvm::lua::lib::increment_lvm_instructions_executed_count(L, CHAIN_GLUA_API_EACH_INSTRUCTIONS_COUNT - 1);
                try{
                    cdcchain::consensus::TransactionEvaluationState* eval_state_ptr =
                        (cdcchain::consensus::TransactionEvaluationState*)
                        (uvm::lua::lib::get_lua_state_value(L, "evaluate_state").pointer_value);
                    cdcchain::consensus::ChainInterface* cur_state;
                    if (!eval_state_ptr || !(cur_state = eval_state_ptr->_current_state))
                    {
                        FC_CAPTURE_AND_THROW(lua_executor_internal_error, (""));
                    }
                    fc::time_point_sec time_stamp = cur_state->get_head_block_timestamp();
                    return time_stamp.sec_since_epoch();
                }
                catch (fc::exception e)
                {
                    L->force_stopping = true;
                    L->exit_code = LUA_API_INTERNAL_ERROR;
                    return 0;
                }
            }
            uint32_t UvmChainApi::get_chain_random(lua_State *L)
            {
				uvm::lua::lib::increment_lvm_instructions_executed_count(L, CHAIN_GLUA_API_EACH_INSTRUCTIONS_COUNT - 1);
                try{
                    cdcchain::consensus::TransactionEvaluationState* eval_state_ptr =
                        (cdcchain::consensus::TransactionEvaluationState*)
                        (uvm::lua::lib::get_lua_state_value(L, "evaluate_state").pointer_value);
                    cdcchain::consensus::ChainInterface* cur_state;
                    if (!eval_state_ptr || !(cur_state = eval_state_ptr->_current_state))
                    {
                        FC_CAPTURE_AND_THROW(lua_executor_internal_error, (""));
                    }

                    return eval_state_ptr->p_result_trx.id().hash(cur_state->get_current_random_seed())._hash[2];

                }
                catch (fc::exception e)
                {
                    L->force_stopping = true;
                    L->exit_code = LUA_API_INTERNAL_ERROR;
                    return 0;
                }
            }

            std::string UvmChainApi::get_transaction_id(lua_State *L)
            {
				uvm::lua::lib::increment_lvm_instructions_executed_count(L, CHAIN_GLUA_API_EACH_INSTRUCTIONS_COUNT - 1);
                try{
                    cdcchain::consensus::TransactionEvaluationState* eval_state_ptr =
                        (cdcchain::consensus::TransactionEvaluationState*)
                        (uvm::lua::lib::get_lua_state_value(L, "evaluate_state").pointer_value);

                    if (!eval_state_ptr)
                        FC_CAPTURE_AND_THROW(lua_executor_internal_error, (""));
                    return eval_state_ptr->trx.id().str();
                }
                catch (fc::exception e)
                {
                    L->force_stopping = true;
                    L->exit_code = LUA_API_INTERNAL_ERROR;
                    return "";
                }
            }


            uint32_t UvmChainApi::get_header_block_num(lua_State *L)
            {
				uvm::lua::lib::increment_lvm_instructions_executed_count(L, CHAIN_GLUA_API_EACH_INSTRUCTIONS_COUNT - 1);
                try{
                    cdcchain::consensus::TransactionEvaluationState* eval_state_ptr =
                        (cdcchain::consensus::TransactionEvaluationState*)
                        (uvm::lua::lib::get_lua_state_value(L, "evaluate_state").pointer_value);

                    if (!eval_state_ptr || !eval_state_ptr->_current_state)
                        FC_CAPTURE_AND_THROW(lua_executor_internal_error, (""));
                    return eval_state_ptr->_current_state->get_head_block_num();
                }
                catch (fc::exception e)
                {
                    L->force_stopping = true;
                    L->exit_code = LUA_API_INTERNAL_ERROR;
                    return 0;
                }
            }

            uint32_t UvmChainApi::wait_for_future_random(lua_State *L, int next)
            {
				uvm::lua::lib::increment_lvm_instructions_executed_count(L, CHAIN_GLUA_API_EACH_INSTRUCTIONS_COUNT - 1);
                try{
                    cdcchain::consensus::TransactionEvaluationState* eval_state_ptr =
                        (cdcchain::consensus::TransactionEvaluationState*)
                        (uvm::lua::lib::get_lua_state_value(L, "evaluate_state").pointer_value);

                    if (!eval_state_ptr || !eval_state_ptr->_current_state)
                        FC_CAPTURE_AND_THROW(lua_executor_internal_error, (""));

                    uint32_t target = eval_state_ptr->_current_state->get_head_block_num() + next;
                    if (target < next)
                        return 0;
                    return target;
                }
                catch (fc::exception e)
                {
                    L->force_stopping = true;
                    L->exit_code = LUA_API_INTERNAL_ERROR;
                    return 0;
                }
            }
            //获取指定块与之前50块的pre_secret hash出的结果，该值在指定块被产出的上一轮出块时就已经确定，而无人可知，无法操控
            //如果希望使用该值作为随机值，以随机值作为其他数据的选取依据时，需要在目标块被产出前确定要被筛选的数据
            //如投注彩票，只允许在目标块被产出前投注
            int32_t UvmChainApi::get_waited(lua_State *L, uint32_t num)
            {
				uvm::lua::lib::increment_lvm_instructions_executed_count(L, CHAIN_GLUA_API_EACH_INSTRUCTIONS_COUNT - 1);
                try{
                    if (num <= 1)
                        return -2;
                    cdcchain::consensus::TransactionEvaluationState* eval_state_ptr =
                        (cdcchain::consensus::TransactionEvaluationState*)
                        (uvm::lua::lib::get_lua_state_value(L, "evaluate_state").pointer_value);
                    cdcchain::consensus::ChainInterface* cur_state;
                    if (!eval_state_ptr || !(cur_state = eval_state_ptr->_current_state))
                        FC_CAPTURE_AND_THROW(lua_executor_internal_error, (""));
                    if (cur_state->get_head_block_num() < num)
                        return -1;
                    BlockIdType id = cur_state->get_block_id(num);
                    BlockHeader _header = cur_state->get_block_header(id);
                    SecretHashType _hash = _header.previous_secret;
                    auto default_id = BlockIdType();
                    for (int i = 0; i < 50; i++)
                    {
                        if ((id = _header.previous) == default_id)
                            break;
                        _header = cur_state->get_block_header(id);
                        _hash = _hash.hash(_header.previous_secret);
                    }
                    return _hash._hash[3] % (1 << 31 - 1);
                }
                catch (const fc::exception& e)
                {
                    L->force_stopping = true;
                    L->exit_code = LUA_API_INTERNAL_ERROR;
                    return -1;
                }
                //string get_wait
            }



            void UvmChainApi::emit(lua_State *L, const char* contract_id, const char* event_name, const char* event_param)
            {
				uvm::lua::lib::increment_lvm_instructions_executed_count(L, CHAIN_GLUA_API_EACH_INSTRUCTIONS_COUNT - 1);
                try {
                    cdcchain::consensus::TransactionEvaluationState* eval_state_ptr =
                        (cdcchain::consensus::TransactionEvaluationState*)
                        (uvm::lua::lib::get_lua_state_value(L, "evaluate_state").pointer_value);

                    if (eval_state_ptr == NULL)
                        FC_CAPTURE_AND_THROW(lua_executor_internal_error, (""));

                    EventOperation event_op(Address(string(contract_id), AddressType::contract_address), std::string(event_name), std::string(event_param));
                    eval_state_ptr->p_result_trx.push_event_operation(event_op);
                }
                catch (const fc::exception&)
                {
                    L->force_stopping = true;
                    L->exit_code = LUA_API_INTERNAL_ERROR;
                    return;
                }
            }

			bool UvmChainApi::is_valid_address(lua_State *L, const char *address_str)
			{
				std::string addr(address_str);
				return Address::is_valid(addr, CDC_ADDRESS_PREFIX) || Address::is_valid(addr, CONTRACT_ADDRESS_PREFIX);
			}

			bool UvmChainApi::is_valid_contract_address(lua_State *L, const char *address_str)
			{
				std::string addr(address_str);
				Address addr_obj(addr);
				return addr_obj.judge_addr_type(addr) == AddressType::contract_address;
			}

			const char * UvmChainApi::get_system_asset_symbol(lua_State *L)
			{
				return CDC_BLOCKCHAIN_SYMBOL;
			}

			uint64_t UvmChainApi::get_system_asset_precision(lua_State *L)
			{
				return CDC_BLOCKCHAIN_PRECISION;
			}


			// for CDC role
			// get
			std::vector<std::string> get_privilege_admin(lua_State *L)
			{
				uvm::lua::lib::increment_lvm_instructions_executed_count(L, CHAIN_GLUA_API_EACH_INSTRUCTIONS_COUNT - 1);
				try {
					cdcchain::consensus::TransactionEvaluationState* eval_state_ptr =
						(cdcchain::consensus::TransactionEvaluationState*)
						(uvm::lua::lib::get_lua_state_value(L, "evaluate_state").pointer_value);

					if (!eval_state_ptr || !eval_state_ptr->_current_state)
						FC_CAPTURE_AND_THROW(lua_executor_internal_error, (""));

					cdcchain::consensus::ChainDatabase* chain_database_ptr = 
						(cdcchain::consensus::ChainDatabase*)eval_state_ptr->_current_state->get_chain_database_ptr();

					if (!chain_database_ptr)
						FC_CAPTURE_AND_THROW(lua_executor_internal_error, (""));

					std::set<Address> privilege_admin_set = chain_database_ptr->get_roles_address_by_filter(RoleAuthEnum::privilege_admin);

					std::vector<std::string> privilege_admin_vec;
					for (auto& addr : privilege_admin_set)
						privilege_admin_vec.push_back(addr.AddressToString(AddressType::cdc_address));

					return privilege_admin_vec;
				}
				catch (fc::exception e)
				{
					L->force_stopping = true;
					L->exit_code = LUA_API_INTERNAL_ERROR;
					return std::vector<std::string>();
				}
			}
			std::vector<std::string> get_general_admin(lua_State *L)
			{
				uvm::lua::lib::increment_lvm_instructions_executed_count(L, CHAIN_GLUA_API_EACH_INSTRUCTIONS_COUNT - 1);
				try {
					cdcchain::consensus::TransactionEvaluationState* eval_state_ptr =
						(cdcchain::consensus::TransactionEvaluationState*)
						(uvm::lua::lib::get_lua_state_value(L, "evaluate_state").pointer_value);

					if (!eval_state_ptr || !eval_state_ptr->_current_state)
						FC_CAPTURE_AND_THROW(lua_executor_internal_error, (""));

					cdcchain::consensus::ChainDatabase* chain_database_ptr =
						(cdcchain::consensus::ChainDatabase*)eval_state_ptr->_current_state->get_chain_database_ptr();

					if (!chain_database_ptr)
						FC_CAPTURE_AND_THROW(lua_executor_internal_error, (""));

					std::set<Address> general_admin_set = chain_database_ptr->get_roles_address_by_filter(RoleAuthEnum::general_admin);

					std::vector<std::string> general_admin_vec;
					for (auto& addr : general_admin_set)
						general_admin_vec.push_back(addr.AddressToString(AddressType::cdc_address));

					return general_admin_vec;
				}
				catch (fc::exception e)
				{
					L->force_stopping = true;
					L->exit_code = LUA_API_INTERNAL_ERROR;
					return std::vector<std::string>();
				}
			}

			std::vector<std::string> get_mining_pool_admin(lua_State *L)
			{
				return std::vector<std::string>();
			}
			std::vector<std::string> get_statistics_pool_admin(lua_State *L)
			{
				return std::vector<std::string>();
			}
			std::vector<std::string> get_merchant_admin(lua_State *L)
			{
				return std::vector<std::string>();
			}
			std::vector<std::string> get_arbitrament_admin(lua_State *L)
			{
				return std::vector<std::string>();
			}

			std::vector<std::string> get_mining_pool_operator(lua_State *L)
			{
				return std::vector<std::string>();
			}
			std::vector<std::string> get_statistics_pool_operator(lua_State *L)
			{
				return std::vector<std::string>();
			}
			std::vector<std::string> get_merchant_operator(lua_State *L)
			{
				return std::vector<std::string>();
			}
			std::vector<std::string> get_arbitrament_operator(lua_State *L)
			{
				return std::vector<std::string>();
			}

			// verify
			int32_t verify_privilege_admin(lua_State *L, const char* verify_address)
			{
				return 0;
			}
			int32_t verify_general_admin(lua_State *L, const char* verify_address)
			{
				return 0;
			}
			int32_t verify_mining_pool_admin(lua_State *L, const char* verify_address)
			{
				return 0;
			}
			int32_t verify_statistics_pool_admin(lua_State *L, const char* verify_address)
			{
				return 0;
			}
			int32_t verify_merchant_admin(lua_State *L, const char* verify_address)
			{
				return 0;
			}
			int32_t verify_arbitrament_admin(lua_State *L, const char* verify_address)
			{
				return 0;
			}

			int32_t verify_mining_pool_operator(lua_State *L, const char* verify_address)
			{
				return 0;
			}
			int32_t verify_statistics_pool_operator(lua_State *L, const char* verify_address)
			{
				return 0;
			}
			int32_t verify_merchant_operator(lua_State *L, const char* verify_address)
			{
				return 0;
			}
			int32_t verify_arbitrament_operator(lua_State *L, const char* verify_address)
			{
				return 0;
			}

			// appoint
			int32_t appoint_mining_pool_admin(lua_State *L, const char* pool_admin)
			{
				return 0;
			}
			int32_t appoint_statistics_pool_admin(lua_State *L, const char* pool_admin)
			{
				return 0;
			}
			int32_t appoint_merchant_admin(lua_State *L, const char* merchant_admin)
			{
				return 0;
			}
			int32_t appoint_arbitrament_admin(lua_State *L, const char* arbitrament_admin)
			{
				return 0;
			}

			int32_t appoint_mining_pool_operator(lua_State *L, const char* pool_operator)
			{
				return 0;
			}
			int32_t appoint_statistics_pool_operator(lua_State *L, const char* pool_operator)
			{
				return 0;
			}
			int32_t appoint_merchant_operator(lua_State *L, const char* merchant_operator)
			{
				return 0;
			}
			int32_t appoint_arbitrament_operator(lua_State *L, const char* arbitrament_operator)
			{
				return 0;
			}

			// revoke
			int32_t revoke_mining_pool_admin(lua_State *L, const char* pool_admin)
			{
				return 0;
			}
			int32_t revoke_statistics_pool_admin(lua_State *L, const char* pool_admin)
			{
				return 0;
			}
			int32_t revoke_merchant_admin(lua_State *L, const char* merchant_admin)
			{
				return 0;
			}
			int32_t revoke_arbitrament_admin(lua_State *L, const char* arbitrament_admin)
			{
				return 0;
			}

			int32_t revoke_mining_pool_operator(lua_State *L, const char* pool_operator)
			{
				return 0;
			}
			int32_t revoke_statistics_pool_operator(lua_State *L, const char* pool_operator)
			{
				return 0;
			}
			int32_t revoke_merchant_operator(lua_State *L, const char* merchant_operator)
			{
				return 0;
			}
			int32_t revoke_arbitrament_operator(lua_State *L, const char* arbitrament_operator)
			{
				return 0;
			}

			// for CDC data
			// checkin
			int32_t checkin_user_receipt_hash(lua_State *L, const char* user_receipt_hash)
			{
				return 0;
			}
			int32_t checkin_mining_result_hash(lua_State *L, const char* mining_result_hash)
			{
				return 0;
			}
			int32_t checkin_ad_putting_feedback_hash(lua_State *L, const char* ad_putting_feedback_hash)
			{
				return 0;
			}
			int32_t checkin_ad_putting_result_hash(lua_State *L, const char* ad_putting_result_hash)
			{
				return 0;
			}

			// verify
			int32_t verify_user_receipt_hash(lua_State *L, const char* user_receipt_hash)
			{
				return 0;
			}
			int32_t verify_mining_result_hash(lua_State *L, const char* mining_result_hash)
			{
				return 0;
			}
			int32_t verify_ad_putting_feedback_hash(lua_State *L, const char* ad_putting_feedback_hash)
			{
				return 0;
			}
			int32_t verify_ad_putting_result_hash(lua_State *L, const char* ad_putting_result_hash)
			{
				return 0;
			}

			// abolish
			int32_t abolish_user_receipt_hash(lua_State *L, const char* user_receipt_hash)
			{
				return 0;
			}
			int32_t abolish_mining_result_hash(lua_State *L, const char* mining_result_hash)
			{
				return 0;
			}
			int32_t abolish_ad_putting_feedback_hash(lua_State *L, const char* ad_putting_feedback_hash)
			{
				return 0;
			}
			int32_t abolish_ad_putting_result_hash(lua_State *L, const char* ad_putting_result_hash)
			{
				return 0;
			}

		}
	}
}
