// Copyright (c) 2017-2018 The CDC developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.


//                                   _           _    __ _ _      
//                                  | |         | |  / _(_) |     
//    __ _  ___ _ __   ___ _ __ __ _| |_ ___  __| | | |_ _| | ___ 
//   / _` |/ _ \ '_ \ / _ \ '__/ _` | __/ _ \/ _` | |  _| | |/ _ \`
//  | (_| |  __/ | | |  __/ | | (_| | ||  __/ (_| | | | | | |  __/
//   \__, |\___|_| |_|\___|_|  \__,_|\__\___|\__,_| |_| |_|_|\___|
//    __/ |                                                       
//   |___/                                                        
//
//
// Warning: this is a generated file, any changes made here will be
//          overwritten by the build process.  If you need to change what is
//          generated here, you should either modify the input json files
//          (network_api.json, wallet_api.json, etc) or modify the code
//          generator (cdcchain_api_generator.cpp) itself
//
#define DEFAULT_LOGGER "rpc"
#include <rpc_stubs/CommonApiRpcServer.hpp>
#include <api/ApiMetadata.hpp>
#include <api/ConversionFunctions.hpp>
#include <boost/bind.hpp>
#include <api/ApiMetadata.hpp>
#include <consensus/account/AccountEntry.hpp>
#include <consensus/address/Address.hpp>
#include <consensus/asset/AssetEntry.hpp>
#include <consensus/block/Block.hpp>
#include <consensus/block/BlockEntry.hpp>
#include <consensus/chainstate/ChainDatabase.hpp>
#include <consensus/operation/Operations.hpp>
#include <consensus/address/PtsAddress.hpp>
#include <consensus/transaction/Transaction.hpp>
#include <consensus/Types.hpp>
#include <fc/crypto/elliptic.hpp>
#include <fc/crypto/sha256.hpp>
#include <fc/exception/exception.hpp>
#include <fc/filesystem.hpp>
#include <fc/network/ip.hpp>
#include <fc/optional.hpp>
#include <fc/time.hpp>
#include<network/Node.hpp>
#include <stdint.h>
#include <string>
#include <wallet/Pretty.hpp>
#include <wallet/TransactionBuilder.hpp>
#include <wallet/Wallet.hpp>
#include <wallet/WalletEntrys.hpp>

namespace cdcchain {
	namespace rpc_stubs {

		fc::variant CommonApiRpcServer::blockchain_get_info_positional(fc::rpc::json_connection* json_connection, const fc::variants& parameters)
		{
			// this method has no prerequisites


			fc::variant_object result = get_client()->blockchain_get_info();
			return fc::variant(result);
		}

		fc::variant CommonApiRpcServer::blockchain_get_info_named(fc::rpc::json_connection* json_connection, const fc::variant_object& parameters)
		{
			// this method has no prerequisites


			fc::variant_object result = get_client()->blockchain_get_info();
			return fc::variant(result);
		}

		fc::variant CommonApiRpcServer::blockchain_generate_snapshot_positional(fc::rpc::json_connection* json_connection, const fc::variants& parameters)
		{
			// this method has no prerequisites

			if (parameters.size() <= 0)
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 1 (filename)");
			std::string filename = parameters[0].as<std::string>();

			get_client()->blockchain_generate_snapshot(filename);
			return fc::variant();
		}

		fc::variant CommonApiRpcServer::blockchain_generate_snapshot_named(fc::rpc::json_connection* json_connection, const fc::variant_object& parameters)
		{
			// this method has no prerequisites

			if (!parameters.contains("filename"))
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 'filename'");
			std::string filename = parameters["filename"].as<std::string>();

			get_client()->blockchain_generate_snapshot(filename);
			return fc::variant();
		}

		fc::variant CommonApiRpcServer::blockchain_get_cdc_account_balance_entry_positional(fc::rpc::json_connection* json_connection, const fc::variants& parameters)
		{
			// this method has no prerequisites

			if (parameters.size() <= 0)
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 1 (block_num)");
			uint32_t block_num = parameters[0].as<uint32_t>();

			std::vector<cdcchain::consensus::CdcTrxidBalance> result = get_client()->blockchain_get_cdc_account_balance_entry(block_num);
			return fc::variant(result);
		}

		fc::variant CommonApiRpcServer::blockchain_get_cdc_account_balance_entry_named(fc::rpc::json_connection* json_connection, const fc::variant_object& parameters)
		{
			// this method has no prerequisites

			if (!parameters.contains("block_num"))
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 'block_num'");
			uint32_t block_num = parameters["block_num"].as<uint32_t>();

			std::vector<cdcchain::consensus::CdcTrxidBalance> result = get_client()->blockchain_get_cdc_account_balance_entry(block_num);
			return fc::variant(result);
		}

		fc::variant CommonApiRpcServer::blockchain_generate_issuance_map_positional(fc::rpc::json_connection* json_connection, const fc::variants& parameters)
		{
			// this method has no prerequisites

			if (parameters.size() <= 0)
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 1 (symbol)");
			std::string symbol = parameters[0].as<std::string>();
			if (parameters.size() <= 1)
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 2 (filename)");
			std::string filename = parameters[1].as<std::string>();

			get_client()->blockchain_generate_issuance_map(symbol, filename);
			return fc::variant();
		}

		fc::variant CommonApiRpcServer::blockchain_generate_issuance_map_named(fc::rpc::json_connection* json_connection, const fc::variant_object& parameters)
		{
			// this method has no prerequisites

			if (!parameters.contains("symbol"))
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 'symbol'");
			std::string symbol = parameters["symbol"].as<std::string>();
			if (!parameters.contains("filename"))
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 'filename'");
			std::string filename = parameters["filename"].as<std::string>();

			get_client()->blockchain_generate_issuance_map(symbol, filename);
			return fc::variant();
		}

        fc::variant CommonApiRpcServer::wallet_import_ethereum_private_key_positional(fc::rpc::json_connection* json_connection, const fc::variants& parameters)
        {
            // check all of this method's prerequisites
            verify_json_connection_is_authenticated(json_connection);
            verify_wallet_is_open();
            verify_wallet_is_unlocked();
            // done checking prerequisites

            if (parameters.size() <= 0)
                FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 1 (priv_key_str)");
            std::string priv_key_str = parameters[0].as<std::string>();
            std::string account_name = (parameters.size() <= 1) ?
                (fc::json::from_string("null").as<std::string>()) :
                parameters[1].as<std::string>();
            bool create_new_account = (parameters.size() <= 2) ?
                (fc::json::from_string("false").as<bool>()) :
                parameters[2].as<bool>();
            bool rescan = (parameters.size() <= 3) ?
                (fc::json::from_string("false").as<bool>()) :
                parameters[3].as<bool>();

            std::string result = get_client()->wallet_import_ethereum_private_key(priv_key_str, account_name, create_new_account, rescan);
            return fc::variant(result);
        }

        fc::variant CommonApiRpcServer::wallet_import_ethereum_private_key_named(fc::rpc::json_connection* json_connection, const fc::variant_object& parameters)
        {
            // check all of this method's prerequisites
            verify_json_connection_is_authenticated(json_connection);
            verify_wallet_is_open();
            verify_wallet_is_unlocked();
            // done checking prerequisites

            if (!parameters.contains("priv_key_str"))
                FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 'priv_key_str'");
            std::string priv_key_str = parameters["priv_key_str"].as<std::string>();
            std::string account_name = parameters.contains("account_name") ?
                (fc::json::from_string("null").as<std::string>()) :
                parameters["account_name"].as<std::string>();
            bool create_new_account = parameters.contains("create_new_account") ?
                (fc::json::from_string("false").as<bool>()) :
                parameters["create_new_account"].as<bool>();
            bool rescan = parameters.contains("rescan") ?
                (fc::json::from_string("false").as<bool>()) :
                parameters["rescan"].as<bool>();

            std::string result = get_client()->wallet_import_ethereum_private_key(priv_key_str, account_name, create_new_account, rescan);
            return fc::variant(result);
        }

		fc::variant CommonApiRpcServer::blockchain_calculate_supply_positional(fc::rpc::json_connection* json_connection, const fc::variants& parameters)
		{
			// this method has no prerequisites

			if (parameters.size() <= 0)
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 1 (asset)");
			std::string asset = parameters[0].as<std::string>();

			cdcchain::consensus::Asset result = get_client()->blockchain_calculate_supply(asset);
			return fc::variant(result);
		}

		fc::variant CommonApiRpcServer::blockchain_calculate_supply_named(fc::rpc::json_connection* json_connection, const fc::variant_object& parameters)
		{
			// this method has no prerequisites

			if (!parameters.contains("asset"))
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 'asset'");
			std::string asset = parameters["asset"].as<std::string>();

			cdcchain::consensus::Asset result = get_client()->blockchain_calculate_supply(asset);
			return fc::variant(result);
		}

		fc::variant CommonApiRpcServer::blockchain_is_synced_positional(fc::rpc::json_connection* json_connection, const fc::variants& parameters)
		{
			// this method has no prerequisites


			bool result = get_client()->blockchain_is_synced();
			return fc::variant(result);
		}

		fc::variant CommonApiRpcServer::blockchain_is_synced_named(fc::rpc::json_connection* json_connection, const fc::variant_object& parameters)
		{
			// this method has no prerequisites


			bool result = get_client()->blockchain_is_synced();
			return fc::variant(result);
		}

		fc::variant CommonApiRpcServer::blockchain_get_block_count_positional(fc::rpc::json_connection* json_connection, const fc::variants& parameters)
		{
			// this method has no prerequisites


			uint32_t result = get_client()->blockchain_get_block_count();
			return fc::variant(result);
		}

		fc::variant CommonApiRpcServer::blockchain_get_block_count_named(fc::rpc::json_connection* json_connection, const fc::variant_object& parameters)
		{
			// this method has no prerequisites


			uint32_t result = get_client()->blockchain_get_block_count();
			return fc::variant(result);
		}

		fc::variant CommonApiRpcServer::blockchain_get_security_state_positional(fc::rpc::json_connection* json_connection, const fc::variants& parameters)
		{
			// this method has no prerequisites


			cdcchain::consensus::BlockchainSecurityState result = get_client()->blockchain_get_security_state();
			return fc::variant(result);
		}

		fc::variant CommonApiRpcServer::blockchain_get_security_state_named(fc::rpc::json_connection* json_connection, const fc::variant_object& parameters)
		{
			// this method has no prerequisites


			cdcchain::consensus::BlockchainSecurityState result = get_client()->blockchain_get_security_state();
			return fc::variant(result);
		}

		fc::variant CommonApiRpcServer::blockchain_list_accounts_positional(fc::rpc::json_connection* json_connection, const fc::variants& parameters)
		{
			// this method has no prerequisites

			std::string first_account_name = (parameters.size() <= 0) ?
				(fc::json::from_string("\"\"").as<std::string>()) :
				parameters[0].as<std::string>();
			uint32_t limit = (parameters.size() <= 1) ?
				(fc::json::from_string("20").as<uint32_t>()) :
				parameters[1].as<uint32_t>();

			std::vector<cdcchain::consensus::AccountEntry> result = get_client()->blockchain_list_accounts(first_account_name, limit);
			return fc::variant(result);
		}

		fc::variant CommonApiRpcServer::blockchain_list_accounts_named(fc::rpc::json_connection* json_connection, const fc::variant_object& parameters)
		{
			// this method has no prerequisites

			std::string first_account_name = parameters.contains("first_account_name") ?
				(fc::json::from_string("\"\"").as<std::string>()) :
				parameters["first_account_name"].as<std::string>();
			uint32_t limit = parameters.contains("limit") ?
				(fc::json::from_string("20").as<uint32_t>()) :
				parameters["limit"].as<uint32_t>();

			std::vector<cdcchain::consensus::AccountEntry> result = get_client()->blockchain_list_accounts(first_account_name, limit);
			return fc::variant(result);
		}

		fc::variant CommonApiRpcServer::blockchain_list_recently_updated_accounts_positional(fc::rpc::json_connection* json_connection, const fc::variants& parameters)
		{
			// this method has no prerequisites


			std::vector<cdcchain::consensus::AccountEntry> result = get_client()->blockchain_list_recently_updated_accounts();
			return fc::variant(result);
		}

		fc::variant CommonApiRpcServer::blockchain_list_recently_updated_accounts_named(fc::rpc::json_connection* json_connection, const fc::variant_object& parameters)
		{
			// this method has no prerequisites


			std::vector<cdcchain::consensus::AccountEntry> result = get_client()->blockchain_list_recently_updated_accounts();
			return fc::variant(result);
		}

		fc::variant CommonApiRpcServer::blockchain_list_recently_registered_accounts_positional(fc::rpc::json_connection* json_connection, const fc::variants& parameters)
		{
			// this method has no prerequisites


			std::vector<cdcchain::consensus::AccountEntry> result = get_client()->blockchain_list_recently_registered_accounts();
			return fc::variant(result);
		}

		fc::variant CommonApiRpcServer::blockchain_list_recently_registered_accounts_named(fc::rpc::json_connection* json_connection, const fc::variant_object& parameters)
		{
			// this method has no prerequisites


			std::vector<cdcchain::consensus::AccountEntry> result = get_client()->blockchain_list_recently_registered_accounts();
			return fc::variant(result);
		}

		fc::variant CommonApiRpcServer::blockchain_list_assets_positional(fc::rpc::json_connection* json_connection, const fc::variants& parameters)
		{
			// this method has no prerequisites

			std::string first_symbol = (parameters.size() <= 0) ?
				(fc::json::from_string("\"\"").as<std::string>()) :
				parameters[0].as<std::string>();
			uint32_t limit = (parameters.size() <= 1) ?
				(fc::json::from_string("20").as<uint32_t>()) :
				parameters[1].as<uint32_t>();

			std::vector<cdcchain::consensus::AssetEntry> result = get_client()->blockchain_list_assets(first_symbol, limit);
			return fc::variant(result);
		}

		fc::variant CommonApiRpcServer::blockchain_list_assets_named(fc::rpc::json_connection* json_connection, const fc::variant_object& parameters)
		{
			// this method has no prerequisites

			std::string first_symbol = parameters.contains("first_symbol") ?
				(fc::json::from_string("\"\"").as<std::string>()) :
				parameters["first_symbol"].as<std::string>();
			uint32_t limit = parameters.contains("limit") ?
				(fc::json::from_string("20").as<uint32_t>()) :
				parameters["limit"].as<uint32_t>();

			std::vector<cdcchain::consensus::AssetEntry> result = get_client()->blockchain_list_assets(first_symbol, limit);
			return fc::variant(result);
		}

		fc::variant CommonApiRpcServer::blockchain_list_pending_transactions_positional(fc::rpc::json_connection* json_connection, const fc::variants& parameters)
		{
			// this method has no prerequisites


			std::vector<std::pair<cdcchain::consensus::TransactionIdType, cdcchain::consensus::SignedTransaction>> result = get_client()->blockchain_list_pending_transactions();
			return fc::variant(result);
		}

		fc::variant CommonApiRpcServer::blockchain_list_pending_transactions_named(fc::rpc::json_connection* json_connection, const fc::variant_object& parameters)
		{
			// this method has no prerequisites


			std::vector<std::pair<cdcchain::consensus::TransactionIdType, cdcchain::consensus::SignedTransaction>> result = get_client()->blockchain_list_pending_transactions();
			return fc::variant(result);
		}

		fc::variant CommonApiRpcServer::blockchain_get_transaction_positional(fc::rpc::json_connection* json_connection, const fc::variants& parameters)
		{
			// this method has no prerequisites

			if (parameters.size() <= 0)
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 1 (transaction_id_prefix)");
			std::string transaction_id_prefix = parameters[0].as<std::string>();
			bool exact = (parameters.size() <= 1) ?
				(fc::json::from_string("false").as<bool>()) :
				parameters[1].as<bool>();

			std::pair<cdcchain::consensus::TransactionIdType, cdcchain::consensus::TransactionEntry> result = get_client()->blockchain_get_transaction(transaction_id_prefix, exact);
			return fc::variant(result);
		}

		fc::variant CommonApiRpcServer::blockchain_get_transaction_named(fc::rpc::json_connection* json_connection, const fc::variant_object& parameters)
		{
			// this method has no prerequisites

			if (!parameters.contains("transaction_id_prefix"))
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 'transaction_id_prefix'");
			std::string transaction_id_prefix = parameters["transaction_id_prefix"].as<std::string>();
			bool exact = parameters.contains("exact") ?
				(fc::json::from_string("false").as<bool>()) :
				parameters["exact"].as<bool>();

			std::pair<cdcchain::consensus::TransactionIdType, cdcchain::consensus::TransactionEntry> result = get_client()->blockchain_get_transaction(transaction_id_prefix, exact);
			return fc::variant(result);
		}

		fc::variant CommonApiRpcServer::blockchain_get_pretty_transaction_positional(fc::rpc::json_connection* json_connection, const fc::variants& parameters)
		{
			// this method has no prerequisites

			if (parameters.size() <= 0)
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 1 (transaction_id_prefix)");
			std::string transaction_id_prefix = parameters[0].as<std::string>();
			bool exact = (parameters.size() <= 1) ?
				(fc::json::from_string("false").as<bool>()) :
				parameters[1].as<bool>();

			cdcchain::wallet::PrettyTransaction result = get_client()->blockchain_get_pretty_transaction(transaction_id_prefix, exact);
			return fc::variant(result);
		}

		fc::variant CommonApiRpcServer::blockchain_get_pretty_transaction_named(fc::rpc::json_connection* json_connection, const fc::variant_object& parameters)
		{
			// this method has no prerequisites

			if (!parameters.contains("transaction_id_prefix"))
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 'transaction_id_prefix'");
			std::string transaction_id_prefix = parameters["transaction_id_prefix"].as<std::string>();
			bool exact = parameters.contains("exact") ?
				(fc::json::from_string("false").as<bool>()) :
				parameters["exact"].as<bool>();

			cdcchain::wallet::PrettyTransaction result = get_client()->blockchain_get_pretty_transaction(transaction_id_prefix, exact);
			return fc::variant(result);
		}

		fc::variant CommonApiRpcServer::blockchain_get_pretty_contract_transaction_positional(fc::rpc::json_connection* json_connection, const fc::variants& parameters)
		{
			// this method has no prerequisites

			if (parameters.size() <= 0)
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 1 (transaction_id_prefix)");
			std::string transaction_id_prefix = parameters[0].as<std::string>();
			bool exact = (parameters.size() <= 1) ?
				(fc::json::from_string("false").as<bool>()) :
				parameters[1].as<bool>();

			cdcchain::wallet::PrettyContractTransaction result = get_client()->blockchain_get_pretty_contract_transaction(transaction_id_prefix, exact);
			return fc::variant(result);
		}

		fc::variant CommonApiRpcServer::blockchain_get_pretty_contract_transaction_named(fc::rpc::json_connection* json_connection, const fc::variant_object& parameters)
		{
			// this method has no prerequisites

			if (!parameters.contains("transaction_id_prefix"))
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 'transaction_id_prefix'");
			std::string transaction_id_prefix = parameters["transaction_id_prefix"].as<std::string>();
			bool exact = parameters.contains("exact") ?
				(fc::json::from_string("false").as<bool>()) :
				parameters["exact"].as<bool>();

			cdcchain::wallet::PrettyContractTransaction result = get_client()->blockchain_get_pretty_contract_transaction(transaction_id_prefix, exact);
			return fc::variant(result);
		}

		fc::variant CommonApiRpcServer::blockchain_get_block_positional(fc::rpc::json_connection* json_connection, const fc::variants& parameters)
		{
			// this method has no prerequisites

			if (parameters.size() <= 0)
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 1 (block)");
			std::string block = parameters[0].as<std::string>();

			fc::optional<cdcchain::consensus::BlockEntry> result = get_client()->blockchain_get_block(block);
			return fc::variant(result);
		}

		fc::variant CommonApiRpcServer::blockchain_get_block_named(fc::rpc::json_connection* json_connection, const fc::variant_object& parameters)
		{
			// this method has no prerequisites

			if (!parameters.contains("block"))
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 'block'");
			std::string block = parameters["block"].as<std::string>();

			fc::optional<cdcchain::consensus::BlockEntry> result = get_client()->blockchain_get_block(block);
			return fc::variant(result);
		}

		fc::variant CommonApiRpcServer::blockchain_get_block_transactions_positional(fc::rpc::json_connection* json_connection, const fc::variants& parameters)
		{
			// this method has no prerequisites

			if (parameters.size() <= 0)
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 1 (block)");
			std::string block = parameters[0].as<std::string>();

			std::map<cdcchain::consensus::TransactionIdType, cdcchain::consensus::TransactionEntry> result = get_client()->blockchain_get_block_transactions(block);
			return fc::variant(result);
		}

		fc::variant CommonApiRpcServer::blockchain_get_block_transactions_named(fc::rpc::json_connection* json_connection, const fc::variant_object& parameters)
		{
			// this method has no prerequisites

			if (!parameters.contains("block"))
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 'block'");
			std::string block = parameters["block"].as<std::string>();

			std::map<cdcchain::consensus::TransactionIdType, cdcchain::consensus::TransactionEntry> result = get_client()->blockchain_get_block_transactions(block);
			return fc::variant(result);
		}

		fc::variant CommonApiRpcServer::blockchain_get_account_positional(fc::rpc::json_connection* json_connection, const fc::variants& parameters)
		{
			// this method has no prerequisites

			if (parameters.size() <= 0)
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 1 (account)");
			std::string account = parameters[0].as<std::string>();

			fc::optional<cdcchain::consensus::AccountEntry> result = get_client()->blockchain_get_account(account);
			return fc::variant(result);
		}

		fc::variant CommonApiRpcServer::blockchain_get_account_named(fc::rpc::json_connection* json_connection, const fc::variant_object& parameters)
		{
			// this method has no prerequisites

			if (!parameters.contains("account"))
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 'account'");
			std::string account = parameters["account"].as<std::string>();

			fc::optional<cdcchain::consensus::AccountEntry> result = get_client()->blockchain_get_account(account);
			return fc::variant(result);
		}

		fc::variant CommonApiRpcServer::blockchain_get_slate_positional(fc::rpc::json_connection* json_connection, const fc::variants& parameters)
		{
			// this method has no prerequisites

			if (parameters.size() <= 0)
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 1 (slate)");
			std::string slate = parameters[0].as<std::string>();

			std::map<cdcchain::consensus::AccountIdType, std::string> result = get_client()->blockchain_get_slate(slate);
			return fc::variant(result);
		}

		fc::variant CommonApiRpcServer::blockchain_get_slate_named(fc::rpc::json_connection* json_connection, const fc::variant_object& parameters)
		{
			// this method has no prerequisites

			if (!parameters.contains("slate"))
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 'slate'");
			std::string slate = parameters["slate"].as<std::string>();

			std::map<cdcchain::consensus::AccountIdType, std::string> result = get_client()->blockchain_get_slate(slate);
			return fc::variant(result);
		}

		fc::variant CommonApiRpcServer::blockchain_get_balance_positional(fc::rpc::json_connection* json_connection, const fc::variants& parameters)
		{
			// this method has no prerequisites

			if (parameters.size() <= 0)
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 1 (balance_id)");
			cdcchain::consensus::Address balance_id = parameters[0].as<cdcchain::consensus::Address>();

			cdcchain::consensus::BalanceEntry result = get_client()->blockchain_get_balance(balance_id);
			return fc::variant(result);
		}

		fc::variant CommonApiRpcServer::blockchain_get_balance_named(fc::rpc::json_connection* json_connection, const fc::variant_object& parameters)
		{
			// this method has no prerequisites

			if (!parameters.contains("balance_id"))
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 'balance_id'");
			cdcchain::consensus::Address balance_id = parameters["balance_id"].as<cdcchain::consensus::Address>();

			cdcchain::consensus::BalanceEntry result = get_client()->blockchain_get_balance(balance_id);
			return fc::variant(result);
		}

		fc::variant CommonApiRpcServer::blockchain_list_balances_positional(fc::rpc::json_connection* json_connection, const fc::variants& parameters)
		{
			// this method has no prerequisites

			std::string first_balance_id = (parameters.size() <= 0) ?
				(fc::json::from_string("\"\"").as<std::string>()) :
				parameters[0].as<std::string>();
			uint32_t limit = (parameters.size() <= 1) ?
				(fc::json::from_string("20").as<uint32_t>()) :
				parameters[1].as<uint32_t>();

			std::unordered_map<cdcchain::consensus::BalanceIdType, cdcchain::consensus::BalanceEntry> result = get_client()->blockchain_list_balances(first_balance_id, limit);
			return fc::variant(result);
		}

		fc::variant CommonApiRpcServer::blockchain_list_balances_named(fc::rpc::json_connection* json_connection, const fc::variant_object& parameters)
		{
			// this method has no prerequisites

			std::string first_balance_id = parameters.contains("first_balance_id") ?
				(fc::json::from_string("\"\"").as<std::string>()) :
				parameters["first_balance_id"].as<std::string>();
			uint32_t limit = parameters.contains("limit") ?
				(fc::json::from_string("20").as<uint32_t>()) :
				parameters["limit"].as<uint32_t>();

			std::unordered_map<cdcchain::consensus::BalanceIdType, cdcchain::consensus::BalanceEntry> result = get_client()->blockchain_list_balances(first_balance_id, limit);
			return fc::variant(result);
		}

		fc::variant CommonApiRpcServer::blockchain_list_address_balances_positional(fc::rpc::json_connection* json_connection, const fc::variants& parameters)
		{
			// this method has no prerequisites

			if (parameters.size() <= 0)
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 1 (addr)");
			std::string addr = parameters[0].as<std::string>();
			fc::time_point chanced_since = (parameters.size() <= 1) ?
				(fc::json::from_string("\"1970-1-1T00:00:01\"").as<fc::time_point>()) :
				parameters[1].as<fc::time_point>();

			std::unordered_map<cdcchain::consensus::BalanceIdType, cdcchain::consensus::BalanceEntry> result = get_client()->blockchain_list_address_balances(addr, chanced_since);
			return fc::variant(result);
		}

		fc::variant CommonApiRpcServer::blockchain_list_address_balances_named(fc::rpc::json_connection* json_connection, const fc::variant_object& parameters)
		{
			// this method has no prerequisites

			if (!parameters.contains("addr"))
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 'addr'");
			std::string addr = parameters["addr"].as<std::string>();
			fc::time_point chanced_since = parameters.contains("chanced_since") ?
				(fc::json::from_string("\"1970-1-1T00:00:01\"").as<fc::time_point>()) :
				parameters["chanced_since"].as<fc::time_point>();

			std::unordered_map<cdcchain::consensus::BalanceIdType, cdcchain::consensus::BalanceEntry> result = get_client()->blockchain_list_address_balances(addr, chanced_since);
			return fc::variant(result);
		}

		fc::variant CommonApiRpcServer::blockchain_list_address_transactions_positional(fc::rpc::json_connection* json_connection, const fc::variants& parameters)
		{
			// this method has no prerequisites

			if (parameters.size() <= 0)
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 1 (addr)");
			std::string addr = parameters[0].as<std::string>();
			uint32_t filter_before = (parameters.size() <= 1) ?
				(fc::json::from_string("\"0\"").as<uint32_t>()) :
				parameters[1].as<uint32_t>();

			fc::variant_object result = get_client()->blockchain_list_address_transactions(addr, filter_before);
			return fc::variant(result);
		}

		fc::variant CommonApiRpcServer::blockchain_list_address_transactions_named(fc::rpc::json_connection* json_connection, const fc::variant_object& parameters)
		{
			// this method has no prerequisites

			if (!parameters.contains("addr"))
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 'addr'");
			std::string addr = parameters["addr"].as<std::string>();
			uint32_t filter_before = parameters.contains("filter_before") ?
				(fc::json::from_string("\"0\"").as<uint32_t>()) :
				parameters["filter_before"].as<uint32_t>();

			fc::variant_object result = get_client()->blockchain_list_address_transactions(addr, filter_before);
			return fc::variant(result);
		}

		fc::variant CommonApiRpcServer::blockchain_get_account_public_balance_positional(fc::rpc::json_connection* json_connection, const fc::variants& parameters)
		{
			// check all of this method's prerequisites
			verify_json_connection_is_authenticated(json_connection);
			verify_wallet_is_open();
			// done checking prerequisites

			if (parameters.size() <= 0)
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 1 (account_name)");
			std::string account_name = parameters[0].as<std::string>();

			cdcchain::wallet::AccountBalanceSummaryType result = get_client()->blockchain_get_account_public_balance(account_name);
			return fc::variant(result);
		}

		fc::variant CommonApiRpcServer::blockchain_get_account_public_balance_named(fc::rpc::json_connection* json_connection, const fc::variant_object& parameters)
		{
			// check all of this method's prerequisites
			verify_json_connection_is_authenticated(json_connection);
			verify_wallet_is_open();
			// done checking prerequisites

			if (!parameters.contains("account_name"))
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 'account_name'");
			std::string account_name = parameters["account_name"].as<std::string>();

			cdcchain::wallet::AccountBalanceSummaryType result = get_client()->blockchain_get_account_public_balance(account_name);
			return fc::variant(result);
		}

		fc::variant CommonApiRpcServer::blockchain_list_key_balances_positional(fc::rpc::json_connection* json_connection, const fc::variants& parameters)
		{
			// this method has no prerequisites

			if (parameters.size() <= 0)
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 1 (key)");
			cdcchain::consensus::PublicKeyType key = parameters[0].as<cdcchain::consensus::PublicKeyType>();

			std::unordered_map<cdcchain::consensus::BalanceIdType, cdcchain::consensus::BalanceEntry> result = get_client()->blockchain_list_key_balances(key);
			return fc::variant(result);
		}

		fc::variant CommonApiRpcServer::blockchain_list_key_balances_named(fc::rpc::json_connection* json_connection, const fc::variant_object& parameters)
		{
			// this method has no prerequisites

			if (!parameters.contains("key"))
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 'key'");
			cdcchain::consensus::PublicKeyType key = parameters["key"].as<cdcchain::consensus::PublicKeyType>();

			std::unordered_map<cdcchain::consensus::BalanceIdType, cdcchain::consensus::BalanceEntry> result = get_client()->blockchain_list_key_balances(key);
			return fc::variant(result);
		}

		fc::variant CommonApiRpcServer::blockchain_get_asset_positional(fc::rpc::json_connection* json_connection, const fc::variants& parameters)
		{
			// this method has no prerequisites

			if (parameters.size() <= 0)
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 1 (asset)");
			std::string asset = parameters[0].as<std::string>();

			fc::optional<cdcchain::consensus::AssetEntry> result = get_client()->blockchain_get_asset(asset);
			return fc::variant(result);
		}

		fc::variant CommonApiRpcServer::blockchain_get_asset_named(fc::rpc::json_connection* json_connection, const fc::variant_object& parameters)
		{
			// this method has no prerequisites

			if (!parameters.contains("asset"))
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 'asset'");
			std::string asset = parameters["asset"].as<std::string>();

			fc::optional<cdcchain::consensus::AssetEntry> result = get_client()->blockchain_get_asset(asset);
			return fc::variant(result);
		}

		fc::variant CommonApiRpcServer::blockchain_list_active_delegates_positional(fc::rpc::json_connection* json_connection, const fc::variants& parameters)
		{
			// this method has no prerequisites

			uint32_t first = (parameters.size() <= 0) ?
				(fc::json::from_string("0").as<uint32_t>()) :
            parameters[0].as<uint32_t>();
            uint32_t count = (parameters.size() <= 1) ?
            (fc::json::from_string("20").as<uint32_t>()) :
            parameters[1].as<uint32_t>();

            std::vector<cdcchain::consensus::AccountEntry> result = get_client()->blockchain_list_active_delegates(first, count);
            return fc::variant(result);
        }

        fc::variant CommonApiRpcServer::blockchain_list_active_delegates_named(fc::rpc::json_connection* json_connection, const fc::variant_object& parameters)
        {
            // this method has no prerequisites

            uint32_t first = parameters.contains("first") ?
                (fc::json::from_string("0").as<uint32_t>()) :
                parameters["first"].as<uint32_t>();
            uint32_t count = parameters.contains("count") ?
                (fc::json::from_string("20").as<uint32_t>()) :
                parameters["count"].as<uint32_t>();

            std::vector<cdcchain::consensus::AccountEntry> result = get_client()->blockchain_list_active_delegates(first, count);
            return fc::variant(result);
        }

        fc::variant CommonApiRpcServer::blockchain_list_delegates_positional(fc::rpc::json_connection* json_connection, const fc::variants& parameters)
        {
            // this method has no prerequisites

            uint32_t first = (parameters.size() <= 0) ?
            (fc::json::from_string("0").as<uint32_t>()) :
            parameters[0].as<uint32_t>();
            uint32_t count = (parameters.size() <= 1) ?
            (fc::json::from_string("20").as<uint32_t>()) :
            parameters[1].as<uint32_t>();

			std::vector<cdcchain::consensus::AccountEntry> result = get_client()->blockchain_list_delegates(first, count);
			return fc::variant(result);
		}

		fc::variant CommonApiRpcServer::blockchain_list_delegates_named(fc::rpc::json_connection* json_connection, const fc::variant_object& parameters)
		{
			// this method has no prerequisites

			uint32_t first = parameters.contains("first") ?
                (fc::json::from_string("0").as<uint32_t>()) :
                parameters["first"].as<uint32_t>();
            uint32_t count = parameters.contains("count") ?
                (fc::json::from_string("20").as<uint32_t>()) :
                parameters["count"].as<uint32_t>();

			std::vector<cdcchain::consensus::AccountEntry> result = get_client()->blockchain_list_delegates(first, count);
			return fc::variant(result);
		}

		fc::variant CommonApiRpcServer::blockchain_list_blocks_positional(fc::rpc::json_connection* json_connection, const fc::variants& parameters)
		{
			// this method has no prerequisites

			uint32_t max_block_num = (parameters.size() <= 0) ?
				(fc::json::from_string("-1").as<uint32_t>()) :
				parameters[0].as<uint32_t>();
			uint32_t limit = (parameters.size() <= 1) ?
				(fc::json::from_string("20").as<uint32_t>()) :
				parameters[1].as<uint32_t>();

			std::vector<cdcchain::consensus::BlockEntry> result = get_client()->blockchain_list_blocks(max_block_num, limit);
			return fc::variant(result);
		}

		fc::variant CommonApiRpcServer::blockchain_list_blocks_named(fc::rpc::json_connection* json_connection, const fc::variant_object& parameters)
		{
			// this method has no prerequisites

			uint32_t max_block_num = parameters.contains("max_block_num") ?
				(fc::json::from_string("-1").as<uint32_t>()) :
				parameters["max_block_num"].as<uint32_t>();
			uint32_t limit = parameters.contains("limit") ?
				(fc::json::from_string("20").as<uint32_t>()) :
				parameters["limit"].as<uint32_t>();

			std::vector<cdcchain::consensus::BlockEntry> result = get_client()->blockchain_list_blocks(max_block_num, limit);
			return fc::variant(result);
		}

		fc::variant CommonApiRpcServer::blockchain_list_missing_block_delegates_positional(fc::rpc::json_connection* json_connection, const fc::variants& parameters)
		{
			// this method has no prerequisites

			if (parameters.size() <= 0)
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 1 (block_number)");
			uint32_t block_number = parameters[0].as<uint32_t>();

			std::vector<std::string> result = get_client()->blockchain_list_missing_block_delegates(block_number);
			return fc::variant(result);
		}

		fc::variant CommonApiRpcServer::blockchain_list_missing_block_delegates_named(fc::rpc::json_connection* json_connection, const fc::variant_object& parameters)
		{
			// this method has no prerequisites

			if (!parameters.contains("block_number"))
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 'block_number'");
			uint32_t block_number = parameters["block_number"].as<uint32_t>();

			std::vector<std::string> result = get_client()->blockchain_list_missing_block_delegates(block_number);
			return fc::variant(result);
		}

		fc::variant CommonApiRpcServer::blockchain_export_fork_graph_positional(fc::rpc::json_connection* json_connection, const fc::variants& parameters)
		{
			// this method has no prerequisites

			uint32_t start_block = (parameters.size() <= 0) ?
				(fc::json::from_string("1").as<uint32_t>()) :
				parameters[0].as<uint32_t>();
			uint32_t end_block = (parameters.size() <= 1) ?
				(fc::json::from_string("-1").as<uint32_t>()) :
				parameters[1].as<uint32_t>();
			cdcchain::consensus::FilePath filename = (parameters.size() <= 2) ?
				(fc::json::from_string("\"\"").as<cdcchain::consensus::FilePath>()) :
				parameters[2].as<cdcchain::consensus::FilePath>();

			std::string result = get_client()->blockchain_export_fork_graph(start_block, end_block, filename);
			return fc::variant(result);
		}

		fc::variant CommonApiRpcServer::blockchain_export_fork_graph_named(fc::rpc::json_connection* json_connection, const fc::variant_object& parameters)
		{
			// this method has no prerequisites

			uint32_t start_block = parameters.contains("start_block") ?
				(fc::json::from_string("1").as<uint32_t>()) :
				parameters["start_block"].as<uint32_t>();
			uint32_t end_block = parameters.contains("end_block") ?
				(fc::json::from_string("-1").as<uint32_t>()) :
				parameters["end_block"].as<uint32_t>();
			cdcchain::consensus::FilePath filename = parameters.contains("filename") ?
				(fc::json::from_string("\"\"").as<cdcchain::consensus::FilePath>()) :
				parameters["filename"].as<cdcchain::consensus::FilePath>();

			std::string result = get_client()->blockchain_export_fork_graph(start_block, end_block, filename);
			return fc::variant(result);
		}

		fc::variant CommonApiRpcServer::blockchain_list_forks_positional(fc::rpc::json_connection* json_connection, const fc::variants& parameters)
		{
			// this method has no prerequisites


			std::map<uint32_t, std::vector<cdcchain::consensus::ForkEntry>> result = get_client()->blockchain_list_forks();
			return fc::variant(result);
		}

		fc::variant CommonApiRpcServer::blockchain_list_forks_named(fc::rpc::json_connection* json_connection, const fc::variant_object& parameters)
		{
			// this method has no prerequisites


			std::map<uint32_t, std::vector<cdcchain::consensus::ForkEntry>> result = get_client()->blockchain_list_forks();
			return fc::variant(result);
		}

		fc::variant CommonApiRpcServer::blockchain_get_delegate_slot_entrys_positional(fc::rpc::json_connection* json_connection, const fc::variants& parameters)
		{
			// this method has no prerequisites

			if (parameters.size() <= 0)
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 1 (delegate_name)");
			std::string delegate_name = parameters[0].as<std::string>();
			uint32_t limit = (parameters.size() <= 1) ?
				(fc::json::from_string("\"10\"").as<uint32_t>()) :
				parameters[1].as<uint32_t>();

			std::vector<cdcchain::consensus::SlotEntry> result = get_client()->blockchain_get_delegate_slot_entrys(delegate_name, limit);
			return fc::variant(result);
		}

		fc::variant CommonApiRpcServer::blockchain_get_delegate_slot_entrys_named(fc::rpc::json_connection* json_connection, const fc::variant_object& parameters)
		{
			// this method has no prerequisites

			if (!parameters.contains("delegate_name"))
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 'delegate_name'");
			std::string delegate_name = parameters["delegate_name"].as<std::string>();
			uint32_t limit = parameters.contains("limit") ?
				(fc::json::from_string("\"10\"").as<uint32_t>()) :
				parameters["limit"].as<uint32_t>();

			std::vector<cdcchain::consensus::SlotEntry> result = get_client()->blockchain_get_delegate_slot_entrys(delegate_name, limit);
			return fc::variant(result);
		}

		fc::variant CommonApiRpcServer::blockchain_get_block_signee_positional(fc::rpc::json_connection* json_connection, const fc::variants& parameters)
		{
			// this method has no prerequisites

			if (parameters.size() <= 0)
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 1 (block)");
			std::string block = parameters[0].as<std::string>();

			std::string result = get_client()->blockchain_get_block_signee(block);
			return fc::variant(result);
		}

		fc::variant CommonApiRpcServer::blockchain_get_block_signee_named(fc::rpc::json_connection* json_connection, const fc::variant_object& parameters)
		{
			// this method has no prerequisites

			if (!parameters.contains("block"))
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 'block'");
			std::string block = parameters["block"].as<std::string>();

			std::string result = get_client()->blockchain_get_block_signee(block);
			return fc::variant(result);
		}

		fc::variant CommonApiRpcServer::blockchain_unclaimed_genesis_positional(fc::rpc::json_connection* json_connection, const fc::variants& parameters)
		{
			// this method has no prerequisites


			cdcchain::consensus::Asset result = get_client()->blockchain_unclaimed_genesis();
			return fc::variant(result);
		}

		fc::variant CommonApiRpcServer::blockchain_unclaimed_genesis_named(fc::rpc::json_connection* json_connection, const fc::variant_object& parameters)
		{
			// this method has no prerequisites


			cdcchain::consensus::Asset result = get_client()->blockchain_unclaimed_genesis();
			return fc::variant(result);
		}

		fc::variant CommonApiRpcServer::blockchain_verify_signature_positional(fc::rpc::json_connection* json_connection, const fc::variants& parameters)
		{
			// this method has no prerequisites

			if (parameters.size() <= 0)
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 1 (signer)");
			std::string signer = parameters[0].as<std::string>();
			if (parameters.size() <= 1)
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 2 (hash)");
			fc::sha256 hash = parameters[1].as<fc::sha256>();
			if (parameters.size() <= 2)
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 3 (signature)");
			fc::ecc::compact_signature signature = parameters[2].as<fc::ecc::compact_signature>();

			bool result = get_client()->blockchain_verify_signature(signer, hash, signature);
			return fc::variant(result);
		}

		fc::variant CommonApiRpcServer::blockchain_verify_signature_named(fc::rpc::json_connection* json_connection, const fc::variant_object& parameters)
		{
			// this method has no prerequisites

			if (!parameters.contains("signer"))
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 'signer'");
			std::string signer = parameters["signer"].as<std::string>();
			if (!parameters.contains("hash"))
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 'hash'");
			fc::sha256 hash = parameters["hash"].as<fc::sha256>();
			if (!parameters.contains("signature"))
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 'signature'");
			fc::ecc::compact_signature signature = parameters["signature"].as<fc::ecc::compact_signature>();

			bool result = get_client()->blockchain_verify_signature(signer, hash, signature);
			return fc::variant(result);
		}

		fc::variant CommonApiRpcServer::blockchain_dump_state_positional(fc::rpc::json_connection* json_connection, const fc::variants& parameters)
		{
			// this method has no prerequisites

			if (parameters.size() <= 0)
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 1 (path)");
			std::string path = parameters[0].as<std::string>();

			get_client()->blockchain_dump_state(path);
			return fc::variant();
		}

		fc::variant CommonApiRpcServer::blockchain_dump_state_named(fc::rpc::json_connection* json_connection, const fc::variant_object& parameters)
		{
			// this method has no prerequisites

			if (!parameters.contains("path"))
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 'path'");
			std::string path = parameters["path"].as<std::string>();

			get_client()->blockchain_dump_state(path);
			return fc::variant();
		}

		fc::variant CommonApiRpcServer::blockchain_broadcast_transaction_positional(fc::rpc::json_connection* json_connection, const fc::variants& parameters)
		{
			// this method has no prerequisites

			if (parameters.size() <= 0)
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 1 (trx)");
			cdcchain::consensus::SignedTransaction trx = parameters[0].as<cdcchain::consensus::SignedTransaction>();

			get_client()->blockchain_broadcast_transaction(trx);
			return fc::variant();
		}

		fc::variant CommonApiRpcServer::blockchain_broadcast_transaction_named(fc::rpc::json_connection* json_connection, const fc::variant_object& parameters)
		{
			// this method has no prerequisites

			if (!parameters.contains("trx"))
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 'trx'");
			cdcchain::consensus::SignedTransaction trx = parameters["trx"].as<cdcchain::consensus::SignedTransaction>();

			get_client()->blockchain_broadcast_transaction(trx);
			return fc::variant();
		}

		fc::variant CommonApiRpcServer::blockchain_btc_address_convert_positional(fc::rpc::json_connection* json_connection, const fc::variants& parameters)
		{
			// this method has no prerequisites

			if (parameters.size() <= 0)
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 1 (path)");
			std::string path = parameters[0].as<std::string>();

			get_client()->blockchain_btc_address_convert(path);
			return fc::variant();
		}

		fc::variant CommonApiRpcServer::blockchain_btc_address_convert_named(fc::rpc::json_connection* json_connection, const fc::variant_object& parameters)
		{
			// this method has no prerequisites

			if (!parameters.contains("path"))
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 'path'");
			std::string path = parameters["path"].as<std::string>();

			get_client()->blockchain_btc_address_convert(path);
			return fc::variant();
		}

		fc::variant CommonApiRpcServer::blockchain_get_transaction_rpc_positional(fc::rpc::json_connection* json_connection, const fc::variants& parameters)
		{
			try {
				// this method has no prerequisites

				if (parameters.size() <= 0)
					FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 1 (transaction_id_prefix)");
				std::string transaction_id_prefix = parameters[0].as<std::string>();
				bool exact = (parameters.size() <= 1) ?
					(fc::json::from_string("false").as<bool>()) :
					parameters[1].as<bool>();

				std::string result = get_client()->blockchain_get_transaction_rpc(transaction_id_prefix, exact);
				return fc::variant(result);
			}
			catch (fc::exception er)
			{
				std::string result = "{\"result\":\"ERROR\",\"message\":\"" + er.to_string() + "\"}";
				return fc::variant(result);
			}

		}
		fc::variant CommonApiRpcServer::blockchain_get_transaction_rpc_named(fc::rpc::json_connection* json_connection, const fc::variant_object& parameters)
		{
			try
			{
				// this method has no prerequisites

				if (!parameters.contains("transaction_id_prefix"))
					FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 'transaction_id_prefix'");
				std::string transaction_id_prefix = parameters["transaction_id_prefix"].as<std::string>();
				bool exact = parameters.contains("exact") ?
					(fc::json::from_string("false").as<bool>()) :
					parameters["exact"].as<bool>();

				std::string result = get_client()->blockchain_get_transaction_rpc(transaction_id_prefix, exact);
				return fc::variant(result);
			}
			catch (fc::exception er)
			{
				std::string result = "{\"result\":\"ERROR\",\"message\":\"\"}";
				return fc::variant(result);
			}
		}

		fc::variant CommonApiRpcServer::blockchain_set_node_vm_enabled_positional(fc::rpc::json_connection* json_connection, const fc::variants& parameters)
		{
			// this method has no prerequisites

			if (parameters.size() <= 0)
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 1 (enabled)");
			bool enabled = parameters[0].as<bool>();

			get_client()->blockchain_set_node_vm_enabled(enabled);
			return fc::variant();
		}

		fc::variant CommonApiRpcServer::blockchain_set_node_vm_enabled_named(fc::rpc::json_connection* json_connection, const fc::variant_object& parameters)
		{
			// this method has no prerequisites

			if (!parameters.contains("enabled"))
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 'enabled'");
			bool enabled = parameters["enabled"].as<bool>();

			get_client()->blockchain_set_node_vm_enabled(enabled);
			return fc::variant();
		}

		fc::variant CommonApiRpcServer::blockchain_get_node_vm_enabled_positional(fc::rpc::json_connection* json_connection, const fc::variants& parameters)
		{
			// this method has no prerequisites


			bool result = get_client()->blockchain_get_node_vm_enabled();
			return fc::variant(result);
		}

		fc::variant CommonApiRpcServer::blockchain_get_node_vm_enabled_named(fc::rpc::json_connection* json_connection, const fc::variant_object& parameters)
		{
			// this method has no prerequisites


			bool result = get_client()->blockchain_get_node_vm_enabled();
			return fc::variant(result);
		}

		fc::variant CommonApiRpcServer::blockchain_get_all_contracts_positional(fc::rpc::json_connection* json_connection, const fc::variants& parameters)
		{
			// this method has no prerequisites


			vector<string> result = get_client()->blockchain_get_all_contracts();
			return fc::variant(result);
		}

		fc::variant CommonApiRpcServer::blockchain_get_all_contracts_named(fc::rpc::json_connection* json_connection, const fc::variant_object& parameters)
		{
			// this method has no prerequisites


			vector<string> result = get_client()->blockchain_get_all_contracts();
			return fc::variant(result);
		}

		fc::variant CommonApiRpcServer::blockchain_get_forever_contracts_positional(fc::rpc::json_connection* json_connection, const fc::variants& parameters)
		{
			// this method has no prerequisites


			unordered_map<string, string> result = get_client()->blockchain_get_forever_contracts();
			return fc::variant(result);
		}

		fc::variant CommonApiRpcServer::blockchain_get_forever_contracts_named(fc::rpc::json_connection* json_connection, const fc::variant_object& parameters)
		{
			// this method has no prerequisites


			unordered_map<string, string> result = get_client()->blockchain_get_forever_contracts();
			return fc::variant(result);
		}

		fc::variant CommonApiRpcServer::blockchain_list_pub_all_address_positional(fc::rpc::json_connection* json_connection, const fc::variants& parameters)
		{
			// this method has no prerequisites

			if (parameters.size() <= 0)
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 1 (pub_key)");
			std::string pub_key = parameters[0].as<std::string>();

			std::vector<std::string> result = get_client()->blockchain_list_pub_all_address(pub_key);
			return fc::variant(result);
		}

		fc::variant CommonApiRpcServer::blockchain_list_pub_all_address_named(fc::rpc::json_connection* json_connection, const fc::variant_object& parameters)
		{
			// this method has no prerequisites

			if (!parameters.contains("pub_key"))
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 'pub_key'");
			std::string pub_key = parameters["pub_key"].as<std::string>();

			std::vector<std::string> result = get_client()->blockchain_list_pub_all_address(pub_key);
			return fc::variant(result);
		}

		fc::variant CommonApiRpcServer::blockchain_list_contract_transaction_history_positional(fc::rpc::json_connection* json_connection, const fc::variants& parameters)
		{
			// this method has no prerequisites

			if (parameters.size() <= 0)
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 1 (from_block_num)");
			uint32_t from_block_num = parameters[0].as<uint32_t>();
			if (parameters.size() <= 1)
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 2 (block_count)");
			uint32_t block_count = parameters[1].as<uint32_t>();
			std::string contract_id = (parameters.size() <= 2) ?
				(fc::json::from_string("\"\"").as<std::string>()) :
				parameters[2].as<std::string>();
			uint32_t trx_type = (parameters.size() <= 3) ?
				(fc::json::from_string("\"99\"").as<uint32_t>()) :
				parameters[3].as<uint32_t>();
			std::string call_method = (parameters.size() <= 4) ?
				(fc::json::from_string("\"\"").as<std::string>()) :
				parameters[4].as<std::string>();

			std::vector<cdcchain::wallet::ContractTransactionSummary> result = get_client()->blockchain_list_contract_transaction_history(from_block_num, block_count, contract_id, trx_type, call_method);
			return fc::variant(result);
		}

		fc::variant CommonApiRpcServer::blockchain_list_contract_transaction_history_named(fc::rpc::json_connection* json_connection, const fc::variant_object& parameters)
		{
			// this method has no prerequisites

			if (!parameters.contains("from_block_num"))
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 'from_block_num'");
			uint32_t from_block_num = parameters["from_block_num"].as<uint32_t>();
			if (!parameters.contains("block_count"))
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 'block_count'");
			uint32_t block_count = parameters["block_count"].as<uint32_t>();
			std::string contract_id = parameters.contains("contract_id") ?
				(fc::json::from_string("\"\"").as<std::string>()) :
				parameters["contract_id"].as<std::string>();
			uint32_t trx_type = parameters.contains("trx_type") ?
				(fc::json::from_string("\"99\"").as<uint32_t>()) :
				parameters["trx_type"].as<uint32_t>();
			std::string call_method = parameters.contains("call_method") ?
				(fc::json::from_string("\"\"").as<std::string>()) :
				parameters["call_method"].as<std::string>();

			std::vector<cdcchain::wallet::ContractTransactionSummary> result = get_client()->blockchain_list_contract_transaction_history(from_block_num, block_count, contract_id, trx_type, call_method);
			return fc::variant(result);
		}

		fc::variant CommonApiRpcServer::network_add_node_positional(fc::rpc::json_connection* json_connection, const fc::variants& parameters)
		{
			// check all of this method's prerequisites
			verify_json_connection_is_authenticated(json_connection);
			// done checking prerequisites

			if (parameters.size() <= 0)
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 1 (node)");
			std::string node = parameters[0].as<std::string>();
			std::string command = (parameters.size() <= 1) ?
				(fc::json::from_string("\"add\"").as<std::string>()) :
				parameters[1].as<std::string>();

			get_client()->network_add_node(node, command);
			return fc::variant();
		}

		fc::variant CommonApiRpcServer::network_add_node_named(fc::rpc::json_connection* json_connection, const fc::variant_object& parameters)
		{
			// check all of this method's prerequisites
			verify_json_connection_is_authenticated(json_connection);
			// done checking prerequisites

			if (!parameters.contains("node"))
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 'node'");
			std::string node = parameters["node"].as<std::string>();
			std::string command = parameters.contains("command") ?
				(fc::json::from_string("\"add\"").as<std::string>()) :
				parameters["command"].as<std::string>();

			get_client()->network_add_node(node, command);
			return fc::variant();
		}

		fc::variant CommonApiRpcServer::network_get_connection_count_positional(fc::rpc::json_connection* json_connection, const fc::variants& parameters)
		{
			// check all of this method's prerequisites
			verify_json_connection_is_authenticated(json_connection);
			// done checking prerequisites


			uint32_t result = get_client()->network_get_connection_count();
			return fc::variant(result);
		}

		fc::variant CommonApiRpcServer::network_get_connection_count_named(fc::rpc::json_connection* json_connection, const fc::variant_object& parameters)
		{
			// check all of this method's prerequisites
			verify_json_connection_is_authenticated(json_connection);
			// done checking prerequisites


			uint32_t result = get_client()->network_get_connection_count();
			return fc::variant(result);
		}

		fc::variant CommonApiRpcServer::network_get_peer_info_positional(fc::rpc::json_connection* json_connection, const fc::variants& parameters)
		{
			// check all of this method's prerequisites
			verify_json_connection_is_authenticated(json_connection);
			// done checking prerequisites

			bool not_firewalled = (parameters.size() <= 0) ?
				(fc::json::from_string("false").as<bool>()) :
				parameters[0].as<bool>();

			std::vector<fc::variant_object> result = get_client()->network_get_peer_info(not_firewalled);
			return fc::variant(result);
		}

		fc::variant CommonApiRpcServer::network_get_peer_info_named(fc::rpc::json_connection* json_connection, const fc::variant_object& parameters)
		{
			// check all of this method's prerequisites
			verify_json_connection_is_authenticated(json_connection);
			// done checking prerequisites

			bool not_firewalled = parameters.contains("not_firewalled") ?
				(fc::json::from_string("false").as<bool>()) :
				parameters["not_firewalled"].as<bool>();

			std::vector<fc::variant_object> result = get_client()->network_get_peer_info(not_firewalled);
			return fc::variant(result);
		}

		fc::variant CommonApiRpcServer::network_broadcast_transaction_positional(fc::rpc::json_connection* json_connection, const fc::variants& parameters)
		{
			// check all of this method's prerequisites
			verify_json_connection_is_authenticated(json_connection);
			verify_connected_to_network();
			// done checking prerequisites

			if (parameters.size() <= 0)
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 1 (transaction_to_broadcast)");
			cdcchain::consensus::SignedTransaction transaction_to_broadcast = parameters[0].as<cdcchain::consensus::SignedTransaction>();

			cdcchain::consensus::TransactionIdType result = get_client()->network_broadcast_transaction(transaction_to_broadcast);
			return fc::variant(result);
		}

		fc::variant CommonApiRpcServer::network_broadcast_transaction_named(fc::rpc::json_connection* json_connection, const fc::variant_object& parameters)
		{
			// check all of this method's prerequisites
			verify_json_connection_is_authenticated(json_connection);
			verify_connected_to_network();
			// done checking prerequisites

			if (!parameters.contains("transaction_to_broadcast"))
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 'transaction_to_broadcast'");
			cdcchain::consensus::SignedTransaction transaction_to_broadcast = parameters["transaction_to_broadcast"].as<cdcchain::consensus::SignedTransaction>();

			cdcchain::consensus::TransactionIdType result = get_client()->network_broadcast_transaction(transaction_to_broadcast);
			return fc::variant(result);
		}

		fc::variant CommonApiRpcServer::network_set_advanced_node_parameters_positional(fc::rpc::json_connection* json_connection, const fc::variants& parameters)
		{
			// check all of this method's prerequisites
			verify_json_connection_is_authenticated(json_connection);
			// done checking prerequisites

			if (parameters.size() <= 0)
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 1 (params)");
			fc::variant_object params = parameters[0].as<fc::variant_object>();

			get_client()->network_set_advanced_node_parameters(params);
			return fc::variant();
		}

		fc::variant CommonApiRpcServer::network_set_advanced_node_parameters_named(fc::rpc::json_connection* json_connection, const fc::variant_object& parameters)
		{
			// check all of this method's prerequisites
			verify_json_connection_is_authenticated(json_connection);
			// done checking prerequisites

			if (!parameters.contains("params"))
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 'params'");
			fc::variant_object params = parameters["params"].as<fc::variant_object>();

			get_client()->network_set_advanced_node_parameters(params);
			return fc::variant();
		}

		fc::variant CommonApiRpcServer::network_get_advanced_node_parameters_positional(fc::rpc::json_connection* json_connection, const fc::variants& parameters)
		{
			// check all of this method's prerequisites
			verify_json_connection_is_authenticated(json_connection);
			// done checking prerequisites


			fc::variant_object result = get_client()->network_get_advanced_node_parameters();
			return fc::variant(result);
		}

		fc::variant CommonApiRpcServer::network_get_advanced_node_parameters_named(fc::rpc::json_connection* json_connection, const fc::variant_object& parameters)
		{
			// check all of this method's prerequisites
			verify_json_connection_is_authenticated(json_connection);
			// done checking prerequisites


			fc::variant_object result = get_client()->network_get_advanced_node_parameters();
			return fc::variant(result);
		}

		fc::variant CommonApiRpcServer::network_get_transaction_propagation_data_positional(fc::rpc::json_connection* json_connection, const fc::variants& parameters)
		{
			// check all of this method's prerequisites
			verify_json_connection_is_authenticated(json_connection);
			// done checking prerequisites

			if (parameters.size() <= 0)
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 1 (transaction_id)");
			cdcchain::consensus::TransactionIdType transaction_id = parameters[0].as<cdcchain::consensus::TransactionIdType>();

			cdcchain::network::MessagePropagationData result = get_client()->network_get_transaction_propagation_data(transaction_id);
			return fc::variant(result);
		}

		fc::variant CommonApiRpcServer::network_get_transaction_propagation_data_named(fc::rpc::json_connection* json_connection, const fc::variant_object& parameters)
		{
			// check all of this method's prerequisites
			verify_json_connection_is_authenticated(json_connection);
			// done checking prerequisites

			if (!parameters.contains("transaction_id"))
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 'transaction_id'");
			cdcchain::consensus::TransactionIdType transaction_id = parameters["transaction_id"].as<cdcchain::consensus::TransactionIdType>();

			cdcchain::network::MessagePropagationData result = get_client()->network_get_transaction_propagation_data(transaction_id);
			return fc::variant(result);
		}

		fc::variant CommonApiRpcServer::network_get_block_propagation_data_positional(fc::rpc::json_connection* json_connection, const fc::variants& parameters)
		{
			// check all of this method's prerequisites
			verify_json_connection_is_authenticated(json_connection);
			// done checking prerequisites

			if (parameters.size() <= 0)
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 1 (block_hash)");
			cdcchain::consensus::BlockIdType block_hash = parameters[0].as<cdcchain::consensus::BlockIdType>();

			cdcchain::network::MessagePropagationData result = get_client()->network_get_block_propagation_data(block_hash);
			return fc::variant(result);
		}

		fc::variant CommonApiRpcServer::network_get_block_propagation_data_named(fc::rpc::json_connection* json_connection, const fc::variant_object& parameters)
		{
			// check all of this method's prerequisites
			verify_json_connection_is_authenticated(json_connection);
			// done checking prerequisites

			if (!parameters.contains("block_hash"))
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 'block_hash'");
			cdcchain::consensus::BlockIdType block_hash = parameters["block_hash"].as<cdcchain::consensus::BlockIdType>();

			cdcchain::network::MessagePropagationData result = get_client()->network_get_block_propagation_data(block_hash);
			return fc::variant(result);
		}

		fc::variant CommonApiRpcServer::network_get_info_positional(fc::rpc::json_connection* json_connection, const fc::variants& parameters)
		{
			// check all of this method's prerequisites
			verify_json_connection_is_authenticated(json_connection);
			// done checking prerequisites


			fc::variant_object result = get_client()->network_get_info();
			return fc::variant(result);
		}

		fc::variant CommonApiRpcServer::network_get_info_named(fc::rpc::json_connection* json_connection, const fc::variant_object& parameters)
		{
			// check all of this method's prerequisites
			verify_json_connection_is_authenticated(json_connection);
			// done checking prerequisites


			fc::variant_object result = get_client()->network_get_info();
			return fc::variant(result);
		}

		fc::variant CommonApiRpcServer::network_list_potential_peers_positional(fc::rpc::json_connection* json_connection, const fc::variants& parameters)
		{
			// check all of this method's prerequisites
			verify_json_connection_is_authenticated(json_connection);
			// done checking prerequisites


			std::vector<cdcchain::network::PotentialPeerEntry> result = get_client()->network_list_potential_peers();
			return fc::variant(result);
		}

		fc::variant CommonApiRpcServer::network_list_potential_peers_named(fc::rpc::json_connection* json_connection, const fc::variant_object& parameters)
		{
			// check all of this method's prerequisites
			verify_json_connection_is_authenticated(json_connection);
			// done checking prerequisites


			std::vector<cdcchain::network::PotentialPeerEntry> result = get_client()->network_list_potential_peers();
			return fc::variant(result);
		}

		fc::variant CommonApiRpcServer::network_get_upnp_info_positional(fc::rpc::json_connection* json_connection, const fc::variants& parameters)
		{
			// check all of this method's prerequisites
			verify_json_connection_is_authenticated(json_connection);
			// done checking prerequisites


			fc::variant_object result = get_client()->network_get_upnp_info();
			return fc::variant(result);
		}

		fc::variant CommonApiRpcServer::network_get_upnp_info_named(fc::rpc::json_connection* json_connection, const fc::variant_object& parameters)
		{
			// check all of this method's prerequisites
			verify_json_connection_is_authenticated(json_connection);
			// done checking prerequisites


			fc::variant_object result = get_client()->network_get_upnp_info();
			return fc::variant(result);
		}

		fc::variant CommonApiRpcServer::network_get_blocked_ips_positional(fc::rpc::json_connection* json_connection, const fc::variants& parameters)
		{
			// check all of this method's prerequisites
			verify_json_connection_is_authenticated(json_connection);
			// done checking prerequisites


			std::vector<std::string> result = get_client()->network_get_blocked_ips();
			return fc::variant(result);
		}

		fc::variant CommonApiRpcServer::network_get_blocked_ips_named(fc::rpc::json_connection* json_connection, const fc::variant_object& parameters)
		{
			// check all of this method's prerequisites
			verify_json_connection_is_authenticated(json_connection);
			// done checking prerequisites


			std::vector<std::string> result = get_client()->network_get_blocked_ips();
			return fc::variant(result);
		}

		fc::variant CommonApiRpcServer::debug_get_client_name_positional(fc::rpc::json_connection* json_connection, const fc::variants& parameters)
		{
			// this method has no prerequisites


			std::string result = get_client()->debug_get_client_name();
			return fc::variant(result);
		}

		fc::variant CommonApiRpcServer::debug_get_client_name_named(fc::rpc::json_connection* json_connection, const fc::variant_object& parameters)
		{
			// this method has no prerequisites


			std::string result = get_client()->debug_get_client_name();
			return fc::variant(result);
		}

		fc::variant CommonApiRpcServer::delegate_get_config_positional(fc::rpc::json_connection* json_connection, const fc::variants& parameters)
		{
			// this method has no prerequisites


			fc::variant result = get_client()->delegate_get_config();
			return fc::variant(result);
		}

		fc::variant CommonApiRpcServer::delegate_get_config_named(fc::rpc::json_connection* json_connection, const fc::variant_object& parameters)
		{
			// this method has no prerequisites


			fc::variant result = get_client()->delegate_get_config();
			return fc::variant(result);
		}

		fc::variant CommonApiRpcServer::delegate_set_network_min_connection_count_positional(fc::rpc::json_connection* json_connection, const fc::variants& parameters)
		{
			// this method has no prerequisites

			if (parameters.size() <= 0)
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 1 (count)");
			uint32_t count = parameters[0].as<uint32_t>();

			get_client()->delegate_set_network_min_connection_count(count);
			return fc::variant();
		}

		fc::variant CommonApiRpcServer::delegate_set_network_min_connection_count_named(fc::rpc::json_connection* json_connection, const fc::variant_object& parameters)
		{
			// this method has no prerequisites

			if (!parameters.contains("count"))
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 'count'");
			uint32_t count = parameters["count"].as<uint32_t>();

			get_client()->delegate_set_network_min_connection_count(count);
			return fc::variant();
		}

		fc::variant CommonApiRpcServer::delegate_set_block_max_transaction_count_positional(fc::rpc::json_connection* json_connection, const fc::variants& parameters)
		{
			// this method has no prerequisites

			if (parameters.size() <= 0)
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 1 (count)");
			uint32_t count = parameters[0].as<uint32_t>();

			get_client()->delegate_set_block_max_transaction_count(count);
			return fc::variant();
		}

		fc::variant CommonApiRpcServer::delegate_set_block_max_transaction_count_named(fc::rpc::json_connection* json_connection, const fc::variant_object& parameters)
		{
			// this method has no prerequisites

			if (!parameters.contains("count"))
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 'count'");
			uint32_t count = parameters["count"].as<uint32_t>();

			get_client()->delegate_set_block_max_transaction_count(count);
			return fc::variant();
		}

		fc::variant CommonApiRpcServer::delegate_set_soft_max_imessage_length_positional(fc::rpc::json_connection* json_connection, const fc::variants& parameters)
		{
			// this method has no prerequisites

			if (parameters.size() <= 0)
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 1 (soft_length)");
			int64_t soft_length = parameters[0].as<int64_t>();

			get_client()->delegate_set_soft_max_imessage_length(soft_length);
			return fc::variant();
		}

		fc::variant CommonApiRpcServer::delegate_set_soft_max_imessage_length_named(fc::rpc::json_connection* json_connection, const fc::variant_object& parameters)
		{
			// this method has no prerequisites

			if (!parameters.contains("soft_length"))
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 'soft_length'");
			int64_t soft_length = parameters["soft_length"].as<int64_t>();

			get_client()->delegate_set_soft_max_imessage_length(soft_length);
			return fc::variant();
		}

		fc::variant CommonApiRpcServer::delegate_set_imessage_fee_coe_positional(fc::rpc::json_connection* json_connection, const fc::variants& parameters)
		{
			// this method has no prerequisites

			if (parameters.size() <= 0)
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 1 (fee_coe)");
			std::string fee_coe = parameters[0].as<std::string>();

			get_client()->delegate_set_imessage_fee_coe(fee_coe);
			return fc::variant();
		}

		fc::variant CommonApiRpcServer::delegate_set_imessage_fee_coe_named(fc::rpc::json_connection* json_connection, const fc::variant_object& parameters)
		{
			// this method has no prerequisites

			if (!parameters.contains("fee_coe"))
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 'fee_coe'");
			std::string fee_coe = parameters["fee_coe"].as<std::string>();

			get_client()->delegate_set_imessage_fee_coe(fee_coe);
			return fc::variant();
		}

		fc::variant CommonApiRpcServer::delegate_set_block_max_size_positional(fc::rpc::json_connection* json_connection, const fc::variants& parameters)
		{
			// this method has no prerequisites

			if (parameters.size() <= 0)
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 1 (size)");
			uint32_t size = parameters[0].as<uint32_t>();

			get_client()->delegate_set_block_max_size(size);
			return fc::variant();
		}

		fc::variant CommonApiRpcServer::delegate_set_block_max_size_named(fc::rpc::json_connection* json_connection, const fc::variant_object& parameters)
		{
			// this method has no prerequisites

			if (!parameters.contains("size"))
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 'size'");
			uint32_t size = parameters["size"].as<uint32_t>();

			get_client()->delegate_set_block_max_size(size);
			return fc::variant();
		}

		fc::variant CommonApiRpcServer::delegate_set_transaction_max_size_positional(fc::rpc::json_connection* json_connection, const fc::variants& parameters)
		{
			// this method has no prerequisites

			if (parameters.size() <= 0)
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 1 (size)");
			uint32_t size = parameters[0].as<uint32_t>();

			get_client()->delegate_set_transaction_max_size(size);
			return fc::variant();
		}

		fc::variant CommonApiRpcServer::delegate_set_transaction_max_size_named(fc::rpc::json_connection* json_connection, const fc::variant_object& parameters)
		{
			// this method has no prerequisites

			if (!parameters.contains("size"))
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 'size'");
			uint32_t size = parameters["size"].as<uint32_t>();

			get_client()->delegate_set_transaction_max_size(size);
			return fc::variant();
		}

		fc::variant CommonApiRpcServer::delegate_set_transaction_canonical_signatures_required_positional(fc::rpc::json_connection* json_connection, const fc::variants& parameters)
		{
			// this method has no prerequisites

			if (parameters.size() <= 0)
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 1 (required)");
			bool required = parameters[0].as<bool>();

			get_client()->delegate_set_transaction_canonical_signatures_required(required);
			return fc::variant();
		}

		fc::variant CommonApiRpcServer::delegate_set_transaction_canonical_signatures_required_named(fc::rpc::json_connection* json_connection, const fc::variant_object& parameters)
		{
			// this method has no prerequisites

			if (!parameters.contains("required"))
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 'required'");
			bool required = parameters["required"].as<bool>();

			get_client()->delegate_set_transaction_canonical_signatures_required(required);
			return fc::variant();
		}

		fc::variant CommonApiRpcServer::delegate_set_transaction_min_fee_positional(fc::rpc::json_connection* json_connection, const fc::variants& parameters)
		{
			// this method has no prerequisites

			if (parameters.size() <= 0)
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 1 (fee)");
			std::string fee = parameters[0].as<std::string>();

			get_client()->delegate_set_transaction_min_fee(fee);
			return fc::variant();
		}

		fc::variant CommonApiRpcServer::delegate_set_transaction_min_fee_named(fc::rpc::json_connection* json_connection, const fc::variant_object& parameters)
		{
			// this method has no prerequisites

			if (!parameters.contains("fee"))
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 'fee'");
			std::string fee = parameters["fee"].as<std::string>();

			get_client()->delegate_set_transaction_min_fee(fee);
			return fc::variant();
		}

		fc::variant CommonApiRpcServer::delegate_blacklist_add_transaction_positional(fc::rpc::json_connection* json_connection, const fc::variants& parameters)
		{
			// this method has no prerequisites

			if (parameters.size() <= 0)
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 1 (id)");
			cdcchain::consensus::TransactionIdType id = parameters[0].as<cdcchain::consensus::TransactionIdType>();

			get_client()->delegate_blacklist_add_transaction(id);
			return fc::variant();
		}

		fc::variant CommonApiRpcServer::delegate_blacklist_add_transaction_named(fc::rpc::json_connection* json_connection, const fc::variant_object& parameters)
		{
			// this method has no prerequisites

			if (!parameters.contains("id"))
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 'id'");
			cdcchain::consensus::TransactionIdType id = parameters["id"].as<cdcchain::consensus::TransactionIdType>();

			get_client()->delegate_blacklist_add_transaction(id);
			return fc::variant();
		}

		fc::variant CommonApiRpcServer::delegate_blacklist_remove_transaction_positional(fc::rpc::json_connection* json_connection, const fc::variants& parameters)
		{
			// this method has no prerequisites

			if (parameters.size() <= 0)
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 1 (id)");
			cdcchain::consensus::TransactionIdType id = parameters[0].as<cdcchain::consensus::TransactionIdType>();

			get_client()->delegate_blacklist_remove_transaction(id);
			return fc::variant();
		}

		fc::variant CommonApiRpcServer::delegate_blacklist_remove_transaction_named(fc::rpc::json_connection* json_connection, const fc::variant_object& parameters)
		{
			// this method has no prerequisites

			if (!parameters.contains("id"))
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 'id'");
			cdcchain::consensus::TransactionIdType id = parameters["id"].as<cdcchain::consensus::TransactionIdType>();

			get_client()->delegate_blacklist_remove_transaction(id);
			return fc::variant();
		}

		fc::variant CommonApiRpcServer::delegate_blacklist_add_operation_positional(fc::rpc::json_connection* json_connection, const fc::variants& parameters)
		{
			// this method has no prerequisites

			if (parameters.size() <= 0)
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 1 (id)");
			cdcchain::consensus::OperationTypeEnum id = parameters[0].as<cdcchain::consensus::OperationTypeEnum>();

			get_client()->delegate_blacklist_add_operation(id);
			return fc::variant();
		}

		fc::variant CommonApiRpcServer::delegate_blacklist_add_operation_named(fc::rpc::json_connection* json_connection, const fc::variant_object& parameters)
		{
			// this method has no prerequisites

			if (!parameters.contains("id"))
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 'id'");
			cdcchain::consensus::OperationTypeEnum id = parameters["id"].as<cdcchain::consensus::OperationTypeEnum>();

			get_client()->delegate_blacklist_add_operation(id);
			return fc::variant();
		}

		fc::variant CommonApiRpcServer::delegate_blacklist_remove_operation_positional(fc::rpc::json_connection* json_connection, const fc::variants& parameters)
		{
			// this method has no prerequisites

			if (parameters.size() <= 0)
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 1 (id)");
			cdcchain::consensus::OperationTypeEnum id = parameters[0].as<cdcchain::consensus::OperationTypeEnum>();

			get_client()->delegate_blacklist_remove_operation(id);
			return fc::variant();
		}

		fc::variant CommonApiRpcServer::delegate_blacklist_remove_operation_named(fc::rpc::json_connection* json_connection, const fc::variant_object& parameters)
		{
			// this method has no prerequisites

			if (!parameters.contains("id"))
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 'id'");
			cdcchain::consensus::OperationTypeEnum id = parameters["id"].as<cdcchain::consensus::OperationTypeEnum>();

			get_client()->delegate_blacklist_remove_operation(id);
			return fc::variant();
		}





		fc::variant CommonApiRpcServer::wallet_get_info_positional(fc::rpc::json_connection* json_connection, const fc::variants& parameters)
		{
			// check all of this method's prerequisites
			verify_json_connection_is_authenticated(json_connection);
			// done checking prerequisites


			fc::variant_object result = get_client()->wallet_get_info();
			return fc::variant(result);
		}

		fc::variant CommonApiRpcServer::wallet_get_info_named(fc::rpc::json_connection* json_connection, const fc::variant_object& parameters)
		{
			// check all of this method's prerequisites
			verify_json_connection_is_authenticated(json_connection);
			// done checking prerequisites


			fc::variant_object result = get_client()->wallet_get_info();
			return fc::variant(result);
		}

		fc::variant CommonApiRpcServer::wallet_open_positional(fc::rpc::json_connection* json_connection, const fc::variants& parameters)
		{
			// check all of this method's prerequisites
			verify_json_connection_is_authenticated(json_connection);
			// done checking prerequisites

			if (parameters.size() <= 0)
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 1 (wallet_name)");
			std::string wallet_name = parameters[0].as<std::string>();

			get_client()->wallet_open(wallet_name);
			return fc::variant();
		}

		fc::variant CommonApiRpcServer::wallet_open_named(fc::rpc::json_connection* json_connection, const fc::variant_object& parameters)
		{
			// check all of this method's prerequisites
			verify_json_connection_is_authenticated(json_connection);
			// done checking prerequisites

			if (!parameters.contains("wallet_name"))
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 'wallet_name'");
			std::string wallet_name = parameters["wallet_name"].as<std::string>();

			get_client()->wallet_open(wallet_name);
			return fc::variant();
		}

		fc::variant CommonApiRpcServer::wallet_create_positional(fc::rpc::json_connection* json_connection, const fc::variants& parameters)
		{
			// check all of this method's prerequisites
			verify_json_connection_is_authenticated(json_connection);
			// done checking prerequisites

			if (parameters.size() <= 0)
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 1 (wallet_name)");
			std::string wallet_name = parameters[0].as<std::string>();
			if (parameters.size() <= 1)
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 2 (new_passphrase)");
			std::string new_passphrase = parameters[1].as<std::string>();
			std::string brain_key = (parameters.size() <= 2) ?
				(fc::json::from_string("\"\"").as<std::string>()) :
				parameters[2].as<std::string>();

			get_client()->wallet_create(wallet_name, new_passphrase, brain_key);
			return fc::variant();
		}

		fc::variant CommonApiRpcServer::wallet_create_named(fc::rpc::json_connection* json_connection, const fc::variant_object& parameters)
		{
			// check all of this method's prerequisites
			verify_json_connection_is_authenticated(json_connection);
			// done checking prerequisites

			if (!parameters.contains("wallet_name"))
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 'wallet_name'");
			std::string wallet_name = parameters["wallet_name"].as<std::string>();
			if (!parameters.contains("new_passphrase"))
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 'new_passphrase'");
			std::string new_passphrase = parameters["new_passphrase"].as<std::string>();
			std::string brain_key = parameters.contains("brain_key") ?
				(fc::json::from_string("\"\"").as<std::string>()) :
				parameters["brain_key"].as<std::string>();

			get_client()->wallet_create(wallet_name, new_passphrase, brain_key);
			return fc::variant();
		}

		fc::variant CommonApiRpcServer::wallet_get_name_positional(fc::rpc::json_connection* json_connection, const fc::variants& parameters)
		{
			// this method has no prerequisites


			fc::optional<std::string> result = get_client()->wallet_get_name();
			return fc::variant(result);
		}

		fc::variant CommonApiRpcServer::wallet_get_name_named(fc::rpc::json_connection* json_connection, const fc::variant_object& parameters)
		{
			// this method has no prerequisites


			fc::optional<std::string> result = get_client()->wallet_get_name();
			return fc::variant(result);
		}

		fc::variant CommonApiRpcServer::wallet_import_private_key_positional(fc::rpc::json_connection* json_connection, const fc::variants& parameters)
		{
			// check all of this method's prerequisites
			verify_json_connection_is_authenticated(json_connection);
			verify_wallet_is_open();
			verify_wallet_is_unlocked();
			// done checking prerequisites

			if (parameters.size() <= 0)
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 1 (wif_key)");
			std::string wif_key = parameters[0].as<std::string>();
			std::string account_name = (parameters.size() <= 1) ?
				(fc::json::from_string("null").as<std::string>()) :
				parameters[1].as<std::string>();
			bool create_new_account = (parameters.size() <= 2) ?
				(fc::json::from_string("false").as<bool>()) :
				parameters[2].as<bool>();
			bool rescan = (parameters.size() <= 3) ?
				(fc::json::from_string("false").as<bool>()) :
				parameters[3].as<bool>();

			std::string result = get_client()->wallet_import_private_key(wif_key, account_name, create_new_account, rescan);
			return fc::variant(result);
		}

		fc::variant CommonApiRpcServer::wallet_import_private_key_named(fc::rpc::json_connection* json_connection, const fc::variant_object& parameters)
		{
			// check all of this method's prerequisites
			verify_json_connection_is_authenticated(json_connection);
			verify_wallet_is_open();
			verify_wallet_is_unlocked();
			// done checking prerequisites

			if (!parameters.contains("wif_key"))
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 'wif_key'");
			std::string wif_key = parameters["wif_key"].as<std::string>();
			std::string account_name = parameters.contains("account_name") ?
				(fc::json::from_string("null").as<std::string>()) :
				parameters["account_name"].as<std::string>();
			bool create_new_account = parameters.contains("create_new_account") ?
				(fc::json::from_string("false").as<bool>()) :
				parameters["create_new_account"].as<bool>();
			bool rescan = parameters.contains("rescan") ?
				(fc::json::from_string("false").as<bool>()) :
				parameters["rescan"].as<bool>();

			std::string result = get_client()->wallet_import_private_key(wif_key, account_name, create_new_account, rescan);
			return fc::variant(result);
		}

		fc::variant CommonApiRpcServer::wallet_close_positional(fc::rpc::json_connection* json_connection, const fc::variants& parameters)
		{
			// this method has no prerequisites


			get_client()->wallet_close();
			return fc::variant();
		}

		fc::variant CommonApiRpcServer::wallet_close_named(fc::rpc::json_connection* json_connection, const fc::variant_object& parameters)
		{
			// this method has no prerequisites


			get_client()->wallet_close();
			return fc::variant();
		}

		fc::variant CommonApiRpcServer::wallet_backup_create_positional(fc::rpc::json_connection* json_connection, const fc::variants& parameters)
		{
			// check all of this method's prerequisites
			verify_json_connection_is_authenticated(json_connection);
			verify_wallet_is_open();
			// done checking prerequisites

			if (parameters.size() <= 0)
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 1 (json_filename)");
			fc::path json_filename = parameters[0].as<fc::path>();

			get_client()->wallet_backup_create(json_filename);
			return fc::variant();
		}

		fc::variant CommonApiRpcServer::wallet_backup_create_named(fc::rpc::json_connection* json_connection, const fc::variant_object& parameters)
		{
			// check all of this method's prerequisites
			verify_json_connection_is_authenticated(json_connection);
			verify_wallet_is_open();
			// done checking prerequisites

			if (!parameters.contains("json_filename"))
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 'json_filename'");
			fc::path json_filename = parameters["json_filename"].as<fc::path>();

			get_client()->wallet_backup_create(json_filename);
			return fc::variant();
		}

		fc::variant CommonApiRpcServer::wallet_backup_restore_positional(fc::rpc::json_connection* json_connection, const fc::variants& parameters)
		{
			// check all of this method's prerequisites
			verify_json_connection_is_authenticated(json_connection);
			// done checking prerequisites

			if (parameters.size() <= 0)
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 1 (json_filename)");
			fc::path json_filename = parameters[0].as<fc::path>();
			if (parameters.size() <= 1)
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 2 (wallet_name)");
			std::string wallet_name = parameters[1].as<std::string>();
			if (parameters.size() <= 2)
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 3 (imported_wallet_passphrase)");
			std::string imported_wallet_passphrase = parameters[2].as<std::string>();

			get_client()->wallet_backup_restore(json_filename, wallet_name, imported_wallet_passphrase);
			return fc::variant();
		}

		fc::variant CommonApiRpcServer::wallet_backup_restore_named(fc::rpc::json_connection* json_connection, const fc::variant_object& parameters)
		{
			// check all of this method's prerequisites
			verify_json_connection_is_authenticated(json_connection);
			// done checking prerequisites

			if (!parameters.contains("json_filename"))
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 'json_filename'");
			fc::path json_filename = parameters["json_filename"].as<fc::path>();
			if (!parameters.contains("wallet_name"))
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 'wallet_name'");
			std::string wallet_name = parameters["wallet_name"].as<std::string>();
			if (!parameters.contains("imported_wallet_passphrase"))
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 'imported_wallet_passphrase'");
			std::string imported_wallet_passphrase = parameters["imported_wallet_passphrase"].as<std::string>();

			get_client()->wallet_backup_restore(json_filename, wallet_name, imported_wallet_passphrase);
			return fc::variant();
		}

		fc::variant CommonApiRpcServer::wallet_set_automatic_backups_positional(fc::rpc::json_connection* json_connection, const fc::variants& parameters)
		{
			// check all of this method's prerequisites
			verify_json_connection_is_authenticated(json_connection);
			verify_wallet_is_open();
			// done checking prerequisites

			if (parameters.size() <= 0)
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 1 (enabled)");
			bool enabled = parameters[0].as<bool>();

			bool result = get_client()->wallet_set_automatic_backups(enabled);
			return fc::variant(result);
		}

		fc::variant CommonApiRpcServer::wallet_set_automatic_backups_named(fc::rpc::json_connection* json_connection, const fc::variant_object& parameters)
		{
			// check all of this method's prerequisites
			verify_json_connection_is_authenticated(json_connection);
			verify_wallet_is_open();
			// done checking prerequisites

			if (!parameters.contains("enabled"))
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 'enabled'");
			bool enabled = parameters["enabled"].as<bool>();

			bool result = get_client()->wallet_set_automatic_backups(enabled);
			return fc::variant(result);
		}

		fc::variant CommonApiRpcServer::wallet_set_transaction_expiration_time_positional(fc::rpc::json_connection* json_connection, const fc::variants& parameters)
		{
			// check all of this method's prerequisites
			verify_json_connection_is_authenticated(json_connection);
			verify_wallet_is_open();
			// done checking prerequisites

			if (parameters.size() <= 0)
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 1 (seconds)");
			uint32_t seconds = parameters[0].as<uint32_t>();

			uint32_t result = get_client()->wallet_set_transaction_expiration_time(seconds);
			return fc::variant(result);
		}

		fc::variant CommonApiRpcServer::wallet_set_transaction_expiration_time_named(fc::rpc::json_connection* json_connection, const fc::variant_object& parameters)
		{
			// check all of this method's prerequisites
			verify_json_connection_is_authenticated(json_connection);
			verify_wallet_is_open();
			// done checking prerequisites

			if (!parameters.contains("seconds"))
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 'seconds'");
			uint32_t seconds = parameters["seconds"].as<uint32_t>();

			uint32_t result = get_client()->wallet_set_transaction_expiration_time(seconds);
			return fc::variant(result);
		}

		fc::variant CommonApiRpcServer::wallet_account_transaction_history_positional(fc::rpc::json_connection* json_connection, const fc::variants& parameters)
		{
			// check all of this method's prerequisites
			verify_json_connection_is_authenticated(json_connection);
			verify_wallet_is_open();
			// done checking prerequisites

			std::string account_name = (parameters.size() <= 0) ?
				(fc::json::from_string("\"\"").as<std::string>()) :
				parameters[0].as<std::string>();
			std::string asset_symbol = (parameters.size() <= 1) ?
				(fc::json::from_string("\"\"").as<std::string>()) :
				parameters[1].as<std::string>();
			int32_t limit = (parameters.size() <= 2) ?
				(fc::json::from_string("0").as<int32_t>()) :
				parameters[2].as<int32_t>();
			uint32_t start_block_num = (parameters.size() <= 3) ?
				(fc::json::from_string("0").as<uint32_t>()) :
				parameters[3].as<uint32_t>();
			uint32_t end_block_num = (parameters.size() <= 4) ?
				(fc::json::from_string("-1").as<uint32_t>()) :
				parameters[4].as<uint32_t>();

			std::vector<cdcchain::wallet::PrettyTransaction> result = get_client()->wallet_account_transaction_history(account_name, asset_symbol, limit, start_block_num, end_block_num);
			return fc::variant(result);
		}

		fc::variant CommonApiRpcServer::wallet_account_transaction_history_named(fc::rpc::json_connection* json_connection, const fc::variant_object& parameters)
		{
			// check all of this method's prerequisites
			verify_json_connection_is_authenticated(json_connection);
			verify_wallet_is_open();
			// done checking prerequisites

			std::string account_name = parameters.contains("account_name") ?
				(fc::json::from_string("\"\"").as<std::string>()) :
				parameters["account_name"].as<std::string>();
			std::string asset_symbol = parameters.contains("asset_symbol") ?
				(fc::json::from_string("\"\"").as<std::string>()) :
				parameters["asset_symbol"].as<std::string>();
			int32_t limit = parameters.contains("limit") ?
				(fc::json::from_string("0").as<int32_t>()) :
				parameters["limit"].as<int32_t>();
			uint32_t start_block_num = parameters.contains("start_block_num") ?
				(fc::json::from_string("0").as<uint32_t>()) :
				parameters["start_block_num"].as<uint32_t>();
			uint32_t end_block_num = parameters.contains("end_block_num") ?
				(fc::json::from_string("-1").as<uint32_t>()) :
				parameters["end_block_num"].as<uint32_t>();

			std::vector<cdcchain::wallet::PrettyTransaction> result = get_client()->wallet_account_transaction_history(account_name, asset_symbol, limit, start_block_num, end_block_num);
			return fc::variant(result);
		}

		fc::variant CommonApiRpcServer::wallet_transaction_history_splite_positional(fc::rpc::json_connection* json_connection, const fc::variants& parameters)
		{
			// check all of this method's prerequisites
			verify_json_connection_is_authenticated(json_connection);
			verify_wallet_is_open();
			// done checking prerequisites

			std::string account_name = (parameters.size() <= 0) ?
				(fc::json::from_string("\"\"").as<std::string>()) :
				parameters[0].as<std::string>();
			std::string asset_symbol = (parameters.size() <= 1) ?
				(fc::json::from_string("\"\"").as<std::string>()) :
				parameters[1].as<std::string>();
			int32_t limit = (parameters.size() <= 2) ?
				(fc::json::from_string("0").as<int32_t>()) :
				parameters[2].as<int32_t>();
			int32_t transaction_type = (parameters.size() <= 3) ?
				(fc::json::from_string("\"2\"").as<int32_t>()) :
				parameters[3].as<int32_t>();

			std::vector<cdcchain::wallet::PrettyTransaction> result = get_client()->wallet_transaction_history_splite(account_name, asset_symbol, limit, transaction_type);
			return fc::variant(result);
		}

		fc::variant CommonApiRpcServer::wallet_transaction_history_splite_named(fc::rpc::json_connection* json_connection, const fc::variant_object& parameters)
		{
			// check all of this method's prerequisites
			verify_json_connection_is_authenticated(json_connection);
			verify_wallet_is_open();
			// done checking prerequisites

			std::string account_name = parameters.contains("account_name") ?
				(fc::json::from_string("\"\"").as<std::string>()) :
				parameters["account_name"].as<std::string>();
			std::string asset_symbol = parameters.contains("asset_symbol") ?
				(fc::json::from_string("\"\"").as<std::string>()) :
				parameters["asset_symbol"].as<std::string>();
			int32_t limit = parameters.contains("limit") ?
				(fc::json::from_string("0").as<int32_t>()) :
				parameters["limit"].as<int32_t>();
			int32_t transaction_type = parameters.contains("transaction_type") ?
				(fc::json::from_string("\"2\"").as<int32_t>()) :
				parameters["transaction_type"].as<int32_t>();

			std::vector<cdcchain::wallet::PrettyTransaction> result = get_client()->wallet_transaction_history_splite(account_name, asset_symbol, limit, transaction_type);
			return fc::variant(result);
		}

		fc::variant CommonApiRpcServer::wallet_account_historic_balance_positional(fc::rpc::json_connection* json_connection, const fc::variants& parameters)
		{
			// check all of this method's prerequisites
			verify_json_connection_is_authenticated(json_connection);
			verify_wallet_is_open();
			// done checking prerequisites

			if (parameters.size() <= 0)
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 1 (time)");
			fc::time_point time = parameters[0].as<fc::time_point>();
			std::string account_name = (parameters.size() <= 1) ?
				(fc::json::from_string("\"\"").as<std::string>()) :
				parameters[1].as<std::string>();

			cdcchain::wallet::AccountBalanceSummaryType result = get_client()->wallet_account_historic_balance(time, account_name);
			return fc::variant(result);
		}

		fc::variant CommonApiRpcServer::wallet_account_historic_balance_named(fc::rpc::json_connection* json_connection, const fc::variant_object& parameters)
		{
			// check all of this method's prerequisites
			verify_json_connection_is_authenticated(json_connection);
			verify_wallet_is_open();
			// done checking prerequisites

			if (!parameters.contains("time"))
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 'time'");
			fc::time_point time = parameters["time"].as<fc::time_point>();
			std::string account_name = parameters.contains("account_name") ?
				(fc::json::from_string("\"\"").as<std::string>()) :
				parameters["account_name"].as<std::string>();

			cdcchain::wallet::AccountBalanceSummaryType result = get_client()->wallet_account_historic_balance(time, account_name);
			return fc::variant(result);
		}

		fc::variant CommonApiRpcServer::wallet_remove_transaction_positional(fc::rpc::json_connection* json_connection, const fc::variants& parameters)
		{
			// check all of this method's prerequisites
			verify_json_connection_is_authenticated(json_connection);
			verify_wallet_is_open();
			verify_wallet_is_unlocked();
			// done checking prerequisites

			if (parameters.size() <= 0)
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 1 (transaction_id)");
			std::string transaction_id = parameters[0].as<std::string>();

			get_client()->wallet_remove_transaction(transaction_id);
			return fc::variant();
		}

		fc::variant CommonApiRpcServer::wallet_remove_transaction_named(fc::rpc::json_connection* json_connection, const fc::variant_object& parameters)
		{
			// check all of this method's prerequisites
			verify_json_connection_is_authenticated(json_connection);
			verify_wallet_is_open();
			verify_wallet_is_unlocked();
			// done checking prerequisites

			if (!parameters.contains("transaction_id"))
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 'transaction_id'");
			std::string transaction_id = parameters["transaction_id"].as<std::string>();

			get_client()->wallet_remove_transaction(transaction_id);
			return fc::variant();
		}

		fc::variant CommonApiRpcServer::wallet_get_pending_transaction_errors_positional(fc::rpc::json_connection* json_connection, const fc::variants& parameters)
		{
			// check all of this method's prerequisites
			verify_json_connection_is_authenticated(json_connection);
			verify_wallet_is_open();
			// done checking prerequisites

			cdcchain::consensus::FilePath filename = (parameters.size() <= 0) ?
				(fc::json::from_string("\"\"").as<cdcchain::consensus::FilePath>()) :
				parameters[0].as<cdcchain::consensus::FilePath>();

			std::map<cdcchain::consensus::TransactionIdType, fc::exception> result = get_client()->wallet_get_pending_transaction_errors(filename);
			return fc::variant(result);
		}

		fc::variant CommonApiRpcServer::wallet_get_pending_transaction_errors_named(fc::rpc::json_connection* json_connection, const fc::variant_object& parameters)
		{
			// check all of this method's prerequisites
			verify_json_connection_is_authenticated(json_connection);
			verify_wallet_is_open();
			// done checking prerequisites

			cdcchain::consensus::FilePath filename = parameters.contains("filename") ?
				(fc::json::from_string("\"\"").as<cdcchain::consensus::FilePath>()) :
				parameters["filename"].as<cdcchain::consensus::FilePath>();

			std::map<cdcchain::consensus::TransactionIdType, fc::exception> result = get_client()->wallet_get_pending_transaction_errors(filename);
			return fc::variant(result);
		}

		fc::variant CommonApiRpcServer::wallet_lock_positional(fc::rpc::json_connection* json_connection, const fc::variants& parameters)
		{
			// check all of this method's prerequisites
			verify_json_connection_is_authenticated(json_connection);
			verify_wallet_is_open();
			// done checking prerequisites


			get_client()->wallet_lock();
			return fc::variant();
		}

		fc::variant CommonApiRpcServer::wallet_lock_named(fc::rpc::json_connection* json_connection, const fc::variant_object& parameters)
		{
			// check all of this method's prerequisites
			verify_json_connection_is_authenticated(json_connection);
			verify_wallet_is_open();
			// done checking prerequisites


			get_client()->wallet_lock();
			return fc::variant();
		}

		fc::variant CommonApiRpcServer::wallet_unlock_positional(fc::rpc::json_connection* json_connection, const fc::variants& parameters)
		{
			// check all of this method's prerequisites
			verify_json_connection_is_authenticated(json_connection);
			verify_wallet_is_open();
			// done checking prerequisites

			if (parameters.size() <= 0)
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 1 (timeout)");
			uint32_t timeout = parameters[0].as<uint32_t>();
			if (parameters.size() <= 1)
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 2 (passphrase)");
			std::string passphrase = parameters[1].as<std::string>();

			get_client()->wallet_unlock(timeout, passphrase);
			return fc::variant();
		}

		fc::variant CommonApiRpcServer::wallet_unlock_named(fc::rpc::json_connection* json_connection, const fc::variant_object& parameters)
		{
			// check all of this method's prerequisites
			verify_json_connection_is_authenticated(json_connection);
			verify_wallet_is_open();
			// done checking prerequisites

			if (!parameters.contains("timeout"))
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 'timeout'");
			uint32_t timeout = parameters["timeout"].as<uint32_t>();
			if (!parameters.contains("passphrase"))
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 'passphrase'");
			std::string passphrase = parameters["passphrase"].as<std::string>();

			get_client()->wallet_unlock(timeout, passphrase);
			return fc::variant();
		}

		fc::variant CommonApiRpcServer::wallet_change_passphrase_positional(fc::rpc::json_connection* json_connection, const fc::variants& parameters)
		{
			// check all of this method's prerequisites
			verify_json_connection_is_authenticated(json_connection);
			verify_wallet_is_open();
			verify_wallet_is_unlocked();
			// done checking prerequisites

			if (parameters.size() <= 0)
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 1 (old_passphrase)");
			std::string old_passphrase = parameters[0].as<std::string>();
			if (parameters.size() <= 1)
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 2 (passphrase)");
			std::string passphrase = parameters[1].as<std::string>();

			get_client()->wallet_change_passphrase(old_passphrase, passphrase);
			return fc::variant();
		}

		fc::variant CommonApiRpcServer::wallet_change_passphrase_named(fc::rpc::json_connection* json_connection, const fc::variant_object& parameters)
		{
			// check all of this method's prerequisites
			verify_json_connection_is_authenticated(json_connection);
			verify_wallet_is_open();
			verify_wallet_is_unlocked();
			// done checking prerequisites

			if (!parameters.contains("old_passphrase"))
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 'old_passphrase'");
			std::string old_passphrase = parameters["old_passphrase"].as<std::string>();
			if (!parameters.contains("passphrase"))
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 'passphrase'");
			std::string passphrase = parameters["passphrase"].as<std::string>();

			get_client()->wallet_change_passphrase(old_passphrase, passphrase);
			return fc::variant();
		}

		fc::variant CommonApiRpcServer::wallet_check_passphrase_positional(fc::rpc::json_connection* json_connection, const fc::variants& parameters)
		{
			// check all of this method's prerequisites
			verify_json_connection_is_authenticated(json_connection);
			verify_wallet_is_open();
			verify_wallet_is_unlocked();
			// done checking prerequisites

			if (parameters.size() <= 0)
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 1 (passphrase)");
			std::string passphrase = parameters[0].as<std::string>();

			bool result = get_client()->wallet_check_passphrase(passphrase);
			return fc::variant(result);
		}

		fc::variant CommonApiRpcServer::wallet_check_passphrase_named(fc::rpc::json_connection* json_connection, const fc::variant_object& parameters)
		{
			// check all of this method's prerequisites
			verify_json_connection_is_authenticated(json_connection);
			verify_wallet_is_open();
			verify_wallet_is_unlocked();
			// done checking prerequisites

			if (!parameters.contains("passphrase"))
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 'passphrase'");
			std::string passphrase = parameters["passphrase"].as<std::string>();

			bool result = get_client()->wallet_check_passphrase(passphrase);
			return fc::variant(result);
		}

		fc::variant CommonApiRpcServer::wallet_check_address_positional(fc::rpc::json_connection* json_connection, const fc::variants& parameters)
		{
			// check all of this method's prerequisites
			verify_json_connection_is_authenticated(json_connection);
			verify_wallet_is_open();
			// done checking prerequisites

			if (parameters.size() <= 0)
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 1 (address)");
			std::string address = parameters[0].as<std::string>();

			bool result = get_client()->wallet_check_address(address);
			return fc::variant(result);
		}

		fc::variant CommonApiRpcServer::wallet_check_address_named(fc::rpc::json_connection* json_connection, const fc::variant_object& parameters)
		{
			// check all of this method's prerequisites
			verify_json_connection_is_authenticated(json_connection);
			verify_wallet_is_open();
			// done checking prerequisites

			if (!parameters.contains("address"))
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 'address'");
			std::string address = parameters["address"].as<std::string>();

			bool result = get_client()->wallet_check_address(address);
			return fc::variant(result);
		}

		fc::variant CommonApiRpcServer::wallet_list_positional(fc::rpc::json_connection* json_connection, const fc::variants& parameters)
		{
			// check all of this method's prerequisites
			verify_json_connection_is_authenticated(json_connection);
			// done checking prerequisites


			std::vector<std::string> result = get_client()->wallet_list();
			return fc::variant(result);
		}

		fc::variant CommonApiRpcServer::wallet_list_named(fc::rpc::json_connection* json_connection, const fc::variant_object& parameters)
		{
			// check all of this method's prerequisites
			verify_json_connection_is_authenticated(json_connection);
			// done checking prerequisites


			std::vector<std::string> result = get_client()->wallet_list();
			return fc::variant(result);
		}

		fc::variant CommonApiRpcServer::wallet_account_create_positional(fc::rpc::json_connection* json_connection, const fc::variants& parameters)
		{
			// check all of this method's prerequisites
			verify_json_connection_is_authenticated(json_connection);
			verify_wallet_is_open();
			verify_wallet_is_unlocked();
			// done checking prerequisites

			if (parameters.size() <= 0)
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 1 (account_name)");
			std::string account_name = parameters[0].as<std::string>();
			fc::variant private_data = (parameters.size() <= 1) ?
				(fc::json::from_string("null").as<fc::variant>()) :
				parameters[1].as<fc::variant>();

			cdcchain::consensus::Address result = get_client()->wallet_account_create(account_name, private_data);
			return fc::variant(result);
		}

		fc::variant CommonApiRpcServer::wallet_account_create_named(fc::rpc::json_connection* json_connection, const fc::variant_object& parameters)
		{
			// check all of this method's prerequisites
			verify_json_connection_is_authenticated(json_connection);
			verify_wallet_is_open();
			verify_wallet_is_unlocked();
			// done checking prerequisites

			if (!parameters.contains("account_name"))
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 'account_name'");
			std::string account_name = parameters["account_name"].as<std::string>();
			fc::variant private_data = parameters.contains("private_data") ?
				(fc::json::from_string("null").as<fc::variant>()) :
				parameters["private_data"].as<fc::variant>();

			cdcchain::consensus::Address result = get_client()->wallet_account_create(account_name, private_data);
			return fc::variant(result);
		}

		fc::variant CommonApiRpcServer::wallet_account_set_approval_positional(fc::rpc::json_connection* json_connection, const fc::variants& parameters)
		{
			// check all of this method's prerequisites
			verify_json_connection_is_authenticated(json_connection);
			verify_wallet_is_open();
			// done checking prerequisites

			if (parameters.size() <= 0)
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 1 (account_name)");
			std::string account_name = parameters[0].as<std::string>();
			int8_t approval = (parameters.size() <= 1) ?
				(fc::json::from_string("1").as<int8_t>()) :
				parameters[1].as<int8_t>();

			int8_t result = get_client()->wallet_account_set_approval(account_name, approval);
			return fc::variant(result);
		}

		fc::variant CommonApiRpcServer::wallet_account_set_approval_named(fc::rpc::json_connection* json_connection, const fc::variant_object& parameters)
		{
			// check all of this method's prerequisites
			verify_json_connection_is_authenticated(json_connection);
			verify_wallet_is_open();
			// done checking prerequisites

			if (!parameters.contains("account_name"))
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 'account_name'");
			std::string account_name = parameters["account_name"].as<std::string>();
			int8_t approval = parameters.contains("approval") ?
				(fc::json::from_string("1").as<int8_t>()) :
				parameters["approval"].as<int8_t>();

			int8_t result = get_client()->wallet_account_set_approval(account_name, approval);
			return fc::variant(result);
		}

		fc::variant CommonApiRpcServer::wallet_get_all_approved_accounts_positional(fc::rpc::json_connection* json_connection, const fc::variants& parameters)
		{
			// check all of this method's prerequisites
			verify_json_connection_is_authenticated(json_connection);
			verify_wallet_is_open();
			// done checking prerequisites

			int8_t approval = (parameters.size() <= 0) ?
				(fc::json::from_string("1").as<int8_t>()) :
				parameters[0].as<int8_t>();

			std::vector<cdcchain::consensus::AccountEntry> result = get_client()->wallet_get_all_approved_accounts(approval);
			return fc::variant(result);
		}

		fc::variant CommonApiRpcServer::wallet_get_all_approved_accounts_named(fc::rpc::json_connection* json_connection, const fc::variant_object& parameters)
		{
			// check all of this method's prerequisites
			verify_json_connection_is_authenticated(json_connection);
			verify_wallet_is_open();
			// done checking prerequisites

			int8_t approval = parameters.contains("approval") ?
				(fc::json::from_string("1").as<int8_t>()) :
				parameters["approval"].as<int8_t>();

			std::vector<cdcchain::consensus::AccountEntry> result = get_client()->wallet_get_all_approved_accounts(approval);
			return fc::variant(result);
		}

		fc::variant CommonApiRpcServer::wallet_address_create_positional(fc::rpc::json_connection* json_connection, const fc::variants& parameters)
		{
			// check all of this method's prerequisites
			verify_json_connection_is_authenticated(json_connection);
			verify_wallet_is_open();
			// done checking prerequisites

			if (parameters.size() <= 0)
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 1 (account_name)");
			std::string account_name = parameters[0].as<std::string>();
			std::string label = (parameters.size() <= 1) ?
				(fc::json::from_string("\"\"").as<std::string>()) :
				parameters[1].as<std::string>();
			int32_t legacy_network_byte = (parameters.size() <= 2) ?
				(fc::json::from_string("-1").as<int32_t>()) :
				parameters[2].as<int32_t>();

			std::string result = get_client()->wallet_address_create(account_name, label, legacy_network_byte);
			return fc::variant(result);
		}

		fc::variant CommonApiRpcServer::wallet_address_create_named(fc::rpc::json_connection* json_connection, const fc::variant_object& parameters)
		{
			// check all of this method's prerequisites
			verify_json_connection_is_authenticated(json_connection);
			verify_wallet_is_open();
			// done checking prerequisites

			if (!parameters.contains("account_name"))
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 'account_name'");
			std::string account_name = parameters["account_name"].as<std::string>();
			std::string label = parameters.contains("label") ?
				(fc::json::from_string("\"\"").as<std::string>()) :
				parameters["label"].as<std::string>();
			int32_t legacy_network_byte = parameters.contains("legacy_network_byte") ?
				(fc::json::from_string("-1").as<int32_t>()) :
				parameters["legacy_network_byte"].as<int32_t>();

			std::string result = get_client()->wallet_address_create(account_name, label, legacy_network_byte);
			return fc::variant(result);
		}

		fc::variant CommonApiRpcServer::wallet_transfer_to_address_positional(fc::rpc::json_connection* json_connection, const fc::variants& parameters)
		{
			// check all of this method's prerequisites
			verify_json_connection_is_authenticated(json_connection);
			verify_wallet_is_open();
			// done checking prerequisites

			if (parameters.size() <= 0)
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 1 (amount_to_transfer)");
			std::string amount_to_transfer = parameters[0].as<std::string>();
			if (parameters.size() <= 1)
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 2 (asset_symbol)");
			std::string asset_symbol = parameters[1].as<std::string>();
			if (parameters.size() <= 2)
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 3 (from_account_name)");
			std::string from_account_name = parameters[2].as<std::string>();
			if (parameters.size() <= 3)
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 4 (to_address)");
			std::string to_address = parameters[3].as<std::string>();
			cdcchain::consensus::Imessage memo_message = (parameters.size() <= 4) ?
				(fc::json::from_string("\"\"").as<cdcchain::consensus::Imessage>()) :
				parameters[4].as<cdcchain::consensus::Imessage>();
			cdcchain::wallet::VoteStrategy strategy = (parameters.size() <= 5) ?
				(fc::json::from_string("\"vote_recommended\"").as<cdcchain::wallet::VoteStrategy>()) :
				parameters[5].as<cdcchain::wallet::VoteStrategy>();

			cdcchain::wallet::WalletTransactionEntry result = get_client()->wallet_transfer_to_address(amount_to_transfer, asset_symbol, from_account_name, to_address, memo_message, strategy);
			return fc::variant(result);
		}

		fc::variant CommonApiRpcServer::wallet_transfer_to_address_named(fc::rpc::json_connection* json_connection, const fc::variant_object& parameters)
		{
			// check all of this method's prerequisites
			verify_json_connection_is_authenticated(json_connection);
			verify_wallet_is_open();
			// done checking prerequisites

			if (!parameters.contains("amount_to_transfer"))
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 'amount_to_transfer'");
			std::string amount_to_transfer = parameters["amount_to_transfer"].as<std::string>();
			if (!parameters.contains("asset_symbol"))
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 'asset_symbol'");
			std::string asset_symbol = parameters["asset_symbol"].as<std::string>();
			if (!parameters.contains("from_account_name"))
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 'from_account_name'");
			std::string from_account_name = parameters["from_account_name"].as<std::string>();
			if (!parameters.contains("to_address"))
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 'to_address'");
			std::string to_address = parameters["to_address"].as<std::string>();
			cdcchain::consensus::Imessage memo_message = parameters.contains("memo_message") ?
				(fc::json::from_string("\"\"").as<cdcchain::consensus::Imessage>()) :
				parameters["memo_message"].as<cdcchain::consensus::Imessage>();
			cdcchain::wallet::VoteStrategy strategy = parameters.contains("strategy") ?
				(fc::json::from_string("\"vote_recommended\"").as<cdcchain::wallet::VoteStrategy>()) :
				parameters["strategy"].as<cdcchain::wallet::VoteStrategy>();

			cdcchain::wallet::WalletTransactionEntry result = get_client()->wallet_transfer_to_address(amount_to_transfer, asset_symbol, from_account_name, to_address, memo_message, strategy);
			return fc::variant(result);
		}

		fc::variant CommonApiRpcServer::wallet_transfer_to_public_account_positional(fc::rpc::json_connection* json_connection, const fc::variants& parameters)
		{
			// check all of this method's prerequisites
			verify_json_connection_is_authenticated(json_connection);
			verify_wallet_is_open();
			verify_wallet_is_unlocked();
			// done checking prerequisites

			if (parameters.size() <= 0)
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 1 (amount_to_transfer)");
			std::string amount_to_transfer = parameters[0].as<std::string>();
			if (parameters.size() <= 1)
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 2 (asset_symbol)");
			std::string asset_symbol = parameters[1].as<std::string>();
			if (parameters.size() <= 2)
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 3 (from_account_name)");
			std::string from_account_name = parameters[2].as<std::string>();
			if (parameters.size() <= 3)
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 4 (to_account_name)");
			std::string to_account_name = parameters[3].as<std::string>();
			cdcchain::consensus::Imessage memo_message = (parameters.size() <= 4) ?
				(fc::json::from_string("\"\"").as<cdcchain::consensus::Imessage>()) :
				parameters[4].as<cdcchain::consensus::Imessage>();
			cdcchain::wallet::VoteStrategy strategy = (parameters.size() <= 5) ?
				(fc::json::from_string("\"vote_recommended\"").as<cdcchain::wallet::VoteStrategy>()) :
				parameters[5].as<cdcchain::wallet::VoteStrategy>();

			cdcchain::wallet::WalletTransactionEntry result = get_client()->wallet_transfer_to_public_account(amount_to_transfer, asset_symbol, from_account_name, to_account_name, memo_message, strategy);
			return fc::variant(result);
		}

		fc::variant CommonApiRpcServer::wallet_transfer_to_public_account_named(fc::rpc::json_connection* json_connection, const fc::variant_object& parameters)
		{
			// check all of this method's prerequisites
			verify_json_connection_is_authenticated(json_connection);
			verify_wallet_is_open();
			verify_wallet_is_unlocked();
			// done checking prerequisites

			if (!parameters.contains("amount_to_transfer"))
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 'amount_to_transfer'");
			std::string amount_to_transfer = parameters["amount_to_transfer"].as<std::string>();
			if (!parameters.contains("asset_symbol"))
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 'asset_symbol'");
			std::string asset_symbol = parameters["asset_symbol"].as<std::string>();
			if (!parameters.contains("from_account_name"))
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 'from_account_name'");
			std::string from_account_name = parameters["from_account_name"].as<std::string>();
			if (!parameters.contains("to_account_name"))
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 'to_account_name'");
			std::string to_account_name = parameters["to_account_name"].as<std::string>();
			cdcchain::consensus::Imessage memo_message = parameters.contains("memo_message") ?
				(fc::json::from_string("\"\"").as<cdcchain::consensus::Imessage>()) :
				parameters["memo_message"].as<cdcchain::consensus::Imessage>();
			cdcchain::wallet::VoteStrategy strategy = parameters.contains("strategy") ?
				(fc::json::from_string("\"vote_recommended\"").as<cdcchain::wallet::VoteStrategy>()) :
				parameters["strategy"].as<cdcchain::wallet::VoteStrategy>();

			cdcchain::wallet::WalletTransactionEntry result = get_client()->wallet_transfer_to_public_account(amount_to_transfer, asset_symbol, from_account_name, to_account_name, memo_message, strategy);
			return fc::variant(result);
		}

		fc::variant CommonApiRpcServer::wallet_withdraw_from_address_positional(fc::rpc::json_connection* json_connection, const fc::variants& parameters)
		{
			// check all of this method's prerequisites
			verify_json_connection_is_authenticated(json_connection);
			// done checking prerequisites

			if (parameters.size() <= 0)
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 1 (amount)");
			std::string amount = parameters[0].as<std::string>();
			if (parameters.size() <= 1)
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 2 (symbol)");
			std::string symbol = parameters[1].as<std::string>();
			if (parameters.size() <= 2)
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 3 (from_address)");
			cdcchain::consensus::Address from_address = parameters[2].as<cdcchain::consensus::Address>();
			if (parameters.size() <= 3)
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 4 (to)");
			std::string to = parameters[3].as<std::string>();
			cdcchain::wallet::VoteStrategy strategy = (parameters.size() <= 4) ?
				(fc::json::from_string("\"vote_none\"").as<cdcchain::wallet::VoteStrategy>()) :
				parameters[4].as<cdcchain::wallet::VoteStrategy>();
			bool sign_and_broadcast = (parameters.size() <= 5) ?
				(fc::json::from_string("true").as<bool>()) :
				parameters[5].as<bool>();
			std::string builder_path = (parameters.size() <= 6) ?
				(fc::json::from_string("\"\"").as<std::string>()) :
				parameters[6].as<std::string>();

			cdcchain::wallet::TransactionBuilder result = get_client()->wallet_withdraw_from_address(amount, symbol, from_address, to, strategy, sign_and_broadcast, builder_path);
			return fc::variant(result);
		}

		fc::variant CommonApiRpcServer::wallet_withdraw_from_address_named(fc::rpc::json_connection* json_connection, const fc::variant_object& parameters)
		{
			// check all of this method's prerequisites
			verify_json_connection_is_authenticated(json_connection);
			// done checking prerequisites

			if (!parameters.contains("amount"))
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 'amount'");
			std::string amount = parameters["amount"].as<std::string>();
			if (!parameters.contains("symbol"))
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 'symbol'");
			std::string symbol = parameters["symbol"].as<std::string>();
			if (!parameters.contains("from_address"))
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 'from_address'");
			cdcchain::consensus::Address from_address = parameters["from_address"].as<cdcchain::consensus::Address>();
			if (!parameters.contains("to"))
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 'to'");
			std::string to = parameters["to"].as<std::string>();
			cdcchain::wallet::VoteStrategy strategy = parameters.contains("strategy") ?
				(fc::json::from_string("\"vote_none\"").as<cdcchain::wallet::VoteStrategy>()) :
				parameters["strategy"].as<cdcchain::wallet::VoteStrategy>();
			bool sign_and_broadcast = parameters.contains("sign_and_broadcast") ?
				(fc::json::from_string("true").as<bool>()) :
				parameters["sign_and_broadcast"].as<bool>();
			std::string builder_path = parameters.contains("builder_path") ?
				(fc::json::from_string("\"\"").as<std::string>()) :
				parameters["builder_path"].as<std::string>();

			cdcchain::wallet::TransactionBuilder result = get_client()->wallet_withdraw_from_address(amount, symbol, from_address, to, strategy, sign_and_broadcast, builder_path);
			return fc::variant(result);
		}

		fc::variant CommonApiRpcServer::wallet_rescan_blockchain_positional(fc::rpc::json_connection* json_connection, const fc::variants& parameters)
		{
			// check all of this method's prerequisites
			verify_json_connection_is_authenticated(json_connection);
			verify_wallet_is_open();
			verify_wallet_is_unlocked();
			// done checking prerequisites

			uint32_t start_block_num = (parameters.size() <= 0) ?
				(fc::json::from_string("0").as<uint32_t>()) :
				parameters[0].as<uint32_t>();
			uint32_t limit = (parameters.size() <= 1) ?
				(fc::json::from_string("-1").as<uint32_t>()) :
				parameters[1].as<uint32_t>();

			get_client()->wallet_rescan_blockchain(start_block_num, limit);
			return fc::variant();
		}

		fc::variant CommonApiRpcServer::wallet_rescan_blockchain_named(fc::rpc::json_connection* json_connection, const fc::variant_object& parameters)
		{
			// check all of this method's prerequisites
			verify_json_connection_is_authenticated(json_connection);
			verify_wallet_is_open();
			verify_wallet_is_unlocked();
			// done checking prerequisites

			uint32_t start_block_num = parameters.contains("start_block_num") ?
				(fc::json::from_string("0").as<uint32_t>()) :
				parameters["start_block_num"].as<uint32_t>();
			uint32_t limit = parameters.contains("limit") ?
				(fc::json::from_string("-1").as<uint32_t>()) :
				parameters["limit"].as<uint32_t>();

			get_client()->wallet_rescan_blockchain(start_block_num, limit);
			return fc::variant();
		}

		fc::variant CommonApiRpcServer::wallet_cancel_scan_positional(fc::rpc::json_connection* json_connection, const fc::variants& parameters)
		{
			// check all of this method's prerequisites
			verify_json_connection_is_authenticated(json_connection);
			verify_wallet_is_open();
			verify_wallet_is_unlocked();
			// done checking prerequisites


			get_client()->wallet_cancel_scan();
			return fc::variant();
		}

		fc::variant CommonApiRpcServer::wallet_cancel_scan_named(fc::rpc::json_connection* json_connection, const fc::variant_object& parameters)
		{
			// check all of this method's prerequisites
			verify_json_connection_is_authenticated(json_connection);
			verify_wallet_is_open();
			verify_wallet_is_unlocked();
			// done checking prerequisites


			get_client()->wallet_cancel_scan();
			return fc::variant();
		}

		fc::variant CommonApiRpcServer::wallet_get_transaction_positional(fc::rpc::json_connection* json_connection, const fc::variants& parameters)
		{
			// check all of this method's prerequisites
			verify_json_connection_is_authenticated(json_connection);
			verify_wallet_is_open();
			// done checking prerequisites

			if (parameters.size() <= 0)
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 1 (transaction_id)");
			std::string transaction_id = parameters[0].as<std::string>();

			cdcchain::wallet::WalletTransactionEntry result = get_client()->wallet_get_transaction(transaction_id);
			return fc::variant(result);
		}

		fc::variant CommonApiRpcServer::wallet_get_transaction_named(fc::rpc::json_connection* json_connection, const fc::variant_object& parameters)
		{
			// check all of this method's prerequisites
			verify_json_connection_is_authenticated(json_connection);
			verify_wallet_is_open();
			// done checking prerequisites

			if (!parameters.contains("transaction_id"))
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 'transaction_id'");
			std::string transaction_id = parameters["transaction_id"].as<std::string>();

			cdcchain::wallet::WalletTransactionEntry result = get_client()->wallet_get_transaction(transaction_id);
			return fc::variant(result);
		}

		fc::variant CommonApiRpcServer::wallet_scan_transaction_positional(fc::rpc::json_connection* json_connection, const fc::variants& parameters)
		{
			// check all of this method's prerequisites
			verify_json_connection_is_authenticated(json_connection);
			verify_wallet_is_open();
			verify_wallet_is_unlocked();
			// done checking prerequisites

			if (parameters.size() <= 0)
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 1 (transaction_id)");
			std::string transaction_id = parameters[0].as<std::string>();
			bool overwrite_existing = (parameters.size() <= 1) ?
				(fc::json::from_string("false").as<bool>()) :
				parameters[1].as<bool>();

			cdcchain::wallet::WalletTransactionEntry result = get_client()->wallet_scan_transaction(transaction_id, overwrite_existing);
			return fc::variant(result);
		}

		fc::variant CommonApiRpcServer::wallet_scan_transaction_named(fc::rpc::json_connection* json_connection, const fc::variant_object& parameters)
		{
			// check all of this method's prerequisites
			verify_json_connection_is_authenticated(json_connection);
			verify_wallet_is_open();
			verify_wallet_is_unlocked();
			// done checking prerequisites

			if (!parameters.contains("transaction_id"))
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 'transaction_id'");
			std::string transaction_id = parameters["transaction_id"].as<std::string>();
			bool overwrite_existing = parameters.contains("overwrite_existing") ?
				(fc::json::from_string("false").as<bool>()) :
				parameters["overwrite_existing"].as<bool>();

			cdcchain::wallet::WalletTransactionEntry result = get_client()->wallet_scan_transaction(transaction_id, overwrite_existing);
			return fc::variant(result);
		}

		fc::variant CommonApiRpcServer::wallet_rebroadcast_transaction_positional(fc::rpc::json_connection* json_connection, const fc::variants& parameters)
		{
			// check all of this method's prerequisites
			verify_json_connection_is_authenticated(json_connection);
			verify_wallet_is_open();
			// done checking prerequisites

			if (parameters.size() <= 0)
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 1 (transaction_id)");
			std::string transaction_id = parameters[0].as<std::string>();

			get_client()->wallet_rebroadcast_transaction(transaction_id);
			return fc::variant();
		}

		fc::variant CommonApiRpcServer::wallet_rebroadcast_transaction_named(fc::rpc::json_connection* json_connection, const fc::variant_object& parameters)
		{
			// check all of this method's prerequisites
			verify_json_connection_is_authenticated(json_connection);
			verify_wallet_is_open();
			// done checking prerequisites

			if (!parameters.contains("transaction_id"))
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 'transaction_id'");
			std::string transaction_id = parameters["transaction_id"].as<std::string>();

			get_client()->wallet_rebroadcast_transaction(transaction_id);
			return fc::variant();
		}

        fc::variant CommonApiRpcServer::wallet_transfer_to_address_build_positional(fc::rpc::json_connection* json_connection, const fc::variants& parameters)
        {
            // check all of this method's prerequisites
            verify_json_connection_is_authenticated(json_connection);
            verify_wallet_is_open();
            // done checking prerequisites

            if (parameters.size() <= 0)
                FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 1 (amount_to_transfer)");
            std::string amount_to_transfer = parameters[0].as<std::string>();
            if (parameters.size() <= 1)
                FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 2 (asset_symbol)");
            std::string asset_symbol = parameters[1].as<std::string>();
            if (parameters.size() <= 2)
                FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 3 (from_account_public_key)");
            std::string from_account_public_key = parameters[2].as<std::string>();
            if (parameters.size() <= 3)
                FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 4 (to_address)");
            std::string to_address = parameters[3].as<std::string>();
            cdcchain::consensus::Imessage memo_message = (parameters.size() <= 4) ?
                (fc::json::from_string("\"\"").as<cdcchain::consensus::Imessage>()) :
                parameters[4].as<cdcchain::consensus::Imessage>();
            cdcchain::wallet::VoteStrategy strategy = (parameters.size() <= 5) ?
                (fc::json::from_string("\"vote_none\"").as<cdcchain::wallet::VoteStrategy>()) :
                parameters[5].as<cdcchain::wallet::VoteStrategy>();

            cdcchain::wallet::WalletTransactionEntry result = get_client()->wallet_transfer_to_address_build(amount_to_transfer, asset_symbol, from_account_public_key, to_address, memo_message, strategy);
            return fc::variant(result);
        }

        fc::variant CommonApiRpcServer::wallet_transfer_to_address_build_named(fc::rpc::json_connection* json_connection, const fc::variant_object& parameters)
        {
            // check all of this method's prerequisites
            verify_json_connection_is_authenticated(json_connection);
            verify_wallet_is_open();
            // done checking prerequisites

            if (!parameters.contains("amount_to_transfer"))
                FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 'amount_to_transfer'");
            std::string amount_to_transfer = parameters["amount_to_transfer"].as<std::string>();
            if (!parameters.contains("asset_symbol"))
                FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 'asset_symbol'");
            std::string asset_symbol = parameters["asset_symbol"].as<std::string>();
            if (!parameters.contains("from_account_public_key"))
                FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 'from_account_public_key'");
            std::string from_account_public_key = parameters["from_account_public_key"].as<std::string>();
            if (!parameters.contains("to_address"))
                FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 'to_address'");
            std::string to_address = parameters["to_address"].as<std::string>();
            cdcchain::consensus::Imessage memo_message = parameters.contains("memo_message") ?
                (fc::json::from_string("\"\"").as<cdcchain::consensus::Imessage>()) :
                parameters["memo_message"].as<cdcchain::consensus::Imessage>();
            cdcchain::wallet::VoteStrategy strategy = parameters.contains("strategy") ?
                (fc::json::from_string("\"vote_none\"").as<cdcchain::wallet::VoteStrategy>()) :
                parameters["strategy"].as<cdcchain::wallet::VoteStrategy>();

            cdcchain::wallet::WalletTransactionEntry result = get_client()->wallet_transfer_to_address_build(amount_to_transfer, asset_symbol, from_account_public_key, to_address, memo_message, strategy);
            return fc::variant(result);
        }

        fc::variant CommonApiRpcServer::wallet_transfer_to_contract_build_positional(fc::rpc::json_connection* json_connection, const fc::variants& parameters)
        {
            // check all of this method's prerequisites
            verify_json_connection_is_authenticated(json_connection);
            verify_wallet_is_open();
            // done checking prerequisites

            if (parameters.size() <= 0)
                FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 1 (amount_to_transfer)");
            double amount_to_transfer = parameters[0].as<double>();
            if (parameters.size() <= 1)
                FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 2 (asset_symbol)");
            std::string asset_symbol = parameters[1].as<std::string>();
            if (parameters.size() <= 2)
                FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 3 (from_account_public_key)");
            std::string from_account_public_key = parameters[2].as<std::string>();
            if (parameters.size() <= 3)
                FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 4 (to_contract)");
            std::string to_contract = parameters[3].as<std::string>();
            if (parameters.size() <= 4)
                FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 5 (amount_for_exec)");
            double amount_for_exec = parameters[4].as<double>();

            cdcchain::wallet::WalletTransactionEntry result = get_client()->wallet_transfer_to_contract_build(amount_to_transfer, asset_symbol, from_account_public_key, to_contract, amount_for_exec);
            return fc::variant(result);
        }

        fc::variant CommonApiRpcServer::wallet_transfer_to_contract_build_named(fc::rpc::json_connection* json_connection, const fc::variant_object& parameters)
        {
            // check all of this method's prerequisites
            verify_json_connection_is_authenticated(json_connection);
            verify_wallet_is_open();
            // done checking prerequisites

            if (!parameters.contains("amount_to_transfer"))
                FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 'amount_to_transfer'");
            double amount_to_transfer = parameters["amount_to_transfer"].as<double>();
            if (!parameters.contains("asset_symbol"))
                FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 'asset_symbol'");
            std::string asset_symbol = parameters["asset_symbol"].as<std::string>();
            if (!parameters.contains("from_account_public_key"))
                FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 'from_account_public_key'");
            std::string from_account_public_key = parameters["from_account_public_key"].as<std::string>();
            if (!parameters.contains("to_contract"))
                FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 'to_contract'");
            std::string to_contract = parameters["to_contract"].as<std::string>();
            if (!parameters.contains("amount_for_exec"))
                FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 'amount_for_exec'");
            double amount_for_exec = parameters["amount_for_exec"].as<double>();

            cdcchain::wallet::WalletTransactionEntry result = get_client()->wallet_transfer_to_contract_build(amount_to_transfer, asset_symbol, from_account_public_key, to_contract, amount_for_exec);
            return fc::variant(result);
        }

        fc::variant CommonApiRpcServer::wallet_call_contract_build_positional(fc::rpc::json_connection* json_connection, const fc::variants& parameters)
        {
            // check all of this method's prerequisites
            verify_json_connection_is_authenticated(json_connection);
            verify_wallet_is_open();
            // done checking prerequisites

            if (parameters.size() <= 0)
                FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 1 (contract)");
            std::string contract = parameters[0].as<std::string>();
            if (parameters.size() <= 1)
                FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 2 (caller_publickey)");
            std::string caller_publickey = parameters[1].as<std::string>();
            if (parameters.size() <= 2)
                FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 3 (function_name)");
            std::string function_name = parameters[2].as<std::string>();
            if (parameters.size() <= 3)
                FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 4 (params)");
            std::string params = parameters[3].as<std::string>();
            if (parameters.size() <= 4)
                FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 5 (asset_symbol)");
            std::string asset_symbol = parameters[4].as<std::string>();
            if (parameters.size() <= 5)
                FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 6 (call_limit)");
            fc::optional<double> call_limit = parameters[5].as<fc::optional<double>>();

            cdcchain::wallet::WalletTransactionEntry result = get_client()->wallet_call_contract_build(contract, caller_publickey, function_name, params, asset_symbol, call_limit);
            return fc::variant(result);
        }

        fc::variant CommonApiRpcServer::wallet_call_contract_build_named(fc::rpc::json_connection* json_connection, const fc::variant_object& parameters)
        {
            // check all of this method's prerequisites
            verify_json_connection_is_authenticated(json_connection);
            verify_wallet_is_open();
            // done checking prerequisites

            if (!parameters.contains("contract"))
                FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 'contract'");
            std::string contract = parameters["contract"].as<std::string>();
            if (!parameters.contains("caller_publickey"))
                FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 'caller_publickey'");
            std::string caller_publickey = parameters["caller_publickey"].as<std::string>();
            if (!parameters.contains("function_name"))
                FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 'function_name'");
            std::string function_name = parameters["function_name"].as<std::string>();
            if (!parameters.contains("params"))
                FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 'params'");
            std::string params = parameters["params"].as<std::string>();
            if (!parameters.contains("asset_symbol"))
                FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 'asset_symbol'");
            std::string asset_symbol = parameters["asset_symbol"].as<std::string>();
            if (!parameters.contains("call_limit"))
                FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 'call_limit'");
            fc::optional<double> call_limit = parameters["call_limit"].as<fc::optional<double>>();

            cdcchain::wallet::WalletTransactionEntry result = get_client()->wallet_call_contract_build(contract, caller_publickey, function_name, params, asset_symbol, call_limit);
            return fc::variant(result);
        }

        fc::variant CommonApiRpcServer::sign_build_transaction_positional(fc::rpc::json_connection* json_connection, const fc::variants& parameters)
        {
            // check all of this method's prerequisites
            verify_json_connection_is_authenticated(json_connection);
            verify_wallet_is_open();
            verify_wallet_is_unlocked();
            // done checking prerequisites

            if (parameters.size() <= 0)
                FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 1 (trasaction_building)");
            cdcchain::wallet::WalletTransactionEntry trasaction_building = parameters[0].as<cdcchain::wallet::WalletTransactionEntry>();

            cdcchain::wallet::WalletTransactionEntry result = get_client()->sign_build_transaction(trasaction_building);
            return fc::variant(result);
        }

        fc::variant CommonApiRpcServer::sign_build_transaction_named(fc::rpc::json_connection* json_connection, const fc::variant_object& parameters)
        {
            // check all of this method's prerequisites
            verify_json_connection_is_authenticated(json_connection);
            verify_wallet_is_open();
            verify_wallet_is_unlocked();
            // done checking prerequisites

            if (!parameters.contains("trasaction_building"))
                FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 'trasaction_building'");
            cdcchain::wallet::WalletTransactionEntry trasaction_building = parameters["trasaction_building"].as<cdcchain::wallet::WalletTransactionEntry>();

            cdcchain::wallet::WalletTransactionEntry result = get_client()->sign_build_transaction(trasaction_building);
            return fc::variant(result);
        }

        fc::variant CommonApiRpcServer::broadcast_building_transaction_positional(fc::rpc::json_connection* json_connection, const fc::variants& parameters)
        {
            // check all of this method's prerequisites
            verify_json_connection_is_authenticated(json_connection);
            verify_wallet_is_open();
            verify_wallet_is_unlocked();
            // done checking prerequisites

            if (parameters.size() <= 0)
                FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 1 (trasaction_building)");
            cdcchain::wallet::WalletTransactionEntry trasaction_building = parameters[0].as<cdcchain::wallet::WalletTransactionEntry>();

            bool result = get_client()->broadcast_building_transaction(trasaction_building);
            return fc::variant(result);
        }

        fc::variant CommonApiRpcServer::broadcast_building_transaction_named(fc::rpc::json_connection* json_connection, const fc::variant_object& parameters)
        {
            // check all of this method's prerequisites
            verify_json_connection_is_authenticated(json_connection);
            verify_wallet_is_open();
            verify_wallet_is_unlocked();
            // done checking prerequisites

            if (!parameters.contains("trasaction_building"))
                FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 'trasaction_building'");
            cdcchain::wallet::WalletTransactionEntry trasaction_building = parameters["trasaction_building"].as<cdcchain::wallet::WalletTransactionEntry>();

            bool result = get_client()->broadcast_building_transaction(trasaction_building);
            return fc::variant(result);
        }

		fc::variant CommonApiRpcServer::wallet_account_register_positional(fc::rpc::json_connection* json_connection, const fc::variants& parameters)
		{
			// check all of this method's prerequisites
			verify_json_connection_is_authenticated(json_connection);
			verify_wallet_is_open();
			verify_wallet_is_unlocked();
			// done checking prerequisites

			if (parameters.size() <= 0)
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 1 (account_name)");
			std::string account_name = parameters[0].as<std::string>();
			if (parameters.size() <= 1)
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 2 (pay_from_account)");
			std::string pay_from_account = parameters[1].as<std::string>();
			fc::variant public_data = (parameters.size() <= 2) ?
				(fc::json::from_string("null").as<fc::variant>()) :
				parameters[2].as<fc::variant>();
			uint8_t delegate_pay_rate = (parameters.size() <= 3) ?
				(fc::json::from_string("-1").as<uint8_t>()) :
				parameters[3].as<uint8_t>();
			std::string account_type = (parameters.size() <= 4) ?
				(fc::json::from_string("\"titan_account\"").as<std::string>()) :
				parameters[4].as<std::string>();

			cdcchain::wallet::WalletTransactionEntry result = get_client()->wallet_account_register(account_name, pay_from_account, public_data, delegate_pay_rate, account_type);
			return fc::variant(result);
		}

		fc::variant CommonApiRpcServer::wallet_account_register_named(fc::rpc::json_connection* json_connection, const fc::variant_object& parameters)
		{
			// check all of this method's prerequisites
			verify_json_connection_is_authenticated(json_connection);
			verify_wallet_is_open();
			verify_wallet_is_unlocked();
			// done checking prerequisites

			if (!parameters.contains("account_name"))
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 'account_name'");
			std::string account_name = parameters["account_name"].as<std::string>();
			if (!parameters.contains("pay_from_account"))
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 'pay_from_account'");
			std::string pay_from_account = parameters["pay_from_account"].as<std::string>();
			fc::variant public_data = parameters.contains("public_data") ?
				(fc::json::from_string("null").as<fc::variant>()) :
				parameters["public_data"].as<fc::variant>();
			uint8_t delegate_pay_rate = parameters.contains("delegate_pay_rate") ?
				(fc::json::from_string("-1").as<uint8_t>()) :
				parameters["delegate_pay_rate"].as<uint8_t>();
			std::string account_type = parameters.contains("account_type") ?
				(fc::json::from_string("\"titan_account\"").as<std::string>()) :
				parameters["account_type"].as<std::string>();

			cdcchain::wallet::WalletTransactionEntry result = get_client()->wallet_account_register(account_name, pay_from_account, public_data, delegate_pay_rate, account_type);
			return fc::variant(result);
		}

		fc::variant CommonApiRpcServer::wallet_account_update_private_data_positional(fc::rpc::json_connection* json_connection, const fc::variants& parameters)
		{
			// check all of this method's prerequisites
			verify_json_connection_is_authenticated(json_connection);
			verify_wallet_is_open();
			verify_wallet_is_unlocked();
			// done checking prerequisites

			if (parameters.size() <= 0)
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 1 (account_name)");
			std::string account_name = parameters[0].as<std::string>();
			fc::variant private_data = (parameters.size() <= 1) ?
				(fc::json::from_string("null").as<fc::variant>()) :
				parameters[1].as<fc::variant>();

			get_client()->wallet_account_update_private_data(account_name, private_data);
			return fc::variant();
		}

		fc::variant CommonApiRpcServer::wallet_account_update_private_data_named(fc::rpc::json_connection* json_connection, const fc::variant_object& parameters)
		{
			// check all of this method's prerequisites
			verify_json_connection_is_authenticated(json_connection);
			verify_wallet_is_open();
			verify_wallet_is_unlocked();
			// done checking prerequisites

			if (!parameters.contains("account_name"))
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 'account_name'");
			std::string account_name = parameters["account_name"].as<std::string>();
			fc::variant private_data = parameters.contains("private_data") ?
				(fc::json::from_string("null").as<fc::variant>()) :
				parameters["private_data"].as<fc::variant>();

			get_client()->wallet_account_update_private_data(account_name, private_data);
			return fc::variant();
		}

		fc::variant CommonApiRpcServer::wallet_account_update_registration_positional(fc::rpc::json_connection* json_connection, const fc::variants& parameters)
		{
			// check all of this method's prerequisites
			verify_json_connection_is_authenticated(json_connection);
			verify_wallet_is_open();
			verify_wallet_is_unlocked();
			// done checking prerequisites

			if (parameters.size() <= 0)
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 1 (account_name)");
			std::string account_name = parameters[0].as<std::string>();
			if (parameters.size() <= 1)
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 2 (pay_from_account)");
			std::string pay_from_account = parameters[1].as<std::string>();
			fc::variant public_data = (parameters.size() <= 2) ?
				(fc::json::from_string("null").as<fc::variant>()) :
				parameters[2].as<fc::variant>();
			uint8_t delegate_pay_rate = (parameters.size() <= 3) ?
				(fc::json::from_string("-1").as<uint8_t>()) :
				parameters[3].as<uint8_t>();

			cdcchain::wallet::WalletTransactionEntry result = get_client()->wallet_account_update_registration(account_name, pay_from_account, public_data, delegate_pay_rate);
			return fc::variant(result);
		}

		fc::variant CommonApiRpcServer::wallet_account_update_registration_named(fc::rpc::json_connection* json_connection, const fc::variant_object& parameters)
		{
			// check all of this method's prerequisites
			verify_json_connection_is_authenticated(json_connection);
			verify_wallet_is_open();
			verify_wallet_is_unlocked();
			// done checking prerequisites

			if (!parameters.contains("account_name"))
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 'account_name'");
			std::string account_name = parameters["account_name"].as<std::string>();
			if (!parameters.contains("pay_from_account"))
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 'pay_from_account'");
			std::string pay_from_account = parameters["pay_from_account"].as<std::string>();
			fc::variant public_data = parameters.contains("public_data") ?
				(fc::json::from_string("null").as<fc::variant>()) :
				parameters["public_data"].as<fc::variant>();
			uint8_t delegate_pay_rate = parameters.contains("delegate_pay_rate") ?
				(fc::json::from_string("-1").as<uint8_t>()) :
				parameters["delegate_pay_rate"].as<uint8_t>();

			cdcchain::wallet::WalletTransactionEntry result = get_client()->wallet_account_update_registration(account_name, pay_from_account, public_data, delegate_pay_rate);
			return fc::variant(result);
		}

		fc::variant CommonApiRpcServer::wallet_account_update_active_key_positional(fc::rpc::json_connection* json_connection, const fc::variants& parameters)
		{
			// check all of this method's prerequisites
			verify_json_connection_is_authenticated(json_connection);
			verify_wallet_is_open();
			verify_wallet_is_unlocked();
			// done checking prerequisites

			if (parameters.size() <= 0)
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 1 (account_to_update)");
			std::string account_to_update = parameters[0].as<std::string>();
			if (parameters.size() <= 1)
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 2 (pay_from_account)");
			std::string pay_from_account = parameters[1].as<std::string>();
			std::string new_active_key = (parameters.size() <= 2) ?
				(fc::json::from_string("\"\"").as<std::string>()) :
				parameters[2].as<std::string>();

			cdcchain::wallet::WalletTransactionEntry result = get_client()->wallet_account_update_active_key(account_to_update, pay_from_account, new_active_key);
			return fc::variant(result);
		}

		fc::variant CommonApiRpcServer::wallet_account_update_active_key_named(fc::rpc::json_connection* json_connection, const fc::variant_object& parameters)
		{
			// check all of this method's prerequisites
			verify_json_connection_is_authenticated(json_connection);
			verify_wallet_is_open();
			verify_wallet_is_unlocked();
			// done checking prerequisites

			if (!parameters.contains("account_to_update"))
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 'account_to_update'");
			std::string account_to_update = parameters["account_to_update"].as<std::string>();
			if (!parameters.contains("pay_from_account"))
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 'pay_from_account'");
			std::string pay_from_account = parameters["pay_from_account"].as<std::string>();
			std::string new_active_key = parameters.contains("new_active_key") ?
				(fc::json::from_string("\"\"").as<std::string>()) :
				parameters["new_active_key"].as<std::string>();

			cdcchain::wallet::WalletTransactionEntry result = get_client()->wallet_account_update_active_key(account_to_update, pay_from_account, new_active_key);
			return fc::variant(result);
		}

		fc::variant CommonApiRpcServer::wallet_list_accounts_positional(fc::rpc::json_connection* json_connection, const fc::variants& parameters)
		{
			// check all of this method's prerequisites
			verify_json_connection_is_authenticated(json_connection);
			verify_wallet_is_open();
			// done checking prerequisites


			std::vector<cdcchain::wallet::WalletAccountEntry> result = get_client()->wallet_list_accounts();
			return fc::variant(result);
		}

		fc::variant CommonApiRpcServer::wallet_list_accounts_named(fc::rpc::json_connection* json_connection, const fc::variant_object& parameters)
		{
			// check all of this method's prerequisites
			verify_json_connection_is_authenticated(json_connection);
			verify_wallet_is_open();
			// done checking prerequisites


			std::vector<cdcchain::wallet::WalletAccountEntry> result = get_client()->wallet_list_accounts();
			return fc::variant(result);
		}

		fc::variant CommonApiRpcServer::wallet_list_unregistered_accounts_positional(fc::rpc::json_connection* json_connection, const fc::variants& parameters)
		{
			// check all of this method's prerequisites
			verify_json_connection_is_authenticated(json_connection);
			verify_wallet_is_open();
			// done checking prerequisites


			std::vector<cdcchain::wallet::WalletAccountEntry> result = get_client()->wallet_list_unregistered_accounts();
			return fc::variant(result);
		}

		fc::variant CommonApiRpcServer::wallet_list_unregistered_accounts_named(fc::rpc::json_connection* json_connection, const fc::variant_object& parameters)
		{
			// check all of this method's prerequisites
			verify_json_connection_is_authenticated(json_connection);
			verify_wallet_is_open();
			// done checking prerequisites


			std::vector<cdcchain::wallet::WalletAccountEntry> result = get_client()->wallet_list_unregistered_accounts();
			return fc::variant(result);
		}

		fc::variant CommonApiRpcServer::wallet_list_my_accounts_positional(fc::rpc::json_connection* json_connection, const fc::variants& parameters)
		{
			// check all of this method's prerequisites
			verify_json_connection_is_authenticated(json_connection);
			verify_wallet_is_open();
			// done checking prerequisites


			std::vector<cdcchain::wallet::WalletAccountEntry> result = get_client()->wallet_list_my_accounts();
			return fc::variant(result);
		}

		fc::variant CommonApiRpcServer::wallet_list_my_accounts_named(fc::rpc::json_connection* json_connection, const fc::variant_object& parameters)
		{
			// check all of this method's prerequisites
			verify_json_connection_is_authenticated(json_connection);
			verify_wallet_is_open();
			// done checking prerequisites


			std::vector<cdcchain::wallet::WalletAccountEntry> result = get_client()->wallet_list_my_accounts();
			return fc::variant(result);
		}

		fc::variant CommonApiRpcServer::wallet_list_my_addresses_positional(fc::rpc::json_connection* json_connection, const fc::variants& parameters)
		{
			// check all of this method's prerequisites
			verify_json_connection_is_authenticated(json_connection);
			verify_wallet_is_open();
			// done checking prerequisites


			std::vector<cdcchain::wallet::AccountAddressData> result = get_client()->wallet_list_my_addresses();
			return fc::variant(result);
		}

		fc::variant CommonApiRpcServer::wallet_list_my_addresses_named(fc::rpc::json_connection* json_connection, const fc::variant_object& parameters)
		{
			// check all of this method's prerequisites
			verify_json_connection_is_authenticated(json_connection);
			verify_wallet_is_open();
			// done checking prerequisites


			std::vector<cdcchain::wallet::AccountAddressData> result = get_client()->wallet_list_my_addresses();
			return fc::variant(result);
		}

		fc::variant CommonApiRpcServer::wallet_get_account_positional(fc::rpc::json_connection* json_connection, const fc::variants& parameters)
		{
			// check all of this method's prerequisites
			verify_json_connection_is_authenticated(json_connection);
			verify_wallet_is_open();
			// done checking prerequisites

			if (parameters.size() <= 0)
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 1 (account_name)");
			std::string account_name = parameters[0].as<std::string>();

			cdcchain::wallet::WalletAccountEntry result = get_client()->wallet_get_account(account_name);
			return fc::variant(result);
		}

		fc::variant CommonApiRpcServer::wallet_get_account_named(fc::rpc::json_connection* json_connection, const fc::variant_object& parameters)
		{
			// check all of this method's prerequisites
			verify_json_connection_is_authenticated(json_connection);
			verify_wallet_is_open();
			// done checking prerequisites

			if (!parameters.contains("account_name"))
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 'account_name'");
			std::string account_name = parameters["account_name"].as<std::string>();

			cdcchain::wallet::WalletAccountEntry result = get_client()->wallet_get_account(account_name);
			return fc::variant(result);
		}

		fc::variant CommonApiRpcServer::wallet_get_account_public_address_positional(fc::rpc::json_connection* json_connection, const fc::variants& parameters)
		{
			// check all of this method's prerequisites
			verify_json_connection_is_authenticated(json_connection);
			verify_wallet_is_open();
			// done checking prerequisites

			if (parameters.size() <= 0)
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 1 (account_name)");
			std::string account_name = parameters[0].as<std::string>();

			std::string result = get_client()->wallet_get_account_public_address(account_name);
			return fc::variant(result);
		}

		fc::variant CommonApiRpcServer::wallet_get_account_public_address_named(fc::rpc::json_connection* json_connection, const fc::variant_object& parameters)
		{
			// check all of this method's prerequisites
			verify_json_connection_is_authenticated(json_connection);
			verify_wallet_is_open();
			// done checking prerequisites

			if (!parameters.contains("account_name"))
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 'account_name'");
			std::string account_name = parameters["account_name"].as<std::string>();

			std::string result = get_client()->wallet_get_account_public_address(account_name);
			return fc::variant(result);
		}

		fc::variant CommonApiRpcServer::wallet_remove_contact_account_positional(fc::rpc::json_connection* json_connection, const fc::variants& parameters)
		{
			// check all of this method's prerequisites
			verify_json_connection_is_authenticated(json_connection);
			verify_wallet_is_open();
			// done checking prerequisites

			if (parameters.size() <= 0)
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 1 (account_name)");
			std::string account_name = parameters[0].as<std::string>();

			get_client()->wallet_remove_contact_account(account_name);
			return fc::variant();
		}

		fc::variant CommonApiRpcServer::wallet_remove_contact_account_named(fc::rpc::json_connection* json_connection, const fc::variant_object& parameters)
		{
			// check all of this method's prerequisites
			verify_json_connection_is_authenticated(json_connection);
			verify_wallet_is_open();
			// done checking prerequisites

			if (!parameters.contains("account_name"))
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 'account_name'");
			std::string account_name = parameters["account_name"].as<std::string>();

			get_client()->wallet_remove_contact_account(account_name);
			return fc::variant();
		}

		fc::variant CommonApiRpcServer::wallet_account_rename_positional(fc::rpc::json_connection* json_connection, const fc::variants& parameters)
		{
			// check all of this method's prerequisites
			verify_json_connection_is_authenticated(json_connection);
			verify_wallet_is_open();
			// done checking prerequisites

			if (parameters.size() <= 0)
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 1 (current_account_name)");
			std::string current_account_name = parameters[0].as<std::string>();
			if (parameters.size() <= 1)
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 2 (new_account_name)");
			std::string new_account_name = parameters[1].as<std::string>();

			get_client()->wallet_account_rename(current_account_name, new_account_name);
			return fc::variant();
		}

		fc::variant CommonApiRpcServer::wallet_account_rename_named(fc::rpc::json_connection* json_connection, const fc::variant_object& parameters)
		{
			// check all of this method's prerequisites
			verify_json_connection_is_authenticated(json_connection);
			verify_wallet_is_open();
			// done checking prerequisites

			if (!parameters.contains("current_account_name"))
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 'current_account_name'");
			std::string current_account_name = parameters["current_account_name"].as<std::string>();
			if (!parameters.contains("new_account_name"))
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 'new_account_name'");
			std::string new_account_name = parameters["new_account_name"].as<std::string>();

			get_client()->wallet_account_rename(current_account_name, new_account_name);
			return fc::variant();
		}

		fc::variant CommonApiRpcServer::wallet_asset_create_positional(fc::rpc::json_connection* json_connection, const fc::variants& parameters)
		{
			// check all of this method's prerequisites
			verify_json_connection_is_authenticated(json_connection);
			verify_wallet_is_open();
			verify_wallet_is_unlocked();
			// done checking prerequisites

			if (parameters.size() <= 0)
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 1 (symbol)");
			std::string symbol = parameters[0].as<std::string>();
			if (parameters.size() <= 1)
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 2 (asset_name)");
			std::string asset_name = parameters[1].as<std::string>();
			if (parameters.size() <= 2)
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 3 (issuer_name)");
			std::string issuer_name = parameters[2].as<std::string>();
			if (parameters.size() <= 3)
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 4 (description)");
			std::string description = parameters[3].as<std::string>();
			if (parameters.size() <= 4)
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 5 (maximum_share_supply)");
			std::string maximum_share_supply = parameters[4].as<std::string>();
			if (parameters.size() <= 5)
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 6 (precision)");
			uint64_t precision = parameters[5].as<uint64_t>();
			fc::variant public_data = (parameters.size() <= 6) ?
				(fc::json::from_string("null").as<fc::variant>()) :
				parameters[6].as<fc::variant>();
			bool is_market_issued = (parameters.size() <= 7) ?
				(fc::json::from_string("false").as<bool>()) :
				parameters[7].as<bool>();

			cdcchain::wallet::WalletTransactionEntry result = get_client()->wallet_asset_create(symbol, asset_name, issuer_name, description, maximum_share_supply, precision, public_data, is_market_issued);
			return fc::variant(result);
		}

		fc::variant CommonApiRpcServer::wallet_asset_create_named(fc::rpc::json_connection* json_connection, const fc::variant_object& parameters)
		{
			// check all of this method's prerequisites
			verify_json_connection_is_authenticated(json_connection);
			verify_wallet_is_open();
			verify_wallet_is_unlocked();
			// done checking prerequisites

			if (!parameters.contains("symbol"))
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 'symbol'");
			std::string symbol = parameters["symbol"].as<std::string>();
			if (!parameters.contains("asset_name"))
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 'asset_name'");
			std::string asset_name = parameters["asset_name"].as<std::string>();
			if (!parameters.contains("issuer_name"))
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 'issuer_name'");
			std::string issuer_name = parameters["issuer_name"].as<std::string>();
			if (!parameters.contains("description"))
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 'description'");
			std::string description = parameters["description"].as<std::string>();
			if (!parameters.contains("maximum_share_supply"))
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 'maximum_share_supply'");
			std::string maximum_share_supply = parameters["maximum_share_supply"].as<std::string>();
			if (!parameters.contains("precision"))
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 'precision'");
			uint64_t precision = parameters["precision"].as<uint64_t>();
			fc::variant public_data = parameters.contains("public_data") ?
				(fc::json::from_string("null").as<fc::variant>()) :
				parameters["public_data"].as<fc::variant>();
			bool is_market_issued = parameters.contains("is_market_issued") ?
				(fc::json::from_string("false").as<bool>()) :
				parameters["is_market_issued"].as<bool>();

			cdcchain::wallet::WalletTransactionEntry result = get_client()->wallet_asset_create(symbol, asset_name, issuer_name, description, maximum_share_supply, precision, public_data, is_market_issued);
			return fc::variant(result);
		}

		fc::variant CommonApiRpcServer::wallet_asset_issue_positional(fc::rpc::json_connection* json_connection, const fc::variants& parameters)
		{
			// check all of this method's prerequisites
			verify_json_connection_is_authenticated(json_connection);
			verify_wallet_is_open();
			verify_wallet_is_unlocked();
			// done checking prerequisites

			if (parameters.size() <= 0)
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 1 (amount)");
			std::string amount = parameters[0].as<std::string>();
			if (parameters.size() <= 1)
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 2 (symbol)");
			std::string symbol = parameters[1].as<std::string>();
			if (parameters.size() <= 2)
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 3 (to_account_name)");
			std::string to_account_name = parameters[2].as<std::string>();
			cdcchain::consensus::Imessage memo_message = (parameters.size() <= 3) ?
				(fc::json::from_string("\"\"").as<cdcchain::consensus::Imessage>()) :
				parameters[3].as<cdcchain::consensus::Imessage>();

			cdcchain::wallet::WalletTransactionEntry result = get_client()->wallet_asset_issue(amount, symbol, to_account_name, memo_message);
			return fc::variant(result);
		}

		fc::variant CommonApiRpcServer::wallet_asset_issue_named(fc::rpc::json_connection* json_connection, const fc::variant_object& parameters)
		{
			// check all of this method's prerequisites
			verify_json_connection_is_authenticated(json_connection);
			verify_wallet_is_open();
			verify_wallet_is_unlocked();
			// done checking prerequisites

			if (!parameters.contains("amount"))
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 'amount'");
			std::string amount = parameters["amount"].as<std::string>();
			if (!parameters.contains("symbol"))
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 'symbol'");
			std::string symbol = parameters["symbol"].as<std::string>();
			if (!parameters.contains("to_account_name"))
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 'to_account_name'");
			std::string to_account_name = parameters["to_account_name"].as<std::string>();
			cdcchain::consensus::Imessage memo_message = parameters.contains("memo_message") ?
				(fc::json::from_string("\"\"").as<cdcchain::consensus::Imessage>()) :
				parameters["memo_message"].as<cdcchain::consensus::Imessage>();

			cdcchain::wallet::WalletTransactionEntry result = get_client()->wallet_asset_issue(amount, symbol, to_account_name, memo_message);
			return fc::variant(result);
		}

		fc::variant CommonApiRpcServer::wallet_asset_issue_to_addresses_positional(fc::rpc::json_connection* json_connection, const fc::variants& parameters)
		{
			// check all of this method's prerequisites
			verify_json_connection_is_authenticated(json_connection);
			verify_wallet_is_open();
			verify_wallet_is_unlocked();
			// done checking prerequisites

			if (parameters.size() <= 0)
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 1 (symbol)");
			std::string symbol = parameters[0].as<std::string>();
			if (parameters.size() <= 1)
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 2 (addresses)");
			std::map<std::string, cdcchain::consensus::ShareType> addresses = parameters[1].as<std::map<std::string, cdcchain::consensus::ShareType>>();

			cdcchain::wallet::WalletTransactionEntry result = get_client()->wallet_asset_issue_to_addresses(symbol, addresses);
			return fc::variant(result);
		}

		fc::variant CommonApiRpcServer::wallet_asset_issue_to_addresses_named(fc::rpc::json_connection* json_connection, const fc::variant_object& parameters)
		{
			// check all of this method's prerequisites
			verify_json_connection_is_authenticated(json_connection);
			verify_wallet_is_open();
			verify_wallet_is_unlocked();
			// done checking prerequisites

			if (!parameters.contains("symbol"))
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 'symbol'");
			std::string symbol = parameters["symbol"].as<std::string>();
			if (!parameters.contains("addresses"))
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 'addresses'");
			std::map<std::string, cdcchain::consensus::ShareType> addresses = parameters["addresses"].as<std::map<std::string, cdcchain::consensus::ShareType>>();

			cdcchain::wallet::WalletTransactionEntry result = get_client()->wallet_asset_issue_to_addresses(symbol, addresses);
			return fc::variant(result);
		}

		fc::variant CommonApiRpcServer::wallet_account_balance_positional(fc::rpc::json_connection* json_connection, const fc::variants& parameters)
		{
			// check all of this method's prerequisites
			verify_json_connection_is_authenticated(json_connection);
			verify_wallet_is_open();
			// done checking prerequisites

			std::string account_name = (parameters.size() <= 0) ?
				(fc::json::from_string("\"\"").as<std::string>()) :
				parameters[0].as<std::string>();

			cdcchain::wallet::AccountBalanceSummaryType result = get_client()->wallet_account_balance(account_name);
			return fc::variant(result);
		}

		fc::variant CommonApiRpcServer::wallet_account_balance_named(fc::rpc::json_connection* json_connection, const fc::variant_object& parameters)
		{
			// check all of this method's prerequisites
			verify_json_connection_is_authenticated(json_connection);
			verify_wallet_is_open();
			// done checking prerequisites

			std::string account_name = parameters.contains("account_name") ?
				(fc::json::from_string("\"\"").as<std::string>()) :
				parameters["account_name"].as<std::string>();

			cdcchain::wallet::AccountBalanceSummaryType result = get_client()->wallet_account_balance(account_name);
			return fc::variant(result);
		}

		fc::variant CommonApiRpcServer::wallet_account_balance_ids_positional(fc::rpc::json_connection* json_connection, const fc::variants& parameters)
		{
			// check all of this method's prerequisites
			verify_json_connection_is_authenticated(json_connection);
			verify_wallet_is_open();
			// done checking prerequisites

			std::string account_name = (parameters.size() <= 0) ?
				(fc::json::from_string("\"\"").as<std::string>()) :
				parameters[0].as<std::string>();

			cdcchain::wallet::AccountBalanceIdSummaryType result = get_client()->wallet_account_balance_ids(account_name);
			return fc::variant(result);
		}

		fc::variant CommonApiRpcServer::wallet_account_balance_ids_named(fc::rpc::json_connection* json_connection, const fc::variant_object& parameters)
		{
			// check all of this method's prerequisites
			verify_json_connection_is_authenticated(json_connection);
			verify_wallet_is_open();
			// done checking prerequisites

			std::string account_name = parameters.contains("account_name") ?
				(fc::json::from_string("\"\"").as<std::string>()) :
				parameters["account_name"].as<std::string>();

			cdcchain::wallet::AccountBalanceIdSummaryType result = get_client()->wallet_account_balance_ids(account_name);
			return fc::variant(result);
		}

		fc::variant CommonApiRpcServer::wallet_account_list_public_keys_positional(fc::rpc::json_connection* json_connection, const fc::variants& parameters)
		{
			// check all of this method's prerequisites
			verify_json_connection_is_authenticated(json_connection);
			verify_wallet_is_open();
			// done checking prerequisites

			if (parameters.size() <= 0)
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 1 (account_name)");
			std::string account_name = parameters[0].as<std::string>();

			std::vector<cdcchain::wallet::PublicKeySummary> result = get_client()->wallet_account_list_public_keys(account_name);
			return fc::variant(result);
		}

		fc::variant CommonApiRpcServer::wallet_account_list_public_keys_named(fc::rpc::json_connection* json_connection, const fc::variant_object& parameters)
		{
			// check all of this method's prerequisites
			verify_json_connection_is_authenticated(json_connection);
			verify_wallet_is_open();
			// done checking prerequisites

			if (!parameters.contains("account_name"))
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 'account_name'");
			std::string account_name = parameters["account_name"].as<std::string>();

			std::vector<cdcchain::wallet::PublicKeySummary> result = get_client()->wallet_account_list_public_keys(account_name);
			return fc::variant(result);
		}

		fc::variant CommonApiRpcServer::wallet_delegate_withdraw_pay_positional(fc::rpc::json_connection* json_connection, const fc::variants& parameters)
		{
			// check all of this method's prerequisites
			verify_json_connection_is_authenticated(json_connection);
			verify_wallet_is_open();
			verify_wallet_is_unlocked();
			// done checking prerequisites

			if (parameters.size() <= 0)
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 1 (delegate_name)");
			std::string delegate_name = parameters[0].as<std::string>();
			if (parameters.size() <= 1)
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 2 (to_account_name)");
			std::string to_account_name = parameters[1].as<std::string>();
			if (parameters.size() <= 2)
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 3 (amount_to_withdraw)");
			std::string amount_to_withdraw = parameters[2].as<std::string>();

			cdcchain::wallet::WalletTransactionEntry result = get_client()->wallet_delegate_withdraw_pay(delegate_name, to_account_name, amount_to_withdraw);
			return fc::variant(result);
		}

		fc::variant CommonApiRpcServer::wallet_delegate_withdraw_pay_named(fc::rpc::json_connection* json_connection, const fc::variant_object& parameters)
		{
			// check all of this method's prerequisites
			verify_json_connection_is_authenticated(json_connection);
			verify_wallet_is_open();
			verify_wallet_is_unlocked();
			// done checking prerequisites

			if (!parameters.contains("delegate_name"))
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 'delegate_name'");
			std::string delegate_name = parameters["delegate_name"].as<std::string>();
			if (!parameters.contains("to_account_name"))
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 'to_account_name'");
			std::string to_account_name = parameters["to_account_name"].as<std::string>();
			if (!parameters.contains("amount_to_withdraw"))
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 'amount_to_withdraw'");
			std::string amount_to_withdraw = parameters["amount_to_withdraw"].as<std::string>();

			cdcchain::wallet::WalletTransactionEntry result = get_client()->wallet_delegate_withdraw_pay(delegate_name, to_account_name, amount_to_withdraw);
			return fc::variant(result);
		}

		fc::variant CommonApiRpcServer::wallet_delegate_pay_balance_query_positional(fc::rpc::json_connection* json_connection, const fc::variants& parameters)
		{
			// check all of this method's prerequisites
			verify_json_connection_is_authenticated(json_connection);
			verify_wallet_is_open();
			verify_wallet_is_unlocked();
			// done checking prerequisites

			if (parameters.size() <= 0)
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 1 (delegate_name)");
			std::string delegate_name = parameters[0].as<std::string>();

			cdcchain::consensus::DelegatePaySalary result = get_client()->wallet_delegate_pay_balance_query(delegate_name);
			return fc::variant(result);
		}

		fc::variant CommonApiRpcServer::wallet_delegate_pay_balance_query_named(fc::rpc::json_connection* json_connection, const fc::variant_object& parameters)
		{
			// check all of this method's prerequisites
			verify_json_connection_is_authenticated(json_connection);
			verify_wallet_is_open();
			verify_wallet_is_unlocked();
			// done checking prerequisites

			if (!parameters.contains("delegate_name"))
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 'delegate_name'");
			std::string delegate_name = parameters["delegate_name"].as<std::string>();

			cdcchain::consensus::DelegatePaySalary result = get_client()->wallet_delegate_pay_balance_query(delegate_name);
			return fc::variant(result);
		}

		fc::variant CommonApiRpcServer::wallet_active_delegate_salary_positional(fc::rpc::json_connection* json_connection, const fc::variants& parameters)
		{
			// check all of this method's prerequisites
			verify_json_connection_is_authenticated(json_connection);
			verify_wallet_is_open();
			verify_wallet_is_unlocked();
			// done checking prerequisites


			std::map<std::string, cdcchain::consensus::DelegatePaySalary> result = get_client()->wallet_active_delegate_salary();
			return fc::variant(result);
		}

		fc::variant CommonApiRpcServer::wallet_active_delegate_salary_named(fc::rpc::json_connection* json_connection, const fc::variant_object& parameters)
		{
			// check all of this method's prerequisites
			verify_json_connection_is_authenticated(json_connection);
			verify_wallet_is_open();
			verify_wallet_is_unlocked();
			// done checking prerequisites


			std::map<std::string, cdcchain::consensus::DelegatePaySalary> result = get_client()->wallet_active_delegate_salary();
			return fc::variant(result);
		}

		fc::variant CommonApiRpcServer::wallet_get_delegate_statue_positional(fc::rpc::json_connection* json_connection, const fc::variants& parameters)
		{
			// check all of this method's prerequisites
			verify_json_connection_is_authenticated(json_connection);
			verify_wallet_is_open();
			// done checking prerequisites

			if (parameters.size() <= 0)
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 1 (account_name)");
			std::string account_name = parameters[0].as<std::string>();

			bool result = get_client()->wallet_get_delegate_statue(account_name);
			return fc::variant(result);
		}

		fc::variant CommonApiRpcServer::wallet_get_delegate_statue_named(fc::rpc::json_connection* json_connection, const fc::variant_object& parameters)
		{
			// check all of this method's prerequisites
			verify_json_connection_is_authenticated(json_connection);
			verify_wallet_is_open();
			// done checking prerequisites

			if (!parameters.contains("account_name"))
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 'account_name'");
			std::string account_name = parameters["account_name"].as<std::string>();

			bool result = get_client()->wallet_get_delegate_statue(account_name);
			return fc::variant(result);
		}

		fc::variant CommonApiRpcServer::wallet_set_transaction_imessage_fee_coe_positional(fc::rpc::json_connection* json_connection, const fc::variants& parameters)
		{
			// check all of this method's prerequisites
			verify_json_connection_is_authenticated(json_connection);
			verify_wallet_is_open();
			// done checking prerequisites

			if (parameters.size() <= 0)
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 1 (fee_coe)");
			std::string fee_coe = parameters[0].as<std::string>();

			get_client()->wallet_set_transaction_imessage_fee_coe(fee_coe);
			return fc::variant();
		}

		fc::variant CommonApiRpcServer::wallet_set_transaction_imessage_fee_coe_named(fc::rpc::json_connection* json_connection, const fc::variant_object& parameters)
		{
			// check all of this method's prerequisites
			verify_json_connection_is_authenticated(json_connection);
			verify_wallet_is_open();
			// done checking prerequisites

			if (!parameters.contains("fee_coe"))
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 'fee_coe'");
			std::string fee_coe = parameters["fee_coe"].as<std::string>();

			get_client()->wallet_set_transaction_imessage_fee_coe(fee_coe);
			return fc::variant();
		}

		fc::variant CommonApiRpcServer::wallet_get_transaction_imessage_fee_coe_positional(fc::rpc::json_connection* json_connection, const fc::variants& parameters)
		{
			// check all of this method's prerequisites
			verify_json_connection_is_authenticated(json_connection);
			verify_wallet_is_open();
			// done checking prerequisites


			double result = get_client()->wallet_get_transaction_imessage_fee_coe();
			return fc::variant(result);
		}

		fc::variant CommonApiRpcServer::wallet_get_transaction_imessage_fee_coe_named(fc::rpc::json_connection* json_connection, const fc::variant_object& parameters)
		{
			// check all of this method's prerequisites
			verify_json_connection_is_authenticated(json_connection);
			verify_wallet_is_open();
			// done checking prerequisites


			double result = get_client()->wallet_get_transaction_imessage_fee_coe();
			return fc::variant(result);
		}

		fc::variant CommonApiRpcServer::wallet_set_transaction_imessage_soft_max_length_positional(fc::rpc::json_connection* json_connection, const fc::variants& parameters)
		{
			// check all of this method's prerequisites
			verify_json_connection_is_authenticated(json_connection);
			verify_wallet_is_open();
			// done checking prerequisites

			if (parameters.size() <= 0)
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 1 (soft_length)");
			int64_t soft_length = parameters[0].as<int64_t>();

			get_client()->wallet_set_transaction_imessage_soft_max_length(soft_length);
			return fc::variant();
		}

		fc::variant CommonApiRpcServer::wallet_set_transaction_imessage_soft_max_length_named(fc::rpc::json_connection* json_connection, const fc::variant_object& parameters)
		{
			// check all of this method's prerequisites
			verify_json_connection_is_authenticated(json_connection);
			verify_wallet_is_open();
			// done checking prerequisites

			if (!parameters.contains("soft_length"))
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 'soft_length'");
			int64_t soft_length = parameters["soft_length"].as<int64_t>();

			get_client()->wallet_set_transaction_imessage_soft_max_length(soft_length);
			return fc::variant();
		}

		fc::variant CommonApiRpcServer::wallet_get_transaction_imessage_soft_max_length_positional(fc::rpc::json_connection* json_connection, const fc::variants& parameters)
		{
			// check all of this method's prerequisites
			verify_json_connection_is_authenticated(json_connection);
			verify_wallet_is_open();
			// done checking prerequisites


			int64_t result = get_client()->wallet_get_transaction_imessage_soft_max_length();
			return fc::variant(result);
		}

		fc::variant CommonApiRpcServer::wallet_get_transaction_imessage_soft_max_length_named(fc::rpc::json_connection* json_connection, const fc::variant_object& parameters)
		{
			// check all of this method's prerequisites
			verify_json_connection_is_authenticated(json_connection);
			verify_wallet_is_open();
			// done checking prerequisites


			int64_t result = get_client()->wallet_get_transaction_imessage_soft_max_length();
			return fc::variant(result);
		}

		fc::variant CommonApiRpcServer::wallet_set_transaction_fee_positional(fc::rpc::json_connection* json_connection, const fc::variants& parameters)
		{
			// check all of this method's prerequisites
			verify_json_connection_is_authenticated(json_connection);
			verify_wallet_is_open();
			// done checking prerequisites

			if (parameters.size() <= 0)
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 1 (fee)");
			std::string fee = parameters[0].as<std::string>();

			cdcchain::consensus::Asset result = get_client()->wallet_set_transaction_fee(fee);
			return fc::variant(result);
		}

		fc::variant CommonApiRpcServer::wallet_set_transaction_fee_named(fc::rpc::json_connection* json_connection, const fc::variant_object& parameters)
		{
			// check all of this method's prerequisites
			verify_json_connection_is_authenticated(json_connection);
			verify_wallet_is_open();
			// done checking prerequisites

			if (!parameters.contains("fee"))
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 'fee'");
			std::string fee = parameters["fee"].as<std::string>();

			cdcchain::consensus::Asset result = get_client()->wallet_set_transaction_fee(fee);
			return fc::variant(result);
		}

		fc::variant CommonApiRpcServer::wallet_get_transaction_fee_positional(fc::rpc::json_connection* json_connection, const fc::variants& parameters)
		{
			// check all of this method's prerequisites
			verify_json_connection_is_authenticated(json_connection);
			verify_wallet_is_open();
			// done checking prerequisites

			std::string symbol = (parameters.size() <= 0) ?
				(fc::json::from_string("\"\"").as<std::string>()) :
				parameters[0].as<std::string>();

			cdcchain::consensus::Asset result = get_client()->wallet_get_transaction_fee(symbol);
			return fc::variant(result);
		}

		fc::variant CommonApiRpcServer::wallet_get_transaction_fee_named(fc::rpc::json_connection* json_connection, const fc::variant_object& parameters)
		{
			// check all of this method's prerequisites
			verify_json_connection_is_authenticated(json_connection);
			verify_wallet_is_open();
			// done checking prerequisites

			std::string symbol = parameters.contains("symbol") ?
				(fc::json::from_string("\"\"").as<std::string>()) :
				parameters["symbol"].as<std::string>();

			cdcchain::consensus::Asset result = get_client()->wallet_get_transaction_fee(symbol);
			return fc::variant(result);
		}

		fc::variant CommonApiRpcServer::wallet_dump_private_key_positional(fc::rpc::json_connection* json_connection, const fc::variants& parameters)
		{
			// check all of this method's prerequisites
			verify_json_connection_is_authenticated(json_connection);
			verify_wallet_is_open();
			verify_wallet_is_unlocked();
			// done checking prerequisites

			if (parameters.size() <= 0)
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 1 (input)");
			std::string input = parameters[0].as<std::string>();

			fc::optional<std::string> result = get_client()->wallet_dump_private_key(input);
			return fc::variant(result);
		}

		fc::variant CommonApiRpcServer::wallet_dump_private_key_named(fc::rpc::json_connection* json_connection, const fc::variant_object& parameters)
		{
			// check all of this method's prerequisites
			verify_json_connection_is_authenticated(json_connection);
			verify_wallet_is_open();
			verify_wallet_is_unlocked();
			// done checking prerequisites

			if (!parameters.contains("input"))
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 'input'");
			std::string input = parameters["input"].as<std::string>();

			fc::optional<std::string> result = get_client()->wallet_dump_private_key(input);
			return fc::variant(result);
		}

		fc::variant CommonApiRpcServer::wallet_dump_account_private_key_positional(fc::rpc::json_connection* json_connection, const fc::variants& parameters)
		{
			// check all of this method's prerequisites
			verify_json_connection_is_authenticated(json_connection);
			verify_wallet_is_open();
			verify_wallet_is_unlocked();
			// done checking prerequisites

			if (parameters.size() <= 0)
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 1 (account_name)");
			std::string account_name = parameters[0].as<std::string>();
			if (parameters.size() <= 1)
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 2 (key_type)");
			cdcchain::wallet::AccountKeyType key_type = parameters[1].as<cdcchain::wallet::AccountKeyType>();

			fc::optional<std::string> result = get_client()->wallet_dump_account_private_key(account_name, key_type);
			return fc::variant(result);
		}

		fc::variant CommonApiRpcServer::wallet_dump_account_private_key_named(fc::rpc::json_connection* json_connection, const fc::variant_object& parameters)
		{
			// check all of this method's prerequisites
			verify_json_connection_is_authenticated(json_connection);
			verify_wallet_is_open();
			verify_wallet_is_unlocked();
			// done checking prerequisites

			if (!parameters.contains("account_name"))
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 'account_name'");
			std::string account_name = parameters["account_name"].as<std::string>();
			if (!parameters.contains("key_type"))
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 'key_type'");
			cdcchain::wallet::AccountKeyType key_type = parameters["key_type"].as<cdcchain::wallet::AccountKeyType>();

			fc::optional<std::string> result = get_client()->wallet_dump_account_private_key(account_name, key_type);
			return fc::variant(result);
		}

		fc::variant CommonApiRpcServer::wallet_account_vote_summary_positional(fc::rpc::json_connection* json_connection, const fc::variants& parameters)
		{
			// check all of this method's prerequisites
			verify_json_connection_is_authenticated(json_connection);
			verify_wallet_is_open();
			// done checking prerequisites

			std::string account_name = (parameters.size() <= 0) ?
				(fc::json::from_string("\"\"").as<std::string>()) :
				parameters[0].as<std::string>();

			cdcchain::wallet::AccountVoteSummaryType result = get_client()->wallet_account_vote_summary(account_name);
			return fc::variant(result);
		}

		fc::variant CommonApiRpcServer::wallet_account_vote_summary_named(fc::rpc::json_connection* json_connection, const fc::variant_object& parameters)
		{
			// check all of this method's prerequisites
			verify_json_connection_is_authenticated(json_connection);
			verify_wallet_is_open();
			// done checking prerequisites

			std::string account_name = parameters.contains("account_name") ?
				(fc::json::from_string("\"\"").as<std::string>()) :
				parameters["account_name"].as<std::string>();

			cdcchain::wallet::AccountVoteSummaryType result = get_client()->wallet_account_vote_summary(account_name);
			return fc::variant(result);
		}

		fc::variant CommonApiRpcServer::wallet_check_vote_status_positional(fc::rpc::json_connection* json_connection, const fc::variants& parameters)
		{
			// check all of this method's prerequisites
			verify_json_connection_is_authenticated(json_connection);
			verify_wallet_is_open();
			// done checking prerequisites

			if (parameters.size() <= 0)
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 1 (account)");
			std::string account = parameters[0].as<std::string>();

			cdcchain::wallet::VoteSummary result = get_client()->wallet_check_vote_status(account);
			return fc::variant(result);
		}

		fc::variant CommonApiRpcServer::wallet_check_vote_status_named(fc::rpc::json_connection* json_connection, const fc::variant_object& parameters)
		{
			// check all of this method's prerequisites
			verify_json_connection_is_authenticated(json_connection);
			verify_wallet_is_open();
			// done checking prerequisites

			if (!parameters.contains("account"))
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 'account'");
			std::string account = parameters["account"].as<std::string>();

			cdcchain::wallet::VoteSummary result = get_client()->wallet_check_vote_status(account);
			return fc::variant(result);
		}

		fc::variant CommonApiRpcServer::wallet_set_setting_positional(fc::rpc::json_connection* json_connection, const fc::variants& parameters)
		{
			// check all of this method's prerequisites
			verify_json_connection_is_authenticated(json_connection);
			verify_wallet_is_open();
			// done checking prerequisites

			if (parameters.size() <= 0)
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 1 (name)");
			std::string name = parameters[0].as<std::string>();
			if (parameters.size() <= 1)
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 2 (value)");
			fc::variant value = parameters[1].as<fc::variant>();

			get_client()->wallet_set_setting(name, value);
			return fc::variant();
		}

		fc::variant CommonApiRpcServer::wallet_set_setting_named(fc::rpc::json_connection* json_connection, const fc::variant_object& parameters)
		{
			// check all of this method's prerequisites
			verify_json_connection_is_authenticated(json_connection);
			verify_wallet_is_open();
			// done checking prerequisites

			if (!parameters.contains("name"))
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 'name'");
			std::string name = parameters["name"].as<std::string>();
			if (!parameters.contains("value"))
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 'value'");
			fc::variant value = parameters["value"].as<fc::variant>();

			get_client()->wallet_set_setting(name, value);
			return fc::variant();
		}

		fc::variant CommonApiRpcServer::wallet_get_setting_positional(fc::rpc::json_connection* json_connection, const fc::variants& parameters)
		{
			// check all of this method's prerequisites
			verify_json_connection_is_authenticated(json_connection);
			verify_wallet_is_open();
			// done checking prerequisites

			if (parameters.size() <= 0)
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 1 (name)");
			std::string name = parameters[0].as<std::string>();

			fc::optional<fc::variant> result = get_client()->wallet_get_setting(name);
			return fc::variant(result);
		}

		fc::variant CommonApiRpcServer::wallet_get_setting_named(fc::rpc::json_connection* json_connection, const fc::variant_object& parameters)
		{
			// check all of this method's prerequisites
			verify_json_connection_is_authenticated(json_connection);
			verify_wallet_is_open();
			// done checking prerequisites

			if (!parameters.contains("name"))
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 'name'");
			std::string name = parameters["name"].as<std::string>();

			fc::optional<fc::variant> result = get_client()->wallet_get_setting(name);
			return fc::variant(result);
		}

		fc::variant CommonApiRpcServer::wallet_delegate_set_block_production_positional(fc::rpc::json_connection* json_connection, const fc::variants& parameters)
		{
			// check all of this method's prerequisites
			verify_json_connection_is_authenticated(json_connection);
			verify_wallet_is_open();
			// done checking prerequisites

			if (parameters.size() <= 0)
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 1 (delegate_name)");
			std::string delegate_name = parameters[0].as<std::string>();
			if (parameters.size() <= 1)
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 2 (enabled)");
			bool enabled = parameters[1].as<bool>();

			get_client()->wallet_delegate_set_block_production(delegate_name, enabled);
			return fc::variant();
		}

		fc::variant CommonApiRpcServer::wallet_delegate_set_block_production_named(fc::rpc::json_connection* json_connection, const fc::variant_object& parameters)
		{
			// check all of this method's prerequisites
			verify_json_connection_is_authenticated(json_connection);
			verify_wallet_is_open();
			// done checking prerequisites

			if (!parameters.contains("delegate_name"))
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 'delegate_name'");
			std::string delegate_name = parameters["delegate_name"].as<std::string>();
			if (!parameters.contains("enabled"))
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 'enabled'");
			bool enabled = parameters["enabled"].as<bool>();

			get_client()->wallet_delegate_set_block_production(delegate_name, enabled);
			return fc::variant();
		}

		fc::variant CommonApiRpcServer::wallet_set_transaction_scanning_positional(fc::rpc::json_connection* json_connection, const fc::variants& parameters)
		{
			// check all of this method's prerequisites
			verify_json_connection_is_authenticated(json_connection);
			verify_wallet_is_open();
			// done checking prerequisites

			if (parameters.size() <= 0)
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 1 (enabled)");
			bool enabled = parameters[0].as<bool>();

			bool result = get_client()->wallet_set_transaction_scanning(enabled);
			return fc::variant(result);
		}

		fc::variant CommonApiRpcServer::wallet_set_transaction_scanning_named(fc::rpc::json_connection* json_connection, const fc::variant_object& parameters)
		{
			// check all of this method's prerequisites
			verify_json_connection_is_authenticated(json_connection);
			verify_wallet_is_open();
			// done checking prerequisites

			if (!parameters.contains("enabled"))
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 'enabled'");
			bool enabled = parameters["enabled"].as<bool>();

			bool result = get_client()->wallet_set_transaction_scanning(enabled);
			return fc::variant(result);
		}

		fc::variant CommonApiRpcServer::wallet_sign_hash_positional(fc::rpc::json_connection* json_connection, const fc::variants& parameters)
		{
			// check all of this method's prerequisites
			verify_json_connection_is_authenticated(json_connection);
			verify_wallet_is_open();
			verify_wallet_is_unlocked();
			// done checking prerequisites

			if (parameters.size() <= 0)
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 1 (signer)");
			std::string signer = parameters[0].as<std::string>();
			if (parameters.size() <= 1)
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 2 (hash)");
			fc::sha256 hash = parameters[1].as<fc::sha256>();

			fc::ecc::compact_signature result = get_client()->wallet_sign_hash(signer, hash);
			return fc::variant(result);
		}

		fc::variant CommonApiRpcServer::wallet_sign_hash_named(fc::rpc::json_connection* json_connection, const fc::variant_object& parameters)
		{
			// check all of this method's prerequisites
			verify_json_connection_is_authenticated(json_connection);
			verify_wallet_is_open();
			verify_wallet_is_unlocked();
			// done checking prerequisites

			if (!parameters.contains("signer"))
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 'signer'");
			std::string signer = parameters["signer"].as<std::string>();
			if (!parameters.contains("hash"))
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 'hash'");
			fc::sha256 hash = parameters["hash"].as<fc::sha256>();

			fc::ecc::compact_signature result = get_client()->wallet_sign_hash(signer, hash);
			return fc::variant(result);
		}

		fc::variant CommonApiRpcServer::wallet_login_start_positional(fc::rpc::json_connection* json_connection, const fc::variants& parameters)
		{
			// check all of this method's prerequisites
			verify_json_connection_is_authenticated(json_connection);
			verify_wallet_is_open();
			verify_wallet_is_unlocked();
			// done checking prerequisites

			if (parameters.size() <= 0)
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 1 (server_account)");
			std::string server_account = parameters[0].as<std::string>();

			std::string result = get_client()->wallet_login_start(server_account);
			return fc::variant(result);
		}

		fc::variant CommonApiRpcServer::wallet_login_start_named(fc::rpc::json_connection* json_connection, const fc::variant_object& parameters)
		{
			// check all of this method's prerequisites
			verify_json_connection_is_authenticated(json_connection);
			verify_wallet_is_open();
			verify_wallet_is_unlocked();
			// done checking prerequisites

			if (!parameters.contains("server_account"))
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 'server_account'");
			std::string server_account = parameters["server_account"].as<std::string>();

			std::string result = get_client()->wallet_login_start(server_account);
			return fc::variant(result);
		}

		fc::variant CommonApiRpcServer::wallet_login_finish_positional(fc::rpc::json_connection* json_connection, const fc::variants& parameters)
		{
			// check all of this method's prerequisites
			verify_json_connection_is_authenticated(json_connection);
			verify_wallet_is_open();
			verify_wallet_is_unlocked();
			// done checking prerequisites

			if (parameters.size() <= 0)
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 1 (server_key)");
			cdcchain::consensus::PublicKeyType server_key = parameters[0].as<cdcchain::consensus::PublicKeyType>();
			if (parameters.size() <= 1)
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 2 (client_key)");
			cdcchain::consensus::PublicKeyType client_key = parameters[1].as<cdcchain::consensus::PublicKeyType>();
			if (parameters.size() <= 2)
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 3 (client_signature)");
			fc::ecc::compact_signature client_signature = parameters[2].as<fc::ecc::compact_signature>();

			fc::variant result = get_client()->wallet_login_finish(server_key, client_key, client_signature);
			return fc::variant(result);
		}

		fc::variant CommonApiRpcServer::wallet_login_finish_named(fc::rpc::json_connection* json_connection, const fc::variant_object& parameters)
		{
			// check all of this method's prerequisites
			verify_json_connection_is_authenticated(json_connection);
			verify_wallet_is_open();
			verify_wallet_is_unlocked();
			// done checking prerequisites

			if (!parameters.contains("server_key"))
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 'server_key'");
			cdcchain::consensus::PublicKeyType server_key = parameters["server_key"].as<cdcchain::consensus::PublicKeyType>();
			if (!parameters.contains("client_key"))
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 'client_key'");
			cdcchain::consensus::PublicKeyType client_key = parameters["client_key"].as<cdcchain::consensus::PublicKeyType>();
			if (!parameters.contains("client_signature"))
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 'client_signature'");
			fc::ecc::compact_signature client_signature = parameters["client_signature"].as<fc::ecc::compact_signature>();

			fc::variant result = get_client()->wallet_login_finish(server_key, client_key, client_signature);
			return fc::variant(result);
		}

		fc::variant CommonApiRpcServer::wallet_balance_set_vote_info_positional(fc::rpc::json_connection* json_connection, const fc::variants& parameters)
		{
			// check all of this method's prerequisites
			verify_json_connection_is_authenticated(json_connection);
			verify_wallet_is_open();
			// done checking prerequisites

			if (parameters.size() <= 0)
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 1 (balance_id)");
			cdcchain::consensus::Address balance_id = parameters[0].as<cdcchain::consensus::Address>();
			std::string voter_address = (parameters.size() <= 1) ?
				(fc::json::from_string("\"\"").as<std::string>()) :
				parameters[1].as<std::string>();
			cdcchain::wallet::VoteStrategy strategy = (parameters.size() <= 2) ?
				(fc::json::from_string("\"vote_all\"").as<cdcchain::wallet::VoteStrategy>()) :
				parameters[2].as<cdcchain::wallet::VoteStrategy>();
			bool sign_and_broadcast = (parameters.size() <= 3) ?
				(fc::json::from_string("\"true\"").as<bool>()) :
				parameters[3].as<bool>();
			std::string builder_path = (parameters.size() <= 4) ?
				(fc::json::from_string("\"\"").as<std::string>()) :
				parameters[4].as<std::string>();

			cdcchain::wallet::TransactionBuilder result = get_client()->wallet_balance_set_vote_info(balance_id, voter_address, strategy, sign_and_broadcast, builder_path);
			return fc::variant(result);
		}

		fc::variant CommonApiRpcServer::wallet_balance_set_vote_info_named(fc::rpc::json_connection* json_connection, const fc::variant_object& parameters)
		{
			// check all of this method's prerequisites
			verify_json_connection_is_authenticated(json_connection);
			verify_wallet_is_open();
			// done checking prerequisites

			if (!parameters.contains("balance_id"))
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 'balance_id'");
			cdcchain::consensus::Address balance_id = parameters["balance_id"].as<cdcchain::consensus::Address>();
			std::string voter_address = parameters.contains("voter_address") ?
				(fc::json::from_string("\"\"").as<std::string>()) :
				parameters["voter_address"].as<std::string>();
			cdcchain::wallet::VoteStrategy strategy = parameters.contains("strategy") ?
				(fc::json::from_string("\"vote_all\"").as<cdcchain::wallet::VoteStrategy>()) :
				parameters["strategy"].as<cdcchain::wallet::VoteStrategy>();
			bool sign_and_broadcast = parameters.contains("sign_and_broadcast") ?
				(fc::json::from_string("\"true\"").as<bool>()) :
				parameters["sign_and_broadcast"].as<bool>();
			std::string builder_path = parameters.contains("builder_path") ?
				(fc::json::from_string("\"\"").as<std::string>()) :
				parameters["builder_path"].as<std::string>();

			cdcchain::wallet::TransactionBuilder result = get_client()->wallet_balance_set_vote_info(balance_id, voter_address, strategy, sign_and_broadcast, builder_path);
			return fc::variant(result);
		}

		fc::variant CommonApiRpcServer::wallet_publish_slate_positional(fc::rpc::json_connection* json_connection, const fc::variants& parameters)
		{
			// check all of this method's prerequisites
			verify_json_connection_is_authenticated(json_connection);
			verify_wallet_is_open();
			verify_wallet_is_unlocked();
			// done checking prerequisites

			if (parameters.size() <= 0)
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 1 (publishing_account_name)");
			std::string publishing_account_name = parameters[0].as<std::string>();
			std::string paying_account_name = (parameters.size() <= 1) ?
				(fc::json::from_string("\"\"").as<std::string>()) :
				parameters[1].as<std::string>();

			cdcchain::wallet::WalletTransactionEntry result = get_client()->wallet_publish_slate(publishing_account_name, paying_account_name);
			return fc::variant(result);
		}

		fc::variant CommonApiRpcServer::wallet_publish_slate_named(fc::rpc::json_connection* json_connection, const fc::variant_object& parameters)
		{
			// check all of this method's prerequisites
			verify_json_connection_is_authenticated(json_connection);
			verify_wallet_is_open();
			verify_wallet_is_unlocked();
			// done checking prerequisites

			if (!parameters.contains("publishing_account_name"))
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 'publishing_account_name'");
			std::string publishing_account_name = parameters["publishing_account_name"].as<std::string>();
			std::string paying_account_name = parameters.contains("paying_account_name") ?
				(fc::json::from_string("\"\"").as<std::string>()) :
				parameters["paying_account_name"].as<std::string>();

			cdcchain::wallet::WalletTransactionEntry result = get_client()->wallet_publish_slate(publishing_account_name, paying_account_name);
			return fc::variant(result);
		}

		fc::variant CommonApiRpcServer::wallet_publish_version_positional(fc::rpc::json_connection* json_connection, const fc::variants& parameters)
		{
			// check all of this method's prerequisites
			verify_json_connection_is_authenticated(json_connection);
			verify_wallet_is_open();
			verify_wallet_is_unlocked();
			// done checking prerequisites

			if (parameters.size() <= 0)
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 1 (publishing_account_name)");
			std::string publishing_account_name = parameters[0].as<std::string>();
			std::string paying_account_name = (parameters.size() <= 1) ?
				(fc::json::from_string("\"\"").as<std::string>()) :
				parameters[1].as<std::string>();

			cdcchain::wallet::WalletTransactionEntry result = get_client()->wallet_publish_version(publishing_account_name, paying_account_name);
			return fc::variant(result);
		}

		fc::variant CommonApiRpcServer::wallet_publish_version_named(fc::rpc::json_connection* json_connection, const fc::variant_object& parameters)
		{
			// check all of this method's prerequisites
			verify_json_connection_is_authenticated(json_connection);
			verify_wallet_is_open();
			verify_wallet_is_unlocked();
			// done checking prerequisites

			if (!parameters.contains("publishing_account_name"))
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 'publishing_account_name'");
			std::string publishing_account_name = parameters["publishing_account_name"].as<std::string>();
			std::string paying_account_name = parameters.contains("paying_account_name") ?
				(fc::json::from_string("\"\"").as<std::string>()) :
				parameters["paying_account_name"].as<std::string>();

			cdcchain::wallet::WalletTransactionEntry result = get_client()->wallet_publish_version(publishing_account_name, paying_account_name);
			return fc::variant(result);
		}

		fc::variant CommonApiRpcServer::wallet_collect_genesis_balances_positional(fc::rpc::json_connection* json_connection, const fc::variants& parameters)
		{
			// check all of this method's prerequisites
			verify_json_connection_is_authenticated(json_connection);
			verify_wallet_is_open();
			verify_wallet_is_unlocked();
			// done checking prerequisites

			if (parameters.size() <= 0)
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 1 (account_name)");
			std::string account_name = parameters[0].as<std::string>();

			cdcchain::wallet::WalletTransactionEntry result = get_client()->wallet_collect_genesis_balances(account_name);
			return fc::variant(result);
		}

		fc::variant CommonApiRpcServer::wallet_collect_genesis_balances_named(fc::rpc::json_connection* json_connection, const fc::variant_object& parameters)
		{
			// check all of this method's prerequisites
			verify_json_connection_is_authenticated(json_connection);
			verify_wallet_is_open();
			verify_wallet_is_unlocked();
			// done checking prerequisites

			if (!parameters.contains("account_name"))
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 'account_name'");
			std::string account_name = parameters["account_name"].as<std::string>();

			cdcchain::wallet::WalletTransactionEntry result = get_client()->wallet_collect_genesis_balances(account_name);
			return fc::variant(result);
		}

		fc::variant CommonApiRpcServer::wallet_recover_accounts_positional(fc::rpc::json_connection* json_connection, const fc::variants& parameters)
		{
			// check all of this method's prerequisites
			verify_json_connection_is_authenticated(json_connection);
			verify_wallet_is_open();
			verify_wallet_is_unlocked();
			// done checking prerequisites

			if (parameters.size() <= 0)
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 1 (accounts_to_recover)");
			int32_t accounts_to_recover = parameters[0].as<int32_t>();
			int32_t maximum_number_of_attempts = (parameters.size() <= 1) ?
				(fc::json::from_string("1000").as<int32_t>()) :
				parameters[1].as<int32_t>();

			int32_t result = get_client()->wallet_recover_accounts(accounts_to_recover, maximum_number_of_attempts);
			return fc::variant(result);
		}

		fc::variant CommonApiRpcServer::wallet_recover_accounts_named(fc::rpc::json_connection* json_connection, const fc::variant_object& parameters)
		{
			// check all of this method's prerequisites
			verify_json_connection_is_authenticated(json_connection);
			verify_wallet_is_open();
			verify_wallet_is_unlocked();
			// done checking prerequisites

			if (!parameters.contains("accounts_to_recover"))
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 'accounts_to_recover'");
			int32_t accounts_to_recover = parameters["accounts_to_recover"].as<int32_t>();
			int32_t maximum_number_of_attempts = parameters.contains("maximum_number_of_attempts") ?
				(fc::json::from_string("1000").as<int32_t>()) :
				parameters["maximum_number_of_attempts"].as<int32_t>();

			int32_t result = get_client()->wallet_recover_accounts(accounts_to_recover, maximum_number_of_attempts);
			return fc::variant(result);
		}

		fc::variant CommonApiRpcServer::wallet_verify_titan_deposit_positional(fc::rpc::json_connection* json_connection, const fc::variants& parameters)
		{
			// check all of this method's prerequisites
			verify_json_connection_is_authenticated(json_connection);
			verify_wallet_is_open();
			verify_wallet_is_unlocked();
			// done checking prerequisites

			if (parameters.size() <= 0)
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 1 (transaction_id_prefix)");
			std::string transaction_id_prefix = parameters[0].as<std::string>();

			fc::optional<fc::variant_object> result = get_client()->wallet_verify_titan_deposit(transaction_id_prefix);
			return fc::variant(result);
		}

		fc::variant CommonApiRpcServer::wallet_verify_titan_deposit_named(fc::rpc::json_connection* json_connection, const fc::variant_object& parameters)
		{
			// check all of this method's prerequisites
			verify_json_connection_is_authenticated(json_connection);
			verify_wallet_is_open();
			verify_wallet_is_unlocked();
			// done checking prerequisites

			if (!parameters.contains("transaction_id_prefix"))
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 'transaction_id_prefix'");
			std::string transaction_id_prefix = parameters["transaction_id_prefix"].as<std::string>();

			fc::optional<fc::variant_object> result = get_client()->wallet_verify_titan_deposit(transaction_id_prefix);
			return fc::variant(result);
		}

		fc::variant CommonApiRpcServer::wallet_repair_entrys_positional(fc::rpc::json_connection* json_connection, const fc::variants& parameters)
		{
			// check all of this method's prerequisites
			verify_json_connection_is_authenticated(json_connection);
			verify_wallet_is_open();
			verify_wallet_is_unlocked();
			// done checking prerequisites

			std::string collecting_account_name = (parameters.size() <= 0) ?
				(fc::json::from_string("\"\"").as<std::string>()) :
				parameters[0].as<std::string>();

			get_client()->wallet_repair_entrys(collecting_account_name);
			return fc::variant();
		}

		fc::variant CommonApiRpcServer::wallet_repair_entrys_named(fc::rpc::json_connection* json_connection, const fc::variant_object& parameters)
		{
			// check all of this method's prerequisites
			verify_json_connection_is_authenticated(json_connection);
			verify_wallet_is_open();
			verify_wallet_is_unlocked();
			// done checking prerequisites

			std::string collecting_account_name = parameters.contains("collecting_account_name") ?
				(fc::json::from_string("\"\"").as<std::string>()) :
				parameters["collecting_account_name"].as<std::string>();

			get_client()->wallet_repair_entrys(collecting_account_name);
			return fc::variant();
		}

		fc::variant CommonApiRpcServer::wallet_regenerate_keys_positional(fc::rpc::json_connection* json_connection, const fc::variants& parameters)
		{
			// check all of this method's prerequisites
			verify_json_connection_is_authenticated(json_connection);
			verify_wallet_is_open();
			verify_wallet_is_unlocked();
			// done checking prerequisites

			if (parameters.size() <= 0)
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 1 (account_name)");
			std::string account_name = parameters[0].as<std::string>();
			if (parameters.size() <= 1)
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 2 (max_key_number)");
			uint32_t max_key_number = parameters[1].as<uint32_t>();

			int32_t result = get_client()->wallet_regenerate_keys(account_name, max_key_number);
			return fc::variant(result);
		}

		fc::variant CommonApiRpcServer::wallet_regenerate_keys_named(fc::rpc::json_connection* json_connection, const fc::variant_object& parameters)
		{
			// check all of this method's prerequisites
			verify_json_connection_is_authenticated(json_connection);
			verify_wallet_is_open();
			verify_wallet_is_unlocked();
			// done checking prerequisites

			if (!parameters.contains("account_name"))
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 'account_name'");
			std::string account_name = parameters["account_name"].as<std::string>();
			if (!parameters.contains("max_key_number"))
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 'max_key_number'");
			uint32_t max_key_number = parameters["max_key_number"].as<uint32_t>();

			int32_t result = get_client()->wallet_regenerate_keys(account_name, max_key_number);
			return fc::variant(result);
		}

		fc::variant CommonApiRpcServer::wallet_account_retract_positional(fc::rpc::json_connection* json_connection, const fc::variants& parameters)
		{
			// check all of this method's prerequisites
			verify_json_connection_is_authenticated(json_connection);
			verify_wallet_is_open();
			verify_wallet_is_unlocked();
			// done checking prerequisites

			if (parameters.size() <= 0)
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 1 (account_to_retract)");
			std::string account_to_retract = parameters[0].as<std::string>();
			if (parameters.size() <= 1)
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 2 (pay_from_account)");
			std::string pay_from_account = parameters[1].as<std::string>();

			cdcchain::wallet::WalletTransactionEntry result = get_client()->wallet_account_retract(account_to_retract, pay_from_account);
			return fc::variant(result);
		}

		fc::variant CommonApiRpcServer::wallet_account_retract_named(fc::rpc::json_connection* json_connection, const fc::variant_object& parameters)
		{
			// check all of this method's prerequisites
			verify_json_connection_is_authenticated(json_connection);
			verify_wallet_is_open();
			verify_wallet_is_unlocked();
			// done checking prerequisites

			if (!parameters.contains("account_to_retract"))
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 'account_to_retract'");
			std::string account_to_retract = parameters["account_to_retract"].as<std::string>();
			if (!parameters.contains("pay_from_account"))
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 'pay_from_account'");
			std::string pay_from_account = parameters["pay_from_account"].as<std::string>();

			cdcchain::wallet::WalletTransactionEntry result = get_client()->wallet_account_retract(account_to_retract, pay_from_account);
			return fc::variant(result);
		}

		fc::variant CommonApiRpcServer::wallet_account_delete_positional(fc::rpc::json_connection* json_connection, const fc::variants& parameters)
		{
			// check all of this method's prerequisites
			verify_json_connection_is_authenticated(json_connection);
			verify_wallet_is_open();
			verify_wallet_is_unlocked();
			// done checking prerequisites

			if (parameters.size() <= 0)
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 1 (account_name)");
			std::string account_name = parameters[0].as<std::string>();

			bool result = get_client()->wallet_account_delete(account_name);
			return fc::variant(result);
		}

		fc::variant CommonApiRpcServer::wallet_account_delete_named(fc::rpc::json_connection* json_connection, const fc::variant_object& parameters)
		{
			// check all of this method's prerequisites
			verify_json_connection_is_authenticated(json_connection);
			verify_wallet_is_open();
			verify_wallet_is_unlocked();
			// done checking prerequisites

			if (!parameters.contains("account_name"))
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 'account_name'");
			std::string account_name = parameters["account_name"].as<std::string>();

			bool result = get_client()->wallet_account_delete(account_name);
			return fc::variant(result);
		}

		fc::variant CommonApiRpcServer::wallet_transfer_to_address_rpc_positional(fc::rpc::json_connection* json_connection, const fc::variants& parameters)
		{
			try {
				// check all of this method's prerequisites
				verify_json_connection_is_authenticated(json_connection);
				verify_wallet_is_open();
				// done checking prerequisites

				if (parameters.size() <= 0)
					FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 1 (amount_to_transfer)");
				std::string amount_to_transfer = parameters[0].as<std::string>();
				if (parameters.size() <= 1)
					FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 2 (asset_symbol)");
				std::string asset_symbol = parameters[1].as<std::string>();
				if (parameters.size() <= 2)
					FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 3 (from_account_name)");
				std::string from_account_name = parameters[2].as<std::string>();
				if (parameters.size() <= 3)
					FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 4 (to_address)");
				std::string to_address = parameters[3].as<std::string>();
				cdcchain::consensus::Imessage memo_message = (parameters.size() <= 4) ?
					(fc::json::from_string("\"\"").as<cdcchain::consensus::Imessage>()) :
					parameters[4].as<cdcchain::consensus::Imessage>();
				cdcchain::wallet::VoteStrategy strategy = (parameters.size() <= 5) ?
					(fc::json::from_string("\"vote_recommended\"").as<cdcchain::wallet::VoteStrategy>()) :
					parameters[5].as<cdcchain::wallet::VoteStrategy>();

				std::string result = get_client()->wallet_transfer_to_address_rpc(amount_to_transfer, asset_symbol, from_account_name, to_address, memo_message, strategy);
				return fc::variant(result);
			}
			catch (fc::exception e)
			{
				std::string res = "{\"result\":\"ERROR\",\"message\":\"";
				res += e.to_string();
				res += "\"}";
				return res;
			}
		}

		fc::variant CommonApiRpcServer::wallet_transfer_to_address_rpc_named(fc::rpc::json_connection* json_connection, const fc::variant_object& parameters)
		{
			try {
				// check all of this method's prerequisites
				verify_json_connection_is_authenticated(json_connection);
				verify_wallet_is_open();
				// done checking prerequisites

				if (!parameters.contains("amount_to_transfer"))
					FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 'amount_to_transfer'");
				std::string amount_to_transfer = parameters["amount_to_transfer"].as<std::string>();
				if (!parameters.contains("asset_symbol"))
					FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 'asset_symbol'");
				std::string asset_symbol = parameters["asset_symbol"].as<std::string>();
				if (!parameters.contains("from_account_name"))
					FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 'from_account_name'");
				std::string from_account_name = parameters["from_account_name"].as<std::string>();
				if (!parameters.contains("to_address"))
					FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 'to_address'");
				std::string to_address = parameters["to_address"].as<std::string>();
				cdcchain::consensus::Imessage memo_message = parameters.contains("memo_message") ?
					(fc::json::from_string("\"\"").as<cdcchain::consensus::Imessage>()) :
					parameters["memo_message"].as<cdcchain::consensus::Imessage>();
				cdcchain::wallet::VoteStrategy strategy = parameters.contains("strategy") ?
					(fc::json::from_string("\"vote_recommended\"").as<cdcchain::wallet::VoteStrategy>()) :
					parameters["strategy"].as<cdcchain::wallet::VoteStrategy>();

				std::string result = get_client()->wallet_transfer_to_address_rpc(amount_to_transfer, asset_symbol, from_account_name, to_address, memo_message, strategy);
				return fc::variant(result);
			}
			catch (fc::exception e)
			{
				std::string res = "{\"result\":\"ERROR\",\"message\":\"";
				res += e.to_string();
				res += "\"}";
				return res;
			}
		}

		fc::variant CommonApiRpcServer::wallet_account_balance_rpc_positional(fc::rpc::json_connection* json_connection, const fc::variants& parameters)
		{
			try {
				// check all of this method's prerequisites
				verify_json_connection_is_authenticated(json_connection);
				verify_wallet_is_open();
				// done checking prerequisites

				std::string account_name = (parameters.size() <= 0) ?
					(fc::json::from_string("\"\"").as<std::string>()) :
					parameters[0].as<std::string>();

				std::string result = get_client()->wallet_account_balance_rpc(account_name);
				return fc::variant(result);
			}
			catch (fc::exception e)
			{
				std::string res = "{\"result\":\"ERROR\",\"message\":\"";
				res += e.to_string();
				res += "\"}";
				return  fc::variant(res);
			}
		}

		fc::variant CommonApiRpcServer::wallet_account_balance_rpc_named(fc::rpc::json_connection* json_connection, const fc::variant_object& parameters)
		{
			try {
				// check all of this method's prerequisites
				verify_json_connection_is_authenticated(json_connection);
				verify_wallet_is_open();
				// done checking prerequisites

				std::string account_name = parameters.contains("account_name") ?
					(fc::json::from_string("\"\"").as<std::string>()) :
					parameters["account_name"].as<std::string>();

				std::string result = get_client()->wallet_account_balance_rpc(account_name);
				return fc::variant(result);
			}
			catch (fc::exception e)
			{
				std::string res = "{\"result\":\"ERROR\",\"message\":\"";
				res += e.to_string();
				res += "\"}";
				return  fc::variant(res);
			}
		}

		fc::variant CommonApiRpcServer::wallet_transfer_to_public_account_rpc_positional(fc::rpc::json_connection* json_connection, const fc::variants& parameters)
		{
			try
			{
				// check all of this method's prerequisites
				verify_json_connection_is_authenticated(json_connection);
				verify_wallet_is_open();
				verify_wallet_is_unlocked();
				// done checking prerequisites

				if (parameters.size() <= 0)
					FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 1 (amount_to_transfer)");
				std::string amount_to_transfer = parameters[0].as<std::string>();
				if (parameters.size() <= 1)
					FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 2 (asset_symbol)");
				std::string asset_symbol = parameters[1].as<std::string>();
				if (parameters.size() <= 2)
					FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 3 (from_account_name)");
				std::string from_account_name = parameters[2].as<std::string>();
				if (parameters.size() <= 3)
					FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 4 (to_account_name)");
				std::string to_account_name = parameters[3].as<std::string>();
				cdcchain::consensus::Imessage memo_message = (parameters.size() <= 4) ?
					(fc::json::from_string("\"\"").as<cdcchain::consensus::Imessage>()) :
					parameters[4].as<cdcchain::consensus::Imessage>();
				cdcchain::wallet::VoteStrategy strategy = (parameters.size() <= 5) ?
					(fc::json::from_string("\"vote_recommended\"").as<cdcchain::wallet::VoteStrategy>()) :
					parameters[5].as<cdcchain::wallet::VoteStrategy>();

				std::string result = get_client()->wallet_transfer_to_public_account_rpc(amount_to_transfer, asset_symbol, from_account_name, to_account_name, memo_message, strategy);
				return fc::variant(result);
			}
			catch (fc::exception er)
			{
				std::string result = "{\"result\":\"ERROR\",\"message\":\"" + er.to_string() + "\"}";
				return fc::variant(result);
			}
		}

		fc::variant CommonApiRpcServer::wallet_transfer_to_public_account_rpc_named(fc::rpc::json_connection* json_connection, const fc::variant_object& parameters)
		{
			try
			{
				// check all of this method's prerequisites
				verify_json_connection_is_authenticated(json_connection);
				verify_wallet_is_open();
				verify_wallet_is_unlocked();
				// done checking prerequisites

				if (!parameters.contains("amount_to_transfer"))
					FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 'amount_to_transfer'");
				std::string amount_to_transfer = parameters["amount_to_transfer"].as<std::string>();
				if (!parameters.contains("asset_symbol"))
					FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 'asset_symbol'");
				std::string asset_symbol = parameters["asset_symbol"].as<std::string>();
				if (!parameters.contains("from_account_name"))
					FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 'from_account_name'");
				std::string from_account_name = parameters["from_account_name"].as<std::string>();
				if (!parameters.contains("to_account_name"))
					FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 'to_account_name'");
				std::string to_account_name = parameters["to_account_name"].as<std::string>();
				cdcchain::consensus::Imessage memo_message = parameters.contains("memo_message") ?
					(fc::json::from_string("\"\"").as<cdcchain::consensus::Imessage>()) :
					parameters["memo_message"].as<cdcchain::consensus::Imessage>();
				cdcchain::wallet::VoteStrategy strategy = parameters.contains("strategy") ?
					(fc::json::from_string("\"vote_recommended\"").as<cdcchain::wallet::VoteStrategy>()) :
					parameters["strategy"].as<cdcchain::wallet::VoteStrategy>();

				std::string result = get_client()->wallet_transfer_to_public_account_rpc(amount_to_transfer, asset_symbol, from_account_name, to_account_name, memo_message, strategy);
				return fc::variant(result);
			}
			catch (fc::exception er)
			{
				std::string result = "{\"result\":\"ERROR\",\"message\":\"" + er.to_string() + "\"}";
				return fc::variant(result);
			}
		}

		fc::variant CommonApiRpcServer::wallet_get_account_owner_publickey_positional(fc::rpc::json_connection* json_connection, const fc::variants& parameters)
		{
			// check all of this method's prerequisites
			verify_json_connection_is_authenticated(json_connection);
			verify_wallet_is_open();
			verify_wallet_is_unlocked();
			// done checking prerequisites

			if (parameters.size() <= 0)
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 1 (account_name)");
			std::string account_name = parameters[0].as<std::string>();

			cdcchain::consensus::PublicKeyType result = get_client()->wallet_get_account_owner_publickey(account_name);
			return fc::variant(result);
		}

		fc::variant CommonApiRpcServer::wallet_get_account_owner_publickey_named(fc::rpc::json_connection* json_connection, const fc::variant_object& parameters)
		{
			// check all of this method's prerequisites
			verify_json_connection_is_authenticated(json_connection);
			verify_wallet_is_open();
			verify_wallet_is_unlocked();
			// done checking prerequisites

			if (!parameters.contains("account_name"))
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 'account_name'");
			std::string account_name = parameters["account_name"].as<std::string>();

			cdcchain::consensus::PublicKeyType result = get_client()->wallet_get_account_owner_publickey(account_name);
			return fc::variant(result);
		}

		fc::variant CommonApiRpcServer::wallet_transfer_to_contract_positional(fc::rpc::json_connection* json_connection, const fc::variants& parameters)
		{
			// check all of this method's prerequisites
			verify_json_connection_is_authenticated(json_connection);
			verify_wallet_is_open();
			verify_wallet_is_unlocked();
			// done checking prerequisites

			if (parameters.size() <= 0)
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 1 (amount_to_transfer)");
			double amount_to_transfer = parameters[0].as<double>();
			if (parameters.size() <= 1)
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 2 (asset_symbol)");
			std::string asset_symbol = parameters[1].as<std::string>();
			if (parameters.size() <= 2)
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 3 (from_account_name)");
			std::string from_account_name = parameters[2].as<std::string>();
			if (parameters.size() <= 3)
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 4 (to_contract)");
			std::string to_contract = parameters[3].as<std::string>();
			if (parameters.size() <= 4)
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 5 (amount_for_exec)");
			double amount_for_exec = parameters[4].as<double>();

			cdcchain::wallet::WalletTransactionEntry result = get_client()->wallet_transfer_to_contract(amount_to_transfer, asset_symbol, from_account_name, to_contract, amount_for_exec);
			return fc::variant(result);
		}

		fc::variant CommonApiRpcServer::wallet_transfer_to_contract_named(fc::rpc::json_connection* json_connection, const fc::variant_object& parameters)
		{
			// check all of this method's prerequisites
			verify_json_connection_is_authenticated(json_connection);
			verify_wallet_is_open();
			verify_wallet_is_unlocked();
			// done checking prerequisites

			if (!parameters.contains("amount_to_transfer"))
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 'amount_to_transfer'");
			double amount_to_transfer = parameters["amount_to_transfer"].as<double>();
			if (!parameters.contains("asset_symbol"))
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 'asset_symbol'");
			std::string asset_symbol = parameters["asset_symbol"].as<std::string>();
			if (!parameters.contains("from_account_name"))
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 'from_account_name'");
			std::string from_account_name = parameters["from_account_name"].as<std::string>();
			if (!parameters.contains("to_contract"))
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 'to_contract'");
			std::string to_contract = parameters["to_contract"].as<std::string>();
			if (!parameters.contains("amount_for_exec"))
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 'amount_for_exec'");
			double amount_for_exec = parameters["amount_for_exec"].as<double>();

			cdcchain::wallet::WalletTransactionEntry result = get_client()->wallet_transfer_to_contract(amount_to_transfer, asset_symbol, from_account_name, to_contract, amount_for_exec);
			return fc::variant(result);
		}

		fc::variant CommonApiRpcServer::wallet_transfer_to_contract_testing_positional(fc::rpc::json_connection* json_connection, const fc::variants& parameters)
		{
			// check all of this method's prerequisites
			verify_json_connection_is_authenticated(json_connection);
			verify_wallet_is_open();
			verify_wallet_is_unlocked();
			// done checking prerequisites

			if (parameters.size() <= 0)
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 1 (amount_to_transfer)");
			double amount_to_transfer = parameters[0].as<double>();
			if (parameters.size() <= 1)
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 2 (asset_symbol)");
			std::string asset_symbol = parameters[1].as<std::string>();
			if (parameters.size() <= 2)
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 3 (from_account_name)");
			std::string from_account_name = parameters[2].as<std::string>();
			if (parameters.size() <= 3)
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 4 (to_contract)");
			std::string to_contract = parameters[3].as<std::string>();

			std::vector<cdcchain::consensus::Asset> result = get_client()->wallet_transfer_to_contract_testing(amount_to_transfer, asset_symbol, from_account_name, to_contract);
			return fc::variant(result);
		}

		fc::variant CommonApiRpcServer::wallet_transfer_to_contract_testing_named(fc::rpc::json_connection* json_connection, const fc::variant_object& parameters)
		{
			// check all of this method's prerequisites
			verify_json_connection_is_authenticated(json_connection);
			verify_wallet_is_open();
			verify_wallet_is_unlocked();
			// done checking prerequisites

			if (!parameters.contains("amount_to_transfer"))
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 'amount_to_transfer'");
			double amount_to_transfer = parameters["amount_to_transfer"].as<double>();
			if (!parameters.contains("asset_symbol"))
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 'asset_symbol'");
			std::string asset_symbol = parameters["asset_symbol"].as<std::string>();
			if (!parameters.contains("from_account_name"))
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 'from_account_name'");
			std::string from_account_name = parameters["from_account_name"].as<std::string>();
			if (!parameters.contains("to_contract"))
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 'to_contract'");
			std::string to_contract = parameters["to_contract"].as<std::string>();

			std::vector<cdcchain::consensus::Asset> result = get_client()->wallet_transfer_to_contract_testing(amount_to_transfer, asset_symbol, from_account_name, to_contract);
			return fc::variant(result);
		}

		fc::variant CommonApiRpcServer::wallet_get_contracts_positional(fc::rpc::json_connection* json_connection, const fc::variants& parameters)
		{
			// check all of this method's prerequisites
			verify_json_connection_is_authenticated(json_connection);
			verify_wallet_is_open();
			verify_wallet_is_unlocked();
			// done checking prerequisites

			std::string account_name = (parameters.size() <= 0) ?
				(fc::json::from_string("\"\"").as<std::string>()) :
				parameters[0].as<std::string>();

			vector<string> result = get_client()->wallet_get_contracts(account_name);
			return fc::variant(result);
		}

		fc::variant CommonApiRpcServer::wallet_get_contracts_named(fc::rpc::json_connection* json_connection, const fc::variant_object& parameters)
		{
			// check all of this method's prerequisites
			verify_json_connection_is_authenticated(json_connection);
			verify_wallet_is_open();
			verify_wallet_is_unlocked();
			// done checking prerequisites

			std::string account_name = parameters.contains("account_name") ?
				(fc::json::from_string("\"\"").as<std::string>()) :
				parameters["account_name"].as<std::string>();

			vector<string> result = get_client()->wallet_get_contracts(account_name);
			return fc::variant(result);
		}

		fc::variant CommonApiRpcServer::wallet_scan_contracts_positional(fc::rpc::json_connection* json_connection, const fc::variants& parameters)
		{
			// check all of this method's prerequisites
			verify_json_connection_is_authenticated(json_connection);
			verify_wallet_is_open();
			verify_wallet_is_unlocked();
			// done checking prerequisites


			get_client()->wallet_scan_contracts();
			return fc::variant();
		}

		fc::variant CommonApiRpcServer::wallet_scan_contracts_named(fc::rpc::json_connection* json_connection, const fc::variant_object& parameters)
		{
			// check all of this method's prerequisites
			verify_json_connection_is_authenticated(json_connection);
			verify_wallet_is_open();
			verify_wallet_is_unlocked();
			// done checking prerequisites


			get_client()->wallet_scan_contracts();
			return fc::variant();
		}

		fc::variant CommonApiRpcServer::wallet_builder_add_signature_positional(fc::rpc::json_connection* json_connection, const fc::variants& parameters)
		{
			// check all of this method's prerequisites
			verify_json_connection_is_authenticated(json_connection);
			verify_wallet_is_open();
			verify_wallet_is_unlocked();
			// done checking prerequisites

			if (parameters.size() <= 0)
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 1 (builder)");
			cdcchain::wallet::TransactionBuilder builder = parameters[0].as<cdcchain::wallet::TransactionBuilder>();
			bool broadcast = (parameters.size() <= 1) ?
				(fc::json::from_string("false").as<bool>()) :
				parameters[1].as<bool>();

			cdcchain::wallet::TransactionBuilder result = get_client()->wallet_builder_add_signature(builder, broadcast);
			return fc::variant(result);
		}

		fc::variant CommonApiRpcServer::wallet_builder_add_signature_named(fc::rpc::json_connection* json_connection, const fc::variant_object& parameters)
		{
			// check all of this method's prerequisites
			verify_json_connection_is_authenticated(json_connection);
			verify_wallet_is_open();
			verify_wallet_is_unlocked();
			// done checking prerequisites

			if (!parameters.contains("builder"))
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 'builder'");
			cdcchain::wallet::TransactionBuilder builder = parameters["builder"].as<cdcchain::wallet::TransactionBuilder>();
			bool broadcast = parameters.contains("broadcast") ?
				(fc::json::from_string("false").as<bool>()) :
				parameters["broadcast"].as<bool>();

			cdcchain::wallet::TransactionBuilder result = get_client()->wallet_builder_add_signature(builder, broadcast);
            return fc::variant(result);
        }

        fc::variant CommonApiRpcServer::wallet_builder_file_add_signature_positional(fc::rpc::json_connection* json_connection, const fc::variants& parameters)
        {
			// check all of this method's prerequisites
			verify_json_connection_is_authenticated(json_connection);
			verify_wallet_is_open();
			verify_wallet_is_unlocked();
			// done checking prerequisites

			if (parameters.size() <= 0)
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 1 (builder_path)");
			cdcchain::consensus::FilePath builder_path = parameters[0].as<cdcchain::consensus::FilePath>();
			bool broadcast = (parameters.size() <= 1) ?
				(fc::json::from_string("false").as<bool>()) :
				parameters[1].as<bool>();

			cdcchain::wallet::TransactionBuilder result = get_client()->wallet_builder_file_add_signature(builder_path, broadcast);
			return fc::variant(result);
		}

		fc::variant CommonApiRpcServer::wallet_builder_file_add_signature_named(fc::rpc::json_connection* json_connection, const fc::variant_object& parameters)
		{
			// check all of this method's prerequisites
			verify_json_connection_is_authenticated(json_connection);
			verify_wallet_is_open();
			verify_wallet_is_unlocked();
			// done checking prerequisites

			if (!parameters.contains("builder_path"))
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 'builder_path'");
			cdcchain::consensus::FilePath builder_path = parameters["builder_path"].as<cdcchain::consensus::FilePath>();
			bool broadcast = parameters.contains("broadcast") ?
				(fc::json::from_string("false").as<bool>()) :
				parameters["broadcast"].as<bool>();

			cdcchain::wallet::TransactionBuilder result = get_client()->wallet_builder_file_add_signature(builder_path, broadcast);
            return fc::variant(result);
        }

        fc::variant CommonApiRpcServer::wallet_multisig_deposit_positional(fc::rpc::json_connection* json_connection, const fc::variants& parameters)
        {
			// check all of this method's prerequisites
			verify_json_connection_is_authenticated(json_connection);
			verify_wallet_is_open();
			verify_wallet_is_unlocked();
			// done checking prerequisites

			if (parameters.size() <= 0)
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 1 (amount)");
			std::string amount = parameters[0].as<std::string>();
			if (parameters.size() <= 1)
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 2 (asset_symbol)");
			std::string asset_symbol = parameters[1].as<std::string>();
			if (parameters.size() <= 2)
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 3 (from_account)");
			std::string from_account = parameters[2].as<std::string>();
			if (parameters.size() <= 3)
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 4 (to_account)");
			std::string to_account = parameters[3].as<std::string>();
			cdcchain::consensus::Imessage memo_message = (parameters.size() <= 4) ?
				(fc::json::from_string("\"\"").as<cdcchain::consensus::Imessage>()) :
				parameters[4].as<cdcchain::consensus::Imessage>();

			cdcchain::wallet::WalletTransactionEntry result = get_client()->wallet_multisig_deposit(amount, asset_symbol, from_account, to_account, memo_message);
			return fc::variant(result);
		}

		fc::variant CommonApiRpcServer::wallet_multisig_deposit_named(fc::rpc::json_connection* json_connection, const fc::variant_object& parameters)
		{
			// check all of this method's prerequisites
			verify_json_connection_is_authenticated(json_connection);
			verify_wallet_is_open();
			verify_wallet_is_unlocked();
			// done checking prerequisites

			if (!parameters.contains("amount"))
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 'amount'");
			std::string amount = parameters["amount"].as<std::string>();
			if (!parameters.contains("asset_symbol"))
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 'asset_symbol'");
			std::string asset_symbol = parameters["asset_symbol"].as<std::string>();
			if (!parameters.contains("from_account"))
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 'from_account'");
			std::string from_account = parameters["from_account"].as<std::string>();
			if (!parameters.contains("to_account"))
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 'to_account'");
			std::string to_account = parameters["to_account"].as<std::string>();
			cdcchain::consensus::Imessage memo_message = parameters.contains("memo_message") ?
				(fc::json::from_string("\"\"").as<cdcchain::consensus::Imessage>()) :
				parameters["memo_message"].as<cdcchain::consensus::Imessage>();

			cdcchain::wallet::WalletTransactionEntry result = get_client()->wallet_multisig_deposit(amount, asset_symbol, from_account, to_account, memo_message);
			return fc::variant(result);
		}

		fc::variant CommonApiRpcServer::wallet_import_multisig_account_positional(fc::rpc::json_connection* json_connection, const fc::variants& parameters)
		{
			// check all of this method's prerequisites
			verify_json_connection_is_authenticated(json_connection);
			verify_wallet_is_open();
			verify_wallet_is_unlocked();
			// done checking prerequisites

			if (parameters.size() <= 0)
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 1 (multisig_address)");
			cdcchain::consensus::Address multisig_address = parameters[0].as<cdcchain::consensus::Address>();

			fc::variant_object result = get_client()->wallet_import_multisig_account(multisig_address);
			return fc::variant(result);
		}

		fc::variant CommonApiRpcServer::wallet_import_multisig_account_named(fc::rpc::json_connection* json_connection, const fc::variant_object& parameters)
		{
			// check all of this method's prerequisites
			verify_json_connection_is_authenticated(json_connection);
			verify_wallet_is_open();
			verify_wallet_is_unlocked();
			// done checking prerequisites

			if (!parameters.contains("multisig_address"))
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 'multisig_address'");
			cdcchain::consensus::Address multisig_address = parameters["multisig_address"].as<cdcchain::consensus::Address>();

			fc::variant_object result = get_client()->wallet_import_multisig_account(multisig_address);
			return fc::variant(result);
		}

		fc::variant CommonApiRpcServer::wallet_import_multisig_account_by_detail_positional(fc::rpc::json_connection* json_connection, const fc::variants& parameters)
		{
			// check all of this method's prerequisites
			verify_json_connection_is_authenticated(json_connection);
			verify_wallet_is_open();
			verify_wallet_is_unlocked();
			// done checking prerequisites

			if (parameters.size() <= 0)
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 1 (asset_symbol)");
			std::string asset_symbol = parameters[0].as<std::string>();
			if (parameters.size() <= 1)
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 2 (m)");
			uint32_t m = parameters[1].as<uint32_t>();
			if (parameters.size() <= 2)
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 3 (addresses)");
			std::vector<cdcchain::consensus::Address> addresses = parameters[2].as<std::vector<cdcchain::consensus::Address>>();

			cdcchain::consensus::Address result = get_client()->wallet_import_multisig_account_by_detail(asset_symbol, m, addresses);
			return fc::variant(result);
		}

		fc::variant CommonApiRpcServer::wallet_import_multisig_account_by_detail_named(fc::rpc::json_connection* json_connection, const fc::variant_object& parameters)
		{
			// check all of this method's prerequisites
			verify_json_connection_is_authenticated(json_connection);
			verify_wallet_is_open();
			verify_wallet_is_unlocked();
			// done checking prerequisites

			if (!parameters.contains("asset_symbol"))
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 'asset_symbol'");
			std::string asset_symbol = parameters["asset_symbol"].as<std::string>();
			if (!parameters.contains("m"))
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 'm'");
			uint32_t m = parameters["m"].as<uint32_t>();
			if (!parameters.contains("addresses"))
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 'addresses'");
			std::vector<cdcchain::consensus::Address> addresses = parameters["addresses"].as<std::vector<cdcchain::consensus::Address>>();

			cdcchain::consensus::Address result = get_client()->wallet_import_multisig_account_by_detail(asset_symbol, m, addresses);
			return fc::variant(result);
		}

		fc::variant CommonApiRpcServer::wallet_multisig_withdraw_start_positional(fc::rpc::json_connection* json_connection, const fc::variants& parameters)
		{
			// check all of this method's prerequisites
			verify_json_connection_is_authenticated(json_connection);
			verify_wallet_is_open();
			verify_wallet_is_unlocked();
			// done checking prerequisites

			if (parameters.size() <= 0)
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 1 (amount)");
			std::string amount = parameters[0].as<std::string>();
			if (parameters.size() <= 1)
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 2 (asset_symbol)");
			std::string asset_symbol = parameters[1].as<std::string>();
			if (parameters.size() <= 2)
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 3 (from)");
			cdcchain::consensus::Address from = parameters[2].as<cdcchain::consensus::Address>();
			if (parameters.size() <= 3)
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 4 (to_address)");
			cdcchain::consensus::Address to_address = parameters[3].as<cdcchain::consensus::Address>();
			cdcchain::consensus::Imessage memo_message = (parameters.size() <= 4) ?
				(fc::json::from_string("\"\"").as<cdcchain::consensus::Imessage>()) :
				parameters[4].as<cdcchain::consensus::Imessage>();
			cdcchain::consensus::FilePath builder_path = (parameters.size() <= 5) ?
				(fc::json::from_string("\"\"").as<cdcchain::consensus::FilePath>()) :
				parameters[5].as<cdcchain::consensus::FilePath>();

			cdcchain::wallet::TransactionBuilder result = get_client()->wallet_multisig_withdraw_start(amount, asset_symbol, from, to_address, memo_message, builder_path);
			return fc::variant(result);
		}

		fc::variant CommonApiRpcServer::wallet_multisig_withdraw_start_named(fc::rpc::json_connection* json_connection, const fc::variant_object& parameters)
		{
			// check all of this method's prerequisites
			verify_json_connection_is_authenticated(json_connection);
			verify_wallet_is_open();
			verify_wallet_is_unlocked();
			// done checking prerequisites

			if (!parameters.contains("amount"))
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 'amount'");
			std::string amount = parameters["amount"].as<std::string>();
			if (!parameters.contains("asset_symbol"))
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 'asset_symbol'");
			std::string asset_symbol = parameters["asset_symbol"].as<std::string>();
			if (!parameters.contains("from"))
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 'from'");
			cdcchain::consensus::Address from = parameters["from"].as<cdcchain::consensus::Address>();
			if (!parameters.contains("to_address"))
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 'to_address'");
			cdcchain::consensus::Address to_address = parameters["to_address"].as<cdcchain::consensus::Address>();
			cdcchain::consensus::Imessage memo_message = parameters.contains("memo_message") ?
				(fc::json::from_string("\"\"").as<cdcchain::consensus::Imessage>()) :
				parameters["memo_message"].as<cdcchain::consensus::Imessage>();
			cdcchain::consensus::FilePath builder_path = parameters.contains("builder_path") ?
				(fc::json::from_string("\"\"").as<cdcchain::consensus::FilePath>()) :
				parameters["builder_path"].as<cdcchain::consensus::FilePath>();

			cdcchain::wallet::TransactionBuilder result = get_client()->wallet_multisig_withdraw_start(amount, asset_symbol, from, to_address, memo_message, builder_path);
			return fc::variant(result);
		}

		fc::variant CommonApiRpcServer::wallet_create_multisig_account_positional(fc::rpc::json_connection* json_connection, const fc::variants& parameters)
		{
			// check all of this method's prerequisites
			verify_json_connection_is_authenticated(json_connection);
			verify_wallet_is_open();
			verify_wallet_is_unlocked();
			// done checking prerequisites

			if (parameters.size() <= 0)
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 1 (amount)");
			std::string amount = parameters[0].as<std::string>();
			if (parameters.size() <= 1)
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 2 (asset_symbol)");
			std::string asset_symbol = parameters[1].as<std::string>();
			if (parameters.size() <= 2)
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 3 (from_account)");
			std::string from_account = parameters[2].as<std::string>();
			if (parameters.size() <= 3)
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 4 (m)");
			uint32_t m = parameters[3].as<uint32_t>();
			if (parameters.size() <= 4)
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 5 (addresses)");
			std::vector<cdcchain::consensus::Address> addresses = parameters[4].as<std::vector<cdcchain::consensus::Address>>();
			cdcchain::consensus::Imessage memo_message = (parameters.size() <= 5) ?
				(fc::json::from_string("\"\"").as<cdcchain::consensus::Imessage>()) :
				parameters[5].as<cdcchain::consensus::Imessage>();

			std::pair<std::string, cdcchain::wallet::WalletTransactionEntry> result = get_client()->wallet_create_multisig_account(amount, asset_symbol, from_account, m, addresses, memo_message);
			return fc::variant(result);
		}

		fc::variant CommonApiRpcServer::wallet_create_multisig_account_named(fc::rpc::json_connection* json_connection, const fc::variant_object& parameters)
		{
			// check all of this method's prerequisites
			verify_json_connection_is_authenticated(json_connection);
			verify_wallet_is_open();
			verify_wallet_is_unlocked();
			// done checking prerequisites

			if (!parameters.contains("amount"))
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 'amount'");
			std::string amount = parameters["amount"].as<std::string>();
			if (!parameters.contains("asset_symbol"))
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 'asset_symbol'");
			std::string asset_symbol = parameters["asset_symbol"].as<std::string>();
			if (!parameters.contains("from_account"))
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 'from_account'");
			std::string from_account = parameters["from_account"].as<std::string>();
			if (!parameters.contains("m"))
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 'm'");
			uint32_t m = parameters["m"].as<uint32_t>();
			if (!parameters.contains("addresses"))
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 'addresses'");
			std::vector<cdcchain::consensus::Address> addresses = parameters["addresses"].as<std::vector<cdcchain::consensus::Address>>();
			cdcchain::consensus::Imessage memo_message = parameters.contains("memo_message") ?
				(fc::json::from_string("\"\"").as<cdcchain::consensus::Imessage>()) :
				parameters["memo_message"].as<cdcchain::consensus::Imessage>();

			std::pair<std::string, cdcchain::wallet::WalletTransactionEntry> result = get_client()->wallet_create_multisig_account(amount, asset_symbol, from_account, m, addresses, memo_message);
			return fc::variant(result);
		}

		fc::variant CommonApiRpcServer::wallet_multisig_account_history_positional(fc::rpc::json_connection* json_connection, const fc::variants& parameters)
		{
			// check all of this method's prerequisites
			verify_json_connection_is_authenticated(json_connection);
			verify_wallet_is_open();
			// done checking prerequisites

			if (parameters.size() <= 0)
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 1 (account_address)");
			std::string account_address = parameters[0].as<std::string>();
			std::string asset_symbol = (parameters.size() <= 1) ?
				(fc::json::from_string("\"\"").as<std::string>()) :
				parameters[1].as<std::string>();
			int32_t limit = (parameters.size() <= 2) ?
				(fc::json::from_string("0").as<int32_t>()) :
				parameters[2].as<int32_t>();
			uint32_t start_block_num = (parameters.size() <= 3) ?
				(fc::json::from_string("0").as<uint32_t>()) :
				parameters[3].as<uint32_t>();
			uint32_t end_block_num = (parameters.size() <= 4) ?
				(fc::json::from_string("-1").as<uint32_t>()) :
				parameters[4].as<uint32_t>();

			std::vector<cdcchain::wallet::PrettyTransaction> result = get_client()->wallet_multisig_account_history(account_address, asset_symbol, limit, start_block_num, end_block_num);
			return fc::variant(result);
		}

		fc::variant CommonApiRpcServer::wallet_multisig_account_history_named(fc::rpc::json_connection* json_connection, const fc::variant_object& parameters)
		{
			// check all of this method's prerequisites
			verify_json_connection_is_authenticated(json_connection);
			verify_wallet_is_open();
			// done checking prerequisites

			if (!parameters.contains("account_address"))
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 'account_address'");
			std::string account_address = parameters["account_address"].as<std::string>();
			std::string asset_symbol = parameters.contains("asset_symbol") ?
				(fc::json::from_string("\"\"").as<std::string>()) :
				parameters["asset_symbol"].as<std::string>();
			int32_t limit = parameters.contains("limit") ?
				(fc::json::from_string("0").as<int32_t>()) :
				parameters["limit"].as<int32_t>();
			uint32_t start_block_num = parameters.contains("start_block_num") ?
				(fc::json::from_string("0").as<uint32_t>()) :
				parameters["start_block_num"].as<uint32_t>();
			uint32_t end_block_num = parameters.contains("end_block_num") ?
				(fc::json::from_string("-1").as<uint32_t>()) :
				parameters["end_block_num"].as<uint32_t>();

			std::vector<cdcchain::wallet::PrettyTransaction> result = get_client()->wallet_multisig_account_history(account_address, asset_symbol, limit, start_block_num, end_block_num);
			return fc::variant(result);
		}

		fc::variant CommonApiRpcServer::wallet_multisig_account_balance_positional(fc::rpc::json_connection* json_connection, const fc::variants& parameters)
		{
			// check all of this method's prerequisites
			verify_json_connection_is_authenticated(json_connection);
			verify_wallet_is_open();
			// done checking prerequisites

			std::string account_address = (parameters.size() <= 0) ?
				(fc::json::from_string("\"\"").as<std::string>()) :
				parameters[0].as<std::string>();

			cdcchain::wallet::AccountBalanceSummaryType result = get_client()->wallet_multisig_account_balance(account_address);
			return fc::variant(result);
		}

		fc::variant CommonApiRpcServer::wallet_multisig_account_balance_named(fc::rpc::json_connection* json_connection, const fc::variant_object& parameters)
		{
			// check all of this method's prerequisites
			verify_json_connection_is_authenticated(json_connection);
			verify_wallet_is_open();
			// done checking prerequisites

			std::string account_address = parameters.contains("account_address") ?
				(fc::json::from_string("\"\"").as<std::string>()) :
				parameters["account_address"].as<std::string>();

			cdcchain::wallet::AccountBalanceSummaryType result = get_client()->wallet_multisig_account_balance(account_address);
			return fc::variant(result);
		}

		fc::variant CommonApiRpcServer::wallet_builder_get_multisig_detail_positional(fc::rpc::json_connection* json_connection, const fc::variants& parameters)
		{
			// check all of this method's prerequisites
			verify_json_connection_is_authenticated(json_connection);
			verify_wallet_is_open();
			// done checking prerequisites

			if (parameters.size() <= 0)
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 1 (transaction_builder)");
			cdcchain::wallet::TransactionBuilder transaction_builder = parameters[0].as<cdcchain::wallet::TransactionBuilder>();

			fc::variant_object result = get_client()->wallet_builder_get_multisig_detail(transaction_builder);
			return fc::variant(result);
		}

		fc::variant CommonApiRpcServer::wallet_builder_get_multisig_detail_named(fc::rpc::json_connection* json_connection, const fc::variant_object& parameters)
		{
			// check all of this method's prerequisites
			verify_json_connection_is_authenticated(json_connection);
			verify_wallet_is_open();
			// done checking prerequisites

			if (!parameters.contains("transaction_builder"))
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 'transaction_builder'");
			cdcchain::wallet::TransactionBuilder transaction_builder = parameters["transaction_builder"].as<cdcchain::wallet::TransactionBuilder>();

			fc::variant_object result = get_client()->wallet_builder_get_multisig_detail(transaction_builder);
			return fc::variant(result);
		}

		fc::variant CommonApiRpcServer::wallet_builder_file_get_multisig_detail_positional(fc::rpc::json_connection* json_connection, const fc::variants& parameters)
		{
			// check all of this method's prerequisites
			verify_json_connection_is_authenticated(json_connection);
			verify_wallet_is_open();
			// done checking prerequisites

			if (parameters.size() <= 0)
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 1 (builder_path)");
			cdcchain::consensus::FilePath builder_path = parameters[0].as<cdcchain::consensus::FilePath>();

			fc::variant_object result = get_client()->wallet_builder_file_get_multisig_detail(builder_path);
			return fc::variant(result);
		}

		fc::variant CommonApiRpcServer::wallet_builder_file_get_multisig_detail_named(fc::rpc::json_connection* json_connection, const fc::variant_object& parameters)
		{
			// check all of this method's prerequisites
			verify_json_connection_is_authenticated(json_connection);
			verify_wallet_is_open();
			// done checking prerequisites

			if (!parameters.contains("builder_path"))
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 'builder_path'");
			cdcchain::consensus::FilePath builder_path = parameters["builder_path"].as<cdcchain::consensus::FilePath>();

			fc::variant_object result = get_client()->wallet_builder_file_get_multisig_detail(builder_path);
			return fc::variant(result);
		}

        fc::variant CommonApiRpcServer::about_positional(fc::rpc::json_connection* json_connection, const fc::variants& parameters)
        {
            // this method has no prerequisites


            fc::variant_object result = get_client()->about();
            return fc::variant(result);
        }

        fc::variant CommonApiRpcServer::about_named(fc::rpc::json_connection* json_connection, const fc::variant_object& parameters)
        {
            // this method has no prerequisites


            fc::variant_object result = get_client()->about();
            return fc::variant(result);
        }

        fc::variant CommonApiRpcServer::get_info_positional(fc::rpc::json_connection* json_connection, const fc::variants& parameters)
        {
            // this method has no prerequisites


            fc::variant_object result = get_client()->get_info();
            return fc::variant(result);
        }

        fc::variant CommonApiRpcServer::get_info_named(fc::rpc::json_connection* json_connection, const fc::variant_object& parameters)
        {
            // this method has no prerequisites


            fc::variant_object result = get_client()->get_info();
            return fc::variant(result);
        }

        fc::variant CommonApiRpcServer::stop_positional(fc::rpc::json_connection* json_connection, const fc::variants& parameters)
        {
            // check all of this method's prerequisites
            verify_json_connection_is_authenticated(json_connection);
            // done checking prerequisites


            get_client()->stop();
            return fc::variant();
        }

        fc::variant CommonApiRpcServer::stop_named(fc::rpc::json_connection* json_connection, const fc::variant_object& parameters)
        {
            // check all of this method's prerequisites
            verify_json_connection_is_authenticated(json_connection);
            // done checking prerequisites


            get_client()->stop();
            return fc::variant();
        }

        fc::variant CommonApiRpcServer::help_positional(fc::rpc::json_connection* json_connection, const fc::variants& parameters)
        {
            // this method has no prerequisites

            std::string command_name = (parameters.size() <= 0) ?
            (fc::json::from_string("\"\"").as<std::string>()) :
            parameters[0].as<std::string>();

            std::string result = get_client()->help(command_name);
            return fc::variant(result);
        }

        fc::variant CommonApiRpcServer::help_named(fc::rpc::json_connection* json_connection, const fc::variant_object& parameters)
        {
            // this method has no prerequisites

            std::string command_name = parameters.contains("command_name") ?
                (fc::json::from_string("\"\"").as<std::string>()) :
                parameters["command_name"].as<std::string>();

            std::string result = get_client()->help(command_name);
            return fc::variant(result);
        }

        fc::variant CommonApiRpcServer::validate_address_positional(fc::rpc::json_connection* json_connection, const fc::variants& parameters)
        {
            // this method has no prerequisites

            if (parameters.size() <= 0)
                FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 1 (address)");
            std::string address = parameters[0].as<std::string>();

            fc::variant_object result = get_client()->validate_address(address);
            return fc::variant(result);
        }

        fc::variant CommonApiRpcServer::validate_address_named(fc::rpc::json_connection* json_connection, const fc::variant_object& parameters)
        {
            // this method has no prerequisites

            if (!parameters.contains("address"))
                FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 'address'");
            std::string address = parameters["address"].as<std::string>();

            fc::variant_object result = get_client()->validate_address(address);
            return fc::variant(result);
        }

        fc::variant CommonApiRpcServer::execute_command_line_positional(fc::rpc::json_connection* json_connection, const fc::variants& parameters)
        {
            // check all of this method's prerequisites
            verify_json_connection_is_authenticated(json_connection);
            // done checking prerequisites

            if (parameters.size() <= 0)
                FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 1 (input)");
            std::string input = parameters[0].as<std::string>();

            std::string result = get_client()->execute_command_line(input);
            return fc::variant(result);
        }

        fc::variant CommonApiRpcServer::execute_command_line_named(fc::rpc::json_connection* json_connection, const fc::variant_object& parameters)
        {
            // check all of this method's prerequisites
            verify_json_connection_is_authenticated(json_connection);
            // done checking prerequisites

            if (!parameters.contains("input"))
                FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 'input'");
            std::string input = parameters["input"].as<std::string>();

            std::string result = get_client()->execute_command_line(input);
            return fc::variant(result);
        }

        fc::variant CommonApiRpcServer::execute_script_positional(fc::rpc::json_connection* json_connection, const fc::variants& parameters)
        {
            // check all of this method's prerequisites
            verify_json_connection_is_authenticated(json_connection);
            // done checking prerequisites

            if (parameters.size() <= 0)
                FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 1 (script)");
            fc::path script = parameters[0].as<fc::path>();

            get_client()->execute_script(script);
            return fc::variant();
        }

        fc::variant CommonApiRpcServer::execute_script_named(fc::rpc::json_connection* json_connection, const fc::variant_object& parameters)
        {
            // check all of this method's prerequisites
            verify_json_connection_is_authenticated(json_connection);
            // done checking prerequisites

            if (!parameters.contains("script"))
                FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 'script'");
            fc::path script = parameters["script"].as<fc::path>();

            get_client()->execute_script(script);
            return fc::variant();
        }

        fc::variant CommonApiRpcServer::batch_positional(fc::rpc::json_connection* json_connection, const fc::variants& parameters)
        {
            // this method has no prerequisites

            if (parameters.size() <= 0)
                FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 1 (method_name)");
            std::string method_name = parameters[0].as<std::string>();
            if (parameters.size() <= 1)
                FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 2 (parameters_list)");
            std::vector<fc::variants> parameters_list = parameters[1].as<std::vector<fc::variants>>();

            fc::variants result = get_client()->batch(method_name, parameters_list);
            return fc::variant(result);
        }

        fc::variant CommonApiRpcServer::batch_named(fc::rpc::json_connection* json_connection, const fc::variant_object& parameters)
        {
            // this method has no prerequisites

            if (!parameters.contains("method_name"))
                FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 'method_name'");
            std::string method_name = parameters["method_name"].as<std::string>();
            if (!parameters.contains("parameters_list"))
                FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 'parameters_list'");
            std::vector<fc::variants> parameters_list = parameters["parameters_list"].as<std::vector<fc::variants>>();

            fc::variants result = get_client()->batch(method_name, parameters_list);
            return fc::variant(result);
        }

        fc::variant CommonApiRpcServer::batch_authenticated_positional(fc::rpc::json_connection* json_connection, const fc::variants& parameters)
        {
            // check all of this method's prerequisites
            verify_json_connection_is_authenticated(json_connection);
            // done checking prerequisites

            if (parameters.size() <= 0)
                FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 1 (method_name)");
            std::string method_name = parameters[0].as<std::string>();
            if (parameters.size() <= 1)
                FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 2 (parameters_list)");
            std::vector<fc::variants> parameters_list = parameters[1].as<std::vector<fc::variants>>();

            fc::variants result = get_client()->batch_authenticated(method_name, parameters_list);
            return fc::variant(result);
        }

        fc::variant CommonApiRpcServer::batch_authenticated_named(fc::rpc::json_connection* json_connection, const fc::variant_object& parameters)
        {
            // check all of this method's prerequisites
            verify_json_connection_is_authenticated(json_connection);
            // done checking prerequisites

            if (!parameters.contains("method_name"))
                FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 'method_name'");
            std::string method_name = parameters["method_name"].as<std::string>();
            if (!parameters.contains("parameters_list"))
                FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 'parameters_list'");
            std::vector<fc::variants> parameters_list = parameters["parameters_list"].as<std::vector<fc::variants>>();

            fc::variants result = get_client()->batch_authenticated(method_name, parameters_list);
            return fc::variant(result);
        }

        fc::variant CommonApiRpcServer::builder_finalize_and_sign_positional(fc::rpc::json_connection* json_connection, const fc::variants& parameters)
        {
            // check all of this method's prerequisites
            verify_json_connection_is_authenticated(json_connection);
            verify_wallet_is_open();
            verify_wallet_is_unlocked();
            // done checking prerequisites

            if (parameters.size() <= 0)
                FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 1 (builder)");
            cdcchain::wallet::TransactionBuilder builder = parameters[0].as<cdcchain::wallet::TransactionBuilder>();

            cdcchain::wallet::WalletTransactionEntry result = get_client()->builder_finalize_and_sign(builder);
            return fc::variant(result);
        }

        fc::variant CommonApiRpcServer::builder_finalize_and_sign_named(fc::rpc::json_connection* json_connection, const fc::variant_object& parameters)
        {
            // check all of this method's prerequisites
            verify_json_connection_is_authenticated(json_connection);
            verify_wallet_is_open();
            verify_wallet_is_unlocked();
            // done checking prerequisites

            if (!parameters.contains("builder"))
                FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 'builder'");
            cdcchain::wallet::TransactionBuilder builder = parameters["builder"].as<cdcchain::wallet::TransactionBuilder>();

            cdcchain::wallet::WalletTransactionEntry result = get_client()->builder_finalize_and_sign(builder);
            return fc::variant(result);
        }

        fc::variant CommonApiRpcServer::meta_help_positional(fc::rpc::json_connection* json_connection, const fc::variants& parameters)
        {
            // this method has no prerequisites


            std::map<std::string, cdcchain::api::MethodData> result = get_client()->meta_help();
            return fc::variant(result);
        }

        fc::variant CommonApiRpcServer::meta_help_named(fc::rpc::json_connection* json_connection, const fc::variant_object& parameters)
        {
            // this method has no prerequisites


            std::map<std::string, cdcchain::api::MethodData> result = get_client()->meta_help();
            return fc::variant(result);
        }

        fc::variant CommonApiRpcServer::rpc_set_username_positional(fc::rpc::json_connection* json_connection, const fc::variants& parameters)
        {
            // check all of this method's prerequisites
            verify_json_connection_is_authenticated(json_connection);
            // done checking prerequisites

            std::string username = (parameters.size() <= 0) ?
            (fc::json::from_string("\"\"").as<std::string>()) :
            parameters[0].as<std::string>();

            get_client()->rpc_set_username(username);
            return fc::variant();
        }

        fc::variant CommonApiRpcServer::rpc_set_username_named(fc::rpc::json_connection* json_connection, const fc::variant_object& parameters)
        {
            // check all of this method's prerequisites
            verify_json_connection_is_authenticated(json_connection);
            // done checking prerequisites

            std::string username = parameters.contains("username") ?
                (fc::json::from_string("\"\"").as<std::string>()) :
                parameters["username"].as<std::string>();

            get_client()->rpc_set_username(username);
            return fc::variant();
        }

        fc::variant CommonApiRpcServer::rpc_set_password_positional(fc::rpc::json_connection* json_connection, const fc::variants& parameters)
        {
            // check all of this method's prerequisites
            verify_json_connection_is_authenticated(json_connection);
            // done checking prerequisites

            std::string password = (parameters.size() <= 0) ?
            (fc::json::from_string("\"\"").as<std::string>()) :
            parameters[0].as<std::string>();

            get_client()->rpc_set_password(password);
            return fc::variant();
        }

        fc::variant CommonApiRpcServer::rpc_set_password_named(fc::rpc::json_connection* json_connection, const fc::variant_object& parameters)
        {
            // check all of this method's prerequisites
            verify_json_connection_is_authenticated(json_connection);
            // done checking prerequisites

            std::string password = parameters.contains("password") ?
                (fc::json::from_string("\"\"").as<std::string>()) :
                parameters["password"].as<std::string>();

            get_client()->rpc_set_password(password);
            return fc::variant();
        }

        fc::variant CommonApiRpcServer::rpc_start_server_positional(fc::rpc::json_connection* json_connection, const fc::variants& parameters)
        {
            // check all of this method's prerequisites
            verify_json_connection_is_authenticated(json_connection);
            // done checking prerequisites

            uint32_t port = (parameters.size() <= 0) ?
            (fc::json::from_string("\"65065\"").as<uint32_t>()) :
            parameters[0].as<uint32_t>();

            get_client()->rpc_start_server(port);
            return fc::variant();
        }

        fc::variant CommonApiRpcServer::rpc_start_server_named(fc::rpc::json_connection* json_connection, const fc::variant_object& parameters)
        {
            // check all of this method's prerequisites
            verify_json_connection_is_authenticated(json_connection);
            // done checking prerequisites

            uint32_t port = parameters.contains("port") ?
                (fc::json::from_string("\"65065\"").as<uint32_t>()) :
                parameters["port"].as<uint32_t>();

            get_client()->rpc_start_server(port);
            return fc::variant();
        }

        fc::variant CommonApiRpcServer::http_start_server_positional(fc::rpc::json_connection* json_connection, const fc::variants& parameters)
        {
            // check all of this method's prerequisites
            verify_json_connection_is_authenticated(json_connection);
            // done checking prerequisites

            uint32_t port = (parameters.size() <= 0) ?
            (fc::json::from_string("\"65066\"").as<uint32_t>()) :
            parameters[0].as<uint32_t>();

            get_client()->http_start_server(port);
            return fc::variant();
        }

        fc::variant CommonApiRpcServer::http_start_server_named(fc::rpc::json_connection* json_connection, const fc::variant_object& parameters)
        {
            // check all of this method's prerequisites
            verify_json_connection_is_authenticated(json_connection);
            // done checking prerequisites

            uint32_t port = parameters.contains("port") ?
                (fc::json::from_string("\"65066\"").as<uint32_t>()) :
                parameters["port"].as<uint32_t>();

            get_client()->http_start_server(port);
            return fc::variant();
        }

        fc::variant CommonApiRpcServer::ntp_update_time_positional(fc::rpc::json_connection* json_connection, const fc::variants& parameters)
        {
            // check all of this method's prerequisites
            verify_json_connection_is_authenticated(json_connection);
            // done checking prerequisites


            get_client()->ntp_update_time();
            return fc::variant();
        }

        fc::variant CommonApiRpcServer::ntp_update_time_named(fc::rpc::json_connection* json_connection, const fc::variant_object& parameters)
        {
            // check all of this method's prerequisites
            verify_json_connection_is_authenticated(json_connection);
            // done checking prerequisites


            get_client()->ntp_update_time();
            return fc::variant();
        }

        fc::variant CommonApiRpcServer::disk_usage_positional(fc::rpc::json_connection* json_connection, const fc::variants& parameters)
        {
            // check all of this method's prerequisites
            verify_json_connection_is_authenticated(json_connection);
            // done checking prerequisites


            fc::variant result = get_client()->disk_usage();
            return fc::variant(result);
        }

        fc::variant CommonApiRpcServer::disk_usage_named(fc::rpc::json_connection* json_connection, const fc::variant_object& parameters)
        {
            // check all of this method's prerequisites
            verify_json_connection_is_authenticated(json_connection);
            // done checking prerequisites


            fc::variant result = get_client()->disk_usage();
            return fc::variant(result);
        }

		fc::variant CommonApiRpcServer::contract_compile_positional(fc::rpc::json_connection* json_connection, const fc::variants& parameters)
		{
			// this method has no prerequisites

			if (parameters.size() <= 0)
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 1 (filename)");
			fc::path filename = parameters[0].as<fc::path>();

			fc::path result = get_client()->contract_compile(filename);
			return fc::variant(result);
		}

		fc::variant CommonApiRpcServer::contract_compile_named(fc::rpc::json_connection* json_connection, const fc::variant_object& parameters)
		{
			// this method has no prerequisites

			if (!parameters.contains("filename"))
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 'filename'");
			fc::path filename = parameters["filename"].as<fc::path>();

			fc::path result = get_client()->contract_compile(filename);
			return fc::variant(result);
		}

		fc::variant CommonApiRpcServer::contract_register_positional(fc::rpc::json_connection* json_connection, const fc::variants& parameters)
		{
			// check all of this method's prerequisites
			verify_json_connection_is_authenticated(json_connection);
			verify_wallet_is_open();
			verify_wallet_is_unlocked();
			// done checking prerequisites

			if (parameters.size() <= 0)
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 1 (owner)");
			std::string owner = parameters[0].as<std::string>();
			if (parameters.size() <= 1)
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 2 (codefile)");
			fc::path codefile = parameters[1].as<fc::path>();
			if (parameters.size() <= 2)
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 3 (asset_symbol)");
			std::string asset_symbol = parameters[2].as<std::string>();
			if (parameters.size() <= 3)
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 4 (init_limit)");
			fc::optional<double> init_limit = parameters[3].as<fc::optional<double>>();

			std::string result = get_client()->contract_register(owner, codefile, asset_symbol, init_limit);
			return fc::variant(result);
		}

		fc::variant CommonApiRpcServer::contract_register_named(fc::rpc::json_connection* json_connection, const fc::variant_object& parameters)
		{
			// check all of this method's prerequisites
			verify_json_connection_is_authenticated(json_connection);
			verify_wallet_is_open();
			verify_wallet_is_unlocked();
			// done checking prerequisites

			if (!parameters.contains("owner"))
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 'owner'");
			std::string owner = parameters["owner"].as<std::string>();
			if (!parameters.contains("codefile"))
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 'codefile'");
			fc::path codefile = parameters["codefile"].as<fc::path>();
			if (!parameters.contains("asset_symbol"))
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 'asset_symbol'");
			std::string asset_symbol = parameters["asset_symbol"].as<std::string>();
			if (!parameters.contains("init_limit"))
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 'init_limit'");
			fc::optional<double> init_limit = parameters["init_limit"].as<fc::optional<double>>();

			std::string result = get_client()->contract_register(owner, codefile, asset_symbol, init_limit);
			return fc::variant(result);
		}

		fc::variant CommonApiRpcServer::contract_register_testing_positional(fc::rpc::json_connection* json_connection, const fc::variants& parameters)
		{
			// check all of this method's prerequisites
			verify_json_connection_is_authenticated(json_connection);
			verify_wallet_is_open();
			verify_wallet_is_unlocked();
			// done checking prerequisites

			if (parameters.size() <= 0)
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 1 (owner)");
			std::string owner = parameters[0].as<std::string>();
			if (parameters.size() <= 1)
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 2 (codefile)");
			fc::path codefile = parameters[1].as<fc::path>();

			std::vector<cdcchain::consensus::Asset> result = get_client()->contract_register_testing(owner, codefile);
			return fc::variant(result);
		}

		fc::variant CommonApiRpcServer::contract_register_testing_named(fc::rpc::json_connection* json_connection, const fc::variant_object& parameters)
		{
			// check all of this method's prerequisites
			verify_json_connection_is_authenticated(json_connection);
			verify_wallet_is_open();
			verify_wallet_is_unlocked();
			// done checking prerequisites

			if (!parameters.contains("owner"))
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 'owner'");
			std::string owner = parameters["owner"].as<std::string>();
			if (!parameters.contains("codefile"))
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 'codefile'");
			fc::path codefile = parameters["codefile"].as<fc::path>();

			std::vector<cdcchain::consensus::Asset> result = get_client()->contract_register_testing(owner, codefile);
			return fc::variant(result);
		}

		fc::variant CommonApiRpcServer::contract_upgrade_positional(fc::rpc::json_connection* json_connection, const fc::variants& parameters)
		{
			// check all of this method's prerequisites
			verify_json_connection_is_authenticated(json_connection);
			verify_wallet_is_open();
			verify_wallet_is_unlocked();
			// done checking prerequisites

			if (parameters.size() <= 0)
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 1 (contract_address)");
			std::string contract_address = parameters[0].as<std::string>();
			if (parameters.size() <= 1)
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 2 (upgrader_name)");
			std::string upgrader_name = parameters[1].as<std::string>();
			if (parameters.size() <= 2)
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 3 (new_contract_name)");
			std::string new_contract_name = parameters[2].as<std::string>();
			if (parameters.size() <= 3)
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 4 (new_contract_desc)");
			cdcchain::consensus::Imessage new_contract_desc = parameters[3].as<cdcchain::consensus::Imessage>();
			if (parameters.size() <= 4)
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 5 (asset_symbol)");
			std::string asset_symbol = parameters[4].as<std::string>();
			if (parameters.size() <= 5)
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 6 (exec_limit)");
			fc::optional<double> exec_limit = parameters[5].as<fc::optional<double>>();

			cdcchain::wallet::WalletTransactionEntry result = get_client()->contract_upgrade(contract_address, upgrader_name, new_contract_name, new_contract_desc, asset_symbol, exec_limit);
			return fc::variant(result);
		}

		fc::variant CommonApiRpcServer::contract_upgrade_named(fc::rpc::json_connection* json_connection, const fc::variant_object& parameters)
		{
			// check all of this method's prerequisites
			verify_json_connection_is_authenticated(json_connection);
			verify_wallet_is_open();
			verify_wallet_is_unlocked();
			// done checking prerequisites

			if (!parameters.contains("contract_address"))
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 'contract_address'");
			std::string contract_address = parameters["contract_address"].as<std::string>();
			if (!parameters.contains("upgrader_name"))
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 'upgrader_name'");
			std::string upgrader_name = parameters["upgrader_name"].as<std::string>();
			if (!parameters.contains("new_contract_name"))
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 'new_contract_name'");
			std::string new_contract_name = parameters["new_contract_name"].as<std::string>();
			if (!parameters.contains("new_contract_desc"))
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 'new_contract_desc'");
			cdcchain::consensus::Imessage new_contract_desc = parameters["new_contract_desc"].as<cdcchain::consensus::Imessage>();
			if (!parameters.contains("asset_symbol"))
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 'asset_symbol'");
			std::string asset_symbol = parameters["asset_symbol"].as<std::string>();
			if (!parameters.contains("exec_limit"))
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 'exec_limit'");
			fc::optional<double> exec_limit = parameters["exec_limit"].as<fc::optional<double>>();

			cdcchain::wallet::WalletTransactionEntry result = get_client()->contract_upgrade(contract_address, upgrader_name, new_contract_name, new_contract_desc, asset_symbol, exec_limit);
			return fc::variant(result);
		}

		fc::variant CommonApiRpcServer::contract_upgrade_testing_positional(fc::rpc::json_connection* json_connection, const fc::variants& parameters)
		{
			// check all of this method's prerequisites
			verify_json_connection_is_authenticated(json_connection);
			verify_wallet_is_open();
			verify_wallet_is_unlocked();
			// done checking prerequisites

			if (parameters.size() <= 0)
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 1 (contract_address)");
			std::string contract_address = parameters[0].as<std::string>();
			if (parameters.size() <= 1)
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 2 (upgrader_name)");
			std::string upgrader_name = parameters[1].as<std::string>();
			if (parameters.size() <= 2)
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 3 (new_contract_name)");
			std::string new_contract_name = parameters[2].as<std::string>();
			if (parameters.size() <= 3)
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 4 (new_contract_desc)");
			cdcchain::consensus::Imessage new_contract_desc = parameters[3].as<cdcchain::consensus::Imessage>();

			std::vector<cdcchain::consensus::Asset> result = get_client()->contract_upgrade_testing(contract_address, upgrader_name, new_contract_name, new_contract_desc);
			return fc::variant(result);
		}

		fc::variant CommonApiRpcServer::contract_upgrade_testing_named(fc::rpc::json_connection* json_connection, const fc::variant_object& parameters)
		{
			// check all of this method's prerequisites
			verify_json_connection_is_authenticated(json_connection);
			verify_wallet_is_open();
			verify_wallet_is_unlocked();
			// done checking prerequisites

			if (!parameters.contains("contract_address"))
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 'contract_address'");
			std::string contract_address = parameters["contract_address"].as<std::string>();
			if (!parameters.contains("upgrader_name"))
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 'upgrader_name'");
			std::string upgrader_name = parameters["upgrader_name"].as<std::string>();
			if (!parameters.contains("new_contract_name"))
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 'new_contract_name'");
			std::string new_contract_name = parameters["new_contract_name"].as<std::string>();
			if (!parameters.contains("new_contract_desc"))
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 'new_contract_desc'");
			cdcchain::consensus::Imessage new_contract_desc = parameters["new_contract_desc"].as<cdcchain::consensus::Imessage>();

			std::vector<cdcchain::consensus::Asset> result = get_client()->contract_upgrade_testing(contract_address, upgrader_name, new_contract_name, new_contract_desc);
			return fc::variant(result);
		}

		fc::variant CommonApiRpcServer::contract_destroy_positional(fc::rpc::json_connection* json_connection, const fc::variants& parameters)
		{
			// check all of this method's prerequisites
			verify_json_connection_is_authenticated(json_connection);
			verify_wallet_is_open();
			verify_wallet_is_unlocked();
			// done checking prerequisites

			if (parameters.size() <= 0)
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 1 (contract_address)");
			std::string contract_address = parameters[0].as<std::string>();
			if (parameters.size() <= 1)
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 2 (destroyer_name)");
			std::string destroyer_name = parameters[1].as<std::string>();
			if (parameters.size() <= 2)
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 3 (asset_symbol)");
			std::string asset_symbol = parameters[2].as<std::string>();
			if (parameters.size() <= 3)
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 4 (exec_limit)");
			fc::optional<double> exec_limit = parameters[3].as<fc::optional<double>>();

			cdcchain::wallet::WalletTransactionEntry result = get_client()->contract_destroy(contract_address, destroyer_name, asset_symbol, exec_limit);
			return fc::variant(result);
		}

		fc::variant CommonApiRpcServer::contract_destroy_named(fc::rpc::json_connection* json_connection, const fc::variant_object& parameters)
		{
			// check all of this method's prerequisites
			verify_json_connection_is_authenticated(json_connection);
			verify_wallet_is_open();
			verify_wallet_is_unlocked();
			// done checking prerequisites

			if (!parameters.contains("contract_address"))
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 'contract_address'");
			std::string contract_address = parameters["contract_address"].as<std::string>();
			if (!parameters.contains("destroyer_name"))
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 'destroyer_name'");
			std::string destroyer_name = parameters["destroyer_name"].as<std::string>();
			if (!parameters.contains("asset_symbol"))
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 'asset_symbol'");
			std::string asset_symbol = parameters["asset_symbol"].as<std::string>();
			if (!parameters.contains("exec_limit"))
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 'exec_limit'");
			fc::optional<double> exec_limit = parameters["exec_limit"].as<fc::optional<double>>();

			cdcchain::wallet::WalletTransactionEntry result = get_client()->contract_destroy(contract_address, destroyer_name, asset_symbol, exec_limit);
			return fc::variant(result);
		}

		fc::variant CommonApiRpcServer::contract_destroy_testing_positional(fc::rpc::json_connection* json_connection, const fc::variants& parameters)
		{
			// check all of this method's prerequisites
			verify_json_connection_is_authenticated(json_connection);
			verify_wallet_is_open();
			verify_wallet_is_unlocked();
			// done checking prerequisites

			if (parameters.size() <= 0)
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 1 (contract_address)");
			std::string contract_address = parameters[0].as<std::string>();
			if (parameters.size() <= 1)
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 2 (destroyer_name)");
			std::string destroyer_name = parameters[1].as<std::string>();

			std::vector<cdcchain::consensus::Asset> result = get_client()->contract_destroy_testing(contract_address, destroyer_name);
			return fc::variant(result);
		}

		fc::variant CommonApiRpcServer::contract_destroy_testing_named(fc::rpc::json_connection* json_connection, const fc::variant_object& parameters)
		{
			// check all of this method's prerequisites
			verify_json_connection_is_authenticated(json_connection);
			verify_wallet_is_open();
			verify_wallet_is_unlocked();
			// done checking prerequisites

			if (!parameters.contains("contract_address"))
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 'contract_address'");
			std::string contract_address = parameters["contract_address"].as<std::string>();
			if (!parameters.contains("destroyer_name"))
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 'destroyer_name'");
			std::string destroyer_name = parameters["destroyer_name"].as<std::string>();

			std::vector<cdcchain::consensus::Asset> result = get_client()->contract_destroy_testing(contract_address, destroyer_name);
			return fc::variant(result);
		}

		fc::variant CommonApiRpcServer::contract_call_positional(fc::rpc::json_connection* json_connection, const fc::variants& parameters)
		{
			// check all of this method's prerequisites
			verify_json_connection_is_authenticated(json_connection);
			verify_wallet_is_open();
			verify_wallet_is_unlocked();
			// done checking prerequisites

			if (parameters.size() <= 0)
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 1 (contract)");
			std::string contract = parameters[0].as<std::string>();
			if (parameters.size() <= 1)
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 2 (caller_name)");
			std::string caller_name = parameters[1].as<std::string>();
			if (parameters.size() <= 2)
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 3 (function_name)");
			std::string function_name = parameters[2].as<std::string>();
			if (parameters.size() <= 3)
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 4 (params)");
			std::string params = parameters[3].as<std::string>();
			if (parameters.size() <= 4)
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 5 (asset_symbol)");
			std::string asset_symbol = parameters[4].as<std::string>();
			if (parameters.size() <= 5)
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 6 (call_limit)");
			fc::optional<double> call_limit = parameters[5].as<fc::optional<double>>();

			cdcchain::wallet::WalletTransactionEntry result = get_client()->contract_call(contract, caller_name, function_name, params, asset_symbol, call_limit);
			return fc::variant(result);
		}

		fc::variant CommonApiRpcServer::contract_call_named(fc::rpc::json_connection* json_connection, const fc::variant_object& parameters)
		{
			// check all of this method's prerequisites
			verify_json_connection_is_authenticated(json_connection);
			verify_wallet_is_open();
			verify_wallet_is_unlocked();
			// done checking prerequisites

			if (!parameters.contains("contract"))
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 'contract'");
			std::string contract = parameters["contract"].as<std::string>();
			if (!parameters.contains("caller_name"))
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 'caller_name'");
			std::string caller_name = parameters["caller_name"].as<std::string>();
			if (!parameters.contains("function_name"))
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 'function_name'");
			std::string function_name = parameters["function_name"].as<std::string>();
			if (!parameters.contains("params"))
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 'params'");
			std::string params = parameters["params"].as<std::string>();
			if (!parameters.contains("asset_symbol"))
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 'asset_symbol'");
			std::string asset_symbol = parameters["asset_symbol"].as<std::string>();
			if (!parameters.contains("call_limit"))
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 'call_limit'");
			fc::optional<double> call_limit = parameters["call_limit"].as<fc::optional<double>>();

			cdcchain::wallet::WalletTransactionEntry result = get_client()->contract_call(contract, caller_name, function_name, params, asset_symbol, call_limit);
			return fc::variant(result);
		}

		fc::variant CommonApiRpcServer::contract_get_info_positional(fc::rpc::json_connection* json_connection, const fc::variants& parameters)
		{
			// this method has no prerequisites

			if (parameters.size() <= 0)
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 1 (contract)");
			std::string contract = parameters[0].as<std::string>();

			cdcchain::consensus::ContractEntryPrintable result = get_client()->contract_get_info(contract);
			return fc::variant(result);
		}

		fc::variant CommonApiRpcServer::contract_get_info_named(fc::rpc::json_connection* json_connection, const fc::variant_object& parameters)
		{
			// this method has no prerequisites

			if (!parameters.contains("contract"))
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 'contract'");
			std::string contract = parameters["contract"].as<std::string>();

			cdcchain::consensus::ContractEntryPrintable result = get_client()->contract_get_info(contract);
			return fc::variant(result);
		}

		fc::variant CommonApiRpcServer::contract_get_balance_positional(fc::rpc::json_connection* json_connection, const fc::variants& parameters)
		{
			// this method has no prerequisites

			if (parameters.size() <= 0)
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 1 (contract)");
			std::string contract = parameters[0].as<std::string>();

			std::vector<cdcchain::consensus::BalanceEntry> result = get_client()->contract_get_balance(contract);
			return fc::variant(result);
		}

		fc::variant CommonApiRpcServer::contract_get_balance_named(fc::rpc::json_connection* json_connection, const fc::variant_object& parameters)
		{
			// this method has no prerequisites

			if (!parameters.contains("contract"))
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 'contract'");
			std::string contract = parameters["contract"].as<std::string>();

			std::vector<cdcchain::consensus::BalanceEntry> result = get_client()->contract_get_balance(contract);
			return fc::variant(result);
		}

		fc::variant CommonApiRpcServer::contract_call_testing_positional(fc::rpc::json_connection* json_connection, const fc::variants& parameters)
		{
			// check all of this method's prerequisites
			verify_json_connection_is_authenticated(json_connection);
			verify_wallet_is_open();
			verify_wallet_is_unlocked();
			// done checking prerequisites

			if (parameters.size() <= 0)
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 1 (contract)");
			std::string contract = parameters[0].as<std::string>();
			if (parameters.size() <= 1)
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 2 (caller_name)");
			std::string caller_name = parameters[1].as<std::string>();
			if (parameters.size() <= 2)
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 3 (function_name)");
			std::string function_name = parameters[2].as<std::string>();
			if (parameters.size() <= 3)
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 4 (params)");
			std::string params = parameters[3].as<std::string>();

			std::vector<cdcchain::consensus::Asset> result = get_client()->contract_call_testing(contract, caller_name, function_name, params);
			return fc::variant(result);
		}

		fc::variant CommonApiRpcServer::contract_call_testing_named(fc::rpc::json_connection* json_connection, const fc::variant_object& parameters)
		{
			// check all of this method's prerequisites
			verify_json_connection_is_authenticated(json_connection);
			verify_wallet_is_open();
			verify_wallet_is_unlocked();
			// done checking prerequisites

			if (!parameters.contains("contract"))
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 'contract'");
			std::string contract = parameters["contract"].as<std::string>();
			if (!parameters.contains("caller_name"))
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 'caller_name'");
			std::string caller_name = parameters["caller_name"].as<std::string>();
			if (!parameters.contains("function_name"))
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 'function_name'");
			std::string function_name = parameters["function_name"].as<std::string>();
			if (!parameters.contains("params"))
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 'params'");
			std::string params = parameters["params"].as<std::string>();

			std::vector<cdcchain::consensus::Asset> result = get_client()->contract_call_testing(contract, caller_name, function_name, params);
			return fc::variant(result);
		}

		fc::variant CommonApiRpcServer::contract_call_offline_positional(fc::rpc::json_connection* json_connection, const fc::variants& parameters)
		{
			// check all of this method's prerequisites
			verify_json_connection_is_authenticated(json_connection);
			verify_wallet_is_open();
			verify_wallet_is_unlocked();
			// done checking prerequisites

			if (parameters.size() <= 0)
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 1 (contract)");
			std::string contract = parameters[0].as<std::string>();
			if (parameters.size() <= 1)
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 2 (caller_name)");
			std::string caller_name = parameters[1].as<std::string>();
			if (parameters.size() <= 2)
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 3 (function_name)");
			std::string function_name = parameters[2].as<std::string>();
			if (parameters.size() <= 3)
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 4 (params)");
			std::string params = parameters[3].as<std::string>();

			std::string result = get_client()->contract_call_offline(contract, caller_name, function_name, params);
			return fc::variant(result);
		}

		fc::variant CommonApiRpcServer::contract_call_offline_named(fc::rpc::json_connection* json_connection, const fc::variant_object& parameters)
		{
			// check all of this method's prerequisites
			verify_json_connection_is_authenticated(json_connection);
			verify_wallet_is_open();
			verify_wallet_is_unlocked();
			// done checking prerequisites

			if (!parameters.contains("contract"))
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 'contract'");
			std::string contract = parameters["contract"].as<std::string>();
			if (!parameters.contains("caller_name"))
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 'caller_name'");
			std::string caller_name = parameters["caller_name"].as<std::string>();
			if (!parameters.contains("function_name"))
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 'function_name'");
			std::string function_name = parameters["function_name"].as<std::string>();
			if (!parameters.contains("params"))
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 'params'");
			std::string params = parameters["params"].as<std::string>();

			std::string result = get_client()->contract_call_offline(contract, caller_name, function_name, params);
			return fc::variant(result);
		}

		fc::variant CommonApiRpcServer::contract_load_to_file_positional(fc::rpc::json_connection* json_connection, const fc::variants& parameters)
		{
			// this method has no prerequisites

			if (parameters.size() <= 0)
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 1 (contract)");
			std::string contract = parameters[0].as<std::string>();
			if (parameters.size() <= 1)
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 2 (file)");
			fc::path file = parameters[1].as<fc::path>();

			cdcchain::consensus::ContractEntryPrintable result = get_client()->contract_load_to_file(contract, file);
			return fc::variant(result);
		}

		fc::variant CommonApiRpcServer::contract_load_to_file_named(fc::rpc::json_connection* json_connection, const fc::variant_object& parameters)
		{
			// this method has no prerequisites

			if (!parameters.contains("contract"))
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 'contract'");
			std::string contract = parameters["contract"].as<std::string>();
			if (!parameters.contains("file"))
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 'file'");
			fc::path file = parameters["file"].as<fc::path>();

			cdcchain::consensus::ContractEntryPrintable result = get_client()->contract_load_to_file(contract, file);
			return fc::variant(result);
		}

		fc::variant CommonApiRpcServer::get_result_trx_id_positional(fc::rpc::json_connection* json_connection, const fc::variants& parameters)
		{
			// this method has no prerequisites

			if (parameters.size() <= 0)
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 1 (request_id)");
			cdcchain::consensus::TransactionIdType request_id = parameters[0].as<cdcchain::consensus::TransactionIdType>();

			cdcchain::consensus::TransactionIdType result = get_client()->get_result_trx_id(request_id);
			return fc::variant(result);
		}

		fc::variant CommonApiRpcServer::get_result_trx_id_named(fc::rpc::json_connection* json_connection, const fc::variant_object& parameters)
		{
			// this method has no prerequisites

			if (!parameters.contains("request_id"))
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 'request_id'");
			cdcchain::consensus::TransactionIdType request_id = parameters["request_id"].as<cdcchain::consensus::TransactionIdType>();

			cdcchain::consensus::TransactionIdType result = get_client()->get_result_trx_id(request_id);
			return fc::variant(result);
		}

		fc::variant CommonApiRpcServer::get_request_trx_id_positional(fc::rpc::json_connection* json_connection, const fc::variants& parameters)
		{
			// this method has no prerequisites

			if (parameters.size() <= 0)
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 1 (request_id)");
			cdcchain::consensus::TransactionIdType request_id = parameters[0].as<cdcchain::consensus::TransactionIdType>();

			cdcchain::consensus::TransactionIdType result = get_client()->get_request_trx_id(request_id);
			return fc::variant(result);
		}

		fc::variant CommonApiRpcServer::get_request_trx_id_named(fc::rpc::json_connection* json_connection, const fc::variant_object& parameters)
		{
			// this method has no prerequisites

			if (!parameters.contains("request_id"))
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 'request_id'");
			cdcchain::consensus::TransactionIdType request_id = parameters["request_id"].as<cdcchain::consensus::TransactionIdType>();

			cdcchain::consensus::TransactionIdType result = get_client()->get_request_trx_id(request_id);
			return fc::variant(result);
		}

		fc::variant CommonApiRpcServer::simulator_open_positional(fc::rpc::json_connection* json_connection, const fc::variants& parameters)
		{
			// check all of this method's prerequisites
			verify_json_connection_is_authenticated(json_connection);
			verify_wallet_is_open();
			verify_wallet_is_unlocked();
			// done checking prerequisites


			get_client()->simulator_open();
			return fc::variant();
		}

		fc::variant CommonApiRpcServer::simulator_open_named(fc::rpc::json_connection* json_connection, const fc::variant_object& parameters)
		{
			// check all of this method's prerequisites
			verify_json_connection_is_authenticated(json_connection);
			verify_wallet_is_open();
			verify_wallet_is_unlocked();
			// done checking prerequisites


			get_client()->simulator_open();
			return fc::variant();
		}

		fc::variant CommonApiRpcServer::simulator_close_positional(fc::rpc::json_connection* json_connection, const fc::variants& parameters)
		{
			// check all of this method's prerequisites
			verify_json_connection_is_authenticated(json_connection);
			verify_wallet_is_open();
			verify_wallet_is_unlocked();
			// done checking prerequisites


			get_client()->simulator_close();
			return fc::variant();
		}

		fc::variant CommonApiRpcServer::simulator_close_named(fc::rpc::json_connection* json_connection, const fc::variant_object& parameters)
		{
			// check all of this method's prerequisites
			verify_json_connection_is_authenticated(json_connection);
			verify_wallet_is_open();
			verify_wallet_is_unlocked();
			// done checking prerequisites


			get_client()->simulator_close();
			return fc::variant();
		}

		fc::variant CommonApiRpcServer::simulator_contract_register_positional(fc::rpc::json_connection* json_connection, const fc::variants& parameters)
		{
			// check all of this method's prerequisites
			verify_json_connection_is_authenticated(json_connection);
			verify_wallet_is_open();
			verify_wallet_is_unlocked();
			verify_simulator_is_open();
			// done checking prerequisites

			if (parameters.size() <= 0)
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 1 (owner)");
			std::string owner = parameters[0].as<std::string>();
			if (parameters.size() <= 1)
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 2 (codefile)");
			fc::path codefile = parameters[1].as<fc::path>();
			if (parameters.size() <= 2)
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 3 (asset_symbol)");
			std::string asset_symbol = parameters[2].as<std::string>();
			if (parameters.size() <= 3)
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 4 (initLimit)");
			fc::optional<double> initLimit = parameters[3].as<fc::optional<double>>();

			std::string result = get_client()->simulator_contract_register(owner, codefile, asset_symbol, initLimit);
			return fc::variant(result);
		}

		fc::variant CommonApiRpcServer::simulator_contract_register_named(fc::rpc::json_connection* json_connection, const fc::variant_object& parameters)
		{
			// check all of this method's prerequisites
			verify_json_connection_is_authenticated(json_connection);
			verify_wallet_is_open();
			verify_wallet_is_unlocked();
			verify_simulator_is_open();
			// done checking prerequisites

			if (!parameters.contains("owner"))
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 'owner'");
			std::string owner = parameters["owner"].as<std::string>();
			if (!parameters.contains("codefile"))
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 'codefile'");
			fc::path codefile = parameters["codefile"].as<fc::path>();
			if (!parameters.contains("asset_symbol"))
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 'asset_symbol'");
			std::string asset_symbol = parameters["asset_symbol"].as<std::string>();
			if (!parameters.contains("initLimit"))
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 'initLimit'");
			fc::optional<double> initLimit = parameters["initLimit"].as<fc::optional<double>>();

			std::string result = get_client()->simulator_contract_register(owner, codefile, asset_symbol, initLimit);
			return fc::variant(result);
		}

		fc::variant CommonApiRpcServer::simulator_contract_call_positional(fc::rpc::json_connection* json_connection, const fc::variants& parameters)
		{
			// check all of this method's prerequisites
			verify_json_connection_is_authenticated(json_connection);
			verify_wallet_is_open();
			verify_wallet_is_unlocked();
			verify_simulator_is_open();
			// done checking prerequisites

			if (parameters.size() <= 0)
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 1 (contract)");
			std::string contract = parameters[0].as<std::string>();
			if (parameters.size() <= 1)
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 2 (caller_name)");
			std::string caller_name = parameters[1].as<std::string>();
			if (parameters.size() <= 2)
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 3 (function_name)");
			std::string function_name = parameters[2].as<std::string>();
			if (parameters.size() <= 3)
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 4 (params)");
			std::string params = parameters[3].as<std::string>();
			if (parameters.size() <= 4)
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 5 (cost_asset)");
			std::string cost_asset = parameters[4].as<std::string>();
			if (parameters.size() <= 5)
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 6 (callLimit)");
			fc::optional<double> callLimit = parameters[5].as<fc::optional<double>>();

			cdcchain::wallet::WalletTransactionEntry result = get_client()->simulator_contract_call(contract, caller_name, function_name, params, cost_asset, callLimit);
			return fc::variant(result);
		}

		fc::variant CommonApiRpcServer::simulator_contract_call_named(fc::rpc::json_connection* json_connection, const fc::variant_object& parameters)
		{
			// check all of this method's prerequisites
			verify_json_connection_is_authenticated(json_connection);
			verify_wallet_is_open();
			verify_wallet_is_unlocked();
			verify_simulator_is_open();
			// done checking prerequisites

			if (!parameters.contains("contract"))
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 'contract'");
			std::string contract = parameters["contract"].as<std::string>();
			if (!parameters.contains("caller_name"))
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 'caller_name'");
			std::string caller_name = parameters["caller_name"].as<std::string>();
			if (!parameters.contains("function_name"))
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 'function_name'");
			std::string function_name = parameters["function_name"].as<std::string>();
			if (!parameters.contains("params"))
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 'params'");
			std::string params = parameters["params"].as<std::string>();
			if (!parameters.contains("cost_asset"))
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 'cost_asset'");
			std::string cost_asset = parameters["cost_asset"].as<std::string>();
			if (!parameters.contains("callLimit"))
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 'callLimit'");
			fc::optional<double> callLimit = parameters["callLimit"].as<fc::optional<double>>();

			cdcchain::wallet::WalletTransactionEntry result = get_client()->simulator_contract_call(contract, caller_name, function_name, params, cost_asset, callLimit);
			return fc::variant(result);
		}

		fc::variant CommonApiRpcServer::simulator_contract_upgrade_positional(fc::rpc::json_connection* json_connection, const fc::variants& parameters)
		{
			// check all of this method's prerequisites
			verify_json_connection_is_authenticated(json_connection);
			verify_wallet_is_open();
			verify_wallet_is_unlocked();
			verify_simulator_is_open();
			// done checking prerequisites

			if (parameters.size() <= 0)
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 1 (contract_address)");
			std::string contract_address = parameters[0].as<std::string>();
			if (parameters.size() <= 1)
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 2 (upgrader_name)");
			std::string upgrader_name = parameters[1].as<std::string>();
			if (parameters.size() <= 2)
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 3 (new_contract_name)");
			std::string new_contract_name = parameters[2].as<std::string>();
			if (parameters.size() <= 3)
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 4 (new_contract_desc)");
			cdcchain::consensus::Imessage new_contract_desc = parameters[3].as<cdcchain::consensus::Imessage>();
			if (parameters.size() <= 4)
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 5 (asset_symbol)");
			std::string asset_symbol = parameters[4].as<std::string>();
			if (parameters.size() <= 5)
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 6 (exec_limit)");
			fc::optional<double> exec_limit = parameters[5].as<fc::optional<double>>();

			cdcchain::wallet::WalletTransactionEntry result = get_client()->simulator_contract_upgrade(contract_address, upgrader_name, new_contract_name, new_contract_desc, asset_symbol, exec_limit);
			return fc::variant(result);
		}

		fc::variant CommonApiRpcServer::simulator_contract_upgrade_named(fc::rpc::json_connection* json_connection, const fc::variant_object& parameters)
		{
			// check all of this method's prerequisites
			verify_json_connection_is_authenticated(json_connection);
			verify_wallet_is_open();
			verify_wallet_is_unlocked();
			verify_simulator_is_open();
			// done checking prerequisites

			if (!parameters.contains("contract_address"))
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 'contract_address'");
			std::string contract_address = parameters["contract_address"].as<std::string>();
			if (!parameters.contains("upgrader_name"))
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 'upgrader_name'");
			std::string upgrader_name = parameters["upgrader_name"].as<std::string>();
			if (!parameters.contains("new_contract_name"))
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 'new_contract_name'");
			std::string new_contract_name = parameters["new_contract_name"].as<std::string>();
			if (!parameters.contains("new_contract_desc"))
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 'new_contract_desc'");
			cdcchain::consensus::Imessage new_contract_desc = parameters["new_contract_desc"].as<cdcchain::consensus::Imessage>();
			if (!parameters.contains("asset_symbol"))
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 'asset_symbol'");
			std::string asset_symbol = parameters["asset_symbol"].as<std::string>();
			if (!parameters.contains("exec_limit"))
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 'exec_limit'");
			fc::optional<double> exec_limit = parameters["exec_limit"].as<fc::optional<double>>();

			cdcchain::wallet::WalletTransactionEntry result = get_client()->simulator_contract_upgrade(contract_address, upgrader_name, new_contract_name, new_contract_desc, asset_symbol, exec_limit);
			return fc::variant(result);
		}

		fc::variant CommonApiRpcServer::simulator_contract_upgrade_testing_positional(fc::rpc::json_connection* json_connection, const fc::variants& parameters)
		{
			// check all of this method's prerequisites
			verify_json_connection_is_authenticated(json_connection);
			verify_wallet_is_open();
			verify_wallet_is_unlocked();
			verify_simulator_is_open();
			// done checking prerequisites

			if (parameters.size() <= 0)
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 1 (contract_address)");
			std::string contract_address = parameters[0].as<std::string>();
			if (parameters.size() <= 1)
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 2 (upgrader_name)");
			std::string upgrader_name = parameters[1].as<std::string>();
			if (parameters.size() <= 2)
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 3 (new_contract_name)");
			std::string new_contract_name = parameters[2].as<std::string>();
			if (parameters.size() <= 3)
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 4 (new_contract_desc)");
			cdcchain::consensus::Imessage new_contract_desc = parameters[3].as<cdcchain::consensus::Imessage>();

			std::vector<cdcchain::consensus::Asset> result = get_client()->simulator_contract_upgrade_testing(contract_address, upgrader_name, new_contract_name, new_contract_desc);
			return fc::variant(result);
		}

		fc::variant CommonApiRpcServer::simulator_contract_upgrade_testing_named(fc::rpc::json_connection* json_connection, const fc::variant_object& parameters)
		{
			// check all of this method's prerequisites
			verify_json_connection_is_authenticated(json_connection);
			verify_wallet_is_open();
			verify_wallet_is_unlocked();
			verify_simulator_is_open();
			// done checking prerequisites

			if (!parameters.contains("contract_address"))
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 'contract_address'");
			std::string contract_address = parameters["contract_address"].as<std::string>();
			if (!parameters.contains("upgrader_name"))
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 'upgrader_name'");
			std::string upgrader_name = parameters["upgrader_name"].as<std::string>();
			if (!parameters.contains("new_contract_name"))
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 'new_contract_name'");
			std::string new_contract_name = parameters["new_contract_name"].as<std::string>();
			if (!parameters.contains("new_contract_desc"))
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 'new_contract_desc'");
			cdcchain::consensus::Imessage new_contract_desc = parameters["new_contract_desc"].as<cdcchain::consensus::Imessage>();

			std::vector<cdcchain::consensus::Asset> result = get_client()->simulator_contract_upgrade_testing(contract_address, upgrader_name, new_contract_name, new_contract_desc);
			return fc::variant(result);
		}

		fc::variant CommonApiRpcServer::simulator_contract_destroy_positional(fc::rpc::json_connection* json_connection, const fc::variants& parameters)
		{
			// check all of this method's prerequisites
			verify_json_connection_is_authenticated(json_connection);
			verify_wallet_is_open();
			verify_wallet_is_unlocked();
			verify_simulator_is_open();
			// done checking prerequisites

			if (parameters.size() <= 0)
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 1 (contract_address)");
			std::string contract_address = parameters[0].as<std::string>();
			if (parameters.size() <= 1)
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 2 (destroyer_name)");
			std::string destroyer_name = parameters[1].as<std::string>();
			if (parameters.size() <= 2)
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 3 (asset_symbol)");
			std::string asset_symbol = parameters[2].as<std::string>();
			if (parameters.size() <= 3)
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 4 (exec_limit)");
			fc::optional<double> exec_limit = parameters[3].as<fc::optional<double>>();

			cdcchain::wallet::WalletTransactionEntry result = get_client()->simulator_contract_destroy(contract_address, destroyer_name, asset_symbol, exec_limit);
			return fc::variant(result);
		}

		fc::variant CommonApiRpcServer::simulator_contract_destroy_named(fc::rpc::json_connection* json_connection, const fc::variant_object& parameters)
		{
			// check all of this method's prerequisites
			verify_json_connection_is_authenticated(json_connection);
			verify_wallet_is_open();
			verify_wallet_is_unlocked();
			verify_simulator_is_open();
			// done checking prerequisites

			if (!parameters.contains("contract_address"))
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 'contract_address'");
			std::string contract_address = parameters["contract_address"].as<std::string>();
			if (!parameters.contains("destroyer_name"))
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 'destroyer_name'");
			std::string destroyer_name = parameters["destroyer_name"].as<std::string>();
			if (!parameters.contains("asset_symbol"))
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 'asset_symbol'");
			std::string asset_symbol = parameters["asset_symbol"].as<std::string>();
			if (!parameters.contains("exec_limit"))
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 'exec_limit'");
			fc::optional<double> exec_limit = parameters["exec_limit"].as<fc::optional<double>>();

			cdcchain::wallet::WalletTransactionEntry result = get_client()->simulator_contract_destroy(contract_address, destroyer_name, asset_symbol, exec_limit);
			return fc::variant(result);
		}

		fc::variant CommonApiRpcServer::simulator_contract_destroy_testing_positional(fc::rpc::json_connection* json_connection, const fc::variants& parameters)
		{
			// check all of this method's prerequisites
			verify_json_connection_is_authenticated(json_connection);
			verify_wallet_is_open();
			verify_wallet_is_unlocked();
			verify_simulator_is_open();
			// done checking prerequisites

			if (parameters.size() <= 0)
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 1 (contract_address)");
			std::string contract_address = parameters[0].as<std::string>();
			if (parameters.size() <= 1)
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 2 (destroyer_name)");
			std::string destroyer_name = parameters[1].as<std::string>();

			std::vector<cdcchain::consensus::Asset> result = get_client()->simulator_contract_destroy_testing(contract_address, destroyer_name);
			return fc::variant(result);
		}

		fc::variant CommonApiRpcServer::simulator_contract_destroy_testing_named(fc::rpc::json_connection* json_connection, const fc::variant_object& parameters)
		{
			// check all of this method's prerequisites
			verify_json_connection_is_authenticated(json_connection);
			verify_wallet_is_open();
			verify_wallet_is_unlocked();
			verify_simulator_is_open();
			// done checking prerequisites

			if (!parameters.contains("contract_address"))
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 'contract_address'");
			std::string contract_address = parameters["contract_address"].as<std::string>();
			if (!parameters.contains("destroyer_name"))
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 'destroyer_name'");
			std::string destroyer_name = parameters["destroyer_name"].as<std::string>();

			std::vector<cdcchain::consensus::Asset> result = get_client()->simulator_contract_destroy_testing(contract_address, destroyer_name);
			return fc::variant(result);
		}

		fc::variant CommonApiRpcServer::simulator_contract_get_info_positional(fc::rpc::json_connection* json_connection, const fc::variants& parameters)
		{
			// check all of this method's prerequisites
			verify_json_connection_is_authenticated(json_connection);
			verify_wallet_is_open();
			verify_wallet_is_unlocked();
			verify_simulator_is_open();
			// done checking prerequisites

			if (parameters.size() <= 0)
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 1 (contract)");
			std::string contract = parameters[0].as<std::string>();

			cdcchain::consensus::ContractEntryPrintable result = get_client()->simulator_contract_get_info(contract);
			return fc::variant(result);
		}

		fc::variant CommonApiRpcServer::simulator_contract_get_info_named(fc::rpc::json_connection* json_connection, const fc::variant_object& parameters)
		{
			// check all of this method's prerequisites
			verify_json_connection_is_authenticated(json_connection);
			verify_wallet_is_open();
			verify_wallet_is_unlocked();
			verify_simulator_is_open();
			// done checking prerequisites

			if (!parameters.contains("contract"))
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 'contract'");
			std::string contract = parameters["contract"].as<std::string>();

			cdcchain::consensus::ContractEntryPrintable result = get_client()->simulator_contract_get_info(contract);
			return fc::variant(result);
		}

		fc::variant CommonApiRpcServer::simulator_contract_get_balance_positional(fc::rpc::json_connection* json_connection, const fc::variants& parameters)
		{
			// check all of this method's prerequisites
			verify_json_connection_is_authenticated(json_connection);
			verify_wallet_is_open();
			verify_wallet_is_unlocked();
			verify_simulator_is_open();
			// done checking prerequisites

			if (parameters.size() <= 0)
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 1 (contract)");
			std::string contract = parameters[0].as<std::string>();

			std::vector<cdcchain::consensus::BalanceEntry> result = get_client()->simulator_contract_get_balance(contract);
			return fc::variant(result);
		}

		fc::variant CommonApiRpcServer::simulator_contract_get_balance_named(fc::rpc::json_connection* json_connection, const fc::variant_object& parameters)
		{
			// check all of this method's prerequisites
			verify_json_connection_is_authenticated(json_connection);
			verify_wallet_is_open();
			verify_wallet_is_unlocked();
			verify_simulator_is_open();
			// done checking prerequisites

			if (!parameters.contains("contract"))
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 'contract'");
			std::string contract = parameters["contract"].as<std::string>();

			std::vector<cdcchain::consensus::BalanceEntry> result = get_client()->simulator_contract_get_balance(contract);
			return fc::variant(result);
		}

		fc::variant CommonApiRpcServer::simulator_transfer_to_contract_positional(fc::rpc::json_connection* json_connection, const fc::variants& parameters)
		{
			// check all of this method's prerequisites
			verify_json_connection_is_authenticated(json_connection);
			verify_wallet_is_open();
			verify_wallet_is_unlocked();
			verify_simulator_is_open();
			// done checking prerequisites

			if (parameters.size() <= 0)
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 1 (amount_to_transfer)");
			double amount_to_transfer = parameters[0].as<double>();
			if (parameters.size() <= 1)
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 2 (asset_symbol)");
			std::string asset_symbol = parameters[1].as<std::string>();
			if (parameters.size() <= 2)
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 3 (from_account_name)");
			std::string from_account_name = parameters[2].as<std::string>();
			if (parameters.size() <= 3)
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 4 (to_contract)");
			std::string to_contract = parameters[3].as<std::string>();
			if (parameters.size() <= 4)
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 5 (amount_for_exec)");
			double amount_for_exec = parameters[4].as<double>();

			cdcchain::wallet::WalletTransactionEntry result = get_client()->simulator_transfer_to_contract(amount_to_transfer, asset_symbol, from_account_name, to_contract, amount_for_exec);
			return fc::variant(result);
		}

		fc::variant CommonApiRpcServer::simulator_transfer_to_contract_named(fc::rpc::json_connection* json_connection, const fc::variant_object& parameters)
		{
			// check all of this method's prerequisites
			verify_json_connection_is_authenticated(json_connection);
			verify_wallet_is_open();
			verify_wallet_is_unlocked();
			verify_simulator_is_open();
			// done checking prerequisites

			if (!parameters.contains("amount_to_transfer"))
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 'amount_to_transfer'");
			double amount_to_transfer = parameters["amount_to_transfer"].as<double>();
			if (!parameters.contains("asset_symbol"))
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 'asset_symbol'");
			std::string asset_symbol = parameters["asset_symbol"].as<std::string>();
			if (!parameters.contains("from_account_name"))
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 'from_account_name'");
			std::string from_account_name = parameters["from_account_name"].as<std::string>();
			if (!parameters.contains("to_contract"))
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 'to_contract'");
			std::string to_contract = parameters["to_contract"].as<std::string>();
			if (!parameters.contains("amount_for_exec"))
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 'amount_for_exec'");
			double amount_for_exec = parameters["amount_for_exec"].as<double>();

			cdcchain::wallet::WalletTransactionEntry result = get_client()->simulator_transfer_to_contract(amount_to_transfer, asset_symbol, from_account_name, to_contract, amount_for_exec);
			return fc::variant(result);
		}

		fc::variant CommonApiRpcServer::simulator_account_balance_positional(fc::rpc::json_connection* json_connection, const fc::variants& parameters)
		{
			// check all of this method's prerequisites
			verify_json_connection_is_authenticated(json_connection);
			verify_wallet_is_open();
			verify_wallet_is_unlocked();
			verify_simulator_is_open();
			// done checking prerequisites

			std::string account_name = (parameters.size() <= 0) ?
				(fc::json::from_string("\"\"").as<std::string>()) :
				parameters[0].as<std::string>();

			cdcchain::wallet::AccountBalanceSummaryType result = get_client()->simulator_account_balance(account_name);
			return fc::variant(result);
		}

		fc::variant CommonApiRpcServer::simulator_account_balance_named(fc::rpc::json_connection* json_connection, const fc::variant_object& parameters)
		{
			// check all of this method's prerequisites
			verify_json_connection_is_authenticated(json_connection);
			verify_wallet_is_open();
			verify_wallet_is_unlocked();
			verify_simulator_is_open();
			// done checking prerequisites

			std::string account_name = parameters.contains("account_name") ?
				(fc::json::from_string("\"\"").as<std::string>()) :
				parameters["account_name"].as<std::string>();

			cdcchain::wallet::AccountBalanceSummaryType result = get_client()->simulator_account_balance(account_name);
			return fc::variant(result);
		}

		fc::variant CommonApiRpcServer::simulator_contract_compile_positional(fc::rpc::json_connection* json_connection, const fc::variants& parameters)
		{
			// check all of this method's prerequisites
			verify_json_connection_is_authenticated(json_connection);
			verify_wallet_is_open();
			verify_wallet_is_unlocked();
			verify_simulator_is_open();
			// done checking prerequisites

			if (parameters.size() <= 0)
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 1 (filename)");
			fc::path filename = parameters[0].as<fc::path>();

			fc::path result = get_client()->simulator_contract_compile(filename);
			return fc::variant(result);
		}

		fc::variant CommonApiRpcServer::simulator_contract_compile_named(fc::rpc::json_connection* json_connection, const fc::variant_object& parameters)
		{
			// check all of this method's prerequisites
			verify_json_connection_is_authenticated(json_connection);
			verify_wallet_is_open();
			verify_wallet_is_unlocked();
			verify_simulator_is_open();
			// done checking prerequisites

			if (!parameters.contains("filename"))
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 'filename'");
			fc::path filename = parameters["filename"].as<fc::path>();

			fc::path result = get_client()->simulator_contract_compile(filename);
			return fc::variant(result);
		}

		fc::variant CommonApiRpcServer::simulator_contract_load_to_file_positional(fc::rpc::json_connection* json_connection, const fc::variants& parameters)
		{
			// check all of this method's prerequisites
			verify_json_connection_is_authenticated(json_connection);
			verify_wallet_is_open();
			verify_wallet_is_unlocked();
			verify_simulator_is_open();
			// done checking prerequisites

			if (parameters.size() <= 0)
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 1 (contract)");
			std::string contract = parameters[0].as<std::string>();
			if (parameters.size() <= 1)
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 2 (file)");
			fc::path file = parameters[1].as<fc::path>();

			cdcchain::consensus::ContractEntryPrintable result = get_client()->simulator_contract_load_to_file(contract, file);
			return fc::variant(result);
		}

		fc::variant CommonApiRpcServer::simulator_contract_load_to_file_named(fc::rpc::json_connection* json_connection, const fc::variant_object& parameters)
		{
			// check all of this method's prerequisites
			verify_json_connection_is_authenticated(json_connection);
			verify_wallet_is_open();
			verify_wallet_is_unlocked();
			verify_simulator_is_open();
			// done checking prerequisites

			if (!parameters.contains("contract"))
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 'contract'");
			std::string contract = parameters["contract"].as<std::string>();
			if (!parameters.contains("file"))
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 'file'");
			fc::path file = parameters["file"].as<fc::path>();

			cdcchain::consensus::ContractEntryPrintable result = get_client()->simulator_contract_load_to_file(contract, file);
			return fc::variant(result);
		}

		fc::variant CommonApiRpcServer::simulator_contract_register_testing_positional(fc::rpc::json_connection* json_connection, const fc::variants& parameters)
		{
			// check all of this method's prerequisites
			verify_json_connection_is_authenticated(json_connection);
			verify_wallet_is_open();
			verify_wallet_is_unlocked();
			verify_simulator_is_open();
			// done checking prerequisites

			if (parameters.size() <= 0)
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 1 (owner)");
			std::string owner = parameters[0].as<std::string>();
			if (parameters.size() <= 1)
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 2 (codefile)");
			fc::path codefile = parameters[1].as<fc::path>();

			std::vector<cdcchain::consensus::Asset> result = get_client()->simulator_contract_register_testing(owner, codefile);
			return fc::variant(result);
		}

		fc::variant CommonApiRpcServer::simulator_contract_register_testing_named(fc::rpc::json_connection* json_connection, const fc::variant_object& parameters)
		{
			// check all of this method's prerequisites
			verify_json_connection_is_authenticated(json_connection);
			verify_wallet_is_open();
			verify_wallet_is_unlocked();
			verify_simulator_is_open();
			// done checking prerequisites

			if (!parameters.contains("owner"))
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 'owner'");
			std::string owner = parameters["owner"].as<std::string>();
			if (!parameters.contains("codefile"))
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 'codefile'");
			fc::path codefile = parameters["codefile"].as<fc::path>();

			std::vector<cdcchain::consensus::Asset> result = get_client()->simulator_contract_register_testing(owner, codefile);
			return fc::variant(result);
		}

		fc::variant CommonApiRpcServer::simulator_contract_call_testing_positional(fc::rpc::json_connection* json_connection, const fc::variants& parameters)
		{
			// check all of this method's prerequisites
			verify_json_connection_is_authenticated(json_connection);
			verify_wallet_is_open();
			verify_wallet_is_unlocked();
			verify_simulator_is_open();
			// done checking prerequisites

			if (parameters.size() <= 0)
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 1 (contract)");
			std::string contract = parameters[0].as<std::string>();
			if (parameters.size() <= 1)
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 2 (caller_name)");
			std::string caller_name = parameters[1].as<std::string>();
			if (parameters.size() <= 2)
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 3 (function_name)");
			std::string function_name = parameters[2].as<std::string>();
			if (parameters.size() <= 3)
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 4 (params)");
			std::string params = parameters[3].as<std::string>();

			std::vector<cdcchain::consensus::Asset> result = get_client()->simulator_contract_call_testing(contract, caller_name, function_name, params);
			return fc::variant(result);
		}

		fc::variant CommonApiRpcServer::simulator_contract_call_testing_named(fc::rpc::json_connection* json_connection, const fc::variant_object& parameters)
		{
			// check all of this method's prerequisites
			verify_json_connection_is_authenticated(json_connection);
			verify_wallet_is_open();
			verify_wallet_is_unlocked();
			verify_simulator_is_open();
			// done checking prerequisites

			if (!parameters.contains("contract"))
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 'contract'");
			std::string contract = parameters["contract"].as<std::string>();
			if (!parameters.contains("caller_name"))
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 'caller_name'");
			std::string caller_name = parameters["caller_name"].as<std::string>();
			if (!parameters.contains("function_name"))
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 'function_name'");
			std::string function_name = parameters["function_name"].as<std::string>();
			if (!parameters.contains("params"))
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 'params'");
			std::string params = parameters["params"].as<std::string>();

			std::vector<cdcchain::consensus::Asset> result = get_client()->simulator_contract_call_testing(contract, caller_name, function_name, params);
			return fc::variant(result);
		}

		fc::variant CommonApiRpcServer::simulator_transfer_to_contract_testing_positional(fc::rpc::json_connection* json_connection, const fc::variants& parameters)
		{
			// check all of this method's prerequisites
			verify_json_connection_is_authenticated(json_connection);
			verify_wallet_is_open();
			verify_wallet_is_unlocked();
			verify_simulator_is_open();
			// done checking prerequisites

			if (parameters.size() <= 0)
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 1 (amount_to_transfer)");
			double amount_to_transfer = parameters[0].as<double>();
			if (parameters.size() <= 1)
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 2 (asset_symbol)");
			std::string asset_symbol = parameters[1].as<std::string>();
			if (parameters.size() <= 2)
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 3 (from_account_name)");
			std::string from_account_name = parameters[2].as<std::string>();
			if (parameters.size() <= 3)
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 4 (to_contract)");
			std::string to_contract = parameters[3].as<std::string>();

			std::vector<cdcchain::consensus::Asset> result = get_client()->simulator_transfer_to_contract_testing(amount_to_transfer, asset_symbol, from_account_name, to_contract);
			return fc::variant(result);
		}

		fc::variant CommonApiRpcServer::simulator_transfer_to_contract_testing_named(fc::rpc::json_connection* json_connection, const fc::variant_object& parameters)
		{
			// check all of this method's prerequisites
			verify_json_connection_is_authenticated(json_connection);
			verify_wallet_is_open();
			verify_wallet_is_unlocked();
			verify_simulator_is_open();
			// done checking prerequisites

			if (!parameters.contains("amount_to_transfer"))
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 'amount_to_transfer'");
			double amount_to_transfer = parameters["amount_to_transfer"].as<double>();
			if (!parameters.contains("asset_symbol"))
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 'asset_symbol'");
			std::string asset_symbol = parameters["asset_symbol"].as<std::string>();
			if (!parameters.contains("from_account_name"))
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 'from_account_name'");
			std::string from_account_name = parameters["from_account_name"].as<std::string>();
			if (!parameters.contains("to_contract"))
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 'to_contract'");
			std::string to_contract = parameters["to_contract"].as<std::string>();

			std::vector<cdcchain::consensus::Asset> result = get_client()->simulator_transfer_to_contract_testing(amount_to_transfer, asset_symbol, from_account_name, to_contract);
			return fc::variant(result);
		}

		fc::variant CommonApiRpcServer::simulator_list_my_addresses_positional(fc::rpc::json_connection* json_connection, const fc::variants& parameters)
		{
			// check all of this method's prerequisites
			verify_json_connection_is_authenticated(json_connection);
			verify_wallet_is_open();
			verify_wallet_is_unlocked();
			verify_simulator_is_open();
			// done checking prerequisites

			std::string account_name = (parameters.size() <= 0) ?
				(fc::json::from_string("\"\"").as<std::string>()) :
				parameters[0].as<std::string>();

			vector<cdcchain::consensus::SimulatorAccountInfo> result = get_client()->simulator_list_my_addresses(account_name);
			return fc::variant(result);
		}

		fc::variant CommonApiRpcServer::simulator_list_my_addresses_named(fc::rpc::json_connection* json_connection, const fc::variant_object& parameters)
		{
			// check all of this method's prerequisites
			verify_json_connection_is_authenticated(json_connection);
			verify_wallet_is_open();
			verify_wallet_is_unlocked();
			verify_simulator_is_open();
			// done checking prerequisites

			std::string account_name = parameters.contains("account_name") ?
				(fc::json::from_string("\"\"").as<std::string>()) :
				parameters["account_name"].as<std::string>();

			vector<cdcchain::consensus::SimulatorAccountInfo> result = get_client()->simulator_list_my_addresses(account_name);
			return fc::variant(result);
		}

		fc::variant CommonApiRpcServer::get_contract_registered_in_transaction_positional(fc::rpc::json_connection* json_connection, const fc::variants& parameters)
		{
			// this method has no prerequisites

			if (parameters.size() <= 0)
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 1 (trx_id)");
			cdcchain::consensus::TransactionIdType trx_id = parameters[0].as<cdcchain::consensus::TransactionIdType>();

			std::string result = get_client()->get_contract_registered_in_transaction(trx_id);
			return fc::variant(result);
		}

		fc::variant CommonApiRpcServer::get_contract_registered_in_transaction_named(fc::rpc::json_connection* json_connection, const fc::variant_object& parameters)
		{
			// this method has no prerequisites

			if (!parameters.contains("trx_id"))
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 'trx_id'");
			cdcchain::consensus::TransactionIdType trx_id = parameters["trx_id"].as<cdcchain::consensus::TransactionIdType>();

			std::string result = get_client()->get_contract_registered_in_transaction(trx_id);
			return fc::variant(result);
		}

		fc::variant CommonApiRpcServer::get_transaction_id_contract_registered_positional(fc::rpc::json_connection* json_connection, const fc::variants& parameters)
		{
			// this method has no prerequisites

			if (parameters.size() <= 0)
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 1 (contract_id)");
			std::string contract_id = parameters[0].as<std::string>();

			cdcchain::consensus::TransactionIdType result = get_client()->get_transaction_id_contract_registered(contract_id);
			return fc::variant(result);
		}

		fc::variant CommonApiRpcServer::get_transaction_id_contract_registered_named(fc::rpc::json_connection* json_connection, const fc::variant_object& parameters)
		{
			// this method has no prerequisites

			if (!parameters.contains("contract_id"))
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 'contract_id'");
			std::string contract_id = parameters["contract_id"].as<std::string>();

			cdcchain::consensus::TransactionIdType result = get_client()->get_transaction_id_contract_registered(contract_id);
			return fc::variant(result);
		}

		fc::variant CommonApiRpcServer::contract_get_info_from_gpc_file_positional(fc::rpc::json_connection* json_connection, const fc::variants& parameters)
		{
			// this method has no prerequisites

			if (parameters.size() <= 0)
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 1 (file)");
			fc::path file = parameters[0].as<fc::path>();

			cdcchain::consensus::CodePrintAble result = get_client()->contract_get_info_from_gpc_file(file);
			return fc::variant(result);
		}

		fc::variant CommonApiRpcServer::contract_get_info_from_gpc_file_named(fc::rpc::json_connection* json_connection, const fc::variant_object& parameters)
		{
			// this method has no prerequisites

			if (!parameters.contains("file"))
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 'file'");
			fc::path file = parameters["file"].as<fc::path>();

			cdcchain::consensus::CodePrintAble result = get_client()->contract_get_info_from_gpc_file(file);
			return fc::variant(result);
		}

		fc::variant CommonApiRpcServer::script_compile_positional(fc::rpc::json_connection* json_connection, const fc::variants& parameters)
		{
			// this method has no prerequisites

			if (parameters.size() <= 0)
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 1 (filename)");
			fc::path filename = parameters[0].as<fc::path>();

			fc::path result = get_client()->script_compile(filename);
			return fc::variant(result);
		}

		fc::variant CommonApiRpcServer::script_compile_named(fc::rpc::json_connection* json_connection, const fc::variant_object& parameters)
		{
			// this method has no prerequisites

			if (!parameters.contains("filename"))
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 'filename'");
			fc::path filename = parameters["filename"].as<fc::path>();

			fc::path result = get_client()->script_compile(filename);
			return fc::variant(result);
		}

		fc::variant CommonApiRpcServer::script_add_positional(fc::rpc::json_connection* json_connection, const fc::variants& parameters)
		{
			// check all of this method's prerequisites
			verify_json_connection_is_authenticated(json_connection);
			verify_wallet_is_open();
			verify_wallet_is_unlocked();
			// done checking prerequisites

			if (parameters.size() <= 0)
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 1 (filename)");
			fc::path filename = parameters[0].as<fc::path>();
			if (parameters.size() <= 1)
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 2 (description)");
			cdcchain::consensus::Imessage description = parameters[1].as<cdcchain::consensus::Imessage>();

			std::string result = get_client()->script_add(filename, description);
			return fc::variant(result);
		}

		fc::variant CommonApiRpcServer::script_add_named(fc::rpc::json_connection* json_connection, const fc::variant_object& parameters)
		{
			// check all of this method's prerequisites
			verify_json_connection_is_authenticated(json_connection);
			verify_wallet_is_open();
			verify_wallet_is_unlocked();
			// done checking prerequisites

			if (!parameters.contains("filename"))
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 'filename'");
			fc::path filename = parameters["filename"].as<fc::path>();
			if (!parameters.contains("description"))
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 'description'");
			cdcchain::consensus::Imessage description = parameters["description"].as<cdcchain::consensus::Imessage>();

			std::string result = get_client()->script_add(filename, description);
			return fc::variant(result);
		}

		fc::variant CommonApiRpcServer::script_remove_positional(fc::rpc::json_connection* json_connection, const fc::variants& parameters)
		{
			// check all of this method's prerequisites
			verify_json_connection_is_authenticated(json_connection);
			verify_wallet_is_open();
			verify_wallet_is_unlocked();
			// done checking prerequisites

			if (parameters.size() <= 0)
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 1 (scriptid)");
			std::string scriptid = parameters[0].as<std::string>();

			get_client()->script_remove(scriptid);
			return fc::variant();
		}

		fc::variant CommonApiRpcServer::script_remove_named(fc::rpc::json_connection* json_connection, const fc::variant_object& parameters)
		{
			// check all of this method's prerequisites
			verify_json_connection_is_authenticated(json_connection);
			verify_wallet_is_open();
			verify_wallet_is_unlocked();
			// done checking prerequisites

			if (!parameters.contains("scriptid"))
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 'scriptid'");
			std::string scriptid = parameters["scriptid"].as<std::string>();

			get_client()->script_remove(scriptid);
			return fc::variant();
		}

		fc::variant CommonApiRpcServer::script_get_info_positional(fc::rpc::json_connection* json_connection, const fc::variants& parameters)
		{
			// check all of this method's prerequisites
			verify_json_connection_is_authenticated(json_connection);
			verify_wallet_is_open();
			verify_wallet_is_unlocked();
			// done checking prerequisites

			if (parameters.size() <= 0)
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 1 (scriptid)");
			std::string scriptid = parameters[0].as<std::string>();

			cdcchain::wallet::ScriptEntryPrintable result = get_client()->script_get_info(scriptid);
			return fc::variant(result);
		}

		fc::variant CommonApiRpcServer::script_get_info_named(fc::rpc::json_connection* json_connection, const fc::variant_object& parameters)
		{
			// check all of this method's prerequisites
			verify_json_connection_is_authenticated(json_connection);
			verify_wallet_is_open();
			verify_wallet_is_unlocked();
			// done checking prerequisites

			if (!parameters.contains("scriptid"))
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 'scriptid'");
			std::string scriptid = parameters["scriptid"].as<std::string>();

			cdcchain::wallet::ScriptEntryPrintable result = get_client()->script_get_info(scriptid);
			return fc::variant(result);
		}

		fc::variant CommonApiRpcServer::scripts_list_positional(fc::rpc::json_connection* json_connection, const fc::variants& parameters)
		{
			// check all of this method's prerequisites
			verify_json_connection_is_authenticated(json_connection);
			verify_wallet_is_open();
			verify_wallet_is_unlocked();
			// done checking prerequisites


			std::vector<cdcchain::wallet::ScriptEntryPrintable> result = get_client()->scripts_list();
			return fc::variant(result);
		}

		fc::variant CommonApiRpcServer::scripts_list_named(fc::rpc::json_connection* json_connection, const fc::variant_object& parameters)
		{
			// check all of this method's prerequisites
			verify_json_connection_is_authenticated(json_connection);
			verify_wallet_is_open();
			verify_wallet_is_unlocked();
			// done checking prerequisites


			std::vector<cdcchain::wallet::ScriptEntryPrintable> result = get_client()->scripts_list();
			return fc::variant(result);
		}

		fc::variant CommonApiRpcServer::script_disable_positional(fc::rpc::json_connection* json_connection, const fc::variants& parameters)
		{
			// check all of this method's prerequisites
			verify_json_connection_is_authenticated(json_connection);
			verify_wallet_is_open();
			verify_wallet_is_unlocked();
			// done checking prerequisites

			if (parameters.size() <= 0)
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 1 (scriptid)");
			std::string scriptid = parameters[0].as<std::string>();

			get_client()->script_disable(scriptid);
			return fc::variant();
		}

		fc::variant CommonApiRpcServer::script_disable_named(fc::rpc::json_connection* json_connection, const fc::variant_object& parameters)
		{
			// check all of this method's prerequisites
			verify_json_connection_is_authenticated(json_connection);
			verify_wallet_is_open();
			verify_wallet_is_unlocked();
			// done checking prerequisites

			if (!parameters.contains("scriptid"))
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 'scriptid'");
			std::string scriptid = parameters["scriptid"].as<std::string>();

			get_client()->script_disable(scriptid);
			return fc::variant();
		}

		fc::variant CommonApiRpcServer::script_enable_positional(fc::rpc::json_connection* json_connection, const fc::variants& parameters)
		{
			// check all of this method's prerequisites
			verify_json_connection_is_authenticated(json_connection);
			verify_wallet_is_open();
			verify_wallet_is_unlocked();
			// done checking prerequisites

			if (parameters.size() <= 0)
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 1 (scriptid)");
			std::string scriptid = parameters[0].as<std::string>();

			get_client()->script_enable(scriptid);
			return fc::variant();
		}

		fc::variant CommonApiRpcServer::script_enable_named(fc::rpc::json_connection* json_connection, const fc::variant_object& parameters)
		{
			// check all of this method's prerequisites
			verify_json_connection_is_authenticated(json_connection);
			verify_wallet_is_open();
			verify_wallet_is_unlocked();
			// done checking prerequisites

			if (!parameters.contains("scriptid"))
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 'scriptid'");
			std::string scriptid = parameters["scriptid"].as<std::string>();

			get_client()->script_enable(scriptid);
			return fc::variant();
		}

		fc::variant CommonApiRpcServer::script_import_to_db_positional(fc::rpc::json_connection* json_connection, const fc::variants& parameters)
		{
			// check all of this method's prerequisites
			verify_json_connection_is_authenticated(json_connection);
			verify_wallet_is_open();
			verify_wallet_is_unlocked();
			// done checking prerequisites

			if (parameters.size() <= 0)
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 1 (dbfile)");
			fc::path dbfile = parameters[0].as<fc::path>();

			get_client()->script_import_to_db(dbfile);
			return fc::variant();
		}

		fc::variant CommonApiRpcServer::script_import_to_db_named(fc::rpc::json_connection* json_connection, const fc::variant_object& parameters)
		{
			// check all of this method's prerequisites
			verify_json_connection_is_authenticated(json_connection);
			verify_wallet_is_open();
			verify_wallet_is_unlocked();
			// done checking prerequisites

			if (!parameters.contains("dbfile"))
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 'dbfile'");
			fc::path dbfile = parameters["dbfile"].as<fc::path>();

			get_client()->script_import_to_db(dbfile);
			return fc::variant();
		}

		fc::variant CommonApiRpcServer::script_export_from_db_positional(fc::rpc::json_connection* json_connection, const fc::variants& parameters)
		{
			// check all of this method's prerequisites
			verify_json_connection_is_authenticated(json_connection);
			verify_wallet_is_open();
			verify_wallet_is_unlocked();
			// done checking prerequisites

			if (parameters.size() <= 0)
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 1 (dbfile)");
			fc::path dbfile = parameters[0].as<fc::path>();

			get_client()->script_export_from_db(dbfile);
			return fc::variant();
		}

		fc::variant CommonApiRpcServer::script_export_from_db_named(fc::rpc::json_connection* json_connection, const fc::variant_object& parameters)
		{
			// check all of this method's prerequisites
			verify_json_connection_is_authenticated(json_connection);
			verify_wallet_is_open();
			verify_wallet_is_unlocked();
			// done checking prerequisites

			if (!parameters.contains("dbfile"))
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 'dbfile'");
			fc::path dbfile = parameters["dbfile"].as<fc::path>();

			get_client()->script_export_from_db(dbfile);
			return fc::variant();
		}

		fc::variant CommonApiRpcServer::script_get_events_bound_positional(fc::rpc::json_connection* json_connection, const fc::variants& parameters)
		{
			// check all of this method's prerequisites
			verify_json_connection_is_authenticated(json_connection);
			verify_wallet_is_open();
			verify_wallet_is_unlocked();
			// done checking prerequisites

			if (parameters.size() <= 0)
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 1 (script_id)");
			std::string script_id = parameters[0].as<std::string>();

			std::vector<std::string> result = get_client()->script_get_events_bound(script_id);
			return fc::variant(result);
		}

		fc::variant CommonApiRpcServer::script_get_events_bound_named(fc::rpc::json_connection* json_connection, const fc::variant_object& parameters)
		{
			// check all of this method's prerequisites
			verify_json_connection_is_authenticated(json_connection);
			verify_wallet_is_open();
			verify_wallet_is_unlocked();
			// done checking prerequisites

			if (!parameters.contains("script_id"))
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 'script_id'");
			std::string script_id = parameters["script_id"].as<std::string>();

			std::vector<std::string> result = get_client()->script_get_events_bound(script_id);
			return fc::variant(result);
		}

		fc::variant CommonApiRpcServer::script_list_event_handler_positional(fc::rpc::json_connection* json_connection, const fc::variants& parameters)
		{
			// check all of this method's prerequisites
			verify_json_connection_is_authenticated(json_connection);
			verify_wallet_is_open();
			verify_wallet_is_unlocked();
			// done checking prerequisites

			if (parameters.size() <= 0)
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 1 (contract_id_str)");
			std::string contract_id_str = parameters[0].as<std::string>();
			if (parameters.size() <= 1)
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 2 (event_type)");
			std::string event_type = parameters[1].as<std::string>();

			std::vector<std::string> result = get_client()->script_list_event_handler(contract_id_str, event_type);
			return fc::variant(result);
		}

		fc::variant CommonApiRpcServer::script_list_event_handler_named(fc::rpc::json_connection* json_connection, const fc::variant_object& parameters)
		{
			// check all of this method's prerequisites
			verify_json_connection_is_authenticated(json_connection);
			verify_wallet_is_open();
			verify_wallet_is_unlocked();
			// done checking prerequisites

			if (!parameters.contains("contract_id_str"))
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 'contract_id_str'");
			std::string contract_id_str = parameters["contract_id_str"].as<std::string>();
			if (!parameters.contains("event_type"))
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 'event_type'");
			std::string event_type = parameters["event_type"].as<std::string>();

			std::vector<std::string> result = get_client()->script_list_event_handler(contract_id_str, event_type);
			return fc::variant(result);
		}

		fc::variant CommonApiRpcServer::script_add_event_handler_positional(fc::rpc::json_connection* json_connection, const fc::variants& parameters)
		{
			// check all of this method's prerequisites
			verify_json_connection_is_authenticated(json_connection);
			verify_wallet_is_open();
			verify_wallet_is_unlocked();
			// done checking prerequisites

			if (parameters.size() <= 0)
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 1 (contract_id_str)");
			std::string contract_id_str = parameters[0].as<std::string>();
			if (parameters.size() <= 1)
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 2 (event_type)");
			std::string event_type = parameters[1].as<std::string>();
			if (parameters.size() <= 2)
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 3 (script_id)");
			std::string script_id = parameters[2].as<std::string>();
			if (parameters.size() <= 3)
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 4 (index)");
			uint32_t index = parameters[3].as<uint32_t>();

			get_client()->script_add_event_handler(contract_id_str, event_type, script_id, index);
			return fc::variant();
		}

		fc::variant CommonApiRpcServer::script_add_event_handler_named(fc::rpc::json_connection* json_connection, const fc::variant_object& parameters)
		{
			// check all of this method's prerequisites
			verify_json_connection_is_authenticated(json_connection);
			verify_wallet_is_open();
			verify_wallet_is_unlocked();
			// done checking prerequisites

			if (!parameters.contains("contract_id_str"))
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 'contract_id_str'");
			std::string contract_id_str = parameters["contract_id_str"].as<std::string>();
			if (!parameters.contains("event_type"))
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 'event_type'");
			std::string event_type = parameters["event_type"].as<std::string>();
			if (!parameters.contains("script_id"))
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 'script_id'");
			std::string script_id = parameters["script_id"].as<std::string>();
			if (!parameters.contains("index"))
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 'index'");
			uint32_t index = parameters["index"].as<uint32_t>();

			get_client()->script_add_event_handler(contract_id_str, event_type, script_id, index);
			return fc::variant();
		}

		fc::variant CommonApiRpcServer::script_delete_event_handler_positional(fc::rpc::json_connection* json_connection, const fc::variants& parameters)
		{
			// check all of this method's prerequisites
			verify_json_connection_is_authenticated(json_connection);
			verify_wallet_is_open();
			verify_wallet_is_unlocked();
			// done checking prerequisites

			if (parameters.size() <= 0)
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 1 (contract_id_str)");
			std::string contract_id_str = parameters[0].as<std::string>();
			if (parameters.size() <= 1)
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 2 (event_type)");
			std::string event_type = parameters[1].as<std::string>();
			if (parameters.size() <= 2)
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 3 (script_id)");
			std::string script_id = parameters[2].as<std::string>();

			get_client()->script_delete_event_handler(contract_id_str, event_type, script_id);
			return fc::variant();
		}

		fc::variant CommonApiRpcServer::script_delete_event_handler_named(fc::rpc::json_connection* json_connection, const fc::variant_object& parameters)
		{
			// check all of this method's prerequisites
			verify_json_connection_is_authenticated(json_connection);
			verify_wallet_is_open();
			verify_wallet_is_unlocked();
			// done checking prerequisites

			if (!parameters.contains("contract_id_str"))
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 'contract_id_str'");
			std::string contract_id_str = parameters["contract_id_str"].as<std::string>();
			if (!parameters.contains("event_type"))
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 'event_type'");
			std::string event_type = parameters["event_type"].as<std::string>();
			if (!parameters.contains("script_id"))
				FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 'script_id'");
			std::string script_id = parameters["script_id"].as<std::string>();

			get_client()->script_delete_event_handler(contract_id_str, event_type, script_id);
			return fc::variant();
		}

        fc::variant CommonApiRpcServer::proposal_apply_for_privilege_admin_positional(fc::rpc::json_connection* json_connection, const fc::variants& parameters)
        {
            // check all of this method's prerequisites
            verify_json_connection_is_authenticated(json_connection);
            verify_wallet_is_open();
            verify_wallet_is_unlocked();
            // done checking prerequisites

            if (parameters.size() <= 0)
                FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 1 (caller_name)");
            std::string caller_name = parameters[0].as<std::string>();
            if (parameters.size() <= 1)
                FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 2 (candidate_address)");
            std::string candidate_address = parameters[1].as<std::string>();
            if (parameters.size() <= 2)
                FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 3 (need_vote_count)");
            uint32_t need_vote_count = parameters[2].as<uint32_t>();
            if (parameters.size() <= 3)
                FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 4 (start_time)");
            uint32_t start_time = parameters[3].as<uint32_t>();
            if (parameters.size() <= 4)
                FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 5 (expected_end_time)");
            uint32_t expected_end_time = parameters[4].as<uint32_t>();

            cdcchain::consensus::ProposalIdType result = get_client()->proposal_apply_for_privilege_admin(caller_name, candidate_address, need_vote_count, start_time, expected_end_time);
            return fc::variant(result);
        }

        fc::variant CommonApiRpcServer::proposal_apply_for_privilege_admin_named(fc::rpc::json_connection* json_connection, const fc::variant_object& parameters)
        {
            // check all of this method's prerequisites
            verify_json_connection_is_authenticated(json_connection);
            verify_wallet_is_open();
            verify_wallet_is_unlocked();
            // done checking prerequisites

            if (!parameters.contains("caller_name"))
                FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 'caller_name'");
            std::string caller_name = parameters["caller_name"].as<std::string>();
            if (!parameters.contains("candidate_address"))
                FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 'candidate_address'");
            std::string candidate_address = parameters["candidate_address"].as<std::string>();
            if (!parameters.contains("need_vote_count"))
                FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 'need_vote_count'");
            uint32_t need_vote_count = parameters["need_vote_count"].as<uint32_t>();
            if (!parameters.contains("start_time"))
                FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 'start_time'");
            uint32_t start_time = parameters["start_time"].as<uint32_t>();
            if (!parameters.contains("expected_end_time"))
                FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 'expected_end_time'");
            uint32_t expected_end_time = parameters["expected_end_time"].as<uint32_t>();

            cdcchain::consensus::ProposalIdType result = get_client()->proposal_apply_for_privilege_admin(caller_name, candidate_address, need_vote_count, start_time, expected_end_time);
            return fc::variant(result);
        }

        fc::variant CommonApiRpcServer::proposal_revoke_privilege_admin_positional(fc::rpc::json_connection* json_connection, const fc::variants& parameters)
        {
            // check all of this method's prerequisites
            verify_json_connection_is_authenticated(json_connection);
            verify_wallet_is_open();
            verify_wallet_is_unlocked();
            // done checking prerequisites

            if (parameters.size() <= 0)
                FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 1 (caller_name)");
            std::string caller_name = parameters[0].as<std::string>();
            if (parameters.size() <= 1)
                FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 2 (privilege_admin)");
            std::string privilege_admin = parameters[1].as<std::string>();
            if (parameters.size() <= 2)
                FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 3 (need_vote_count)");
            uint32_t need_vote_count = parameters[2].as<uint32_t>();
            if (parameters.size() <= 3)
                FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 4 (start_time)");
            uint32_t start_time = parameters[3].as<uint32_t>();
            if (parameters.size() <= 4)
                FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 5 (expected_end_time)");
            uint32_t expected_end_time = parameters[4].as<uint32_t>();

            cdcchain::consensus::ProposalIdType result = get_client()->proposal_revoke_privilege_admin(caller_name, privilege_admin, need_vote_count, start_time, expected_end_time);
            return fc::variant(result);
        }

        fc::variant CommonApiRpcServer::proposal_revoke_privilege_admin_named(fc::rpc::json_connection* json_connection, const fc::variant_object& parameters)
        {
            // check all of this method's prerequisites
            verify_json_connection_is_authenticated(json_connection);
            verify_wallet_is_open();
            verify_wallet_is_unlocked();
            // done checking prerequisites

            if (!parameters.contains("caller_name"))
                FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 'caller_name'");
            std::string caller_name = parameters["caller_name"].as<std::string>();
            if (!parameters.contains("privilege_admin"))
                FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 'privilege_admin'");
            std::string privilege_admin = parameters["privilege_admin"].as<std::string>();
            if (!parameters.contains("need_vote_count"))
                FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 'need_vote_count'");
            uint32_t need_vote_count = parameters["need_vote_count"].as<uint32_t>();
            if (!parameters.contains("start_time"))
                FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 'start_time'");
            uint32_t start_time = parameters["start_time"].as<uint32_t>();
            if (!parameters.contains("expected_end_time"))
                FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 'expected_end_time'");
            uint32_t expected_end_time = parameters["expected_end_time"].as<uint32_t>();

            cdcchain::consensus::ProposalIdType result = get_client()->proposal_revoke_privilege_admin(caller_name, privilege_admin, need_vote_count, start_time, expected_end_time);
            return fc::variant(result);
        }

        fc::variant CommonApiRpcServer::proposal_approve_positional(fc::rpc::json_connection* json_connection, const fc::variants& parameters)
        {
            // check all of this method's prerequisites
            verify_json_connection_is_authenticated(json_connection);
            verify_wallet_is_open();
            verify_wallet_is_unlocked();
            // done checking prerequisites

            if (parameters.size() <= 0)
                FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 1 (caller_name)");
            std::string caller_name = parameters[0].as<std::string>();
            if (parameters.size() <= 1)
                FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 2 (proposal_id)");
            std::string proposal_id = parameters[1].as<std::string>();

            cdcchain::wallet::WalletTransactionEntry result = get_client()->proposal_approve(caller_name, proposal_id);
            return fc::variant(result);
        }

        fc::variant CommonApiRpcServer::proposal_approve_named(fc::rpc::json_connection* json_connection, const fc::variant_object& parameters)
        {
            // check all of this method's prerequisites
            verify_json_connection_is_authenticated(json_connection);
            verify_wallet_is_open();
            verify_wallet_is_unlocked();
            // done checking prerequisites

            if (!parameters.contains("caller_name"))
                FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 'caller_name'");
            std::string caller_name = parameters["caller_name"].as<std::string>();
            if (!parameters.contains("proposal_id"))
                FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 'proposal_id'");
            std::string proposal_id = parameters["proposal_id"].as<std::string>();

            cdcchain::wallet::WalletTransactionEntry result = get_client()->proposal_approve(caller_name, proposal_id);
            return fc::variant(result);
        }

        fc::variant CommonApiRpcServer::proposal_get_info_positional(fc::rpc::json_connection* json_connection, const fc::variants& parameters)
        {
            // this method has no prerequisites

            if (parameters.size() <= 0)
                FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 1 (proposal_id)");
            std::string proposal_id = parameters[0].as<std::string>();

            cdcchain::consensus::ProposalEntry result = get_client()->proposal_get_info(proposal_id);
            return fc::variant(result);
        }

        fc::variant CommonApiRpcServer::proposal_get_info_named(fc::rpc::json_connection* json_connection, const fc::variant_object& parameters)
        {
            // this method has no prerequisites

            if (!parameters.contains("proposal_id"))
                FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 'proposal_id'");
            std::string proposal_id = parameters["proposal_id"].as<std::string>();

            cdcchain::consensus::ProposalEntry result = get_client()->proposal_get_info(proposal_id);
            return fc::variant(result);
        }

        fc::variant CommonApiRpcServer::appoint_general_admin_positional(fc::rpc::json_connection* json_connection, const fc::variants& parameters)
        {
            // check all of this method's prerequisites
            verify_json_connection_is_authenticated(json_connection);
            verify_wallet_is_open();
            verify_wallet_is_unlocked();
            // done checking prerequisites

            if (parameters.size() <= 0)
                FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 1 (caller_name)");
            std::string caller_name = parameters[0].as<std::string>();
            if (parameters.size() <= 1)
                FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 2 (candidate_address)");
            std::string candidate_address = parameters[1].as<std::string>();

            cdcchain::wallet::WalletTransactionEntry result = get_client()->appoint_general_admin(caller_name, candidate_address);
            return fc::variant(result);
        }

        fc::variant CommonApiRpcServer::appoint_general_admin_named(fc::rpc::json_connection* json_connection, const fc::variant_object& parameters)
        {
            // check all of this method's prerequisites
            verify_json_connection_is_authenticated(json_connection);
            verify_wallet_is_open();
            verify_wallet_is_unlocked();
            // done checking prerequisites

            if (!parameters.contains("caller_name"))
                FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 'caller_name'");
            std::string caller_name = parameters["caller_name"].as<std::string>();
            if (!parameters.contains("candidate_address"))
                FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 'candidate_address'");
            std::string candidate_address = parameters["candidate_address"].as<std::string>();

            cdcchain::wallet::WalletTransactionEntry result = get_client()->appoint_general_admin(caller_name, candidate_address);
            return fc::variant(result);
        }

        fc::variant CommonApiRpcServer::revoke_general_admin_positional(fc::rpc::json_connection* json_connection, const fc::variants& parameters)
        {
            // check all of this method's prerequisites
            verify_json_connection_is_authenticated(json_connection);
            verify_wallet_is_open();
            verify_wallet_is_unlocked();
            // done checking prerequisites

            if (parameters.size() <= 0)
                FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 1 (caller_name)");
            std::string caller_name = parameters[0].as<std::string>();
            if (parameters.size() <= 1)
                FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 2 (general_admin_address)");
            std::string general_admin_address = parameters[1].as<std::string>();

            cdcchain::wallet::WalletTransactionEntry result = get_client()->revoke_general_admin(caller_name, general_admin_address);
            return fc::variant(result);
        }

        fc::variant CommonApiRpcServer::revoke_general_admin_named(fc::rpc::json_connection* json_connection, const fc::variant_object& parameters)
        {
            // check all of this method's prerequisites
            verify_json_connection_is_authenticated(json_connection);
            verify_wallet_is_open();
            verify_wallet_is_unlocked();
            // done checking prerequisites

            if (!parameters.contains("caller_name"))
                FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 'caller_name'");
            std::string caller_name = parameters["caller_name"].as<std::string>();
            if (!parameters.contains("general_admin_address"))
                FC_THROW_EXCEPTION(fc::invalid_arg_exception, "missing required parameter 'general_admin_address'");
            std::string general_admin_address = parameters["general_admin_address"].as<std::string>();

            cdcchain::wallet::WalletTransactionEntry result = get_client()->revoke_general_admin(caller_name, general_admin_address);
            return fc::variant(result);
        }

        fc::variant CommonApiRpcServer::get_all_privilege_admin_positional(fc::rpc::json_connection* json_connection, const fc::variants& parameters)
        {
            // this method has no prerequisites


            std::vector<cdcchain::consensus::Address> result = get_client()->get_all_privilege_admin();
            return fc::variant(result);
        }

        fc::variant CommonApiRpcServer::get_all_privilege_admin_named(fc::rpc::json_connection* json_connection, const fc::variant_object& parameters)
        {
            // this method has no prerequisites


            std::vector<cdcchain::consensus::Address> result = get_client()->get_all_privilege_admin();
            return fc::variant(result);
        }

        fc::variant CommonApiRpcServer::get_all_general_admin_positional(fc::rpc::json_connection* json_connection, const fc::variants& parameters)
        {
            // this method has no prerequisites


            std::vector<cdcchain::consensus::Address> result = get_client()->get_all_general_admin();
            return fc::variant(result);
        }

        fc::variant CommonApiRpcServer::get_all_general_admin_named(fc::rpc::json_connection* json_connection, const fc::variant_object& parameters)
        {
            // this method has no prerequisites


            std::vector<cdcchain::consensus::Address> result = get_client()->get_all_general_admin();
            return fc::variant(result);
        }

		void CommonApiRpcServer::register_common_api_methods(const fc::rpc::json_connection_ptr& json_connection)
		{
			fc::rpc::json_connection::method bound_positional_method;
			fc::rpc::json_connection::named_param_method bound_named_method;
			auto capture_con = json_connection.get();
			// register method blockchain_get_info
			bound_positional_method = boost::bind(&CommonApiRpcServer::blockchain_get_info_positional,
				this, capture_con, _1);
			json_connection->add_method("blockchain_get_info", bound_positional_method);
			json_connection->add_method("getconfig", bound_positional_method);
			json_connection->add_method("get_config", bound_positional_method);
			json_connection->add_method("config", bound_positional_method);
			json_connection->add_method("blockchain_get_config", bound_positional_method);
			bound_named_method = boost::bind(&CommonApiRpcServer::blockchain_get_info_named,
				this, capture_con, _1);
			json_connection->add_named_param_method("blockchain_get_info", bound_named_method);
			json_connection->add_named_param_method("getconfig", bound_named_method);
            json_connection->add_named_param_method("get_config", bound_named_method);
            json_connection->add_named_param_method("config", bound_named_method);
            json_connection->add_named_param_method("blockchain_get_config", bound_named_method);

           // register method blockchain_generate_snapshot
			bound_positional_method = boost::bind(&CommonApiRpcServer::blockchain_generate_snapshot_positional,
				this, capture_con, _1);
			json_connection->add_method("blockchain_generate_snapshot", bound_positional_method);
			bound_named_method = boost::bind(&CommonApiRpcServer::blockchain_generate_snapshot_named,
				this, capture_con, _1);
			json_connection->add_named_param_method("blockchain_generate_snapshot", bound_named_method);

			// register method blockchain_get_cdc_account_balance_entry
			bound_positional_method = boost::bind(&CommonApiRpcServer::blockchain_get_cdc_account_balance_entry_positional,
				this, capture_con, _1);
			json_connection->add_method("blockchain_get_cdc_account_balance_entry", bound_positional_method);
            bound_named_method = boost::bind(&CommonApiRpcServer::blockchain_get_cdc_account_balance_entry_named, 
                this, capture_con, _1);
            json_connection->add_named_param_method("blockchain_get_cdc_account_balance_entry", bound_named_method);

           // register method blockchain_generate_issuance_map
			bound_positional_method = boost::bind(&CommonApiRpcServer::blockchain_generate_issuance_map_positional,
				this, capture_con, _1);
			json_connection->add_method("blockchain_generate_issuance_map", bound_positional_method);
			bound_named_method = boost::bind(&CommonApiRpcServer::blockchain_generate_issuance_map_named,
				this, capture_con, _1);
			json_connection->add_named_param_method("blockchain_generate_issuance_map", bound_named_method);

			// register method blockchain_calculate_supply
			bound_positional_method = boost::bind(&CommonApiRpcServer::blockchain_calculate_supply_positional,
				this, capture_con, _1);
			json_connection->add_method("blockchain_calculate_supply", bound_positional_method);
			json_connection->add_method("supply", bound_positional_method);
			json_connection->add_method("calculate_supply", bound_positional_method);
			bound_named_method = boost::bind(&CommonApiRpcServer::blockchain_calculate_supply_named,
				this, capture_con, _1);
			json_connection->add_named_param_method("blockchain_calculate_supply", bound_named_method);
			json_connection->add_named_param_method("supply", bound_named_method);
			json_connection->add_named_param_method("calculate_supply", bound_named_method);

			// register method blockchain_is_synced
			bound_positional_method = boost::bind(&CommonApiRpcServer::blockchain_is_synced_positional,
				this, capture_con, _1);
			json_connection->add_method("blockchain_is_synced", bound_positional_method);
			json_connection->add_method("synced", bound_positional_method);
			bound_named_method = boost::bind(&CommonApiRpcServer::blockchain_is_synced_named,
				this, capture_con, _1);
			json_connection->add_named_param_method("blockchain_is_synced", bound_named_method);
			json_connection->add_named_param_method("synced", bound_named_method);

			// register method blockchain_get_block_count
			bound_positional_method = boost::bind(&CommonApiRpcServer::blockchain_get_block_count_positional,
				this, capture_con, _1);
			json_connection->add_method("blockchain_get_block_count", bound_positional_method);
			json_connection->add_method("blockchain_get_blockcount", bound_positional_method);
			json_connection->add_method("getblockcount", bound_positional_method);
			bound_named_method = boost::bind(&CommonApiRpcServer::blockchain_get_block_count_named,
				this, capture_con, _1);
			json_connection->add_named_param_method("blockchain_get_block_count", bound_named_method);
			json_connection->add_named_param_method("blockchain_get_blockcount", bound_named_method);
			json_connection->add_named_param_method("getblockcount", bound_named_method);

			// register method blockchain_get_security_state
			bound_positional_method = boost::bind(&CommonApiRpcServer::blockchain_get_security_state_positional,
				this, capture_con, _1);
			json_connection->add_method("blockchain_get_security_state", bound_positional_method);
			json_connection->add_method("alert_state", bound_positional_method);
			json_connection->add_method("security_state", bound_positional_method);
			bound_named_method = boost::bind(&CommonApiRpcServer::blockchain_get_security_state_named,
				this, capture_con, _1);
			json_connection->add_named_param_method("blockchain_get_security_state", bound_named_method);
			json_connection->add_named_param_method("alert_state", bound_named_method);
			json_connection->add_named_param_method("security_state", bound_named_method);

			// register method blockchain_list_accounts
			bound_positional_method = boost::bind(&CommonApiRpcServer::blockchain_list_accounts_positional,
				this, capture_con, _1);
			json_connection->add_method("blockchain_list_accounts", bound_positional_method);
			bound_named_method = boost::bind(&CommonApiRpcServer::blockchain_list_accounts_named,
				this, capture_con, _1);
			json_connection->add_named_param_method("blockchain_list_accounts", bound_named_method);

			// register method blockchain_list_recently_updated_accounts
			bound_positional_method = boost::bind(&CommonApiRpcServer::blockchain_list_recently_updated_accounts_positional,
				this, capture_con, _1);
			json_connection->add_method("blockchain_list_recently_updated_accounts", bound_positional_method);
			bound_named_method = boost::bind(&CommonApiRpcServer::blockchain_list_recently_updated_accounts_named,
				this, capture_con, _1);
			json_connection->add_named_param_method("blockchain_list_recently_updated_accounts", bound_named_method);

			// register method blockchain_list_recently_registered_accounts
			bound_positional_method = boost::bind(&CommonApiRpcServer::blockchain_list_recently_registered_accounts_positional,
				this, capture_con, _1);
			json_connection->add_method("blockchain_list_recently_registered_accounts", bound_positional_method);
			bound_named_method = boost::bind(&CommonApiRpcServer::blockchain_list_recently_registered_accounts_named,
				this, capture_con, _1);
			json_connection->add_named_param_method("blockchain_list_recently_registered_accounts", bound_named_method);

			// register method blockchain_list_assets
			bound_positional_method = boost::bind(&CommonApiRpcServer::blockchain_list_assets_positional,
				this, capture_con, _1);
			json_connection->add_method("blockchain_list_assets", bound_positional_method);
			bound_named_method = boost::bind(&CommonApiRpcServer::blockchain_list_assets_named,
				this, capture_con, _1);
			json_connection->add_named_param_method("blockchain_list_assets", bound_named_method);

			// register method blockchain_list_pending_transactions
			bound_positional_method = boost::bind(&CommonApiRpcServer::blockchain_list_pending_transactions_positional,
				this, capture_con, _1);
			json_connection->add_method("blockchain_list_pending_transactions", bound_positional_method);
			json_connection->add_method("blockchain_get_pending_transactions", bound_positional_method);
			json_connection->add_method("list_pending", bound_positional_method);
			bound_named_method = boost::bind(&CommonApiRpcServer::blockchain_list_pending_transactions_named,
				this, capture_con, _1);
			json_connection->add_named_param_method("blockchain_list_pending_transactions", bound_named_method);
			json_connection->add_named_param_method("blockchain_get_pending_transactions", bound_named_method);
			json_connection->add_named_param_method("list_pending", bound_named_method);

			// register method blockchain_get_transaction
			bound_positional_method = boost::bind(&CommonApiRpcServer::blockchain_get_transaction_positional,
				this, capture_con, _1);
			json_connection->add_method("blockchain_get_transaction", bound_positional_method);
			bound_named_method = boost::bind(&CommonApiRpcServer::blockchain_get_transaction_named,
				this, capture_con, _1);
			json_connection->add_named_param_method("blockchain_get_transaction", bound_named_method);

			// register method blockchain_get_pretty_transaction
			bound_positional_method = boost::bind(&CommonApiRpcServer::blockchain_get_pretty_transaction_positional,
				this, capture_con, _1);
			json_connection->add_method("blockchain_get_pretty_transaction", bound_positional_method);
			bound_named_method = boost::bind(&CommonApiRpcServer::blockchain_get_pretty_transaction_named,
				this, capture_con, _1);
			json_connection->add_named_param_method("blockchain_get_pretty_transaction", bound_named_method);

			// register method blockchain_get_pretty_contract_transaction
			bound_positional_method = boost::bind(&CommonApiRpcServer::blockchain_get_pretty_contract_transaction_positional,
				this, capture_con, _1);
			json_connection->add_method("blockchain_get_pretty_contract_transaction", bound_positional_method);
			bound_named_method = boost::bind(&CommonApiRpcServer::blockchain_get_pretty_contract_transaction_named,
				this, capture_con, _1);
			json_connection->add_named_param_method("blockchain_get_pretty_contract_transaction", bound_named_method);

			// register method blockchain_get_block
			bound_positional_method = boost::bind(&CommonApiRpcServer::blockchain_get_block_positional,
				this, capture_con, _1);
			json_connection->add_method("blockchain_get_block", bound_positional_method);
			json_connection->add_method("get_block", bound_positional_method);
			json_connection->add_method("getblock", bound_positional_method);
			json_connection->add_method("blockchain_get_block_hash", bound_positional_method);
			json_connection->add_method("blockchain_get_blockhash", bound_positional_method);
			json_connection->add_method("getblockhash", bound_positional_method);
			bound_named_method = boost::bind(&CommonApiRpcServer::blockchain_get_block_named,
				this, capture_con, _1);
			json_connection->add_named_param_method("blockchain_get_block", bound_named_method);
			json_connection->add_named_param_method("get_block", bound_named_method);
			json_connection->add_named_param_method("getblock", bound_named_method);
			json_connection->add_named_param_method("blockchain_get_block_hash", bound_named_method);
			json_connection->add_named_param_method("blockchain_get_blockhash", bound_named_method);
			json_connection->add_named_param_method("getblockhash", bound_named_method);

			// register method blockchain_get_block_transactions
			bound_positional_method = boost::bind(&CommonApiRpcServer::blockchain_get_block_transactions_positional,
				this, capture_con, _1);
			json_connection->add_method("blockchain_get_block_transactions", bound_positional_method);
			bound_named_method = boost::bind(&CommonApiRpcServer::blockchain_get_block_transactions_named,
				this, capture_con, _1);
			json_connection->add_named_param_method("blockchain_get_block_transactions", bound_named_method);

			// register method blockchain_get_account
			bound_positional_method = boost::bind(&CommonApiRpcServer::blockchain_get_account_positional,
				this, capture_con, _1);
			json_connection->add_method("blockchain_get_account", bound_positional_method);
			json_connection->add_method("get_account", bound_positional_method);
			bound_named_method = boost::bind(&CommonApiRpcServer::blockchain_get_account_named,
				this, capture_con, _1);
			json_connection->add_named_param_method("blockchain_get_account", bound_named_method);
			json_connection->add_named_param_method("get_account", bound_named_method);

			// register method blockchain_get_slate
			bound_positional_method = boost::bind(&CommonApiRpcServer::blockchain_get_slate_positional,
				this, capture_con, _1);
			json_connection->add_method("blockchain_get_slate", bound_positional_method);
			json_connection->add_method("get_slate", bound_positional_method);
			bound_named_method = boost::bind(&CommonApiRpcServer::blockchain_get_slate_named,
				this, capture_con, _1);
			json_connection->add_named_param_method("blockchain_get_slate", bound_named_method);
			json_connection->add_named_param_method("get_slate", bound_named_method);

			// register method blockchain_get_balance
			bound_positional_method = boost::bind(&CommonApiRpcServer::blockchain_get_balance_positional,
				this, capture_con, _1);
			json_connection->add_method("blockchain_get_balance", bound_positional_method);
			json_connection->add_method("get_balance", bound_positional_method);
			bound_named_method = boost::bind(&CommonApiRpcServer::blockchain_get_balance_named,
				this, capture_con, _1);
			json_connection->add_named_param_method("blockchain_get_balance", bound_named_method);
			json_connection->add_named_param_method("get_balance", bound_named_method);

			// register method blockchain_list_balances
			bound_positional_method = boost::bind(&CommonApiRpcServer::blockchain_list_balances_positional,
				this, capture_con, _1);
			json_connection->add_method("blockchain_list_balances", bound_positional_method);
			json_connection->add_method("list_balances", bound_positional_method);
			bound_named_method = boost::bind(&CommonApiRpcServer::blockchain_list_balances_named,
				this, capture_con, _1);
			json_connection->add_named_param_method("blockchain_list_balances", bound_named_method);
			json_connection->add_named_param_method("list_balances", bound_named_method);

			// register method blockchain_list_address_balances
			bound_positional_method = boost::bind(&CommonApiRpcServer::blockchain_list_address_balances_positional,
				this, capture_con, _1);
			json_connection->add_method("blockchain_list_address_balances", bound_positional_method);
			json_connection->add_method("list_address_balances", bound_positional_method);
			bound_named_method = boost::bind(&CommonApiRpcServer::blockchain_list_address_balances_named,
				this, capture_con, _1);
			json_connection->add_named_param_method("blockchain_list_address_balances", bound_named_method);
			json_connection->add_named_param_method("list_address_balances", bound_named_method);

			// register method blockchain_list_address_transactions
			bound_positional_method = boost::bind(&CommonApiRpcServer::blockchain_list_address_transactions_positional,
				this, capture_con, _1);
			json_connection->add_method("blockchain_list_address_transactions", bound_positional_method);
			json_connection->add_method("list_address_transactions", bound_positional_method);
			bound_named_method = boost::bind(&CommonApiRpcServer::blockchain_list_address_transactions_named,
				this, capture_con, _1);
			json_connection->add_named_param_method("blockchain_list_address_transactions", bound_named_method);
			json_connection->add_named_param_method("list_address_transactions", bound_named_method);

			// register method blockchain_get_account_public_balance
			bound_positional_method = boost::bind(&CommonApiRpcServer::blockchain_get_account_public_balance_positional,
				this, capture_con, _1);
			json_connection->add_method("blockchain_get_account_public_balance", bound_positional_method);
			bound_named_method = boost::bind(&CommonApiRpcServer::blockchain_get_account_public_balance_named,
				this, capture_con, _1);
			json_connection->add_named_param_method("blockchain_get_account_public_balance", bound_named_method);

			// register method blockchain_list_key_balances
			bound_positional_method = boost::bind(&CommonApiRpcServer::blockchain_list_key_balances_positional,
				this, capture_con, _1);
			json_connection->add_method("blockchain_list_key_balances", bound_positional_method);
			json_connection->add_method("list_key_balances", bound_positional_method);
			bound_named_method = boost::bind(&CommonApiRpcServer::blockchain_list_key_balances_named,
				this, capture_con, _1);
			json_connection->add_named_param_method("blockchain_list_key_balances", bound_named_method);
			json_connection->add_named_param_method("list_key_balances", bound_named_method);

			// register method blockchain_get_asset
			bound_positional_method = boost::bind(&CommonApiRpcServer::blockchain_get_asset_positional,
				this, capture_con, _1);
			json_connection->add_method("blockchain_get_asset", bound_positional_method);
			json_connection->add_method("get_asset", bound_positional_method);
			bound_named_method = boost::bind(&CommonApiRpcServer::blockchain_get_asset_named,
				this, capture_con, _1);
			json_connection->add_named_param_method("blockchain_get_asset", bound_named_method);
			json_connection->add_named_param_method("get_asset", bound_named_method);

			// register method blockchain_list_active_delegates
			bound_positional_method = boost::bind(&CommonApiRpcServer::blockchain_list_active_delegates_positional,
				this, capture_con, _1);
			json_connection->add_method("blockchain_list_active_delegates", bound_positional_method);
			json_connection->add_method("blockchain_get_active_delegates", bound_positional_method);
			bound_named_method = boost::bind(&CommonApiRpcServer::blockchain_list_active_delegates_named,
				this, capture_con, _1);
			json_connection->add_named_param_method("blockchain_list_active_delegates", bound_named_method);
			json_connection->add_named_param_method("blockchain_get_active_delegates", bound_named_method);

			// register method blockchain_list_delegates
			bound_positional_method = boost::bind(&CommonApiRpcServer::blockchain_list_delegates_positional,
				this, capture_con, _1);
			json_connection->add_method("blockchain_list_delegates", bound_positional_method);
			json_connection->add_method("blockchain_get_delegates", bound_positional_method);
			bound_named_method = boost::bind(&CommonApiRpcServer::blockchain_list_delegates_named,
				this, capture_con, _1);
			json_connection->add_named_param_method("blockchain_list_delegates", bound_named_method);
			json_connection->add_named_param_method("blockchain_get_delegates", bound_named_method);

			// register method blockchain_list_blocks
			bound_positional_method = boost::bind(&CommonApiRpcServer::blockchain_list_blocks_positional,
				this, capture_con, _1);
			json_connection->add_method("blockchain_list_blocks", bound_positional_method);
			json_connection->add_method("list_blocks", bound_positional_method);
			bound_named_method = boost::bind(&CommonApiRpcServer::blockchain_list_blocks_named,
				this, capture_con, _1);
			json_connection->add_named_param_method("blockchain_list_blocks", bound_named_method);
			json_connection->add_named_param_method("list_blocks", bound_named_method);

			// register method blockchain_list_missing_block_delegates
			bound_positional_method = boost::bind(&CommonApiRpcServer::blockchain_list_missing_block_delegates_positional,
				this, capture_con, _1);
			json_connection->add_method("blockchain_list_missing_block_delegates", bound_positional_method);
			bound_named_method = boost::bind(&CommonApiRpcServer::blockchain_list_missing_block_delegates_named,
				this, capture_con, _1);
			json_connection->add_named_param_method("blockchain_list_missing_block_delegates", bound_named_method);

			// register method blockchain_export_fork_graph
			bound_positional_method = boost::bind(&CommonApiRpcServer::blockchain_export_fork_graph_positional,
				this, capture_con, _1);
			json_connection->add_method("blockchain_export_fork_graph", bound_positional_method);
			json_connection->add_method("export_forks", bound_positional_method);
			bound_named_method = boost::bind(&CommonApiRpcServer::blockchain_export_fork_graph_named,
				this, capture_con, _1);
			json_connection->add_named_param_method("blockchain_export_fork_graph", bound_named_method);
			json_connection->add_named_param_method("export_forks", bound_named_method);

			// register method blockchain_list_forks
			bound_positional_method = boost::bind(&CommonApiRpcServer::blockchain_list_forks_positional,
				this, capture_con, _1);
			json_connection->add_method("blockchain_list_forks", bound_positional_method);
			json_connection->add_method("list_forks", bound_positional_method);
			bound_named_method = boost::bind(&CommonApiRpcServer::blockchain_list_forks_named,
				this, capture_con, _1);
			json_connection->add_named_param_method("blockchain_list_forks", bound_named_method);
			json_connection->add_named_param_method("list_forks", bound_named_method);

			// register method blockchain_get_delegate_slot_entrys
			bound_positional_method = boost::bind(&CommonApiRpcServer::blockchain_get_delegate_slot_entrys_positional,
				this, capture_con, _1);
			json_connection->add_method("blockchain_get_delegate_slot_entrys", bound_positional_method);
			json_connection->add_method("get_slot", bound_positional_method);
			bound_named_method = boost::bind(&CommonApiRpcServer::blockchain_get_delegate_slot_entrys_named,
				this, capture_con, _1);
			json_connection->add_named_param_method("blockchain_get_delegate_slot_entrys", bound_named_method);
			json_connection->add_named_param_method("get_slot", bound_named_method);

			// register method blockchain_get_block_signee
			bound_positional_method = boost::bind(&CommonApiRpcServer::blockchain_get_block_signee_positional,
				this, capture_con, _1);
			json_connection->add_method("blockchain_get_block_signee", bound_positional_method);
			bound_named_method = boost::bind(&CommonApiRpcServer::blockchain_get_block_signee_named,
				this, capture_con, _1);
			json_connection->add_named_param_method("blockchain_get_block_signee", bound_named_method);

			// register method blockchain_unclaimed_genesis
			bound_positional_method = boost::bind(&CommonApiRpcServer::blockchain_unclaimed_genesis_positional,
				this, capture_con, _1);
			json_connection->add_method("blockchain_unclaimed_genesis", bound_positional_method);
			bound_named_method = boost::bind(&CommonApiRpcServer::blockchain_unclaimed_genesis_named,
				this, capture_con, _1);
			json_connection->add_named_param_method("blockchain_unclaimed_genesis", bound_named_method);

			// register method blockchain_verify_signature
			bound_positional_method = boost::bind(&CommonApiRpcServer::blockchain_verify_signature_positional,
				this, capture_con, _1);
			json_connection->add_method("blockchain_verify_signature", bound_positional_method);
			json_connection->add_method("verify_signature", bound_positional_method);
			json_connection->add_method("verify_sig", bound_positional_method);
			json_connection->add_method("blockchain_verify_sig", bound_positional_method);
			bound_named_method = boost::bind(&CommonApiRpcServer::blockchain_verify_signature_named,
				this, capture_con, _1);
			json_connection->add_named_param_method("blockchain_verify_signature", bound_named_method);
			json_connection->add_named_param_method("verify_signature", bound_named_method);
			json_connection->add_named_param_method("verify_sig", bound_named_method);
			json_connection->add_named_param_method("blockchain_verify_sig", bound_named_method);

			// register method blockchain_dump_state
			bound_positional_method = boost::bind(&CommonApiRpcServer::blockchain_dump_state_positional,
				this, capture_con, _1);
			json_connection->add_method("blockchain_dump_state", bound_positional_method);
			bound_named_method = boost::bind(&CommonApiRpcServer::blockchain_dump_state_named,
				this, capture_con, _1);
			json_connection->add_named_param_method("blockchain_dump_state", bound_named_method);

			// register method blockchain_broadcast_transaction
			bound_positional_method = boost::bind(&CommonApiRpcServer::blockchain_broadcast_transaction_positional,
				this, capture_con, _1);
			json_connection->add_method("blockchain_broadcast_transaction", bound_positional_method);
			bound_named_method = boost::bind(&CommonApiRpcServer::blockchain_broadcast_transaction_named,
				this, capture_con, _1);
			json_connection->add_named_param_method("blockchain_broadcast_transaction", bound_named_method);

			// register method blockchain_btc_address_convert
			bound_positional_method = boost::bind(&CommonApiRpcServer::blockchain_btc_address_convert_positional,
				this, capture_con, _1);
			json_connection->add_method("blockchain_btc_address_convert", bound_positional_method);
			bound_named_method = boost::bind(&CommonApiRpcServer::blockchain_btc_address_convert_named,
				this, capture_con, _1);
			json_connection->add_named_param_method("blockchain_btc_address_convert", bound_named_method);

			// register method blockchain_get_transaction_rpc
			bound_positional_method = boost::bind(&CommonApiRpcServer::blockchain_get_transaction_rpc_positional,
				this, capture_con, _1);
			json_connection->add_method("blockchain_get_transaction_rpc", bound_positional_method);
			bound_named_method = boost::bind(&CommonApiRpcServer::blockchain_get_transaction_rpc_named,
				this, capture_con, _1);
			json_connection->add_named_param_method("blockchain_get_transaction_rpc", bound_named_method);

			// register method blockchain_set_node_vm_enabled
			bound_positional_method = boost::bind(&CommonApiRpcServer::blockchain_set_node_vm_enabled_positional,
				this, capture_con, _1);
			json_connection->add_method("blockchain_set_node_vm_enabled", bound_positional_method);
			bound_named_method = boost::bind(&CommonApiRpcServer::blockchain_set_node_vm_enabled_named,
				this, capture_con, _1);
			json_connection->add_named_param_method("blockchain_set_node_vm_enabled", bound_named_method);

			// register method blockchain_get_node_vm_enabled
			bound_positional_method = boost::bind(&CommonApiRpcServer::blockchain_get_node_vm_enabled_positional,
				this, capture_con, _1);
			json_connection->add_method("blockchain_get_node_vm_enabled", bound_positional_method);
			bound_named_method = boost::bind(&CommonApiRpcServer::blockchain_get_node_vm_enabled_named,
				this, capture_con, _1);
			json_connection->add_named_param_method("blockchain_get_node_vm_enabled", bound_named_method);

			// register method blockchain_get_all_contracts
			bound_positional_method = boost::bind(&CommonApiRpcServer::blockchain_get_all_contracts_positional,
				this, capture_con, _1);
			json_connection->add_method("blockchain_get_all_contracts", bound_positional_method);
            bound_named_method = boost::bind(&CommonApiRpcServer::blockchain_get_all_contracts_named, 
                this, capture_con, _1);
            json_connection->add_named_param_method("blockchain_get_all_contracts", bound_named_method);

           // register method blockchain_get_forever_contracts
            bound_positional_method = boost::bind(&CommonApiRpcServer::blockchain_get_forever_contracts_positional,
                this, capture_con, _1);
            json_connection->add_method("blockchain_get_forever_contracts", bound_positional_method);
            bound_named_method = boost::bind(&CommonApiRpcServer::blockchain_get_forever_contracts_named, 
                this, capture_con, _1);
            json_connection->add_named_param_method("blockchain_get_forever_contracts", bound_named_method);

           // register method blockchain_list_pub_all_address
            bound_positional_method = boost::bind(&CommonApiRpcServer::blockchain_list_pub_all_address_positional,
                this, capture_con, _1);
            json_connection->add_method("blockchain_list_pub_all_address", bound_positional_method);
            bound_named_method = boost::bind(&CommonApiRpcServer::blockchain_list_pub_all_address_named, 
                this, capture_con, _1);
            json_connection->add_named_param_method("blockchain_list_pub_all_address", bound_named_method);

           // register method blockchain_list_contract_transaction_history
            bound_positional_method = boost::bind(&CommonApiRpcServer::blockchain_list_contract_transaction_history_positional,
                this, capture_con, _1);
            json_connection->add_method("blockchain_list_contract_transaction_history", bound_positional_method);
			json_connection->add_method("", bound_positional_method);
			bound_named_method = boost::bind(&CommonApiRpcServer::blockchain_list_contract_transaction_history_named,
				this, capture_con, _1);
			json_connection->add_named_param_method("blockchain_list_contract_transaction_history", bound_named_method);
			json_connection->add_named_param_method("", bound_named_method);

			// register method network_add_node
			bound_positional_method = boost::bind(&CommonApiRpcServer::network_add_node_positional,
				this, capture_con, _1);
			json_connection->add_method("network_add_node", bound_positional_method);
			json_connection->add_method("addnode", bound_positional_method);
			bound_named_method = boost::bind(&CommonApiRpcServer::network_add_node_named,
				this, capture_con, _1);
			json_connection->add_named_param_method("network_add_node", bound_named_method);
			json_connection->add_named_param_method("addnode", bound_named_method);

			// register method network_get_connection_count
			bound_positional_method = boost::bind(&CommonApiRpcServer::network_get_connection_count_positional,
				this, capture_con, _1);
			json_connection->add_method("network_get_connection_count", bound_positional_method);
			json_connection->add_method("getconnectioncount", bound_positional_method);
			bound_named_method = boost::bind(&CommonApiRpcServer::network_get_connection_count_named,
				this, capture_con, _1);
			json_connection->add_named_param_method("network_get_connection_count", bound_named_method);
			json_connection->add_named_param_method("getconnectioncount", bound_named_method);

			// register method network_get_peer_info
			bound_positional_method = boost::bind(&CommonApiRpcServer::network_get_peer_info_positional,
				this, capture_con, _1);
			json_connection->add_method("network_get_peer_info", bound_positional_method);
			bound_named_method = boost::bind(&CommonApiRpcServer::network_get_peer_info_named,
				this, capture_con, _1);
			json_connection->add_named_param_method("network_get_peer_info", bound_named_method);

			// register method network_broadcast_transaction
			bound_positional_method = boost::bind(&CommonApiRpcServer::network_broadcast_transaction_positional,
				this, capture_con, _1);
			json_connection->add_method("network_broadcast_transaction", bound_positional_method);
			bound_named_method = boost::bind(&CommonApiRpcServer::network_broadcast_transaction_named,
				this, capture_con, _1);
			json_connection->add_named_param_method("network_broadcast_transaction", bound_named_method);

            // register method wallet_transfer_to_address_build
            bound_positional_method = boost::bind(&CommonApiRpcServer::wallet_transfer_to_address_build_positional,
                this, capture_con, _1);
            json_connection->add_method("wallet_transfer_to_address_build", bound_positional_method);
            bound_named_method = boost::bind(&CommonApiRpcServer::wallet_transfer_to_address_build_named,
                this, capture_con, _1);
            json_connection->add_named_param_method("wallet_transfer_to_address_build", bound_named_method);

            // register method wallet_transfer_to_contract_build
            bound_positional_method = boost::bind(&CommonApiRpcServer::wallet_transfer_to_contract_build_positional,
                this, capture_con, _1);
            json_connection->add_method("wallet_transfer_to_contract_build", bound_positional_method);
            bound_named_method = boost::bind(&CommonApiRpcServer::wallet_transfer_to_contract_build_named,
                this, capture_con, _1);
            json_connection->add_named_param_method("wallet_transfer_to_contract_build", bound_named_method);

            // register method wallet_call_contract_build
            bound_positional_method = boost::bind(&CommonApiRpcServer::wallet_call_contract_build_positional,
                this, capture_con, _1);
            json_connection->add_method("wallet_call_contract_build", bound_positional_method);
            bound_named_method = boost::bind(&CommonApiRpcServer::wallet_call_contract_build_named,
                this, capture_con, _1);
            json_connection->add_named_param_method("wallet_call_contract_build", bound_named_method);

            // register method sign_build_transaction
            bound_positional_method = boost::bind(&CommonApiRpcServer::sign_build_transaction_positional,
                this, capture_con, _1);
            json_connection->add_method("sign_build_transaction", bound_positional_method);
            bound_named_method = boost::bind(&CommonApiRpcServer::sign_build_transaction_named,
                this, capture_con, _1);
            json_connection->add_named_param_method("sign_build_transaction", bound_named_method);

            // register method broadcast_building_transaction
            bound_positional_method = boost::bind(&CommonApiRpcServer::broadcast_building_transaction_positional,
                this, capture_con, _1);
            json_connection->add_method("broadcast_building_transaction", bound_positional_method);
            bound_named_method = boost::bind(&CommonApiRpcServer::broadcast_building_transaction_named,
                this, capture_con, _1);
            json_connection->add_named_param_method("broadcast_building_transaction", bound_named_method);


			// register method network_set_advanced_node_parameters
			bound_positional_method = boost::bind(&CommonApiRpcServer::network_set_advanced_node_parameters_positional,
				this, capture_con, _1);
			json_connection->add_method("network_set_advanced_node_parameters", bound_positional_method);
			bound_named_method = boost::bind(&CommonApiRpcServer::network_set_advanced_node_parameters_named,
				this, capture_con, _1);
			json_connection->add_named_param_method("network_set_advanced_node_parameters", bound_named_method);

			// register method network_get_advanced_node_parameters
			bound_positional_method = boost::bind(&CommonApiRpcServer::network_get_advanced_node_parameters_positional,
				this, capture_con, _1);
			json_connection->add_method("network_get_advanced_node_parameters", bound_positional_method);
			bound_named_method = boost::bind(&CommonApiRpcServer::network_get_advanced_node_parameters_named,
				this, capture_con, _1);
			json_connection->add_named_param_method("network_get_advanced_node_parameters", bound_named_method);

			// register method network_get_transaction_propagation_data
			bound_positional_method = boost::bind(&CommonApiRpcServer::network_get_transaction_propagation_data_positional,
				this, capture_con, _1);
			json_connection->add_method("network_get_transaction_propagation_data", bound_positional_method);
			bound_named_method = boost::bind(&CommonApiRpcServer::network_get_transaction_propagation_data_named,
				this, capture_con, _1);
			json_connection->add_named_param_method("network_get_transaction_propagation_data", bound_named_method);

			// register method network_get_block_propagation_data
			bound_positional_method = boost::bind(&CommonApiRpcServer::network_get_block_propagation_data_positional,
				this, capture_con, _1);
			json_connection->add_method("network_get_block_propagation_data", bound_positional_method);
			bound_named_method = boost::bind(&CommonApiRpcServer::network_get_block_propagation_data_named,
				this, capture_con, _1);
			json_connection->add_named_param_method("network_get_block_propagation_data", bound_named_method);

			// register method network_get_info
			bound_positional_method = boost::bind(&CommonApiRpcServer::network_get_info_positional,
				this, capture_con, _1);
			json_connection->add_method("network_get_info", bound_positional_method);
			bound_named_method = boost::bind(&CommonApiRpcServer::network_get_info_named,
				this, capture_con, _1);
			json_connection->add_named_param_method("network_get_info", bound_named_method);

			// register method network_list_potential_peers
			bound_positional_method = boost::bind(&CommonApiRpcServer::network_list_potential_peers_positional,
				this, capture_con, _1);
			json_connection->add_method("network_list_potential_peers", bound_positional_method);
			bound_named_method = boost::bind(&CommonApiRpcServer::network_list_potential_peers_named,
				this, capture_con, _1);
			json_connection->add_named_param_method("network_list_potential_peers", bound_named_method);

			// register method network_get_upnp_info
			bound_positional_method = boost::bind(&CommonApiRpcServer::network_get_upnp_info_positional,
				this, capture_con, _1);
			json_connection->add_method("network_get_upnp_info", bound_positional_method);
			bound_named_method = boost::bind(&CommonApiRpcServer::network_get_upnp_info_named,
				this, capture_con, _1);
			json_connection->add_named_param_method("network_get_upnp_info", bound_named_method);

			// register method network_get_blocked_ips
			bound_positional_method = boost::bind(&CommonApiRpcServer::network_get_blocked_ips_positional,
				this, capture_con, _1);
			json_connection->add_method("network_get_blocked_ips", bound_positional_method);
			bound_named_method = boost::bind(&CommonApiRpcServer::network_get_blocked_ips_named,
				this, capture_con, _1);
			json_connection->add_named_param_method("network_get_blocked_ips", bound_named_method);

			// register method debug_get_client_name
			bound_positional_method = boost::bind(&CommonApiRpcServer::debug_get_client_name_positional,
				this, capture_con, _1);
			json_connection->add_method("debug_get_client_name", bound_positional_method);
			bound_named_method = boost::bind(&CommonApiRpcServer::debug_get_client_name_named,
				this, capture_con, _1);
			json_connection->add_named_param_method("debug_get_client_name", bound_named_method);

			// register method delegate_get_config
			bound_positional_method = boost::bind(&CommonApiRpcServer::delegate_get_config_positional,
				this, capture_con, _1);
			json_connection->add_method("delegate_get_config", bound_positional_method);
			bound_named_method = boost::bind(&CommonApiRpcServer::delegate_get_config_named,
				this, capture_con, _1);
			json_connection->add_named_param_method("delegate_get_config", bound_named_method);

			// register method delegate_set_network_min_connection_count
			bound_positional_method = boost::bind(&CommonApiRpcServer::delegate_set_network_min_connection_count_positional,
				this, capture_con, _1);
			json_connection->add_method("delegate_set_network_min_connection_count", bound_positional_method);
			bound_named_method = boost::bind(&CommonApiRpcServer::delegate_set_network_min_connection_count_named,
				this, capture_con, _1);
			json_connection->add_named_param_method("delegate_set_network_min_connection_count", bound_named_method);

			// register method delegate_set_block_max_transaction_count
			bound_positional_method = boost::bind(&CommonApiRpcServer::delegate_set_block_max_transaction_count_positional,
				this, capture_con, _1);
			json_connection->add_method("delegate_set_block_max_transaction_count", bound_positional_method);
			bound_named_method = boost::bind(&CommonApiRpcServer::delegate_set_block_max_transaction_count_named,
				this, capture_con, _1);
			json_connection->add_named_param_method("delegate_set_block_max_transaction_count", bound_named_method);

			// register method delegate_set_soft_max_imessage_length
			bound_positional_method = boost::bind(&CommonApiRpcServer::delegate_set_soft_max_imessage_length_positional,
				this, capture_con, _1);
			json_connection->add_method("delegate_set_soft_max_imessage_length", bound_positional_method);
			bound_named_method = boost::bind(&CommonApiRpcServer::delegate_set_soft_max_imessage_length_named,
				this, capture_con, _1);
			json_connection->add_named_param_method("delegate_set_soft_max_imessage_length", bound_named_method);

			// register method delegate_set_imessage_fee_coe
			bound_positional_method = boost::bind(&CommonApiRpcServer::delegate_set_imessage_fee_coe_positional,
				this, capture_con, _1);
			json_connection->add_method("delegate_set_imessage_fee_coe", bound_positional_method);
			bound_named_method = boost::bind(&CommonApiRpcServer::delegate_set_imessage_fee_coe_named,
				this, capture_con, _1);
			json_connection->add_named_param_method("delegate_set_imessage_fee_coe", bound_named_method);

			// register method delegate_set_block_max_size
			bound_positional_method = boost::bind(&CommonApiRpcServer::delegate_set_block_max_size_positional,
				this, capture_con, _1);
			json_connection->add_method("delegate_set_block_max_size", bound_positional_method);
			bound_named_method = boost::bind(&CommonApiRpcServer::delegate_set_block_max_size_named,
				this, capture_con, _1);
			json_connection->add_named_param_method("delegate_set_block_max_size", bound_named_method);

			// register method delegate_set_transaction_max_size
			bound_positional_method = boost::bind(&CommonApiRpcServer::delegate_set_transaction_max_size_positional,
				this, capture_con, _1);
			json_connection->add_method("delegate_set_transaction_max_size", bound_positional_method);
			bound_named_method = boost::bind(&CommonApiRpcServer::delegate_set_transaction_max_size_named,
				this, capture_con, _1);
			json_connection->add_named_param_method("delegate_set_transaction_max_size", bound_named_method);

			// register method delegate_set_transaction_canonical_signatures_required
			bound_positional_method = boost::bind(&CommonApiRpcServer::delegate_set_transaction_canonical_signatures_required_positional,
				this, capture_con, _1);
			json_connection->add_method("delegate_set_transaction_canonical_signatures_required", bound_positional_method);
			bound_named_method = boost::bind(&CommonApiRpcServer::delegate_set_transaction_canonical_signatures_required_named,
				this, capture_con, _1);
			json_connection->add_named_param_method("delegate_set_transaction_canonical_signatures_required", bound_named_method);

			// register method delegate_set_transaction_min_fee
			bound_positional_method = boost::bind(&CommonApiRpcServer::delegate_set_transaction_min_fee_positional,
				this, capture_con, _1);
			json_connection->add_method("delegate_set_transaction_min_fee", bound_positional_method);
			bound_named_method = boost::bind(&CommonApiRpcServer::delegate_set_transaction_min_fee_named,
				this, capture_con, _1);
			json_connection->add_named_param_method("delegate_set_transaction_min_fee", bound_named_method);

			// register method delegate_blacklist_add_transaction
			bound_positional_method = boost::bind(&CommonApiRpcServer::delegate_blacklist_add_transaction_positional,
				this, capture_con, _1);
			json_connection->add_method("delegate_blacklist_add_transaction", bound_positional_method);
			bound_named_method = boost::bind(&CommonApiRpcServer::delegate_blacklist_add_transaction_named,
				this, capture_con, _1);
			json_connection->add_named_param_method("delegate_blacklist_add_transaction", bound_named_method);

			// register method delegate_blacklist_remove_transaction
			bound_positional_method = boost::bind(&CommonApiRpcServer::delegate_blacklist_remove_transaction_positional,
				this, capture_con, _1);
			json_connection->add_method("delegate_blacklist_remove_transaction", bound_positional_method);
			bound_named_method = boost::bind(&CommonApiRpcServer::delegate_blacklist_remove_transaction_named,
				this, capture_con, _1);
			json_connection->add_named_param_method("delegate_blacklist_remove_transaction", bound_named_method);

			// register method delegate_blacklist_add_operation
			bound_positional_method = boost::bind(&CommonApiRpcServer::delegate_blacklist_add_operation_positional,
				this, capture_con, _1);
			json_connection->add_method("delegate_blacklist_add_operation", bound_positional_method);
			bound_named_method = boost::bind(&CommonApiRpcServer::delegate_blacklist_add_operation_named,
				this, capture_con, _1);
			json_connection->add_named_param_method("delegate_blacklist_add_operation", bound_named_method);

			// register method delegate_blacklist_remove_operation
			bound_positional_method = boost::bind(&CommonApiRpcServer::delegate_blacklist_remove_operation_positional,
				this, capture_con, _1);
			json_connection->add_method("delegate_blacklist_remove_operation", bound_positional_method);
			bound_named_method = boost::bind(&CommonApiRpcServer::delegate_blacklist_remove_operation_named,
                this, capture_con, _1);
            json_connection->add_named_param_method("delegate_blacklist_remove_operation", bound_named_method);



           // register method wallet_get_info
            bound_positional_method = boost::bind(&CommonApiRpcServer::wallet_get_info_positional,
				this, capture_con, _1);
			json_connection->add_method("wallet_get_info", bound_positional_method);
			bound_named_method = boost::bind(&CommonApiRpcServer::wallet_get_info_named,
				this, capture_con, _1);
			json_connection->add_named_param_method("wallet_get_info", bound_named_method);

			// register method wallet_open
			bound_positional_method = boost::bind(&CommonApiRpcServer::wallet_open_positional,
				this, capture_con, _1);
			json_connection->add_method("wallet_open", bound_positional_method);
			json_connection->add_method("open", bound_positional_method);
			bound_named_method = boost::bind(&CommonApiRpcServer::wallet_open_named,
				this, capture_con, _1);
			json_connection->add_named_param_method("wallet_open", bound_named_method);
			json_connection->add_named_param_method("open", bound_named_method);

			// register method wallet_create
			bound_positional_method = boost::bind(&CommonApiRpcServer::wallet_create_positional,
				this, capture_con, _1);
			json_connection->add_method("wallet_create", bound_positional_method);
			json_connection->add_method("create", bound_positional_method);
			bound_named_method = boost::bind(&CommonApiRpcServer::wallet_create_named,
				this, capture_con, _1);
			json_connection->add_named_param_method("wallet_create", bound_named_method);
			json_connection->add_named_param_method("create", bound_named_method);

			// register method wallet_get_name
			bound_positional_method = boost::bind(&CommonApiRpcServer::wallet_get_name_positional,
				this, capture_con, _1);
			json_connection->add_method("wallet_get_name", bound_positional_method);
			bound_named_method = boost::bind(&CommonApiRpcServer::wallet_get_name_named,
				this, capture_con, _1);
			json_connection->add_named_param_method("wallet_get_name", bound_named_method);

			// register method wallet_import_private_key
			bound_positional_method = boost::bind(&CommonApiRpcServer::wallet_import_private_key_positional,
				this, capture_con, _1);
			json_connection->add_method("wallet_import_private_key", bound_positional_method);
			json_connection->add_method("import_key", bound_positional_method);
			json_connection->add_method("importprivkey", bound_positional_method);
			bound_named_method = boost::bind(&CommonApiRpcServer::wallet_import_private_key_named,
				this, capture_con, _1);
			json_connection->add_named_param_method("wallet_import_private_key", bound_named_method);
			json_connection->add_named_param_method("import_key", bound_named_method);
			json_connection->add_named_param_method("importprivkey", bound_named_method);

            // register method wallet_import_ethereum_private_key
            bound_positional_method = boost::bind(&CommonApiRpcServer::wallet_import_ethereum_private_key_positional,
                this, capture_con, _1);
            json_connection->add_method("wallet_import_ethereum_private_key", bound_positional_method);
            bound_named_method = boost::bind(&CommonApiRpcServer::wallet_import_ethereum_private_key_named,
                this, capture_con, _1);
            json_connection->add_named_param_method("wallet_import_ethereum_private_key", bound_named_method);

			// register method wallet_close
			bound_positional_method = boost::bind(&CommonApiRpcServer::wallet_close_positional,
				this, capture_con, _1);
			json_connection->add_method("wallet_close", bound_positional_method);
			json_connection->add_method("close", bound_positional_method);
			bound_named_method = boost::bind(&CommonApiRpcServer::wallet_close_named,
				this, capture_con, _1);
			json_connection->add_named_param_method("wallet_close", bound_named_method);
			json_connection->add_named_param_method("close", bound_named_method);

			// register method wallet_backup_create
			bound_positional_method = boost::bind(&CommonApiRpcServer::wallet_backup_create_positional,
				this, capture_con, _1);
			json_connection->add_method("wallet_backup_create", bound_positional_method);
			json_connection->add_method("backupwallet", bound_positional_method);
			json_connection->add_method("wallet_export_to_json", bound_positional_method);
			bound_named_method = boost::bind(&CommonApiRpcServer::wallet_backup_create_named,
				this, capture_con, _1);
			json_connection->add_named_param_method("wallet_backup_create", bound_named_method);
			json_connection->add_named_param_method("backupwallet", bound_named_method);
			json_connection->add_named_param_method("wallet_export_to_json", bound_named_method);

			// register method wallet_backup_restore
			bound_positional_method = boost::bind(&CommonApiRpcServer::wallet_backup_restore_positional,
				this, capture_con, _1);
			json_connection->add_method("wallet_backup_restore", bound_positional_method);
			json_connection->add_method("wallet_create_from_json", bound_positional_method);
			bound_named_method = boost::bind(&CommonApiRpcServer::wallet_backup_restore_named,
				this, capture_con, _1);
			json_connection->add_named_param_method("wallet_backup_restore", bound_named_method);
			json_connection->add_named_param_method("wallet_create_from_json", bound_named_method);

			// register method wallet_set_automatic_backups
			bound_positional_method = boost::bind(&CommonApiRpcServer::wallet_set_automatic_backups_positional,
				this, capture_con, _1);
			json_connection->add_method("wallet_set_automatic_backups", bound_positional_method);
			json_connection->add_method("auto_backup", bound_positional_method);
			json_connection->add_method("autobackup", bound_positional_method);
			bound_named_method = boost::bind(&CommonApiRpcServer::wallet_set_automatic_backups_named,
				this, capture_con, _1);
			json_connection->add_named_param_method("wallet_set_automatic_backups", bound_named_method);
			json_connection->add_named_param_method("auto_backup", bound_named_method);
			json_connection->add_named_param_method("autobackup", bound_named_method);

			// register method wallet_set_transaction_expiration_time
			bound_positional_method = boost::bind(&CommonApiRpcServer::wallet_set_transaction_expiration_time_positional,
				this, capture_con, _1);
			json_connection->add_method("wallet_set_transaction_expiration_time", bound_positional_method);
			json_connection->add_method("set_expiration", bound_positional_method);
			bound_named_method = boost::bind(&CommonApiRpcServer::wallet_set_transaction_expiration_time_named,
				this, capture_con, _1);
			json_connection->add_named_param_method("wallet_set_transaction_expiration_time", bound_named_method);
			json_connection->add_named_param_method("set_expiration", bound_named_method);

			// register method wallet_account_transaction_history
			bound_positional_method = boost::bind(&CommonApiRpcServer::wallet_account_transaction_history_positional,
				this, capture_con, _1);
			json_connection->add_method("wallet_account_transaction_history", bound_positional_method);
			json_connection->add_method("history", bound_positional_method);
			json_connection->add_method("listtransactions", bound_positional_method);
			bound_named_method = boost::bind(&CommonApiRpcServer::wallet_account_transaction_history_named,
				this, capture_con, _1);
			json_connection->add_named_param_method("wallet_account_transaction_history", bound_named_method);
			json_connection->add_named_param_method("history", bound_named_method);
			json_connection->add_named_param_method("listtransactions", bound_named_method);

			// register method wallet_transaction_history_splite
			bound_positional_method = boost::bind(&CommonApiRpcServer::wallet_transaction_history_splite_positional,
				this, capture_con, _1);
			json_connection->add_method("wallet_transaction_history_splite", bound_positional_method);
			bound_named_method = boost::bind(&CommonApiRpcServer::wallet_transaction_history_splite_named,
				this, capture_con, _1);
			json_connection->add_named_param_method("wallet_transaction_history_splite", bound_named_method);

			// register method wallet_account_historic_balance
			bound_positional_method = boost::bind(&CommonApiRpcServer::wallet_account_historic_balance_positional,
				this, capture_con, _1);
			json_connection->add_method("wallet_account_historic_balance", bound_positional_method);
			bound_named_method = boost::bind(&CommonApiRpcServer::wallet_account_historic_balance_named,
				this, capture_con, _1);
			json_connection->add_named_param_method("wallet_account_historic_balance", bound_named_method);

			// register method wallet_remove_transaction
			bound_positional_method = boost::bind(&CommonApiRpcServer::wallet_remove_transaction_positional,
				this, capture_con, _1);
			json_connection->add_method("wallet_remove_transaction", bound_positional_method);
			json_connection->add_method("remove_transaction", bound_positional_method);
			json_connection->add_method("wallet_transaction_remove", bound_positional_method);
			bound_named_method = boost::bind(&CommonApiRpcServer::wallet_remove_transaction_named,
				this, capture_con, _1);
			json_connection->add_named_param_method("wallet_remove_transaction", bound_named_method);
			json_connection->add_named_param_method("remove_transaction", bound_named_method);
			json_connection->add_named_param_method("wallet_transaction_remove", bound_named_method);

			// register method wallet_get_pending_transaction_errors
			bound_positional_method = boost::bind(&CommonApiRpcServer::wallet_get_pending_transaction_errors_positional,
				this, capture_con, _1);
			json_connection->add_method("wallet_get_pending_transaction_errors", bound_positional_method);
			bound_named_method = boost::bind(&CommonApiRpcServer::wallet_get_pending_transaction_errors_named,
				this, capture_con, _1);
			json_connection->add_named_param_method("wallet_get_pending_transaction_errors", bound_named_method);

			// register method wallet_lock
			bound_positional_method = boost::bind(&CommonApiRpcServer::wallet_lock_positional,
				this, capture_con, _1);
			json_connection->add_method("wallet_lock", bound_positional_method);
			json_connection->add_method("lock", bound_positional_method);
			bound_named_method = boost::bind(&CommonApiRpcServer::wallet_lock_named,
				this, capture_con, _1);
			json_connection->add_named_param_method("wallet_lock", bound_named_method);
			json_connection->add_named_param_method("lock", bound_named_method);

			// register method wallet_unlock
			bound_positional_method = boost::bind(&CommonApiRpcServer::wallet_unlock_positional,
				this, capture_con, _1);
			json_connection->add_method("wallet_unlock", bound_positional_method);
			json_connection->add_method("unlock", bound_positional_method);
			json_connection->add_method("walletpassphrase", bound_positional_method);
			bound_named_method = boost::bind(&CommonApiRpcServer::wallet_unlock_named,
				this, capture_con, _1);
			json_connection->add_named_param_method("wallet_unlock", bound_named_method);
			json_connection->add_named_param_method("unlock", bound_named_method);
			json_connection->add_named_param_method("walletpassphrase", bound_named_method);

			// register method wallet_change_passphrase
			bound_positional_method = boost::bind(&CommonApiRpcServer::wallet_change_passphrase_positional,
				this, capture_con, _1);
			json_connection->add_method("wallet_change_passphrase", bound_positional_method);
			json_connection->add_method("walletpassphrasechange", bound_positional_method);
			bound_named_method = boost::bind(&CommonApiRpcServer::wallet_change_passphrase_named,
				this, capture_con, _1);
			json_connection->add_named_param_method("wallet_change_passphrase", bound_named_method);
			json_connection->add_named_param_method("walletpassphrasechange", bound_named_method);

			// register method wallet_check_passphrase
			bound_positional_method = boost::bind(&CommonApiRpcServer::wallet_check_passphrase_positional,
				this, capture_con, _1);
			json_connection->add_method("wallet_check_passphrase", bound_positional_method);
			json_connection->add_method("check_passphrase", bound_positional_method);
			json_connection->add_method("check_password", bound_positional_method);
			bound_named_method = boost::bind(&CommonApiRpcServer::wallet_check_passphrase_named,
				this, capture_con, _1);
			json_connection->add_named_param_method("wallet_check_passphrase", bound_named_method);
			json_connection->add_named_param_method("check_passphrase", bound_named_method);
			json_connection->add_named_param_method("check_password", bound_named_method);

			// register method wallet_check_address
			bound_positional_method = boost::bind(&CommonApiRpcServer::wallet_check_address_positional,
				this, capture_con, _1);
			json_connection->add_method("wallet_check_address", bound_positional_method);
			json_connection->add_method("check_address", bound_positional_method);
			bound_named_method = boost::bind(&CommonApiRpcServer::wallet_check_address_named,
				this, capture_con, _1);
			json_connection->add_named_param_method("wallet_check_address", bound_named_method);
			json_connection->add_named_param_method("check_address", bound_named_method);

			// register method wallet_list
			bound_positional_method = boost::bind(&CommonApiRpcServer::wallet_list_positional,
				this, capture_con, _1);
			json_connection->add_method("wallet_list", bound_positional_method);
			bound_named_method = boost::bind(&CommonApiRpcServer::wallet_list_named,
				this, capture_con, _1);
			json_connection->add_named_param_method("wallet_list", bound_named_method);

			// register method wallet_account_create
			bound_positional_method = boost::bind(&CommonApiRpcServer::wallet_account_create_positional,
				this, capture_con, _1);
			json_connection->add_method("wallet_account_create", bound_positional_method);
			json_connection->add_method("wallet_create_account", bound_positional_method);
			json_connection->add_method("create_account", bound_positional_method);
			bound_named_method = boost::bind(&CommonApiRpcServer::wallet_account_create_named,
				this, capture_con, _1);
			json_connection->add_named_param_method("wallet_account_create", bound_named_method);
			json_connection->add_named_param_method("wallet_create_account", bound_named_method);
			json_connection->add_named_param_method("create_account", bound_named_method);

			// register method wallet_account_set_approval
			bound_positional_method = boost::bind(&CommonApiRpcServer::wallet_account_set_approval_positional,
				this, capture_con, _1);
			json_connection->add_method("wallet_account_set_approval", bound_positional_method);
			json_connection->add_method("approve", bound_positional_method);
			json_connection->add_method("set_approval", bound_positional_method);
			json_connection->add_method("wallet_approve_delegate", bound_positional_method);
			json_connection->add_method("wallet_approve", bound_positional_method);
			bound_named_method = boost::bind(&CommonApiRpcServer::wallet_account_set_approval_named,
				this, capture_con, _1);
			json_connection->add_named_param_method("wallet_account_set_approval", bound_named_method);
			json_connection->add_named_param_method("approve", bound_named_method);
			json_connection->add_named_param_method("set_approval", bound_named_method);
			json_connection->add_named_param_method("wallet_approve_delegate", bound_named_method);
			json_connection->add_named_param_method("wallet_approve", bound_named_method);

			// register method wallet_get_all_approved_accounts
			bound_positional_method = boost::bind(&CommonApiRpcServer::wallet_get_all_approved_accounts_positional,
				this, capture_con, _1);
			json_connection->add_method("wallet_get_all_approved_accounts", bound_positional_method);
			json_connection->add_method("all_approved_accounts", bound_positional_method);
			json_connection->add_method("approved_accounts", bound_positional_method);
			bound_named_method = boost::bind(&CommonApiRpcServer::wallet_get_all_approved_accounts_named,
				this, capture_con, _1);
			json_connection->add_named_param_method("wallet_get_all_approved_accounts", bound_named_method);
			json_connection->add_named_param_method("all_approved_accounts", bound_named_method);
			json_connection->add_named_param_method("approved_accounts", bound_named_method);

			// register method wallet_address_create
			bound_positional_method = boost::bind(&CommonApiRpcServer::wallet_address_create_positional,
				this, capture_con, _1);
			json_connection->add_method("wallet_address_create", bound_positional_method);
			json_connection->add_method("new_address", bound_positional_method);
			bound_named_method = boost::bind(&CommonApiRpcServer::wallet_address_create_named,
				this, capture_con, _1);
			json_connection->add_named_param_method("wallet_address_create", bound_named_method);
			json_connection->add_named_param_method("new_address", bound_named_method);

			// register method wallet_transfer_to_address
			bound_positional_method = boost::bind(&CommonApiRpcServer::wallet_transfer_to_address_positional,
				this, capture_con, _1);
			json_connection->add_method("wallet_transfer_to_address", bound_positional_method);
			bound_named_method = boost::bind(&CommonApiRpcServer::wallet_transfer_to_address_named,
				this, capture_con, _1);
			json_connection->add_named_param_method("wallet_transfer_to_address", bound_named_method);

			// register method wallet_transfer_to_public_account
			bound_positional_method = boost::bind(&CommonApiRpcServer::wallet_transfer_to_public_account_positional,
				this, capture_con, _1);
			json_connection->add_method("wallet_transfer_to_public_account", bound_positional_method);
			json_connection->add_method("transfer_public", bound_positional_method);
			bound_named_method = boost::bind(&CommonApiRpcServer::wallet_transfer_to_public_account_named,
				this, capture_con, _1);
			json_connection->add_named_param_method("wallet_transfer_to_public_account", bound_named_method);
			json_connection->add_named_param_method("transfer_public", bound_named_method);

			// register method wallet_withdraw_from_address
			bound_positional_method = boost::bind(&CommonApiRpcServer::wallet_withdraw_from_address_positional,
				this, capture_con, _1);
			json_connection->add_method("wallet_withdraw_from_address", bound_positional_method);
			json_connection->add_method("withdraw_from_address", bound_positional_method);
			bound_named_method = boost::bind(&CommonApiRpcServer::wallet_withdraw_from_address_named,
				this, capture_con, _1);
			json_connection->add_named_param_method("wallet_withdraw_from_address", bound_named_method);
			json_connection->add_named_param_method("withdraw_from_address", bound_named_method);

			// register method wallet_rescan_blockchain
			bound_positional_method = boost::bind(&CommonApiRpcServer::wallet_rescan_blockchain_positional,
				this, capture_con, _1);
			json_connection->add_method("wallet_rescan_blockchain", bound_positional_method);
			json_connection->add_method("scan", bound_positional_method);
			json_connection->add_method("rescan", bound_positional_method);
			bound_named_method = boost::bind(&CommonApiRpcServer::wallet_rescan_blockchain_named,
				this, capture_con, _1);
			json_connection->add_named_param_method("wallet_rescan_blockchain", bound_named_method);
			json_connection->add_named_param_method("scan", bound_named_method);
			json_connection->add_named_param_method("rescan", bound_named_method);

			// register method wallet_cancel_scan
			bound_positional_method = boost::bind(&CommonApiRpcServer::wallet_cancel_scan_positional,
				this, capture_con, _1);
			json_connection->add_method("wallet_cancel_scan", bound_positional_method);
			bound_named_method = boost::bind(&CommonApiRpcServer::wallet_cancel_scan_named,
				this, capture_con, _1);
			json_connection->add_named_param_method("wallet_cancel_scan", bound_named_method);

			// register method wallet_get_transaction
			bound_positional_method = boost::bind(&CommonApiRpcServer::wallet_get_transaction_positional,
				this, capture_con, _1);
			json_connection->add_method("wallet_get_transaction", bound_positional_method);
			json_connection->add_method("get_transaction", bound_positional_method);
			bound_named_method = boost::bind(&CommonApiRpcServer::wallet_get_transaction_named,
				this, capture_con, _1);
			json_connection->add_named_param_method("wallet_get_transaction", bound_named_method);
			json_connection->add_named_param_method("get_transaction", bound_named_method);

			// register method wallet_scan_transaction
			bound_positional_method = boost::bind(&CommonApiRpcServer::wallet_scan_transaction_positional,
				this, capture_con, _1);
			json_connection->add_method("wallet_scan_transaction", bound_positional_method);
			json_connection->add_method("scan_transaction", bound_positional_method);
			json_connection->add_method("wallet_transaction_scan", bound_positional_method);
			bound_named_method = boost::bind(&CommonApiRpcServer::wallet_scan_transaction_named,
				this, capture_con, _1);
			json_connection->add_named_param_method("wallet_scan_transaction", bound_named_method);
			json_connection->add_named_param_method("scan_transaction", bound_named_method);
			json_connection->add_named_param_method("wallet_transaction_scan", bound_named_method);

			// register method wallet_rebroadcast_transaction
			bound_positional_method = boost::bind(&CommonApiRpcServer::wallet_rebroadcast_transaction_positional,
				this, capture_con, _1);
			json_connection->add_method("wallet_rebroadcast_transaction", bound_positional_method);
			json_connection->add_method("rebroadcast", bound_positional_method);
			json_connection->add_method("wallet_transaction_rebroadcast", bound_positional_method);
			bound_named_method = boost::bind(&CommonApiRpcServer::wallet_rebroadcast_transaction_named,
				this, capture_con, _1);
			json_connection->add_named_param_method("wallet_rebroadcast_transaction", bound_named_method);
			json_connection->add_named_param_method("rebroadcast", bound_named_method);
			json_connection->add_named_param_method("wallet_transaction_rebroadcast", bound_named_method);

			// register method wallet_account_register
			bound_positional_method = boost::bind(&CommonApiRpcServer::wallet_account_register_positional,
				this, capture_con, _1);
			json_connection->add_method("wallet_account_register", bound_positional_method);
			json_connection->add_method("register", bound_positional_method);
			bound_named_method = boost::bind(&CommonApiRpcServer::wallet_account_register_named,
				this, capture_con, _1);
			json_connection->add_named_param_method("wallet_account_register", bound_named_method);
			json_connection->add_named_param_method("register", bound_named_method);

			// register method wallet_account_update_private_data
			bound_positional_method = boost::bind(&CommonApiRpcServer::wallet_account_update_private_data_positional,
				this, capture_con, _1);
			json_connection->add_method("wallet_account_update_private_data", bound_positional_method);
			json_connection->add_method("update_private_data", bound_positional_method);
			bound_named_method = boost::bind(&CommonApiRpcServer::wallet_account_update_private_data_named,
				this, capture_con, _1);
			json_connection->add_named_param_method("wallet_account_update_private_data", bound_named_method);
			json_connection->add_named_param_method("update_private_data", bound_named_method);

			// register method wallet_account_update_registration
			bound_positional_method = boost::bind(&CommonApiRpcServer::wallet_account_update_registration_positional,
				this, capture_con, _1);
			json_connection->add_method("wallet_account_update_registration", bound_positional_method);
			json_connection->add_method("update_registration", bound_positional_method);
			bound_named_method = boost::bind(&CommonApiRpcServer::wallet_account_update_registration_named,
				this, capture_con, _1);
			json_connection->add_named_param_method("wallet_account_update_registration", bound_named_method);
			json_connection->add_named_param_method("update_registration", bound_named_method);

			// register method wallet_account_update_active_key
			bound_positional_method = boost::bind(&CommonApiRpcServer::wallet_account_update_active_key_positional,
				this, capture_con, _1);
			json_connection->add_method("wallet_account_update_active_key", bound_positional_method);
			bound_named_method = boost::bind(&CommonApiRpcServer::wallet_account_update_active_key_named,
				this, capture_con, _1);
			json_connection->add_named_param_method("wallet_account_update_active_key", bound_named_method);

			// register method wallet_list_accounts
			bound_positional_method = boost::bind(&CommonApiRpcServer::wallet_list_accounts_positional,
				this, capture_con, _1);
			json_connection->add_method("wallet_list_accounts", bound_positional_method);
			json_connection->add_method("listaccounts", bound_positional_method);
			bound_named_method = boost::bind(&CommonApiRpcServer::wallet_list_accounts_named,
				this, capture_con, _1);
			json_connection->add_named_param_method("wallet_list_accounts", bound_named_method);
			json_connection->add_named_param_method("listaccounts", bound_named_method);

			// register method wallet_list_unregistered_accounts
			bound_positional_method = boost::bind(&CommonApiRpcServer::wallet_list_unregistered_accounts_positional,
				this, capture_con, _1);
			json_connection->add_method("wallet_list_unregistered_accounts", bound_positional_method);
			bound_named_method = boost::bind(&CommonApiRpcServer::wallet_list_unregistered_accounts_named,
				this, capture_con, _1);
			json_connection->add_named_param_method("wallet_list_unregistered_accounts", bound_named_method);

			// register method wallet_list_my_accounts
			bound_positional_method = boost::bind(&CommonApiRpcServer::wallet_list_my_accounts_positional,
				this, capture_con, _1);
			json_connection->add_method("wallet_list_my_accounts", bound_positional_method);
			bound_named_method = boost::bind(&CommonApiRpcServer::wallet_list_my_accounts_named,
				this, capture_con, _1);
			json_connection->add_named_param_method("wallet_list_my_accounts", bound_named_method);

			// register method wallet_list_my_addresses
			bound_positional_method = boost::bind(&CommonApiRpcServer::wallet_list_my_addresses_positional,
				this, capture_con, _1);
			json_connection->add_method("wallet_list_my_addresses", bound_positional_method);
			bound_named_method = boost::bind(&CommonApiRpcServer::wallet_list_my_addresses_named,
				this, capture_con, _1);
			json_connection->add_named_param_method("wallet_list_my_addresses", bound_named_method);

			// register method wallet_get_account
			bound_positional_method = boost::bind(&CommonApiRpcServer::wallet_get_account_positional,
				this, capture_con, _1);
			json_connection->add_method("wallet_get_account", bound_positional_method);
			bound_named_method = boost::bind(&CommonApiRpcServer::wallet_get_account_named,
				this, capture_con, _1);
			json_connection->add_named_param_method("wallet_get_account", bound_named_method);

			// register method wallet_get_account_public_address
			bound_positional_method = boost::bind(&CommonApiRpcServer::wallet_get_account_public_address_positional,
				this, capture_con, _1);
			json_connection->add_method("wallet_get_account_public_address", bound_positional_method);
			bound_named_method = boost::bind(&CommonApiRpcServer::wallet_get_account_public_address_named,
				this, capture_con, _1);
			json_connection->add_named_param_method("wallet_get_account_public_address", bound_named_method);

			// register method wallet_remove_contact_account
			bound_positional_method = boost::bind(&CommonApiRpcServer::wallet_remove_contact_account_positional,
				this, capture_con, _1);
			json_connection->add_method("wallet_remove_contact_account", bound_positional_method);
			bound_named_method = boost::bind(&CommonApiRpcServer::wallet_remove_contact_account_named,
				this, capture_con, _1);
			json_connection->add_named_param_method("wallet_remove_contact_account", bound_named_method);

			// register method wallet_account_rename
			bound_positional_method = boost::bind(&CommonApiRpcServer::wallet_account_rename_positional,
				this, capture_con, _1);
			json_connection->add_method("wallet_account_rename", bound_positional_method);
			json_connection->add_method("wallet_rename_account", bound_positional_method);
			bound_named_method = boost::bind(&CommonApiRpcServer::wallet_account_rename_named,
				this, capture_con, _1);
			json_connection->add_named_param_method("wallet_account_rename", bound_named_method);
			json_connection->add_named_param_method("wallet_rename_account", bound_named_method);

			// register method wallet_asset_create
			bound_positional_method = boost::bind(&CommonApiRpcServer::wallet_asset_create_positional,
				this, capture_con, _1);
			json_connection->add_method("wallet_asset_create", bound_positional_method);
			bound_named_method = boost::bind(&CommonApiRpcServer::wallet_asset_create_named,
				this, capture_con, _1);
			json_connection->add_named_param_method("wallet_asset_create", bound_named_method);

			// register method wallet_asset_issue
			bound_positional_method = boost::bind(&CommonApiRpcServer::wallet_asset_issue_positional,
				this, capture_con, _1);
			json_connection->add_method("wallet_asset_issue", bound_positional_method);
			bound_named_method = boost::bind(&CommonApiRpcServer::wallet_asset_issue_named,
				this, capture_con, _1);
			json_connection->add_named_param_method("wallet_asset_issue", bound_named_method);

			// register method wallet_asset_issue_to_addresses
			bound_positional_method = boost::bind(&CommonApiRpcServer::wallet_asset_issue_to_addresses_positional,
				this, capture_con, _1);
			json_connection->add_method("wallet_asset_issue_to_addresses", bound_positional_method);
			bound_named_method = boost::bind(&CommonApiRpcServer::wallet_asset_issue_to_addresses_named,
				this, capture_con, _1);
			json_connection->add_named_param_method("wallet_asset_issue_to_addresses", bound_named_method);

			// register method wallet_account_balance
			bound_positional_method = boost::bind(&CommonApiRpcServer::wallet_account_balance_positional,
				this, capture_con, _1);
			json_connection->add_method("wallet_account_balance", bound_positional_method);
			json_connection->add_method("balance", bound_positional_method);
			json_connection->add_method("getbalance", bound_positional_method);
			bound_named_method = boost::bind(&CommonApiRpcServer::wallet_account_balance_named,
				this, capture_con, _1);
			json_connection->add_named_param_method("wallet_account_balance", bound_named_method);
			json_connection->add_named_param_method("balance", bound_named_method);
			json_connection->add_named_param_method("getbalance", bound_named_method);

			// register method wallet_account_balance_ids
			bound_positional_method = boost::bind(&CommonApiRpcServer::wallet_account_balance_ids_positional,
				this, capture_con, _1);
			json_connection->add_method("wallet_account_balance_ids", bound_positional_method);
			bound_named_method = boost::bind(&CommonApiRpcServer::wallet_account_balance_ids_named,
				this, capture_con, _1);
			json_connection->add_named_param_method("wallet_account_balance_ids", bound_named_method);

			// register method wallet_account_list_public_keys
			bound_positional_method = boost::bind(&CommonApiRpcServer::wallet_account_list_public_keys_positional,
				this, capture_con, _1);
			json_connection->add_method("wallet_account_list_public_keys", bound_positional_method);
			json_connection->add_method("public_keys", bound_positional_method);
			bound_named_method = boost::bind(&CommonApiRpcServer::wallet_account_list_public_keys_named,
				this, capture_con, _1);
			json_connection->add_named_param_method("wallet_account_list_public_keys", bound_named_method);
			json_connection->add_named_param_method("public_keys", bound_named_method);

			// register method wallet_delegate_withdraw_pay
			bound_positional_method = boost::bind(&CommonApiRpcServer::wallet_delegate_withdraw_pay_positional,
				this, capture_con, _1);
			json_connection->add_method("wallet_delegate_withdraw_pay", bound_positional_method);
			json_connection->add_method("pay_delegate", bound_positional_method);
			bound_named_method = boost::bind(&CommonApiRpcServer::wallet_delegate_withdraw_pay_named,
				this, capture_con, _1);
			json_connection->add_named_param_method("wallet_delegate_withdraw_pay", bound_named_method);
			json_connection->add_named_param_method("pay_delegate", bound_named_method);

			// register method wallet_delegate_pay_balance_query
			bound_positional_method = boost::bind(&CommonApiRpcServer::wallet_delegate_pay_balance_query_positional,
				this, capture_con, _1);
			json_connection->add_method("wallet_delegate_pay_balance_query", bound_positional_method);
			json_connection->add_method("query_salary", bound_positional_method);
			bound_named_method = boost::bind(&CommonApiRpcServer::wallet_delegate_pay_balance_query_named,
				this, capture_con, _1);
			json_connection->add_named_param_method("wallet_delegate_pay_balance_query", bound_named_method);
			json_connection->add_named_param_method("query_salary", bound_named_method);

			// register method wallet_active_delegate_salary
			bound_positional_method = boost::bind(&CommonApiRpcServer::wallet_active_delegate_salary_positional,
				this, capture_con, _1);
			json_connection->add_method("wallet_active_delegate_salary", bound_positional_method);
			bound_named_method = boost::bind(&CommonApiRpcServer::wallet_active_delegate_salary_named,
				this, capture_con, _1);
			json_connection->add_named_param_method("wallet_active_delegate_salary", bound_named_method);

			// register method wallet_get_delegate_statue
			bound_positional_method = boost::bind(&CommonApiRpcServer::wallet_get_delegate_statue_positional,
				this, capture_con, _1);
			json_connection->add_method("wallet_get_delegate_statue", bound_positional_method);
			bound_named_method = boost::bind(&CommonApiRpcServer::wallet_get_delegate_statue_named,
				this, capture_con, _1);
			json_connection->add_named_param_method("wallet_get_delegate_statue", bound_named_method);

			// register method wallet_set_transaction_imessage_fee_coe
			bound_positional_method = boost::bind(&CommonApiRpcServer::wallet_set_transaction_imessage_fee_coe_positional,
				this, capture_con, _1);
			json_connection->add_method("wallet_set_transaction_imessage_fee_coe", bound_positional_method);
			json_connection->add_method("set_fee_coe", bound_positional_method);
			bound_named_method = boost::bind(&CommonApiRpcServer::wallet_set_transaction_imessage_fee_coe_named,
				this, capture_con, _1);
			json_connection->add_named_param_method("wallet_set_transaction_imessage_fee_coe", bound_named_method);
			json_connection->add_named_param_method("set_fee_coe", bound_named_method);

			// register method wallet_get_transaction_imessage_fee_coe
			bound_positional_method = boost::bind(&CommonApiRpcServer::wallet_get_transaction_imessage_fee_coe_positional,
				this, capture_con, _1);
			json_connection->add_method("wallet_get_transaction_imessage_fee_coe", bound_positional_method);
			json_connection->add_method("get_fee_coe", bound_positional_method);
			bound_named_method = boost::bind(&CommonApiRpcServer::wallet_get_transaction_imessage_fee_coe_named,
				this, capture_con, _1);
			json_connection->add_named_param_method("wallet_get_transaction_imessage_fee_coe", bound_named_method);
			json_connection->add_named_param_method("get_fee_coe", bound_named_method);

			// register method wallet_set_transaction_imessage_soft_max_length
			bound_positional_method = boost::bind(&CommonApiRpcServer::wallet_set_transaction_imessage_soft_max_length_positional,
				this, capture_con, _1);
			json_connection->add_method("wallet_set_transaction_imessage_soft_max_length", bound_positional_method);
			json_connection->add_method("set_soft_length", bound_positional_method);
			bound_named_method = boost::bind(&CommonApiRpcServer::wallet_set_transaction_imessage_soft_max_length_named,
				this, capture_con, _1);
			json_connection->add_named_param_method("wallet_set_transaction_imessage_soft_max_length", bound_named_method);
			json_connection->add_named_param_method("set_soft_length", bound_named_method);

			// register method wallet_get_transaction_imessage_soft_max_length
			bound_positional_method = boost::bind(&CommonApiRpcServer::wallet_get_transaction_imessage_soft_max_length_positional,
				this, capture_con, _1);
			json_connection->add_method("wallet_get_transaction_imessage_soft_max_length", bound_positional_method);
			json_connection->add_method("get_soft_length", bound_positional_method);
			bound_named_method = boost::bind(&CommonApiRpcServer::wallet_get_transaction_imessage_soft_max_length_named,
				this, capture_con, _1);
			json_connection->add_named_param_method("wallet_get_transaction_imessage_soft_max_length", bound_named_method);
			json_connection->add_named_param_method("get_soft_length", bound_named_method);

			// register method wallet_set_transaction_fee
			bound_positional_method = boost::bind(&CommonApiRpcServer::wallet_set_transaction_fee_positional,
				this, capture_con, _1);
			json_connection->add_method("wallet_set_transaction_fee", bound_positional_method);
			json_connection->add_method("wallet_set_priority_fee", bound_positional_method);
			json_connection->add_method("set_priority_fee", bound_positional_method);
			json_connection->add_method("settrxfee", bound_positional_method);
			json_connection->add_method("setfee", bound_positional_method);
			json_connection->add_method("set_fee", bound_positional_method);
			bound_named_method = boost::bind(&CommonApiRpcServer::wallet_set_transaction_fee_named,
				this, capture_con, _1);
			json_connection->add_named_param_method("wallet_set_transaction_fee", bound_named_method);
			json_connection->add_named_param_method("wallet_set_priority_fee", bound_named_method);
			json_connection->add_named_param_method("set_priority_fee", bound_named_method);
			json_connection->add_named_param_method("settrxfee", bound_named_method);
			json_connection->add_named_param_method("setfee", bound_named_method);
			json_connection->add_named_param_method("set_fee", bound_named_method);

			// register method wallet_get_transaction_fee
			bound_positional_method = boost::bind(&CommonApiRpcServer::wallet_get_transaction_fee_positional,
				this, capture_con, _1);
			json_connection->add_method("wallet_get_transaction_fee", bound_positional_method);
			json_connection->add_method("wallet_get_priority_fee", bound_positional_method);
			json_connection->add_method("get_priority_fee", bound_positional_method);
			json_connection->add_method("gettrxfee", bound_positional_method);
			json_connection->add_method("getfee", bound_positional_method);
			json_connection->add_method("get_fee", bound_positional_method);
			bound_named_method = boost::bind(&CommonApiRpcServer::wallet_get_transaction_fee_named,
				this, capture_con, _1);
			json_connection->add_named_param_method("wallet_get_transaction_fee", bound_named_method);
			json_connection->add_named_param_method("wallet_get_priority_fee", bound_named_method);
			json_connection->add_named_param_method("get_priority_fee", bound_named_method);
			json_connection->add_named_param_method("gettrxfee", bound_named_method);
			json_connection->add_named_param_method("getfee", bound_named_method);
			json_connection->add_named_param_method("get_fee", bound_named_method);

			// register method wallet_dump_private_key
			bound_positional_method = boost::bind(&CommonApiRpcServer::wallet_dump_private_key_positional,
				this, capture_con, _1);
			json_connection->add_method("wallet_dump_private_key", bound_positional_method);
			json_connection->add_method("dump_private_key", bound_positional_method);
			json_connection->add_method("dumpprivkey", bound_positional_method);
			bound_named_method = boost::bind(&CommonApiRpcServer::wallet_dump_private_key_named,
				this, capture_con, _1);
			json_connection->add_named_param_method("wallet_dump_private_key", bound_named_method);
			json_connection->add_named_param_method("dump_private_key", bound_named_method);
			json_connection->add_named_param_method("dumpprivkey", bound_named_method);

			// register method wallet_dump_account_private_key
			bound_positional_method = boost::bind(&CommonApiRpcServer::wallet_dump_account_private_key_positional,
				this, capture_con, _1);
			json_connection->add_method("wallet_dump_account_private_key", bound_positional_method);
			bound_named_method = boost::bind(&CommonApiRpcServer::wallet_dump_account_private_key_named,
				this, capture_con, _1);
			json_connection->add_named_param_method("wallet_dump_account_private_key", bound_named_method);

			// register method wallet_account_vote_summary
			bound_positional_method = boost::bind(&CommonApiRpcServer::wallet_account_vote_summary_positional,
				this, capture_con, _1);
			json_connection->add_method("wallet_account_vote_summary", bound_positional_method);
			json_connection->add_method("votes", bound_positional_method);
			bound_named_method = boost::bind(&CommonApiRpcServer::wallet_account_vote_summary_named,
				this, capture_con, _1);
			json_connection->add_named_param_method("wallet_account_vote_summary", bound_named_method);
			json_connection->add_named_param_method("votes", bound_named_method);

			// register method wallet_check_vote_status
			bound_positional_method = boost::bind(&CommonApiRpcServer::wallet_check_vote_status_positional,
				this, capture_con, _1);
			json_connection->add_method("wallet_check_vote_status", bound_positional_method);
			bound_named_method = boost::bind(&CommonApiRpcServer::wallet_check_vote_status_named,
				this, capture_con, _1);
			json_connection->add_named_param_method("wallet_check_vote_status", bound_named_method);

			// register method wallet_set_setting
			bound_positional_method = boost::bind(&CommonApiRpcServer::wallet_set_setting_positional,
				this, capture_con, _1);
			json_connection->add_method("wallet_set_setting", bound_positional_method);
			bound_named_method = boost::bind(&CommonApiRpcServer::wallet_set_setting_named,
				this, capture_con, _1);
			json_connection->add_named_param_method("wallet_set_setting", bound_named_method);

			// register method wallet_get_setting
			bound_positional_method = boost::bind(&CommonApiRpcServer::wallet_get_setting_positional,
				this, capture_con, _1);
			json_connection->add_method("wallet_get_setting", bound_positional_method);
			bound_named_method = boost::bind(&CommonApiRpcServer::wallet_get_setting_named,
				this, capture_con, _1);
			json_connection->add_named_param_method("wallet_get_setting", bound_named_method);

			// register method wallet_delegate_set_block_production
			bound_positional_method = boost::bind(&CommonApiRpcServer::wallet_delegate_set_block_production_positional,
				this, capture_con, _1);
			json_connection->add_method("wallet_delegate_set_block_production", bound_positional_method);
			bound_named_method = boost::bind(&CommonApiRpcServer::wallet_delegate_set_block_production_named,
				this, capture_con, _1);
			json_connection->add_named_param_method("wallet_delegate_set_block_production", bound_named_method);

			// register method wallet_set_transaction_scanning
			bound_positional_method = boost::bind(&CommonApiRpcServer::wallet_set_transaction_scanning_positional,
				this, capture_con, _1);
			json_connection->add_method("wallet_set_transaction_scanning", bound_positional_method);
			bound_named_method = boost::bind(&CommonApiRpcServer::wallet_set_transaction_scanning_named,
				this, capture_con, _1);
			json_connection->add_named_param_method("wallet_set_transaction_scanning", bound_named_method);

			// register method wallet_sign_hash
			bound_positional_method = boost::bind(&CommonApiRpcServer::wallet_sign_hash_positional,
				this, capture_con, _1);
			json_connection->add_method("wallet_sign_hash", bound_positional_method);
			bound_named_method = boost::bind(&CommonApiRpcServer::wallet_sign_hash_named,
				this, capture_con, _1);
			json_connection->add_named_param_method("wallet_sign_hash", bound_named_method);

			// register method wallet_login_start
			bound_positional_method = boost::bind(&CommonApiRpcServer::wallet_login_start_positional,
				this, capture_con, _1);
			json_connection->add_method("wallet_login_start", bound_positional_method);
			bound_named_method = boost::bind(&CommonApiRpcServer::wallet_login_start_named,
				this, capture_con, _1);
			json_connection->add_named_param_method("wallet_login_start", bound_named_method);

			// register method wallet_login_finish
			bound_positional_method = boost::bind(&CommonApiRpcServer::wallet_login_finish_positional,
				this, capture_con, _1);
			json_connection->add_method("wallet_login_finish", bound_positional_method);
			bound_named_method = boost::bind(&CommonApiRpcServer::wallet_login_finish_named,
				this, capture_con, _1);
			json_connection->add_named_param_method("wallet_login_finish", bound_named_method);

			// register method wallet_balance_set_vote_info
			bound_positional_method = boost::bind(&CommonApiRpcServer::wallet_balance_set_vote_info_positional,
				this, capture_con, _1);
			json_connection->add_method("wallet_balance_set_vote_info", bound_positional_method);
			json_connection->add_method("set_vote_info", bound_positional_method);
			bound_named_method = boost::bind(&CommonApiRpcServer::wallet_balance_set_vote_info_named,
				this, capture_con, _1);
			json_connection->add_named_param_method("wallet_balance_set_vote_info", bound_named_method);
			json_connection->add_named_param_method("set_vote_info", bound_named_method);

			// register method wallet_publish_slate
			bound_positional_method = boost::bind(&CommonApiRpcServer::wallet_publish_slate_positional,
				this, capture_con, _1);
			json_connection->add_method("wallet_publish_slate", bound_positional_method);
			bound_named_method = boost::bind(&CommonApiRpcServer::wallet_publish_slate_named,
				this, capture_con, _1);
			json_connection->add_named_param_method("wallet_publish_slate", bound_named_method);

			// register method wallet_publish_version
			bound_positional_method = boost::bind(&CommonApiRpcServer::wallet_publish_version_positional,
				this, capture_con, _1);
			json_connection->add_method("wallet_publish_version", bound_positional_method);
			bound_named_method = boost::bind(&CommonApiRpcServer::wallet_publish_version_named,
				this, capture_con, _1);
			json_connection->add_named_param_method("wallet_publish_version", bound_named_method);

			// register method wallet_collect_genesis_balances
			bound_positional_method = boost::bind(&CommonApiRpcServer::wallet_collect_genesis_balances_positional,
				this, capture_con, _1);
			json_connection->add_method("wallet_collect_genesis_balances", bound_positional_method);
			bound_named_method = boost::bind(&CommonApiRpcServer::wallet_collect_genesis_balances_named,
				this, capture_con, _1);
			json_connection->add_named_param_method("wallet_collect_genesis_balances", bound_named_method);

			// register method wallet_recover_accounts
			bound_positional_method = boost::bind(&CommonApiRpcServer::wallet_recover_accounts_positional,
				this, capture_con, _1);
			json_connection->add_method("wallet_recover_accounts", bound_positional_method);
			bound_named_method = boost::bind(&CommonApiRpcServer::wallet_recover_accounts_named,
				this, capture_con, _1);
			json_connection->add_named_param_method("wallet_recover_accounts", bound_named_method);

			// register method wallet_verify_titan_deposit
			bound_positional_method = boost::bind(&CommonApiRpcServer::wallet_verify_titan_deposit_positional,
				this, capture_con, _1);
			json_connection->add_method("wallet_verify_titan_deposit", bound_positional_method);
			bound_named_method = boost::bind(&CommonApiRpcServer::wallet_verify_titan_deposit_named,
				this, capture_con, _1);
			json_connection->add_named_param_method("wallet_verify_titan_deposit", bound_named_method);

			// register method wallet_repair_entrys
			bound_positional_method = boost::bind(&CommonApiRpcServer::wallet_repair_entrys_positional,
				this, capture_con, _1);
			json_connection->add_method("wallet_repair_entrys", bound_positional_method);
			bound_named_method = boost::bind(&CommonApiRpcServer::wallet_repair_entrys_named,
				this, capture_con, _1);
			json_connection->add_named_param_method("wallet_repair_entrys", bound_named_method);

			// register method wallet_regenerate_keys
			bound_positional_method = boost::bind(&CommonApiRpcServer::wallet_regenerate_keys_positional,
				this, capture_con, _1);
			json_connection->add_method("wallet_regenerate_keys", bound_positional_method);
			bound_named_method = boost::bind(&CommonApiRpcServer::wallet_regenerate_keys_named,
				this, capture_con, _1);
			json_connection->add_named_param_method("wallet_regenerate_keys", bound_named_method);

			// register method wallet_account_retract
			bound_positional_method = boost::bind(&CommonApiRpcServer::wallet_account_retract_positional,
				this, capture_con, _1);
			json_connection->add_method("wallet_account_retract", bound_positional_method);
			bound_named_method = boost::bind(&CommonApiRpcServer::wallet_account_retract_named,
				this, capture_con, _1);
			json_connection->add_named_param_method("wallet_account_retract", bound_named_method);

			// register method wallet_account_delete
			bound_positional_method = boost::bind(&CommonApiRpcServer::wallet_account_delete_positional,
				this, capture_con, _1);
			json_connection->add_method("wallet_account_delete", bound_positional_method);
			bound_named_method = boost::bind(&CommonApiRpcServer::wallet_account_delete_named,
				this, capture_con, _1);
			json_connection->add_named_param_method("wallet_account_delete", bound_named_method);

			// register method wallet_transfer_to_address_rpc
			bound_positional_method = boost::bind(&CommonApiRpcServer::wallet_transfer_to_address_rpc_positional,
				this, capture_con, _1);
			json_connection->add_method("wallet_transfer_to_address_rpc", bound_positional_method);
			bound_named_method = boost::bind(&CommonApiRpcServer::wallet_transfer_to_address_rpc_named,
				this, capture_con, _1);
			json_connection->add_named_param_method("wallet_transfer_to_address_rpc", bound_named_method);

			// register method wallet_account_balance_rpc
			bound_positional_method = boost::bind(&CommonApiRpcServer::wallet_account_balance_rpc_positional,
				this, capture_con, _1);
			json_connection->add_method("wallet_account_balance_rpc", bound_positional_method);
			bound_named_method = boost::bind(&CommonApiRpcServer::wallet_account_balance_rpc_named,
				this, capture_con, _1);
			json_connection->add_named_param_method("wallet_account_balance_rpc", bound_named_method);

			// register method wallet_transfer_to_public_account_rpc
			bound_positional_method = boost::bind(&CommonApiRpcServer::wallet_transfer_to_public_account_rpc_positional,
				this, capture_con, _1);
			json_connection->add_method("wallet_transfer_to_public_account_rpc", bound_positional_method);
			bound_named_method = boost::bind(&CommonApiRpcServer::wallet_transfer_to_public_account_rpc_named,
				this, capture_con, _1);
			json_connection->add_named_param_method("wallet_transfer_to_public_account_rpc", bound_named_method);

			// register method wallet_get_account_owner_publickey
			bound_positional_method = boost::bind(&CommonApiRpcServer::wallet_get_account_owner_publickey_positional,
				this, capture_con, _1);
			json_connection->add_method("wallet_get_account_owner_publickey", bound_positional_method);
			bound_named_method = boost::bind(&CommonApiRpcServer::wallet_get_account_owner_publickey_named,
				this, capture_con, _1);
			json_connection->add_named_param_method("wallet_get_account_owner_publickey", bound_named_method);

			// register method wallet_transfer_to_contract
			bound_positional_method = boost::bind(&CommonApiRpcServer::wallet_transfer_to_contract_positional,
				this, capture_con, _1);
			json_connection->add_method("wallet_transfer_to_contract", bound_positional_method);
			bound_named_method = boost::bind(&CommonApiRpcServer::wallet_transfer_to_contract_named,
				this, capture_con, _1);
			json_connection->add_named_param_method("wallet_transfer_to_contract", bound_named_method);

			// register method wallet_transfer_to_contract_testing
			bound_positional_method = boost::bind(&CommonApiRpcServer::wallet_transfer_to_contract_testing_positional,
				this, capture_con, _1);
			json_connection->add_method("wallet_transfer_to_contract_testing", bound_positional_method);
			bound_named_method = boost::bind(&CommonApiRpcServer::wallet_transfer_to_contract_testing_named,
				this, capture_con, _1);
			json_connection->add_named_param_method("wallet_transfer_to_contract_testing", bound_named_method);

			// register method wallet_get_contracts
			bound_positional_method = boost::bind(&CommonApiRpcServer::wallet_get_contracts_positional,
				this, capture_con, _1);
			json_connection->add_method("wallet_get_contracts", bound_positional_method);
			bound_named_method = boost::bind(&CommonApiRpcServer::wallet_get_contracts_named,
				this, capture_con, _1);
			json_connection->add_named_param_method("wallet_get_contracts", bound_named_method);

			// register method wallet_scan_contracts
			bound_positional_method = boost::bind(&CommonApiRpcServer::wallet_scan_contracts_positional,
				this, capture_con, _1);
			json_connection->add_method("wallet_scan_contracts", bound_positional_method);
			bound_named_method = boost::bind(&CommonApiRpcServer::wallet_scan_contracts_named,
				this, capture_con, _1);
			json_connection->add_named_param_method("wallet_scan_contracts", bound_named_method);

           // register method wallet_builder_add_signature
            bound_positional_method = boost::bind(&CommonApiRpcServer::wallet_builder_add_signature_positional,
                this, capture_con, _1);
            json_connection->add_method("wallet_builder_add_signature", bound_positional_method);
            bound_named_method = boost::bind(&CommonApiRpcServer::wallet_builder_add_signature_named, 
                this, capture_con, _1);
            json_connection->add_named_param_method("wallet_builder_add_signature", bound_named_method);

           // register method wallet_builder_file_add_signature
            bound_positional_method = boost::bind(&CommonApiRpcServer::wallet_builder_file_add_signature_positional,
                this, capture_con, _1);
            json_connection->add_method("wallet_builder_file_add_signature", bound_positional_method);
            bound_named_method = boost::bind(&CommonApiRpcServer::wallet_builder_file_add_signature_named, 
                this, capture_con, _1);
            json_connection->add_named_param_method("wallet_builder_file_add_signature", bound_named_method);

           // register method wallet_multisig_deposit
            bound_positional_method = boost::bind(&CommonApiRpcServer::wallet_multisig_deposit_positional,
                this, capture_con, _1);
            json_connection->add_method("wallet_multisig_deposit", bound_positional_method);
            bound_named_method = boost::bind(&CommonApiRpcServer::wallet_multisig_deposit_named, 
                this, capture_con, _1);
            json_connection->add_named_param_method("wallet_multisig_deposit", bound_named_method);

           // register method wallet_import_multisig_account
            bound_positional_method = boost::bind(&CommonApiRpcServer::wallet_import_multisig_account_positional,
                this, capture_con, _1);
            json_connection->add_method("wallet_import_multisig_account", bound_positional_method);
            bound_named_method = boost::bind(&CommonApiRpcServer::wallet_import_multisig_account_named, 
                this, capture_con, _1);
            json_connection->add_named_param_method("wallet_import_multisig_account", bound_named_method);

           // register method wallet_import_multisig_account_by_detail
            bound_positional_method = boost::bind(&CommonApiRpcServer::wallet_import_multisig_account_by_detail_positional,
                this, capture_con, _1);
            json_connection->add_method("wallet_import_multisig_account_by_detail", bound_positional_method);
            bound_named_method = boost::bind(&CommonApiRpcServer::wallet_import_multisig_account_by_detail_named, 
                this, capture_con, _1);
            json_connection->add_named_param_method("wallet_import_multisig_account_by_detail", bound_named_method);

           // register method wallet_multisig_withdraw_start
            bound_positional_method = boost::bind(&CommonApiRpcServer::wallet_multisig_withdraw_start_positional,
                this, capture_con, _1);
            json_connection->add_method("wallet_multisig_withdraw_start", bound_positional_method);
            bound_named_method = boost::bind(&CommonApiRpcServer::wallet_multisig_withdraw_start_named, 
                this, capture_con, _1);
            json_connection->add_named_param_method("wallet_multisig_withdraw_start", bound_named_method);

           // register method wallet_create_multisig_account
            bound_positional_method = boost::bind(&CommonApiRpcServer::wallet_create_multisig_account_positional,
                this, capture_con, _1);
            json_connection->add_method("wallet_create_multisig_account", bound_positional_method);
            bound_named_method = boost::bind(&CommonApiRpcServer::wallet_create_multisig_account_named, 
                this, capture_con, _1);
            json_connection->add_named_param_method("wallet_create_multisig_account", bound_named_method);

           // register method wallet_multisig_account_history
            bound_positional_method = boost::bind(&CommonApiRpcServer::wallet_multisig_account_history_positional,
                this, capture_con, _1);
            json_connection->add_method("wallet_multisig_account_history", bound_positional_method);
            json_connection->add_method("multisig_history", bound_positional_method);
            bound_named_method = boost::bind(&CommonApiRpcServer::wallet_multisig_account_history_named, 
                this, capture_con, _1);
            json_connection->add_named_param_method("wallet_multisig_account_history", bound_named_method);
            json_connection->add_named_param_method("multisig_history", bound_named_method);

           // register method wallet_multisig_account_balance
            bound_positional_method = boost::bind(&CommonApiRpcServer::wallet_multisig_account_balance_positional,
                this, capture_con, _1);
            json_connection->add_method("wallet_multisig_account_balance", bound_positional_method);
            json_connection->add_method("multisig_balance", bound_positional_method);
            bound_named_method = boost::bind(&CommonApiRpcServer::wallet_multisig_account_balance_named, 
                this, capture_con, _1);
            json_connection->add_named_param_method("wallet_multisig_account_balance", bound_named_method);
            json_connection->add_named_param_method("multisig_balance", bound_named_method);

           // register method wallet_builder_get_multisig_detail
            bound_positional_method = boost::bind(&CommonApiRpcServer::wallet_builder_get_multisig_detail_positional,
                this, capture_con, _1);
            json_connection->add_method("wallet_builder_get_multisig_detail", bound_positional_method);
            bound_named_method = boost::bind(&CommonApiRpcServer::wallet_builder_get_multisig_detail_named, 
                this, capture_con, _1);
            json_connection->add_named_param_method("wallet_builder_get_multisig_detail", bound_named_method);

           // register method wallet_builder_file_get_multisig_detail
            bound_positional_method = boost::bind(&CommonApiRpcServer::wallet_builder_file_get_multisig_detail_positional,
                this, capture_con, _1);
            json_connection->add_method("wallet_builder_file_get_multisig_detail", bound_positional_method);
            bound_named_method = boost::bind(&CommonApiRpcServer::wallet_builder_file_get_multisig_detail_named, 
                this, capture_con, _1);
            json_connection->add_named_param_method("wallet_builder_file_get_multisig_detail", bound_named_method);

           // register method about
			bound_positional_method = boost::bind(&CommonApiRpcServer::about_positional,
				this, capture_con, _1);
			json_connection->add_method("about", bound_positional_method);
			bound_named_method = boost::bind(&CommonApiRpcServer::about_named,
				this, capture_con, _1);
			json_connection->add_named_param_method("about", bound_named_method);

			// register method get_info
			bound_positional_method = boost::bind(&CommonApiRpcServer::get_info_positional,
				this, capture_con, _1);
			json_connection->add_method("get_info", bound_positional_method);
			json_connection->add_method("getinfo", bound_positional_method);
			json_connection->add_method("info", bound_positional_method);
			bound_named_method = boost::bind(&CommonApiRpcServer::get_info_named,
				this, capture_con, _1);
			json_connection->add_named_param_method("get_info", bound_named_method);
			json_connection->add_named_param_method("getinfo", bound_named_method);
			json_connection->add_named_param_method("info", bound_named_method);

			// register method stop
			bound_positional_method = boost::bind(&CommonApiRpcServer::stop_positional,
				this, capture_con, _1);
			json_connection->add_method("stop", bound_positional_method);
			json_connection->add_method("quit", bound_positional_method);
			json_connection->add_method("exit", bound_positional_method);
			bound_named_method = boost::bind(&CommonApiRpcServer::stop_named,
				this, capture_con, _1);
			json_connection->add_named_param_method("stop", bound_named_method);
			json_connection->add_named_param_method("quit", bound_named_method);
			json_connection->add_named_param_method("exit", bound_named_method);

			// register method help
			bound_positional_method = boost::bind(&CommonApiRpcServer::help_positional,
				this, capture_con, _1);
			json_connection->add_method("help", bound_positional_method);
			json_connection->add_method("h", bound_positional_method);
			bound_named_method = boost::bind(&CommonApiRpcServer::help_named,
				this, capture_con, _1);
			json_connection->add_named_param_method("help", bound_named_method);
			json_connection->add_named_param_method("h", bound_named_method);

			// register method validate_address
			bound_positional_method = boost::bind(&CommonApiRpcServer::validate_address_positional,
				this, capture_con, _1);
			json_connection->add_method("validate_address", bound_positional_method);
			json_connection->add_method("validateaddress", bound_positional_method);
			bound_named_method = boost::bind(&CommonApiRpcServer::validate_address_named,
				this, capture_con, _1);
			json_connection->add_named_param_method("validate_address", bound_named_method);
			json_connection->add_named_param_method("validateaddress", bound_named_method);

			// register method execute_command_line
			bound_positional_method = boost::bind(&CommonApiRpcServer::execute_command_line_positional,
				this, capture_con, _1);
			json_connection->add_method("execute_command_line", bound_positional_method);
			bound_named_method = boost::bind(&CommonApiRpcServer::execute_command_line_named,
				this, capture_con, _1);
			json_connection->add_named_param_method("execute_command_line", bound_named_method);

			// register method execute_script
			bound_positional_method = boost::bind(&CommonApiRpcServer::execute_script_positional,
				this, capture_con, _1);
			json_connection->add_method("execute_script", bound_positional_method);
			bound_named_method = boost::bind(&CommonApiRpcServer::execute_script_named,
				this, capture_con, _1);
			json_connection->add_named_param_method("execute_script", bound_named_method);

			// register method batch
			bound_positional_method = boost::bind(&CommonApiRpcServer::batch_positional,
				this, capture_con, _1);
			json_connection->add_method("batch", bound_positional_method);
			bound_named_method = boost::bind(&CommonApiRpcServer::batch_named,
				this, capture_con, _1);
			json_connection->add_named_param_method("batch", bound_named_method);

			// register method batch_authenticated
			bound_positional_method = boost::bind(&CommonApiRpcServer::batch_authenticated_positional,
				this, capture_con, _1);
			json_connection->add_method("batch_authenticated", bound_positional_method);
			bound_named_method = boost::bind(&CommonApiRpcServer::batch_authenticated_named,
				this, capture_con, _1);
			json_connection->add_named_param_method("batch_authenticated", bound_named_method);

			// register method builder_finalize_and_sign
			bound_positional_method = boost::bind(&CommonApiRpcServer::builder_finalize_and_sign_positional,
				this, capture_con, _1);
			json_connection->add_method("builder_finalize_and_sign", bound_positional_method);
			bound_named_method = boost::bind(&CommonApiRpcServer::builder_finalize_and_sign_named,
				this, capture_con, _1);
			json_connection->add_named_param_method("builder_finalize_and_sign", bound_named_method);

			// register method meta_help
			bound_positional_method = boost::bind(&CommonApiRpcServer::meta_help_positional,
				this, capture_con, _1);
			json_connection->add_method("meta_help", bound_positional_method);
			bound_named_method = boost::bind(&CommonApiRpcServer::meta_help_named,
				this, capture_con, _1);
			json_connection->add_named_param_method("meta_help", bound_named_method);

			// register method rpc_set_username
			bound_positional_method = boost::bind(&CommonApiRpcServer::rpc_set_username_positional,
				this, capture_con, _1);
			json_connection->add_method("rpc_set_username", bound_positional_method);
			bound_named_method = boost::bind(&CommonApiRpcServer::rpc_set_username_named,
				this, capture_con, _1);
			json_connection->add_named_param_method("rpc_set_username", bound_named_method);

			// register method rpc_set_password
			bound_positional_method = boost::bind(&CommonApiRpcServer::rpc_set_password_positional,
				this, capture_con, _1);
			json_connection->add_method("rpc_set_password", bound_positional_method);
			bound_named_method = boost::bind(&CommonApiRpcServer::rpc_set_password_named,
				this, capture_con, _1);
			json_connection->add_named_param_method("rpc_set_password", bound_named_method);

			// register method rpc_start_server
			bound_positional_method = boost::bind(&CommonApiRpcServer::rpc_start_server_positional,
				this, capture_con, _1);
			json_connection->add_method("rpc_start_server", bound_positional_method);
			bound_named_method = boost::bind(&CommonApiRpcServer::rpc_start_server_named,
				this, capture_con, _1);
			json_connection->add_named_param_method("rpc_start_server", bound_named_method);

			// register method http_start_server
			bound_positional_method = boost::bind(&CommonApiRpcServer::http_start_server_positional,
				this, capture_con, _1);
			json_connection->add_method("http_start_server", bound_positional_method);
			bound_named_method = boost::bind(&CommonApiRpcServer::http_start_server_named,
				this, capture_con, _1);
			json_connection->add_named_param_method("http_start_server", bound_named_method);

			// register method ntp_update_time
			bound_positional_method = boost::bind(&CommonApiRpcServer::ntp_update_time_positional,
				this, capture_con, _1);
			json_connection->add_method("ntp_update_time", bound_positional_method);
			bound_named_method = boost::bind(&CommonApiRpcServer::ntp_update_time_named,
				this, capture_con, _1);
			json_connection->add_named_param_method("ntp_update_time", bound_named_method);

			// register method disk_usage
			bound_positional_method = boost::bind(&CommonApiRpcServer::disk_usage_positional,
				this, capture_con, _1);
			json_connection->add_method("disk_usage", bound_positional_method);
			json_connection->add_method("size", bound_positional_method);
			json_connection->add_method("sizes", bound_positional_method);
			json_connection->add_method("usage", bound_positional_method);
			json_connection->add_method("diskusage", bound_positional_method);
			bound_named_method = boost::bind(&CommonApiRpcServer::disk_usage_named,
				this, capture_con, _1);
			json_connection->add_named_param_method("disk_usage", bound_named_method);
			json_connection->add_named_param_method("size", bound_named_method);
			json_connection->add_named_param_method("sizes", bound_named_method);
			json_connection->add_named_param_method("usage", bound_named_method);
            json_connection->add_named_param_method("diskusage", bound_named_method);

           // register method contract_compile
            bound_positional_method = boost::bind(&CommonApiRpcServer::contract_compile_positional,
				this, capture_con, _1);
			json_connection->add_method("contract_compile", bound_positional_method);
			bound_named_method = boost::bind(&CommonApiRpcServer::contract_compile_named,
				this, capture_con, _1);
			json_connection->add_named_param_method("contract_compile", bound_named_method);

			// register method contract_register
			bound_positional_method = boost::bind(&CommonApiRpcServer::contract_register_positional,
				this, capture_con, _1);
			json_connection->add_method("contract_register", bound_positional_method);
			bound_named_method = boost::bind(&CommonApiRpcServer::contract_register_named,
				this, capture_con, _1);
			json_connection->add_named_param_method("contract_register", bound_named_method);

			// register method contract_register_testing
			bound_positional_method = boost::bind(&CommonApiRpcServer::contract_register_testing_positional,
				this, capture_con, _1);
			json_connection->add_method("contract_register_testing", bound_positional_method);
			bound_named_method = boost::bind(&CommonApiRpcServer::contract_register_testing_named,
				this, capture_con, _1);
			json_connection->add_named_param_method("contract_register_testing", bound_named_method);

			// register method contract_upgrade
			bound_positional_method = boost::bind(&CommonApiRpcServer::contract_upgrade_positional,
				this, capture_con, _1);
			json_connection->add_method("contract_upgrade", bound_positional_method);
			bound_named_method = boost::bind(&CommonApiRpcServer::contract_upgrade_named,
				this, capture_con, _1);
			json_connection->add_named_param_method("contract_upgrade", bound_named_method);

			// register method contract_upgrade_testing
			bound_positional_method = boost::bind(&CommonApiRpcServer::contract_upgrade_testing_positional,
				this, capture_con, _1);
			json_connection->add_method("contract_upgrade_testing", bound_positional_method);
			bound_named_method = boost::bind(&CommonApiRpcServer::contract_upgrade_testing_named,
				this, capture_con, _1);
			json_connection->add_named_param_method("contract_upgrade_testing", bound_named_method);

			// register method contract_destroy
			bound_positional_method = boost::bind(&CommonApiRpcServer::contract_destroy_positional,
				this, capture_con, _1);
			json_connection->add_method("contract_destroy", bound_positional_method);
			bound_named_method = boost::bind(&CommonApiRpcServer::contract_destroy_named,
				this, capture_con, _1);
			json_connection->add_named_param_method("contract_destroy", bound_named_method);

			// register method contract_destroy_testing
			bound_positional_method = boost::bind(&CommonApiRpcServer::contract_destroy_testing_positional,
				this, capture_con, _1);
			json_connection->add_method("contract_destroy_testing", bound_positional_method);
			bound_named_method = boost::bind(&CommonApiRpcServer::contract_destroy_testing_named,
				this, capture_con, _1);
			json_connection->add_named_param_method("contract_destroy_testing", bound_named_method);

			// register method contract_call
			bound_positional_method = boost::bind(&CommonApiRpcServer::contract_call_positional,
				this, capture_con, _1);
			json_connection->add_method("contract_call", bound_positional_method);
			bound_named_method = boost::bind(&CommonApiRpcServer::contract_call_named,
				this, capture_con, _1);
			json_connection->add_named_param_method("contract_call", bound_named_method);

			// register method contract_get_info
			bound_positional_method = boost::bind(&CommonApiRpcServer::contract_get_info_positional,
				this, capture_con, _1);
			json_connection->add_method("contract_get_info", bound_positional_method);
			bound_named_method = boost::bind(&CommonApiRpcServer::contract_get_info_named,
				this, capture_con, _1);
			json_connection->add_named_param_method("contract_get_info", bound_named_method);

			// register method contract_get_balance
			bound_positional_method = boost::bind(&CommonApiRpcServer::contract_get_balance_positional,
				this, capture_con, _1);
			json_connection->add_method("contract_get_balance", bound_positional_method);
			bound_named_method = boost::bind(&CommonApiRpcServer::contract_get_balance_named,
				this, capture_con, _1);
			json_connection->add_named_param_method("contract_get_balance", bound_named_method);

			// register method contract_call_testing
			bound_positional_method = boost::bind(&CommonApiRpcServer::contract_call_testing_positional,
				this, capture_con, _1);
			json_connection->add_method("contract_call_testing", bound_positional_method);
			bound_named_method = boost::bind(&CommonApiRpcServer::contract_call_testing_named,
				this, capture_con, _1);
			json_connection->add_named_param_method("contract_call_testing", bound_named_method);

			// register method contract_call_offline
			bound_positional_method = boost::bind(&CommonApiRpcServer::contract_call_offline_positional,
				this, capture_con, _1);
			json_connection->add_method("contract_call_offline", bound_positional_method);
			bound_named_method = boost::bind(&CommonApiRpcServer::contract_call_offline_named,
				this, capture_con, _1);
			json_connection->add_named_param_method("contract_call_offline", bound_named_method);

			// register method contract_load_to_file
			bound_positional_method = boost::bind(&CommonApiRpcServer::contract_load_to_file_positional,
				this, capture_con, _1);
			json_connection->add_method("contract_load_to_file", bound_positional_method);
			bound_named_method = boost::bind(&CommonApiRpcServer::contract_load_to_file_named,
				this, capture_con, _1);
			json_connection->add_named_param_method("contract_load_to_file", bound_named_method);

			// register method get_result_trx_id
			bound_positional_method = boost::bind(&CommonApiRpcServer::get_result_trx_id_positional,
				this, capture_con, _1);
			json_connection->add_method("get_result_trx_id", bound_positional_method);
			bound_named_method = boost::bind(&CommonApiRpcServer::get_result_trx_id_named,
				this, capture_con, _1);
			json_connection->add_named_param_method("get_result_trx_id", bound_named_method);

			// register method get_request_trx_id
			bound_positional_method = boost::bind(&CommonApiRpcServer::get_request_trx_id_positional,
				this, capture_con, _1);
			json_connection->add_method("get_request_trx_id", bound_positional_method);
			bound_named_method = boost::bind(&CommonApiRpcServer::get_request_trx_id_named,
				this, capture_con, _1);
			json_connection->add_named_param_method("get_request_trx_id", bound_named_method);

			// register method simulator_open
			bound_positional_method = boost::bind(&CommonApiRpcServer::simulator_open_positional,
				this, capture_con, _1);
			json_connection->add_method("simulator_open", bound_positional_method);
			bound_named_method = boost::bind(&CommonApiRpcServer::simulator_open_named,
				this, capture_con, _1);
			json_connection->add_named_param_method("simulator_open", bound_named_method);

			// register method simulator_close
			bound_positional_method = boost::bind(&CommonApiRpcServer::simulator_close_positional,
				this, capture_con, _1);
			json_connection->add_method("simulator_close", bound_positional_method);
			bound_named_method = boost::bind(&CommonApiRpcServer::simulator_close_named,
				this, capture_con, _1);
			json_connection->add_named_param_method("simulator_close", bound_named_method);

			// register method simulator_contract_register
			bound_positional_method = boost::bind(&CommonApiRpcServer::simulator_contract_register_positional,
				this, capture_con, _1);
			json_connection->add_method("simulator_contract_register", bound_positional_method);
			bound_named_method = boost::bind(&CommonApiRpcServer::simulator_contract_register_named,
				this, capture_con, _1);
			json_connection->add_named_param_method("simulator_contract_register", bound_named_method);

			// register method simulator_contract_call
			bound_positional_method = boost::bind(&CommonApiRpcServer::simulator_contract_call_positional,
				this, capture_con, _1);
			json_connection->add_method("simulator_contract_call", bound_positional_method);
			bound_named_method = boost::bind(&CommonApiRpcServer::simulator_contract_call_named,
				this, capture_con, _1);
			json_connection->add_named_param_method("simulator_contract_call", bound_named_method);

			// register method simulator_contract_upgrade
			bound_positional_method = boost::bind(&CommonApiRpcServer::simulator_contract_upgrade_positional,
				this, capture_con, _1);
			json_connection->add_method("simulator_contract_upgrade", bound_positional_method);
			bound_named_method = boost::bind(&CommonApiRpcServer::simulator_contract_upgrade_named,
				this, capture_con, _1);
			json_connection->add_named_param_method("simulator_contract_upgrade", bound_named_method);

			// register method simulator_contract_upgrade_testing
			bound_positional_method = boost::bind(&CommonApiRpcServer::simulator_contract_upgrade_testing_positional,
				this, capture_con, _1);
			json_connection->add_method("simulator_contract_upgrade_testing", bound_positional_method);
			bound_named_method = boost::bind(&CommonApiRpcServer::simulator_contract_upgrade_testing_named,
				this, capture_con, _1);
			json_connection->add_named_param_method("simulator_contract_upgrade_testing", bound_named_method);

			// register method simulator_contract_destroy
			bound_positional_method = boost::bind(&CommonApiRpcServer::simulator_contract_destroy_positional,
				this, capture_con, _1);
			json_connection->add_method("simulator_contract_destroy", bound_positional_method);
			bound_named_method = boost::bind(&CommonApiRpcServer::simulator_contract_destroy_named,
				this, capture_con, _1);
			json_connection->add_named_param_method("simulator_contract_destroy", bound_named_method);

			// register method simulator_contract_destroy_testing
			bound_positional_method = boost::bind(&CommonApiRpcServer::simulator_contract_destroy_testing_positional,
				this, capture_con, _1);
			json_connection->add_method("simulator_contract_destroy_testing", bound_positional_method);
			bound_named_method = boost::bind(&CommonApiRpcServer::simulator_contract_destroy_testing_named,
				this, capture_con, _1);
			json_connection->add_named_param_method("simulator_contract_destroy_testing", bound_named_method);

			// register method simulator_contract_get_info
			bound_positional_method = boost::bind(&CommonApiRpcServer::simulator_contract_get_info_positional,
				this, capture_con, _1);
			json_connection->add_method("simulator_contract_get_info", bound_positional_method);
			bound_named_method = boost::bind(&CommonApiRpcServer::simulator_contract_get_info_named,
				this, capture_con, _1);
			json_connection->add_named_param_method("simulator_contract_get_info", bound_named_method);

			// register method simulator_contract_get_balance
			bound_positional_method = boost::bind(&CommonApiRpcServer::simulator_contract_get_balance_positional,
				this, capture_con, _1);
			json_connection->add_method("simulator_contract_get_balance", bound_positional_method);
			bound_named_method = boost::bind(&CommonApiRpcServer::simulator_contract_get_balance_named,
				this, capture_con, _1);
			json_connection->add_named_param_method("simulator_contract_get_balance", bound_named_method);

			// register method simulator_transfer_to_contract
			bound_positional_method = boost::bind(&CommonApiRpcServer::simulator_transfer_to_contract_positional,
				this, capture_con, _1);
			json_connection->add_method("simulator_transfer_to_contract", bound_positional_method);
			bound_named_method = boost::bind(&CommonApiRpcServer::simulator_transfer_to_contract_named,
				this, capture_con, _1);
			json_connection->add_named_param_method("simulator_transfer_to_contract", bound_named_method);

			// register method simulator_account_balance
			bound_positional_method = boost::bind(&CommonApiRpcServer::simulator_account_balance_positional,
				this, capture_con, _1);
			json_connection->add_method("simulator_account_balance", bound_positional_method);
			bound_named_method = boost::bind(&CommonApiRpcServer::simulator_account_balance_named,
				this, capture_con, _1);
			json_connection->add_named_param_method("simulator_account_balance", bound_named_method);

			// register method simulator_contract_compile
			bound_positional_method = boost::bind(&CommonApiRpcServer::simulator_contract_compile_positional,
				this, capture_con, _1);
			json_connection->add_method("simulator_contract_compile", bound_positional_method);
			bound_named_method = boost::bind(&CommonApiRpcServer::simulator_contract_compile_named,
				this, capture_con, _1);
			json_connection->add_named_param_method("simulator_contract_compile", bound_named_method);

			// register method simulator_contract_load_to_file
			bound_positional_method = boost::bind(&CommonApiRpcServer::simulator_contract_load_to_file_positional,
				this, capture_con, _1);
			json_connection->add_method("simulator_contract_load_to_file", bound_positional_method);
			bound_named_method = boost::bind(&CommonApiRpcServer::simulator_contract_load_to_file_named,
				this, capture_con, _1);
			json_connection->add_named_param_method("simulator_contract_load_to_file", bound_named_method);

			// register method simulator_contract_register_testing
			bound_positional_method = boost::bind(&CommonApiRpcServer::simulator_contract_register_testing_positional,
				this, capture_con, _1);
			json_connection->add_method("simulator_contract_register_testing", bound_positional_method);
			bound_named_method = boost::bind(&CommonApiRpcServer::simulator_contract_register_testing_named,
				this, capture_con, _1);
			json_connection->add_named_param_method("simulator_contract_register_testing", bound_named_method);

			// register method simulator_contract_call_testing
			bound_positional_method = boost::bind(&CommonApiRpcServer::simulator_contract_call_testing_positional,
				this, capture_con, _1);
			json_connection->add_method("simulator_contract_call_testing", bound_positional_method);
			bound_named_method = boost::bind(&CommonApiRpcServer::simulator_contract_call_testing_named,
				this, capture_con, _1);
			json_connection->add_named_param_method("simulator_contract_call_testing", bound_named_method);

			// register method simulator_transfer_to_contract_testing
			bound_positional_method = boost::bind(&CommonApiRpcServer::simulator_transfer_to_contract_testing_positional,
				this, capture_con, _1);
			json_connection->add_method("simulator_transfer_to_contract_testing", bound_positional_method);
			bound_named_method = boost::bind(&CommonApiRpcServer::simulator_transfer_to_contract_testing_named,
				this, capture_con, _1);
			json_connection->add_named_param_method("simulator_transfer_to_contract_testing", bound_named_method);

			// register method simulator_list_my_addresses
			bound_positional_method = boost::bind(&CommonApiRpcServer::simulator_list_my_addresses_positional,
				this, capture_con, _1);
			json_connection->add_method("simulator_list_my_addresses", bound_positional_method);
			bound_named_method = boost::bind(&CommonApiRpcServer::simulator_list_my_addresses_named,
				this, capture_con, _1);
			json_connection->add_named_param_method("simulator_list_my_addresses", bound_named_method);

			// register method get_contract_registered_in_transaction
			bound_positional_method = boost::bind(&CommonApiRpcServer::get_contract_registered_in_transaction_positional,
				this, capture_con, _1);
			json_connection->add_method("get_contract_registered_in_transaction", bound_positional_method);
			bound_named_method = boost::bind(&CommonApiRpcServer::get_contract_registered_in_transaction_named,
				this, capture_con, _1);
			json_connection->add_named_param_method("get_contract_registered_in_transaction", bound_named_method);

			// register method get_transaction_id_contract_registered
			bound_positional_method = boost::bind(&CommonApiRpcServer::get_transaction_id_contract_registered_positional,
				this, capture_con, _1);
			json_connection->add_method("get_transaction_id_contract_registered", bound_positional_method);
			bound_named_method = boost::bind(&CommonApiRpcServer::get_transaction_id_contract_registered_named,
				this, capture_con, _1);
			json_connection->add_named_param_method("get_transaction_id_contract_registered", bound_named_method);

			// register method contract_get_info_from_gpc_file
			bound_positional_method = boost::bind(&CommonApiRpcServer::contract_get_info_from_gpc_file_positional,
				this, capture_con, _1);
			json_connection->add_method("contract_get_info_from_gpc_file", bound_positional_method);
			bound_named_method = boost::bind(&CommonApiRpcServer::contract_get_info_from_gpc_file_named,
				this, capture_con, _1);
			json_connection->add_named_param_method("contract_get_info_from_gpc_file", bound_named_method);

			// register method script_compile
			bound_positional_method = boost::bind(&CommonApiRpcServer::script_compile_positional,
				this, capture_con, _1);
			json_connection->add_method("script_compile", bound_positional_method);
			bound_named_method = boost::bind(&CommonApiRpcServer::script_compile_named,
				this, capture_con, _1);
			json_connection->add_named_param_method("script_compile", bound_named_method);

			// register method script_add
			bound_positional_method = boost::bind(&CommonApiRpcServer::script_add_positional,
				this, capture_con, _1);
			json_connection->add_method("script_add", bound_positional_method);
			bound_named_method = boost::bind(&CommonApiRpcServer::script_add_named,
				this, capture_con, _1);
			json_connection->add_named_param_method("script_add", bound_named_method);

			// register method script_remove
			bound_positional_method = boost::bind(&CommonApiRpcServer::script_remove_positional,
				this, capture_con, _1);
			json_connection->add_method("script_remove", bound_positional_method);
			bound_named_method = boost::bind(&CommonApiRpcServer::script_remove_named,
				this, capture_con, _1);
			json_connection->add_named_param_method("script_remove", bound_named_method);

			// register method script_get_info
			bound_positional_method = boost::bind(&CommonApiRpcServer::script_get_info_positional,
				this, capture_con, _1);
			json_connection->add_method("script_get_info", bound_positional_method);
			bound_named_method = boost::bind(&CommonApiRpcServer::script_get_info_named,
				this, capture_con, _1);
			json_connection->add_named_param_method("script_get_info", bound_named_method);

			// register method scripts_list
			bound_positional_method = boost::bind(&CommonApiRpcServer::scripts_list_positional,
				this, capture_con, _1);
			json_connection->add_method("scripts_list", bound_positional_method);
			bound_named_method = boost::bind(&CommonApiRpcServer::scripts_list_named,
				this, capture_con, _1);
			json_connection->add_named_param_method("scripts_list", bound_named_method);

			// register method script_disable
			bound_positional_method = boost::bind(&CommonApiRpcServer::script_disable_positional,
				this, capture_con, _1);
			json_connection->add_method("script_disable", bound_positional_method);
			bound_named_method = boost::bind(&CommonApiRpcServer::script_disable_named,
				this, capture_con, _1);
			json_connection->add_named_param_method("script_disable", bound_named_method);

			// register method script_enable
			bound_positional_method = boost::bind(&CommonApiRpcServer::script_enable_positional,
				this, capture_con, _1);
			json_connection->add_method("script_enable", bound_positional_method);
			bound_named_method = boost::bind(&CommonApiRpcServer::script_enable_named,
				this, capture_con, _1);
			json_connection->add_named_param_method("script_enable", bound_named_method);

			// register method script_import_to_db
			bound_positional_method = boost::bind(&CommonApiRpcServer::script_import_to_db_positional,
				this, capture_con, _1);
			json_connection->add_method("script_import_to_db", bound_positional_method);
			bound_named_method = boost::bind(&CommonApiRpcServer::script_import_to_db_named,
				this, capture_con, _1);
			json_connection->add_named_param_method("script_import_to_db", bound_named_method);

			// register method script_export_from_db
			bound_positional_method = boost::bind(&CommonApiRpcServer::script_export_from_db_positional,
				this, capture_con, _1);
			json_connection->add_method("script_export_from_db", bound_positional_method);
			bound_named_method = boost::bind(&CommonApiRpcServer::script_export_from_db_named,
				this, capture_con, _1);
			json_connection->add_named_param_method("script_export_from_db", bound_named_method);

			// register method script_get_events_bound
			bound_positional_method = boost::bind(&CommonApiRpcServer::script_get_events_bound_positional,
				this, capture_con, _1);
			json_connection->add_method("script_get_events_bound", bound_positional_method);
			bound_named_method = boost::bind(&CommonApiRpcServer::script_get_events_bound_named,
				this, capture_con, _1);
			json_connection->add_named_param_method("script_get_events_bound", bound_named_method);

			// register method script_list_event_handler
			bound_positional_method = boost::bind(&CommonApiRpcServer::script_list_event_handler_positional,
				this, capture_con, _1);
			json_connection->add_method("script_list_event_handler", bound_positional_method);
			bound_named_method = boost::bind(&CommonApiRpcServer::script_list_event_handler_named,
				this, capture_con, _1);
			json_connection->add_named_param_method("script_list_event_handler", bound_named_method);

			// register method script_add_event_handler
			bound_positional_method = boost::bind(&CommonApiRpcServer::script_add_event_handler_positional,
				this, capture_con, _1);
			json_connection->add_method("script_add_event_handler", bound_positional_method);
			bound_named_method = boost::bind(&CommonApiRpcServer::script_add_event_handler_named,
				this, capture_con, _1);
			json_connection->add_named_param_method("script_add_event_handler", bound_named_method);

			// register method script_delete_event_handler
			bound_positional_method = boost::bind(&CommonApiRpcServer::script_delete_event_handler_positional,
				this, capture_con, _1);
			json_connection->add_method("script_delete_event_handler", bound_positional_method);
			bound_named_method = boost::bind(&CommonApiRpcServer::script_delete_event_handler_named,
				this, capture_con, _1);
			json_connection->add_named_param_method("script_delete_event_handler", bound_named_method);

           // register method proposal_apply_for_privilege_admin
            bound_positional_method = boost::bind(&CommonApiRpcServer::proposal_apply_for_privilege_admin_positional,
                this, capture_con, _1);
            json_connection->add_method("proposal_apply_for_privilege_admin", bound_positional_method);
            bound_named_method = boost::bind(&CommonApiRpcServer::proposal_apply_for_privilege_admin_named, 
                this, capture_con, _1);
            json_connection->add_named_param_method("proposal_apply_for_privilege_admin", bound_named_method);

           // register method proposal_revoke_privilege_admin
            bound_positional_method = boost::bind(&CommonApiRpcServer::proposal_revoke_privilege_admin_positional,
                this, capture_con, _1);
            json_connection->add_method("proposal_revoke_privilege_admin", bound_positional_method);
            bound_named_method = boost::bind(&CommonApiRpcServer::proposal_revoke_privilege_admin_named, 
                this, capture_con, _1);
            json_connection->add_named_param_method("proposal_revoke_privilege_admin", bound_named_method);

           // register method proposal_approve
            bound_positional_method = boost::bind(&CommonApiRpcServer::proposal_approve_positional,
                this, capture_con, _1);
            json_connection->add_method("proposal_approve", bound_positional_method);
            bound_named_method = boost::bind(&CommonApiRpcServer::proposal_approve_named, 
                this, capture_con, _1);
            json_connection->add_named_param_method("proposal_approve", bound_named_method);

           // register method proposal_get_info
            bound_positional_method = boost::bind(&CommonApiRpcServer::proposal_get_info_positional,
                this, capture_con, _1);
            json_connection->add_method("proposal_get_info", bound_positional_method);
            bound_named_method = boost::bind(&CommonApiRpcServer::proposal_get_info_named, 
                this, capture_con, _1);
            json_connection->add_named_param_method("proposal_get_info", bound_named_method);

           // register method appoint_general_admin
            bound_positional_method = boost::bind(&CommonApiRpcServer::appoint_general_admin_positional,
                this, capture_con, _1);
            json_connection->add_method("appoint_general_admin", bound_positional_method);
            bound_named_method = boost::bind(&CommonApiRpcServer::appoint_general_admin_named, 
                this, capture_con, _1);
            json_connection->add_named_param_method("appoint_general_admin", bound_named_method);

           // register method revoke_general_admin
            bound_positional_method = boost::bind(&CommonApiRpcServer::revoke_general_admin_positional,
                this, capture_con, _1);
            json_connection->add_method("revoke_general_admin", bound_positional_method);
            bound_named_method = boost::bind(&CommonApiRpcServer::revoke_general_admin_named, 
                this, capture_con, _1);
            json_connection->add_named_param_method("revoke_general_admin", bound_named_method);

           // register method get_all_privilege_admin
            bound_positional_method = boost::bind(&CommonApiRpcServer::get_all_privilege_admin_positional,
                this, capture_con, _1);
            json_connection->add_method("get_all_privilege_admin", bound_positional_method);
            bound_named_method = boost::bind(&CommonApiRpcServer::get_all_privilege_admin_named, 
                this, capture_con, _1);
            json_connection->add_named_param_method("get_all_privilege_admin", bound_named_method);

           // register method get_all_general_admin
            bound_positional_method = boost::bind(&CommonApiRpcServer::get_all_general_admin_positional,
                this, capture_con, _1);
            json_connection->add_method("get_all_general_admin", bound_positional_method);
            bound_named_method = boost::bind(&CommonApiRpcServer::get_all_general_admin_named, 
                this, capture_con, _1);
            json_connection->add_named_param_method("get_all_general_admin", bound_named_method);

        }

        void CommonApiRpcServer::register_common_api_method_metadata()
        {
            {
                // register method blockchain_get_info
                cdcchain::api::MethodData blockchain_get_info_method_metadata{ "blockchain_get_info", nullptr,
                    /* description */ "Returns current blockchain information and parameters",
                    /* returns */ "json_object",
                    /* params: */{                    },
                    /* prerequisites */ (cdcchain::api::MethodPrerequisites) 0,
                    /* detailed description */ "Returns current blockchain information and parameters\n\nParameters:\n  (none)\n\nReturns:\n  json_object\n",
                    /* aliases */ {"getconfig", "get_config", "config", "blockchain_get_config"}, true};
                store_method_metadata(blockchain_get_info_method_metadata);
            }

            {
                // register method blockchain_generate_snapshot
                cdcchain::api::MethodData blockchain_generate_snapshot_method_metadata{ "blockchain_generate_snapshot", nullptr,
                    /* description */ "Save snapshot of current base asset balances to specified file",
                    /* returns */ "void",
                    /* params: */{
                        {"filename", "string", cdcchain::api::required_positional, fc::ovariant()}
                          },
                    /* prerequisites */ (cdcchain::api::MethodPrerequisites) 0,
                    /* detailed description */ "Save snapshot of current base asset balances to specified file\n\nParameters:\n  filename (string, required): filename to save snapshot to\n\nReturns:\n  void\n",
                    /* aliases */ {}, false};
                store_method_metadata(blockchain_generate_snapshot_method_metadata);
            }

            {
                // register method blockchain_get_cdc_account_balance_entry
                cdcchain::api::MethodData blockchain_get_cdc_account_balance_entry_method_metadata{ "blockchain_get_cdc_account_balance_entry", nullptr,
                    /* description */ "fetch all CdcTrxidBalance from block where blocknum of the block lower than block_num or equal to block_num.",
                    /* returns */ "vector<cdc_trxid_balance>",
                    /* params: */{
                        {"block_num", "uint32_t", cdcchain::api::required_positional, fc::ovariant()}
                          },
                    /* prerequisites */ (cdcchain::api::MethodPrerequisites) 0,
                    /* detailed description */ "fetch all CdcTrxidBalance from block where blocknum of the block lower than block_num or equal to block_num.\n\nParameters:\n  block_num (uint32_t, required): \n\nReturns:\n  vector<cdc_trxid_balance>\n",
                    /* aliases */ {}, false};
                store_method_metadata(blockchain_get_cdc_account_balance_entry_method_metadata);
            }

            {
                // register method blockchain_generate_issuance_map
                cdcchain::api::MethodData blockchain_generate_issuance_map_method_metadata{ "blockchain_generate_issuance_map", nullptr,
                    /* description */ "A utility to help verify UIA distribution. Returns a snapshot map of all issuances for a particular UIA.",
                    /* returns */ "void",
                    /* params: */{
                        {"symbol", "string", cdcchain::api::required_positional, fc::ovariant()},
                        {"filename", "string", cdcchain::api::required_positional, fc::ovariant()}
                          },
                    /* prerequisites */ (cdcchain::api::MethodPrerequisites) 0,
                    /* detailed description */ "A utility to help verify UIA distribution. Returns a snapshot map of all issuances for a particular UIA.\n\nParameters:\n  symbol (string, required): the UIA for which to compute issuance map\n  filename (string, required): filename to save snapshot to\n\nReturns:\n  void\n",
                    /* aliases */ {}, false};
                store_method_metadata(blockchain_generate_issuance_map_method_metadata);
            }

            {
                // register method blockchain_calculate_supply
                cdcchain::api::MethodData blockchain_calculate_supply_method_metadata{ "blockchain_calculate_supply", nullptr,
                    /* description */ "Calculate the total supply of an asset from the current blockchain database state",
                    /* returns */ "asset",
                    /* params: */{
                        {"asset", "string", cdcchain::api::required_positional, fc::ovariant()}
                          },
                    /* prerequisites */ (cdcchain::api::MethodPrerequisites) 0,
                    /* detailed description */ "Calculate the total supply of an asset from the current blockchain database state\n\nParameters:\n  asset (string, required): asset ticker symbol or ID to calculate supply for\n\nReturns:\n  asset\n",
                    /* aliases */ {"supply", "calculate_supply"}, true};
                store_method_metadata(blockchain_calculate_supply_method_metadata);
            }

            {
                // register method blockchain_is_synced
                cdcchain::api::MethodData blockchain_is_synced_method_metadata{ "blockchain_is_synced", nullptr,
                    /* description */ "Returns true if the local blockchain is synced with the network; false otherwise",
                    /* returns */ "bool",
                    /* params: */{                    },
                    /* prerequisites */ (cdcchain::api::MethodPrerequisites) 0,
                    /* detailed description */ "Returns true if the local blockchain is synced with the network; false otherwise\n\nParameters:\n  (none)\n\nReturns:\n  bool\n",
                    /* aliases */ {"synced"}, false};
                store_method_metadata(blockchain_is_synced_method_metadata);
            }

            {
                // register method blockchain_get_block_count
                cdcchain::api::MethodData blockchain_get_block_count_method_metadata{ "blockchain_get_block_count", nullptr,
                    /* description */ "Returns the current head block number",
                    /* returns */ "uint32_t",
                    /* params: */{                    },
                    /* prerequisites */ (cdcchain::api::MethodPrerequisites) 0,
                    /* detailed description */ "Returns the current head block number\n\nParameters:\n  (none)\n\nReturns:\n  uint32_t\n",
                    /* aliases */ {"blockchain_get_blockcount", "getblockcount"}, true};
                store_method_metadata(blockchain_get_block_count_method_metadata);
            }

            {
                // register method blockchain_get_security_state
                cdcchain::api::MethodData blockchain_get_security_state_method_metadata{ "blockchain_get_security_state", nullptr,
                    /* description */ "Returns information about blockchain security level",
                    /* returns */ "blockchain_security_state",
                    /* params: */{                    },
                    /* prerequisites */ (cdcchain::api::MethodPrerequisites) 0,
                    /* detailed description */ "Returns information about blockchain security level\n\nParameters:\n  (none)\n\nReturns:\n  blockchain_security_state\n",
                    /* aliases */ {"alert_state", "security_state"}, true};
                store_method_metadata(blockchain_get_security_state_method_metadata);
            }

            {
                // register method blockchain_list_accounts
                cdcchain::api::MethodData blockchain_list_accounts_method_metadata{ "blockchain_list_accounts", nullptr,
                    /* description */ "Returns registered accounts starting with a given name upto a the limit provided",
                    /* returns */ "account_entry_array",
                    /* params: */{
                        {"first_account_name", "account_name", cdcchain::api::optional_positional, fc::variant(fc::json::from_string("\"\""))},
                        {"limit", "uint32_t", cdcchain::api::optional_positional, fc::variant(fc::json::from_string("20"))}
                          },
                    /* prerequisites */ (cdcchain::api::MethodPrerequisites) 0,
                    /* detailed description */ "Returns registered accounts starting with a given name upto a the limit provided\n\nParameters:\n  first_account_name (account_name, optional, defaults to \"\"): the first account name to include\n  limit (uint32_t, optional, defaults to 20): the maximum number of items to list\n\nReturns:\n  account_entry_array\n",
                    /* aliases */ {}, true};
                store_method_metadata(blockchain_list_accounts_method_metadata);
            }

            {
                // register method blockchain_list_recently_updated_accounts
                cdcchain::api::MethodData blockchain_list_recently_updated_accounts_method_metadata{ "blockchain_list_recently_updated_accounts", nullptr,
                    /* description */ "Returns a list of recently updated accounts",
                    /* returns */ "account_entry_array",
                    /* params: */{                    },
                    /* prerequisites */ (cdcchain::api::MethodPrerequisites) 0,
                    /* detailed description */ "Returns a list of recently updated accounts\n\nParameters:\n  (none)\n\nReturns:\n  account_entry_array\n",
                    /* aliases */ {}, true};
                store_method_metadata(blockchain_list_recently_updated_accounts_method_metadata);
            }

            {
                // register method blockchain_list_recently_registered_accounts
                cdcchain::api::MethodData blockchain_list_recently_registered_accounts_method_metadata{ "blockchain_list_recently_registered_accounts", nullptr,
                    /* description */ "Returns a list of recently registered accounts",
                    /* returns */ "account_entry_array",
                    /* params: */{                    },
                    /* prerequisites */ (cdcchain::api::MethodPrerequisites) 0,
                    /* detailed description */ "Returns a list of recently registered accounts\n\nParameters:\n  (none)\n\nReturns:\n  account_entry_array\n",
                    /* aliases */ {}, true};
                store_method_metadata(blockchain_list_recently_registered_accounts_method_metadata);
            }

            {
                // register method blockchain_list_assets
                cdcchain::api::MethodData blockchain_list_assets_method_metadata{ "blockchain_list_assets", nullptr,
                    /* description */ "Returns registered assets starting with a given name upto a the limit provided",
                    /* returns */ "asset_entry_array",
                    /* params: */{
                        {"first_symbol", "asset_symbol", cdcchain::api::optional_positional, fc::variant(fc::json::from_string("\"\""))},
                        {"limit", "uint32_t", cdcchain::api::optional_positional, fc::variant(fc::json::from_string("20"))}
                          },
                    /* prerequisites */ (cdcchain::api::MethodPrerequisites) 0,
                    /* detailed description */ "Returns registered assets starting with a given name upto a the limit provided\n\nParameters:\n  first_symbol (asset_symbol, optional, defaults to \"\"): the prefix of the first asset symbol name to include\n  limit (uint32_t, optional, defaults to 20): the maximum number of items to list\n\nReturns:\n  asset_entry_array\n",
                    /* aliases */ {}, true};
                store_method_metadata(blockchain_list_assets_method_metadata);
            }

            {
                // register method blockchain_list_pending_transactions
                cdcchain::api::MethodData blockchain_list_pending_transactions_method_metadata{ "blockchain_list_pending_transactions", nullptr,
                    /* description */ "Return a list of transactions that are not yet in a block.",
                    /* returns */ "signed_transaction_pair_array",
                    /* params: */{                    },
                    /* prerequisites */ (cdcchain::api::MethodPrerequisites) 0,
                    /* detailed description */ "Return a list of transactions that are not yet in a block.\n\nParameters:\n  (none)\n\nReturns:\n  signed_transaction_pair_array\n",
                    /* aliases */ {"blockchain_get_pending_transactions", "list_pending"}, false};
                store_method_metadata(blockchain_list_pending_transactions_method_metadata);
            }

            {
                // register method blockchain_get_transaction
                cdcchain::api::MethodData blockchain_get_transaction_method_metadata{ "blockchain_get_transaction", nullptr,
                    /* description */ "Get detailed information about an in-wallet transaction",
                    /* returns */ "transaction_entry_pair",
                    /* params: */{
                        {"transaction_id_prefix", "string", cdcchain::api::required_positional, fc::ovariant()},
                        {"exact", "bool", cdcchain::api::optional_positional, fc::variant(fc::json::from_string("false"))}
                          },
                    /* prerequisites */ (cdcchain::api::MethodPrerequisites) 0,
                    /* detailed description */ "Get detailed information about an in-wallet transaction\n\nParameters:\n  transaction_id_prefix (string, required): the base58 transaction ID to return\n  exact (bool, optional, defaults to false): whether or not a partial match is ok\n\nReturns:\n  transaction_entry_pair\n",
                    /* aliases */ {}, true};
                store_method_metadata(blockchain_get_transaction_method_metadata);
            }

            {
                // register method blockchain_get_pretty_transaction
                cdcchain::api::MethodData blockchain_get_pretty_transaction_method_metadata{ "blockchain_get_pretty_transaction", nullptr,
                    /* description */ "Get pretty information about an in-wallet transaction",
                    /* returns */ "pretty_transaction",
                    /* params: */{
                        {"transaction_id_prefix", "string", cdcchain::api::required_positional, fc::ovariant()},
                        {"exact", "bool", cdcchain::api::optional_positional, fc::variant(fc::json::from_string("false"))}
                          },
                    /* prerequisites */ (cdcchain::api::MethodPrerequisites) 0,
                    /* detailed description */ "Get pretty information about an in-wallet transaction\n\nParameters:\n  transaction_id_prefix (string, required): the base16 transaction ID to return\n  exact (bool, optional, defaults to false): whether or not a partial match is ok\n\nReturns:\n  pretty_transaction\n",
                    /* aliases */ {}, true};
                store_method_metadata(blockchain_get_pretty_transaction_method_metadata);
            }

            {
                // register method blockchain_get_pretty_contract_transaction
                cdcchain::api::MethodData blockchain_get_pretty_contract_transaction_method_metadata{ "blockchain_get_pretty_contract_transaction", nullptr,
                    /* description */ "Get pretty information about an in-wallet contract transaction",
                    /* returns */ "pretty_contract_transaction",
                    /* params: */{
                        {"transaction_id_prefix", "string", cdcchain::api::required_positional, fc::ovariant()},
                        {"exact", "bool", cdcchain::api::optional_positional, fc::variant(fc::json::from_string("false"))}
                          },
                    /* prerequisites */ (cdcchain::api::MethodPrerequisites) 0,
                    /* detailed description */ "Get pretty information about an in-wallet contract transaction\n\nParameters:\n  transaction_id_prefix (string, required): the base16 transaction ID to return\n  exact (bool, optional, defaults to false): whether or not a partial match is ok\n\nReturns:\n  pretty_contract_transaction\n",
                    /* aliases */ {}, true};
                store_method_metadata(blockchain_get_pretty_contract_transaction_method_metadata);
            }

            {
                // register method blockchain_get_block
                cdcchain::api::MethodData blockchain_get_block_method_metadata{ "blockchain_get_block", nullptr,
                    /* description */ "Retrieves the block entry for the given block number or ID",
                    /* returns */ "oblock_entry",
                    /* params: */{
                        {"block", "string", cdcchain::api::required_positional, fc::ovariant()}
                          },
                    /* prerequisites */ (cdcchain::api::MethodPrerequisites) 0,
                    /* detailed description */ "Retrieves the block entry for the given block number or ID\n\nParameters:\n  block (string, required): block number or ID to retrieve\n\nReturns:\n  oblock_entry\n",
                    /* aliases */ {"get_block", "getblock", "blockchain_get_block_hash", "blockchain_get_blockhash", "getblockhash"}, true};
                store_method_metadata(blockchain_get_block_method_metadata);
            }

            {
                // register method blockchain_get_block_transactions
                cdcchain::api::MethodData blockchain_get_block_transactions_method_metadata{ "blockchain_get_block_transactions", nullptr,
                    /* description */ "Retrieves the detailed transaction information for a block",
                    /* returns */ "transaction_entry_map",
                    /* params: */{
                        {"block", "string", cdcchain::api::required_positional, fc::ovariant()}
                          },
                    /* prerequisites */ (cdcchain::api::MethodPrerequisites) 0,
                    /* detailed description */ "Retrieves the detailed transaction information for a block\n\nParameters:\n  block (string, required): the number or id of the block to get transactions from\n\nReturns:\n  transaction_entry_map\n",
                    /* aliases */ {}, true};
                store_method_metadata(blockchain_get_block_transactions_method_metadata);
            }

            {
                // register method blockchain_get_account
                cdcchain::api::MethodData blockchain_get_account_method_metadata{ "blockchain_get_account", nullptr,
                    /* description */ "Retrieves the entry for the given account name or ID",
                    /* returns */ "optional_account_entry",
                    /* params: */{
                        {"account", "string", cdcchain::api::required_positional, fc::ovariant()}
                          },
                    /* prerequisites */ (cdcchain::api::MethodPrerequisites) 0,
                    /* detailed description */ "Retrieves the entry for the given account name or ID\n\nParameters:\n  account (string, required): account name, ID, or public key to retrieve the entry for\n\nReturns:\n  optional_account_entry\n",
                    /* aliases */ {"get_account"}, true};
                store_method_metadata(blockchain_get_account_method_metadata);
            }

            {
                // register method blockchain_get_slate
                cdcchain::api::MethodData blockchain_get_slate_method_metadata{ "blockchain_get_slate", nullptr,
                    /* description */ "Retrieves a map of delegate IDs and names defined by the given slate ID or recommending account",
                    /* returns */ "map<account_id_type, string>",
                    /* params: */{
                        {"slate", "string", cdcchain::api::required_positional, fc::ovariant()}
                          },
                    /* prerequisites */ (cdcchain::api::MethodPrerequisites) 0,
                    /* detailed description */ "Retrieves a map of delegate IDs and names defined by the given slate ID or recommending account\n\nParameters:\n  slate (string, required): slate ID or recommending account name for which to retrieve the slate of delegates\n\nReturns:\n  map<account_id_type, string>\n",
                    /* aliases */ {"get_slate"}, true};
                store_method_metadata(blockchain_get_slate_method_metadata);
            }

            {
                // register method blockchain_get_balance
                cdcchain::api::MethodData blockchain_get_balance_method_metadata{ "blockchain_get_balance", nullptr,
                    /* description */ "Retrieves the specified balance entry",
                    /* returns */ "balance_entry",
                    /* params: */{
                        {"balance_id", "address", cdcchain::api::required_positional, fc::ovariant()}
                          },
                    /* prerequisites */ (cdcchain::api::MethodPrerequisites) 0,
                    /* detailed description */ "Retrieves the specified balance entry\n\nParameters:\n  balance_id (address, required): the ID of the balance entry\n\nReturns:\n  balance_entry\n",
                    /* aliases */ {"get_balance"}, true};
                store_method_metadata(blockchain_get_balance_method_metadata);
            }

            {
                // register method blockchain_list_balances
                cdcchain::api::MethodData blockchain_list_balances_method_metadata{ "blockchain_list_balances", nullptr,
                    /* description */ "Lists balance entrys starting at the given balance ID",
                    /* returns */ "balance_entry_map",
                    /* params: */{
                        {"first_balance_id", "string", cdcchain::api::optional_positional, fc::variant(fc::json::from_string("\"\""))},
                        {"limit", "uint32_t", cdcchain::api::optional_positional, fc::variant(fc::json::from_string("20"))}
                          },
                    /* prerequisites */ (cdcchain::api::MethodPrerequisites) 0,
                    /* detailed description */ "Lists balance entrys starting at the given balance ID\n\nParameters:\n  first_balance_id (string, optional, defaults to \"\"): the first balance id to start at\n  limit (uint32_t, optional, defaults to 20): the maximum number of items to list\n\nReturns:\n  balance_entry_map\n",
                    /* aliases */ {"list_balances"}, true};
                store_method_metadata(blockchain_list_balances_method_metadata);
            }

            {
                // register method blockchain_list_address_balances
                cdcchain::api::MethodData blockchain_list_address_balances_method_metadata{ "blockchain_list_address_balances", nullptr,
                    /* description */ "Lists balance entrys which are the balance IDs or which can be claimed by signature for this address",
                    /* returns */ "balance_entry_map",
                    /* params: */{
                        {"addr", "string", cdcchain::api::required_positional, fc::ovariant()},
                        {"chanced_since", "timestamp", cdcchain::api::optional_positional, fc::variant(fc::json::from_string("\"1970-1-1T00:00:01\""))}
                          },
                    /* prerequisites */ (cdcchain::api::MethodPrerequisites) 0,
                    /* detailed description */ "Lists balance entrys which are the balance IDs or which can be claimed by signature for this address\n\nParameters:\n  addr (string, required): address to scan for\n  chanced_since (timestamp, optional, defaults to \"1970-1-1T00:00:01\"): Filter all balances that haven't chanced since the provided timestamp\n\nReturns:\n  balance_entry_map\n",
                    /* aliases */ {"list_address_balances"}, true};
                store_method_metadata(blockchain_list_address_balances_method_metadata);
            }

            {
                // register method blockchain_list_address_transactions
                cdcchain::api::MethodData blockchain_list_address_transactions_method_metadata{ "blockchain_list_address_transactions", nullptr,
                    /* description */ "Lists all transactions that involve the provided address after the specified time",
                    /* returns */ "variant_object",
                    /* params: */{
                        {"addr", "string", cdcchain::api::required_positional, fc::ovariant()},
                        {"filter_before", "uint32_t", cdcchain::api::optional_positional, fc::variant(fc::json::from_string("\"0\""))}
                          },
                    /* prerequisites */ (cdcchain::api::MethodPrerequisites) 0,
                    /* detailed description */ "Lists all transactions that involve the provided address after the specified time\n\nParameters:\n  addr (string, required): address to scan for\n  filter_before (uint32_t, optional, defaults to \"0\"): Filter all transactions that occured prior to the specified block number\n\nReturns:\n  variant_object\n",
                    /* aliases */ {"list_address_transactions"}, true};
                store_method_metadata(blockchain_list_address_transactions_method_metadata);
            }

            {
                // register method blockchain_get_account_public_balance
                cdcchain::api::MethodData blockchain_get_account_public_balance_method_metadata{ "blockchain_get_account_public_balance", nullptr,
                    /* description */ "Get the account entry for a given name",
                    /* returns */ "account_balance_summary_type",
                    /* params: */{
                        {"account_name", "account_name", cdcchain::api::required_positional, fc::ovariant()}
                          },
                    /* prerequisites */ (cdcchain::api::MethodPrerequisites) 2,
                    /* detailed description */ "Get the account entry for a given name\n\nParameters:\n  account_name (account_name, required): the name of the account whose public address you want\n\nReturns:\n  account_balance_summary_type\n",
                    /* aliases */ {}, true};
                store_method_metadata(blockchain_get_account_public_balance_method_metadata);
            }

            {
                // register method blockchain_list_key_balances
                cdcchain::api::MethodData blockchain_list_key_balances_method_metadata{ "blockchain_list_key_balances", nullptr,
                    /* description */ "Lists balance entrys which can be claimed by signature for this key",
                    /* returns */ "balance_entry_map",
                    /* params: */{
                        {"key", "public_key", cdcchain::api::required_positional, fc::ovariant()}
                          },
                    /* prerequisites */ (cdcchain::api::MethodPrerequisites) 0,
                    /* detailed description */ "Lists balance entrys which can be claimed by signature for this key\n\nParameters:\n  key (public_key, required): Key to scan for\n\nReturns:\n  balance_entry_map\n",
                    /* aliases */ {"list_key_balances"}, true};
                store_method_metadata(blockchain_list_key_balances_method_metadata);
            }

            {
                // register method blockchain_get_asset
                cdcchain::api::MethodData blockchain_get_asset_method_metadata{ "blockchain_get_asset", nullptr,
                    /* description */ "Retrieves the entry for the given asset ticker symbol or ID",
                    /* returns */ "optional_asset_entry",
                    /* params: */{
                        {"asset", "string", cdcchain::api::required_positional, fc::ovariant()}
                          },
                    /* prerequisites */ (cdcchain::api::MethodPrerequisites) 0,
                    /* detailed description */ "Retrieves the entry for the given asset ticker symbol or ID\n\nParameters:\n  asset (string, required): asset ticker symbol or ID to retrieve\n\nReturns:\n  optional_asset_entry\n",
                    /* aliases */ {"get_asset"}, true};
                store_method_metadata(blockchain_get_asset_method_metadata);
            }

            {
                // register method blockchain_list_active_delegates
                cdcchain::api::MethodData blockchain_list_active_delegates_method_metadata{ "blockchain_list_active_delegates", nullptr,
                    /* description */ "Returns a list of the current round's active delegates in signing order",
                    /* returns */ "account_entry_array",
                    /* params: */{
                        {"first", "uint32_t", cdcchain::api::optional_positional, fc::variant(fc::json::from_string("0"))},
                        {"count", "uint32_t", cdcchain::api::optional_positional, fc::variant(fc::json::from_string("20"))}
                          },
                    /* prerequisites */ (cdcchain::api::MethodPrerequisites) 0,
                    /* detailed description */ "Returns a list of the current round's active delegates in signing order\n\nParameters:\n  first (uint32_t, optional, defaults to 0): \n  count (uint32_t, optional, defaults to 20): \n\nReturns:\n  account_entry_array\n",
                    /* aliases */ {"blockchain_get_active_delegates"}, true};
                store_method_metadata(blockchain_list_active_delegates_method_metadata);
            }

            {
                // register method blockchain_list_delegates
                cdcchain::api::MethodData blockchain_list_delegates_method_metadata{ "blockchain_list_delegates", nullptr,
                    /* description */ "Returns a list of all the delegates sorted by vote",
                    /* returns */ "account_entry_array",
                    /* params: */{
                        {"first", "uint32_t", cdcchain::api::optional_positional, fc::variant(fc::json::from_string("0"))},
                        {"count", "uint32_t", cdcchain::api::optional_positional, fc::variant(fc::json::from_string("20"))}
                          },
                    /* prerequisites */ (cdcchain::api::MethodPrerequisites) 0,
                    /* detailed description */ "Returns a list of all the delegates sorted by vote\n\nParameters:\n  first (uint32_t, optional, defaults to 0): \n  count (uint32_t, optional, defaults to 20): \n\nReturns:\n  account_entry_array\n",
                    /* aliases */ {"blockchain_get_delegates"}, true};
                store_method_metadata(blockchain_list_delegates_method_metadata);
            }

            {
                // register method blockchain_list_blocks
                cdcchain::api::MethodData blockchain_list_blocks_method_metadata{ "blockchain_list_blocks", nullptr,
                    /* description */ "Returns a descending list of block entrys starting from the specified block number",
                    /* returns */ "block_entry_array",
                    /* params: */{
                        {"max_block_num", "uint32_t", cdcchain::api::optional_positional, fc::variant(fc::json::from_string("-1"))},
                        {"limit", "uint32_t", cdcchain::api::optional_positional, fc::variant(fc::json::from_string("20"))}
                          },
                    /* prerequisites */ (cdcchain::api::MethodPrerequisites) 0,
                    /* detailed description */ "Returns a descending list of block entrys starting from the specified block number\n\nParameters:\n  max_block_num (uint32_t, optional, defaults to -1): the block num to start from; negative to count backwards from the current head block\n  limit (uint32_t, optional, defaults to 20): max number of blocks to return\n\nReturns:\n  block_entry_array\n",
                    /* aliases */ {"list_blocks"}, true};
                store_method_metadata(blockchain_list_blocks_method_metadata);
            }

            {
                // register method blockchain_list_missing_block_delegates
                cdcchain::api::MethodData blockchain_list_missing_block_delegates_method_metadata{ "blockchain_list_missing_block_delegates", nullptr,
                    /* description */ "Returns any delegates who were supposed to produce a given block number but didn't",
                    /* returns */ "account_name_array",
                    /* params: */{
                        {"block_number", "uint32_t", cdcchain::api::required_positional, fc::ovariant()}
                          },
                    /* prerequisites */ (cdcchain::api::MethodPrerequisites) 0,
                    /* detailed description */ "Returns any delegates who were supposed to produce a given block number but didn't\n\nParameters:\n  block_number (uint32_t, required): The block to examine\n\nReturns:\n  account_name_array\n",
                    /* aliases */ {}, true};
                store_method_metadata(blockchain_list_missing_block_delegates_method_metadata);
            }

            {
                // register method blockchain_export_fork_graph
                cdcchain::api::MethodData blockchain_export_fork_graph_method_metadata{ "blockchain_export_fork_graph", nullptr,
                    /* description */ "dumps the fork data to graphviz format",
                    /* returns */ "string",
                    /* params: */{
                        {"start_block", "uint32_t", cdcchain::api::optional_positional, fc::variant(fc::json::from_string("1"))},
                        {"end_block", "uint32_t", cdcchain::api::optional_positional, fc::variant(fc::json::from_string("-1"))},
                        {"filename", "path", cdcchain::api::optional_positional, fc::variant(fc::json::from_string("\"\""))}
                          },
                    /* prerequisites */ (cdcchain::api::MethodPrerequisites) 0,
                    /* detailed description */ "dumps the fork data to graphviz format\n\nParameters:\n  start_block (uint32_t, optional, defaults to 1): the first block number to consider\n  end_block (uint32_t, optional, defaults to -1): the last block number to consider\n  filename (path, optional, defaults to \"\"): the filename to save to\n\nReturns:\n  string\n",
                    /* aliases */ {"export_forks"}, false};
                store_method_metadata(blockchain_export_fork_graph_method_metadata);
            }

            {
                // register method blockchain_list_forks
                cdcchain::api::MethodData blockchain_list_forks_method_metadata{ "blockchain_list_forks", nullptr,
                    /* description */ "returns a list of all blocks for which there is a fork off of the main chain",
                    /* returns */ "map<uint32_t, vector<fork_entry>>",
                    /* params: */{                    },
                    /* prerequisites */ (cdcchain::api::MethodPrerequisites) 0,
                    /* detailed description */ "returns a list of all blocks for which there is a fork off of the main chain\n\nParameters:\n  (none)\n\nReturns:\n  map<uint32_t, vector<fork_entry>>\n",
                    /* aliases */ {"list_forks"}, true};
                store_method_metadata(blockchain_list_forks_method_metadata);
            }

            {
                // register method blockchain_get_delegate_slot_entrys
                cdcchain::api::MethodData blockchain_get_delegate_slot_entrys_method_metadata{ "blockchain_get_delegate_slot_entrys", nullptr,
                    /* description */ "Query the most recent block production slot entrys for the specified delegate",
                    /* returns */ "slot_entrys_list",
                    /* params: */{
                        {"delegate_name", "string", cdcchain::api::required_positional, fc::ovariant()},
                        {"limit", "uint32_t", cdcchain::api::optional_positional, fc::variant(fc::json::from_string("\"10\""))}
                          },
                    /* prerequisites */ (cdcchain::api::MethodPrerequisites) 0,
                    /* detailed description */ "Query the most recent block production slot entrys for the specified delegate\n\nParameters:\n  delegate_name (string, required): Delegate whose block production slot entrys to query\n  limit (uint32_t, optional, defaults to \"10\"): The maximum number of slot entrys to return\n\nReturns:\n  slot_entrys_list\n",
                    /* aliases */ {"get_slot"}, true};
                store_method_metadata(blockchain_get_delegate_slot_entrys_method_metadata);
            }

            {
                // register method blockchain_get_block_signee
                cdcchain::api::MethodData blockchain_get_block_signee_method_metadata{ "blockchain_get_block_signee", nullptr,
                    /* description */ "Get the delegate that signed a given block",
                    /* returns */ "string",
                    /* params: */{
                        {"block", "string", cdcchain::api::required_positional, fc::ovariant()}
                          },
                    /* prerequisites */ (cdcchain::api::MethodPrerequisites) 0,
                    /* detailed description */ "Get the delegate that signed a given block\n\nParameters:\n  block (string, required): block number or ID to retrieve the signee for\n\nReturns:\n  string\n",
                    /* aliases */ {}, true};
                store_method_metadata(blockchain_get_block_signee_method_metadata);
            }

            {
                // register method blockchain_unclaimed_genesis
                cdcchain::api::MethodData blockchain_unclaimed_genesis_method_metadata{ "blockchain_unclaimed_genesis", nullptr,
                    /* description */ "Returns the total shares in the genesis block which have never been fully or partially claimed.",
                    /* returns */ "asset",
                    /* params: */{                    },
                    /* prerequisites */ (cdcchain::api::MethodPrerequisites) 0,
                    /* detailed description */ "Returns the total shares in the genesis block which have never been fully or partially claimed.\n\nParameters:\n  (none)\n\nReturns:\n  asset\n",
                    /* aliases */ {}, true};
                store_method_metadata(blockchain_unclaimed_genesis_method_metadata);
            }

            {
                // register method blockchain_verify_signature
                cdcchain::api::MethodData blockchain_verify_signature_method_metadata{ "blockchain_verify_signature", nullptr,
                    /* description */ "Verify that the given signature proves the given hash was signed by the given account.",
                    /* returns */ "bool",
                    /* params: */{
                        {"signer", "string", cdcchain::api::required_positional, fc::ovariant()},
                        {"hash", "sha256", cdcchain::api::required_positional, fc::ovariant()},
                        {"signature", "compact_signature", cdcchain::api::required_positional, fc::ovariant()}
                          },
                    /* prerequisites */ (cdcchain::api::MethodPrerequisites) 0,
                    /* detailed description */ "Verify that the given signature proves the given hash was signed by the given account.\n\nParameters:\n  signer (string, required): A public key, address, or account name whose signature to check\n  hash (sha256, required): The hash the signature claims to be for\n  signature (compact_signature, required): A signature produced by wallet_sign_hash\n\nReturns:\n  bool\n",
                    /* aliases */ {"verify_signature", "verify_sig", "blockchain_verify_sig"}, true};
                store_method_metadata(blockchain_verify_signature_method_metadata);
            }

            {
                // register method blockchain_dump_state
                cdcchain::api::MethodData blockchain_dump_state_method_metadata{ "blockchain_dump_state", nullptr,
                    /* description */ "TODO",
                    /* returns */ "void",
                    /* params: */{
                        {"path", "string", cdcchain::api::required_positional, fc::ovariant()}
                          },
                    /* prerequisites */ (cdcchain::api::MethodPrerequisites) 0,
                    /* detailed description */ "TODO\n\nParameters:\n  path (string, required): the directory to dump the state into\n\nReturns:\n  void\n",
                    /* aliases */ {}, true};
                store_method_metadata(blockchain_dump_state_method_metadata);
            }

            {
                // register method blockchain_broadcast_transaction
                cdcchain::api::MethodData blockchain_broadcast_transaction_method_metadata{ "blockchain_broadcast_transaction", nullptr,
                    /* description */ "Takes a signed transaction and broadcasts it to the network.",
                    /* returns */ "void",
                    /* params: */{
                        {"trx", "signed_transaction", cdcchain::api::required_positional, fc::ovariant()}
                          },
                    /* prerequisites */ (cdcchain::api::MethodPrerequisites) 0,
                    /* detailed description */ "Takes a signed transaction and broadcasts it to the network.\n\nParameters:\n  trx (signed_transaction, required): The transaction to broadcast\n\nReturns:\n  void\n",
                    /* aliases */ {}, true};
                store_method_metadata(blockchain_broadcast_transaction_method_metadata);
            }

            {
                // register method blockchain_btc_address_convert
                cdcchain::api::MethodData blockchain_btc_address_convert_method_metadata{ "blockchain_btc_address_convert", nullptr,
                    /* description */ "Convert bitcoin address file to cdcchain address file.",
                    /* returns */ "void",
                    /* params: */{
                        {"path", "string", cdcchain::api::required_positional, fc::ovariant()}
                          },
                    /* prerequisites */ (cdcchain::api::MethodPrerequisites) 0,
                    /* detailed description */ "Convert bitcoin address file to cdcchain address file.\n\nParameters:\n  path (string, required): The bitcoin address file path.\n\nReturns:\n  void\n",
                    /* aliases */ {}, true};
                store_method_metadata(blockchain_btc_address_convert_method_metadata);
            }

            {
                // register method blockchain_get_transaction_rpc
                cdcchain::api::MethodData blockchain_get_transaction_rpc_method_metadata{ "blockchain_get_transaction_rpc", nullptr,
                    /* description */ "Get detailed information about an in-wallet transaction",
                    /* returns */ "string",
                    /* params: */{
                        {"transaction_id_prefix", "string", cdcchain::api::required_positional, fc::ovariant()},
                        {"exact", "bool", cdcchain::api::optional_positional, fc::variant(fc::json::from_string("false"))}
                          },
                    /* prerequisites */ (cdcchain::api::MethodPrerequisites) 0,
                    /* detailed description */ "Get detailed information about an in-wallet transaction\n\nParameters:\n  transaction_id_prefix (string, required): the base58 transaction ID to return\n  exact (bool, optional, defaults to false): whether or not a partial match is ok\n\nReturns:\n  string\n",
                    /* aliases */ {}, true};
                store_method_metadata(blockchain_get_transaction_rpc_method_metadata);
            }

            {
                // register method blockchain_set_node_vm_enabled
                cdcchain::api::MethodData blockchain_set_node_vm_enabled_method_metadata{ "blockchain_set_node_vm_enabled", nullptr,
                    /* description */ "set the vm enabled flag of normal node, no effect for the delegate",
                    /* returns */ "void",
                    /* params: */{
                        {"enabled", "bool", cdcchain::api::required_positional, fc::ovariant()}
                          },
                    /* prerequisites */ (cdcchain::api::MethodPrerequisites) 0,
                    /* detailed description */ "set the vm enabled flag of normal node, no effect for the delegate\n\nParameters:\n  enabled (bool, required): vm enabled flag\n\nReturns:\n  void\n",
                    /* aliases */ {}, true};
                store_method_metadata(blockchain_set_node_vm_enabled_method_metadata);
            }

            {
                // register method wallet_transfer_to_address_build
                cdcchain::api::MethodData wallet_transfer_to_address_build_method_metadata{ "wallet_transfer_to_address_build", nullptr,
                    /* description */ "create a simple (non-TITAN) transfer to an address without signature",
                    /* returns */ "transaction_entry",
                    /* params: */{
                        { "amount_to_transfer", "string", cdcchain::api::required_positional, fc::ovariant() },
                { "asset_symbol", "asset_symbol", cdcchain::api::required_positional, fc::ovariant() },
                { "from_account_public_key", "string", cdcchain::api::required_positional, fc::ovariant() },
                { "to_address", "string", cdcchain::api::required_positional, fc::ovariant() },
                { "memo_message", "information", cdcchain::api::optional_positional, fc::variant(fc::json::from_string("\"\"")) },
                { "strategy", "vote_strategy", cdcchain::api::optional_positional, fc::variant(fc::json::from_string("\"vote_none\"")) }
                },
                    /* prerequisites */ (cdcchain::api::MethodPrerequisites) 2,
                    /* detailed description */ "create a simple (non-TITAN) transfer to an address without signature\n\nParameters:\n  amount_to_transfer (string, required): the amount of shares to transfer\n  asset_symbol (asset_symbol, required): the asset to transfer\n  from_account_public_key (string, required): the source account to draw the shares from\n  to_address (string, required): the address or pubkey to transfer to\n  memo_message (information, optional, defaults to \"\"): a memo to store with the transaction\n  strategy (vote_strategy, optional, defaults to \"vote_none\"): enumeration [vote_none | vote_all | vote_random | vote_recommended] \n\nReturns:\n  transaction_entry\n",
                    /* aliases */{}, false };
                store_method_metadata(wallet_transfer_to_address_build_method_metadata);
            }

            {
            // register method wallet_transfer_to_contract_build
            cdcchain::api::MethodData wallet_transfer_to_contract_build_method_metadata{ "wallet_transfer_to_contract_build", nullptr,
                /* description */ "Do a simple transfer to a contract (name or address)",
                /* returns */ "transaction_entry",
                /* params: */{
                    { "amount_to_transfer", "real_amount", cdcchain::api::required_positional, fc::ovariant() },
            { "asset_symbol", "asset_symbol", cdcchain::api::required_positional, fc::ovariant() },
            { "from_account_public_key", "string", cdcchain::api::required_positional, fc::ovariant() },
            { "to_contract", "string", cdcchain::api::required_positional, fc::ovariant() },
            { "amount_for_exec", "real_amount", cdcchain::api::required_positional, fc::ovariant() }
            },
                /* prerequisites */ (cdcchain::api::MethodPrerequisites) 4,
                /* detailed description */ "Do a simple transfer to a contract (name or address)\n\nParameters:\n  amount_to_transfer (real_amount, required): the amount of shares to transfer\n  asset_symbol (asset_symbol, required): the asset to transfer\n  from_account_public_key (string, required): the source account public key to draw the shares from\n  to_contract (string, required): the contract name or contract address to transfer to\n  amount_for_exec (real_amount, required): the amount of shares to exec  on_deposit callback of target contract\n\nReturns:\n  transaction_entry\n",
                /* aliases */{}, false };
            store_method_metadata(wallet_transfer_to_contract_build_method_metadata);
            }

            {
                // register method wallet_call_contract_build
                cdcchain::api::MethodData wallet_call_contract_build_method_metadata{ "wallet_call_contract_build", nullptr,
                    /* description */ "call contract by contract name or contract address without signature",
                    /* returns */ "transaction_entry",
                    /* params: */{
                        { "contract", "string", cdcchain::api::required_positional, fc::ovariant() },
                { "caller_publickey", "string", cdcchain::api::required_positional, fc::ovariant() },
                { "function_name", "string", cdcchain::api::required_positional, fc::ovariant() },
                { "params", "string", cdcchain::api::required_positional, fc::ovariant() },
                { "asset_symbol", "string", cdcchain::api::required_positional, fc::ovariant() },
                { "call_limit", "optional_double", cdcchain::api::required_positional, fc::ovariant() }
                },
                    /* prerequisites */ (cdcchain::api::MethodPrerequisites) 2,
                    /* detailed description */ "call contract by contract name or contract address without signature\n\nParameters:\n  contract (string, required): contract name or contract address need to be called\n  caller_publickey (string, required): caller public key\n  function_name (string, required): function in contract \n  params (string, required): parameters which would be passed to function\n  asset_symbol (string, required): symbol of asset used to call\n  call_limit (optional_double, required): the limit of asset amount used to call contract \n\nReturns:\n  transaction_entry\n",
                    /* aliases */{}, false };
                store_method_metadata(wallet_call_contract_build_method_metadata);
            }

            {
                // register method sign_build_transaction
                cdcchain::api::MethodData sign_build_transaction_method_metadata{ "sign_build_transaction", nullptr,
                    /* description */ "sign transaction which get from build interface",
                    /* returns */ "transaction_entry",
                    /* params: */{
                        { "trasaction_building", "transaction_entry", cdcchain::api::required_positional, fc::ovariant() }
                },
                    /* prerequisites */ (cdcchain::api::MethodPrerequisites) 4,
                    /* detailed description */ "sign transaction which get from build interface\n\nParameters:\n  trasaction_building (transaction_entry, required): the transaction which get from build interface\n\nReturns:\n  transaction_entry\n",
                    /* aliases */{}, false };
                store_method_metadata(sign_build_transaction_method_metadata);
            }

            {
                // register method broadcast_building_transaction
                cdcchain::api::MethodData broadcast_building_transaction_method_metadata{ "broadcast_building_transaction", nullptr,
                    /* description */ "broadcast signed transaction which get from build interface",
                    /* returns */ "bool",
                    /* params: */{
                        { "trasaction_building", "transaction_entry", cdcchain::api::required_positional, fc::ovariant() }
                },
                    /* prerequisites */ (cdcchain::api::MethodPrerequisites) 4,
                    /* detailed description */ "broadcast signed transaction which get from build interface\n\nParameters:\n  trasaction_building (transaction_entry, required): the transaction which get from build interface\n\nReturns:\n  bool\n",
                    /* aliases */{}, false };
                store_method_metadata(broadcast_building_transaction_method_metadata);
            }

            {
                // register method blockchain_get_node_vm_enabled
                cdcchain::api::MethodData blockchain_get_node_vm_enabled_method_metadata{ "blockchain_get_node_vm_enabled", nullptr,
                    /* description */ "get the vm enabled flag of normal node",
                    /* returns */ "bool",
                    /* params: */{                    },
                    /* prerequisites */ (cdcchain::api::MethodPrerequisites) 0,
                    /* detailed description */ "get the vm enabled flag of normal node\n\nParameters:\n  (none)\n\nReturns:\n  bool\n",
                    /* aliases */ {}, true};
                store_method_metadata(blockchain_get_node_vm_enabled_method_metadata);
            }

            {
                // register method blockchain_get_all_contracts
                cdcchain::api::MethodData blockchain_get_all_contracts_method_metadata{ "blockchain_get_all_contracts", nullptr,
                    /* description */ "get all contracts on the chain",
                    /* returns */ "contract_id_list",
                    /* params: */{                    },
                    /* prerequisites */ (cdcchain::api::MethodPrerequisites) 0,
                    /* detailed description */ "get all contracts on the chain\n\nParameters:\n  (none)\n\nReturns:\n  contract_id_list\n",
                    /* aliases */ {}, true};
                store_method_metadata(blockchain_get_all_contracts_method_metadata);
            }

            {
                // register method blockchain_get_forever_contracts
                cdcchain::api::MethodData blockchain_get_forever_contracts_method_metadata{ "blockchain_get_forever_contracts", nullptr,
                    /* description */ "get all forever contracts on the chain",
                    /* returns */ "contract_id_name_map",
                    /* params: */{                    },
                    /* prerequisites */ (cdcchain::api::MethodPrerequisites) 0,
                    /* detailed description */ "get all forever contracts on the chain\n\nParameters:\n  (none)\n\nReturns:\n  contract_id_name_map\n",
                    /* aliases */ {}, true};
                store_method_metadata(blockchain_get_forever_contracts_method_metadata);
            }

            {
                // register method blockchain_list_pub_all_address
                cdcchain::api::MethodData blockchain_list_pub_all_address_method_metadata{ "blockchain_list_pub_all_address", nullptr,
                    /* description */ "list all address converted by public",
                    /* returns */ "string_array",
                    /* params: */{
                        {"pub_key", "string", cdcchain::api::required_positional, fc::ovariant()}
                          },
                    /* prerequisites */ (cdcchain::api::MethodPrerequisites) 0,
                    /* detailed description */ "list all address converted by public\n\nParameters:\n  pub_key (string, required): public key need to list all addresses\n\nReturns:\n  string_array\n",
                    /* aliases */ {}, true};
                store_method_metadata(blockchain_list_pub_all_address_method_metadata);
            }

            {
                // register method blockchain_list_contract_transaction_history
                cdcchain::api::MethodData blockchain_list_contract_transaction_history_method_metadata{ "blockchain_list_contract_transaction_history", nullptr,
                    /* description */ "Lists contract transactions match the conditions",
                    /* returns */ "contract_transaction_summarys",
                    /* params: */{
                        {"from_block_num", "uint32_t", cdcchain::api::required_positional, fc::ovariant()},
                        {"block_count", "uint32_t", cdcchain::api::required_positional, fc::ovariant()},
                        {"contract_id", "string", cdcchain::api::optional_positional, fc::variant(fc::json::from_string("\"\""))},
                        {"trx_type", "uint32_t", cdcchain::api::optional_positional, fc::variant(fc::json::from_string("\"99\""))},
                        {"call_method", "string", cdcchain::api::optional_positional, fc::variant(fc::json::from_string("\"\""))}
                          },
                    /* prerequisites */ (cdcchain::api::MethodPrerequisites) 0,
                    /* detailed description */ "Lists contract transactions match the conditions\n\nParameters:\n  from_block_num (uint32_t, required): start block num\n  block_count (uint32_t, required): block count\n  contract_id (string, optional, defaults to \"\"): contract_id of contract transaction, and Null string represents all contract id\n  trx_type (uint32_t, optional, defaults to \"99\"): contract transaction type, 99 represents all kinds of transaction type\n  call_method (string, optional, defaults to \"\"): if contract transaction type is set to contract_call_transaction, this arg can work, and it represents the method called\n\nReturns:\n  contract_transaction_summarys\n",
                    /* aliases */ {""}, true};
                store_method_metadata(blockchain_list_contract_transaction_history_method_metadata);
            }

            {
                // register method network_add_node
                cdcchain::api::MethodData network_add_node_method_metadata{ "network_add_node", nullptr,
                    /* description */ "Attempts add or remove <node> from the peer list or try a connection to <node> once",
                    /* returns */ "void",
                    /* params: */{
                        {"node", "string", cdcchain::api::required_positional, fc::ovariant()},
                        {"command", "string", cdcchain::api::optional_positional, fc::variant(fc::json::from_string("\"add\""))}
                          },
                    /* prerequisites */ (cdcchain::api::MethodPrerequisites) 1,
                    /* detailed description */ "Attempts add or remove <node> from the peer list or try a connection to <node> once\n\nParameters:\n  node (string, required): The node (see network_get_peer_info for nodes)\n  command (string, optional, defaults to \"add\"): 'add' to add a node to the list, 'remove' to remove a node from the list, 'onetry' to try a connection to the node once\n\nReturns:\n  void\n",
                    /* aliases */ {"addnode"}, false};
                store_method_metadata(network_add_node_method_metadata);
            }

            {
                // register method network_get_connection_count
                cdcchain::api::MethodData network_get_connection_count_method_metadata{ "network_get_connection_count", nullptr,
                    /* description */ "Returns the number of fully-established connections to other nodes",
                    /* returns */ "uint32_t",
                    /* params: */{                    },
                    /* prerequisites */ (cdcchain::api::MethodPrerequisites) 1,
                    /* detailed description */ "Returns the number of fully-established connections to other nodes\n\nParameters:\n  (none)\n\nReturns:\n  uint32_t\n",
                    /* aliases */ {"getconnectioncount"}, false};
                store_method_metadata(network_get_connection_count_method_metadata);
            }

            {
                // register method network_get_peer_info
                cdcchain::api::MethodData network_get_peer_info_method_metadata{ "network_get_peer_info", nullptr,
                    /* description */ "Returns data about each connected node",
                    /* returns */ "json_object_array",
                    /* params: */{
                        {"not_firewalled", "bool", cdcchain::api::optional_positional, fc::variant(fc::json::from_string("false"))}
                          },
                    /* prerequisites */ (cdcchain::api::MethodPrerequisites) 1,
                    /* detailed description */ "Returns data about each connected node\n\nParameters:\n  not_firewalled (bool, optional, defaults to false): true to output only peers not behind a firewall and false otherwise\n\nReturns:\n  json_object_array\n",
                    /* aliases */ {}, false};
                store_method_metadata(network_get_peer_info_method_metadata);
            }

            {
                // register method network_broadcast_transaction
                cdcchain::api::MethodData network_broadcast_transaction_method_metadata{ "network_broadcast_transaction", nullptr,
                    /* description */ "Broadcast a previously-created signed transaction to the network",
                    /* returns */ "transaction_id",
                    /* params: */{
                        {"transaction_to_broadcast", "signed_transaction", cdcchain::api::required_positional, fc::ovariant()}
                          },
                    /* prerequisites */ (cdcchain::api::MethodPrerequisites) 9,
                    /* detailed description */ "Broadcast a previously-created signed transaction to the network\n\nParameters:\n  transaction_to_broadcast (signed_transaction, required): The transaction to broadcast to the network\n\nReturns:\n  transaction_id\n",
                    /* aliases */ {}, false};
                store_method_metadata(network_broadcast_transaction_method_metadata);
            }

            {
                // register method network_set_advanced_node_parameters
                cdcchain::api::MethodData network_set_advanced_node_parameters_method_metadata{ "network_set_advanced_node_parameters", nullptr,
                    /* description */ "Sets advanced node parameters, used for setting up automated tests",
                    /* returns */ "void",
                    /* params: */{
                        {"params", "json_object", cdcchain::api::required_positional, fc::ovariant()}
                          },
                    /* prerequisites */ (cdcchain::api::MethodPrerequisites) 1,
                    /* detailed description */ "Sets advanced node parameters, used for setting up automated tests\n\nParameters:\n  params (json_object, required): A JSON object containing the name/value pairs for the parameters to set\n\nReturns:\n  void\n",
                    /* aliases */ {}, false};
                store_method_metadata(network_set_advanced_node_parameters_method_metadata);
            }

            {
                // register method network_get_advanced_node_parameters
                cdcchain::api::MethodData network_get_advanced_node_parameters_method_metadata{ "network_get_advanced_node_parameters", nullptr,
                    /* description */ "Sets advanced node parameters, used for setting up automated tests",
                    /* returns */ "json_object",
                    /* params: */{                    },
                    /* prerequisites */ (cdcchain::api::MethodPrerequisites) 1,
                    /* detailed description */ "Sets advanced node parameters, used for setting up automated tests\n\nParameters:\n  (none)\n\nReturns:\n  json_object\n",
                    /* aliases */ {}, false};
                store_method_metadata(network_get_advanced_node_parameters_method_metadata);
            }

            {
                // register method network_get_transaction_propagation_data
                cdcchain::api::MethodData network_get_transaction_propagation_data_method_metadata{ "network_get_transaction_propagation_data", nullptr,
                    /* description */ "Returns the time the transaction was first seen by this client",
                    /* returns */ "message_propagation_data",
                    /* params: */{
                        {"transaction_id", "transaction_id", cdcchain::api::required_positional, fc::ovariant()}
                          },
                    /* prerequisites */ (cdcchain::api::MethodPrerequisites) 1,
                    /* detailed description */ "Returns the time the transaction was first seen by this client\n\nThis interrogates the p2p node's message cache to find out when it first saw this transaction. The data in the message cache is only kept for a few blocks, so you can only use this to ask about recent transactions. This is intended to be used to track message propagation delays in our test network.\n\nParameters:\n  transaction_id (transaction_id, required): the id of the transaction\n\nReturns:\n  message_propagation_data\n",
                    /* aliases */ {}, false};
                store_method_metadata(network_get_transaction_propagation_data_method_metadata);
            }

            {
                // register method network_get_block_propagation_data
                cdcchain::api::MethodData network_get_block_propagation_data_method_metadata{ "network_get_block_propagation_data", nullptr,
                    /* description */ "Returns the time the block was first seen by this client",
                    /* returns */ "message_propagation_data",
                    /* params: */{
                        {"block_hash", "block_id_type", cdcchain::api::required_positional, fc::ovariant()}
                          },
                    /* prerequisites */ (cdcchain::api::MethodPrerequisites) 1,
                    /* detailed description */ "Returns the time the block was first seen by this client\n\nThis interrogates the p2p node's message cache to find out when it first saw this block. The data in the message cache is only kept for a few blocks, so you can only use this to ask about recent transactions. This is intended to be used to track message propagation delays in our test network.\n\nParameters:\n  block_hash (block_id_type, required): the id of the block\n\nReturns:\n  message_propagation_data\n",
                    /* aliases */ {}, false};
                store_method_metadata(network_get_block_propagation_data_method_metadata);
            }

            {
                // register method network_get_info
                cdcchain::api::MethodData network_get_info_method_metadata{ "network_get_info", nullptr,
                    /* description */ "Returns assorted information about the network settings and connections",
                    /* returns */ "json_object",
                    /* params: */{                    },
                    /* prerequisites */ (cdcchain::api::MethodPrerequisites) 1,
                    /* detailed description */ "Returns assorted information about the network settings and connections\n\nParameters:\n  (none)\n\nReturns:\n  json_object\n",
                    /* aliases */ {}, false};
                store_method_metadata(network_get_info_method_metadata);
            }

            {
                // register method network_list_potential_peers
                cdcchain::api::MethodData network_list_potential_peers_method_metadata{ "network_list_potential_peers", nullptr,
                    /* description */ "Returns list of potential peers",
                    /* returns */ "potential_peer_entry_array",
                    /* params: */{                    },
                    /* prerequisites */ (cdcchain::api::MethodPrerequisites) 1,
                    /* detailed description */ "Returns list of potential peers\n\nParameters:\n  (none)\n\nReturns:\n  potential_peer_entry_array\n",
                    /* aliases */ {}, false};
                store_method_metadata(network_list_potential_peers_method_metadata);
            }

            {
                // register method network_get_upnp_info
                cdcchain::api::MethodData network_get_upnp_info_method_metadata{ "network_get_upnp_info", nullptr,
                    /* description */ "Get information on UPNP status including whether it's enabled and what the client believes its IP to be",
                    /* returns */ "json_object",
                    /* params: */{                    },
                    /* prerequisites */ (cdcchain::api::MethodPrerequisites) 1,
                    /* detailed description */ "Get information on UPNP status including whether it's enabled and what the client believes its IP to be\n\nParameters:\n  (none)\n\nReturns:\n  json_object\n",
                    /* aliases */ {}, false};
                store_method_metadata(network_get_upnp_info_method_metadata);
            }

            {
                // register method network_get_blocked_ips
                cdcchain::api::MethodData network_get_blocked_ips_method_metadata{ "network_get_blocked_ips", nullptr,
                    /* description */ "Get list of ips in blacklist",
                    /* returns */ "block_ip_array",
                    /* params: */{                    },
                    /* prerequisites */ (cdcchain::api::MethodPrerequisites) 1,
                    /* detailed description */ "Get list of ips in blacklist\n\nParameters:\n  (none)\n\nReturns:\n  block_ip_array\n",
                    /* aliases */ {}, false};
                store_method_metadata(network_get_blocked_ips_method_metadata);
            }

            {
                // register method debug_get_client_name
                cdcchain::api::MethodData debug_get_client_name_method_metadata{ "debug_get_client_name", nullptr,
                    /* description */ "Returns client's debug name specified in config.json",
                    /* returns */ "string",
                    /* params: */{                    },
                    /* prerequisites */ (cdcchain::api::MethodPrerequisites) 0,
                    /* detailed description */ "Returns client's debug name specified in config.json\n\nParameters:\n  (none)\n\nReturns:\n  string\n",
                    /* aliases */ {}, false};
                store_method_metadata(debug_get_client_name_method_metadata);
            }

            {
                // register method delegate_get_config
                cdcchain::api::MethodData delegate_get_config_method_metadata{ "delegate_get_config", nullptr,
                    /* description */ "Returns current settings used during local block production",
                    /* returns */ "variant",
                    /* params: */{                    },
                    /* prerequisites */ (cdcchain::api::MethodPrerequisites) 0,
                    /* detailed description */ "Returns current settings used during local block production\n\nParameters:\n  (none)\n\nReturns:\n  variant\n",
                    /* aliases */ {}, false};
                store_method_metadata(delegate_get_config_method_metadata);
            }

            {
                // register method delegate_set_network_min_connection_count
                cdcchain::api::MethodData delegate_set_network_min_connection_count_method_metadata{ "delegate_set_network_min_connection_count", nullptr,
                    /* description */ "Set minimum network connection count required for block production",
                    /* returns */ "void",
                    /* params: */{
                        {"count", "uint32_t", cdcchain::api::required_positional, fc::ovariant()}
                          },
                    /* prerequisites */ (cdcchain::api::MethodPrerequisites) 0,
                    /* detailed description */ "Set minimum network connection count required for block production\n\nParameters:\n  count (uint32_t, required): minimum network connection count\n\nReturns:\n  void\n",
                    /* aliases */ {}, false};
                store_method_metadata(delegate_set_network_min_connection_count_method_metadata);
            }

            {
                // register method delegate_set_block_max_transaction_count
                cdcchain::api::MethodData delegate_set_block_max_transaction_count_method_metadata{ "delegate_set_block_max_transaction_count", nullptr,
                    /* description */ "Set maximum number of transactions allowed in a block",
                    /* returns */ "void",
                    /* params: */{
                        {"count", "uint32_t", cdcchain::api::required_positional, fc::ovariant()}
                          },
                    /* prerequisites */ (cdcchain::api::MethodPrerequisites) 0,
                    /* detailed description */ "Set maximum number of transactions allowed in a block\n\nParameters:\n  count (uint32_t, required): maximum transaction count\n\nReturns:\n  void\n",
                    /* aliases */ {}, false};
                store_method_metadata(delegate_set_block_max_transaction_count_method_metadata);
            }

            {
                // register method delegate_set_soft_max_imessage_length
                cdcchain::api::MethodData delegate_set_soft_max_imessage_length_method_metadata{ "delegate_set_soft_max_imessage_length", nullptr,
                    /* description */ "Set soft max length",
                    /* returns */ "void",
                    /* params: */{
                        {"soft_length", "int64_t", cdcchain::api::required_positional, fc::ovariant()}
                          },
                    /* prerequisites */ (cdcchain::api::MethodPrerequisites) 0,
                    /* detailed description */ "Set soft max length\n\nParameters:\n  soft_length (int64_t, required): soft max length\n\nReturns:\n  void\n",
                    /* aliases */ {}, false};
                store_method_metadata(delegate_set_soft_max_imessage_length_method_metadata);
            }

            {
                // register method delegate_set_imessage_fee_coe
                cdcchain::api::MethodData delegate_set_imessage_fee_coe_method_metadata{ "delegate_set_imessage_fee_coe", nullptr,
                    /* description */ "Set fee coe",
                    /* returns */ "void",
                    /* params: */{
                        {"fee_coe", "string", cdcchain::api::required_positional, fc::ovariant()}
                          },
                    /* prerequisites */ (cdcchain::api::MethodPrerequisites) 0,
                    /* detailed description */ "Set fee coe\n\nParameters:\n  fee_coe (string, required): imessage fee coe\n\nReturns:\n  void\n",
                    /* aliases */ {}, false};
                store_method_metadata(delegate_set_imessage_fee_coe_method_metadata);
            }

            {
                // register method delegate_set_block_max_size
                cdcchain::api::MethodData delegate_set_block_max_size_method_metadata{ "delegate_set_block_max_size", nullptr,
                    /* description */ "Set maximum block size allowed",
                    /* returns */ "void",
                    /* params: */{
                        {"size", "uint32_t", cdcchain::api::required_positional, fc::ovariant()}
                          },
                    /* prerequisites */ (cdcchain::api::MethodPrerequisites) 0,
                    /* detailed description */ "Set maximum block size allowed\n\nParameters:\n  size (uint32_t, required): maximum block size in bytes\n\nReturns:\n  void\n",
                    /* aliases */ {}, false};
                store_method_metadata(delegate_set_block_max_size_method_metadata);
            }

            {
                // register method delegate_set_transaction_max_size
                cdcchain::api::MethodData delegate_set_transaction_max_size_method_metadata{ "delegate_set_transaction_max_size", nullptr,
                    /* description */ "Set maximum transaction size allowed",
                    /* returns */ "void",
                    /* params: */{
                        {"size", "uint32_t", cdcchain::api::required_positional, fc::ovariant()}
                          },
                    /* prerequisites */ (cdcchain::api::MethodPrerequisites) 0,
                    /* detailed description */ "Set maximum transaction size allowed\n\nParameters:\n  size (uint32_t, required): maximum transaction size in bytes\n\nReturns:\n  void\n",
                    /* aliases */ {}, false};
                store_method_metadata(delegate_set_transaction_max_size_method_metadata);
            }

            {
                // register method delegate_set_transaction_canonical_signatures_required
                cdcchain::api::MethodData delegate_set_transaction_canonical_signatures_required_method_metadata{ "delegate_set_transaction_canonical_signatures_required", nullptr,
                    /* description */ "Set whether canonical signatures are required",
                    /* returns */ "void",
                    /* params: */{
                        {"required", "bool", cdcchain::api::required_positional, fc::ovariant()}
                          },
                    /* prerequisites */ (cdcchain::api::MethodPrerequisites) 0,
                    /* detailed description */ "Set whether canonical signatures are required\n\nParameters:\n  required (bool, required): whether canonical signatures are required\n\nReturns:\n  void\n",
                    /* aliases */ {}, false};
                store_method_metadata(delegate_set_transaction_canonical_signatures_required_method_metadata);
            }

            {
                // register method delegate_set_transaction_min_fee
                cdcchain::api::MethodData delegate_set_transaction_min_fee_method_metadata{ "delegate_set_transaction_min_fee", nullptr,
                    /* description */ "Set minimum transaction fee allowed",
                    /* returns */ "void",
                    /* params: */{
                        {"fee", "string", cdcchain::api::required_positional, fc::ovariant()}
                          },
                    /* prerequisites */ (cdcchain::api::MethodPrerequisites) 0,
                    /* detailed description */ "Set minimum transaction fee allowed\n\nParameters:\n  fee (string, required): minimum transaction fee in shares\n\nReturns:\n  void\n",
                    /* aliases */ {}, false};
                store_method_metadata(delegate_set_transaction_min_fee_method_metadata);
            }

            {
                // register method delegate_blacklist_add_transaction
                cdcchain::api::MethodData delegate_blacklist_add_transaction_method_metadata{ "delegate_blacklist_add_transaction", nullptr,
                    /* description */ "Add specified transaction to blacklist",
                    /* returns */ "void",
                    /* params: */{
                        {"id", "transaction_id", cdcchain::api::required_positional, fc::ovariant()}
                          },
                    /* prerequisites */ (cdcchain::api::MethodPrerequisites) 0,
                    /* detailed description */ "Add specified transaction to blacklist\n\nParameters:\n  id (transaction_id, required): transaction to add to blacklist\n\nReturns:\n  void\n",
                    /* aliases */ {}, false};
                store_method_metadata(delegate_blacklist_add_transaction_method_metadata);
            }

            {
                // register method delegate_blacklist_remove_transaction
                cdcchain::api::MethodData delegate_blacklist_remove_transaction_method_metadata{ "delegate_blacklist_remove_transaction", nullptr,
                    /* description */ "Remove specified transaction from blacklist",
                    /* returns */ "void",
                    /* params: */{
                        {"id", "transaction_id", cdcchain::api::required_positional, fc::ovariant()}
                          },
                    /* prerequisites */ (cdcchain::api::MethodPrerequisites) 0,
                    /* detailed description */ "Remove specified transaction from blacklist\n\nParameters:\n  id (transaction_id, required): transaction to remove from blacklist\n\nReturns:\n  void\n",
                    /* aliases */ {}, false};
                store_method_metadata(delegate_blacklist_remove_transaction_method_metadata);
            }

            {
                // register method delegate_blacklist_add_operation
                cdcchain::api::MethodData delegate_blacklist_add_operation_method_metadata{ "delegate_blacklist_add_operation", nullptr,
                    /* description */ "Add specified operation to blacklist",
                    /* returns */ "void",
                    /* params: */{
                        {"id", "operation_type", cdcchain::api::required_positional, fc::ovariant()}
                          },
                    /* prerequisites */ (cdcchain::api::MethodPrerequisites) 0,
                    /* detailed description */ "Add specified operation to blacklist\n\nParameters:\n  id (operation_type, required): operation to add to blacklist\n\nReturns:\n  void\n",
                    /* aliases */ {}, false};
                store_method_metadata(delegate_blacklist_add_operation_method_metadata);
            }

            {
                // register method delegate_blacklist_remove_operation
                cdcchain::api::MethodData delegate_blacklist_remove_operation_method_metadata{ "delegate_blacklist_remove_operation", nullptr,
                    /* description */ "Remove specified operation from blacklist",
                    /* returns */ "void",
                    /* params: */{
                        {"id", "operation_type", cdcchain::api::required_positional, fc::ovariant()}
                          },
                    /* prerequisites */ (cdcchain::api::MethodPrerequisites) 0,
                    /* detailed description */ "Remove specified operation from blacklist\n\nParameters:\n  id (operation_type, required): operation to remove from blacklist\n\nReturns:\n  void\n",
                    /* aliases */ {}, false};
                store_method_metadata(delegate_blacklist_remove_operation_method_metadata);
            }


            {
                // register method wallet_get_info
                cdcchain::api::MethodData wallet_get_info_method_metadata{ "wallet_get_info", nullptr,
                    /* description */ "Extra information about the wallet.",
                    /* returns */ "json_object",
                    /* params: */{                    },
                    /* prerequisites */ (cdcchain::api::MethodPrerequisites) 1,
                    /* detailed description */ "Extra information about the wallet.\n\nParameters:\n  (none)\n\nReturns:\n  json_object\n",
                    /* aliases */ {}, false};
                store_method_metadata(wallet_get_info_method_metadata);
            }

            {
                // register method wallet_open
                cdcchain::api::MethodData wallet_open_method_metadata{ "wallet_open", nullptr,
                    /* description */ "Opens the wallet of the given name",
                    /* returns */ "void",
                    /* params: */{
                        {"wallet_name", "wallet_name", cdcchain::api::required_positional, fc::ovariant()}
                          },
                    /* prerequisites */ (cdcchain::api::MethodPrerequisites) 1,
                    /* detailed description */ "Opens the wallet of the given name\n\nParameters:\n  wallet_name (wallet_name, required): the name of the wallet to open\n\nReturns:\n  void\n",
                    /* aliases */ {"open"}, false};
                store_method_metadata(wallet_open_method_metadata);
            }

            {
                // register method wallet_create
                cdcchain::api::MethodData wallet_create_method_metadata{ "wallet_create", nullptr,
                    /* description */ "Creates a wallet with the given name",
                    /* returns */ "void",
                    /* params: */{
                        {"wallet_name", "wallet_name", cdcchain::api::required_positional, fc::ovariant()},
                        {"new_passphrase", "new_passphrase", cdcchain::api::required_positional, fc::ovariant()},
                        {"brain_key", "brainkey", cdcchain::api::optional_positional, fc::variant(fc::json::from_string("\"\""))}
                          },
                    /* prerequisites */ (cdcchain::api::MethodPrerequisites) 1,
                    /* detailed description */ "Creates a wallet with the given name\n\nParameters:\n  wallet_name (wallet_name, required): name of the wallet to create\n  new_passphrase (new_passphrase, required): a passphrase for encrypting the wallet\n  brain_key (brainkey, optional, defaults to \"\"): a strong passphrase that will be used to generate all private keys, defaults to a large random number\n\nReturns:\n  void\n",
                    /* aliases */ {"create"}, false};
                store_method_metadata(wallet_create_method_metadata);
            }

            {
                // register method wallet_get_name
                cdcchain::api::MethodData wallet_get_name_method_metadata{ "wallet_get_name", nullptr,
                    /* description */ "Returns the wallet name passed to wallet_open",
                    /* returns */ "optional_wallet_name",
                    /* params: */{                    },
                    /* prerequisites */ (cdcchain::api::MethodPrerequisites) 0,
                    /* detailed description */ "Returns the wallet name passed to wallet_open\n\nParameters:\n  (none)\n\nReturns:\n  optional_wallet_name\n",
                    /* aliases */ {}, false};
                store_method_metadata(wallet_get_name_method_metadata);
            }

            {
                // register method wallet_import_private_key
                cdcchain::api::MethodData wallet_import_private_key_method_metadata{ "wallet_import_private_key", nullptr,
                    /* description */ "Loads the private key into the specified account. Returns which account it was actually imported to.",
                    /* returns */ "account_name",
                    /* params: */{
                        {"wif_key", "wif_private_key", cdcchain::api::required_positional, fc::ovariant()},
                        {"account_name", "account_name", cdcchain::api::optional_positional, fc::variant(fc::json::from_string("null"))},
                        {"create_new_account", "bool", cdcchain::api::optional_positional, fc::variant(fc::json::from_string("false"))},
                        {"rescan", "bool", cdcchain::api::optional_positional, fc::variant(fc::json::from_string("false"))}
                          },
                    /* prerequisites */ (cdcchain::api::MethodPrerequisites) 4,
                    /* detailed description */ "Loads the private key into the specified account. Returns which account it was actually imported to.\n\nParameters:\n  wif_key (wif_private_key, required): A private key in bitcoin Wallet Import Format (WIF)\n  account_name (account_name, optional, defaults to null): the name of the account the key should be imported into, if null then the key must belong to an active account\n  create_new_account (bool, optional, defaults to false): If true, the wallet will attempt to create a new account for the name provided rather than import the key into an existing account\n  rescan (bool, optional, defaults to false): If true, the wallet will rescan the blockchain looking for transactions that involve this private key\n\nReturns:\n  account_name\n",
                    /* aliases */ {"import_key", "importprivkey"}, false};
                store_method_metadata(wallet_import_private_key_method_metadata);
            }

            {
                // register method wallet_import_ethereum_private_key
                cdcchain::api::MethodData wallet_import_ethereum_private_key_method_metadata{ "wallet_import_ethereum_private_key", nullptr,
                    /* description */ "Loads the ethereum private key into the specified account. Returns which account it was actually imported to.",
                    /* returns */ "account_name",
                    /* params: */{
                        { "priv_key_str", "string", cdcchain::api::required_positional, fc::ovariant() },
                { "account_name", "account_name", cdcchain::api::optional_positional, fc::variant(fc::json::from_string("null")) },
                { "create_new_account", "bool", cdcchain::api::optional_positional, fc::variant(fc::json::from_string("false")) },
                { "rescan", "bool", cdcchain::api::optional_positional, fc::variant(fc::json::from_string("false")) }
                },
                    /* prerequisites */ (cdcchain::api::MethodPrerequisites) 4,
                    /* detailed description */ "Loads the ethereum private key into the specified account. Returns which account it was actually imported to.\n\nParameters:\n  priv_key_str (string, required): A private key of ethereum\n  account_name (account_name, optional, defaults to null): the name of the account the key should be imported into, if null then the key must belong to an active account\n  create_new_account (bool, optional, defaults to false): If true, the wallet will attempt to create a new account for the name provided rather than import the key into an existing account\n  rescan (bool, optional, defaults to false): If true, the wallet will rescan the blockchain looking for transactions that involve this private key\n\nReturns:\n  account_name\n",
                    /* aliases */{}, false };
                store_method_metadata(wallet_import_ethereum_private_key_method_metadata);
            }

            {
                // register method wallet_close
                cdcchain::api::MethodData wallet_close_method_metadata{ "wallet_close", nullptr,
                    /* description */ "Closes the curent wallet if one is open",
                    /* returns */ "void",
                    /* params: */{                    },
                    /* prerequisites */ (cdcchain::api::MethodPrerequisites) 0,
                    /* detailed description */ "Closes the curent wallet if one is open\n\nParameters:\n  (none)\n\nReturns:\n  void\n",
                    /* aliases */ {"close"}, false};
                store_method_metadata(wallet_close_method_metadata);
            }

            {
                // register method wallet_backup_create
                cdcchain::api::MethodData wallet_backup_create_method_metadata{ "wallet_backup_create", nullptr,
                    /* description */ "Exports the current wallet to a JSON file",
                    /* returns */ "void",
                    /* params: */{
                        {"json_filename", "filename", cdcchain::api::required_positional, fc::ovariant()}
                          },
                    /* prerequisites */ (cdcchain::api::MethodPrerequisites) 2,
                    /* detailed description */ "Exports the current wallet to a JSON file\n\nParameters:\n  json_filename (filename, required): the full path and filename of JSON file to generate\n\nReturns:\n  void\n",
                    /* aliases */ {"backupwallet", "wallet_export_to_json"}, false};
                store_method_metadata(wallet_backup_create_method_metadata);
            }

            {
                // register method wallet_backup_restore
                cdcchain::api::MethodData wallet_backup_restore_method_metadata{ "wallet_backup_restore", nullptr,
                    /* description */ "Creates a new wallet from an exported JSON file",
                    /* returns */ "void",
                    /* params: */{
                        {"json_filename", "filename", cdcchain::api::required_positional, fc::ovariant()},
                        {"wallet_name", "wallet_name", cdcchain::api::required_positional, fc::ovariant()},
                        {"imported_wallet_passphrase", "passphrase", cdcchain::api::required_positional, fc::ovariant()}
                          },
                    /* prerequisites */ (cdcchain::api::MethodPrerequisites) 1,
                    /* detailed description */ "Creates a new wallet from an exported JSON file\n\nParameters:\n  json_filename (filename, required): the full path and filename of JSON wallet to import\n  wallet_name (wallet_name, required): name of the wallet to create\n  imported_wallet_passphrase (passphrase, required): passphrase of the imported wallet\n\nReturns:\n  void\n",
                    /* aliases */ {"wallet_create_from_json"}, false};
                store_method_metadata(wallet_backup_restore_method_metadata);
            }

            {
                // register method wallet_set_automatic_backups
                cdcchain::api::MethodData wallet_set_automatic_backups_method_metadata{ "wallet_set_automatic_backups", nullptr,
                    /* description */ "Enables or disables automatic wallet backups",
                    /* returns */ "bool",
                    /* params: */{
                        {"enabled", "bool", cdcchain::api::required_positional, fc::ovariant()}
                          },
                    /* prerequisites */ (cdcchain::api::MethodPrerequisites) 2,
                    /* detailed description */ "Enables or disables automatic wallet backups\n\nParameters:\n  enabled (bool, required): true to enable and false to disable\n\nReturns:\n  bool\n",
                    /* aliases */ {"auto_backup", "autobackup"}, false};
                store_method_metadata(wallet_set_automatic_backups_method_metadata);
            }

            {
                // register method wallet_set_transaction_expiration_time
                cdcchain::api::MethodData wallet_set_transaction_expiration_time_method_metadata{ "wallet_set_transaction_expiration_time", nullptr,
                    /* description */ "Set transaction expiration time",
                    /* returns */ "uint32_t",
                    /* params: */{
                        {"seconds", "uint32_t", cdcchain::api::required_positional, fc::ovariant()}
                          },
                    /* prerequisites */ (cdcchain::api::MethodPrerequisites) 2,
                    /* detailed description */ "Set transaction expiration time\n\nParameters:\n  seconds (uint32_t, required): seconds before new transactions expire\n\nReturns:\n  uint32_t\n",
                    /* aliases */ {"set_expiration"}, false};
                store_method_metadata(wallet_set_transaction_expiration_time_method_metadata);
            }

            {
                // register method wallet_account_transaction_history
                cdcchain::api::MethodData wallet_account_transaction_history_method_metadata{ "wallet_account_transaction_history", nullptr,
                    /* description */ "Lists transaction history for the specified account",
                    /* returns */ "pretty_transactions",
                    /* params: */{
                        {"account_name", "string", cdcchain::api::optional_positional, fc::variant(fc::json::from_string("\"\""))},
                        {"asset_symbol", "string", cdcchain::api::optional_positional, fc::variant(fc::json::from_string("\"\""))},
                        {"limit", "int32_t", cdcchain::api::optional_positional, fc::variant(fc::json::from_string("0"))},
                        {"start_block_num", "uint32_t", cdcchain::api::optional_positional, fc::variant(fc::json::from_string("0"))},
                        {"end_block_num", "uint32_t", cdcchain::api::optional_positional, fc::variant(fc::json::from_string("-1"))}
                          },
                    /* prerequisites */ (cdcchain::api::MethodPrerequisites) 2,
                    /* detailed description */ "Lists transaction history for the specified account\n\nParameters:\n  account_name (string, optional, defaults to \"\"): the name of the account for which the transaction history will be returned, \"\" for all accounts\n  asset_symbol (string, optional, defaults to \"\"): only include transactions involving the specified asset, or \"\" to include all\n  limit (int32_t, optional, defaults to 0): limit the number of returned transactions; negative for most recent and positive for least recent. 0 does not limit\n  start_block_num (uint32_t, optional, defaults to 0): the earliest block number to list transactions from; 0 to include all transactions starting from genesis\n  end_block_num (uint32_t, optional, defaults to -1): the latest block to list transaction from; -1 to include all transactions ending at the head block\n\nReturns:\n  pretty_transactions\n",
                    /* aliases */ {"history", "listtransactions"}, false};
                store_method_metadata(wallet_account_transaction_history_method_metadata);
            }

            {
                // register method wallet_transaction_history_splite
                cdcchain::api::MethodData wallet_transaction_history_splite_method_metadata{ "wallet_transaction_history_splite", nullptr,
                    /* description */ "Lists transaction history for the specified account",
                    /* returns */ "pretty_transactions",
                    /* params: */{
                        {"account_name", "string", cdcchain::api::optional_positional, fc::variant(fc::json::from_string("\"\""))},
                        {"asset_symbol", "string", cdcchain::api::optional_positional, fc::variant(fc::json::from_string("\"\""))},
                        {"limit", "int32_t", cdcchain::api::optional_positional, fc::variant(fc::json::from_string("0"))},
                        {"transaction_type", "int32_t", cdcchain::api::optional_positional, fc::variant(fc::json::from_string("\"2\""))}
                          },
                    /* prerequisites */ (cdcchain::api::MethodPrerequisites) 2,
                    /* detailed description */ "Lists transaction history for the specified account\n\nParameters:\n  account_name (string, optional, defaults to \"\"): the name of the account for which the transaction history will be returned, \"\" for all accounts\n  asset_symbol (string, optional, defaults to \"\"): only include transactions involving the specified asset, or \"\" to include all\n  limit (int32_t, optional, defaults to 0): limit the number of returned transactions; negative for most recent and positive for least recent. 0 does not limit\n  transaction_type (int32_t, optional, defaults to \"2\"): transaction type\n\nReturns:\n  pretty_transactions\n",
                    /* aliases */ {}, false};
                store_method_metadata(wallet_transaction_history_splite_method_metadata);
            }

            {
                // register method wallet_account_historic_balance
                cdcchain::api::MethodData wallet_account_historic_balance_method_metadata{ "wallet_account_historic_balance", nullptr,
                    /* description */ "Lists wallet's balance at the given time",
                    /* returns */ "account_balance_summary_type",
                    /* params: */{
                        {"time", "timestamp", cdcchain::api::required_positional, fc::ovariant()},
                        {"account_name", "string", cdcchain::api::optional_positional, fc::variant(fc::json::from_string("\"\""))}
                          },
                    /* prerequisites */ (cdcchain::api::MethodPrerequisites) 2,
                    /* detailed description */ "Lists wallet's balance at the given time\n\nParameters:\n  time (timestamp, required): the date and time for which the balance will be computed\n  account_name (string, optional, defaults to \"\"): the name of the account for which the historic balance will be returned, \"\" for all accounts\n\nReturns:\n  account_balance_summary_type\n",
                    /* aliases */ {}, false};
                store_method_metadata(wallet_account_historic_balance_method_metadata);
            }

            {
                // register method wallet_remove_transaction
                cdcchain::api::MethodData wallet_remove_transaction_method_metadata{ "wallet_remove_transaction", nullptr,
                    /* description */ "Removes the specified transaction entry from your transaction history. USE WITH CAUTION! Rescan cannot reconstruct all transaction details",
                    /* returns */ "void",
                    /* params: */{
                        {"transaction_id", "string", cdcchain::api::required_positional, fc::ovariant()}
                          },
                    /* prerequisites */ (cdcchain::api::MethodPrerequisites) 4,
                    /* detailed description */ "Removes the specified transaction entry from your transaction history. USE WITH CAUTION! Rescan cannot reconstruct all transaction details\n\nParameters:\n  transaction_id (string, required): the id (or id prefix) of the transaction entry\n\nReturns:\n  void\n",
                    /* aliases */ {"remove_transaction", "wallet_transaction_remove"}, false};
                store_method_metadata(wallet_remove_transaction_method_metadata);
            }

            {
                // register method wallet_get_pending_transaction_errors
                cdcchain::api::MethodData wallet_get_pending_transaction_errors_method_metadata{ "wallet_get_pending_transaction_errors", nullptr,
                    /* description */ "Return any errors for your currently pending transactions",
                    /* returns */ "map<transaction_id_type, fc::exception>",
                    /* params: */{
                        {"filename", "path", cdcchain::api::optional_positional, fc::variant(fc::json::from_string("\"\""))}
                          },
                    /* prerequisites */ (cdcchain::api::MethodPrerequisites) 2,
                    /* detailed description */ "Return any errors for your currently pending transactions\n\nParameters:\n  filename (path, optional, defaults to \"\"): filename to save pending transaction errors to\n\nReturns:\n  map<transaction_id_type, fc::exception>\n",
                    /* aliases */ {}, false};
                store_method_metadata(wallet_get_pending_transaction_errors_method_metadata);
            }

            {
                // register method wallet_lock
                cdcchain::api::MethodData wallet_lock_method_metadata{ "wallet_lock", nullptr,
                    /* description */ "Lock the private keys in wallet, disables spending commands until unlocked",
                    /* returns */ "void",
                    /* params: */{                    },
                    /* prerequisites */ (cdcchain::api::MethodPrerequisites) 2,
                    /* detailed description */ "Lock the private keys in wallet, disables spending commands until unlocked\n\nParameters:\n  (none)\n\nReturns:\n  void\n",
                    /* aliases */ {"lock"}, false};
                store_method_metadata(wallet_lock_method_metadata);
            }

            {
                // register method wallet_unlock
                cdcchain::api::MethodData wallet_unlock_method_metadata{ "wallet_unlock", nullptr,
                    /* description */ "Unlock the private keys in the wallet to enable spending operations",
                    /* returns */ "void",
                    /* params: */{
                        {"timeout", "uint32_t", cdcchain::api::required_positional, fc::ovariant()},
                        {"passphrase", "passphrase", cdcchain::api::required_positional, fc::ovariant()}
                          },
                    /* prerequisites */ (cdcchain::api::MethodPrerequisites) 2,
                    /* detailed description */ "Unlock the private keys in the wallet to enable spending operations\n\nParameters:\n  timeout (uint32_t, required): the number of seconds to keep the wallet unlocked\n  passphrase (passphrase, required): the passphrase for encrypting the wallet\n\nReturns:\n  void\n",
                    /* aliases */ {"unlock", "walletpassphrase"}, false};
                store_method_metadata(wallet_unlock_method_metadata);
            }

            {
                // register method wallet_change_passphrase
                cdcchain::api::MethodData wallet_change_passphrase_method_metadata{ "wallet_change_passphrase", nullptr,
                    /* description */ "Change the password of the current wallet",
                    /* returns */ "void",
                    /* params: */{
                        {"old_passphrase", "passphrase", cdcchain::api::required_positional, fc::ovariant()},
                        {"passphrase", "passphrase", cdcchain::api::required_positional, fc::ovariant()}
                          },
                    /* prerequisites */ (cdcchain::api::MethodPrerequisites) 4,
                    /* detailed description */ "Change the password of the current wallet\n\nThis will change the wallet's spending passphrase, please make sure you remember it.\n\nParameters:\n  old_passphrase (passphrase, required): the old passphrase for this wallet\n  passphrase (passphrase, required): the passphrase for encrypting the wallet\n\nReturns:\n  void\n",
                    /* aliases */ {"walletpassphrasechange"}, false};
                store_method_metadata(wallet_change_passphrase_method_metadata);
            }

            {
                // register method wallet_check_passphrase
                cdcchain::api::MethodData wallet_check_passphrase_method_metadata{ "wallet_check_passphrase", nullptr,
                    /* description */ "check the password of the current wallet",
                    /* returns */ "bool",
                    /* params: */{
                        {"passphrase", "passphrase", cdcchain::api::required_positional, fc::ovariant()}
                          },
                    /* prerequisites */ (cdcchain::api::MethodPrerequisites) 4,
                    /* detailed description */ "check the password of the current wallet\n\nThis will check the wallet's spending passphrase.\n\nParameters:\n  passphrase (passphrase, required): the passphrase to be checking\n\nReturns:\n  bool\n",
                    /* aliases */ {"check_passphrase", "check_password"}, false};
                store_method_metadata(wallet_check_passphrase_method_metadata);
            }

            {
                // register method wallet_check_address
                cdcchain::api::MethodData wallet_check_address_method_metadata{ "wallet_check_address", nullptr,
                    /* description */ "check address is valid address or an acount name.",
                    /* returns */ "bool",
                    /* params: */{
                        {"address", "string", cdcchain::api::required_positional, fc::ovariant()}
                          },
                    /* prerequisites */ (cdcchain::api::MethodPrerequisites) 2,
                    /* detailed description */ "check address is valid address or an acount name.\n\nThis will check the address.\n\nParameters:\n  address (string, required): the address/accountname to be checking (string, required)\n\nReturns:\n  bool\n",
                    /* aliases */ {"check_address"}, false};
                store_method_metadata(wallet_check_address_method_metadata);
            }

            {
                // register method wallet_list
                cdcchain::api::MethodData wallet_list_method_metadata{ "wallet_list", nullptr,
                    /* description */ "Return a list of wallets in the current data directory",
                    /* returns */ "wallet_name_array",
                    /* params: */{                    },
                    /* prerequisites */ (cdcchain::api::MethodPrerequisites) 1,
                    /* detailed description */ "Return a list of wallets in the current data directory\n\nParameters:\n  (none)\n\nReturns:\n  wallet_name_array\n",
                    /* aliases */ {}, false};
                store_method_metadata(wallet_list_method_metadata);
            }

            {
                // register method wallet_account_create
                cdcchain::api::MethodData wallet_account_create_method_metadata{ "wallet_account_create", nullptr,
                    /* description */ "Add new account for receiving payments",
                    /* returns */ "address",
                    /* params: */{
                        {"account_name", "account_name", cdcchain::api::required_positional, fc::ovariant()},
                        {"private_data", "json_variant", cdcchain::api::optional_positional, fc::variant(fc::json::from_string("null"))}
                          },
                    /* prerequisites */ (cdcchain::api::MethodPrerequisites) 4,
                    /* detailed description */ "Add new account for receiving payments\n\nParameters:\n  account_name (account_name, required): the name you will use to refer to this receive account\n  private_data (json_variant, optional, defaults to null): Extra data to store with this account entry\n\nReturns:\n  address\n",
                    /* aliases */ {"wallet_create_account", "create_account"}, false};
                store_method_metadata(wallet_account_create_method_metadata);
            }

            {
                // register method wallet_account_set_approval
                cdcchain::api::MethodData wallet_account_set_approval_method_metadata{ "wallet_account_set_approval", nullptr,
                    /* description */ "Updates your approval of the specified account",
                    /* returns */ "int8_t",
                    /* params: */{
                        {"account_name", "account_name", cdcchain::api::required_positional, fc::ovariant()},
                        {"approval", "int8_t", cdcchain::api::optional_positional, fc::variant(fc::json::from_string("1"))}
                          },
                    /* prerequisites */ (cdcchain::api::MethodPrerequisites) 2,
                    /* detailed description */ "Updates your approval of the specified account\n\nParameters:\n  account_name (account_name, required): the name of the account to set approval for\n  approval (int8_t, optional, defaults to 1): 1, 0, or -1 respectively for approve, neutral, or disapprove\n\nReturns:\n  int8_t\n",
                    /* aliases */ {"approve", "set_approval", "wallet_approve_delegate", "wallet_approve"}, false};
                store_method_metadata(wallet_account_set_approval_method_metadata);
            }

            {
                // register method wallet_get_all_approved_accounts
                cdcchain::api::MethodData wallet_get_all_approved_accounts_method_metadata{ "wallet_get_all_approved_accounts", nullptr,
                    /* description */ "Return all approved account entrys",
                    /* returns */ "account_entry_array",
                    /* params: */{
                        {"approval", "int8_t", cdcchain::api::optional_positional, fc::variant(fc::json::from_string("1"))}
                          },
                    /* prerequisites */ (cdcchain::api::MethodPrerequisites) 2,
                    /* detailed description */ "Return all approved account entrys\n\nParameters:\n  approval (int8_t, optional, defaults to 1): 1, 0, or -1 respectively for approve, neutral, or disapprove\n\nReturns:\n  account_entry_array\n",
                    /* aliases */ {"all_approved_accounts", "approved_accounts"}, false};
                store_method_metadata(wallet_get_all_approved_accounts_method_metadata);
            }

            {
                // register method wallet_address_create
                cdcchain::api::MethodData wallet_address_create_method_metadata{ "wallet_address_create", nullptr,
                    /* description */ "Creates an address which can be used for a simple (non-TITAN) transfer.",
                    /* returns */ "string",
                    /* params: */{
                        {"account_name", "string", cdcchain::api::required_positional, fc::ovariant()},
                        {"label", "string", cdcchain::api::optional_positional, fc::variant(fc::json::from_string("\"\""))},
                        {"legacy_network_byte", "int32_t", cdcchain::api::optional_positional, fc::variant(fc::json::from_string("-1"))}
                          },
                    /* prerequisites */ (cdcchain::api::MethodPrerequisites) 2,
                    /* detailed description */ "Creates an address which can be used for a simple (non-TITAN) transfer.\n\nParameters:\n  account_name (string, required): The account name that will own this address\n  label (string, optional, defaults to \"\"): \n  legacy_network_byte (int32_t, optional, defaults to -1): If not -1, use this as the network byte for a BTC-style address.\n\nReturns:\n  string\n",
                    /* aliases */ {"new_address"}, false};
                store_method_metadata(wallet_address_create_method_metadata);
            }

            {
                // register method wallet_transfer_to_address
                cdcchain::api::MethodData wallet_transfer_to_address_method_metadata{ "wallet_transfer_to_address", nullptr,
                    /* description */ "Do a simple (non-TITAN) transfer to an address",
                    /* returns */ "transaction_entry",
                    /* params: */{
                        {"amount_to_transfer", "string", cdcchain::api::required_positional, fc::ovariant()},
                        {"asset_symbol", "asset_symbol", cdcchain::api::required_positional, fc::ovariant()},
                        {"from_account_name", "account_name", cdcchain::api::required_positional, fc::ovariant()},
                        {"to_address", "string", cdcchain::api::required_positional, fc::ovariant()},
                        {"memo_message", "information", cdcchain::api::optional_positional, fc::variant(fc::json::from_string("\"\""))},
                        {"strategy", "vote_strategy", cdcchain::api::optional_positional, fc::variant(fc::json::from_string("\"vote_recommended\""))}
                          },
                    /* prerequisites */ (cdcchain::api::MethodPrerequisites) 2,
                    /* detailed description */ "Do a simple (non-TITAN) transfer to an address\n\nParameters:\n  amount_to_transfer (string, required): the amount of shares to transfer\n  asset_symbol (asset_symbol, required): the asset to transfer\n  from_account_name (account_name, required): the source account to draw the shares from\n  to_address (string, required): the address or pubkey to transfer to\n  memo_message (information, optional, defaults to \"\"): a memo to store with the transaction\n  strategy (vote_strategy, optional, defaults to \"vote_recommended\"): enumeration [vote_none | vote_all | vote_random | vote_recommended] \n\nReturns:\n  transaction_entry\n",
                    /* aliases */ {}, false};
                store_method_metadata(wallet_transfer_to_address_method_metadata);
            }

            {
                // register method wallet_transfer_to_public_account
                cdcchain::api::MethodData wallet_transfer_to_public_account_method_metadata{ "wallet_transfer_to_public_account", nullptr,
                    /* description */ "Sends given amount to the given account",
                    /* returns */ "transaction_entry",
                    /* params: */{
                        {"amount_to_transfer", "string", cdcchain::api::required_positional, fc::ovariant()},
                        {"asset_symbol", "asset_symbol", cdcchain::api::required_positional, fc::ovariant()},
                        {"from_account_name", "sending_account_name", cdcchain::api::required_positional, fc::ovariant()},
                        {"to_account_name", "receive_account_name", cdcchain::api::required_positional, fc::ovariant()},
                        {"memo_message", "information", cdcchain::api::optional_positional, fc::variant(fc::json::from_string("\"\""))},
                        {"strategy", "vote_strategy", cdcchain::api::optional_positional, fc::variant(fc::json::from_string("\"vote_recommended\""))}
                          },
                    /* prerequisites */ (cdcchain::api::MethodPrerequisites) 4,
                    /* detailed description */ "Sends given amount to the given account\n\nParameters:\n  amount_to_transfer (string, required): the amount of shares to transfer\n  asset_symbol (asset_symbol, required): the asset to transfer\n  from_account_name (sending_account_name, required): the source account to draw the shares from\n  to_account_name (receive_account_name, required): the account to transfer the shares to\n  memo_message (information, optional, defaults to \"\"): a memo to store with the transaction\n  strategy (vote_strategy, optional, defaults to \"vote_recommended\"): enumeration [vote_none | vote_all | vote_random | vote_recommended] \n\nReturns:\n  transaction_entry\n",
                    /* aliases */ {"transfer_public"}, false};
                store_method_metadata(wallet_transfer_to_public_account_method_metadata);
            }

            {
                // register method wallet_withdraw_from_address
                cdcchain::api::MethodData wallet_withdraw_from_address_method_metadata{ "wallet_withdraw_from_address", nullptr,
                    /* description */ "",
                    /* returns */ "transaction_builder",
                    /* params: */{
                        {"amount", "string", cdcchain::api::required_positional, fc::ovariant()},
                        {"symbol", "string", cdcchain::api::required_positional, fc::ovariant()},
                        {"from_address", "address", cdcchain::api::required_positional, fc::ovariant()},
                        {"to", "string", cdcchain::api::required_positional, fc::ovariant()},
                        {"strategy", "vote_strategy", cdcchain::api::optional_positional, fc::variant(fc::json::from_string("\"vote_none\""))},
                        {"sign_and_broadcast", "bool", cdcchain::api::optional_positional, fc::variant(fc::json::from_string("true"))},
                        {"builder_path", "string", cdcchain::api::optional_positional, fc::variant(fc::json::from_string("\"\""))}
                          },
                    /* prerequisites */ (cdcchain::api::MethodPrerequisites) 1,
                    /* detailed description */ "\n\nParameters:\n  amount (string, required): how much to transfer\n  symbol (string, required): which asset\n  from_address (address, required): the balance address to withdraw from\n  to (string, required): address or account to receive funds\n  strategy (vote_strategy, optional, defaults to \"vote_none\"): enumeration [vote_none | vote_all | vote_random | vote_recommended] \n  sign_and_broadcast (bool, optional, defaults to true): \n  builder_path (string, optional, defaults to \"\"): If specified, will write builder here instead of to DATA_DIR/transactions/latest.trx\n\nReturns:\n  transaction_builder\n",
                    /* aliases */ {"withdraw_from_address"}, false};
                store_method_metadata(wallet_withdraw_from_address_method_metadata);
            }

            {
                // register method wallet_rescan_blockchain
                cdcchain::api::MethodData wallet_rescan_blockchain_method_metadata{ "wallet_rescan_blockchain", nullptr,
                    /* description */ "Scans the blockchain history for operations relevant to this wallet.",
                    /* returns */ "void",
                    /* params: */{
                        {"start_block_num", "uint32_t", cdcchain::api::optional_positional, fc::variant(fc::json::from_string("0"))},
                        {"limit", "uint32_t", cdcchain::api::optional_positional, fc::variant(fc::json::from_string("-1"))}
                          },
                    /* prerequisites */ (cdcchain::api::MethodPrerequisites) 4,
                    /* detailed description */ "Scans the blockchain history for operations relevant to this wallet.\n\nParameters:\n  start_block_num (uint32_t, optional, defaults to 0): the first block to scan\n  limit (uint32_t, optional, defaults to -1): the maximum number of blocks to scan\n\nReturns:\n  void\n",
                    /* aliases */ {"scan", "rescan"}, false};
                store_method_metadata(wallet_rescan_blockchain_method_metadata);
            }

            {
                // register method wallet_cancel_scan
                cdcchain::api::MethodData wallet_cancel_scan_method_metadata{ "wallet_cancel_scan", nullptr,
                    /* description */ "Cancel any current scan task",
                    /* returns */ "void",
                    /* params: */{                    },
                    /* prerequisites */ (cdcchain::api::MethodPrerequisites) 4,
                    /* detailed description */ "Cancel any current scan task\n\nParameters:\n  (none)\n\nReturns:\n  void\n",
                    /* aliases */ {}, false};
                store_method_metadata(wallet_cancel_scan_method_metadata);
            }

            {
                // register method wallet_get_transaction
                cdcchain::api::MethodData wallet_get_transaction_method_metadata{ "wallet_get_transaction", nullptr,
                    /* description */ "Queries your wallet for the specified transaction",
                    /* returns */ "transaction_entry",
                    /* params: */{
                        {"transaction_id", "string", cdcchain::api::required_positional, fc::ovariant()}
                          },
                    /* prerequisites */ (cdcchain::api::MethodPrerequisites) 2,
                    /* detailed description */ "Queries your wallet for the specified transaction\n\nParameters:\n  transaction_id (string, required): the id (or id prefix) of the transaction\n\nReturns:\n  transaction_entry\n",
                    /* aliases */ {"get_transaction"}, false};
                store_method_metadata(wallet_get_transaction_method_metadata);
            }

            {
                // register method wallet_scan_transaction
                cdcchain::api::MethodData wallet_scan_transaction_method_metadata{ "wallet_scan_transaction", nullptr,
                    /* description */ "Scans the specified transaction",
                    /* returns */ "transaction_entry",
                    /* params: */{
                        {"transaction_id", "string", cdcchain::api::required_positional, fc::ovariant()},
                        {"overwrite_existing", "bool", cdcchain::api::optional_positional, fc::variant(fc::json::from_string("false"))}
                          },
                    /* prerequisites */ (cdcchain::api::MethodPrerequisites) 4,
                    /* detailed description */ "Scans the specified transaction\n\nParameters:\n  transaction_id (string, required): the id (or id prefix) of the transaction\n  overwrite_existing (bool, optional, defaults to false): true to overwrite existing wallet transaction entry and false otherwise\n\nReturns:\n  transaction_entry\n",
                    /* aliases */ {"scan_transaction", "wallet_transaction_scan"}, false};
                store_method_metadata(wallet_scan_transaction_method_metadata);
            }

            {
                // register method wallet_rebroadcast_transaction
                cdcchain::api::MethodData wallet_rebroadcast_transaction_method_metadata{ "wallet_rebroadcast_transaction", nullptr,
                    /* description */ "Rebroadcasts the specified transaction",
                    /* returns */ "void",
                    /* params: */{
                        {"transaction_id", "string", cdcchain::api::required_positional, fc::ovariant()}
                          },
                    /* prerequisites */ (cdcchain::api::MethodPrerequisites) 2,
                    /* detailed description */ "Rebroadcasts the specified transaction\n\nParameters:\n  transaction_id (string, required): the id (or id prefix) of the transaction\n\nReturns:\n  void\n",
                    /* aliases */ {"rebroadcast", "wallet_transaction_rebroadcast"}, false};
                store_method_metadata(wallet_rebroadcast_transaction_method_metadata);
            }

            {
                // register method wallet_account_register
                cdcchain::api::MethodData wallet_account_register_method_metadata{ "wallet_account_register", nullptr,
                    /* description */ "Updates the data published about a given account",
                    /* returns */ "transaction_entry",
                    /* params: */{
                        {"account_name", "account_name", cdcchain::api::required_positional, fc::ovariant()},
                        {"pay_from_account", "account_name", cdcchain::api::required_positional, fc::ovariant()},
                        {"public_data", "json_variant", cdcchain::api::optional_positional, fc::variant(fc::json::from_string("null"))},
                        {"delegate_pay_rate", "uint8_t", cdcchain::api::optional_positional, fc::variant(fc::json::from_string("-1"))},
                        {"account_type", "string", cdcchain::api::optional_positional, fc::variant(fc::json::from_string("\"titan_account\""))}
                          },
                    /* prerequisites */ (cdcchain::api::MethodPrerequisites) 4,
                    /* detailed description */ "Updates the data published about a given account\n\nParameters:\n  account_name (account_name, required): the account that will be updated\n  pay_from_account (account_name, required): the account from which fees will be paid\n  public_data (json_variant, optional, defaults to null): public data about the account\n  delegate_pay_rate (uint8_t, optional, defaults to -1): -1 for non-delegates; otherwise the percent of delegate pay to accept per produced block\n  account_type (string, optional, defaults to \"titan_account\"): titan_account | public_account - public accounts do not receive memos and all payments are made to the active key\n\nReturns:\n  transaction_entry\n",
                    /* aliases */ {"register"}, false};
                store_method_metadata(wallet_account_register_method_metadata);
            }

            {
                // register method wallet_account_update_private_data
                cdcchain::api::MethodData wallet_account_update_private_data_method_metadata{ "wallet_account_update_private_data", nullptr,
                    /* description */ "Updates the local private data for an account",
                    /* returns */ "void",
                    /* params: */{
                        {"account_name", "account_name", cdcchain::api::required_positional, fc::ovariant()},
                        {"private_data", "json_variant", cdcchain::api::optional_positional, fc::variant(fc::json::from_string("null"))}
                          },
                    /* prerequisites */ (cdcchain::api::MethodPrerequisites) 4,
                    /* detailed description */ "Updates the local private data for an account\n\nParameters:\n  account_name (account_name, required): the account that will be updated\n  private_data (json_variant, optional, defaults to null): private data about the account\n\nReturns:\n  void\n",
                    /* aliases */ {"update_private_data"}, false};
                store_method_metadata(wallet_account_update_private_data_method_metadata);
            }

            {
                // register method wallet_account_update_registration
                cdcchain::api::MethodData wallet_account_update_registration_method_metadata{ "wallet_account_update_registration", nullptr,
                    /* description */ "Updates the data published about a given account",
                    /* returns */ "transaction_entry",
                    /* params: */{
                        {"account_name", "account_name", cdcchain::api::required_positional, fc::ovariant()},
                        {"pay_from_account", "account_name", cdcchain::api::required_positional, fc::ovariant()},
                        {"public_data", "json_variant", cdcchain::api::optional_positional, fc::variant(fc::json::from_string("null"))},
                        {"delegate_pay_rate", "uint8_t", cdcchain::api::optional_positional, fc::variant(fc::json::from_string("-1"))}
                          },
                    /* prerequisites */ (cdcchain::api::MethodPrerequisites) 4,
                    /* detailed description */ "Updates the data published about a given account\n\nParameters:\n  account_name (account_name, required): the account that will be updated\n  pay_from_account (account_name, required): the account from which fees will be paid\n  public_data (json_variant, optional, defaults to null): public data about the account\n  delegate_pay_rate (uint8_t, optional, defaults to -1): -1 for non-delegates; otherwise the percent of delegate pay to accept per produced block\n\nReturns:\n  transaction_entry\n",
                    /* aliases */ {"update_registration"}, false};
                store_method_metadata(wallet_account_update_registration_method_metadata);
            }

            {
                // register method wallet_account_update_active_key
                cdcchain::api::MethodData wallet_account_update_active_key_method_metadata{ "wallet_account_update_active_key", nullptr,
                    /* description */ "Updates the specified account's active key and broadcasts the transaction.",
                    /* returns */ "transaction_entry",
                    /* params: */{
                        {"account_to_update", "account_name", cdcchain::api::required_positional, fc::ovariant()},
                        {"pay_from_account", "account_name", cdcchain::api::required_positional, fc::ovariant()},
                        {"new_active_key", "string", cdcchain::api::optional_positional, fc::variant(fc::json::from_string("\"\""))}
                          },
                    /* prerequisites */ (cdcchain::api::MethodPrerequisites) 4,
                    /* detailed description */ "Updates the specified account's active key and broadcasts the transaction.\n\nParameters:\n  account_to_update (account_name, required): The name of the account to update the active key of.\n  pay_from_account (account_name, required): The account from which fees will be paid.\n  new_active_key (string, optional, defaults to \"\"): WIF private key to update active key to. If empty, a new key will be generated.\n\nReturns:\n  transaction_entry\n",
                    /* aliases */ {}, false};
                store_method_metadata(wallet_account_update_active_key_method_metadata);
            }

            {
                // register method wallet_list_accounts
                cdcchain::api::MethodData wallet_list_accounts_method_metadata{ "wallet_list_accounts", nullptr,
                    /* description */ "Lists all accounts associated with this wallet",
                    /* returns */ "wallet_account_entry_array",
                    /* params: */{                    },
                    /* prerequisites */ (cdcchain::api::MethodPrerequisites) 2,
                    /* detailed description */ "Lists all accounts associated with this wallet\n\nParameters:\n  (none)\n\nReturns:\n  wallet_account_entry_array\n",
                    /* aliases */ {"listaccounts"}, false};
                store_method_metadata(wallet_list_accounts_method_metadata);
            }

            {
                // register method wallet_list_unregistered_accounts
                cdcchain::api::MethodData wallet_list_unregistered_accounts_method_metadata{ "wallet_list_unregistered_accounts", nullptr,
                    /* description */ "Lists all unregistered accounts belonging to this wallet",
                    /* returns */ "wallet_account_entry_array",
                    /* params: */{                    },
                    /* prerequisites */ (cdcchain::api::MethodPrerequisites) 2,
                    /* detailed description */ "Lists all unregistered accounts belonging to this wallet\n\nParameters:\n  (none)\n\nReturns:\n  wallet_account_entry_array\n",
                    /* aliases */ {}, false};
                store_method_metadata(wallet_list_unregistered_accounts_method_metadata);
            }

            {
                // register method wallet_list_my_accounts
                cdcchain::api::MethodData wallet_list_my_accounts_method_metadata{ "wallet_list_my_accounts", nullptr,
                    /* description */ "Lists all accounts for which we have a private key in this wallet",
                    /* returns */ "wallet_account_entry_array",
                    /* params: */{                    },
                    /* prerequisites */ (cdcchain::api::MethodPrerequisites) 2,
                    /* detailed description */ "Lists all accounts for which we have a private key in this wallet\n\nParameters:\n  (none)\n\nReturns:\n  wallet_account_entry_array\n",
                    /* aliases */ {}, false};
                store_method_metadata(wallet_list_my_accounts_method_metadata);
            }

            {
                // register method wallet_list_my_addresses
                cdcchain::api::MethodData wallet_list_my_addresses_method_metadata{ "wallet_list_my_addresses", nullptr,
                    /* description */ "Lists all accounts and account addresses for which we have a private key in this wallet",
                    /* returns */ "account_address_entry_array",
                    /* params: */{                    },
                    /* prerequisites */ (cdcchain::api::MethodPrerequisites) 2,
                    /* detailed description */ "Lists all accounts and account addresses for which we have a private key in this wallet\n\nParameters:\n  (none)\n\nReturns:\n  account_address_entry_array\n",
                    /* aliases */ {}, false};
                store_method_metadata(wallet_list_my_addresses_method_metadata);
            }

            {
                // register method wallet_get_account
                cdcchain::api::MethodData wallet_get_account_method_metadata{ "wallet_get_account", nullptr,
                    /* description */ "Get the account entry for a given name",
                    /* returns */ "wallet_account_entry",
                    /* params: */{
                        {"account_name", "account_name", cdcchain::api::required_positional, fc::ovariant()}
                          },
                    /* prerequisites */ (cdcchain::api::MethodPrerequisites) 2,
                    /* detailed description */ "Get the account entry for a given name\n\nParameters:\n  account_name (account_name, required): the name of the account to retrieve\n\nReturns:\n  wallet_account_entry\n",
                    /* aliases */ {}, false};
                store_method_metadata(wallet_get_account_method_metadata);
            }

            {
                // register method wallet_get_account_public_address
                cdcchain::api::MethodData wallet_get_account_public_address_method_metadata{ "wallet_get_account_public_address", nullptr,
                    /* description */ "Get the account entry for a given name",
                    /* returns */ "string",
                    /* params: */{
                        {"account_name", "account_name", cdcchain::api::required_positional, fc::ovariant()}
                          },
                    /* prerequisites */ (cdcchain::api::MethodPrerequisites) 2,
                    /* detailed description */ "Get the account entry for a given name\n\nParameters:\n  account_name (account_name, required): the name of the account whose public address you want\n\nReturns:\n  string\n",
                    /* aliases */ {}, false};
                store_method_metadata(wallet_get_account_public_address_method_metadata);
            }

            {
                // register method wallet_remove_contact_account
                cdcchain::api::MethodData wallet_remove_contact_account_method_metadata{ "wallet_remove_contact_account", nullptr,
                    /* description */ "Remove a contact account from your wallet",
                    /* returns */ "void",
                    /* params: */{
                        {"account_name", "account_name", cdcchain::api::required_positional, fc::ovariant()}
                          },
                    /* prerequisites */ (cdcchain::api::MethodPrerequisites) 2,
                    /* detailed description */ "Remove a contact account from your wallet\n\nParameters:\n  account_name (account_name, required): the name of the contact\n\nReturns:\n  void\n",
                    /* aliases */ {}, false};
                store_method_metadata(wallet_remove_contact_account_method_metadata);
            }

            {
                // register method wallet_account_rename
                cdcchain::api::MethodData wallet_account_rename_method_metadata{ "wallet_account_rename", nullptr,
                    /* description */ "Rename an account in wallet",
                    /* returns */ "void",
                    /* params: */{
                        {"current_account_name", "account_name", cdcchain::api::required_positional, fc::ovariant()},
                        {"new_account_name", "new_account_name", cdcchain::api::required_positional, fc::ovariant()}
                          },
                    /* prerequisites */ (cdcchain::api::MethodPrerequisites) 2,
                    /* detailed description */ "Rename an account in wallet\n\nParameters:\n  current_account_name (account_name, required): the current name of the account\n  new_account_name (new_account_name, required): the new name for the account\n\nReturns:\n  void\n",
                    /* aliases */ {"wallet_rename_account"}, false};
                store_method_metadata(wallet_account_rename_method_metadata);
            }

            {
                // register method wallet_asset_create
                cdcchain::api::MethodData wallet_asset_create_method_metadata{ "wallet_asset_create", nullptr,
                    /* description */ "Creates a new user issued asset",
                    /* returns */ "transaction_entry",
                    /* params: */{
                        {"symbol", "asset_symbol", cdcchain::api::required_positional, fc::ovariant()},
                        {"asset_name", "string", cdcchain::api::required_positional, fc::ovariant()},
                        {"issuer_name", "string", cdcchain::api::required_positional, fc::ovariant()},
                        {"description", "string", cdcchain::api::required_positional, fc::ovariant()},
                        {"maximum_share_supply", "string", cdcchain::api::required_positional, fc::ovariant()},
                        {"precision", "uint64_t", cdcchain::api::required_positional, fc::ovariant()},
                        {"public_data", "json_variant", cdcchain::api::optional_positional, fc::variant(fc::json::from_string("null"))},
                        {"is_market_issued", "bool", cdcchain::api::optional_positional, fc::variant(fc::json::from_string("false"))}
                          },
                    /* prerequisites */ (cdcchain::api::MethodPrerequisites) 4,
                    /* detailed description */ "Creates a new user issued asset\n\nParameters:\n  symbol (asset_symbol, required): the ticker symbol for the new asset\n  asset_name (string, required): the name of the asset\n  issuer_name (string, required): the name of the issuer of the asset\n  description (string, required): a description of the asset\n  maximum_share_supply (string, required): the maximum number of shares of the asset\n  precision (uint64_t, required): defines where the decimal should be displayed, must be a power of 10\n  public_data (json_variant, optional, defaults to null): arbitrary data attached to the asset\n  is_market_issued (bool, optional, defaults to false): creation of a new BitAsset that is created by shorting\n\nReturns:\n  transaction_entry\n",
                    /* aliases */ {}, false};
                store_method_metadata(wallet_asset_create_method_metadata);
            }

            {
                // register method wallet_asset_issue
                cdcchain::api::MethodData wallet_asset_issue_method_metadata{ "wallet_asset_issue", nullptr,
                    /* description */ "Issues new shares of a given asset type",
                    /* returns */ "transaction_entry",
                    /* params: */{
                        {"amount", "string", cdcchain::api::required_positional, fc::ovariant()},
                        {"symbol", "asset_symbol", cdcchain::api::required_positional, fc::ovariant()},
                        {"to_account_name", "account_name", cdcchain::api::required_positional, fc::ovariant()},
                        {"memo_message", "information", cdcchain::api::optional_positional, fc::variant(fc::json::from_string("\"\""))}
                          },
                    /* prerequisites */ (cdcchain::api::MethodPrerequisites) 4,
                    /* detailed description */ "Issues new shares of a given asset type\n\nThe asset being issued must have been created via wallet_asset_create in a previous block.\n\nParameters:\n  amount (string, required): the amount of shares to issue\n  symbol (asset_symbol, required): the ticker symbol for asset\n  to_account_name (account_name, required): the name of the account to receive the shares\n  memo_message (information, optional, defaults to \"\"): the memo to send to the receiver\n\nReturns:\n  transaction_entry\n",
                    /* aliases */ {}, false};
                store_method_metadata(wallet_asset_issue_method_metadata);
            }

            {
                // register method wallet_asset_issue_to_addresses
                cdcchain::api::MethodData wallet_asset_issue_to_addresses_method_metadata{ "wallet_asset_issue_to_addresses", nullptr,
                    /* description */ "Issues new UIA shares to specific addresses.",
                    /* returns */ "transaction_entry",
                    /* params: */{
                        {"symbol", "asset_symbol", cdcchain::api::required_positional, fc::ovariant()},
                        {"addresses", "snapshot_map", cdcchain::api::required_positional, fc::ovariant()}
                          },
                    /* prerequisites */ (cdcchain::api::MethodPrerequisites) 4,
                    /* detailed description */ "Issues new UIA shares to specific addresses.\n\nThis is intended to be used with a helper script to break up snapshots. It will not do any magic for you.\n\nParameters:\n  symbol (asset_symbol, required): the ticker symbol for asset\n  addresses (snapshot_map, required): A map of addresses-to-amounts to transfer the new shares to\n\nReturns:\n  transaction_entry\n",
                    /* aliases */ {}, false};
                store_method_metadata(wallet_asset_issue_to_addresses_method_metadata);
            }

            {
                // register method wallet_account_balance
                cdcchain::api::MethodData wallet_account_balance_method_metadata{ "wallet_account_balance", nullptr,
                    /* description */ "Lists the total asset balances for the specified account",
                    /* returns */ "account_balance_summary_type",
                    /* params: */{
                        {"account_name", "account_name", cdcchain::api::optional_positional, fc::variant(fc::json::from_string("\"\""))}
                          },
                    /* prerequisites */ (cdcchain::api::MethodPrerequisites) 2,
                    /* detailed description */ "Lists the total asset balances for the specified account\n\nParameters:\n  account_name (account_name, optional, defaults to \"\"): the account to get a balance for, or leave empty for all accounts\n\nReturns:\n  account_balance_summary_type\n",
                    /* aliases */ {"balance", "getbalance"}, true};
                store_method_metadata(wallet_account_balance_method_metadata);
            }

            {
                // register method wallet_account_balance_ids
                cdcchain::api::MethodData wallet_account_balance_ids_method_metadata{ "wallet_account_balance_ids", nullptr,
                    /* description */ "Lists the balance IDs for the specified account",
                    /* returns */ "account_balance_id_summary_type",
                    /* params: */{
                        {"account_name", "account_name", cdcchain::api::optional_positional, fc::variant(fc::json::from_string("\"\""))}
                          },
                    /* prerequisites */ (cdcchain::api::MethodPrerequisites) 2,
                    /* detailed description */ "Lists the balance IDs for the specified account\n\nParameters:\n  account_name (account_name, optional, defaults to \"\"): the account to get a balance IDs for, or leave empty for all accounts\n\nReturns:\n  account_balance_id_summary_type\n",
                    /* aliases */ {}, false};
                store_method_metadata(wallet_account_balance_ids_method_metadata);
            }

            {
                // register method wallet_account_list_public_keys
                cdcchain::api::MethodData wallet_account_list_public_keys_method_metadata{ "wallet_account_list_public_keys", nullptr,
                    /* description */ "Lists all public keys in this account",
                    /* returns */ "public_key_summary_array",
                    /* params: */{
                        {"account_name", "account_name", cdcchain::api::required_positional, fc::ovariant()}
                          },
                    /* prerequisites */ (cdcchain::api::MethodPrerequisites) 2,
                    /* detailed description */ "Lists all public keys in this account\n\nParameters:\n  account_name (account_name, required): the account for which public keys should be listed\n\nReturns:\n  public_key_summary_array\n",
                    /* aliases */ {"public_keys"}, true};
                store_method_metadata(wallet_account_list_public_keys_method_metadata);
            }

            {
                // register method wallet_delegate_withdraw_pay
                cdcchain::api::MethodData wallet_delegate_withdraw_pay_method_metadata{ "wallet_delegate_withdraw_pay", nullptr,
                    /* description */ "Used to transfer some of the delegate's pay from their balance",
                    /* returns */ "transaction_entry",
                    /* params: */{
                        {"delegate_name", "account_name", cdcchain::api::required_positional, fc::ovariant()},
                        {"to_account_name", "account_name", cdcchain::api::required_positional, fc::ovariant()},
                        {"amount_to_withdraw", "string", cdcchain::api::required_positional, fc::ovariant()}
                          },
                    /* prerequisites */ (cdcchain::api::MethodPrerequisites) 4,
                    /* detailed description */ "Used to transfer some of the delegate's pay from their balance\n\nParameters:\n  delegate_name (account_name, required): the delegate whose pay is being cashed out\n  to_account_name (account_name, required): the account that should receive the funds\n  amount_to_withdraw (string, required): the amount to withdraw\n\nReturns:\n  transaction_entry\n",
                    /* aliases */ {"pay_delegate"}, false};
                store_method_metadata(wallet_delegate_withdraw_pay_method_metadata);
            }

            {
                // register method wallet_delegate_pay_balance_query
                cdcchain::api::MethodData wallet_delegate_pay_balance_query_method_metadata{ "wallet_delegate_pay_balance_query", nullptr,
                    /* description */ "query delegate's pay balance",
                    /* returns */ "delegate_salarys",
                    /* params: */{
                        {"delegate_name", "account_name", cdcchain::api::required_positional, fc::ovariant()}
                          },
                    /* prerequisites */ (cdcchain::api::MethodPrerequisites) 4,
                    /* detailed description */ "query delegate's pay balance\n\nParameters:\n  delegate_name (account_name, required): the delegate whose pay is being cashed out\n\nReturns:\n  delegate_salarys\n",
                    /* aliases */ {"query_salary"}, false};
                store_method_metadata(wallet_delegate_pay_balance_query_method_metadata);
            }

            {
                // register method wallet_active_delegate_salary
                cdcchain::api::MethodData wallet_active_delegate_salary_method_metadata{ "wallet_active_delegate_salary", nullptr,
                    /* description */ "query delegate's pay balance",
                    /* returns */ "delegate_salary_map",
                    /* params: */{                    },
                    /* prerequisites */ (cdcchain::api::MethodPrerequisites) 4,
                    /* detailed description */ "query delegate's pay balance\n\nParameters:\n  (none)\n\nReturns:\n  delegate_salary_map\n",
                    /* aliases */ {}, false};
                store_method_metadata(wallet_active_delegate_salary_method_metadata);
            }

            {
                // register method wallet_get_delegate_statue
                cdcchain::api::MethodData wallet_get_delegate_statue_method_metadata{ "wallet_get_delegate_statue", nullptr,
                    /* description */ "Get delegate produce block statue",
                    /* returns */ "bool",
                    /* params: */{
                        {"account_name", "string", cdcchain::api::required_positional, fc::ovariant()}
                          },
                    /* prerequisites */ (cdcchain::api::MethodPrerequisites) 2,
                    /* detailed description */ "Get delegate produce block statue\n\nParameters:\n  account_name (string, required): delegate account name to get statue\n\nReturns:\n  bool\n",
                    /* aliases */ {}, false};
                store_method_metadata(wallet_get_delegate_statue_method_metadata);
            }

            {
                // register method wallet_set_transaction_imessage_fee_coe
                cdcchain::api::MethodData wallet_set_transaction_imessage_fee_coe_method_metadata{ "wallet_set_transaction_imessage_fee_coe", nullptr,
                    /* description */ "Set imessage fee coefficient",
                    /* returns */ "void",
                    /* params: */{
                        {"fee_coe", "string", cdcchain::api::required_positional, fc::ovariant()}
                          },
                    /* prerequisites */ (cdcchain::api::MethodPrerequisites) 2,
                    /* detailed description */ "Set imessage fee coefficient\n\nParameters:\n  fee_coe (string, required): fee coefficient\n\nReturns:\n  void\n",
                    /* aliases */ {"set_fee_coe"}, false};
                store_method_metadata(wallet_set_transaction_imessage_fee_coe_method_metadata);
            }

            {
                // register method wallet_get_transaction_imessage_fee_coe
                cdcchain::api::MethodData wallet_get_transaction_imessage_fee_coe_method_metadata{ "wallet_get_transaction_imessage_fee_coe", nullptr,
                    /* description */ "Get imessage fee coefficient",
                    /* returns */ "real_amount",
                    /* params: */{                    },
                    /* prerequisites */ (cdcchain::api::MethodPrerequisites) 2,
                    /* detailed description */ "Get imessage fee coefficient\n\nParameters:\n  (none)\n\nReturns:\n  real_amount\n",
                    /* aliases */ {"get_fee_coe"}, false};
                store_method_metadata(wallet_get_transaction_imessage_fee_coe_method_metadata);
            }

            {
                // register method wallet_set_transaction_imessage_soft_max_length
                cdcchain::api::MethodData wallet_set_transaction_imessage_soft_max_length_method_metadata{ "wallet_set_transaction_imessage_soft_max_length", nullptr,
                    /* description */ "Set imessage soft max length",
                    /* returns */ "void",
                    /* params: */{
                        {"soft_length", "amount", cdcchain::api::required_positional, fc::ovariant()}
                          },
                    /* prerequisites */ (cdcchain::api::MethodPrerequisites) 2,
                    /* detailed description */ "Set imessage soft max length\n\nParameters:\n  soft_length (amount, required): max soft length\n\nReturns:\n  void\n",
                    /* aliases */ {"set_soft_length"}, false};
                store_method_metadata(wallet_set_transaction_imessage_soft_max_length_method_metadata);
            }

            {
                // register method wallet_get_transaction_imessage_soft_max_length
                cdcchain::api::MethodData wallet_get_transaction_imessage_soft_max_length_method_metadata{ "wallet_get_transaction_imessage_soft_max_length", nullptr,
                    /* description */ "Get soft max length",
                    /* returns */ "amount",
                    /* params: */{                    },
                    /* prerequisites */ (cdcchain::api::MethodPrerequisites) 2,
                    /* detailed description */ "Get soft max length\n\nParameters:\n  (none)\n\nReturns:\n  amount\n",
                    /* aliases */ {"get_soft_length"}, false};
                store_method_metadata(wallet_get_transaction_imessage_soft_max_length_method_metadata);
            }

            {
                // register method wallet_set_transaction_fee
                cdcchain::api::MethodData wallet_set_transaction_fee_method_metadata{ "wallet_set_transaction_fee", nullptr,
                    /* description */ "Set the fee to add to new transactions",
                    /* returns */ "asset",
                    /* params: */{
                        {"fee", "string", cdcchain::api::required_positional, fc::ovariant()}
                          },
                    /* prerequisites */ (cdcchain::api::MethodPrerequisites) 2,
                    /* detailed description */ "Set the fee to add to new transactions\n\nParameters:\n  fee (string, required): the wallet transaction fee to set\n\nReturns:\n  asset\n",
                    /* aliases */ {"wallet_set_priority_fee", "set_priority_fee", "settrxfee", "setfee", "set_fee"}, false};
                store_method_metadata(wallet_set_transaction_fee_method_metadata);
            }

            {
                // register method wallet_get_transaction_fee
                cdcchain::api::MethodData wallet_get_transaction_fee_method_metadata{ "wallet_get_transaction_fee", nullptr,
                    /* description */ "Returns ",
                    /* returns */ "asset",
                    /* params: */{
                        {"symbol", "asset_symbol", cdcchain::api::optional_positional, fc::variant(fc::json::from_string("\"\""))}
                          },
                    /* prerequisites */ (cdcchain::api::MethodPrerequisites) 2,
                    /* detailed description */ "Returns \n\nParameters:\n  symbol (asset_symbol, optional, defaults to \"\"): the wallet transaction if paid in the given asset type\n\nReturns:\n  asset\n",
                    /* aliases */ {"wallet_get_priority_fee", "get_priority_fee", "gettrxfee", "getfee", "get_fee"}, true};
                store_method_metadata(wallet_get_transaction_fee_method_metadata);
            }

            {
                // register method wallet_dump_private_key
                cdcchain::api::MethodData wallet_dump_private_key_method_metadata{ "wallet_dump_private_key", nullptr,
                    /* description */ "Reveals the private key corresponding to the specified public key or address; use with caution",
                    /* returns */ "optional_string",
                    /* params: */{
                        {"input", "string", cdcchain::api::required_positional, fc::ovariant()}
                          },
                    /* prerequisites */ (cdcchain::api::MethodPrerequisites) 4,
                    /* detailed description */ "Reveals the private key corresponding to the specified public key or address; use with caution\n\nParameters:\n  input (string, required): public key or address to dump private key for\n\nReturns:\n  optional_string\n",
                    /* aliases */ {"dump_private_key", "dumpprivkey"}, false};
                store_method_metadata(wallet_dump_private_key_method_metadata);
            }

            {
                // register method wallet_dump_account_private_key
                cdcchain::api::MethodData wallet_dump_account_private_key_method_metadata{ "wallet_dump_account_private_key", nullptr,
                    /* description */ "Reveals the specified account private key; use with caution",
                    /* returns */ "optional_string",
                    /* params: */{
                        {"account_name", "string", cdcchain::api::required_positional, fc::ovariant()},
                        {"key_type", "account_key_type", cdcchain::api::required_positional, fc::ovariant()}
                          },
                    /* prerequisites */ (cdcchain::api::MethodPrerequisites) 4,
                    /* detailed description */ "Reveals the specified account private key; use with caution\n\nParameters:\n  account_name (string, required): account name to dump private key for\n  key_type (account_key_type, required): which account private key to dump; one of {owner_key, active_key, signing_key}\n\nReturns:\n  optional_string\n",
                    /* aliases */ {}, false};
                store_method_metadata(wallet_dump_account_private_key_method_metadata);
            }

            {
                // register method wallet_account_vote_summary
                cdcchain::api::MethodData wallet_account_vote_summary_method_metadata{ "wallet_account_vote_summary", nullptr,
                    /* description */ "Returns the allocation of votes by this account",
                    /* returns */ "account_vote_summary",
                    /* params: */{
                        {"account_name", "account_name", cdcchain::api::optional_positional, fc::variant(fc::json::from_string("\"\""))}
                          },
                    /* prerequisites */ (cdcchain::api::MethodPrerequisites) 2,
                    /* detailed description */ "Returns the allocation of votes by this account\n\nParameters:\n  account_name (account_name, optional, defaults to \"\"): the account to report votes on, or empty for all accounts\n\nReturns:\n  account_vote_summary\n",
                    /* aliases */ {"votes"}, false};
                store_method_metadata(wallet_account_vote_summary_method_metadata);
            }

            {
                // register method wallet_check_vote_status
                cdcchain::api::MethodData wallet_check_vote_status_method_metadata{ "wallet_check_vote_status", nullptr,
                    /* description */ "Get info about the votes of balances controlled by this account",
                    /* returns */ "vote_summary",
                    /* params: */{
                        {"account", "account_name", cdcchain::api::required_positional, fc::ovariant()}
                          },
                    /* prerequisites */ (cdcchain::api::MethodPrerequisites) 2,
                    /* detailed description */ "Get info about the votes of balances controlled by this account\n\nParameters:\n  account (account_name, required): \n\nReturns:\n  vote_summary\n",
                    /* aliases */ {}, false};
                store_method_metadata(wallet_check_vote_status_method_metadata);
            }

            {
                // register method wallet_set_setting
                cdcchain::api::MethodData wallet_set_setting_method_metadata{ "wallet_set_setting", nullptr,
                    /* description */ "Set a property in the GUI settings DB",
                    /* returns */ "void",
                    /* params: */{
                        {"name", "string", cdcchain::api::required_positional, fc::ovariant()},
                        {"value", "variant", cdcchain::api::required_positional, fc::ovariant()}
                          },
                    /* prerequisites */ (cdcchain::api::MethodPrerequisites) 2,
                    /* detailed description */ "Set a property in the GUI settings DB\n\nParameters:\n  name (string, required): the name of the setting to set\n  value (variant, required): the value to set the setting to\n\nReturns:\n  void\n",
                    /* aliases */ {}, false};
                store_method_metadata(wallet_set_setting_method_metadata);
            }

            {
                // register method wallet_get_setting
                cdcchain::api::MethodData wallet_get_setting_method_metadata{ "wallet_get_setting", nullptr,
                    /* description */ "Get the value of the given setting",
                    /* returns */ "optional_variant",
                    /* params: */{
                        {"name", "string", cdcchain::api::required_positional, fc::ovariant()}
                          },
                    /* prerequisites */ (cdcchain::api::MethodPrerequisites) 2,
                    /* detailed description */ "Get the value of the given setting\n\nParameters:\n  name (string, required): The name of the setting to fetch\n\nReturns:\n  optional_variant\n",
                    /* aliases */ {}, false};
                store_method_metadata(wallet_get_setting_method_metadata);
            }

            {
                // register method wallet_delegate_set_block_production
                cdcchain::api::MethodData wallet_delegate_set_block_production_method_metadata{ "wallet_delegate_set_block_production", nullptr,
                    /* description */ "Enable or disable block production for a particular delegate account",
                    /* returns */ "void",
                    /* params: */{
                        {"delegate_name", "string", cdcchain::api::required_positional, fc::ovariant()},
                        {"enabled", "bool", cdcchain::api::required_positional, fc::ovariant()}
                          },
                    /* prerequisites */ (cdcchain::api::MethodPrerequisites) 2,
                    /* detailed description */ "Enable or disable block production for a particular delegate account\n\nParameters:\n  delegate_name (string, required): The delegate to enable/disable block production for; ALL for all delegate accounts\n  enabled (bool, required): true to enable block production, false otherwise\n\nReturns:\n  void\n",
                    /* aliases */ {}, false};
                store_method_metadata(wallet_delegate_set_block_production_method_metadata);
            }

            {
                // register method wallet_set_transaction_scanning
                cdcchain::api::MethodData wallet_set_transaction_scanning_method_metadata{ "wallet_set_transaction_scanning", nullptr,
                    /* description */ "Enable or disable wallet transaction scanning",
                    /* returns */ "bool",
                    /* params: */{
                        {"enabled", "bool", cdcchain::api::required_positional, fc::ovariant()}
                          },
                    /* prerequisites */ (cdcchain::api::MethodPrerequisites) 2,
                    /* detailed description */ "Enable or disable wallet transaction scanning\n\nParameters:\n  enabled (bool, required): true to enable transaction scanning, false otherwise\n\nReturns:\n  bool\n",
                    /* aliases */ {}, false};
                store_method_metadata(wallet_set_transaction_scanning_method_metadata);
            }

            {
                // register method wallet_sign_hash
                cdcchain::api::MethodData wallet_sign_hash_method_metadata{ "wallet_sign_hash", nullptr,
                    /* description */ "Signs the provided message digest with the account key",
                    /* returns */ "compact_signature",
                    /* params: */{
                        {"signer", "string", cdcchain::api::required_positional, fc::ovariant()},
                        {"hash", "sha256", cdcchain::api::required_positional, fc::ovariant()}
                          },
                    /* prerequisites */ (cdcchain::api::MethodPrerequisites) 4,
                    /* detailed description */ "Signs the provided message digest with the account key\n\nParameters:\n  signer (string, required): A public key, address, or account name whose key to sign with\n  hash (sha256, required): SHA256 digest of the message to sign\n\nReturns:\n  compact_signature\n",
                    /* aliases */ {}, false};
                store_method_metadata(wallet_sign_hash_method_metadata);
            }

            {
                // register method wallet_login_start
                cdcchain::api::MethodData wallet_login_start_method_metadata{ "wallet_login_start", nullptr,
                    /* description */ "Initiates the login procedure by providing a Ub Login URL",
                    /* returns */ "string",
                    /* params: */{
                        {"server_account", "string", cdcchain::api::required_positional, fc::ovariant()}
                          },
                    /* prerequisites */ (cdcchain::api::MethodPrerequisites) 4,
                    /* detailed description */ "Initiates the login procedure by providing a Ub Login URL\n\nParameters:\n  server_account (string, required): Name of the account of the server. The user will be shown this name as the site he is logging into.\n\nReturns:\n  string\n",
                    /* aliases */ {}, false};
                store_method_metadata(wallet_login_start_method_metadata);
            }

            {
                // register method wallet_login_finish
                cdcchain::api::MethodData wallet_login_finish_method_metadata{ "wallet_login_finish", nullptr,
                    /* description */ "Completes the login procedure by finding the user's public account key and shared secret",
                    /* returns */ "variant",
                    /* params: */{
                        {"server_key", "public_key", cdcchain::api::required_positional, fc::ovariant()},
                        {"client_key", "public_key", cdcchain::api::required_positional, fc::ovariant()},
                        {"client_signature", "compact_signature", cdcchain::api::required_positional, fc::ovariant()}
                          },
                    /* prerequisites */ (cdcchain::api::MethodPrerequisites) 4,
                    /* detailed description */ "Completes the login procedure by finding the user's public account key and shared secret\n\nParameters:\n  server_key (public_key, required): The one-time public key from wallet_login_start.\n  client_key (public_key, required): The client's one-time public key.\n  client_signature (compact_signature, required): The client's signature of the shared secret.\n\nReturns:\n  variant\n",
                    /* aliases */ {}, false};
                store_method_metadata(wallet_login_finish_method_metadata);
            }

            {
                // register method wallet_balance_set_vote_info
                cdcchain::api::MethodData wallet_balance_set_vote_info_method_metadata{ "wallet_balance_set_vote_info", nullptr,
                    /* description */ "Set this balance's voting address and slate",
                    /* returns */ "transaction_builder",
                    /* params: */{
                        {"balance_id", "address", cdcchain::api::required_positional, fc::ovariant()},
                        {"voter_address", "string", cdcchain::api::optional_positional, fc::variant(fc::json::from_string("\"\""))},
                        {"strategy", "vote_strategy", cdcchain::api::optional_positional, fc::variant(fc::json::from_string("\"vote_all\""))},
                        {"sign_and_broadcast", "bool", cdcchain::api::optional_positional, fc::variant(fc::json::from_string("\"true\""))},
                        {"builder_path", "string", cdcchain::api::optional_positional, fc::variant(fc::json::from_string("\"\""))}
                          },
                    /* prerequisites */ (cdcchain::api::MethodPrerequisites) 2,
                    /* detailed description */ "Set this balance's voting address and slate\n\nParameters:\n  balance_id (address, required): the current name of the account\n  voter_address (string, optional, defaults to \"\"): The new voting address. If none is specified, tries to re-use existing address.\n  strategy (vote_strategy, optional, defaults to \"vote_all\"): enumeration [vote_none | vote_all | vote_random | vote_recommended] \n  sign_and_broadcast (bool, optional, defaults to \"true\"): \n  builder_path (string, optional, defaults to \"\"): If specified, will write builder here instead of to DATA_DIR/transactions/latest.trx\n\nReturns:\n  transaction_builder\n",
                    /* aliases */ {"set_vote_info"}, false};
                store_method_metadata(wallet_balance_set_vote_info_method_metadata);
            }

            {
                // register method wallet_publish_slate
                cdcchain::api::MethodData wallet_publish_slate_method_metadata{ "wallet_publish_slate", nullptr,
                    /* description */ "Publishes the current wallet delegate slate to the public data associated with the account",
                    /* returns */ "transaction_entry",
                    /* params: */{
                        {"publishing_account_name", "account_name", cdcchain::api::required_positional, fc::ovariant()},
                        {"paying_account_name", "account_name", cdcchain::api::optional_positional, fc::variant(fc::json::from_string("\"\""))}
                          },
                    /* prerequisites */ (cdcchain::api::MethodPrerequisites) 4,
                    /* detailed description */ "Publishes the current wallet delegate slate to the public data associated with the account\n\nParameters:\n  publishing_account_name (account_name, required): The account to publish the slate ID under\n  paying_account_name (account_name, optional, defaults to \"\"): The account to pay transaction fees or leave empty to pay with publishing account\n\nReturns:\n  transaction_entry\n",
                    /* aliases */ {}, false};
                store_method_metadata(wallet_publish_slate_method_metadata);
            }

            {
                // register method wallet_publish_version
                cdcchain::api::MethodData wallet_publish_version_method_metadata{ "wallet_publish_version", nullptr,
                    /* description */ "Publish your current client version to the specified account's public data entry",
                    /* returns */ "transaction_entry",
                    /* params: */{
                        {"publishing_account_name", "account_name", cdcchain::api::required_positional, fc::ovariant()},
                        {"paying_account_name", "account_name", cdcchain::api::optional_positional, fc::variant(fc::json::from_string("\"\""))}
                          },
                    /* prerequisites */ (cdcchain::api::MethodPrerequisites) 4,
                    /* detailed description */ "Publish your current client version to the specified account's public data entry\n\nParameters:\n  publishing_account_name (account_name, required): The account to publish the client version under\n  paying_account_name (account_name, optional, defaults to \"\"): The account to pay transaction fees with or leave empty to pay with publishing account\n\nReturns:\n  transaction_entry\n",
                    /* aliases */ {}, false};
                store_method_metadata(wallet_publish_version_method_metadata);
            }

            {
                // register method wallet_collect_genesis_balances
                cdcchain::api::MethodData wallet_collect_genesis_balances_method_metadata{ "wallet_collect_genesis_balances", nullptr,
                    /* description */ "Collect specified account's genesis balances",
                    /* returns */ "transaction_entry",
                    /* params: */{
                        {"account_name", "account_name", cdcchain::api::required_positional, fc::ovariant()}
                          },
                    /* prerequisites */ (cdcchain::api::MethodPrerequisites) 4,
                    /* detailed description */ "Collect specified account's genesis balances\n\nParameters:\n  account_name (account_name, required): account to collect genesis balances for\n\nReturns:\n  transaction_entry\n",
                    /* aliases */ {}, false};
                store_method_metadata(wallet_collect_genesis_balances_method_metadata);
            }

            {
                // register method wallet_recover_accounts
                cdcchain::api::MethodData wallet_recover_accounts_method_metadata{ "wallet_recover_accounts", nullptr,
                    /* description */ "Attempts to recover accounts created after last backup was taken and returns number of successful recoveries. Use if you have restored from backup and are missing accounts.",
                    /* returns */ "int32_t",
                    /* params: */{
                        {"accounts_to_recover", "int32_t", cdcchain::api::required_positional, fc::ovariant()},
                        {"maximum_number_of_attempts", "int32_t", cdcchain::api::optional_positional, fc::variant(fc::json::from_string("1000"))}
                          },
                    /* prerequisites */ (cdcchain::api::MethodPrerequisites) 4,
                    /* detailed description */ "Attempts to recover accounts created after last backup was taken and returns number of successful recoveries. Use if you have restored from backup and are missing accounts.\n\nParameters:\n  accounts_to_recover (int32_t, required): The number of accounts to attept to recover\n  maximum_number_of_attempts (int32_t, optional, defaults to 1000): The maximum number of keys to generate trying to recover accounts\n\nReturns:\n  int32_t\n",
                    /* aliases */ {}, false};
                store_method_metadata(wallet_recover_accounts_method_metadata);
            }

            {
                // register method wallet_verify_titan_deposit
                cdcchain::api::MethodData wallet_verify_titan_deposit_method_metadata{ "wallet_verify_titan_deposit", nullptr,
                    /* description */ "Verify whether the specified transaction made a TITAN deposit to the current wallet; returns null if not",
                    /* returns */ "optional_variant_object",
                    /* params: */{
                        {"transaction_id_prefix", "string", cdcchain::api::required_positional, fc::ovariant()}
                          },
                    /* prerequisites */ (cdcchain::api::MethodPrerequisites) 4,
                    /* detailed description */ "Verify whether the specified transaction made a TITAN deposit to the current wallet; returns null if not\n\nParameters:\n  transaction_id_prefix (string, required): the id (or id prefix) of the transaction entry\n\nReturns:\n  optional_variant_object\n",
                    /* aliases */ {}, false};
                store_method_metadata(wallet_verify_titan_deposit_method_metadata);
            }

            {
                // register method wallet_repair_entrys
                cdcchain::api::MethodData wallet_repair_entrys_method_metadata{ "wallet_repair_entrys", nullptr,
                    /* description */ "tries to repair any inconsistent wallet account, key, and transaction entrys",
                    /* returns */ "void",
                    /* params: */{
                        {"collecting_account_name", "account_name", cdcchain::api::optional_positional, fc::variant(fc::json::from_string("\"\""))}
                          },
                    /* prerequisites */ (cdcchain::api::MethodPrerequisites) 4,
                    /* detailed description */ "tries to repair any inconsistent wallet account, key, and transaction entrys\n\nParameters:\n  collecting_account_name (account_name, optional, defaults to \"\"): collect any orphan balances into this account\n\nReturns:\n  void\n",
                    /* aliases */ {}, false};
                store_method_metadata(wallet_repair_entrys_method_metadata);
            }

            {
                // register method wallet_regenerate_keys
                cdcchain::api::MethodData wallet_regenerate_keys_method_metadata{ "wallet_regenerate_keys", nullptr,
                    /* description */ "regenerates private keys as part of wallet recovery",
                    /* returns */ "int32_t",
                    /* params: */{
                        {"account_name", "account_name", cdcchain::api::required_positional, fc::ovariant()},
                        {"max_key_number", "uint32_t", cdcchain::api::required_positional, fc::ovariant()}
                          },
                    /* prerequisites */ (cdcchain::api::MethodPrerequisites) 4,
                    /* detailed description */ "regenerates private keys as part of wallet recovery\n\nParameters:\n  account_name (account_name, required): the account the generated keys should be a part of\n  max_key_number (uint32_t, required): the last key number to regenerate\n\nReturns:\n  int32_t\n",
                    /* aliases */ {}, false};
                store_method_metadata(wallet_regenerate_keys_method_metadata);
            }

            {
                // register method wallet_account_retract
                cdcchain::api::MethodData wallet_account_retract_method_metadata{ "wallet_account_retract", nullptr,
                    /* description */ "Retract (permanently disable) the specified account in case of master key compromise.",
                    /* returns */ "transaction_entry",
                    /* params: */{
                        {"account_to_retract", "account_name", cdcchain::api::required_positional, fc::ovariant()},
                        {"pay_from_account", "account_name", cdcchain::api::required_positional, fc::ovariant()}
                          },
                    /* prerequisites */ (cdcchain::api::MethodPrerequisites) 4,
                    /* detailed description */ "Retract (permanently disable) the specified account in case of master key compromise.\n\nParameters:\n  account_to_retract (account_name, required): The name of the account to retract.\n  pay_from_account (account_name, required): The account from which fees will be paid.\n\nReturns:\n  transaction_entry\n",
                    /* aliases */ {}, false};
                store_method_metadata(wallet_account_retract_method_metadata);
            }

            {
                // register method wallet_account_delete
                cdcchain::api::MethodData wallet_account_delete_method_metadata{ "wallet_account_delete", nullptr,
                    /* description */ "delete account from Wallet.",
                    /* returns */ "bool",
                    /* params: */{
                        {"account_name", "string", cdcchain::api::required_positional, fc::ovariant()}
                          },
                    /* prerequisites */ (cdcchain::api::MethodPrerequisites) 4,
                    /* detailed description */ "delete account from Wallet.\n\nParameters:\n  account_name (string, required): The name of the account to retract.\n\nReturns:\n  bool\n",
                    /* aliases */ {}, false};
                store_method_metadata(wallet_account_delete_method_metadata);
            }

            {
                // register method wallet_transfer_to_address_rpc
                cdcchain::api::MethodData wallet_transfer_to_address_rpc_method_metadata{ "wallet_transfer_to_address_rpc", nullptr,
                    /* description */ "Do a simple (non-TITAN) transfer to an address",
                    /* returns */ "string",
                    /* params: */{
                        {"amount_to_transfer", "string", cdcchain::api::required_positional, fc::ovariant()},
                        {"asset_symbol", "asset_symbol", cdcchain::api::required_positional, fc::ovariant()},
                        {"from_account_name", "account_name", cdcchain::api::required_positional, fc::ovariant()},
                        {"to_address", "string", cdcchain::api::required_positional, fc::ovariant()},
                        {"memo_message", "information", cdcchain::api::optional_positional, fc::variant(fc::json::from_string("\"\""))},
                        {"strategy", "vote_strategy", cdcchain::api::optional_positional, fc::variant(fc::json::from_string("\"vote_recommended\""))}
                          },
                    /* prerequisites */ (cdcchain::api::MethodPrerequisites) 2,
                    /* detailed description */ "Do a simple (non-TITAN) transfer to an address\n\nParameters:\n  amount_to_transfer (string, required): the amount of shares to transfer\n  asset_symbol (asset_symbol, required): the asset to transfer\n  from_account_name (account_name, required): the source account to draw the shares from\n  to_address (string, required): the address or pubkey to transfer to\n  memo_message (information, optional, defaults to \"\"): a memo to store with the transaction\n  strategy (vote_strategy, optional, defaults to \"vote_recommended\"): enumeration [vote_none | vote_all | vote_random | vote_recommended] \n\nReturns:\n  string\n",
                    /* aliases */ {}, false};
                store_method_metadata(wallet_transfer_to_address_rpc_method_metadata);
            }

            {
                // register method wallet_account_balance_rpc
                cdcchain::api::MethodData wallet_account_balance_rpc_method_metadata{ "wallet_account_balance_rpc", nullptr,
                    /* description */ "Lists the total asset balances for the specified account",
                    /* returns */ "string",
                    /* params: */{
                        {"account_name", "account_name", cdcchain::api::optional_positional, fc::variant(fc::json::from_string("\"\""))}
                          },
                    /* prerequisites */ (cdcchain::api::MethodPrerequisites) 2,
                    /* detailed description */ "Lists the total asset balances for the specified account\n\nParameters:\n  account_name (account_name, optional, defaults to \"\"): the account to get a balance for, or leave empty for all accounts\n\nReturns:\n  string\n",
                    /* aliases */ {}, true};
                store_method_metadata(wallet_account_balance_rpc_method_metadata);
            }

            {
                // register method wallet_transfer_to_public_account_rpc
                cdcchain::api::MethodData wallet_transfer_to_public_account_rpc_method_metadata{ "wallet_transfer_to_public_account_rpc", nullptr,
                    /* description */ "Sends given amount to the given account",
                    /* returns */ "string",
                    /* params: */{
                        {"amount_to_transfer", "string", cdcchain::api::required_positional, fc::ovariant()},
                        {"asset_symbol", "asset_symbol", cdcchain::api::required_positional, fc::ovariant()},
                        {"from_account_name", "sending_account_name", cdcchain::api::required_positional, fc::ovariant()},
                        {"to_account_name", "receive_account_name", cdcchain::api::required_positional, fc::ovariant()},
                        {"memo_message", "information", cdcchain::api::optional_positional, fc::variant(fc::json::from_string("\"\""))},
                        {"strategy", "vote_strategy", cdcchain::api::optional_positional, fc::variant(fc::json::from_string("\"vote_recommended\""))}
                          },
                    /* prerequisites */ (cdcchain::api::MethodPrerequisites) 4,
                    /* detailed description */ "Sends given amount to the given account\n\nParameters:\n  amount_to_transfer (string, required): the amount of shares to transfer\n  asset_symbol (asset_symbol, required): the asset to transfer\n  from_account_name (sending_account_name, required): the source account to draw the shares from\n  to_account_name (receive_account_name, required): the account to transfer the shares to\n  memo_message (information, optional, defaults to \"\"): a memo to store with the transaction\n  strategy (vote_strategy, optional, defaults to \"vote_recommended\"): enumeration [vote_none | vote_all | vote_random | vote_recommended] \n\nReturns:\n  string\n",
                    /* aliases */ {}, false};
                store_method_metadata(wallet_transfer_to_public_account_rpc_method_metadata);
            }

            {
                // register method wallet_get_account_owner_publickey
                cdcchain::api::MethodData wallet_get_account_owner_publickey_method_metadata{ "wallet_get_account_owner_publickey", nullptr,
                    /* description */ "Get owner publickey of specific account",
                    /* returns */ "public_key",
                    /* params: */{
                        {"account_name", "account_name", cdcchain::api::required_positional, fc::ovariant()}
                          },
                    /* prerequisites */ (cdcchain::api::MethodPrerequisites) 4,
                    /* detailed description */ "Get owner publickey of specific account\n\nParameters:\n  account_name (account_name, required): the name of the account\n\nReturns:\n  public_key\n",
                    /* aliases */ {}, false};
                store_method_metadata(wallet_get_account_owner_publickey_method_metadata);
            }

            {
                // register method wallet_transfer_to_contract
                cdcchain::api::MethodData wallet_transfer_to_contract_method_metadata{ "wallet_transfer_to_contract", nullptr,
                    /* description */ "Do a simple transfer to a contract (name or address)",
                    /* returns */ "transaction_entry",
                    /* params: */{
                        {"amount_to_transfer", "real_amount", cdcchain::api::required_positional, fc::ovariant()},
                        {"asset_symbol", "asset_symbol", cdcchain::api::required_positional, fc::ovariant()},
                        {"from_account_name", "account_name", cdcchain::api::required_positional, fc::ovariant()},
                        {"to_contract", "string", cdcchain::api::required_positional, fc::ovariant()},
                        {"amount_for_exec", "real_amount", cdcchain::api::required_positional, fc::ovariant()}
                          },
                    /* prerequisites */ (cdcchain::api::MethodPrerequisites) 4,
                    /* detailed description */ "Do a simple transfer to a contract (name or address)\n\nParameters:\n  amount_to_transfer (real_amount, required): the amount of shares to transfer\n  asset_symbol (asset_symbol, required): the asset to transfer\n  from_account_name (account_name, required): the source account to draw the shares from\n  to_contract (string, required): the contract name or contract address to transfer to\n  amount_for_exec (real_amount, required): the amount of shares to exec  on_deposit callback of target contract\n\nReturns:\n  transaction_entry\n",
                    /* aliases */ {}, false};
                store_method_metadata(wallet_transfer_to_contract_method_metadata);
            }

            {
                // register method wallet_transfer_to_contract_testing
                cdcchain::api::MethodData wallet_transfer_to_contract_testing_method_metadata{ "wallet_transfer_to_contract_testing", nullptr,
                    /* description */ "Do a simple transfer to a contract (name or address) on local endpoint, and do not spread it on P2P network",
                    /* returns */ "asset_array",
                    /* params: */{
                        {"amount_to_transfer", "real_amount", cdcchain::api::required_positional, fc::ovariant()},
                        {"asset_symbol", "asset_symbol", cdcchain::api::required_positional, fc::ovariant()},
                        {"from_account_name", "account_name", cdcchain::api::required_positional, fc::ovariant()},
                        {"to_contract", "string", cdcchain::api::required_positional, fc::ovariant()}
                          },
                    /* prerequisites */ (cdcchain::api::MethodPrerequisites) 4,
                    /* detailed description */ "Do a simple transfer to a contract (name or address) on local endpoint, and do not spread it on P2P network\n\nParameters:\n  amount_to_transfer (real_amount, required): the amount of shares to transfer\n  asset_symbol (asset_symbol, required): the asset to transfer\n  from_account_name (account_name, required): the source account to draw the shares from\n  to_contract (string, required): the contract name or contract address to transfer to\n\nReturns:\n  asset_array\n",
                    /* aliases */ {}, false};
                store_method_metadata(wallet_transfer_to_contract_testing_method_metadata);
            }

            {
                // register method wallet_get_contracts
                cdcchain::api::MethodData wallet_get_contracts_method_metadata{ "wallet_get_contracts", nullptr,
                    /* description */ "get all the contracts belong to the account of the wallet",
                    /* returns */ "contract_id_list",
                    /* params: */{
                        {"account_name", "string", cdcchain::api::optional_positional, fc::variant(fc::json::from_string("\"\""))}
                          },
                    /* prerequisites */ (cdcchain::api::MethodPrerequisites) 4,
                    /* detailed description */ "get all the contracts belong to the account of the wallet\n\nParameters:\n  account_name (string, optional, defaults to \"\"): the account in wallet\n\nReturns:\n  contract_id_list\n",
                    /* aliases */ {}, false};
                store_method_metadata(wallet_get_contracts_method_metadata);
            }

            {
                // register method wallet_scan_contracts
                cdcchain::api::MethodData wallet_scan_contracts_method_metadata{ "wallet_scan_contracts", nullptr,
                    /* description */ "scan to get all the contracts",
                    /* returns */ "void",
                    /* params: */{                    },
                    /* prerequisites */ (cdcchain::api::MethodPrerequisites) 4,
                    /* detailed description */ "scan to get all the contracts\n\nParameters:\n  (none)\n\nReturns:\n  void\n",
                    /* aliases */ {}, false};
                store_method_metadata(wallet_scan_contracts_method_metadata);
            }

            {
                // register method wallet_builder_add_signature
                cdcchain::api::MethodData wallet_builder_add_signature_method_metadata{ "wallet_builder_add_signature", nullptr,
                    /* description */ "Review a transaction and add a signature.",
                    /* returns */ "transaction_builder",
                    /* params: */{
                        {"builder", "transaction_builder", cdcchain::api::required_positional, fc::ovariant()},
                        {"broadcast", "bool", cdcchain::api::optional_positional, fc::variant(fc::json::from_string("false"))}
                          },
                    /* prerequisites */ (cdcchain::api::MethodPrerequisites) 4,
                    /* detailed description */ "Review a transaction and add a signature.\n\nParameters:\n  builder (transaction_builder, required): A transaction builder object created by a wallet. If null, tries to use builder in file.\n  broadcast (bool, optional, defaults to false): Try to broadcast this transaction? (bool, optional, defaults to false)\n\nReturns:\n  transaction_builder\n",
                    /* aliases */ {}, false};
                store_method_metadata(wallet_builder_add_signature_method_metadata);
            }

            {
                // register method wallet_builder_file_add_signature
                cdcchain::api::MethodData wallet_builder_file_add_signature_method_metadata{ "wallet_builder_file_add_signature", nullptr,
                    /* description */ "Review a transaction in a builder file and add a signature.",
                    /* returns */ "transaction_builder",
                    /* params: */{
                        {"builder_path", "path", cdcchain::api::required_positional, fc::ovariant()},
                        {"broadcast", "bool", cdcchain::api::optional_positional, fc::variant(fc::json::from_string("false"))}
                          },
                    /* prerequisites */ (cdcchain::api::MethodPrerequisites) 4,
                    /* detailed description */ "Review a transaction in a builder file and add a signature.\n\nParameters:\n  builder_path (path, required): builder_path If specified, will write builder here instead of to DATA_DIR/transactions/latest.trx\n  broadcast (bool, optional, defaults to false): Try to broadcast this transaction? (bool, optional, defaults to false)\n\nReturns:\n  transaction_builder\n",
                    /* aliases */ {}, false};
                store_method_metadata(wallet_builder_file_add_signature_method_metadata);
            }

            {
                // register method wallet_multisig_deposit
                cdcchain::api::MethodData wallet_multisig_deposit_method_metadata{ "wallet_multisig_deposit", nullptr,
                    /* description */ "transfer to multisig account",
                    /* returns */ "transaction_entry",
                    /* params: */{
                        {"amount", "string", cdcchain::api::required_positional, fc::ovariant()},
                        {"asset_symbol", "asset_symbol", cdcchain::api::required_positional, fc::ovariant()},
                        {"from_account", "string", cdcchain::api::required_positional, fc::ovariant()},
                        {"to_account", "string", cdcchain::api::required_positional, fc::ovariant()},
                        {"memo_message", "information", cdcchain::api::optional_positional, fc::variant(fc::json::from_string("\"\""))}
                          },
                    /* prerequisites */ (cdcchain::api::MethodPrerequisites) 4,
                    /* detailed description */ "transfer to multisig account\n\nParameters:\n  amount (string, required):  how much to transfer (string, required)\n  asset_symbol (asset_symbol, required): which asset (string, required)\n  from_account (string, required):  TITAN name to withdraw from (string, required)\n  to_account (string, required): deposit multisig account address which must be created. (string, required)\n  memo_message (information, optional, defaults to \"\"): a memo to store with the transaction\n\nReturns:\n  transaction_entry\n",
                    /* aliases */ {}, false};
                store_method_metadata(wallet_multisig_deposit_method_metadata);
            }

            {
                // register method wallet_import_multisig_account
                cdcchain::api::MethodData wallet_import_multisig_account_method_metadata{ "wallet_import_multisig_account", nullptr,
                    /* description */ "import multisig account,if address exist return multisig detail",
                    /* returns */ "variant_object",
                    /* params: */{
                        {"multisig_address", "address", cdcchain::api::required_positional, fc::ovariant()}
                          },
                    /* prerequisites */ (cdcchain::api::MethodPrerequisites) 4,
                    /* detailed description */ "import multisig account,if address exist return multisig detail\n\nParameters:\n  multisig_address (address, required): multisig address\n\nReturns:\n  variant_object\n",
                    /* aliases */ {}, false};
                store_method_metadata(wallet_import_multisig_account_method_metadata);
            }

            {
                // register method wallet_import_multisig_account_by_detail
                cdcchain::api::MethodData wallet_import_multisig_account_by_detail_method_metadata{ "wallet_import_multisig_account_by_detail", nullptr,
                    /* description */ "get multisig account address and import address",
                    /* returns */ "address",
                    /* params: */{
                        {"asset_symbol", "asset_symbol", cdcchain::api::required_positional, fc::ovariant()},
                        {"m", "uint32_t", cdcchain::api::required_positional, fc::ovariant()},
                        {"addresses", "address_list", cdcchain::api::required_positional, fc::ovariant()}
                          },
                    /* prerequisites */ (cdcchain::api::MethodPrerequisites) 4,
                    /* detailed description */ "get multisig account address and import address\n\nParameters:\n  asset_symbol (asset_symbol, required): which asset (string, required)\n  m (uint32_t, required): Required number of signatures (uint32_t, required)\n  addresses (address_list, required): List of possible addresses for signatures (address_list, required)\n\nReturns:\n  address\n",
                    /* aliases */ {}, false};
                store_method_metadata(wallet_import_multisig_account_by_detail_method_metadata);
            }

            {
                // register method wallet_multisig_withdraw_start
                cdcchain::api::MethodData wallet_multisig_withdraw_start_method_metadata{ "wallet_multisig_withdraw_start", nullptr,
                    /* description */ "transfer to normal account from multisig account",
                    /* returns */ "transaction_builder",
                    /* params: */{
                        {"amount", "string", cdcchain::api::required_positional, fc::ovariant()},
                        {"asset_symbol", "asset_symbol", cdcchain::api::required_positional, fc::ovariant()},
                        {"from", "address", cdcchain::api::required_positional, fc::ovariant()},
                        {"to_address", "address", cdcchain::api::required_positional, fc::ovariant()},
                        {"memo_message", "information", cdcchain::api::optional_positional, fc::variant(fc::json::from_string("\"\""))},
                        {"builder_path", "path", cdcchain::api::optional_positional, fc::variant(fc::json::from_string("\"\""))}
                          },
                    /* prerequisites */ (cdcchain::api::MethodPrerequisites) 4,
                    /* detailed description */ "transfer to normal account from multisig account\n\nParameters:\n  amount (string, required):  how much to transfer (string, required)\n  asset_symbol (asset_symbol, required): which asset (string, required)\n  from (address, required): multisig balance ID to withdraw from (address, required)\n  to_address (address, required): address to receive funds (address, required)\n  memo_message (information, optional, defaults to \"\"): a memo to store with the transaction\n  builder_path (path, optional, defaults to \"\"): If specified, will write builder here instead of to DATA_DIR/transactions/latest.trx\n\nReturns:\n  transaction_builder\n",
                    /* aliases */ {}, false};
                store_method_metadata(wallet_multisig_withdraw_start_method_metadata);
            }

            {
                // register method wallet_create_multisig_account
                cdcchain::api::MethodData wallet_create_multisig_account_method_metadata{ "wallet_create_multisig_account", nullptr,
                    /* description */ "transfer to multisig account",
                    /* returns */ "pair<string, wallet_transaction_entry>",
                    /* params: */{
                        {"amount", "string", cdcchain::api::required_positional, fc::ovariant()},
                        {"asset_symbol", "asset_symbol", cdcchain::api::required_positional, fc::ovariant()},
                        {"from_account", "string", cdcchain::api::required_positional, fc::ovariant()},
                        {"m", "uint32_t", cdcchain::api::required_positional, fc::ovariant()},
                        {"addresses", "address_list", cdcchain::api::required_positional, fc::ovariant()},
                        {"memo_message", "information", cdcchain::api::optional_positional, fc::variant(fc::json::from_string("\"\""))}
                          },
                    /* prerequisites */ (cdcchain::api::MethodPrerequisites) 4,
                    /* detailed description */ "transfer to multisig account\n\nParameters:\n  amount (string, required):  how much to transfer (string, required)\n  asset_symbol (asset_symbol, required): which asset (string, required)\n  from_account (string, required):  TITAN name to withdraw from (string, required)\n  m (uint32_t, required): Required number of signatures (uint32_t, required)\n  addresses (address_list, required): List of possible addresses for signatures (address_list, required)\n  memo_message (information, optional, defaults to \"\"): a memo to store with the transaction\n\nReturns:\n  pair<string, wallet_transaction_entry>\n",
                    /* aliases */ {}, false};
                store_method_metadata(wallet_create_multisig_account_method_metadata);
            }

            {
                // register method wallet_multisig_account_history
                cdcchain::api::MethodData wallet_multisig_account_history_method_metadata{ "wallet_multisig_account_history", nullptr,
                    /* description */ "Lists multisig account transaction history for the specified account",
                    /* returns */ "pretty_transactions",
                    /* params: */{
                        {"account_address", "string", cdcchain::api::required_positional, fc::ovariant()},
                        {"asset_symbol", "string", cdcchain::api::optional_positional, fc::variant(fc::json::from_string("\"\""))},
                        {"limit", "int32_t", cdcchain::api::optional_positional, fc::variant(fc::json::from_string("0"))},
                        {"start_block_num", "uint32_t", cdcchain::api::optional_positional, fc::variant(fc::json::from_string("0"))},
                        {"end_block_num", "uint32_t", cdcchain::api::optional_positional, fc::variant(fc::json::from_string("-1"))}
                          },
                    /* prerequisites */ (cdcchain::api::MethodPrerequisites) 2,
                    /* detailed description */ "Lists multisig account transaction history for the specified account\n\nParameters:\n  account_address (string, required): the multisig account history\n  asset_symbol (string, optional, defaults to \"\"): only include transactions involving the specified asset, or \"\" to include all\n  limit (int32_t, optional, defaults to 0): limit the number of returned transactions; negative for most recent and positive for least recent. 0 does not limit\n  start_block_num (uint32_t, optional, defaults to 0): the earliest block number to list transactions from; 0 to include all transactions starting from genesis\n  end_block_num (uint32_t, optional, defaults to -1): the latest block to list transaction from; -1 to include all transactions ending at the head block\n\nReturns:\n  pretty_transactions\n",
                    /* aliases */ {"multisig_history"}, false};
                store_method_metadata(wallet_multisig_account_history_method_metadata);
            }

            {
                // register method wallet_multisig_account_balance
                cdcchain::api::MethodData wallet_multisig_account_balance_method_metadata{ "wallet_multisig_account_balance", nullptr,
                    /* description */ "Lists the total asset balances for the specified account",
                    /* returns */ "account_balance_summary_type",
                    /* params: */{
                        {"account_address", "string", cdcchain::api::optional_positional, fc::variant(fc::json::from_string("\"\""))}
                          },
                    /* prerequisites */ (cdcchain::api::MethodPrerequisites) 2,
                    /* detailed description */ "Lists the total asset balances for the specified account\n\nParameters:\n  account_address (string, optional, defaults to \"\"): the multisig account to get a balance for, or leave empty for all accounts\n\nReturns:\n  account_balance_summary_type\n",
                    /* aliases */ {"multisig_balance"}, true};
                store_method_metadata(wallet_multisig_account_balance_method_metadata);
            }

            {
                // register method wallet_builder_get_multisig_detail
                cdcchain::api::MethodData wallet_builder_get_multisig_detail_method_metadata{ "wallet_builder_get_multisig_detail", nullptr,
                    /* description */ "get builder signature details",
                    /* returns */ "variant_object",
                    /* params: */{
                        {"transaction_builder", "transaction_builder", cdcchain::api::required_positional, fc::ovariant()}
                          },
                    /* prerequisites */ (cdcchain::api::MethodPrerequisites) 2,
                    /* detailed description */ "get builder signature details\n\nParameters:\n  transaction_builder (transaction_builder, required): transaction builder json data\n\nReturns:\n  variant_object\n",
                    /* aliases */ {}, true};
                store_method_metadata(wallet_builder_get_multisig_detail_method_metadata);
            }

            {
                // register method wallet_builder_file_get_multisig_detail
                cdcchain::api::MethodData wallet_builder_file_get_multisig_detail_method_metadata{ "wallet_builder_file_get_multisig_detail", nullptr,
                    /* description */ "get builder signature details",
                    /* returns */ "variant_object",
                    /* params: */{
                        {"builder_path", "path", cdcchain::api::required_positional, fc::ovariant()}
                          },
                    /* prerequisites */ (cdcchain::api::MethodPrerequisites) 2,
                    /* detailed description */ "get builder signature details\n\nParameters:\n  builder_path (path, required): builder_path If specified, will write builder here instead of to DATA_DIR/transactions/latest.trx\n\nReturns:\n  variant_object\n",
                    /* aliases */ {}, true};
                store_method_metadata(wallet_builder_file_get_multisig_detail_method_metadata);
            }

            {
                // register method about
                cdcchain::api::MethodData about_method_metadata{ "about", nullptr,
                    /* description */ "Returns version number and associated information for this client",
                    /* returns */ "json_object",
                    /* params: */{                    },
                    /* prerequisites */ (cdcchain::api::MethodPrerequisites) 0,
                    /* detailed description */ "Returns version number and associated information for this client\n\nParameters:\n  (none)\n\nReturns:\n  json_object\n",
                    /* aliases */ {}, false};
                store_method_metadata(about_method_metadata);
            }

            {
                // register method get_info
                cdcchain::api::MethodData get_info_method_metadata{ "get_info", nullptr,
                    /* description */ "Returns version number and associated information for this client",
                    /* returns */ "json_object",
                    /* params: */{                    },
                    /* prerequisites */ (cdcchain::api::MethodPrerequisites) 0,
                    /* detailed description */ "Returns version number and associated information for this client\n\nParameters:\n  (none)\n\nReturns:\n  json_object\n",
                    /* aliases */ {"getinfo", "info"}, false};
                store_method_metadata(get_info_method_metadata);
            }

            {
                // register method stop
                cdcchain::api::MethodData stop_method_metadata{ "stop", nullptr,
                    /* description */ "shut down the RPC server and exit this client",
                    /* returns */ "void",
                    /* params: */{                    },
                    /* prerequisites */ (cdcchain::api::MethodPrerequisites) 1,
                    /* detailed description */ "shut down the RPC server and exit this client\n\nParameters:\n  (none)\n\nReturns:\n  void\n",
                    /* aliases */ {"quit", "exit"}, false};
                store_method_metadata(stop_method_metadata);
            }

            {
                // register method help
                cdcchain::api::MethodData help_method_metadata{ "help", nullptr,
                    /* description */ "display a list of commands, or detailed help on an individual command",
                    /* returns */ "string",
                    /* params: */{
                        {"command_name", "method_name", cdcchain::api::optional_positional, fc::variant(fc::json::from_string("\"\""))}
                          },
                    /* prerequisites */ (cdcchain::api::MethodPrerequisites) 0,
                    /* detailed description */ "display a list of commands, or detailed help on an individual command\n\nParameters:\n  command_name (method_name, optional, defaults to \"\"): the name of the method to get detailed help, or omit this for a list of commands\n\nReturns:\n  string\n",
                    /* aliases */ {"h"}, false};
                store_method_metadata(help_method_metadata);
            }

            {
                // register method validate_address
                cdcchain::api::MethodData validate_address_method_metadata{ "validate_address", nullptr,
                    /* description */ "Return information about given Ub address",
                    /* returns */ "json_object",
                    /* params: */{
                        {"address", "string", cdcchain::api::required_positional, fc::ovariant()}
                          },
                    /* prerequisites */ (cdcchain::api::MethodPrerequisites) 0,
                    /* detailed description */ "Return information about given Ub address\n\nParameters:\n  address (string, required): the address or public key to validate\n\nReturns:\n  json_object\n",
                    /* aliases */ {"validateaddress"}, false};
                store_method_metadata(validate_address_method_metadata);
            }

            {
                // register method execute_command_line
                cdcchain::api::MethodData execute_command_line_method_metadata{ "execute_command_line", nullptr,
                    /* description */ "Execute the given command as if it were typed on the CLI",
                    /* returns */ "string",
                    /* params: */{
                        {"input", "passphrase", cdcchain::api::required_positional, fc::ovariant()}
                          },
                    /* prerequisites */ (cdcchain::api::MethodPrerequisites) 1,
                    /* detailed description */ "Execute the given command as if it were typed on the CLI\n\nParameters:\n  input (passphrase, required): The entire command input as if it were a CLI input\n\nReturns:\n  string\n",
                    /* aliases */ {}, false};
                store_method_metadata(execute_command_line_method_metadata);
            }

            {
                // register method execute_script
                cdcchain::api::MethodData execute_script_method_metadata{ "execute_script", nullptr,
                    /* description */ "Execute the given file as if it were typed on the CLI",
                    /* returns */ "void",
                    /* params: */{
                        {"script", "filename", cdcchain::api::required_positional, fc::ovariant()}
                          },
                    /* prerequisites */ (cdcchain::api::MethodPrerequisites) 1,
                    /* detailed description */ "Execute the given file as if it were typed on the CLI\n\nParameters:\n  script (filename, required): Name of a file containing CLI commands to execute\n\nReturns:\n  void\n",
                    /* aliases */ {}, false};
                store_method_metadata(execute_script_method_metadata);
            }

            {
                // register method batch
                cdcchain::api::MethodData batch_method_metadata{ "batch", nullptr,
                    /* description */ "Takes any no_prerequisites command and an array of its arguments and returns an array of results. Example: batch blockchain_get_blockhash [[1], [2]]",
                    /* returns */ "variants",
                    /* params: */{
                        {"method_name", "string", cdcchain::api::required_positional, fc::ovariant()},
                        {"parameters_list", "parameters_list", cdcchain::api::required_positional, fc::ovariant()}
                          },
                    /* prerequisites */ (cdcchain::api::MethodPrerequisites) 0,
                    /* detailed description */ "Takes any no_prerequisites command and an array of its arguments and returns an array of results. Example: batch blockchain_get_blockhash [[1], [2]]\n\nParameters:\n  method_name (string, required): The command name for calling\n  parameters_list (parameters_list, required): The list of list of parameters for this command, the return will be the list of execute result of corresponding parameters\n\nReturns:\n  variants\n",
                    /* aliases */ {}, false};
                store_method_metadata(batch_method_metadata);
            }

            {
                // register method batch_authenticated
                cdcchain::api::MethodData batch_authenticated_method_metadata{ "batch_authenticated", nullptr,
                    /* description */ "Takes any no_prerequisites command and an array of its arguments and returns an array of results. Example: batch_authenticated blockchain_get_blockhash [[1], [2]]",
                    /* returns */ "variants",
                    /* params: */{
                        {"method_name", "string", cdcchain::api::required_positional, fc::ovariant()},
                        {"parameters_list", "parameters_list", cdcchain::api::required_positional, fc::ovariant()}
                          },
                    /* prerequisites */ (cdcchain::api::MethodPrerequisites) 1,
                    /* detailed description */ "Takes any no_prerequisites command and an array of its arguments and returns an array of results. Example: batch_authenticated blockchain_get_blockhash [[1], [2]]\n\nParameters:\n  method_name (string, required): The command name for calling\n  parameters_list (parameters_list, required): The list of list of parameters for this command, the return will be the list of execute result of corresponding parameters\n\nReturns:\n  variants\n",
                    /* aliases */ {}, false};
                store_method_metadata(batch_authenticated_method_metadata);
            }

            {
                // register method builder_finalize_and_sign
                cdcchain::api::MethodData builder_finalize_and_sign_method_metadata{ "builder_finalize_and_sign", nullptr,
                    /* description */ "Takes a transaction builder and returns a signed transaction for broadcasting",
                    /* returns */ "transaction_entry",
                    /* params: */{
                        {"builder", "transaction_builder", cdcchain::api::required_positional, fc::ovariant()}
                          },
                    /* prerequisites */ (cdcchain::api::MethodPrerequisites) 5,
                    /* detailed description */ "Takes a transaction builder and returns a signed transaction for broadcasting\n\nParameters:\n  builder (transaction_builder, required): \n\nReturns:\n  transaction_entry\n",
                    /* aliases */ {}, false};
                store_method_metadata(builder_finalize_and_sign_method_metadata);
            }

            {
                // register method meta_help
                cdcchain::api::MethodData meta_help_method_metadata{ "meta_help", nullptr,
                    /* description */ "Returns help information as JSON data",
                    /* returns */ "method_map_type",
                    /* params: */{                    },
                    /* prerequisites */ (cdcchain::api::MethodPrerequisites) 0,
                    /* detailed description */ "Returns help information as JSON data\n\nParameters:\n  (none)\n\nReturns:\n  method_map_type\n",
                    /* aliases */ {}, false};
                store_method_metadata(meta_help_method_metadata);
            }

            {
                // register method rpc_set_username
                cdcchain::api::MethodData rpc_set_username_method_metadata{ "rpc_set_username", nullptr,
                    /* description */ "Set the username for basic auth for the http server.",
                    /* returns */ "void",
                    /* params: */{
                        {"username", "string", cdcchain::api::optional_positional, fc::variant(fc::json::from_string("\"\""))}
                          },
                    /* prerequisites */ (cdcchain::api::MethodPrerequisites) 1,
                    /* detailed description */ "Set the username for basic auth for the http server.\n\nParameters:\n  username (string, optional, defaults to \"\"): Username for basic auth\n\nReturns:\n  void\n",
                    /* aliases */ {}, false};
                store_method_metadata(rpc_set_username_method_metadata);
            }

            {
                // register method rpc_set_password
                cdcchain::api::MethodData rpc_set_password_method_metadata{ "rpc_set_password", nullptr,
                    /* description */ "Set the password for basic auth for the http server.",
                    /* returns */ "void",
                    /* params: */{
                        {"password", "passphrase", cdcchain::api::optional_positional, fc::variant(fc::json::from_string("\"\""))}
                          },
                    /* prerequisites */ (cdcchain::api::MethodPrerequisites) 1,
                    /* detailed description */ "Set the password for basic auth for the http server.\n\nParameters:\n  password (passphrase, optional, defaults to \"\"): Password for basic auth\n\nReturns:\n  void\n",
                    /* aliases */ {}, false};
                store_method_metadata(rpc_set_password_method_metadata);
            }

            {
                // register method rpc_start_server
                cdcchain::api::MethodData rpc_start_server_method_metadata{ "rpc_start_server", nullptr,
                    /* description */ "Set the port and start rpc server.",
                    /* returns */ "void",
                    /* params: */{
                        {"port", "uint32_t", cdcchain::api::optional_positional, fc::variant(fc::json::from_string("\"65065\""))}
                          },
                    /* prerequisites */ (cdcchain::api::MethodPrerequisites) 1,
                    /* detailed description */ "Set the port and start rpc server.\n\nParameters:\n  port (uint32_t, optional, defaults to \"65065\"): Port for rpc server\n\nReturns:\n  void\n",
                    /* aliases */ {}, false};
                store_method_metadata(rpc_start_server_method_metadata);
            }

            {
                // register method http_start_server
                cdcchain::api::MethodData http_start_server_method_metadata{ "http_start_server", nullptr,
                    /* description */ "Set the port and start http server.",
                    /* returns */ "void",
                    /* params: */{
                        {"port", "uint32_t", cdcchain::api::optional_positional, fc::variant(fc::json::from_string("\"65066\""))}
                          },
                    /* prerequisites */ (cdcchain::api::MethodPrerequisites) 1,
                    /* detailed description */ "Set the port and start http server.\n\nParameters:\n  port (uint32_t, optional, defaults to \"65066\"): Port for http server\n\nReturns:\n  void\n",
                    /* aliases */ {}, false};
                store_method_metadata(http_start_server_method_metadata);
            }

            {
                // register method ntp_update_time
                cdcchain::api::MethodData ntp_update_time_method_metadata{ "ntp_update_time", nullptr,
                    /* description */ "Update the NTP time right now.",
                    /* returns */ "void",
                    /* params: */{                    },
                    /* prerequisites */ (cdcchain::api::MethodPrerequisites) 1,
                    /* detailed description */ "Update the NTP time right now.\n\nParameters:\n  (none)\n\nReturns:\n  void\n",
                    /* aliases */ {}, false};
                store_method_metadata(ntp_update_time_method_metadata);
            }

            {
                // register method disk_usage
                cdcchain::api::MethodData disk_usage_method_metadata{ "disk_usage", nullptr,
                    /* description */ "Report disk space taken up by different groups of client files",
                    /* returns */ "variant",
                    /* params: */{                    },
                    /* prerequisites */ (cdcchain::api::MethodPrerequisites) 1,
                    /* detailed description */ "Report disk space taken up by different groups of client files\n\nParameters:\n  (none)\n\nReturns:\n  variant\n",
                    /* aliases */ {"size", "sizes", "usage", "diskusage"}, false};
                store_method_metadata(disk_usage_method_metadata);
            }

            {
                // register method contract_compile
                cdcchain::api::MethodData contract_compile_method_metadata{ "contract_compile", nullptr,
                    /* description */ "compile contract source code to byte code, and store to binary file",
                    /* returns */ "filename",
                    /* params: */{
                        {"filename", "filename", cdcchain::api::required_positional, fc::ovariant()}
                          },
                    /* prerequisites */ (cdcchain::api::MethodPrerequisites) 0,
                    /* detailed description */ "compile contract source code to byte code, and store to binary file\n\nParameters:\n  filename (filename, required): contract source file name\n\nReturns:\n  filename\n",
                    /* aliases */ {}, true};
                store_method_metadata(contract_compile_method_metadata);
            }

            {
                // register method contract_register
                cdcchain::api::MethodData contract_register_method_metadata{ "contract_register", nullptr,
                    /* description */ "register a temporary contract",
                    /* returns */ "string",
                    /* params: */{
                        {"owner", "string", cdcchain::api::required_positional, fc::ovariant()},
                        {"codefile", "filename", cdcchain::api::required_positional, fc::ovariant()},
                        {"asset_symbol", "string", cdcchain::api::required_positional, fc::ovariant()},
                        {"init_limit", "optional_double", cdcchain::api::required_positional, fc::ovariant()}
                          },
                    /* prerequisites */ (cdcchain::api::MethodPrerequisites) 4,
                    /* detailed description */ "register a temporary contract\n\nParameters:\n  owner (string, required): contract register owner address\n  codefile (filename, required): contract bytesfile name\n  asset_symbol (string, required): asset symbol name\n  init_limit (optional_double, required): the limit of asset amount used to init contract \n\nReturns:\n  string\n",
                    /* aliases */ {}, false};
                store_method_metadata(contract_register_method_metadata);
            }

            {
                // register method contract_register_testing
                cdcchain::api::MethodData contract_register_testing_method_metadata{ "contract_register_testing", nullptr,
                    /* description */ "register a temporary contract on local endpoint, and do not spread it on P2P network",
                    /* returns */ "asset_array",
                    /* params: */{
                        {"owner", "string", cdcchain::api::required_positional, fc::ovariant()},
                        {"codefile", "filename", cdcchain::api::required_positional, fc::ovariant()}
                          },
                    /* prerequisites */ (cdcchain::api::MethodPrerequisites) 4,
                    /* detailed description */ "register a temporary contract on local endpoint, and do not spread it on P2P network\n\nParameters:\n  owner (string, required): contract register owner address\n  codefile (filename, required): contract bytesfile name\n\nReturns:\n  asset_array\n",
                    /* aliases */ {}, false};
                store_method_metadata(contract_register_testing_method_metadata);
            }

            {
                // register method contract_upgrade
                cdcchain::api::MethodData contract_upgrade_method_metadata{ "contract_upgrade", nullptr,
                    /* description */ "upgrade temporary contract to permanent contract",
                    /* returns */ "transaction_entry",
                    /* params: */{
                        {"contract_address", "string", cdcchain::api::required_positional, fc::ovariant()},
                        {"upgrader_name", "string", cdcchain::api::required_positional, fc::ovariant()},
                        {"new_contract_name", "string", cdcchain::api::required_positional, fc::ovariant()},
                        {"new_contract_desc", "information", cdcchain::api::required_positional, fc::ovariant()},
                        {"asset_symbol", "string", cdcchain::api::required_positional, fc::ovariant()},
                        {"exec_limit", "optional_double", cdcchain::api::required_positional, fc::ovariant()}
                          },
                    /* prerequisites */ (cdcchain::api::MethodPrerequisites) 4,
                    /* detailed description */ "upgrade temporary contract to permanent contract\n\nParameters:\n  contract_address (string, required): contract address need to upgrade\n  upgrader_name (string, required): upgrader name\n  new_contract_name (string, required): permanent contract name\n  new_contract_desc (information, required): permanent contract description\n  asset_symbol (string, required): symbol of asset used to destroy\n  exec_limit (optional_double, required): the limit of asset amount used to destroy contract \n\nReturns:\n  transaction_entry\n",
                    /* aliases */ {}, false};
                store_method_metadata(contract_upgrade_method_metadata);
            }

            {
                // register method contract_upgrade_testing
                cdcchain::api::MethodData contract_upgrade_testing_method_metadata{ "contract_upgrade_testing", nullptr,
                    /* description */ "test upgrade temporary contract to permanent contract",
                    /* returns */ "asset_array",
                    /* params: */{
                        {"contract_address", "string", cdcchain::api::required_positional, fc::ovariant()},
                        {"upgrader_name", "string", cdcchain::api::required_positional, fc::ovariant()},
                        {"new_contract_name", "string", cdcchain::api::required_positional, fc::ovariant()},
                        {"new_contract_desc", "information", cdcchain::api::required_positional, fc::ovariant()}
                          },
                    /* prerequisites */ (cdcchain::api::MethodPrerequisites) 4,
                    /* detailed description */ "test upgrade temporary contract to permanent contract\n\nParameters:\n  contract_address (string, required): contract address need to upgrade\n  upgrader_name (string, required): upgrader name\n  new_contract_name (string, required): permanent contract name\n  new_contract_desc (information, required): permanent contract description\n\nReturns:\n  asset_array\n",
                    /* aliases */ {}, false};
                store_method_metadata(contract_upgrade_testing_method_metadata);
            }

            {
                // register method contract_destroy
                cdcchain::api::MethodData contract_destroy_method_metadata{ "contract_destroy", nullptr,
                    /* description */ "destroy temporary contract",
                    /* returns */ "transaction_entry",
                    /* params: */{
                        {"contract_address", "string", cdcchain::api::required_positional, fc::ovariant()},
                        {"destroyer_name", "string", cdcchain::api::required_positional, fc::ovariant()},
                        {"asset_symbol", "string", cdcchain::api::required_positional, fc::ovariant()},
                        {"exec_limit", "optional_double", cdcchain::api::required_positional, fc::ovariant()}
                          },
                    /* prerequisites */ (cdcchain::api::MethodPrerequisites) 4,
                    /* detailed description */ "destroy temporary contract\n\nParameters:\n  contract_address (string, required): contract address need to destroy\n  destroyer_name (string, required): destroyer name\n  asset_symbol (string, required): symbol of asset used to destroy\n  exec_limit (optional_double, required): the limit of asset amount used to destroy contract \n\nReturns:\n  transaction_entry\n",
                    /* aliases */ {}, false};
                store_method_metadata(contract_destroy_method_metadata);
            }

            {
                // register method contract_destroy_testing
                cdcchain::api::MethodData contract_destroy_testing_method_metadata{ "contract_destroy_testing", nullptr,
                    /* description */ "testing destroy temporary contract",
                    /* returns */ "asset_array",
                    /* params: */{
                        {"contract_address", "string", cdcchain::api::required_positional, fc::ovariant()},
                        {"destroyer_name", "string", cdcchain::api::required_positional, fc::ovariant()}
                          },
                    /* prerequisites */ (cdcchain::api::MethodPrerequisites) 4,
                    /* detailed description */ "testing destroy temporary contract\n\nParameters:\n  contract_address (string, required): contract address need to destroy\n  destroyer_name (string, required): destroyer name\n\nReturns:\n  asset_array\n",
                    /* aliases */ {}, false};
                store_method_metadata(contract_destroy_testing_method_metadata);
            }

            {
                // register method contract_call
                cdcchain::api::MethodData contract_call_method_metadata{ "contract_call", nullptr,
                    /* description */ "call contract by contract name or contract address",
                    /* returns */ "transaction_entry",
                    /* params: */{
                        {"contract", "string", cdcchain::api::required_positional, fc::ovariant()},
                        {"caller_name", "string", cdcchain::api::required_positional, fc::ovariant()},
                        {"function_name", "string", cdcchain::api::required_positional, fc::ovariant()},
                        {"params", "string", cdcchain::api::required_positional, fc::ovariant()},
                        {"asset_symbol", "string", cdcchain::api::required_positional, fc::ovariant()},
                        {"call_limit", "optional_double", cdcchain::api::required_positional, fc::ovariant()}
                          },
                    /* prerequisites */ (cdcchain::api::MethodPrerequisites) 4,
                    /* detailed description */ "call contract by contract name or contract address\n\nParameters:\n  contract (string, required): contract name or contract address need to be called\n  caller_name (string, required): caller name\n  function_name (string, required): function in contract \n  params (string, required): parameters which would be passed to function\n  asset_symbol (string, required): symbol of asset used to call\n  call_limit (optional_double, required): the limit of asset amount used to call contract \n\nReturns:\n  transaction_entry\n",
                    /* aliases */ {}, false};
                store_method_metadata(contract_call_method_metadata);
            }

            {
                // register method contract_get_info
                cdcchain::api::MethodData contract_get_info_method_metadata{ "contract_get_info", nullptr,
                    /* description */ "get contract entry by contract name or contract address",
                    /* returns */ "contract_entry_printable",
                    /* params: */{
                        {"contract", "string", cdcchain::api::required_positional, fc::ovariant()}
                          },
                    /* prerequisites */ (cdcchain::api::MethodPrerequisites) 0,
                    /* detailed description */ "get contract entry by contract name or contract address\n\nParameters:\n  contract (string, required): contract name or contract address\n\nReturns:\n  contract_entry_printable\n",
                    /* aliases */ {}, false};
                store_method_metadata(contract_get_info_method_metadata);
            }

            {
                // register method contract_get_balance
                cdcchain::api::MethodData contract_get_balance_method_metadata{ "contract_get_balance", nullptr,
                    /* description */ "get contract balance entry and margin balance entry by contract name or contract address",
                    /* returns */ "balance_entry_list",
                    /* params: */{
                        {"contract", "string", cdcchain::api::required_positional, fc::ovariant()}
                          },
                    /* prerequisites */ (cdcchain::api::MethodPrerequisites) 0,
                    /* detailed description */ "get contract balance entry and margin balance entry by contract name or contract address\n\nParameters:\n  contract (string, required): contract name or contract address\n\nReturns:\n  balance_entry_list\n",
                    /* aliases */ {}, false};
                store_method_metadata(contract_get_balance_method_metadata);
            }

            {
                // register method contract_call_testing
                cdcchain::api::MethodData contract_call_testing_method_metadata{ "contract_call_testing", nullptr,
                    /* description */ "call contract function by contract name or contract address on local endpoint, and do not spread it on P2P network",
                    /* returns */ "asset_array",
                    /* params: */{
                        {"contract", "string", cdcchain::api::required_positional, fc::ovariant()},
                        {"caller_name", "string", cdcchain::api::required_positional, fc::ovariant()},
                        {"function_name", "string", cdcchain::api::required_positional, fc::ovariant()},
                        {"params", "string", cdcchain::api::required_positional, fc::ovariant()}
                          },
                    /* prerequisites */ (cdcchain::api::MethodPrerequisites) 4,
                    /* detailed description */ "call contract function by contract name or contract address on local endpoint, and do not spread it on P2P network\n\nParameters:\n  contract (string, required): contract name or contract address need to be called\n  caller_name (string, required): caller name\n  function_name (string, required): function in contract \n  params (string, required): parameters which would be passed to function\n\nReturns:\n  asset_array\n",
                    /* aliases */ {}, false};
                store_method_metadata(contract_call_testing_method_metadata);
            }

            {
                // register method contract_call_offline
                cdcchain::api::MethodData contract_call_offline_method_metadata{ "contract_call_offline", nullptr,
                    /* description */ "call contract offline function by contract name or contract address",
                    /* returns */ "string",
                    /* params: */{
                        {"contract", "string", cdcchain::api::required_positional, fc::ovariant()},
                        {"caller_name", "string", cdcchain::api::required_positional, fc::ovariant()},
                        {"function_name", "string", cdcchain::api::required_positional, fc::ovariant()},
                        {"params", "string", cdcchain::api::required_positional, fc::ovariant()}
                          },
                    /* prerequisites */ (cdcchain::api::MethodPrerequisites) 4,
                    /* detailed description */ "call contract offline function by contract name or contract address\n\nParameters:\n  contract (string, required): contract name or contract address need to be called\n  caller_name (string, required): caller name\n  function_name (string, required): offline function in contract \n  params (string, required): parameters which would be passed to offline function\n\nReturns:\n  string\n",
                    /* aliases */ {}, false};
                store_method_metadata(contract_call_offline_method_metadata);
            }

            {
                // register method contract_load_to_file
                cdcchain::api::MethodData contract_load_to_file_method_metadata{ "contract_load_to_file", nullptr,
                    /* description */ "save contract to file",
                    /* returns */ "contract_entry_printable",
                    /* params: */{
                        {"contract", "string", cdcchain::api::required_positional, fc::ovariant()},
                        {"file", "filename", cdcchain::api::required_positional, fc::ovariant()}
                          },
                    /* prerequisites */ (cdcchain::api::MethodPrerequisites) 0,
                    /* detailed description */ "save contract to file\n\nParameters:\n  contract (string, required): contract name or contract address need to be saved\n  file (filename, required): the file name with full path\n\nReturns:\n  contract_entry_printable\n",
                    /* aliases */ {}, false};
                store_method_metadata(contract_load_to_file_method_metadata);
            }

            {
                // register method get_result_trx_id
                cdcchain::api::MethodData get_result_trx_id_method_metadata{ "get_result_trx_id", nullptr,
                    /* description */ "get result tranraction id according to request trx id",
                    /* returns */ "transaction_id",
                    /* params: */{
                        {"request_id", "transaction_id", cdcchain::api::required_positional, fc::ovariant()}
                          },
                    /* prerequisites */ (cdcchain::api::MethodPrerequisites) 0,
                    /* detailed description */ "get result tranraction id according to request trx id\n\nParameters:\n  request_id (transaction_id, required): transaction id  of request\n\nReturns:\n  transaction_id\n",
                    /* aliases */ {}, false};
                store_method_metadata(get_result_trx_id_method_metadata);
            }

            {
                // register method get_request_trx_id
                cdcchain::api::MethodData get_request_trx_id_method_metadata{ "get_request_trx_id", nullptr,
                    /* description */ "get request tranraction id according to result trx id",
                    /* returns */ "transaction_id",
                    /* params: */{
                        {"request_id", "transaction_id", cdcchain::api::required_positional, fc::ovariant()}
                          },
                    /* prerequisites */ (cdcchain::api::MethodPrerequisites) 0,
                    /* detailed description */ "get request tranraction id according to result trx id\n\nParameters:\n  request_id (transaction_id, required): transaction id  of result\n\nReturns:\n  transaction_id\n",
                    /* aliases */ {}, false};
                store_method_metadata(get_request_trx_id_method_metadata);
            }

            {
                // register method simulator_open
                cdcchain::api::MethodData simulator_open_method_metadata{ "simulator_open", nullptr,
                    /* description */ "open simulator, let the state in simulator related state",
                    /* returns */ "void",
                    /* params: */{                    },
                    /* prerequisites */ (cdcchain::api::MethodPrerequisites) 4,
                    /* detailed description */ "open simulator, let the state in simulator related state\n\nParameters:\n  (none)\n\nReturns:\n  void\n",
                    /* aliases */ {}, false};
                store_method_metadata(simulator_open_method_metadata);
            }

            {
                // register method simulator_close
                cdcchain::api::MethodData simulator_close_method_metadata{ "simulator_close", nullptr,
                    /* description */ "close simulator, clear simulator related state",
                    /* returns */ "void",
                    /* params: */{                    },
                    /* prerequisites */ (cdcchain::api::MethodPrerequisites) 4,
                    /* detailed description */ "close simulator, clear simulator related state\n\nParameters:\n  (none)\n\nReturns:\n  void\n",
                    /* aliases */ {}, false};
                store_method_metadata(simulator_close_method_metadata);
            }

            {
                // register method simulator_contract_register
                cdcchain::api::MethodData simulator_contract_register_method_metadata{ "simulator_contract_register", nullptr,
                    /* description */ "in simulator state: register a temporary contract",
                    /* returns */ "string",
                    /* params: */{
                        {"owner", "string", cdcchain::api::required_positional, fc::ovariant()},
                        {"codefile", "filename", cdcchain::api::required_positional, fc::ovariant()},
                        {"asset_symbol", "string", cdcchain::api::required_positional, fc::ovariant()},
                        {"initLimit", "optional_double", cdcchain::api::required_positional, fc::ovariant()}
                          },
                    /* prerequisites */ (cdcchain::api::MethodPrerequisites) 16,
                    /* detailed description */ "in simulator state: register a temporary contract\n\nParameters:\n  owner (string, required): contract register owner address\n  codefile (filename, required): contract bytesfile name\n  asset_symbol (string, required): asset symbol name\n  initLimit (optional_double, required): the limit of asset amount used to init contract \n\nReturns:\n  string\n",
                    /* aliases */ {}, false};
                store_method_metadata(simulator_contract_register_method_metadata);
            }

            {
                // register method simulator_contract_call
                cdcchain::api::MethodData simulator_contract_call_method_metadata{ "simulator_contract_call", nullptr,
                    /* description */ "in simulator state: call contract by contract name or contract address",
                    /* returns */ "transaction_entry",
                    /* params: */{
                        {"contract", "string", cdcchain::api::required_positional, fc::ovariant()},
                        {"caller_name", "string", cdcchain::api::required_positional, fc::ovariant()},
                        {"function_name", "string", cdcchain::api::required_positional, fc::ovariant()},
                        {"params", "string", cdcchain::api::required_positional, fc::ovariant()},
                        {"cost_asset", "string", cdcchain::api::required_positional, fc::ovariant()},
                        {"callLimit", "optional_double", cdcchain::api::required_positional, fc::ovariant()}
                          },
                    /* prerequisites */ (cdcchain::api::MethodPrerequisites) 16,
                    /* detailed description */ "in simulator state: call contract by contract name or contract address\n\nParameters:\n  contract (string, required): contract name or contract address need to be called\n  caller_name (string, required): destroyer name\n  function_name (string, required): function in contract \n  params (string, required): parameters which would be passed to function\n  cost_asset (string, required): symbol of asset used to call\n  callLimit (optional_double, required): the limit of asset amount used to call contract \n\nReturns:\n  transaction_entry\n",
                    /* aliases */ {}, false};
                store_method_metadata(simulator_contract_call_method_metadata);
            }

            {
                // register method simulator_contract_upgrade
                cdcchain::api::MethodData simulator_contract_upgrade_method_metadata{ "simulator_contract_upgrade", nullptr,
                    /* description */ "in simulator state: upgrade temporary contract to permanent contract",
                    /* returns */ "transaction_entry",
                    /* params: */{
                        {"contract_address", "string", cdcchain::api::required_positional, fc::ovariant()},
                        {"upgrader_name", "string", cdcchain::api::required_positional, fc::ovariant()},
                        {"new_contract_name", "string", cdcchain::api::required_positional, fc::ovariant()},
                        {"new_contract_desc", "information", cdcchain::api::required_positional, fc::ovariant()},
                        {"asset_symbol", "string", cdcchain::api::required_positional, fc::ovariant()},
                        {"exec_limit", "optional_double", cdcchain::api::required_positional, fc::ovariant()}
                          },
                    /* prerequisites */ (cdcchain::api::MethodPrerequisites) 16,
                    /* detailed description */ "in simulator state: upgrade temporary contract to permanent contract\n\nParameters:\n  contract_address (string, required): contract address need to upgrade\n  upgrader_name (string, required): upgrader name\n  new_contract_name (string, required): permanent contract name\n  new_contract_desc (information, required): permanent contract description\n  asset_symbol (string, required): symbol of asset used to destroy\n  exec_limit (optional_double, required): the limit of asset amount used to destroy contract \n\nReturns:\n  transaction_entry\n",
                    /* aliases */ {}, false};
                store_method_metadata(simulator_contract_upgrade_method_metadata);
            }

            {
                // register method simulator_contract_upgrade_testing
                cdcchain::api::MethodData simulator_contract_upgrade_testing_method_metadata{ "simulator_contract_upgrade_testing", nullptr,
                    /* description */ "in simulator state: upgrade temporary contract to permanent contract",
                    /* returns */ "asset_array",
                    /* params: */{
                        {"contract_address", "string", cdcchain::api::required_positional, fc::ovariant()},
                        {"upgrader_name", "string", cdcchain::api::required_positional, fc::ovariant()},
                        {"new_contract_name", "string", cdcchain::api::required_positional, fc::ovariant()},
                        {"new_contract_desc", "information", cdcchain::api::required_positional, fc::ovariant()}
                          },
                    /* prerequisites */ (cdcchain::api::MethodPrerequisites) 16,
                    /* detailed description */ "in simulator state: upgrade temporary contract to permanent contract\n\nParameters:\n  contract_address (string, required): contract address need to upgrade\n  upgrader_name (string, required): upgrader name\n  new_contract_name (string, required): permanent contract name\n  new_contract_desc (information, required): permanent contract description\n\nReturns:\n  asset_array\n",
                    /* aliases */ {}, false};
                store_method_metadata(simulator_contract_upgrade_testing_method_metadata);
            }

            {
                // register method simulator_contract_destroy
                cdcchain::api::MethodData simulator_contract_destroy_method_metadata{ "simulator_contract_destroy", nullptr,
                    /* description */ "in simulator state: destroy temporary contract",
                    /* returns */ "transaction_entry",
                    /* params: */{
                        {"contract_address", "string", cdcchain::api::required_positional, fc::ovariant()},
                        {"destroyer_name", "string", cdcchain::api::required_positional, fc::ovariant()},
                        {"asset_symbol", "string", cdcchain::api::required_positional, fc::ovariant()},
                        {"exec_limit", "optional_double", cdcchain::api::required_positional, fc::ovariant()}
                          },
                    /* prerequisites */ (cdcchain::api::MethodPrerequisites) 16,
                    /* detailed description */ "in simulator state: destroy temporary contract\n\nParameters:\n  contract_address (string, required): contract address need to destroy\n  destroyer_name (string, required): destroyer name\n  asset_symbol (string, required): symbol of asset used to destroy\n  exec_limit (optional_double, required): the limit of asset amount used to destroy contract \n\nReturns:\n  transaction_entry\n",
                    /* aliases */ {}, false};
                store_method_metadata(simulator_contract_destroy_method_metadata);
            }

            {
                // register method simulator_contract_destroy_testing
                cdcchain::api::MethodData simulator_contract_destroy_testing_method_metadata{ "simulator_contract_destroy_testing", nullptr,
                    /* description */ "in simulator state: test destroy temporary contract",
                    /* returns */ "asset_array",
                    /* params: */{
                        {"contract_address", "string", cdcchain::api::required_positional, fc::ovariant()},
                        {"destroyer_name", "string", cdcchain::api::required_positional, fc::ovariant()}
                          },
                    /* prerequisites */ (cdcchain::api::MethodPrerequisites) 16,
                    /* detailed description */ "in simulator state: test destroy temporary contract\n\nParameters:\n  contract_address (string, required): contract address need to destroy\n  destroyer_name (string, required): destroyer name\n\nReturns:\n  asset_array\n",
                    /* aliases */ {}, false};
                store_method_metadata(simulator_contract_destroy_testing_method_metadata);
            }

            {
                // register method simulator_contract_get_info
                cdcchain::api::MethodData simulator_contract_get_info_method_metadata{ "simulator_contract_get_info", nullptr,
                    /* description */ "in simulator state: get contract entry by contract name or contract address",
                    /* returns */ "contract_entry_printable",
                    /* params: */{
                        {"contract", "string", cdcchain::api::required_positional, fc::ovariant()}
                          },
                    /* prerequisites */ (cdcchain::api::MethodPrerequisites) 16,
                    /* detailed description */ "in simulator state: get contract entry by contract name or contract address\n\nParameters:\n  contract (string, required): contract name or contract address\n\nReturns:\n  contract_entry_printable\n",
                    /* aliases */ {}, false};
                store_method_metadata(simulator_contract_get_info_method_metadata);
            }

            {
                // register method simulator_contract_get_balance
                cdcchain::api::MethodData simulator_contract_get_balance_method_metadata{ "simulator_contract_get_balance", nullptr,
                    /* description */ "in simulator state: get contract balance entry and margin balance entry by contract name or contract address",
                    /* returns */ "balance_entry_list",
                    /* params: */{
                        {"contract", "string", cdcchain::api::required_positional, fc::ovariant()}
                          },
                    /* prerequisites */ (cdcchain::api::MethodPrerequisites) 16,
                    /* detailed description */ "in simulator state: get contract balance entry and margin balance entry by contract name or contract address\n\nParameters:\n  contract (string, required): contract name or contract address\n\nReturns:\n  balance_entry_list\n",
                    /* aliases */ {}, false};
                store_method_metadata(simulator_contract_get_balance_method_metadata);
            }

            {
                // register method simulator_transfer_to_contract
                cdcchain::api::MethodData simulator_transfer_to_contract_method_metadata{ "simulator_transfer_to_contract", nullptr,
                    /* description */ "in simulator state: transfer to contract",
                    /* returns */ "transaction_entry",
                    /* params: */{
                        {"amount_to_transfer", "real_amount", cdcchain::api::required_positional, fc::ovariant()},
                        {"asset_symbol", "asset_symbol", cdcchain::api::required_positional, fc::ovariant()},
                        {"from_account_name", "account_name", cdcchain::api::required_positional, fc::ovariant()},
                        {"to_contract", "string", cdcchain::api::required_positional, fc::ovariant()},
                        {"amount_for_exec", "real_amount", cdcchain::api::required_positional, fc::ovariant()}
                          },
                    /* prerequisites */ (cdcchain::api::MethodPrerequisites) 16,
                    /* detailed description */ "in simulator state: transfer to contract\n\nParameters:\n  amount_to_transfer (real_amount, required): the amount of shares to transfer\n  asset_symbol (asset_symbol, required): the asset to transfer\n  from_account_name (account_name, required): the source account to draw the shares from\n  to_contract (string, required): the contract name or contract address to transfer to\n  amount_for_exec (real_amount, required): the amount of shares to exec\n\nReturns:\n  transaction_entry\n",
                    /* aliases */ {}, false};
                store_method_metadata(simulator_transfer_to_contract_method_metadata);
            }

            {
                // register method simulator_account_balance
                cdcchain::api::MethodData simulator_account_balance_method_metadata{ "simulator_account_balance", nullptr,
                    /* description */ "in simulator state: lookup balance of account",
                    /* returns */ "account_balance_summary_type",
                    /* params: */{
                        {"account_name", "account_name", cdcchain::api::optional_positional, fc::variant(fc::json::from_string("\"\""))}
                          },
                    /* prerequisites */ (cdcchain::api::MethodPrerequisites) 16,
                    /* detailed description */ "in simulator state: lookup balance of account\n\nParameters:\n  account_name (account_name, optional, defaults to \"\"): the account to lookup balance\n\nReturns:\n  account_balance_summary_type\n",
                    /* aliases */ {}, false};
                store_method_metadata(simulator_account_balance_method_metadata);
            }

            {
                // register method simulator_contract_compile
                cdcchain::api::MethodData simulator_contract_compile_method_metadata{ "simulator_contract_compile", nullptr,
                    /* description */ "in simulator compile contract source code to byte code, and store to binary file",
                    /* returns */ "filename",
                    /* params: */{
                        {"filename", "filename", cdcchain::api::required_positional, fc::ovariant()}
                          },
                    /* prerequisites */ (cdcchain::api::MethodPrerequisites) 16,
                    /* detailed description */ "in simulator compile contract source code to byte code, and store to binary file\n\nParameters:\n  filename (filename, required): contract source file name\n\nReturns:\n  filename\n",
                    /* aliases */ {}, true};
                store_method_metadata(simulator_contract_compile_method_metadata);
            }

            {
                // register method simulator_contract_load_to_file
                cdcchain::api::MethodData simulator_contract_load_to_file_method_metadata{ "simulator_contract_load_to_file", nullptr,
                    /* description */ "in simulator save contract to a gpc file",
                    /* returns */ "contract_entry_printable",
                    /* params: */{
                        {"contract", "string", cdcchain::api::required_positional, fc::ovariant()},
                        {"file", "filename", cdcchain::api::required_positional, fc::ovariant()}
                          },
                    /* prerequisites */ (cdcchain::api::MethodPrerequisites) 16,
                    /* detailed description */ "in simulator save contract to a gpc file\n\nParameters:\n  contract (string, required): contract name or contract address need to be saved\n  file (filename, required): the file name with full path\n\nReturns:\n  contract_entry_printable\n",
                    /* aliases */ {}, true};
                store_method_metadata(simulator_contract_load_to_file_method_metadata);
            }

            {
                // register method simulator_contract_register_testing
                cdcchain::api::MethodData simulator_contract_register_testing_method_metadata{ "simulator_contract_register_testing", nullptr,
                    /* description */ "in simulator register a temporary contract on local endpoint, and do not spread it on P2P network",
                    /* returns */ "asset_array",
                    /* params: */{
                        {"owner", "string", cdcchain::api::required_positional, fc::ovariant()},
                        {"codefile", "filename", cdcchain::api::required_positional, fc::ovariant()}
                          },
                    /* prerequisites */ (cdcchain::api::MethodPrerequisites) 16,
                    /* detailed description */ "in simulator register a temporary contract on local endpoint, and do not spread it on P2P network\n\nParameters:\n  owner (string, required): contract register owner address\n  codefile (filename, required): contract bytesfile name\n\nReturns:\n  asset_array\n",
                    /* aliases */ {}, false};
                store_method_metadata(simulator_contract_register_testing_method_metadata);
            }

            {
                // register method simulator_contract_call_testing
                cdcchain::api::MethodData simulator_contract_call_testing_method_metadata{ "simulator_contract_call_testing", nullptr,
                    /* description */ "in simulator call contract function by contract name or contract address on local endpoint, and do not spread it on P2P network",
                    /* returns */ "asset_array",
                    /* params: */{
                        {"contract", "string", cdcchain::api::required_positional, fc::ovariant()},
                        {"caller_name", "string", cdcchain::api::required_positional, fc::ovariant()},
                        {"function_name", "string", cdcchain::api::required_positional, fc::ovariant()},
                        {"params", "string", cdcchain::api::required_positional, fc::ovariant()}
                          },
                    /* prerequisites */ (cdcchain::api::MethodPrerequisites) 16,
                    /* detailed description */ "in simulator call contract function by contract name or contract address on local endpoint, and do not spread it on P2P network\n\nParameters:\n  contract (string, required): contract name or contract address need to be called\n  caller_name (string, required): caller name\n  function_name (string, required): function in contract \n  params (string, required): parameters which would be passed to function\n\nReturns:\n  asset_array\n",
                    /* aliases */ {}, false};
                store_method_metadata(simulator_contract_call_testing_method_metadata);
            }

            {
                // register method simulator_transfer_to_contract_testing
                cdcchain::api::MethodData simulator_transfer_to_contract_testing_method_metadata{ "simulator_transfer_to_contract_testing", nullptr,
                    /* description */ "in simulator Do a simple transfer to a contract (name or address) on local endpoint, and do not spread it on P2P network",
                    /* returns */ "asset_array",
                    /* params: */{
                        {"amount_to_transfer", "real_amount", cdcchain::api::required_positional, fc::ovariant()},
                        {"asset_symbol", "asset_symbol", cdcchain::api::required_positional, fc::ovariant()},
                        {"from_account_name", "account_name", cdcchain::api::required_positional, fc::ovariant()},
                        {"to_contract", "string", cdcchain::api::required_positional, fc::ovariant()}
                          },
                    /* prerequisites */ (cdcchain::api::MethodPrerequisites) 16,
                    /* detailed description */ "in simulator Do a simple transfer to a contract (name or address) on local endpoint, and do not spread it on P2P network\n\nParameters:\n  amount_to_transfer (real_amount, required): the amount of shares to transfer\n  asset_symbol (asset_symbol, required): the asset to transfer\n  from_account_name (account_name, required): the source account to draw the shares from\n  to_contract (string, required): the contract name or contract address to transfer to\n\nReturns:\n  asset_array\n",
                    /* aliases */ {}, false};
                store_method_metadata(simulator_transfer_to_contract_testing_method_metadata);
            }

            {
                // register method simulator_list_my_addresses
                cdcchain::api::MethodData simulator_list_my_addresses_method_metadata{ "simulator_list_my_addresses", nullptr,
                    /* description */ "list the account info of the wallet",
                    /* returns */ "simulator_account_info_list",
                    /* params: */{
                        {"account_name", "string", cdcchain::api::optional_positional, fc::variant(fc::json::from_string("\"\""))}
                          },
                    /* prerequisites */ (cdcchain::api::MethodPrerequisites) 16,
                    /* detailed description */ "list the account info of the wallet\n\nParameters:\n  account_name (string, optional, defaults to \"\"): the account in wallet\n\nReturns:\n  simulator_account_info_list\n",
                    /* aliases */ {}, false};
                store_method_metadata(simulator_list_my_addresses_method_metadata);
            }

            {
                // register method get_contract_registered_in_transaction
                cdcchain::api::MethodData get_contract_registered_in_transaction_method_metadata{ "get_contract_registered_in_transaction", nullptr,
                    /* description */ "get id of contract registered in specific transaction",
                    /* returns */ "string",
                    /* params: */{
                        {"trx_id", "transaction_id", cdcchain::api::required_positional, fc::ovariant()}
                          },
                    /* prerequisites */ (cdcchain::api::MethodPrerequisites) 0,
                    /* detailed description */ "get id of contract registered in specific transaction\n\nParameters:\n  trx_id (transaction_id, required): specific contract id\n\nReturns:\n  string\n",
                    /* aliases */ {}, false};
                store_method_metadata(get_contract_registered_in_transaction_method_metadata);
            }

            {
                // register method get_transaction_id_contract_registered
                cdcchain::api::MethodData get_transaction_id_contract_registered_method_metadata{ "get_transaction_id_contract_registered", nullptr,
                    /* description */ "get id of transaction that specific contract registered in ",
                    /* returns */ "transaction_id",
                    /* params: */{
                        {"contract_id", "string", cdcchain::api::required_positional, fc::ovariant()}
                          },
                    /* prerequisites */ (cdcchain::api::MethodPrerequisites) 0,
                    /* detailed description */ "get id of transaction that specific contract registered in \n\nParameters:\n  contract_id (string, required): specific contract id\n\nReturns:\n  transaction_id\n",
                    /* aliases */ {}, false};
                store_method_metadata(get_transaction_id_contract_registered_method_metadata);
            }

            {
                // register method contract_get_info_from_gpc_file
                cdcchain::api::MethodData contract_get_info_from_gpc_file_method_metadata{ "contract_get_info_from_gpc_file", nullptr,
                    /* description */ "get contract info from gpc file",
                    /* returns */ "code_printable",
                    /* params: */{
                        {"file", "filename", cdcchain::api::required_positional, fc::ovariant()}
                          },
                    /* prerequisites */ (cdcchain::api::MethodPrerequisites) 0,
                    /* detailed description */ "get contract info from gpc file\n\nParameters:\n  file (filename, required): contract gpc file name\n\nReturns:\n  code_printable\n",
                    /* aliases */ {}, true};
                store_method_metadata(contract_get_info_from_gpc_file_method_metadata);
            }

            {
                // register method script_compile
                cdcchain::api::MethodData script_compile_method_metadata{ "script_compile", nullptr,
                    /* description */ "compile script source code to byte code, and store to binary file",
                    /* returns */ "filename",
                    /* params: */{
                        {"filename", "filename", cdcchain::api::required_positional, fc::ovariant()}
                          },
                    /* prerequisites */ (cdcchain::api::MethodPrerequisites) 0,
                    /* detailed description */ "compile script source code to byte code, and store to binary file\n\nParameters:\n  filename (filename, required): script source file name\n\nReturns:\n  filename\n",
                    /* aliases */ {}, true};
                store_method_metadata(script_compile_method_metadata);
            }

            {
                // register method script_add
                cdcchain::api::MethodData script_add_method_metadata{ "script_add", nullptr,
                    /* description */ "Add a compiled script to database",
                    /* returns */ "string",
                    /* params: */{
                        {"filename", "filename", cdcchain::api::required_positional, fc::ovariant()},
                        {"description", "information", cdcchain::api::required_positional, fc::ovariant()}
                          },
                    /* prerequisites */ (cdcchain::api::MethodPrerequisites) 4,
                    /* detailed description */ "Add a compiled script to database\n\nParameters:\n  filename (filename, required): filename of the specified script\n  description (information, required): description of the script\n\nReturns:\n  string\n",
                    /* aliases */ {}, false};
                store_method_metadata(script_add_method_metadata);
            }

            {
                // register method script_remove
                cdcchain::api::MethodData script_remove_method_metadata{ "script_remove", nullptr,
                    /* description */ "Remove a compiled script form database",
                    /* returns */ "void",
                    /* params: */{
                        {"scriptid", "string", cdcchain::api::required_positional, fc::ovariant()}
                          },
                    /* prerequisites */ (cdcchain::api::MethodPrerequisites) 4,
                    /* detailed description */ "Remove a compiled script form database\n\nParameters:\n  scriptid (string, required): scriptid of the specified script\n\nReturns:\n  void\n",
                    /* aliases */ {}, false};
                store_method_metadata(script_remove_method_metadata);
            }

            {
                // register method script_get_info
                cdcchain::api::MethodData script_get_info_method_metadata{ "script_get_info", nullptr,
                    /* description */ "Get info of a script specified by script_id ",
                    /* returns */ "scriptentry_printable",
                    /* params: */{
                        {"scriptid", "string", cdcchain::api::required_positional, fc::ovariant()}
                          },
                    /* prerequisites */ (cdcchain::api::MethodPrerequisites) 4,
                    /* detailed description */ "Get info of a script specified by script_id \n\nParameters:\n  scriptid (string, required): scriptid of the specified script\n\nReturns:\n  scriptentry_printable\n",
                    /* aliases */ {}, false};
                store_method_metadata(script_get_info_method_metadata);
            }

            {
                // register method scripts_list
                cdcchain::api::MethodData scripts_list_method_metadata{ "scripts_list", nullptr,
                    /* description */ "List all scripts in database ",
                    /* returns */ "scriptentry_printable_list",
                    /* params: */{                    },
                    /* prerequisites */ (cdcchain::api::MethodPrerequisites) 4,
                    /* detailed description */ "List all scripts in database \n\nParameters:\n  (none)\n\nReturns:\n  scriptentry_printable_list\n",
                    /* aliases */ {}, false};
                store_method_metadata(scripts_list_method_metadata);
            }

            {
                // register method script_disable
                cdcchain::api::MethodData script_disable_method_metadata{ "script_disable", nullptr,
                    /* description */ "disable a compiled script from database",
                    /* returns */ "void",
                    /* params: */{
                        {"scriptid", "string", cdcchain::api::required_positional, fc::ovariant()}
                          },
                    /* prerequisites */ (cdcchain::api::MethodPrerequisites) 4,
                    /* detailed description */ "disable a compiled script from database\n\nParameters:\n  scriptid (string, required): scriptid of the specified script\n\nReturns:\n  void\n",
                    /* aliases */ {}, false};
                store_method_metadata(script_disable_method_metadata);
            }

            {
                // register method script_enable
                cdcchain::api::MethodData script_enable_method_metadata{ "script_enable", nullptr,
                    /* description */ "enable a compiled script from database",
                    /* returns */ "void",
                    /* params: */{
                        {"scriptid", "string", cdcchain::api::required_positional, fc::ovariant()}
                          },
                    /* prerequisites */ (cdcchain::api::MethodPrerequisites) 4,
                    /* detailed description */ "enable a compiled script from database\n\nParameters:\n  scriptid (string, required): scriptid of the specified script\n\nReturns:\n  void\n",
                    /* aliases */ {}, false};
                store_method_metadata(script_enable_method_metadata);
            }

            {
                // register method script_import_to_db
                cdcchain::api::MethodData script_import_to_db_method_metadata{ "script_import_to_db", nullptr,
                    /* description */ "import scripts from a database directory",
                    /* returns */ "void",
                    /* params: */{
                        {"dbfile", "filename", cdcchain::api::required_positional, fc::ovariant()}
                          },
                    /* prerequisites */ (cdcchain::api::MethodPrerequisites) 4,
                    /* detailed description */ "import scripts from a database directory\n\nParameters:\n  dbfile (filename, required): path of database for importing from\n\nReturns:\n  void\n",
                    /* aliases */ {}, false};
                store_method_metadata(script_import_to_db_method_metadata);
            }

            {
                // register method script_export_from_db
                cdcchain::api::MethodData script_export_from_db_method_metadata{ "script_export_from_db", nullptr,
                    /* description */ "export scripts to a database directory",
                    /* returns */ "void",
                    /* params: */{
                        {"dbfile", "filename", cdcchain::api::required_positional, fc::ovariant()}
                          },
                    /* prerequisites */ (cdcchain::api::MethodPrerequisites) 4,
                    /* detailed description */ "export scripts to a database directory\n\nParameters:\n  dbfile (filename, required): path of database for exporting to\n\nReturns:\n  void\n",
                    /* aliases */ {}, false};
                store_method_metadata(script_export_from_db_method_metadata);
            }

            {
                // register method script_get_events_bound
                cdcchain::api::MethodData script_get_events_bound_method_metadata{ "script_get_events_bound", nullptr,
                    /* description */ "get contract id and event which binded with specific script",
                    /* returns */ "string_array",
                    /* params: */{
                        {"script_id", "string", cdcchain::api::required_positional, fc::ovariant()}
                          },
                    /* prerequisites */ (cdcchain::api::MethodPrerequisites) 4,
                    /* detailed description */ "get contract id and event which binded with specific script\n\nParameters:\n  script_id (string, required): id of specific script\n\nReturns:\n  string_array\n",
                    /* aliases */ {}, false};
                store_method_metadata(script_get_events_bound_method_metadata);
            }

            {
                // register method script_list_event_handler
                cdcchain::api::MethodData script_list_event_handler_method_metadata{ "script_list_event_handler", nullptr,
                    /* description */ "list all event handlers related with the specified contract id and event type",
                    /* returns */ "scriptid_list",
                    /* params: */{
                        {"contract_id_str", "string", cdcchain::api::required_positional, fc::ovariant()},
                        {"event_type", "string", cdcchain::api::required_positional, fc::ovariant()}
                          },
                    /* prerequisites */ (cdcchain::api::MethodPrerequisites) 4,
                    /* detailed description */ "list all event handlers related with the specified contract id and event type\n\nParameters:\n  contract_id_str (string, required): id of the binding contract at blockchain\n  event_type (string, required): type of the binding event at blockchain\n\nReturns:\n  scriptid_list\n",
                    /* aliases */ {}, false};
                store_method_metadata(script_list_event_handler_method_metadata);
            }

            {
                // register method script_add_event_handler
                cdcchain::api::MethodData script_add_event_handler_method_metadata{ "script_add_event_handler", nullptr,
                    /* description */ "set a new relation with a script to the specified contract id and event type",
                    /* returns */ "void",
                    /* params: */{
                        {"contract_id_str", "string", cdcchain::api::required_positional, fc::ovariant()},
                        {"event_type", "string", cdcchain::api::required_positional, fc::ovariant()},
                        {"script_id", "string", cdcchain::api::required_positional, fc::ovariant()},
                        {"index", "uint32_t", cdcchain::api::required_positional, fc::ovariant()}
                          },
                    /* prerequisites */ (cdcchain::api::MethodPrerequisites) 4,
                    /* detailed description */ "set a new relation with a script to the specified contract id and event type\n\nParameters:\n  contract_id_str (string, required): id of contract at blockchain want to bind\n  event_type (string, required): type of event at blockchain want to bind\n  script_id (string, required): id of local script want to bind with\n  index (uint32_t, required): the position of script vector want to insert\n\nReturns:\n  void\n",
                    /* aliases */ {}, false};
                store_method_metadata(script_add_event_handler_method_metadata);
            }

            {
                // register method script_delete_event_handler
                cdcchain::api::MethodData script_delete_event_handler_method_metadata{ "script_delete_event_handler", nullptr,
                    /* description */ "drop the relation with a script to the specified contract id and event type",
                    /* returns */ "void",
                    /* params: */{
                        {"contract_id_str", "string", cdcchain::api::required_positional, fc::ovariant()},
                        {"event_type", "string", cdcchain::api::required_positional, fc::ovariant()},
                        {"script_id", "string", cdcchain::api::required_positional, fc::ovariant()}
                          },
                    /* prerequisites */ (cdcchain::api::MethodPrerequisites) 4,
                    /* detailed description */ "drop the relation with a script to the specified contract id and event type\n\nParameters:\n  contract_id_str (string, required): id of contract at blockchain want to delete\n  event_type (string, required): type of event at blockchain want to delete\n  script_id (string, required): id of local script want to delete with\n\nReturns:\n  void\n",
                    /* aliases */ {}, false};
                store_method_metadata(script_delete_event_handler_method_metadata);
            }

            {
                // register method proposal_apply_for_privilege_admin
                cdcchain::api::MethodData proposal_apply_for_privilege_admin_method_metadata{ "proposal_apply_for_privilege_admin", nullptr,
                    /* description */ "create a proposal to apply for privilege admin",
                    /* returns */ "proposal_id_type",
                    /* params: */{
                        {"caller_name", "string", cdcchain::api::required_positional, fc::ovariant()},
                        {"candidate_address", "string", cdcchain::api::required_positional, fc::ovariant()},
                        {"need_vote_count", "uint32_t", cdcchain::api::required_positional, fc::ovariant()},
                        {"start_time", "uint32_t", cdcchain::api::required_positional, fc::ovariant()},
                        {"expected_end_time", "uint32_t", cdcchain::api::required_positional, fc::ovariant()}
                          },
                    /* prerequisites */ (cdcchain::api::MethodPrerequisites) 4,
                    /* detailed description */ "create a proposal to apply for privilege admin\n\nParameters:\n  caller_name (string, required): proposal from account name\n  candidate_address (string, required): candidate need to proposal for privilege admin\n  need_vote_count (uint32_t, required): need vote count\n  start_time (uint32_t, required): proposal start timestamp\n  expected_end_time (uint32_t, required): proposal expected end timestamp\n\nReturns:\n  proposal_id_type\n",
                    /* aliases */ {}, true};
                store_method_metadata(proposal_apply_for_privilege_admin_method_metadata);
            }

            {
                // register method proposal_revoke_privilege_admin
                cdcchain::api::MethodData proposal_revoke_privilege_admin_method_metadata{ "proposal_revoke_privilege_admin", nullptr,
                    /* description */ "create a proposal to revoke privilege admin",
                    /* returns */ "proposal_id_type",
                    /* params: */{
                        {"caller_name", "string", cdcchain::api::required_positional, fc::ovariant()},
                        {"privilege_admin", "string", cdcchain::api::required_positional, fc::ovariant()},
                        {"need_vote_count", "uint32_t", cdcchain::api::required_positional, fc::ovariant()},
                        {"start_time", "uint32_t", cdcchain::api::required_positional, fc::ovariant()},
                        {"expected_end_time", "uint32_t", cdcchain::api::required_positional, fc::ovariant()}
                          },
                    /* prerequisites */ (cdcchain::api::MethodPrerequisites) 4,
                    /* detailed description */ "create a proposal to revoke privilege admin\n\nParameters:\n  caller_name (string, required): proposal from account name\n  privilege_admin (string, required): privilege admin address need to revoke\n  need_vote_count (uint32_t, required): need vote count\n  start_time (uint32_t, required): proposal start timestamp\n  expected_end_time (uint32_t, required): proposal expected end timestamp\n\nReturns:\n  proposal_id_type\n",
                    /* aliases */ {}, true};
                store_method_metadata(proposal_revoke_privilege_admin_method_metadata);
            }

            {
                // register method proposal_approve
                cdcchain::api::MethodData proposal_approve_method_metadata{ "proposal_approve", nullptr,
                    /* description */ "to approve a proposal",
                    /* returns */ "transaction_entry",
                    /* params: */{
                        {"caller_name", "string", cdcchain::api::required_positional, fc::ovariant()},
                        {"proposal_id", "string", cdcchain::api::required_positional, fc::ovariant()}
                          },
                    /* prerequisites */ (cdcchain::api::MethodPrerequisites) 4,
                    /* detailed description */ "to approve a proposal\n\nParameters:\n  caller_name (string, required): approver account name\n  proposal_id (string, required): proposal id to approve\n\nReturns:\n  transaction_entry\n",
                    /* aliases */ {}, true};
                store_method_metadata(proposal_approve_method_metadata);
            }

            {
                // register method proposal_get_info
                cdcchain::api::MethodData proposal_get_info_method_metadata{ "proposal_get_info", nullptr,
                    /* description */ "get proposal info",
                    /* returns */ "proposal_entry",
                    /* params: */{
                        {"proposal_id", "string", cdcchain::api::required_positional, fc::ovariant()}
                          },
                    /* prerequisites */ (cdcchain::api::MethodPrerequisites) 0,
                    /* detailed description */ "get proposal info\n\nParameters:\n  proposal_id (string, required): proposal id\n\nReturns:\n  proposal_entry\n",
                    /* aliases */ {}, true};
                store_method_metadata(proposal_get_info_method_metadata);
            }

            {
                // register method appoint_general_admin
                cdcchain::api::MethodData appoint_general_admin_method_metadata{ "appoint_general_admin", nullptr,
                    /* description */ "privilege admin appoint a general admin",
                    /* returns */ "transaction_entry",
                    /* params: */{
                        {"caller_name", "string", cdcchain::api::required_positional, fc::ovariant()},
                        {"candidate_address", "string", cdcchain::api::required_positional, fc::ovariant()}
                          },
                    /* prerequisites */ (cdcchain::api::MethodPrerequisites) 4,
                    /* detailed description */ "privilege admin appoint a general admin\n\nParameters:\n  caller_name (string, required): privilege admin account name\n  candidate_address (string, required): appoint candidate for general admin\n\nReturns:\n  transaction_entry\n",
                    /* aliases */ {}, true};
                store_method_metadata(appoint_general_admin_method_metadata);
            }

            {
                // register method revoke_general_admin
                cdcchain::api::MethodData revoke_general_admin_method_metadata{ "revoke_general_admin", nullptr,
                    /* description */ "privilege admin revoke a general admin",
                    /* returns */ "transaction_entry",
                    /* params: */{
                        {"caller_name", "string", cdcchain::api::required_positional, fc::ovariant()},
                        {"general_admin_address", "string", cdcchain::api::required_positional, fc::ovariant()}
                          },
                    /* prerequisites */ (cdcchain::api::MethodPrerequisites) 4,
                    /* detailed description */ "privilege admin revoke a general admin\n\nParameters:\n  caller_name (string, required): privilege admin account name\n  general_admin_address (string, required): general admin need to revoke\n\nReturns:\n  transaction_entry\n",
                    /* aliases */ {}, true};
                store_method_metadata(revoke_general_admin_method_metadata);
            }

            {
                // register method get_all_privilege_admin
                cdcchain::api::MethodData get_all_privilege_admin_method_metadata{ "get_all_privilege_admin", nullptr,
                    /* description */ "get all privilege admin",
                    /* returns */ "address_list",
                    /* params: */{                    },
                    /* prerequisites */ (cdcchain::api::MethodPrerequisites) 0,
                    /* detailed description */ "get all privilege admin\n\nParameters:\n  (none)\n\nReturns:\n  address_list\n",
                    /* aliases */ {}, true};
                store_method_metadata(get_all_privilege_admin_method_metadata);
            }

            {
                // register method get_all_general_admin
                cdcchain::api::MethodData get_all_general_admin_method_metadata{ "get_all_general_admin", nullptr,
                    /* description */ "get all general admin",
                    /* returns */ "address_list",
                    /* params: */{                    },
                    /* prerequisites */ (cdcchain::api::MethodPrerequisites) 0,
                    /* detailed description */ "get all general admin\n\nParameters:\n  (none)\n\nReturns:\n  address_list\n",
                    /* aliases */ {}, true};
                store_method_metadata(get_all_general_admin_method_metadata);
            }

        }

        fc::variant CommonApiRpcServer::direct_invoke_positional_method(const std::string& method_name, const fc::variants& parameters)
        {
            if (method_name == "blockchain_get_info")
                return blockchain_get_info_positional(nullptr, parameters);
            if (method_name == "blockchain_generate_snapshot")
                return blockchain_generate_snapshot_positional(nullptr, parameters);
            if (method_name == "blockchain_get_cdc_account_balance_entry")
                return blockchain_get_cdc_account_balance_entry_positional(nullptr, parameters);
            if (method_name == "blockchain_generate_issuance_map")
                return blockchain_generate_issuance_map_positional(nullptr, parameters);
            if (method_name == "blockchain_calculate_supply")
                return blockchain_calculate_supply_positional(nullptr, parameters);
            if (method_name == "blockchain_is_synced")
                return blockchain_is_synced_positional(nullptr, parameters);
            if (method_name == "blockchain_get_block_count")
                return blockchain_get_block_count_positional(nullptr, parameters);
            if (method_name == "blockchain_get_security_state")
                return blockchain_get_security_state_positional(nullptr, parameters);
            if (method_name == "blockchain_list_accounts")
                return blockchain_list_accounts_positional(nullptr, parameters);
            if (method_name == "blockchain_list_recently_updated_accounts")
                return blockchain_list_recently_updated_accounts_positional(nullptr, parameters);
            if (method_name == "blockchain_list_recently_registered_accounts")
                return blockchain_list_recently_registered_accounts_positional(nullptr, parameters);
            if (method_name == "blockchain_list_assets")
                return blockchain_list_assets_positional(nullptr, parameters);
            if (method_name == "blockchain_list_pending_transactions")
                return blockchain_list_pending_transactions_positional(nullptr, parameters);
            if (method_name == "blockchain_get_transaction")
                return blockchain_get_transaction_positional(nullptr, parameters);
            if (method_name == "blockchain_get_pretty_transaction")
                return blockchain_get_pretty_transaction_positional(nullptr, parameters);
            if (method_name == "blockchain_get_pretty_contract_transaction")
                return blockchain_get_pretty_contract_transaction_positional(nullptr, parameters);
            if (method_name == "blockchain_get_block")
                return blockchain_get_block_positional(nullptr, parameters);
            if (method_name == "blockchain_get_block_transactions")
                return blockchain_get_block_transactions_positional(nullptr, parameters);
            if (method_name == "blockchain_get_account")
                return blockchain_get_account_positional(nullptr, parameters);
            if (method_name == "blockchain_get_slate")
                return blockchain_get_slate_positional(nullptr, parameters);
            if (method_name == "blockchain_get_balance")
                return blockchain_get_balance_positional(nullptr, parameters);
            if (method_name == "blockchain_list_balances")
                return blockchain_list_balances_positional(nullptr, parameters);
            if (method_name == "blockchain_list_address_balances")
                return blockchain_list_address_balances_positional(nullptr, parameters);
            if (method_name == "blockchain_list_address_transactions")
                return blockchain_list_address_transactions_positional(nullptr, parameters);
            if (method_name == "blockchain_get_account_public_balance")
                return blockchain_get_account_public_balance_positional(nullptr, parameters);
            if (method_name == "blockchain_list_key_balances")
                return blockchain_list_key_balances_positional(nullptr, parameters);
            if (method_name == "blockchain_get_asset")
                return blockchain_get_asset_positional(nullptr, parameters);
            if (method_name == "blockchain_list_active_delegates")
                return blockchain_list_active_delegates_positional(nullptr, parameters);
            if (method_name == "blockchain_list_delegates")
                return blockchain_list_delegates_positional(nullptr, parameters);
            if (method_name == "blockchain_list_blocks")
                return blockchain_list_blocks_positional(nullptr, parameters);
            if (method_name == "blockchain_list_missing_block_delegates")
                return blockchain_list_missing_block_delegates_positional(nullptr, parameters);
            if (method_name == "blockchain_export_fork_graph")
                return blockchain_export_fork_graph_positional(nullptr, parameters);
            if (method_name == "blockchain_list_forks")
                return blockchain_list_forks_positional(nullptr, parameters);
            if (method_name == "blockchain_get_delegate_slot_entrys")
                return blockchain_get_delegate_slot_entrys_positional(nullptr, parameters);
            if (method_name == "blockchain_get_block_signee")
                return blockchain_get_block_signee_positional(nullptr, parameters);
            if (method_name == "blockchain_unclaimed_genesis")
                return blockchain_unclaimed_genesis_positional(nullptr, parameters);
            if (method_name == "blockchain_verify_signature")
                return blockchain_verify_signature_positional(nullptr, parameters);
            if (method_name == "blockchain_dump_state")
                return blockchain_dump_state_positional(nullptr, parameters);
            if (method_name == "blockchain_broadcast_transaction")
                return blockchain_broadcast_transaction_positional(nullptr, parameters);
            if (method_name == "blockchain_btc_address_convert")
                return blockchain_btc_address_convert_positional(nullptr, parameters);
            if (method_name == "blockchain_get_transaction_rpc")
                return blockchain_get_transaction_rpc_positional(nullptr, parameters);
            if (method_name == "blockchain_set_node_vm_enabled")
                return blockchain_set_node_vm_enabled_positional(nullptr, parameters);
            if (method_name == "blockchain_get_node_vm_enabled")
                return blockchain_get_node_vm_enabled_positional(nullptr, parameters);
            if (method_name == "blockchain_get_all_contracts")
                return blockchain_get_all_contracts_positional(nullptr, parameters);
            if (method_name == "blockchain_get_forever_contracts")
                return blockchain_get_forever_contracts_positional(nullptr, parameters);
            if (method_name == "blockchain_list_pub_all_address")
                return blockchain_list_pub_all_address_positional(nullptr, parameters);
            if (method_name == "blockchain_list_contract_transaction_history")
                return blockchain_list_contract_transaction_history_positional(nullptr, parameters);
            if (method_name == "network_add_node")
                return network_add_node_positional(nullptr, parameters);
            if (method_name == "network_get_connection_count")
                return network_get_connection_count_positional(nullptr, parameters);
            if (method_name == "network_get_peer_info")
                return network_get_peer_info_positional(nullptr, parameters);
            if (method_name == "network_broadcast_transaction")
                return network_broadcast_transaction_positional(nullptr, parameters);
            if (method_name == "network_set_advanced_node_parameters")
                return network_set_advanced_node_parameters_positional(nullptr, parameters);
            if (method_name == "network_get_advanced_node_parameters")
                return network_get_advanced_node_parameters_positional(nullptr, parameters);
            if (method_name == "network_get_transaction_propagation_data")
                return network_get_transaction_propagation_data_positional(nullptr, parameters);
            if (method_name == "network_get_block_propagation_data")
                return network_get_block_propagation_data_positional(nullptr, parameters);
            if (method_name == "network_get_info")
                return network_get_info_positional(nullptr, parameters);
            if (method_name == "network_list_potential_peers")
                return network_list_potential_peers_positional(nullptr, parameters);
            if (method_name == "network_get_upnp_info")
                return network_get_upnp_info_positional(nullptr, parameters);
            if (method_name == "network_get_blocked_ips")
                return network_get_blocked_ips_positional(nullptr, parameters);
            if (method_name == "debug_get_client_name")
                return debug_get_client_name_positional(nullptr, parameters);
            if (method_name == "delegate_get_config")
                return delegate_get_config_positional(nullptr, parameters);
            if (method_name == "delegate_set_network_min_connection_count")
                return delegate_set_network_min_connection_count_positional(nullptr, parameters);
            if (method_name == "delegate_set_block_max_transaction_count")
                return delegate_set_block_max_transaction_count_positional(nullptr, parameters);
            if (method_name == "delegate_set_soft_max_imessage_length")
                return delegate_set_soft_max_imessage_length_positional(nullptr, parameters);
            if (method_name == "delegate_set_imessage_fee_coe")
                return delegate_set_imessage_fee_coe_positional(nullptr, parameters);
            if (method_name == "delegate_set_block_max_size")
                return delegate_set_block_max_size_positional(nullptr, parameters);
            if (method_name == "delegate_set_transaction_max_size")
                return delegate_set_transaction_max_size_positional(nullptr, parameters);
            if (method_name == "delegate_set_transaction_canonical_signatures_required")
                return delegate_set_transaction_canonical_signatures_required_positional(nullptr, parameters);
            if (method_name == "delegate_set_transaction_min_fee")
                return delegate_set_transaction_min_fee_positional(nullptr, parameters);
            if (method_name == "delegate_blacklist_add_transaction")
                return delegate_blacklist_add_transaction_positional(nullptr, parameters);
            if (method_name == "delegate_blacklist_remove_transaction")
                return delegate_blacklist_remove_transaction_positional(nullptr, parameters);
            if (method_name == "delegate_blacklist_add_operation")
                return delegate_blacklist_add_operation_positional(nullptr, parameters);
            if (method_name == "delegate_blacklist_remove_operation")
                return delegate_blacklist_remove_operation_positional(nullptr, parameters);
            
            if (method_name == "wallet_get_info")
                return wallet_get_info_positional(nullptr, parameters);
            if (method_name == "wallet_open")
                return wallet_open_positional(nullptr, parameters);
            if (method_name == "wallet_create")
                return wallet_create_positional(nullptr, parameters);
            if (method_name == "wallet_get_name")
                return wallet_get_name_positional(nullptr, parameters);
            if (method_name == "wallet_import_private_key")
                return wallet_import_private_key_positional(nullptr, parameters);
            if (method_name == "wallet_import_ethereum_private_key")
                return wallet_import_ethereum_private_key_positional(nullptr, parameters);
            if (method_name == "wallet_close")
                return wallet_close_positional(nullptr, parameters);
            if (method_name == "wallet_backup_create")
                return wallet_backup_create_positional(nullptr, parameters);
            if (method_name == "wallet_backup_restore")
                return wallet_backup_restore_positional(nullptr, parameters);
            if (method_name == "wallet_set_automatic_backups")
                return wallet_set_automatic_backups_positional(nullptr, parameters);
            if (method_name == "wallet_set_transaction_expiration_time")
                return wallet_set_transaction_expiration_time_positional(nullptr, parameters);
            if (method_name == "wallet_account_transaction_history")
                return wallet_account_transaction_history_positional(nullptr, parameters);
            if (method_name == "wallet_transaction_history_splite")
                return wallet_transaction_history_splite_positional(nullptr, parameters);
            if (method_name == "wallet_account_historic_balance")
                return wallet_account_historic_balance_positional(nullptr, parameters);
            if (method_name == "wallet_remove_transaction")
                return wallet_remove_transaction_positional(nullptr, parameters);
            if (method_name == "wallet_get_pending_transaction_errors")
                return wallet_get_pending_transaction_errors_positional(nullptr, parameters);
            if (method_name == "wallet_lock")
                return wallet_lock_positional(nullptr, parameters);
            if (method_name == "wallet_unlock")
                return wallet_unlock_positional(nullptr, parameters);
            if (method_name == "wallet_change_passphrase")
                return wallet_change_passphrase_positional(nullptr, parameters);
            if (method_name == "wallet_check_passphrase")
                return wallet_check_passphrase_positional(nullptr, parameters);
            if (method_name == "wallet_check_address")
                return wallet_check_address_positional(nullptr, parameters);
            if (method_name == "wallet_list")
                return wallet_list_positional(nullptr, parameters);
            if (method_name == "wallet_account_create")
                return wallet_account_create_positional(nullptr, parameters);
            if (method_name == "wallet_account_set_approval")
                return wallet_account_set_approval_positional(nullptr, parameters);
            if (method_name == "wallet_get_all_approved_accounts")
                return wallet_get_all_approved_accounts_positional(nullptr, parameters);
            if (method_name == "wallet_address_create")
                return wallet_address_create_positional(nullptr, parameters);
            if (method_name == "wallet_transfer_to_address")
                return wallet_transfer_to_address_positional(nullptr, parameters);
            if (method_name == "wallet_transfer_to_public_account")
                return wallet_transfer_to_public_account_positional(nullptr, parameters);
            if (method_name == "wallet_withdraw_from_address")
                return wallet_withdraw_from_address_positional(nullptr, parameters);
            if (method_name == "wallet_rescan_blockchain")
                return wallet_rescan_blockchain_positional(nullptr, parameters);
            if (method_name == "wallet_cancel_scan")
                return wallet_cancel_scan_positional(nullptr, parameters);
            if (method_name == "wallet_get_transaction")
                return wallet_get_transaction_positional(nullptr, parameters);
            if (method_name == "wallet_scan_transaction")
                return wallet_scan_transaction_positional(nullptr, parameters);
            if (method_name == "wallet_rebroadcast_transaction")
                return wallet_rebroadcast_transaction_positional(nullptr, parameters);
            if (method_name == "wallet_account_register")
                return wallet_account_register_positional(nullptr, parameters);
            if (method_name == "wallet_account_update_private_data")
                return wallet_account_update_private_data_positional(nullptr, parameters);
            if (method_name == "wallet_account_update_registration")
                return wallet_account_update_registration_positional(nullptr, parameters);
            if (method_name == "wallet_account_update_active_key")
                return wallet_account_update_active_key_positional(nullptr, parameters);
            if (method_name == "wallet_list_accounts")
                return wallet_list_accounts_positional(nullptr, parameters);
            if (method_name == "wallet_list_unregistered_accounts")
                return wallet_list_unregistered_accounts_positional(nullptr, parameters);
            if (method_name == "wallet_list_my_accounts")
                return wallet_list_my_accounts_positional(nullptr, parameters);
            if (method_name == "wallet_list_my_addresses")
                return wallet_list_my_addresses_positional(nullptr, parameters);
            if (method_name == "wallet_get_account")
                return wallet_get_account_positional(nullptr, parameters);
            if (method_name == "wallet_get_account_public_address")
                return wallet_get_account_public_address_positional(nullptr, parameters);
            if (method_name == "wallet_remove_contact_account")
                return wallet_remove_contact_account_positional(nullptr, parameters);
            if (method_name == "wallet_account_rename")
                return wallet_account_rename_positional(nullptr, parameters);
            if (method_name == "wallet_asset_create")
                return wallet_asset_create_positional(nullptr, parameters);
            if (method_name == "wallet_asset_issue")
                return wallet_asset_issue_positional(nullptr, parameters);
            if (method_name == "wallet_asset_issue_to_addresses")
                return wallet_asset_issue_to_addresses_positional(nullptr, parameters);
            if (method_name == "wallet_account_balance")
                return wallet_account_balance_positional(nullptr, parameters);
            if (method_name == "wallet_account_balance_ids")
                return wallet_account_balance_ids_positional(nullptr, parameters);
            if (method_name == "wallet_account_list_public_keys")
                return wallet_account_list_public_keys_positional(nullptr, parameters);
            if (method_name == "wallet_delegate_withdraw_pay")
                return wallet_delegate_withdraw_pay_positional(nullptr, parameters);
            if (method_name == "wallet_delegate_pay_balance_query")
                return wallet_delegate_pay_balance_query_positional(nullptr, parameters);
            if (method_name == "wallet_active_delegate_salary")
                return wallet_active_delegate_salary_positional(nullptr, parameters);
            if (method_name == "wallet_get_delegate_statue")
                return wallet_get_delegate_statue_positional(nullptr, parameters);
            if (method_name == "wallet_set_transaction_imessage_fee_coe")
                return wallet_set_transaction_imessage_fee_coe_positional(nullptr, parameters);
            if (method_name == "wallet_get_transaction_imessage_fee_coe")
                return wallet_get_transaction_imessage_fee_coe_positional(nullptr, parameters);
            if (method_name == "wallet_set_transaction_imessage_soft_max_length")
                return wallet_set_transaction_imessage_soft_max_length_positional(nullptr, parameters);
            if (method_name == "wallet_get_transaction_imessage_soft_max_length")
                return wallet_get_transaction_imessage_soft_max_length_positional(nullptr, parameters);
            if (method_name == "wallet_set_transaction_fee")
                return wallet_set_transaction_fee_positional(nullptr, parameters);
            if (method_name == "wallet_get_transaction_fee")
                return wallet_get_transaction_fee_positional(nullptr, parameters);
            if (method_name == "wallet_dump_private_key")
                return wallet_dump_private_key_positional(nullptr, parameters);
            if (method_name == "wallet_dump_account_private_key")
                return wallet_dump_account_private_key_positional(nullptr, parameters);
            if (method_name == "wallet_account_vote_summary")
                return wallet_account_vote_summary_positional(nullptr, parameters);
            if (method_name == "wallet_check_vote_status")
                return wallet_check_vote_status_positional(nullptr, parameters);
            if (method_name == "wallet_set_setting")
                return wallet_set_setting_positional(nullptr, parameters);
            if (method_name == "wallet_get_setting")
                return wallet_get_setting_positional(nullptr, parameters);
            if (method_name == "wallet_delegate_set_block_production")
                return wallet_delegate_set_block_production_positional(nullptr, parameters);
            if (method_name == "wallet_set_transaction_scanning")
                return wallet_set_transaction_scanning_positional(nullptr, parameters);
            if (method_name == "wallet_sign_hash")
                return wallet_sign_hash_positional(nullptr, parameters);
            if (method_name == "wallet_login_start")
                return wallet_login_start_positional(nullptr, parameters);
            if (method_name == "wallet_login_finish")
                return wallet_login_finish_positional(nullptr, parameters);
            if (method_name == "wallet_balance_set_vote_info")
                return wallet_balance_set_vote_info_positional(nullptr, parameters);
            if (method_name == "wallet_publish_slate")
                return wallet_publish_slate_positional(nullptr, parameters);
            if (method_name == "wallet_publish_version")
                return wallet_publish_version_positional(nullptr, parameters);
            if (method_name == "wallet_collect_genesis_balances")
                return wallet_collect_genesis_balances_positional(nullptr, parameters);
            if (method_name == "wallet_recover_accounts")
                return wallet_recover_accounts_positional(nullptr, parameters);
            if (method_name == "wallet_verify_titan_deposit")
                return wallet_verify_titan_deposit_positional(nullptr, parameters);
            if (method_name == "wallet_repair_entrys")
                return wallet_repair_entrys_positional(nullptr, parameters);
            if (method_name == "wallet_regenerate_keys")
                return wallet_regenerate_keys_positional(nullptr, parameters);
            if (method_name == "wallet_account_retract")
                return wallet_account_retract_positional(nullptr, parameters);
            if (method_name == "wallet_account_delete")
                return wallet_account_delete_positional(nullptr, parameters);
            if (method_name == "wallet_transfer_to_address_rpc")
                return wallet_transfer_to_address_rpc_positional(nullptr, parameters);
            if (method_name == "wallet_account_balance_rpc")
                return wallet_account_balance_rpc_positional(nullptr, parameters);
            if (method_name == "wallet_transfer_to_public_account_rpc")
                return wallet_transfer_to_public_account_rpc_positional(nullptr, parameters);
            if (method_name == "wallet_get_account_owner_publickey")
                return wallet_get_account_owner_publickey_positional(nullptr, parameters);
            if (method_name == "wallet_transfer_to_contract")
                return wallet_transfer_to_contract_positional(nullptr, parameters);
            if (method_name == "wallet_transfer_to_contract_testing")
                return wallet_transfer_to_contract_testing_positional(nullptr, parameters);
            if (method_name == "wallet_get_contracts")
                return wallet_get_contracts_positional(nullptr, parameters);
            if (method_name == "wallet_scan_contracts")
                return wallet_scan_contracts_positional(nullptr, parameters);
            if (method_name == "wallet_builder_add_signature")
                return wallet_builder_add_signature_positional(nullptr, parameters);
            if (method_name == "wallet_builder_file_add_signature")
                return wallet_builder_file_add_signature_positional(nullptr, parameters);
            if (method_name == "wallet_multisig_deposit")
                return wallet_multisig_deposit_positional(nullptr, parameters);
            if (method_name == "wallet_import_multisig_account")
                return wallet_import_multisig_account_positional(nullptr, parameters);
            if (method_name == "wallet_import_multisig_account_by_detail")
                return wallet_import_multisig_account_by_detail_positional(nullptr, parameters);
            if (method_name == "wallet_multisig_withdraw_start")
                return wallet_multisig_withdraw_start_positional(nullptr, parameters);
            if (method_name == "wallet_create_multisig_account")
                return wallet_create_multisig_account_positional(nullptr, parameters);
            if (method_name == "wallet_multisig_account_history")
                return wallet_multisig_account_history_positional(nullptr, parameters);
            if (method_name == "wallet_multisig_account_balance")
                return wallet_multisig_account_balance_positional(nullptr, parameters);
            if (method_name == "wallet_builder_get_multisig_detail")
                return wallet_builder_get_multisig_detail_positional(nullptr, parameters);
            if (method_name == "wallet_builder_file_get_multisig_detail")
                return wallet_builder_file_get_multisig_detail_positional(nullptr, parameters);
            if (method_name == "wallet_transfer_to_address_build")
                return wallet_transfer_to_address_build_positional(nullptr, parameters);
            if (method_name == "wallet_transfer_to_contract_build")
                return wallet_transfer_to_contract_build_positional(nullptr, parameters);
            if (method_name == "wallet_call_contract_build")
                return wallet_call_contract_build_positional(nullptr, parameters);
            if (method_name == "sign_build_transaction")
                return sign_build_transaction_positional(nullptr, parameters);
            if (method_name == "broadcast_building_transaction")
                return broadcast_building_transaction_positional(nullptr, parameters);
            if (method_name == "about")
                return about_positional(nullptr, parameters);
            if (method_name == "get_info")
                return get_info_positional(nullptr, parameters);
            if (method_name == "stop")
                return stop_positional(nullptr, parameters);
            if (method_name == "help")
                return help_positional(nullptr, parameters);
            if (method_name == "validate_address")
                return validate_address_positional(nullptr, parameters);
            if (method_name == "execute_command_line")
                return execute_command_line_positional(nullptr, parameters);
            if (method_name == "execute_script")
                return execute_script_positional(nullptr, parameters);
            if (method_name == "batch")
                return batch_positional(nullptr, parameters);
            if (method_name == "batch_authenticated")
                return batch_authenticated_positional(nullptr, parameters);
            if (method_name == "builder_finalize_and_sign")
                return builder_finalize_and_sign_positional(nullptr, parameters);
            if (method_name == "meta_help")
                return meta_help_positional(nullptr, parameters);
            if (method_name == "rpc_set_username")
                return rpc_set_username_positional(nullptr, parameters);
            if (method_name == "rpc_set_password")
                return rpc_set_password_positional(nullptr, parameters);
            if (method_name == "rpc_start_server")
                return rpc_start_server_positional(nullptr, parameters);
            if (method_name == "http_start_server")
                return http_start_server_positional(nullptr, parameters);
            if (method_name == "ntp_update_time")
                return ntp_update_time_positional(nullptr, parameters);
            if (method_name == "disk_usage")
                return disk_usage_positional(nullptr, parameters);
            if (method_name == "contract_compile")
                return contract_compile_positional(nullptr, parameters);
            if (method_name == "contract_register")
                return contract_register_positional(nullptr, parameters);
            if (method_name == "contract_register_testing")
                return contract_register_testing_positional(nullptr, parameters);
            if (method_name == "contract_upgrade")
                return contract_upgrade_positional(nullptr, parameters);
            if (method_name == "contract_upgrade_testing")
                return contract_upgrade_testing_positional(nullptr, parameters);
            if (method_name == "contract_destroy")
                return contract_destroy_positional(nullptr, parameters);
            if (method_name == "contract_destroy_testing")
                return contract_destroy_testing_positional(nullptr, parameters);
            if (method_name == "contract_call")
                return contract_call_positional(nullptr, parameters);
            if (method_name == "contract_get_info")
                return contract_get_info_positional(nullptr, parameters);
            if (method_name == "contract_get_balance")
                return contract_get_balance_positional(nullptr, parameters);
            if (method_name == "contract_call_testing")
                return contract_call_testing_positional(nullptr, parameters);
            if (method_name == "contract_call_offline")
                return contract_call_offline_positional(nullptr, parameters);
            if (method_name == "contract_load_to_file")
                return contract_load_to_file_positional(nullptr, parameters);
            if (method_name == "get_result_trx_id")
                return get_result_trx_id_positional(nullptr, parameters);
            if (method_name == "get_request_trx_id")
                return get_request_trx_id_positional(nullptr, parameters);
            if (method_name == "simulator_open")
                return simulator_open_positional(nullptr, parameters);
            if (method_name == "simulator_close")
                return simulator_close_positional(nullptr, parameters);
            if (method_name == "simulator_contract_register")
                return simulator_contract_register_positional(nullptr, parameters);
            if (method_name == "simulator_contract_call")
                return simulator_contract_call_positional(nullptr, parameters);
            if (method_name == "simulator_contract_upgrade")
                return simulator_contract_upgrade_positional(nullptr, parameters);
            if (method_name == "simulator_contract_upgrade_testing")
                return simulator_contract_upgrade_testing_positional(nullptr, parameters);
            if (method_name == "simulator_contract_destroy")
                return simulator_contract_destroy_positional(nullptr, parameters);
            if (method_name == "simulator_contract_destroy_testing")
                return simulator_contract_destroy_testing_positional(nullptr, parameters);
            if (method_name == "simulator_contract_get_info")
                return simulator_contract_get_info_positional(nullptr, parameters);
            if (method_name == "simulator_contract_get_balance")
                return simulator_contract_get_balance_positional(nullptr, parameters);
            if (method_name == "simulator_transfer_to_contract")
                return simulator_transfer_to_contract_positional(nullptr, parameters);
            if (method_name == "simulator_account_balance")
                return simulator_account_balance_positional(nullptr, parameters);
            if (method_name == "simulator_contract_compile")
                return simulator_contract_compile_positional(nullptr, parameters);
            if (method_name == "simulator_contract_load_to_file")
                return simulator_contract_load_to_file_positional(nullptr, parameters);
            if (method_name == "simulator_contract_register_testing")
                return simulator_contract_register_testing_positional(nullptr, parameters);
            if (method_name == "simulator_contract_call_testing")
                return simulator_contract_call_testing_positional(nullptr, parameters);
            if (method_name == "simulator_transfer_to_contract_testing")
                return simulator_transfer_to_contract_testing_positional(nullptr, parameters);
            if (method_name == "simulator_list_my_addresses")
                return simulator_list_my_addresses_positional(nullptr, parameters);
            if (method_name == "get_contract_registered_in_transaction")
                return get_contract_registered_in_transaction_positional(nullptr, parameters);
            if (method_name == "get_transaction_id_contract_registered")
                return get_transaction_id_contract_registered_positional(nullptr, parameters);
            if (method_name == "contract_get_info_from_gpc_file")
                return contract_get_info_from_gpc_file_positional(nullptr, parameters);
            if (method_name == "script_compile")
                return script_compile_positional(nullptr, parameters);
            if (method_name == "script_add")
                return script_add_positional(nullptr, parameters);
            if (method_name == "script_remove")
                return script_remove_positional(nullptr, parameters);
            if (method_name == "script_get_info")
                return script_get_info_positional(nullptr, parameters);
            if (method_name == "scripts_list")
                return scripts_list_positional(nullptr, parameters);
            if (method_name == "script_disable")
                return script_disable_positional(nullptr, parameters);
            if (method_name == "script_enable")
                return script_enable_positional(nullptr, parameters);
            if (method_name == "script_import_to_db")
                return script_import_to_db_positional(nullptr, parameters);
            if (method_name == "script_export_from_db")
                return script_export_from_db_positional(nullptr, parameters);
            if (method_name == "script_get_events_bound")
                return script_get_events_bound_positional(nullptr, parameters);
            if (method_name == "script_list_event_handler")
                return script_list_event_handler_positional(nullptr, parameters);
            if (method_name == "script_add_event_handler")
                return script_add_event_handler_positional(nullptr, parameters);
            if (method_name == "script_delete_event_handler")
                return script_delete_event_handler_positional(nullptr, parameters);
            if (method_name == "proposal_apply_for_privilege_admin")
                return proposal_apply_for_privilege_admin_positional(nullptr, parameters);
            if (method_name == "proposal_revoke_privilege_admin")
                return proposal_revoke_privilege_admin_positional(nullptr, parameters);
            if (method_name == "proposal_approve")
                return proposal_approve_positional(nullptr, parameters);
            if (method_name == "proposal_get_info")
                return proposal_get_info_positional(nullptr, parameters);
            if (method_name == "appoint_general_admin")
                return appoint_general_admin_positional(nullptr, parameters);
            if (method_name == "revoke_general_admin")
                return revoke_general_admin_positional(nullptr, parameters);
            if (method_name == "get_all_privilege_admin")
                return get_all_privilege_admin_positional(nullptr, parameters);
            if (method_name == "get_all_general_admin")
                return get_all_general_admin_positional(nullptr, parameters);
            FC_ASSERT(false, "shouldn't happen");
        }

	}
} // end namespace cdcchain::rpc_stubs
