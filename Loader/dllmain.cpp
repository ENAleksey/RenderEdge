#define WIN32_LEAN_AND_MEAN

#include <windows.h>
#include <string>
#include "Hook/fp_call.h"
#include "Hook/iat.h"


uintptr_t address_LoadLibraryA = 0;
std::wstring RenderEdgePath;

void Message(const std::wstring& msg)
{
	MessageBoxW(nullptr, msg.c_str(), L"RenderEdge_loader.dll", MB_OK | MB_ICONERROR | MB_TOPMOST);
}

bool FileExists(const std::wstring& fileName)
{
	return GetFileAttributesW(fileName.c_str()) != DWORD(-1);
}

std::wstring GetModulePath(HMODULE hModule)
{
	wchar_t path[MAX_PATH];
	GetModuleFileNameW(hModule, path, sizeof(path));
	std::wstring filePath = path;

	size_t pos = filePath.rfind('\\');
	if (pos == std::wstring::npos)
		return L"";

	return filePath.substr(0, pos + 1);
}

HMODULE LoadDll(const std::wstring& patch)
{
	HMODULE hModule = nullptr;

	if (FileExists(patch.c_str()))
	{
		hModule = LoadLibraryW(patch.c_str());
		if (!hModule)
		{
			Message(L"Failed to load:\n" + patch);
		}
	}
	else
	{
		Message(L"File not found:\n" + patch);
	}

	return hModule;
}


HMODULE __stdcall LoadLibraryA_proxy(LPCSTR lpFilePath)
{
	if (strcmp(lpFilePath, "Game.dll") == 0)
	{
		HMODULE hGameDll = LoadLibraryW(L"Game.dll");

		if (!hGameDll)
		{
			return nullptr;
		}

		std::wstring path = RenderEdgePath + L"RenderEdge_exp.dll";
		if (FileExists(path.c_str()))
		{
			LoadDll(RenderEdgePath + L"AntTweakBar.dll");
			if (!LoadLibraryW(path.c_str()))
			{
				Message(L"Failed to load:\n" + path);
			}
		}
		else
		{
			LoadDll(RenderEdgePath + L"RenderEdge.dll");
		}

		return hGameDll;
	}

	return std_call<HMODULE>(address_LoadLibraryA, lpFilePath);
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD  ul_reason_for_call, LPVOID lpReserved)
{
	if (ul_reason_for_call == DLL_PROCESS_ATTACH)
	{
		DisableThreadLibraryCalls(hModule);

		RenderEdgePath = GetModulePath(hModule);
		address_LoadLibraryA = hook::iat(L"war3.exe", "kernel32.dll", "LoadLibraryA", (uintptr_t)LoadLibraryA_proxy);
	}
	else if (ul_reason_for_call == DLL_PROCESS_DETACH)
	{

	}

	return TRUE;
}