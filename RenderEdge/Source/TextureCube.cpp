#include "TextureCube.h"

#include "Log.h"
#include "MPQ.h"
#include "Buffer.h"


TextureCube::TextureCube()
{
	texture = nullptr;
}

TextureCube::~TextureCube()
{
	Release();
}

bool TextureCube::IsSupportedExtension(const std::string& ext)
{
	return ext == "dds";
}

bool TextureCube::CreateFromFile(IDirect3DDevice9* pDevice, const std::string& fileName, D3DFORMAT format)
{
	const std::string ext = utils::GetFileExtension(fileName);

	if (IsSupportedExtension(ext))
	{
		HRESULT hr = D3DXGetImageInfoFromFileA(fileName.c_str(), &imageInfo);
		if (hr == D3D_OK)
			hr = D3DXCreateCubeTextureFromFileExA(pDevice, fileName.c_str(), imageInfo.Width, imageInfo.Height, 0, format, D3DPOOL_MANAGED, D3DX_FILTER_NONE, D3DX_FILTER_NONE, 0, &imageInfo, nullptr, &texture);

		if (hr != D3D_OK)
		{
			if (hr == D3DXERR_INVALIDDATA)
				LOG(ERROR) << __FUNCTION__ << " -> Invalid Data: " << fileName;
			else
				LOG(ERROR) << __FUNCTION__ << " -> Unknown Error: " << fileName;

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

bool TextureCube::CreateFromFileInMPQ(IDirect3DDevice9* pDevice, HANDLE archive, const std::string& fileName, D3DFORMAT format)
{
	std::string ext = utils::GetFileExtension(fileName);

	if (IsSupportedExtension(ext))
	{
		BUFFER Buffer;
		if (!MPQ::LoadFile(archive, fileName, Buffer))
			return false;

		HRESULT hr = D3DXGetImageInfoFromFileInMemory(Buffer.GetData(), Buffer.GetSize(), &imageInfo);
		if (hr == D3D_OK)
			hr = D3DXCreateCubeTextureFromFileInMemoryEx(pDevice, Buffer.GetData(), Buffer.GetSize(), imageInfo.Width, imageInfo.Height, 0, format, D3DPOOL_MANAGED, D3DX_FILTER_NONE, D3DX_FILTER_NONE, 0, &imageInfo, nullptr, &texture);
		
		if (hr != D3D_OK)
		{
			LOG(ERROR) << __FUNCTION__ << " -> Failed to load texture: " << fileName;
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

void TextureCube::Release()
{
	SAFE_RELEASE(texture);
}