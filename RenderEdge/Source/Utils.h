#pragma once

#include <string>
#include <Windows.h>

#ifndef SAFE_RELEASE
#define SAFE_RELEASE(p)			{ if(p) { (p)->Release(); (p) = nullptr; } }
#endif

#ifndef SAFE_DELETE
#define SAFE_DELETE(p)			{ if(p) { delete (p); (p) = nullptr; } }
#endif

#ifndef V_RETURN
#define V_RETURN(hr)			{ if(FAILED(hr)) { MessageBoxW(nullptr, L"Fail!", L"Error!", MB_OK); } }
#endif

#ifndef SAFE_ARRAY_DELETE
#define SAFE_ARRAY_DELETE(x)	{ if (x) { delete [] x; x = nullptr; } }
#endif


template <typename Type> void SetValueFromMemory(uintptr_t addres, Type value)
{
	DWORD dwOldProtect;
	if (VirtualProtect((LPVOID*)addres, sizeof(Type), PAGE_EXECUTE_READWRITE, &dwOldProtect))
		*(Type*)(LPVOID*)addres = value;
}


void Message(const std::string& msg, const std::string& title);
void Message(const std::string& msg);

namespace utils
{
	std::string get_ext(const std::string& st);

	const char* from_utf8(char* s);
	bool IsHexColor(const std::string& str);
	std::string ExtractFilePath(const std::string& fileName);
	bool FileExists(const std::string& name);
}

namespace registry
{
	std::string GetString(const std::string& key, const std::string& value);
	DWORD GetDword(const std::string& key, const std::string& value);
}