#include "PostProcessing.h"

#include "Engine.h"
#include "ResourceManager.h"
#include "Log.h"


CPostProcessing* PostProcessing = nullptr;

CPostProcessing::CPostProcessing(IDirect3DDevice9* pDevice)
{
	m_pDevice = pDevice;

	InitTemporaryResources();

	if (ResourceManager)
		ResourceManager->LoadShader("Shaders\\PostProcess.cso", nullptr, &m_pEffect);


	// Debug View
	bDebugView = false;
	iDebugScreen = EDebugScreen::SceneDepth;


	// SMAA
	bSMAA = false;
	iSMAAInput = SMAA::INPUT_COLOR;
	fSMAAThreshold = 0.1f;
	iSMAASearchSteps = 16;
	iSMADiagSearchSteps = 8;
	fSMAACornerRounding = 25.0f;


	// Temporal AA
	bTemporalAA = false;
	bUseVelocity = false;
	fJitterSpreadTAA = 0.75f;
	fSharpnessTAA = 0.25f;
	fStationaryBlendingTAA = 0.95f;
	fMotionBlendingTAA = 0.85f;
	jitter = D3DXVECTOR2(0.0f, 0.0f);
	iTemporalAASampleIndex = 0;
	iHistoryPingPong = 0;


	// Bloom
	bBloom = false;
	fBloomThreshold = 1.0f;
	fBloomIntensity = 0.5f;
	iBloomPasses = 7;
	fBloomAnamorphicRatio = 0.0f;
	//fBloomSoftKnee = 0.5f;

	BloomSizeScale = 4.0;
	Bloom1Tint = D3DXVECTOR3(0.3465f, 0.3465f, 0.3465f);
	Bloom1Size = 0.3f;
	Bloom2Tint = D3DXVECTOR3(0.138f, 0.138f, 0.138f);
	Bloom2Size = 1.0f;
	Bloom3Tint = D3DXVECTOR3(0.1176f, 0.1176f, 0.1176f);
	Bloom3Size = 2.0f;
	Bloom4Tint = D3DXVECTOR3(0.066f, 0.066f, 0.066f);
	Bloom4Size = 10.0f;
	Bloom5Tint = D3DXVECTOR3(0.066f, 0.066f, 0.066f);
	Bloom5Size = 30.0f;
	Bloom6Tint = D3DXVECTOR3(0.061f, 0.061f, 0.061f);
	Bloom6Size = 64.0f;

	bLensDirt = false;
	fLensDirtIntensity = 2.0f;
	lensDirtTextureFileName = "Textures\\LensDirt.png";


	// Auto Exposure
	bAutoExposure = false;
	fAutoExposureSpeedUp = 2.0f;
	fAutoExposureSpeedDown = 1.0f;
	fAutoExposureMinBrightness = 0.03f;
	fAutoExposureMaxBrightness = 2.0f;
	fAutoExposureHistogramLogMin = -8.0f;
	fAutoExposureHistogramLogMax = 4.0f;
	fAutoExposureBias = 0.0f;
	fAutoExposureCalibrationConstant = 16.0f;
	iExposurePingPong = 0;


	// Color Correction
	bUpdateLUT = true;

	fWhiteTemp = 6500.0f;
	fWhiteTint = 0.0f;

	vColorSaturation = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	vColorContrast = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	vColorGamma = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	vColorGain = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	vColorOffset = D3DXVECTOR4(0.0f, 0.0f, 0.0f, 0.0f);

	vColorSaturationShadows = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	vColorContrastShadows = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	vColorGammaShadows = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	vColorGainShadows = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	vColorOffsetShadows = D3DXVECTOR4(0.0f, 0.0f, 0.0f, 0.0f);

	vColorSaturationMidtones = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	vColorContrastMidtones = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	vColorGammaMidtones = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	vColorGainMidtones = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	vColorOffsetMidtones = D3DXVECTOR4(0.0f, 0.0f, 0.0f, 0.0f);

	vColorSaturationHighlights = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	vColorContrastHighlights = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	vColorGammaHighlights = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	vColorGainHighlights = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	vColorOffsetHighlights = D3DXVECTOR4(0.0f, 0.0f, 0.0f, 0.0f);

	fColorCorrectionShadowsMax = 0.09f;
	fColorCorrectionHighlightsMin = 0.5f;

	fBlueCorrection = 0.6f;
	fExpandGamut = 1.0f;

	bUserLUT = false;
	fUserLutIntensity = 1.0f;
	userLutTextureFileName = "Textures\\lut.png";

	iColorGamut = 0;
	iOutputDevice = 0;
	fGamma = 2.2f;


	// Tonemapper
	fFilmSlope = 0.88f;
	fFilmToe = 0.55f;
	fFilmShoulder = 0.26f;
	fFilmBlackClip = 0.0f;
	fFilmWhiteClip = 0.04f;


	// Ambient Occlusion
	bSSAO = false;
	fSSAOIntensity = 1.0f;
	fSSAORadius = 1.0f;
	fSSAOContrast = 0.6f;
	fSSAOGeometryCoeff = 0.8f;
	fSSAOBeta = 0.002f;
	bSSAODownsample = true;
	bSSAODownsampleOld = bSSAODownsample;


	// Reflections
	bSSR = false;
	bSSRDownsample = true;
	bSSRDownsampleOld = bSSRDownsample;
	fSSRMinRayStep = 0.1f;//0.01f;
	fSSRRayStep = 0.3f;//1.8318f;
	fSSRJitter = 0.0f;
	fSSRRayhitThreshold = 0.2f;
	fSSRDepthThreshold = 3.0f;


	// Contact Shadows
	bContactShadows = false;
	bContactShadowsDownsample = true;
	bContactShadowsDownsampleOld = bContactShadowsDownsample;
	fContactShadowsRayLength = 0.1f;


	// ChromaticAberration
	bChromaticAberration = false;
	fChromaticAberrationIntensity = 0.05f;


	// Vignette
	bVignette = false;
	vVignetteColor = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	bVignetteRounded = false;
	fVignetteSmoothness = 0.2f;
	fVignetteIntensity = 0.15f;
	fVignetteRoundness = 1.0f;


	// Film Grain
	bFilmGrain = false;
	fFilmGrainIntensity = 0.5f;
	fFilmGrainVariance = 0.4f;
	iFilmGrainSignalToNoiseRatio = 6;


	// Dithering
	bDithering = true;
	iDitheringTextureIndex = 0;
}

CPostProcessing::~CPostProcessing()
{
	SAFE_RELEASE(m_pEffect);
	SAFE_DELETE(Smaa);

	ReleaseTemporaryResources();
}


void CPostProcessing::OnResetDevice()
{
	if (m_pEffect)
		m_pEffect->OnResetDevice();

	if (Smaa)
		Smaa->OnResetDevice();

	InitTemporaryResources();

	bUpdateLUT = true;
}

void CPostProcessing::OnLostDevice()
{
	if (m_pEffect)
		m_pEffect->OnLostDevice();

	if (Smaa)
		Smaa->OnLostDevice();

	ReleaseTemporaryResources();
}

void CPostProcessing::InitTemporaryResources()
{

}

void CPostProcessing::ReleaseTemporaryResources()
{
	velocityRT.Release();
	colorGradingLutRT.Release();
	adaptedExposureRTs[0].Release();
	adaptedExposureRTs[1].Release();
	ssaoRT.Release();
	ssrRT.Release();
	contactShadowsRT.Release();
	taaRTs[0].Release();
	taaRTs[1].Release();

	spectralLutTexture.Release();
	userLutTexture.Release();
	lensDirtTexture.Release();
	for (uint32 i = 0; i < 64; i++)
		noiseTextures[i].Release();
}

void CPostProcessing::ReloadShaders()
{
	if (ResourceManager)
	{
		SAFE_RELEASE(m_pEffect);
		ResourceManager->LoadShader("Shaders\\PostProcess.cso", nullptr, &m_pEffect);
	}
}


void CPostProcessing::DrawFullScreenTriangle(float x, float y, float width, float height)
{
	RECT rect = { x, y, x + width, y + height };

	width = 2.0f * width - 0.5f;
	height = 2.0f * height - 0.5f;

	float vertices[3][6] =
	{
		{ x - 0.5f, y - 0.5f, 0.5f, 1.0f, 0.0f, 0.0f },
		{ x - 0.5f, y + height, 0.5f, 1.0f, 0.0f, 2.0f },
		{ x + width, y - 0.5f, 0.5f, 1.0f, 2.0f, 0.0f }
	};

	DWORD scissor;
	m_pDevice->GetRenderState(D3DRS_SCISSORTESTENABLE, &scissor);
	m_pDevice->SetRenderState(D3DRS_SCISSORTESTENABLE, 1);
	m_pDevice->SetScissorRect(&rect);
	m_pDevice->SetFVF(D3DFVF_XYZRHW | D3DFVF_TEX1);
	m_pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 1, vertices, sizeof(vertices[0]));
	m_pDevice->SetRenderState(D3DRS_SCISSORTESTENABLE, scissor);
}

void CPostProcessing::DrawFullScreenTriangle()
{
	D3DSURFACE_DESC descRT;
	PDIRECT3DSURFACE9 pSurfRT;
	m_pDevice->GetRenderTarget(0, &pSurfRT);
	pSurfRT->GetDesc(&descRT);
	pSurfRT->Release();

	DrawFullScreenTriangle(0.0f, 0.0f, descRT.Width, descRT.Height);
}

void CPostProcessing::ApplyEffect(const std::string& technique, uint32 pass, bool clear)
{
	if (clear)
		m_pDevice->Clear(0, nullptr, D3DCLEAR_TARGET, 0x00000000, 1.0f, 0);

	m_pEffect->SetTechnique(technique.c_str());
	uint32 iPassCount;
	m_pEffect->Begin(&iPassCount, 0);
	if (pass >= 0 && pass < iPassCount)
	{
		m_pEffect->BeginPass(pass);
		DrawFullScreenTriangle();
		m_pEffect->EndPass();
	}
	m_pEffect->End();
}

void CPostProcessing::ApplyEffect(TextureRenderTarget2D* destRT, const std::string& technique, uint32 pass, bool clear)
{
	m_pDevice->SetRenderTarget(0, destRT->GetSurface());
	ApplyEffect(technique, pass, clear);
	destRT->ReleaseSurface();
}

void CPostProcessing::ApplyEffect(IDirect3DSurface9* destRT, const std::string& technique, uint32 pass, bool clear)
{
	m_pDevice->SetRenderTarget(0, destRT);
	ApplyEffect(technique, pass, clear);
}

void CPostProcessing::SetDebugScreen(EDebugScreen debugScreen, TextureRenderTarget2D* pRT, bool bOneChannel, const D3DXVECTOR2& tiling)
{
	if (bDebugView && iDebugScreen == debugScreen)
	{
		m_pEffect->SetValue("g_vDebugScreenTiling", &tiling, sizeof(D3DXVECTOR2));
		m_pEffect->SetTexture("g_debugTexture", pRT->GetTexture());
		m_pEffect->SetBool("g_bDebugScreenOneChannel", bOneChannel);
	}
}




void GetSampleOffsets_DownScale3x3(uint32 dwWidth, uint32 dwHeight, D3DXVECTOR2* avSampleOffsets)
{
	if (nullptr == avSampleOffsets)
		return;

	float tU = 1.0f / dwWidth;
	float tV = 1.0f / dwHeight;

	// Sample from the 9 surrounding points. 
	uint32 index = 0;
	for (int y = -1; y <= 1; y++)
	{
		for (int x = -1; x <= 1; x++)
		{
			avSampleOffsets[index].x = x * tU;
			avSampleOffsets[index].y = y * tV;

			index++;
		}
	}
}

void GetSampleOffsets_DownScale2x2_Lum(uint32 dwSrcWidth, uint32 dwSrcHeight, uint32 dwDestWidth, uint32 dwDestHeight, D3DXVECTOR2* avSampleOffsets)
{
	if (nullptr == avSampleOffsets)
		return;

	float tU = 1.0f / dwSrcWidth;
	float tV = 1.0f / dwSrcHeight;

	float deltaU = (float)dwSrcWidth / dwDestWidth / 2.0f;
	float deltaV = (float)dwSrcHeight / dwDestHeight / 2.0f;

	// Sample from 4 surrounding points. 
	uint32 index = 0;
	for (uint32 y = 0; y < 2; y++)
	{
		for (uint32 x = 0; x <= 2; x++)
		{
			avSampleOffsets[index].x = (x - 0.5f) * deltaU * tU;
			avSampleOffsets[index].y = (y - 0.5f) * deltaV * tV;

			index++;
		}
	}
}



void CPostProcessing::ComputeEyeAdaptationValues()
{
	float LocalExposureMultipler = pow(2.0f, fAutoExposureBias);

	const float CalibrationConstant = math::Clamp(fAutoExposureCalibrationConstant, 1.0f, 100.f) * 0.01f;
	float AverageLuminanceScale = 1.0f / CalibrationConstant;

	float HistogramLogMin = fAutoExposureHistogramLogMin;
	float HistogramLogMax = fAutoExposureHistogramLogMax;
	HistogramLogMin = min(HistogramLogMin, HistogramLogMax - 1);

	float MinAverageLuminance = fAutoExposureMinBrightness;
	float MaxAverageLuminance = fAutoExposureMaxBrightness;
	MinAverageLuminance = min(MinAverageLuminance, MaxAverageLuminance);

	float DeltaLog = HistogramLogMax - HistogramLogMin;
	float Multiply = 1.0f / DeltaLog;
	float Add = -HistogramLogMin * Multiply;
	float MinIntensity = exp2(HistogramLogMin);

	m_pEffect->SetFloat("g_fMinBrightness", MinAverageLuminance);
	m_pEffect->SetFloat("g_fMaxBrightness", MaxAverageLuminance);

	m_pEffect->SetFloat("g_fExposureOffset", LocalExposureMultipler);
	m_pEffect->SetFloat("g_fDeltaTime", g_fDeltaTime);
	m_pEffect->SetFloat("g_fEyeAdaptationSpeedUp", fAutoExposureSpeedUp);
	m_pEffect->SetFloat("g_fEyeAdaptationSpeedDown", fAutoExposureSpeedDown);

	m_pEffect->SetFloat("g_fHistogramMultiply", Multiply);
	m_pEffect->SetFloat("g_fHistogramAdd", Add);
	m_pEffect->SetFloat("g_fHistogramMinIntensity", MinIntensity);
	m_pEffect->SetFloat("g_fAverageLuminanceScale", AverageLuminanceScale);
}

void CPostProcessing::CalculateAutoExposure(TextureRenderTarget2D* sourceRT)
{
	ComputeEyeAdaptationValues();

	enum EPass
	{
		LogLumAverage,
		DownScale,
		CalculateAdaptedExposure
	};

	const uint32 kNumStages = 5;
	TextureRenderTarget2D lumAverageRTs[kNumStages];

	uint32 size = 1;
	for (uint32 i = 0; i < kNumStages; i++)
	{
		lumAverageRTs[i].Create(m_pDevice, size, size, 1, ETextureUsage::RenderTarget, ETextureFormat::RHalf);
		size *= 3;
	}

	// Average Lumiance
	{
		const uint32 sourceWidth = sourceRT->GetWidth();
		const uint32 sourceHeight = sourceRT->GetHeight();
		const uint32 destWidth = lumAverageRTs[kNumStages - 1].GetWidth();
		const uint32 destHeight = lumAverageRTs[kNumStages - 1].GetHeight();

		D3DXVECTOR2 offsets[16];
		GetSampleOffsets_DownScale2x2_Lum(sourceWidth, sourceHeight, destWidth, destHeight, offsets);

		m_pEffect->SetTexture("g_mainTexture", sourceRT->GetTexture());
		m_pEffect->SetValue("g_avSampleOffsets", &offsets, sizeof(offsets));
		ApplyEffect(&lumAverageRTs[kNumStages - 1], "AutoExposure", EPass::LogLumAverage);
	}

	// Downsample
	for (uint32 i = kNumStages - 1; i > 0; i--)
	{
		const uint32 sourceWidth = lumAverageRTs[i].GetWidth();
		const uint32 sourceHeight = lumAverageRTs[i].GetHeight();

		D3DXVECTOR2 offsets[16];
		GetSampleOffsets_DownScale3x3(sourceWidth, sourceHeight, offsets);

		m_pEffect->SetTexture("g_mainTexture", lumAverageRTs[i].GetTexture());
		m_pEffect->SetValue("g_avSampleOffsets", &offsets, sizeof(offsets));
		ApplyEffect(&lumAverageRTs[i - 1], "AutoExposure", EPass::DownScale);
	}

	// Adaptation
	{
		if (adaptedExposureRTs[0].IsEmpty())
			adaptedExposureRTs[0].Create(m_pDevice, 1, 1, 1, ETextureUsage::RenderTarget, ETextureFormat::RHalf);
		if (adaptedExposureRTs[1].IsEmpty())
			adaptedExposureRTs[1].Create(m_pDevice, 1, 1, 1, ETextureUsage::RenderTarget, ETextureFormat::RHalf);

		uint32 pp = iExposurePingPong;
		TextureRenderTarget2D* pLast = &adaptedExposureRTs[++pp % 2];
		TextureRenderTarget2D* pCur = &adaptedExposureRTs[++pp % 2];
		iExposurePingPong = ++pp % 2;

		m_pEffect->SetTexture("g_eyeAdaptationTexture", pLast->GetTexture());
		m_pEffect->SetTexture("g_curExposureTexture", lumAverageRTs[0].GetTexture());
		ApplyEffect(pCur, "AutoExposure", EPass::CalculateAdaptedExposure);
	}

	// Cleanup
	for (uint32 i = 0; i < kNumStages; i++)
		lumAverageRTs[i].Release();
}

void CPostProcessing::RenderSMAA(TextureRenderTarget2D* sourceRT, TextureRenderTarget2D* destRT)
{
	if (Smaa == nullptr)
		Smaa = new SMAA(m_pDevice);

	Smaa->setThreshold(fSMAAThreshold);
	Smaa->setMaxSearchSteps(iSMAASearchSteps);
	Smaa->setMaxSearchStepsDiag(iSMADiagSearchSteps);
	Smaa->setCornerRounding(fSMAACornerRounding);

	switch (iSMAAInput)
	{
	case SMAA::INPUT_LUMA:
	case SMAA::INPUT_COLOR:
		Smaa->go(sourceRT, sourceRT, destRT->GetSurface(), iSMAAInput);
		break;
	case SMAA::INPUT_DEPTH:
		Smaa->go(&g_depthRT, sourceRT, destRT->GetSurface(), iSMAAInput);
		break;
	}

	destRT->ReleaseSurface();
}

void CPostProcessing::VelocityPass()
{
	//if (velocityRT == nullptr)
	//	m_pDevice->CreateTexture(g_vBufferSize.x, g_vBufferSize.y, 1, D3DUSAGE_RENDERTARGET, D3DFMT_G16R16F, D3DPOOL_DEFAULT, &velocityRT, nullptr);

	//m_pEffect->SetMatrix("g_mViewProjectionInverse", &g_mViewProjectionInverse);
	//m_pEffect->SetMatrix("g_mViewProjectionInversePrev", &g_mViewProjectionInversePrev);
	//g_mViewProjectionInversePrev = g_mViewProjectionInverse;

	//m_pEffect->SetMatrix("g_mProjection", &g_mProj);
	//m_pEffect->SetMatrix("g_mProjectionPrev", &g_mProjPrev);
	//g_mProjPrev = g_mProj;

	//ApplyEffect(velocityRT, "Velocity");
}



float Halton(int32 Index, int32 Base)
{
	float Result = 0.0f;
	float InvBase = 1.0f / Base;
	float Fraction = InvBase;
	while (Index > 0)
	{
		Result += (Index % Base) * Fraction;
		Index /= Base;
		Fraction *= InvBase;
	}
	return Result;
}

const D3DXVECTOR2& CPostProcessing::GenerateRandomOffset()
{
	D3DXVECTOR2 offset = D3DXVECTOR2(
		Halton((iTemporalAASampleIndex & 1023) + 1, 2) - 0.5f,
		Halton((iTemporalAASampleIndex & 1023) + 1, 3) - 0.5f
	);
	return offset;
}

const D3DXVECTOR2& CPostProcessing::GenerateRandomOffset2()
{
	float u1 = Halton(iTemporalAASampleIndex + 1, 2);
	float u2 = Halton(iTemporalAASampleIndex + 1, 3);

	// Generates samples in normal distribution
	// exp( x^2 / Sigma^2 )

	float FilterSize = 1.0f;

	// Scale distribution to set non-unit variance
	// Variance = Sigma^2
	float Sigma = 0.47f * FilterSize;

	// Window to [-0.5, 0.5] output
	// Without windowing we could generate samples far away on the infinite tails.
	float OutWindow = 0.5f;
	float InWindow = exp(-0.5 * math::Square(OutWindow / Sigma));

	// Box-Muller transform
	float Theta = 2.0f * D3DX_PI * u2;
	float r = Sigma * sqrt(-2.0f * log((1.0f - u1) * InWindow + u1));

	float SampleX = r * cos(Theta);
	float SampleY = r * sin(Theta);

	const int sampleCount = 8;
	if (++iTemporalAASampleIndex >= sampleCount)
		iTemporalAASampleIndex = 0;

	return D3DXVECTOR2(SampleX, SampleY);
}

void CPostProcessing::SetJitteredProjectionMatrix()
{
	jitter = GenerateRandomOffset();

	D3DXMATRIX mProjJittered = g_mProjNonJittered;

	//projectionMatrix.m[2][0] += (jitter.x * 2.0f) * g_vViewportSize.z;
	//projectionMatrix.m[2][1] += (jitter.y * -2.0f) * g_vViewportSize.w;

	mProjJittered.m[3][0] += jitter.x * fJitterSpreadTAA;
	mProjJittered.m[3][1] += jitter.y * fJitterSpreadTAA;

	jitter = D3DXVECTOR2(jitter.x * g_vViewportSize.z, jitter.y * g_vViewportSize.w);

	g_mProj = mProjJittered;
	//m_pDevice->SetTransform(D3DTS_PROJECTION, &mProjJittered);
}

void CPostProcessing::ResetProjectionMatrix()
{
	g_mProj = g_mProjNonJittered;
	//m_pDevice->SetTransform(D3DTS_PROJECTION, &g_mProj);
}

TextureRenderTarget2D* CPostProcessing::CheckHistory(TextureRenderTarget2D* sourceRT, int id)
{
	if (taaRTs[id].IsEmpty())
	{
		taaRTs[id].Create(m_pDevice, g_vBufferSize.x, g_vBufferSize.y, 1, ETextureUsage::RenderTarget, g_mainRT.GetFormat());

		m_pEffect->SetTexture("g_mainTexture", sourceRT->GetTexture());
		ApplyEffect(&taaRTs[id], "TemporalAA", 0);
	}

	return &taaRTs[id];
}

void CPostProcessing::RenderTAA(TextureRenderTarget2D* sourceRT, TextureRenderTarget2D* destRT)
{
	uint32 pp = iHistoryPingPong;
	TextureRenderTarget2D* historyRead = CheckHistory(sourceRT, ++pp % 2);
	TextureRenderTarget2D* historyWrite = CheckHistory(sourceRT, ++pp % 2);
	iHistoryPingPong = ++pp % 2;

	const float kMotionAmplification = 100.0f * 60.0f;
	m_pEffect->SetValue("g_vJitter", jitter, sizeof(D3DXVECTOR2));
	m_pEffect->SetFloat("g_fSharpness", fSharpnessTAA);
	m_pEffect->SetValue("g_vBlendParameters", D3DXVECTOR3(fStationaryBlendingTAA, fMotionBlendingTAA, kMotionAmplification), sizeof(D3DXVECTOR3));
	m_pEffect->SetTexture("g_mainTexture", sourceRT->GetTexture());
	m_pEffect->SetTexture("g_historyTexture", historyRead->GetTexture());
	m_pEffect->SetTexture("g_velocityTexture", velocityRT.GetTexture());

	m_pDevice->SetRenderTarget(1, historyWrite->GetSurface());
	ApplyEffect(destRT, "TemporalAA");
	historyWrite->ReleaseSurface();

	ResetProjectionMatrix();
	m_pDevice->SetRenderTarget(1, nullptr);
}



void CPostProcessing::Dithering()
{
	if (ResourceManager && noiseTextures->IsEmpty())
		for (uint32 i = 0; i < 64; i++)
			ResourceManager->LoadTexture2D("Textures\\Bluenoise64\\LDR_LLL1_" + std::to_string(i) + ".png", &noiseTextures[i]);

	if (++iDitheringTextureIndex >= 64)
		iDitheringTextureIndex = 0;

	float rndOffsetX = static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
	float rndOffsetY = static_cast<float>(rand()) / static_cast<float>(RAND_MAX);

	const D3DXVECTOR4 vDitheringCoords = D3DXVECTOR4(g_vBufferSize.x / 64.0f, g_vBufferSize.y / 64.0f, rndOffsetX, rndOffsetY);

	m_pEffect->SetTexture("g_ditheringTexture", noiseTextures[iDitheringTextureIndex].GetTexture());
	m_pEffect->SetValue("g_vDitheringCoords", &vDitheringCoords, sizeof(D3DXVECTOR4));
}

void CPostProcessing::RenderSSAO()
{
	const enum EPass
	{
		Occlusion,
		HorizontalBlur,
		VerticalBlur,
		Composition
	};

	float ts = bSSAODownsample ? 0.5f : 1.0f;
	int scaledWidth = g_vBufferSize.x * ts;
	int scaledHeight = g_vBufferSize.y * ts;

	TextureRenderTarget2D maskRT(m_pDevice, scaledWidth, scaledHeight, 1, ETextureUsage::RenderTarget, ETextureFormat::ARGB32);
	TextureRenderTarget2D horizontalBlurRT(m_pDevice, scaledWidth, scaledHeight, 1, ETextureUsage::RenderTarget, ETextureFormat::ARGB32);
	TextureRenderTarget2D verticalBlurRT(m_pDevice, scaledWidth, scaledHeight, 1, ETextureUsage::RenderTarget, ETextureFormat::ARGB32);

	if (bSSAODownsample != bSSAODownsampleOld)
	{
		ssaoRT.Release();
		bSSAODownsampleOld = bSSAODownsample;
	}

	if (ssaoRT.IsEmpty())
	{
		ssaoRT.Create(m_pDevice, scaledWidth, scaledHeight, 1, ETextureUsage::RenderTarget, ETextureFormat::R8);
	}

	// AO estimation
	m_pEffect->SetFloat("g_fSSAOIntensity", fSSAOIntensity);
	m_pEffect->SetFloat("g_fSSAORadius", fSSAORadius * 0.0001f);
	m_pEffect->SetFloat("g_fSSAOContrast", fSSAOContrast);
	m_pEffect->SetFloat("g_fSSAOGeometryCoeff", fSSAOGeometryCoeff);
	m_pEffect->SetFloat("g_fSSAOBeta", fSSAOBeta);
	m_pEffect->SetFloat("g_fSSAODownsample", ts);
	ApplyEffect(&maskRT, "SSAO", EPass::Occlusion);

	// Separable blur (horizontal pass)
	m_pEffect->SetTexture("g_mainTexture", maskRT.GetTexture());
	ApplyEffect(&horizontalBlurRT, "SSAO", EPass::HorizontalBlur);
	maskRT.Release();

	// Separable blur (vertical pass)
	m_pEffect->SetTexture("g_mainTexture", horizontalBlurRT.GetTexture());
	ApplyEffect(&verticalBlurRT, "SSAO", EPass::VerticalBlur);
	horizontalBlurRT.Release();

	// Composite
	m_pEffect->SetTexture("g_mainTexture", verticalBlurRT.GetTexture());
	ApplyEffect(&ssaoRT, "SSAO", EPass::Composition);
	verticalBlurRT.Release();

	// Debug Screen
	PostProcessing->SetDebugScreen(EDebugScreen::SSAO, &ssaoRT, true);
}

void CPostProcessing::RenderSSR(TextureRenderTarget2D* sourceRT)
{
	if (bSSRDownsample != bSSRDownsampleOld)
	{
		ssrRT.Release();
		bSSRDownsampleOld = bSSRDownsample;
	}

	if (ssrRT.IsEmpty())
	{
		float ts = bSSRDownsample ? 0.5f : 1.0f;
		ssrRT.Create(m_pDevice, g_vBufferSize.x * ts, g_vBufferSize.y * ts, 1, ETextureUsage::RenderTarget, g_mainRT.GetFormat());
	}

	const float fRRayhitThreshold = (fSSRRayhitThreshold >= 1.0f) ? FLT_MAX : fSSRRayhitThreshold * 0.001f;
	m_pEffect->SetFloat("g_fSSRRayhitThreshold", fRRayhitThreshold);
	m_pEffect->SetFloat("g_fSSRDepthThreshold", fSSRDepthThreshold * 0.01f);
	m_pEffect->SetFloat("g_fSSRJitter", fSSRJitter * 0.01f);
	m_pEffect->SetFloat("g_fSSRMinRayStep", fSSRMinRayStep);
	m_pEffect->SetFloat("g_fSSRRayStep", fSSRRayStep * 0.1f);
	m_pEffect->SetTexture("g_mainTexture", sourceRT->GetTexture());
	ApplyEffect(&ssrRT, "SSR");

	// Debug Screen
	PostProcessing->SetDebugScreen(EDebugScreen::SSR, &ssrRT);
}

void CPostProcessing::RenderContactShadows()
{
	float ts = bContactShadowsDownsample ? 0.5f : 1.0f;

	if (bContactShadowsDownsample != bContactShadowsDownsampleOld)
	{
		contactShadowsRT.Release();
		bContactShadowsDownsampleOld = bContactShadowsDownsample;
	}

	if (contactShadowsRT.IsEmpty())
	{
		contactShadowsRT.Create(m_pDevice, g_vBufferSize.x * ts, g_vBufferSize.y * ts, 1, ETextureUsage::RenderTarget, ETextureFormat::R8);
	}

	m_pEffect->SetValue("g_vLightDir", g_bDefaultLightDir ? &g_vGlobalLightDir : &g_vLightDir, sizeof(D3DXVECTOR3));
	m_pEffect->SetFloat("g_fContactShadowsRayLength", fContactShadowsRayLength);
	m_pEffect->SetFloat("g_fContactShadowsDownsample", ts);
	ApplyEffect(&contactShadowsRT, "ContactShadows");

	// Debug Screen
	PostProcessing->SetDebugScreen(EDebugScreen::ContactShadows, &contactShadowsRT, true);
}

void CPostProcessing::RenderBloom(TextureRenderTarget2D* sourceRT)
{
	/*struct FBloomStage
	{
	float BloomSize;
	const D3DXVECTOR3* Tint;
	};
	FBloomStage BloomStages[] =
	{
	{ Bloom1Size, &Bloom1Tint },
	{ Bloom2Size, &Bloom2Tint },
	{ Bloom3Size, &Bloom3Tint },
	{ Bloom4Size, &Bloom4Tint },
	{ Bloom5Size, &Bloom5Tint },
	{ Bloom6Size, &Bloom6Tint },
	};*/
	//float TintScale = 1.0f / iterations;

	enum EPass
	{
		BrightPass,
		Downsample,
		Upsample
	};

	// Prefiltering parameters
	m_pEffect->SetFloat("g_fBloomThreshold", fBloomThreshold);
	m_pEffect->SetTexture("g_curExposureTexture", adaptedExposureRTs[0].GetTexture());
	m_pEffect->SetBool("g_bAutoExposure", bAutoExposure);

	// Negative anamorphic ratio values distort vertically - positive is horizontal
	float ratio = math::Clamp(fBloomAnamorphicRatio, -1.0f, 1.0f);
	float rw = ratio < 0.0f ? -ratio : 0.0f;
	float rh = ratio > 0.0f ? ratio : 0.0f;
	uint32 tw = math::FloorToInt(g_vBufferSize.x / (2.0f - rw));
	uint32 th = math::FloorToInt(g_vBufferSize.y / (2.0f - rh));

	// Determine the iteration count
	//uint32 s = max(tw, th);
	//float logs = log2(s) + min(fBloomRadius, 10.0f) - 10.0f;
	//uint32 logs_i = math::FloorToInt(logs);
	const uint32 iterations = iBloomPasses;// math::Clamp(fBloomRadius, 2, 16);
	//float sampleScale = 0.5f + logs - logs_i;
	m_pEffect->SetFloat("g_fBloomScale", 1.0f);

	TextureRenderTarget2D* pLastRT = sourceRT;
	TextureRenderTarget2D* downsampleRTs = new TextureRenderTarget2D[iterations];
	TextureRenderTarget2D* upsampleRTs = new TextureRenderTarget2D[iterations];

	// Bright EPass and Downsample
	for (uint32 i = 0; i < iterations; i++)
	{
		downsampleRTs[i].Create(m_pDevice, tw, th, 1, ETextureUsage::RenderTarget, g_mainRT.GetFormat());
		upsampleRTs[i].Create(m_pDevice, tw, th, 1, ETextureUsage::RenderTarget, g_mainRT.GetFormat());

		m_pEffect->SetTexture("g_mainTexture", pLastRT->GetTexture());
		m_pEffect->SetValue("g_vMainTextureSize", D3DXVECTOR2(1.0f / pLastRT->GetWidth(), 1.0f / pLastRT->GetHeight()), sizeof(D3DXVECTOR2));
		ApplyEffect(&downsampleRTs[i], "Bloom", (i == 0) ? EPass::BrightPass : EPass::Downsample);

		pLastRT = &downsampleRTs[i];
		tw = max(tw * 0.5f, 1);
		th = max(th * 0.5f, 1);
	}

	// Upsample
	for (int32 i = iterations - 2; i >= 0; i--)
	{
		//FBloomStage& Op = BloomStages[6 - (i+1)];
		//const D3DXVECTOR3 tint = (*Op.Tint);// *TintScale;
		//m_pEffect->SetValue("g_vBloomColor", &tint, sizeof(D3DXVECTOR3));
		//m_pEffect->SetFloat("g_fBloomScale", 1.0 / (Op.BloomSize * g_fBloomRadius));

		m_pEffect->SetTexture("g_blurTexture", downsampleRTs[i].GetTexture());
		m_pEffect->SetTexture("g_mainTexture", pLastRT->GetTexture());
		m_pEffect->SetValue("g_vMainTextureSize", D3DXVECTOR2(1.0f / pLastRT->GetWidth(), 1.0f / pLastRT->GetHeight()), sizeof(D3DXVECTOR2));
		ApplyEffect(&upsampleRTs[i], "Bloom", EPass::Upsample);

		pLastRT = &upsampleRTs[i];
	}

	// Debug Screen
	PostProcessing->SetDebugScreen(EDebugScreen::BloomBrightPass, &downsampleRTs[0]);

	// Final EPass
	{
		//m_pEffect->SetFloat("g_fBloomScale", 1.0 / (BloomStages[0].BloomSize * g_fBloomRadius));
		//m_pEffect->SetValue("g_vBloomColor", &(*BloomStages[5].Tint), sizeof(D3DXVECTOR3));

		const float intensity = exp2(fBloomIntensity / 10.0f) - 1.0f;
		m_pEffect->SetFloat("g_fBloomIntensity", intensity);
		m_pEffect->SetTexture("g_bloomTexture", pLastRT->GetTexture());
		m_pEffect->SetValue("g_vMainTextureSize", D3DXVECTOR2(1.0f / pLastRT->GetWidth(), 1.0f / pLastRT->GetHeight()), sizeof(D3DXVECTOR2));
		m_pEffect->SetBool("g_bLensDirt", bLensDirt);

		if (bLensDirt)
		{
			if (ResourceManager && lensDirtTexture.IsEmpty())
				ResourceManager->LoadTexture2D(lensDirtTextureFileName, &lensDirtTexture);

			float dirtRatio = (float)lensDirtTexture.GetWidth() / (float)lensDirtTexture.GetHeight();
			float screenRatio = (float)g_vBufferSize.x / (float)g_vBufferSize.y;
			D3DXVECTOR4 dirtTileOffset = D3DXVECTOR4(1.0f, 1.0f, 0.0f, 0.0f);

			if (dirtRatio > screenRatio)
			{
				dirtTileOffset.x = screenRatio / dirtRatio;
				dirtTileOffset.z = (1.0f - dirtTileOffset.x) * 0.5f;
			}
			else if (screenRatio > dirtRatio)
			{
				dirtTileOffset.y = dirtRatio / screenRatio;
				dirtTileOffset.w = (1.0f - dirtTileOffset.y) * 0.5f;
			}

			m_pEffect->SetTexture("g_lensDirtTexture", lensDirtTexture.GetTexture());
			m_pEffect->SetFloat("g_fLensDirtIntensity", fLensDirtIntensity);
			m_pEffect->SetValue("g_vLensDirtTileOffset", &dirtTileOffset, sizeof(D3DXVECTOR4));
		}
	}

	// Cleanup
	for (uint32 i = 0; i < iterations; i++)
	{
		downsampleRTs[i].Release();
		upsampleRTs[i].Release();
	}

	SAFE_DELETE(downsampleRTs);
	SAFE_DELETE(upsampleRTs);
}

void CPostProcessing::RenderColorGradingLut()
{
	const uint32 lutSize = 32;
	if (colorGradingLutRT.IsEmpty())
		colorGradingLutRT.Create(m_pDevice, lutSize * lutSize, lutSize, 1, ETextureUsage::RenderTarget, ETextureFormat::ARGB2101010);

	m_pEffect->SetInt("g_iColorGamut", iColorGamut);
	m_pEffect->SetInt("g_iOutputDevice", iOutputDevice);
	m_pEffect->SetFloat("g_fInverseGamma", 1.0f / fGamma);

	m_pEffect->SetFloat("g_fBlueCorrection", fBlueCorrection);
	m_pEffect->SetFloat("g_fExpandGamut", fExpandGamut);

	m_pEffect->SetFloat("g_fFilmSlope", fFilmSlope);
	m_pEffect->SetFloat("g_fFilmToe", fFilmToe);
	m_pEffect->SetFloat("g_fFilmShoulder", fFilmShoulder);
	m_pEffect->SetFloat("g_fFilmBlackClip", fFilmBlackClip);
	m_pEffect->SetFloat("g_fFilmWhiteClip", fFilmWhiteClip);

	m_pEffect->SetFloat("g_fWhiteTemp", fWhiteTemp);
	m_pEffect->SetFloat("g_fWhiteTint", fWhiteTint);

	m_pEffect->SetValue("g_vColorSaturation", &vColorSaturation, sizeof(D3DXVECTOR4));
	m_pEffect->SetValue("g_vColorContrast", &vColorContrast, sizeof(D3DXVECTOR4));
	m_pEffect->SetValue("g_vColorGamma", &vColorGamma, sizeof(D3DXVECTOR4));
	m_pEffect->SetValue("g_vColorGain", &vColorGain, sizeof(D3DXVECTOR4));
	m_pEffect->SetValue("g_vColorOffset", &vColorOffset, sizeof(D3DXVECTOR4));

	m_pEffect->SetValue("g_vColorSaturationShadows", &vColorSaturationShadows, sizeof(D3DXVECTOR4));
	m_pEffect->SetValue("g_vColorContrastShadows", &vColorContrastShadows, sizeof(D3DXVECTOR4));
	m_pEffect->SetValue("g_vColorGammaShadows", &vColorGammaShadows, sizeof(D3DXVECTOR4));
	m_pEffect->SetValue("g_vColorGainShadows", &vColorGainShadows, sizeof(D3DXVECTOR4));
	m_pEffect->SetValue("g_vColorOffsetShadows", &vColorOffsetShadows, sizeof(D3DXVECTOR4));

	m_pEffect->SetValue("g_vColorSaturationMidtones", &vColorSaturationMidtones, sizeof(D3DXVECTOR4));
	m_pEffect->SetValue("g_vColorContrastMidtones", &vColorContrastMidtones, sizeof(D3DXVECTOR4));
	m_pEffect->SetValue("g_vColorGammaMidtones", &vColorGammaMidtones, sizeof(D3DXVECTOR4));
	m_pEffect->SetValue("g_vColorGainMidtones", &vColorGainMidtones, sizeof(D3DXVECTOR4));
	m_pEffect->SetValue("g_vColorOffsetMidtones", &vColorOffsetMidtones, sizeof(D3DXVECTOR4));

	m_pEffect->SetValue("g_vColorSaturationHighlights", &vColorSaturationHighlights, sizeof(D3DXVECTOR4));
	m_pEffect->SetValue("g_vColorContrastHighlights", &vColorContrastHighlights, sizeof(D3DXVECTOR4));
	m_pEffect->SetValue("g_vColorGammaHighlights", &vColorGammaHighlights, sizeof(D3DXVECTOR4));
	m_pEffect->SetValue("g_vColorGainHighlights", &vColorGainHighlights, sizeof(D3DXVECTOR4));
	m_pEffect->SetValue("g_vColorOffsetHighlights", &vColorOffsetHighlights, sizeof(D3DXVECTOR4));

	m_pEffect->SetFloat("g_fColorCorrectionShadowsMax", fColorCorrectionShadowsMax);
	m_pEffect->SetFloat("g_fColorCorrectionHighlightsMin", fColorCorrectionHighlightsMin);

	m_pEffect->SetBool("g_bUserLUT", bUserLUT);
	if (bUserLUT)
	{
		if (ResourceManager && userLutTexture.IsEmpty())
			ResourceManager->LoadTexture2D(userLutTextureFileName, &userLutTexture);

		m_pEffect->SetFloat("g_fUserLutIntensity", fUserLutIntensity);
		m_pEffect->SetTexture("g_userLutTexture", userLutTexture.GetTexture());
	}

	ApplyEffect(&colorGradingLutRT, "BuildHdrLut");

	m_pEffect->SetTexture("g_hdrLutTexture", colorGradingLutRT.GetTexture());
}

void CPostProcessing::FinalPass(TextureRenderTarget2D* sourceRT, IDirect3DSurface9* destRT)
{
	enum EPass
	{
		Main,
		Debug,
		DebugDepth
	};

	// Debug Screen
	if (bDebugView)
	{
		PostProcessing->SetDebugScreen(EDebugScreen::SceneColor, sourceRT);
		PostProcessing->SetDebugScreen(EDebugScreen::SceneDepth, &g_depthRT, true);

		ApplyEffect(destRT, "FinalPass", (iDebugScreen == EDebugScreen::SceneDepth) ? EPass::DebugDepth : EPass::Debug);

		m_pEffect->SetTexture("g_debugTexture", nullptr);

		return;
	}

	// Main Parameters
	m_pEffect->SetTexture("g_mainTexture", sourceRT->GetTexture());
	m_pEffect->SetTexture("g_curExposureTexture", adaptedExposureRTs[0].GetTexture());
	m_pEffect->SetBool("g_bAutoExposure", bAutoExposure);
	m_pEffect->SetBool("g_bBloom", bBloom);
	m_pEffect->SetBool("g_bVignette", bVignette);
	m_pEffect->SetBool("g_bChromaticAberration", bChromaticAberration);
	m_pEffect->SetBool("g_bFilmGrain", bFilmGrain);
	m_pEffect->SetBool("g_bDithering", bDithering);

	// Vignetting
	if (bVignette)
	{
		float roundness = (1.0f - fVignetteRoundness) * 6.0f + fVignetteRoundness;
		m_pEffect->SetBool("g_bVignetteRounded", bVignetteRounded);
		m_pEffect->SetValue("g_vVignetteColor", &vVignetteColor, sizeof(D3DXVECTOR3));
		m_pEffect->SetFloat("g_fVignetteIntensity", fVignetteIntensity * 3.0f);
		m_pEffect->SetFloat("g_fVignetteSmoothness", fVignetteSmoothness * 5.0f);
		m_pEffect->SetFloat("g_fVignetteRoundness", roundness);
	}

	// Chromatic Aberration
	if (bChromaticAberration)
	{
		if (ResourceManager && spectralLutTexture.IsEmpty())
			ResourceManager->LoadTexture2D("Textures\\SpectralLut_BlueRed.tga", &spectralLutTexture);

		m_pEffect->SetFloat("g_fChromaticAberrationIntensity", fChromaticAberrationIntensity * 0.05f);
		m_pEffect->SetTexture("g_spectralLutTexture", spectralLutTexture.GetTexture());
	}

	// Film Grain
	if (bFilmGrain)
	{
		m_pEffect->SetFloat("g_fFilmGrainIntensity", fFilmGrainIntensity);
		m_pEffect->SetFloat("g_fFilmGrainVariance", fFilmGrainVariance);
		m_pEffect->SetInt("g_iFilmGrainSignalToNoiseRatio", iFilmGrainSignalToNoiseRatio);
	}

	// Dithering
	if (bDithering)
		Dithering();

	ApplyEffect(destRT, "FinalPass", EPass::Main);
}



const D3DXMATRIX& GetInverseRotationMatrix(const D3DXVECTOR3& Rot)
{
	return D3DXMATRIX( // Yaw
		cos(Rot.x), -sin(Rot.x), 0.0f, 0.0f,
		sin(Rot.x), cos(Rot.x), 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f) *
		D3DXMATRIX( // Pitch
			cos(Rot.y), 0.0f, -sin(Rot.y), 0.0f,
			0.0f, 1.0f, 0.0f, 0.0f,
			sin(Rot.y), 0.0f, cos(Rot.y), 0.0f,
			0.0f, 0.0f, 0.0f, 1.0f) *
		D3DXMATRIX( // Roll
			1.0f, 0.0f, 0.0f, 0.0f,
			0.0f, cos(Rot.z), -sin(Rot.z), 0.0f,
			0.0f, sin(Rot.z), cos(Rot.z), 0.0f,
			0.0f, 0.0f, 0.0f, 1.0f);
}

const D3DXVECTOR2& CreateInvDeviceZToWorldZTransform(const D3DXMATRIX& ProjMatrix)
{
	float DepthMul = ProjMatrix.m[2][2];
	float DepthAdd = ProjMatrix.m[3][2];

	if (DepthAdd == 0.0f)
		DepthAdd = 0.00000001f;

	float SubtractValue = DepthMul / DepthAdd;
	SubtractValue -= 0.00000001f;

	return D3DXVECTOR2(1.0f / DepthAdd, SubtractValue);
}

void CPostProcessing::Render()
{
	m_pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
	m_pDevice->SetRenderState(D3DRS_ZENABLE, D3DZB_FALSE);
	m_pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);
	m_pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_ALWAYS);
	m_pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
	m_pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);

	// =============================================================

	D3DXMATRIX mView, mProj(g_mProjNonJittered), mViewInv, mProjInv;

	// TO-DO: move this to SceneView class
	{
		D3DXVECTOR4 LocalViewOrigin = g_vCameraPos;
		D3DXVECTOR3 Rotation = g_vCameraRotation;

		D3DXMATRIX ViewRotationMatrix = GetInverseRotationMatrix(Rotation) * D3DXMATRIX(
			0, 0, 1, 0,
			1, 0, 0, 0,
			0, 1, 0, 0,
			0, 0, 0, 1);

		if (!(abs(ViewRotationMatrix.m[3][0]) <= 0.0f && abs(ViewRotationMatrix.m[3][1]) <= 0.0f && abs(ViewRotationMatrix.m[3][2]) <= 0.0f))
		{
			D3DXVECTOR4 result;
			D3DXMATRIX invViewRotationMatrix;
			D3DXMatrixInverse(&invViewRotationMatrix, nullptr, &ViewRotationMatrix);
			D3DXVec4Transform(&result, &D3DXVECTOR4(0.0f, 0.0f, 0.0f, 1.0f), &invViewRotationMatrix);

			LocalViewOrigin += result;

			ViewRotationMatrix.m[3][0] = 0.0f;
			ViewRotationMatrix.m[3][1] = 0.0f;
			ViewRotationMatrix.m[3][2] = 0.0f;
		}

		D3DXMATRIX translation(
			1.0f, 0.0f, 0.0f, 0.0f,
			0.0f, 1.0f, 0.0f, 0.0f,
			0.0f, 0.0f, 1.0f, 0.0f,
			-LocalViewOrigin.x, -LocalViewOrigin.y, -LocalViewOrigin.z, 1.0f);

		D3DXMATRIX ViewMatrix = translation * ViewRotationMatrix;

		mView = ViewMatrix;
	}

	D3DXMatrixInverse(&mViewInv, nullptr, &mView);
	D3DXMatrixInverse(&mProjInv, nullptr, &mProj);
	//D3DXMATRIX mInvViewProj;
	//D3DXMatrixInverse(&mInvViewProj, nullptr, &(mView * mProj));

	m_pEffect->SetInt("g_iFrameIndexMod8", g_iFrameIndexMod8);
	m_pEffect->SetFloat("g_fTimer", g_fTimer);
	m_pEffect->SetMatrix("g_mProj", &mProj);
	m_pEffect->SetMatrix("g_mView", &mView);
	m_pEffect->SetMatrix("g_mViewInv", &mViewInv);
	m_pEffect->SetMatrix("g_mProjInv", &mProjInv);
	m_pEffect->SetMatrix("g_mViewProj", &(mView * mProj));
	m_pEffect->SetMatrix("g_mInvViewProj", &(mProjInv * mViewInv));
	m_pEffect->SetValue("g_vCameraPos", &g_vCameraPos, sizeof(D3DXVECTOR3));
	m_pEffect->SetTexture("g_depthTexture", g_depthRT.GetTexture());

	const float fn = g_fCameraFarZ / g_fCameraNearZ;
	m_pEffect->SetValue("g_vCameraClipPlanes", D3DXVECTOR4(1.0f - fn, fn, g_fCameraNearZ, g_fCameraFarZ), sizeof(D3DXVECTOR4));

	D3DXVECTOR2 InvDeviceZToWorldZTransform = CreateInvDeviceZToWorldZTransform(mProj);
	m_pEffect->SetValue("g_vInvDeviceZToWorldZTransform", &InvDeviceZToWorldZTransform, sizeof(D3DXVECTOR2));

	m_pEffect->SetValue("g_vScreenScaleBias", &g_vScreenPositionScaleBias, sizeof(D3DXVECTOR4));
	m_pEffect->SetValue("g_vBufferSize", &g_vBufferSize, sizeof(D3DXVECTOR4));
	m_pEffect->SetValue("g_vViewportSize", &g_vViewportSize, sizeof(D3DXVECTOR4));
	m_pEffect->SetValue("g_vViewportRect", &g_vViewportRect, sizeof(D3DXVECTOR4));

	// ===================================================================================

	// Anti-Aliasing
	TextureRenderTarget2D* tempRT = nullptr;
	if (bTemporalAA)
	{
		if (bUseVelocity)
			VelocityPass();

		tempRT = new TextureRenderTarget2D(m_pDevice, g_vBufferSize.x, g_vBufferSize.y, 1, ETextureUsage::RenderTarget, g_mainRT.GetFormat());

		if (bSMAA)
		{
			TextureRenderTarget2D smaaRT(m_pDevice, g_vBufferSize.x, g_vBufferSize.y, 1, ETextureUsage::RenderTarget, g_mainRT.GetFormat());
			RenderSMAA(&g_mainRT, &smaaRT);
			RenderTAA(&smaaRT, tempRT);
			smaaRT.Release();
		}
		else
		{
			RenderTAA(&g_mainRT, tempRT);
		}
	}
	else if (bSMAA)
	{
		tempRT = new TextureRenderTarget2D(m_pDevice, g_vBufferSize.x, g_vBufferSize.y, 1, ETextureUsage::RenderTarget, g_mainRT.GetFormat());
		RenderSMAA(&g_mainRT, tempRT);
	}
	else
	{
		tempRT = &g_mainRT;
	}

	// Auto Exposure
	if (bAutoExposure)
		CalculateAutoExposure(tempRT);

	// Bloom
	if (bBloom)
		RenderBloom(tempRT);

	// Ambient Occlusion
	if (bSSAO)
		RenderSSAO();

	// Screen-Space Reflections
	if (bSSR)
		RenderSSR(tempRT);

	// Screen-Space Contact Shadows
	if (bContactShadows)
		RenderContactShadows();

	// Color Grading LUT
	//if (bUpdateLUT)
	{
		RenderColorGradingLut();
		//D3DXSaveTextureToFileA("ColorGradingLut.png", D3DXIFF_PNG, colorGradingLutRT.GetTexture(), nullptr);
		bUpdateLUT = false;
	}

	// Composite
	FinalPass(tempRT, g_pBackBuffer);

	// Cleanup Anti-Aliasing Texture
	if (bTemporalAA || bSMAA)
		SAFE_RELEASE(tempRT);
}