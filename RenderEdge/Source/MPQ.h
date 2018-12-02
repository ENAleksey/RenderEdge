#pragma once

#include <windows.h>
#include <string.h>
#include <sstream>
#include "Buffer.h"

namespace MPQ
{
	bool OpenArchive(const std::string& fileName, HANDLE* mpqHandle);
	bool LoadFile(HANDLE MpqHandle, const std::string& FileName, BUFFER& Buffer, bool bFromMap = false);
}