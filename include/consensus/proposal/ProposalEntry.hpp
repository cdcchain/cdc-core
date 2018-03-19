#pragma once

#include <consensus/Types.hpp>

namespace cdcchain {
	namespace consensus {

		enum ProposalTypeEnum {
			apply_for_privilege_admin = 1,
			revoke_privilege_admin = 2
		};

		//front declaration for typedef
		class ChainInterface;

		struct ProposalCondition {
			fc::enum_type<fc::unsigned_int, ProposalTypeEnum> proposal_type;
			std::vector<char> proposal_data;

			ProposalCondition(){}

			ProposalCondition(const ProposalCondition& cond) : proposal_type(cond.proposal_type),
				proposal_data(cond.proposal_data){}

			template<typename ProposalType>
			ProposalCondition(const ProposalType& t)
			{
				proposal_type = ProposalType::type;
				proposal_data = fc::raw::pack(t);
			}

			template<typename ProposalType>
			ProposalType as()const
			{
				FC_ASSERT(type == ProposalType::type, "", ("proposal_type", type)("ProposalType", ProposalType::type));
				return fc::raw::unpack<ProposalType>(data);
			}
		};

		struct ProposalEntry;
		typedef fc::optional<ProposalEntry> oProposalEntry;

		struct ProposalEntry {
			ProposalIdType proposal_id;
			ProposalCondition proposal_condition;
			cdcchain::consensus::Address proposal_from;
			bool has_finished = false;
			fc::time_point_sec start_time;
			fc::time_point_sec expected_end_time;
			fc::time_point_sec finish_time;
			std::set<cdcchain::consensus::Address> proposal_voter;

			ProposalEntry();
			ProposalEntry(const ProposalIdType& id);

			static oProposalEntry lookup(const ChainInterface&, const ProposalIdType&);
			static void store(ChainInterface&, const ProposalIdType&, const ProposalEntry&);
			static void remove(ChainInterface&, const ProposalIdType&);
		};

		struct ApplyForPrivilegeAdmin {
			static const ProposalTypeEnum type;

			cdcchain::consensus::Address candidate;
			int delegate_vote_need;
		};

		struct RevokePrivilegeAdmin {
			static const ProposalTypeEnum type;

			cdcchain::consensus::Address privilege_admin;
			int delegate_vote_need;
		};

		class ProposalDbInterface
		{
			friend struct ProposalEntry;
			virtual  oProposalEntry  proposal_lookup_by_id(const ProposalIdType&)const = 0;
			virtual void proposal_insert_into_id_map(const ProposalIdType&, const ProposalEntry&) = 0;
			virtual void proposal_erase_from_id_map(const ProposalIdType&) = 0;
		};

	}
} // cdcchain::consensus


FC_REFLECT_ENUM(cdcchain::consensus::ProposalTypeEnum,
(apply_for_privilege_admin)
(revoke_privilege_admin)
)

FC_REFLECT(cdcchain::consensus::ProposalCondition,
(proposal_type)
(proposal_data)
)

FC_REFLECT(cdcchain::consensus::ApplyForPrivilegeAdmin,
(candidate)
(delegate_vote_need)
)

FC_REFLECT(cdcchain::consensus::RevokePrivilegeAdmin,
(privilege_admin)
(delegate_vote_need)
)

FC_REFLECT(cdcchain::consensus::ProposalEntry,
(proposal_id)
(proposal_condition)
(proposal_from)
(has_finished)
(start_time)
(expected_end_time)
(finish_time)
(proposal_voter)
)