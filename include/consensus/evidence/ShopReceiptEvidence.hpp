#pragma once


#include <consensus/evidence/Evidences.hpp>
#include <consensus/Types.hpp>

namespace cdcchain {
    namespace consensus {
        struct ShopReceiptEvidence
        {
            static const EvidenceTypeEnum type;
            string brand_id;
			string merchant_id;
			string merchant_serial;
			string receipt_amount;
			string merchandise;
			string receipt_time;
			string remark;

			ShopReceiptEvidence(){}
			ShopReceiptEvidence(string _brand_id, string _merchant_id, string _merchant_serial, 
				string _receipt_amount, string _merchandise, string _receipt_time, string _remark)
			{
				brand_id = _brand_id;
				merchant_id = _merchant_id;
				merchant_serial = _merchant_serial;
				receipt_amount = _receipt_amount;
				merchandise = _merchandise;
				receipt_time = _receipt_time;
				remark = _remark;
			}

            void evaluate(TransactionEvaluationState& eval_state)const;
        };
    }
}
FC_REFLECT(cdcchain::consensus::ShopReceiptEvidence, (brand_id)(merchant_id)(merchant_serial)(receipt_amount)(merchandise)(receipt_time)(remark))
