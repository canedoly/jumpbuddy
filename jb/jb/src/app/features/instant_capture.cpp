#include "../utils/utils.hpp"

#include "settings.hpp"

MAKE_SIGNATURE(CTriggerAreaCapture_CaptureThink, "server.dll", "E8 ? ? ? ? 80 BF ? ? ? ? ? C6 87 ? ? ? ? ?", 0);

MAKE_HOOK(
	CTriggerAreaCapture_CaptureThink, memory::relToAbs(signatures::CTriggerAreaCapture_CaptureThink.m_address),
	void, __fastcall, void *ecx, void *edx)
{
	if (settings::instant_capture && ecx)
	{
		//CTriggerAreaCapture::m_flCapTime
		*reinterpret_cast<float *>(reinterpret_cast<std::uintptr_t>(ecx) + 1216) = 0.0f;
	}

	CALL_ORIGINAL(ecx, edx);
}