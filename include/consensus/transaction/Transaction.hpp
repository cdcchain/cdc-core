#pragma once

#include <consensus/account/AccountEntry.hpp>
#include <consensus/operation/Operations.hpp>
#include <consensus/operation/StorageOperations.hpp>
#include <consensus/operation/EventOperations.hpp>
#include <consensus/operation/BalanceOperations.hpp>
#include <consensus/slate/SlateEntry.hpp>
#include <consensus/WithdrawTypes.hpp>
#include <map>
#include <fc/reflect/variant.hpp>

namespace cdcchain {
    namespace consensus {

        enum TransactionType
        {
            normal_transaction = 0,
            withdraw_pay_transaction = 1,        //代理取工资
            register_account_transaction = 2,    //注册账户
            register_delegate_transaction = 3,   //注册代理
            upgrade_account_transaction = 4,    //代理升级
            update_account_transaction = 5,     //更新账户信息

            contract_register_transaction = 10,
            transfer_contract_transaction = 11,
            contract_upgrade_transaction = 12,
            contract_destroy_transaction = 13,
            contract_call_transaction = 14
        };

        enum ResultTransactionType
        {
            origin_transaction = 0,          //原始交易
            complete_result_transaction = 1,       //完整的结果交易
            incomplete_result_transaction = 2,       //不完整的结果交易
        };

        struct market_index_key;
        struct Code;
        struct Transaction
        {
            fc::time_point_sec    expiration;
            optional<uint64_t>    reserved;
            string cdc_account;
            //string from_account;
            Asset cdc_inport_asset;
            vector<Operation>     operations;
            fc::enum_type<uint8_t, ResultTransactionType>    result_trx_type = ResultTransactionType::origin_transaction;    
            TransactionIdType     result_trx_id = TransactionIdType();

            DigestType digest(const DigestType& chain_id)const;

            void issue(const Asset& amount_to_issue);

            void define_slate(const set<AccountIdType>& slate);

            void withdraw(const BalanceIdType& account, ShareType amount);

            void withdraw_from_contract(const BalanceIdType& account, ShareType amount, const ContractIdType& contract_id);

            void withdraw_pay(const AccountIdType account, ShareType amount);
			void deposit(const Address& addr, const Asset& amount);


            void deposit_multisig(const MultisigMetaInfo& info, const Asset& amount);

            void release_escrow(const Address& escrow_account,
                const Address& released_by,
                ShareType amount_to_sender,
                ShareType amount_to_receiver);

            PublicKeyType deposit_to_escrow(fc::ecc::public_key receiver_key,
                fc::ecc::public_key escrow_key,
                DigestType agreement,
                Asset amount,
                fc::ecc::private_key from_key,
                const string& memo_message,
                const fc::ecc::public_key& memo_public_key,
                fc::ecc::private_key one_time_private_key,
                MemoFlagsEnum memo_type = from_memo);

            PublicKeyType deposit_to_account(fc::ecc::public_key receiver_key,
                Asset amount,
                fc::ecc::private_key from_key,
                const string& memo_message,
                const fc::ecc::public_key& memo_public_key,
                fc::ecc::private_key one_time_private_key,
                MemoFlagsEnum memo_type = from_memo,
                bool use_stealth_address = true);


            void register_account(const string& name,
                const variant& public_data,
                const PublicKeyType& master,
                const PublicKeyType& active,
                uint8_t pay_rate = -1,
                optional<AccountMetaInfo> info = optional<AccountMetaInfo>());

            void update_account(AccountIdType account_id,
                uint8_t delegate_pay_rate,
                const optional<variant>& public_data,
                const optional<PublicKeyType>& active);

            void create_asset(const string& symbol,
                const string& name,
                const string& description,
                const variant& data,
                AccountIdType issuer_id,
                ShareType max_share_supply,
                uint64_t precision);

            void update_asset(const AssetIdType asset_id,
                const optional<string>& name,
                const optional<string>& description,
                const optional<variant>& public_data,
                const optional<double>& maximum_share_supply,
                const optional<uint64_t>& precision);

            void update_asset_ext(const AssetIdType asset_id,
                const optional<string>& name,
                const optional<string>& description,
                const optional<variant>& public_data,
                const optional<double>& maximum_share_supply,
                const optional<uint64_t>& precision,
                const ShareType issuer_fee,
                uint16_t market_fee,
                uint32_t flags,
                uint32_t issuer_permissions,
                AccountIdType issuer_account_id,
                uint32_t required_sigs,
                const vector<Address>& authority
                );

            void contract_call(const ContractIdType& contract,
                const string& method,
                const string& arguments,
                const PublicKeyType& caller_public_key,
                const Asset& costlimit,
                const Asset& transaction_fee,
                const map<BalanceIdType, ShareType>& balances
                );

			void proposal_apply_for_privilege_admin(const Address& proposal_from,
				const Address& candidate,
				int delegate_vote_need,
				const fc::time_point_sec& start_time,
				const fc::time_point_sec& expected_end_time);

			void proposal_revoke_privilege_admin(const Address& proposal_from,
				const Address& privilege_admin,
				int delegate_vote_need,
				const fc::time_point_sec& start_time,
				const fc::time_point_sec& expected_end_time);

			void proposal_approve(
				const Address& proposal_approver,
				const ProposalIdType& proposal_id);

			void appoint_general_admin(
				const Address& caller_address,
				const Address& candidate_address);

			void revoke_general_admin(
				const Address& caller_address,
				const Address& general_admin_address);


            void update_signing_key(const AccountIdType account_id, const PublicKeyType& signing_key);

            void update_balance_vote(const BalanceIdType& balance_id, const optional<Address>& new_restricted_owner);

            void set_slates(const SlateIdType slate_id);
            void AddtionImessage(const string imessage);
            bool is_cancel()const;
            ContractIdType contract_register(const uvm::blockchain::Code& code, const PublicKeyType& owner, const Asset& initlimit, const Asset& transaction_fee, const map<BalanceIdType, ShareType>& initcost);

            void contract_upgrade(const ContractIdType& id,
                const string& name, const string& desc, const Asset& execlimit, const Asset& fee, const std::map<BalanceIdType, ShareType>& balances);

            void contract_destroy(const ContractIdType& id, Asset& exec_limit, const Asset& fee, const std::map<BalanceIdType, ShareType>& balances);

        }; // transaction

        struct SignedTransaction : public Transaction
        {
            TransactionIdType   id()const;
            size_t                data_size()const;
            void                  sign(const fc::ecc::private_key& signer, const DigestType& chain_id);
            PublicKeyType       get_signing_key(const size_t sig_index, const DigestType& chain_id)const;
            void push_transaction(const SignedTransaction& trx);
            void push_storage_operation(const StorageOperation& storage_op);
            void push_event_operation(const EventOperation& event_op);
            void push_balances_withdraw_operation(const BalancesWithdrawOperation& balances_withdraw_op);
            bool check_operations_legality()const;
            vector<fc::ecc::compact_signature> signatures;
        };
        typedef vector<SignedTransaction> signed_transactions;
        typedef optional<SignedTransaction> osigned_transaction;
        struct CdcTrxidBalance
        {
            CdcTrxidBalance(){};
            CdcTrxidBalance(string cdc_account, TransactionIdType trx_id, Asset asset_trx, uint32_t
                block_num, string from_account, fc::time_point_sec create_time) :
                cdc_account(cdc_account),
                trx_id(trx_id),
                asset_trx(asset_trx),
                block_num(block_num),
                from_account(from_account),
                create_time(create_time){};
            string cdc_account;
            uint32_t block_num;
            TransactionIdType trx_id;
            Asset asset_trx;
            string from_account;
            fc::time_point_sec create_time;
            friend bool operator > (const CdcTrxidBalance& uba, const CdcTrxidBalance& ubb){
                return uba.block_num > ubb.block_num;
            }
            friend bool operator < (const CdcTrxidBalance& uba, const CdcTrxidBalance& ubb){
                return uba.block_num < ubb.block_num;
            }
            friend bool operator == (const CdcTrxidBalance& uba, const CdcTrxidBalance& ubb){
                return uba.block_num == ubb.block_num;
            }
            friend bool operator != (const CdcTrxidBalance& uba, const CdcTrxidBalance& ubb){
                return uba.block_num != ubb.block_num;
            }
        };
        struct CdcBalanceEntry
        {
            std::set<TransactionIdType> cdc_trxid_sort;
            std::multimap<uint32_t, CdcTrxidBalance> cdc_block_sort;
        };
        struct TransactionLocation
        {
            TransactionLocation(uint32_t block_num = 0, uint32_t trx_num = 0)
                :block_num(block_num), trx_num(trx_num){}

            uint32_t block_num;
            uint32_t trx_num;
        };
        typedef optional<TransactionLocation> oTransactionLocation;

    }
} // cdcchain::consensus

FC_REFLECT_ENUM(cdcchain::consensus::TransactionType,
    (normal_transaction)
    (withdraw_pay_transaction)
    (register_account_transaction)
    (register_delegate_transaction)
    (upgrade_account_transaction)
    (update_account_transaction)
    (contract_register_transaction)
    (transfer_contract_transaction)
    (contract_upgrade_transaction)
    (contract_destroy_transaction)
    (contract_call_transaction)
    )

    FC_REFLECT_ENUM(cdcchain::consensus::ResultTransactionType,
    (origin_transaction)
    (complete_result_transaction)
    (incomplete_result_transaction)
    )

    FC_REFLECT(cdcchain::consensus::CdcTrxidBalance, (cdc_account)(trx_id)(asset_trx)(block_num)(from_account)(create_time))
    FC_REFLECT(cdcchain::consensus::CdcBalanceEntry, (cdc_trxid_sort)(cdc_block_sort))
    FC_REFLECT(cdcchain::consensus::Transaction, (expiration)(reserved)(cdc_account)(cdc_inport_asset)(operations)(result_trx_type)(result_trx_id))
    FC_REFLECT_DERIVED(cdcchain::consensus::SignedTransaction, (cdcchain::consensus::Transaction), (signatures))
    FC_REFLECT(cdcchain::consensus::TransactionLocation, (block_num)(trx_num))
