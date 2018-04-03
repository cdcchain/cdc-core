// Copyright (c) 2017-2018 The CDC developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.


#include <client/Client.hpp>
#include <client/ClientImpl.hpp>

#include <consensus/Types.hpp>
#include <fc/reflect/variant.hpp>

#include <wallet/Wallet.hpp>

namespace cdcchain {
    namespace client {
        namespace detail {

            string ClientImpl::script_add(const fc::path& path, const string& desc)
            {
                // set limit in  simulator state
                if (_chain_db->get_is_in_simulator())
                    FC_THROW_EXCEPTION(simulator_command_forbidden, "in simulator, this command is forbidden, you cannot call it!");

                return Address(_wallet->script_add(path, desc)).AddressToString(AddressType::script_id);
            }
            void ClientImpl::script_remove(const string& script_id)
            {
                // set limit in  simulator state
                if (_chain_db->get_is_in_simulator())
                    FC_THROW_EXCEPTION(simulator_command_forbidden, "in simulator, this command is forbidden, you cannot call it!");

                _wallet->delete_script(ScriptIdType(script_id,AddressType::script_id));
            }
            ScriptEntryPrintable ClientImpl::script_get_info(const string& script_id)
            {
                // set limit in  simulator state
                if (_chain_db->get_is_in_simulator())
                    FC_THROW_EXCEPTION(simulator_command_forbidden, "in simulator, this command is forbidden, you cannot call it!");

                auto res = _wallet->get_script_entry(ScriptIdType(script_id, AddressType::script_id));
                if (res.valid())
                {
                    ScriptEntryPrintable res_printable(*res);
                    return res_printable;
                }

                FC_CAPTURE_AND_THROW(script_not_found_in_db, (("no such script in database")));
            }
            vector<ScriptEntryPrintable> ClientImpl::scripts_list()
            {
                // set limit in  simulator state
                if (_chain_db->get_is_in_simulator())
                    FC_THROW_EXCEPTION(simulator_command_forbidden, "in simulator, this command is forbidden, you cannot call it!");

                vector<ScriptEntryPrintable> res_printable_vec;

                for (auto res : _wallet->scripts_list())
                    res_printable_vec.push_back(ScriptEntryPrintable(res));

                return res_printable_vec;
            }
            void ClientImpl::script_disable(const string& id)
            {
                // set limit in  simulator state
                if (_chain_db->get_is_in_simulator())
                    FC_THROW_EXCEPTION(simulator_command_forbidden, "in simulator, this command is forbidden, you cannot call it!");

				try {
                _wallet->script_disable(ScriptIdType(id, AddressType::script_id));
				}
				catch (const invalid_address&)
				{
					FC_CAPTURE_AND_THROW(script_id_not_valid, ("id"));
				}
			
            }
            void ClientImpl::script_enable(const string& id)
            {
                // set limit in  simulator state
                if (_chain_db->get_is_in_simulator())
                    FC_THROW_EXCEPTION(simulator_command_forbidden, "in simulator, this command is forbidden, you cannot call it!");

				try {
					_wallet->script_enable(ScriptIdType(id, AddressType::script_id));
				}
				catch (const invalid_address&)
				{
					FC_CAPTURE_AND_THROW(script_id_not_valid, ("id"));
				}
            }
            void  ClientImpl::script_import_to_db(const fc::path& src_dir)
            {
                // set limit in  simulator state
                if (_chain_db->get_is_in_simulator())
                    FC_THROW_EXCEPTION(simulator_command_forbidden, "in simulator, this command is forbidden, you cannot call it!");

                _wallet->script_import_to_db(src_dir);
            }
            void  ClientImpl::script_export_from_db(const fc::path& dest_dir)
            {
                // set limit in  simulator state
                if (_chain_db->get_is_in_simulator())
                    FC_THROW_EXCEPTION(simulator_command_forbidden, "in simulator, this command is forbidden, you cannot call it!");

                _wallet->script_export_from_db(dest_dir);
            }

			std::vector<std::string> ClientImpl::script_list_event_handler(const string& contract_id_str, const std::string& event_type)
			{
				// set limit in  simulator state
				if (_chain_db->get_is_in_simulator())
					FC_THROW_EXCEPTION(simulator_command_forbidden, "in simulator, this command is forbidden, you cannot call it!");
				cdcchain::consensus::ContractIdType contract_id = get_contract_address(contract_id_str);
			
                auto idVec=_wallet->script_list_event_handler(contract_id, event_type);
                vector<string> res;
                for (auto id : idVec)
                {
                    res.push_back(id.AddressToString(script_id));
                }
                return res;
            }

            void ClientImpl::script_add_event_handler(const string& contract_id_str, const std::string& event_type, const string& script_id, uint32_t index)
            {
                // set limit in  simulator state
                if (_chain_db->get_is_in_simulator())
                    FC_THROW_EXCEPTION(simulator_command_forbidden, "in simulator, this command is forbidden, you cannot call it!");

                cdcchain::consensus::ContractIdType contract_id = cdcchain::consensus::Address(contract_id_str, cdcchain::consensus::AddressType::contract_address);
                _wallet->script_add_event_handler(contract_id, event_type, ScriptIdType(script_id, AddressType::script_id), index);
            }

            void ClientImpl::script_delete_event_handler(const string& contract_id_str, const std::string& event_type, const string& script_id)
            {
                // set limit in  simulator state
                if (_chain_db->get_is_in_simulator())
                    FC_THROW_EXCEPTION(simulator_command_forbidden, "in simulator, this command is forbidden, you cannot call it!");

                cdcchain::consensus::ContractIdType contract_id = cdcchain::consensus::Address(contract_id_str, cdcchain::consensus::AddressType::contract_address);
                _wallet->script_delete_event_handler(contract_id, event_type, ScriptIdType(script_id, AddressType::script_id));
            }
			std::vector<std::string> ClientImpl::script_get_events_bound(const std::string& script_id)
			{
				return _wallet->script_get_events_bound(script_id);
			}
        }
    }
}
