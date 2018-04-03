// Copyright (c) 2017-2018 The CDC developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.


#pragma once

#include <string>
#include <fc/crypto/elliptic.hpp>
#include <fc/optional.hpp>

namespace cdcchain {
    namespace utilities {

        std::string                        key_to_wif_single_hash(const fc::ecc::private_key& key);
        std::string                        key_to_wif(const fc::ecc::private_key& key);
        fc::optional<fc::ecc::private_key> wif_to_key(const std::string& wif_key);

    }
} // end namespace cdcchain::utilities
