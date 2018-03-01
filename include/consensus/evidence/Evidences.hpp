#pragma once

#include <fc/io/enum_type.hpp>
#include <fc/io/raw.hpp>
#include <fc/reflect/reflect.hpp>
#include <consensus/Types.hpp>

/**
 *  The C keyword 'not' is NOT friendly on VC++ but we still want to use
 *  it for readability, so we will have the pre-processor convert it to the
 *  more traditional form.  The goal here is to make the understanding of
 *  the validation logic as english-like as possible.
 */
#define NOT !
#define AND &&
#define OR ||

namespace cdcchain {
    namespace consensus {

        class TransactionEvaluationState;

		enum EvidenceTypeEnum
		{
			null_ev_type = 0,
			shop_receipt_ev_type = 1,
        };

        /**
         *  A poly-morphic operator that modifies the blockchain database
         *  is some manner.
         */
        struct Evidence
        {
            Evidence() :type(null_ev_type){}

            Evidence(const Evidence& o)
                :type(o.type), data(o.data), data_len(o.data_len), ev_id(o.ev_id){}

            Evidence(Evidence&& o)
                :type(o.type), data(std::move(o.data)), data_len(std::move(o.data_len)), ev_id(std::move(o.ev_id)){}

            template<typename EvidenceType>
            Evidence(const EvidenceType& t)
            {
                type = EvidenceType::type;
                data = fc::raw::pack(t);
				data_len = data.size();

				fc::sha512::encoder enc;
				fc::raw::pack(enc, data);
				ev_id = fc::ripemd160::hash(enc.result());
            }

            template<typename EvidenceType>
            EvidenceType as()const
            {
                FC_ASSERT((EvidenceTypeEnum)type == EvidenceType::type, "", ("type", type)("EvidenceType", EvidenceType::type));
                return fc::raw::unpack<EvidenceType>(data);
            }

            Evidence& operator=(const Evidence& o)
            {
                if (this == &o) return *this;
                type = o.type;
                data = o.data;
				data_len = o.data_len;
				ev_id = o.ev_id;
                return *this;
            }

            Evidence& operator=(Evidence&& o)
            {
                if (this == &o) return *this;
                type = o.type;
                data = std::move(o.data);
				data_len = std::move(o.data_len);
				ev_id = std::move(o.ev_id);
                return *this;
            }

			EvidenceIdType id()const
			{
				fc::sha512::encoder enc;
				fc::raw::pack(enc, data);
				return fc::ripemd160::hash(enc.result());
			}

			bool check_ev_id(const EvidenceIdType& ev_id_check)const
			{
				return id() == ev_id_check;
			}

            fc::enum_type<uint8_t, EvidenceTypeEnum> type;
            std::vector<char> data;
			uint32_t data_len;
			EvidenceIdType ev_id;
        };

    }
} // cdcchain::consensus

FC_REFLECT_ENUM(cdcchain::consensus::EvidenceTypeEnum,
    (null_ev_type)
	(shop_receipt_ev_type)
    )

    FC_REFLECT(cdcchain::consensus::Evidence, (type)(data)(data_len)(ev_id))

namespace fc {
    void to_variant(const cdcchain::consensus::Evidence& var, variant& vo);
    void from_variant(const variant& var, cdcchain::consensus::Evidence& vo);
}
