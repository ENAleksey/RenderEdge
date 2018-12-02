#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

#include "JassApi.h"
#include "GameUI.h"
#include "Input.h"
#include <stdio.h>
#include "Storm.h"
#include "ResourceManager.h"
#include "RenderingHook.h"
#include "Camera.h"

#include "MultiWindow.h"
#include "GameOffsets.h"
#include "fp_call.h"
#include "d3d8to9.hpp"
#include "Detour.h"
#include "Engine.h"
#include "Log.h"

#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")
#pragma comment(lib, "libjpeg.lib")
#pragma comment(lib, "detours.lib")
#pragma comment(lib, "freetype.lib")
#pragma comment(lib, "Version.lib")


template <typename Type>
void SetGameValue(uintptr_t addres, Type value)
{
	DWORD dwOldProtect;
	if (VirtualProtect((LPVOID*)addres, sizeof(Type), PAGE_EXECUTE_READWRITE, &dwOldProtect))
		*(Type*)(LPVOID*)addres = value;
}

void PatchMemory(uintptr_t pAddress, uint8* bytes, uint32 size)
{
	void* address = reinterpret_cast<void*>(pAddress);

	unsigned long Protection;
	VirtualProtect(address, size, PAGE_READWRITE, &Protection);
	memcpy(address, (const void*)bytes, size);
	VirtualProtect(address, size, Protection, &Protection);
}


bool ReadConfigs()
{
	LOG(INFO) << "Reading settings from 'HKEY_CURRENT_USER\\Software\\RenderEdge'...";

	DWORD dwTemp = registry::GetDword("Software\\RenderEdge", "Debug");
	if (dwTemp == -1)
	{
		LOG(ERROR) << "> Failed to read 'Debug' value!";
		return false;
	}
	Log::bDebug = (dwTemp == 1);

	dwTemp = registry::GetDword("Software\\RenderEdge", "AllowLocalFiles");
	if (dwTemp == -1)
	{
		LOG(ERROR) << "> Failed to read 'AllowLocalFiles' value!";
		return false;
	}
	CResourceManager::bAllowLocalFiles = (dwTemp == 1);

	LOG(INFO) << "> Success!";

	return true;
}

uint32 GetGameBuildVersion()
{
	DWORD dwHandle;
	DWORD sz = GetFileVersionInfoSizeA("Game.dll", &dwHandle);
	if (sz == 0)
	{
		return 0;
	}

	char* buf = new char[sz];
	if (!GetFileVersionInfoA("Game.dll", dwHandle, sz, &buf[0]))
	{
		delete buf;
		return 0;
	}

	VS_FIXEDFILEINFO* pvi;
	sz = sizeof(VS_FIXEDFILEINFO);
	if (!VerQueryValueA(&buf[0], "\\", (LPVOID*)&pvi, (unsigned int*)&sz))
	{
		delete buf;
		return 0;
	}
	delete buf;

	return pvi->dwFileVersionLS & 0xFFFF;
}


Direct3D8* WINAPI Direct3DCreate8_proxy(UINT SDKVersion)
{
	//LOG(DEBUG) << "Redirecting 'Direct3DCreate8(" << SDKVersion << ")'";

	IDirect3D9* const d3d = Direct3DCreate9(D3D_SDK_VERSION);

	if (d3d == nullptr)
	{
		LOG(WARNING) << "'Direct3DCreate9' failed!";
		return nullptr;
	}

	return new Direct3D8(d3d);
}

bool HookDirect3DCreate8()
{
	bool bResult = false;

	HMODULE hModule = LoadLibraryW(L"d3d8.dll");
	if (!hModule)
		return bResult;

	uintptr_t address_Direct3DCreate8 = (uintptr_t)GetProcAddress(hModule, "Direct3DCreate8");
	if (address_Direct3DCreate8)
		bResult = Detour::Install(&address_Direct3DCreate8, (uintptr_t)Direct3DCreate8_proxy);

	if (hModule)
		FreeLibrary(hModule);

	return bResult;
}


BOOL WINAPI DllMain(HINSTANCE module_handle, DWORD reason_for_call, LPVOID reserved)
{
	if (reason_for_call == DLL_PROCESS_ATTACH)
	{
		RenderEdgePath = utils::GetModulePath(module_handle);

		if (!Log::Open(RenderEdgePath + "RenderEdge.log"))
			ExitMessage("Failed to create log file!");

		const uint32 gameBuildVersion = GetGameBuildVersion();

		LOG(INFO) << "RenderEdge path:  " << RenderEdgePath;
		LOG(INFO) << "WarCraft path:    " << utils::GetModulePath(nullptr);
		LOG(INFO) << "WarCraft version: " << gameBuildVersion;

		if (gameBuildVersion != 6401)
		{
			LOG(ERROR) << "> Unsupported WarCraft version!";
			ExitMessage("RenderEdge supports only 1.26a patch!");
		}

		if (!ReadConfigs())
		{
			LOG(ERROR) << "> Failed to read settings from Registry Editor!";
			ExitMessage("Failed to read settings from Registry Editor!");
		}

		if (!HookDirect3DCreate8())
		{
			LOG(ERROR) << "Failed to hook 'Direct3DCreate8'!";
			ExitMessage("Failed to hook Direct3DCreate8!");
		}

		InitGameOffsets(gameBuildVersion);

		if (!MultiWindow::Init())
			LOG(ERROR) << "Failed to init Muti Window!";

		if (!Storm::Init())
			LOG(ERROR) << "Failed to init Storm API!";

		if (!Jass::Init())
			LOG(ERROR) << "Failed to init Jass API!";

		if (!RenderingHook::Init())
			LOG(ERROR) << "Failed to init Rendering Hook!";

		if (!Input::Init())
			LOG(ERROR) << "Failed to init Input System!";

		// Unlock FPS
		uint8 bytes0[] = { 0xFF };
		PatchMemory(address_LockFPS, bytes0, 1);

		// Unlock BLP Texture Size
		uint8 bytes1[] = { 0x3D, 0x00, 0x80 };
		uint8 bytes2[] = { 0xB8, 0x00, 0x80 };
		PatchMemory(address_LockTextureSizeCmp, bytes1, 3);
		PatchMemory(address_LockTextureSizeMov, bytes2, 3);

		// Change Local Game Delay
		SetGameValue(address_localDelay, 10);
	}
	else if (reason_for_call == DLL_PROCESS_DETACH)
	{

	}

	return TRUE;
}