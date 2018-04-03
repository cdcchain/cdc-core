// Copyright (c) 2017-2018 The CDC developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.


#pragma once
#include <memory>
#include <fc/variant.hpp>
#include <fc/exception/exception.hpp>
#include <fc/log/log_message.hpp>
#include <api/ApiMetadata.hpp>
#include <rpc_stubs/CommonApiRpcServer.hpp>
#include <client/Client.hpp>
#include <fc/network/http/server.hpp>

namespace cdcchain {
    namespace client {
        class client;
    }
}

namespace cdcchain {
    namespace rpc {
        namespace detail { class RpcServerImpl; }

        typedef std::map<std::string, cdcchain::api::MethodData> MethodMapType;
        typedef std::function<void(const fc::path& filename, const fc::http::server::response&)> HttpCallbackType;
        /**
        *  @class rpc_server
        *  @brief provides a json-rpc interface to the cdcchain client
        */
        class RpcServer
        {
        public:
            RpcServer(cdcchain::client::Client* client);
            virtual ~RpcServer();

            bool        configure_rpc(const cdcchain::client::RpcServerConfig& cfg);
            bool        configure_http(const cdcchain::client::RpcServerConfig& cfg);
            bool        configure_encrypted_rpc(const cdcchain::client::RpcServerConfig& cfg);

            /// used to invoke json methods from the cli without going over the network
            fc::variant direct_invoke_method(const std::string& method_name, const fc::variants& arguments);

            const cdcchain::api::MethodData& get_method_data(const std::string& method_name);
            std::vector<cdcchain::api::MethodData> get_all_method_data() const;

            // wait until the RPC server is shut down (via the above close(), or by processing a "stop" RPC call)
            void wait_till_rpc_server_shutdown();
            void shutdown_rpc_server();
            std::string help(const std::string& command_name) const;

            MethodMapType meta_help()const;

            void set_http_file_callback(const HttpCallbackType&);

            fc::optional<fc::ip::endpoint> get_rpc_endpoint() const;
            fc::optional<fc::ip::endpoint> get_httpd_endpoint() const;
        protected:
            friend class cdcchain::rpc::detail::RpcServerImpl;

            void validate_method_data(cdcchain::api::MethodData method);
            void register_method(cdcchain::api::MethodData method);

        private:
            std::unique_ptr<detail::RpcServerImpl> my;
        };

        typedef std::shared_ptr<RpcServer> RpcServerPtr;


        class Exception : public fc::exception {
        public:
            Exception(fc::log_message&& m);
            Exception(fc::log_messages);
            Exception(const Exception& c);
            Exception();
            virtual const char* what() const throw() override = 0;
            virtual int32_t get_rpc_error_code() const = 0;
        };

#define RPC_DECLARE_EXCEPTION(TYPE) \
  class TYPE : public Exception \
          { \
  public: \
    TYPE( fc::log_message&& m ); \
    TYPE( fc::log_messages ); \
    TYPE( const TYPE& c ); \
    TYPE(); \
    virtual const char* what() const throw() override; \
    int32_t get_rpc_error_code() const override; \
          };

        RPC_DECLARE_EXCEPTION(rpc_misc_error_exception)

            RPC_DECLARE_EXCEPTION(rpc_client_not_connected_exception)

            RPC_DECLARE_EXCEPTION(rpc_wallet_unlock_needed_exception)
            RPC_DECLARE_EXCEPTION(rpc_wallet_passphrase_incorrect_exception)
            RPC_DECLARE_EXCEPTION(rpc_wallet_open_needed_exception)
            RPC_DECLARE_EXCEPTION(rpc_simulator_open_needed_exception)

    }
} // cdcchain::rpc

