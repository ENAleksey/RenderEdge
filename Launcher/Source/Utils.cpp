#include "Utils.h"

void Message(const std::string& msg)
{
	MessageBoxA(nullptr, msg.c_str(), "RenderEdge.exe", MB_OK | MB_ICONERROR);
}


namespace utils
{
	std::string GetModulePath(HMODULE hModule)
	{
		char path[MAX_PATH];
		GetModuleFileNameA(hModule, path, sizeof(path));
		std::string filePath = path;

		size_t pos = filePath.rfind('\\');
		if (pos == std::wstring::npos)
			return "";

		return filePath.substr(0, pos + 1);
	}

	bool FileExists(const std::string& fileName)
	{
		const DWORD fileAttributes = GetFileAttributesA(fileName.c_str());
		return (fileAttributes != INVALID_FILE_ATTRIBUTES) && (fileAttributes != FILE_ATTRIBUTE_DIRECTORY);
	}
}

namespace registry
{
	std::string GetString(const std::string& key, const std::string& value)
	{
		HKEY hKey;
		if (RegOpenKeyExA(HKEY_CURRENT_USER, key.c_str(), 0, KEY_QUERY_VALUE, &hKey) != ERROR_SUCCESS)
			return "";

		char szBuffer[256] = { '\0' };
		DWORD dwBufferSize = sizeof(szBuffer);
		LONG ret = RegQueryValueExA(hKey, value.c_str(), nullptr, nullptr, (LPBYTE)szBuffer, &dwBufferSize);
		RegCloseKey(hKey);

		if (ret != ERROR_SUCCESS)
			return "";

		return szBuffer;
	}

	DWORD GetDword(const std::string& key, const std::string& value)
	{
		HKEY hKey;
		if (RegOpenKeyExA(HKEY_CURRENT_USER, key.c_str(), 0, KEY_QUERY_VALUE, &hKey) != ERROR_SUCCESS)
			return -1;

		DWORD dwValue = 0;
		DWORD dwDataSize = sizeof(DWORD);
		LONG ret = RegQueryValueExA(hKey, value.c_str(), nullptr, nullptr, reinterpret_cast<LPBYTE>(&dwValue), &dwDataSize);
		RegCloseKey(hKey);

		if (ret != ERROR_SUCCESS)
			return -1;

		return dwValue;
	}
}