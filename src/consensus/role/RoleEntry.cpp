#include <consensus/chainstate/ChainInterface.hpp>
#include <consensus/role/RoleEntry.hpp>

namespace cdcchain {
	namespace consensus {

		const RoleAuthEnum PrivilegeAdminRole::type = privilege_admin;
		const RoleAuthEnum GeneralAdminRole::type = general_admin;
		const RoleAuthEnum MerchantAdminRole::type = merchant_admin;
		const RoleAuthEnum MerchantOperatorRole::type = merchant_operator;
		const RoleAuthEnum MiningPoolAdminRole::type = mining_pool_admin;
		const RoleAuthEnum MiningPoolOperatorRole::type = mining_pool_operator;
		const RoleAuthEnum StatisticsPoolAdminRole::type = statistics_pool_admin;
		const RoleAuthEnum StatisticsPoolOperatorRole::type = statistics_pool_operator;
		const RoleAuthEnum ArbitramentAdminRole::type = arbitrament_admin;
		const RoleAuthEnum ArbitramentOperatorRole::type = arbitrament_operator;


		oRoleEntry RoleEntry::lookup(const ChainInterface& db, const Address& addr)
		{
			try
			{
				return db.role_lookup_by_addr(addr);
			}FC_CAPTURE_AND_RETHROW((addr))
		}

		void RoleEntry::store(ChainInterface& db, const Address& addr, const RoleEntry& entry)
		{
			try
			{
				db.role_insert_into_addr_map(addr, entry);
			}FC_CAPTURE_AND_RETHROW((addr)(entry))
		}

		void RoleEntry::remove(ChainInterface& db, const Address& addr)
		{
			try
			{
				const oRoleEntry entry = db.lookup<RoleEntry>(addr);

				if (entry.valid())
				{
					db.role_erase_from_addr_map(addr);
				}
			}FC_CAPTURE_AND_RETHROW((addr))
		}

	}
}