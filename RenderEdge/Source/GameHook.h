#pragma once

#include <Windows.h>
#include "int_t.h"

namespace HOOK {
	enum RENDER_TYPE { D3D_MESH, D3D_PARTICLE };
	enum RENDER_STATE { STATE_NULL, STATE_UNIT_AND_EFFECT, STATE_PORTRAIT, STATE_MAYJOR_UI, STATE_MINOR_UI, STATE_MINI_MAP };

	void JmpPatch(void* pDest, void* pSrc, int32 nNops = 0);
	DWORD getFuncPtr(DWORD address);

	extern uintptr_t address_render_mesh_real_func;
	extern uintptr_t address_render_particle_real_func;

	// Globals values
	extern volatile DWORD g_CurrentRenderTarget;
	extern volatile RENDER_TYPE g_CurrentRenderType;

	// Deploy hooks to capture render call
	bool deployHooks();
	RENDER_STATE getCurrentRenderState();
}