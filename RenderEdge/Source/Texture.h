#pragma once

#include <d3d9.h>
#include <d3dx9.h>
#include <string.h>
#include <sstream>
#include "Buffer.h"
#include "int_t.h"

class Texture
{
public:
	Texture();
	~Texture();

	IDirect3DTexture9* texture;
	uint32 height;
	uint32 width;

	bool CreateFromFile(IDirect3DDevice9* pDevice, const std::string& filename);
	bool CreateFromFileInMPQ(IDirect3DDevice9* pDevice, HANDLE archive, const std::string& filename);
	bool CreateEmpty(IDirect3DDevice9* pDevice, uint32 argb);
	bool FromArray(IDirect3DDevice9* pDevice, const byte* bytes, uint32 width, uint32 height);
	bool IsSupportedExtension(const std::string& ext);
	void Release();
};