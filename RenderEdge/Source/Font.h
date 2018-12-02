#pragma once

#include "FreeTypeFont.h"
#include "Texture2D.h"
#include <memory>

class CBaseFont
{
public:
	CBaseFont(IDirect3DDevice9* pDevice, const std::string& fontName, uint32 size, int32 style);
	~CBaseFont();

	Texture2D*    pTexture;       // onwed! glyph set texture
	TextMetrics pMetrics;
	int32       pSurfaceWidth;  // width of glyph set texture (px)
	int32       pSurfaceHeight; // height of glyph set texture (px)
	int32       pMargin;        // glyph margin in texture (px)
	CharInfo    pInfo[256];     // glyph placement info (orig. ABC widths and position incl. margin)
	int32       pFirst;
	int32       pCount;
};

class CFont
{
public:
	CFont();
	~CFont();

	bool CreateFromFile(IDirect3DDevice9* pDevice, const std::string& fontName, uint32 size);
	bool CreateFromFileInMPQ(IDirect3DDevice9* pDevice, HANDLE archive, const std::string& fontName, uint32 size);
	//void Release();

	CBaseFont* GetNormal();
	CBaseFont* GetBold();
	CBaseFont* GetItalic();
	CBaseFont* GetBoldItalic();

private:
	CBaseFont* normalFont;
	CBaseFont* boldFont;
	CBaseFont* italicFont;
	CBaseFont* boldItalicFont;
};
