#pragma once

#include <consensus/transaction/TransactionEntry.hpp>
#include <consensus/operation/Operations.hpp>

namespace cdcchain {
    namespace consensus {

        struct TransactionOperation
        {
            static const OperationTypeEnum type;

            TransactionOperation(){}

            TransactionOperation(const SignedTransaction& signed_trx)
                :trx(signed_trx){}

            TransactionOperation(const TransactionOperation& trx_op)
                :trx(trx_op.trx){}

            SignedTransaction trx;

            void evaluate(TransactionEvaluationState& eval_state)const;
        };

    }
} // cdcchain::consensus


FC_REFLECT(cdcchain::consensus::TransactionOperation, (trx))
