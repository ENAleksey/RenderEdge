#pragma once

#include "Utils.h"

class TextureCube
{
private:
	IDirect3DCubeTexture9* texture;
	D3DXIMAGE_INFO imageInfo;

public:
	TextureCube();
	~TextureCube();

	IDirect3DCubeTexture9* GetTexture() { return texture; };
	uint32 GetWidth() { return imageInfo.Width; };
	uint32 GetHeight() { return imageInfo.Height; };
	bool IsEmpty() { return texture == nullptr; };

	bool IsSupportedExtension(const std::string& ext);
	bool CreateFromFile(IDirect3DDevice9* pDevice, const std::string& fileName, D3DFORMAT format = D3DFMT_UNKNOWN);
	bool CreateFromFileInMPQ(IDirect3DDevice9* pDevice, HANDLE archive, const std::string& fileName, D3DFORMAT format = D3DFMT_UNKNOWN);

	void Release();
};