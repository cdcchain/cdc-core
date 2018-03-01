#pragma once

#include <consensus/account/AccountEntry.hpp>
#include <consensus/operation/Operations.hpp>

namespace cdcchain {
    namespace consensus {

        struct RegisterAccountOperation
        {
            static const OperationTypeEnum type;

            RegisterAccountOperation(){}

            RegisterAccountOperation(const std::string& n,
                const fc::variant& d,
                const PublicKeyType& owner,
                const PublicKeyType& active,
                uint8_t pay_rate = -1)
                :name(n), public_data(d), owner_key(owner), active_key(active), delegate_pay_rate(pay_rate){}

            std::string                 name;
            fc::variant                 public_data;
            PublicKeyType             owner_key;
            PublicKeyType             active_key;

            uint8_t                     delegate_pay_rate = -1;

            /**
             *  Meta information is used by clients to evaluate
             *  how to send to this account.  This is designed to
             *  support registering of multi-sig accounts or
             *  accounts with other advanced rules.
             *
             *  This data does not effect validation rules.
             */
            optional<AccountMetaInfo> meta_data;

            bool is_delegate()const;

            void evaluate(TransactionEvaluationState& eval_state)const;
        };

        struct UpdateAccountOperation
        {
            static const OperationTypeEnum type;

            AccountIdType                   account_id;
            fc::optional<fc::variant>         public_data;
            fc::optional<PublicKeyType>     active_key;
            uint8_t                           delegate_pay_rate = -1;

            bool is_retracted()const;
            bool is_delegate()const;

            void evaluate(TransactionEvaluationState& eval_state)const;
        };

        struct UpdateSigningKeyOperation
        {
            static const OperationTypeEnum  type;

            AccountIdType  account_id;
            PublicKeyType  signing_key;

            void evaluate(TransactionEvaluationState& eval_state)const;
        };

        struct WithdrawPayOperation
        {
            static const OperationTypeEnum type;
            WithdrawPayOperation() :amount(0){}

            WithdrawPayOperation(ShareType amount_to_withdraw,
                AccountIdType id)
                :amount(amount_to_withdraw), account_id(id) {}

            ShareType                       amount;
            AccountIdType                  account_id;

            void evaluate(TransactionEvaluationState& eval_state)const;
        };
		struct GetContractFeeOperation {
			static const OperationTypeEnum type;
			GetContractFeeOperation():amount(0){}
			GetContractFeeOperation(ShareType amount_to_withdraw,string address)
				:amount(amount_to_withdraw), account_address(address) {}

			void evaluate(TransactionEvaluationState& eval_state)const;
			ShareType                       amount;
			string                  account_address;
		};

    }
} // cdcchain::consensus

FC_REFLECT(cdcchain::consensus::RegisterAccountOperation, (name)(public_data)(owner_key)(active_key)(delegate_pay_rate)(meta_data))
FC_REFLECT(cdcchain::consensus::UpdateAccountOperation, (account_id)(public_data)(active_key)(delegate_pay_rate))
FC_REFLECT(cdcchain::consensus::WithdrawPayOperation, (amount)(account_id))
FC_REFLECT(cdcchain::consensus::UpdateSigningKeyOperation, (account_id)(signing_key))
FC_REFLECT(cdcchain::consensus::GetContractFeeOperation,(amount)(account_address))
