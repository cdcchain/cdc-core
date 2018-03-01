#include <uvm/lprefix.h>

#include <stdlib.h>
#include <math.h>
#include <string>
#include <vector>
#include <unordered_map>
#include <memory>

#include <uvm/uvm_storage.h>
#include <uvm/uvm_lib.h>

using uvm::lua::api::global_uvm_chain_api;

static UvmStorageTableReadList *get_or_init_storage_table_read_list(lua_State *L)
{
	UvmStateValueNode state_value_node = uvm::lua::lib::get_lua_state_value_node(L, LUA_STORAGE_READ_TABLES_KEY);
	UvmStorageTableReadList *list = nullptr;;
	if (state_value_node.type != LUA_STATE_VALUE_POINTER || nullptr == state_value_node.value.pointer_value)
	{
		list = (UvmStorageTableReadList*)malloc(sizeof(UvmStorageTableReadList));
		new (list)UvmStorageTableReadList();
		UvmStateValue value_to_store;
		value_to_store.pointer_value = list;
		uvm::lua::lib::set_lua_state_value(L, LUA_STORAGE_READ_TABLES_KEY, value_to_store, LUA_STATE_VALUE_POINTER);
	}
	else
	{
		list = (UvmStorageTableReadList*)state_value_node.value.pointer_value;
	}
	return list;
}

static struct UvmStorageValue get_last_storage_changed_value(lua_State *L, const char *contract_id,
	UvmStorageChangeList *list, const std::string &key)
{
	struct UvmStorageValue nil_value;
	nil_value.type = uvm::blockchain::StorageValueTypes::storage_value_null;
	auto post_when_read_table = [&](UvmStorageValue value) {
		if (lua_storage_is_table(value.type))
		{
			// when read a table, snapshot it and record it, when commit, merge to the changes
			UvmStorageTableReadList *table_read_list = get_or_init_storage_table_read_list(L);
			if (table_read_list)
			{
				for (auto it = table_read_list->begin(); it != table_read_list->end(); ++it)
				{
					if (it->contract_id == std::string(contract_id) && it->key == key)
					{
						return;
					}
				}
				UvmStorageChangeItem change_item;
				change_item.contract_id = contract_id;
				change_item.key = key;
				change_item.before = value;
				table_read_list->push_back(change_item);
			}
		}
	};
	if (!list || list->size() < 1)
	{
		auto value = global_uvm_chain_api->get_storage_value_from_uvm_by_address(L, contract_id, key);
		post_when_read_table(value);
		// cache the value if it's the first time to read
		if (!list) {
			list = (UvmStorageChangeList*)malloc(sizeof(UvmStorageChangeList));
			new (list)UvmStorageChangeList();
			UvmStateValue value_to_store;
			value_to_store.pointer_value = list;
			uvm::lua::lib::set_lua_state_value(L, LUA_STORAGE_CHANGELIST_KEY, value_to_store, LUA_STATE_VALUE_POINTER);
		}
		UvmStorageChangeItem change_item;
		change_item.before = value;
		change_item.after = value;
		change_item.contract_id = contract_id;
		change_item.key = key;
		list->push_back(change_item);

		return value;
	}
	for (auto it = list->rbegin(); it != list->rend(); ++it)
	{
		if (it->contract_id == std::string(contract_id) && it->key == key)
			return it->after;
	}
	auto value = global_uvm_chain_api->get_storage_value_from_uvm_by_address(L, contract_id, key);
	post_when_read_table(value);
	return value;
}

static std::string get_contract_id_string_in_storage_Evidence(lua_State *L)
{
	return uvm::lua::lib::get_current_using_contract_id(L);
}

static std::string global_key_for_storage_prop(std::string contract_id, std::string key)
{
	return "gk_" + contract_id + "__" + key;
}

bool lua_push_storage_value(lua_State *L, const UvmStorageValue &value);
#define max_support_array_size 10000000  // max array size supported

static bool lua_push_storage_table_value(lua_State *L, UvmTableMap *map, int type)
{
	if (nullptr == L || nullptr == map)
		return false;
	lua_createtable(L, 0, 0);
	// when is array, push as array
	if (lua_storage_is_array((uvm::blockchain::StorageValueTypes) type))
	{
		// sort the unordered_map, then push items keys, 1,2,3,... one by one into the new table array
		auto count = 0;
		while (count < max_support_array_size)
		{
			++count;
			std::string key = std::to_string(count);
			if (map->find(key) == map->end())
				break;
			auto value = map->at(key);
			lua_push_storage_value(L, value);
			lua_seti(L, -2, count);
		}
	}
	else
	{
		for (auto it = map->begin(); it != map->end(); ++it)
		{
			const auto &key = it->first;
			UvmStorageValue value = it->second;
			lua_push_storage_value(L, value);
			lua_setfield(L, -2, key.c_str());
		}
	}
	return true;
}
bool lua_push_storage_value(lua_State *L, const UvmStorageValue &value)
{
	if (nullptr == L)
		return false;
	switch (value.type)
	{
	case uvm::blockchain::StorageValueTypes::storage_value_int: lua_pushinteger(L, value.value.int_value); break;
	case uvm::blockchain::StorageValueTypes::storage_value_bool: lua_pushboolean(L, value.value.bool_value); break;
	case uvm::blockchain::StorageValueTypes::storage_value_number: lua_pushnumber(L, value.value.number_value); break;
	case uvm::blockchain::StorageValueTypes::storage_value_null: lua_pushnil(L); break;
	case uvm::blockchain::StorageValueTypes::storage_value_string: lua_pushstring(L, value.value.string_value); break;
	case uvm::blockchain::StorageValueTypes::storage_value_stream: {
		auto stream = (uvm::lua::lib::UvmByteStream*) value.value.userdata_value;
		lua_pushlightuserdata(L, (void*)stream);
		luaL_getmetatable(L, "UvmByteStream_metatable");
		lua_setmetatable(L, -2);
	} break;
	default: {
		if (uvm::blockchain::is_any_table_storage_value_type(value.type)
			|| uvm::blockchain::is_any_array_storage_value_type(value.type))
		{
			lua_push_storage_table_value(L, value.value.table_value, value.type);
			break;
		}
		lua_pushnil(L);
	}
	}
	return true;
}

static UvmStorageChangeItem diff_storage_change_if_is_table(lua_State *L, UvmStorageChangeItem change_item)
{
	if (!lua_storage_is_table(change_item.after.type))
		return change_item;
	if (!lua_storage_is_table(change_item.before.type) || !lua_storage_is_table(change_item.after.type))
		return change_item;
	auto new_before = (UvmTableMapP)malloc(sizeof(UvmTableMap));
	new (new_before)UvmTableMap();
	auto new_after = (UvmTableMapP)malloc(sizeof(UvmTableMap));
	new (new_after)UvmTableMap();
	for (auto it1 = change_item.before.value.table_value->begin(); it1 != change_item.before.value.table_value->end(); ++it1)
	{
		auto found = change_item.after.value.table_value->find(it1->first);
		if (found == change_item.after.value.table_value->end())
		{
			new_before->insert(new_before->end(), std::make_pair(it1->first, it1->second));
			continue;
		}
		if (found->second.equals(it1->second))
		{
			continue;
		}
		if (it1->second.type == uvm::blockchain::StorageValueTypes::storage_value_null)
			continue;
		new_before->insert(new_before->end(), std::make_pair(it1->first, it1->second));
		new_after->insert(new_after->end(), std::make_pair(found->first, found->second));
	}
	for (auto it1 = change_item.after.value.table_value->begin(); it1 != change_item.after.value.table_value->end(); ++it1)
	{
		auto found = change_item.before.value.table_value->find(it1->first);
		if (found == change_item.before.value.table_value->end())
		{
			new_after->insert(new_after->end(), std::make_pair(it1->first, it1->second));
		}
	}
	change_item.before.value.table_value = new_before;
	change_item.after.value.table_value = new_after;
	return change_item;
}
static bool has_property_changed_in_changelist(UvmStorageChangeList *list, std::string contract_id, std::string name)
{
	if (nullptr == list)
		return false;
	for (auto it = list->begin(); it != list->end(); ++it)
	{
		auto item = *it;
		if (item.contract_id == contract_id && item.key == name)
			return true;
	}
	return false;
}
bool luaL_commit_storage_changes(lua_State *L)
{
	UvmStateValueNode storage_changelist_node = uvm::lua::lib::get_lua_state_value_node(L, LUA_STORAGE_CHANGELIST_KEY);
	if (global_uvm_chain_api->has_exception(L))
	{
		if (storage_changelist_node.type == LUA_STATE_VALUE_POINTER && nullptr != storage_changelist_node.value.pointer_value)
		{
			UvmStorageChangeList *list = (UvmStorageChangeList*)storage_changelist_node.value.pointer_value;
			list->clear();
		}
		return false;
	}
	// merge changes
	std::unordered_map<std::string, std::shared_ptr<std::unordered_map<std::string, UvmStorageChangeItem>>> changes;
	UvmStorageTableReadList *table_read_list = get_or_init_storage_table_read_list(L);
	if (storage_changelist_node.type != LUA_STATE_VALUE_POINTER && table_read_list)
	{
		storage_changelist_node.type = LUA_STATE_VALUE_POINTER;
		auto *list = (UvmStorageChangeList*)malloc(sizeof(UvmStorageChangeList));
		new (list)UvmStorageChangeList();
		UvmStateValue value_to_store;
		value_to_store.pointer_value = list;
		uvm::lua::lib::set_lua_state_value(L, LUA_STORAGE_CHANGELIST_KEY, value_to_store, LUA_STATE_VALUE_POINTER);
		storage_changelist_node.value.pointer_value = list;
	}
	if (storage_changelist_node.type == LUA_STATE_VALUE_POINTER && nullptr != storage_changelist_node.value.pointer_value)
	{
		UvmStorageChangeList *list = (UvmStorageChangeList*)storage_changelist_node.value.pointer_value;
		// merge initial tables here
		if (table_read_list)
		{
			for (auto it = table_read_list->begin(); it != table_read_list->end(); ++it)
			{
				auto change_item = *it;
				std::string global_skey = global_key_for_storage_prop(change_item.contract_id, change_item.key);
				lua_getglobal(L, global_skey.c_str());
				if (lua_istable(L, -1))
				{
					auto after_value = lua_type_to_storage_value_type(L, -1, 0);
					// check whether changelist has this property's change item. only read value if not exist
					change_item.after = after_value;
					// FIXME: eg. a= {}, storage.a = a, a['name'] = 123, storage.a = {}   How to deal with the above circumstances?  maybe it will help to treat the storage as a table
					//if (!has_property_changed_in_changelist(list, change_item.contract_id, change_item.key))
					// {
					if (!change_item.before.equals(change_item.after))
					{
						list->push_back(change_item);
					}
					// }
				}
				lua_pop(L, 1);
			}
			table_read_list->clear();
		}
		for (auto it = list->begin(); it != list->end(); ++it)
		{
			UvmStorageChangeItem change_item = *it;
			auto found = changes.find(change_item.contract_id);
			if (found != changes.end())
			{
				auto contract_changes = found->second;
				auto found_key = contract_changes->find(change_item.key);
				if (found_key != contract_changes->end())
				{
					found_key->second.after = change_item.after;
				}
				else
				{
					contract_changes->insert(std::make_pair(change_item.key, change_item));
				}
			}
			else
			{
				auto contract_changes = std::make_shared<std::unordered_map<std::string, UvmStorageChangeItem>>();
				contract_changes->insert(contract_changes->end(), std::make_pair(change_item.key, change_item));
				changes.insert(changes.end(), std::make_pair(change_item.contract_id, contract_changes));
			}
		}
	}
	else
	{
		return false;
	}
	if (uvm::lua::lib::is_calling_contract_init_api(L)
		&& changes.size() == 0)
	{
		auto starting_contract_address = uvm::lua::lib::get_starting_contract_address(L);
		auto stream = global_uvm_chain_api->open_contract_by_address(L, starting_contract_address.c_str());
		if (stream && stream->contract_storage_properties.size() > 0)
		{
			global_uvm_chain_api->throw_exception(L, UVM_API_SIMPLE_ERROR, "some storage of this contract not init");
			return false;
		}
	}
	for (auto it = changes.begin(); it != changes.end(); ++it)
	{
		auto stream = global_uvm_chain_api->open_contract_by_address(L, it->first.c_str());
		if (!stream)
		{
			global_uvm_chain_api->throw_exception(L, UVM_API_SIMPLE_ERROR, "Can't get contract info by contract address %s", it->first.c_str());
			return false;
		}
		bool is_in_starting_contract_init = false;
		if (uvm::lua::lib::is_calling_contract_init_api(L))
		{
			auto starting_contract_address = uvm::lua::lib::get_starting_contract_address(L);
			if (it->first == starting_contract_address)
			{
				is_in_starting_contract_init = true;
				const auto &storage_properties_in_chain = stream->contract_storage_properties;
				if (it->second->size() != storage_properties_in_chain.size())
				{
					global_uvm_chain_api->throw_exception(L, UVM_API_SIMPLE_ERROR, "some storage of this contract not init");
					return false;
				}
				for (auto &p1 : *(it->second))
				{
					if (storage_properties_in_chain.find(p1.first) == storage_properties_in_chain.end())
					{
						global_uvm_chain_api->throw_exception(L, UVM_API_SIMPLE_ERROR, "Can't find storage %s", p1.first.c_str());
						return false;
					}
					auto storage_info_in_chain = storage_properties_in_chain.at(p1.first);
					if (uvm::blockchain::is_any_table_storage_value_type(p1.second.after.type)
						|| uvm::blockchain::is_any_array_storage_value_type(p1.second.after.type))
					{
						// [] will show as {} in runtime
						if (!uvm::blockchain::is_any_table_storage_value_type(storage_info_in_chain)
							&& !uvm::blockchain::is_any_array_storage_value_type(storage_info_in_chain))
						{
							global_uvm_chain_api->throw_exception(L, UVM_API_SIMPLE_ERROR, "storage %s type not matched in chain", p1.first.c_str());
							return false;
						}
						if (p1.second.after.value.table_value->size()>0)
						{
							for (auto &item_in_table : *(p1.second.after.value.table_value))
							{
								item_in_table.second.try_parse_type(uvm::blockchain::get_storage_base_type(storage_info_in_chain));
							}
							auto item_after = p1.second.after.value.table_value->begin()->second;
							if (item_after.type != uvm::blockchain::get_item_type_in_table_or_array(storage_info_in_chain))
							{
								global_uvm_chain_api->throw_exception(L, UVM_API_SIMPLE_ERROR, "storage %s type not matched in chain", p1.first.c_str());
								return false;
							}
						}
						if (p1.second.after.type == uvm::blockchain::storage_value_unknown_table
							|| p1.second.after.type == uvm::blockchain::storage_value_unknown_array)
						{
							p1.second.after.type = storage_info_in_chain;
						}
					}
					else if (p1.second.after.type == uvm::blockchain::StorageValueTypes::storage_value_number
						&& storage_info_in_chain == uvm::blockchain::StorageValueTypes::storage_value_int)
					{
						p1.second.after.type = uvm::blockchain::StorageValueTypes::storage_value_int;
						p1.second.after.value.int_value = (lua_Integer)p1.second.after.value.number_value;
					}
					else if (p1.second.after.type == uvm::blockchain::StorageValueTypes::storage_value_int
						&& storage_info_in_chain == uvm::blockchain::StorageValueTypes::storage_value_number)
					{
						p1.second.after.type = uvm::blockchain::StorageValueTypes::storage_value_number;
						p1.second.after.value.number_value = (lua_Number)p1.second.after.value.int_value;
					}
				}
			}
		}
		auto it2 = it->second->begin();
		while (it2 != it->second->end())
		{
			if (lua_storage_is_table(it2->second.after.type))
			{
				// when before is empty table, and after is array
				// when before is array, and after is empty table
				if (lua_storage_is_array(it2->second.before.type) && it2->second.after.value.table_value->size() == 0)
					it2->second.after.type = it2->second.before.type;
				else if (lua_storage_is_table(it2->second.before.type) && it2->second.before.value.table_value->size()>0)
					it2->second.after.type = it2->second.before.type;
				// just save table diff
				it2->second = diff_storage_change_if_is_table(L, it2->second);
			}
			// check storage changes and the corresponding types of compile-time contracts, and modify the type of commit
			if (!is_in_starting_contract_init)
			{
				const auto &storage_properties_in_chain = stream->contract_storage_properties;
				if (it2->second.before.type != uvm::blockchain::StorageValueTypes::storage_value_null
					&& storage_properties_in_chain.find(it2->first) != storage_properties_in_chain.end())
				{
					auto storage_info_in_chain = storage_properties_in_chain.at(it2->first);
					if (uvm::blockchain::is_any_table_storage_value_type(it2->second.after.type)
						|| uvm::blockchain::is_any_array_storage_value_type(it2->second.after.type))
					{
						// [] showed as {} in runtime
						if (!uvm::blockchain::is_any_table_storage_value_type(storage_info_in_chain)
							&& !uvm::blockchain::is_any_array_storage_value_type(storage_info_in_chain))
						{
							global_uvm_chain_api->throw_exception(L, UVM_API_SIMPLE_ERROR, "storage %s type not matched in chain", it2->first.c_str());
							return false;
						}
						if (it2->second.after.value.table_value->size() > 0)
						{
							for (auto &item_in_table : *(it2->second.after.value.table_value))
							{
								item_in_table.second.try_parse_type(uvm::blockchain::get_storage_base_type(storage_info_in_chain));
							}
							auto item_after = it2->second.after.value.table_value->begin()->second;
							if (item_after.type != uvm::blockchain::get_item_type_in_table_or_array(storage_info_in_chain))
							{
								global_uvm_chain_api->throw_exception(L, UVM_API_SIMPLE_ERROR, "storage %s type not matched in chain", it2->first.c_str());
								return false;
							}
						}
						// check match of after's value type and type in chain
						if (it2->second.after.type == uvm::blockchain::storage_value_unknown_table
							|| it2->second.after.type == uvm::blockchain::storage_value_unknown_array)
						{
							it2->second.after.type = storage_info_in_chain;
						}
					}
					else if (it2->second.after.type == uvm::blockchain::StorageValueTypes::storage_value_number
						&& storage_info_in_chain == uvm::blockchain::StorageValueTypes::storage_value_int)
					{
						it2->second.after.type = uvm::blockchain::StorageValueTypes::storage_value_int;
						it2->second.after.value.int_value = (lua_Integer)it2->second.after.value.number_value;
					}
					else if (it2->second.after.type == uvm::blockchain::StorageValueTypes::storage_value_int
						&& storage_info_in_chain == uvm::blockchain::StorageValueTypes::storage_value_number)
					{
						it2->second.after.type = uvm::blockchain::StorageValueTypes::storage_value_number;
						it2->second.after.value.number_value = (lua_Number)it2->second.after.value.int_value;
					}
				}
			}
			// map/array's sub item values' types must be consistent, and are primitive types
			if (lua_storage_is_table(it2->second.after.type))
			{
				uvm::blockchain::StorageValueTypes item_value_type;
				bool is_first = true;
				for (const auto &p : *it2->second.after.value.table_value)
				{
					if (is_first)
					{
						item_value_type = p.second.type;
						continue;
					}
					is_first = true;
					if (!UvmStorageValue::is_same_base_type_with_type_parse(p.second.type, item_value_type))
					{
						global_uvm_chain_api->throw_exception(L, UVM_API_SIMPLE_ERROR,
							"array/map's value type must be same in contract storage");
						return false;
					}
				}
			}
			if (it2->second.after.type == it2->second.before.type)
			{
				if (it2->second.after.type == uvm::blockchain::StorageValueTypes::storage_value_int
					&& it2->second.after.value.int_value == it2->second.before.value.int_value)
				{
					it2 = it->second->erase(it2);
					continue;
				}
				else if (it2->second.after.type == uvm::blockchain::StorageValueTypes::storage_value_bool
					&& it2->second.after.value.bool_value == it2->second.before.value.bool_value)
				{
					it2 = it->second->erase(it2);
					continue;
				}
				else if (it2->second.after.type == uvm::blockchain::StorageValueTypes::storage_value_number
					&& abs(it2->second.after.value.number_value - it2->second.before.value.number_value) < 0.0000001)
				{
					it2 = it->second->erase(it2);
					continue;
				}
				else if (it2->second.after.type == uvm::blockchain::StorageValueTypes::storage_value_string
					&& strcmp(it2->second.after.value.string_value, it2->second.before.value.string_value) == 0)
				{
					it2 = it->second->erase(it2);
					continue;
				}
				else if (it2->second.after.type == uvm::blockchain::StorageValueTypes::storage_value_stream
					&& ((uvm::lua::lib::UvmByteStream*) it2->second.after.value.userdata_value)->equals((uvm::lua::lib::UvmByteStream*) it2->second.before.value.userdata_value))
				{
					it2 = it->second->erase(it2);
					continue;
				}
				else if (!lua_storage_is_table(it2->second.after.type)
					&& it2->second.after.type != uvm::blockchain::StorageValueTypes::storage_value_string
					&& memcmp(&it2->second.after.value, &it2->second.before.value, sizeof(UvmStorageValueUnion)) == 0)
				{
					it2 = it->second->erase(it2);
					continue;
				}
				else if (lua_storage_is_table(it2->second.after.type))
				{
					if ((it2->second.after.value.table_value->size() == 0
						&& it2->second.before.value.table_value->size() == 0))
					{
						it2 = it->second->erase(it2);
						continue;
					}
				}
			}
			++it2;
		}
	}
	// commit changes to uvm
	if (uvm::lua::lib::check_in_lua_sandbox(L))
	{
		printf("commit storage changes in sandbox\n");
		return false;
	}
	auto result = global_uvm_chain_api->commit_storage_changes_to_uvm(L, changes);
	if (storage_changelist_node.type == LUA_STATE_VALUE_POINTER && nullptr != storage_changelist_node.value.pointer_value)
	{
		UvmStorageChangeList *list = (UvmStorageChangeList*)storage_changelist_node.value.pointer_value;
		list->clear();
	}
	return result;
}


namespace uvm {
	namespace lib {

		int uvmlib_get_storage_impl(lua_State *L,
			const char *contract_id, const char *name)
		{
			uvm::lua::lib::increment_lvm_instructions_executed_count(L, CHAIN_GLUA_API_EACH_INSTRUCTIONS_COUNT - 1);

			const auto &code_contract_id = get_contract_id_string_in_storage_Evidence(L);
			if (code_contract_id != contract_id)
			{
				global_uvm_chain_api->throw_exception(L, UVM_API_SIMPLE_ERROR, "contract can only access its own storage directly");
				uvm::lua::lib::notify_lua_state_stop(L);
				L->force_stopping = true;
				return 0;
			}
			const auto &global_key = global_key_for_storage_prop(contract_id, name);
			lua_getglobal(L, global_key.c_str());
			if (lua_istable(L, -1))
			{
				// auto value = lua_type_to_storage_value_type(L, -1, 0);
				return 1;
			}
			lua_pop(L, 1);
			const auto &state_value_node = uvm::lua::lib::get_lua_state_value_node(L, LUA_STORAGE_CHANGELIST_KEY);
			int result;
			if (state_value_node.type != LUA_STATE_VALUE_POINTER || !state_value_node.value.pointer_value)
			{
				const auto &value = get_last_storage_changed_value(L, contract_id, nullptr, std::string(name));
				lua_push_storage_value(L, value);
				if (lua_storage_is_table(value.type))
				{
					lua_pushvalue(L, -1);
					lua_setglobal(L, global_key.c_str());
					// uvm::lua::lib::add_maybe_storage_changed_contract_id(L, contract_id);
				}
				result = 1;
			}
			else if (uvm::lua::lib::check_in_lua_sandbox(L))
			{
				printf("get storage in sandbox\n");
				lua_pushnil(L);
				result = 1;
			}
			else
			{
				UvmStorageChangeList *list = (UvmStorageChangeList*)state_value_node.value.pointer_value;
				const auto &value = get_last_storage_changed_value(L, contract_id, list, std::string(name));
				lua_push_storage_value(L, value);
				if (lua_storage_is_table(value.type))
				{
					lua_pushvalue(L, -1);
					lua_setglobal(L, global_key_for_storage_prop(contract_id, name).c_str());
				}
				result = 1;
			}
			return result;
		}

		int uvmlib_set_storage_impl(lua_State *L,
			const char *contract_id, const char *name, int value_index)
		{
			const auto &code_contract_id = get_contract_id_string_in_storage_Evidence(L);
			if (code_contract_id != contract_id && code_contract_id != contract_id)
			{
				global_uvm_chain_api->throw_exception(L, UVM_API_SIMPLE_ERROR, "contract can only access its own storage directly");
				uvm::lua::lib::notify_lua_state_stop(L);
				L->force_stopping = true;
				return 0;
			}
			if (!name || strlen(name) < 1)
			{
				global_uvm_chain_api->throw_exception(L, UVM_API_SIMPLE_ERROR, "second argument of set_storage must be name");
				return 0;
			}

			// uvm::lua::lib::add_maybe_storage_changed_contract_id(L, contract_id);

			// FIXME: If this is a table, each time you create a new object, take up too much memory, and read too slow
			// FIXME: When considering the commit to read storage changes, do not change every time
			const auto &arg2 = lua_type_to_storage_value_type(L, value_index, 0);

			if (lua_istable(L, value_index))
			{
				// add it to read_list if it's table, because it will be changed
				lua_pushvalue(L, value_index);
				lua_setglobal(L, global_key_for_storage_prop(contract_id, name).c_str());
				auto *table_read_list = get_or_init_storage_table_read_list(L);
				if (table_read_list)
				{
					bool found = false;
					for (auto it = table_read_list->begin(); it != table_read_list->end(); ++it)
					{
						if (it->contract_id == std::string(contract_id) && it->key == name)
						{
							found = true;
							break;
						}
					}
					if (!found)
					{
						UvmStorageChangeItem change_item;
						change_item.contract_id = contract_id;
						change_item.key = name;
						change_item.before = arg2;
						change_item.after = arg2;
						// merge change history to release too many not-used-again objects
						table_read_list->push_back(change_item);
					}
				}
			}
			/*
			if (arg2.type >= LVALUE_NOT_SUPPORT)
			{
			global_uvm_chain_api->throw_exception(L, UVM_API_SIMPLE_ERROR, "third argument of set_storage must be value");
			return 0;
			}
			*/

			// log the value before and the new value
			UvmStateValueNode state_value_node = uvm::lua::lib::get_lua_state_value_node(L, LUA_STORAGE_CHANGELIST_KEY);
			UvmStorageChangeList *list;
			if (state_value_node.type != LUA_STATE_VALUE_POINTER || nullptr == state_value_node.value.pointer_value)
			{
				list = (UvmStorageChangeList*)malloc(sizeof(UvmStorageChangeList));
				new (list)UvmStorageChangeList();
				UvmStateValue value_to_store;
				value_to_store.pointer_value = list;
				uvm::lua::lib::set_lua_state_value(L, LUA_STORAGE_CHANGELIST_KEY, value_to_store, LUA_STATE_VALUE_POINTER);
			}
			else
			{
				list = (UvmStorageChangeList*)state_value_node.value.pointer_value;
			}
			if (uvm::lua::lib::check_in_lua_sandbox(L))
			{
				printf("set storage in sandbox\n");
				return 0;
			}
			std::string name_str(name);
			auto before = get_last_storage_changed_value(L, contract_id, list, name_str);
			auto after = arg2;
			if (after.type == uvm::blockchain::StorageValueTypes::storage_value_null)
			{
				global_uvm_chain_api->throw_exception(L, UVM_API_SIMPLE_ERROR, (name_str + "storage can't change to nil").c_str());
				uvm::lua::lib::notify_lua_state_stop(L);
				return 0;
			}
			if (before.type != uvm::blockchain::StorageValueTypes::storage_value_null
				&& (before.type != after.type && !lua_storage_is_table(before.type)))
			{
				global_uvm_chain_api->throw_exception(L, UVM_API_SIMPLE_ERROR, (std::string(name) + "storage can't change type").c_str());
				uvm::lua::lib::notify_lua_state_stop(L);
				return 0;
			}

			// can't create new storage index outside init
			if (!uvm::lua::lib::is_calling_contract_init_api(L)
				&& before.type == uvm::blockchain::StorageValueTypes::storage_value_null)
			{
				// when not in init api
				global_uvm_chain_api->throw_exception(L, UVM_API_SIMPLE_ERROR, (std::string(name) + "storage can't register storage after inited").c_str());
				uvm::lua::lib::notify_lua_state_stop(L);
				return 0;
			}

			// disable nested map
			if (lua_storage_is_table(after.type))
			{
				auto inner_table = after.value.table_value;
				if (nullptr != inner_table)
				{
					for (auto it = inner_table->begin(); it != inner_table->end(); ++it)
					{
						if (lua_storage_is_table(it->second.type))
						{
							global_uvm_chain_api->throw_exception(L, UVM_API_SIMPLE_ERROR, "storage not support nested map");
							uvm::lua::lib::notify_lua_state_stop(L);
							return 0;
						}
					}
				}
			}

			if (lua_storage_is_table(after.type))
			{
				// table properties can't change type except change to nil(in whole history in this lua_State)
				// value type must be same in table in storage
				int table_value_type = -1;
				if (lua_storage_is_table(before.type))
				{
					for (auto it = before.value.table_value->begin(); it != before.value.table_value->end(); ++it)
					{
						auto found = after.value.table_value->find(it->first);
						if (it->second.type != uvm::blockchain::StorageValueTypes::storage_value_null)
						{
							if (table_value_type < 0)
							{
								table_value_type = it->second.type;
							}
							else
							{
								if (table_value_type != it->second.type)
								{
									global_uvm_chain_api->throw_exception(L, UVM_API_SIMPLE_ERROR, "storage table type must be same");
									uvm::lua::lib::notify_lua_state_stop(L);
									return 0;
								}
							}
						}
					}
				}
				for (auto it = after.value.table_value->begin(); it != after.value.table_value->end(); ++it)
				{
					if (it->second.type != uvm::blockchain::StorageValueTypes::storage_value_null)
					{
						if (table_value_type < 0)
						{
							table_value_type = it->second.type;
						}
						else
						{
							if (table_value_type != it->second.type)
							{
								global_uvm_chain_api->throw_exception(L, UVM_API_SIMPLE_ERROR, "storage table type must be same");
								uvm::lua::lib::notify_lua_state_stop(L);
								return 0;
							}
						}
					}
				}
				if ((!lua_storage_is_table(before.type) || before.value.table_value->size() < 1) && after.value.table_value->size() > 0)
				{
					// if before table is empty and after table not empty, search type before
					for (auto it = list->begin(); it != list->end(); ++it)
					{
						if (it->contract_id == std::string(contract_id) && it->key == std::string(name))
						{
							if (lua_storage_is_table(it->after.type) && it->after.value.table_value->size() > 0)
							{
								for (auto it2 = it->after.value.table_value->begin(); it2 != it->after.value.table_value->end(); ++it2)
								{
									if (it2->second.type != uvm::blockchain::StorageValueTypes::storage_value_null)
									{
										if (it2->second.type != table_value_type)
										{
											global_uvm_chain_api->throw_exception(L, UVM_API_SIMPLE_ERROR, "storage table type must be same");
											uvm::lua::lib::notify_lua_state_stop(L);
											return 0;
										}
									}
								}
							}
						}
					}
				}
			}


			UvmStorageChangeItem change_item;
			change_item.key = name;
			change_item.contract_id = contract_id;
			change_item.after = after;
			change_item.before = before;
			// merge change history to release too many not-used-again objects
			list->push_back(change_item);

			return 0;
		}

	}
}
