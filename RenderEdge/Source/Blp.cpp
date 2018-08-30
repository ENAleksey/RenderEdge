
#include "Blp.h"
#include "Jpeg.h"
#include "Utils.h"
#include <d3dx9.h>


BOOL LoadBLP(IDirect3DDevice9* Direct3DDevice, IDirect3DTexture9*& Texture, BUFFER& Buffer)
{
	BLP_HEADER Header;
	//D3DSURFACE_DESC SurfaceInfo;

	if (Direct3DDevice == NULL)
	{
		Message("Unable to retrieve the Direct3D device!", "Unable to load texture!");
		return FALSE;
	}

	std::memcpy(reinterpret_cast<CHAR*>(&Header), &Buffer[0], sizeof(BLP_HEADER));
	if(Header.MagicNumber != '1PLB')
	{
		Message("The file is not a BLP texture!", "Unable to load texture!");
		return FALSE;
	}


	switch(Header.Compression)
	{
		case 0:
		{
			if(!LoadCompressed(Direct3DDevice, Texture, Header, Buffer)) return FALSE;
			break;
		}

		case 1:
		{
			if(!LoadUncompressed(Direct3DDevice, Texture, Header, Buffer)) return FALSE;
			break;
		}

		default:
		{
			Message("Unknown compression method!", "Unable to load texture!");
			return FALSE;
		}
	}
	if (!Texture)
	{
		MessageBoxA(NULL, "Error!", "Texture::CreateTextureFromMPQ", MB_OK | MB_ICONERROR);
		return FALSE;
	}
	
	if(FAILED(D3DXFilterTexture(Texture, NULL, D3DX_DEFAULT, D3DX_DEFAULT)))
	{
		Message("Texture filtering failed!", "Unable to load texture!");
		return FALSE;
	}
	
	return TRUE;
}


//+-----------------------------------------------------------------------------
//| Loads a compressed blp texture
//+-----------------------------------------------------------------------------
BOOL LoadCompressed(IDirect3DDevice9* Direct3DDevice, IDirect3DTexture9*& Texture, BLP_HEADER& Header, BUFFER& Buffer)
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

	if(FAILED(D3DXCreateTexture(Direct3DDevice, Header.Width, Header.Height, D3DX_DEFAULT, 0,
								D3DFMT_UNKNOWN, D3DPOOL_MANAGED, &Texture)))
	{
		Message("Texture creation failed!", "Unable to load texture!");
		return FALSE;
	}

	TempBuffer2.Resize(Header.Size[0] + JpegHeaderSize);

	std::memcpy(&TempBuffer2[0], &Buffer[sizeof(BLP_HEADER) + sizeof(DWORD)], JpegHeaderSize);
	std::memcpy(&TempBuffer2[JpegHeaderSize], &Buffer[Header.Offset[0]], Header.Size[0]);

	if(!Jpeg.Read(TempBuffer2, TempBuffer))
	{
		Message("BLP reading failed!", "Unable to load texture!");
		return FALSE;
	}

	if(FAILED(Texture->LockRect(0, &LockedRect, NULL, D3DLOCK_DISCARD)))
	{
		Message("Texture locking failed!", "Unable to load texture!");
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

	Texture->UnlockRect(0);

	return TRUE;
}


//+-----------------------------------------------------------------------------
//| Loads an uncompressed blp texture
//+-----------------------------------------------------------------------------
BOOL LoadUncompressed(IDirect3DDevice9* Direct3DDevice, IDirect3DTexture9*& Texture, BLP_HEADER& Header, BUFFER& Buffer)
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

	if(FAILED(D3DXCreateTexture(Direct3DDevice, Header.Width, Header.Height, D3DX_DEFAULT, 0,
								D3DFMT_UNKNOWN, D3DPOOL_MANAGED, &Texture)))
	{
		Message("Texture creation failed!", "Unable to load texture!");
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
			Message("Unable to load texture, unknown picture type!", 0);
			return FALSE;
		}
	}

	if(FAILED(Texture->LockRect(0, &LockedRect, NULL, 0)))
	{
		Message("Unable to load texture, texture locking failed!", 0);
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

	Texture->UnlockRect(0);

	return TRUE;
}
