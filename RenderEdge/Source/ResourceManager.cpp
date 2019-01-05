#include "ResourceManager.h"
#include "MPQ.h"


CResourceManager* ResourceManager = nullptr;
bool CResourceManager::bAllowLocalFiles = false;

CResourceManager::CResourceManager(IDirect3DDevice9* pDevice)
{
	m_pDevice = pDevice;
}


void CResourceManager::LoadTexture2D(const std::string& fileName, Texture2D* pTexture, bool bFromMpq, D3DFORMAT format)
{
	bool bLocalFiles = false;
	if (bAllowLocalFiles && !bFromMpq)
		if (utils::FileExists(RenderEdgePath + fileName))
			bLocalFiles = true;

	if (bLocalFiles)
		pTexture->CreateFromFile(m_pDevice, RenderEdgePath + fileName, format);
	else
		pTexture->CreateFromFileInMPQ(m_pDevice, mpqRenderEdge, fileName, format);
}

void CResourceManager::LoadTextureCube(const std::string& fileName, TextureCube* pTexture, bool bFromMpq, D3DFORMAT format)
{
	bool bLocalFiles = false;
	if (bAllowLocalFiles && !bFromMpq)
		if (utils::FileExists(RenderEdgePath + fileName))
			bLocalFiles = true;

	if (bLocalFiles)
		pTexture->CreateFromFile(m_pDevice, RenderEdgePath + fileName, format);
	else
		pTexture->CreateFromFileInMPQ(m_pDevice, mpqRenderEdge, fileName, format);
}

void CResourceManager::LoadShader(const std::string& fileName, D3DXMACRO* defines, ID3DXEffect** pEffect, bool bFromMpq)
{
	std::string filePath = fileName;
	ID3DXBuffer* pErrorBuffer = nullptr;
	DWORD shaderFlags = D3DXFX_NOT_CLONEABLE;

	bool bLocalFiles = false;
	if (bAllowLocalFiles && !bFromMpq)
		if (utils::FileExists(RenderEdgePath + fileName))
			bLocalFiles = true;

	if (bLocalFiles)
	{
		D3DXCreateEffectFromFileA(m_pDevice, (RenderEdgePath + filePath).c_str(), defines, nullptr, shaderFlags, nullptr, pEffect, &pErrorBuffer);
	}
	else
	{
		BUFFER buffer;
		if (MPQ::LoadFile(0, filePath, buffer))
			D3DXCreateEffect(m_pDevice, buffer.GetData(), buffer.GetSize(), defines, nullptr, shaderFlags, nullptr, pEffect, &pErrorBuffer);
	}

	if (pErrorBuffer)
	{
		Message((char*)pErrorBuffer->GetBufferPointer(), fileName);
		pErrorBuffer->Release();
	}
}