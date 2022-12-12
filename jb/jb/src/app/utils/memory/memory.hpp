#pragma once

#include <cstdint>
#include <cstddef>

#include <Windows.h>

namespace memory
{
	std::uintptr_t findSignature(const char *module, const char *search);

	inline void *getVFunc(void *ptr, std::size_t index)
	{
		return reinterpret_cast<void *>((*static_cast<int **>(ptr))[index]);
	}

	inline std::uintptr_t relToAbs(std::uintptr_t address)
	{
		return *reinterpret_cast<std::uintptr_t *>(address + 1) + address + 5;
	}
}