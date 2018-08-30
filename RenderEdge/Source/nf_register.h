#pragma once

#include "signal.h"
#include <cstdint>

namespace base { namespace warcraft3 { namespace jass { namespace nf_register {
	extern signal<void, uintptr_t> event_hook;
	extern signal<void, void>      event_add;
	bool initialize();
}}}} 

extern int32_t TlsValue;