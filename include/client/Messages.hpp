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
			
			evidence_message_type = 1011,
			shopreceipt_message_type = 1012,
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

		struct EvidenceMessage
		{
			static const MessageTypeEnum type;

			EvidenceMessage() {}
			EvidenceMessage(const cdcchain::consensus::Evidence& _ev,
				const cdcchain::consensus::TransactionIdType& _trx_id, uint32_t _ev_index)
				:ev(_ev), trx_id(_trx_id), ev_index(_ev_index) {}

			cdcchain::consensus::Evidence ev;
			cdcchain::consensus::TransactionIdType trx_id;
			uint32_t ev_index;
		};

		struct ShopReceiptMessage: public EvidenceMessage
		{
			static const MessageTypeEnum type;

			ShopReceiptMessage() {}
			ShopReceiptMessage(const cdcchain::consensus::Evidence& _ev,
				const cdcchain::consensus::TransactionIdType& _trx_id, uint32_t _ev_index)
				:EvidenceMessage(_ev, _trx_id, _ev_index) {}
		};

    }
} // cdcchain::client

FC_REFLECT_ENUM(cdcchain::client::MessageTypeEnum, 
(trx_message_type)
(block_message_type)
(batch_trx_message_type)
(evidence_message_type)
(shopreceipt_message_type))
FC_REFLECT(cdcchain::client::TrxMessage, (trx))
FC_REFLECT(cdcchain::client::BatchTrxMessage, (trx_vec))
FC_REFLECT(cdcchain::client::BlockMessage, (block)(block_id))
FC_REFLECT(cdcchain::client::EvidenceMessage, (ev)(trx_id)(ev_index))
FC_REFLECT_DERIVED(cdcchain::client::ShopReceiptMessage, (cdcchain::client::EvidenceMessage))
