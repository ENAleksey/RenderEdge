#include "Font.h"
#include "Engine.h"

CBaseFont::CBaseFont(IDirect3DDevice9* pDevice, const std::string& fontName, uint32 size, int32 style) : pFirst(32), pCount(224)
{
	CFreeTypeFont* pFont = new CFreeTypeFont(fontName, size, style);
	pTexture = new Texture2D();

	pFont->RenderGlyphsToSurface(pDevice, pFirst, pCount, pTexture, pSurfaceWidth, pSurfaceHeight, pMargin, pInfo);
	pFont->GetMetrics(pMetrics);

	SAFE_DELETE(pFont)
}

CBaseFont::~CBaseFont()
{
	SAFE_DELETE(pTexture);
}


CFont::CFont()
{

}

CFont::~CFont()
{
	SAFE_DELETE(normalFont);
	SAFE_DELETE(boldFont);
	SAFE_DELETE(italicFont);
	SAFE_DELETE(boldItalicFont);
}

bool CFont::CreateFromFile(IDirect3DDevice9* pDevice, const std::string& fontName, uint32 size)
{
	normalFont = new CBaseFont(pDevice, fontName, size, 0);
	boldFont = new CBaseFont(pDevice, fontName, size, FONT_STYLE_BOLD);
	italicFont = new CBaseFont(pDevice, fontName, size, FONT_STYLE_ITALIC);
	boldItalicFont = new CBaseFont(pDevice, fontName, size, FONT_STYLE_BOLD | FONT_STYLE_ITALIC);

	return true;
}

bool CFont::CreateFromFileInMPQ(IDirect3DDevice9* pDevice, HANDLE archive, const std::string& fontName, uint32 size)
{
	return false;
}

CBaseFont* CFont::GetNormal()
{
	if (normalFont == nullptr)
		return nullptr;
	
	return normalFont;
}

CBaseFont* CFont::GetBold()
{
	if (boldFont == nullptr)
		return GetNormal();
	
	return boldFont;
}

CBaseFont* CFont::GetItalic()
{
	if (italicFont == nullptr)
		return GetNormal();

	return italicFont;
}

CBaseFont* CFont::GetBoldItalic()
{
	if (boldItalicFont == nullptr)
		return GetNormal();
	
	return boldItalicFont;
}
