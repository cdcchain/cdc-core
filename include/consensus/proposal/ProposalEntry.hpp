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
				FC_ASSERT(proposal_type == ProposalType::type, "", ("proposal_type", proposal_type)("ProposalType", ProposalType::type));
				return fc::raw::unpack<ProposalType>(proposal_data);
			}
		};

		struct ProposalEntry;
		typedef fc::optional<ProposalEntry> oProposalEntry;

		struct ProposalEntry {
			ProposalCondition proposal_condition;
			cdcchain::consensus::Address proposal_from;
			fc::time_point_sec start_time;
			fc::time_point_sec expected_end_time;
			std::set<cdcchain::consensus::Address> proposal_voter;

			ProposalEntry(){}
			ProposalEntry(const ProposalCondition& cond, const Address& from_addr, const fc::time_point_sec& _start_time,
				const fc::time_point_sec& _expected_end_time): proposal_condition(cond), proposal_from(from_addr),
				start_time(_start_time), expected_end_time(_expected_end_time){}

			ProposalIdType id()const;

			static oProposalEntry lookup(const ChainInterface&, const ProposalIdType&);
			static void store(ChainInterface&, const ProposalIdType&, const ProposalEntry&);
			static void remove(ChainInterface&, const ProposalIdType&);
		};

		struct ApplyForPrivilegeAdmin {
			static const ProposalTypeEnum type;

			ApplyForPrivilegeAdmin(){}
			ApplyForPrivilegeAdmin(const Address& addr, int vote_need): candidate(addr), delegate_vote_need(vote_need){}

			cdcchain::consensus::Address candidate;
			int delegate_vote_need;
		};

		struct RevokePrivilegeAdmin {
			static const ProposalTypeEnum type;

			RevokePrivilegeAdmin(){}
			RevokePrivilegeAdmin(const Address& addr, int vote_need): privilege_admin(addr), delegate_vote_need(vote_need){}

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
(proposal_condition)
(proposal_from)
(start_time)
(expected_end_time)
(proposal_voter)
)