#include "GameHook.h"
#include "Engine.h"
#include "GameOffsets.h"

namespace HOOK {
	static DWORD next_line;
	volatile DWORD g_CurrentRenderTarget;
	volatile RENDER_TYPE g_CurrentRenderType;
	volatile DWORD currentRenderCall;
	
	uintptr_t address_render_mesh_real_func = 0;
	uintptr_t address_render_particle_real_func = 0;

	//
	// Trampoline functions
	//
	#pragma warning(push)
	#pragma warning(disable : 4740)


	void JmpPatch(void* pDest, void* pSrc, int32 nNops)
	{
		DWORD OldProt;
		VirtualProtect(pSrc, 5 + nNops, PAGE_EXECUTE_READWRITE, &OldProt);
		*(BYTE*)pSrc = (BYTE)0xE9;
		*(DWORD*)((DWORD)pSrc + 1) = (DWORD)pDest - (DWORD)pSrc - 5;
		for (int32 i = 0; i < nNops; ++i)
			*(BYTE*)((DWORD)pSrc + 5 + i) = 0x90;
		VirtualProtect(pSrc, 5 + nNops, OldProt, &OldProt);
	}

	// Read the function pointer from a call or a jmp
	DWORD getFuncPtr(DWORD address)
	{
		return *(DWORD*)address + address + 4;
	}


	__declspec (naked) void render_state_sequence()
	{
		__asm
		{
			mov edx, [eax+0x30];
			mov ecx, edi;
			pushad;
			mov [currentRenderCall], edx;
		}

		next_line = address_render_state_sequence + 5;

		__asm
		{
			popad;
			jmp [next_line];
		}
	}
	__declspec (naked) void render_target_switch()
	{
		// Save all registers
		__asm 
		{
			pushad;
			mov [g_CurrentRenderTarget], eax;
		}

		next_line = address_render_target_switch + 9; // 9 bytes after the original address

		// Restore the original code
		__asm
		{
			popad;
			cmp eax, 0x15
			ja default_case;
			jmp [next_line];
		default_case:
			jmp [address_render_target_switch_default_case];
		}
	}
	__declspec (naked) void render_mesh()
	{
		__asm pushad;

		g_CurrentRenderType = D3D_MESH;
		next_line = address_render_mesh + 5;

		__asm
		{
			popad;
			call address_render_mesh_real_func;
			jmp next_line;
		}
	}
	__declspec (naked) void render_particle()
	{
		__asm pushad;

		g_CurrentRenderType = D3D_PARTICLE;
		next_line = address_render_particle + 5;

		__asm
		{
			popad;
			call [address_render_particle_real_func];
			jmp next_line;
		}
	}
	#pragma warning(pop)

	bool deployHooks()
	{
		address_render_mesh_real_func = getFuncPtr(address_render_mesh+1);
		address_render_particle_real_func = getFuncPtr(address_render_particle+1);

		JmpPatch(render_state_sequence, (void*)address_render_state_sequence);
		JmpPatch(render_target_switch, (void*)address_render_target_switch, 4);
		JmpPatch(render_mesh, (void*)address_render_mesh);
		JmpPatch(render_particle, (void*)address_render_particle);

		return true;
	}

	RENDER_STATE getCurrentRenderState()
	{
		int32 offest = currentRenderCall;
		if (offest == address_render_UnitAndEffect_func)
		{
			return STATE_UNIT_AND_EFFECT;
		}
		else if (offest == address_render_Unknown1_func)
		{
			return STATE_PORTRAIT;
		}
		else if (offest == address_render_MayjorUI_func)
		{
			return STATE_MAYJOR_UI;
		}
		else if (offest == address_render_MinorUI_func)
		{
			return STATE_MINOR_UI;
		}
		else if (offest == address_render_MiniMap_func)
		{
			return STATE_MINI_MAP;
		}
		return STATE_NULL;
	}
}