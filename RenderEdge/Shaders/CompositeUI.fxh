#ifndef __COMPOSITEUI__
#define __COMPOSITEUI__

#include "PostProcessCommon.fxh"

texture g_userInterfaceTexture;
sampler2D userInterfaceSampler = sampler_state
{
	Texture = <g_userInterfaceTexture>;
	MipFilter = None;
	MinFilter = Linear;
    MagFilter = Linear;
	AddressU = Clamp;
    AddressV = Clamp;
};

float4 CompositeUserInterfacePS(float2 texCoord : TEXCOORD0) : COLOR
{
	float4 base = tex2D(mainSampler, texCoord);
	float4 ui = tex2D(userInterfaceSampler, texCoord);
	
	float3 finalColor = lerp(base.rgb, ui.rgb, ui.a);
	
    return float4(finalColor, 1.0f);
}

#endif // __COMPOSITEUI__