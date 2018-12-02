#ifndef __LUTBAKER__
#define __LUTBAKER__

#include "Aces.fxh"
#include "ToneMapping.fxh"
#include "GammaCorrection.fxh"
#include "PostProcessCommon.fxh"


bool g_bUserLUT;
float g_fUserLutIntensity;
float3 g_vMappingPolynomial = { 0.0f, 1.0f, 0.0f };
float g_fInverseGamma;
const float LUTSize = 32;

texture g_userLutTexture;
sampler2D userLutSampler = sampler_state
{
	Texture = <g_userLutTexture>;
	MipFilter = NONE;
	MinFilter = LINEAR;
	MagFilter = LINEAR;
};


float3 ColorCorrection(float3 InLDRColor)
{
	return g_vMappingPolynomial.x * (InLDRColor * InLDRColor) + g_vMappingPolynomial.y * InLDRColor + g_vMappingPolynomial.z;
}

float3 ToneMapping(float3 LinearColor)
{
    const float3x3 sRGB_2_AP1 = mul(XYZ_2_AP1_MAT, mul(D65_2_D60_CAT, sRGB_2_XYZ_MAT));
    const float3x3 AP1_2_sRGB = mul(XYZ_2_sRGB_MAT, mul(D60_2_D65_CAT, AP1_2_XYZ_MAT));

    const float3x3 AP0_2_AP1 = mul(XYZ_2_AP1_MAT, AP0_2_XYZ_MAT);
    const float3x3 AP1_2_AP0 = mul(XYZ_2_AP0_MAT, AP1_2_XYZ_MAT);

    const float3x3 AP1_2_Output = OuputGamutMappingMatrix(g_iColorGamut);

    float3 BalancedColor = WhiteBalance(LinearColor, g_fWhiteTemp, g_fWhiteTint);
    float3 ColorAP1 = mul(sRGB_2_AP1, BalancedColor);

    // Expand bright saturated colors outside the sRGB gamut to fake wide gamut rendering.
    float LumaAP1 = dot(ColorAP1, AP1_RGB2Y);
    float3 ChromaAP1 = ColorAP1 / LumaAP1;

    float ChromaDistSqr = dot(ChromaAP1 - 1, ChromaAP1 - 1);
    float ExpandAmount = (1 - exp2(-4 * ChromaDistSqr)) * (1 - exp2(-4 * g_fExpandGamut * LumaAP1 * LumaAP1));

    const float3x3 Wide_2_XYZ_MAT =
    {
        0.5441691, 0.2395926, 0.1666943,
		0.2394656, 0.7021530, 0.0583814,
		-0.0023439, 0.0361834, 1.0552183,
    };

    const float3x3 Wide_2_AP1 = mul(XYZ_2_AP1_MAT, Wide_2_XYZ_MAT);
    const float3x3 ExpandMat = mul(Wide_2_AP1, AP1_2_sRGB);

    float3 ColorExpand = mul(ExpandMat, ColorAP1);
    ColorAP1 = lerp(ColorAP1, ColorExpand, ExpandAmount);

    ColorAP1 = ColorCorrectAll(ColorAP1);

    const float3x3 BlueCorrect =
    {
        0.9404372683, -0.0183068787, 0.0778696104,
		0.0083786969, 0.8286599939, 0.1629613092,
		0.0005471261, -0.0008833746, 1.0003362486
    };
    const float3x3 BlueCorrectInv =
    {
        1.06318, 0.0233956, -0.0865726,
		-0.0106337, 1.20632, -0.19569,
		-0.000590887, 0.00105248, 0.999538
    };
    const float3x3 BlueCorrectAP1 = mul(AP0_2_AP1, mul(BlueCorrect, AP1_2_AP0));
    const float3x3 BlueCorrectInvAP1 = mul(AP0_2_AP1, mul(BlueCorrectInv, AP1_2_AP0));

	// Blue correction
    ColorAP1 = lerp(ColorAP1, mul(BlueCorrectAP1, ColorAP1), g_fBlueCorrection);

    // Tonemapped color in the AP1 gamut
    ColorAP1 = FilmToneMap(ColorAP1);

	// Uncorrect blue to maintain white point
    ColorAP1 = lerp(ColorAP1, mul(BlueCorrectInvAP1, ColorAP1), g_fBlueCorrection);

    // Convert from AP1 to sRGB and clip out-of-gamut values
    float3 FilmColor = max(0, mul(AP1_2_sRGB, ColorAP1));
	
    if (g_bUserLUT)
    {
        float3 GammaColor = LinearToSrgb(saturate(FilmColor));

        const float LUTSize = 16;
        float3 UVW = GammaColor * ((LUTSize - 1) / LUTSize) + (0.5f / LUTSize);
		
        float3 colorGraded = UnwrappedTexture3DSample(userLutSampler, UVW, LUTSize);
        GammaColor = lerp(GammaColor, colorGraded, g_fUserLutIntensity);
		
        FilmColor = toLinear(GammaColor);
    }
	
	//FilmColor = ColorCorrection(FilmColor);
	//FilmColor = pow(max(0, FilmColor), g_vInverseGamma.y);
	
    float3 OutDeviceColor = 0;
	
	// sRGB, user specified gamut
    if (g_iOutputDevice == 0)
    {
        float3 OutputGamutColor = FilmColor;
        OutDeviceColor = LinearToSrgb(OutputGamutColor);
    }
	// Rec 709, user specified gamut
    else if (g_iOutputDevice == 1)
    {
        float3 OutputGamutColor = mul(AP1_2_Output, mul(sRGB_2_AP1, FilmColor));
        OutDeviceColor = LinearTo709(OutputGamutColor);
    }
	// Gamma 2.2, user specified gamut
    else if (g_iOutputDevice == 2)
    {
        float3 OutputGamutColor = mul(AP1_2_Output, mul(sRGB_2_AP1, FilmColor));
        OutDeviceColor = pow(abs(OutputGamutColor), g_fInverseGamma);
    }
	/*
	// ACES 1000nit transform with PQ/2084 encoding, user specified gamut
	else if (g_iOutputDevice == 3 || g_iOutputDevice == 5)
	{
		float3 ODTColor = ACESOutputTransforms1000(GradedColor);
		ODTColor = mul(AP1_2_Output, ODTColor);
		OutDeviceColor = LinearToST2084(ODTColor);
	}
	// ACES 2000nit transform with PQ/2084 encoding, user specified gamut
	else if (g_iOutputDevice == 4 || g_iOutputDevice == 6)
	{
		float3 ODTColor = ACESOutputTransforms2000(GradedColor);
		ODTColor = mul(AP1_2_Output, ODTColor);
		OutDeviceColor = LinearToST2084(ODTColor);
	}
	*/
	
    return OutDeviceColor;
}

float4 BuildHdrLutPS(float2 texCooord : TEXCOORD0) : COLOR
{
	float3 Neutral;
	{ 
		float2 UV = texCooord;

		// 0.49999f instead of 0.5f to avoid getting into negative values
		UV -= float2(0.49999f / (LUTSize * LUTSize), 0.49999f / LUTSize);

		float Scale = LUTSize / (LUTSize - 1);

		float3 RGB;
		
		RGB.r = frac(UV.x * LUTSize);
		RGB.b = UV.x - RGB.r / LUTSize;
		RGB.g = UV.y;

		Neutral = RGB * Scale;
	}
	
	float3 LinearColor  = LogToLin(Neutral) - LogToLin(0);
	float3 OutColor = ToneMapping(LinearColor) / 1.05;
	
	return float4(OutColor, 0.0f);
}

//-----------------------------------------------------------------------------

technique BuildHdrLut
{
    pass p0
    {
        PixelShader = compile ps_3_0 BuildHdrLutPS();
    }
}

#endif // __LUTBAKER__