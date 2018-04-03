// Copyright (c) 2017-2018 The CDC developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.


#include <stdint.h>
#include <utilities/GitRevision.hpp>

#define CDCCORE_GIT_REVISION_SHA "7e7f255f185ffaf53397084f6ca747674088f176"
#define CDCCORE_GIT_REVISION_UNIX_TIMESTAMP 1488663957
#define CDCCORE_GIT_REVISION_DESCRIPTION "SmallCDC"

namespace cdcchain {
    namespace utilities {

        const char* const git_revision_sha = CDCCORE_GIT_REVISION_SHA;
        const uint32_t git_revision_unix_timestamp = CDCCORE_GIT_REVISION_UNIX_TIMESTAMP;
        const char* const git_revision_description = CDCCORE_GIT_REVISION_DESCRIPTION;

    }
} // end namespace cdcchain::utilities
