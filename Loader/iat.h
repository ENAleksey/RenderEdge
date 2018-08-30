#pragma once

#include <Windows.h>

namespace base { namespace hook {	
	uintptr_t iat(HMODULE module_handle,      const char* dll_name, const char* api_name, uintptr_t new_function);
	uintptr_t iat(const wchar_t* module_name, const char* dll_name, const char* api_name, uintptr_t new_function);
}}
