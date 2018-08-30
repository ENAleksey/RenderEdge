#pragma once

#include <string>
#include <Windows.h>

void Message(const std::string& msg);

namespace utils
{
	std::string ExtractFilePath(const std::string& fileName);
	bool FileExists(const std::string& name);
}

namespace registry
{
	std::string GetString(const std::string& key, const std::string& value);
	DWORD GetDword(const std::string& key, const std::string& value);
}