// Copyright (c) 2017-2018 The CDC developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.


#include <consensus/Exceptions.hpp>
#include <consensus/chainstate/PendingChainState.hpp>
#include <consensus/operation/ProposalOperations.hpp>


namespace cdcchain {
	namespace consensus {

		void ProposalForPrivilegeOperation::evaluate(TransactionEvaluationState& eval_state)const
		{
			FC_ASSERT(delegate_vote_need >= CDC_BLOCKCHAIN_NUM_DELEGATES / 2 + 1);
			FC_ASSERT(expected_end_time > start_time);
			FC_ASSERT(expected_end_time > eval_state._current_state->now());
			
			oRoleEntry role_entry = eval_state._current_state->get_role_entry(ContractIdType());
			if (role_entry.valid()) {
				for(const auto& role_cond: role_entry->role_cond_vec) {
					if (role_cond.role_address == candidate &&
						role_cond.role_type == RoleTypeEnum::privilege_admin)
						FC_CAPTURE_AND_THROW(is_privilege_admin, ("candidate has already been a privilege admin"));
				}
			}

			oAccountEntry account_entry = eval_state._current_state->get_account_entry(proposal_from);
			FC_ASSERT(account_entry.valid(), "proposal account must be registered account");
			
			bool active_delegate = eval_state._current_state->is_active_delegate(account_entry->id);
			FC_ASSERT(active_delegate, "proposal account must be active delegate");

			if (!eval_state.check_signature(proposal_from))
				FC_CAPTURE_AND_THROW(missing_signature, ("ProposalForPrivilege need proposal_from's signature"));

			ApplyForPrivilegeAdmin apply_for_privilege_admin(candidate, delegate_vote_need);
			ProposalCondition proposal_cond(apply_for_privilege_admin);

			ProposalEntry new_proposal_entry(proposal_cond, proposal_from, start_time, expected_end_time);
			ProposalIdType id = new_proposal_entry.id();
			
			oProposalEntry proposal_entry = eval_state._current_state->get_proposal_entry(id);
			FC_ASSERT(!proposal_entry.valid(), "ProposalEntry has existed"); 

			eval_state._current_state->store_proposal_entry(new_proposal_entry);
		}

		void ProposalRevokePrivilegeOperation::evaluate(TransactionEvaluationState& eval_state)const
		{
			FC_ASSERT(delegate_vote_need >= CDC_BLOCKCHAIN_NUM_DELEGATES / 2 + 1);
			FC_ASSERT(expected_end_time > start_time);
			FC_ASSERT(expected_end_time > eval_state._current_state->now());

			oRoleEntry role_entry = eval_state._current_state->get_role_entry(ContractIdType());
			if (!role_entry.valid())
				FC_CAPTURE_AND_THROW(is_not_privilege_admin, ("this address is not a privilege admin"));

			bool is_privilege_admin = false;
			for (const auto& role_cond : role_entry->role_cond_vec) {
				if (role_cond.role_address == privilege_admin &&
					role_cond.role_type == RoleTypeEnum::privilege_admin) {
					is_privilege_admin = true;
					break;
				}
			}

			if (NOT is_privilege_admin)
				FC_CAPTURE_AND_THROW(is_not_privilege_admin, ("this address is not a privilege admin"));

			oAccountEntry account_entry = eval_state._current_state->get_account_entry(proposal_from);
			FC_ASSERT(account_entry.valid(), "proposal account must be registered account");

			bool active_delegate = eval_state._current_state->is_active_delegate(account_entry->id);
			FC_ASSERT(active_delegate, "proposal account must be active delegate");

			if (!eval_state.check_signature(proposal_from))
				FC_CAPTURE_AND_THROW(missing_signature, ("ProposalRevokePrivilege need proposal_from's signature"));

			RevokePrivilegeAdmin revoke_privilege_admin(privilege_admin, delegate_vote_need);
			ProposalCondition proposal_cond(revoke_privilege_admin);

			ProposalEntry new_proposal_entry(proposal_cond, proposal_from, start_time, expected_end_time);
			ProposalIdType id = new_proposal_entry.id();

			oProposalEntry proposal_entry = eval_state._current_state->get_proposal_entry(id);
			FC_ASSERT(!proposal_entry.valid(), "proposal entry has existed already");

			eval_state._current_state->store_proposal_entry(new_proposal_entry);
		}

		void ProposalApproveOperation::evaluate(TransactionEvaluationState& eval_state)const
		{
			oProposalEntry proposal_entry = eval_state._current_state->get_proposal_entry(proposal_id);
			FC_ASSERT(proposal_entry.valid(), "can not find proposal entry");

			FC_ASSERT(proposal_entry->expected_end_time > eval_state._current_state->now(), "this proposal is outmoded");

			oAccountEntry account_entry = eval_state._current_state->get_account_entry(approver);
			FC_ASSERT(account_entry.valid(), "approver account must be registered account");

			bool active_delegate = eval_state._current_state->is_active_delegate(account_entry->id);
			FC_ASSERT(active_delegate, "approver account must be active delegate");

			if (!eval_state.check_signature(approver))
				FC_CAPTURE_AND_THROW(missing_signature, ("ProposalApproveOperation need approver's signature"));

			if (proposal_entry->proposal_voter.find(approver) != proposal_entry->proposal_voter.end())
				FC_CAPTURE_AND_THROW(duplicate_approver, ("the proposal has been approved before"));

			if (proposal_entry->proposal_condition.proposal_type == ProposalTypeEnum::apply_for_privilege_admin) {
				ApplyForPrivilegeAdmin apply_for_privilege_admin = proposal_entry->proposal_condition.as<ApplyForPrivilegeAdmin>();
				
				if (proposal_entry->proposal_voter.size() >= apply_for_privilege_admin.delegate_vote_need)
					FC_CAPTURE_AND_THROW(proposal_has_finished, ("this proposal has been finished"));

				// 判断是否已经是超级管理员   
				oRoleEntry role_entry = eval_state._current_state->get_role_entry(ContractIdType());
				if (role_entry.valid()) {
					for (const auto& role_cond : role_entry->role_cond_vec) {
						if (role_cond.role_address == apply_for_privilege_admin.candidate &&
							role_cond.role_type == RoleTypeEnum::privilege_admin)
							FC_CAPTURE_AND_THROW(is_privilege_admin, ("candidate has already been a privilege admin"));
					}
				}

				// change proposal entry
				proposal_entry->proposal_voter.insert(approver);
				eval_state._current_state->store_proposal_entry(*proposal_entry);

				// change role entry
				if (proposal_entry->proposal_voter.size() >= apply_for_privilege_admin.delegate_vote_need)
				{
					RoleEntry entry;
					oRoleEntry role_entry = eval_state._current_state->get_role_entry(ContractIdType());
					if (!role_entry.valid())
						entry.contract_id = ContractIdType();
					else
						entry = *role_entry;

					PrivilegeAdminRole privilege_admin;
					privilege_admin.gain_auth_time = eval_state._current_state->now();
					RoleCondition role_cond(apply_for_privilege_admin.candidate, RoleSubTypeEnum::sub_none, privilege_admin);

					entry.role_cond_vec.push_back(role_cond);
					entry.update_time = eval_state._current_state->now();

					eval_state._current_state->store_role_entry(entry);
				}
			}
			else if (proposal_entry->proposal_condition.proposal_type == ProposalTypeEnum::revoke_privilege_admin) {
				RevokePrivilegeAdmin revoke_privilege_admin = proposal_entry->proposal_condition.as<RevokePrivilegeAdmin>();

				if (proposal_entry->proposal_voter.size() >= revoke_privilege_admin.delegate_vote_need)
					FC_CAPTURE_AND_THROW(proposal_has_finished, ("this proposal has been finished"));

				// 判断是否已经不是超级管理员
				oRoleEntry role_entry = eval_state._current_state->get_role_entry(ContractIdType());
				if (!role_entry.valid())
					FC_CAPTURE_AND_THROW(is_not_privilege_admin, ("this address is not a privilege admin"));

				bool is_privilege_admin = false;
				for (const auto& role_cond : role_entry->role_cond_vec) {
					if (role_cond.role_address == revoke_privilege_admin.privilege_admin &&
						role_cond.role_type == RoleTypeEnum::privilege_admin) {
						is_privilege_admin = true;
						break;
					}
				}

				if (NOT is_privilege_admin)
					FC_CAPTURE_AND_THROW(is_not_privilege_admin, ("this address is not a privilege admin"));

				// change proposal entry
				proposal_entry->proposal_voter.insert(approver);
				eval_state._current_state->store_proposal_entry(*proposal_entry);

				// change role entry
				if (proposal_entry->proposal_voter.size() >= revoke_privilege_admin.delegate_vote_need)
				{
					for (auto iter = role_entry->role_cond_vec.begin(); iter != role_entry->role_cond_vec.end(); ) {
						if (iter->role_address == revoke_privilege_admin.privilege_admin &&
							iter->role_type == RoleTypeEnum::privilege_admin) {
							iter = role_entry->role_cond_vec.erase(iter);
						}
						else {
							++iter;
						}
					}

					role_entry->update_time = eval_state._current_state->now();
					eval_state._current_state->store_role_entry(*role_entry);
				}
			}
			else {
				FC_CAPTURE_AND_THROW(invalid_proposal_type, ("this proposal type is not support right now"));
			}
				
		}
	}
}