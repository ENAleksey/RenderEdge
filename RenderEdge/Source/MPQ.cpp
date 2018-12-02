#include "MPQ.h"

#include "Log.h"
#include "Engine.h"
#include "Storm.h"
#include "Utils.h"
#include "Buffer.h"

namespace MPQ
{
	uint32 MpqLoadPriority = 15;
	bool OpenArchive(const std::string& fileName, HANDLE* mpqHandle)
	{
		if (!Storm::OpenArchive(fileName.c_str(), MpqLoadPriority, 0, mpqHandle))
		{
			LOG(ERROR) << "Failed to load MPQ: " << fileName;

			return false;
		}

		LOG(DEBUG) << "Loaded MPQ: " << fileName;

		MpqLoadPriority++;

		return true;
	}

	bool LoadFile(HANDLE MpqHandle, const std::string& fileName, BUFFER& Buffer, bool bFromMap)
	{
		HANDLE FileHandle;

		if (MpqHandle == nullptr)
		{
			if (!Storm::OpenFile(fileName.c_str(), &FileHandle))
			{
				LOG(ERROR) << "Storm::OpenFile -> File not found: " << fileName;
				return false;
			}
		}
		else
		{
			if (!Storm::OpenFileEx(MpqHandle, fileName.c_str(), 0, &FileHandle))
			{
				LOG(ERROR) << "Storm::OpenFileEx -> File not found: " << fileName;
				return false;
			}
		}

		if (bFromMap)
		{
			HANDLE fileArchive;
			char archiveName[256];

			Storm::GetFileArchive(FileHandle, &fileArchive);
			Storm::GetArchiveName(fileArchive, archiveName, sizeof(archiveName));

			if (utils::GetFileExtension(archiveName) != ".w3x")
			{
				Storm::CloseFile(FileHandle);
				return false;
			}
		}

		DWORD Size = Storm::GetFileSize(FileHandle, nullptr);

		Buffer.Resize(Size);

		DWORD BytesRead = 0;
		if (!Storm::ReadFile(FileHandle, Buffer.GetData(), Buffer.GetSize(), &BytesRead, 0))
		{
			Storm::CloseFile(FileHandle);
			LOG(ERROR) << "Storm::ReadFile " << fileName;
			return false;
		}

		Storm::CloseFile(FileHandle);

		if (BytesRead != Size)
		{
			LOG(ERROR) << "Storm::LoadFile -> Not all bytes were read in " << fileName;
			return false;
		}

		LOG(DEBUG) << "Loaded file: " << fileName;

		return true;
	}
}