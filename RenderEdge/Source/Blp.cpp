#include "Blp.h"

#include "Log.h"
#include "Jpeg.h"
#include "Utils.h"


BOOL LoadBLP(IDirect3DDevice9* pDevice, IDirect3DTexture9*& pTexture, BUFFER& Buffer)
{
	BLP_HEADER Header;
	//D3DSURFACE_DESC SurfaceInfo;

	std::memcpy(reinterpret_cast<CHAR*>(&Header), &Buffer[0], sizeof(BLP_HEADER));
	if(Header.MagicNumber != '1PLB')
	{
		LOG(ERROR) << "LoadBLP -> Unable to load texture: The file is not a BLP texture!";
		return FALSE;
	}

	switch(Header.Compression)
	{
		case 0:
		{
			if(!LoadCompressed(pDevice, pTexture, Header, Buffer)) return FALSE;
			break;
		}
		case 1:
		{
			if(!LoadUncompressed(pDevice, pTexture, Header, Buffer)) return FALSE;
			break;
		}
		default:
		{
			LOG(ERROR) << "LoadBLP -> Unable to load texture: Unknown compression method!";
			return FALSE;
		}
	}
	
	if(FAILED(D3DXFilterTexture(pTexture, NULL, D3DX_DEFAULT, D3DX_DEFAULT)))
	{
		LOG(ERROR) << "LoadBLP -> Unable to load texture: Texture filtering failed!";
		return FALSE;
	}
	
	return TRUE;
}


//+-----------------------------------------------------------------------------
//| Loads a compressed blp texture
//+-----------------------------------------------------------------------------
BOOL LoadCompressed(IDirect3DDevice9* pDevice, IDirect3DTexture9*& pTexture, BLP_HEADER& Header, BUFFER& Buffer)
{
	INT X;
	INT Y;
	INT Index;
	INT BufferIndex;
	UCHAR* Pointer;
	BUFFER TempBuffer;
	BUFFER TempBuffer2;
	D3DLOCKED_RECT LockedRect;
	DWORD JpegHeaderSize;

	std::memcpy(reinterpret_cast<CHAR*>(&JpegHeaderSize), &Buffer[sizeof(BLP_HEADER)], sizeof(DWORD));

	if(FAILED(D3DXCreateTexture(pDevice, Header.Width, Header.Height, D3DX_DEFAULT, 0, D3DFMT_UNKNOWN, D3DPOOL_MANAGED, &pTexture)))
	{
		LOG(ERROR) << "LoadCompressed -> Unable to load texture: Texture creation failed!";
		return FALSE;
	}

	TempBuffer2.Resize(Header.Size[0] + JpegHeaderSize);

	std::memcpy(&TempBuffer2[0], &Buffer[sizeof(BLP_HEADER) + sizeof(DWORD)], JpegHeaderSize);
	std::memcpy(&TempBuffer2[JpegHeaderSize], &Buffer[Header.Offset[0]], Header.Size[0]);

	if(!Jpeg.Read(TempBuffer2, TempBuffer))
	{
		LOG(ERROR) << "LoadCompressed -> Unable to load texture: BLP reading failed!";
		return FALSE;
	}

	if(FAILED(pTexture->LockRect(0, &LockedRect, NULL, D3DLOCK_DISCARD)))
	{
		LOG(ERROR) << "LoadCompressed -> Unable to load texture: Texture locking failed!";
		return FALSE;
	}

	Index = 0;
	BufferIndex = 0;
	Pointer = reinterpret_cast<UCHAR*>(LockedRect.pBits);

	for(Y = 0; Y < static_cast<INT>(Header.Height); Y++)
	{
		for(X = 0; X < static_cast<INT>(Header.Width); X++)
		{
			Pointer[Index++] = TempBuffer[BufferIndex++];
			Pointer[Index++] = TempBuffer[BufferIndex++];
			Pointer[Index++] = TempBuffer[BufferIndex++];
			Pointer[Index++] = TempBuffer[BufferIndex++];
		}

		Index += LockedRect.Pitch - (Header.Width * 4);
	}

	pTexture->UnlockRect(0);

	return TRUE;
}


//+-----------------------------------------------------------------------------
//| Loads an uncompressed blp texture
//+-----------------------------------------------------------------------------
BOOL LoadUncompressed(IDirect3DDevice9* pDevice, IDirect3DTexture9*& pTexture, BLP_HEADER& Header, BUFFER& Buffer)
{
	INT i;
	INT X;
	INT Y;
	INT Size;
	INT Index;
	INT BufferIndex;
	UCHAR* Pointer;
	BUFFER TempBuffer;
	D3DLOCKED_RECT LockedRect;
	CONST INT PALETTE_SIZE = 256;
	BLP_RGBA Palette[PALETTE_SIZE];
	BLP_RGBA* TargetPixel;

	std::memcpy(reinterpret_cast<CHAR*>(Palette), &Buffer[sizeof(BLP_HEADER)], (PALETTE_SIZE * 4));

	if(FAILED(D3DXCreateTexture(pDevice, Header.Width, Header.Height, D3DX_DEFAULT, 0, D3DFMT_UNKNOWN, D3DPOOL_MANAGED, &pTexture)))
	{
		LOG(ERROR) << "LoadUncompressed -> Unable to load texture: Texture creation failed!";
		return FALSE;
	}

	Size = Header.Width * Header.Height;
	TempBuffer.Resize(Size * 4);

	switch(Header.PictureType)
	{
		case 3:
		case 4:
		{
			BLP_PIXEL* SourcePixel;

			SourcePixel = reinterpret_cast<BLP_PIXEL*>(&Buffer[sizeof(BLP_HEADER) + (PALETTE_SIZE * 4)]);
			TargetPixel = reinterpret_cast<BLP_RGBA*>(&TempBuffer[0]);

			for(i = 0; i < Size; i++)
			{
				TargetPixel[i].Red = Palette[SourcePixel[i].Index].Red;
				TargetPixel[i].Green = Palette[SourcePixel[i].Index].Green;
				TargetPixel[i].Blue = Palette[SourcePixel[i].Index].Blue;
			}
			for(i = 0; i < Size; i++)
			{
				TargetPixel[i].Alpha = SourcePixel[Size + i].Index;
			}

			break;
		}
		case 5:
		{
			BLP_PIXEL* SourcePixel;

			SourcePixel = reinterpret_cast<BLP_PIXEL*>(&Buffer[sizeof(BLP_HEADER) + (PALETTE_SIZE * 4)]);
			TargetPixel = reinterpret_cast<BLP_RGBA*>(&TempBuffer[0]);

			for(i = 0; i < Size; i++)
			{
				TargetPixel[i].Red = Palette[SourcePixel[i].Index].Red;
				TargetPixel[i].Green = Palette[SourcePixel[i].Index].Green;
				TargetPixel[i].Blue = Palette[SourcePixel[i].Index].Blue;
				TargetPixel[i].Alpha = 255 - Palette[SourcePixel[i].Index].Alpha;
			}

			break;
		}
		default:
		{
			LOG(ERROR) << "LoadUncompressed -> Unable to load texture: Unable to load texture, unknown picture type!";
			return FALSE;
		}
	}

	if(FAILED(pTexture->LockRect(0, &LockedRect, NULL, 0)))
	{
		LOG(ERROR) << "LoadUncompressed -> Unable to load texture: Texture locking failed!";
		return FALSE;
	}

	Index = 0;
	BufferIndex = 0;
	Pointer = reinterpret_cast<UCHAR*>(LockedRect.pBits);

	for(Y = 0; Y < static_cast<INT>(Header.Height); Y++)
	{
		for(X = 0; X < static_cast<INT>(Header.Width); X++)
		{
			Pointer[Index++] = TempBuffer[BufferIndex++];
			Pointer[Index++] = TempBuffer[BufferIndex++];
			Pointer[Index++] = TempBuffer[BufferIndex++];
			Pointer[Index++] = TempBuffer[BufferIndex++];
		}

		Index += LockedRect.Pitch - (Header.Width * 4);
	}

	pTexture->UnlockRect(0);

	return TRUE;
}
