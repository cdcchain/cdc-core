
#include <consensus/Exceptions.hpp>
#include <consensus/chainstate/PendingChainState.hpp>
#include <consensus/evidence/ShopReceiptEvidence.hpp>
#include <consensus/shopreceipt/ShopReceiptEntry.hpp>

#include <consensus/block/ForkBlocks.hpp>

namespace cdcchain {
    namespace consensus {
        void ShopReceiptEvidence::evaluate(TransactionEvaluationState& eval_state) const
        {
            try
            {
				FC_ASSERT(!brand_id.empty() && brand_id.length() != 0);
				FC_ASSERT(!merchant_id.empty() && merchant_id.length() != 0);
				FC_ASSERT(!merchant_serial.empty() && merchant_serial.length() != 0);
				FC_ASSERT(!receipt_amount.empty() && receipt_amount.length() != 0);
				FC_ASSERT(!merchandise.empty() && merchandise.length() != 0);
				FC_ASSERT(!receipt_time.empty() && receipt_time.length() != 0);

				//TODO
				//need to add some verifications for input arguments

				Evidence ev = Evidence(*this);
				size_t ev_size = ev.data_len;

				eval_state.required_fees += Asset(SHOP_RECEIPT_EVIDENCE_FEE_PRICE * ev_size, 0);

				ShopReceiptEntry new_entry;
				new_entry.brand_id = brand_id;
				new_entry.merchant_id = merchant_id;
				new_entry.merchant_serial = merchant_serial;
				new_entry.receipt_amount = receipt_amount;
				new_entry.merchandise = merchandise;
				new_entry.receipt_time = receipt_time;
				new_entry.from_trx_id = eval_state.ev_from_trx;
				new_entry.ev_index = eval_state.ev_index;
				new_entry.id = Evidence(*this).id();

				eval_state._current_state->store_shopreceipt_entry(new_entry);

            } FC_CAPTURE_AND_RETHROW((*this))
        }
    }
}
