// Copyright (c) 2017-2018 The CDC developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.


#pragma once

#include <fc/exception/exception.hpp>

namespace cdcchain {
    namespace rpc {

        // All registered in rpc_server.cpp
        FC_DECLARE_EXCEPTION(rpc_exception, 60000, "RPC Error");
        FC_DECLARE_EXCEPTION(missing_parameter, 60001, "Missing Parameter");
        FC_DECLARE_EXCEPTION(unknown_method, 60002, "Unknown Method");
        FC_DECLARE_EXCEPTION(login_required, 60003, "Login Required");

    }
} // cdcchain::rpc
