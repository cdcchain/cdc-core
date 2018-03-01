#pragma once

#include <consensus/Types.hpp>

namespace cdcchain {
    namespace consensus {

        struct SlateEntry;
        typedef optional<SlateEntry> oSlateEntry;

        class ChainInterface;
        struct SlateEntry
        {
            set<AccountIdType> slate;
            vector<AccountIdType> duplicate_slate;

            SlateIdType id()const;

            static SlateIdType id_v1(const vector<AccountIdType>& slate)
            {
                if (slate.empty()) return 0;
                return fc::sha256::hash(slate)._hash[0];
            }

            void sanity_check(const ChainInterface&)const;
            static oSlateEntry lookup(const ChainInterface&, const SlateIdType);
            static void store(ChainInterface&, const SlateIdType, const SlateEntry&);
            static void remove(ChainInterface&, const SlateIdType);
        };

        class SlateDbInterface
        {
            friend struct SlateEntry;

            virtual oSlateEntry slate_lookup_by_id(const SlateIdType)const = 0;
            virtual void slate_insert_into_id_map(const SlateIdType, const SlateEntry&) = 0;
            virtual void slate_erase_from_id_map(const SlateIdType) = 0;
        };

    }
} // cdcchain::consensus

FC_REFLECT(cdcchain::consensus::SlateEntry, (slate)(duplicate_slate))
