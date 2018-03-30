#include <utilities/CommonApi.hpp>
#include <client/Client.hpp>
#include <client/ClientImpl.hpp>

namespace cdcchain {
	namespace client {
		namespace detail {

			cdcchain::consensus::ProposalIdType detail::ClientImpl::proposal_apply_for_privilege_admin(const std::string& caller_name, const std::string& candidate_address, uint32_t need_vote_count, uint32_t start_time, uint32_t expected_end_time)
			{
				// set limit in  simulator state
				if (_chain_db->get_is_in_simulator())
					FC_THROW_EXCEPTION(simulator_command_forbidden, "in simulator, this command is forbidden, you cannot call it!");

				FC_ASSERT(Address::is_valid(candidate_address), "invalid candidate_address");

				cdcchain::consensus::Address addr = Address(candidate_address, AddressType::cdc_address);
				ProposalIdType proposal_id;

				auto entry = _wallet->proposal_apply_for_privilege_admin(caller_name,
					addr,
					need_vote_count,
					start_time,
					expected_end_time, proposal_id);
				_wallet->cache_transaction(entry);
				network_broadcast_transaction(entry.trx);

				return proposal_id;
			}

			cdcchain::consensus::ProposalIdType detail::ClientImpl::proposal_revoke_privilege_admin(const std::string& caller_name, const std::string& privilege_admin_address, uint32_t need_vote_count, uint32_t start_time, uint32_t expected_end_time)
			{
				// set limit in  simulator state
				if (_chain_db->get_is_in_simulator())
					FC_THROW_EXCEPTION(simulator_command_forbidden, "in simulator, this command is forbidden, you cannot call it!");

				FC_ASSERT(Address::is_valid(privilege_admin_address), "invalid privilege_admin_address");

				cdcchain::consensus::Address addr = Address(privilege_admin_address, AddressType::cdc_address);
				ProposalIdType proposal_id;

				auto entry = _wallet->proposal_revoke_privilege_admin(caller_name,
					addr,
					need_vote_count,
					start_time,
					expected_end_time, proposal_id);
				_wallet->cache_transaction(entry);
				network_broadcast_transaction(entry.trx);

				return proposal_id;
			}

			cdcchain::wallet::WalletTransactionEntry detail::ClientImpl::proposal_approve(const std::string& caller_name, const std::string& proposal_id)
			{
				// set limit in  simulator state
				if (_chain_db->get_is_in_simulator())
					FC_THROW_EXCEPTION(simulator_command_forbidden, "in simulator, this command is forbidden, you cannot call it!");

				ProposalIdType id = variant(proposal_id).as<ProposalIdType>();

				auto entry = _wallet->proposal_approve(caller_name, id);
				_wallet->cache_transaction(entry);
				network_broadcast_transaction(entry.trx);

				return entry;
			}

			cdcchain::consensus::ProposalEntry detail::ClientImpl::proposal_get_info(const std::string& proposal_id) const
			{
				// set limit in  simulator state
				if (_chain_db->get_is_in_simulator())
					FC_THROW_EXCEPTION(simulator_command_forbidden, "in simulator, this command is forbidden, you cannot call it!");

				auto id_prefix = variant(proposal_id).as<ProposalIdType>();
				oProposalEntry oentry = _chain_db->get_proposal_entry(id_prefix);
				FC_ASSERT(oentry.valid(), "Proposal id not found!");
				return *oentry;
			}

			cdcchain::wallet::WalletTransactionEntry detail::ClientImpl::appoint_general_admin(const std::string& caller_name, const std::string& candidate_address) 
			{
				// set limit in  simulator state
				if (_chain_db->get_is_in_simulator())
					FC_THROW_EXCEPTION(simulator_command_forbidden, "in simulator, this command is forbidden, you cannot call it!");

				FC_ASSERT(Address::is_valid(candidate_address), "invalid candidate_address");

				cdcchain::consensus::Address addr = Address(candidate_address, AddressType::cdc_address);

				auto entry = _wallet->appoint_general_admin(caller_name, addr);
				_wallet->cache_transaction(entry);
				network_broadcast_transaction(entry.trx);

				return entry;
			}

			cdcchain::wallet::WalletTransactionEntry detail::ClientImpl::revoke_general_admin(const std::string& caller_name, const std::string& general_admin_address) 
			{
				// set limit in  simulator state
				if (_chain_db->get_is_in_simulator())
					FC_THROW_EXCEPTION(simulator_command_forbidden, "in simulator, this command is forbidden, you cannot call it!");

				FC_ASSERT(Address::is_valid(general_admin_address), "invalid general_admin_address");

				cdcchain::consensus::Address addr = Address(general_admin_address, AddressType::cdc_address);
				ProposalIdType proposal_id;

				auto entry = _wallet->revoke_general_admin(caller_name, addr);
				_wallet->cache_transaction(entry);
				network_broadcast_transaction(entry.trx);

				return entry;
			}

			std::vector<cdcchain::consensus::Address> detail::ClientImpl::get_all_privilege_admin() const
			{
				// set limit in  simulator state
				if (_chain_db->get_is_in_simulator())
					FC_THROW_EXCEPTION(simulator_command_forbidden, "in simulator, this command is forbidden, you cannot call it!");

				std::vector<cdcchain::consensus::Address> address_vec;

				auto role_entry = _chain_db->lookup<RoleEntry>(ContractIdType());
				if(!role_entry.valid())
					return std::vector<cdcchain::consensus::Address>();
				
				for (const auto& cond : role_entry->role_cond_vec) 
					if (cond.role_type == RoleTypeEnum::privilege_admin)
						address_vec.push_back(cond.role_address);
				
				return address_vec;
			}

			std::vector<cdcchain::consensus::Address> detail::ClientImpl::get_all_general_admin() const
			{
				// set limit in  simulator state
				if (_chain_db->get_is_in_simulator())
					FC_THROW_EXCEPTION(simulator_command_forbidden, "in simulator, this command is forbidden, you cannot call it!");

				std::vector<cdcchain::consensus::Address> address_vec;

				auto role_entry = _chain_db->lookup<RoleEntry>(ContractIdType());
				if (!role_entry.valid())
					return std::vector<cdcchain::consensus::Address>();

				for (const auto& cond : role_entry->role_cond_vec)
					if (cond.role_type == RoleTypeEnum::general_admin)
						address_vec.push_back(cond.role_address);

				return address_vec;
			}

		}
	}
} // namespace cdcchain::client::detail