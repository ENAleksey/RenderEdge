#include "MPQ.h"

#include "Engine.h"
#include "Storm.h"
#include "Utils.h"
#include "Log.h"
#include "Buffer.h"

namespace MPQ
{
	uint32_t MpqLoadPriority = 15;
	void OpenArchive(const std::string& fileName, HANDLE mpqHandle)
	{
		if (utils::FileExists(fileName.c_str()))
		{
			Storm::OpenArchive(fileName.c_str(), MpqLoadPriority, 0, &mpqHandle);
			MpqLoadPriority++;

			LOG(logDEBUG) << "Loaded MPQ: " << fileName;
		}
		else
		{
			LOG(logERROR) << "Failed to load MPQ: " << fileName;
			Message("Failed to load MPQ:\n" + fileName);
		}
	}

	bool LoadFile(HANDLE MpqHandle, const std::string& fileName, BUFFER& Buffer)
	{
		DWORD Size;
		HANDLE FileHandle;
		DWORD BytesRead = 0;

		if (MpqHandle == NULL)
		{
			if (!Storm::OpenFile(fileName.c_str(), &FileHandle))
			{
				LOG(logERROR) << "Storm::OpenFile -> File not found: " << fileName;
				return false;
			}
		}
		else
		{
			if (!Storm::OpenFileEx(MpqHandle, fileName.c_str(), 0, &FileHandle))
			{
				LOG(logERROR) << "Storm::OpenFileEx -> File not found: " << fileName;
				return false;
			}
		}

		Size = Storm::GetFileSize(FileHandle, NULL);

		Buffer.Resize(Size);

		if (!Storm::ReadFile(FileHandle, Buffer.GetData(), Buffer.GetSize(), &BytesRead, NULL))
		{
			Storm::CloseFile(FileHandle);
			LOG(logERROR) << "Storm::ReadFile " << fileName;
			return false;
		}

		Storm::CloseFile(FileHandle);

		if (BytesRead != Size)
		{
			LOG(logERROR) << "Storm::LoadFile -> Not all bytes were read in " << fileName;
			return false;
		}

		LOG(logDEBUG) << "Loaded file: " << fileName;

		return true;
	}
}