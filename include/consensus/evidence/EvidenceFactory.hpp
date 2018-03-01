#pragma once

#include <consensus/Exceptions.hpp>
#include <consensus/evidence/Evidences.hpp>

namespace cdcchain {
    namespace consensus {

        /**
         * @class evidence_factory
         *
         *  Enables polymorphic creation and serialization of evidence objects in
         *  an manner that can be extended by derived chains.
         */
        class EvidenceFactory
        {
        public:
            static EvidenceFactory& instance();
            class EvidenceConverterBase
            {
            public:
                virtual ~EvidenceConverterBase(){};
                virtual void to_variant(const cdcchain::consensus::Evidence& in, fc::variant& out) = 0;
                virtual void from_variant(const fc::variant& in, cdcchain::consensus::Evidence& out) = 0;
                virtual void evaluate(TransactionEvaluationState& eval_state, const Evidence& op) = 0;
            };

            template<typename EvidenceType>
            class evidence_converter : public EvidenceConverterBase
            {
            public:
                virtual void to_variant(const cdcchain::consensus::Evidence& in, fc::variant& output)
                {
                    try {
                        FC_ASSERT(in.type == EvidenceType::type);
                        fc::mutable_variant_object obj("type", in.type);

                        obj["data"] = fc::raw::unpack<EvidenceType>(in.data);

                        output = std::move(obj);
                    } FC_RETHROW_EXCEPTIONS(warn, "")
                }

                virtual void from_variant(const fc::variant& in, cdcchain::consensus::Evidence& output)
                {
                    try {
                        auto obj = in.get_object();

                        FC_ASSERT(output.type == EvidenceType::type);
                        output.data = fc::raw::pack(obj["data"].as<EvidenceType>());
                    } FC_RETHROW_EXCEPTIONS(warn, "type: ${type}", ("type", fc::get_typename<EvidenceType>::name()))
                }

                virtual void evaluate(TransactionEvaluationState& eval_state, const Evidence& ev)
                {
                    try {
                        ev.as<EvidenceType>().evaluate(eval_state);
                    } FC_CAPTURE_AND_RETHROW((ev))
                }
            };

            template<typename EvidenceType>
            void   register_evidence()
            {
                FC_ASSERT(_converters.find(EvidenceType::type) == _converters.end(),
                    "Evidence ID already Registered ${id}", ("id", EvidenceType::type));
                _converters[EvidenceType::type] = std::make_shared< evidence_converter<EvidenceType> >();
            }

            void evaluate(TransactionEvaluationState& eval_state, const Evidence& ev)
            {
                auto itr = _converters.find(uint8_t(ev.type));
                if (itr == _converters.end())
                    FC_THROW_EXCEPTION(cdcchain::consensus::unsupported_chain_evidence, "", ("ev", ev));
                itr->second->evaluate(eval_state, ev);
            }

            /// defined in evidences.cpp
            void to_variant(const cdcchain::consensus::Evidence& in, fc::variant& output);
            /// defined in evidences.cpp
            void from_variant(const fc::variant& in, cdcchain::consensus::Evidence& output);

        private:
            std::unordered_map<int, std::shared_ptr<EvidenceConverterBase> > _converters;
        };

    }
} // cdcchain::consensus 
