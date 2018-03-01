#pragma once

#include <string>

namespace cdcchain {
    namespace utilities {

        std::string escape_string_for_c_source_code(const std::string& input);

    }
} // end namespace cdcchain::utilities
