#pragma once

#include <d3d9.h>
#include <d3dx9.h>
#include "Utils.h"

//class PostProcess
//{
//public:
//	PostProcess(IDirect3DDevice9* pDevice, uint32_t width, uint32_t height);
//	~PostProcess();
//
//	void OnResetDevice(uint32_t width, uint32_t height);
//	void OnLostDevice();
//	void Prepare();
//
//private:
//	void RenderQuad();
//	void ApplyEffect(const char* technique);
//
//	IDirect3DDevice9* m_pDevice;
//	IDirect3DVertexDeclaration9* m_pVertexDeclaration;
//	D3DXVECTOR4 m_vScreenSize;
//	ID3DXEffect* m_pEffect;
//};