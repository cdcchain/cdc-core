#include <consensus/Time.hpp>
#include <client/Client.hpp>
#include <client/ClientImpl.hpp>
#include <utilities/KeyConversion.hpp>
#include <wallet/Wallet.hpp>

#ifndef WIN32
#include <csignal>
#endif

namespace cdcchain {
    namespace client {
        namespace detail {

            std::string ClientImpl::debug_get_client_name() const
            {
                // set limit in  simulator state
                if (_chain_db->get_is_in_simulator())
                    FC_THROW_EXCEPTION(simulator_command_forbidden, "in simulator, this command is forbidden, you cannot call it!");

                return this->_config.client_debug_name;
            }

        }
    }
} // namespace cdcchain::client::detail
