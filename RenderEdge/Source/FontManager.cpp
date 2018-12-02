#include "FontManager.h"
#include "Utils.h"
#include "Log.h"
#include "MPQ.h"


CFontManager* FontManager;

bool CFontManager::LoadFontFromMPQ(const std::string& fileName)
{
	BUFFER Buffer;
	if (utils::GetFileExtension(fileName) == "ttf")
	{
		if (!MPQ::LoadFile(nullptr, fileName, Buffer))
		{
			LOG(ERROR) << "CFontManager::LoadFontFromMPQ -> Failed to load font file: " << fileName;
			return false;
		}
	}
	else
	{
		LOG(ERROR) << "CFontManager::LoadFontFromMPQ -> Unsupported extension: " << fileName;
		return false;
	}

	DWORD nFonts;
	if (AddFontMemResourceEx(Buffer.GetData(), Buffer.GetSize(), 0, &nFonts) == 0)
	{
		LOG(ERROR) << "CFontManager::LoadFontFromMPQ -> AddFontMemResourceEx failed: " << fileName;
		return false;
	}

	return true;
}

CFontManager::CFontManager(IDirect3DDevice9* pDevice)
{
	m_pDevice = pDevice;

	//LoadFontFromMPQ("Fonts\\FRIZQT__.ttf"); // Nimrod MT

	const char* defFontName = "Consolas";
	const uint32 defFontSize = 13;

	CreateFontFromFile(defFontName, defFontSize);
	m_pDefaultFont = GetFont(defFontName, defFontSize);
}

CFontManager::~CFontManager()
{
	for (uint32 i = 0; i < FontContainer.GetSize(); i++)
		SAFE_DELETE(FontContainer[i]);

	FontContainer.Clear();
}

bool CFontManager::CreateFontFromFile(const std::string& fontName, uint32 size)
{
	CFont* pFont = new CFont;
	int32 Index = FontContainer.GetIndex(fontName + std::to_string(size));

	if (Index != INVALID_INDEX)
	{
		return false;
	}

	if (!pFont->CreateFromFile(m_pDevice, fontName, size))
		return false;

	if (!FontContainer.Add(fontName + std::to_string(size), pFont))
	{
		LOG(ERROR) << "FontManager::CreateFontFromFile -> Unable to add font!";
		delete pFont; pFont = nullptr;
		return false;
	}

	return true;
}

bool CFontManager::CreateFontFromMPQ(HANDLE archive, const std::string& fontName, uint32 size)
{
	CFont* pFont = new CFont;
	int32 Index = FontContainer.GetIndex(fontName + std::to_string(size));

	if (Index != INVALID_INDEX)
	{
		return false;
	}

	if (!pFont->CreateFromFileInMPQ(m_pDevice, archive, fontName, size))
		return false;

	if (!FontContainer.Add(fontName + std::to_string(size), pFont))
	{
		LOG(ERROR) << "FontManager::CreateFontFromMPQ -> Unable to add font!";
		delete pFont; pFont = nullptr;
		return false;
	}

	return true;
}

CFont* CFontManager::GetFont(const std::string& fontName, uint32 size)
{
	int32 Index = FontContainer.GetIndex(fontName + std::to_string(size));

	if (Index == INVALID_INDEX) return nullptr;

	return FontContainer[Index];
}

CFont* CFontManager::GetDefaultFont()
{
	return m_pDefaultFont;
}

bool CFontManager::Remove(const std::string& fontName, uint32 size)
{
	int32 Index = FontContainer.GetIndex(fontName + std::to_string(size));

	if (Index == INVALID_INDEX) return false;

	FontContainer.Remove(Index);

	return true;
}

bool CFontManager::Remove(int32 id)
{
	if (!FontContainer.ValidIndex(id)) return false;

	FontContainer.Remove(id);

	return true;
}