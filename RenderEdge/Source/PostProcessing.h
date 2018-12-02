#pragma once

#include "Utils.h"
#include "Texture2D.h"
#include "TextureRenderTarget2D.h"
#include "SMAA.h"

enum class EDebugScreen : uint32
{
	SceneDepth,
	CascadedShadows,
	ContactShadows,
	SSAO,
	SSR,
	BloomBrightPass,
	Bloom
};

class CPostProcessing
{
private:
	void InitTemporaryResources();
	void ReleaseTemporaryResources();

	void DrawFullScreenTriangle(float x, float y, float width, float height);
	void DrawFullScreenTriangle();

	void ApplyEffect(const std::string& technique, uint32 pass = 0, bool clear = true);
	void ApplyEffect(TextureRenderTarget2D* destRT, const std::string& technique, uint32 pass = 0, bool clear = true);
	void ApplyEffect(IDirect3DSurface9* destRT, const std::string& technique, uint32 pass = 0, bool clear = true);

	IDirect3DDevice9* m_pDevice;


	// Effects
	void ComputeEyeAdaptationValues();
	void CalculateAutoExposure(TextureRenderTarget2D* sourceRT);
	void RenderSMAA(TextureRenderTarget2D* sourceRT, TextureRenderTarget2D* destRT);
	void VelocityPass();
	const D3DXVECTOR2& GenerateRandomOffset();
	const D3DXVECTOR2& GenerateRandomOffset2();
	void ResetProjectionMatrix();
	TextureRenderTarget2D* CheckHistory(TextureRenderTarget2D* sourceRT, int id);
	void RenderTAA(TextureRenderTarget2D* sourceRT, TextureRenderTarget2D* destRT);
	void Dithering();
	void RenderSSAO();
	void RenderSSR(TextureRenderTarget2D* sourceRT);
	void RenderContactShadows();
	void RenderBloom(TextureRenderTarget2D* sourceRT);
	void RenderColorGradingLut();
	void FinalPass(TextureRenderTarget2D* sourceRT, IDirect3DSurface9* destRT);

public:
	CPostProcessing(IDirect3DDevice9* pDevice);
	~CPostProcessing();

	void OnResetDevice();
	void OnLostDevice();
	void SetJitteredProjectionMatrix();
	void Render();

	ID3DXEffect* m_pEffect;


	// Debug View
	bool bDebugView;
	EDebugScreen iDebugScreen;
	void SetDebugScreen(EDebugScreen debugScreen, TextureRenderTarget2D* pRT, bool bOneChannel = false, const D3DXVECTOR2& tiling = { 1.0f, 1.0f });


	// SMAA
	bool bSMAA;
	SMAA::Input iSMAAInput;
	float fSMAAThreshold;
	uint32 iSMAASearchSteps;
	uint32 iSMADiagSearchSteps;
	float fSMAACornerRounding;


	// Temporal AA
	bool bTemporalAA;
	bool bUseVelocity;
	float fJitterSpreadTAA;
	float fSharpnessTAA;
	float fStationaryBlendingTAA;
	float fMotionBlendingTAA;
	TextureRenderTarget2D velocityRT;
	TextureRenderTarget2D taaRTs[2];
	D3DXVECTOR2 jitter;
	uint32 iTemporalAASampleIndex;
	uint32 iHistoryPingPong;


	// Bloom
	bool bBloom;
	float fBloomThreshold;
	float fBloomIntensity;
	float fBloomRadius;
	float fBloomAnamorphicRatio;
	//float fBloomSoftKnee;

	float BloomSizeScale;
	D3DXVECTOR3 Bloom1Tint;
	float Bloom1Size;
	D3DXVECTOR3 Bloom2Tint;
	float Bloom2Size;
	D3DXVECTOR3 Bloom3Tint;
	float Bloom3Size;
	D3DXVECTOR3 Bloom4Tint;
	float Bloom4Size;
	D3DXVECTOR3 Bloom5Tint;
	float Bloom5Size;
	D3DXVECTOR3 Bloom6Tint;
	float Bloom6Size;

	bool bLensDirt;
	float fLensDirtIntensity;
	Texture2D lensDirtTexture;
	std::string lensDirtTextureFileName;


	// Auto Exposure
	bool bAutoExposure;
	float fAutoExposureSpeedUp;
	float fAutoExposureSpeedDown;
	float fAutoExposureMinBrightness;
	float fAutoExposureMaxBrightness;
	float fAutoExposureHistogramLogMin;
	float fAutoExposureHistogramLogMax;
	float fAutoExposureBias;
	float fAutoExposureCalibrationConstant;
	uint32 iExposurePingPong;
	TextureRenderTarget2D adaptedExposureRTs[2];


	// Color Correction
	bool bUpdateLUT;
	TextureRenderTarget2D colorGradingLutRT;

	float fWhiteTemp;
	float fWhiteTint;

	D3DXVECTOR4 vColorSaturation;
	D3DXVECTOR4 vColorContrast;
	D3DXVECTOR4 vColorGamma;
	D3DXVECTOR4 vColorGain;
	D3DXVECTOR4 vColorOffset;

	D3DXVECTOR4 vColorSaturationShadows;
	D3DXVECTOR4 vColorContrastShadows;
	D3DXVECTOR4 vColorGammaShadows;
	D3DXVECTOR4 vColorGainShadows;
	D3DXVECTOR4 vColorOffsetShadows;

	D3DXVECTOR4 vColorSaturationMidtones;
	D3DXVECTOR4 vColorContrastMidtones;
	D3DXVECTOR4 vColorGammaMidtones;
	D3DXVECTOR4 vColorGainMidtones;
	D3DXVECTOR4 vColorOffsetMidtones;

	D3DXVECTOR4 vColorSaturationHighlights;
	D3DXVECTOR4 vColorContrastHighlights;
	D3DXVECTOR4 vColorGammaHighlights;
	D3DXVECTOR4 vColorGainHighlights;
	D3DXVECTOR4 vColorOffsetHighlights;

	float fColorCorrectionShadowsMax;
	float fColorCorrectionHighlightsMin;

	float fBlueCorrection;
	float fExpandGamut;

	Texture2D userLutTexture;
	std::string userLutTextureFileName;
	bool bUserLUT;
	float fUserLutIntensity;

	uint32 iColorGamut;
	uint32 iOutputDevice;
	float fGamma;


	// Tonemapper
	float fFilmSlope;
	float fFilmToe;
	float fFilmShoulder;
	float fFilmBlackClip;
	float fFilmWhiteClip;


	// Ambient Occlusion
	bool bSSAO;
	float fSSAOIntensity;
	float fSSAORadius;
	float fSSAOContrast;
	float fSSAOGeometryCoeff;
	float fSSAOBeta;
	bool bSSAODownsample;
	bool bSSAODownsampleOld;
	TextureRenderTarget2D ssaoRT;


	// Reflections
	bool bSSR;
	bool bSSRDownsample;
	bool bSSRDownsampleOld;
	float fSSRMinRayStep;
	float fSSRRayStep;
	float fSSRJitter;
	float fSSRRayhitThreshold;
	float fSSRDepthThreshold;
	TextureRenderTarget2D ssrRT;


	// Contact Shadows
	bool bContactShadows;
	bool bContactShadowsDownsample;
	bool bContactShadowsDownsampleOld;
	float fContactShadowsRayLength;
	TextureRenderTarget2D contactShadowsRT;


	// ChromaticAberration
	bool bChromaticAberration;
	float fChromaticAberrationIntensity;
	Texture2D spectralLutTexture;


	// Vignette
	bool bVignette;
	D3DXVECTOR3 vVignetteColor;
	bool bVignetteRounded;
	float fVignetteSmoothness;
	float fVignetteIntensity;
	float fVignetteRoundness;


	// Film Grain
	bool bFilmGrain;
	float fFilmGrainIntensity;
	float fFilmGrainVariance;
	uint32 iFilmGrainSignalToNoiseRatio;


	// Dithering
	bool bDithering;
	Texture2D noiseTextures[64];
	uint32 iDitheringTextureIndex;
};

extern CPostProcessing* PostProcessing;