#ifndef __SSAO__
#define __SSAO__

#include "PostProcessCommon.fxh"

float g_fSSAOIntensity;
float g_fSSAORadius;
float g_fSSAODownsample;

float g_fSSAOContrast;
float g_fSSAOGeometryCoeff;
float g_fSSAOBeta;

#define SAMPLE_COUNT 10
//#define BLUR_HIGH_QUALITY


float4 PackAONormal(float ao, float3 n)
{
    return float4(ao, n * 0.5 + 0.5);
}

float GetPackedAO(float4 p)
{
    return p.r;
}

float3 GetPackedNormal(float4 p)
{
    return p.gba * 2.0 - 1.0;
}

float CheckBounds(float2 uv, float d)
{
    float ob = any(uv < 0) + any(uv > 1);
    ob += (d >= 0.99999);
    return ob * 1e8;
}

float SampleDepth(float2 uv)
{
    float d = SampleLinearDepth(uv);
    return d /** g_vCameraClipPlanes.w*/ + CheckBounds(uv, d);
}

float CompareNormal(float3 d1, float3 d2)
{
    return smoothstep(g_fSSAOGeometryCoeff, 1.0, dot(d1, d2));
}

float2 CosSin(float theta)
{
    float sn, cs;
    sincos(theta, sn, cs);
    return float2(cs, sn);
}

float UVRandom(float u, float v)
{
    float f = dot(float2(12.9898, 78.233), float2(u, v));
    return frac(43758.5453 * sin(f));
}

float3 ReconstructViewPos(float2 uv, float3x3 mProjection)
{
	float depth = SampleDepth(uv);
	float2 p11_22 = float2(mProjection._11, mProjection._22);
    float2 p13_31 = float2(mProjection._13, mProjection._23);
    return float3((uv * 2.0 - 1.0 - p13_31) / p11_22 * depth, depth);
}

float3 GetViewSpacePosition(float2 uv)
{
    float depth = SampleNonLinearDepth(uv);
    float4 result = mul(g_mProjInv, float4(2.0 * uv - 1.0, depth, 1.0));
    return result.xyz / result.w;
}

float3 ReconstructNormal(float2 texCoord)
{
	float3 offs = float3(g_vBufferSize.zw, 0);

	float3 f = ReconstructViewPos(texCoord.xy, g_mProj);
	float3 d_dx1 = -f + ReconstructViewPos(texCoord.xy + offs.xz, g_mProj);
	float3 d_dx2 =  f - ReconstructViewPos(texCoord.xy - offs.xz, g_mProj);
	float3 d_dy1 = -f + ReconstructViewPos(texCoord.xy + offs.zy, g_mProj);
	float3 d_dy2 =  f - ReconstructViewPos(texCoord.xy - offs.zy, g_mProj);

	d_dx1 = lerp(d_dx1, d_dx2, abs(d_dx1.z) > abs(d_dx2.z));
	d_dy1 = lerp(d_dy1, d_dy2, abs(d_dy1.z) > abs(d_dy2.z));

	return normalize(cross(d_dy1, d_dx1));
}

float GradientNoise(float2 uv)
{
    uv = floor(uv * g_vBufferSize.xy);
    float f = dot(float2(0.06711056, 0.00583715), uv);
    return frac(52.9829189 * frac(f));
}

float3 PickSamplePoint(float2 uv, float index)
{
    float gn = GradientNoise(uv * g_fSSAODownsample);
    float u = frac(UVRandom(0.0, index + uv.x * 1e-10) + gn) * 2.0 - 1.0;
    float theta = (UVRandom(1.0, index + uv.x * 1e-10) + gn) * 6.28318530718;
    float3 v = float3(CosSin(theta) * sqrt(1.0 - u * u), u);
    float l = sqrt((index + 1.0) / SAMPLE_COUNT) * g_fSSAORadius;
    return v * l;
}

float PositivePow(float base, float power)
{
    return pow(max(abs(base), 1.192092896e-07f), power);
}

float4 PS_SSAO(float2 texCoord : TEXCOORD0) : COLOR0
{
    float3 norm_o = ReconstructNormal(texCoord);
    float depth_o = SampleDepth(texCoord);
    float3 vpos_o = ReconstructViewPos(texCoord, g_mProj);

    float ao = 0.0;
    for (int i = 0; i < SAMPLE_COUNT; i++)
    {
        float3 v_s1 = PickSamplePoint(texCoord, i);

        v_s1 = faceforward(v_s1, -norm_o, v_s1);
        float3 vpos_s1 = vpos_o + v_s1;

        float3 spos_s1 = mul((float3x3)g_mProj, vpos_s1);
        float2 uv_s1_01 = (spos_s1.xy / vpos_s1.z + 1.0) * 0.5;

        float3 vpos_s2 = ReconstructViewPos(uv_s1_01, g_mProj);
        float3 v_s2 = vpos_s2 - vpos_o;

        float a1 = max(dot(v_s2, norm_o) - g_fSSAOBeta * depth_o, 0.0);
        float a2 = dot(v_s2, v_s2) + 1.0e-4;
        ao += a1 / a2;
    }
	
	ao *= g_fSSAORadius;
    ao = PositivePow(ao * g_fSSAOIntensity / SAMPLE_COUNT, g_fSSAOContrast);

    return PackAONormal(ao, norm_o);
}

float4 FragBlur(float2 texCoord : TEXCOORD0, uniform bool bHorizontalBlur) : COLOR0
{
    float2 delta = bHorizontalBlur ? float2(g_vBufferSize.z / g_fSSAODownsample * 2.0, 0.0) : float2(0.0, g_vBufferSize.w / g_fSSAODownsample * 2.0); // / g_fSSAODownsample ?

#if defined(BLUR_HIGH_QUALITY)

    float4 p0  = tex2D(mainSampler, texCoord);
    float4 p1a = tex2D(mainSampler, texCoord - delta);
    float4 p1b = tex2D(mainSampler, texCoord + delta);
    float4 p2a = tex2D(mainSampler, texCoord - delta * 2.0);
    float4 p2b = tex2D(mainSampler, texCoord + delta * 2.0);
    float4 p3a = tex2D(mainSampler, texCoord - delta * 3.2307692308);
    float4 p3b = tex2D(mainSampler, texCoord + delta * 3.2307692308);

    float3 n0 = bHorizontalBlur ? ReconstructNormal(texCoord) : GetPackedNormal(p0);

    float w0  = 0.37004405286;
    float w1a = CompareNormal(n0, GetPackedNormal(p1a)) * 0.31718061674;
    float w1b = CompareNormal(n0, GetPackedNormal(p1b)) * 0.31718061674;
    float w2a = CompareNormal(n0, GetPackedNormal(p2a)) * 0.19823788546;
    float w2b = CompareNormal(n0, GetPackedNormal(p2b)) * 0.19823788546;
    float w3a = CompareNormal(n0, GetPackedNormal(p3a)) * 0.11453744493;
    float w3b = CompareNormal(n0, GetPackedNormal(p3b)) * 0.11453744493;

    float s;
    s  = GetPackedAO(p0)  * w0;
    s += GetPackedAO(p1a) * w1a;
    s += GetPackedAO(p1b) * w1b;
    s += GetPackedAO(p2a) * w2a;
    s += GetPackedAO(p2b) * w2b;
    s += GetPackedAO(p3a) * w3a;
    s += GetPackedAO(p3b) * w3b;

    s /= w0 + w1a + w1b + w2a + w2b + w3a + w3b;
	
#else

    float4 p0  = tex2D(mainSampler, texCoord);
    float4 p1a = tex2D(mainSampler, texCoord - delta * 1.3846153846);
    float4 p1b = tex2D(mainSampler, texCoord + delta * 1.3846153846);
    float4 p2a = tex2D(mainSampler, texCoord - delta * 3.2307692308);
    float4 p2b = tex2D(mainSampler, texCoord + delta * 3.2307692308);

	float3 n0 = bHorizontalBlur ? ReconstructNormal(texCoord) : GetPackedNormal(p0);

    float w0  = 0.2270270270;
    float w1a = CompareNormal(n0, GetPackedNormal(p1a)) * 0.3162162162;
    float w1b = CompareNormal(n0, GetPackedNormal(p1b)) * 0.3162162162;
    float w2a = CompareNormal(n0, GetPackedNormal(p2a)) * 0.0702702703;
    float w2b = CompareNormal(n0, GetPackedNormal(p2b)) * 0.0702702703;

    float s;
    s  = GetPackedAO(p0)  * w0;
    s += GetPackedAO(p1a) * w1a;
    s += GetPackedAO(p1b) * w1b;
    s += GetPackedAO(p2a) * w2a;
    s += GetPackedAO(p2b) * w2b;

    s /= w0 + w1a + w1b + w2a + w2b;

#endif

    return PackAONormal(s, n0);
}

float BlurSmall(sampler2D samp, float2 uv, float2 delta)
{
    float4 p0 = tex2D(samp, uv);
    float4 p1 = tex2D(samp, uv + float2(-delta.x, -delta.y));
    float4 p2 = tex2D(samp, uv + float2( delta.x, -delta.y));
    float4 p3 = tex2D(samp, uv + float2(-delta.x,  delta.y));
    float4 p4 = tex2D(samp, uv + float2( delta.x,  delta.y));

    float3 n0 = GetPackedNormal(p0);

    float w0 = 1.0;
    float w1 = CompareNormal(n0, GetPackedNormal(p1));
    float w2 = CompareNormal(n0, GetPackedNormal(p2));
    float w3 = CompareNormal(n0, GetPackedNormal(p3));
    float w4 = CompareNormal(n0, GetPackedNormal(p4));

    float s;
    s = GetPackedAO(p0) * w0;
    s += GetPackedAO(p1) * w1;
    s += GetPackedAO(p2) * w2;
    s += GetPackedAO(p3) * w3;
    s += GetPackedAO(p4) * w4;

    return s / (w0 + w1 + w2 + w3 + w4);
}

float4 FragComposition(float2 texCoord : TEXCOORD0) : COLOR0
{
    float2 delta = g_vBufferSize.zw / g_fSSAODownsample / g_fSSAODownsample;
    float ao = BlurSmall(mainSampler, texCoord, delta);
    return float4(1.0f - ao, 0.0f, 0.0f, 1.0f);
}

//-----------------------------------------------------------------------------

technique SSAO
{
    pass Occlusion
    {
        PixelShader = compile ps_3_0 PS_SSAO();
    }
	
	pass HorizontalBlur
    {
        PixelShader = compile ps_3_0 FragBlur(true);
    }
	
	pass VerticalBlur
    {
        PixelShader = compile ps_3_0 FragBlur(false);
    }
	
	pass Composition
    {
        PixelShader = compile ps_3_0 FragComposition();
    }
}

#endif // __SSAO__