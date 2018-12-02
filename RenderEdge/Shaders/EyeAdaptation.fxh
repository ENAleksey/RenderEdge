#ifndef __EYE_ADAPTATION__
#define __EYE_ADAPTATION__

#include "PostProcessCommon.fxh"

float g_fDeltaTime;

bool g_bAutoExposure;
float g_fExposureOffset;
float g_fEyeAdaptationSpeedUp;
float g_fEyeAdaptationSpeedDown;
float g_fMinBrightness;
float g_fMaxBrightness;

float g_fHistogramMultiply;
float g_fHistogramAdd;
float g_fHistogramMinIntensity;
float g_fAverageLuminanceScale;

float2 g_avSampleOffsets[16];
float4 g_avSampleWeights[16];

texture g_eyeAdaptationTexture;
sampler2D eyeAdaptationSampler = sampler_state
{
	Texture = <g_eyeAdaptationTexture>;
	MipFilter = NONE;
	MinFilter = POINT;
	MagFilter = POINT;
	AddressU = CLAMP;
	AddressV = CLAMP;
};

texture g_curExposureTexture;
sampler2D exposureSampler = sampler_state
{
	Texture = <g_curExposureTexture>;
	MipFilter = NONE;
	MinFilter = POINT;
	MagFilter = POINT;
	AddressU = CLAMP;
	AddressV = CLAMP;
};


float GetLogLumAverage(float3 color)
{
	float intensity = max(dot(color, float3(0.2126, 0.7152, 0.0722)), g_fHistogramMinIntensity);
	return g_fHistogramMultiply * log2(intensity) + g_fHistogramAdd; 
	
}

float ComputeEyeAdaptation(float oldExposure, float targetExposure, float deltaTime)
{
	float diff = targetExposure - oldExposure;
    float adaptionSpeed = (diff > 0) ? g_fEyeAdaptationSpeedUp : g_fEyeAdaptationSpeedDown;
	float factor = 1.0f - exp2(-deltaTime * adaptionSpeed);

	return clamp(oldExposure + diff * factor, g_fMinBrightness, g_fMaxBrightness);
}

float4 LogLumAveragePS(float2 texCoord : TEXCOORD0) : COLOR
{
    float  fAvg = 0.0f;
    for( int i = 0; i < 4; i++ )
        fAvg += GetLogLumAverage(tex2D(mainSampler, ViewportToScreen(texCoord + g_avSampleOffsets[i])).rgb);
		
    fAvg /= 4;

    return float4(fAvg, 0.0f, 0.0f, 1.0f);
}

float4 DownScalePS(float2 texCoord : TEXCOORD0) : COLOR
{	
    float fAvg = 0.0f; 
    for( int i = 0; i < 9; i++ )
		fAvg += tex2D(mainSampler, texCoord + g_avSampleOffsets[i]).r;
		
    fAvg /= 9;

    return float4(fAvg, 0.0f, 0.0f, 1.0f);
}

float4 CalculateAdaptedExposurePS(float2 texCoord : TEXCOORD0) : COLOR
{
	float logLumAve = tex2D(exposureSampler, float2(0.5f, 0.5f)).r;
	logLumAve = (logLumAve - g_fHistogramAdd) / g_fHistogramMultiply;
    float lumAve = exp2(logLumAve) * g_fAverageLuminanceScale;
	float clampedLumAve = clamp(lumAve, g_fMinBrightness, g_fMaxBrightness);

	float exposureScaleOld = tex2D(eyeAdaptationSampler, float2(0.5f, 0.5f)).r;
	float luminanceAveOld = g_fExposureOffset / (exposureScaleOld != 0 ? exposureScaleOld : 1.0f);

	float smoothedLuminance = ComputeEyeAdaptation(luminanceAveOld, clampedLumAve, g_fDeltaTime);
	float smoothedExposureScale = g_fExposureOffset / max(0.0001f, smoothedLuminance);
	
	return float4(smoothedExposureScale, 0.0f, 0.0f, 1.0f);
}

//-----------------------------------------------------------------------------

technique AutoExposure
{
	pass LogLumAverage
    {
        PixelShader = compile ps_2_0 LogLumAveragePS();
    }
	
    pass DownScale
    {
        PixelShader = compile ps_2_0 DownScalePS();
    }
	
    pass CalculateAdaptedExposure
    {
        PixelShader = compile ps_2_0 CalculateAdaptedExposurePS();
    }
}

#endif // __EYE_ADAPTATION__