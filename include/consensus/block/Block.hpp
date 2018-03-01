#pragma once

#include <consensus/transaction/Transaction.hpp>

namespace cdcchain {
    namespace consensus {

        struct BlockHeader
        {
            DigestType  digest()const;

            BlockIdType        previous;
            uint32_t             block_num = 0;
            fc::time_point_sec   timestamp;
            DigestType          transaction_digest;
			uint32_t			evidence_count = 0;
			DigestType			evidence_digest;
            /** used for random number generation on the blockchain */
            SecretHashType     next_secret_hash;
            SecretHashType     previous_secret;
        };

        struct SignedBlockHeader : public BlockHeader
        {
            BlockIdType    id()const;
            bool             validate_signee(const fc::ecc::public_key& expected_signee, bool enforce_canonical = false)const;
            PublicKeyType  signee(bool enforce_canonical = false)const;
            void             sign(const fc::ecc::private_key& signer);

            SignatureType delegate_signature;
        };

        struct FullBlock : public SignedBlockHeader
        {
            size_t               block_size()const;

            signed_transactions  user_transactions;
        };
		struct EvidenceBlock : public SignedBlockHeader
		{
			EvidenceBlock() {}
			EvidenceBlock(const FullBlock& block_data);
			signed_transactions user_evidences;

		};
        struct DigestBlock : public SignedBlockHeader
        {
            DigestBlock(){}
            DigestBlock(const FullBlock& block_data);
			DigestBlock(const EvidenceBlock& evidence_data);

            DigestType                      calculate_transaction_digest()const;
            bool                            validate_transaction_digest()const;

			bool                            validate_digest()const;
            bool                            validate_unique()const;

			DigestType                      calculate_evidence_digest()const;
			bool                            validate_evidence_digest()const;

            std::vector<TransactionIdType> user_transaction_ids;
			std::vector<EvidenceIdType> user_evidence_ids;
        };
		
		

    }
} // cdcchain::consensus

FC_REFLECT(cdcchain::consensus::BlockHeader,
    (previous)(block_num)(timestamp)(transaction_digest)(evidence_count)(evidence_digest)(next_secret_hash)(previous_secret))
    FC_REFLECT_DERIVED(cdcchain::consensus::SignedBlockHeader, (cdcchain::consensus::BlockHeader), (delegate_signature))
    FC_REFLECT_DERIVED(cdcchain::consensus::FullBlock, (cdcchain::consensus::SignedBlockHeader), (user_transactions))
	FC_REFLECT_DERIVED(cdcchain::consensus::EvidenceBlock, (cdcchain::consensus::BlockHeader), (user_evidences))
    FC_REFLECT_DERIVED(cdcchain::consensus::DigestBlock, (cdcchain::consensus::SignedBlockHeader), (user_transaction_ids)(user_evidence_ids))
