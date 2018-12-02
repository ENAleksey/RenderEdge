#include "TextureRenderTarget2D.h"
#include "Log.h"


TextureRenderTarget2D::TextureRenderTarget2D() :
	width(0), height(0), mipLevels(0), texture(nullptr), surface(nullptr), format(ETextureFormat::Unknown)
{

}

TextureRenderTarget2D::TextureRenderTarget2D(IDirect3DDevice9* pDevice, uint32 width, uint32 height, uint32 mipLevels, ETextureUsage usage, ETextureFormat format) :
	width(0), height(0), mipLevels(0), texture(nullptr), surface(nullptr), format(ETextureFormat::Unknown)
{
	Create(pDevice, width, height, mipLevels, usage, format);
}

TextureRenderTarget2D::~TextureRenderTarget2D()
{
	Release();
}

bool TextureRenderTarget2D::Create(IDirect3DDevice9* pDevice, uint32 width, uint32 height, uint32 mipLevels, ETextureUsage usage, ETextureFormat format)
{
	this->width = width;
	this->height = height;
	this->mipLevels = mipLevels;
	this->format = format;

	HRESULT hr = pDevice->CreateTexture(width, height, mipLevels, static_cast<uint32>(usage), static_cast<D3DFORMAT>(format), D3DPOOL_DEFAULT, &texture, nullptr);

	if (hr != D3D_OK)
	{
		LOG(ERROR) << "TextureRenderTarget2D::Create -> Failed to create texture";
		return false;
	}

	return true;
}

IDirect3DSurface9* TextureRenderTarget2D::GetSurface()
{
	if (surface == nullptr && texture != nullptr)
		texture->GetSurfaceLevel(0, &surface);

	return surface;
}

void TextureRenderTarget2D::ReleaseSurface()
{
	SAFE_RELEASE(surface);
}

void TextureRenderTarget2D::Release()
{
	SAFE_RELEASE(texture);
	SAFE_RELEASE(surface);
}