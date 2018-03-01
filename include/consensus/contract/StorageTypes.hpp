#pragma once

#include <consensus/asset/Asset.hpp>
#include <consensus/Config.hpp>
#include <consensus/Types.hpp>

#include <fc/io/enum_type.hpp>
#include <fc/io/raw.hpp>

#include <uvm/uvm_api.h>
#include <uvm/uvm_lib.h>

#include <uvm/luaconf.h>

namespace cdcchain {
    namespace consensus {

		using uvm::blockchain::StorageValueTypes;

        extern std::map <StorageValueTypes, std::string> storage_type_map;

        struct StorageDataType
        {
            fc::enum_type<uint8_t, StorageValueTypes>  storage_type;
            std::vector<char>                           storage_data;

            StorageDataType() :storage_type(uvm::blockchain::StorageValueTypes::storage_value_null){}

            template<typename StorageType>
            StorageDataType(const StorageType& t)
            {
                storage_type = StorageType::type;
                storage_data = fc::raw::pack(t);
            }

            template<typename StorageType>
            StorageType as()const
            {
                FC_ASSERT(storage_type == StorageType::type, "", ("type", storage_type)("StorageType", StorageType::type));
                return fc::raw::unpack<StorageType>(storage_data);
            }

            static StorageDataType get_storage_data_from_lua_storage(const UvmStorageValue& lua_storage);
            static UvmStorageValue create_lua_storage_from_storage_data(lua_State *L, const StorageDataType& storage_data);

            inline static bool is_table_type(StorageValueTypes type)
            {
                return (type >= StorageValueTypes::storage_value_unknown_table && type <= StorageValueTypes::storage_value_string_table);
            }

            inline static bool is_array_type(StorageValueTypes type)
            {
                return (type >= StorageValueTypes::storage_value_unknown_array && type <= StorageValueTypes::storage_value_string_array);
            }
        };


        struct StorageNullType
        {
            StorageNullType() : raw_storage(0){}

            static const uint8_t    type;
            LUA_INTEGER raw_storage;
        };


        struct StorageIntType
        {
            StorageIntType(){}
            StorageIntType(LUA_INTEGER value) :raw_storage(value){}

            static const uint8_t    type;
            LUA_INTEGER raw_storage;
        };


        struct StorageNumberType
        {
            StorageNumberType(){}
            StorageNumberType(double value) :raw_storage(value){}

            static const uint8_t    type;
            double raw_storage;
        };


        struct StorageBoolType
        {
            StorageBoolType(){}
            StorageBoolType(bool value) :raw_storage(value){}

            static const uint8_t    type;
            bool raw_storage;
        };


        struct StorageStringType
        {
            StorageStringType(){}
            StorageStringType(string value) :raw_storage(value){}

            static const uint8_t    type;
            string raw_storage;
        };

        //table
        struct StorageIntTableType
        {
            StorageIntTableType(){}
            StorageIntTableType(const std::map<std::string, LUA_INTEGER>& value_map) :raw_storage_map(value_map){}

            static const uint8_t    type;
            std::map<std::string, LUA_INTEGER> raw_storage_map;
        };


        struct StorageNumberTableType
        {
            StorageNumberTableType(){}
            StorageNumberTableType(const std::map<std::string, double>& value_map) :raw_storage_map(value_map){}

            static const uint8_t    type;
            std::map<std::string, double> raw_storage_map;
        };


        struct StorageBoolTableType
        {
            StorageBoolTableType(){}
            StorageBoolTableType(const std::map<std::string, bool>& value_map) :raw_storage_map(value_map){}

            static const uint8_t    type;
            std::map<std::string, bool> raw_storage_map;
        };

        struct StorageStringTableType
        {
            StorageStringTableType(){}
            StorageStringTableType(const std::map<std::string, string>& value_map) :raw_storage_map(value_map){}

            static const uint8_t    type;
            std::map<std::string, string> raw_storage_map;
        };

        //array
        struct StorageIntArrayType
        {
            StorageIntArrayType(){}
            StorageIntArrayType(const std::map<std::string, LUA_INTEGER>& value_map) :raw_storage_map(value_map){}

            static const uint8_t    type;
            std::map<std::string, LUA_INTEGER> raw_storage_map;
        };


        struct StorageNumberArrayType
        {
            StorageNumberArrayType(){}
            StorageNumberArrayType(const std::map<std::string, double>& value_map) :raw_storage_map(value_map){}

            static const uint8_t    type;
            std::map<std::string, double> raw_storage_map;
        };


        struct StorageBoolArrayType
        {
            StorageBoolArrayType(){}
            StorageBoolArrayType(const std::map<std::string, bool>& value_map) :raw_storage_map(value_map){}

            static const uint8_t    type;
            std::map<std::string, bool> raw_storage_map;
        };

        struct StorageStringArrayType
        {
            StorageStringArrayType(){}
            StorageStringArrayType(const std::map<std::string, string>& value_map) :raw_storage_map(value_map){}

            static const uint8_t    type;
            std::map<std::string, string> raw_storage_map;
        };

    }
} // cdcchain::consensus


FC_REFLECT_ENUM(cdcchain::consensus::StorageValueTypes,
    (storage_value_null)
    (storage_value_int)
    (storage_value_number)
    (storage_value_bool)
    (storage_value_string)
    (storage_value_unknown_table)
    (storage_value_int_table)
    (storage_value_number_table)
    (storage_value_bool_table)
    (storage_value_string_table)
    (storage_value_unknown_array)
    (storage_value_int_array)
    (storage_value_number_array)
    (storage_value_bool_array)
    (storage_value_string_array)
    )

    FC_REFLECT(cdcchain::consensus::StorageDataType,
    (storage_type)
    (storage_data)
    )

    FC_REFLECT(cdcchain::consensus::StorageNullType,
    (raw_storage)
    )

    FC_REFLECT(cdcchain::consensus::StorageIntType,
    (raw_storage)
    )

    FC_REFLECT(cdcchain::consensus::StorageBoolType,
    (raw_storage)
    )

    FC_REFLECT(cdcchain::consensus::StorageNumberType,
    (raw_storage)
    )

    FC_REFLECT(cdcchain::consensus::StorageStringType,
    (raw_storage)
    )

    FC_REFLECT(cdcchain::consensus::StorageIntTableType,
    (raw_storage_map)
    )

    FC_REFLECT(cdcchain::consensus::StorageBoolTableType,
    (raw_storage_map)
    )

    FC_REFLECT(cdcchain::consensus::StorageNumberTableType,
    (raw_storage_map)
    )

    FC_REFLECT(cdcchain::consensus::StorageStringTableType,
    (raw_storage_map)
    )

    FC_REFLECT(cdcchain::consensus::StorageIntArrayType,
    (raw_storage_map)
    )

    FC_REFLECT(cdcchain::consensus::StorageBoolArrayType,
    (raw_storage_map)
    )

    FC_REFLECT(cdcchain::consensus::StorageNumberArrayType,
    (raw_storage_map)
    )

    FC_REFLECT(cdcchain::consensus::StorageStringArrayType,
    (raw_storage_map)
    )
