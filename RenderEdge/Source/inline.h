#pragma once

#include <cstdint>

namespace base { namespace hook {  
#if !defined(DISABLE_DETOURS)
	bool inline_install(uintptr_t* pointer_ptr, uintptr_t detour);
	bool inline_uninstall(uintptr_t* pointer_ptr, uintptr_t detour);
#endif
	uintptr_t replace_pointer(uintptr_t address, uintptr_t new_value);
}}
