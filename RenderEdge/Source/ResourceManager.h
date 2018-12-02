#pragma once

#include "Engine.h"
#include "Texture2D.h"
#include "TextureCube.h"

class CResourceManager
{
private:
	IDirect3DDevice9* m_pDevice;

public:
	CResourceManager(IDirect3DDevice9* pDevice);

	void LoadTexture2D(const std::string& fileName, Texture2D* pTexture2D, bool bFromMpq = false, D3DFORMAT format = D3DFMT_UNKNOWN);
	void LoadTextureCube(const std::string& fileName, TextureCube* pTextureCube, bool bFromMpq = false, D3DFORMAT format = D3DFMT_UNKNOWN);
	void LoadShader(const std::string& fileName, D3DXMACRO* defines, ID3DXEffect** pEffect, bool bFromMpq = false);

	static bool bAllowLocalFiles;
};

extern CResourceManager* ResourceManager;