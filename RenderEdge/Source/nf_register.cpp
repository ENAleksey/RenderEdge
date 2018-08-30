#include "nf_register.h"
#include "iat.h"
#include "do_once.h"
#include "fp_call.h"
#include "JassApi.h"

int32_t TlsValue;


namespace base { namespace warcraft3 { namespace jass { namespace nf_register {

	signal<void, uintptr_t> event_hook;
	signal<void, void>      event_add;
	uintptr_t               thread_id = 0;
	uintptr_t               stat = 0;
	uintptr_t               real_storm_alloc = 0;
	uintptr_t               real_tls_get_value = 0;

	uintptr_t __stdcall fake_storm_alloc(uint32_t amount, const char* log_filename, uint32_t log_line, uint32_t default_value)
	{
		uintptr_t retval = std_call<uintptr_t>(real_storm_alloc, amount, log_filename, log_line, default_value);

		if ((amount == 176)
			&& (log_line == 668)
			&& (default_value == 0)
			&& (strcmp(log_filename, "Jass.cpp") == 0))
		{
			stat = 1;
			thread_id = ::GetCurrentThreadId();
		}
		else if (stat == 3)
		{
			if (thread_id == ::GetCurrentThreadId())
			{
				if ((amount == 140)
					&& (log_line == 90)
					&& (default_value == 0)
					&& (strcmp(log_filename, "Agile.cpp") == 0))
				{
					stat = 0;
					event_hook(retval);
				}
			}
		}

		return retval;
	}

	uintptr_t __stdcall fake_storm_alloc_126(uint32_t amount, const char* log_filename, uint32_t log_line, uint32_t default_value)
	{
		uintptr_t retval = std_call<uintptr_t>(real_storm_alloc, amount, log_filename, log_line, default_value);

		if ((amount == 176)
			&& (log_line == 668)
			&& (default_value == 0)
			&& (strcmp(log_filename, ".\\Jass.cpp") == 0))
		{
			stat = 1;
			thread_id = ::GetCurrentThreadId();
		}
		else if (stat == 3)
		{
			if (thread_id == ::GetCurrentThreadId())
			{
				if ((amount == 140)
					&& (log_line == 90)
					&& (default_value == 0)
					&& (strcmp(log_filename, ".\\Agile.cpp") == 0))
				{
					stat = 0;
					event_hook(retval);
				}
			}
		}

		return retval;
	}

	uintptr_t __stdcall fake_tls_get_value(uint32_t tls_index)
	{
		if ((stat != 0) && (thread_id == ::GetCurrentThreadId()))
		{
			if (stat == 1)
			{
				stat = 2;
			}
			else if (stat == 2)
			{
				stat = 3;
				event_add();
			}
		}

		TlsValue = std_call<uintptr_t>(real_tls_get_value, tls_index);


		return TlsValue;
	}

	bool initialize()
	{
		DO_ONCE_NOTHREADSAFE()
		{
			if (GetGameVersion() == GameVersion::v127a)
				real_storm_alloc = hook::iat(L"Game.dll", "Storm.dll", (const char*)401, (uintptr_t)fake_storm_alloc);
			else if (GetGameVersion() == GameVersion::v126a)
				real_storm_alloc = hook::iat(L"Game.dll", "Storm.dll", (const char*)401, (uintptr_t)fake_storm_alloc_126);

			real_tls_get_value = hook::iat(L"Game.dll", "Kernel32.dll", "TlsGetValue", (uintptr_t)fake_tls_get_value);

			return true;
		}

		return false;
	}

}}}} 