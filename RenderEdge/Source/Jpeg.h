#pragma once

//+-----------------------------------------------------------------------------
//| Prevents stupid redefinitions
//+-----------------------------------------------------------------------------
#define XMD_H


//+-----------------------------------------------------------------------------
//| Included files
//+-----------------------------------------------------------------------------
#include "Buffer.h"
#include "int_t.h"


//+-----------------------------------------------------------------------------
//| Included JPEG files (requires C inclusion)
//+-----------------------------------------------------------------------------


#pragma warning(push)
#pragma warning(disable:4005)
extern "C"
{
#include <jpeglib.h>
}
#pragma warning(pop)

//+-----------------------------------------------------------------------------
//| Source manager structure
//+-----------------------------------------------------------------------------

struct JPEG_SOURCE_MANAGER
{
	JPEG_SOURCE_MANAGER()
	{
		SourceBuffer = NULL;
		SourceBufferSize = 0;
		Buffer = NULL;
	}

	jpeg_source_mgr Manager;
	uint8* SourceBuffer;
	size_t SourceBufferSize;
	JOCTET* Buffer;
};


//+-----------------------------------------------------------------------------
//| Destination manager structure
//+-----------------------------------------------------------------------------
struct JPEG_DESTINATION_MANAGER
{
	JPEG_DESTINATION_MANAGER()
	{
		DestinationBuffer = NULL;
		DestinationBufferSize = 0;
		Buffer = NULL;
	}

	jpeg_destination_mgr Manager;
	uint8* DestinationBuffer;
	size_t DestinationBufferSize;
	JOCTET* Buffer;
};


//+-----------------------------------------------------------------------------
//| Jpeg class
//+-----------------------------------------------------------------------------
class JPEG
{
public:
	JPEG();
	~JPEG();

	bool Write(const BUFFER& SourceBuffer, BUFFER& TargetBuffer, int32 Width, int32 Height, int32 Quality);
	bool Read(const BUFFER& SourceBuffer, BUFFER& TargetBuffer, int32* Width = NULL, int32* Height = NULL);

protected:
	static void SetMemorySource(jpeg_decompress_struct* Info, uint8* Buffer, size_t Size);
	static void SetMemoryDestination(jpeg_compress_struct* Info, uint8* Buffer, size_t Size);

	static void SourceInit(jpeg_decompress_struct* Info);
	static boolean SourceFill(jpeg_decompress_struct* Info);
	static void SourceSkip(jpeg_decompress_struct* Info, long NrOfBytes);
	static void SourceTerminate(jpeg_decompress_struct* Info);

	static void DestinationInit(jpeg_compress_struct* Info);
	static boolean DestinationEmpty(jpeg_compress_struct* Info);
	static void DestinationTerminate(jpeg_compress_struct* Info);
};


//+-----------------------------------------------------------------------------
//| Global objects
//+-----------------------------------------------------------------------------
extern JPEG Jpeg;
