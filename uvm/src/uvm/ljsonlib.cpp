#define ljsonlib_cpp

#include <uvm/lprefix.h>


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>
#include <sstream>
#include <cassert>

#include <uvm/lua.h>

#include <uvm/lauxlib.h>
#include <uvm/lualib.h>
#include <uvm/uvm_tokenparser.h>
#include <uvm/uvm_api.h>
#include <uvm/uvm_lib.h>
#include <uvm/uvm_lutil.h>

using uvm::lua::api::global_uvm_chain_api;

using namespace uvm::parser;

static UvmStorageValue nil_storage_value()
{
    UvmStorageValue value;
    value.type = uvm::blockchain::StorageValueTypes::storage_value_null;
    value.value.int_value = 0;
    return value;
}

static UvmStorageValue tokens_to_lua_value(lua_State *L, UvmTokenParser *token_parser, bool *result)
{
    if (token_parser->eof())
    {
        if (nullptr != result)
        {
            *result = false;
        }
        return nil_storage_value();
    }
    auto cur_token = token_parser->current();
    if (token_parser->current_position() == token_parser->size() - 1 || (cur_token.type != '{' && cur_token.type != '['))
    {
        auto token = token_parser->current();
        token_parser->next();
        switch (token.type)
        {
        case TOKEN_RESERVED::LTK_INT:
        {
            auto token_str = token.token;
            std::stringstream ss;
            ss << token_str;
            lua_Integer token_int = 0;
            ss >> token_int;
            UvmStorageValue value;
            value.type = uvm::blockchain::StorageValueTypes::storage_value_int;
            value.value.int_value = token_int;
            if (nullptr != result)
                *result = true;
            return value;
        }  break;
        case TOKEN_RESERVED::LTK_FLT:
        {
            auto token_str = token.token;
            std::stringstream ss;
            ss << token_str;
            lua_Number token_num = 0;
            ss >> token_num;
            UvmStorageValue value;
            value.type = uvm::blockchain::StorageValueTypes::storage_value_number;
            value.value.number_value = token_num;
            if (nullptr != result)
                *result = true;
            return value;
        } break;
        case TOKEN_RESERVED::LTK_TRUE:
        case TOKEN_RESERVED::LTK_FALSE:
        case TOKEN_RESERVED::LTK_NAME:
        {
            auto token_str = token.token;
            if (token_str == "true")
            {
                UvmStorageValue value;
                value.type = uvm::blockchain::StorageValueTypes::storage_value_bool;
                value.value.bool_value = true;
                if (nullptr != result)
                    *result = true;
                return value;
            }
            else if (token_str == "false")
            {
                UvmStorageValue value;
                value.type = uvm::blockchain::StorageValueTypes::storage_value_bool;
                value.value.bool_value = false;
                if (nullptr != result)
                    *result = true;
                return value;
            }
            else if (token_str == "null")
            {
                UvmStorageValue value;
                value.type = uvm::blockchain::StorageValueTypes::storage_value_null;
                value.value.int_value = 0;
                if (nullptr != result)
                    *result = true;
                return value;
            }
            else
            {
                global_uvm_chain_api->throw_exception(L, UVM_API_SIMPLE_ERROR, "parse json error(unknown symbol name %s)", token_str.c_str());
                if (nullptr != result)
                    *result = false;
                return nil_storage_value();
            }
        } break;
        case TOKEN_RESERVED::LTK_STRING:
        {
            UvmStorageValue value;
            value.type = uvm::blockchain::StorageValueTypes::storage_value_string;
            auto token_str = token.token;
			// FIXME: unescape
			token_str = uvm::util::unescape_string(token_str);
            value.value.string_value = uvm::lua::lib::malloc_managed_string(L, token_str.length() + 1);
            memset(value.value.string_value, 0x0, token_str.length() + 1);
            strncpy(value.value.string_value, token_str.c_str(), token_str.length());
            assert(nullptr != value.value.string_value);
            if (nullptr != result)
                *result = true;
            return value;
        } break;
        default:
            global_uvm_chain_api->throw_exception(L, UVM_API_SIMPLE_ERROR, "parse json error(unknown token %s)", token.token.c_str());
            if (nullptr != result)
                *result = false;
            return nil_storage_value();
        }
    }
    auto token = token_parser->current();
    token_parser->next();
    switch (token.type)
    {
    case '{':
    {
        if (token_parser->eof())
        {
            global_uvm_chain_api->throw_exception(L, UVM_API_SIMPLE_ERROR, "parse json error(unknown token %s)", token.token.c_str());
            if (nullptr != result)
                *result = false;
            return nil_storage_value();
        }
        if (token_parser->current().type == '}')
        {
            token_parser->next();
            UvmStorageValue value;
            value.type = uvm::blockchain::StorageValueTypes::storage_value_unknown_table;
            value.value.table_value = uvm::lua::lib::create_managed_lua_table_map(L);
            assert(nullptr != value.value.table_value);
            if (nullptr != result)
                *result = true;
            return value;
        }
        UvmStorageValue table_value;
        table_value.type = uvm::blockchain::StorageValueTypes::storage_value_unknown_table; // FIXME: change it by sub item value type
        table_value.value.table_value = uvm::lua::lib::create_managed_lua_table_map(L);
        assert(nullptr != table_value.value.table_value);
        do
        {
            if (token_parser->eof())
            {
                global_uvm_chain_api->throw_exception(L, UVM_API_SIMPLE_ERROR, "parse json error(unknown token %s)", token.token.c_str());
                if (nullptr != result)
                    *result = false;
                return nil_storage_value();
            }
            token = token_parser->current();
            token_parser->next();
            if (token.type != TOKEN_RESERVED::LTK_STRING)
            {
                global_uvm_chain_api->throw_exception(L, UVM_API_SIMPLE_ERROR, "parse json error(unknown token %s)", token.token.c_str());
                if (nullptr != result)
                    *result = false;
                return nil_storage_value();
            }
            auto prop_key = token.token;
            if (token_parser->eof())
            {
                global_uvm_chain_api->throw_exception(L, UVM_API_SIMPLE_ERROR, "parse json error(unknown token %s)", token.token.c_str());
                if (nullptr != result)
                    *result = false;
                return nil_storage_value();
            }
            token = token_parser->current();
            token_parser->next();
            if (token.type != ':')
            {
                global_uvm_chain_api->throw_exception(L, UVM_API_SIMPLE_ERROR, "parse json error(unknown token %s)", token.token.c_str());
                if (nullptr != result)
                    *result = false;
                return nil_storage_value();
            }
            if (token_parser->eof())
            {
                global_uvm_chain_api->throw_exception(L, UVM_API_SIMPLE_ERROR, "parse json error(unknown token %s)", token.token.c_str());
                if (nullptr != result)
                    *result = false;
                return nil_storage_value();
            }
            bool sub_result = false;
            auto sub_value = tokens_to_lua_value(L, token_parser, &sub_result);
            if (!sub_result)
            {
                if (nullptr != result)
                    *result = false;
                return nil_storage_value();
            }
            table_value.value.table_value->erase(prop_key);
            (*table_value.value.table_value)[prop_key] = sub_value;
            if (token_parser->eof())
            {
                global_uvm_chain_api->throw_exception(L, UVM_API_SIMPLE_ERROR, "parse json error(unknown token %s)", token.token.c_str());
                if (nullptr != result)
                    *result = false;
                return nil_storage_value();
            }
            token = token_parser->current();
            token_parser->next();
            if (token.type == ',')
            {
                // go on read the table content
            }
            else if (token.type == '}')
            {
                // end of table content
                break;
            }
            else
            {
                global_uvm_chain_api->throw_exception(L, UVM_API_SIMPLE_ERROR, "parse json error(unknown token %s)", token.token.c_str());
                if (nullptr != result)
                    *result = false;
                return nil_storage_value();
            }
        } while (true);
        if (nullptr != result)
            *result = true;
        return table_value;
    }break;
    case '[':
    {
        if (token_parser->eof())
        {
            global_uvm_chain_api->throw_exception(L, UVM_API_SIMPLE_ERROR, "parse json error(unknown token %s)", token.token.c_str());
            if (nullptr != result)
                *result = false;
            return nil_storage_value();
        }
        if (token_parser->current().type == ']')
        {
            token_parser->next();
            UvmStorageValue value;
            value.type = uvm::blockchain::StorageValueTypes::storage_value_unknown_array;
            value.value.table_value = uvm::lua::lib::create_managed_lua_table_map(L);
            assert(nullptr != value.value.table_value);
            if (nullptr != result)
                *result = true;
            return value;
        }
        UvmStorageValue table_value;
        table_value.type = uvm::blockchain::StorageValueTypes::storage_value_unknown_array; // FIXME: change by sub item value type
        table_value.value.table_value = uvm::lua::lib::create_managed_lua_table_map(L);
        assert(nullptr != table_value.value.table_value);
        size_t count = 0;
        do
        {
            if (token_parser->eof())
            {
                global_uvm_chain_api->throw_exception(L, UVM_API_SIMPLE_ERROR, "parse json error(unknown token %s)", token.token.c_str());
                if (nullptr != result)
                    *result = false;
                return nil_storage_value();
            }
            bool sub_result = false;
            auto sub_value = tokens_to_lua_value(L, token_parser, &sub_result);
            if (!sub_result)
            {
                if (nullptr != result)
                    *result = false;
                return nil_storage_value();
            }
            auto prop_key = std::to_string(++count);
            table_value.value.table_value->erase(prop_key);
            (*table_value.value.table_value)[prop_key] = sub_value;
            if (token_parser->eof())
            {
                global_uvm_chain_api->throw_exception(L, UVM_API_SIMPLE_ERROR, "parse json error(unknown token %s)", token.token.c_str());
                if (nullptr != result)
                    *result = false;
                return nil_storage_value();
            }
            token = token_parser->current();
            token_parser->next();
            if (token.type == ',')
            {
                // go on read the array content
            }
            else if (token.type == ']')
            {
                // end of table content
                break;
            }
            else
            {
                global_uvm_chain_api->throw_exception(L, UVM_API_SIMPLE_ERROR, "parse json error(unknown token %s)", token.token.c_str());
                if (nullptr != result)
                    *result = false;
                return nil_storage_value();
            }
        } while (true);
        if (nullptr != result)
            *result = true;
        return table_value;
    } break;

    default:
    {
        bool result = false;
        auto value = tokens_to_lua_value(L, token_parser, &result);
        if (!result)
            return nil_storage_value();
        return value; // FIXME: this not check the matched { and [ and whether there are more chars after the token
    }
    }
}

static int json_to_lua(lua_State *L)
{
    if (lua_gettop(L) < 1)
        return 0;
    if (!lua_isstring(L, 1))
        return 0;
    auto json_str = luaL_checkstring(L, 1);
    uvm::lua::lib::UvmStateScope scope;
    auto token_parser = std::make_shared<UvmTokenParser>(scope.L());
    token_parser->parse(std::string(json_str));
    token_parser->reset_position();
    bool result = false;
    auto value = tokens_to_lua_value(L, token_parser.get(), &result);
    if (!result)
    {
        return 0;
    }
    lua_push_storage_value(L, value);
    return 1;
}

static int lua_to_json(lua_State *L)
{
    if (lua_gettop(L) < 1)
        return 0;
    auto value = luaL_tojsonstring(L, 1, nullptr);
    lua_pushstring(L, value);
    return 1;
}

static const luaL_Reg dblib[] = {
    { "loads", json_to_lua },
    { "dumps", lua_to_json },
    { nullptr, nullptr }
};


LUAMOD_API int luaopen_json(lua_State *L) {
    luaL_newlib(L, dblib);
    return 1;
}

