#include "JassApi.h"

#include "do_once.h"
#include "nf_register.h"
#include "basic_searcher.h"
#include "fp_call.h"
#include "Engine.h"
#include "Input.h"
#include "inline.h"
#include "Log.h"
#include "GUI.h"
#include "CJass.h"
#include <list>
#include "d3d8to9.hpp"
#include "GameOffsets.h"
#include "Utils.h"
#include "FontManager.h"
#include "CGameUI.h"


uint32 War3Version;
uintptr_t address_GetGameUI;

base::warcraft3::basic_searcher war3_searcher(GetModuleHandleW(L"game.dll"));
static uintptr_t address_BindNative;

struct JassNative
{
	uintptr_t   func;
	const char* name;
	const char* param;

	JassNative(uintptr_t f, const char* n, const char* p) : func(f), name(n), param(p) { }
};

std::vector<JassNative> CustomNatives;


GameState GetGameState()
{
	int32 rt = -1;

	auto hProcess = GetCurrentProcess();

	if (!ReadProcessMemory(hProcess, (void*)(TlsValue + 4 * 0x0D), (void*)&rt, 4, NULL))
		return GameState::NONE;
	if (!ReadProcessMemory(hProcess, (void*)(rt + 0x10), (void*)&rt, 4, NULL))
		return GameState::NONE;
	if (!ReadProcessMemory(hProcess, (void*)(rt + 0x8), (void*)&rt, 4, NULL))
		return GameState::NONE;
	if (!ReadProcessMemory(hProcess, (void*)(rt + 0x278), (void*)&rt, 4, NULL))
		return GameState::NONE;

	return static_cast<GameState>(rt);
}

bool IsGamePaused()
{
	return (GameUI->isGamePaused != 0);
}

void register_game_reset_event(std::function<void(uintptr_t)> func)
{
	base::warcraft3::jass::nf_register::event_hook.connect(func);
}


uintptr_t convert_function(uintptr_t address)
{
	return address + *(uintptr_t*)(address + 1) + 5;
}


uintptr_t search_BindNative()
{
	uintptr_t ptr = war3_searcher.search_string("StringCase");
	ptr += 9;
	return convert_function(ptr);
}


GameVersion GetGameVersion()
{
	return static_cast<GameVersion>(War3Version);
}

uint32 GetGameUI(uint32 unk0, uint32 unk1)
{
	return fast_call<uint32>(address_GetGameUI, unk0, unk1);
}

uint32 ReadGameUIArray(uint32 element)
{
	return *((uint32*)GetGameUI(0, 0) + element);
}

//uint32 ReadGameUI(uint32 offset)
//{
//	return *((uint32*)(GetGameUI(0, 0) + offset));
//}

// ReadGameUI(offset) == ReadGameUIArray(offset/4)


bool IsGaming()
{
	return (GetGameUI(0, 0) != 0);
}

uintptr_t current_function(uintptr_t ptr)
{
	static uint32 nop = 0xCCCCCCCC;
	for (; nop != *(uint32*)ptr; --ptr)
		;
	ptr += 4;
	return ptr;
}


uintptr_t search_GetGameUI()
{
	uintptr_t gameUI;

	gameUI = war3_searcher.search_string("EnableSelect");
	gameUI = *(uintptr_t*)(gameUI + 0x05);

	gameUI = base::warcraft3::next_opcode(gameUI, 0xE8, 5);
	gameUI = convert_function(gameUI);

	return gameUI;
}

uint32 search_version()
{
	static const char warcraft_version_string[] = "Warcraft III (build ";

	uintptr_t ptr;
	size_t size = sizeof(warcraft_version_string) - 1;
	ptr = war3_searcher.search_string_ptr(warcraft_version_string, size);
	if (!ptr)
	{
		return 0;
	}
	uint32 n = 0;
	ptr += size;
	while (isdigit(*(uint8_t*)ptr))
	{
		n = n * 10 + *(uint8_t*)ptr - '0';
		ptr++;
	}

	return n;
}


void async_initialize()
{
	DO_ONCE_NOTHREADSAFE()
	{
		base::warcraft3::jass::nf_register::event_add.connect([&]()
		{
			for (const JassNative& curNative : CustomNatives)
			{
				fast_call<void>(address_BindNative, curNative.func, curNative.name, curNative.param);
			}
		});
	}
}

bool AddNative(uintptr_t func, const char* name, const char* param)
{
	async_initialize();
	CustomNatives.push_back(JassNative(func, name, param));

	return true;
}





int32 g_iWheelDelta = 0;
int32 g_iTrigKey = -1;


float from_jReal(jReal val)
{
	return *(float*)&val;
}
jReal to_jReal(float val)
{
	return *(jReal*)&val;
}
const char* from_jString(jString val)
{
	if (!val)
		return nullptr;

	val = *(uint32*)((uint32)val + 8);

	if (!val)
		return nullptr;

	char* string = (char*)(*(uint32*)(val + 28));

	return utils::from_utf8(string);
}


jInteger jNATIVE jGetMouseX()
{
	return GetMouseX();
}
jInteger jNATIVE jGetMouseY()
{
	return GetMouseY();
}
jInteger jNATIVE jGetMouseXRelative()
{
	return GetMouseXRelative();
}
jInteger jNATIVE jGetMouseYRelative()
{
	return GetMouseYRelative();
}
jBoolean jNATIVE jIsKeyDown(jInteger Key)
{
	return IsKeyDown(Key);
}
jInteger jNATIVE jGetWindowWidth()
{
	return GetWindowWidth();
}
jInteger jNATIVE jGetWindowHeight()
{
	return GetWindowHeight();
}
jInteger jNATIVE jGetWindowX()
{
	return GetWindowX();
}
jInteger jNATIVE jGetWindowY()
{
	return GetWindowY();
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
jReal jNATIVE jFPS()
{
	return to_jReal(g_fFPS);
}
jReal jNATIVE jDeltaTime()
{
	return to_jReal(g_fDeltaTime);
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
		ResetDevice();
	}
}
jNothing jNATIVE jEnableAnisoFiltering(jBoolean bEnable, jInteger maxAnisotropy)
{
	g_bAnisoFiltering = bEnable;
	g_iMaxAnisotropy = maxAnisotropy;
}


jReal jNATIVE jGetMouseTerrainX()
{
	return to_jReal(MouseTerrain.x);
}
jReal jNATIVE jGetMouseTerrainY()
{
	return to_jReal(MouseTerrain.y);
}
jReal jNATIVE jGetMouseTerrainZ()
{
	return to_jReal(MouseTerrain.z);
}
jBoolean jNATIVE jIsMouseOverUI()
{
	return IsMouseOverUI();
}
jNothing jNATIVE jBlockMouse(jBoolean bBlock)
{
	BlockMouse(bBlock);
}


jNothing jNATIVE jHideInterface()
{
	uint32 pRootFrame = GetGameUI(0, 0) + 180;

	SetFramePoint(GameUI->UpperButtonBarFrame, EFramePoint::TopLeft, pRootFrame, EFramePoint::TopLeft, 0.0f, 1.0f);
	SetFramePoint(GameUI->ResourceBarFrame, EFramePoint::TopRight, pRootFrame, EFramePoint::TopRight, 0.0f, 1.0f);

	SetFramePoint(GameUI->SimpleConsole, EFramePoint::TopLeft, pRootFrame, EFramePoint::TopLeft, 10.0f, 0.0f);
	SetFramePoint(GameUI->SimpleConsole, EFramePoint::TopRight, pRootFrame, EFramePoint::TopRight, -10.0f, 0.0f);

	SetFramePoint(GameUI->Portrait + 180, EFramePoint::BottomLeft, pRootFrame, EFramePoint::BottomLeft, 1.0f, 1.0f);
	SetFramePoint(GameUI->Minimap + 180, EFramePoint::BottomLeft, pRootFrame, EFramePoint::BottomLeft, 1.0f, 1.0f);

	SetFramePoint(GameUI->PeonBar, EFramePoint::BottomLeft, pRootFrame, EFramePoint::BottomLeft, 1.0f, 1.0f);
	SetFramePoint(GameUI->HeroBar, EFramePoint::TopLeft, pRootFrame, EFramePoint::TopLeft, 0.0f, 1.0f);

	SetFramePoint(GameUI->TimeOfDayIndicator + 180, EFramePoint::BottomLeft, pRootFrame, EFramePoint::BottomLeft, 1.0f, 1.0f);
	SetFramePoint(*(uint32*)(GameUI->TimeOfDayIndicator + 432) + 180, EFramePoint::Top, pRootFrame, EFramePoint::Top, 1.0f, 0.0f);

	SetFramePoint(*(uint32*)(GameUI->InfoBar + 332), EFramePoint::BottomRight, pRootFrame, EFramePoint::TopLeft, 1.0f, 0.0f); // ConsoleInventoryCoverTexture
}
jNothing jNATIVE jEditBlackBorders(jInteger newUpperHeight, jInteger newBottomHeight)
{
	float upperHeight = newUpperHeight * 0.6f / GetWindowHeight();
	float bottomHeight = newBottomHeight * 0.6f / GetWindowHeight();

	uint32 pWorldFrameWar3 = GameUI->WorldFrameWar3 + 180;
	uint32 pRootFrame = GetGameUI(0, 0) + 180;

	SetFramePoint(pWorldFrameWar3, EFramePoint::TopRight, pRootFrame, EFramePoint::TopRight, 0.0f, -upperHeight);
	SetFramePoint(pWorldFrameWar3, EFramePoint::BottomLeft, pRootFrame, EFramePoint::BottomLeft, 0.0f, bottomHeight);
}
jNothing jNATIVE jEditPortrait(jInteger anchor, jInteger newX, jInteger newY, jInteger newWidth, jInteger newHeight)
{
	float x = newX * 0.8f / GetWindowWidth();
	float y = newY * 0.6f / GetWindowHeight();
	float width = newWidth * 0.8f / GetWindowWidth();
	float height = newHeight * 0.6f / GetWindowHeight();

	uint32 pPortraitFrame = GameUI->Portrait + 180;
	uint32 pRootFrame = GetGameUI(0, 0) + 180;

	if (newWidth >= 0) SetFrameWidth(pPortraitFrame, width);
	if (newHeight >= 0) SetFrameHeight(pPortraitFrame, height);
	SetFramePoint(pPortraitFrame, EFramePoint::BottomLeft, pRootFrame, EFramePoint(anchor), x, -(y + GetFrameHeight(pPortraitFrame)));
}
jNothing jNATIVE jEditMinimap(jInteger anchor, jInteger newX, jInteger newY, jInteger newWidth, jInteger newHeight)
{
	float x = newX * 0.8f / GetWindowWidth();
	float y = newY * 0.6f / GetWindowHeight();
	float width = newWidth * 0.8f / GetWindowWidth();
	float height = newHeight * 0.6f / GetWindowHeight();

	uint32 pMinimapFrame = GameUI->Minimap + 180;
	uint32 pRootFrame = GetGameUI(0, 0) + 180;

	SetFramePoint(pMinimapFrame, EFramePoint::BottomLeft, pRootFrame, EFramePoint(anchor), x, -(y + height));
	SetFramePoint(pMinimapFrame, EFramePoint::TopRight, pRootFrame, EFramePoint(anchor), x + width, -y);
}
jNothing jNATIVE jEditCommandBarButton(jInteger row, jInteger column, jInteger anchor, jInteger newX, jInteger newY, jInteger newWidth, jInteger newHeight)
{
	if (row < 0 || row > 2)
		return;
	if (column < 0 || column > 3)
		return;

	float x = newX * 0.8f / GetWindowWidth();
	float y = newY * 0.6f / GetWindowHeight();
	float width = newWidth * 0.8f / GetWindowWidth();
	float height = newHeight * 0.6f / GetWindowHeight();

	uint32 pButtonFrame = GetCommandBarButton(row, column);
	uint32 pRootFrame = GetGameUI(0, 0) + 180;

	if (newWidth >= 0) SetFrameWidth(pButtonFrame, width);
	if (newHeight >= 0) SetFrameHeight(pButtonFrame, height);
	SetFramePoint(pButtonFrame, EFramePoint::TopLeft, pRootFrame, EFramePoint(anchor), x, -y);
}
jNothing jNATIVE jEditHeroBarButton(jInteger buttonId, jInteger anchor, jInteger newX, jInteger newY, jInteger newWidth, jInteger newHeight)
{
	if (buttonId < 0 || buttonId > 6)
		return;

	float x = newX * 0.8f / GetWindowWidth();
	float y = newY * 0.6f / GetWindowHeight();
	float width = newWidth * 0.8f / GetWindowWidth();
	float height = newHeight * 0.6f / GetWindowHeight();

	uint32 pButtonFrame = GetHeroBarButton(buttonId);
	uint32 pRootFrame = GetGameUI(0, 0) + 180;

	if (newWidth >= 0) SetFrameWidth(pButtonFrame, width);
	if (newHeight >= 0) SetFrameHeight(pButtonFrame, height);
	SetFramePoint(pButtonFrame, EFramePoint::TopLeft, pRootFrame, EFramePoint(anchor), x, -y);
}
jNothing jNATIVE jEditItemBarButton(jInteger buttonId, jInteger anchor, jInteger newX, jInteger newY, jInteger newWidth, jInteger newHeight)
{
	if (buttonId < 0 || buttonId > 5)
		return;

	float x = newX * 0.8f / GetWindowWidth();
	float y = newY * 0.6f / GetWindowHeight();
	float width = newWidth * 0.8f / GetWindowWidth();
	float height = newHeight * 0.6f / GetWindowHeight();

	uint32 pButtonFrame = GetItemBarButton(buttonId);
	uint32 pRootFrame = GetGameUI(0, 0) + 180;

	if (newWidth >= 0) SetFrameWidth(pButtonFrame, width);
	if (newHeight >= 0) SetFrameHeight(pButtonFrame, height);
	SetFramePoint(pButtonFrame, EFramePoint::TopLeft, pRootFrame, EFramePoint(anchor), x, -y);
}
jNothing jNATIVE jEditMinimapButton(jInteger buttonId, jInteger anchor, jInteger newX, jInteger newY, jInteger newWidth, jInteger newHeight)
{
	if (buttonId < 0 || buttonId > 4)
		return;

	float x = newX * 0.8f / GetWindowWidth();
	float y = newY * 0.6f / GetWindowHeight();
	float width = newWidth * 0.8f / GetWindowWidth();
	float height = newHeight * 0.6f / GetWindowHeight();

	uint32 pButtonFrame = GameUI->MinimapButtons[buttonId];
	uint32 pRootFrame = GetGameUI(0, 0) + 180;

	if (newWidth >= 0) SetFrameWidth(pButtonFrame, width);
	if (newHeight >= 0) SetFrameHeight(pButtonFrame, height);
	SetFramePoint(pButtonFrame, EFramePoint::TopLeft, pRootFrame, EFramePoint(anchor), x, -y);
}
jNothing jNATIVE jEditUpperButtonBarButton(jInteger buttonId, jInteger anchor, jInteger newX, jInteger newY, jInteger newWidth, jInteger newHeight)
{
	if (buttonId < 0 || buttonId > 3)
		return;

	float x = newX * 0.8f / GetWindowWidth();
	float y = newY * 0.6f / GetWindowHeight();
	float width = newWidth * 0.8f / GetWindowWidth();
	float height = newHeight * 0.6f / GetWindowHeight();

	int32 pRootFrame = GetGameUI(0, 0) + 180;
	int32 pButtonFrame = GetUpperButtonBarButton(buttonId);

	if (newWidth >= 0) SetFrameWidth(pButtonFrame, width);
	if (newHeight >= 0) SetFrameHeight(pButtonFrame, height);
	if (buttonId == 0)
		SetFramePoint(pButtonFrame, EFramePoint::TopLeft, pRootFrame, EFramePoint(anchor), x, -y);
	else
		SetFramePoint(pButtonFrame, EFramePoint::Left, pRootFrame, EFramePoint(anchor), x, -(y + GetFrameHeight(pButtonFrame) / 2));
}


jNothing jNATIVE jCtrlSetSize(jInteger id, jInteger width, jInteger height)
{
	if (id >= 0)
		MainGUI->SetSize(id, width, height);
}
jNothing jNATIVE jCtrlSetAnchor(jInteger id, jInteger parentId, jInteger anchor)
{
	if (id >= 0)
		MainGUI->SetAnchor(id, parentId, static_cast<Anchor>(anchor));
}
jNothing jNATIVE jCtrlSetPosition(jInteger id, jInteger offsetX, jInteger offsetY)
{
	if (id >= 0)
		MainGUI->SetPosition(id, offsetX, offsetY);
}
jNothing jNATIVE jCtrlNew(jInteger id, jInteger offsetX, jInteger offsetY, jInteger width, jInteger height)
{
	if (id >= 0)
		MainGUI->New(id, offsetX, offsetY, width, height);
}
jNothing jNATIVE jCtrlSetTexture(jInteger id, jString filename)
{
	if (id >= 0)
		MainGUI->SetTexture(id, from_jString(filename));
}
jNothing jNATIVE jCtrlSetColor(jInteger id, jInteger argb)
{
	if (id >= 0)
		MainGUI->SetColor(id, argb);
}
jNothing jNATIVE jCtrlSetText(jInteger id, jString newtext, jBoolean bWrap)
{
	if (id >= 0)
		MainGUI->SetText(id, from_jString(newtext), bWrap);
}
jNothing jNATIVE jCtrlSetTextAlignment(jInteger id, jInteger alignment)
{
	if (id >= 0)
		MainGUI->SetTextAlignment(id, static_cast<TextAlignment>(alignment));
}
jNothing jNATIVE jCtrlShow(jInteger id, jBoolean isShow)
{
	if (id >= 0)
		MainGUI->Show(id, isShow);
}
jNothing jNATIVE jCtrlSetDepth(jInteger id, jReal* fDepth)
{
	if (id >= 0)
		MainGUI->SetDepth(id, from_jReal(*fDepth));
}
jNothing jNATIVE jCtrlSetZOrder(jInteger id, jInteger iZOrder)
{
	if (id >= 0)
		MainGUI->SetZOrder(id, iZOrder);
}
jNothing jNATIVE jCtrlSetAngle(jInteger id, jReal* fAngle)
{
	if (id >= 0)
		MainGUI->SetAngle(id, from_jReal(*fAngle));
}
jInteger jNATIVE jCtrlGetFromPoint(jInteger x, jInteger y)
{
	return MainGUI->GetCtrlFromPoint(x, y);
}
jInteger jNATIVE jCtrlGetWidth(jInteger id)
{
	if (id >= 0)
		return MainGUI->GetWidth(id);
	return 0;
}
jInteger jNATIVE jCtrlGetHeight(jInteger id)
{
	if (id >= 0)
		return MainGUI->GetHeight(id);
	return 0;
}
jNothing jNATIVE jCtrlSetFont(jInteger id, jString name, jInteger size)
{
	if (id >= 0)
		MainGUI->SetFont(id, from_jString(name), size);
}
jBoolean jNATIVE jCtrlIsText(jInteger id)
{
	if (id >= 0)
		return MainGUI->IsText(id);
	return jFalse;
}
jNothing jNATIVE jGUILoadFont(jString fileName)
{
	MainFontManager->LoadFontFromMPQ(from_jString(fileName));
}


std::list<jTrigger> MouseWheelTriggers;
std::list<jTrigger> MouseMoveTriggers;
std::list<jTrigger> WindowResizeTriggers;
std::list<jTrigger> FrameUpdateTriggers;
std::list<std::pair<jTrigger, jInteger>> MouseDownTriggers;
std::list<std::pair<jTrigger, jInteger>> MouseUpTriggers;
std::list<std::pair<jTrigger, jInteger>> KeyDownTriggers;
std::list<std::pair<jTrigger, jInteger>> KeyUpTriggers;

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
	if (jass::TriggerEvaluate(trigger))
		jass::TriggerExecute(trigger);
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
	if (MainEngine->bMapInit)
	{
		g_iTrigKey = key;
		for (auto trigger : ((state == 0) ? KeyDownTriggers : KeyUpTriggers))
			if (trigger.second == key || trigger.second == -1)
				RunTrigger(trigger.first);
	}
}
void ExecuteMouseTriggers(int32 button, int32 state)
{
	if (MainEngine->bMapInit)
	{
		g_iTrigKey = button;
		for (auto trigger : ((state == 0) ? MouseDownTriggers : MouseUpTriggers))
			if (trigger.second == button || trigger.second == -1)
				RunTrigger(trigger.first);
	}
}
void ExecuteWheelTriggers(int32 delta)
{
	if (MainEngine->bMapInit)
	{
		g_iWheelDelta = delta;
		for (auto trigger : MouseWheelTriggers)
			RunTrigger(trigger);
	}
}
void ExecuteMouseMoveTriggers(int32 x, int32 y)
{
	if (MainEngine->bMapInit)
	{
		for (auto trigger : MouseMoveTriggers)
			RunTrigger(trigger);
	}
}
void ExecuteWindowResizeTriggers()
{
	if (MainEngine->bMapInit)
	{
		for (auto trigger : WindowResizeTriggers)
			RunTrigger(trigger);
	}
}
void ExecuteFrameUpdateTriggers()
{
	if (MainEngine->bMapInit)
	{
		for (auto trigger : FrameUpdateTriggers)
			RunTrigger(trigger);
	}
}


bool JassApiInit()
{
	LOG(logDEBUG) << "========= On JassAPI Init Start =======";
	LOG(logDEBUG) << "address_GameBase:\t0x" << std::hex << address_GameBase;

	War3Version = search_version();

	address_BindNative = search_BindNative();
	address_GetGameUI = search_GetGameUI();

	base::warcraft3::jass::nf_register::initialize();


	LOG(logDEBUG) << "address_BindNative:\t0x" << std::hex << address_BindNative;
	LOG(logDEBUG) << "address_GetGameUI:\t0x" << std::hex << address_GetGameUI;

	AddNative((uintptr_t)jGetMouseXRelative, "GetMouseXRelative", "()I");
	AddNative((uintptr_t)jGetMouseYRelative, "GetMouseYRelative", "()I");
	AddNative((uintptr_t)jGetMouseX, "GetMouseX", "()I");
	AddNative((uintptr_t)jGetMouseY, "GetMouseY", "()I");
	AddNative((uintptr_t)jSetMousePos, "SetMousePos", "(II)");
	AddNative((uintptr_t)jGetWheelDelta, "GetWheelDelta", "()I");
	AddNative((uintptr_t)jGetMouseTerrainX, "GetMouseTerrainX", "()R");
	AddNative((uintptr_t)jGetMouseTerrainY, "GetMouseTerrainY", "()R");
	AddNative((uintptr_t)jGetMouseTerrainZ, "GetMouseTerrainZ", "()R");
	AddNative((uintptr_t)jIsMouseOverUI, "IsMouseOverUI", "()B");
	AddNative((uintptr_t)jBlockMouse, "BlockMouse", "(B)V");

	AddNative((uintptr_t)jIsKeyDown, "IsKeyDown", "(I)B");
	AddNative((uintptr_t)jGetTriggerKey, "GetTriggerKey", "()I");
	AddNative((uintptr_t)jTriggerRegisterMouseWheelEvent, "TriggerRegisterMouseWheelEvent", "(Htrigger;)V");
	AddNative((uintptr_t)jTriggerRegisterMouseMoveEvent, "TriggerRegisterMouseMoveEvent", "(Htrigger;)V");
	AddNative((uintptr_t)jTriggerRegisterMouseEvent, "TriggerRegisterMouseEvent", "(Htrigger;II)V");
	AddNative((uintptr_t)jTriggerRegisterKeyEvent, "TriggerRegisterKeyEvent", "(Htrigger;II)V");

	AddNative((uintptr_t)jGetWindowWidth, "GetWindowWidth", "()I");
	AddNative((uintptr_t)jGetWindowHeight, "GetWindowHeight", "()I");
	AddNative((uintptr_t)jGetWindowX, "GetWindowX", "()I");
	AddNative((uintptr_t)jGetWindowY, "GetWindowY", "()I");
	AddNative((uintptr_t)jTriggerRegisterWindowResizeEvent, "TriggerRegisterWindowResizeEvent", "(Htrigger;)V");

	AddNative((uintptr_t)jFPS, "GetFPS", "()R");
	AddNative((uintptr_t)jDeltaTime, "GetDeltaTime", "()R");
	AddNative((uintptr_t)jCOLOR_ARGB, "COLOR_ARGB", "(IIII)I");
	AddNative((uintptr_t)jEnableVsync, "EnableVsync", "(B)V");
	AddNative((uintptr_t)jTriggerRegisterFrameUpdateEvent, "TriggerRegisterFrameUpdateEvent", "(Htrigger;)V");
	AddNative((uintptr_t)jIsGamePaused, "IsGamePaused", "()B");
	AddNative((uintptr_t)jEnableAnisoFiltering, "EnableAnisoFiltering", "(BI)V");

	AddNative((uintptr_t)jCtrlNew, "CtrlNew", "(IIIII)V");
	AddNative((uintptr_t)jCtrlSetColor, "CtrlSetColor", "(II)V");
	AddNative((uintptr_t)jCtrlSetTexture, "CtrlSetTexture", "(IS)V");
	AddNative((uintptr_t)jCtrlSetText, "CtrlSetText", "(ISB)V");
	AddNative((uintptr_t)jCtrlSetTextAlignment, "CtrlSetTextAlignment", "(II)V");
	AddNative((uintptr_t)jCtrlSetSize, "CtrlSetSize", "(III)V");
	AddNative((uintptr_t)jCtrlSetPosition, "CtrlSetPosition", "(III)V");
	AddNative((uintptr_t)jCtrlSetAnchor, "CtrlSetAnchor", "(III)V");
	AddNative((uintptr_t)jCtrlShow, "CtrlShow", "(IB)V");
	AddNative((uintptr_t)jCtrlSetDepth, "CtrlSetDepth", "(IR)V");
	AddNative((uintptr_t)jCtrlSetZOrder, "CtrlSetZOrder", "(II)V");
	AddNative((uintptr_t)jCtrlSetAngle, "CtrlSetAngle", "(IR)V");
	AddNative((uintptr_t)jCtrlGetWidth, "CtrlGetWidth", "(I)I");
	AddNative((uintptr_t)jCtrlGetHeight, "CtrlGetHeight", "(I)I");
	AddNative((uintptr_t)jCtrlGetFromPoint, "CtrlGetFromPoint", "(II)I");
	AddNative((uintptr_t)jCtrlIsText, "CtrlIsText", "(I)B");
	AddNative((uintptr_t)jCtrlSetFont, "CtrlSetFont", "(ISI)V");
	AddNative((uintptr_t)jGUILoadFont, "GUILoadFont", "(S)V");

	AddNative((uintptr_t)jHideInterface, "HideInterface", "()V");
	AddNative((uintptr_t)jEditBlackBorders, "EditBlackBorders", "(II)V");
	AddNative((uintptr_t)jEditPortrait, "EditPortrait", "(IIIII)V");
	AddNative((uintptr_t)jEditMinimap, "EditMinimap", "(IIIII)V");
	AddNative((uintptr_t)jEditCommandBarButton, "EditCommandBarButton", "(IIIIIII)V");
	AddNative((uintptr_t)jEditHeroBarButton, "EditHeroBarButton", "(IIIIII)V");
	AddNative((uintptr_t)jEditItemBarButton, "EditItemBarButton", "(IIIIII)V");
	AddNative((uintptr_t)jEditMinimapButton, "EditMinimapButton", "(IIIIII)V");
	AddNative((uintptr_t)jEditUpperButtonBarButton, "EditUpperButtonBarButton", "(IIIIII)V");
	LOG(logDEBUG) << "========= On JassAPI Init End =========";

	return true;
}