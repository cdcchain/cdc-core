// Copyright (c) 2017-2018 The CDC developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.


/** @file cdcchain/blockchain/fork_blocks.hpp
 *  @brief Defines global block number constants for when hardforks take effect
 */

#pragma once

#include <stdint.h>
#include <vector>

#define CDC_EXPECTED_CHAIN_ID       DigestType( "6ae7455c7af731c05698dae7100345ba0e4e229b99672d025201a80909cb8092" )
#define CDC_DESIRED_CHAIN_ID        DigestType( "75c11a81b7670bbaa721cc603eadb2313756f94a3bcbb9928e9101432701ac5f" )

#define CDC_V0_4_0_FORK_BLOCK_NUM    274000
#define CDC_V0_4_9_FORK_BLOCK_NUM    316001
#define CDC_V0_4_9_FORK_2_BLOCK_NUM  340000
#define CDC_V0_4_10_FORK_BLOCK_NUM   357000
#define CDC_V0_4_12_FORK_BLOCK_NUM   408750
#define CDC_V0_4_13_FORK_BLOCK_NUM   451500
#define CDC_V0_4_15_FORK_BLOCK_NUM   494000
#define CDC_V0_4_16_FORK_BLOCK_NUM   554800
#define CDC_V0_4_17_FORK_BLOCK_NUM   578900
#define CDC_V0_4_18_FORK_BLOCK_NUM   613200
#define CDC_V0_4_19_FORK_BLOCK_NUM   640000
#define CDC_V0_4_21_FORK_BLOCK_NUM   820200
#define CDC_V0_4_23_FORK_BLOCK_NUM   871000
#define CDC_V0_4_24_FORK_BLOCK_NUM   991700
#define CDC_V0_4_26_FORK_BLOCK_NUM  1315314
#define CDC_V0_5_0_FORK_BLOCK_NUM   1575500
#define CDC_V0_6_0_FORK_BLOCK_NUM   1772200
#define CDC_V0_6_1_FORK_BLOCK_NUM   CDC_V0_6_0_FORK_BLOCK_NUM
#define CDC_V0_6_2_FORK_BLOCK_NUM   CDC_V0_6_0_FORK_BLOCK_NUM
#define CDC_V0_6_3_FORK_BLOCK_NUM   CDC_V0_6_0_FORK_BLOCK_NUM

#define CDC_V0_6_4_FORK_BLOCK_NUM   2071000 // TODO: Rename

#define CDC_SHORTFIX_FORK_BLOCK_NUM 2113000 // TODO: Rename

#define CDC_V0_7_0_FORK_BLOCK_NUM   9999999
#define CDC_V0_8_0_FORK_BLOCK_NUM   9999999

#define CDC_FORK_TO_UNIX_TIME_LIST  ((CDC_V0_4_0_FORK_BLOCK_NUM,   "0.4.0",     1408064036)) \
                                    ((CDC_V0_4_9_FORK_2_BLOCK_NUM, "0.4.9",     1409193626)) \
                                    ((CDC_V0_4_10_FORK_BLOCK_NUM,  "0.4.10",    1409437355)) \
                                    ((CDC_V0_4_12_FORK_BLOCK_NUM,  "0.4.12",    1409846462)) \
                                    ((CDC_V0_4_13_FORK_BLOCK_NUM,  "0.4.13",    1410294635)) \
                                    ((CDC_V0_4_15_FORK_BLOCK_NUM,  "0.4.15",    1410657316)) \
                                    ((CDC_V0_4_16_FORK_BLOCK_NUM,  "0.4.16",    1411258737)) \
                                    ((CDC_V0_4_17_FORK_BLOCK_NUM,  "0.4.17",    1411599233)) \
                                    ((CDC_V0_4_18_FORK_BLOCK_NUM,  "0.4.18",    1411765631)) \
                                    ((CDC_V0_4_19_FORK_BLOCK_NUM,  "0.4.19",    1412203442)) \
                                    ((CDC_V0_4_21_FORK_BLOCK_NUM,  "0.4.21",    1414019090)) \
                                    ((CDC_V0_4_23_FORK_BLOCK_NUM,  "0.4.23",    1414426032)) \
                                    ((CDC_V0_4_24_FORK_BLOCK_NUM,  "0.4.24",    1415398550)) \
                                    ((CDC_V0_4_26_FORK_BLOCK_NUM,  "0.4.26",    1418401491)) \
                                    ((CDC_V0_5_0_FORK_BLOCK_NUM,   "0.5.0",     1421192371)) \
                                    ((CDC_V0_6_0_FORK_BLOCK_NUM,   "0.6.0",     1423270604)) \
                                    ((CDC_V0_6_4_FORK_BLOCK_NUM,   "0.7.0",     1426625313))

namespace cdcchain {
    namespace consensus {
        uint32_t estimate_last_known_fork_from_git_revision_timestamp(uint32_t revision_time);
        std::vector<uint32_t> get_list_of_fork_block_numbers();
    }
}
