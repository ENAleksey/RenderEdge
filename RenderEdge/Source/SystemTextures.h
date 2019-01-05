#pragma once

#include "TextureRenderTarget2D.h"
#include "Utils.h"

class CSystemTextures
{
private:
	IDirect3DDevice9* m_pDevice;

	void InitTemporaryResources();
	void ReleaseTemporaryResources();

public:
	CSystemTextures(IDirect3DDevice9* pDevice);
	~CSystemTextures();

	void OnResetDevice();
	void OnLostDevice();

	TextureRenderTarget2D preIntegratedGFRT;
};

extern CSystemTextures* SystemTextures;