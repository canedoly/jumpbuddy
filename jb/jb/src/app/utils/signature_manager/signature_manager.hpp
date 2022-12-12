#pragma once

#include "../memory/memory.hpp"

struct Signature
{
	std::uintptr_t m_address{ 0x0 };
	const char *m_dll{ nullptr };
	const char *m_sig{ nullptr };
	const char *m_name{ nullptr };
	unsigned int m_offset{ 0 };

	Signature(const char *dll, const char *sig, const char *name, unsigned int offset);
};

namespace signature_manager
{
	bool initialize();
}

#define MAKE_SIGNATURE(name, dll, sig, offset) namespace signatures { inline Signature name(dll, sig, #name, offset); }