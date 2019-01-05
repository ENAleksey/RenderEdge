#ifndef __SHADOWCOMMON__
#define __SHADOWCOMMON__

#include "Random.fxh"

#define NUM_CASCADES 3
float4x4 g_mShadow[NUM_CASCADES];
float g_vCascades[NUM_CASCADES];

bool g_bShadows;
bool g_bSoftShadows;
bool g_bVisCascades;
float g_fRadius;
float4 g_vShadowBufferSize;
float g_fShadowPartitionSize;
float g_fSoftTransitionScale;
float g_fShadowSharpen;

static const float2 kernel[4] =
{
    float2(0.7437094f, -0.2600714f),
	float2(0.1452257f, 0.9243255f),
	float2(-0.2595889f, -0.6537333f),
	float2(-0.5877237f, 0.3391896f)
};

texture g_shadowTexture;
sampler2D shadowSampler = sampler_state
{
    Texture = <g_shadowTexture>;
    MipFilter = None;
    MinFilter = Point;
    MagFilter = Point;
    BorderColor = 0xFFFFFF;
    AddressU = Border;
    AddressV = Border;
};


/*float PCF3x3(float2 Fraction, float4 Values0, float4 Values1, float4 Values2, float4 Values3)
{
    float2 VerticalLerp00 = lerp(float2(Values0.x, Values1.x), float2(Values0.y, Values1.y), Fraction.xx);
    float PCFResult00 = lerp(VerticalLerp00.x, VerticalLerp00.y, Fraction.y);

    float2 VerticalLerp10 = lerp(float2(Values0.y, Values1.y), float2(Values0.z, Values1.z), Fraction.xx);
    float PCFResult10 = lerp(VerticalLerp10.x, VerticalLerp10.y, Fraction.y);

    float2 VerticalLerp20 = lerp(float2(Values0.z, Values1.z), float2(Values0.w, Values1.w), Fraction.xx);
    float PCFResult20 = lerp(VerticalLerp20.x, VerticalLerp20.y, Fraction.y);

    float2 VerticalLerp01 = lerp(float2(Values1.x, Values2.x), float2(Values1.y, Values2.y), Fraction.xx);
    float PCFResult01 = lerp(VerticalLerp01.x, VerticalLerp01.y, Fraction.y);

    float2 VerticalLerp11 = lerp(float2(Values1.y, Values2.y), float2(Values1.z, Values2.z), Fraction.xx);
    float PCFResult11 = lerp(VerticalLerp11.x, VerticalLerp11.y, Fraction.y);

    float2 VerticalLerp21 = lerp(float2(Values1.z, Values2.z), float2(Values1.w, Values2.w), Fraction.xx);
    float PCFResult21 = lerp(VerticalLerp21.x, VerticalLerp21.y, Fraction.y);

    float2 VerticalLerp02 = lerp(float2(Values2.x, Values3.x), float2(Values2.y, Values3.y), Fraction.xx);
    float PCFResult02 = lerp(VerticalLerp02.x, VerticalLerp02.y, Fraction.y);

    float2 VerticalLerp12 = lerp(float2(Values2.y, Values3.y), float2(Values2.z, Values3.z), Fraction.xx);
    float PCFResult12 = lerp(VerticalLerp12.x, VerticalLerp12.y, Fraction.y);

    float2 VerticalLerp22 = lerp(float2(Values2.z, Values3.z), float2(Values2.w, Values3.w), Fraction.xx);
    float PCFResult22 = lerp(VerticalLerp22.x, VerticalLerp22.y, Fraction.y);

    return saturate((PCFResult00 + PCFResult10 + PCFResult20 + PCFResult01 + PCFResult11 + PCFResult21 + PCFResult02 + PCFResult12 + PCFResult22) * 0.11111f);
}

float4 CalculateOcclusion(float4 ShadowmapDepth, float SceneDepth)
{
    return saturate((ShadowmapDepth - SceneDepth) * g_fSoftTransitionScale + 1.0f);
}

void FetchRowOfFour(float2 Sample00TexelCenter, float VerticalOffset, out float4 Values0, float SceneDepth)
{
    Values0.x = tex2D(shadowSampler, (Sample00TexelCenter + float2(0, VerticalOffset)) * g_vShadowBufferSize.zw).r;
    Values0.y = tex2D(shadowSampler, (Sample00TexelCenter + float2(1, VerticalOffset)) * g_vShadowBufferSize.zw).r;
    Values0.z = tex2D(shadowSampler, (Sample00TexelCenter + float2(2, VerticalOffset)) * g_vShadowBufferSize.zw).r;
    Values0.w = tex2D(shadowSampler, (Sample00TexelCenter + float2(3, VerticalOffset)) * g_vShadowBufferSize.zw).r;
    Values0 = CalculateOcclusion(Values0, SceneDepth);
}

float ManualPCF(float2 ShadowPosition, float SceneDepth)
{
    float2 TexelPos = ShadowPosition * g_vShadowBufferSize.xy - 0.5f;
    float2 Fraction = frac(TexelPos);
    float2 TexelCenter = floor(TexelPos) + 0.5f;
	{
        float2 Sample00TexelCenter = TexelCenter - float2(1, 1);

        float4 SampleValues0, SampleValues1, SampleValues2, SampleValues3;

        FetchRowOfFour(Sample00TexelCenter, 0, SampleValues0, SceneDepth);
        FetchRowOfFour(Sample00TexelCenter, 1, SampleValues1, SceneDepth);
        FetchRowOfFour(Sample00TexelCenter, 2, SampleValues2, SceneDepth);
        FetchRowOfFour(Sample00TexelCenter, 3, SampleValues3, SceneDepth);
        return PCF3x3(Fraction, SampleValues0, SampleValues1, SampleValues2, SampleValues3);
    }
}*/

float CalculateOcclusion(float ShadowmapDepth, float SceneDepth)
{
    return saturate((ShadowmapDepth - SceneDepth) * g_fSoftTransitionScale + 1.0f);
}

float ManualNoFiltering(float2 ShadowPosition, float SceneDepth)
{
    return CalculateOcclusion(tex2D(shadowSampler, ShadowPosition).r, SceneDepth);
}


float GetShadowTerm(float3 worldPos, float3 vertexPos)
{
	if (vertexPos.z < 0.0f || vertexPos.z > g_vCascades[NUM_CASCADES - 1])
		return 1.0f;
		
    int iCascadeIndex = 2;
    if (vertexPos.z <= g_vCascades[0])
        iCascadeIndex = 0;
    else if (vertexPos.z <= g_vCascades[1])
        iCascadeIndex = 1;
	
	//worldPos += g_vLightDir.xyz * pow(saturate(g_fMaterialTranslucent - 0.4f), 4.0f);
	
    float3 shadowCoord = mul(float4(worldPos, 1.0f), g_mShadow[iCascadeIndex]).xyz;
    shadowCoord.x = (shadowCoord.x + iCascadeIndex) * g_fShadowPartitionSize;
    shadowCoord.z = min(shadowCoord.z, 0.99999f);
	
    float fShadowTerm = 0.0f;
    /*if (g_bSoftShadows)
    {
        fShadowTerm = ManualPCF(shadowCoord.xy, shadowCoord.z);
        fShadowTerm = saturate((fShadowTerm - 0.5) * g_fShadowSharpen + 0.5);
    }
	else*/
	{
        if (g_fRadius > 0.0f)
        {
            const float angle = randomAngle(vertexPos, 100);
            const float s = sin(angle);
            const float c = cos(angle);
			
			[unroll]
            for (int i = 0; i < 4; i++)
            {
                const float2 rotatedOffset = float2(kernel[i].x * c + kernel[i].y * s, kernel[i].x * -s + kernel[i].y * c);
                fShadowTerm += ManualNoFiltering(shadowCoord.xy + rotatedOffset * g_vShadowBufferSize.zw * g_fRadius, shadowCoord.z);
            }
            fShadowTerm /= 4;
        }
        else
        {
            fShadowTerm = ManualNoFiltering(shadowCoord.xy, shadowCoord.z);
        }
    }
	
    return fShadowTerm;
}

#endif // __SHADOWCOMMON__