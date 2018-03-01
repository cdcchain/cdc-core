#pragma once

namespace cdcchain {
    namespace utilities {

        template<size_t BlockSize = 16, char PaddingChar = ' '>
        class PaddingOstream : public fc::buffered_ostream {
        public:
            PaddingOstream(fc::ostream_ptr o, size_t bufsize = 4096) : buffered_ostream(o, bufsize) {}
            virtual ~PaddingOstream() {}

            virtual size_t writesome(const char* buffer, size_t len) {
                auto out = buffered_ostream::writesome(buffer, len);
                bytes_out += out;
                bytes_out %= BlockSize;
                return out;
            }
            virtual size_t writesome(const std::shared_ptr<const char>& buf, size_t len, size_t offset) {
                auto out = buffered_ostream::writesome(buf, len, offset);
                bytes_out += out;
                bytes_out %= BlockSize;
                return out;
            }
            virtual void flush() {
                static const char pad = PaddingChar;
                while (bytes_out % BlockSize)
                    writesome(&pad, 1);
                buffered_ostream::flush();
            }

        private:
            size_t bytes_out = 0;
        };

    }
} //cdcchain::utilities

