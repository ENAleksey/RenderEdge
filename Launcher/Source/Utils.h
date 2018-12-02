#pragma once

#include <string>
#include <Windows.h>

void Message(const std::string& msg);

namespace utils
{
	std::string GetModulePath(HMODULE hModule);
	bool FileExists(const std::string& fileName);
}

namespace registry
{
	std::string GetString(const std::string& key, const std::string& value);
	DWORD GetDword(const std::string& key, const std::string& value);
}