#pragma once
#include <consensus/block/Block.hpp>
#include <client/Client.hpp>

namespace cdcchain {
    namespace client {

        enum MessageTypeEnum
        {
            trx_message_type = 1000,
            block_message_type = 1001,
            batch_trx_message_type = 1002,
        };

        struct TrxMessage
        {
            static const MessageTypeEnum type;

            cdcchain::consensus::SignedTransaction trx;
            TrxMessage() {}
            TrxMessage(cdcchain::consensus::SignedTransaction transaction) :
                trx(std::move(transaction))
            {}
        };

        struct BatchTrxMessage
        {
            static const MessageTypeEnum type;
            std::vector<cdcchain::consensus::SignedTransaction> trx_vec;
            BatchTrxMessage() {}
            BatchTrxMessage(std::vector<cdcchain::consensus::SignedTransaction> transactions) :
                trx_vec(std::move(transactions))
            {}
        };

        struct BlockMessage
        {
            static const MessageTypeEnum type;

            BlockMessage(){}
            BlockMessage(const cdcchain::consensus::FullBlock& blk)
                :block(blk), block_id(blk.id()){}

            cdcchain::consensus::FullBlock    block;
            cdcchain::consensus::BlockIdType block_id;

        };

    }
} // cdcchain::client

FC_REFLECT_ENUM(cdcchain::client::MessageTypeEnum, 
(trx_message_type)
(block_message_type)
(batch_trx_message_type))

FC_REFLECT(cdcchain::client::TrxMessage, (trx))
FC_REFLECT(cdcchain::client::BatchTrxMessage, (trx_vec))
FC_REFLECT(cdcchain::client::BlockMessage, (block)(block_id))

