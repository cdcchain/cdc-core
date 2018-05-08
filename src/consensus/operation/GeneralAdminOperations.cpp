// Copyright (c) 2017-2018 The CDC developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.


#include <consensus/Exceptions.hpp>
#include <consensus/chainstate/PendingChainState.hpp>
#include <consensus/operation/GeneralAdminOperations.hpp>


namespace cdcchain {
	namespace consensus {

		void AppointGeneralAdminOperation::evaluate(TransactionEvaluationState& eval_state)const
		{
			oAccountEntry account_entry = eval_state._current_state->get_account_entry(appointer);
			FC_ASSERT(account_entry.valid(), "appointer must be registered account");

			bool active_delegate = eval_state._current_state->is_active_delegate(account_entry->id);
			FC_ASSERT(active_delegate, "appointer must be active delegate");

			if (!eval_state.check_signature(appointer))
				FC_CAPTURE_AND_THROW(missing_signature, ("AppointGeneralAdminOperation need appointer's signature"));

			// 判断是否已经是管理员
			oRoleEntry role_entry = eval_state._current_state->get_role_entry(ContractIdType());
			RoleEntry entry;
			if (role_entry.valid()) {
				for (const auto& role_cond : role_entry->role_cond_vec) {
					if (role_cond.role_address == candidate &&
						role_cond.role_type == RoleTypeEnum::general_admin)
						FC_CAPTURE_AND_THROW(is_general_admin, ("candidate has already been a general admin"));
				}
				entry = *role_entry;
			}

			GeneralAdminRole general_admin;
			general_admin.gain_auth_time = eval_state._current_state->now();
			RoleCondition role_cond(candidate, RoleSubTypeEnum::sub_none, general_admin);
			entry.role_cond_vec.push_back(role_cond);

			entry.update_time = eval_state._current_state->now();
			eval_state._current_state->store_role_entry(entry);
		}

		void RevokeGeneralAdminOperation::evaluate(TransactionEvaluationState& eval_state)const
		{
			oAccountEntry account_entry = eval_state._current_state->get_account_entry(appointer);
			FC_ASSERT(account_entry.valid(), "appointer must be registered account");

			bool active_delegate = eval_state._current_state->is_active_delegate(account_entry->id);
			FC_ASSERT(active_delegate, "appointer must be active delegate");

			if (!eval_state.check_signature(appointer))
				FC_CAPTURE_AND_THROW(missing_signature, ("RevokeGeneralAdminOperation need appointer's signature"));

			// 判断是否已经不是管理员
			oRoleEntry role_entry = eval_state._current_state->get_role_entry(ContractIdType());
			if (!role_entry.valid())
				FC_CAPTURE_AND_THROW(is_not_general_admin, ("this address is not a general admin"));

			bool is_general_admin = false;
			for (const auto& role_cond : role_entry->role_cond_vec) {
				if (role_cond.role_address == general_admin &&
					role_cond.role_type == RoleTypeEnum::general_admin) {
					is_general_admin = true;
					break;
				}
			}
			if (NOT is_general_admin)
				FC_CAPTURE_AND_THROW(is_not_general_admin, ("this address is not a general admin"));

			for (auto iter = role_entry->role_cond_vec.begin(); iter != role_entry->role_cond_vec.end(); ) {
				if (iter->role_address == general_admin &&
					iter->role_type == RoleTypeEnum::general_admin) {
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
}