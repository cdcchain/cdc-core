#pragma once


#include <consensus/operation/Operations.hpp>
#include <consensus/Types.hpp>

namespace cdcchain {
    namespace consensus {
        struct ImessageMemoOperation
        {
            static const OperationTypeEnum type;
            string imessage;
            ImessageMemoOperation(){}
            ImessageMemoOperation(std::string imess) :imessage(imess){}
            void evaluate(TransactionEvaluationState& eval_state)const;
        };
    }
}
FC_REFLECT(cdcchain::consensus::ImessageMemoOperation, (imessage))
