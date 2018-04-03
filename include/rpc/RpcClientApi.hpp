// Copyright (c) 2017-2018 The CDC developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.


#pragma once

#include <network/Node.hpp>
#include <wallet/Wallet.hpp>

#include <fc/filesystem.hpp>
#include <fc/network/ip.hpp>

#include <memory>

namespace cdcchain {
    namespace rpc {
        namespace detail { class RpcClientImpl; }

        using namespace cdcchain::consensus;
        using namespace cdcchain::wallet;

        typedef vector<std::pair<ShareType, string> > Balances;

        enum GenerateTransactionFlag
        {
            sign_and_broadcast = 0,
            do_not_broadcast = 1,
            do_not_sign = 2
        };

    }
} // cdcchain::rpc
FC_REFLECT_ENUM(cdcchain::rpc::GenerateTransactionFlag, (do_not_broadcast)(do_not_sign)(sign_and_broadcast))
