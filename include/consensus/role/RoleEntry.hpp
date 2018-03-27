#pragma once

#include <consensus/Types.hpp>

namespace cdcchain {
	namespace consensus {

		enum RoleAuthEnum {
			// admin
			privilege_admin = 0,
			general_admin = 1,

			// contract
			contract_admin = 10,
			contract_operator = 11,
		};

		class ChainInterface;

		struct  PrivilegeAdminRole {
			static const RoleAuthEnum type;
			fc::time_point_sec gain_auth_time;
		};

		struct  GeneralAdminRole {
			static const RoleAuthEnum type;
			fc::time_point_sec gain_auth_time;
		};

		struct ContractAdminRole {
			static const RoleAuthEnum type;
			fc::time_point_sec gain_auth_time;
			ContractIdType from_contract;
		};

		struct ContractOperatorRole {
			static const RoleAuthEnum type;
			fc::time_point_sec gain_auth_time;
			ContractIdType from_contract;
		};

		struct RoleCondition {
			fc::enum_type<fc::unsigned_int, RoleAuthEnum> role_type;
			cdcchain::consensus::Address role_address;
			std::vector<char> role_data;

			RoleCondition() {}

			RoleCondition(const RoleCondition& cond) : role_type(cond.role_type),
				role_address(cond.role_address), role_data(cond.role_data) {}

			template<typename RoleAuthType>
			RoleCondition(const Address& user_address, const RoleAuthType& t)
			{
				role_type = RoleAuthType::type;
				role_address = user_address;
				role_data = fc::raw::pack(t);
			}

			template<typename RoleAuthType>
			RoleAuthType as()const
			{
				FC_ASSERT(role_type == RoleAuthType::type, "", ("role_type", role_type)("RoleAuthType", RoleAuthType::type));
				return fc::raw::unpack<RoleAuthType>(role_data);
			}

		};

		struct RoleEntry;
		typedef fc::optional<RoleEntry> oRoleEntry;

		struct RoleEntry {
			cdcchain::consensus::ContractIdType contract_id;
			
			vector<RoleCondition> role_cond_vec;
			fc::time_point_sec update_time;

			static oRoleEntry lookup(const ChainInterface&, const ContractIdType&);
			static void store(ChainInterface&, const ContractIdType&, const RoleEntry&);
			static void remove(ChainInterface&, const ContractIdType&);
		};

		class RoleDbInterface
		{
			friend struct RoleEntry;
			virtual  oRoleEntry  role_lookup_by_addr(const Address&)const = 0;
			virtual void role_insert_into_addr_map(const Address&, const RoleEntry&) = 0;
			virtual void role_erase_from_addr_map(const Address&) = 0;
		};
	}
}

FC_REFLECT_ENUM(cdcchain::consensus::RoleAuthEnum,
(privilege_admin)
(general_admin)
(contract_admin)
(contract_operator)
)

FC_REFLECT(cdcchain::consensus::RoleCondition,
	(role_type)
	(role_address)
	(role_data)
)

FC_REFLECT(cdcchain::consensus::PrivilegeAdminRole,
(gain_auth_time)
)

FC_REFLECT(cdcchain::consensus::GeneralAdminRole,
(gain_auth_time)
)

FC_REFLECT(cdcchain::consensus::ContractAdminRole,
(gain_auth_time)
(from_contract)
)

FC_REFLECT(cdcchain::consensus::ContractOperatorRole,
(gain_auth_time)
(from_contract)
)

FC_REFLECT(cdcchain::consensus::RoleEntry,
	(contract_id)
	(role_cond_vec)
	(update_time)
	)