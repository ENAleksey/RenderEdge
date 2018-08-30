#pragma once

#include "ft2build.h"
#include FT_FREETYPE_H

#include <d3d9.h>
#include "Texture.h"


enum FontStyleFlags
{
	FONT_STYLE_BOLD = 0x01,
	FONT_STYLE_ITALIC = 0x02,
	FONT_STYLE_UNDERLINE = 0x04
};

struct CharABC
{
	int32 a;
	int32 b;
	int32 c;
};

struct CharInfo
{
	int32     x;
	int32     y;
	int32     image_width;
	CharABC abc;
};

struct TextMetrics
{
	int32 ascent;
	int32 descent;
	int32 height;
	int32 maxwidth;
	int32 externalleading;
};


class FreeTypeFont
{
public:
	FreeTypeFont(const std::string& fileName, int32 size, int32 style);
	~FreeTypeFont();

	void GetMetrics(TextMetrics &metric);
	void GetCharABC(int32 first, int32 count, CharABC *abc);

	void CalcTextureSizeForRange(int32 first, int32 count, int32 &width, int32 &height);
	void CalcTextureSizeForRangeImpl(const TextMetrics &tm, CharABC *abc, int32 first, int32 count, int32 &width, int32 &height);

	bool RenderGlyphsToSurface(IDirect3DDevice9* pd3dDevice, int32 first, int32 count, Texture* texture, int32 &width, int32 &height, int32 &margin, CharInfo *info);

private:
	FT_ULong CharToIndex(char chr);

private:
	FT_Library pFreeType;
	FT_Face pFace;
};