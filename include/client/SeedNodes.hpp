#pragma once

namespace cdcchain {
    namespace client {

#ifndef CDC_TEST_NETWORK
        static const std::vector<std::string> SeedNodes
        {
			"35.169.193.139:50066",
			"54.241.225.196:50066",
			"54.241.197.100:50066",
			"34.239.55.17:50066",
			"54.83.144.117:50066",
			"34.202.114.151:50066",
			"18.217.10.131:50066",
			"18.216.152.205:50066",
			"18.218.55.92:50066",
			"52.89.234.162:50066"
        };
#else
        static const std::vector<std::string> SeedNodes
        {
        };
#endif

    }
} // cdcchain::client
