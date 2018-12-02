#include "Mesh.h"

#include "Engine.h"
#include "Buffers.h"

struct Vertex
{
	D3DXVECTOR3 pos;
	D3DXVECTOR3 normal;
	D3DXVECTOR2 texCoord;
	//D3DXVECTOR3 tangent;
};

struct WarVertex
{
	D3DXVECTOR3 pos;
	D3DXVECTOR3 normal;
	D3DXVECTOR2 texCoord;
};

//void CalcTangentVector(const D3DXVECTOR3& pos1, const D3DXVECTOR3& pos2, const D3DXVECTOR3& pos3, const D3DXVECTOR2& texCoord1, const D3DXVECTOR2& texCoord2, const D3DXVECTOR2& texCoord3, const D3DXVECTOR3& normal, D3DXVECTOR4& tangent)
//{
//	D3DXVECTOR3 edge1(pos2.x - pos1.x, pos2.y - pos1.y, pos2.z - pos1.z);
//	D3DXVECTOR3 edge2(pos3.x - pos1.x, pos3.y - pos1.y, pos3.z - pos1.z);
//
//	D3DXVec3Normalize(&edge1, &edge1);
//	D3DXVec3Normalize(&edge2, &edge2);
//
//	D3DXVECTOR2 texEdge1(texCoord2.x - texCoord1.x, texCoord2.y - texCoord1.y);
//	D3DXVECTOR2 texEdge2(texCoord3.x - texCoord1.x, texCoord3.y - texCoord1.y);
//
//	D3DXVec2Normalize(&texEdge1, &texEdge1);
//	D3DXVec2Normalize(&texEdge2, &texEdge2);
//
//	D3DXVECTOR3 bitangent;
//	float det = (texEdge1.x * texEdge2.y) - (texEdge1.y * texEdge2.x);
//
//	if (fabsf(det) < 1e-6f)
//	{
//		tangent.x = 1.0f;
//		tangent.y = 0.0f;
//		tangent.z = 0.0f;
//
//		bitangent.x = 0.0f;
//		bitangent.y = 1.0f;
//		bitangent.z = 0.0f;
//	}
//	else
//	{
//		det = 1.0f / det;
//
//		tangent.x = (texEdge2.y * edge1.x - texEdge1.y * edge2.x) * det;
//		tangent.y = (texEdge2.y * edge1.y - texEdge1.y * edge2.y) * det;
//		tangent.z = (texEdge2.y * edge1.z - texEdge1.y * edge2.z) * det;
//		tangent.w = 0.0f;
//
//		bitangent.x = (-texEdge2.x * edge1.x + texEdge1.x * edge2.x) * det;
//		bitangent.y = (-texEdge2.x * edge1.y + texEdge1.x * edge2.y) * det;
//		bitangent.z = (-texEdge2.x * edge1.z + texEdge1.x * edge2.z) * det;
//
//		D3DXVec4Normalize(&tangent, &tangent);
//		D3DXVec3Normalize(&bitangent, &bitangent);
//	}
//
//	const D3DXVECTOR3 n = normal;
//	const D3DXVECTOR3 t = D3DXVECTOR3(tangent.x, tangent.y, tangent.z);
//	D3DXVECTOR3 b;
//
//	D3DXVec3Cross(&b, &n, &t);
//	tangent.w = (D3DXVec3Dot(&b, &bitangent) < 0.0f) ? -1.0f : 1.0f;
//}

Mesh::Mesh(IDirect3DDevice9* pDevice, IDirect3DBaseTexture9* texture, D3DPRIMITIVETYPE type, uint32 numVertices, uint32 primCount)
{
	m_pVB = nullptr;
	m_pIB = nullptr;
	m_Texture = nullptr;

	GetMesh(pDevice, texture, type, numVertices, primCount);
}

void Mesh::GetMesh(IDirect3DDevice9* pDevice, IDirect3DBaseTexture9* texture, D3DPRIMITIVETYPE type, uint32 numVertices, uint32 primCount)
{
	m_PrimCount = primCount;
	m_NumVertices = numVertices;
	pDevice->GetTransform(D3DTS_WORLD, &m_mWorld);
	m_Texture = texture;
	m_Type = type;


	SAFE_RELEASE(m_pVB);
	SAFE_RELEASE(m_pIB);

	pDevice->CreateVertexBuffer(g_VertexData.SizeLocked, D3DUSAGE_DYNAMIC | D3DUSAGE_WRITEONLY, 0, D3DPOOL_DEFAULT, &m_pVB, 0);
	pDevice->CreateIndexBuffer(g_IndexData.SizeLocked, D3DUSAGE_DYNAMIC | D3DUSAGE_WRITEONLY, D3DFMT_INDEX16, D3DPOOL_DEFAULT, &m_pIB, 0);


	void* pVertices = nullptr;
	if (m_pVB->Lock(0, g_VertexData.SizeLocked, &pVertices, D3DLOCK_DISCARD) == D3D_OK)
	{
		memcpy(pVertices, g_VertexData.pbLocked, g_VertexData.SizeLocked);
		m_pVB->Unlock();
	}

	void* pIndices = nullptr;
	if (m_pIB->Lock(0, g_IndexData.SizeLocked, &pIndices, D3DLOCK_DISCARD) == D3D_OK)
	{
		memcpy(pIndices, g_IndexData.pbLocked, g_IndexData.SizeLocked);
		m_pIB->Unlock();
	}
}

void Mesh::Render(IDirect3DDevice9* pDevice)
{
	pDevice->SetStreamSource(0, m_pVB, 0, sizeof(Vertex));
	pDevice->SetIndices(m_pIB);
	pDevice->DrawIndexedPrimitive(m_Type, 0, 0, m_NumVertices, 0, m_PrimCount);
}

void Mesh::Release()
{
	SAFE_RELEASE(m_pVB);
	SAFE_RELEASE(m_pIB);

	m_PrimCount = 0;
	m_NumVertices = 0;
	D3DXMatrixIdentity(&m_mWorld);
	m_Texture = nullptr;
}