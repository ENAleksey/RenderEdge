#pragma once

#include "Texture.h"
#include "Container.h"

class TextureManager
{
public:
	TextureManager(IDirect3DDevice9* pDevice);

	bool CreateTextureFromFile(const std::string& filename);
	bool CreateTextureFromMPQ(HANDLE archive, const std::string& filename);
	bool CreateEmptyTexture(uint32 argb, const std::string& name);
	Texture* GetTexture(const std::string& fileName);
	Texture* GetDefaultTexture();
	bool Remove(const std::string& fileName);
	bool Remove(int32 id);

private:
	IDirect3DDevice9* m_pDevice;
	CONTAINER<Texture*> TextureContainer;
	Texture* m_pDefaultTexture;
};

extern TextureManager* MainTextureManager;
