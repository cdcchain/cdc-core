// Copyright (c) 2017-2018 The CDC developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.


#pragma once
#include <fc/exception/exception.hpp>

namespace cdcchain {
    namespace db {

        FC_DECLARE_EXCEPTION(level_map_failure, 10000, "level_map failure");
        FC_DECLARE_EXCEPTION(level_map_open_failure, 10001, "level_map open failure");

        FC_DECLARE_EXCEPTION(level_pod_map_failure, 11000, "level_pod_map failure");
        FC_DECLARE_EXCEPTION(level_pod_map_open_failure, 11001, "level_pod_map open failure");

    }
} // cdcchain::db
