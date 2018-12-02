#include "GameOffsets.h"
#include "JassApi.h"
#include "Engine.h"

uintptr_t address_GameBase;

uintptr_t address_MouseEvent;
uintptr_t address_WndProc;

uintptr_t address_LockFPS;
uintptr_t address_LockTextureSizeCmp;
uintptr_t address_LockTextureSizeMov;
uintptr_t address_localDelay;
uintptr_t address_lanDelay;
uintptr_t address_netDelay;

uintptr_t address_MatrixPerspectiveFov;
uintptr_t address_MatrixLookAt;
uintptr_t address_RenderWorldObjects;
uintptr_t address_RenderTranslucent;
uintptr_t address_RenderOpaque;
uintptr_t address_RenderWorld;
uintptr_t address_BuildHPBars;
uintptr_t address_BuildMainMenu;
uintptr_t address_InitSceneView;

uintptr_t address_GetGameUI;
uintptr_t address_SetFramePoint;
uintptr_t address_SetFramePoint2;
uintptr_t address_SetFrameWidth;
uintptr_t address_SetFrameHeight;
uintptr_t address_SetFrameText;

uintptr_t address_GetTerrain;
uintptr_t address_gxDevice;
uintptr_t address_InitJassNatives;
uintptr_t address_BindJassNative;

uintptr_t address_ApplyFogOfWarEx;
uintptr_t address_dwSceneSettings1;
uintptr_t address_MiscDataGetColor;


void InitGameOffsets(uint32 gameBuildVersion)
{
	address_GameBase = (uintptr_t)GetModuleHandleW(L"Game.dll");

	if (gameBuildVersion == 6401)
	{
		address_MouseEvent = address_GameBase + 0x398EA0;
		address_WndProc = address_GameBase + 0x52C9C0;

		address_LockFPS = address_GameBase + 0x62D7FB;
		address_LockTextureSizeCmp = address_GameBase + 0x52D35E;
		address_LockTextureSizeMov = address_GameBase + 0x52D375;
		address_localDelay = address_GameBase + 0x660F01;
		address_lanDelay = address_GameBase + 0x661A91;
		address_netDelay = address_GameBase + 0x65DE41;

		address_MatrixPerspectiveFov = address_GameBase + 0x7B66F0;
		address_MatrixLookAt = address_GameBase + 0x7B8120;
		address_RenderWorldObjects = address_GameBase + 0x395620;
		address_RenderTranslucent = address_GameBase + 0x50B3A0;
		address_RenderOpaque = address_GameBase + 0x50B1A0;
		address_RenderWorld = address_GameBase + 0x395900;
		address_BuildHPBars = address_GameBase + 0x379A30;
		address_BuildMainMenu = address_GameBase + 0x58BD20;
		address_InitSceneView = address_GameBase + 0x4E6C80;

		address_GetGameUI = address_GameBase + 0x300710;
		address_SetFramePoint = address_GameBase + 0x606770;
		address_SetFramePoint2 = address_GameBase + 0x6061B0;
		address_SetFrameWidth = address_GameBase + 0x605D90;
		address_SetFrameHeight = address_GameBase + 0x605DB0;
		address_SetFrameText = address_GameBase + 0x611D40;

		address_GetTerrain = address_GameBase + 0x01F5A0;
		address_gxDevice = address_GameBase + 0xACBD40;
		address_InitJassNatives = address_GameBase + 0x3D4020;
		address_BindJassNative = address_GameBase + 0x455110;

		address_ApplyFogOfWarEx = address_GameBase + 0x748250;
		address_dwSceneSettings1 = address_GameBase + 0xA88F7C;
		address_MiscDataGetColor = address_GameBase + 0x72B0B0;
	}
}