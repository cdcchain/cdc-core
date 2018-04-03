// Copyright (c) 2017-2018 The CDC developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.


#pragma once

#include <consensus/Config.hpp>
#include <consensus/Types.hpp>
#include <fc/time.hpp>

#ifdef CDC_TEST_NETWORK
#define NETWORK_MIN_CONNECTION_COUNT_DEFAULT 0
#else
#define NETWORK_MIN_CONNECTION_COUNT_DEFAULT 4
#endif

#define CDC_BLOCKCHAIN_AVERAGE_TRX_SIZE 512 // just a random assumption used to calibrate TRX per SEC
/** defines the maximum block size allowed as 10000 KB */
/** defines the maximum trx size allowed as 100 KB */
#define CDC_BLOCKCHAIN_MAX_TRX_SIZE (2 * CDC_BLOCKCHAIN_AVERAGE_TRX_SIZE * 100) 
#define CDC_BLOCKCHAIN_MAX_BLOCK_SIZE (2 * CDC_BLOCKCHAIN_AVERAGE_TRX_SIZE * CDC_BLOCKCHAIN_MAX_PENDING_QUEUE_SIZE)

namespace cdcchain {
    namespace consensus {

        struct DelegateConfig
        {
            uint32_t            network_min_connection_count = NETWORK_MIN_CONNECTION_COUNT_DEFAULT;

            uint32_t            block_max_transaction_count = -1;
            uint32_t            block_max_size = CDC_BLOCKCHAIN_MAX_BLOCK_SIZE;
            fc::microseconds    block_max_production_time = fc::seconds(3);

            uint32_t            transaction_max_size = CDC_BLOCKCHAIN_MAX_TRX_SIZE;
            bool                transaction_canonical_signatures_required = false;
            ShareType          transaction_min_fee = CDC_BLOCKCHAIN_PRECISION / CDC_BLOCKCHAIN_PRECISION;
            ImessageLengthIdType transaction_imessage_max_soft_length = CDC_BLOCKCHAIN_MAX_SOFT_MAX_MESSAGE_SIZE;
            ImessageIdType      transaction_imessage_min_fee_coe = CDC_BLOCKCHAIN_MIN_MESSAGE_FEE_COE;
            set<TransactionIdType>    transaction_blacklist;
            set<OperationTypeEnum>    operation_blacklist;

            void validate()const
            {
                try {
                    FC_ASSERT(block_max_size <= CDC_BLOCKCHAIN_MAX_BLOCK_SIZE);
                    FC_ASSERT(block_max_production_time.count() >= 0);
                    FC_ASSERT(block_max_production_time.to_seconds() <= CDC_BLOCKCHAIN_BLOCK_INTERVAL_SEC);
                    FC_ASSERT(transaction_max_size <= CDC_BLOCKCHAIN_MAX_TRX_SIZE);
                    FC_ASSERT(transaction_min_fee >= CDC_BLOCKCHAIN_DEFAULT_RELAY_FEE);
                    FC_ASSERT(transaction_min_fee <= CDC_BLOCKCHAIN_MAX_SHARES);
                    FC_ASSERT(transaction_imessage_min_fee_coe >= CDC_BLOCKCHAIN_MIN_MESSAGE_FEE_COE);
                    FC_ASSERT(transaction_imessage_max_soft_length >= 0);
                    FC_ASSERT(transaction_imessage_max_soft_length <= CDC_BLOCKCHAIN_MAX_MESSAGE_SIZE);
                } FC_CAPTURE_AND_RETHROW()
            }
        };

    }
} // cdcchain::consensus

FC_REFLECT(cdcchain::consensus::DelegateConfig,
    (network_min_connection_count)
    (block_max_transaction_count)
    (block_max_size)
    (block_max_production_time)
    (transaction_max_size)
    (transaction_canonical_signatures_required)
    (transaction_min_fee)
    (transaction_imessage_max_soft_length)
    (transaction_imessage_min_fee_coe)
    (transaction_blacklist)
    (operation_blacklist)
    )
