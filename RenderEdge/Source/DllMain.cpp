#include <SDKDDKVer.h>
#define WIN32_LEAN_AND_MEAN
#include <windows.h>

#pragma comment( lib, "d3d9.lib" )
#pragma comment( lib, "d3dx9.lib" )
#pragma comment( lib, "detours.lib" )
#pragma comment( lib, "freetype.lib" )
#pragma comment( lib, "libjpeg.lib" )
#pragma comment( lib, "psapi.lib" )

#include <fstream>

#include "fp_call.h"
#include "dyn_iat.h"
#include "Input.h"
#include "GameHook.h"
#include "Storm.h"
#include "JassApi.h"
#include "iat.h"
#include "Utils.h"
#include "Log.h"
#include "inline.h"

#include "Engine.h"
#include "GameOffsets.h"

#include "int_t.h"

#include "d3d8to9.hpp"
//#include "d3d9.hpp"


template <typename Type> void SetGameValue(uintptr_t addres, Type value)
{
	SetValueFromMemory(address_GameBase + addres, value);
}

template <typename Type> void SetGameValuePtr(uintptr_t addres, Type value)
{
	SetValueFromMemory(address_GameBase + addres, (uintptr_t)(new Type(value)));
}


Direct3D8* WINAPI Direct3DCreate8_proxy(UINT SDKVersion)
{
	LOG(logDEBUG) << "Redirecting 'Direct3DCreate8(" << SDKVersion << ")'...";

	IDirect3D9 *const d3d = Direct3DCreate9(D3D_SDK_VERSION);

	if (d3d == nullptr)
		return nullptr;

	return new Direct3D8(d3d);
}

//IDirect3D9* WINAPI Direct3DCreate9_proxy(UINT SDKVersion)
//{
//	LOG(logDEBUG) << "Redirecting 'Direct3DCreate9(" << SDKVersion << ")'...";
//
//	IDirect3D9 *const d3d = Direct3DCreate9(D3D_SDK_VERSION);
//
//	if (d3d == nullptr)
//		return nullptr;
//
//	return new Direct3D9(d3d);
//}



bool ChangeDelay(uint32 singlePlayerDelay, uint32 lanDelay, uint32 bnetDelay) // 10 35 100
{
	SetValueFromMemory(address_localDelay, singlePlayerDelay); // 35ms
	//SetValueFromMemory(address_lanDelay, lanDelay); // 35ms
	//SetValueFromMemory(address_netDelay, bnetDelay); // 100ms

	return true;
}

void WriteAsm(void* pxAdress, uint8* code, uint32 size)
{
	unsigned long Protection;
	VirtualProtect(pxAdress, size, PAGE_READWRITE, &Protection);
	memcpy(pxAdress, static_cast<const void*>(code), size);
	VirtualProtect(pxAdress, size, Protection, &Protection);
}

void UnlockFPS()
{
	uint8 bytes[] = { 0x83, 0xE0, 0xFF };

	WriteAsm(reinterpret_cast<void*>(address_LockFPS), bytes, 3);
}

void UnlockTextureSize()
{
	uint8 bytes1[] = { 0x3D, 0x00, 0x80 };
	uint8 bytes2[] = { 0xB8, 0x00, 0x80 };

	WriteAsm(reinterpret_cast<void*>(address_LockTextureSizeCmp), bytes1, 3);
	WriteAsm(reinterpret_cast<void*>(address_LockTextureSizeMov), bytes2, 3);
}


uint32 __fastcall SetCameraField_proxy(void* a1, uint32 unused, uint32 cameraField, float value, float time, uint32 a5)
{
	if (cameraField == 0)
	{
		uint32 v1 = reinterpret_cast<uint32>(a1) + 252;
		uint32 v2 = fast_call<uint32>(address_SetCameraField_misc, *(uint32*)(v1 + 8), *(uint32*)(v1 + 12));
		*((float*)v2 + 32) = 0.01f;
	}

	return this_call<uint32>(address_SetCameraField, a1, cameraField, value, time, a5);
}


void __fastcall CreateProjMatrix_proxy(uint32 outMatrix, uint32 unused, float fovY, float aspectRatio, float nearZ, float farZ)
{
	float yScale = 1.0f / tan(fovY * 0.5f / sqrt(aspectRatio * aspectRatio + 1.0f));
	float xScale = yScale / (aspectRatio * fWideScreenMul);

	*(float*)(outMatrix) = xScale;
	*(float*)(outMatrix + 16) = 0.0f;
	*(float*)(outMatrix + 32) = 0.0f;
	*(float*)(outMatrix + 48) = 0.0f;

	*(float*)(outMatrix + 4) = 0.0f;
	*(float*)(outMatrix + 20) = yScale;
	*(float*)(outMatrix + 36) = 0.0f;
	*(float*)(outMatrix + 52) = 0.0f;

	*(float*)(outMatrix + 8) = 0.0f;
	*(float*)(outMatrix + 24) = 0.0f;
	*(float*)(outMatrix + 40) = (nearZ + farZ) / (farZ - nearZ);
	*(float*)(outMatrix + 56) = (-2.0f * nearZ * farZ) / (farZ - nearZ);

	*(float*)(outMatrix + 12) = 0.0f;
	*(float*)(outMatrix + 28) = 0.0f;
	*(float*)(outMatrix + 44) = 1.0f;
	*(float*)(outMatrix + 60) = 0.0f;
}

uintptr_t address_CreateMatrixPerspectiveOffCenter = 0;
void __fastcall CreateMatrixPerspectiveOffCenter_proxy(int a1, int unused, float left, float right, float bottom, float top, float nearZ, float farZ)
{
	
	//left = right - right* fWideScreenMul;
	//left *= fWideScreenMul;
	//right *= fWideScreenMul;

	float width = right - left;
	float height = top - bottom;
	float depth = farZ - nearZ;

	message = std::to_string(width);

	float* test = new float[2];
	test[1] = 0.0f;
	delete[] test;

	if (nearZ == 0.0f && farZ == 500.0f)
		width *= fWideScreenMul;

	*(float *)a1 = 2.0 / width;
	*(float *)(a1 + 16) = 0.0;
	*(float *)(a1 + 32) = 0.0;
	*(float *)(a1 + 48) = -((right + left) / width);

	*(float *)(a1 + 4) = 0.0;
	*(float *)(a1 + 20) = 2.0 / height;
	*(float *)(a1 + 36) = 0.0;
	*(float *)(a1 + 52) = -((top + bottom) / height);

	*(float *)(a1 + 8) = 0.0;
	*(float *)(a1 + 24) = 0.0;
	*(float *)(a1 + 40) = 2.0 / depth;
	*(float *)(a1 + 56) = -((farZ + nearZ) / depth);

	*(float *)(a1 + 12) = 0.0;
	*(float *)(a1 + 28) = 0.0;
	*(float *)(a1 + 44) = 0.0;
	*(float *)(a1 + 60) = 1.0;
}


bool ReadConfigs()
{
	RenderEdgePath = registry::GetString("Software\\RenderEdge", "InstallPath");
	if (RenderEdgePath.empty())
	{
		LOG(logERROR) << "Failed to read 'InstallPath' value!";
		return false;
	}

	DWORD dwTemp = registry::GetDword("Software\\RenderEdge", "Debug");
	if (dwTemp == -1)
	{
		LOG(logERROR) << "Failed to read 'Debug' value!";
		return false;
	}
	g_bDebug = (dwTemp == 1);

	dwTemp = registry::GetDword("Software\\RenderEdge", "AllowLocalFiles");
	if (dwTemp == -1)
	{
		LOG(logERROR) << "Failed to read 'AllowLocalFiles' value!";
		return false;
	}
	g_bAllowLocalFiles = (dwTemp == 1);

	LOG(logINFO) << "WarCraft InstallPath:\t" + registry::GetString("Software\\RenderEdge", "War3InstallPath");
	LOG(logINFO) << "RenderEdge InstallPath:\t" + RenderEdgePath;

	return true;
}

void InitLoggingSystem(HMODULE module)
{
	char patch[256];
	GetModuleFileNameA(module, patch, sizeof(patch));
	std::string logFilePatch = utils::ExtractFilePath(patch) + "RenderEdge.log";

	std::fstream file(logFilePatch);
	uint32 size = 0;
	file.seekg(0, std::ios::end);
	size = (uint32)file.tellg();
	file.close();

	FILE* log_fd = fopen(logFilePatch.c_str(), (size > 1e+5) ? "w" : "a");
	Output2FILE::Stream() = log_fd;
}


// sub_6F60E3B0 - Clamp?
// sub_6F62BD00 - ?
// sub_6F337380 - ?

void __fastcall BuildHPBars_proxy(uint32 a1, uint32 unused, uint32 a2, uint32 a3)
{
	fast_call<void>(address_BuildHPBars, a1, unused, a2, a3);

	uint32 pHPBarFrame = *((uint32*)a1 + 3);
	if (pHPBarFrame)
		*((float*)pHPBarFrame + 22) /= fWideScreenMul;
}



void** __fastcall SetFramePoint_proxy(uint32 pFrame, uint32 unused, EFramePoint point, uint32 pParentFrame, EFramePoint relativePoint, float offsetX, float offsetY, uint32 bUpdate)
{
	float newX = offsetX;
	float newY = offsetY;
	EFramePoint newRelativePoint = relativePoint;

	return this_call<void**>(address_SetFramePoint, pFrame, static_cast<uint32>(point), pParentFrame, static_cast<uint32>(newRelativePoint), newX, newY, bUpdate);
}

void** __fastcall SetFramePoint2_proxy(uint32 pFrame, uint32 unused, EFramePoint point, float offsetX, float offsetY, uint32 bUpdate)
{
	float newX = offsetX;
	float newY = offsetY;

	//if (x == 0.60000002f)
	//	newX = 0.65f;
	//else
	newX /= fWideScreenMul;

	//newX += 0.1f;

	newX += 1.0f;

	return this_call<void**>(address_SetFramePoint2, pFrame, static_cast<uint32>(point), newX, newY, bUpdate);
}

void** __fastcall SetFrameWidth_proxy(uint32 pFrame, uint32 unused, float width)
{
	float newWidth = width;

	//if (width == 0.17449999f)
	//	newWidth = 0.1745f;
	//else
	//newWidth /= fWideScreenMul;

	return this_call<void**>(address_SetFrameWidth, pFrame, newWidth);
}

void** __fastcall SetFrameHeight_proxy(uint32 pFrame, uint32 unused, float height)
{
	return this_call<void**>(address_SetFrameHeight, pFrame, height);
}

BOOL APIENTRY DllMain(HMODULE module, DWORD reason, LPVOID)
{
	if (reason == DLL_PROCESS_ATTACH)
	{
		DisableThreadLibraryCalls(module);

		InitLoggingSystem(module);

		if (!ReadConfigs())
		{
			Message("Failed to read settings from 'HKEY_CURRENT_USER\\Software\\RenderEdge'!");
			TerminateProcess(GetCurrentProcess(), 0);
		}

		HMODULE hGameDll = GetModuleHandleW(L"Game.dll");
		address_GameBase = reinterpret_cast<uintptr_t>(hGameDll);

		//==================================

		if (!Storm::InitStormAPI())
			LOG(logERROR) << "Failed to init StormAPI!";
		if (!JassApiInit())
			LOG(logERROR) << "Failed to init JassAPI!";

		InitGameOffsets();

		//==================================

		if (GetGameVersion() == GameVersion::v126a)
		{
			base::hook::dyn_iat(hGameDll, L"d3d8.dll", "Direct3DCreate8", 0, (uintptr_t)Direct3DCreate8_proxy);
		}
		/*else if (GetGameVersion() == GameVersion::v128f)
		{
			base::hook::dyn_iat(hGameDll, L"d3d9.dll", "Direct3DCreate9", 0, (uintptr_t)Direct3DCreate9_proxy);
		}*/
		else
			Message("Unsupported WarCraft patch version!");

		//==================================

		if (!HOOK::deployHooks())
			LOG(logERROR) << "Failed to init RenderStateHook!";
		if (!InitInputSystem())
			LOG(logERROR) << "Failed to init InputAPI!";

		//==================================

		void InitializeMutilWar3();
		InitializeMutilWar3();
		ChangeDelay(5, 35, 100);

		//address_CreateMatrixPerspectiveOffCenter = address_GameBase + 0x7B6250;
		//base::hook::inline_install(&address_CreateMatrixPerspectiveOffCenter, (uintptr_t)CreateMatrixPerspectiveOffCenter_proxy);

		//base::hook::inline_install(&address_SetCameraField, (uintptr_t)SetCameraField_proxy);
		base::hook::inline_install(&address_CreateProjMatrix, (uintptr_t)CreateProjMatrix_proxy);
		base::hook::inline_install(&address_BuildHPBars, (uintptr_t)BuildHPBars_proxy);
		UnlockFPS();
		UnlockTextureSize();

		//base::hook::inline_install(&address_SetFramePoint, (uintptr_t)SetFramePoint_proxy);
		//base::hook::inline_install(&address_SetFramePoint2, (uintptr_t)SetFramePoint2_proxy);
		//base::hook::inline_install(&address_SetFrameWidth, (uintptr_t)SetFrameWidth_proxy);
		//base::hook::inline_install(&address_SetFrameHeight, (uintptr_t)SetFrameHeight_proxy);

		//==================================
	}
	else if (reason == DLL_PROCESS_DETACH)
	{
		if (MainEngine != nullptr)
		{
			delete MainEngine;
			MainEngine = nullptr;
		}
	}

	return TRUE;
}