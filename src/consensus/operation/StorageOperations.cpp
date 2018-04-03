// Copyright (c) 2017-2018 The CDC developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.


#include <consensus/operation/StorageOperations.hpp>
#include <consensus/transaction/TransactionEvaluationState.hpp>
#include <consensus/Exceptions.hpp>
#include <consensus/chainstate/ChainInterface.hpp>

namespace cdcchain {
    namespace consensus {

        template<typename StorageBaseType, typename StorageContainerType>
        void StorageOperation::update_contract_map_storage(const StorageDataChangeType& change_storage, StorageDataType& storage)const
        {
            //���������л�
            std::map<std::string, StorageBaseType> storage_table = storage.as<StorageContainerType>().raw_storage_map;
            std::map<std::string, StorageBaseType> storage_before_table = change_storage.storage_before.as<StorageContainerType>().raw_storage_map;
            std::map<std::string, StorageBaseType> storage_after_table = change_storage.storage_after.as<StorageContainerType>().raw_storage_map;

            //ɾ������before map�е�
            auto iter_before = storage_before_table.begin();
            for (; iter_before != storage_before_table.end(); ++iter_before)
                storage_table.erase(iter_before->first);

            //��������after map�е�
            auto iter_after = storage_after_table.begin();
            for (; iter_after != storage_after_table.end(); ++iter_after)
                storage_table[iter_after->first] = iter_after->second;

            //�����л�
            StorageContainerType new_storage;
            new_storage.raw_storage_map = storage_table;
            storage = StorageDataType(new_storage);
        }

        void StorageOperation::update_contract_storages(const std::string storage_name, const StorageDataChangeType& change_storage,
            std::map<std::string, StorageDataType>& contract_storages)const
        {
            if (change_storage.storage_before.storage_type == StorageValueTypes::storage_value_null &&
                change_storage.storage_after.storage_type != StorageValueTypes::storage_value_null)
            {
                StorageDataType storage_data;
                storage_data.storage_type = change_storage.storage_after.storage_type;
                storage_data.storage_data = change_storage.storage_after.storage_data;

                contract_storages.erase(storage_name);
                contract_storages.emplace(make_pair(storage_name, storage_data));
            }
            else if (change_storage.storage_before.storage_type != StorageValueTypes::storage_value_null &&
                change_storage.storage_after.storage_type == StorageValueTypes::storage_value_null)
            {
                contract_storages.erase(storage_name);
            }
            else if (change_storage.storage_before.storage_type != StorageValueTypes::storage_value_null &&
                change_storage.storage_after.storage_type != StorageValueTypes::storage_value_null)
            {
                //����������ֱ���滻
                //map���͵Ļ����������л�, ��������, Ȼ���������л����滻
                auto iter = contract_storages.find(storage_name);
                FC_ASSERT(iter != contract_storages.end(), "can not get storage_name");

                auto storage_type = iter->second.storage_type;

                if (is_any_base_storage_value_type(storage_type))
                    iter->second.storage_data = change_storage.storage_after.storage_data;
                else if (storage_type == StorageValueTypes::storage_value_int_table)
                    update_contract_map_storage<LUA_INTEGER, StorageIntTableType>(change_storage, iter->second);
                else if (storage_type == StorageValueTypes::storage_value_number_table)
                    update_contract_map_storage<double, StorageNumberTableType>(change_storage, iter->second);
                else if (storage_type == StorageValueTypes::storage_value_bool_table)
                    update_contract_map_storage<bool, StorageBoolTableType>(change_storage, iter->second);
                else if (storage_type == StorageValueTypes::storage_value_string_table)
                    update_contract_map_storage<std::string, StorageStringTableType>(change_storage, iter->second);
                else if (storage_type == StorageValueTypes::storage_value_int_array)
                    update_contract_map_storage<LUA_INTEGER, StorageIntArrayType>(change_storage, iter->second);
                else if (storage_type == StorageValueTypes::storage_value_number_array)
                    update_contract_map_storage<double, StorageNumberArrayType>(change_storage, iter->second);
                else if (storage_type == StorageValueTypes::storage_value_bool_array)
                    update_contract_map_storage<bool, StorageBoolArrayType>(change_storage, iter->second);
                else if (storage_type == StorageValueTypes::storage_value_string_array)
                    update_contract_map_storage<std::string, StorageStringArrayType>(change_storage, iter->second);
            }
            else
            {
                contract_storages.erase(storage_name);
            }
        }


        void StorageOperation::evaluate(TransactionEvaluationState& eval_state)const
        {
            try{
                if (!eval_state.evaluate_contract_result)
                    FC_CAPTURE_AND_THROW(not_be_result_of_execute, (type));
                //����contract_id��ȡ���Ϻ�Լstorage
                oContractStorage ocontractstorage = eval_state._current_state->get_contractstorage_entry(this->contract_id);

                std::map<std::string, StorageDataType> contract_storages;
                if (ocontractstorage.valid())
                    contract_storages = ocontractstorage->contract_storages;

                auto iter_change = contract_change_storages.begin();
                auto iter = contract_storages.begin();

                for (; iter_change != contract_change_storages.end(); ++iter_change)
                {
                    //storage_after��storage_before���Ͳ�һ��
                    if (iter_change->second.storage_before.storage_type != StorageValueTypes::storage_value_null 
                        && iter_change->second.storage_after.storage_type != StorageValueTypes::storage_value_null)
                        FC_ASSERT(iter_change->second.storage_before.storage_type == iter_change->second.storage_after.storage_type,
                            "the after storage type is not match the before");

                    //��������contract_storages��contract_before_storages����ͬ��storage name, ���Ͳ�һ��
                    if ((iter = contract_storages.find(iter_change->first)) != contract_storages.end())
                        if (iter->second.storage_type != StorageValueTypes::storage_value_null &&
                            iter_change->second.storage_before.storage_type != StorageValueTypes::storage_value_null)
                            FC_ASSERT(iter->second.storage_type == iter_change->second.storage_before.storage_type,
                                "the type of storage from entry is not match the before");
                }

                iter_change = contract_change_storages.begin();
                for (; iter_change != contract_change_storages.end(); ++iter_change)
                    update_contract_storages(iter_change->first, iter_change->second, contract_storages);

                ContractStorageEntry entry;
                entry.id = this->contract_id;
                entry.contract_storages = contract_storages;

                eval_state._current_state->store_contractstorage_entry(entry);

            } FC_CAPTURE_AND_RETHROW((*this))
        }
    }
}
