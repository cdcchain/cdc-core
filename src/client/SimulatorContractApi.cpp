#include <client/Client.hpp>
#include <client/ClientImpl.hpp>
#include <wallet/Exceptions.hpp>

#include <fc/reflect/variant.hpp>

#include <fc/thread/non_preemptable_scope_check.hpp>
#include "console/Locale.hpp"

#include <uvm/uvm_api.h>
#include <uvm/uvm_lib.h>
#include <fc/exception/exception.hpp>

#include <boost/uuid/sha1.hpp>
#include "consensus/operation/ContractOperations.hpp"

#include <utilities/CommonApi.hpp>

namespace cdcchain
{
    namespace client
    {
        namespace detail
        {
            void ClientImpl::simulator_open() const
            {
                FC_ASSERT(_wallet->is_open(), "Wallet not open!");
                FC_ASSERT(_wallet->is_unlocked(), "Wallet not unlock!");

                //for call simulator_open again in rpc 
                if (_chain_db->get_is_in_simulator())
                    FC_THROW_EXCEPTION(simulator_reopen, "you have opened simulator already!");

                _chain_db->set_is_in_simulator(true);
                _chain_db->get_simulator_pending_state();
                _chain_db->store_balance_entries_for_simulator();
                _chain_db->store_account_entries_for_simulator(_wallet->list_accounts());
            }

            void ClientImpl::simulator_close() const
            {
                // for all simulator_close again in rpc
                if (false == _chain_db->get_is_in_simulator())
                    FC_THROW_EXCEPTION(simulator_reclose, "you have closed simulator already!");

                _chain_db->set_is_in_simulator(false);
                _chain_db->clear_simulator_pending_state();
            }

            ChainInterfacePtr ClientImpl::simulator_get_correct_state_ptr() const
            {

                if (_chain_db->get_is_in_simulator())
                    return _chain_db->get_simulator_pending_state();

                return _chain_db;
            }

            Address ClientImpl::simulator_get_contract_address(const string& contract) const
            {
                Address contract_address;
                bool is_addr = contract_address.is_valid(contract, CONTRACT_ADDRESS_PREFIX);

                ChainInterfacePtr data_ptr = simulator_get_correct_state_ptr();
                return get_contract_address(contract, data_ptr);
            }

            ContractEntryPrintable ClientImpl::simulator_contract_load_to_file(const string &contract, const fc::path &file)
            {
                return contract_load_to_file(contract, file);
            }

            fc::path ClientImpl::simulator_contract_compile(const fc::path& filename) const
            {
                return contract_compile_helper(filename);
            }

            std::string ClientImpl::simulator_contract_register(const std::string& owner,
                const fc::path& codefile,
                const std::string& asset_symbol,
                const fc::optional<double>& init_limit)
            {
                string codefile_str = codefile.string();
                size_t pos = codefile_str.find_last_of('.');
                if ((pos == string::npos) || codefile_str.substr(pos) != ".gpc")
                {
                    FC_THROW_EXCEPTION(cdcchain::consensus::invalid_contract_filename, "contract bytecode file name should end with .gpc");
                }

                auto entry = _wallet->contract_register(owner,
                    codefile,
                    asset_symbol,
                    *init_limit);

                PendingChainStatePtr simulator_state = _chain_db->get_simulator_pending_state();
                simulator_state->simulator_evaluate_transaction(entry.trx, CDC_BLOCKCHAIN_DEFAULT_RELAY_FEE);

                return entry.trx.operations[0].as<RegisterContractOperation>().get_contract_id().AddressToString(AddressType::contract_address);
            }

            std::vector<cdcchain::consensus::Asset> ClientImpl::simulator_contract_register_testing(
                const std::string& owner,
                const fc::path& codefile)
            {
                return _wallet->contract_register_testing(owner, codefile);
            }

            cdcchain::wallet::WalletTransactionEntry ClientImpl::simulator_contract_call(const std::string& contract, const std::string& caller_name, const std::string& function_name, const std::string& params, const std::string& asset_symbol, const fc::optional<double>& call_limit)
            {
                Address contract_address = simulator_get_contract_address(contract);

                if (params.length() > CONTRACT_PARAM_MAX_LEN)
                    FC_CAPTURE_AND_THROW(contract_parameter_length_over_limit, ("the parameter length of contract function is over limit"));

                if (CallContractOperation::is_function_not_allow_call(function_name))
                {
                    FC_CAPTURE_AND_THROW(method_can_not_be_called_explicitly, (function_name)("method can't be called explicitly !"));
                }

                auto entry = _wallet->contract_call(caller_name, contract_address, function_name, params, asset_symbol, *call_limit);

                PendingChainStatePtr simulator_state = _chain_db->get_simulator_pending_state();
                simulator_state->simulator_evaluate_transaction(entry.trx, CDC_BLOCKCHAIN_DEFAULT_RELAY_FEE);
                return entry;
            }

            std::vector<cdcchain::consensus::Asset> ClientImpl::simulator_contract_call_testing(const std::string& contract, const std::string& caller_name, const std::string& function_name, const std::string& params)
            {
                Address contract_address;
                contract_address = simulator_get_contract_address(contract);
                return _wallet->contract_call_testing(caller_name, contract_address, function_name, params);
            }

			std::vector<cdcchain::consensus::Asset> ClientImpl::simulator_contract_upgrade_testing(const std::string& contract_address, const std::string& upgrader_name, const std::string& new_contract_name, const std::string& new_contract_desc)
			{
				Address addr;

				FC_ASSERT(addr.is_valid(contract_address, CONTRACT_ADDRESS_PREFIX), "contract address not valid");
				addr = Address(contract_address, AddressType::contract_address);
		
				return _wallet->contract_upgrade_testing(addr, upgrader_name, new_contract_name, new_contract_desc);
			}

            cdcchain::wallet::WalletTransactionEntry ClientImpl::simulator_contract_upgrade(const std::string& contract_address,
                const std::string& upgrader_name,
                const std::string& new_contract_name,
                const std::string& new_contract_desc,
				const std::string& asset_symbol,
				const fc::optional<double>& exec_limit)
            {
                Address addr;

                FC_ASSERT(addr.is_valid(contract_address, CONTRACT_ADDRESS_PREFIX), "contract address not valid");
                addr = Address(contract_address, AddressType::contract_address);

                auto entry = _wallet->contract_upgrade(addr,
                    upgrader_name,
                    new_contract_name,
                    new_contract_desc,
					asset_symbol,
					*exec_limit
					);

                PendingChainStatePtr simulator_state = _chain_db->get_simulator_pending_state();
                simulator_state->simulator_evaluate_transaction(entry.trx, CDC_BLOCKCHAIN_DEFAULT_RELAY_FEE);

                return entry;
            }

			std::vector<cdcchain::consensus::Asset> ClientImpl::simulator_contract_destroy_testing(const std::string& contract_address, const std::string& destroyer_name)
			{
				Address addr;

				FC_ASSERT(addr.is_valid(contract_address, CONTRACT_ADDRESS_PREFIX), "contract address not valid");
				addr = Address(contract_address, AddressType::contract_address);
				
				return _wallet->contract_destroy_testing(addr, destroyer_name);
			}

            cdcchain::wallet::WalletTransactionEntry ClientImpl::simulator_contract_destroy(const std::string& contract_address,
				const std::string& destroyer_name, const std::string& asset_symbol, const fc::optional<double>& exec_limit)
            {
                Address addr;

                FC_ASSERT(addr.is_valid(contract_address, CONTRACT_ADDRESS_PREFIX), "contract address not valid");
                addr = Address(contract_address, AddressType::contract_address);

                auto entry = _wallet->contract_destroy(addr,
                    destroyer_name,
					asset_symbol,
					*exec_limit
                    );

                PendingChainStatePtr simulator_state = _chain_db->get_simulator_pending_state();
                simulator_state->simulator_evaluate_transaction(entry.trx, CDC_BLOCKCHAIN_DEFAULT_RELAY_FEE);

                return entry;
            }

            cdcchain::consensus::ContractEntryPrintable ClientImpl::simulator_contract_get_info(const std::string& contract)
            {
                Address contract_address = simulator_get_contract_address(contract);
                ChainInterfacePtr data_ptr = simulator_get_correct_state_ptr();

                cdcchain::consensus::oContractEntry entry = data_ptr->get_contract_entry(contract_address);

                FC_ASSERT(entry.valid());

                ContractEntryPrintable print_entry(*entry);

				cdcchain::consensus::oAccountEntry account_entry = _chain_db->get_account_entry(print_entry.owner_address);
				if (account_entry.valid())
					print_entry.owner_name = account_entry->name;

                return print_entry;
            }

            CodePrintAble ClientImpl::contract_get_info_from_gpc_file(const fc::path &file)
            {
                //check file path & name is valid
                std::string file_str = file.string();
                const auto pos = file_str.find_last_of('.');
                FC_ASSERT(pos != std::string::npos && file_str.substr(pos) == ".gpc", "file name is invalid!");

                uvm::blockchain::Code code;
                /************************************************************************/
                /*        get contract entry from file                                  */
                /************************************************************************/
                unsigned int digest[5];

                FILE * fd = fopen(file_str.c_str(), "rb");
                if (NULL == fd)
                    FC_THROW_EXCEPTION(fc::file_not_found_exception, "file not found!");

                //get digest

                for (int i = 0; i < 5; ++i)
                {
                    cdcchain::utilities::common_fread_int(fd, (int*)&digest[i]);
                    unsigned char chr1 = (digest[i] & 0xFF000000) >> 24;
                    unsigned char chr2 = (digest[i] & 0x00FF0000) >> 16;
                    unsigned char chr3 = (digest[i] & 0x0000FF00) >> 8;
                    unsigned char chr4 = (digest[i] & 0x000000FF);

                    code.code_hash += to_printable_hex(chr1) + to_printable_hex(chr2) +
                        to_printable_hex(chr3) + to_printable_hex(chr4);
                }

                //read byte_code
                int byte_code_len;
                cdcchain::utilities::common_fread_int(fd, &byte_code_len);
                code.byte_code.resize(byte_code_len);
                cdcchain::utilities::common_fread_octets(fd, code.byte_code.data(), byte_code_len);

                //read api and offline_api
                int api_count;
                cdcchain::utilities::common_fread_int(fd, &api_count);
                for (int i = 0; i < api_count; ++i)
                {
                    int api_len;
                    cdcchain::utilities::common_fread_int(fd, &api_len);
                    std::string abi_str;
                    abi_str.resize(api_len);
                    cdcchain::utilities::common_fread_octets(fd, (void*)(abi_str.data()), api_len);
                    code.abi.insert(abi_str);
                }

                int offline_api_count;
                cdcchain::utilities::common_fread_int(fd, &offline_api_count);
                for (int i = 0; i < offline_api_count; ++i)
                {
                    int offline_api_len;
                    cdcchain::utilities::common_fread_int(fd, &offline_api_len);
                    std::string offline_abi_str;
                    offline_abi_str.resize(offline_api_len);
                    cdcchain::utilities::common_fread_octets(fd, (void*)offline_abi_str.data(), offline_api_len);
                    code.offline_abi.insert(offline_abi_str);
                }

                //read event api
                int event_count;
                cdcchain::utilities::common_fread_int(fd, &event_count);
                for (int i = 0; i < event_count; ++i)
                {
                    int event_len;
                    cdcchain::utilities::common_fread_int(fd, &event_len);
                    std::string event_str;
                    event_str.resize(event_len);
                    cdcchain::utilities::common_fread_octets(fd, (void*)event_str.data(), event_len);
                    code.events.insert(event_str);
                }

                //read storage info
                int storage_info_count;
                cdcchain::utilities::common_fread_int(fd, &storage_info_count);
                for (int i = 0; i < storage_info_count; ++i)
                {
                    int storage_name_len;
                    cdcchain::utilities::common_fread_int(fd, &storage_name_len);
                    std::string storage_name;
                    storage_name.resize(storage_name_len);
                    cdcchain::utilities::common_fread_octets(fd, (void*)storage_name.data(), storage_name_len);
                    
                    cdcchain::consensus::StorageValueTypes storage_type;
                    cdcchain::utilities::common_fread_int(fd, (int*)&storage_type);
                    code.storage_properties.insert(make_pair(storage_name, storage_type));
                }

                fclose(fd);

                return CodePrintAble(code);

            }

            std::vector<cdcchain::consensus::BalanceEntry> ClientImpl::simulator_contract_get_balance(const std::string& contract)
            {
                std::vector<cdcchain::consensus::BalanceEntry> entry_list;

                Address contract_address = simulator_get_contract_address(contract);
                ChainInterfacePtr data_ptr = simulator_get_correct_state_ptr();


                BalanceIdType contract_balance_id = data_ptr->get_balanceid(contract_address, WithdrawBalanceTypes::withdraw_contract_type);
                oBalanceEntry entry = data_ptr->get_balance_entry(contract_balance_id);
                if (entry.valid())
                    entry_list.emplace_back(*entry);
                else
                    entry_list.emplace_back(BalanceEntry());

                BalanceIdType margin_balance_id = data_ptr->get_balanceid(contract_address, WithdrawBalanceTypes::withdraw_margin_type);
                entry = data_ptr->get_balance_entry(margin_balance_id);
                if (entry.valid())
                    entry_list.emplace_back(*entry);
                else
                    entry_list.emplace_back(BalanceEntry());

                return entry_list;

            }

            WalletTransactionEntry  ClientImpl::simulator_transfer_to_contract(double amount_to_transfer,
                const string& asset_symbol,
                const string& from_account_name,
                const string& to_contract,
                double amount_for_exec)
            {
                Address contract_address = simulator_get_contract_address(to_contract);

                auto entry = _wallet->transfer_asset_to_contract(amount_to_transfer,
                    asset_symbol,
                    from_account_name,
                    contract_address,
                    amount_for_exec,
                    true);

                PendingChainStatePtr simulator_state = _chain_db->get_simulator_pending_state();
                simulator_state->simulator_evaluate_transaction(entry.trx, CDC_BLOCKCHAIN_DEFAULT_RELAY_FEE);

                return entry;
            }

            std::vector<cdcchain::consensus::Asset> ClientImpl::simulator_transfer_to_contract_testing(
                double amount_to_transfer,
                const string& asset_symbol,
                const string& from_account_name,
                const string& to_contract)
            {
                Address contract_address;

                contract_address = simulator_get_contract_address(to_contract);

                return _wallet->transfer_asset_to_contract_testing(amount_to_transfer,
                    asset_symbol,
                    from_account_name,
                    contract_address,
                    true);
            }

            AccountBalanceSummaryType ClientImpl::simulator_account_balance(const string &account_name)
            {
                try
                {
                    // set the balances state for simulator
                    PendingChainStatePtr simulator_state = _chain_db->get_simulator_pending_state();

					if (!account_name.empty() && !simulator_state->is_valid_account_name(account_name))
						FC_THROW_EXCEPTION(invalid_name, "Invalid account name!", ("account_name", account_name));

                    map<string, map<AssetIdType, ShareType>> balances;

                    vector<std::pair<std::string, BalanceEntry>> account_balances;
                    const time_point_sec now = simulator_state->now();

                    for (auto iter = simulator_state->_balance_id_to_entry.begin(); iter != simulator_state->_balance_id_to_entry.end(); ++iter)
                    {
                        auto entry = iter->second;

                        if (entry.condition.type != withdraw_signature_type) continue;

                        const Asset balance = entry.get_spendable_balance(now);
                        if (balance.amount == 0) continue;

                        const optional<Address> owner = entry.owner();
                        if (!owner.valid()) continue;

                        const oWalletKeyEntry key_entry = _wallet->get_wallet_db().lookup_key(*owner);
                        if (!key_entry.valid() || !key_entry->has_private_key()) continue;

                        const oWalletAccountEntry account_entry = _wallet->get_wallet_db().lookup_account(key_entry->account_address);
                        const string name = account_entry.valid() ? account_entry->name : string(key_entry->public_key);
                        if (!account_name.empty() && name != account_name) continue;

                        account_balances.push_back(make_pair(name, entry));
                    }

                    // get the balance summary
                    for (const auto& entry : account_balances)
                    {
                        const Asset balance = entry.second.get_spendable_balance(simulator_state->now());
                        balances[entry.first][balance.asset_id] += balance.amount;
                    }

                    return balances;

                } FC_CAPTURE_AND_RETHROW()
            }

            std::vector<SimulatorAccountInfo> ClientImpl::simulator_list_my_addresses(const string& account_name)
            {
                try
                {
                    if (!account_name.empty() && !_chain_db->is_valid_account_name(account_name))
                        FC_THROW_EXCEPTION(invalid_name, "Invalid account name!", ("account_name", account_name));

                    // set the state for simulator
                    PendingChainStatePtr simulator_state = _chain_db->get_simulator_pending_state();
                    vector<SimulatorAccountInfo> result;

                    for (auto iter = simulator_state->_vec_wallet_accounts.begin(); iter != simulator_state->_vec_wallet_accounts.end(); ++iter)
                    {
                        if (!account_name.empty() && iter->name != account_name) continue;
                        result.push_back(*iter);
                    }

                    return result;
                }FC_CAPTURE_AND_RETHROW()

            }
        }//namespace detail	
    }//namespace client
}//namespace cdcchain

