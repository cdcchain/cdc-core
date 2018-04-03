// Copyright (c) 2017-2018 The CDC developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.


#include <consensus/contract/ContractEntry.hpp>
#include <consensus/chainstate/ChainInterface.hpp>
#include <consensus/Types.hpp>
#include <consensus/address/Address.hpp>
#include <consensus/Exceptions.hpp>

#include <fc/array.hpp>
#include <fc/crypto/ripemd160.hpp>
#include <fc/crypto/elliptic.hpp>
#include <fc/crypto/base58.hpp>
#include <boost/uuid/sha1.hpp>

#include <utilities/CommonApi.hpp>

using namespace cdcchain::consensus;

namespace cdcchain {
    namespace consensus{

        std::string ContractEntry::id_to_base58()const
        {
            fc::array<char, 24> bin_addr;
            memcpy((char*)&bin_addr, (char*)&(this->id.addr), sizeof(this->id.addr));
            auto checksum = fc::ripemd160::hash((char*)&(this->id.addr), sizeof(this->id.addr));
            memcpy(((char*)&bin_addr) + 20, (char*)&checksum._hash[0], 4);
            return CONTRACT_ADDRESS_PREFIX + fc::to_base58(bin_addr.data, sizeof(bin_addr));
        }

        oContractEntry ContractEntry::lookup(const ChainInterface& db, const ContractIdType& id)
        {
            try
            {
                return db.contract_lookup_by_id(id);

            }FC_CAPTURE_AND_RETHROW((id))

        }

        oContractEntry ContractEntry::lookup(const ChainInterface& db, const ContractName& name)
        {
            try
            {
                return db.contract_lookup_by_name(name);

            }FC_CAPTURE_AND_RETHROW((name))

        }

        void ContractEntry::store(ChainInterface& db, const ContractIdType& id, const ContractEntry& contract)
        {
            try
            {
                db.contract_insert_into_id_map(id, contract);
                 if (db.is_valid_contract_name(contract.contract_name))
                 {
                     db.contractname_insert_into_id_map(contract.contract_name, id);
                 }

            }FC_CAPTURE_AND_RETHROW((id)(contract))
        }

        void ContractEntry::remove(ChainInterface& db, const ContractIdType& id)
        {
            try
            {
                const oContractEntry info = db.lookup<ContractEntry>(id);

                if (info.valid())
                {
                    db.contract_erase_from_id_map(id);
                    db.contractname_erase_from_id_map(info->contract_name);
                }


            }FC_CAPTURE_AND_RETHROW((id))
        }


		oContractIdEntry ContractIdEntry::lookup(const ChainInterface& db, const ContractName& name)
		{
			try
			{
				return db.contractid_lookup_by_name(name);

			}FC_CAPTURE_AND_RETHROW((name))

		}

		void ContractIdEntry::store(ChainInterface& db, const ContractName& name, const ContractIdEntry& entry)
		{
			try
			{
				db.contractname_insert_into_id_map(name, entry);
				
			}FC_CAPTURE_AND_RETHROW((name)(entry))
		}
		void ContractIdEntry::remove(ChainInterface& db, const ContractName& name)
		{
			try
			{
				db.contractname_erase_from_id_map(name);

			}FC_CAPTURE_AND_RETHROW((name))
		}


        oContractStorage ContractStorageEntry::lookup(const ChainInterface& db, const ContractIdType& id)
        {
            try
            {
                return db.contractstorage_lookup_by_id(id);
            }FC_CAPTURE_AND_RETHROW((id))

        }


        void ContractStorageEntry::store(ChainInterface& db, const ContractIdType& id, const ContractStorageEntry& storage)
        {
            try
            {
                db.contractstorage_insert_into_id_map(id, storage);
            }FC_CAPTURE_AND_RETHROW((id)(storage))


        }


        void ContractStorageEntry::remove(ChainInterface& db, const ContractIdType& id)
        {
            try
            {
                const oContractStorage storage = db.lookup<ContractStorageEntry>(id);

                if (storage.valid())
                {
                    db.contractstorage_erase_from_id_map(id);
                }
            }FC_CAPTURE_AND_RETHROW((id))

        }



        ResultTIdEntry::ResultTIdEntry()
        {
        }

        ResultTIdEntry::ResultTIdEntry(const TransactionIdType & id) :res(id)
        {
        }

        oResultTIdEntry ResultTIdEntry::lookup(const ChainInterface &db, const TransactionIdType &req)
        {
            try
            {
                return  db.contract_lookup_resultid_by_reqestid(req);
            }FC_CAPTURE_AND_RETHROW((req))
        }

        void ResultTIdEntry::store(ChainInterface &db, const TransactionIdType &req, const ResultTIdEntry &res)
        {
            try
            {
                db.contract_store_resultid_by_reqestid(req, res);
            }FC_CAPTURE_AND_RETHROW((req))
        }

        void ResultTIdEntry::remove(ChainInterface &db, const TransactionIdType &req)
        {
            try
            {
                db.contract_erase_resultid_by_reqestid(req);
            }FC_CAPTURE_AND_RETHROW((req))
        }

		RequestIdEntry::RequestIdEntry()
		{
		}

		RequestIdEntry::RequestIdEntry(const TransactionIdType & id):req(id)
		{

		}

		oRequestIdEntry RequestIdEntry::lookup(const ChainInterface &db, const TransactionIdType &res)
		{
			try
			{
				return  db.contract_lookup_requestid_by_resultid(res);
			}FC_CAPTURE_AND_RETHROW((res))
		}

		void RequestIdEntry::store(ChainInterface &db, const TransactionIdType &res, const RequestIdEntry &req)
		{
			try
			{
				db.contract_store_requestid_by_resultid(res, req);
			}FC_CAPTURE_AND_RETHROW((res))
		}

		void RequestIdEntry::remove(ChainInterface &db, const TransactionIdType &res)
		{
			try
			{
				db.contract_erase_requestid_by_resultid(res);
			}FC_CAPTURE_AND_RETHROW((res))
		}
		

		ContractTrxEntry::ContractTrxEntry()
		{
		}

		ContractTrxEntry::ContractTrxEntry(const TransactionIdType & id):trx_id(id)
		{
		}

		oContractTrxEntry ContractTrxEntry::lookup(const ChainInterface &db, const ContractIdType &id)
		{
			try
			{
				return db.contract_lookup_trxid_by_contract_id(id);
			}FC_CAPTURE_AND_RETHROW((id));
		}

		void ContractTrxEntry::store(ChainInterface &db, const ContractIdType &id, const ContractTrxEntry &trx_entry)
		{
			try {
				db.contract_store_trxid_by_contractid(id, trx_entry);
			}FC_CAPTURE_AND_RETHROW((id));
		}

		void ContractTrxEntry::remove( ChainInterface &db, const ContractIdType & id)
		{
			try{
				db.contract_erase_trxid_by_contract_id(id);
			}FC_CAPTURE_AND_RETHROW((id));
			
		}

		ContractinTrxEntry::ContractinTrxEntry()
		{
		}

		ContractinTrxEntry::ContractinTrxEntry(const ContractIdType & id):contract_id(id)
		{
		}

		oContractinTrxEntry ContractinTrxEntry::lookup(const ChainInterface &db, const TransactionIdType &id)
		{
			try
			{
				return db.contract_lookup_contractid_by_trxid(id);
			}FC_CAPTURE_AND_RETHROW((id));
		}

		void ContractinTrxEntry::store(ChainInterface &db, const TransactionIdType &id, const ContractinTrxEntry &contract_entry)
		{
			try
			{
				db.contract_store_contractid_by_trxid(id,contract_entry);
			}FC_CAPTURE_AND_RETHROW((id));
		}

		void ContractinTrxEntry::remove(ChainInterface &db, const TransactionIdType &id)
		{
			try
			{
				db.contract_erase_contractid_by_trxid(id);
			}FC_CAPTURE_AND_RETHROW((id));
		}

		ContractTemplateEntry::ContractTemplateEntry()
		{
		}

		oContractTemplateEntry ContractTemplateEntry::lookup(const ChainInterface &db, const std::string& hash)
		{
			try
			{
				return db.contracttemplate_lookup_by_hash(hash);
			}FC_CAPTURE_AND_RETHROW((hash));
		}

		void ContractTemplateEntry::store(ChainInterface &db, const std::string& hash, const ContractTemplateEntry &entry)
		{
			try
			{
				db.contracttemplate_insert_into_hash_map(hash, entry);
			}FC_CAPTURE_AND_RETHROW((hash));
		}

		void ContractTemplateEntry::remove(ChainInterface &db, const std::string& hash)
		{
			try
			{
				db.contracttemplate_erase_from_hash_map(hash);
			}FC_CAPTURE_AND_RETHROW((hash));
		}

}
}
