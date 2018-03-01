#pragma once
#include <consensus/transaction/Transaction.hpp>
#include <consensus/Types.hpp>
#include <consensus/WithdrawTypes.hpp>
namespace cdcchain {
	namespace consensus {
		struct ContractCreatorEntry;
		typedef fc::optional<ContractCreatorEntry> oContractCreatorEntry;

		class ChainInterface;
		struct ContractCreatorEntry {
			string contract_creater;
			Asset fee_collector;
			ContractCreatorEntry(string creater = "", Asset fee = Asset()):contract_creater(creater), fee_collector(fee){
			};
			void sanity_check(const ChainInterface&)const;
			static oContractCreatorEntry lookup(const ChainInterface&, const string&);
			static void store(ChainInterface&, const string, const ContractCreatorEntry&);
			static void remove(ChainInterface&, const string);
		};
		class ContractCreatorDBInterface
		{
			friend struct ContractCreatorEntry;

			virtual oContractCreatorEntry contractcreator_lookup_by_symbol(const string&)const = 0;
			virtual void contractcreator_insert_into_map(const string&,const ContractCreatorEntry&) = 0;
			virtual void contractcreator_erase_from_map(const string&) = 0;
		};
	}
}
FC_REFLECT(cdcchain::consensus::ContractCreatorEntry,(contract_creater)(fee_collector))
