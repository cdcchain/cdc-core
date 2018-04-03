// Copyright (c) 2017-2018 The CDC developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.


#pragma once

#include <consensus/Types.hpp>
namespace cdcchain {
    namespace consensus {

        // The difference between a condition and normal business logic is that
        // condition proof equivalence classes always yield the same condition
        // and so you can embed the proof at the right "scope" in the transaction
        // without doing anything complicated.    
        // eval(with[cond](expr)) would mean:   push_permission prove("with[cond](expr)"); eval(expr)

        struct Condition
        {
        };
        struct proof
        {
            Condition get_condition();
        };

        struct MultisigCondition : Condition
        {
            uint32_t                 required; // 0 means anyone can claim. -1 means the DAC can
            std::set<Address>        owners;

            MultisigCondition() :required(-1), owners(set<Address>()){}
            MultisigCondition(uint32_t m, set<Address> owners)
                :required(m), owners(owners)
            {}
        };

        // pow
        // delegate_fraud
        // timelock
        // BTC spv utxo claim
        // cross-chain trading
        // 

    }
} // cdcchain::consensus

FC_REFLECT(cdcchain::consensus::Condition, BOOST_PP_SEQ_NIL);
FC_REFLECT(cdcchain::consensus::MultisigCondition, (required)(owners));
