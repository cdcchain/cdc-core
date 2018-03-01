#pragma  once

#include <consensus/Types.hpp>
#include <consensus/contract/Code.hpp>
#include <consensus/contract/StorageTypes.hpp>
#include <consensus/WithdrawTypes.hpp>
#include <fc/optional.hpp>
#include <string>
#include <vector>
#include <set>
#include <boost/uuid/sha1.hpp>


using namespace cdcchain::consensus;

namespace cdcchain {
    namespace consensus{

		using namespace uvm::blockchain;

        enum ContractApiType
        {
            chain = 1,
            offline = 2,
            event = 3
        };

        enum ContractState
        {
            valid = 1,
            deleted = 2
        };

        enum ContractLevel
        {
            temp = 1,
            forever = 2
        };


        //front declaration for typedef
        class ChainInterface;
        struct  ContractEntry;
        struct ContractStorageEntry;
        //use fc optional to hold the return value
        typedef fc::optional<ContractEntry> oContractEntry;
        typedef fc::optional<ContractStorageEntry> oContractStorage;
        typedef fc::optional<ContractIdType> oContractIdType;


        //contract information
        struct  ContractEntry
        {
            ContractName  contract_name; // contract name
            ContractIdType  id; //contract address
            fc::enum_type<fc::unsigned_int, ContractLevel> level = ContractLevel::temp; //the level of the contract
            PublicKeyType owner; //the owner of the contract
            fc::enum_type<fc::unsigned_int, ContractState> state = ContractState::valid; //contract state
            std::string description; //the description of contract
            uvm::blockchain::Code code; // code-related of contract
            fc::optional<uint64_t>    reserved;
            TransactionIdType trx_id;
			fc::time_point register_time;
            //the address string, contain contract address prefix
            std::string id_to_base58()const;
		

            // database related functions
            static oContractEntry lookup(const ChainInterface&, const ContractIdType&);
            static oContractEntry lookup(const ChainInterface&, const ContractName&);
            static void store(ChainInterface&, const ContractIdType&, const ContractEntry&);
            static void remove(ChainInterface&, const ContractIdType&);

        };

        struct ContractEntryPrintable
        {
            ContractName  contract_name; // contract name
            string  id; //contract address
            fc::enum_type<fc::unsigned_int, ContractLevel> level = ContractLevel::temp; //the level of the contract
            PublicKeyType owner; //the owner of the contract
            Address owner_address;  //the owner address of the contract
            string owner_name;  //the owner name of the contract
            fc::enum_type<fc::unsigned_int, ContractState> state = ContractState::valid; //contract state
            std::string description; //the description of contract
            CodePrintAble code_printable; // code-related of contract
            fc::optional<uint64_t>    reserved;
            TransactionIdType trx_id;

            ContractEntryPrintable(){}

            ContractEntryPrintable(const ContractEntry& entry) : contract_name(entry.contract_name), id(entry.id.AddressToString(AddressType::contract_address)), level(entry.level),
                owner(entry.owner), owner_address(entry.owner), state(entry.state), description(entry.description), code_printable(entry.code), reserved(entry.reserved),
                trx_id(entry.trx_id) {}
        };

        //contract storage
        struct ContractStorageEntry
        {
            //std::vector<ContractChar> contract_storage;
            ContractIdType  id; //contract address
            std::map<std::string, StorageDataType> contract_storages;

            static oContractStorage lookup(const ChainInterface&, const ContractIdType&);
            static void store(ChainInterface&, const ContractIdType&, const ContractStorageEntry&);
            static void remove(ChainInterface&, const ContractIdType&);

        };
		struct  ResultTIdEntry;
		typedef fc::optional<ResultTIdEntry> oResultTIdEntry;
		struct ResultTIdEntry
		{
			TransactionIdType res;
			ResultTIdEntry();
			ResultTIdEntry(const TransactionIdType& id);
			static oResultTIdEntry lookup(const ChainInterface&, const TransactionIdType&);
			static void store(ChainInterface&, const TransactionIdType& , const ResultTIdEntry&);
			static void remove(ChainInterface&, const TransactionIdType&);
		};
		struct RequestIdEntry;
		typedef fc::optional<RequestIdEntry> oRequestIdEntry;
		struct RequestIdEntry
		{
			TransactionIdType req;
			RequestIdEntry();
			RequestIdEntry(const TransactionIdType& id);
			static oRequestIdEntry lookup(const ChainInterface&, const TransactionIdType&);
			static void store(ChainInterface&, const TransactionIdType&, const RequestIdEntry&);
			static void remove(ChainInterface&, const TransactionIdType&);

		};
		struct ContractTrxEntry;
		typedef fc::optional<ContractTrxEntry> oContractTrxEntry;
		struct ContractTrxEntry
		{
			TransactionIdType trx_id;
			ContractTrxEntry();
			ContractTrxEntry(const TransactionIdType& id);
			static oContractTrxEntry lookup(const ChainInterface&, const ContractIdType&);
			static void store(ChainInterface&, const ContractIdType&,const ContractTrxEntry&);
			static void remove(ChainInterface&, const ContractIdType&);
		};
		struct ContractinTrxEntry;
		typedef fc::optional<ContractinTrxEntry> oContractinTrxEntry;
		struct ContractinTrxEntry
		{
			ContractIdType contract_id;
			ContractinTrxEntry();
			ContractinTrxEntry(const ContractIdType& id);
			static oContractinTrxEntry lookup(const ChainInterface&, const TransactionIdType&);
			static void store(ChainInterface&, const TransactionIdType&, const ContractinTrxEntry&);
			static void remove(ChainInterface&, const TransactionIdType&);
		};

		struct ContractTemplateEntry;
		typedef fc::optional<ContractTemplateEntry> oContractTemplateEntry;
		struct ContractTemplateEntry
		{
			uvm::blockchain::Code code;
			PublicKeyType delegate_pubkey;
			ContractTemplateEntry();
			static oContractTemplateEntry lookup(const ChainInterface&, const std::string&);
			static void store(ChainInterface&, const std::string&, const ContractTemplateEntry&);
			static void remove(ChainInterface&, const std::string&);
		};

        class ContractDbInterface
        {

            friend struct ContractEntry;
            friend struct ContractStorageEntry;
			friend struct ResultTIdEntry;
			friend struct RequestIdEntry;
			friend struct ContractinTrxEntry;
			friend struct ContractTrxEntry;
			friend struct ContractTemplateEntry;
            //lookup related
            virtual  oContractEntry  contract_lookup_by_id(const ContractIdType&)const = 0;
            virtual  oContractEntry  contract_lookup_by_name(const ContractName&)const = 0;
            virtual oContractStorage contractstorage_lookup_by_id(const ContractIdType&)const = 0;
			virtual oResultTIdEntry contract_lookup_resultid_by_reqestid(const TransactionIdType&)const = 0;
			virtual oRequestIdEntry contract_lookup_requestid_by_resultid(const TransactionIdType&)const = 0;
			virtual oContractinTrxEntry contract_lookup_contractid_by_trxid(const TransactionIdType&)const = 0;
			virtual oContractTrxEntry contract_lookup_trxid_by_contract_id(const ContractIdType&)const = 0;
			virtual oContractTemplateEntry contracttemplate_lookup_by_hash(const std::string&)const = 0;

			//insert related
            virtual void contract_insert_into_id_map(const ContractIdType&, const ContractEntry&) = 0;
            virtual void contract_insert_into_name_map(const ContractName&, const ContractIdType&) = 0;
            virtual void contractstorage_insert_into_id_map(const ContractIdType&, const ContractStorageEntry&) = 0;
			virtual void contract_store_resultid_by_reqestid(const TransactionIdType& req, const ResultTIdEntry& res) = 0;
			virtual void contract_store_requestid_by_resultid(const TransactionIdType& req, const RequestIdEntry& res) = 0;
			virtual void contract_store_contractid_by_trxid(const TransactionIdType& id, const ContractinTrxEntry& res) = 0;
			virtual void contract_store_trxid_by_contractid(const ContractIdType& id, const ContractTrxEntry & res) = 0;
			virtual void contracttemplate_insert_into_hash_map(const std::string&, const ContractTemplateEntry&) = 0;
			//erase related
            virtual void contract_erase_from_id_map(const ContractIdType&) = 0;
            virtual void contract_erase_from_name_map(const ContractName&) = 0;
            virtual void contractstorage_erase_from_id_map(const ContractIdType&) = 0;
			virtual void contract_erase_resultid_by_reqestid(const TransactionIdType& req) = 0;
			virtual void contract_erase_requestid_by_resultid(const TransactionIdType& req) = 0;
			virtual void contract_erase_trxid_by_contract_id(const ContractIdType&) = 0;
			virtual void contract_erase_contractid_by_trxid(const TransactionIdType& req) = 0;
			virtual void contracttemplate_erase_from_hash_map(const std::string&) = 0;

        };
    }
}

FC_REFLECT_ENUM(cdcchain::consensus::ContractApiType,
    (chain)
    (offline)
    (event)
    )

    FC_REFLECT_ENUM(cdcchain::consensus::ContractState,
    (valid)
    (deleted)
    )

    FC_REFLECT_ENUM(cdcchain::consensus::ContractLevel,
    (temp)
    (forever)
    )

    FC_REFLECT(cdcchain::consensus::ContractEntry,
    (contract_name)
    (id)
    (level)
    (owner)
    (state)
    (description)
    (code)
    (reserved)
    (trx_id)
    )

    FC_REFLECT(cdcchain::consensus::ContractEntryPrintable,
    (contract_name)
    (id)
    (level)
    (owner)
    (owner_address)
    (owner_name)
    (state)
    (description)
    (code_printable)
    (reserved)
    (trx_id)
    )

    FC_REFLECT(cdcchain::consensus::ContractStorageEntry, (id)(contract_storages))
	FC_REFLECT(cdcchain::consensus::ResultTIdEntry, (res))
	FC_REFLECT(cdcchain::consensus::RequestIdEntry, (req))
	FC_REFLECT(cdcchain::consensus::ContractTrxEntry, (trx_id))
	FC_REFLECT(cdcchain::consensus::ContractinTrxEntry, (contract_id))
	FC_REFLECT(cdcchain::consensus::ContractTemplateEntry, (code)(delegate_pubkey))
	
