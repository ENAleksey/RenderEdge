#pragma once

#include "Utils.h"

enum class EFramePoint : uint32
{
	TopLeft = 0,
	Top = 1,
	TopRight = 2,
	Left = 3,
	Center = 4,
	Right = 5,
	BottomLeft = 6,
	Bottom = 7,
	BottomRight = 8
};

struct CGameUI
{
	int VirtualTable; // 0
	int field0004;
	int field0008;
	int field000C;
	int field0010;
	int field0014;
	int field0018;
	int field001C;
	int field0020;
	int field0024;
	int field0028;
	int field002C;
	int field0030;
	int field0034;
	int field0038;
	int field003C;
	int field0040;
	int field0044;
	int field0048;
	int field004C;
	int field0050;
	int field0054;
	int field0058;
	int field005C;
	int field0060;
	int field0064;
	int field0068;
	int field006C;
	int field0070;
	int field0074;
	int field0078;
	int field007C;
	int field0080;
	int field0084;
	int field0088;
	int field008C;
	int field0090;
	int field0094;
	int field0098;
	int field009C;
	int field00A0;
	int field00A4;
	int field00A8;
	int field00AC;
	int field00B0;
	uint32 Frame;
	int field00B8;
	int field00BC;
	int field00C0;
	int field00C4;
	int field00C8;
	int field00CC;
	int field00D0;
	int field00D4;
	int field00D8;
	int field00DC;
	int field00E0;
	int field00E4;
	int field00E8;
	int field00EC;
	int field00F0;
	int field00F4;
	int field00F8;
	int field00FC;

	int field0100; // 64
	int field0104;
	int field0108;
	int field010C;
	int field0110;
	int field0114;
	int field0118;
	int field011C;
	int field0120;
	int field0124;
	int field0128;
	int field012C;
	int field0130;
	int field0134;
	int field0138;
	int field013C;
	int field0140;
	int field0144;
	int field0148;
	int field014C;
	int field0150;
	int field0154;
	int field0158;
	int field015C;
	int field0160;
	int field0164;
	int field0168;
	int field016C;
	int field0170;
	int field0174;
	int field0178;
	int field017C;
	int field0180;
	int field0184;
	int field0188;
	int field018C;
	int field0190;
	int field0194;
	int field0198;
	int field019C;
	int field01A0;
	int field01A4;
	int field01A8;
	int isUserInputEnabled;
	int isUserInterfaceEnabled;
	int field01B4;
	int field01B8;
	int field01BC;
	int field01C0;
	int field01C4;
	int field01C8;
	int field01CC;
	int field01D0;
	int field01D4;
	int field01D8;
	int field01DC;
	int field01E0;
	int field01E4;
	int field01E8;
	int field01EC;
	int field01F0;
	int field01F4;
	int field01F8;
	int field01FC;

	int field0200; // 128
	int field0204;
	int field0208;
	int field020C;
	int field0210;
	int field0214;
	int field0218;
	int field021C;
	int field0220;
	int field0224;
	int field0228;
	int field022C;
	int field0230;
	int field0234;
	int field0238;
	int field023C;
	int field0240;
	int field0244;
	int field0248;
	int field024C;
	int field0250;
	int Camera;
	int isInGameMenu;
	int field025C;
	int isGamePaused;
	int field0264;
	int field0268;
	int field026C;
	int field0270;
	int field0274;
	int field0278;
	int field027C;
	int field0280;
	int field0284;
	int field0288;
	int field028C;
	int isDragSelectionEnabled;
	int isDragSelectionVisible;
	int isPreSelectionEnabled;
	int isPreSelectionVisible;
	int isSelectionEnabled;
	int isSelectionVisible;
	int field02A8;
	int field02AC;
	int field02B0;
	int field02B4;
	int field02B8;
	int field02BC;
	int field02C0;
	int field02C4;
	int field02C8;
	int field02CC;
	int field02D0;
	int field02D4;
	int field02D8;
	int field02DC;
	int field02E0;
	int field02E4;
	int field02E8;
	int field02EC;
	int field02F0;
	int field02F4;
	int field02F8;
	int field02FC;

	int field0300; // 192
	int field0304;
	int field0308;
	int field030C;
	int field0310;
	int field0314;
	int field0318;
	int field031C;
	int field0320;
	int field0324;
	int field0328;
	int field032C;
	int field0330;
	int field0334;
	int field0338;
	int field033C;
	int field0340;
	int field0344;
	int field0348;
	int field034C;
	int field0350;
	int field0354;
	int field0358;
	int field035C;
	int field0360;
	int field0364;
	int field0368;
	int field036C;
	int field0370;
	int field0374;
	int field0378;
	int field037C;
	int field0380;
	int field0384;
	int field0388;
	int field038C;
	int field0390;
	int field0394;
	int field0398;
	int field039C;
	int field03A0;
	int field03A4;
	int field03A8;
	int field03AC;
	int field03B0;
	int field03B4;
	int field03B8;
	uint32 WorldFrameWar3; // CWorldFrameWar3*
	uint32 Minimap; // CFrame*
	uint32 InfoBar;
	uint32 CommandBar;
	uint32 ResourceBarFrame;
	uint32 UpperButtonBarFrame;
	int field03D4; // BYTE[4]
	uint32 ClickableBlock;
	uint32 HeroBar;
	uint32 PeonBar;
	uint32 Message; // CSimpleMessageFrame*
	uint32 UnitMessage; // CSimpleMessageFrame*
	uint32 ChatMessage; // CSimpleMessageFrame*
	uint32 TopMessage; // CSimpleMessageFrame*
	uint32 Portrait; // CFrame*
	uint32 TimeOfDayIndicator; // CFrame*
	uint32 ChatEditBar;

	uint32 CinematicPanel; // 256
	int field0404;
	uint32 MinimapButtons[5]; // BYTE[20]
	/*uint32 MinimapButton1;
	uint32 MinimapButton2;
	uint32 MinimapButton3;
	uint32 MinimapButton4;
	uint32 MinimapButton5;*/
	uint32 FrameB; // CFrame*
	uint32 MouseBorders;
	uint32 FrameA; // CFrame*
	uint32 SimpleConsole;
	int QuickSaveHotKey;
	int QuickLoadHotKey;
	int QuickHelpHotKey;
	int QuickOptionsHotKey;
	int QuickQuitHotKey;
	int MinimapSignalHotKey;
	int MinimapTerrainHotKey;
	int MinimapColorsHotKey;
	int MinimapCreepsHotKey;
	int FormationToggleHotKey;
};

CGameUI* GetGameUI(uint32 unk0, uint32 unk1);
uint32 GetGameCamera();
uint32 GetWorldFrame();
bool IsInGameMenu();
bool IsGamePaused();
bool IsGaming();

void SetFramePoint(uint32 pFrame, EFramePoint point, uint32 pParentFrame, EFramePoint relativePoint, float offsetX, float offsetY);
void SetFrameWidth(uint32 pFrame, float width);
void SetFrameHeight(uint32 pFrame, float height);
float GetFrameWidth(uint32 pFrame);
float GetFrameHeight(uint32 pFrame);
uint32 GetFramePoint(uint32 pFrame, EFramePoint point);
uint32 GetFramePointParent(uint32 pFrame, EFramePoint point);
uint32 GetFramePointRelativePoint(uint32 pFrame, EFramePoint point);
float GetFramePointX(uint32 pFrame, EFramePoint point);
float GetFramePointY(uint32 pFrame, EFramePoint point);
D3DXVECTOR2 GetFramePointPos(uint32 pFrame, EFramePoint point);
void SetFrameText(uint32 pFrame, const char* text);
void SetFrameText(uint32 pFrame, const std::string& text);

uint32 GetPanelButton(uint32 pFrame, uint8 row, uint8 column);
uint32 GetUpperButtonBarButton(uint8 id);
uint32 GetCommandBarButton(uint8 row, uint8 column);
uint32 GetItemBarButton(uint8 id);
uint32 GetHeroBarButton(uint8 id);