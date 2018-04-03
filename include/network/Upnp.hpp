// Copyright (c) 2017-2018 The CDC developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.


#pragma once
#include <stdint.h>
#include <memory>
#include <fc/network/ip.hpp>

namespace cdcchain {
    namespace network {

        namespace detail { class UpnpServiceImpl; }

        class UpnpService
        {
        public:
            UpnpService();
            ~UpnpService();

            fc::ip::address external_ip()const;
            uint16_t mapped_port()const;
            void map_port(uint16_t p);
        private:
            std::unique_ptr<detail::UpnpServiceImpl> my;
        };

    }
} // cdcchain::net
