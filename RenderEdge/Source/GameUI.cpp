#include "GameUI.h"

#include "GameOffsets.h"
#include "fp_call.h"

CGameUI* GetGameUI(uint32 unk0, uint32 unk1)
{
	return fast_call<CGameUI*>(address_GetGameUI, unk0, unk1);
}

uint32 GetWorldFrame()
{
	CGameUI* pGameUI = GetGameUI(0, 0);
	if (!pGameUI)
		return 0;

	uint32 pWorldFrame = pGameUI->WorldFrameWar3;

	return pWorldFrame;
}

uint32 GetGameCamera()
{
	CGameUI* pGameUI = GetGameUI(0, 0);
	if (!pGameUI)
		return 0;

	uint32 pWorldFrame = pGameUI->WorldFrameWar3;
	uint32 pGameCamera = *(uint32*)(pWorldFrame + 320);

	return pGameCamera;
}

bool IsInGameMenu()
{
	CGameUI* pGameUI = GetGameUI(0, 0);
	if (!pGameUI)
		return false;

	return pGameUI->isInGameMenu != 0;
}

bool IsGamePaused()
{
	CGameUI* pGameUI = GetGameUI(0, 0);
	if (!pGameUI)
		return false;

	bool bGamePaused = (pGameUI->isInGameMenu != 0) ? true : (pGameUI->isGamePaused != 0);

	return bGamePaused;
}

bool IsGaming()
{
	return GetGameUI(0, 0) != nullptr;
}

// ======================================================================

void SetFramePoint(uint32 pFrame, EFramePoint point, uint32 pParentFrame, EFramePoint relativePoint, float offsetX, float offsetY)
{
	this_call<void**>(address_GameBase + 0x606770, pFrame, static_cast<uint32>(point), pParentFrame, static_cast<uint32>(relativePoint), offsetX, offsetY, 1);
}

void SetFrameWidth(uint32 pFrame, float width)
{
	this_call<void**>(address_GameBase + 0x605D90, pFrame, width);
}

void SetFrameHeight(uint32 pFrame, float height)
{
	this_call<void**>(address_GameBase + 0x605DB0, pFrame, height);
}

float GetFrameWidth(uint32 pFrame)
{
	return *(float*)(pFrame + 88);
}

float GetFrameHeight(uint32 pFrame)
{
	return *(float*)(pFrame + 92);
}

uint32 GetFramePoint(uint32 pFrame, EFramePoint point)
{
	return *(uint32*)(pFrame + 4 * static_cast<uint32>(point) + 8);
}

uint32 GetFramePointParent(uint32 pFrame, EFramePoint point)
{
	return *(uint32*)(GetFramePoint(pFrame, point) + 4);
}

uint32 GetFramePointRelativePoint(uint32 pFrame, EFramePoint point)
{
	return *(uint32*)(GetFramePoint(pFrame, point) + 8);
}

float GetFramePointX(uint32 pFrame, EFramePoint point)
{
	return *(float*)(GetFramePoint(pFrame, point) + 12);
}

float GetFramePointY(uint32 pFrame, EFramePoint point)
{
	return *(float*)(GetFramePoint(pFrame, point) + 16);
}

D3DXVECTOR2 GetFramePointPos(uint32 pFrame, EFramePoint point)
{
	uint32 pFramePoint = GetFramePoint(pFrame, point);
	return D3DXVECTOR2(*(float*)(pFramePoint + 12), *(float*)(pFramePoint + 16));
}

void SetFrameText(uint32 pFrame, const char* text)
{
	this_call<void**>(address_SetFrameText, pFrame, text);
}

void SetFrameText(uint32 pFrame, const std::string& text)
{
	SetFrameText(pFrame, text.c_str());
}

// ======================================================================

uint32 GetPanelButton(uint32 pFrame, uint8 row, uint8 column)
{
	return *(DWORD*)(*(DWORD*)(16 * row + *((DWORD*)pFrame + 85) + 8) + 4 * column);
}

uint32 GetUpperButtonBarButton(uint8 id)
{
	CGameUI* pGameUI = GetGameUI(0, 0);
	if (!pGameUI)
		return 0;

	uint32 pUpperButtonBar = pGameUI->UpperButtonBarFrame;
	if (id == 0)
		return *((uint32*)pUpperButtonBar + 78);
	else if (id == 1)
		return *((uint32*)pUpperButtonBar + 76);
	else if (id == 2)
		return *((uint32*)pUpperButtonBar + 77);
	else if (id == 3)
		return *((uint32*)pUpperButtonBar + 88);

	return 0;
}

uint32 GetCommandBarButton(uint8 row, uint8 column)
{
	CGameUI* pGameUI = GetGameUI(0, 0);
	if (!pGameUI)
		return 0;

	return GetPanelButton(pGameUI->CommandBar, row, column);
}

uint32 GetItemBarButton(uint8 id)
{
	CGameUI* pGameUI = GetGameUI(0, 0);
	if (!pGameUI)
		return 0;

	uint32 pItemBar = *(uint32*)(pGameUI->InfoBar + 328);
	return *(uint32*)(*(uint32*)(pItemBar + 304) + 8 * id + 4);
}

uint32 GetHeroBarButton(uint8 id)
{
	CGameUI* pGameUI = GetGameUI(0, 0);
	if (!pGameUI)
		return 0;

	return GetPanelButton(pGameUI->HeroBar, id, 0);
}