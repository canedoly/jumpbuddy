#pragma once

#include "../../libs/minhook/include/MinHook.h"

struct Hook
{
	void *m_originalfn{};
	void *m_initfn{};

	inline void create(void *src, void *dst)
	{
		MH_CreateHook(src, dst, &m_originalfn);
	}

	template <typename fn> inline fn original()
	{
		return reinterpret_cast<fn>(m_originalfn);
	}

	Hook(void *initfn);
};

namespace hook_manager
{
	bool initialize();
	bool free();
}

#define MAKE_HOOK(name, address, type, callconvo, ...) namespace hooks \
{\
	namespace name\
	{\
		void init(); \
		inline Hook hook(init); \
		using fn = type(callconvo *)(__VA_ARGS__); \
		type callconvo func(__VA_ARGS__); \
	}\
} \
void hooks::name::init() { hook.create(reinterpret_cast<void *>(address), reinterpret_cast<void *>(func)); } \
type callconvo hooks::name::func(__VA_ARGS__)

#define CALL_ORIGINAL hook.original<fn>()