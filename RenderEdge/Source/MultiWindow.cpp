#include "MultiWindow.h"

#include <WinSock.h>
#include "Detour.h"
#include "fp_call.h"
#include <functional>
#include "Utils.h"

#pragma comment(lib, "wsock32.lib")

namespace MultiWindow
{
	uintptr_t address_WSockBind = 0;
	uintptr_t address_WSockSendTo = 0;
	uintptr_t address_CreateEventA = 0;
	uint16 g_tcp_port;

	int32 __stdcall WSockBind_proxy(SOCKET s, const struct sockaddr FAR* name, int32 namelen)
	{
		int32 optVal;
		int32 optLen = sizeof(int32);

		if (SOCKET_ERROR != ::getsockopt(s, SOL_SOCKET, SO_TYPE, (char*)&optVal, &optLen))
		{
			if (optVal == SOCK_DGRAM)
			{
				if (((struct sockaddr_in*)name)->sin_port == 0xE017)
				{
					// udp && port == 6112
					BOOL optval = TRUE;
					::setsockopt(s, SOL_SOCKET, SO_REUSEADDR, (const char*)&optval, sizeof(optval));
					return std_call<int32>(address_WSockBind, s, name, namelen);
				}
			}
			else if (optVal == SOCK_STREAM)
			{
				// tcp
				BOOL optval = FALSE;
				::setsockopt(s, SOL_SOCKET, SO_REUSEADDR, (const char*)&optval, sizeof(optval));

				uint16 port = ::ntohs(((struct sockaddr_in*)name)->sin_port);

				for (;;)
				{
					if (std_call<int32>(address_WSockBind, s, name, namelen) != SOCKET_ERROR)
					{
						g_tcp_port = port;
						return 0;
					}

					((struct sockaddr_in*)name)->sin_port = ::htons(++port);
				}
			}
		}

		return std_call<int32>(address_WSockBind, s, name, namelen);
	}

	int32 __stdcall WSockSendTo_proxy(SOCKET s, const char FAR * buf, int32 len, int32 flags, const struct sockaddr FAR * to, int32 tolen)
	{
		struct war3_packet
		{
			uint8 f7_;
			uint8 cmd_;
			uint16 size_;
		};

		struct war3_packet* data_ptr = (struct war3_packet*)buf;

		if (len >= sizeof(war3_packet) && data_ptr->f7_ == 0xF7)
		{
			if (data_ptr->cmd_ == 0x30)
			{
				*(uint16*)(&buf[data_ptr->size_ - 2]) = g_tcp_port;
				sockaddr_in addr = *(sockaddr_in*)to;
				addr.sin_addr.S_un.S_addr = ::inet_addr("255.255.255.255");
				return std_call<int32>(address_WSockSendTo, s, (char*)buf, len, flags, (const sockaddr*)&addr, sizeof(sockaddr_in));
			}
		}

		return std_call<int32>(address_WSockSendTo, s, buf, len, flags, to, tolen);
	}

	HANDLE __stdcall CreateEventA_proxy(LPSECURITY_ATTRIBUTES lpEventAttributes, BOOL bManualReset, BOOL bInitialState, LPCSTR lpName)
	{
		HANDLE retval = std_call<HANDLE>(address_CreateEventA, lpEventAttributes, bManualReset, bInitialState, lpName);

		if ((lpName != NULL) && (0 == strcmp(lpName, "Warcraft III Game Application")))
		{
			::SetLastError(0);
		}

		return retval;
	}

	bool Init()
	{
		bool bResult = true;

		HMODULE hModule = GetModuleHandleW(L"wsock32.dll");
		if (!hModule)
			false;

		address_WSockBind = (uintptr_t)GetProcAddress(hModule, (const char*)2);
		address_WSockSendTo = (uintptr_t)GetProcAddress(hModule, (const char*)20);
		bResult &= Detour::Install(&address_WSockBind, (uintptr_t)WSockBind_proxy);
		bResult &= Detour::Install(&address_WSockSendTo, (uintptr_t)WSockSendTo_proxy);

		hModule = GetModuleHandleW(L"kernel32.dll");
		if (!hModule)
			return false;

		address_CreateEventA = (uintptr_t)GetProcAddress(hModule, "CreateEventA");
		bResult &= Detour::Install(&address_CreateEventA, (uintptr_t)CreateEventA_proxy);

		return bResult;
	}
}