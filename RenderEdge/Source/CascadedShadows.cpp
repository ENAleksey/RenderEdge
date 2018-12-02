#include "CascadedShadows.h"
#include "ResourceManager.h"
#include "PostProcessing.h"

CCascadedShadows* CascadedShadows = nullptr;


CCascadedShadows::CCascadedShadows(IDirect3DDevice9* pDevice)
{
	m_pDevice = pDevice;

	bObjectsShadows = false;
	bTerrainShadows = false;
	bSoftShadows = false;
	fSoftTransitionScale = 200.0f;
	fShadowSharpen = 1.0f;
	fRadius = 1.0f;
	fAlphaThreshold = 0.8f;
	fFarZ = 3000.0f;
	fFoV = 45.0f;
	iShadowMapSize = 1024;
	iShadowMapSizeOld = iShadowMapSize;
	iShadowCullMode = D3DCULL::D3DCULL_NONE;
	pShadowDepth = nullptr;

	iChunksCount = 0;
	iUnitsCount = 0;

	fSplitWeight = 0.04f;
	far_bound = D3DXVECTOR4(0, 0, 0, 0);
	bVisCascades = false;

	D3DVERTEXELEMENT9 vertexElements[] =
	{
		{ 0,  0, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION, 0 },
		{ 0, 12, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_NORMAL,   0 },
		{ 0, 24, D3DDECLTYPE_FLOAT2, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 0 },
		D3DDECL_END()
	};

	m_pDevice->CreateVertexDeclaration(vertexElements, &pVertexDecl);

	if (ResourceManager)
		ResourceManager->LoadShader("Shaders\\Shadows.cso", nullptr, &m_pEffect);
}

CCascadedShadows::~CCascadedShadows()
{
	SAFE_RELEASE(m_pEffect);
	SAFE_RELEASE(pVertexDecl);
	SAFE_RELEASE(pShadowDepth);
	shadowRT.Release();
	ReleaseMeshes();
}

void CCascadedShadows::OnResetDevice()
{
	if (m_pEffect)
		m_pEffect->OnResetDevice();
}

void CCascadedShadows::OnLostDevice()
{
	if (m_pEffect)
		m_pEffect->OnLostDevice();

	SAFE_RELEASE(pShadowDepth);
	shadowRT.Release();
	ReleaseMeshes();
}

void CCascadedShadows::ReleaseMeshes()
{
	for (auto& mesh : terrainMeshes)
		SAFE_DELETE(mesh);
	for (auto& mesh : unitMeshes)
		SAFE_DELETE(mesh);

	terrainMeshes.clear();
	unitMeshes.clear();
}





D3DXMATRIX* MatrixLookAtLH(D3DXMATRIX *pout, CONST D3DXVECTOR3 *peye, CONST D3DXVECTOR3 *pat, CONST D3DXVECTOR3 *pup)
{
	D3DXVECTOR3 axisX, axisY, axisZ;

	D3DXVec3Subtract(&axisZ, pat, peye);
	D3DXVec3Normalize(&axisZ, &axisZ);
	D3DXVec3Cross(&axisX, &axisZ, pup);
	D3DXVec3Normalize(&axisX, &axisX);
	D3DXVec3Cross(&axisY, &axisX, &axisZ);
	D3DXVec3Normalize(&axisY, &axisY);

	pout->m[0][0] = axisX.x;
	pout->m[1][0] = axisX.y;
	pout->m[2][0] = axisX.z;
	pout->m[3][0] = -D3DXVec3Dot(&axisX, peye);
	pout->m[0][1] = axisY.x;
	pout->m[1][1] = axisY.y;
	pout->m[2][1] = axisY.z;
	pout->m[3][1] = -D3DXVec3Dot(&axisY, peye);
	pout->m[0][2] = axisZ.x;
	pout->m[1][2] = axisZ.y;
	pout->m[2][2] = axisZ.z;
	pout->m[3][2] = -D3DXVec3Dot(&axisZ, peye);
	pout->m[0][3] = 0.0f;
	pout->m[1][3] = 0.0f;
	pout->m[2][3] = 0.0f;
	pout->m[3][3] = 1.0f;

	return pout;
}

void CCascadedShadows::RenderCascade(uint32 curSplit)
{
	D3DXMATRIX matView, matProj;

	const float dist = min(fFarZ, g_fCameraFarZ);
	D3DXVECTOR3 lightDir = g_bDefaultLightDir ? g_vGlobalLightDir : g_vLightDir;
	D3DXVECTOR3 LightPos = f[curSplit].center - lightDir * dist;
	MatrixLookAtLH(&matView, &LightPos, &f[curSplit].center, &D3DXVECTOR3(0.0f, 0.0f, 1.0f));
	//D3DXMatrixLookAtLH(&matView, &LightPos, &f[curSplit].center, (g_fDebugValue == -1.0f) ? &D3DXVECTOR3(0.0f, 1.0f, 0.0f) : &D3DXVECTOR3(0.0f, 0.0f, 1.0f));

	//MatrixLookAtLH(&matView, &D3DXVECTOR3(0.0f, 0.0f, 0.0f), &lightDir, &D3DXVECTOR3(0.0f, 0.0f, 1.0f));


	//============================================================================


	//{
	float minX = FLT_MAX;
	float minY = FLT_MAX;
	float minZ = FLT_MAX;
	float maxX = -FLT_MAX;
	float maxY = -FLT_MAX;
	float maxZ = -FLT_MAX;


	//============================================================================


	D3DXVECTOR4 trans0(f[curSplit].point[0], 1);
	D3DXVec4Transform(&trans0, &trans0, &matView);

	minX = trans0.x; maxX = trans0.x;
	minY = trans0.y; maxY = trans0.y;
	maxZ = trans0.z; minZ = trans0.z;

	for (uint32 i = 0; i < 8; i++)
	{
		D3DXVECTOR4 trans(f[curSplit].point[i], 1);
		D3DXVec4Transform(&trans, &trans, &matView);

		if (minX > trans.x) minX = trans.x;
		if (maxX < trans.x) maxX = trans.x;
		if (minY > trans.y) minY = trans.y;
		if (maxY < trans.y) maxY = trans.y;
		if (minZ > trans.z) minZ = trans.z;
		if (maxZ < trans.z) maxZ = trans.z;
	}


	//D3DXMatrixOrthoOffCenterLH(&matProj, -1.0f, 1.0f, 1.0f, -1.0f, -minZ, -maxZ);

	minZ = 10.0f;

						 //float W = (abs(maxX - minX));
						 //float H = (abs(maxY - minY));


	D3DXMatrixOrthoOffCenterLH(&matProj, minX, maxX, minY, maxY, minZ, maxZ);
	//D3DXMatrixOrthoLH(&matProj, W, H, minZ, maxZ);


	//============================================================================


	//D3DXVECTOR4 trans0(f[curSplit].point[0], 1);
	//D3DXVec4Transform(&trans0, &trans0, &matView);
	//
	//minZ = trans0.z;
	//maxZ = trans0.z;
	//
	//for (uint32 i = 1; i < 8; i++)
	//{
	//	D3DXVECTOR4 trans(f[curSplit].point[i], 1);
	//	D3DXVec4Transform(&trans, &trans, &matView);
	//
	//	if (trans.z > maxZ) { maxZ = trans.z; }
	//	if (trans.z < minZ) { minZ = trans.z; }
	//}
	//
	//D3DXMatrixOrthoOffCenterLH(&matProj, -1.0f, 1.0f, 1.0f, -1.0f, -maxZ, -minZ);
	//
	//D3DXMATRIX viewInverse;
	//D3DXMatrixInverse(&viewInverse, nullptr, &g_mView);
	//
	//for (uint32 i = 0; i < 8; i++)
	//{
	//	D3DXVECTOR4 trans(f[curSplit].point[i], 1);
	//	D3DXVec4Transform(&trans, &trans, &(matView * matProj)); //(matView * matProj)
	//
	//	if (minX > trans.x) minX = trans.x;
	//	if (maxX < trans.x) maxX = trans.x;
	//	if (minY > trans.y) minY = trans.y;
	//	if (maxY < trans.y) maxY = trans.y;
	//	//if (minZ > trans.z) minZ = trans.z;
	//	if (maxZ < trans.z) maxZ = trans.z;
	//}

	/*float quantizationStep = 1.0f / g_iShadowMapSize;
	float qx = (float)std::remainder(minX, quantizationStep);
	float qy = (float)std::remainder(minY, quantizationStep);
	minX -= qx;
	minY -= qy;
	maxX += g_iShadowMapSize;
	maxY += g_iShadowMapSize;

	D3DXMatrixOrthoOffCenterLH(&matProj, minX, maxX, minY, maxY, minZ, maxZ);*/


	//============================================================================

	//minZ = 0.0f;

	float fScaleX = 2.0f / (maxX - minX);
	float fScaleY = 2.0f / (maxY - minY);
	float fScaleZ = 1.0f;// 1.0f / (maxZ - minZ);

	float fOffsetX = -0.5f*(maxX + minX)*fScaleX;
	float fOffsetY = -0.5f*(maxY + minY)*fScaleY;
	float fOffsetZ = 0.0f;// -minZ * fScaleZ;

	D3DXMATRIX mCropView(
		fScaleX, 0.0f, 0.0f, 0.0f,
		0.0f, fScaleY, 0.0f, 0.0f,
		0.0f, 0.0f, fScaleZ, 0.0f,
		fOffsetX, fOffsetY, fOffsetZ, 1.0f);

	//matProj *= mCropView;
	//}

	float fTexOffsX = 0.5f + (0.5f / iShadowMapSize / 3.0f);
	float fTexOffsY = 0.5f + (0.5f / iShadowMapSize);
	D3DXMATRIX m_bias(
		0.5f, 0.0f, 0.0f, 0.0f,
		0.0f, -0.5f, 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f, 0.0f,
		fTexOffsX, fTexOffsY, 0.0f, 1.0f);

	D3DXMATRIX matLightViewProj = matView * matProj;
	mShadow[curSplit] = matLightViewProj * m_bias;


	//========================================================================

	D3DVIEWPORT9 oldViewport;
	D3DVIEWPORT9 viewport{ curSplit * iShadowMapSize, 0, iShadowMapSize, iShadowMapSize, 0, 1 };
	m_pDevice->GetViewport(&oldViewport);
	m_pDevice->SetViewport(&viewport);

	m_pEffect->SetTechnique("BuildDepthBuffer");

	uint32 uPasses = 0;
	m_pEffect->Begin(&uPasses, 0);
	m_pEffect->BeginPass(0);

	//=============== Render Scene ==================
	m_pDevice->SetVertexDeclaration(pVertexDecl);

	if (bTerrainShadows)
	{
		for (const auto& mesh : terrainMeshes)
		{
			m_pEffect->SetMatrix("g_mLightViewProj", &(mesh->m_mWorld * matLightViewProj));
			m_pEffect->SetTexture("g_albedoTexture", nullptr);
			m_pEffect->SetFloat("g_fAlphaThreshold", 0.0f);
			m_pEffect->CommitChanges();
			mesh->Render(m_pDevice);
		}
	}

	if (bObjectsShadows)
	{
		for (const auto& mesh : unitMeshes)
		{
			m_pEffect->SetMatrix("g_mLightViewProj", &(mesh->m_mWorld * matLightViewProj));
			m_pEffect->SetTexture("g_albedoTexture", mesh->m_Texture);
			m_pEffect->SetFloat("g_fAlphaThreshold", fAlphaThreshold);
			m_pEffect->CommitChanges();
			mesh->Render(m_pDevice);
		}
	}

	//===============================================

	m_pEffect->EndPass();
	m_pEffect->End();

	m_pDevice->SetViewport(&oldViewport);
}

void CCascadedShadows::UpdateSplitDist(Frustum* f, float nd, float fd)
{
	float lambda = fSplitWeight;
	float ratio = fd / nd;

	// calculate how many shadow maps do we really need
	/*m_currentSplitCount = 1;
	if (!m_maxSplitDistances.empty())
	{
	for (size_t i = 0; i < m_maxSplitDistances.size(); i++)
	{
	float d = m_maxSplitDistances[i] - m_splitShift;
	if (m_furthestPointInCamera >= d) m_currentSplitCount++;
	}
	}*/

	for (uint32 i = 1; i < NUM_CASCADES; i++)
	{
		float si = i / (float)NUM_CASCADES;
		f[i].neard = lambda * (nd*powf(ratio, si)) + (1 - lambda)*(nd + (fd - nd)*si);
		f[i - 1].fard = f[i].neard;// *1.005f;
	}

	f[0].neard = nd;
	f[NUM_CASCADES - 1].fard = fd;
}

void CCascadedShadows::UpdateFrustumPoints(Frustum& f, D3DXVECTOR3& center, D3DXVECTOR3& view_dir)
{
	D3DXVECTOR3 up(0.0f, 0.0f, 1.0f);
	D3DXVECTOR3 right;
	D3DXVec3Cross(&right, &view_dir, &up);

	D3DXVECTOR3 fc = center + view_dir * f.fard;
	D3DXVECTOR3 nc = center + view_dir * f.neard;

	D3DXVec3Normalize(&right, &right);
	D3DXVECTOR3 tmp;
	D3DXVec3Cross(&tmp, &right, &view_dir);
	D3DXVec3Normalize(&up, &tmp);

	float near_height = tan(f.fov / 2.0f) * f.neard;
	float near_width = near_height * f.ratio;
	float far_height = tan(f.fov / 2.0f) * f.fard;
	float far_width = far_height * f.ratio;

	f.point[0] = nc - up * near_height - right * near_width;
	f.point[1] = nc + up * near_height - right * near_width;
	f.point[2] = nc + up * near_height + right * near_width;
	f.point[3] = nc - up * near_height + right * near_width;

	f.point[4] = fc - up * far_height - right * far_width;
	f.point[5] = fc + up * far_height - right * far_width;
	f.point[6] = fc + up * far_height + right * far_width;
	f.point[7] = fc - up * far_height + right * far_width;

	D3DXVECTOR3 vCenter(0, 0, 0);
	for (uint32 i = 0; i < 8; i++)
		vCenter += f.point[i];
	vCenter /= 8;
	f.center = vCenter;
}

void CCascadedShadows::Render()
{
	float nearZ = max(100.0f, g_fCameraNearZ);
	float farZ = min(fFarZ, g_fCameraFarZ);
	UpdateSplitDist(f, nearZ, farZ);
	D3DXVECTOR4 bound;
	float far_b[3];
	for (uint32 i = 0; i < NUM_CASCADES; i++)
	{
		D3DXVec4Transform(&bound, &D3DXVECTOR4(0, 0, f[i].fard, 1), &g_mProj);
		far_b[i] = bound.z;
	}
	far_bound = D3DXVECTOR4(far_b[0], far_b[1], far_b[2], 1);

	D3DXVECTOR3 view_dir = D3DXVECTOR3(g_mView._13, g_mView._23, g_mView._33);
	float camFoV = D3DXToRadian(fFoV); // GetCameraField(3).fl;
	float aspectRatio = g_vBufferSize.x / g_vBufferSize.y;

	// ======================================================

	if (iShadowMapSize != iShadowMapSizeOld)
	{
		shadowRT.Release();
		SAFE_RELEASE(pShadowDepth);
		iShadowMapSizeOld = iShadowMapSize;
	}

	if (shadowRT.IsEmpty())
		if (!shadowRT.Create(m_pDevice, iShadowMapSize * NUM_CASCADES, iShadowMapSize, 1, ETextureUsage::RenderTarget, ETextureFormat::RFloat))
			Message("Failed to create shadowRT");

	if (pShadowDepth == nullptr)
		if (FAILED(m_pDevice->CreateDepthStencilSurface(iShadowMapSize * NUM_CASCADES, iShadowMapSize, D3DFMT_D16, D3DMULTISAMPLE_NONE, 0, TRUE, &pShadowDepth, nullptr)))
			Message("Failed to create pShadowDepth");

	// ======================================================

	IDirect3DSurface9* pOldColorRT = nullptr;
	IDirect3DSurface9* pOldDepthRT = nullptr;
	m_pDevice->GetRenderTarget(0, &pOldColorRT);
	m_pDevice->GetDepthStencilSurface(&pOldDepthRT);

	m_pDevice->SetRenderTarget(0, shadowRT.GetSurface());
	m_pDevice->SetDepthStencilSurface(pShadowDepth);
	m_pDevice->Clear(0, nullptr, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, 0xFFFFFFFF, 1.0f, 0);
	shadowRT.ReleaseSurface();

	m_pDevice->SetRenderState(D3DRS_ZENABLE, TRUE);
	m_pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
	m_pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);
	m_pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
	m_pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
	m_pDevice->SetRenderState(D3DRS_FOGENABLE, FALSE);
	m_pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);
	m_pDevice->SetRenderState(D3DRS_CULLMODE, iShadowCullMode);

	for (uint32 i = 0; i < NUM_CASCADES; i++)
	{
		f[i].fov = camFoV;
		f[i].ratio = aspectRatio;

		UpdateFrustumPoints(f[i], g_vCameraPos, view_dir);

		RenderCascade(i);
	}

	m_pDevice->SetRenderTarget(0, pOldColorRT);
	m_pDevice->SetDepthStencilSurface(pOldDepthRT);

	SAFE_RELEASE(pOldColorRT);
	SAFE_RELEASE(pOldDepthRT);

	// Debug Screen
	if (PostProcessing)
		PostProcessing->SetDebugScreen(EDebugScreen::CascadedShadows, &shadowRT, true, D3DXVECTOR2(1.0f, NUM_CASCADES / aspectRatio));
}
