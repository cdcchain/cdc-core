#pragma once

#include <consensus/Types.hpp>

namespace cdcchain {
	namespace consensus {

		enum CdcDataTypeEnum {
			user_receipt_data = 1,
			mining_result_data = 2,
			ad_putting_feedback_data = 3,
			ad_putting_result_data = 4
		};

		//front declaration for typedef
		class ChainInterface;

		struct CdcDataCondition {
			fc::enum_type<fc::unsigned_int, CdcDataTypeEnum> cdcdata_type;
			std::vector<char> cdcdata_data;

			CdcDataCondition() {}

			CdcDataCondition(const CdcDataCondition& cond) : cdcdata_type(cond.cdcdata_type),
				cdcdata_data(cond.cdcdata_data) {}

			template<typename CdcDataType>
			CdcDataCondition(const CdcDataType& t)
			{
				cdcdata_type = CdcDataType::type;
				cdcdata_data = fc::raw::pack(t);
			}

			template<typename CdcDataType>
			CdcDataType as()const
			{
				FC_ASSERT(cdcdata_type == CdcDataType::type, "", ("proposal_type", cdcdata_type)("CdcDataType", CdcDataType::type));
				return fc::raw::unpack<CdcDataType>(cdcdata_data);
			}
		};

		struct CdcDataEntry;
		typedef fc::optional<CdcDataEntry> oCdcDataEntry;

		struct CdcDataEntry {
			CdcDataDigestIdType cdcdata_id;
			CdcDataCondition cdcdata_condition;
			fc::time_point_sec checkin_time;
			Address checkin_admin;

			CdcDataEntry() {}
			CdcDataEntry(const CdcDataDigestIdType& _data_id, const CdcDataCondition& cond, 
				const fc::time_point_sec& _checkin_time, const Address& admin)
				:cdcdata_id(_data_id), cdcdata_condition(cond), checkin_time(_checkin_time), checkin_admin(admin) {}

			static oCdcDataEntry lookup(const ChainInterface&, const CdcDataDigestIdType&);
			static void store(ChainInterface&, const CdcDataDigestIdType&, const CdcDataEntry&);
			static void remove(ChainInterface&, const CdcDataDigestIdType&);
		};

		struct UserReceiptData {
			static const CdcDataTypeEnum type;

			UserReceiptData() {}
			UserReceiptData(const Address& _chunk_from)
				:data_chunk_from(_chunk_from) {}

			Address data_chunk_from;
		};

		struct MiningResultData {
			static const CdcDataTypeEnum type;

			MiningResultData() {}
			MiningResultData(const Address& _merchant_id, 
				const TransactionIdType& _task_id, const Address& _result_from)
				:from_merchant_id(_merchant_id), mining_task_id(_task_id), mining_result_from(_result_from) {}

			Address from_merchant_id;
			TransactionIdType mining_task_id;
			Address mining_result_from;
		};
		
		struct AdPuttingFeedbackData {
			static const CdcDataTypeEnum type;

			AdPuttingFeedbackData() {}
			AdPuttingFeedbackData(const Address& _merchant_id, 
				const TransactionIdType& _task_id, const Address& _feeback_from)
				:from_merchant_id(_merchant_id), mining_task_id(_task_id),  putting_feeback_from(_feeback_from) {}

			Address from_merchant_id;
			TransactionIdType mining_task_id;
			Address putting_feeback_from;
		};

		struct AdPuttingResultData {
			static const CdcDataTypeEnum type;

			AdPuttingResultData() {}
			AdPuttingResultData(const Address& _merchant_id, const TransactionIdType& _task_id,
				const CdcDataDigestIdType& _feedback_id, const Address& _result_from)
				:from_merchant_id(_merchant_id), mining_task_id(_task_id), 
				putting_feedback_id(_feedback_id), putting_result_from(_result_from) {}

			Address from_merchant_id;
			TransactionIdType mining_task_id;
			CdcDataDigestIdType putting_feedback_id;
			Address putting_result_from;
		};

		class CdcDataDbInterface
		{
			friend struct CdcDataEntry;
			virtual  oCdcDataEntry  cdcdata_lookup_by_id(const CdcDataDigestIdType&)const = 0;
			virtual void cdcdata_insert_into_id_map(const CdcDataDigestIdType&, const CdcDataEntry&) = 0;
			virtual void cdcdata_erase_from_id_map(const CdcDataDigestIdType&) = 0;
		};

	}
}


FC_REFLECT_ENUM(cdcchain::consensus::CdcDataTypeEnum,
(user_receipt_data)
(mining_result_data)
(ad_putting_feedback_data)
(ad_putting_result_data)
)

FC_REFLECT(cdcchain::consensus::CdcDataCondition,
(cdcdata_type)
(cdcdata_data)
)

FC_REFLECT(cdcchain::consensus::CdcDataEntry,
(cdcdata_id)
(cdcdata_condition)
(checkin_time)
(checkin_admin)
)

FC_REFLECT(cdcchain::consensus::UserReceiptData,
(data_chunk_from)
)

FC_REFLECT(cdcchain::consensus::MiningResultData,
(from_merchant_id)
(mining_task_id)
(mining_result_from)
)

FC_REFLECT(cdcchain::consensus::AdPuttingFeedbackData,
(from_merchant_id)
(mining_task_id)
(putting_feeback_from)
)

FC_REFLECT(cdcchain::consensus::AdPuttingResultData,
(from_merchant_id)
(mining_task_id)
(putting_feedback_id)
(putting_result_from)
)