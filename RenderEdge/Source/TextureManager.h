#pragma once

#include "Texture2D.h"
#include "Container.h"

class CTextureManager
{
public:
	CTextureManager(IDirect3DDevice9* pDevice);
	~CTextureManager();

	bool CreateTextureFromFile(const std::string& filename);
	bool CreateTextureFromMPQ(HANDLE archive, const std::string& filename);
	bool CreateEmptyTexture(uint32 argb, const std::string& name);
	Texture2D* GetTexture(const std::string& fileName);
	Texture2D* GetDefaultTexture();
	bool Remove(const std::string& fileName);
	bool Remove(int32 id);

private:
	IDirect3DDevice9* m_pDevice;
	CONTAINER<Texture2D*> TextureContainer;
	Texture2D* m_pDefaultTexture;
};

extern CTextureManager* TextureManager;
