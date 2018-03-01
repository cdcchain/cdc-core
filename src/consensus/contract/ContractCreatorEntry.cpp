#include <consensus/contract/ContractCreatorEntry.hpp>
#include <consensus/chainstate/ChainInterface.hpp>
namespace cdcchain {
	namespace consensus {
		void ContractCreatorEntry::sanity_check(const ChainInterface& db)const {
			try {
				FC_ASSERT(!contract_creater.empty(), "Invalid contract creator");
				FC_ASSERT(fee_collector.amount >= 0,"Invalid contract fee");
				FC_ASSERT(fee_collector.asset_id == Asset().asset_id, "Asset id error");
			} FC_CAPTURE_AND_RETHROW((*this))
		}
		oContractCreatorEntry ContractCreatorEntry::lookup(const ChainInterface& db, const string& creater) {
			try {
				return db.contractcreator_lookup_by_symbol(creater);
			}FC_CAPTURE_AND_RETHROW((creater))
			
		}
		void ContractCreatorEntry::store(ChainInterface& db, const string creator, const ContractCreatorEntry& fee) {
			try {
				db.contractcreator_insert_into_map(creator, fee);
			}FC_CAPTURE_AND_RETHROW((creator))
		}
		void ContractCreatorEntry::remove(ChainInterface& db, const string creator) {
			try {
				db.contractcreator_erase_from_map(creator);
			}FC_CAPTURE_AND_RETHROW((creator))
		}
	}
}