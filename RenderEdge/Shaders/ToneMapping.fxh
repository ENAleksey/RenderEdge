#ifndef __COLORGRADING__
#define __COLORGRADING__

#include "ACES.fxh"
#include "PostProcessCommon.fxh"

int g_iColorGamut;
int g_iOutputDevice;


float g_fFilmSlope;
float g_fFilmToe;
float g_fFilmShoulder;
float g_fFilmBlackClip;
float g_fFilmWhiteClip;

float g_fBlueCorrection;
float g_fExpandGamut;

float g_fWhiteTemp;
float g_fWhiteTint;

float4 g_vColorSaturation;
float4 g_vColorContrast;
float4 g_vColorGamma;
float4 g_vColorGain;
float4 g_vColorOffset;

float4 g_vColorSaturationShadows;
float4 g_vColorContrastShadows;
float4 g_vColorGammaShadows;
float4 g_vColorGainShadows;
float4 g_vColorOffsetShadows;

float4 g_vColorSaturationMidtones;
float4 g_vColorContrastMidtones;
float4 g_vColorGammaMidtones;
float4 g_vColorGainMidtones;
float4 g_vColorOffsetMidtones;

float4 g_vColorSaturationHighlights;
float4 g_vColorContrastHighlights;
float4 g_vColorGammaHighlights;
float4 g_vColorGainHighlights;
float4 g_vColorOffsetHighlights;

float g_fColorCorrectionShadowsMax;
float g_fColorCorrectionHighlightsMin;


const float3x3 GamutMappingIdentityMatrix =
{
    1.0f, 0.0f, 0.0f,
    0.0f, 1.0f, 0.0f,
    0.0f, 0.0f, 1.0f
};

float3x3 OuputGamutMappingMatrix(int OutputGamut)
{
	const float3x3 AP1_2_sRGB = mul(XYZ_2_sRGB_MAT, mul(D60_2_D65_CAT, AP1_2_XYZ_MAT));
	const float3x3 AP1_2_DCI_D65 = mul(XYZ_2_P3D65_MAT, mul(D60_2_D65_CAT, AP1_2_XYZ_MAT));
	const float3x3 AP1_2_Rec2020 = mul(XYZ_2_Rec2020_MAT, mul(D60_2_D65_CAT, AP1_2_XYZ_MAT));

	if (OutputGamut == 1)
		return AP1_2_DCI_D65;
	else if (OutputGamut == 2)
		return AP1_2_Rec2020;
	else if (OutputGamut == 3)
		return AP1_2_AP0_MAT;
	else if (OutputGamut == 4)
		return GamutMappingIdentityMatrix;
	else
		return AP1_2_sRGB;
}


float2 PlanckianLocusChromaticity(float Temp)
{
	float u = (0.860117757f + 1.54118254e-4f * Temp + 1.28641212e-7f * Temp*Temp) / (1.0f + 8.42420235e-4f * Temp + 7.08145163e-7f * Temp*Temp);
	float v = (0.317398726f + 4.22806245e-5f * Temp + 4.20481691e-8f * Temp*Temp) / (1.0f - 2.89741816e-5f * Temp + 1.61456053e-7f * Temp*Temp);

	float x = 3*u / (2*u - 8*v + 4);
	float y = 2*v / (2*u - 8*v + 4);

	return float2(x,y);
}

float2 D_IlluminantChromaticity(float Temp)
{
	Temp *= 1.4388f / 1.438f;

	float x =	Temp <= 7000.0f ?
				0.244063f + (0.09911e3f + (2.9678e6f - 4.6070e9f / Temp) / Temp) / Temp :
				0.237040f + (0.24748e3f + (1.9018e6f - 2.0064e9f / Temp) / Temp) / Temp;
	
	float y = -3.0f * x*x + 2.87f * x - 0.275f;

	return float2(x,y);
}

float2 PlanckianIsothermal(float Temp, float Tint)
{
	float u = (0.860117757f + 1.54118254e-4f * Temp + 1.28641212e-7f * Temp*Temp) / (1.0f + 8.42420235e-4f * Temp + 7.08145163e-7f * Temp*Temp);
	float v = (0.317398726f + 4.22806245e-5f * Temp + 4.20481691e-8f * Temp*Temp) / (1.0f - 2.89741816e-5f * Temp + 1.61456053e-7f * Temp*Temp);

	float ud = (-1.13758118e9f - 1.91615621e6f * Temp - 1.53177f * Temp*Temp) / Pow2(1.41213984e6f + 1189.62f * Temp + Temp*Temp);
	float vd = ( 1.97471536e9f - 705674.0f * Temp - 308.607f * Temp*Temp) / Pow2(6.19363586e6f - 179.456f * Temp + Temp*Temp);

	float2 uvd = normalize(float2(u, v));

	u += -uvd.y * Tint * 0.05;
	v +=  uvd.x * Tint * 0.05;
	
	float x = 3*u / (2*u - 8*v + 4);
	float y = 2*v / (2*u - 8*v + 4);

	return float2(x,y);
}

float3 WhiteBalance(float3 LinearColor, float WhiteTemp, float WhiteTint)
{
	float2 SrcWhiteDaylight = D_IlluminantChromaticity(WhiteTemp);
	float2 SrcWhitePlankian = PlanckianLocusChromaticity(WhiteTemp);

	float2 SrcWhite = WhiteTemp < 4000.0f ? SrcWhitePlankian : SrcWhiteDaylight;
	float2 D65White = float2(0.31270f, 0.32900f);

	{
		float2 Isothermal = PlanckianIsothermal(WhiteTemp, WhiteTint) - SrcWhitePlankian;
		SrcWhite += Isothermal;
	}

	float3x3 WhiteBalanceMat = ChromaticAdaptation(SrcWhite, D65White);
	WhiteBalanceMat = mul(XYZ_2_sRGB_MAT, mul(WhiteBalanceMat, sRGB_2_XYZ_MAT));

	return mul(WhiteBalanceMat, LinearColor);
}

float3 ColorCorrect(float3 WorkingColor, float4 ColorSaturation, float4 ColorContrast, float4 ColorGamma, float4 ColorGain, float4 ColorOffset)
{
	// TODO optimize
	float Luma = dot(WorkingColor, AP1_RGB2Y);
	WorkingColor = max(0.0f, lerp(Luma.xxx, WorkingColor, ColorSaturation.xyz*ColorSaturation.w));
	WorkingColor = pow(WorkingColor * (1.0f / 0.18f), ColorContrast.xyz*ColorContrast.w) * 0.18f;
	WorkingColor = pow(WorkingColor, 1.0f / (ColorGamma.xyz*ColorGamma.w));
	WorkingColor = WorkingColor * (ColorGain.xyz * ColorGain.w) + (ColorOffset.xyz + ColorOffset.w);
	return WorkingColor;
}

float3 ColorCorrectAll(float3 WorkingColor)
{
	float Luma = dot( WorkingColor, AP1_RGB2Y );

	// Shadow CC
	float3 CCColorShadows = ColorCorrect(WorkingColor, 
		g_vColorSaturationShadows*g_vColorSaturation, 
		g_vColorContrastShadows*g_vColorContrast, 
		g_vColorGammaShadows*g_vColorGamma, 
		g_vColorGainShadows*g_vColorGain, 
		g_vColorOffsetShadows+g_vColorOffset);
	float CCWeightShadows = 1- smoothstep(0, g_fColorCorrectionShadowsMax, Luma);
	
	// Highlight CC
	float3 CCColorHighlights = ColorCorrect(WorkingColor, 
		g_vColorSaturationHighlights*g_vColorSaturation, 
		g_vColorContrastHighlights*g_vColorContrast, 
		g_vColorGammaHighlights*g_vColorGamma, 
		g_vColorGainHighlights*g_vColorGain, 
		g_vColorOffsetHighlights+g_vColorOffset);
	float CCWeightHighlights = smoothstep(g_fColorCorrectionHighlightsMin, 1, Luma);

	// Midtone CC
	float3 CCColorMidtones = ColorCorrect(WorkingColor, 
		g_vColorSaturationMidtones*g_vColorSaturation, 
		g_vColorContrastMidtones*g_vColorContrast, 
		g_vColorGammaMidtones*g_vColorGamma, 
		g_vColorGainMidtones*g_vColorGain, 
		g_vColorOffsetMidtones+g_vColorOffset);
	float CCWeightMidtones = 1 - CCWeightShadows - CCWeightHighlights;

	// Blend Shadow, Midtone and Highlight CCs
	float3 WorkingColorSMH = CCColorShadows*CCWeightShadows + CCColorMidtones*CCWeightMidtones + CCColorHighlights*CCWeightHighlights;
	
	return WorkingColorSMH;
}


float3 FilmToneMap2(float3 LinearColor) 
{
    const float3x3 sRGB_2_AP1 = mul(XYZ_2_AP1_MAT, mul(D65_2_D60_CAT, sRGB_2_XYZ_MAT));

	// Use ACEScg primaries as working space
	float3 WorkingColor = mul(sRGB_2_AP1, float3(LinearColor));
	WorkingColor = max(0.0f, WorkingColor);

	// Pre desaturate
	WorkingColor = lerp(dot(WorkingColor, AP1_RGB2Y), WorkingColor, 0.96f);
	
	const float ToeScale = 1.0f + g_fFilmBlackClip - g_fFilmToe;
	const float ShoulderScale = 1.0f + g_fFilmWhiteClip - g_fFilmShoulder;
	
	const float InMatch = 0.18f;
	const float OutMatch = 0.18f;

	float ToeMatch;
	if(g_fFilmToe > 0.8f)
	{
		ToeMatch = (1.0f - g_fFilmToe  - OutMatch) / g_fFilmSlope + log10(InMatch);
	}
	else
	{
		const float bt = (OutMatch + g_fFilmBlackClip) / ToeScale - 1.0f;
		ToeMatch = log10(InMatch) - 0.5f * log( (1.0f + bt)/(1.0f - bt) ) * (ToeScale / g_fFilmSlope);
	}

	float StraightMatch = (1.0f - g_fFilmToe) / g_fFilmSlope - ToeMatch;
	float ShoulderMatch = g_fFilmShoulder / g_fFilmSlope - StraightMatch;
	
	float3 LogColor = log10(WorkingColor);
	float3 StraightColor = g_fFilmSlope * (LogColor + StraightMatch);
	
	float3 ToeColor = (-g_fFilmBlackClip) + (2.0f * ToeScale) / (1.0f + exp((-2.0f * g_fFilmSlope / ToeScale) * (LogColor - ToeMatch)));
	float3 ShoulderColor = (1.0f + g_fFilmWhiteClip) - (2.0f * ShoulderScale) / (1.0f + exp((2.0f * g_fFilmSlope / ShoulderScale) * (LogColor - ShoulderMatch)));

	ToeColor = LogColor < ToeMatch ? ToeColor : StraightColor;
	ShoulderColor = LogColor > ShoulderMatch ? ShoulderColor : StraightColor;

	float3 t = saturate((LogColor - ToeMatch) / (ShoulderMatch - ToeMatch));
	t = ShoulderMatch < ToeMatch ? 1.0f - t : t;
	t = (3.0f - 2.0f * t) * t * t;
	float3 ToneColor = lerp(ToeColor, ShoulderColor, t);

	// Post desaturate
	ToneColor = lerp(dot(float3(ToneColor), AP1_RGB2Y), ToneColor, 0.93f);

	// Returning positive AP1 values
	return max(0.0f, ToneColor);
}

float3 FilmToneMap(float3 LinearColor)
{
    const float3x3 sRGB_2_AP0 = mul(XYZ_2_AP0_MAT, mul(D65_2_D60_CAT, sRGB_2_XYZ_MAT));
    const float3x3 sRGB_2_AP1 = mul(XYZ_2_AP1_MAT, mul(D65_2_D60_CAT, sRGB_2_XYZ_MAT));

    const float3x3 AP0_2_sRGB = mul(XYZ_2_sRGB_MAT, mul(D60_2_D65_CAT, AP0_2_XYZ_MAT));
    const float3x3 AP1_2_sRGB = mul(XYZ_2_sRGB_MAT, mul(D60_2_D65_CAT, AP1_2_XYZ_MAT));
	
    const float3x3 AP0_2_AP1 = mul(XYZ_2_AP1_MAT, AP0_2_XYZ_MAT);
    const float3x3 AP1_2_AP0 = mul(XYZ_2_AP0_MAT, AP1_2_XYZ_MAT);
	
    float3 ColorAP1 = LinearColor;
	//float3 ColorAP1 = mul( sRGB_2_AP1, float3(LinearColor) );

    float3 ColorAP0 = mul(AP1_2_AP0, ColorAP1);

#if 1
	// "Glow" module constants
    const float RRT_GLOW_GAIN = 0.05;
    const float RRT_GLOW_MID = 0.08;

    float saturation = rgb_2_saturation(ColorAP0);
    float ycIn = rgb_2_yc(ColorAP0);
    float s = sigmoid_shaper((saturation - 0.4) / 0.2);
    float addedGlow = 1 + glow_fwd(ycIn, RRT_GLOW_GAIN * s, RRT_GLOW_MID);
    ColorAP0 *= addedGlow;
#endif

#if 1
	// --- Red modifier --- //
    const float RRT_RED_SCALE = 0.82;
    const float RRT_RED_PIVOT = 0.03;
    const float RRT_RED_HUE = 0;
    const float RRT_RED_WIDTH = 135;
    float hue = rgb_2_hue(ColorAP0);
    float centeredHue = center_hue(hue, RRT_RED_HUE);
    float hueWeight = Pow2(smoothstep(0, 1, 1 - abs(2 * centeredHue / RRT_RED_WIDTH)));
		
    ColorAP0.r += hueWeight * saturation * (RRT_RED_PIVOT - ColorAP0.r) * (1. - RRT_RED_SCALE);
#endif
	
	// Use ACEScg primaries as working space
    float3 WorkingColor = mul(AP0_2_AP1_MAT, ColorAP0);

    WorkingColor = max(0, WorkingColor);

	// Pre desaturate
    WorkingColor = lerp(dot(WorkingColor, AP1_RGB2Y), WorkingColor, 0.96);
	
    const half ToeScale = 1 + g_fFilmBlackClip - g_fFilmToe;
    const half ShoulderScale = 1 + g_fFilmWhiteClip - g_fFilmShoulder;
	
    const float InMatch = 0.18;
    const float OutMatch = 0.18;

    float ToeMatch;
    if (g_fFilmToe > 0.8)
    {
		// 0.18 will be on straight segment
        ToeMatch = (1 - g_fFilmToe - OutMatch) / g_fFilmSlope + log10(InMatch);
    }
    else
    {
		// 0.18 will be on toe segment

		// Solve for ToeMatch such that input of InMatch gives output of OutMatch.
        const float bt = (OutMatch + g_fFilmBlackClip) / ToeScale - 1;
        ToeMatch = log10(InMatch) - 0.5 * log((1 + bt) / (1 - bt)) * (ToeScale / g_fFilmSlope);
    }

    float StraightMatch = (1 - g_fFilmToe) / g_fFilmSlope - ToeMatch;
    float ShoulderMatch = g_fFilmShoulder / g_fFilmSlope - StraightMatch;
	
    float3 LogColor = log10(WorkingColor);
    float3 StraightColor = g_fFilmSlope * (LogColor + StraightMatch);
	
    float3 ToeColor = (-g_fFilmBlackClip) + (2 * ToeScale) / (1 + exp((-2 * g_fFilmSlope / ToeScale) * (LogColor - ToeMatch)));
    float3 ShoulderColor = (1 + g_fFilmWhiteClip) - (2 * ShoulderScale) / (1 + exp((2 * g_fFilmSlope / ShoulderScale) * (LogColor - ShoulderMatch)));

    ToeColor = LogColor < ToeMatch ? ToeColor : StraightColor;
    ShoulderColor = LogColor > ShoulderMatch ? ShoulderColor : StraightColor;

    float3 t = saturate((LogColor - ToeMatch) / (ShoulderMatch - ToeMatch));
    t = ShoulderMatch < ToeMatch ? 1 - t : t;
    t = (3 - 2 * t) * t * t;
    float3 ToneColor = lerp(ToeColor, ShoulderColor, t);

	// Post desaturate
    ToneColor = lerp(dot(float3(ToneColor), AP1_RGB2Y), ToneColor, 0.93);

	// Returning positive AP1 values
    return max(0, ToneColor);
}

#endif // __COLORGRADING__