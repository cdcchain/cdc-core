#include <consensus/chainstate/ChainInterface.hpp>
#include <consensus/cdcdata/CdcDataEntry.hpp>


namespace cdcchain {
	namespace consensus {

		const CdcDataTypeEnum UserReceiptData::type = user_receipt_data;
		const CdcDataTypeEnum MiningResultData::type = mining_result_data;
		const CdcDataTypeEnum AdPuttingFeedbackData::type = ad_putting_feedback_data;
		const CdcDataTypeEnum AdPuttingResultData::type = ad_putting_result_data;

		oCdcDataEntry CdcDataEntry::lookup(const ChainInterface& db, const CdcDataDigestIdType& id)
		{
			try
			{
				return db.cdcdata_lookup_by_id(id);
			}FC_CAPTURE_AND_RETHROW((id))
		}

		void CdcDataEntry::store(ChainInterface& db, const CdcDataDigestIdType& id, const CdcDataEntry& entry)
		{
			try
			{
				db.cdcdata_insert_into_id_map(id, entry);
			}FC_CAPTURE_AND_RETHROW((id)(entry))
		}

		void CdcDataEntry::remove(ChainInterface& db, const CdcDataDigestIdType& id)
		{
			try
			{
				const oCdcDataEntry entry = db.lookup<CdcDataEntry>(id);

				if (entry.valid())
				{
					db.cdcdata_erase_from_id_map(id);
				}
			}FC_CAPTURE_AND_RETHROW((id))
		}

	}
}
