// Copyright (c) 2017-2018 The CDC developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.


#pragma once
#include <stdint.h>

namespace cdcchain {
    namespace utilities {

        extern const char* const git_revision_sha;
        extern const uint32_t git_revision_unix_timestamp;
        extern const char* const git_revision_description;

    }
} // end namespace cdcchain::utilities
