#include "CascadedShadows.h"
#include "ResourceManager.h"
#include "PostProcessing.h"
#include "Log.h"

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
	vShadowBufferSize = D3DXVECTOR4(iShadowMapSize * NUM_CASCADES, iShadowMapSize, 1.0f / (iShadowMapSize * NUM_CASCADES), 1.0f / iShadowMapSize);
	iShadowCullMode = D3DCULL::D3DCULL_NONE;
	pShadowDepth = nullptr;

	iChunksCount = 0;
	iUnitsCount = 0;

	fSplitWeight = 0.04f;
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


D3DXMATRIX* MatrixLookAtLH(D3DXMATRIX* pOut, const D3DXVECTOR3* pEye, const D3DXVECTOR3* pAt, const D3DXVECTOR3* pUp)
{
	D3DXVECTOR3 axisX, axisY, axisZ;

	D3DXVec3Subtract(&axisZ, pAt, pEye);
	D3DXVec3Normalize(&axisZ, &axisZ);
	D3DXVec3Cross(&axisX, &axisZ, pUp);
	D3DXVec3Normalize(&axisX, &axisX);
	D3DXVec3Cross(&axisY, &axisX, &axisZ);
	D3DXVec3Normalize(&axisY, &axisY);

	pOut->m[0][0] = axisX.x;
	pOut->m[1][0] = axisX.y;
	pOut->m[2][0] = axisX.z;
	pOut->m[3][0] = -D3DXVec3Dot(&axisX, pEye);
	pOut->m[0][1] = axisY.x;
	pOut->m[1][1] = axisY.y;
	pOut->m[2][1] = axisY.z;
	pOut->m[3][1] = -D3DXVec3Dot(&axisY, pEye);
	pOut->m[0][2] = axisZ.x;
	pOut->m[1][2] = axisZ.y;
	pOut->m[2][2] = axisZ.z;
	pOut->m[3][2] = -D3DXVec3Dot(&axisZ, pEye);
	pOut->m[0][3] = 0.0f;
	pOut->m[1][3] = 0.0f;
	pOut->m[2][3] = 0.0f;
	pOut->m[3][3] = 1.0f;

	return pOut;
}

D3DXMATRIX* MatrixOrthoOffCenterLH(D3DXMATRIX* pOut, float left, float right, float bottom, float top, float nearZ, float farZ)
{
	D3DXMatrixIdentity(pOut);

	pOut[0][0] = 2.0f / (right - left);
	pOut[1][1] = 2.0f / (top - bottom);
	pOut[2][2] = 2.0f / (farZ - nearZ);
	pOut[3][0] = -((right + left) / (right - left));
	pOut[3][1] = -((top + bottom) / (top - bottom));
	pOut[3][2] = -((farZ + nearZ) / (farZ - nearZ));

	return pOut;
}


void CCascadedShadows::RenderCascade(uint32 curSplit)
{
	D3DXMATRIX matView, matProj, matLightViewProj;

	// View Matrix
	{
		const float dist = min(fFarZ, g_fCameraFarZ);
		D3DXVECTOR3 lightDir = g_bDefaultLightDir ? g_vGlobalLightDir : g_vLightDir;
		D3DXVECTOR3 lightPos = pFrustums[curSplit].center - lightDir * dist;
		MatrixLookAtLH(&matView, &lightPos, &pFrustums[curSplit].center, &D3DXVECTOR3(0.0f, 0.0f, 1.0f));
	}

	// Projection Matrix
	{
		float minX = FLT_MAX;
		float minY = FLT_MAX;
		float minZ = FLT_MAX;
		float maxX = -FLT_MAX;
		float maxY = -FLT_MAX;
		float maxZ = -FLT_MAX;

		for (uint32 i = 0; i < 8; i++)
		{
			D3DXVECTOR4 trans(pFrustums[curSplit].point[i], 1.0f);
			D3DXVec4Transform(&trans, &trans, &matView);

			if (minX > trans.x) minX = trans.x;
			if (maxX < trans.x) maxX = trans.x;
			if (minY > trans.y) minY = trans.y;
			if (maxY < trans.y) maxY = trans.y;
			if (minZ > trans.z) minZ = trans.z;
			if (maxZ < trans.z) maxZ = trans.z;
		}

		minZ = 10.0f;

	//	if (g_fDebugValue == 1.0f)
		//	MatrixOrthoOffCenterLH(&matProj, minX, maxX, minY, maxY, minZ, maxZ);
		//else
			D3DXMatrixOrthoOffCenterLH(&matProj, minX, maxX, minY, maxY, minZ, maxZ);
	}

	// Shadow Matrix
	{
		float fTexOffsX = 0.5f + (0.5f * vShadowBufferSize.z);
		float fTexOffsY = 0.5f + (0.5f * vShadowBufferSize.w);
		D3DXMATRIX m_bias(
			0.5f, 0.0f, 0.0f, 0.0f,
			0.0f, -0.5f, 0.0f, 0.0f,
			0.0f, 0.0f, 1.0f, 0.0f,
			fTexOffsX, fTexOffsY, 0.0f, 1.0f);

		matLightViewProj = matView * matProj;
		mShadow[curSplit] = matLightViewProj * m_bias;
	}

	// Render Scene
	{
		D3DVIEWPORT9 oldViewport;
		D3DVIEWPORT9 viewport{ curSplit * iShadowMapSize, 0, iShadowMapSize, iShadowMapSize, 0.0f, 1.0f };
		m_pDevice->GetViewport(&oldViewport);
		m_pDevice->SetViewport(&viewport);

		m_pEffect->SetTechnique("BuildDepthBuffer");

		uint32 uPasses = 0;
		m_pEffect->Begin(&uPasses, 0);
		m_pEffect->BeginPass(0);

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

		m_pEffect->EndPass();
		m_pEffect->End();

		m_pDevice->SetViewport(&oldViewport);
	}
}

void CCascadedShadows::UpdateSplitDist(Frustum* frustums, float nearClip, float farClip)
{
	float lambda = fSplitWeight;
	float ratio = farClip / nearClip;

	// Calculate how many shadow maps do we really need
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
		frustums[i].neard = lambda * (nearClip * powf(ratio, si)) + (1 - lambda) * (nearClip + (farClip - nearClip) * si);
		frustums[i - 1].fard = frustums[i].neard;// *1.005f;
	}

	frustums[0].neard = nearClip;
	frustums[NUM_CASCADES - 1].fard = farClip;
}

void CCascadedShadows::UpdateCascades()
{
	float cascadeSplits[NUM_CASCADES];

	float nearClip = g_fCameraNearZ;
	float farClip = g_fCameraFarZ;
	float clipRange = farClip - nearClip;

	float minZ = nearClip;
	float maxZ = nearClip + clipRange;

	float range = maxZ - minZ;
	float ratio = maxZ / minZ;

	// Calculate split depths based on view camera furstum
	// Based on method presentd in https://developer.nvidia.com/gpugems/GPUGems3/gpugems3_ch10.html
	for (uint32 i = 0; i < NUM_CASCADES; i++)
	{
		float p = (i + 1) / static_cast<float>(NUM_CASCADES);
		float log = minZ * std::pow(ratio, p);
		float uniform = minZ + range * p;
		float d = fSplitWeight * (log - uniform) + uniform;
		cascadeSplits[i] = (d - nearClip) / clipRange;
	}

	// Calculate orthographic projection matrix for each cascade
	float lastSplitDist = 0.0;
	for (uint32 i = 0; i < NUM_CASCADES; i++)
	{
		float splitDist = cascadeSplits[i];

		D3DXVECTOR3 frustumCorners[8] = {
			D3DXVECTOR3(-1.0f, 1.0f, -1.0f),
			D3DXVECTOR3(1.0f, 1.0f, -1.0f),
			D3DXVECTOR3(1.0f, -1.0f, -1.0f),
			D3DXVECTOR3(-1.0f, -1.0f, -1.0f),
			D3DXVECTOR3(-1.0f, 1.0f, 1.0f),
			D3DXVECTOR3(1.0f, 1.0f, 1.0f),
			D3DXVECTOR3(1.0f, -1.0f, 1.0f),
			D3DXVECTOR3(-1.0f, -1.0f, 1.0f),
		};

		// Project frustum corners into world space
		D3DXMATRIX invCam;
		D3DXMatrixInverse(&invCam, nullptr, &(g_mProj * g_mView));
		for (uint32 i = 0; i < 8; i++)
		{
			D3DXVECTOR4 invCorner = D3DXVECTOR4(frustumCorners[i], 1.0f);
			D3DXVec4Transform(&invCorner, &invCorner, &invCam);
			frustumCorners[i] = D3DXVECTOR3(invCorner);// / invCorner.w;
		}

		for (uint32 i = 0; i < 4; i++)
		{
			D3DXVECTOR3 dist = frustumCorners[i + 4] - frustumCorners[i];
			frustumCorners[i + 4] = frustumCorners[i] + (dist * splitDist);
			frustumCorners[i] = frustumCorners[i] + (dist * lastSplitDist);
		}

		// Get frustum center
		D3DXVECTOR3 frustumCenter = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		for (uint32 i = 0; i < 8; i++)
		{
			frustumCenter += frustumCorners[i];
		}
		frustumCenter /= 8.0f;

		float radius = 0.0f;
		for (uint32 i = 0; i < 8; i++)
		{
			float distance = D3DXVec3Length(&(frustumCorners[i] - frustumCenter));
			radius = max(radius, distance);
		}
		radius = std::ceil(radius * 16.0f) / 16.0f;

		D3DXVECTOR3 maxExtents = D3DXVECTOR3(radius, radius, radius);
		D3DXVECTOR3 minExtents = -maxExtents;

		D3DXVECTOR3 lightDir = g_bDefaultLightDir ? g_vGlobalLightDir : g_vLightDir;
		D3DXMATRIX lightViewMatrix, lightOrthoMatrix;
		MatrixLookAtLH(&lightViewMatrix, &(frustumCenter - lightDir * -minExtents.z), &frustumCenter, &D3DXVECTOR3(0.0f, 0.0f, 1.0f));
		D3DXMatrixOrthoOffCenterLH(&lightOrthoMatrix, minExtents.x, maxExtents.x, minExtents.y, maxExtents.y, 0.0f, maxExtents.z - minExtents.z);

		// Store split distance and matrix in cascade
		splitDepths[i] = (g_fCameraNearZ + splitDist * clipRange) * -1.0f;
		mShadow[i] = lightOrthoMatrix * lightViewMatrix;

		lastSplitDist = cascadeSplits[i];
	}

	// Render Scene
	for (uint32 i = 0; i < NUM_CASCADES; i++)
	{
		D3DVIEWPORT9 oldViewport;
		D3DVIEWPORT9 viewport{ i * iShadowMapSize, 0, iShadowMapSize, iShadowMapSize, 0.0f, 1.0f };
		m_pDevice->GetViewport(&oldViewport);
		m_pDevice->SetViewport(&viewport);

		m_pEffect->SetTechnique("BuildDepthBuffer");

		uint32 uPasses = 0;
		m_pEffect->Begin(&uPasses, 0);
		m_pEffect->BeginPass(0);

		m_pDevice->SetVertexDeclaration(pVertexDecl);

		if (bTerrainShadows)
		{
			for (const auto& mesh : terrainMeshes)
			{
				m_pEffect->SetMatrix("g_mLightViewProj", &(mesh->m_mWorld * mShadow[i]));
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
				m_pEffect->SetMatrix("g_mLightViewProj", &(mesh->m_mWorld * mShadow[i]));
				m_pEffect->SetTexture("g_albedoTexture", mesh->m_Texture);
				m_pEffect->SetFloat("g_fAlphaThreshold", fAlphaThreshold);
				m_pEffect->CommitChanges();
				mesh->Render(m_pDevice);
			}
		}
		m_pEffect->EndPass();
		m_pEffect->End();

		m_pDevice->SetViewport(&oldViewport);
	}
}

void CCascadedShadows::UpdateFrustumPoints(Frustum& frustum, const D3DXVECTOR3& center, const D3DXVECTOR3& view_dir)
{
	D3DXVECTOR3 up(0.0f, 0.0f, 1.0f);
	D3DXVECTOR3 right;
	D3DXVec3Cross(&right, &view_dir, &up);

	D3DXVECTOR3 fc = center + view_dir * frustum.fard;
	D3DXVECTOR3 nc = center + view_dir * frustum.neard;

	D3DXVec3Normalize(&right, &right);
	D3DXVECTOR3 tmp;
	D3DXVec3Cross(&tmp, &right, &view_dir);
	D3DXVec3Normalize(&up, &tmp);

	float near_height = tan(frustum.fov / 2.0f) * frustum.neard;
	float near_width = near_height * frustum.ratio;
	float far_height = tan(frustum.fov / 2.0f) * frustum.fard;
	float far_width = far_height * frustum.ratio;

	frustum.point[0] = nc - up * near_height - right * near_width;
	frustum.point[1] = nc + up * near_height - right * near_width;
	frustum.point[2] = nc + up * near_height + right * near_width;
	frustum.point[3] = nc - up * near_height + right * near_width;

	frustum.point[4] = fc - up * far_height - right * far_width;
	frustum.point[5] = fc + up * far_height - right * far_width;
	frustum.point[6] = fc + up * far_height + right * far_width;
	frustum.point[7] = fc - up * far_height + right * far_width;

	D3DXVECTOR3 vCenter(0, 0, 0);
	for (uint32 i = 0; i < 8; i++)
		vCenter += frustum.point[i];
	vCenter /= 8;

	frustum.center = vCenter;
}

void CCascadedShadows::Render()
{
	// Update Textures
	{
		if (iShadowMapSize != iShadowMapSizeOld)
		{
			shadowRT.Release();
			SAFE_RELEASE(pShadowDepth);

			iShadowMapSizeOld = iShadowMapSize;
			vShadowBufferSize = D3DXVECTOR4(iShadowMapSize * NUM_CASCADES, iShadowMapSize, 1.0f / (iShadowMapSize * NUM_CASCADES), 1.0f / iShadowMapSize);
		}

		if (shadowRT.IsEmpty())
			if (!shadowRT.Create(m_pDevice, vShadowBufferSize.x, vShadowBufferSize.y, 1, ETextureUsage::RenderTarget, ETextureFormat::RFloat))
				Message("Failed to create shadowRT");

		if (pShadowDepth == nullptr)
			if (FAILED(m_pDevice->CreateDepthStencilSurface(vShadowBufferSize.x, vShadowBufferSize.y, D3DFMT_D16, D3DMULTISAMPLE_NONE, 0, TRUE, &pShadowDepth, nullptr)))
				Message("Failed to create pShadowDepth");
	}

	// Update Splits Distances
	{
		const float nearZ = max(100.0f, g_fCameraNearZ);
		const float farZ = min(fFarZ, g_fCameraFarZ);

		UpdateSplitDist(pFrustums, nearZ, farZ);

		for (uint32 i = 0; i < NUM_CASCADES; i++)
		{
			D3DXVECTOR4 bound;
			D3DXVec4Transform(&bound, &D3DXVECTOR4(0, 0, pFrustums[i].fard, 1), &g_mProj);
			splitDepths[i] = bound.z;
		}
	}

	// Render Cascades
	{
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

		const D3DXVECTOR3 view_dir = D3DXVECTOR3(g_mView._13, g_mView._23, g_mView._33);
		const float camFoV = D3DXToRadian(fFoV);
		const float aspectRatio = g_vBufferSize.x * g_vBufferSize.w;

		for (uint32 i = 0; i < NUM_CASCADES; i++)
		{
			pFrustums[i].fov = camFoV;
			pFrustums[i].ratio = aspectRatio;

			UpdateFrustumPoints(pFrustums[i], g_vCameraPos, view_dir);

			RenderCascade(i);
		}

		m_pDevice->SetRenderTarget(0, pOldColorRT);
		m_pDevice->SetDepthStencilSurface(pOldDepthRT);

		SAFE_RELEASE(pOldColorRT);
		SAFE_RELEASE(pOldDepthRT);
	}

	// Debug Screen
	if (PostProcessing)
		PostProcessing->SetDebugScreen(EDebugScreen::CascadedShadows, &shadowRT, true, D3DXVECTOR2(1.0f, NUM_CASCADES * g_vBufferSize.y * g_vBufferSize.z));
}
