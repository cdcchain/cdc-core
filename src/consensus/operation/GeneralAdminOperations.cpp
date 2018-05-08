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
			if (!eval_state.check_signature(appointer))
				FC_CAPTURE_AND_THROW(missing_signature, ("AppointGeneralAdminOperation need appointer's signature"));

			oRoleEntry role_entry = eval_state._current_state->get_role_entry(ContractIdType());
			FC_ASSERT(role_entry.valid(), "can not get admin role entry");

			bool is_privlege_admin = false;
			// 判断appointer是否为特权管理员
			for (const auto& role_cond : role_entry->role_cond_vec) {
				if (role_cond.role_address == appointer &&
					role_cond.role_type == RoleTypeEnum::privilege_admin) {
					is_privlege_admin = true;
					break;
				}
			}
			FC_ASSERT(is_privlege_admin, "appointer is not privilege admin");

			RoleEntry entry;	
			// 判断candidate是否已经是一般管理员
			for (const auto& role_cond : role_entry->role_cond_vec) {
				if (role_cond.role_address == candidate &&
					role_cond.role_type == RoleTypeEnum::general_admin)
					FC_CAPTURE_AND_THROW(is_general_admin, ("candidate has already been a general admin"));
			}
			entry = *role_entry;
			
			GeneralAdminRole general_admin;
			general_admin.gain_auth_time = eval_state._current_state->now();
			RoleCondition role_cond(candidate, RoleSubTypeEnum::sub_none, general_admin);
			entry.role_cond_vec.push_back(role_cond);

			entry.update_time = eval_state._current_state->now();
			eval_state._current_state->store_role_entry(entry);
		}

		void RevokeGeneralAdminOperation::evaluate(TransactionEvaluationState& eval_state)const
		{
			if (!eval_state.check_signature(appointer))
				FC_CAPTURE_AND_THROW(missing_signature, ("RevokeGeneralAdminOperation need appointer's signature"));

			oRoleEntry role_entry = eval_state._current_state->get_role_entry(ContractIdType());
			FC_ASSERT(role_entry.valid(), "can not get admin role entry");

			bool is_privlege_admin = false;
			// 判断appointer是否为特权管理员
			for (const auto& role_cond : role_entry->role_cond_vec) {
				if (role_cond.role_address == appointer &&
					role_cond.role_type == RoleTypeEnum::privilege_admin) {
					is_privlege_admin = true;
					break;
				}
			}
			FC_ASSERT(is_privlege_admin, "appointer is not privilege admin");

			// 判断candidate是否不是一般管理员
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