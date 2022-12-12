#include "app/app.hpp"

#define UNLOAD_KEY VK_F11

DWORD WINAPI mainThread(LPVOID param)
{
	if (!app::load())
	{
		MBOX("jumpbuddy failed to load");

		FreeLibraryAndExitThread(reinterpret_cast<HMODULE>(param), EXIT_SUCCESS);
	}

	while (!GetAsyncKeyState(UNLOAD_KEY))
	{
		Sleep(500);
	}
	
	if (!app::unload())
	{
		MBOX("jumpbuddy failed to unload");

		FreeLibraryAndExitThread(reinterpret_cast<HMODULE>(param), EXIT_SUCCESS);
	}

	Sleep(500);

	FreeLibraryAndExitThread(reinterpret_cast<HMODULE>(param), EXIT_SUCCESS);
}

BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpReserved)
{
    if (fdwReason != DLL_PROCESS_ATTACH)
    {
        return TRUE;
    }

	auto main_thread{ CreateThread(0, 0, mainThread, hinstDLL, 0, 0) };

	if (!main_thread)
	{
		return TRUE;
	}

	CloseHandle(main_thread);
	
    return TRUE;
}