#include "../utils/utils.hpp"

#include "settings.hpp"

MAKE_SIGNATURE(C_TFPlayer_OverrideView, "client.dll", "55 8B EC 83 EC 0C 56 FF 75 08 8B F1 E8 ? ? ? ? FF B6 ? ? ? ?", 0);

MAKE_HOOK(
	C_TFPlayer_OverrideView, signatures::C_TFPlayer_OverrideView.m_address,
	void, __fastcall, void *ecx, void *edx, void *pSetup)
{
	if (settings::custom_fov && ecx && pSetup)
	{
		//CBasePlayer::m_iFOV
		*reinterpret_cast<int *>(reinterpret_cast<std::uintptr_t>(ecx) + 4412) = settings::custom_fov;

		//CViewSetup::fov
		*reinterpret_cast<float *>(reinterpret_cast<std::uintptr_t>(pSetup) + 56) = static_cast<float>(settings::custom_fov);
	}

	CALL_ORIGINAL(ecx, edx, pSetup);
}