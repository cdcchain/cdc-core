#include <consensus/evidence/ShopReceiptEvidence.hpp>
#include <consensus/evidence/EvidenceFactory.hpp>
#include <consensus/evidence/Evidences.hpp>
#include <fc/io/raw_variant.hpp>
#include <fc/reflect/variant.hpp>

namespace cdcchain {
    namespace consensus {
        const EvidenceTypeEnum ShopReceiptEvidence::type = shop_receipt_ev_type;
        static bool first_chain = []()->bool{
            cdcchain::consensus::EvidenceFactory::instance().register_evidence<ShopReceiptEvidence>();
            return true;
        }();

        EvidenceFactory& EvidenceFactory::instance()
        {
            static std::unique_ptr<EvidenceFactory> inst(new EvidenceFactory());
            return *inst;
        }

        void EvidenceFactory::to_variant(const cdcchain::consensus::Evidence& in, fc::variant& output)
        {
            try {
                auto converter_itr = _converters.find(in.type.value);
                FC_ASSERT(converter_itr != _converters.end(), "No such converter!");
                converter_itr->second->to_variant(in, output);
            } FC_RETHROW_EXCEPTIONS(warn, "")
        }

        void EvidenceFactory::from_variant(const fc::variant& in, cdcchain::consensus::Evidence& output)
        {
            try {
                auto obj = in.get_object();

                output.type = obj["type"].as<EvidenceTypeEnum>();

                auto converter_itr = _converters.find(output.type.value);
                FC_ASSERT(converter_itr != _converters.end());
                converter_itr->second->from_variant(in, output);
            } FC_RETHROW_EXCEPTIONS(warn, "", ("in", in))
        }

    }
} // cdcchain::consensus

namespace fc {
    void to_variant(const cdcchain::consensus::Evidence& var, variant& vo)
    {
        cdcchain::consensus::EvidenceFactory::instance().to_variant(var, vo);
    }

    void from_variant(const variant& var, cdcchain::consensus::Evidence& vo)
    {
        cdcchain::consensus::EvidenceFactory::instance().from_variant(var, vo);
    }
}
