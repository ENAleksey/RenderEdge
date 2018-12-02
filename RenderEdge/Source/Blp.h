//+-----------------------------------------------------------------------------
//| Inclusion guard
//+-----------------------------------------------------------------------------
#ifndef TEXTURE_LOADER_BLP_H
#define TEXTURE_LOADER_BLP_H

#include <Windows.h>
#include <d3d9.h>
#include <d3dx9.h>
#include "Buffer.h"
//#include <cstdint>


//+-----------------------------------------------------------------------------
//| Constants
//+-----------------------------------------------------------------------------
CONST INT MAX_NR_OF_BLP_MIP_MAPS = 16;


//+-----------------------------------------------------------------------------
//| Blp header structure
//+-----------------------------------------------------------------------------
struct BLP_HEADER
{
	BLP_HEADER()
	{
		MagicNumber = '1PLB';
		Compression = 0;
		Flags = 0;
		Width = 0;
		Height = 0;
		PictureType = 0;
		PictureSubType = 0;
		ZeroMemory(Offset, MAX_NR_OF_BLP_MIP_MAPS * sizeof(DWORD));
		ZeroMemory(Size, MAX_NR_OF_BLP_MIP_MAPS * sizeof(DWORD));
	}

	DWORD MagicNumber;
	DWORD Compression;
	DWORD Flags;
	DWORD Width;
	DWORD Height;
	DWORD PictureType;
	DWORD PictureSubType;
	DWORD Offset[MAX_NR_OF_BLP_MIP_MAPS];
	DWORD Size[MAX_NR_OF_BLP_MIP_MAPS];
};


//+-----------------------------------------------------------------------------
//| Blp RGBA structure
//+-----------------------------------------------------------------------------
struct BLP_RGBA
{
	UCHAR Red;
	UCHAR Green;
	UCHAR Blue;
	UCHAR Alpha;
};


//+-----------------------------------------------------------------------------
//| Blp pixel structure
//+-----------------------------------------------------------------------------
struct BLP_PIXEL
{
	UCHAR Index;
};


BOOL LoadBLP(IDirect3DDevice9* Direct3DDevice, IDirect3DTexture9*& Texture, BUFFER& Buffer);

BOOL LoadCompressed(IDirect3DDevice9* Direct3DDevice, IDirect3DTexture9*& Texture, BLP_HEADER& Header, BUFFER& Buffer);
BOOL LoadUncompressed(IDirect3DDevice9* Direct3DDevice, IDirect3DTexture9*& Texture, BLP_HEADER& Header, BUFFER& Buffer);

#endif
