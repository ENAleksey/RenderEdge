#include "Texture2D.h"

#include "Log.h"
#include "MPQ.h"
#include "Blp.h"
#include "Buffer.h"


Texture2D::Texture2D()
{
	texture = nullptr;
}

Texture2D::~Texture2D()
{
	Release();
}

bool Texture2D::IsSupportedExtension(const std::string& ext)
{
	return ext == "blp"
		|| ext == "bmp"
		|| ext == "dds"
		|| ext == "dib"
		|| ext == "hdr"
		|| ext == "jpg"
		|| ext == "pfm"
		|| ext == "png"
		|| ext == "ppm"
		|| ext == "tga";
}


bool Texture2D::CreateFromFile(IDirect3DDevice9* pDevice, const std::string& fileName, D3DFORMAT format)
{
	const std::string ext = utils::GetFileExtension(fileName);

	if (IsSupportedExtension(ext))
	{
		HRESULT hr = D3DXGetImageInfoFromFileA(fileName.c_str(), &imageInfo);
		if (hr == D3D_OK)
			hr = D3DXCreateTextureFromFileExA(pDevice, fileName.c_str(), imageInfo.Width, imageInfo.Height, 1, 0, format, D3DPOOL_MANAGED, D3DX_FILTER_NONE, D3DX_FILTER_NONE, 0, &imageInfo, nullptr, &texture);

		if (hr != D3D_OK)
		{
			if (hr == D3DXERR_INVALIDDATA)
				LOG(ERROR) << __FUNCTION__ << " -> Invalid Data: " + fileName;
			else
				LOG(ERROR) << __FUNCTION__ << " -> Unknown Error: " + fileName;

			return false;
		}
	}
	else
	{
		LOG(ERROR) << __FUNCTION__ << " -> Unknown texture format: " << fileName;
		return false;
	}

	return true;
}

bool Texture2D::CreateFromFileInMPQ(IDirect3DDevice9* pDevice, HANDLE archive, const std::string& fileName, D3DFORMAT format)
{
	const std::string ext = utils::GetFileExtension(fileName);

	if (IsSupportedExtension(ext))
	{
		BUFFER Buffer;
		if (!MPQ::LoadFile(archive, fileName, Buffer))
			return false;

		if (ext == "blp")
		{
			if (!LoadBLP(pDevice, texture, Buffer))
			{
				LOG(ERROR) << __FUNCTION__ << " -> Failed to load BLP texture: " << fileName;
				return false;
			}

			IDirect3DSurface9* pSurfDest = nullptr;
			D3DSURFACE_DESC texDesc;
			texture->GetSurfaceLevel(0, &pSurfDest);
			pSurfDest->GetDesc(&texDesc);
			SAFE_RELEASE(pSurfDest);

			imageInfo.Width = texDesc.Width;
			imageInfo.Height = texDesc.Height;
		}
		else
		{
			HRESULT hr = D3DXGetImageInfoFromFileInMemory(Buffer.GetData(), Buffer.GetSize(), &imageInfo);
			if (hr == D3D_OK)
				hr = D3DXCreateTextureFromFileInMemoryEx(pDevice, Buffer.GetData(), Buffer.GetSize(), imageInfo.Width, imageInfo.Height, 1, 0, format, D3DPOOL_MANAGED, D3DX_FILTER_NONE, D3DX_FILTER_NONE, 0, &imageInfo, nullptr, &texture);

			if (hr != D3D_OK)
			{
				LOG(ERROR) << __FUNCTION__ << " -> Failed to load texture: " << fileName;
				return false;
			}
		}
	}
	else
	{
		LOG(ERROR) << __FUNCTION__ << " -> Unknown texture format: " << fileName;
		return false;
	}

	return true;
}

bool Texture2D::CreateFromArray(IDirect3DDevice9* pDevice, const uint8* data, uint32 width, uint32 height, D3DFORMAT format)
{
	int32 bpp = 4;
	if (format == D3DFMT_A8 || format == D3DFMT_L8)
		bpp = 1;

	imageInfo.Width = width;
	imageInfo.Height = height;

	if (FAILED(pDevice->CreateTexture(width, height, 1, 0, format, D3DPOOL_MANAGED, &texture, nullptr)))
		return false;

	D3DLOCKED_RECT lock;
	if (FAILED(texture->LockRect(0, &lock, nullptr, D3DLOCK_DISCARD)))
		return false;

	char* dst = reinterpret_cast<char*>(lock.pBits);
	for (uint32 y = 0; y < height; ++y)
	{
		memcpy(dst, data, width * bpp);
		data += width * bpp;
		dst += lock.Pitch;
	}

	texture->UnlockRect(0);

	return true;
}

void Texture2D::Release()
{
	SAFE_RELEASE(texture);
}