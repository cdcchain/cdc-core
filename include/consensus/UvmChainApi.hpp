﻿#pragma once

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


namespace cdcchain
{
	namespace lua
	{
		namespace api
		{
			// 这里是demo实现，需要具体重新实现这里所有API

			class UvmChainApi : public uvm::lua::api::IUvmChainApi
			{
			public:
				/**
				* check whether the contract apis limit over, in this lua_State
				* @param L the lua stack
				* @return TRUE(1 or not 0) if over limit(will break the vm), FALSE(0) if not over limit
				*/
				virtual int check_contract_api_instructions_over_limit(lua_State *L);

				/**
				* whether exception happen in L
				*/
				virtual bool has_exception(lua_State *L);

				/**
				* clear exception marked
				*/
				virtual void clear_exceptions(lua_State *L);


				/**
				* when exception happened, use this api to tell cdcchain
				* @param L the lua stack
				* @param code error code, 0 is OK, other is different error
				* @param error_format error info string, will be released by lua
				* @param ... error arguments
				*/
				virtual void throw_exception(lua_State *L, int code, const char *error_format, ...);

				/**
				* get contract info stored before from cdcchain api
				* @param name contract name
				* @param contract_info_ret this api save the contract's api name array here if found, this var will be free by this api
				* @return TRUE(1 or not 0) if success, FALSE(0) if failed
				*/
				virtual int get_stored_contract_info(lua_State *L, const char *name, std::shared_ptr<UvmContractInfo> contract_info_ret);

				virtual int get_stored_contract_info_by_address(lua_State *L, const char *address, std::shared_ptr<UvmContractInfo> contract_info_ret);

				virtual std::shared_ptr<UvmModuleByteStream> get_bytestream_from_code(lua_State *L, const uvm::blockchain::Code& code);
				/**
				* load contract lua byte stream from cdcchain api
				*/
				virtual std::shared_ptr<UvmModuleByteStream> open_contract(lua_State *L, const char *name);

				virtual std::shared_ptr<UvmModuleByteStream> open_contract_by_address(lua_State *L, const char *address);

				/**
				* get contract address/id from cdcchain by contract name
				*/
				virtual void get_contract_address_by_name(lua_State *L, const char *name, char *address, size_t *address_size);

				/*
				* check whether the contract exist
				*/
				virtual bool check_contract_exist(lua_State *L, const char *name);

				/**
				* check contract exist by ID string address
				*/
				virtual bool check_contract_exist_by_address(lua_State *L, const char *address);

				/**
				* store contract lua module byte stream to cdcchain api
				*/
				//int save_contract(lua_State *L, const char *name, UvmModuleByteStream *stream);

				/**
				* register new storage name of contract to cdcchain
				*/
				virtual bool register_storage(lua_State *L, const char *contract_name, const char *name);

				/**
				* directly get storage value from cdcchain
				*/
				//void free_contract_storage(lua_State *L, UvmStorageValue* storage);

				virtual UvmStorageValue get_storage_value_from_uvm(lua_State *L, const char *contract_name, std::string name);

				virtual UvmStorageValue get_storage_value_from_uvm_by_address(lua_State *L, const char *contract_address, std::string name);

				/**
				* after lua merge storage changes in lua_State, use the function to store the merged changes of storage to cdcchain
				*/
				virtual bool commit_storage_changes_to_uvm(lua_State *L, AllContractsChangesMap &changes);

				/**
				* 注册对象地址到关联lua_State的外部对象池（在外部创建的各种类型的对象）中，不同类型的对象需要一个单独的对象池
				* lua_State被释放的时候需要释放所有对象池中所有对象
				* 返回值是glua中用来操作这个对象的句柄/指针，目前只能是对象地址本身，以lightuserdata的形式存在于glua中
				*/
				virtual intptr_t register_object_in_pool(lua_State *L, intptr_t object_addr, UvmOutsideObjectTypes type);

				/**
				* 判断某个对象(register_object_in_pool的返回对象，一般实现为对象的内存地址)是否是关联lua_State中某个类型的对象池中的对象（从而可以判断是否可以强制转换)
				* 如果找到，返回对象地址，否则返回0
				*/
				virtual intptr_t is_object_in_pool(lua_State *L, intptr_t object_key, UvmOutsideObjectTypes type);

				/**
				* 释放lua_State关联的所有外部对象池中的对象已经对象池本身
				*/
				virtual void release_objects_in_pool(lua_State *L);

				/************************************************************************/
				/* transfer asset from contract by account address                      */
				/************************************************************************/
				virtual lua_Integer transfer_from_contract_to_address(lua_State *L, const char *contract_address, const char *to_address,
					const char *asset_type, int64_t amount);

				/************************************************************************/
				/* transfer asset from contract by account name on chain                */
				/************************************************************************/
				virtual lua_Integer transfer_from_contract_to_public_account(lua_State *L, const char *contract_address, const char *to_account_name,
					const char *asset_type, int64_t amount);

				virtual int64_t get_contract_balance_amount(lua_State *L, const char *contract_address, const char* asset_symbol);
				virtual int64_t get_transaction_fee(lua_State *L);
				virtual uint32_t get_chain_now(lua_State *L);
				virtual uint32_t get_chain_random(lua_State *L);
				virtual std::string get_transaction_id(lua_State *L);
				virtual uint32_t get_header_block_num(lua_State *L);
				virtual uint32_t wait_for_future_random(lua_State *L, int next);

				virtual int32_t get_waited(lua_State *L, uint32_t num);

				virtual void emit(lua_State *L, const char* contract_id, const char* event_name, const char* event_param);
				virtual bool is_valid_address(lua_State *L, const char *address_str);
				virtual bool is_valid_contract_address(lua_State *L, const char *address_str);
				virtual const char *get_system_asset_symbol(lua_State *L);
				virtual uint64_t get_system_asset_precision(lua_State *L);


				// for CDC role
				// get
				virtual std::vector<std::string> get_privilege_admin(lua_State *L);
				virtual std::vector<std::string> get_general_admin(lua_State *L);

				virtual std::vector<std::string> get_contract_admin(lua_State *L, _CON_ARG_ const char* contract_id);
				virtual std::vector<std::string> get_contract_operator(lua_State *L, _CON_ARG_ const char* contract_id);

				// verify
				virtual int32_t verify_privilege_admin(lua_State *L, const char* user_address);
				virtual int32_t verify_general_admin(lua_State *L, const char* user_address);

				virtual int32_t verify_contract_admin(lua_State *L, const char* user_address, _CON_ARG_ const char* contract_id);
				virtual int32_t verify_contract_operator(lua_State *L, const char* user_address, _CON_ARG_ const char* contract_id);

				// appoint
				virtual int32_t appoint_contract_admin(lua_State *L, uint32_t role_sub_type, const char* user_address, _CON_ARG_ const char* contract_id);
				virtual int32_t appoint_contract_operator(lua_State *L, uint32_t role_sub_type, const char* user_address, _CON_ARG_ const char* contract_id);

				// revoke
				virtual int32_t revoke_contract_admin(lua_State *L, const char* user_address, _CON_ARG_ const char* contract_id);
				virtual int32_t revoke_contract_operator(lua_State *L, const char* user_address, _CON_ARG_ const char* contract_id);


				// for CDC data
				// checkin
				virtual int32_t checkin_cdcdata_hash(lua_State *L, uint32_t cdcdata_type, const char* cdcdata_hash, const char* remark, _CON_ARG_ const char* caller_address);

				// verify
				virtual int32_t verify_cdcdata_hash(lua_State *L, uint32_t cdcdata_type, const char* cdcdata_hash);

				// abolish
				virtual int32_t abolish_cdcdata_hash(lua_State *L, uint32_t cdcdata_type, const char* cdcdata_hash);

			};

		}
	}
}
