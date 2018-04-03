// Copyright (c) 2017-2018 The CDC developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.


#pragma once

#include <consensus/transaction/TransactionEvaluationState.hpp>

namespace cdcchain {
    namespace consensus {

        struct UniqueTransactionKey
        {
            time_point_sec  expiration;
            DigestType     digest;

            UniqueTransactionKey(const Transaction& t, const DigestType& chain_id)
                : expiration(t.expiration), digest(t.digest(chain_id)) {}

            friend bool operator == (const UniqueTransactionKey& a, const UniqueTransactionKey& b)
            {
                return std::tie(a.expiration, a.digest) == std::tie(b.expiration, b.digest);
            }

            friend bool operator < (const UniqueTransactionKey& a, const UniqueTransactionKey& b)
            {
                return std::tie(a.expiration, a.digest) < std::tie(b.expiration, b.digest);
            }
        };

        struct TransactionEntry;
        typedef optional<TransactionEntry> oTransactionEntry;

        class ChainInterface;
        struct TransactionEntry : public TransactionEvaluationState
        {
            TransactionEntry(){}

            TransactionEntry(const TransactionLocation& loc, const TransactionEvaluationState& s)
                :TransactionEvaluationState(s), chain_location(loc) {}

            TransactionLocation chain_location;

            void sanity_check(const ChainInterface&)const;
            static oTransactionEntry lookup(const ChainInterface& db, const TransactionIdType&);
            static void store(ChainInterface& db, const TransactionIdType&, const TransactionEntry&);
            static void remove(ChainInterface& db, const TransactionIdType&);
        };

        class TransactionDbInterface
        {
            friend struct TransactionEntry;

            virtual oTransactionEntry transaction_lookup_by_id(const TransactionIdType&)const = 0;

            virtual void transaction_insert_into_id_map(const TransactionIdType&, const TransactionEntry&) = 0;
            virtual void transaction_insert_into_unique_set(const Transaction&) = 0;

            virtual void transaction_erase_from_id_map(const TransactionIdType&) = 0;
            virtual void transaction_erase_from_unique_set(const Transaction&) = 0;
        };

    }
} // cdcchain::consensus

FC_REFLECT_DERIVED(cdcchain::consensus::TransactionEntry,
    (cdcchain::consensus::TransactionEvaluationState),
    (chain_location)
    )
