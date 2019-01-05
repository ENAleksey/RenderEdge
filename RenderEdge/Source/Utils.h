#pragma once

#include <d3d9.h>
#include <d3dx9.h>
#include <string>


#ifndef V
#define V(x) { hr = (x); }
#endif
#ifndef V_RETURN
#define V_RETURN(x) { hr = (x); if( FAILED(hr) ) { return hr; } }
#endif

#ifndef SAFE_DELETE
#define SAFE_DELETE(p) { if (p) { delete (p); (p) = nullptr; } }
#endif
#ifndef SAFE_DELETE_ARRAY
#define SAFE_DELETE_ARRAY(p) { if (p) { delete[] (p); (p) = nullptr; } }
#endif
#ifndef SAFE_RELEASE
#define SAFE_RELEASE(p) { if (p) { (p)->Release(); (p) = nullptr; } }
#endif


using int8 = signed char;
using int16 = short;
using int32 = int;
using int64 = long long;
using uint8 = unsigned char;
using uint16 = unsigned short;
using uint32 = unsigned int;
using uint64 = unsigned long long;


void Message(const std::string & msg, const std::string & title);
void Message(const std::string & msg);
void ExitMessage(const std::string & msg);

namespace utils
{
	std::string GetModulePath(HMODULE hModule);
	std::string GetFileExtension(const std::string& st);
	bool ParseFloat(const std::string& Stream, const std::string& Match, float& Value);
	const char* from_utf8(char* s);
	bool IsHexColor(const std::string& str);
	std::string ExtractFilePath(const std::string& fileName);
	bool FileExists(const std::string& name);
}

namespace math
{
	float Square(float x);
	float Lerp(float a, float b, float x);
	float Clamp(float x, float a, float b);
	float ToLinearSpace(float x);
	int32 FloorToInt(float x);
	bool IsEqual(float a, float b, float e = FLT_EPSILON);
	uint32 ReverseBits(uint32 Bits);
}

namespace registry
{
	std::string GetString(const std::string& key, const std::string& value);
	DWORD GetDword(const std::string& key, const std::string& value);
}