#ifndef __POSTPROCESSCOMMON__
#define __POSTPROCESSCOMMON__

//#pragma warning (disable : 3205) // conversion of larger type to smaller
//#pragma warning (disable : 3568) // unknown pragma ignored
//#pragma warning (disable : 3571) // "pow(f,e) will not work for negative f"; however in majority of our calls to pow we know f is not negative
//#pragma warning (disable : 3206) // implicit truncation of vector type

static const float PI = 3.1415926535897932f;

float4x4 g_mProj;
float4x4 g_mView;
float4x4 g_mViewInv;
float4x4 g_mProjInv;
float4x4 g_mInvViewProj;
float4x4 g_mViewProj;

float g_fTimer;
float4 g_vCameraClipPlanes; // x: 1-far/near,  y: far/near,  z: near,  w: far
float3 g_vCameraPos;

float4 g_vBufferSize;
float4 g_vViewportSize;
float4 g_vViewportRect;
float4 g_vScreenScaleBias;

int g_iFrameIndexMod8;
float2 g_vInvDeviceZToWorldZTransform;


texture g_mainTexture;
sampler2D mainSampler = sampler_state
{
	Texture = <g_mainTexture>;
	MipFilter = None;
	MinFilter = Linear;
    MagFilter = Linear;
	AddressU = Clamp;
    AddressV = Clamp;
	BorderColor = 0x000000;
};

texture g_depthTexture;
sampler2D depthSampler = sampler_state
{
	Texture = <g_depthTexture>;
	MipFilter = None;
	MinFilter = Linear;
    MagFilter = Linear;
	BorderColor = 0xFFFFFF;
	AddressU = Border;
    AddressV = Border;
};


float2 ScreenToUV(float2 screenPos)
{
	return screenPos * g_vScreenScaleBias.xy + g_vScreenScaleBias.zw;
}

float2 UVToScreen(float2 uv)
{
	return (uv - g_vScreenScaleBias.zw) / g_vScreenScaleBias.xy;
}

float2 ViewportToScreen(float2 uv)
{
	return uv * g_vViewportSize.xy * g_vBufferSize.zw + g_vViewportRect.xy;
}

bool IsOutsideViewport(float2 texCoord)
{
	return texCoord.x < g_vViewportRect.x || texCoord.x > g_vViewportRect.z || texCoord.y < g_vViewportRect.y || texCoord.y > g_vViewportRect.w;
}

float Linear01Depth(float z)
{
    return 1.0f / (z * g_vCameraClipPlanes.x + g_vCameraClipPlanes.y);
}

float Linear01DepthFromNear(float z)
{
	return 1.0f / (g_vCameraClipPlanes.x + g_vCameraClipPlanes.y / z);
}

float SampleNonLinearDepth(float2 uv)
{
    return tex2Dlod(depthSampler, float4(uv, 0, 0)).x;
}

float SampleLinearDepth(float2 uv)
{
    return Linear01Depth(tex2Dlod(depthSampler, float4(uv, 0, 0)).x);
}

float CalcSceneDepth(float2 texCoord)
{
	float DeviceZ = SampleNonLinearDepth(texCoord);
	return 1.0f / (DeviceZ * g_vInvDeviceZToWorldZTransform[0] - g_vInvDeviceZToWorldZTransform[1]);
}

float Pow2(float x)
{
	return x * x;
}

float FastSign(float x)
{
    return saturate(x * 3.402823466e+38 + 0.5) * 2.0 - 1.0;
}

float3 Luminance(float3 linearColor)
{
	return dot(linearColor, float3(0.3f, 0.59f, 0.11f));
}

float4 UnwrappedTexture3DSample(sampler2D Sampler, float3 UVW, float Size)
{
	float IntW = floor(UVW.z * Size - 0.5);
	float FracW = UVW.z * Size - 0.5 - IntW;

	float U = (UVW.x + IntW) / Size;
	float V = UVW.y;

	float4 RG0 = tex2D(Sampler, float2(U, V));
	float4 RG1 = tex2D(Sampler, float2(U + 1.0f / Size, V));

	return lerp(RG0, RG1, FracW);
}

#endif // __POSTPROCESSCOMMON__