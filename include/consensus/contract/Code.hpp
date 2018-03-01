#pragma  once

#include <consensus/Types.hpp>
#include <consensus/contract/StorageTypes.hpp>
#include <consensus/WithdrawTypes.hpp>
#include <fc/optional.hpp>
#include <string>
#include <vector>
#include <set>

using namespace cdcchain::consensus;

#define PRINTABLE_CHAR(chr) \
if (chr >= 0 && chr <= 9)  \
    chr = chr + '0'; \
else \
    chr = chr + 'a' - 10; 


namespace uvm {
	namespace blockchain {

		using uvm::blockchain::StorageValueTypes;

		//the code-related detail of contract
		struct Code
		{
			std::set<std::string> abi;
			std::set<std::string> offline_abi;
			std::set<std::string> events;
			std::map<std::string, fc::enum_type<fc::unsigned_int, StorageValueTypes>> storage_properties;
			std::vector<ContractChar> byte_code;
			std::string code_hash;
			Code(const fc::path&);
			Code();
			void SetApis(char* module_apis[], int count, int api_type);
			bool valid() const;
			std::string GetHash() const;
		};

		inline std::string to_printable_hex(unsigned char chr)
		{
			unsigned char high = chr >> 4;
			unsigned char low = chr & 0x0F;
			char tmp[16];

			PRINTABLE_CHAR(high);
			PRINTABLE_CHAR(low);

			snprintf(tmp, sizeof(tmp), "%c%c", high, low);
			return string(tmp);
		}

		struct CodePrintAble
		{
			std::set<std::string> abi;
			std::set<std::string> offline_abi;
			std::set<std::string> events;
			std::map<std::string, std::string> printable_storage_properties;
			std::string printable_code;
			std::string code_hash;

			CodePrintAble() {}

			CodePrintAble(const Code& code) : abi(code.abi), offline_abi(code.offline_abi), events(code.events), code_hash(code.code_hash)
			{
				unsigned char* code_buf = (unsigned char*)malloc(code.byte_code.size());
				FC_ASSERT(code_buf, "malloc failed");

				for (int i = 0; i < code.byte_code.size(); ++i)
				{
					code_buf[i] = code.byte_code[i];
					printable_code = printable_code + to_printable_hex(code_buf[i]);
				}

				for (const auto& storage_info : code.storage_properties)
				{
					std::string storage_type = "unknown type";
					auto iter = storage_type_map.find(storage_info.second);
					if (iter != storage_type_map.end())
						storage_type = iter->second;

					printable_storage_properties.insert(make_pair(storage_info.first, storage_type));
				}

				free(code_buf);
			}
		};

	}
}


FC_REFLECT(uvm::blockchain::Code,
(abi)
(offline_abi)
(events)
(storage_properties)
(byte_code)
(code_hash)
)

FC_REFLECT(uvm::blockchain::CodePrintAble,
(abi)
(offline_abi)
(events)
(printable_storage_properties)
(printable_code)
(code_hash)
)