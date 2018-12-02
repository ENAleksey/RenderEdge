#include "FreeTypeFont.h"
#include "Utils.h"
#include <Windows.h>
#include "MPQ.h"

#include <freetype/ftsnames.h>

CFreeTypeFont::CFreeTypeFont(const std::string& fileName, int32 size, int32 style)
{
	HFONT font = CreateFontA(size, 0, 0, 0, style & FONT_STYLE_BOLD ? FW_BOLD : FW_NORMAL, style & FONT_STYLE_ITALIC, 0, 0,
		DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, fileName.c_str());

	HDC dc = GetDC(0);
	HGDIOBJ pf = SelectObject(dc, HGDIOBJ(font));
	DWORD cbsize = GetFontData(dc, 0, 0, nullptr, 0);
	void* buffer = malloc(cbsize);
	GetFontData(dc, 0, 0, buffer, cbsize);

	DeleteObject(SelectObject(dc, pf));
	ReleaseDC(0, dc);

	//=======================

	FT_Init_FreeType(&pFreeType);

	FT_New_Memory_Face(pFreeType, reinterpret_cast<FT_Byte*>(buffer), cbsize, 0, &pFace);
	FT_Set_Char_Size(pFace, size << 6, size << 6, 96, 96);

	/*
	if ((pFace->style_flags & FT_STYLE_FLAG_ITALIC) == 0 && (style & FONT_STYLE_ITALIC) != 0) {
		FT_Matrix m;
		m.xx = 0x10000;
		m.xy = 22536;
		m.yx = 0;
		m.yy = 0x10000;
		FT_Set_Transform(pFace, &m, nullptr);
	}
	*/
}

CFreeTypeFont::~CFreeTypeFont()
{
	FT_Done_Face(pFace);
	FT_Done_FreeType(pFreeType);
}


void CFreeTypeFont::GetMetrics(TextMetrics &metric)
{
	metric.ascent = pFace->size->metrics.ascender >> 6;
	metric.descent = (-pFace->size->metrics.descender) >> 6;
	metric.height = metric.ascent + metric.descent;
	metric.maxwidth = pFace->size->metrics.max_advance >> 6;
	metric.externalleading = (pFace->size->metrics.height >> 6) - metric.height;
}

void CFreeTypeFont::GetCharABC(int32 first, int32 count, CharABC *abc)
{
	for (int32 n = 0; n < count; ++n)
	{
		FT_Load_Glyph(pFace, CharToIndex(first + n), FT_LOAD_NO_BITMAP);
		abc[n].a = pFace->glyph->metrics.horiBearingX / 64;
		abc[n].b = pFace->glyph->metrics.width >> 6;
		abc[n].c = pFace->glyph->metrics.horiAdvance / 64 - abc[n].a - abc[n].b;
	}
}

void CFreeTypeFont::CalcTextureSizeForRange(int32 first, int32 count, int32 &width, int32 &height)
{
	TextMetrics tm;
	GetMetrics(tm);

	CharABC *abcwd = new CharABC[count];
	GetCharABC(first, count, abcwd);

	CalcTextureSizeForRangeImpl(tm, abcwd, first, count, width, height);

	delete[] abcwd;
}

void CFreeTypeFont::CalcTextureSizeForRangeImpl(const TextMetrics &tm, CharABC *abc, int32 first, int32 count, int32 &width, int32 &height)
{
	const int32 margin = 1; // 1px margin around glyph
	const int32 extra_width = margin * 2;
	const int32 extra_height = margin * 2;

	int32 total_pixels = 0;

	for (int32 glyph = 0; glyph < count; ++glyph)
	{
		total_pixels += (abc[glyph].b + extra_width) * (tm.height + extra_height);
	}

	int32 side = int32(sqrt(float(total_pixels)));

	int32 size = 8; // let 8x8 be minimum texture size
	while (size < side)
		size *= 2;

	width = size;
	height = size;

	// check fit in sizes loop
	while (true)
	{
		int32 x = 0, y = 0;
		for (int32 glyph = 0; glyph < count; ++glyph)
		{
			int32 current_width = abc[glyph].b + extra_width;

			if (int32(x + current_width) > width)
			{
				x = 0;
				y += tm.height + extra_height;
			}

			x += current_width;
		}

		if (x > 0)
			y += tm.height + extra_height;

		if (y > height)
		{
			// height overflow, doubling width
			width *= 2;
			continue;
		}

		if (y <= height / 2)
		{
			// height can be reduced by 2
			height /= 2;
		}

		break;
	}
}


bool CFreeTypeFont::RenderGlyphsToSurface(IDirect3DDevice9* pDevice, int32 first, int32 count, Texture2D* texture, int32 &width, int32 &height, int32 &margin, CharInfo *info)
{
	margin = 1; // 1px margin around glyph
	const int32 extra_width = margin * 2;
	const int32 extra_height = margin * 2;

	TextMetrics tm;
	GetMetrics(tm);

	CharABC *abcwd = new CharABC[count];
	GetCharABC(first, count, abcwd);

	CalcTextureSizeForRangeImpl(tm, abcwd, first, count, width, height);

	uint8* texture_image = new uint8[width * height]; // final texture image (alpha channel only)
	int32 x = 0, y = 0;                               // glyph position in TEXTURE

	memset(texture_image, 0, width * height);

	for (int32 glyph = 0; glyph < count; ++glyph)
	{
		// render glyph
		FT_Load_Glyph(pFace, CharToIndex(glyph + first), FT_LOAD_RENDER);

		int32 width_diff = pFace->glyph->bitmap.width - abcwd[glyph].b;
		int32 current_width = abcwd[glyph].b + width_diff + extra_width;

		if (int32(x + current_width) > width)
		{
			x = 0;
			y += tm.height + extra_height;
		}

		//info->abc = abcwd[glyph];
		info->abc.a = pFace->glyph->bitmap_left;
		info->abc.b = pFace->glyph->bitmap.width;
		info->abc.c = (pFace->glyph->advance.x >> 6) - info->abc.a - info->abc.b;
		info->image_width = pFace->glyph->bitmap.width;
		info->x = x;
		info->y = y;

		// copy glyph to texture image
		uint8* src = reinterpret_cast<uint8*>(pFace->glyph->bitmap.buffer);
		uint8* dst = texture_image + x + (y + tm.ascent - pFace->glyph->bitmap_top) * width + margin;

		for (int32 gy = 0; gy < pFace->glyph->bitmap.rows; ++gy)
		{
			for (int32 gx = 0; gx < pFace->glyph->bitmap.width; ++gx)
			{
				*dst = *src;
				++dst;
				++src;
			}

			src += pFace->glyph->bitmap.pitch - pFace->glyph->bitmap.width;
			dst += width - pFace->glyph->bitmap.width;
		}

		x += current_width;
		++info;
	}

	delete[] abcwd;

	
	/*HANDLE f = CreateFileA("glyphs.raw", GENERIC_WRITE, 0, nullptr, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, 0);
	if (f != INVALID_HANDLE_VALUE)
	{
		DWORD written = 0;
		WriteFile(f, texture_image, width * height, &written, nullptr);
		CloseHandle(f);
	}*/
	

	texture->CreateFromArray(pDevice, texture_image, width, height, D3DFMT_A8);

	delete[] texture_image;

	return true;
}

FT_ULong CFreeTypeFont::CharToIndex(char chr)
{
	char output[4] = { 0, 0, 0, 0 };

	MultiByteToWideChar(CP_ACP, 0, &chr, 1, reinterpret_cast<LPWSTR>(&output), 4);

	return FT_Get_Char_Index(pFace, *reinterpret_cast<FT_ULong*>(output));
}
	