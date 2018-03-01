#include <consensus/evidence/ShopReceiptEvidence.hpp>
#include <consensus/shopreceipt/ShopReceiptEntry.hpp>
#include <consensus/chainstate/ChainInterface.hpp>

namespace cdcchain {
    namespace consensus {

        void ShopReceiptEntry::sanity_check(const ChainInterface& db)const
        {
        }

        oShopReceiptEntry ShopReceiptEntry::lookup(const ChainInterface& db, const ShopReceiptIdType& id)
        {
            try {
                return db.shopreceipt_lookup_by_id(id);
            } FC_CAPTURE_AND_RETHROW((id))
        }

        void ShopReceiptEntry::store(ChainInterface& db, const ShopReceiptIdType& id, const ShopReceiptEntry& entry)
        {
            try {
                db.shopreceipt_insert_into_id_map(id, entry);
            } FC_CAPTURE_AND_RETHROW((id)(entry))
        }

        void ShopReceiptEntry::remove(ChainInterface& db, const ShopReceiptIdType& id)
        {
            try {
                const oShopReceiptEntry prev_entry = db.lookup<ShopReceiptEntry>(id);
                if (prev_entry.valid())
                {
                    db.shopreceipt_erase_from_id_map(id);
                }
            } FC_CAPTURE_AND_RETHROW((id))
        }

    }
} // cdcchain::consensus
