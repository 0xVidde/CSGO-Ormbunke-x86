#include "hooks.h" 
#include "Hack.h"

#ifdef _WIN64
#define GWL_WNDPROC GWLP_WNDPROC
#endif


void MainThread(HMODULE hMod)
{
	hooks::Init();
	Hack::Init();

	FreeLibraryAndExitThread(hMod, 1);
}

BOOL WINAPI DllMain(HMODULE hMod, DWORD dwReason, LPVOID lpReserved)
{
	switch (dwReason)
	{
	case DLL_PROCESS_ATTACH:
		CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE)MainThread, hMod, 0, nullptr);
		break;
	case DLL_PROCESS_DETACH:
		break;
	}
	return TRUE;
}

