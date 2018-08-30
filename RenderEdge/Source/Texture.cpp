#include "Texture.h"

#include "MPQ.h"
#include "Blp.h"
#include "Utils.h"
#include "Log.h"


Texture::Texture()
{
	height = 0;
	width = 0;
	texture = nullptr;
}

Texture::~Texture()
{
	Release();
}


bool Texture::IsSupportedExtension(const std::string& ext)
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

bool Texture::CreateFromFile(IDirect3DDevice9* pDevice, const std::string& filename)
{
	HRESULT hr = D3DXCreateTextureFromFileA(pDevice, filename.c_str(), &texture);

	D3DSURFACE_DESC desc;
	texture->GetLevelDesc(0, &desc);
	width = desc.Width;
	height = desc.Height;

	if (hr != D3D_OK)
	{
		if (hr == D3DXERR_INVALIDDATA)
			LOG(logERROR) << "Texture::CreateTextureFromFile -> Invalid Data " << filename;
		else
			LOG(logERROR) << "Texture::CreateTextureFromFile -> Unknown Error " << filename;

		return false;
	}


	return true;
}

bool Texture::CreateFromFileInMPQ(IDirect3DDevice9* pDevice, HANDLE archive, const std::string& filename)
{
	std::string ext = utils::get_ext(filename);

	if (IsSupportedExtension(ext))
	{
		BUFFER Buffer;
		if (!MPQ::LoadFile(archive, filename, Buffer))
			return false;

		if (ext == "blp")
		{
			if (!LoadBLP(pDevice, texture, Buffer))
			{
				LOG(logERROR) << "Texture::CreateTextureFromFileInMPQ -> Failed to load: " << filename;
				return false;
			}
		}
		else
		{
			if (FAILED(D3DXCreateTextureFromFileInMemoryEx(pDevice, Buffer.GetData(), Buffer.GetSize(),
				D3DX_DEFAULT, D3DX_DEFAULT, D3DX_DEFAULT, 0, D3DFMT_UNKNOWN, D3DPOOL_MANAGED, 
				D3DX_FILTER_NONE, D3DX_DEFAULT, 0, nullptr, nullptr, &texture)))
			{
				LOG(logERROR) << "Texture::CreateTextureFromFileInMPQ -> Failed to load: " << filename;
				return false;
			}
		}
	}
	else
	{
		LOG(logERROR) << "Texture::CreateTextureFromFileInMPQ -> Unknown texture format: " << filename;
		return false;
	}


	D3DSURFACE_DESC desc;
	texture->GetLevelDesc(0, &desc);
	width = desc.Width;
	height = desc.Height;

	return true;
}

bool Texture::CreateEmpty(IDirect3DDevice9* pDevice, uint32 argb)
{
	width = 1;
	height = 1;

	HRESULT hr = D3DXCreateTexture(pDevice, width, height, 1, 0, D3DFMT_A8R8G8B8, D3DPOOL_MANAGED, &texture);

	if (hr != D3D_OK)
	{
		if (hr == D3DXERR_INVALIDDATA)
			LOG(logERROR) << "Texture::CreateEmptyTexture - Invalid Data";
		else
			LOG(logERROR) << "Texture::CreateEmptyTexture - Unknown Error";

		return false;
	}

	D3DLOCKED_RECT lr;
	texture->LockRect(0, &lr, 0, 0);
	uint32* imageData = (uint32*)lr.pBits;
	imageData[0] = argb;
	texture->UnlockRect(0);

	return true;
}

bool Texture::FromArray(IDirect3DDevice9* pDevice, const byte* bytes, uint32 width, uint32 height)
{
	D3DFORMAT fmt = D3DFMT_A8; // D3DFMT_A8R8G8B8
	int32 bpp = 1; // 4

	if (FAILED(pDevice->CreateTexture(width, height, 1, 0, fmt, D3DPOOL_MANAGED, &texture, nullptr)))
		return false;

	D3DLOCKED_RECT lock;
	if (FAILED(texture->LockRect(0, &lock, nullptr, D3DLOCK_DISCARD)))
		return false;

	char* dst = reinterpret_cast<char*>(lock.pBits);
	for (uint32 y = 0; y < height; ++y)
	{
		memcpy(dst, bytes, width * bpp);
		bytes += width * bpp;
		dst += lock.Pitch;
	}

	texture->UnlockRect(0);

	return true;
}

void Texture::Release()
{
	if (texture != nullptr)
	{
		texture->Release();
		texture = nullptr;
	}
}

