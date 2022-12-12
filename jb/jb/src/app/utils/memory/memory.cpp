#include "memory.hpp"

#define INRANGE(x, a, b) (x >= a && x <= b) 
#define GET_BITS(x) (INRANGE((x & (~0x20)),'A','F') ? ((x & (~0x20)) - 'A' + 0xA) : (INRANGE(x,'0','9') ? x - '0' : 0))
#define GET_BYTES(x) (GET_BITS(x[0]) << 4 | GET_BITS(x[1]))

std::uintptr_t memory::findSignature(const char *module, const char *search)
{
	auto findSignatureInternal = [&](std::uintptr_t address, std::size_t length, const char *search) -> std::uintptr_t
	{
		auto pattern{ search };
		std::uintptr_t first_match{ 0 };

		for (auto cur{ address }; cur < length; cur++)
		{
			if (!*pattern)
			{
				return first_match;
			}

			const auto byte_pattern{ *(BYTE *)pattern };

			if (byte_pattern == '\?' || *(BYTE *)cur == GET_BYTES(pattern))
			{
				if (!first_match)
				{
					first_match = cur;
				}

				if (!pattern[2])
				{
					return first_match;
				}

				if (byte_pattern == '\?\?' || byte_pattern != '\?')
				{
					pattern += 3;
				}

				else
				{
					pattern += 2;
				}
			}

			else
			{
				pattern = search;
				first_match = 0;
			}
		}

		return 0;
	};

	const auto mod{ reinterpret_cast<DWORD>(GetModuleHandleA(module)) };

	if (!mod)
	{
		return 0;
	}

	const auto nt{ reinterpret_cast<PIMAGE_NT_HEADERS>(mod + reinterpret_cast<PIMAGE_DOS_HEADER>(mod)->e_lfanew) };

	if (!nt)
	{
		return 0;
	}

	return findSignatureInternal(mod + nt->OptionalHeader.BaseOfCode, mod + nt->OptionalHeader.SizeOfCode, search);
}