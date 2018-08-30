#include <SDKDDKVer.h>
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <sstream>

#include "fp_call.h"
#include "iat.h"

char current_dir[300];

void Message(const std::string & msg)
{
	MessageBoxA(nullptr, msg.c_str(), "RenderEdge_loader.dll", MB_OK | MB_ICONERROR);
}


bool FileExists(const char* fname)
{
	return GetFileAttributesA(fname) != DWORD(-1);
}

void LoadDll(const std::string& patch)
{
	if (FileExists(patch.c_str()))
	{
		if (!LoadLibraryA(patch.c_str()))
			Message("Failed to load:\n" + patch);
	}
	else
		Message("File not found:\n" + patch);
}


HMODULE hGameDll = 0;
uintptr_t RealLoadLibraryA = 0;
HMODULE __stdcall FakeLoadLibraryA(LPCSTR lpFilePath)
{
	if (strcmp(lpFilePath, "Game.dll") == 0)
	{
		if (!hGameDll)
		{
			hGameDll = ::LoadLibraryA("Game.dll");
			if (!hGameDll)
			{
				hGameDll = ::LoadLibraryA("Game.dll");
				if (!hGameDll)
				{
					return hGameDll;
				}
			}



			std::string patch = std::string(current_dir) + "RenderEdge_exp.dll";
			if (FileExists(patch.c_str()))
			{
				LoadDll(std::string(current_dir) + "AntTweakBar.dll");
				if (!LoadLibraryA(patch.c_str()))
					Message("Failed to load:\n" + patch);
			}
			else
				LoadDll(std::string(current_dir) + "RenderEdge.dll");


			/*std::string patch = std::string(current_dir) + "AntTweakBar.dll";
			if (FileExists(patch.c_str()))
			{
				if (!LoadLibraryA(patch.c_str()))
					Message("Failed to load:\n" + patch);
			}

			LoadDll(std::string(current_dir) + "RenderEdge.dll");*/

			return hGameDll;
		}
	}

	return std_call<HMODULE>(RealLoadLibraryA, lpFilePath);
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD  ul_reason_for_call, LPVOID lpReserved)
{
	if (ul_reason_for_call == DLL_PROCESS_ATTACH)
	{
		DisableThreadLibraryCalls(hModule);

		int pp[3];
		char p1[300], p2[300], *p3;
		GetModuleFileNameA(hModule, p1, sizeof(p1));
		GetFullPathNameA(p1, sizeof(p2), p2, &p3);
		pp[1] = lstrlenA(p2);
		pp[2] = lstrlenA(p3);
		pp[0] = pp[1] - pp[2] + 1;
		lstrcpynA(current_dir, p2, pp[0]);

		RealLoadLibraryA = base::hook::iat(L"war3.exe", "kernel32.dll", "LoadLibraryA", (uintptr_t)FakeLoadLibraryA);
	}

	return TRUE;
}

