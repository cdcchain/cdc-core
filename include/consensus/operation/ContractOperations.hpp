#pragma once

#include <consensus/asset/Asset.hpp>
#include <consensus/operation/Operations.hpp>
#include <consensus/account/AccountEntry.hpp>
#include <consensus/Types.hpp>
#include <consensus/asset/AssetEntry.hpp>
#include <consensus/contract/ContractEntry.hpp>

namespace cdcchain {
    namespace consensus {

        struct UpgradeContractOperation
        {
            static const OperationTypeEnum type;

            UpgradeContractOperation(){}

			UpgradeContractOperation(const ContractIdType& arg_id, const string& arg_name, const string& arg_desc, 
										Asset& execlimit, const Asset& fee, const std::map<BalanceIdType, ShareType>& arg_balances)
									:id(arg_id), name(arg_name), desc(arg_desc), exec_limit(execlimit), balances(arg_balances),transaction_fee(fee){}

            ContractIdType id;
            string         name;
            string         desc;
			Asset          exec_limit;
			Asset transaction_fee;
			std::map<BalanceIdType, ShareType> balances;

            void evaluate(TransactionEvaluationState& eval_state)const;
        };

        struct DestroyContractOperation
        {
            static const OperationTypeEnum type;

            DestroyContractOperation(){}

			DestroyContractOperation(const ContractIdType& arg_id, const std::map<BalanceIdType, ShareType>& arg_balances, const Asset& execlimit, const Asset& fee)
                :id(id), balances(arg_balances), exec_limit(execlimit),transaction_fee(fee){}

            ContractIdType id;
			Asset exec_limit;
			Asset transaction_fee;
			std::map<BalanceIdType, ShareType> balances;
            void evaluate(TransactionEvaluationState& eval_state)const;
        };

		struct OnDestroyOperation
		{
			static const OperationTypeEnum type;

			OnDestroyOperation(){}
			OnDestroyOperation(const ContractIdType& arg_id, const Asset& arg_amount) :id(arg_id), amount(arg_amount){}

			ContractIdType id;
			Asset amount;

			void evaluate(TransactionEvaluationState& eval_state)const;

		};

		struct OnUpgradeOperation
		{

			static const OperationTypeEnum type;

			OnUpgradeOperation(){}
			OnUpgradeOperation(const ContractIdType& arg_id, const string& arg_name, const string& arg_desc) :id(arg_id), name(arg_name), desc(arg_desc){}

			ContractIdType id;
			string         name;
			string         desc;
			void evaluate(TransactionEvaluationState& eval_state)const;
		};


        struct RegisterContractOperation
        {
            static const OperationTypeEnum type;

            RegisterContractOperation(){}
            RegisterContractOperation(const uvm::blockchain::Code& code, const PublicKeyType& owner, const std::map<BalanceIdType, ShareType>& balances, const Asset& initcost,const Asset& fee) :balances(balances), contract_code(code), owner(owner), initcost(initcost), register_time(fc::time_point::now()), transaction_fee(fee){}

			uvm::blockchain::Code  contract_code;   //�������
            Asset initcost;         //��ʼ����
			Asset transaction_fee;
            std::map<BalanceIdType, ShareType> balances;         //�۳���balance
            PublicKeyType owner;    //��Լ������
            fc::time_point     register_time;
            ContractIdType get_contract_id()const;
            void evaluate(TransactionEvaluationState& eval_state)const;
        };
        struct CallContractOperation
        {
            static const OperationTypeEnum type;
            static bool is_function_not_allow_call(const string& method);
            CallContractOperation(){}
            CallContractOperation(const ContractIdType& contract,
                const string& method,
                const string& args, const PublicKeyType caller,
                const Asset& costlimit,
				const Asset& fee,
                const std::map<BalanceIdType, ShareType>& balances) : balances(balances), caller(caller), contract(contract), method(method), args(args), costlimit(costlimit),transaction_fee(fee){}

            PublicKeyType caller;
            std::map<BalanceIdType, ShareType> balances;
            ContractIdType contract;
            Asset costlimit;
			Asset transaction_fee;
            string method;
            string args;
            void evaluate(TransactionEvaluationState& eval_state)const;
        };

		struct ContractInfoOperation
		{
			static const OperationTypeEnum type;
			ContractInfoOperation() {}
			ContractInfoOperation(const ContractIdType& id,const PublicKeyType& owner,const uvm::blockchain::Code& code,
				const fc::time_point& time):contract_id(id),owner(owner),code(code),register_time(time) {}
			ContractIdType contract_id;
			PublicKeyType owner;
			uvm::blockchain::Code code;
			fc::time_point     register_time;
			void evaluate(TransactionEvaluationState& eval_state)const;
		};
        struct TransferContractOperation
        {
            static const OperationTypeEnum type;

            BalanceIdType                balance_id()const;

            TransferContractOperation() {}
            TransferContractOperation(const Address& to, const Asset& amnt, const Asset& exec_cost, const Asset& fee, const PublicKeyType& from, const map<BalanceIdType, ShareType>& balances)
                :balances(balances), transfer_amount(amnt), costlimit(exec_cost), from(from), contract_id(to), transaction_fee(fee){};
            PublicKeyType from;
            Asset costlimit;
			Asset transaction_fee;
            Asset transfer_amount;
            std::map<BalanceIdType, ShareType> balances;
            ContractIdType contract_id;


            void evaluate(TransactionEvaluationState& eval_state)const;
        };        
        struct OnCallSuccessOperation
        {
            static const OperationTypeEnum type;

            void evaluate(TransactionEvaluationState& eval_state)const {}
        };
    }
}


FC_REFLECT(cdcchain::consensus::UpgradeContractOperation, (id)(name)(desc)(exec_limit)(transaction_fee)(balances))
FC_REFLECT(cdcchain::consensus::DestroyContractOperation, (id)(exec_limit)(transaction_fee)(balances))
FC_REFLECT(cdcchain::consensus::OnDestroyOperation, (id)(amount))
FC_REFLECT(cdcchain::consensus::OnUpgradeOperation, (id)(name)(desc))
FC_REFLECT(cdcchain::consensus::OnCallSuccessOperation, )
FC_REFLECT(cdcchain::consensus::RegisterContractOperation, (contract_code)(initcost)(transaction_fee)(balances)(owner)(register_time))
FC_REFLECT(cdcchain::consensus::CallContractOperation, (caller)(balances)(contract)(costlimit)(transaction_fee)(method)(args))
FC_REFLECT(cdcchain::consensus::ContractInfoOperation, (contract_id)(owner)(code)(register_time))
FC_REFLECT(cdcchain::consensus::TransferContractOperation, (from)(costlimit)(transaction_fee)(transfer_amount)(balances)(contract_id))
