#pragma once

#include <d3d9.h>
#include <d3dx9.h>
#include "PostProcess.h"

struct SCREEN_VERTEX
{
	D3DXVECTOR4 p;
	D3DXVECTOR2 t;

	static const DWORD FVF = D3DFVF_XYZRHW | D3DFVF_TEX1;
};
//const DWORD SCREEN_VERTEX::FVF = D3DFVF_XYZRHW | D3DFVF_TEX1;

struct PostProcessManager 
{
	PostProcessManager(IDirect3DDevice9* pd3dDevice);
	~PostProcessManager();

	IDirect3DDevice9* m_pDevice;
	ID3DXEffect* m_pEffect;
	IDirect3DTexture9* m_pHDRTexture;
	IDirect3DSurface9* m_pHDRSurface;
	IDirect3DSurface9* m_pBackBuffer;

	bool g_presented;


	HRESULT InitTempRes();
	HRESULT InitPermRes();
	HRESULT ReleaseTempRes();
	HRESULT ReleasePermRes();
	void Render();


	void OnLostDevice();
	void OnResetDevice();
};

extern PostProcessManager* PP_Manager;