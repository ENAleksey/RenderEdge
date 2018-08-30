#pragma once

#include "FreeTypeFont.h"
#include "Texture.h"
#include <memory>

class BaseFont
{
public:
	BaseFont(IDirect3DDevice9* pDevice, const std::string& fontName, uint32 size, int32 style);
	~BaseFont();

	Texture*    pTexture;       // onwed! glyph set texture
	TextMetrics pMetrics;
	int32       pSurfaceWidth;  // width of glyph set texture (px)
	int32       pSurfaceHeight; // height of glyph set texture (px)
	int32       pMargin;        // glyph margin in texture (px)
	CharInfo    pInfo[256];     // glyph placement info (orig. ABC widths and position incl. margin)
	int32       pFirst;
	int32       pCount;
};

class Font
{
public:
	Font();
	~Font();

	bool CreateFromFile(IDirect3DDevice9* pDevice, const std::string& fontName, uint32 size);
	bool CreateFromFileInMPQ(IDirect3DDevice9* pDevice, HANDLE archive, const std::string& fontName, uint32 size);

	BaseFont* GetNormal();
	BaseFont* GetBold();
	BaseFont* GetItalic();
	BaseFont* GetBoldItalic();

private:
	BaseFont* normalFont;
	BaseFont* boldFont;
	BaseFont* italicFont;
	BaseFont* boldItalicFont;
};
