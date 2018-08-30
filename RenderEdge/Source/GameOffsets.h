#pragma once
#include <cstdint>

extern uintptr_t address_MouseEvent;
extern uintptr_t address_WndProc;

extern uintptr_t address_localDelay;
extern uintptr_t address_lanDelay;
extern uintptr_t address_netDelay;

extern uintptr_t address_BuildHPBars;
extern uintptr_t address_CreateProjMatrix;
extern uintptr_t address_LockFPS;
extern uintptr_t address_LockTextureSizeCmp;
extern uintptr_t address_LockTextureSizeMov;
extern uintptr_t address_SetCameraField;
extern uintptr_t address_SetCameraField_misc;

extern uintptr_t address_render_state_sequence;
extern uintptr_t address_render_target_switch;
extern uintptr_t address_render_target_switch_default_case;
extern uintptr_t address_render_mesh;
extern uintptr_t address_render_particle;
extern uintptr_t address_render_UnitAndEffect_func;
extern uintptr_t address_render_Unknown1_func;
extern uintptr_t address_render_MayjorUI_func;
extern uintptr_t address_render_MinorUI_func;
extern uintptr_t address_render_MiniMap_func;

extern uintptr_t address_SetFramePoint;
extern uintptr_t address_SetFramePoint2;
extern uintptr_t address_SetFrameWidth;
extern uintptr_t address_SetFrameHeight;

void InitGameOffsets();