#include "Font.h"
#include "Engine.h"

BaseFont::BaseFont(IDirect3DDevice9* pDevice, const std::string& fontName, uint32 size, int32 style) : pFirst(32), pCount(224)
{
	FreeTypeFont* pFont = new FreeTypeFont(fontName, size, style);
	pTexture = new Texture;

	pFont->RenderGlyphsToSurface(pDevice, pFirst, pCount, pTexture, pSurfaceWidth, pSurfaceHeight, pMargin, pInfo);
	pFont->GetMetrics(pMetrics);

	delete pFont;
	pFont = nullptr;
}

BaseFont::~BaseFont()
{
}



Font::Font()
{
}

Font::~Font()
{
	if (normalFont != nullptr)
	{
		delete normalFont; normalFont = nullptr;
	}
	if (boldFont != nullptr)
	{
		delete boldFont; boldFont = nullptr;
	}
	if (italicFont != nullptr)
	{
		delete italicFont; italicFont = nullptr;
	}
	if (boldItalicFont != nullptr)
	{
		delete boldItalicFont; boldItalicFont = nullptr;
	}
}

bool Font::CreateFromFile(IDirect3DDevice9* pDevice, const std::string& fontName, uint32 size)
{
	normalFont = new BaseFont(pDevice, fontName, size, 0);
	boldFont = new BaseFont(pDevice, fontName, size, FONT_STYLE_BOLD);
	italicFont = new BaseFont(pDevice, fontName, size, FONT_STYLE_ITALIC);
	boldItalicFont = new BaseFont(pDevice, fontName, size, FONT_STYLE_BOLD | FONT_STYLE_ITALIC);

	return true;
}

bool Font::CreateFromFileInMPQ(IDirect3DDevice9* pDevice, HANDLE archive, const std::string& fontName, uint32 size)
{
	return false;
}

BaseFont* Font::GetNormal()
{
	if (normalFont == nullptr)
		return nullptr;
	
	return normalFont;
}

BaseFont* Font::GetBold()
{
	if (boldFont == nullptr)
		return GetNormal();
	
	return boldFont;
}

BaseFont* Font::GetItalic()
{
	if (italicFont == nullptr)
		return GetNormal();

	return italicFont;
}

BaseFont* Font::GetBoldItalic()
{
	if (boldItalicFont == nullptr)
		return GetNormal();
	
	return boldItalicFont;
}
