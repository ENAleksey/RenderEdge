#ifndef __TAA__
#define __TAA__

#include "PostProcessCommon.fxh"

texture g_historyTexture;
sampler2D historySampler = sampler_state
{
	Texture = <g_historyTexture>;
	MipFilter = NONE;
	MinFilter = LINEAR;
    MagFilter = LINEAR;
	AddressU = Clamp;
    AddressV = Clamp;
};

texture g_velocityTexture;
sampler2D velocitySampler = sampler_state
{
	Texture = <g_velocityTexture>;
	MipFilter = NONE;
	MinFilter = LINEAR;
    MagFilter = LINEAR;
	AddressU = BORDER;
    AddressV = BORDER;
};

float2 g_vJitter;
float3 g_vBlendParameters; // x: static, y: dynamic, z: motion amplification
float g_fSharpness;

#define HALF_MAX_MINUS1 65472.0 // (2 - 2^-9) * 2^15


float Min3(float a, float b, float c)
{
    return min(min(a, b), c);
}

float Luminance2(float3 linearRgb)
{
    return dot(linearRgb, float3(0.2126729, 0.7151522, 0.0721750));
}


float2 GetClosestFragment(float2 texCoord)
{
	const float2 k = g_vBufferSize.zw;

	const float4 neighborhood = float4(
		tex2D(depthSampler, texCoord - k).r,
		tex2D(depthSampler, texCoord + float2(k.x, -k.y)).r,
		tex2D(depthSampler, texCoord + float2(-k.x, k.y)).r,
		tex2D(depthSampler, texCoord + k).r
	);

	float3 result = float3(0.0, 0.0, tex2D(depthSampler, texCoord).r);
	result = lerp(result, float3(-1.0, -1.0, neighborhood.x), step(neighborhood.x, result.z));
	result = lerp(result, float3( 1.0, -1.0, neighborhood.y), step(neighborhood.y, result.z));
	result = lerp(result, float3(-1.0,  1.0, neighborhood.z), step(neighborhood.z, result.z));
	result = lerp(result, float3( 1.0,  1.0, neighborhood.w), step(neighborhood.w, result.z));

	return (texCoord + result.xy * k);
}

float4 ClipToAABB(float4 color, float3 minimum, float3 maximum)
{
	// Note: only clips towards aabb center (but fast!)
	float3 center = 0.5 * (maximum + minimum);
	float3 extents = 0.5 * (maximum - minimum);

	// This is actually `distance`, however the keyword is reserved
	float3 offset = color.rgb - center;

	float3 ts = abs(extents / (offset + 0.0001));
	float t = saturate(Min3(ts.x, ts.y, ts.z));
	color.rgb = center + offset * t;
	return color;
}


struct OutputSolver
{
	float4 destination : COLOR0;
	float4 history     : COLOR1;
};

OutputSolver Solve(float2 motion, float2 texCoord)
{
	const float2 k = g_vBufferSize.zw;
	float2 uv = texCoord - g_vJitter;

	float4 color = tex2D(mainSampler, uv);

	float4 topLeft = tex2D(mainSampler, uv - k * 0.5);
	float4 bottomRight = tex2D(mainSampler, uv + k * 0.5);

	float4 corners = 4.0 * (topLeft + bottomRight) - 2.0 * color;

	// Sharpen output
	color += (color - (corners * 0.166667)) * 2.718282 * g_fSharpness;
	color = clamp(color, 0.0, HALF_MAX_MINUS1);

	// Tonemap color and history samples
	float4 average = (corners + color) * 0.142857;

	float4 history = tex2D(historySampler, texCoord - motion);

	float motionLength = 0;//length(motion);
	float2 luma = float2(Luminance2(average.rgb), Luminance2(color.rgb));
	//float nudge = 4.0 * abs(luma.x - luma.y);
	float nudge = lerp(4.0, 0.25, saturate(motionLength * 100.0)) * abs(luma.x - luma.y);

	float4 minimum = min(bottomRight, topLeft) - nudge;
	float4 maximum = max(topLeft, bottomRight) + nudge;

	// Clip history samples
	history = ClipToAABB(history, minimum.xyz, maximum.xyz);

	// Blend method
	float weight = clamp(
		lerp(g_vBlendParameters.x, g_vBlendParameters.y, motionLength * g_vBlendParameters.z),
		g_vBlendParameters.y, g_vBlendParameters.x
	);

	color = lerp(color, history, weight);
	color = clamp(color, 0.0, HALF_MAX_MINUS1);

	OutputSolver output;
	output.destination = float4(color.rgb, 1.0f);
	output.history = float4(color.rgb, 1.0f);
	return output;
}

OutputSolver FragSolverDilate(float2 texCoord : TEXCOORD0)
{
	//float2 closest = GetClosestFragment(texCoord);
	//float2 motion = tex2D(velocitySampler, closest).xy;
	return Solve(0, texCoord);
}

/* float4 CopyTexturePS(float2 texCoord : TEXCOORD0) : COLOR
{
    return tex2D(mainSampler, texCoord);
}

//float4x4 g_mViewProjectionInverse;
//float4x4 g_mViewProjectionInversePrev;
float4x4 g_mProjPrev;

float4 VelocityPS(float2 texCoord : TEXCOORD0) : COLOR
{
	float3 currentPos = ReconstructViewPos(texCoord, g_mProj);//GetPositionFromDepth(texCoord, g_mViewProjectionInverse);
	float3 previousPos = ReconstructViewPos(texCoord, g_mProjPrev);//GetPositionFromDepth(texCoord, g_mViewProjectionInversePrev);
	
	float2 velocity = (currentPos - previousPos) * 0.5f;
	
	return float4(velocity, 1.0f, 1.0f);
} */


//-----------------------------------------------------------------------------

technique TemporalAA
{
    pass Pass1
    {
        PixelShader = compile ps_3_0 FragSolverDilate();
    }
}

/* technique CopyTexture
{
    pass Pass1
    {
        PixelShader = compile ps_2_0 CopyTexturePS();
    }
}

technique Velocity
{
    pass Pass1
    {
        PixelShader = compile ps_3_0 VelocityPS();
    }
} */

#endif // __TAA__