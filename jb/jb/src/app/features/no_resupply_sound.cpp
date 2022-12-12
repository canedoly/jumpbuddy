#include "../utils/utils.hpp"

#include "settings.hpp"

MAKE_SIGNATURE(CBaseEntity_EmitSound, "server.dll", "E8 ? ? ? ? 83 C4 18 8D 4D 90", 0);

MAKE_HOOK(
	CBaseEntity_EmitSound, memory::relToAbs(signatures::CBaseEntity_EmitSound.m_address),
	void, __cdecl, void *filter, int iEntIndex, const char *soundname, void *pOrigin, float soundtime, float *duration)
{
	if (settings::no_resupply_sound)
	{
		static const auto TF_REGENERATE_SOUND{ HASH_CT("Regenerate.Touch") };

		if (HASH_RT(soundname) == TF_REGENERATE_SOUND)
		{
			return;
		}
	}

	CALL_ORIGINAL(filter, iEntIndex, soundname, pOrigin, soundtime, duration);
}