#pragma once
#include <consensus/block/Block.hpp>

namespace cdcchain {
    namespace consensus {

        struct BlockEntry : public cdcchain::consensus::DigestBlock
        {
            BlockIdType       id;
            uint64_t            block_size = 0; /* Bytes */
            fc::microseconds    latency; /* Time between block timestamp and first push_block */

            ShareType          signee_shares_issued = 0;
            ShareType          signee_fees_collected = 0;
            ShareType          signee_fees_destroyed = 0;
            fc::ripemd160       random_seed;

            fc::microseconds    processing_time; /* Time taken for extend_chain to run */
        };
        typedef optional<BlockEntry> oBlockEntry;

    }
} // cdcchain::consensus

FC_REFLECT_DERIVED(cdcchain::consensus::BlockEntry,
    (cdcchain::consensus::DigestBlock),
    (id)
    (block_size)
    (latency)
    (signee_shares_issued)
    (signee_fees_collected)
    (signee_fees_destroyed)
    (random_seed)
    (processing_time)
    )
