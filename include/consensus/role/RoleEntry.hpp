#pragma once

#include <consensus/Types.hpp>

namespace cdcchain {
	namespace consensus {

		enum RoleAuthEnum {
			// admin
			privilege_admin = 0,
			general_admin = 1,

			// merchant
			merchant_admin = 10,
			merchant_operator = 11,

			// mining pool
			mining_pool_admin = 40,
			mining_pool_operator = 41,

			// statistics pool
			statistics_pool_admin = 50,
			statistics_pool_operator = 51,

			// arbitrament
			arbitrament_admin = 80,
			arbitrament_operator = 81
		};

		class ChainInterface;

		struct RoleCondition {
			fc::enum_type<fc::unsigned_int, RoleAuthEnum> role_type;
			std::vector<char> role_data;

			RoleCondition() {}

			RoleCondition(const RoleCondition& cond) : role_type(cond.role_type),
				role_data(cond.role_data) {}

			template<typename RoleAuthType>
			RoleCondition(const RoleAuthType& t)
			{
				role_type = RoleAuthType::type;
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
			cdcchain::consensus::Address user_address;
			vector<RoleCondition> role_cond_vec;
			fc::time_point_sec update_time;

			static oRoleEntry lookup(const ChainInterface&, const Address&);
			static void store(ChainInterface&, const Address&, const RoleEntry&);
			static void remove(ChainInterface&, const Address&);
		};

		struct  PrivilegeAdminRole {
			static const RoleAuthEnum type;
			fc::time_point_sec gain_auth_time;
		};

		struct  GeneralAdminRole {
			static const RoleAuthEnum type;
			fc::time_point_sec gain_auth_time;
		};

		struct MerchantAdminRole {
			static const RoleAuthEnum type;
			fc::time_point_sec gain_auth_time;
			ContractIdType from_merchant;
		};

		struct MerchantOperatorRole {
			static const RoleAuthEnum type;
			fc::time_point_sec gain_auth_time;
			ContractIdType from_merchant;
		};

		struct MiningPoolAdminRole {
			static const RoleAuthEnum type;
			fc::time_point_sec gain_auth_time;
			ContractIdType from_pool;
		};

		struct MiningPoolOperatorRole {
			static const RoleAuthEnum type;
			fc::time_point_sec gain_auth_time;
			ContractIdType from_pool;
		};

		struct StatisticsPoolAdminRole {
			static const RoleAuthEnum type;
			fc::time_point_sec gain_auth_time;
			ContractIdType from_pool;
		};

		struct StatisticsPoolOperatorRole {
			static const RoleAuthEnum type;
			fc::time_point_sec gain_auth_time;
			ContractIdType from_pool;
		};

		struct ArbitramentAdminRole {
			static const RoleAuthEnum type;
			fc::time_point_sec gain_auth_time;
			ContractIdType from_arbitrament;
		};

		struct ArbitramentOperatorRole {
			static const RoleAuthEnum type;
			fc::time_point_sec gain_auth_time;
			ContractIdType from_arbitrament;
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
(merchant_admin)
(merchant_operator)
(mining_pool_admin)
(mining_pool_operator)
(statistics_pool_admin)
(statistics_pool_operator)
(arbitrament_admin)
(arbitrament_operator)
)

FC_REFLECT(cdcchain::consensus::RoleCondition,
	(role_type)
	(role_data)
)

FC_REFLECT(cdcchain::consensus::PrivilegeAdminRole,
(gain_auth_time)
)

FC_REFLECT(cdcchain::consensus::GeneralAdminRole,
(gain_auth_time)
)

FC_REFLECT(cdcchain::consensus::MerchantAdminRole,
(gain_auth_time)
(from_merchant)
)

FC_REFLECT(cdcchain::consensus::MerchantOperatorRole,
(gain_auth_time)
(from_merchant)
)

FC_REFLECT(cdcchain::consensus::MiningPoolAdminRole,
(gain_auth_time)
(from_pool)
)

FC_REFLECT(cdcchain::consensus::MiningPoolOperatorRole,
(gain_auth_time)
(from_pool)
)

FC_REFLECT(cdcchain::consensus::StatisticsPoolAdminRole,
(gain_auth_time)
(from_pool)
)

FC_REFLECT(cdcchain::consensus::StatisticsPoolOperatorRole,
(gain_auth_time)
(from_pool)
)

FC_REFLECT(cdcchain::consensus::ArbitramentAdminRole,
(gain_auth_time)
(from_arbitrament)
)

FC_REFLECT(cdcchain::consensus::ArbitramentOperatorRole,
(gain_auth_time)
(from_arbitrament)
)

FC_REFLECT(cdcchain::consensus::RoleEntry,
	(user_address)
	(role_cond_vec)
	(update_time)
	)