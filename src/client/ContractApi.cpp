// Copyright (c) 2017-2018 The CDC developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.


#include <client/Client.hpp>
#include <client/ClientImpl.hpp>

#include <fc/reflect/variant.hpp>

#include <fc/thread/non_preemptable_scope_check.hpp>
#include "console/Locale.hpp"

#include <uvm/uvm_api.h>
#include <uvm/uvm_lib.h>
#include <uvm/uvm_lutil.h>
#include <fc/exception/exception.hpp>

#include <boost/uuid/sha1.hpp>
#include "consensus/operation/ContractOperations.hpp"
#include <utilities/CommonApi.hpp>


#define FREE_LUA_MODULE(p_lua_module) \
delete (p_lua_module);


namespace cdcchain {
    namespace client {
        namespace detail {

            void contract_compile_callback(lua_State *L, std::list<void*>*args_list)
            {
                if (args_list->empty())
                    return;

                UvmStateValue statevalue;
                statevalue.pointer_value = args_list->front();

                uvm::lua::lib::set_lua_state_value(L, "evaluate_state", statevalue, UvmStateValueType::LUA_STATE_VALUE_POINTER);
            }

            int ClientImpl::save_code_to_file(const string& name, UvmModuleByteStream *stream, char* err_msg) const
            {
                boost::uuids::detail::sha1 sha;
                unsigned int digest[5];

				UvmModuleByteStream* p_new_stream = new UvmModuleByteStream();
                if (NULL == p_new_stream)
                {
                    strcpy(err_msg, "malloc UvmModuleByteStream fail");
                    return -1;
                }
                p_new_stream->is_bytes = stream->is_bytes;
				p_new_stream->buff = stream->buff;
                for (int i = 0; i < stream->contract_apis.size(); ++i)
                {
                    int new_flag = 1;
                    for (int j = 0; j < stream->offline_apis.size(); ++j)
                    {
                        if (stream->contract_apis[i] == stream->offline_apis[j])
                        {
                            new_flag = 0;
                            continue;
                        }
                    }

                    if (new_flag)
                    {
						p_new_stream->contract_apis.push_back(stream->contract_apis[i]);
                    }
                }
                p_new_stream->offline_apis = stream->offline_apis;
                p_new_stream->contract_emit_events = stream->contract_emit_events;
                p_new_stream->contract_storage_properties = stream->contract_storage_properties;

                p_new_stream->contract_id = stream->contract_id;
                p_new_stream->contract_name = stream->contract_name;
                p_new_stream->contract_level = stream->contract_level;
                p_new_stream->contract_state = stream->contract_state;

                FILE *f = fopen(name.c_str(), "wb");
                if (NULL == f)
                {
                    delete (p_new_stream);
                    strcpy(err_msg, strerror(errno));
                    return -1;
                }

                sha.process_bytes(p_new_stream->buff.data(), p_new_stream->buff.size());
                sha.get_digest(digest);
                for (int i = 0; i < 5; ++i)
                    cdcchain::utilities::common_fwrite_int(f, (int*)&digest[i]);

				int p_new_stream_buf_size = (int) p_new_stream->buff.size();
                cdcchain::utilities::common_fwrite_int(f, &p_new_stream_buf_size);
				p_new_stream->buff.resize(p_new_stream_buf_size);
                cdcchain::utilities::common_fwrite_stream(f, p_new_stream->buff.data(), p_new_stream->buff.size());

                int contract_apis_count = (int)p_new_stream->contract_apis.size();
                cdcchain::utilities::common_fwrite_int(f, &contract_apis_count);
                for (int i = 0; i < contract_apis_count; ++i)
                {
                    int api_len = p_new_stream->contract_apis[i].length();
                    cdcchain::utilities::common_fwrite_int(f, &api_len);
                    cdcchain::utilities::common_fwrite_stream(f, p_new_stream->contract_apis[i].c_str(), api_len);
                }

                int offline_apis_count = (int)p_new_stream->offline_apis.size();
                cdcchain::utilities::common_fwrite_int(f, &offline_apis_count);
                for (int i = 0; i < offline_apis_count; ++i)
                {
                    int offline_api_len = p_new_stream->offline_apis[i].length();
                    cdcchain::utilities::common_fwrite_int(f, &offline_api_len);
                    cdcchain::utilities::common_fwrite_stream(f, p_new_stream->offline_apis[i].c_str(), offline_api_len);
                }

                int contract_emit_events_count = p_new_stream->contract_emit_events.size();
                cdcchain::utilities::common_fwrite_int(f, &contract_emit_events_count);
                for (int i = 0; i < contract_emit_events_count; ++i)
                {
                    int event_len = p_new_stream->contract_emit_events[i].length();
                    cdcchain::utilities::common_fwrite_int(f, &event_len);
                    cdcchain::utilities::common_fwrite_stream(f, p_new_stream->contract_emit_events[i].c_str(), event_len);
                }

                int contract_storage_properties_count = p_new_stream->contract_storage_properties.size();
                cdcchain::utilities::common_fwrite_int(f, &contract_storage_properties_count);
                for (const auto& storage_info : p_new_stream->contract_storage_properties)
                {
                    int storage_len = storage_info.first.length();
                    cdcchain::utilities::common_fwrite_int(f, &storage_len);
                    cdcchain::utilities::common_fwrite_stream(f, storage_info.first.c_str(), storage_len);
                    int storage_type = storage_info.second;
                    cdcchain::utilities::common_fwrite_int(f, &storage_type);
                }

                fclose(f);
                delete (p_new_stream);
                return 0;
            }

            ContractEntryPrintable ClientImpl::contract_load_to_file(const string &contract, const fc::path &file)
            {
                //get contract entry
                Address contract_address=get_contract_address(contract);
                oContractEntry contract_entry= _chain_db->get_contract_entry(contract_address);
                FC_ASSERT(contract_entry.valid(),"ALWAYS PASS");
                    

                //check file path & name is valid
                std::string file_str = file.string();
                const auto pos = file_str.find_last_of('.');
                FC_ASSERT(pos != std::string::npos && file_str.substr(pos) == ".gpc", "file name is invalid!");

                CodePrintAble code(contract_entry->code);

                /************************************************************************/
                /*        write contract entry to file                                  */
                /************************************************************************/
                boost::uuids::detail::sha1 sha;
                unsigned int digest[5];
                int byte_code_len = (int)contract_entry->code.byte_code.size();

                FILE* f = fopen(file_str.c_str(), "wb");
                if (NULL == f)
                    FC_THROW_EXCEPTION(fc::file_not_found_exception, "file not found!");

                
                sha.process_bytes(contract_entry->code.byte_code.data(), byte_code_len);
                sha.get_digest(digest);
                for (int i = 0; i < 5; ++i)
                    cdcchain::utilities::common_fwrite_int(f, (int*)&digest[i]);

                cdcchain::utilities::common_fwrite_int(f, &byte_code_len);
                cdcchain::utilities::common_fwrite_stream(f, contract_entry->code.byte_code.data(), byte_code_len);

                int contract_apis_count = (int)contract_entry->code.abi.size();
                cdcchain::utilities::common_fwrite_int(f, &contract_apis_count);
                for (const auto& abi: contract_entry->code.abi)
                {
                    int api_len = abi.length();
                    cdcchain::utilities::common_fwrite_int(f, &api_len);
                    cdcchain::utilities::common_fwrite_stream(f, abi.c_str(), api_len);
                }

                int offline_apis_count = (int)contract_entry->code.offline_abi.size();
                cdcchain::utilities::common_fwrite_int(f, &offline_apis_count);
                for (const auto& offline_abi: contract_entry->code.offline_abi)
                {
                    int offline_api_len = offline_abi.length();
                    cdcchain::utilities::common_fwrite_int(f, &offline_api_len);
                    cdcchain::utilities::common_fwrite_stream(f, offline_abi.c_str(), offline_api_len);
                }

                int contract_emit_events_count = (int)contract_entry->code.events.size();
                cdcchain::utilities::common_fwrite_int(f, &contract_emit_events_count);
                for (const auto& event: contract_entry->code.events)
                {
                    int event_len = event.length();
                    cdcchain::utilities::common_fwrite_int(f, &event_len);
                    cdcchain::utilities::common_fwrite_stream(f, event.c_str(), event_len);
                }

                int contract_storage_properties_count = (int)contract_entry->code.storage_properties.size();
                cdcchain::utilities::common_fwrite_int(f, &contract_storage_properties_count);
                for (const auto& storage_info : contract_entry->code.storage_properties)
                {
                    int storage_len = storage_info.first.length();
                    cdcchain::utilities::common_fwrite_int(f, &storage_len);
                    cdcchain::utilities::common_fwrite_stream(f, storage_info.first.c_str(), storage_len);
                    int storage_type = storage_info.second;
                    cdcchain::utilities::common_fwrite_int(f, &storage_type);
                }
                
                fclose(f);

                return ContractEntryPrintable(*contract_entry);
            }

            cdcchain::consensus::Address ClientImpl::get_contract_address(const string& contract,ChainInterfacePtr db) const
            {
                if (db == nullptr)
                {
                    db = _chain_db;
                }
                Address contract_address;
                oContractEntry contract_entry;
				bool is_addr = false;
				try {
					is_addr = contract_address.is_valid(contract, CONTRACT_ADDRESS_PREFIX);
				}
				catch (...) {
					is_addr = false;
				}
                bool is_name;
                if (is_addr)
                {
                    contract_address = Address(contract, AddressType::contract_address);

                    contract_entry = db->get_contract_entry(contract_address);
                    FC_ASSERT(contract_entry.valid(), "contract address not exist");
                }
                else if (is_name = db->is_valid_contract_name(contract), is_name)
                {
                    contract_entry = db->get_contract_entry(contract);
                    FC_ASSERT(contract_entry.valid(), "contract name not exist");
                    contract_address = Address(contract_entry->id);
                }
                else
                {
                    FC_ASSERT(false, "not valid contract name or address");
                }

                return contract_address;
            }

            fc::path ClientImpl::contract_compile_helper(const fc::path& filename) const
            {
                // if file not exist
                if (!fc::exists(filename))
                    FC_THROW_EXCEPTION(fc::file_not_found_exception, "the file not exist!");

                char err_msg[LUA_EXCEPTION_MULTILINE_STRNG_MAX_LENGTH + 1] = "\0";
                string filename_str = filename.string();
                string out_filename;

                size_t pos;
                pos = filename_str.find_last_of('.');
                if ((pos != string::npos) && (filename_str.substr(pos) == ".glua"|| filename_str.substr(pos) == ".lua"))
                {
                    out_filename = filename_str.substr(0, pos) + ".gpc";
                }
                else
                {
                    FC_THROW_EXCEPTION(cdcchain::consensus::invalid_contract_filename, "contract source file name should end with .lua or .glua");
                }

                UvmModuleByteStream* p_lua_module = new UvmModuleByteStream();
                FC_ASSERT(p_lua_module, "p_lua_module malloc fail!");

				ChainInterfacePtr data_ptr = _wallet->get_correct_state_ptr();
                PendingChainStatePtr          pend_state = std::make_shared<PendingChainState>(data_ptr);
                TransactionEvaluationStatePtr trx_eval_state = std::make_shared<TransactionEvaluationState>(pend_state.get());

                UvmStatePreProcessorFunction lua_state_pre;
                lua_state_pre.processor = contract_compile_callback;
                std::list<void*> args_list;
                args_list.push_back(trx_eval_state.get());
                lua_state_pre.args = args_list;

                uvm::util::TimeDiff time_diff;
                time_diff.start();
                if (false)
                {
                    delete p_lua_module;
					err_msg[LUA_EXCEPTION_MULTILINE_STRNG_MAX_LENGTH] = '\0';
                    FC_THROW_EXCEPTION(cdcchain::consensus::contract_compile_fail, err_msg);
                    
                }
                time_diff.end();
                std::cout << "compile using time " << time_diff.diff_timestamp() << "s" << std::endl;

                if (save_code_to_file(out_filename, p_lua_module, err_msg) < 0)
                {
                    delete p_lua_module;
					p_lua_module = nullptr;
					err_msg[LUA_EXCEPTION_MULTILINE_STRNG_MAX_LENGTH] = '\0';
                    FC_THROW_EXCEPTION(cdcchain::consensus::save_bytecode_to_gpcfile_fail, err_msg);
                }
				if(p_lua_module)
					delete p_lua_module;

                return fc::path(out_filename);
            }


			fc::path ClientImpl::contract_compile(const fc::path& filename) const
			{
				// set limit in  simulator state
				if (_chain_db->get_is_in_simulator())
					FC_THROW_EXCEPTION(simulator_command_forbidden, "in simulator, this command is forbidden, you cannot call it!");

				return contract_compile_helper(filename);
			}

            std::string ClientImpl::contract_register(
                const std::string& owner,
                const fc::path& codefile,
                const std::string& asset_symbol,
                const fc::optional<double>& init_limit)
            {
				// set limit in  simulator state
				if (_chain_db->get_is_in_simulator())
					FC_THROW_EXCEPTION(simulator_command_forbidden, "in simulator, this command is forbidden, you cannot call it!");

                auto entry = _wallet->contract_register(owner,
                    codefile,
                    asset_symbol,
                    *init_limit);

                _wallet->cache_transaction(entry,false);
                network_broadcast_transaction(entry.trx);
                return entry.trx.operations[0].as<RegisterContractOperation>().get_contract_id().AddressToString(AddressType::contract_address);
            }

            std::vector<cdcchain::consensus::Asset> ClientImpl::contract_register_testing(
                const std::string& owner,
                const fc::path& codefile)
            {
				// set limit in  simulator state
				if (_chain_db->get_is_in_simulator())
					FC_THROW_EXCEPTION(simulator_command_forbidden, "in simulator, this command is forbidden, you cannot call it!");

                return _wallet->contract_register_testing(owner, codefile);
            }

            cdcchain::wallet::WalletTransactionEntry ClientImpl::contract_call(const std::string& contract, const std::string& caller_name, const std::string& function_name, const std::string& params, const std::string& asset_symbol, const fc::optional<double>& call_limit)
            {
				// set limit in  simulator state
				if (_chain_db->get_is_in_simulator())
					FC_THROW_EXCEPTION(simulator_command_forbidden, "in simulator, this command is forbidden, you cannot call it!");

                Address contract_address;
                contract_address = get_contract_address(contract);
                auto entry = _wallet->contract_call(caller_name, contract_address, function_name, params, asset_symbol, *call_limit);
                _wallet->cache_transaction(entry,false);
                network_broadcast_transaction(entry.trx);
                return entry;
            }

            std::vector<cdcchain::consensus::Asset> ClientImpl::contract_call_testing(const std::string& contract, const std::string& caller_name, const std::string& function_name, const std::string& params)
            {
				// set limit in  simulator state
				if (_chain_db->get_is_in_simulator())
					FC_THROW_EXCEPTION(simulator_command_forbidden, "in simulator, this command is forbidden, you cannot call it!");

                Address contract_address;
                contract_address = get_contract_address(contract);
                return _wallet->contract_call_testing(caller_name, contract_address, function_name, params);
            }

            std::string ClientImpl::contract_call_offline(const std::string& contract, const std::string& caller_name, const std::string& function_name, const std::string& params)
            {
				// set limit in  simulator state
				if (_chain_db->get_is_in_simulator())
					FC_THROW_EXCEPTION(simulator_command_forbidden, "in simulator, this command is forbidden, you cannot call it!");

                Address contract_address;

                contract_address = get_contract_address(contract);

                return _wallet->contract_call_offline(caller_name, contract_address, function_name, params);
            }

            cdcchain::wallet::WalletTransactionEntry ClientImpl::contract_upgrade(
                const std::string& contract_address,
                const std::string& upgrader_name,
                const std::string& new_contract_name,
                const std::string& new_contract_desc,
				const std::string& asset_symbol,
				const fc::optional<double>& exec_limit)
            {

				// set limit in  simulator state
				if (_chain_db->get_is_in_simulator())
					FC_THROW_EXCEPTION(simulator_command_forbidden, "in simulator, this command is forbidden, you cannot call it!");

                Address addr;

                FC_ASSERT(addr.is_valid(contract_address, CONTRACT_ADDRESS_PREFIX), "contract address not valid");
                addr = Address(contract_address, AddressType::contract_address);

                auto entry = _wallet->contract_upgrade(addr,
                    upgrader_name,
                    new_contract_name,
                    new_contract_desc,
				    asset_symbol,
					*exec_limit);
                _wallet->cache_transaction(entry,false);
                network_broadcast_transaction(entry.trx);
                return entry;
            }

			std::vector<cdcchain::consensus::Asset> ClientImpl::contract_upgrade_testing(
				const std::string& contract_address,
				const std::string& upgrader_name,
				const std::string& new_contract_name,
				const std::string& new_contract_desc
				)
			{
				// set limit in  simulator state
				if (_chain_db->get_is_in_simulator())
					FC_THROW_EXCEPTION(simulator_command_forbidden, "in simulator, this command is forbidden, you cannot call it!");

				Address addr;

				FC_ASSERT(addr.is_valid(contract_address, CONTRACT_ADDRESS_PREFIX), "contract address not valid");
				addr = Address(contract_address, AddressType::contract_address);

				return _wallet->contract_upgrade_testing(addr, upgrader_name, new_contract_name, new_contract_desc);


			}
				

            cdcchain::wallet::WalletTransactionEntry ClientImpl::contract_destroy(
                const std::string& contract_address,
                const std::string& destroyer_name,
				const std::string& asset_symbol,
				const fc::optional<double>& exec_limit)
            {
				// set limit in  simulator state
				if (_chain_db->get_is_in_simulator())
					FC_THROW_EXCEPTION(simulator_command_forbidden, "in simulator, this command is forbidden, you cannot call it!");

                Address addr;

                FC_ASSERT(addr.is_valid(contract_address, CONTRACT_ADDRESS_PREFIX), "contract address not valid");
                addr = Address(contract_address, AddressType::contract_address);

                auto entry = _wallet->contract_destroy(addr,
                    destroyer_name,
					asset_symbol,
					*exec_limit
					);
                _wallet->cache_transaction(entry,false);
                network_broadcast_transaction(entry.trx);
                return entry;
            }

			std::vector<cdcchain::consensus::Asset> ClientImpl::contract_destroy_testing(const std::string& contract_address, const std::string& destroyer_name)
			{
				// set limit in  simulator state
				if (_chain_db->get_is_in_simulator())
					FC_THROW_EXCEPTION(simulator_command_forbidden, "in simulator, this command is forbidden, you cannot call it!");

				Address addr;

				FC_ASSERT(addr.is_valid(contract_address, CONTRACT_ADDRESS_PREFIX), "contract address not valid");
				addr = Address(contract_address, AddressType::contract_address);

			    return _wallet->contract_destroy_testing(addr, destroyer_name);

			}

            cdcchain::consensus::ContractEntryPrintable ClientImpl::contract_get_info(const std::string& contract)
            {
				// set limit in  simulator state
				if (_chain_db->get_is_in_simulator())
					FC_THROW_EXCEPTION(simulator_command_forbidden, "in simulator, this command is forbidden, you cannot call it!");

                Address contract_address;
                contract_address = get_contract_address(contract);

                cdcchain::consensus::oContractEntry entry = _chain_db->get_contract_entry(contract_address);
                FC_ASSERT(entry.valid());

                ContractEntryPrintable print_entry(*entry);

                cdcchain::consensus::oAccountEntry account_entry = _chain_db->get_account_entry(print_entry.owner_address);
                if (account_entry.valid())
                    print_entry.owner_name = account_entry->name;

                return print_entry;
            }

            std::vector<cdcchain::consensus::BalanceEntry> ClientImpl::contract_get_balance(const std::string& contract)
            {
				// set limit in  simulator state
				if (_chain_db->get_is_in_simulator())
					FC_THROW_EXCEPTION(simulator_command_forbidden, "in simulator, this command is forbidden, you cannot call it!");

                std::vector<cdcchain::consensus::BalanceEntry> entry_list;

                Address contract_address;

                contract_address = get_contract_address(contract);

                BalanceIdType contract_balance_id = _chain_db->get_balanceid(contract_address, WithdrawBalanceTypes::withdraw_contract_type);
                oBalanceEntry entry = _chain_db->get_balance_entry(contract_balance_id);
                if (entry.valid())
                    entry_list.emplace_back(*entry);
                else
                    entry_list.emplace_back(BalanceEntry());

                BalanceIdType margin_balance_id = _chain_db->get_balanceid(contract_address, WithdrawBalanceTypes::withdraw_margin_type);
                entry = _chain_db->get_balance_entry(margin_balance_id);
                if (entry.valid())
                    entry_list.emplace_back(*entry);
                else
                    entry_list.emplace_back(BalanceEntry());

                return entry_list;
            }

            WalletTransactionEntry detail::ClientImpl::wallet_transfer_to_contract(
                double amount_to_transfer,
                const string& asset_symbol,
                const string& from_account_name,
                const string& to_contract, double amount_for_exec)
            {
                // set limit in  simulator state
                if (_chain_db->get_is_in_simulator())
                    FC_THROW_EXCEPTION(simulator_command_forbidden, "in simulator, this command is forbidden, you cannot call it!");

                Address contract_address;

                contract_address = get_contract_address(to_contract);

                auto entry = _wallet->transfer_asset_to_contract(amount_to_transfer,
                    asset_symbol,
                    from_account_name,
                    contract_address, amount_for_exec,
                    true);
                _wallet->cache_transaction(entry,false);
                network_broadcast_transaction(entry.trx);
                return entry;
            }

            std::vector<cdcchain::consensus::Asset> ClientImpl::wallet_transfer_to_contract_testing(
                double amount_to_transfer,
                const string& asset_symbol,
                const string& from_account_name,
                const string& to_contract)
            {
                // set limit in  simulator state
                if (_chain_db->get_is_in_simulator())
                    FC_THROW_EXCEPTION(simulator_command_forbidden, "in simulator, this command is forbidden, you cannot call it!");

                Address contract_address;

                contract_address = get_contract_address(to_contract);

                return _wallet->transfer_asset_to_contract_testing(amount_to_transfer,
                    asset_symbol,
                    from_account_name,
                    contract_address,
                    true);
            }

			cdcchain::consensus::TransactionIdType ClientImpl::get_result_trx_id(const cdcchain::consensus::TransactionIdType& id)
			{
				// set limit in  simulator state
				if (_chain_db->get_is_in_simulator())
					FC_THROW_EXCEPTION(simulator_command_forbidden, "in simulator, this command is forbidden, you cannot call it!");

				auto res=_chain_db->lookup<ResultTIdEntry>(id);
				if (!res.valid() || res->res == TransactionIdType())
					FC_CAPTURE_AND_THROW(Result_trx_id_not_found);
				return res->res;
			}
			cdcchain::consensus::TransactionIdType ClientImpl::get_request_trx_id(const cdcchain::consensus::TransactionIdType& id)
			{
				// set limit in  simulator state
				if (_chain_db->get_is_in_simulator())
					FC_THROW_EXCEPTION(simulator_command_forbidden, "in simulator, this command is forbidden, you cannot call it!");

				auto res = _chain_db->lookup<RequestIdEntry>(id);
				if (!res.valid() || res->req == TransactionIdType())
					FC_CAPTURE_AND_THROW(Request_trx_id_not_found);
				return res->req;
			}

			std::string ClientImpl::get_contract_registered_in_transaction(const cdcchain::consensus::TransactionIdType& trx_id)
			{
				// set limit in  simulator state
				if (_chain_db->get_is_in_simulator())
					FC_THROW_EXCEPTION(simulator_command_forbidden, "in simulator, this command is forbidden, you cannot call it!");

				auto res=_chain_db->lookup<ContractinTrxEntry>(trx_id);
				if (!res.valid() || res->contract_id == ContractIdType())
					FC_CAPTURE_AND_THROW(no_contract_registered_in_this_transaction);
				return  res->contract_id.AddressToString(AddressType::contract_address);

			}

			cdcchain::consensus::TransactionIdType ClientImpl::get_transaction_id_contract_registered(const std::string& contract_id)
			{
				// set limit in  simulator state
				if (_chain_db->get_is_in_simulator())
					FC_THROW_EXCEPTION(simulator_command_forbidden, "in simulator, this command is forbidden, you cannot call it!");

				ContractIdType id(contract_id, AddressType::contract_address);
				auto res = _chain_db->lookup<ContractTrxEntry>(id);
				if (!res.valid() || res->trx_id == TransactionIdType())
					FC_CAPTURE_AND_THROW(transaction_contract_registered_in_not_found);
				return res->trx_id;
			}


        }
    }
} // namespace cdcchain::client::detail
