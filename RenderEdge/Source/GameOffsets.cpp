#include "GameOffsets.h"
#include "JassApi.h"
#include "Engine.h"

uintptr_t address_MouseEvent = 0;
uintptr_t address_WndProc = 0;

uintptr_t address_localDelay = 0;
uintptr_t address_lanDelay = 0;
uintptr_t address_netDelay = 0;

uintptr_t address_BuildHPBars = 0;
uintptr_t address_CreateProjMatrix = 0;
uintptr_t address_LockFPS = 0;
uintptr_t address_LockTextureSizeCmp = 0;
uintptr_t address_LockTextureSizeMov = 0;
uintptr_t address_SetCameraField = 0;
uintptr_t address_SetCameraField_misc = 0;

uintptr_t address_render_state_sequence = 0;
uintptr_t address_render_target_switch = 0;
uintptr_t address_render_target_switch_default_case = 0;
uintptr_t address_render_mesh = 0;
uintptr_t address_render_particle = 0;
uintptr_t address_render_UnitAndEffect_func = 0;
uintptr_t address_render_Unknown1_func = 0;
uintptr_t address_render_MayjorUI_func = 0;
uintptr_t address_render_MinorUI_func = 0;
uintptr_t address_render_MiniMap_func = 0;

uintptr_t address_SetFramePoint = 0;
uintptr_t address_SetFramePoint2 = 0;
uintptr_t address_SetFrameWidth = 0;
uintptr_t address_SetFrameHeight = 0;
uintptr_t address_DisableUI = 0;


void InitGameOffsets()
{
	if (GetGameVersion() == GameVersion::v128f)
	{
		// signed int32 __stdcall MouseEvent(int32 a1, int32 a2, int32 a3, int32 a4)

		address_MouseEvent =                        address_GameBase + 0x0;
		address_WndProc =                           address_GameBase + 0x0;

		address_BuildHPBars =                       address_GameBase + 0x0;
		address_CreateProjMatrix =                  address_GameBase + 0x1554F0;
		address_LockFPS =                           address_GameBase + 0x0;
		address_LockTextureSizeCmp =                address_GameBase + 0x0;
		address_LockTextureSizeMov =                address_GameBase + 0x0;
		address_SetCameraField =                    address_GameBase + 0x0;
		address_SetCameraField_misc =               address_GameBase + 0x0;

		address_localDelay =                        address_GameBase + 0x0;
		address_lanDelay =                          address_GameBase + 0x0;
		address_netDelay =                          address_GameBase + 0x0;

		address_render_state_sequence =             address_GameBase + 0x0;
		address_render_target_switch =              address_GameBase + 0x0;
		address_render_target_switch_default_case = address_GameBase + 0x0;
		address_render_mesh =                       address_GameBase + 0x0;
		address_render_particle =                   address_GameBase + 0x0;
		address_render_UnitAndEffect_func =         address_GameBase + 0x0;
		address_render_Unknown1_func =              address_GameBase + 0x0;
		address_render_MayjorUI_func =              address_GameBase + 0x0;
		address_render_MinorUI_func =               address_GameBase + 0x0;
		address_render_MiniMap_func =               address_GameBase + 0x0;

		address_SetFramePoint =                     address_GameBase + 0x0;
		address_SetFramePoint2 =                    address_GameBase + 0x0;
		address_SetFrameWidth =                     address_GameBase + 0x0;
		address_SetFrameHeight =                    address_GameBase + 0x0;
	}
	else if (GetGameVersion() == GameVersion::v126a)
	{
		address_MouseEvent =                        address_GameBase + 0x398EA0;
		address_WndProc =                           address_GameBase + 0x52C9C0;

		address_BuildHPBars =                       address_GameBase + 0x379A30;
		address_CreateProjMatrix =                  address_GameBase + 0x7B66F0;
		address_LockFPS =                           address_GameBase + 0x62D7F9;
		address_LockTextureSizeCmp =                address_GameBase + 0x52D35E;
		address_LockTextureSizeMov =                address_GameBase + 0x52D375;
		address_SetCameraField =                    address_GameBase + 0x305A60;
		address_SetCameraField_misc =               address_GameBase + 0x03FA30;

		address_localDelay =                        address_GameBase + 0x660F01;
		address_lanDelay =                          address_GameBase + 0x661A91;
		address_netDelay =                          address_GameBase + 0x65DE41;

		address_render_state_sequence =             address_GameBase + 0x5FD84D;
		address_render_target_switch =              address_GameBase + 0x395696;
		address_render_target_switch_default_case = address_GameBase + 0x395899;
		address_render_mesh =                       address_GameBase + 0x50B9CB;
		address_render_particle =                   address_GameBase + 0x50B9E7;
		address_render_UnitAndEffect_func =         address_GameBase + 0x395900;
		address_render_Unknown1_func =              address_GameBase + 0x33AE70;
		address_render_MayjorUI_func =              address_GameBase + 0x60C580;
		address_render_MinorUI_func =               address_GameBase + 0x60EA80;
		address_render_MiniMap_func =               address_GameBase + 0x347F40;

		address_SetFramePoint =                     address_GameBase + 0x606770;
		address_SetFramePoint2 =                    address_GameBase + 0x6061B0;
		address_SetFrameWidth =                     address_GameBase + 0x605D90;
		address_SetFrameHeight =                    address_GameBase + 0x605DB0;
	}
}