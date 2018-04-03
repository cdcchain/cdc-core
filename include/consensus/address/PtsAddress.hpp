// Copyright (c) 2017-2018 The CDC developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.


#pragma once

#include <fc/array.hpp>
#include <string>

namespace fc { namespace ecc { class public_key; } }

namespace cdcchain {
    namespace consensus {

        /**
         *  Implements address stringification and validation from PTS
         */
        struct PtsAddress
        {
            PtsAddress(); ///< constructs empty / null address
            PtsAddress(const std::string& base58str);   ///< converts to binary, validates checksum
            PtsAddress(const fc::ecc::public_key& pub, bool compressed = true, uint8_t version = 56); ///< converts to binary

            uint8_t version()const { return addr.at(0); }
            bool is_valid()const;

            operator std::string()const; ///< converts to base58 + checksum

            fc::array<char, 25> addr; ///< binary representation of address
        };

        inline bool operator == (const PtsAddress& a, const PtsAddress& b) { return a.addr == b.addr; }
        inline bool operator != (const PtsAddress& a, const PtsAddress& b) { return a.addr != b.addr; }
        inline bool operator <  (const PtsAddress& a, const PtsAddress& b) { return a.addr < b.addr; }

    }
} // namespace cdcchain::consensus

namespace std
{
    template<>
    struct hash < cdcchain::consensus::PtsAddress >
    {
    public:
        size_t operator()(const cdcchain::consensus::PtsAddress &a) const
        {
            size_t s;
            memcpy((char*)&s, &a.addr.data[sizeof(a) - sizeof(s)], sizeof(s));
            return s;
        }
    };
}

#include <fc/reflect/reflect.hpp>
FC_REFLECT(cdcchain::consensus::PtsAddress, (addr))

namespace fc
{
    void to_variant(const cdcchain::consensus::PtsAddress& var, fc::variant& vo);
    void from_variant(const fc::variant& var, cdcchain::consensus::PtsAddress& vo);
}
