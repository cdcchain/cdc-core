// Copyright (c) 2017-2018 The CDC developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.


/*
 * This file contains structs to populate for JSON representation of transactions/operations
 * for wallets and block explorers and such
 */

#pragma once

namespace cdcchain {
    namespace wallet {

        using namespace cdcchain::consensus;

        struct PublicKeySummary
        {
            string    hex;
            string    native_pubkey;
            string    native_address;
            string    pts_normal_address;
            string    pts_compressed_address;
            string    btc_normal_address;
            string    btc_compressed_address;

        };

        struct VoteSummary
        {
            bool      up_to_date_with_recommendation;  // Are my votes all voting for the result of "vote_recommended" ?
            float     utilization;
            float     negative_utilization;
        };

        struct PrettyLedgerEntry
        {
            string                                   from_account;
			string                                   from_account_name;
            string                                   to_account;
			string                                   to_account_name;
            Asset                                    amount;
            string                                   memo;
            map<string, map<AssetIdType, Asset>>   running_balances;
        };

        struct PrettyTransaction
        {
            bool                        is_virtual = false;
            bool                        is_confirmed = false;
            bool                        is_market = false;
            bool                        is_market_cancel = false;
            TransactionIdType         trx_id;
            uint32_t                    block_num = 0;
            // position of the trx in a block
            uint32_t                    block_position = 0;
            // transaction type
            fc::enum_type<cdcchain::consensus::TransactionType, uint32_t>   trx_type = cdcchain::consensus::TransactionType::normal_transaction;
            vector<PrettyLedgerEntry> ledger_entries;
            Asset                       fee;
            fc::time_point_sec          timestamp;
            fc::time_point_sec          expiration_timestamp;
            optional<fc::exception>     error;
        };

        struct PrettyContractLedgerEntry
        {
            string      from_account;
            string      from_account_name;
            string      to_account;
            string      to_account_name;
            Asset       amount;
            Asset       fee;
            string      memo;
        };

        struct PrettyContractTransaction
        {
            TransactionIdType       result_trx_id;
            TransactionIdType       orig_trx_id;
            uint32_t                block_num = 0;
            uint32_t                block_position = 0;
            fc::enum_type<cdcchain::consensus::TransactionType, uint32_t>   trx_type;
            bool is_completed;
            PrettyContractLedgerEntry to_contract_ledger_entry;
            vector<PrettyContractLedgerEntry>  from_contract_ledger_entries;
            fc::time_point_sec      timestamp;
            fc::time_point_sec      expiration_timestamp;
            std::vector<std::string>    reserved;
            optional<fc::exception>     error;
        };

        struct ContractTransactionSummary
        {
            TransactionIdType       result_trx_id;
            TransactionIdType       orig_trx_id;
            uint32_t                block_num = 0;
            uint32_t                block_position = 0;
            fc::enum_type<cdcchain::consensus::TransactionType, uint32_t>   trx_type;
            std::string             contract_address;
            std::string             method;
            std::string             params;
			bool					is_completed;
        };
        struct PrettyReserveBalance
        {
            BalanceIdType     balance_id;
            optional<string>    sharedrop_address;

            time_point_sec      start_time;
            uint32_t            duration = 0;

            AssetIdType       asset_id;
            ShareType          original_balance;
            ShareType          reserve_balance;
            ShareType          claimed_balance;
            ShareType          available_balance;
        };

        struct EscrowSummary
        {
            /** the transaction ID that created the escrow balance */
            TransactionIdType creating_transaction_id;
            BalanceIdType     balance_id;
            /** the amount of money still held in escrow */
            Asset               balance;
            /** the account name of the escrow agent */
            string              sender_account_name;
            string              receiver_account_name;
            string              escrow_agent_account_name;
            DigestType         agreement_digest;
        };


    }
} // cdcchain::wallet

FC_REFLECT(cdcchain::wallet::PublicKeySummary, (hex)(native_pubkey)(native_address)(pts_normal_address)(pts_compressed_address)(btc_normal_address)(btc_compressed_address))

FC_REFLECT(cdcchain::wallet::VoteSummary, (utilization)(negative_utilization)(up_to_date_with_recommendation))

FC_REFLECT(cdcchain::wallet::PrettyLedgerEntry,
(from_account)
(from_account_name)
(to_account)
(to_account_name)
(amount)
(memo)
(running_balances)
)
FC_REFLECT(cdcchain::wallet::PrettyTransaction,
(is_virtual)
(is_confirmed)
(is_market)
(is_market_cancel)
(trx_id)
(block_num)
(block_position)
(trx_type)
(ledger_entries)
(fee)
(timestamp)
(expiration_timestamp)
(error)
)

FC_REFLECT(cdcchain::wallet::PrettyContractLedgerEntry,
(from_account)
(from_account_name)
(to_account)
(to_account_name)
(amount)
(fee)
(memo)
)

FC_REFLECT(cdcchain::wallet::PrettyContractTransaction,
(result_trx_id)
(orig_trx_id)
(block_num)
(block_position)
(trx_type)
(is_completed)
(to_contract_ledger_entry)
(from_contract_ledger_entries)
(timestamp)
(expiration_timestamp)
(reserved)
(error)
)

FC_REFLECT(cdcchain::wallet::ContractTransactionSummary,
(result_trx_id)
(orig_trx_id)
(block_num)
(block_position)
(trx_type)
(contract_address)
(method)
(params)
(is_completed)
)
FC_REFLECT(cdcchain::wallet::PrettyReserveBalance,
(balance_id)
(sharedrop_address)
(start_time)
(duration)
(asset_id)
(original_balance)
(reserve_balance)
(claimed_balance)
(available_balance)
)
FC_REFLECT(cdcchain::wallet::EscrowSummary,
(creating_transaction_id)
(balance_id)
(balance)
(sender_account_name)
(receiver_account_name)
(escrow_agent_account_name)
(agreement_digest)
)
