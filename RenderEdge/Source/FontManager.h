#pragma once

#include "Font.h"
#include "Container.h"

class FontManager
{
public:
	FontManager(IDirect3DDevice9* pDevice);

	bool LoadFontFromMPQ(const std::string& fileName);
	bool CreateFontFromFile(const std::string& fontName, uint32 size);
	bool CreateFontFromMPQ(HANDLE archive, const std::string& fontName, uint32 size);
	Font* GetFont(const std::string& fontName, uint32 size);
	Font* GetDefaultFont();
	bool Remove(const std::string& fontName, uint32 size);
	bool Remove(int32 id);

private:
	IDirect3DDevice9* m_pDevice;
	CONTAINER<Font*> FontContainer;
	Font* m_pDefaultFont;
};

extern FontManager* MainFontManager;
