#include "../utils/utils.hpp"

#include "settings.hpp"

MAKE_SIGNATURE(AttribHookValueInt, "server.dll", "E8 ? ? ? ? 83 C4 14 48", 0);
MAKE_SIGNATURE(no_self_blast_dmg_2nd_xref, "server.dll", "E8 ? ? ? ? 83 C4 14 85 C0 0F 95 45 F4", 5);
MAKE_SIGNATURE(no_self_blast_dmg_3rd_xref, "server.dll", "E8 ? ? ? ? 83 C4 14 89 45 E8 85 C0 74 10 68 ? ? ? ? E8 ? ? ? ?", 5);
MAKE_SIGNATURE(no_self_blast_dmg_4th_xref, "server.dll", "E8 ? ? ? ? 83 C4 14 89 45 E0 85 C0 74 10 68 ? ? ? ? E8 ? ? ? ? 83 C4 04", 5);

MAKE_HOOK(
	AttribHookValueInt, memory::relToAbs(signatures::AttribHookValueInt.m_address),
	int, __cdecl, int TValue, const char *pszAttribHook, void *pEntity, void *pItemList, bool bIsGlobalConstString)
{
	if (settings::no_damage)
	{
		static const auto no_self_blast_dmg{ HASH_CT("no_self_blast_dmg") };

		if (HASH_RT(pszAttribHook) == no_self_blast_dmg)
		{
			auto retaddr{ reinterpret_cast<std::uintptr_t>(_ReturnAddress()) };

			if (retaddr != signatures::no_self_blast_dmg_2nd_xref.m_address //to prevent blast jumping sound
				&& retaddr != signatures::no_self_blast_dmg_3rd_xref.m_address //to prevent custom sticky explosion effect
				&& retaddr != signatures::no_self_blast_dmg_4th_xref.m_address) //to prevent custom rocket explosion effect
			{
				return 2;
			}
		}
	}

	return CALL_ORIGINAL(TValue, pszAttribHook, pEntity, pItemList, bIsGlobalConstString);
}

MAKE_SIGNATURE(CMoveHelperServer_PlayerFallingDamage, "server.dll", "55 8B EC 83 EC 6C 56 8B F1 8B 0D ? ? ? ?", 0);

MAKE_HOOK(
	CMoveHelperServer_PlayerFallingDamage, signatures::CMoveHelperServer_PlayerFallingDamage.m_address,
	bool, __fastcall, void *ecx, void *edx)
{
	if (settings::no_damage)
	{
		return true;
	}

	return CALL_ORIGINAL(ecx, edx);
}