#pragma once
#include "Utils.h"

extern uintptr_t address_GameBase;

extern uintptr_t address_MouseEvent;
extern uintptr_t address_WndProc;

extern uintptr_t address_LockFPS;
extern uintptr_t address_LockTextureSizeCmp;
extern uintptr_t address_LockTextureSizeMov;
extern uintptr_t address_localDelay;
extern uintptr_t address_lanDelay;
extern uintptr_t address_netDelay;

extern uintptr_t address_MatrixPerspectiveFov;
extern uintptr_t address_MatrixLookAt;
extern uintptr_t address_RenderWorldObjects;
extern uintptr_t address_RenderTranslucent;
extern uintptr_t address_RenderOpaque;
extern uintptr_t address_RenderWorld;
extern uintptr_t address_RenderCineFilter;
extern uintptr_t address_RenderUI;
extern uintptr_t address_BuildHPBars;
extern uintptr_t address_BuildMainMenu;
extern uintptr_t address_InitSceneView;

extern uintptr_t address_GetGameUI;
extern uintptr_t address_SetFramePoint;
extern uintptr_t address_SetFramePoint2;
extern uintptr_t address_SetFrameWidth;
extern uintptr_t address_SetFrameHeight;
extern uintptr_t address_SetFrameText;

extern uintptr_t address_GetTerrain;
extern uintptr_t address_gxDevice;
extern uintptr_t address_InitJassNatives;
extern uintptr_t address_BindJassNative;

extern uintptr_t address_ApplyFogOfWarEx;
extern uintptr_t address_dwSceneSettings1;
extern uintptr_t address_MiscDataGetColor;

void InitGameOffsets(uint32 gameBuildVersion);