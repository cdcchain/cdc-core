#pragma once

#include <consensus/Config.hpp>
#include <consensus/address/PtsAddress.hpp>

#include <fc/array.hpp>
#include <fc/crypto/ripemd160.hpp>
#include <fc/crypto/hex.hpp>

namespace fc { namespace ecc {
    class public_key;
    typedef fc::array<char,33>  public_key_data;
} } // fc::ecc

namespace cdcchain { namespace consensus {

    enum AddressType
    {
        cdc_address = 0,
        contract_address = 1,
        script_id = 2,
        multisig_address = 3
    };

   struct WithdrawCondition;
   struct PublicKeyType;

   /**
    *  @brief a 160 bit hash of a public key
    *
    *  An address can be converted to or from a base58 string with 32 bit checksum.
    *
    *  An address is calculated as ripemd160( sha512( compressed_ecc_public_key ) )
    *
    *  When converted to a string, checksum calculated as the first 4 bytes ripemd160( address ) is
    *  appended to the binary address before converting to base58.
    */
   class Address
   {
      public:
       Address(const AddressType& address_type = AddressType::cdc_address); ///< constructs empty / null address
       explicit Address(const std::string& hex_str, const AddressType& address_type = AddressType::cdc_address);   ///< converts to binary, hex_str should not include '0x'
       Address( const fc::ecc::public_key& pub ); ///< converts to binary
       explicit Address( const fc::ecc::public_key_data& pub ); ///< converts to binary
       Address( const PtsAddress& pub ); ///< converts to binary
       Address( const WithdrawCondition& condition );
       Address( const PublicKeyType& pubkey );

       static bool is_valid( const std::string& hex_str, const AddressType& address_type = AddressType::cdc_address);
       int judge_addr_type(const std::string& hex_str);

       std::string AddressToString(const AddressType& address_type = AddressType::cdc_address)const;
       explicit operator std::string() const; ///< converts to base58 + checksum

       fc::ripemd160 addr;

   };
   inline bool operator == ( const Address& a, const Address& b ) { return std::string(a) == std::string(b); }
   inline bool operator != (const Address& a, const Address& b) { return std::string(a) != std::string(b); }
   inline bool operator <  (const Address& a, const Address& b) { return std::string(a) <  std::string(b); }

} } // namespace emo::blockchain

namespace fc
{
   void to_variant( const cdcchain::consensus::Address& var,  fc::variant& vo );
   void from_variant( const fc::variant& var, cdcchain::consensus::Address& vo );
}

namespace std
{
   template<>
   struct hash<cdcchain::consensus::Address>
   {
       public:
         size_t operator()(const cdcchain::consensus::Address &a) const
         {
             return (uint64_t(a.addr._hash[0]) << 32) | uint64_t(a.addr._hash[0]);
         }
   };
}

#include <fc/reflect/reflect.hpp>
FC_REFLECT(cdcchain::consensus::Address, (addr) )
