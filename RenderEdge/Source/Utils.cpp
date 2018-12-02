#include "Utils.h"

#include <stdarg.h>
#include <memory>
#include <intrin.h>
#include <vector>


void Message(const std::string& msg, const std::string& title)
{
	MessageBoxA(nullptr, msg.c_str(), title.c_str(), MB_OK | MB_ICONERROR | MB_TOPMOST);
}

void Message(const std::string& msg)
{
	Message(msg, "RenderEdge.dll");
}

void ExitMessage(const std::string& msg)
{
	if (!msg.empty())
		Message(msg, "RenderEdge.dll");

	TerminateProcess(GetCurrentProcess(), ERROR_SUCCESS);
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

	std::string GetFileExtension(const std::string& st)
	{
		size_t pos = st.rfind('.');

		if (pos == std::string::npos)
			return "";

		return st.substr(pos + 1);
	}

	bool ParseFloat(const std::string& Stream, const std::string& Match, float& Value)
	{
		int Temp = Stream.find(Match);

		if (Temp == -1)
			return false;

		Value = std::stof(Stream.substr(Temp + Match.size()));

		return true;
	}

	wchar_t* utf8_to_unicode(char* utf8_string)
	{
		int32 err;
		wchar_t* res;
		int32 res_len = MultiByteToWideChar(CP_UTF8, 0, utf8_string, -1, nullptr, 0);
		if (res_len == 0)
		{
			return nullptr;
		}
		res = (wchar_t*)calloc(sizeof(wchar_t), res_len);
		if (res == nullptr)
		{
			return nullptr;
		}
		err = MultiByteToWideChar(CP_UTF8, 0, utf8_string, -1, res, res_len);
		if (err == 0)
		{
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
			return nullptr;
		}
		res = (char*)calloc(sizeof(char), res_len);
		if (res == nullptr)
		{
			return nullptr;
		}
		err = WideCharToMultiByte(CP_ACP, 0, unicode_string, -1, res, res_len, nullptr, nullptr);
		if (err == 0)
		{
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

	bool FileExists(const std::string& fileName)
	{
		const DWORD fileAttributes = GetFileAttributesA(fileName.c_str());
		return (fileAttributes != INVALID_FILE_ATTRIBUTES) && (fileAttributes != FILE_ATTRIBUTE_DIRECTORY);
	}
}

namespace math
{
	float Square(float x)
	{
		return x * x;
	}

	float Lerp(float a, float b, float x)
	{
		return (a * (1.0 - x)) + (b * x);
	}

	float Clamp(float x, float a, float b)
	{
		return x < a ? a : (x > b ? b : x);
	}

	float ToLinearSpace(float x)
	{
		return pow(x, 2.2f);
	}

	int32 FloorToInt(float x)
	{
		return _mm_cvt_ss2si(_mm_set_ss(x + x - 0.5f)) >> 1;
	}

	bool IsEqual(float a, float b, float e)
	{
		return abs(a - b) <= e;
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