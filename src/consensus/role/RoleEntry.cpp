#include <consensus/chainstate/ChainInterface.hpp>
#include <consensus/role/RoleEntry.hpp>

namespace cdcchain {
	namespace consensus {

		const RoleTypeEnum PrivilegeAdminRole::type = privilege_admin;
		const RoleTypeEnum GeneralAdminRole::type = general_admin;
		const RoleTypeEnum ContractAdminRole::type = contract_admin;
		const RoleTypeEnum ContractOperatorRole::type = contract_operator;


		oRoleEntry RoleEntry::lookup(const ChainInterface& db, const ContractIdType& contract_id)
		{
			try
			{
				return db.role_lookup_by_addr(contract_id);
			}FC_CAPTURE_AND_RETHROW((contract_id))
		}

		void RoleEntry::store(ChainInterface& db, const ContractIdType& contract_id, const RoleEntry& entry)
		{
			try
			{
				db.role_insert_into_addr_map(contract_id, entry);
			}FC_CAPTURE_AND_RETHROW((contract_id)(entry))
		}

		void RoleEntry::remove(ChainInterface& db, const ContractIdType& contract_id)
		{
			try
			{
				const oRoleEntry entry = db.lookup<RoleEntry>(contract_id);

				if (entry.valid())
				{
					db.role_erase_from_addr_map(contract_id);
				}
			}FC_CAPTURE_AND_RETHROW((contract_id))
		}

	}
}