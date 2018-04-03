// Copyright (c) 2017-2018 The CDC developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.



#include <consensus/Exceptions.hpp>
#include <consensus/chainstate/PendingChainState.hpp>
#include <consensus/operation/ImessageOperations.hpp>

#include <consensus/block/ForkBlocks.hpp>

namespace cdcchain {
    namespace consensus {
        void ImessageMemoOperation::evaluate(TransactionEvaluationState& eval_state) const
        {
            try
            {
                FC_ASSERT(!imessage.empty());
                if (this->imessage.size() > CDC_BLOCKCHAIN_MAX_MESSAGE_SIZE)
                {
                    FC_CAPTURE_AND_THROW(message_too_long, (imessage.size()));
                }
                auto fee = Asset(eval_state._current_state->get_imessage_need_fee(imessage), 0);
                eval_state.imessage_length = imessage.size();
                eval_state.required_fees += fee;
            } FC_CAPTURE_AND_RETHROW((*this))
        }
    }
}
