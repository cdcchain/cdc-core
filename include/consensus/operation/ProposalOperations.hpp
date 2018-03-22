#pragma once

#include <consensus/Types.hpp>
#include <consensus/operation/Operations.hpp>
#include <consensus/proposal/ProposalEntry.hpp>

namespace cdcchain {
	namespace consensus {

		struct ProposalForPrivilegeOperation
		{
			static const OperationTypeEnum type;

			Address proposal_from;
			Address candidate;
			int delegate_vote_need;
			fc::time_point_sec start_time;
			fc::time_point_sec expected_end_time;

			ProposalForPrivilegeOperation(){}

			ProposalForPrivilegeOperation(const Address& _proposal_from, const Address& _candidate, int _delegate_vote_need,
				const fc::time_point_sec& _start_time, const fc::time_point_sec& _expected_end_time):
				proposal_from(_proposal_from), candidate(_candidate), delegate_vote_need(_delegate_vote_need),
				start_time(_start_time), expected_end_time(_expected_end_time){}

			void evaluate(TransactionEvaluationState& eval_state)const;
		};

		struct ProposalRevokePrivilegeOperation
		{
			static const OperationTypeEnum type;

			Address proposal_from;
			Address privilege_admin;
			int delegate_vote_need;
			fc::time_point_sec start_time;
			fc::time_point_sec expected_end_time;

			ProposalRevokePrivilegeOperation(){}

			ProposalRevokePrivilegeOperation(const Address& _proposal_from, const Address& _privilege_admin, int _delegate_vote_need,
				const fc::time_point_sec& _start_time, const fc::time_point_sec& _expected_end_time) :
				proposal_from(_proposal_from), privilege_admin(_privilege_admin), 
				delegate_vote_need(_delegate_vote_need),
				start_time(_start_time), expected_end_time(_expected_end_time){}

			void evaluate(TransactionEvaluationState& eval_state)const;
		};

		struct ProposalApproveOperation
		{
			static const OperationTypeEnum type;

			ProposalIdType proposal_id;
			Address approver;

			ProposalApproveOperation(){}

			ProposalApproveOperation(const ProposalIdType& _proposal_id, const Address& _approver):
				proposal_id(_proposal_id), approver(_approver){}

			void evaluate(TransactionEvaluationState& eval_state)const;
		};
	}
}


FC_REFLECT(cdcchain::consensus::ProposalForPrivilegeOperation, 
(proposal_from)
(candidate)
(delegate_vote_need)
(start_time)
(expected_end_time)
)

FC_REFLECT(cdcchain::consensus::ProposalRevokePrivilegeOperation,
(proposal_from)
(privilege_admin)
(delegate_vote_need)
(start_time)
(expected_end_time)
)

FC_REFLECT(cdcchain::consensus::ProposalApproveOperation,
(proposal_id)
(approver)
)
