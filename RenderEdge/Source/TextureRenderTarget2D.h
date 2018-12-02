#pragma once

#include "Utils.h"

enum class ETextureFormat : uint32
{
	Unknown = 0,
	RGB8 = 20,
	ARGB32 = 21,
	ARGB2101010 = 31,
	RG16 = 34,
	RGBA16 = 36,
	R8 = 50,
	R16 = 81,
	RHalf = 111,
	RGHalf = 112,
	RGBAHalf = 113,
	RFloat = 114,
	RGFloat = 115,
	RGBAFloat = 116,
	RESZ = MAKEFOURCC('R', 'E', 'S', 'Z'),
	INTZ = MAKEFOURCC('I', 'N', 'T', 'Z'),
	RAWZ = MAKEFOURCC('R', 'A', 'W', 'Z')
};

enum class ETextureUsage : uint32
{
	None = 0,
	RenderTarget = 1,
	DepthStencil = 2
};

class TextureRenderTarget2D
{
private:
	IDirect3DTexture9* texture;
	IDirect3DSurface9* surface;
	uint32 width;
	uint32 height;
	uint32 mipLevels;
	ETextureFormat format;

public:
	TextureRenderTarget2D();
	TextureRenderTarget2D(IDirect3DDevice9* pDevice, uint32 width, uint32 height, uint32 mipLevels, ETextureUsage usage, ETextureFormat format);
	~TextureRenderTarget2D();

	IDirect3DTexture9* GetTexture() { return texture; };
	uint32 GetWidth() { return width; };
	uint32 GetHeight() { return height; };
	uint32 GetMipLevels() { return mipLevels; };
	ETextureFormat GetFormat() { return format; };
	bool IsEmpty() { return texture == nullptr; };

	IDirect3DSurface9* GetSurface();
	void ReleaseSurface();

	bool Create(IDirect3DDevice9* pDevice, uint32 width, uint32 height, uint32 mipLevels, ETextureUsage usage, ETextureFormat format);
	void Release();
};