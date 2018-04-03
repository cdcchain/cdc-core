// Copyright (c) 2017-2018 The CDC developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.



#pragma once

#if CDC_GLOBAL_API_LOG

#include <fc/variant.hpp>

namespace cdcchain {
    namespace api {

        class CommonApi;

        // individual api_logger objects are called from singleton global_api_logger
        class ApiLogger
        {
        public:

            ApiLogger();
            virtual ~ApiLogger();

            virtual void log_call_started(uint64_t call_id, const cdcchain::api::CommonApi* target, const fc::string& name, const fc::variants& args) = 0;
            virtual void log_call_finished(uint64_t call_id, const cdcchain::api::CommonApi* target, const fc::string& name, const fc::variants& args, const fc::variant& result) = 0;

            virtual void connect();
            virtual void disconnect();

            bool is_connected;
        };

        class GlobalApiLogger
        {
        public:

            GlobalApiLogger();
            virtual ~GlobalApiLogger();

            virtual uint64_t log_call_started(const cdcchain::api::CommonApi* target, const fc::string& name, const fc::variants& args) = 0;
            virtual void log_call_finished(uint64_t call_id, const cdcchain::api::CommonApi* target, const fc::string& name, const fc::variants& args, const fc::variant& result) = 0;
            virtual bool obscure_passwords() const = 0;

            static GlobalApiLogger* get_instance();

            static GlobalApiLogger* the_instance;

            std::vector< ApiLogger* > active_loggers;
        };

    }
} // end namespace cdcchain::api

#endif
