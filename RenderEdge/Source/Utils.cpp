#include "Utils.h"
#include "Engine.h"
#include "Log.h"
#include "int_t.h"

#include <memory>

void Message(const std::string & msg, const std::string & title)
{
	MessageBoxA(nullptr, msg.c_str(), title.c_str(), MB_OK | MB_ICONERROR);
}

void Message(const std::string & msg)
{
	Message(msg, "RenderEdge.dll");
}


namespace utils
{
	std::string get_ext(const std::string& st)
	{
		size_t pos = st.rfind('.');

		if (pos == std::string::npos)
			return "";

		return st.substr(pos + 1);
	}


	wchar_t* utf8_to_unicode(char* utf8_string)
	{
		int32 err;
		wchar_t* res;
		int32 res_len = MultiByteToWideChar(CP_UTF8, 0, utf8_string, -1, nullptr, 0);
		if (res_len == 0)
		{
			LOG(logERROR) << "Failed to obtain utf8 string length";
			return nullptr;
		}
		res = (wchar_t*)calloc(sizeof(wchar_t), res_len);
		if (res == nullptr)
		{
			LOG(logERROR) << "Failed to allocate unicode string";
			return nullptr;
		}
		err = MultiByteToWideChar(CP_UTF8, 0, utf8_string, -1, res, res_len);
		if (err == 0)
		{
			LOG(logERROR) << "Failed to convert to unicode";
			free(res);
			return nullptr;
		}
		return res;
	}

	char* unicode_to_1251(wchar_t* unicode_string)
	{
		int32 err;
		char* res;
		int32 res_len = WideCharToMultiByte(CP_ACP, 0, unicode_string, -1, nullptr, 0, nullptr, nullptr);
		if (res_len == 0)
		{
			LOG(logERROR) << "Failed to obtain required cp1251 string length";
			return nullptr;
		}
		res = (char*)calloc(sizeof(char), res_len);
		if (res == nullptr)
		{
			LOG(logERROR) << "Failed to allocate cp1251 string";
			return nullptr;
		}
		err = WideCharToMultiByte(CP_ACP, 0, unicode_string, -1, res, res_len, nullptr, nullptr);
		if (err == 0)
		{
			LOG(logERROR) << "Failed to convert from unicode";
			free(res);
			return nullptr;
		}
		return res;
	}

	const char* from_utf8(char* s)
	{
		wchar_t* unicode = utf8_to_unicode(s);
		if (unicode != nullptr)
		{
			char* ascii = unicode_to_1251(unicode);
			if (ascii != nullptr)
				return ascii;
		}

		return "Error! (from_utf8)";
	}

	bool IsHexColor(const std::string& str)
	{
		if (str.size() != 8)
			return false;

		uint8 i = 0;
		uint8 j = 0;

		for (const char& curChar : str)
		{
			i++;
			if (isxdigit(curChar))
				j++;
		}

		return (i == j);
	}

	std::string ExtractFilePath(const std::string& fileName)
	{
		size_t pos = fileName.rfind('\\');

		if (pos == std::string::npos)
			return "";

		return fileName.substr(0, pos + 1);
	}

	bool FileExists(const std::string& name)
	{
		return GetFileAttributesA(name.c_str()) != DWORD(-1);
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