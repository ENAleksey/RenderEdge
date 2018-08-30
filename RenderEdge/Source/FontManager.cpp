#include "FontManager.h"
#include "Utils.h"
#include "Log.h"
#include "MPQ.h"


FontManager* MainFontManager;

bool FontManager::LoadFontFromMPQ(const std::string& fileName)
{
	BUFFER Buffer;
	if (utils::get_ext(fileName) == "ttf")
	{
		if (!MPQ::LoadFile(nullptr, fileName, Buffer))
		{
			Message("Failed to load font file:\n" + fileName);
			return false;
		}
	}
	else
	{
		Message("Failed to load font file:\nUnsupported extension");
		return false;
	}

	DWORD nFonts;
	if (AddFontMemResourceEx(Buffer.GetData(), Buffer.GetSize(), 0, &nFonts) == 0)
	{
		Message("Font add fails");
		return false;
	}

	return true;
}

FontManager::FontManager(IDirect3DDevice9* pDevice)
{
	m_pDevice = pDevice;

	//LoadFontFromMPQ("Fonts\\FRIZQT__.ttf"); // Nimrod MT

	const char* defFontName = "Consolas";
	const uint32 defFontSize = 13;

	CreateFontFromFile(defFontName, defFontSize);
	m_pDefaultFont = GetFont(defFontName, defFontSize);
}

bool FontManager::CreateFontFromFile(const std::string& fontName, uint32 size)
{
	Font* pFont = new Font;
	int32 Index = FontContainer.GetIndex(fontName + std::to_string(size));

	if (Index != INVALID_INDEX)
	{
		LOG(logDEBUG) << "FontManager::CreateFontFromFile -> File already exists!";
		return false;
	}

	if (!pFont->CreateFromFile(m_pDevice, fontName, size))
		return false;

	if (!FontContainer.Add(fontName + std::to_string(size), pFont))
	{
		LOG(logERROR) << "FontManager::CreateFontFromFile -> Unable to add font!";
		delete pFont; pFont = nullptr;
		return false;
	}

	return true;
}

bool FontManager::CreateFontFromMPQ(HANDLE archive, const std::string& fontName, uint32 size)
{
	Font* pFont = new Font;
	int32 Index = FontContainer.GetIndex(fontName + std::to_string(size));

	if (Index != INVALID_INDEX)
	{
		LOG(logDEBUG) << "FontManager::CreateFontFromMPQ -> File already exists!";
		return false;
	}

	if (!pFont->CreateFromFileInMPQ(m_pDevice, archive, fontName, size))
		return false;

	if (!FontContainer.Add(fontName + std::to_string(size), pFont))
	{
		LOG(logERROR) << "FontManager::CreateFontFromMPQ -> Unable to add font!";
		delete pFont; pFont = nullptr;
		return false;
	}

	return true;
}

Font* FontManager::GetFont(const std::string& fontName, uint32 size)
{
	int32 Index = FontContainer.GetIndex(fontName + std::to_string(size));

	if (Index == INVALID_INDEX) return nullptr;

	return FontContainer[Index];
}

Font* FontManager::GetDefaultFont()
{
	return m_pDefaultFont;
}

bool FontManager::Remove(const std::string& fontName, uint32 size)
{
	int32 Index = FontContainer.GetIndex(fontName + std::to_string(size));

	if (Index == INVALID_INDEX) return false;

	FontContainer.Remove(Index);

	return true;
}

bool FontManager::Remove(int32 id)
{
	if (!FontContainer.ValidIndex(id)) return false;

	FontContainer.Remove(id);

	return true;
}