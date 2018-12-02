#pragma once

#include "Font.h"
#include "Container.h"

class CFontManager
{
public:
	CFontManager(IDirect3DDevice9* pDevice);
	~CFontManager();

	bool LoadFontFromMPQ(const std::string& fileName);
	bool CreateFontFromFile(const std::string& fontName, uint32 size);
	bool CreateFontFromMPQ(HANDLE archive, const std::string& fontName, uint32 size);
	CFont* GetFont(const std::string& fontName, uint32 size);
	CFont* GetDefaultFont();
	bool Remove(const std::string& fontName, uint32 size);
	bool Remove(int32 id);

private:
	IDirect3DDevice9* m_pDevice;
	CONTAINER<CFont*> FontContainer;
	CFont* m_pDefaultFont;
};

extern CFontManager* FontManager;
