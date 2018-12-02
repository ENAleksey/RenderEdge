#include "Detour.h"

#include <Windows.h>
#include <detours.h>

namespace Detour
{
	bool Install(uintptr_t* pointer_ptr, uintptr_t detour)
	{
		if (DetourTransactionBegin() == NO_ERROR)
		{
			if (DetourUpdateThread(GetCurrentThread()) == NO_ERROR)
			{
				if (DetourAttach((PVOID*)pointer_ptr, (PVOID)detour) == NO_ERROR)
				{
					if (DetourTransactionCommit() == NO_ERROR)
					{
						return true;
					}
				}
			}
			DetourTransactionAbort();
		}

		return false;
	}

	bool Uninstall(uintptr_t* pointer_ptr, uintptr_t detour)
	{
		if (DetourTransactionBegin() == NO_ERROR)
		{
			if (DetourUpdateThread(GetCurrentThread()) == NO_ERROR)
			{
				if (DetourDetach((PVOID*)pointer_ptr, (PVOID)detour) == NO_ERROR)
				{
					if (DetourTransactionCommit() == NO_ERROR)
					{
						return true;
					}
				}
			}
			DetourTransactionAbort();
		}
		
		return false;
	}
}