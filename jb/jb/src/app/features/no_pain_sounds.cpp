#include "../utils/utils.hpp"

#include "settings.hpp"

MAKE_SIGNATURE(CTFPlayer_PainSound, "server.dll", "E8 ? ? ? ? 8B 07 8B CF 8B 80 ? ? ? ? FF D0 89 45 DC", 0);

MAKE_HOOK(
	CTFPlayer_PainSound, memory::relToAbs(signatures::CTFPlayer_PainSound.m_address),
	void, __fastcall, void *ecx, void *edx, void *info)
{
	if (settings::no_pain_sounds)
	{
		return;
	}

	CALL_ORIGINAL(ecx, edx, info);
}

MAKE_SIGNATURE(CTFPlayer_DeathSound, "server.dll", "55 8B EC 51 57 8B F9 8D 87 ? ? ? ? 85 C0 74 0F", 0);

MAKE_HOOK(
	CTFPlayer_DeathSound, signatures::CTFPlayer_DeathSound.m_address,
	void, __fastcall, void *ecx, void *edx, void *info)
{
	if (settings::no_pain_sounds)
	{
		return;
	}

	CALL_ORIGINAL(ecx, edx, info);
}