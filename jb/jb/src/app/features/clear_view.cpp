#include "../utils/utils.hpp"

#include "settings.hpp"

MAKE_SIGNATURE(CBasePlayer_CalcPlayerView, "client.dll", "E8 ? ? ? ? 8B CE E8 ? ? ? ? 84 C0 74 15", 0);

MAKE_HOOK(
	CBasePlayer_CalcPlayerView, memory::relToAbs(signatures::CBasePlayer_CalcPlayerView.m_address),
	void, __fastcall, void *ecx, void *edx, float *eyeOrigin, float *eyeAngles, float &fov)
{
	if (settings::clear_view && ecx)
	{
		//CBasePlayer::m_vecPunchAngle
		auto &punch{ *reinterpret_cast<float *>(reinterpret_cast<std::uintptr_t>(ecx) + (3724 + 8)) };

		auto old_punch{ punch };

		punch = 0.0f;

		CALL_ORIGINAL(ecx, edx, eyeOrigin, eyeAngles, fov);

		punch = old_punch;

		return;
	}

	CALL_ORIGINAL(ecx, edx, eyeOrigin, eyeAngles, fov);
}

MAKE_SIGNATURE(CViewEffects_Shake, "client.dll", "55 8B EC 56 8B 75 08 57 8B F9 8B 06", 0);

MAKE_HOOK(
	CViewEffects_Shake, signatures::CViewEffects_Shake.m_address,
	void, __fastcall, void *ecx, void *edx, void *data)
{
	if (settings::clear_view)
	{
		return;
	}

	CALL_ORIGINAL(ecx, edx, data);
}