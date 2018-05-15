option(TESTNET "ON for testnet or OFF for mainnet" OFF)
if(${TESTNET} STREQUAL "ON")
set(CDC_BIN_NAME "cdc-test")
else()
set(CDC_BIN_NAME "cdc")
endif()

aux_source_directory(src/api API_SRC)
aux_source_directory(src/client CLIENT_SRC)
aux_source_directory(src/console CONSOLE_SRC)
aux_source_directory(src/db DB_SRC)
aux_source_directory(src/network NETWORK_SRC)
aux_source_directory(src/rpc RPC_SRC)
aux_source_directory(src/rpc_stubs RPC_STUBS_SRC)
aux_source_directory(src/utilities UTILITIES_SRC)
aux_source_directory(src/wallet WALLET_SRC)
aux_source_directory(src/consensus            CONSENSUS_SRC)
aux_source_directory(src/consensus/account    CONSENSUS_SRC_account)
aux_source_directory(src/consensus/address    CONSENSUS_SRC_address)
aux_source_directory(src/consensus/asset      CONSENSUS_SRC_asset)
aux_source_directory(src/consensus/balance    CONSENSUS_SRC_balance)
aux_source_directory(src/consensus/block      CONSENSUS_SRC_block)
aux_source_directory(src/consensus/chainstate CONSENSUS_SRC_chainstate)
aux_source_directory(src/consensus/contract   CONSENSUS_SRC_contract)
aux_source_directory(src/consensus/contract_engine  CONSENSUS_SRC_contract_engine)
aux_source_directory(src/consensus/genesis    CONSENSUS_SRC_genesis)
aux_source_directory(src/consensus/operation  CONSENSUS_SRC_operation)
aux_source_directory(src/consensus/property   CONSENSUS_SRC_property)
aux_source_directory(src/consensus/slate      CONSENSUS_SRC_slate)
aux_source_directory(src/consensus/slot       CONSENSUS_SRC_slot)
aux_source_directory(src/consensus/transaction      CONSENSUS_SRC_transaction)
aux_source_directory(src/consensus/proposal      CONSENSUS_SRC_proposal)
aux_source_directory(src/consensus/role      CONSENSUS_SRC_role)
aux_source_directory(src/consensus/cdcdata      CONSENSUS_SRC_cdcdata)

add_definitions("-DHAVE_CXX_STDHEADERS")

option(TESTNET "ON for testnet or OFF for mainnet" ON)
if(TESTNET)
add_definitions("-DCDC_TEST_NETWORK")
endif()

cmake_minimum_required(VERSION 2.8)
SET (CMAKE_CXX_COMPILER     "/usr/bin/g++")

# Boost settings
set(Boost_USE_STATIC_LIBS     ON)
set(Boost_USE_MULTITHREADED   ON)
set(Boost_USE_STATIC_RUNTIME  ON)

# Specify Boost libraries that will use.
find_package( Boost REQUIRED COMPONENTS system program_options chrono context coroutine date_time exception filesystem iostreams locale thread )

set(CMAKE_CXX_FLAGS "-std=c++11 -w -DCDC_GLOBAL_API_LOG=1" )
set(Boost_INCLUDE_DIR　"/usr/include/boost")
set(Boost_LIBRARY_DIR  "/usr/lib/x86_64-linux-gnu")

include_directories( ${Boost_INCLUDE_DIR}
        "include"
        "dependence/fc/include"
        "dependence/leveldb/include"
        "dependence/miniupnp"
        "dependence/openssl/include"
        "dependence/libuvm/include"
)

link_directories( ${Boost_LIBRARY_DIR}
        "dependence/fc"
        "dependence/leveldb/out-static"
        "dependence/miniupnp/miniupnpc"
        "dependence/openssl"
        "dependence/fc/vendor/secp256k1-zkp/src/project_secp256k1-build/.libs"
        "dependence/libuvm/lib64/linux"
        "."
        "src/api"
        "src/client"
        "src/consensus"
        "src/console"
        "src/db"
        "src/network"
        "src/rpc"
        "src/rpc_stubs"
        "src/utilities"
        "src/wallet"
)

set(SOURCE_FILES
	src/Main.cpp
)

add_library(blockchain ${API_SRC} ${CLIENT_SRC} ${CONSOLE_SRC} ${DB_SRC} ${NETWORK_SRC} ${RPC_SRC} ${RPC_STUBS_SRC} ${UTILITIES_SRC} ${WALLET_SRC}
                ${CONSENSUS_SRC}
                ${CONSENSUS_SRC_account} ${CONSENSUS_SRC_address} ${CONSENSUS_SRC_asset} ${CONSENSUS_SRC_balance} ${CONSENSUS_SRC_block} ${CONSENSUS_SRC_chainstate} ${CONSENSUS_SRC_contract}
                ${CONSENSUS_SRC_contract_engine} ${CONSENSUS_SRC_genesis} ${CONSENSUS_SRC_operation} ${CONSENSUS_SRC_property} ${CONSENSUS_SRC_slate} ${CONSENSUS_SRC_slot} ${CONSENSUS_SRC_transaction}
                ${CONSENSUS_SRC_proposal} ${CONSENSUS_SRC_role} ${CONSENSUS_SRC_cdcdata} 
)

add_executable(${CDC_BIN_NAME} ${SOURCE_FILES})
target_link_libraries(${CDC_BIN_NAME} blockchain libuvm.a libfc.a libsecp256k1.a libleveldb.a libminiupnpc.a ${Boost_LIBRARIES} libcrypto.a dl)
