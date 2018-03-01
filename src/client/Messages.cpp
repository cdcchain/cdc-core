#include <client/Messages.hpp>
namespace cdcchain {
    namespace client {

        const MessageTypeEnum TrxMessage::type = MessageTypeEnum::trx_message_type;
        const MessageTypeEnum BlockMessage::type = MessageTypeEnum::block_message_type;
        const MessageTypeEnum BatchTrxMessage::type = MessageTypeEnum::batch_trx_message_type;
		const MessageTypeEnum EvidenceMessage::type = MessageTypeEnum::evidence_message_type;
		const MessageTypeEnum ShopReceiptMessage::type = MessageTypeEnum::shopreceipt_message_type;

    }
} // cdcchain::client
