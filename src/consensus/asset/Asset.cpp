// Copyright (c) 2017-2018 The CDC developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.


#include <consensus/asset/Asset.hpp>
#include <consensus/Config.hpp>
#include <consensus/Exceptions.hpp>

#include <fc/reflect/variant.hpp>
#include <fc/uint128.hpp>
#include <fc/real128.hpp>

#include <sstream>
#include <stdio.h>

#include <uvm/lprefix.h>

namespace cdcchain {
    namespace consensus {

        Price operator *(const Price& l, const Price& r)
        {
            try {
                FC_ASSERT(l.quote_asset_id == r.quote_asset_id);
                FC_ASSERT(l.base_asset_id == r.base_asset_id);

                // infinity times zero is undefined / exception
                // infinity times anything else is infinity
                if (l.is_infinite())
                {
                    if (r.ratio == fc::uint128_t(0))
                        FC_THROW_EXCEPTION(price_multiplication_undefined, "price multiplication undefined (0 * inf)");
                    return l;
                }
                if (r.is_infinite())
                {
                    if (l.ratio == fc::uint128_t(0))
                        FC_THROW_EXCEPTION(price_multiplication_undefined, "price multiplication undefined (inf * 0)");
                    return r;
                }

                // zero times anything is zero (infinity is already handled above)
                if (l.ratio == fc::uint128_t(0))
                    return l;
                if (r.ratio == fc::uint128_t(0))
                    return r;

                fc::bigint product = l.ratio;
                product *= r.ratio;
                product /= FC_REAL128_PRECISION;

                // if the quotient is zero, it means there was an underflow
                //    (i.e. the result is nonzero but too small to represent)
                if (product == fc::bigint())
                    FC_THROW_EXCEPTION(price_multiplication_underflow, "price multiplication underflow");

                static fc::bigint bi_infinity = Price::infinite();

                // if the quotient is infinity or bigger, then we have a finite
                //    result that is too big to represent (overflow)
                if (product >= bi_infinity)
                    FC_THROW_EXCEPTION(price_multiplication_overflow, "price multiplication overflow");

                // NB we throw away the low bits, thus this function always rounds down

                Price result(fc::uint128(product),
                    l.base_asset_id, l.quote_asset_id);
                return result;
            } FC_CAPTURE_AND_RETHROW((l)(r))
        }

        Asset::operator std::string()const
        {
            return fc::to_string(amount);
        }

        Asset& Asset::operator += (const Asset& o)
        {
            try {
                FC_ASSERT(this->asset_id == o.asset_id, "", ("*this", *this)("o", o));

                if (((o.amount > 0) && (amount > (INT64_MAX - o.amount))) ||
                    ((o.amount < 0) && (amount < (INT64_MIN - o.amount))))
                {
                    FC_THROW_EXCEPTION(addition_overflow, "asset addition overflow  ${a} + ${b}",
                        ("a", *this)("b", o));
                }

                amount += o.amount;
                return *this;
            } FC_CAPTURE_AND_RETHROW((*this)(o))
        }

        Asset& Asset::operator -= (const Asset& o)
        {
            FC_ASSERT(asset_id == o.asset_id);

            if ((o.amount > 0 && amount < INT64_MIN + o.amount) ||
                (o.amount < 0 && amount > INT64_MAX + o.amount))
            {
                FC_THROW_EXCEPTION(subtraction_overflow, "asset subtraction underflow  ${a} - ${b}",
                    ("a", *this)("b", o));
            }

            amount -= o.amount;
            return *this;
        }

        const fc::uint128& Price::one()
        {
            static fc::uint128_t o = fc::uint128(1, 0);
            return o;
        }

        const fc::uint128& Price::infinite()
        {
            static fc::uint128 i(-1);
            return i;
        }

        bool Price::is_infinite() const
        {
            static fc::uint128 infinity = infinite();
            return (this->ratio == infinity);
        }

        Price::Price(const std::string& s)
        {
            try {
                int pos = set_ratio_from_string(s);
                std::stringstream ss(s.substr(pos));

                char div;
                ss >> quote_asset_id.value >> div >> base_asset_id.value;

                FC_ASSERT(quote_asset_id > base_asset_id, "${quote} > ${base}", ("quote", quote_asset_id)("base", base_asset_id));
            } FC_RETHROW_EXCEPTIONS(warn, "")
        }

        int Price::set_ratio_from_string(const std::string& ratio_str)
        {
            const char* c = ratio_str.c_str();
            int digit = *c - '0';
            if (digit >= 0 && digit <= 9)
            {
                uint64_t int_part = digit;
                ++c;
                digit = *c - '0';
                while (digit >= 0 && digit <= 9)
                {
                    int_part = int_part * 10 + digit;
                    ++c;
                    digit = *c - '0';
                }
                ratio = fc::uint128(int_part) * FC_REAL128_PRECISION;
            }
            else
            {
                // if the string doesn't look like "123.45" or ".45", this code isn't designed to parse it correctly
                // in particular, we don't try to handle leading whitespace or '+'/'-' indicators at the beginning
                assert(*c == '.');
                ratio = fc::uint128();
            }


            if (*c == '.')
            {
                c++;
                digit = *c - '0';
                if (digit >= 0 && digit <= 9)
                {
                    int64_t frac_part = digit;
                    int64_t frac_magnitude = 10;
                    ++c;
                    digit = *c - '0';
                    while (digit >= 0 && digit <= 9)
                    {
                        frac_part = frac_part * 10 + digit;
                        frac_magnitude *= 10;
                        ++c;
                        digit = *c - '0';
                    }
                    ratio += fc::uint128(frac_part) * (FC_REAL128_PRECISION / frac_magnitude);
                }
            }

            return c - ratio_str.c_str();
        }

        Price::Price(double a, AssetIdType q, AssetIdType b)
        {
            FC_ASSERT(q > b, "${quote} > ${base}", ("quote", q)("base", b));

            uint64_t high_bits = uint64_t(a);
            double fract_part = a - high_bits;
            //uint64_t low_bits = uint64_t(-1)*fract_part;
            //ratio = fc::uint128( high_bits, low_bits );
            ratio = (fc::uint128(high_bits) * FC_REAL128_PRECISION) + (int64_t((fract_part)* FC_REAL128_PRECISION));
            base_asset_id = b;
            quote_asset_id = q;
        }

        Price::operator double()const
        {
            return double(ratio.high_bits()) + double(ratio.low_bits()) / double(uint64_t(-1));
        }

        std::string Price::ratio_string()const
        {
            //std::string full_int = std::string( ratio );
            std::stringstream ss;
            ss << std::string(ratio / FC_REAL128_PRECISION);
            ss << '.';
            ss << std::string((ratio % FC_REAL128_PRECISION) + FC_REAL128_PRECISION).substr(1);

            auto number = ss.str();
            while (number.back() == '0') number.pop_back();

            return number;
        }

        Price::operator std::string()const
        {
            try {
                auto number = ratio_string();

                number += ' ' + fc::to_string(int64_t(quote_asset_id.value));
                number += '/' + fc::to_string(int64_t(base_asset_id.value));

                return number;
            } FC_RETHROW_EXCEPTIONS(warn, "")
        }


        /**
         *  A price will reorder the asset types such that the
         *  asset type with the lower enum value is always the
         *  denominator.  Therefore  cdcchain/usd and  usd/cdcchain will
         *  always result in a price measured in usd/cdcchain because
         *  asset::cdcchain <  asset::usd.
         */
        Price operator / (const Asset& a, const Asset& b)
        {
            try
            {
                if (a.asset_id == b.asset_id)
                    FC_CAPTURE_AND_THROW(asset_divide_by_self);

                Price p;
                auto l = a; auto r = b;
                if (l.asset_id < r.asset_id) { std::swap(l, r); }
                //ilog( "${a} / ${b}", ("a",l)("b",r) );

                if (r.amount == 0)
                    FC_CAPTURE_AND_THROW(asset_divide_by_zero, (r));

                p.base_asset_id = r.asset_id;
                p.quote_asset_id = l.asset_id;

                fc::bigint bl = l.amount;
                fc::bigint br = r.amount;
                fc::bigint result = (bl * fc::bigint(FC_REAL128_PRECISION)) / br;

                p.ratio = result;
                return p;
            } FC_RETHROW_EXCEPTIONS(warn, "${a} / ${b}", ("a", a)("b", b));
        }


        Asset operator / (const Asset& a, const Price& p)
        {
            return a * p;
        }

        /**
         *  Assuming a.type is either the numerator.type or denominator.type in
         *  the price equation, return the number of the other asset type that
         *  could be exchanged at price p.
         *
         *  ie:  p = 3 usd/cdcchain & a = 4 cdcchain then result = 12 usd
         *  ie:  p = 3 usd/cdcchain & a = 4 usd then result = 1.333 cdcchain
         */
        Asset operator * (const Asset& a, const Price& p)
        {
            try {
                if (a.asset_id == p.base_asset_id)
                {
                    fc::bigint ba(a.amount); // 64.64
                    fc::bigint r(p.ratio); // 64.64

                    auto amnt = ba * r; //  128.128
                    amnt /= FC_REAL128_PRECISION; // 128.64 
                    auto lg2 = amnt.log2();
                    if (lg2 >= 128)
                    {
                        FC_THROW_EXCEPTION(addition_overflow, "overflow ${a} * ${p}", ("a", a)("p", p));
                    }

                    Asset rtn;
                    rtn.amount = amnt.to_int64();
                    rtn.asset_id = p.quote_asset_id;

                    //ilog( "${a} * ${p} => ${rtn}", ("a", a)("p",p )("rtn",rtn) );
                    return rtn;
                }
                else if (a.asset_id == p.quote_asset_id)
                {
                    fc::bigint amt(a.amount); // 64.64
                    amt *= FC_REAL128_PRECISION; //<<= 64;  // 64.128
                    fc::bigint pri(p.ratio); // 64.64

                    auto result = amt / pri;  // 64.64
                    //            ilog( "amt: ${amt} / ${pri}", ("amt",string(amt))("pri",string(pri) ) );
                    //           ilog( "${r}", ("r",string(result) ) );

                    auto lg2 = result.log2();
                    if (lg2 >= 128)
                    {
                        //  wlog( "." );
                        FC_THROW_EXCEPTION(addition_overflow,
                            "overflow ${a} / ${p} = ${r} lg2 = ${l}",
                            ("a", a)("p", p)("r", std::string(result))("l", lg2));
                    }
                    //  result += 5000000000; // TODO: evaluate this rounding factor..
                    Asset r;
                    r.amount = result.to_int64();
                    r.asset_id = p.base_asset_id;
                    // ilog( "r.amount = ${r}", ("r",r.amount) );
                    // ilog( "${a} * ${p} => ${rtn}", ("a", a)("p",p )("rtn",r) );
                    return r;
                }
                FC_THROW_EXCEPTION(asset_type_mismatch, "type mismatch multiplying asset ${a} by price ${p}",
                    ("a", a)("p", p));
            } FC_RETHROW_EXCEPTIONS(warn, "type mismatch multiplying asset ${a} by price ${p}",
                ("a", a)("p", p));

        }

        Asset to_asset(AssetIdType asset_id, uint64_t asset_precision, double double_amount)
        {
            FC_ASSERT(double_amount >= 0, "double_amount should greater or equal than 0");

            Asset asset(0, asset_id);
            int add_zero_count = 0;

            uint64_t k = asset_precision;
            uint64_t m = 0;
            uint64_t zero_count = 0;
            while (k >= 10)
            {
                uint64_t t = k;
                k = t / 10;
                m = t % 10;
                FC_ASSERT(m == 0, "invalid asset precision");
                zero_count = zero_count + 1;
            }
            FC_ASSERT(k == 1, "invalid asset precision");
            
            char numbuf[1024];
            snprintf(numbuf, sizeof(numbuf), "%f", double_amount);
            std::string string_amount = string(numbuf);
            
            auto pos = string_amount.find_first_of(".");
            if (pos == -1)
                add_zero_count = zero_count;
            else
            {
                uint64_t t = string_amount.length() - pos - 1;
                std::string string_tmp;
                if (zero_count > t)
                {
                    string_tmp = string_amount.substr(0, pos) + string_amount.substr(pos + 1, t);
                    add_zero_count = zero_count - t;
                }
                else
                {
                    string_tmp = string_amount.substr(0, pos) + string_amount.substr(pos + 1, zero_count);
                }
                string_amount = string_tmp;
            }
            
            for (int i = 0; i < add_zero_count; ++i)
                string_amount = string_amount + "0";

            uint64_t asset_amount;
            std::stringstream stringstream_amount(string_amount);
            stringstream_amount >> asset_amount;
            asset.amount = asset_amount;

            return asset;
        }
    }
} // cdcchain::consensus

namespace fc
{

    /*
       void to_variant( const cdcchain::consensus::asset& var,  variant& vo )
       {
       vo = std::string(var);
       }
       void from_variant( const variant& var,  cdcchain::consensus::asset& vo )
       {
       vo = cdcchain::consensus::asset( var.as_string() );
       }
       */
    void to_variant(const cdcchain::consensus::Price& var, variant& vo)
    {
        fc::mutable_variant_object obj("ratio", var.ratio_string());
        obj("quote_asset_id", var.quote_asset_id);
        obj("base_asset_id", var.base_asset_id);
        vo = std::move(obj);
    }
    void from_variant(const variant& var, cdcchain::consensus::Price& vo)
    {
        auto obj = var.get_object();
        vo.set_ratio_from_string(obj["ratio"].as_string());
        from_variant(obj["quote_asset_id"], vo.quote_asset_id);
        from_variant(obj["base_asset_id"], vo.base_asset_id);
    }

} // fc
