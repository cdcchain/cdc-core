#pragma once
#include <consensus/Types.hpp>

namespace cdcchain {
    namespace consensus {
        namespace detail{

            static std::map<uint32_t, cdcchain::consensus::BlockIdType> CHECKPOINT_BLOCKS
            {
                //{ 1246900, cdcchain::consensus::block_id_type( "b5214c1bc914ea5da6c1bb8f774d07f12b85dbe2" ) },
                //{ 1279500, cdcchain::consensus::block_id_type( "488313d2c1c85bdec117bac0379f7b17f7cfbed3" ) }
            };
            // Initialized in load_checkpoints()
            static uint32_t LAST_CHECKPOINT_BLOCK_NUM = 0;

        }
    }
} // cdcchain::consensus
