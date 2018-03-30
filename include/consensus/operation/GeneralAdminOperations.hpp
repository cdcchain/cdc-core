#pragma once

#include <consensus/Types.hpp>
#include <consensus/operation/Operations.hpp>

namespace cdcchain {
	namespace consensus {

		struct AppointGeneralAdminOperation
		{
			static const OperationTypeEnum type;

			Address appointer;
			Address candidate;

			AppointGeneralAdminOperation(){}

			AppointGeneralAdminOperation(const Address& _appointer, const Address& _candidate) :
				appointer(_appointer), candidate(_candidate) {}

			void evaluate(TransactionEvaluationState& eval_state)const;
		};

		struct RevokeGeneralAdminOperation
		{
			static const OperationTypeEnum type;

			Address appointer;
			Address general_admin;

			RevokeGeneralAdminOperation(){}
			RevokeGeneralAdminOperation(const Address& _appointer, const Address& _general_admin) :
				appointer(_appointer), general_admin(_general_admin) {}

			void evaluate(TransactionEvaluationState& eval_state)const;
		};

	}
}


FC_REFLECT(cdcchain::consensus::AppointGeneralAdminOperation,
(appointer)
(candidate)
)

FC_REFLECT(cdcchain::consensus::RevokeGeneralAdminOperation,
(appointer)
(general_admin)
)