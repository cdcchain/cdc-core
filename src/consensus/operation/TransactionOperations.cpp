// Copyright (c) 2017-2018 The CDC developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.


#include <consensus/operation/TransactionOperations.hpp>
#include <consensus/chainstate/ChainInterface.hpp>
namespace cdcchain {
    namespace consensus {

        void TransactionOperation::evaluate(TransactionEvaluationState& eval_state)const
        {
            try {
				TransactionIdType id= eval_state.trx.result_trx_id;
                eval_state.evaluate(trx);
				eval_state._current_state->store(trx.id(), ResultTIdEntry(id));
				eval_state._current_state->store(id, RequestIdEntry(trx.id()));
            }
            FC_CAPTURE_AND_RETHROW((*this))
        }

    }
}

