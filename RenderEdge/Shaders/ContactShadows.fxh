#ifndef __CONTACTSHADOWS__
#define __CONTACTSHADOWS__

#include "PostProcessCommon.fxh"
#include "Random.fxh"

float3 g_vLightDir;
float g_fContactShadowsRayLength;
float g_fContactShadowsDownsample;

/*
float ShadowRayCast2(float3 RayOriginTranslatedWorld, float3 RayDirection, float RayLength, int NumSteps, float StepOffset)
{
	float4 RayStartClip	= float4( RayOriginTranslatedWorld, 1 );
	float4 RayDirClip	= mul( float4( RayDirection * RayLength, 0 ), g_mView);
	float4 RayEndClip	= RayStartClip + RayDirClip;

	float3 RayStartScreen = RayStartClip.xyz;// / RayStartClip.w;
	float3 RayEndScreen = RayEndClip.xyz;// / RayEndClip.w;
	
	float3 RayStepScreen = RayEndScreen - RayStartScreen;

	float3 RayStartUVz = float3( GetUV(RayStartScreen), RayStartScreen.z );
	float3 RayStepUVz = float3( GetUV(RayStepScreen), RayStepScreen.z );

	float4 RayDepthClip	= RayStartClip + float4( 0, 0, RayLength, 0 );
	float3 RayDepthScreen = RayDepthClip.xyz;// / RayDepthClip.w;

	const float Step = 1.0 / NumSteps;

	// *2 to get less morie pattern in extreme cases, larger values make object appear not grounded in reflections
	const float CompareTolerance = abs( RayDepthScreen.z - RayStartScreen.z ) * Step * 2;

	float SampleTime = StepOffset * Step + Step;

	float FirstHitTime = -1.0;

	[unroll]
	for( int i = 0; i < NumSteps; i++ )
	{
		float3 SampleUVz = RayStartUVz + RayStepUVz * SampleTime;
		float SampleDepth = SampleLinearDepth(SampleUVz.xy);

		float DepthDiff = SampleUVz.z - SampleDepth;
		bool Hit = abs( DepthDiff + CompareTolerance ) < CompareTolerance;

		FirstHitTime = (Hit && FirstHitTime < 0.0) ? SampleTime : FirstHitTime;

		SampleTime += Step;
	}

	float Shadow = FirstHitTime > 0.0 ? 1.0 : 0.0;

	// Off screen masking
	float2 Vignette = max(6.0 * abs(RayStartScreen.xy + RayStepScreen.xy * FirstHitTime) - 5.0, 0.0);
	Shadow *= saturate( 1.0 - dot( Vignette, Vignette ) );

	return 1 - Shadow;
}

float ShadowRayCast(float3 RayOriginTranslatedWorld, float3 RayDirection, float RayLength, int NumSteps, float StepOffset)
{
	float4 RayStartClip	= mul( float4( RayOriginTranslatedWorld, 1 ), g_mProj);
	float4 RayDirClip	= mul( float4( RayDirection * RayLength, 0 ), g_mViewProj);
	float4 RayEndClip	= RayStartClip + RayDirClip;

	float3 RayStartScreen = RayStartClip.xyz / RayStartClip.w;
	float3 RayEndScreen = RayEndClip.xyz / RayEndClip.w;
	
	float3 RayStepScreen = RayEndScreen - RayStartScreen;

	float3 RayStartUVz = float3( RayStartScreen.xy * g_vScreenScaleBias.xy + g_vScreenScaleBias.zw, RayStartScreen.z );
	float3 RayStepUVz = float3( RayStepScreen.xy * g_vScreenScaleBias.xy, RayStepScreen.z );

	float4 RayDepthClip	= RayStartClip + mul(float4( 0, 0, RayLength, 0 ), g_mProj);
	float3 RayDepthScreen = RayDepthClip.xyz / RayDepthClip.w;

	const float Step = 1.0 / NumSteps;

	// *2 to get less morie pattern in extreme cases, larger values make object appear not grounded in reflections
	const float CompareTolerance = abs( RayDepthScreen.z - RayStartScreen.z ) * Step * 2;

	float SampleTime = StepOffset * Step + Step;

	float FirstHitTime = -1.0;

	[unroll]
	for( int i = 0; i < NumSteps; i++ )
	{
		float3 SampleUVz = RayStartUVz + RayStepUVz * SampleTime;
		float SampleDepth = SampleLinearDepth(SampleUVz.xy);

		float DepthDiff = SampleUVz.z - SampleDepth;
		bool Hit = abs( DepthDiff + CompareTolerance ) < CompareTolerance;

		FirstHitTime = (Hit && FirstHitTime < 0.0) ? SampleTime : FirstHitTime;

		SampleTime += Step;
	}

	float Shadow = FirstHitTime > 0.0 ? 1.0 : 0.0;

	// Off screen masking
	float2 Vignette = max(6.0 * abs(RayStartScreen.xy + RayStepScreen.xy * FirstHitTime) - 5.0, 0.0);
	Shadow *= saturate( 1.0 - dot( Vignette, Vignette ) );

	return 1 - Shadow;
}
*/



float3 ViewSpace(float2 uv, float z)
{
	float2 uvScale = float2(-g_mProjInv[0][0], -g_mProjInv[1][1]);
    float linearZ = g_vCameraClipPlanes.z * g_vCameraClipPlanes.w / (z * (g_vCameraClipPlanes.w - g_vCameraClipPlanes.z) - g_vCameraClipPlanes.w);
	return float3(uv * uvScale, 1.0) * linearZ;
}

float3 ClipSpace(float3 coord)
{
	float2 uvScale = float2(-g_mProjInv[0][0], -g_mProjInv[1][1]);
	float encodedZ = (g_vCameraClipPlanes.z * g_vCameraClipPlanes.w / coord.z + g_vCameraClipPlanes.w) / (g_vCameraClipPlanes.w - g_vCameraClipPlanes.z);
	return float3(coord.xy / (coord.z * uvScale), encodedZ);
}



float ShadowRayCast1(float2 texCoord, float3 RayDirection, float RayLength, int NumSteps, float StepOffset)
{
	float4 screenScaleBias = g_vScreenScaleBias;
	screenScaleBias.y *= -1.0f;
	
    float3 lightDirView = mul(float4(RayDirection * RayLength, 0.0f), g_mView);

    float3 rayOriginView = ViewSpace((texCoord - screenScaleBias.zw) / (screenScaleBias.xy), SampleNonLinearDepth(texCoord));
	float3 rayStartClip = ClipSpace(rayOriginView);
	float3 rayEndClip = ClipSpace(rayOriginView + lightDirView);
	float3 rayStepClip = rayEndClip - rayStartClip;
	
	float4 RayStartClip = mul(float4(rayOriginView, 1), g_mProj);
	float3 RayStartScreen = RayStartClip.xyz / RayStartClip.w;
	
	float3 RayStartUVz = float3(rayStartClip.xy * screenScaleBias.xy + screenScaleBias.zw, rayStartClip.z);
	float3 RayStepUVz = float3(rayStepClip.xy * screenScaleBias.xy, rayStepClip.z);
	
	float4 RayDepthClip	= RayStartClip + mul(float4(0, 0, RayLength, 0), g_mProj);
	float3 RayDepthScreen = RayDepthClip.xyz / RayDepthClip.w;
	
	const float Step = 1.0 / NumSteps;
	
	const float CompareTolerance = abs(RayDepthScreen.z - RayStartScreen.z) * Step * 2;
	
	float SampleTime = StepOffset * Step + Step;

	float FirstHitTime = -1.0;
	
	[unroll]
	for (uint i = 0; i < NumSteps; ++i)
	{
		float3 sampleUVz = RayStartUVz + RayStepUVz * SampleTime;
		float sampleDepth = SampleNonLinearDepth(sampleUVz.xy);
		
		float depthDiff = sampleDepth - sampleUVz.z;
		bool Hit = abs(depthDiff + CompareTolerance) < CompareTolerance;
		
		FirstHitTime = (Hit && FirstHitTime < 0.0) ? SampleTime : FirstHitTime;

		SampleTime += Step;
	}

	float Shadow = FirstHitTime > 0.0 ? 1.0 : 0.0;

	float2 Vignette = max(6.0 * abs(RayStartScreen.xy + RayStartScreen.xy * FirstHitTime) - 5.0, 0.0);
	Shadow *= saturate(1.0 - dot(Vignette, Vignette));

	return 1 - Shadow;
}


float ShadowRayCast(float3 RayOriginTranslatedWorld, float3 RayDirection, float RayLength, int NumSteps, float StepOffset)
{
    float4 RayStartClip = mul(float4(RayOriginTranslatedWorld, 1), g_mViewProj);
    float4 RayDirClip = mul(float4(RayDirection * RayLength, 0), g_mViewProj);
    float4 RayEndClip = RayStartClip + RayDirClip; // mul(float4(RayOriginTranslatedWorld + RayDirection * RayLength, 0), g_mViewProj);

    float3 RayStartScreen = RayStartClip.xyz / RayStartClip.w;
    float3 RayEndScreen = RayEndClip.xyz / RayEndClip.w;
	
    float3 RayStepScreen = RayEndScreen - RayStartScreen;

    float3 RayStartUVz = float3(RayStartScreen.xy * g_vScreenScaleBias.xy + g_vScreenScaleBias.wz, RayStartScreen.z);
    float3 RayStepUVz = float3(RayStepScreen.xy * g_vScreenScaleBias.xy, RayStepScreen.z);

    float4 RayDepthClip = RayStartClip + mul(float4(0, 0, RayLength, 0), g_mProj);
    float3 RayDepthScreen = RayDepthClip.xyz / RayDepthClip.w;

    const float Step = 1.0 / NumSteps;

	// *2 to get less morie pattern in extreme cases, larger values make object appear not grounded in reflections
    const float CompareTolerance = abs(RayDepthScreen.z - RayStartScreen.z) * Step * 2;

    float SampleTime = StepOffset * Step + Step;

    float FirstHitTime = -1.0;

    [unroll]
    for (int i = 0; i < NumSteps; i++)
    {
        float3 SampleUVz = RayStartUVz + RayStepUVz * SampleTime;
        float SampleDepth = SampleNonLinearDepth(SampleUVz.xy).r;

        float DepthDiff = SampleUVz.z - SampleDepth;
        bool Hit = abs(DepthDiff + CompareTolerance) < CompareTolerance;

        FirstHitTime = (Hit && FirstHitTime < 0.0) ? SampleTime : FirstHitTime;

        SampleTime += Step;
    }

    float Shadow = FirstHitTime > 0.0 ? 1.0 : 0.0;

	// Off screen masking
    float2 Vignette = max(6.0 * abs(RayStartScreen.xy + RayStepScreen.xy * FirstHitTime) - 5.0, 0.0);
    Shadow *= saturate(1.0 - dot(Vignette, Vignette));

    return 1 - Shadow;
}



float4 ContactShadowsPS(float2 texCoord : TEXCOORD0) : COLOR0
{
	float SceneDepth = CalcSceneDepth(texCoord);
	float Dither = InterleavedGradientNoise(texCoord * g_vBufferSize.xy * g_fContactShadowsDownsample, g_iFrameIndexMod8);
    float StepOffset = Dither - 0.5;
	
    float Shadow = ShadowRayCast1(texCoord, normalize(g_vLightDir), g_fContactShadowsRayLength * SceneDepth, 8, StepOffset);
    
    //float4x4 ScreenToTranslatedWorld = float4x4(
	//	1, 0, 0, 0,
	//	0, 1, 0, 0,
	//	0, 0, g_mProj[2][2], 1,
	//	0, 0, g_mProj[3][2], 0) * (g_mProjInv * g_mViewInv);

    //float3 ScreenVector = mul(float4(OutPosition.xy, 1, 0), ScreenToTranslatedWorld).xyz;
    //float3 WorldPosition = ScreenVector * SceneDepth + g_vCameraPos;
    //float3 ViewPosition = ViewSpace(texCoord * 2.0 - 1.0, SampleNonLinearDepth(texCoord));
    //float Shadow = ShadowRayCast(WorldPosition - g_vCameraPos, normalize(g_vLightDir), g_fContactShadowsRayLength * SceneDepth, 8, StepOffset);
	
	return float4(Shadow, 0, 0, 0);
}

//-----------------------------------------------------------------------------

technique ContactShadows
{
    pass p0
    {
        PixelShader = compile ps_3_0 ContactShadowsPS();
    }
}

#endif // __CONTACTSHADOWS__