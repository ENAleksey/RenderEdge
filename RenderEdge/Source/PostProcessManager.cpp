#include "PostProcessManager.h"
#include "Utils.h"
#include "Engine.h"

PostProcessManager* PP_Manager;

PostProcessManager::PostProcessManager(IDirect3DDevice9* pd3dDevice)
{
	m_pDevice = pd3dDevice;
	InitTempRes();
	InitPermRes();
}

PostProcessManager::~PostProcessManager()
{
	ReleaseTempRes();
	ReleasePermRes();
}


HRESULT PostProcessManager::InitTempRes()
{
	HRESULT hr;

	ID3DXBuffer* errorBuffer = 0;
	hr = D3DXCreateEffectFromFileA(m_pDevice, "Shaders/War3HDR.fx", 0, 0, D3DXSHADER_DEBUG, 0, &m_pEffect, &errorBuffer);
	if (FAILED(hr))
	{
		Message((char*)errorBuffer->GetBufferPointer(), "Failed to create War3HDR.fx");
		errorBuffer->Release();
	}

	hr = m_pDevice->CreateTexture(g_wndWidth, g_wndHeight, 1, D3DUSAGE_RENDERTARGET, D3DFMT_A16B16G16R16F, D3DPOOL_DEFAULT, &m_pHDRTexture, NULL);
	if (FAILED(hr))
	{
		MessageBoxA(NULL, "Failed to create m_pHDRTexture!", "Error", MB_OK);
		return hr;
	}
	m_pHDRTexture->GetSurfaceLevel(0, &m_pHDRSurface);

	
	return D3D_OK;
}

HRESULT PostProcessManager::InitPermRes()
{
	
	return D3D_OK;
}

HRESULT PostProcessManager::ReleaseTempRes()
{
	SAFE_RELEASE(m_pBackBuffer);
	SAFE_RELEASE(m_pHDRTexture);
	SAFE_RELEASE(m_pHDRSurface);

	return D3D_OK;
}

HRESULT PostProcessManager::ReleasePermRes()
{

	return D3D_OK;
}

	
void PostProcessManager::Render()
{
	/*
	if (g_bUseEffect)
	{
		m_pEffect->SetInt("g_iTonemapTech", g_iTonemapTech);
		m_pEffect->SetFloat("MIDDLE_GRAY", g_fKeyValue);
		m_pEffect->SetFloat("LUM_WHITE", g_fLumWhite);
		m_pEffect->SetFloat("BRIGHT_THRESHOLD", g_fBrightThreshold);
		m_pEffect->SetFloat("BRIGHT_PASS_OFFSET", g_fBrightOffset);

		m_pEffect->SetBool("g_bEnableBloom", g_bEnableBloom);
		m_pEffect->SetBool("g_bEnableBlueShift", g_bEnableBlueShift);
		m_pEffect->SetBool("g_bEnableCA", g_bEnableCA);
		m_pEffect->SetBool("g_bEnableVignetting", g_bEnableVignetting);
		m_pEffect->SetBool("g_bEnableColorCorrection", g_bEnableColorCorrection);

		m_pEffect->SetFloat("g_fCAStrength", g_fCAStrength);
		m_pEffect->SetFloat("g_fCCContrastScale", g_fCCContrastScale);
		m_pEffect->SetFloat("g_fCCContrastBias", g_fCCContrastBias);
		m_pEffect->SetFloat("g_fCCSaturation", g_fCCSaturation);
		m_pEffect->SetFloat("g_fBloomStrength", g_fBloomStrength);

		m_pEffect->SetFloat("g_fEyeAdaptationSpeedUp", g_fEyeAdaptationSpeedUp);
		m_pEffect->SetFloat("g_fEyeAdaptationSpeedDown", g_fEyeAdaptationSpeedDown);
		m_pEffect->SetFloat("g_fMinBrightness", g_fMinBrightness);
		m_pEffect->SetFloat("g_fMaxBrightness", g_fMaxBrightness);

		//---------------------------------------------------------------------

		m_pDevice->GetRenderTarget(0, &m_pBackBuffer);
		m_pDevice->StretchRect(m_pBackBuffer, NULL, m_pHDRSurface, NULL, D3DTEXF_NONE);

		//---------------------------------------------------------------------

		MeasureLuminance(m_pDevice);
		CalculateAdaptation(m_pDevice);
		BrightPassFilter(m_pDevice);
		RenderBloom(m_pDevice);

		//---------------------------------------------------------------------

		m_pDevice->SetRenderTarget(0, m_pBackBuffer);
		m_pDevice->StretchRect(m_pHDRSurface, 0, m_pBackBuffer, 0, D3DTEXF_NONE);

		m_pDevice->SetTexture(0, m_pHDRTexture);
		m_pDevice->SetTexture(1, m_pTexAdaptedLuminanceCur);
		m_pDevice->SetTexture(2, m_apTexBloom[0]);

		m_pDevice->SetSamplerState(2, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
		m_pDevice->SetSamplerState(2, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);

		m_pEffect->SetTechnique("TechFinalPass");

		UINT uiPass, uiNumPasses;

		m_pEffect->Begin(&uiNumPasses, 0);
		for (uiPass = 0; uiPass < uiNumPasses; uiPass++)
		{
			m_pEffect->BeginPass(uiPass);
			DrawFullScreenQuad(m_pDevice);
			m_pEffect->EndPass();
		}
		m_pEffect->End();

		//---------------------------------------------------------------------

		//m_pDevice->SetTexture(texStage, currentTexture);
	}
	*/
}

void PostProcessManager::OnLostDevice()
{
	ReleaseTempRes();
}

void PostProcessManager::OnResetDevice()
{
	InitTempRes();
}