#pragma once

#include "Engine.h"
#include "Mesh.h"
#include "TextureRenderTarget2D.h"
#include <vector>

#define NUM_CASCADES 3

struct Frustum
{
	float neard;
	float fard;
	float fov;
	float ratio;
	D3DXVECTOR3 point[8];
	D3DXVECTOR3 center;
};


class CCascadedShadows
{
private:
	IDirect3DDevice9* m_pDevice;
	ID3DXEffect* m_pEffect;
	uint32 m_iNumCascades;
	TextureRenderTarget2D shadowRT;
	IDirect3DSurface9* pShadowDepth;
	IDirect3DVertexDeclaration9* pVertexDecl;

	void UpdateSplitDist(Frustum* f, float nd, float fd);
	void UpdateFrustumPoints(Frustum& f, D3DXVECTOR3& center, D3DXVECTOR3& view_dir);
	void RenderCascade(uint32 iCascade);

public:
	CCascadedShadows(IDirect3DDevice9* pDevice);
	~CCascadedShadows();

	void OnResetDevice();
	void OnLostDevice();

	bool IsEnabled() { return (bObjectsShadows || bTerrainShadows); }
	const uint32& GetCascadesCount() { return m_iNumCascades; }
	IDirect3DTexture9* GetTexture() { return shadowRT.GetTexture(); }
	void ReleaseMeshes();
	void Render();

	bool bObjectsShadows;
	bool bTerrainShadows;
	bool bSoftShadows;
	float fSoftTransitionScale;
	float fShadowSharpen;
	float fRadius;
	float fAlphaThreshold;
	float fFarZ;
	float fFoV;
	uint32 iShadowMapSize;
	uint32 iShadowMapSizeOld;
	D3DCULL iShadowCullMode;
	D3DXMATRIX mShadow[NUM_CASCADES];

	std::vector<Mesh*> terrainMeshes;
	std::vector<Mesh*> unitMeshes;
	uint32 iChunksCount;
	uint32 iUnitsCount;

	Frustum f[NUM_CASCADES];
	float fSplitWeight;
	D3DXVECTOR4 far_bound;
	bool bVisCascades;
};

extern CCascadedShadows* CascadedShadows;
