#include "../utils/utils.hpp"

#include "settings.hpp"

MAKE_SIGNATURE(CHudDamageIndicator_ShouldDraw, "client.dll", "56 8B F1 E8 ? ? ? ? 84 C0 75 02 5E C3 83 BE ? ? ? ? ?", 0);

MAKE_HOOK(
	CHudDamageIndicator_ShouldDraw, signatures::CHudDamageIndicator_ShouldDraw.m_address,
	bool, __fastcall, void *ecx, void *edx)
{
	if (settings::no_damage_indicator)
	{
		return false;
	}

	return CALL_ORIGINAL(ecx, edx);
}