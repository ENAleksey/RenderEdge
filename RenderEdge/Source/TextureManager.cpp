#include "TextureManager.h"
#include "Utils.h"
//#include "Log.h"


CTextureManager* TextureManager;

CTextureManager::CTextureManager(IDirect3DDevice9* pDevice)
{
	m_pDevice = pDevice;

	CreateEmptyTexture(0xFF00FF00, "Default");
	m_pDefaultTexture = GetTexture("Default");
}

CTextureManager::~CTextureManager()
{
	for (uint32 i = 0; i < TextureContainer.GetSize(); i++)
		SAFE_DELETE(TextureContainer[i]);

	TextureContainer.Clear();
}

bool CTextureManager::CreateTextureFromFile(const std::string& filename)
{
	Texture2D* texture = new Texture2D();
	int32 Index = TextureContainer.GetIndex(filename);

	if (Index != INVALID_INDEX)
	{
		//LOG(logDEBUG) << "TextureManager::CreateTextureFromFile -> File already exists!";
		return false;
	}

	if (!texture->CreateFromFile(m_pDevice, filename))
		return false;

	if (!TextureContainer.Add(filename, texture))
	{
		//LOG(logERROR) << "TextureManager::CreateTextureFromFile -> Unable to add texture!";
		delete texture; texture = nullptr;
		return false;
	}

	return true;
}

bool CTextureManager::CreateTextureFromMPQ(HANDLE archive, const std::string& filename)
{
	Texture2D* texture = new Texture2D();
	int32 Index = TextureContainer.GetIndex(filename);

	if (Index != INVALID_INDEX)
	{
		//LOG(logDEBUG) << "TextureManager::CreateTextureFromMPQ -> File already exists!";
		return false;
	}

	if (!texture->CreateFromFileInMPQ(m_pDevice, archive, filename))
		return false;

	if (!TextureContainer.Add(filename, texture))
	{
		//LOG(logERROR) << "TextureManager::CreateTextureFromMPQ -> Unable to add texture!";
		delete texture; texture = nullptr;
		return false;
	}

	return true;
}

bool CTextureManager::CreateEmptyTexture(uint32 argb, const std::string& name)
{
	Texture2D* texture = new Texture2D();
	int32 Index = TextureContainer.GetIndex(name);

	if (Index != INVALID_INDEX)
	{
		//LOG(logDEBUG) << "TextureManager::CreateEmptyTexture -> File already exists!";
		return false;
	}

	if (!texture->CreateFromArray(m_pDevice, reinterpret_cast<uint8*>(&argb), 1, 1, D3DFMT_A8R8G8B8))
		return false;

	if (!TextureContainer.Add(name, texture))
	{
		//LOG(logERROR) << "TextureManager::CreateEmptyTexture -> Unable to add texture!";
		delete texture; texture = nullptr;
		return false;
	}

	return true;
}

Texture2D* CTextureManager::GetTexture(const std::string& fileName)
{
	int32 Index = TextureContainer.GetIndex(fileName);

	if (Index == INVALID_INDEX) return nullptr;

	return TextureContainer[Index];
}

Texture2D* CTextureManager::GetDefaultTexture()
{
	return m_pDefaultTexture;
}

bool CTextureManager::Remove(const std::string& fileName)
{
	int32 Index;

	Index = TextureContainer.GetIndex(fileName);
	if (Index == INVALID_INDEX) return false;

	TextureContainer.Remove(Index);

	return true;
}

bool CTextureManager::Remove(int32 id)
{
	if (!TextureContainer.ValidIndex(id)) return false;

	TextureContainer.Remove(id);

	return true;
}