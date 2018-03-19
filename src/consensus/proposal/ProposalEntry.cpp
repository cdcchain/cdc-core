#include <consensus/chainstate/ChainInterface.hpp>
#include <consensus/proposal/ProposalEntry.hpp>

namespace cdcchain {
	namespace consensus {

		const ProposalTypeEnum ApplyForPrivilegeAdmin::type = apply_for_privilege_admin;

		ProposalEntry::ProposalEntry()
		{
		}

		ProposalEntry::ProposalEntry(const ProposalIdType& id):proposal_id(id)
		{
		}

		oProposalEntry ProposalEntry::lookup(const ChainInterface& db, const ProposalIdType& id)
		{
			try
			{
				return db.proposal_lookup_by_id(id);
			}FC_CAPTURE_AND_RETHROW((id))
		}

		void ProposalEntry::store(ChainInterface& db, const ProposalIdType& id, const ProposalEntry& entry)
		{
			try
			{
				db.proposal_insert_into_id_map(id, entry);
			}FC_CAPTURE_AND_RETHROW((id)(entry))
		}

		void ProposalEntry::remove(ChainInterface& db, const ProposalIdType& id)
		{
			try
			{
				const oProposalEntry entry = db.lookup<ProposalEntry>(id);

				if (entry.valid())
				{
					db.proposal_erase_from_id_map(id);
				}
			}FC_CAPTURE_AND_RETHROW((id))
		}

	}
}
