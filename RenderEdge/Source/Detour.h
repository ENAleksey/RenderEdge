#pragma once

#include <cstdint>

namespace Detour
{
	bool Install(uintptr_t* pointer_ptr, uintptr_t detour);
	bool Uninstall(uintptr_t* pointer_ptr, uintptr_t detour);
}