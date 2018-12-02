#pragma once

#include "Utils.h"

class Texture2D
{
private:
	IDirect3DTexture9* texture;
	D3DXIMAGE_INFO imageInfo;

public:
	Texture2D();
	~Texture2D();

	bool IsSupportedExtension(const std::string& ext);

	IDirect3DTexture9* GetTexture() { return texture; };
	uint32 GetWidth() { return imageInfo.Width; };
	uint32 GetHeight() { return imageInfo.Height; };
	bool IsEmpty() { return texture == nullptr; };

	bool CreateFromFile(IDirect3DDevice9* pDevice, const std::string& fileName, D3DFORMAT format = D3DFMT_UNKNOWN);
	bool CreateFromFileInMPQ(IDirect3DDevice9* pDevice, HANDLE archive, const std::string& fileName, D3DFORMAT format = D3DFMT_UNKNOWN);
	bool CreateFromArray(IDirect3DDevice9* pDevice, const uint8* data, uint32 width, uint32 height, D3DFORMAT format);

	void Release();
};