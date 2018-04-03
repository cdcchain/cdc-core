// Copyright (c) 2017-2018 The CDC developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.


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

		struct CdcDataEntry;
		typedef fc::optional<CdcDataEntry> oCdcDataEntry;

		struct CdcDataEntry {
			CdcDataDigestIdType cdcdata_id;
			fc::enum_type<fc::unsigned_int, CdcDataTypeEnum> cdcdata_type;
			std::string cdcdata_remark;
			fc::time_point_sec checkin_time;
			Address checkin_admin;

			CdcDataEntry() {}

			CdcDataEntry(const CdcDataDigestIdType& _data_id, const CdcDataTypeEnum& _cdcdata_type, const string& _cdcdata_remark,
				const fc::time_point_sec& _checkin_time, const Address& admin)
				:cdcdata_id(_data_id), cdcdata_type(_cdcdata_type), cdcdata_remark(_cdcdata_remark), 
				checkin_time(_checkin_time), checkin_admin(admin) {}

			static oCdcDataEntry lookup(const ChainInterface&, const CdcDataDigestIdType&);
			static void store(ChainInterface&, const CdcDataDigestIdType&, const CdcDataEntry&);
			static void remove(ChainInterface&, const CdcDataDigestIdType&);
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

FC_REFLECT(cdcchain::consensus::CdcDataEntry,
(cdcdata_id)
(cdcdata_type)
(cdcdata_remark)
(checkin_time)
(checkin_admin)
)
