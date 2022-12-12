#include "signature_manager.hpp"

#include "../memory/memory.hpp"

#include <vector>

std::vector<Signature *> signatures{};

Signature::Signature(const char *dll, const char *sig, const char *name, unsigned int offset)
{
	m_dll = dll;
	m_sig = sig;
	m_name = name;
	m_offset = offset;

	signatures.push_back(this);
}

bool signature_manager::initialize()
{
	for (const auto &signature : signatures)
	{
		signature->m_address = memory::findSignature(signature->m_dll, signature->m_sig);

		if (!signature->m_address)
		{
			return false;
		}

		signature->m_address += signature->m_offset;
	}

	return true;
}