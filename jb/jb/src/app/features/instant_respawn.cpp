#include "../utils/utils.hpp"

#include "settings.hpp"

MAKE_SIGNATURE(CTFPlayer_Event_Killed, "server.dll", "E8 ? ? ? ? 8B 8F ? ? ? ? 85 C9 74 62", 0);
MAKE_SIGNATURE(CTFPlayer_ForceRegenerateAndRespawn, "server.dll", "E9 ? ? ? ? 5E 5F C3 CC CC CC CC 55", 0);

MAKE_HOOK(
	CTFPlayer_Event_Killed, memory::relToAbs(signatures::CTFPlayer_Event_Killed.m_address),
	void, __fastcall, void *ecx, void *edx, void *info)
{
	if (settings::instant_respawn && ecx)
	{
		reinterpret_cast<void(__thiscall *)(void *)>(memory::relToAbs(signatures::CTFPlayer_ForceRegenerateAndRespawn.m_address))(ecx);

		return;
	}

	CALL_ORIGINAL(ecx, edx, info);
}