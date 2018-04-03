// Copyright (c) 2017-2018 The CDC developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.


#include <consensus/Exceptions.hpp>
#include <consensus/chainstate/PendingChainState.hpp>
#include <consensus/operation/SlateOperations.hpp>

#include <consensus/block/ForkBlocks.hpp>

namespace cdcchain {
    namespace consensus {

        void DefineSlateOperation::evaluate(TransactionEvaluationState& eval_state)const
        {
            try {
                FC_ASSERT(!slate.empty());
                if (this->slate.size() > CDC_BLOCKCHAIN_MAX_SLATE_SIZE)
                    FC_CAPTURE_AND_THROW(too_may_delegates_in_slate, (slate.size()));

                SlateEntry entry;
                for (const signed_int id : this->slate)
                {
                    if (id >= 0)
                    {
                        const oAccountEntry delegate_entry = eval_state._current_state->get_account_entry(id);
                        FC_ASSERT(delegate_entry.valid() && delegate_entry->is_delegate());
                    }
                    entry.slate.insert(id);
                }

                //     if( eval_state._current_state->get_head_block_num() < CDC_V0_6_3_FORK_BLOCK_NUM )
                //     {
                //         const slate_id_type slate_id = slate_entry::id_v1( this->slate );
                //         const oslate_entry current_slate = eval_state._current_state->get_slate_entry( slate_id );
                //         if( !current_slate.valid() )
                //         {
                //             if( entry.slate.size() < this->slate.size() )
                //                 entry.duplicate_slate = this->slate;
                // 
                //             eval_state._current_state->store( slate_id, entry );
                //             entry.duplicate_slate.clear();
                //         }
                //     }

                const SlateIdType slate_id = entry.id();
                const oSlateEntry current_slate = eval_state._current_state->get_slate_entry(slate_id);
                if (current_slate.valid())
                {
                    FC_ASSERT(current_slate->slate == entry.slate, "Slate ID collision!", ("current_slate", *current_slate)("new_slate", entry));
                    return;
                }

                eval_state._current_state->store_slate_entry(entry);
            } FC_CAPTURE_AND_RETHROW((*this))
        }

    }
} // cdcchain::consensus
