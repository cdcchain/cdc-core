#include <consensus/block/Block.hpp>
#include <algorithm>

namespace cdcchain {
    namespace consensus {

        DigestType BlockHeader::digest()const
        {
            fc::sha256::encoder enc;
            fc::raw::pack(enc, *this);
            return enc.result();
        }

        BlockIdType SignedBlockHeader::id()const
        {
            fc::sha512::encoder enc;
            fc::raw::pack(enc, *this);
            return fc::ripemd160::hash(enc.result());
        }

        bool SignedBlockHeader::validate_signee(const fc::ecc::public_key& expected_signee, bool enforce_canonical)const
        {
            return fc::ecc::public_key(delegate_signature, digest(), enforce_canonical) == expected_signee;
        }

        PublicKeyType SignedBlockHeader::signee(bool enforce_canonical)const
        {
            return fc::ecc::public_key(delegate_signature, digest(), enforce_canonical);
        }

        void SignedBlockHeader::sign(const fc::ecc::private_key& signer)
        {
            try {
                delegate_signature = signer.sign_compact(digest());
            } FC_RETHROW_EXCEPTIONS(warn, "")
        }

        size_t FullBlock::block_size()const
        {
            fc::datastream<size_t> ds;
            fc::raw::pack(ds, *this);
            return ds.tellp();
        }

        DigestBlock::DigestBlock(const FullBlock& block_data)
        {
            (SignedBlockHeader&)*this = block_data;
            user_transaction_ids.reserve(block_data.user_transactions.size());
			for (const auto& item : block_data.user_transactions) {
				user_transaction_ids.push_back(item.id());
				for (const auto& ev : item.evidences)
					user_evidence_ids.push_back(ev.id());
			}
        }
		DigestBlock::DigestBlock(const EvidenceBlock& evidence_data)
		{
			(SignedBlockHeader&)*this = evidence_data;
			user_transaction_ids.reserve(evidence_data.user_evidences.size());
			for (const auto& item : evidence_data.user_evidences) {
				for (const auto& ev : item.evidences)
					user_evidence_ids.push_back(ev.id());
			}
		}

		EvidenceBlock::EvidenceBlock(const FullBlock& block_data)
		{
			(SignedBlockHeader&)*this = block_data;
			for (const auto& item : block_data.user_transactions) {
				if (item.evidences.size() > 0)
					user_evidences.push_back(item);
			}
		}
		

        DigestType DigestBlock::calculate_transaction_digest()const
        {
            fc::sha512::encoder enc;
            fc::raw::pack(enc, user_transaction_ids);
            return fc::sha256::hash(enc.result());
        }

        bool DigestBlock::validate_transaction_digest()const
        {
            return calculate_transaction_digest() == transaction_digest;
        }

		bool DigestBlock::validate_digest()const
		{
			return validate_transaction_digest() && validate_evidence_digest();
		}

        bool DigestBlock::validate_unique()const
        {
            std::unordered_set<TransactionIdType> trx_ids;
            for (const auto& id : user_transaction_ids)
                if (!trx_ids.insert(id).second) return false;
            return true;
        }

		DigestType DigestBlock::calculate_evidence_digest()const
		{
			fc::sha512::encoder enc;
			fc::raw::pack(enc, user_evidence_ids);
			return fc::sha256::hash(enc.result());
		}

		bool DigestBlock::validate_evidence_digest()const
		{
			return calculate_evidence_digest() == evidence_digest;
		}

    }
} // cdcchain::consensus
