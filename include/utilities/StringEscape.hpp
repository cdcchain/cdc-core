// Copyright (c) 2017-2018 The CDC developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.


#pragma once

#include <string>

namespace cdcchain {
    namespace utilities {

        std::string escape_string_for_c_source_code(const std::string& input);

    }
} // end namespace cdcchain::utilities
