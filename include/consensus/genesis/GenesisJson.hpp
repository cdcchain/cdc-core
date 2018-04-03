// Copyright (c) 2017-2018 The CDC developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.


#pragma once
#include <consensus/genesis/GenesisState.hpp>
#include <sstream>

namespace cdcchain {
    namespace consensus {

        GenesisState get_builtin_genesis_block_config();
        fc::sha256 get_builtin_genesis_block_state_hash();

    }
} // cdcchain::consensus
