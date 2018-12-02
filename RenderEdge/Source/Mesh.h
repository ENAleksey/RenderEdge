#pragma once

#include "utils.h"
#include "d3d8to9.hpp"

class Mesh
{
public:
	Mesh()
	{
		m_pVB = nullptr;
		m_pIB = nullptr;
		m_Texture = nullptr;
	}

	Mesh(IDirect3DDevice9* pDevice, IDirect3DBaseTexture9* texture, D3DPRIMITIVETYPE type, uint32 numVertices, uint32 primCount);

	~Mesh()
	{
		SAFE_RELEASE(m_pVB);
		SAFE_RELEASE(m_pIB);
	}

	void GetMesh(IDirect3DDevice9* pDevice, IDirect3DBaseTexture9* texture, D3DPRIMITIVETYPE type, uint32 numVertices, uint32 primCount);
	void Render(IDirect3DDevice9* pDevice);
	void Release();

	uint32 m_PrimCount;
	uint32 m_NumVertices;
	D3DXMATRIX m_mWorld;
	IDirect3DBaseTexture9* m_Texture;
	D3DPRIMITIVETYPE m_Type;
	IDirect3DVertexBuffer9* m_pVB;
	IDirect3DIndexBuffer9* m_pIB;
};