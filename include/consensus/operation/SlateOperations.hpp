#pragma once

#include <consensus/operation/Operations.hpp>

namespace cdcchain {
    namespace consensus {

        struct DefineSlateOperation
        {
            static const OperationTypeEnum type;

            vector<signed_int> slate;

            void evaluate(TransactionEvaluationState& eval_state)const;
        };

    }
} // cdcchain::consensus

FC_REFLECT(cdcchain::consensus::DefineSlateOperation, (slate))
