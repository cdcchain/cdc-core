// Copyright (c) 2017-2018 The CDC developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.


#include <consensus/address/Address.hpp>
#include <consensus/WithdrawTypes.hpp>
#include <consensus/Exceptions.hpp>

#include <fc/crypto/base58.hpp>
#include <algorithm>

#include <utilities/Keccak.hpp>

namespace cdcchain {
  namespace consensus {

   Address::Address(const AddressType& address_type){}

   
   Address::Address(const std::string& hex_str, const AddressType& address_type)
   {
       std::string  addr_str;

       if (!Address::is_valid(hex_str, address_type))
       {
           FC_THROW_EXCEPTION(invalid_address, "invalid address ${a}", ("a", hex_str));
       }

       if (address_type == AddressType::cdc_address)
           addr_str = hex_str.substr(2, hex_str.size());
       else
           addr_str = hex_str.substr(1, hex_str.size());

       addr = fc::ripemd160(addr_str);
   }

   Address::Address( const WithdrawCondition& condition )
   {
      fc::sha512::encoder enc;
      fc::raw::pack(enc, condition);
      auto tmp = enc.result();

      Keccak tmp_addr;
      tmp_addr.add(tmp.data(), tmp.data_size());

      auto addr_str_keccaksha3 = tmp_addr.getHash();
      auto hex_str = addr_str_keccaksha3.substr(24, addr_str_keccaksha3.size());

      addr = fc::ripemd160(hex_str);
   }

   bool Address::is_valid( const std::string& hex_str, const AddressType& address_type)
   {
       std::string  addr_str;

       if (address_type == AddressType::cdc_address)
       {
           //FC_ASSERT(hex_str.size() >= 2 && hex_str[0] == CDC_ADDRESS_PREFIX[0] && hex_str[1] == CDC_ADDRESS_PREFIX[1]);
		   if (!(hex_str.size() >= 2 && hex_str[0] == CDC_ADDRESS_PREFIX[0] && hex_str[1] == CDC_ADDRESS_PREFIX[1]))
			  return false;
		   addr_str = hex_str.substr(2, hex_str.size());
       }        
       else if (address_type == AddressType::contract_address)
       {
           //FC_ASSERT(hex_str.size() >= 2 && hex_str[0] == CONTRACT_ADDRESS_PREFIX[0]);
		   if (!(hex_str.size() >= 2 && hex_str[0] == CONTRACT_ADDRESS_PREFIX[0]))
			  return false;
           addr_str = hex_str.substr(1, hex_str.size());

       }           
       else if (address_type == AddressType::script_id)
       {
           //FC_ASSERT(hex_str.size() >= 2 && hex_str[0] == SCRIPT_ID_PREFIX[0]);
		   if (!(hex_str.size() >= 2 && hex_str[0] == SCRIPT_ID_PREFIX[0]))
		       return false;
           addr_str = hex_str.substr(1, hex_str.size());
       }           
       else if (address_type == AddressType::multisig_address)
       {
           //FC_ASSERT(hex_str.size() >= 2 && hex_str[0] == MULTI_ADDRESS_PREFIX[0]);
		   if (!(hex_str.size() >= 2 && hex_str[0] == MULTI_ADDRESS_PREFIX[0]))
		       return false;
           addr_str = hex_str.substr(1, hex_str.size());
       }

       //FC_ASSERT(addr_str.size() == ADDRESS_HEX_LEN, "the address hex str length is invalid!");
	   if (!(addr_str.size() == ADDRESS_HEX_LEN, "the address hex str length is invalid!"))
	       return false;

       for (auto i = addr_str.begin(); i != addr_str.end(); ++i)
       {
           fc::from_hex(*i);
       }

       return true;     
   }

   Address::Address( const fc::ecc::public_key& pub )
   {
       auto dat = pub.serialize_ecc_point();
       
       Keccak tmp_addr;
       tmp_addr.add(dat.begin() + 1, dat.size() - 1);

       auto addr_str_keccaksha3 = tmp_addr.getHash();
       auto hex_str = addr_str_keccaksha3.substr(24, addr_str_keccaksha3.size());

       addr = fc::ripemd160(hex_str);

   }

   Address::Address( const PtsAddress& ptsaddr )
   {

       Keccak tmp_addr;
       tmp_addr.add((char*)&ptsaddr, sizeof(ptsaddr));

       auto addr_str_keccaksha3 = tmp_addr.getHash();
       auto hex_str = addr_str_keccaksha3.substr(24, addr_str_keccaksha3.size());

       addr = fc::ripemd160(hex_str);
   }

   Address::Address( const fc::ecc::public_key_data& pub )
   {
       fc::ecc::public_key pub_key(pub);
       auto dat = pub_key.serialize_ecc_point();

       Keccak tmp_addr;
       tmp_addr.add(dat.begin() + 1, dat.size() - 1);

       auto addr_str_keccaksha3 = tmp_addr.getHash();
       auto hex_str = addr_str_keccaksha3.substr(24, addr_str_keccaksha3.size());

       addr = fc::ripemd160(hex_str);
   }

   Address::Address( const PublicKeyType& pub )
   {

       fc::ecc::public_key pub_key(pub.key_data);
       auto dat = pub_key.serialize_ecc_point();

       Keccak tmp_addr;
       tmp_addr.add(dat.begin() + 1, dat.size() - 1);

       auto addr_str_keccaksha3 = tmp_addr.getHash();
       auto hex_str = addr_str_keccaksha3.substr(24, addr_str_keccaksha3.size());

       addr = fc::ripemd160(hex_str);

   }

   int Address::judge_addr_type(const std::string& hex_str)
   {
       // chain address
       if (hex_str[0] == CDC_ADDRESS_PREFIX[0] && hex_str[1] == CDC_ADDRESS_PREFIX[1])
           return AddressType::cdc_address;
       else if (hex_str[0] == CONTRACT_ADDRESS_PREFIX[0])
           return AddressType::contract_address;
       else if (hex_str[0] == SCRIPT_ID_PREFIX[0])
           return AddressType::script_id;
       else if (hex_str[0] == MULTI_ADDRESS_PREFIX[0])
           return AddressType::multisig_address;
   }

   std::string Address::AddressToString(const AddressType& address_type)const
   {
       if (address_type == AddressType::cdc_address)
       {
           return  CDC_ADDRESS_PREFIX + addr.str();
       }
       else if (address_type == AddressType::contract_address)
       {
           return CONTRACT_ADDRESS_PREFIX + addr.str();
       }
       else if (address_type == AddressType::script_id)
       {
           return SCRIPT_ID_PREFIX + addr.str();
       }
       else if (address_type == AddressType::multisig_address)
       {
           return MULTI_ADDRESS_PREFIX + addr.str();
       }


   }

   Address::operator std::string() const
   {

       return CDC_ADDRESS_PREFIX +  addr.str();
   }



} } // namespace emo::blockchain


namespace fc
{
    void to_variant(const cdcchain::consensus::Address& var, variant& vo)
    {
        vo = std::string(var);
    }
    void from_variant(const variant& var, cdcchain::consensus::Address& vo)
    {
        vo = cdcchain::consensus::Address(var.as_string());
    }
}

