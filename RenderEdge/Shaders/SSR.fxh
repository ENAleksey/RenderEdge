#ifndef __SSR__
#define __SSR__

#include "PostProcessCommon.fxh"
#include "SSAO.fxh"
#include "Random.fxh"

float g_fSSRJitter;
float g_fSSRMinRayStep;
float g_fSSRRayStep;
float g_fSSRRayhitThreshold;
float g_fSSRDepthThreshold;

#define MAX_STEPS 16
#define BINARY_SEARCH_STEPS 16


float2 GetUV(float3 position)
{
	//float4 pVP = mul(float4(position, 1.0f), g_mProj);
	//return pVP.xy / pVP.w * g_vScreenScaleBias.xy * float2(1, -1) + g_vScreenScaleBias.zw;
	
	float2 uvScale = float2(g_mProjInv[0][0], g_mProjInv[1][1]);
	return position.xy / (position.z * uvScale) * g_vScreenScaleBias.xy * float2(1, -1) + g_vScreenScaleBias.zw;
}

float GetDepthDiff(float3 vHitCoord)
{
	float2 vProjectedCoord = GetUV(vHitCoord).xy;
    float fDepth = SampleLinearDepth(vProjectedCoord) /* * g_vCameraClipPlanes.w */;
    float fDepthDiff = vHitCoord.z - fDepth;
	return fDepthDiff;
}


/* float3 BinarySearch(float3 vDir, inout float3 vHitCoord)
{
	[loop]
	for (int i = 0; i < BINARY_SEARCH_STEPS; i++)
	{
		float2 vProjectedCoord = GetUV(vHitCoord);
		float fDepth = SampleDepth(vProjectedCoord.xy);
		float fDepthDiff = fDepth - vHitCoord.z;

		vDir *= 0.5f;
		if (fDepthDiff > 0.0f)
			vHitCoord += vDir;
		else if (fDepthDiff < 0.0f)
			vHitCoord -= vDir;
	}

	float2 vProjectedCoord = GetUV(vHitCoord);
	float fDepth = SampleDepth(vProjectedCoord.xy);
	float fDepthDiff = fDepth - vHitCoord.z;

	return float3(vProjectedCoord.xy, 1.0f);
}

float3 RayMarch(float3 vDir, inout float3 vHitCoord)
{
    float2 vProjectedCoord;
	float fDepth;
	
	//float2 vProjectedCoordSky;

	//vDir *= g_fSSRRayStep * 0.1f;

	[loop]
	for (int i = 0; i < MAX_STEPS; i++)
	{
		vHitCoord += vDir;

		vProjectedCoord = GetUV(vHitCoord);
		fDepth = SampleDepth(vProjectedCoord.xy);
		[branch]
		if (fDepth >= 0.99999f) // ?
		{
			//vProjectedCoordSky = vProjectedCoord;
            continue;
		}
		float fDepthDiff = fDepth - vHitCoord.z;

		[branch]
		if (vDir.z - fDepthDiff < g_fSSRDepthThreshold)
		{
			[branch]
			if (fDepthDiff <= 0.0f)
				return BinarySearch(vDir, vHitCoord);
		}
	}
	
	return float3(vProjectedCoord, 1.0f);
}  */

/*float4 RayCastCheap(float3 R, float SceneDepth, float3 PositionTranslatedWorld, float StepOffset)
{
	float4 RayStartClip	= mul( float4( PositionTranslatedWorld, 1 ), g_mViewProj );
	float4 RayEndClip	= mul( float4( PositionTranslatedWorld + R * SceneDepth, 1 ), g_mViewProj );

	float3 RayStartScreen = RayStartClip.xyz / RayStartClip.w;
	float3 RayEndScreen = RayEndClip.xyz / RayEndClip.w;

	// Normalize 2D length
	float3 RayStepScreen = ( RayEndScreen - RayStartScreen ) / length( RayEndScreen.xy - RayStartScreen.xy );
	RayStepScreen *= 0.75;

	float3 RayStartUVz = float3( RayStartScreen.xy * g_vScreenScaleBias.xy + g_vScreenScaleBias.wz, RayStartScreen.z );
	float3 RayStepUVz = float3( RayStepScreen.xy * g_vScreenScaleBias.xy, RayStepScreen.z );
	
	const float Step = 1.0 / (4 + 1);

	// *2 to get less morie pattern in extreme cases, larger values make object appear not grounded in reflections
	const float CompareTolerance = abs( RayStepUVz.z ) * Step * 2;

	// Vectorized to group fetches
	float4 SampleTime = ( StepOffset + float4( 1, 2, 3, 4 ) ) * Step;
	float4 SampleUV0 = RayStartUVz.xyxy + RayStepUVz.xyxy * SampleTime.xxyy;
	float4 SampleUV1 = RayStartUVz.xyxy + RayStepUVz.xyxy * SampleTime.zzww;
	float4 SampleZ   = RayStartUVz.zzzz + RayStepUVz.zzzz * SampleTime;

	float4 SampleDepth = 0;
	SampleDepth.x = SampleNonLinearDepth(SampleUV0.xy);
	SampleDepth.y = SampleNonLinearDepth(SampleUV0.zw);
	SampleDepth.z = SampleNonLinearDepth(SampleUV1.xy);
	SampleDepth.w = SampleNonLinearDepth(SampleUV1.zw);

	float4 DepthDiff = SampleZ - SampleDepth;
	float4 IntersectTime = ( SampleDepth - RayStartUVz.zzzz ) / RayStepUVz.zzzz;
		
	bool4 Hit = abs( DepthDiff + CompareTolerance ) < CompareTolerance;
	
	// If hit set to intersect time. If missed set to 1, beyond end of ray
	float4 HitTime = Hit ? IntersectTime : 1;

	// Take closest hit
	HitTime.xy = min( HitTime.xy, HitTime.zw );
	float MinHitTime = min( HitTime.x, HitTime.y );

	float3 HitUVz = RayStartUVz + RayStepUVz * MinHitTime;

	[branch]
	if( MinHitTime == 1 && RayStepUVz.z < 0 )
	{
		float4 RayInfClip	= mul( float4( PositionTranslatedWorld + R * 2000000, 1 ), g_mProj );
		float3 RayInfScreen = RayInfClip.xyz / RayInfClip.w;
		float3 RayInfUVz = float3( RayInfScreen.xy * float2( 0.5, -0.5 ) + 0.5, RayInfScreen.z );

		HitUVz = RayInfUVz;
		MinHitTime = 0.5;
	}

	return float4( HitUVz, MinHitTime );
}*/



float3 SSRBinarySearch(float3 vDir, inout float3 vHitCoord)
{
    for (int i = 0; i < BINARY_SEARCH_STEPS; i++)
    {
		[branch]
        if (GetDepthDiff(vHitCoord) <= 0.0f)
            vHitCoord += vDir;

        vDir *= 0.5f;
        vHitCoord -= vDir;
    }
	
	float2 vProjectedCoord = GetUV(vHitCoord).xy;
    float fDepth = SampleLinearDepth(vProjectedCoord.xy) /* * g_vCameraClipPlanes.w */;
    float fDepthDiff = vHitCoord.z - fDepth;

    return float3(vProjectedCoord.xy, abs(fDepthDiff) < g_fSSRRayhitThreshold ? 1.0f : 0.0f);
}

float3 SSRRayMarch(float3 vDir, inout float3 vHitCoord)
{
    for (int i = 0; i < MAX_STEPS; i++)
    {
        vHitCoord += vDir;

		[branch]
        if (GetDepthDiff(vHitCoord) > 0.0f)
            return SSRBinarySearch(vDir, vHitCoord);

        vDir *= 1.18f; // g_fSSRRayStep;
    }

    return float3(0.0f, 0.0f, 0.0f);
}



float3 getPosition(float2 texCoord)
{
    float z = SampleNonLinearDepth(texCoord);
    float x = texCoord.x * 2.0f - 1.0f;
    float y = (1.0 - texCoord.y) * 2.0f - 1.0f;
    float4 position_s = float4(x, y, z, 1.0f);
    float4 position_v = mul(position_s, g_mInvViewProj);
    return position_v.xyz / position_v.w;
}

float3 ComputeWorldSpacePosition2(float2 positionNDC)
{
	//positionNDC.y = 1.0f - positionNDC.y;
	float deviceDepth = SampleNonLinearDepth(positionNDC);
    float4 positionCS  = float4(positionNDC * 2.0 - 1.0, deviceDepth, 1.0);
	//positionCS.y = -positionCS.y;
    float4 hpositionWS = mul(g_mInvViewProj, positionCS); // (projMatrix * viewMatrix).inv
	//float4 hpositionWS = mul(positionCS, mul(g_mProj, g_mView));
    return hpositionWS.xyz / hpositionWS.w;
}

float3 VisualizePosition(float3 pos, float2 texCoord)
    {
        const float grid = 5;
        const float width = 3;

        pos *= grid;

        // Detect borders with using derivatives.
        float3 fw = fwidth(pos);
        float3 bc = saturate(width - abs(1 - 2 * frac(pos)) / fw);

        // Frequency filter
        float3 f1 = smoothstep(1 / grid, 2 / grid, fw);
        float3 f2 = smoothstep(2 / grid, 4 / grid, fw);
        bc = lerp(lerp(bc, 0.5, f1), 0, f2);

        // Blend with the source color.
        float3 c = tex2D(mainSampler, texCoord);
        c.rgb = toLinear(lerp(LinearToSrgb(c.rgb), bc, 0.5f));

        return c;
    }

float4 PS_SSR(float2 texCoord : TEXCOORD0) : COLOR0
{
	//float3 worldPos = ComputeWorldSpacePosition2(texCoord);
	//return float4(worldPos, 1.0f);
	//return float4(VisualizePosition(worldPos, texCoord), 1.0f);
				
				
    float3 viewPos = ReconstructViewPos(texCoord, g_mProj);
	float3 viewNormal = ReconstructNormal(texCoord);
	float3 reflectDir = normalize(reflect(normalize(viewPos), normalize(viewNormal)));

	float3 hitPos = viewPos;
	
	float Dither = InterleavedGradientNoise(texCoord * g_vBufferSize.xy, g_iFrameIndexMod8);
	float StepOffset = Dither - 0.5;
	
	float Step = StepOffset * g_fSSRRayStep + g_fSSRRayStep;
	
	float3 vCoords = SSRRayMarch(Step * reflectDir, hitPos);
	
	float2 ScreenPos = UVToScreen(vCoords.xy);
	float2 Vignette = saturate(abs(ScreenPos) * 5 - 4);
	float ReflectionMultiplier = saturate(reflectDir.z) * saturate(1.0f - dot(Vignette, Vignette)) * vCoords.z;
	
	float3 reflectionColor = tex2Dlod(mainSampler, float4(vCoords.xy, 0.0f, 0.0f)).rgb * ReflectionMultiplier;
	reflectionColor = -min(-reflectionColor, 0.0f);
	
	//float3 viewDir = normalize(viewPos);
	//float3 WorldPosition = viewDir * CalcSceneDepth(texCoord) + g_vCameraPos;
	
	return float4(reflectionColor, 1.0f - ReflectionMultiplier);
}

//-----------------------------------------------------------------------------

technique SSR
{
    pass p0
    {
        PixelShader = compile ps_3_0 PS_SSR();
    }
}

#endif // __SSR__