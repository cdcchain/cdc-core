
#include <consensus/contract/Code.hpp>

#include <consensus/chainstate/ChainInterface.hpp>
#include <consensus/Types.hpp>
#include <consensus/Exceptions.hpp>

#include <fc/array.hpp>
#include <fc/crypto/ripemd160.hpp>
#include <fc/crypto/elliptic.hpp>
#include <fc/crypto/base58.hpp>

#include <utilities/CommonApi.hpp>



#define INIT_API_FROM_FILE(dst_set, except_1, except_2, except_3)\
{\
read_count = cdcchain::utilities::common_fread_int(f, &api_count); \
if (read_count != 1)\
{\
fclose(f); \
throw except_1(); \
}\
for (int i = 0; i < api_count; i++)\
{\
int api_len = 0; \
read_count = cdcchain::utilities::common_fread_int(f, &api_len); \
if (read_count != 1)\
{\
fclose(f); \
throw except_2(); \
}\
api_buf = (char*)malloc(api_len + 1); \
if (api_buf == NULL) \
{ \
fclose(f); \
FC_ASSERT(api_buf == NULL, "malloc fail!"); \
}\
read_count = cdcchain::utilities::common_fread_octets(f, api_buf, api_len); \
if (read_count != 1)\
{\
fclose(f); \
free(api_buf); \
throw except_3(); \
}\
api_buf[api_len] = '\0'; \
dst_set.insert(std::string(api_buf)); \
free(api_buf); \
}\
}

#define INIT_STORAGE_FROM_FILE(dst_map, except_1, except_2, except_3, except_4)\
{\
read_count = cdcchain::utilities::common_fread_int(f, &storage_count); \
if (read_count != 1)\
{\
fclose(f); \
throw except_1(); \
}\
for (int i = 0; i < storage_count; i++)\
{\
int storage_name_len = 0; \
read_count = cdcchain::utilities::common_fread_int(f, &storage_name_len); \
if (read_count != 1)\
{\
fclose(f); \
throw except_2(); \
}\
storage_buf = (char*)malloc(storage_name_len + 1); \
if (storage_buf == NULL) \
{ \
fclose(f); \
FC_ASSERT(storage_buf == NULL, "malloc fail!"); \
}\
read_count = cdcchain::utilities::common_fread_octets(f, storage_buf, storage_name_len); \
if (read_count != 1)\
{\
fclose(f); \
free(storage_buf); \
throw except_3(); \
}\
storage_buf[storage_name_len] = '\0'; \
read_count = cdcchain::utilities::common_fread_int(f, (int*)&storage_type); \
if (read_count != 1)\
{\
fclose(f); \
free(storage_buf); \
throw except_4(); \
}\
dst_map.insert(std::make_pair(std::string(storage_buf), storage_type)); \
free(storage_buf); \
}\
}

namespace uvm {
	namespace blockchain {

		Code::Code(const fc::path& path)
		{
			if (!fc::exists(path))
				FC_THROW_EXCEPTION(fc::file_not_found_exception, "Script file not found!");

			string file = path.string();
			FILE* f = fopen(file.c_str(), "rb");
			fseek(f, 0, SEEK_END);
			int fsize = ftell(f);
			fseek(f, 0, SEEK_SET);

			unsigned int digest[5];
			int read_count = 0;
			for (int i = 0; i < 5; ++i)
			{
				read_count = cdcchain::utilities::common_fread_int(f, (int*)&digest[i]);
				if (read_count != 1)
				{
					fclose(f);
					FC_THROW_EXCEPTION(cdcchain::consensus::read_verify_code_fail, "Read verify code fail!");
				}
			}

			int len = 0;
			read_count = cdcchain::utilities::common_fread_int(f, &len);
			if (read_count != 1 || len < 0 || (len >= (fsize - ftell(f))))
			{
				fclose(f);
				FC_THROW_EXCEPTION(cdcchain::consensus::read_bytescode_len_fail, "Read bytescode len fail!");
			}

			byte_code.resize(len);
			read_count = cdcchain::utilities::common_fread_octets(f, byte_code.data(), len);
			if (read_count != 1)
			{
				fclose(f);
				FC_THROW_EXCEPTION(cdcchain::consensus::read_bytescode_fail, "Read bytescode fail!");
			}

			boost::uuids::detail::sha1 sha;
			unsigned int check_digest[5];
			sha.process_bytes(byte_code.data(), byte_code.size());
			sha.get_digest(check_digest);
			if (memcmp((void*)digest, (void*)check_digest, sizeof(unsigned int) * 5))
			{
				fclose(f);
				FC_THROW_EXCEPTION(cdcchain::consensus::verify_bytescode_sha1_fail, "Verify bytescode SHA1 fail!");
			}

			for (int i = 0; i < 5; ++i)
			{
				unsigned char chr1 = (check_digest[i] & 0xFF000000) >> 24;
				unsigned char chr2 = (check_digest[i] & 0x00FF0000) >> 16;
				unsigned char chr3 = (check_digest[i] & 0x0000FF00) >> 8;
				unsigned char chr4 = (check_digest[i] & 0x000000FF);

				code_hash = code_hash + to_printable_hex(chr1) + to_printable_hex(chr2) +
					to_printable_hex(chr3) + to_printable_hex(chr4);
			}

			int api_count = 0;
			char* api_buf = nullptr;

			INIT_API_FROM_FILE(abi, read_api_count_fail, read_api_len_fail, read_api_fail);
			INIT_API_FROM_FILE(offline_abi, read_offline_api_count_fail, read_offline_api_len_fail, read_offline_api_fail);
			INIT_API_FROM_FILE(events, read_events_count_fail, read_events_len_fail, read_events_fail);

			int storage_count = 0;
			char* storage_buf = nullptr;
			StorageValueTypes storage_type;

			INIT_STORAGE_FROM_FILE(storage_properties, read_storage_count_fail, read_storage_name_len_fail, read_storage_name_fail, read_storage_type_fail);

			fclose(f);
		}
		std::string Code::GetHash() const
		{
			std::string hashstr = "";
			boost::uuids::detail::sha1 sha;
			unsigned int check_digest[5];
			sha.process_bytes(byte_code.data(), byte_code.size());
			sha.get_digest(check_digest);
			for (int i = 0; i < 5; ++i)
			{
				unsigned char chr1 = (check_digest[i] & 0xFF000000) >> 24;
				unsigned char chr2 = (check_digest[i] & 0x00FF0000) >> 16;
				unsigned char chr3 = (check_digest[i] & 0x0000FF00) >> 8;
				unsigned char chr4 = (check_digest[i] & 0x000000FF);

				hashstr = hashstr + to_printable_hex(chr1) + to_printable_hex(chr2) +
					to_printable_hex(chr3) + to_printable_hex(chr4);
			}
			return hashstr;
		}
		Code::Code()
		{

		}

		void Code::SetApis(char* module_apis[], int count, int api_type)
		{
			if (api_type == ContractApiType::chain)
			{
				abi.clear();
				for (int i = 0; i < count; i++)
					abi.insert(module_apis[i]);
			}
			else if (api_type == ContractApiType::offline)
			{
				offline_abi.clear();
				for (int i = 0; i < count; i++)
					offline_abi.insert(module_apis[i]);
			}
			else if (api_type == ContractApiType::event)
			{
				events.clear();
				for (int i = 0; i < count; i++)
					events.insert(module_apis[i]);
			}
		}

		bool Code::valid() const
		{
			//FC_ASSERT(0);
			//return false;
			return true;
		}

	}
}