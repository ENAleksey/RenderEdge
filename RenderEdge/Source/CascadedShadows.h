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
	TextureRenderTarget2D shadowRT;
	IDirect3DSurface9* pShadowDepth;
	IDirect3DVertexDeclaration9* pVertexDecl;
	//uint32 m_iNumCascades;

	void UpdateCascades();
	void UpdateSplitDist(Frustum* frustums, float nd, float fd);
	void UpdateFrustumPoints(Frustum& frustum, const D3DXVECTOR3& center, const D3DXVECTOR3& view_dir);
	void RenderCascade(uint32 iCascade);

public:
	CCascadedShadows(IDirect3DDevice9* pDevice);
	~CCascadedShadows();

	void OnResetDevice();
	void OnLostDevice();
	void ReloadShaders();

	bool IsEnabled() { return (bObjectsShadows || bTerrainShadows); }
	//const uint32& GetCascadesCount() { return m_iNumCascades; }
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
	D3DXVECTOR4 vShadowBufferSize;
	D3DCULL iShadowCullMode;
	D3DXMATRIX mShadow[NUM_CASCADES];

	std::vector<Mesh*> terrainMeshes;
	std::vector<Mesh*> unitMeshes;
	uint32 iChunksCount;
	uint32 iUnitsCount;

	Frustum pFrustums[NUM_CASCADES];
	float splitDepths[NUM_CASCADES];
	float fSplitWeight;
	bool bVisCascades;
};

extern CCascadedShadows* CascadedShadows;
