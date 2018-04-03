// Copyright (c) 2017-2018 The CDC developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.


#include <consensus/Config.hpp>
#include <consensus/Types.hpp>

#include <fc/crypto/base58.hpp>
#include <fc/exception/exception.hpp>
#include <fc/io/raw.hpp>

namespace cdcchain {
    namespace consensus {

        PublicKeyType::PublicKeyType() :key_data(){};

        PublicKeyType::PublicKeyType(const fc::ecc::public_key_data& data)
            :key_data(data) {};

        PublicKeyType::PublicKeyType(const fc::ecc::public_key& pubkey)
            :key_data(pubkey) {};

        PublicKeyType::PublicKeyType(const std::string& base58str)
        {
            // TODO:  Refactor syntactic checks into static is_valid()
            //        to make public_key_type API more similar to address API
            std::string prefix(CDC_ADDRESS_PREFIX);
            try
            {
                if (is_valid_v1(base58str))
                    prefix = std::string(CDC_ADDRESS_PREFIX);
            }
            catch (...)
            {
            }
            const size_t prefix_len = prefix.size();
            FC_ASSERT(base58str.size() > prefix_len, "Address must be longger than CDC_ADDRESS_PREFIX");
            FC_ASSERT(base58str.substr(0, prefix_len) == prefix, "", ("base58str", base58str));
            auto bin = fc::from_base58(base58str.substr(prefix_len));
            auto bin_key = fc::raw::unpack<BinaryKey>(bin);
            key_data = bin_key.data;
            FC_ASSERT(fc::ripemd160::hash(key_data.data, key_data.size())._hash[0] == bin_key.check);
        };

        bool PublicKeyType::is_valid_v1(const std::string& base58str)
        {
            std::string prefix(CDC_ADDRESS_PREFIX);
            const size_t prefix_len = prefix.size();
            FC_ASSERT(base58str.size() > prefix_len, "Address must be longger than CDC_ADDRESS_PREFIX");
            FC_ASSERT(base58str.substr(0, prefix_len) == prefix, "", ("base58str", base58str));
            auto bin = fc::from_base58(base58str.substr(prefix_len));
            auto bin_key = fc::raw::unpack<BinaryKey>(bin);
            fc::ecc::public_key_data key_data = bin_key.data;
            FC_ASSERT(fc::ripemd160::hash(key_data.data, key_data.size())._hash[0] == bin_key.check);
            return true;
        }

        PublicKeyType::operator fc::ecc::public_key_data() const
        {
            return key_data;
        };

        PublicKeyType::operator fc::ecc::public_key() const
        {
            return fc::ecc::public_key(key_data);
        };

        PublicKeyType::operator std::string() const
        {
            BinaryKey k;
            k.data = key_data;
            k.check = fc::ripemd160::hash(k.data.data, k.data.size())._hash[0];
            auto data = fc::raw::pack(k);
            return CDC_ADDRESS_PREFIX + fc::to_base58(data.data(), data.size());
        }

        bool operator == (const PublicKeyType& p1, const fc::ecc::public_key& p2)
        {
            return p1.key_data == p2.serialize();
        }

        bool operator == (const PublicKeyType& p1, const PublicKeyType& p2)
        {
            return p1.key_data == p2.key_data;
        }

        bool operator != (const PublicKeyType& p1, const PublicKeyType& p2)
        {
            return p1.key_data != p2.key_data;
        }

    }
} // cdcchain::consensus

namespace fc
{
    void to_variant(const cdcchain::consensus::PublicKeyType& var, fc::variant& vo)
    {
        vo = std::string(var);
    }

    void from_variant(const fc::variant& var, cdcchain::consensus::PublicKeyType& vo)
    {
        vo = cdcchain::consensus::PublicKeyType(var.as_string());
    }
} // fc
