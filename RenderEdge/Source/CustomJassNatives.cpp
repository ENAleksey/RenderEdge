#include "CustomJassNatives.h"

#include <list>

#include "JassApi.h"
#include "JassNatives.h"
#include "GameUI.h"
#include "Engine.h"
#include "GUI.h"
#include "Input.h"
#include "FontManager.h"


int32 g_iWheelDelta = 0;
int32 g_iTrigKey = -1;

std::list<jTrigger> MouseWheelTriggers;
std::list<jTrigger> MouseMoveTriggers;
std::list<jTrigger> WindowResizeTriggers;
std::list<jTrigger> FrameUpdateTriggers;
std::list<std::pair<jTrigger, jInteger>> MouseDownTriggers;
std::list<std::pair<jTrigger, jInteger>> MouseUpTriggers;
std::list<std::pair<jTrigger, jInteger>> KeyDownTriggers;
std::list<std::pair<jTrigger, jInteger>> KeyUpTriggers;


jInteger jNATIVE jGetMouseX()
{
	return Input::GetMouseX();
}
jInteger jNATIVE jGetMouseY()
{
	return Input::GetMouseY();
}
jInteger jNATIVE jGetMouseXRelative()
{
	return Input::GetMouseXRelative();
}
jInteger jNATIVE jGetMouseYRelative()
{
	return Input::GetMouseYRelative();
}
jBoolean jNATIVE jIsKeyDown(jInteger Key)
{
	return Input::IsKeyDown(Key);
}
jInteger jNATIVE jGetWindowWidth()
{
	return Input::GetWindowWidth();
}
jInteger jNATIVE jGetWindowHeight()
{
	return Input::GetWindowHeight();
}
jInteger jNATIVE jGetWindowX()
{
	return Input::GetWindowX();
}
jInteger jNATIVE jGetWindowY()
{
	return Input::GetWindowY();
}
jNothing jNATIVE jSetMousePos(jInteger x, jInteger y)
{
	SetCursorPos(x, y);
}
jInteger jNATIVE jGetTriggerKey()
{
	return g_iTrigKey;
}
jInteger jNATIVE jGetWheelDelta()
{
	return g_iWheelDelta;
}
jReal jNATIVE jGetFPS()
{
	return Jass::to_jReal(g_fFPS);
}
jReal jNATIVE jGetDeltaTime()
{
	return Jass::to_jReal(g_fDeltaTime);
}
jInteger jNATIVE jCOLOR_ARGB(jInteger a, jInteger r, jInteger g, jInteger b)
{
	return D3DCOLOR_ARGB(a, r, g, b);
}
jBoolean jNATIVE jIsGamePaused()
{
	return IsGamePaused();
}
jNothing jNATIVE jEnableVsync(jBoolean bEnable)
{
	if ((jBoolean)g_bVsyncEnabled != bEnable)
	{
		g_bVsyncEnabled = bEnable;
		g_bResetDevice = true;
	}
}
jNothing jNATIVE jEnableAnisoFiltering(jBoolean bEnable, jInteger maxAnisotropy)
{
	g_bAnisoFiltering = bEnable;
	g_iMaxAnisotropy = maxAnisotropy;
}


jReal jNATIVE jGetMouseTerrainX()
{
	return Jass::to_jReal(Input::vMousePosTerrain.x);
}
jReal jNATIVE jGetMouseTerrainY()
{
	return Jass::to_jReal(Input::vMousePosTerrain.y);
}
jReal jNATIVE jGetMouseTerrainZ()
{
	return Jass::to_jReal(Input::vMousePosTerrain.z);
}
jBoolean jNATIVE jIsMouseOverUI()
{
	return Input::IsMouseOverUI();
}
jNothing jNATIVE jBlockMouse(jBoolean bBlock)
{
	Input::BlockMouse(bBlock);
}

void RemapValuesGUI(float& x, float& y, float& width, float& height)
{
	const float xMul = 0.8f / Input::GetWindowWidth();
	const float yMul = 0.6f / Input::GetWindowHeight();

	x *= xMul;
	y *= yMul;
	width *= xMul;
	height *= yMul;
}
jNothing jNATIVE jHideInterface()
{
	CGameUI* pGameUI = GetGameUI(0, 0);
	uint32 pRootFrame = (uint32)pGameUI + 180;

	SetFramePoint(pGameUI->UpperButtonBarFrame, EFramePoint::TopLeft, pRootFrame, EFramePoint::TopLeft, 0.0f, 1.0f);
	SetFramePoint(pGameUI->ResourceBarFrame, EFramePoint::TopRight, pRootFrame, EFramePoint::TopRight, 0.0f, 1.0f);

	SetFramePoint(pGameUI->SimpleConsole, EFramePoint::TopLeft, pRootFrame, EFramePoint::TopLeft, 10.0f, 0.0f);
	SetFramePoint(pGameUI->SimpleConsole, EFramePoint::TopRight, pRootFrame, EFramePoint::TopRight, -10.0f, 0.0f);

	SetFramePoint(pGameUI->Portrait + 180, EFramePoint::BottomLeft, pRootFrame, EFramePoint::BottomLeft, 1.0f, 1.0f);
	SetFramePoint(pGameUI->Minimap + 180, EFramePoint::BottomLeft, pRootFrame, EFramePoint::BottomLeft, 1.0f, 1.0f);

	SetFramePoint(pGameUI->PeonBar, EFramePoint::BottomLeft, pRootFrame, EFramePoint::BottomLeft, 1.0f, 1.0f);
	SetFramePoint(pGameUI->HeroBar, EFramePoint::TopLeft, pRootFrame, EFramePoint::TopLeft, 0.0f, 1.0f);

	SetFramePoint(pGameUI->TimeOfDayIndicator + 180, EFramePoint::BottomLeft, pRootFrame, EFramePoint::BottomLeft, 1.0f, 1.0f);
	SetFramePoint(*(uint32*)(pGameUI->TimeOfDayIndicator + 432) + 180, EFramePoint::Top, pRootFrame, EFramePoint::Top, 1.0f, 0.0f);

	SetFramePoint(*(uint32*)(pGameUI->InfoBar + 332), EFramePoint::BottomRight, pRootFrame, EFramePoint::TopLeft, 1.0f, 0.0f); // ConsoleInventoryCoverTexture
}
jNothing jNATIVE jEditBlackBorders(jInteger newUpperHeight, jInteger newBottomHeight)
{
	CGameUI* pGameUI = GetGameUI(0, 0);
	uint32 pWorldFrameWar3 = pGameUI->WorldFrameWar3 + 180;
	uint32 pRootFrame = (uint32)pGameUI + 180;

	float upperHeight = newUpperHeight * 0.6f / Input::GetWindowHeight();
	float bottomHeight = newBottomHeight * 0.6f / Input::GetWindowHeight();

	SetFramePoint(pWorldFrameWar3, EFramePoint::TopRight, pRootFrame, EFramePoint::TopRight, 0.0f, -upperHeight);
	SetFramePoint(pWorldFrameWar3, EFramePoint::BottomLeft, pRootFrame, EFramePoint::BottomLeft, 0.0f, bottomHeight);
}
jNothing jNATIVE jEditPortrait(jInteger anchor, jInteger newX, jInteger newY, jInteger newWidth, jInteger newHeight)
{
	CGameUI* pGameUI = GetGameUI(0, 0);
	uint32 pPortraitFrame = pGameUI->Portrait + 180;
	uint32 pRootFrame = (uint32)pGameUI + 180;

	float x(newX), y(newY), width(newWidth), height(newHeight);
	RemapValuesGUI(x, y, width, height);

	if (newWidth >= 0) SetFrameWidth(pPortraitFrame, width);
	if (newHeight >= 0) SetFrameHeight(pPortraitFrame, height);
	SetFramePoint(pPortraitFrame, EFramePoint::BottomLeft, pRootFrame, EFramePoint(anchor), x, -(y + GetFrameHeight(pPortraitFrame)));
}
jNothing jNATIVE jEditMinimap(jInteger anchor, jInteger newX, jInteger newY, jInteger newWidth, jInteger newHeight)
{
	CGameUI* pGameUI = GetGameUI(0, 0);
	uint32 pMinimapFrame = pGameUI->Minimap + 180;
	uint32 pRootFrame = (uint32)pGameUI + 180;

	float x(newX), y(newY), width(newWidth), height(newHeight);
	RemapValuesGUI(x, y, width, height);

	SetFramePoint(pMinimapFrame, EFramePoint::BottomLeft, pRootFrame, EFramePoint(anchor), x, -(y + height));
	SetFramePoint(pMinimapFrame, EFramePoint::TopRight, pRootFrame, EFramePoint(anchor), x + width, -y);
}
jNothing jNATIVE jEditCommandBarButton(jInteger row, jInteger column, jInteger anchor, jInteger newX, jInteger newY, jInteger newWidth, jInteger newHeight)
{
	if (row < 0 || row > 2)
		return;
	if (column < 0 || column > 3)
		return;

	CGameUI* pGameUI = GetGameUI(0, 0);
	uint32 pButtonFrame = GetCommandBarButton(row, column);
	uint32 pRootFrame = (uint32)pGameUI + 180;

	float x(newX), y(newY), width(newWidth), height(newHeight);
	RemapValuesGUI(x, y, width, height);

	if (newWidth >= 0) SetFrameWidth(pButtonFrame, width);
	if (newHeight >= 0) SetFrameHeight(pButtonFrame, height);
	SetFramePoint(pButtonFrame, EFramePoint::TopLeft, pRootFrame, EFramePoint(anchor), x, -y);
}
jNothing jNATIVE jEditHeroBarButton(jInteger buttonId, jInteger anchor, jInteger newX, jInteger newY, jInteger newWidth, jInteger newHeight)
{
	if (buttonId < 0 || buttonId > 6)
		return;

	CGameUI* pGameUI = GetGameUI(0, 0);
	uint32 pButtonFrame = GetHeroBarButton(buttonId);
	uint32 pRootFrame = (uint32)pGameUI + 180;

	float x(newX), y(newY), width(newWidth), height(newHeight);
	RemapValuesGUI(x, y, width, height);

	if (newWidth >= 0) SetFrameWidth(pButtonFrame, width);
	if (newHeight >= 0) SetFrameHeight(pButtonFrame, height);
	SetFramePoint(pButtonFrame, EFramePoint::TopLeft, pRootFrame, EFramePoint(anchor), x, -y);
}
jNothing jNATIVE jEditItemBarButton(jInteger buttonId, jInteger anchor, jInteger newX, jInteger newY, jInteger newWidth, jInteger newHeight)
{
	if (buttonId < 0 || buttonId > 5)
		return;

	CGameUI* pGameUI = GetGameUI(0, 0);
	uint32 pButtonFrame = GetItemBarButton(buttonId);
	uint32 pRootFrame = (uint32)pGameUI + 180;

	float x(newX), y(newY), width(newWidth), height(newHeight);
	RemapValuesGUI(x, y, width, height);

	if (newWidth >= 0) SetFrameWidth(pButtonFrame, width);
	if (newHeight >= 0) SetFrameHeight(pButtonFrame, height);
	SetFramePoint(pButtonFrame, EFramePoint::TopLeft, pRootFrame, EFramePoint(anchor), x, -y);
}
jNothing jNATIVE jEditMinimapButton(jInteger buttonId, jInteger anchor, jInteger newX, jInteger newY, jInteger newWidth, jInteger newHeight)
{
	if (buttonId < 0 || buttonId > 4)
		return;

	CGameUI* pGameUI = GetGameUI(0, 0);
	uint32 pButtonFrame = pGameUI->MinimapButtons[buttonId];
	uint32 pRootFrame = (uint32)pGameUI + 180;

	float x(newX), y(newY), width(newWidth), height(newHeight);
	RemapValuesGUI(x, y, width, height);

	if (newWidth >= 0) SetFrameWidth(pButtonFrame, width);
	if (newHeight >= 0) SetFrameHeight(pButtonFrame, height);
	SetFramePoint(pButtonFrame, EFramePoint::TopLeft, pRootFrame, EFramePoint(anchor), x, -y);
}
jNothing jNATIVE jEditUpperButtonBarButton(jInteger buttonId, jInteger anchor, jInteger newX, jInteger newY, jInteger newWidth, jInteger newHeight)
{
	if (buttonId < 0 || buttonId > 3)
		return;

	CGameUI* pGameUI = GetGameUI(0, 0);
	uint32 pRootFrame = (uint32)pGameUI + 180;
	uint32 pButtonFrame = GetUpperButtonBarButton(buttonId);

	float x(newX), y(newY), width(newWidth), height(newHeight);
	RemapValuesGUI(x, y, width, height);

	if (newWidth >= 0) SetFrameWidth(pButtonFrame, width);
	if (newHeight >= 0) SetFrameHeight(pButtonFrame, height);
	if (buttonId == 0)
		SetFramePoint(pButtonFrame, EFramePoint::TopLeft, pRootFrame, EFramePoint(anchor), x, -y);
	else
		SetFramePoint(pButtonFrame, EFramePoint::Left, pRootFrame, EFramePoint(anchor), x, -(y + GetFrameHeight(pButtonFrame) / 2));
}


jNothing jNATIVE jCtrlSetSize(jInteger id, jInteger width, jInteger height)
{
	if (!CustomUI || id < 0)
		return;

	CustomUI->SetCtrlSize(id, width, height);
}
jNothing jNATIVE jCtrlSetAnchor(jInteger id, jInteger parentId, jInteger anchor)
{
	if (!CustomUI || id < 0)
		return;

	CustomUI->SetCtrlAnchor(id, parentId, static_cast<EAnchor>(anchor));
}
jNothing jNATIVE jCtrlSetPosition(jInteger id, jInteger offsetX, jInteger offsetY)
{
	if (!CustomUI || id < 0)
		return;

	CustomUI->SetCtrlPosition(id, offsetX, offsetY);
}
jNothing jNATIVE jCtrlNew(jInteger id, jInteger offsetX, jInteger offsetY, jInteger width, jInteger height)
{
	if (!CustomUI || id < 0)
		return;

	CustomUI->NewCtrl(id, offsetX, offsetY, width, height);
}
jNothing jNATIVE jCtrlSetTexture(jInteger id, jString filename)
{
	if (!CustomUI || id < 0)
		return;

	CustomUI->SetCtrlTexture(id, Jass::from_jString(filename));
}
jNothing jNATIVE jCtrlSetColor(jInteger id, jInteger argb)
{
	if (!CustomUI || id < 0)
		return;

	CustomUI->SetCtrlColor(id, argb);
}
jNothing jNATIVE jCtrlSetText(jInteger id, jString newtext, jBoolean bWrap)
{
	if (!CustomUI || id < 0)
		return;

	CustomUI->SetCtrlText(id, Jass::from_jString(newtext), bWrap);
}
jNothing jNATIVE jCtrlSetTextAlignment(jInteger id, jInteger alignment)
{
	if (!CustomUI || id < 0)
		return;

	CustomUI->SetCtrlTextAlignment(id, static_cast<ETextAlignment>(alignment));
}
jNothing jNATIVE jCtrlShow(jInteger id, jBoolean isShow)
{
	if (!CustomUI || id < 0)
		return;

	CustomUI->ShowCtrl(id, isShow);
}
jNothing jNATIVE jCtrlSetDepth(jInteger id, jReal* fDepth)
{
	if (!CustomUI || id < 0)
		return;

	CustomUI->SetCtrlDepth(id, Jass::from_jReal(*fDepth));
}
jNothing jNATIVE jCtrlSetZOrder(jInteger id, jInteger iZOrder)
{
	if (!CustomUI || id < 0)
		return;

	CustomUI->SetCtrlZOrder(id, iZOrder);
}
jNothing jNATIVE jCtrlSetAngle(jInteger id, jReal* fAngle)
{
	if (!CustomUI || id < 0)
		return;

	CustomUI->SetCtrlAngle(id, Jass::from_jReal(*fAngle));
}
jInteger jNATIVE jCtrlGetFromPoint(jInteger x, jInteger y)
{
	if (!CustomUI)
		return -1;

	return CustomUI->GetCtrlFromPoint(x, y);
}
jInteger jNATIVE jCtrlGetWidth(jInteger id)
{
	if (!CustomUI || id < 0)
		return 0;

	return CustomUI->GetCtrlWidth(id);
}
jInteger jNATIVE jCtrlGetHeight(jInteger id)
{
	if (!CustomUI || id < 0)
		return 0;

	return CustomUI->GetCtrlHeight(id);
}
jNothing jNATIVE jCtrlSetFont(jInteger id, jString name, jInteger size)
{
	if (!CustomUI || id < 0)
		return;

	CustomUI->SetCtrlFont(id, Jass::from_jString(name), size);
}
jBoolean jNATIVE jCtrlIsText(jInteger id)
{
	if (!CustomUI || id < 0)
		return jFalse;

	return CustomUI->CtrlIsText(id);
}
jNothing jNATIVE jGUILoadFont(jString fileName)
{
	if (FontManager)
		FontManager->LoadFontFromMPQ(Jass::from_jString(fileName));
}




void ClearExecuteTriggers()
{
	MouseWheelTriggers.clear();
	MouseMoveTriggers.clear();
	WindowResizeTriggers.clear();
	FrameUpdateTriggers.clear();
	MouseDownTriggers.clear();
	MouseUpTriggers.clear();
	KeyDownTriggers.clear();
	KeyUpTriggers.clear();
}
void RunTrigger(jTrigger trigger)
{
	if (JassNatives::TriggerEvaluate(trigger))
		JassNatives::TriggerExecute(trigger);
}

jNothing jNATIVE jTriggerRegisterMouseMoveEvent(jTrigger t)
{
	MouseMoveTriggers.push_back(t);
}
jNothing jNATIVE jTriggerRegisterMouseWheelEvent(jTrigger t)
{
	MouseWheelTriggers.push_back(t);
}
jNothing jNATIVE jTriggerRegisterWindowResizeEvent(jTrigger t)
{
	WindowResizeTriggers.push_back(t);
}
jNothing jNATIVE jTriggerRegisterKeyEvent(jTrigger t, jInteger key, jInteger state)
{
	if (state == 0)
		KeyDownTriggers.push_back(std::make_pair(t, key));
	else if (state == 1)
		KeyUpTriggers.push_back(std::make_pair(t, key));
}
jNothing jNATIVE jTriggerRegisterMouseEvent(jTrigger t, jInteger button, jInteger state)
{
	if (state == 0)
		MouseDownTriggers.push_back(std::make_pair(t, button));
	else if (state == 1)
		MouseUpTriggers.push_back(std::make_pair(t, button));
}
jNothing jNATIVE jTriggerRegisterFrameUpdateEvent(jTrigger t)
{
	FrameUpdateTriggers.push_back(t);
}

void ExecuteKeyTriggers(int32 key, int32 state)
{
	if (!IsGaming())
		return;

	g_iTrigKey = key;
	for (auto trigger : ((state == 0) ? KeyDownTriggers : KeyUpTriggers))
		if (trigger.second == key || trigger.second == -1)
			RunTrigger(trigger.first);
}
void ExecuteMouseTriggers(int32 button, int32 state)
{
	if (!IsGaming())
		return;

	g_iTrigKey = button;
	for (auto trigger : ((state == 0) ? MouseDownTriggers : MouseUpTriggers))
		if (trigger.second == button || trigger.second == -1)
			RunTrigger(trigger.first);
}
void ExecuteWheelTriggers(int32 delta)
{
	if (!IsGaming())
		return;

	g_iWheelDelta = delta;
	for (auto trigger : MouseWheelTriggers)
		RunTrigger(trigger);
}
void ExecuteMouseMoveTriggers(int32 x, int32 y)
{
	if (!IsGaming())
		return;

	for (auto trigger : MouseMoveTriggers)
		RunTrigger(trigger);
}
void ExecuteWindowResizeTriggers()
{
	if (!IsGaming())
		return;

	for (auto trigger : WindowResizeTriggers)
		RunTrigger(trigger);
}
void ExecuteFrameUpdateTriggers()
{
	if (!IsGaming())
		return;

	for (auto trigger : FrameUpdateTriggers)
		RunTrigger(trigger);
}


void InitCustomNatives()
{
	Jass::BindNative((uintptr_t)jGetMouseXRelative, "GetMouseXRelative", "()I");
	Jass::BindNative((uintptr_t)jGetMouseYRelative, "GetMouseYRelative", "()I");
	Jass::BindNative((uintptr_t)jGetMouseX, "GetMouseX", "()I");
	Jass::BindNative((uintptr_t)jGetMouseY, "GetMouseY", "()I");
	Jass::BindNative((uintptr_t)jSetMousePos, "SetMousePos", "(II)");
	Jass::BindNative((uintptr_t)jGetWheelDelta, "GetWheelDelta", "()I");
	Jass::BindNative((uintptr_t)jGetMouseTerrainX, "GetMouseTerrainX", "()R");
	Jass::BindNative((uintptr_t)jGetMouseTerrainY, "GetMouseTerrainY", "()R");
	Jass::BindNative((uintptr_t)jGetMouseTerrainZ, "GetMouseTerrainZ", "()R");
	Jass::BindNative((uintptr_t)jIsMouseOverUI, "IsMouseOverUI", "()B");
	Jass::BindNative((uintptr_t)jBlockMouse, "BlockMouse", "(B)V");

	Jass::BindNative((uintptr_t)jIsKeyDown, "IsKeyDown", "(I)B");
	Jass::BindNative((uintptr_t)jGetTriggerKey, "GetTriggerKey", "()I");
	Jass::BindNative((uintptr_t)jTriggerRegisterMouseWheelEvent, "TriggerRegisterMouseWheelEvent", "(Htrigger;)V");
	Jass::BindNative((uintptr_t)jTriggerRegisterMouseMoveEvent, "TriggerRegisterMouseMoveEvent", "(Htrigger;)V");
	Jass::BindNative((uintptr_t)jTriggerRegisterMouseEvent, "TriggerRegisterMouseEvent", "(Htrigger;II)V");
	Jass::BindNative((uintptr_t)jTriggerRegisterKeyEvent, "TriggerRegisterKeyEvent", "(Htrigger;II)V");

	Jass::BindNative((uintptr_t)jGetWindowWidth, "GetWindowWidth", "()I");
	Jass::BindNative((uintptr_t)jGetWindowHeight, "GetWindowHeight", "()I");
	Jass::BindNative((uintptr_t)jGetWindowX, "GetWindowX", "()I");
	Jass::BindNative((uintptr_t)jGetWindowY, "GetWindowY", "()I");
	Jass::BindNative((uintptr_t)jTriggerRegisterWindowResizeEvent, "TriggerRegisterWindowResizeEvent", "(Htrigger;)V");

	Jass::BindNative((uintptr_t)jGetFPS, "GetFPS", "()R");
	Jass::BindNative((uintptr_t)jGetDeltaTime, "GetDeltaTime", "()R");
	Jass::BindNative((uintptr_t)jCOLOR_ARGB, "COLOR_ARGB", "(IIII)I");
	Jass::BindNative((uintptr_t)jEnableVsync, "EnableVsync", "(B)V");
	Jass::BindNative((uintptr_t)jTriggerRegisterFrameUpdateEvent, "TriggerRegisterFrameUpdateEvent", "(Htrigger;)V");
	Jass::BindNative((uintptr_t)jIsGamePaused, "IsGamePaused", "()B");
	Jass::BindNative((uintptr_t)jEnableAnisoFiltering, "EnableAnisoFiltering", "(BI)V");

	Jass::BindNative((uintptr_t)jCtrlNew, "CtrlNew", "(IIIII)V");
	Jass::BindNative((uintptr_t)jCtrlSetColor, "CtrlSetColor", "(II)V");
	Jass::BindNative((uintptr_t)jCtrlSetTexture, "CtrlSetTexture", "(IS)V");
	Jass::BindNative((uintptr_t)jCtrlSetText, "CtrlSetText", "(ISB)V");
	Jass::BindNative((uintptr_t)jCtrlSetTextAlignment, "CtrlSetTextAlignment", "(II)V");
	Jass::BindNative((uintptr_t)jCtrlSetSize, "CtrlSetSize", "(III)V");
	Jass::BindNative((uintptr_t)jCtrlSetPosition, "CtrlSetPosition", "(III)V");
	Jass::BindNative((uintptr_t)jCtrlSetAnchor, "CtrlSetAnchor", "(III)V");
	Jass::BindNative((uintptr_t)jCtrlShow, "CtrlShow", "(IB)V");
	Jass::BindNative((uintptr_t)jCtrlSetDepth, "CtrlSetDepth", "(IR)V");
	Jass::BindNative((uintptr_t)jCtrlSetZOrder, "CtrlSetZOrder", "(II)V");
	Jass::BindNative((uintptr_t)jCtrlSetAngle, "CtrlSetAngle", "(IR)V");
	Jass::BindNative((uintptr_t)jCtrlGetWidth, "CtrlGetWidth", "(I)I");
	Jass::BindNative((uintptr_t)jCtrlGetHeight, "CtrlGetHeight", "(I)I");
	Jass::BindNative((uintptr_t)jCtrlGetFromPoint, "CtrlGetFromPoint", "(II)I");
	Jass::BindNative((uintptr_t)jCtrlIsText, "CtrlIsText", "(I)B");
	Jass::BindNative((uintptr_t)jCtrlSetFont, "CtrlSetFont", "(ISI)V");
	Jass::BindNative((uintptr_t)jGUILoadFont, "GUILoadFont", "(S)V");

	Jass::BindNative((uintptr_t)jHideInterface, "HideInterface", "()V");
	Jass::BindNative((uintptr_t)jEditBlackBorders, "EditBlackBorders", "(II)V");
	Jass::BindNative((uintptr_t)jEditPortrait, "EditPortrait", "(IIIII)V");
	Jass::BindNative((uintptr_t)jEditMinimap, "EditMinimap", "(IIIII)V");
	Jass::BindNative((uintptr_t)jEditCommandBarButton, "EditCommandBarButton", "(IIIIIII)V");
	Jass::BindNative((uintptr_t)jEditHeroBarButton, "EditHeroBarButton", "(IIIIII)V");
	Jass::BindNative((uintptr_t)jEditItemBarButton, "EditItemBarButton", "(IIIIII)V");
	Jass::BindNative((uintptr_t)jEditMinimapButton, "EditMinimapButton", "(IIIIII)V");
	Jass::BindNative((uintptr_t)jEditUpperButtonBarButton, "EditUpperButtonBarButton", "(IIIIII)V");
}