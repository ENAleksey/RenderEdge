#ifndef __BLOOM__
#define __BLOOM__

#include "PostProcessCommon.fxh"
#include "EyeAdaptation.fxh"


float2 g_vMainTextureSize;
float g_fBloomScale;
float3 g_vBloomColor;

bool g_bBloom;
float g_fBloomIntensity;
float g_fBloomThreshold;

texture g_blurTexture;
sampler blurSampler = sampler_state 
{
	Texture = <g_blurTexture>;
	MipFilter = None;
	MinFilter = Linear;
    MagFilter = Linear;
	AddressU = Border;
    AddressV = Border;
	BorderColor = 0x000000;
};


float3 DownsampleFilter(sampler2D tex, float2 uv, float2 texelSize)
{
    float3 A = tex2D(tex, uv + texelSize * float2(-1.0f, -1.0f));
    float3 B = tex2D(tex, uv + texelSize * float2( 0.0f, -1.0f));
    float3 C = tex2D(tex, uv + texelSize * float2( 1.0f, -1.0f));
    float3 D = tex2D(tex, uv + texelSize * float2(-0.5f, -0.5f));
    float3 E = tex2D(tex, uv + texelSize * float2( 0.5f, -0.5f));
    float3 F = tex2D(tex, uv + texelSize * float2(-1.0f,  0.0f));
    float3 G = tex2D(tex, uv);
    float3 H = tex2D(tex, uv + texelSize * float2( 1.0f,  0.0f));
    float3 I = tex2D(tex, uv + texelSize * float2(-0.5f,  0.5f));
    float3 J = tex2D(tex, uv + texelSize * float2( 0.5f,  0.5f));
    float3 K = tex2D(tex, uv + texelSize * float2(-1.0f,  1.0f));
    float3 L = tex2D(tex, uv + texelSize * float2( 0.0f,  1.0f));
    float3 M = tex2D(tex, uv + texelSize * float2( 1.0f,  1.0f));

    float2 div = float2(0.125f, 0.0625f);

    float3 o = (D + E + I + J) * div.x;
    o += (A + B + G + F) * div.y;
    o += (B + C + H + G) * div.y;
    o += (F + G + L + K) * div.y;
    o += (G + H + M + L) * div.y;
	
	//float2 newUV = uv;
	//if(newUV.x < 0.0 || newUV.x > 1.0 || newUV.y < 0.0 || newUV.y > 1.0) o = 0.0f;
	
    return o;
}

float3 UpsampleFilter(sampler2D tex, float2 uv, float2 texelSize, float sampleScale)
{
    float4 d = texelSize.xyxy * float4(1.0f, 1.0f, -1.0f, 0.0f) * sampleScale;

    float3 s;
    s =  tex2D(tex, uv - d.xy);
    s += tex2D(tex, uv - d.wy) * 2.0f;
    s += tex2D(tex, uv - d.zy);

    s += tex2D(tex, uv + d.zw) * 2.0f;
    s += tex2D(tex, uv)        * 4.0f;
    s += tex2D(tex, uv + d.xw) * 2.0f;

    s += tex2D(tex, uv + d.zy);
    s += tex2D(tex, uv + d.wy) * 2.0f;
    s += tex2D(tex, uv + d.xy);

    return s * 0.0625f;
}

float4 BrightPassPS(float2 texCoord : TEXCOORD0) : COLOR
{
	if (IsOutsideViewport(texCoord))
		discard;
		
	float3 linearColor = DownsampleFilter(mainSampler, texCoord, g_vMainTextureSize);
	linearColor = min(float3(256 * 256, 256 * 256, 256 * 256), linearColor);
	
	float exposureScale = 1.0f;
	if (g_bAutoExposure)
		exposureScale = tex2D(exposureSampler, float2(0.5f, 0.5f)).r;

	float totalLuminance = Luminance(linearColor) * exposureScale;
	float bloomLuminance = totalLuminance - g_fBloomThreshold;
	float bloomAmount = saturate(bloomLuminance / 2.0f);
	
	linearColor *= bloomAmount;
	
    return float4(linearColor, 1.0f);
}

float4 DownsamplePS(float2 texCoord : TEXCOORD0) : COLOR
{
    return float4(DownsampleFilter(mainSampler, texCoord, g_vMainTextureSize), 1.0f);
}

float4 UpsamplePS(float2 texCoord : TEXCOORD0) : COLOR
{
	float3 bloom = UpsampleFilter(mainSampler, texCoord, g_vMainTextureSize, g_fBloomScale);
	float3 color = tex2D(blurSampler, texCoord);
	
    return float4(color + bloom, 1.0f);
}

//-----------------------------------------------------------------------------

technique Bloom
{
	pass BrightPass
    {
        PixelShader = compile ps_2_0 BrightPassPS();
    }
	
    pass Downsample
    {
        PixelShader = compile ps_2_0 DownsamplePS();
    }

	pass Upsample
    {
        PixelShader = compile ps_2_0 UpsamplePS();
    }
}

#endif // __BLOOM__