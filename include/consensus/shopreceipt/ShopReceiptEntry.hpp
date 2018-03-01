#pragma once
#include <consensus/Types.hpp>

namespace cdcchain {
    namespace consensus {

        struct ShopReceiptEntry;
        typedef fc::optional<ShopReceiptEntry> oShopReceiptEntry;

        class ChainInterface;
        struct ShopReceiptEntry
        {
			string brand_id;
			string merchant_id;
			string merchant_serial;
			string receipt_amount;
			string merchandise;
			string receipt_time;
			string remark;

			ShopReceiptIdType id;
			TransactionIdType from_trx_id;
			uint32_t ev_index;

            void sanity_check(const ChainInterface&)const;
            static oShopReceiptEntry lookup(const ChainInterface&, const ShopReceiptIdType&);
            static void store(ChainInterface&, const ShopReceiptIdType&, const ShopReceiptEntry&);
            static void remove(ChainInterface&, const ShopReceiptIdType&);
        };

        class ShopReceiptDbInterface
        {
            friend struct ShopReceiptEntry;

            virtual oShopReceiptEntry shopreceipt_lookup_by_id(const ShopReceiptIdType&)const = 0;
            virtual void shopreceipt_insert_into_id_map(const ShopReceiptIdType&, const ShopReceiptEntry&) = 0;
            virtual void shopreceipt_erase_from_id_map(const ShopReceiptIdType&) = 0;
        };

    }
} // cdcchain::consensus

FC_REFLECT(cdcchain::consensus::ShopReceiptEntry,
	(brand_id)
	(merchant_id)
	(merchant_serial)
	(receipt_amount)
	(merchandise)
	(receipt_time)
	(remark)
	(from_trx_id)
	(ev_index)
	(id)
    )
