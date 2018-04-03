// Copyright (c) 2017-2018 The CDC developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.


#include <assert.h>

#include <algorithm>

#include <fc/crypto/hex.hpp>
#include <fc/crypto/aes.hpp>
#include <fc/crypto/city.hpp>
#include <fc/log/logger.hpp>
#include <fc/network/ip.hpp>
#include <fc/exception/exception.hpp>

#include <network/StcpSocket.hpp>

namespace cdcchain {
    namespace network {

        StcpSocket::StcpSocket()
            //:_buf_len(0)
#ifndef NDEBUG
            : _read_buffer_in_use(false),
            _write_buffer_in_use(false)
#endif
        {
        }
        StcpSocket::~StcpSocket()
        {
        }

        void StcpSocket::do_key_exchange()
        {
            _priv_key = fc::ecc::private_key::generate();
            fc::ecc::public_key pub = _priv_key.get_public_key();
            fc::ecc::public_key_data s = pub.serialize();
            std::shared_ptr<char> serialized_key_buffer(new char[sizeof(fc::ecc::public_key_data)], [](char* p){ delete[] p; });
            memcpy(serialized_key_buffer.get(), (char*)&s, sizeof(fc::ecc::public_key_data));
            _sock.write(serialized_key_buffer, sizeof(fc::ecc::public_key_data));
            _sock.read(serialized_key_buffer, sizeof(fc::ecc::public_key_data));
            fc::ecc::public_key_data rpub;
            memcpy((char*)&rpub, serialized_key_buffer.get(), sizeof(fc::ecc::public_key_data));

            _shared_secret = _priv_key.get_shared_secret(rpub);
            //    ilog("shared secret ${s}", ("s", shared_secret) );
            _send_aes.init(fc::sha256::hash((char*)&_shared_secret, sizeof(_shared_secret)),
                fc::city_hash_crc_128((char*)&_shared_secret, sizeof(_shared_secret)));
            _recv_aes.init(fc::sha256::hash((char*)&_shared_secret, sizeof(_shared_secret)),
                fc::city_hash_crc_128((char*)&_shared_secret, sizeof(_shared_secret)));
        }


        void StcpSocket::connect_to(const fc::ip::endpoint& remote_endpoint)
        {
            _sock.connect_to(remote_endpoint);
            do_key_exchange();
        }

        void StcpSocket::bind(const fc::ip::endpoint& local_endpoint)
        {
            _sock.bind(local_endpoint);
        }

        /**
         *   This method must read at least 16 bytes at a time from
         *   the underlying TCP socket so that it can decrypt them. It
         *   will buffer any left-over.
         */
        size_t StcpSocket::readsome(char* buffer, size_t len)
        {
            try {
                assert(len > 0 && (len % 16) == 0);

#ifndef NDEBUG
                // This code was written with the assumption that you'd only be making one call to readsome 
                // at a time so it reuses _read_buffer.  If you really need to make concurrent calls to 
                // readsome(), you'll need to prevent reusing _read_buffer here
                struct check_buffer_in_use {
                    bool& _buffer_in_use;
                    check_buffer_in_use(bool& buffer_in_use) : _buffer_in_use(buffer_in_use) { assert(!_buffer_in_use); _buffer_in_use = true; }
                    ~check_buffer_in_use() { assert(_buffer_in_use); _buffer_in_use = false; }
                } buffer_in_use_checker(_read_buffer_in_use);
#endif

                const size_t read_buffer_length = 4096;
                if (!_read_buffer)
                    _read_buffer.reset(new char[read_buffer_length], [](char* p){ delete[] p; });

                len = std::min<size_t>(read_buffer_length, len);

                size_t s = _sock.readsome(_read_buffer, len, 0);
                if (s % 16)
                {
                    _sock.read(_read_buffer, 16 - (s % 16), s);
                    s += 16 - (s % 16);
                }
                _recv_aes.decode(_read_buffer.get(), s, buffer);
                return s;
            } FC_RETHROW_EXCEPTIONS(warn, "", ("len", len))
        }

        size_t StcpSocket::readsome(const std::shared_ptr<char>& buf, size_t len, size_t offset)
        {
            return readsome(buf.get() + offset, len);
        }

        bool StcpSocket::eof()const
        {
            return _sock.eof();
        }

        size_t StcpSocket::writesome(const char* buffer, size_t len)
        {
            try {
                assert(len > 0 && (len % 16) == 0);

#ifndef NDEBUG
                // This code was written with the assumption that you'd only be making one call to writesome
                // at a time so it reuses _write_buffer.  If you really need to make concurrent calls to 
                // writesome(), you'll need to prevent reusing _write_buffer here
                struct check_buffer_in_use {
                    bool& _buffer_in_use;
                    check_buffer_in_use(bool& buffer_in_use) : _buffer_in_use(buffer_in_use) { assert(!_buffer_in_use); _buffer_in_use = true; }
                    ~check_buffer_in_use() { assert(_buffer_in_use); _buffer_in_use = false; }
                } buffer_in_use_checker(_write_buffer_in_use);
#endif

                const std::size_t write_buffer_length = 4096;
                if (!_write_buffer)
                    _write_buffer.reset(new char[write_buffer_length], [](char* p){ delete[] p; });
                len = std::min<size_t>(write_buffer_length, len);
                memset(_write_buffer.get(), 0, len); // just in case aes.encode screws up
                /**
                 * every sizeof(crypt_buf) bytes the aes channel
                 * has an error and doesn't decrypt properly...  disable
                 * for now because we are going to upgrade to something
                 * better.
                 */
                uint32_t ciphertext_len = _send_aes.encode(buffer, len, _write_buffer.get());
                assert(ciphertext_len == len);
                _sock.write(_write_buffer, ciphertext_len);
                return ciphertext_len;
            } FC_RETHROW_EXCEPTIONS(warn, "", ("len", len))
        }

        size_t StcpSocket::writesome(const std::shared_ptr<const char>& buf, size_t len, size_t offset)
        {
            return writesome(buf.get() + offset, len);
        }

        void StcpSocket::flush()
        {
            _sock.flush();
        }


        void StcpSocket::close()
        {
            try
            {
                _sock.close();
            }FC_RETHROW_EXCEPTIONS(warn, "error closing stcp socket");
        }

        void StcpSocket::accept()
        {
            do_key_exchange();
        }


    }
} // namespace cdcchain::net

