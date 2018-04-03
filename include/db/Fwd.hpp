// Copyright (c) 2017-2018 The CDC developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.


#pragma once
#include <memory>

namespace cdcchain {
    namespace db {

        class peer;
        typedef std::shared_ptr<peer> peer_ptr;

        class peer_ram;
        typedef std::shared_ptr<peer_ram> peer_ram_ptr;

    }
} // namespace cdcchain::db 
