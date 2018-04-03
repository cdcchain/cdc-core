// Copyright (c) 2017-2018 The CDC developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.


#pragma once

#include <network/Node.hpp>
#include <rpc_stubs/CommonApiRpcClient.hpp>
#include <wallet/Wallet.hpp>

#include <fc/filesystem.hpp>
#include <fc/network/ip.hpp>

#include <memory>

namespace cdcchain {
    namespace rpc {
        namespace detail { class RpcClientImpl; }

        /**
        *  @class rpc_client
        *  @brief provides a C++ interface to a remote CDC client over JSON-RPC
        */
        class RpcClient : public cdcchain::rpc_stubs::CommonApiRpcClient
        {
        public:
            RpcClient();
            virtual ~RpcClient();

            void connect_to(const fc::ip::endpoint& remote_endpoint,
                const cdcchain::consensus::PublicKeyType& remote_public_key = cdcchain::consensus::PublicKeyType());

            bool login(const std::string& username, const std::string& password);
            virtual fc::rpc::json_connection_ptr get_json_connection() const override;
            void reset_json_connection();
        private:
            std::unique_ptr<detail::RpcClientImpl> my;
        };
        typedef std::shared_ptr<RpcClient> RpcClientPtr;
    }
} // cdcchain::rpc
