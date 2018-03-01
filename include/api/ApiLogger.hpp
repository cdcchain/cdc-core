#pragma once

#include <api/GlobalApiLogger.hpp>

#if CDC_GLOBAL_API_LOG

#include <fc/io/iostream.hpp>
#include <fc/thread/mutex.hpp>
#include <fc/variant.hpp>

namespace cdcchain {
    namespace api {

        class StreamApiLogger : public cdcchain::api::ApiLogger
        {
        public:
            StreamApiLogger(fc::ostream_ptr output);
            virtual ~StreamApiLogger();

            virtual void log_call_started(uint64_t call_id, const cdcchain::api::CommonApi* target, const fc::string& name, const fc::variants& args) override;
            virtual void log_call_finished(uint64_t call_id, const cdcchain::api::CommonApi* target, const fc::string& name, const fc::variants& args, const fc::variant& result) override;

            virtual void close();

            fc::ostream_ptr output;
            fc::mutex output_mutex;
            bool is_first_item;
            bool is_closed;
        };

    }
} // end namespace cdcchain::client

#endif
