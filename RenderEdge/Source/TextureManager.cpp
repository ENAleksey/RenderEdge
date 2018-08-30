#include "TextureManager.h"
#include "Utils.h"
#include "Log.h"


TextureManager* MainTextureManager;

TextureManager::TextureManager(IDirect3DDevice9* pDevice)
{
	m_pDevice = pDevice;

	CreateEmptyTexture(0xff00ff00, "Default");
	m_pDefaultTexture = GetTexture("Default");
}

bool TextureManager::CreateTextureFromFile(const std::string& filename)
{
	Texture* texture = new Texture;
	int32 Index = TextureContainer.GetIndex(filename);

	if (Index != INVALID_INDEX)
	{
		LOG(logDEBUG) << "TextureManager::CreateTextureFromFile -> File already exists!";
		return false;
	}

	if (!texture->CreateFromFile(m_pDevice, filename))
		return false;

	if (!TextureContainer.Add(filename, texture))
	{
		LOG(logERROR) << "TextureManager::CreateTextureFromFile -> Unable to add texture!";
		delete texture; texture = nullptr;
		return false;
	}

	return true;
}

bool TextureManager::CreateTextureFromMPQ(HANDLE archive, const std::string& filename)
{
	Texture* texture = new Texture;
	int32 Index = TextureContainer.GetIndex(filename);

	if (Index != INVALID_INDEX)
	{
		LOG(logDEBUG) << "TextureManager::CreateTextureFromMPQ -> File already exists!";
		return false;
	}

	if (!texture->CreateFromFileInMPQ(m_pDevice, archive, filename))
		return false;

	if (!TextureContainer.Add(filename, texture))
	{
		LOG(logERROR) << "TextureManager::CreateTextureFromMPQ -> Unable to add texture!";
		delete texture; texture = nullptr;
		return false;
	}

	return true;
}

bool TextureManager::CreateEmptyTexture(uint32 argb, const std::string& name)
{
	Texture* texture = new Texture;
	int32 Index = TextureContainer.GetIndex(name);

	if (Index != INVALID_INDEX)
	{
		LOG(logDEBUG) << "TextureManager::CreateEmptyTexture -> File already exists!";
		return false;
	}

	if (!texture->CreateEmpty(m_pDevice, argb))
		return false;

	if (!TextureContainer.Add(name, texture))
	{
		LOG(logERROR) << "TextureManager::CreateEmptyTexture -> Unable to add texture!";
		delete texture; texture = nullptr;
		return false;
	}

	return true;
}

Texture* TextureManager::GetTexture(const std::string& fileName)
{
	int32 Index = TextureContainer.GetIndex(fileName);

	if (Index == INVALID_INDEX) return nullptr;

	return TextureContainer[Index];
}

Texture* TextureManager::GetDefaultTexture()
{
	return m_pDefaultTexture;
}

bool TextureManager::Remove(const std::string& fileName)
{
	int32 Index;

	Index = TextureContainer.GetIndex(fileName);
	if (Index == INVALID_INDEX) return false;

	TextureContainer.Remove(Index);

	return true;
}

bool TextureManager::Remove(int32 id)
{
	if (!TextureContainer.ValidIndex(id)) return false;

	TextureContainer.Remove(id);

	return true;
}