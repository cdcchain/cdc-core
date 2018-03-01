#pragma once

#include <consensus/contract_engine/ContractEngine.hpp>
#include <consensus/contract_engine/uvm_contract_engine.hpp>

namespace cdcchain
{
	namespace consensus
	{
		namespace contract_engine
		{
			typedef ::glua::UvmContractEngine ActiveContractEngine;

			class ContractEngineBuilder
			{
			private:
				std::shared_ptr<ActiveContractEngine> _engine;
			public:
				virtual ~ContractEngineBuilder();
				ContractEngineBuilder *set_use_contract(bool use_contract);
				ContractEngineBuilder *set_caller(std::string caller, std::string caller_address);
				std::shared_ptr<ActiveContractEngine> build();
			};
		}
	}
}
