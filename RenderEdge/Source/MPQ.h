#pragma once

#include <windows.h>
#include <string.h>
#include <sstream>
#include "Buffer.h"

namespace MPQ
{
	void OpenArchive(const std::string& fileName, HANDLE mpqHandle);
	bool LoadFile(HANDLE MpqHandle, const std::string& fileNameame, BUFFER& Buffer);
}