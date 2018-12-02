#ifndef __SHADINGMODELS__
#define __SHADINGMODELS__

float3 g_vLightDir;
float3 g_vLightColor;

bool g_bSkyLight;
float g_fSkyLightBlendFactor;
float g_fSkyLightIntensity;
float3 g_vSkyColor;
float3 g_vIndColor;
float3 g_vAmbColor;

#define BURLEY_DIFFUSE 1
bool g_bPBS;
float g_fMaterialRoughness;
float g_fMaterialMetallic;
float g_fMaterialSpecular;
float g_fMaterialTranslucent;

bool g_bEnablePointLight;
int g_iPointLightCount;
float4 g_vPointLightColorAndIntensity[8];
float4 g_vPointLightPosAndInvRadius[8];

bool g_bIBL;
float2 g_vEnvCubemapRotation;
float g_fCubemapBrightness;
bool g_bEnvCubemapSwapYZ;

bool g_bNormalMapping;


texture g_envTexture;
samplerCUBE envMap = sampler_state
{
    Texture = <g_envTexture>;
    MinFilter = Linear;
    MipFilter = Linear;
    MagFilter = Linear;
    AddressU = Clamp;
    AddressV = Clamp;
    AddressW = Clamp;
};

texture g_reflectionTexture;
sampler2D reflectionSampler = sampler_state
{
	Texture = <g_reflectionTexture>;
	MipFilter = NONE;
	MinFilter = LINEAR;
	MagFilter = LINEAR;
	AddressU = BORDER;
    AddressV = BORDER;
};


float3 SampleNormal(sampler2D samp, float2 texCoord, float3 worldNormal, float3 viewDir)
{
	if (g_bNormalMapping)
	{
		float3 normal = normalize(tex2D(samp, texCoord) * 2.0f - 1.0f);
		
		// TODO: use normalize(mul(normal, IN.tangentToWorld));
		return normalize(mul(float3(-normal.x, -normal.y, normal.z), CalcCotangentFrame(worldNormal, -viewDir, texCoord)));
	}
	
	return worldNormal;
}


#if BURLEY_DIFFUSE == 1
float3 Diffuse_Burley2(float3 diffuseColor, float roughness, float NoV, float NoL, float VoH)
{
	float energyBias = lerp (0 , 0.5 , roughness );
	float energyFactor = lerp (1.0 , 1.0 / 1.51 , roughness );
	float FD90 = energyBias + 2.0f * VoH * VoH * roughness;
	float FdV = 1.0f + (FD90 - 1.0f) * Pow5(1.0f - NoV);
	float FdL = 1.0f + (FD90 - 1.0f) * Pow5(1.0f - NoL);
	return NoL * diffuseColor * ((1.0f / PI) * FdV * FdL) * energyFactor;
}

float3 Diffuse_Burley(float3 diffuseColor, float roughness, float NoV, float NoL, float VoH)
{
	float FD90 = 0.5f + 2.0f * VoH * VoH * roughness;
	float FdV = 1.0f + (FD90 - 1.0f) * Pow5(1.0f - NoV);
	float FdL = 1.0f + (FD90 - 1.0f) * Pow5(1.0f - NoL);
	return NoL * diffuseColor * ((1.0f / PI) * FdV * FdL);
}
#endif

float3 Diffuse_Lambert(float3 diffuseColor)
{
	return diffuseColor * (1.0f / PI);
}


float D_GGX(float a2, float NoH)
{
	float d = Pow2(NoH) * (a2 - 1.0f) + 1.0f;
	return a2 * rcp(PI*d*d);
}

float Vis_SmithJointApprox(float a, float NoV, float NoL)
{
	float Vis_SmithV = NoL * (NoV * (1.0f - a) + a);
	float Vis_SmithL = NoV * (NoL * (1.0f - a) + a);
	return 0.5f * rcp(Vis_SmithV + Vis_SmithL);
}

float3 F_Schlick(float3 SpecularColor, float VoH)
{
	float Fc = Pow5(1.0f - VoH);
	return saturate(50.0f * SpecularColor.g) * Fc + (1.0f - Fc) * SpecularColor;
}

//#if 0
float GetBurley12(float roughness, float NoV, float LoH, float NoL)
{
	float F = (1.0f + 2.0f * Pow2(LoH) * roughness) - 1.0f;
	return NoL * (1.0f + F * Pow5(1.0f - NoL)) * (1.0f + F * Pow5(1.0f - NoV));
}

float GetTranslucentNoL(float translucent_scale, float VoL, float NoL)
{
	float translucent = 1.0f - sqrt(1.0f - VoL);
	translucent = (pow(translucent, 3.4f) + 0.15f) * (Pow2(saturate(translucent_scale - 0.4f))) * 2.0f;
	
	NoL = pow(saturate((NoL + translucent_scale) / (1.0f + translucent_scale)), 1.0f + translucent_scale * 2.0f);
	
	return saturate(NoL * (1.0f - translucent) + translucent);
}

float GetGGX(float roughness, float NoV, float NoL, float NoH)
{
	float a = Pow2(roughness * (1.0f - 0.02f) + 0.02f);
	float a2 = Pow2(a);
	float k = a * 0.5f;
	
	float d = Pow2(NoH) * (a2 - 1.0f) + 1.0f + 0.00000001f;
	
	float specular = NoL * a2;
	specular /= (NoL * (1.0f - k) + k) * (NoV * (1.0f - k) + k) * (PI * Pow2(d));
	
	return specular;
}

float3 GetSpecularBRDF(float3 specularColor, float NoV, float LoH, float NoL, float NoH, float roughness)
{
	float fresnel = Pow5(1.0f - saturate(LoH)) * 1 * saturate(0.08f * g_fMaterialSpecular * 25.0f + 1.0f - roughness + g_fMaterialMetallic);
	return (specularColor * (1.0f - fresnel) + fresnel) * GetGGX(roughness, NoV, NoL, NoH);
}

float3 StandardShading3(float3 albedoColor, float3 specularColor, float roughness, float3 normal, float3 lightDir, float3 viewDir)
{
	float3 H = normalize(lightDir + viewDir);
	float NoL = dot(normal, lightDir);
	float NoV = saturate(dot(normal, viewDir));
	float LoV = saturate(dot(lightDir, -viewDir));
	float NoH = saturate(dot(normal, H));
	float LoH = saturate(dot(lightDir, H));
	
	float NoL2 = saturate((-NoL + g_fMaterialTranslucent) / Pow2(1.0f + g_fMaterialTranslucent));
	float Scatter = D_GGX( g_fDebugValue*g_fDebugValue*g_fDebugValue*g_fDebugValue, LoV );
	
	float3 diffuse = albedoColor * GetBurley12(roughness, NoV, LoH, saturate((NoL + g_fMaterialTranslucent) + g_fMaterialTranslucent));
	
	float3 specular = GetSpecularBRDF(specularColor, NoV, LoH, pow(saturate(NoL), 1.0f + g_fMaterialTranslucent), NoH, roughness);
	
	
	return diffuse + specular + albedoColor*Scatter*NoL2;
}

float3 StandardShading2(float3 albedoColor, float3 specularColor, float roughness, float3 normal, float3 lightDir, float3 viewDir)
{
	float3 H = normalize(lightDir + viewDir);
	float NoL = dot(normal, lightDir);
	float NoV = saturate(dot(normal, viewDir));
	float LoV = saturate(dot(lightDir, -viewDir));
	float NoH = saturate(dot(normal, H));
	float LoH = saturate(dot(lightDir, H));
	
	float3 diffuse = albedoColor * GetBurley12(roughness, NoV, LoH, GetTranslucentNoL(g_fMaterialTranslucent, LoV, NoL));
	
	float3 specular = GetSpecularBRDF(specularColor, NoV, LoH, pow(saturate(NoL), 1.0f + g_fMaterialTranslucent), NoH, roughness);
	
	return diffuse + specular;
}

float3 StandardShading(float3 albedoColor, float3 specularColor, float roughness, float3 normal, float3 lightDir, float3 viewDir)
{
	float3 H = normalize(lightDir + viewDir);
	float NoL = saturate(dot(normal, lightDir));
	float NoV = saturate(dot(normal, viewDir));
	float LoV = saturate(dot(lightDir, -viewDir));
	float NoH = saturate(dot(normal, H));
	float LoH = saturate(dot(lightDir, H));
	
	float3 diffuse = albedoColor * GetBurley12(roughness, NoV, LoH, NoL);
	
	float3 specular = GetSpecularBRDF(specularColor, NoV, LoH, NoL, NoH, roughness);
	
	return diffuse + specular;
}
//#endif

float3 StandardShading0(float3 albedoColor, float3 specularColor, float roughness, float3 normal, float3 lightDir, float3 viewDir)
{
	const float a = roughness * roughness;
	const float a2 = a * a;
	
	float NoL = dot(normal, lightDir);
	float NoV = dot(normal, viewDir);
	float LoV = dot(lightDir, viewDir);
	float InvLenH = rsqrt(2.0f + 2.0f * LoV);
	float NoH = saturate((NoL + NoV) * InvLenH);
	float VoH = saturate(InvLenH + InvLenH * LoV);
	NoL = saturate(NoL);
	NoV = saturate(abs(NoV) + 1e-5f);
	
	float D = D_GGX(a2, NoH);
	float Vis = Vis_SmithJointApprox(a, NoV, NoL);
	float3 F = F_Schlick(specularColor, VoH);
	float3 specular = D * Vis * F;
	
#if BURLEY_DIFFUSE == 1
	float3 diffuse = Diffuse_Burley(albedoColor, roughness, NoV, NoL, VoH);
#else
	float3 diffuse = Diffuse_Lambert(albedoColor);
#endif
	
	return (diffuse + specular) * NoL;
}


// ======================================

#define REFLECTION_CAPTURE_ROUGHEST_MIP 3
#define REFLECTION_CAPTURE_ROUGHNESS_MIP_SCALE 1.2

float ComputeReflectionCaptureMipFromRoughness(float Roughness, float CubemapMaxMip)
{
	float LevelFrom1x1 = REFLECTION_CAPTURE_ROUGHEST_MIP - REFLECTION_CAPTURE_ROUGHNESS_MIP_SCALE * log2(Roughness);
	return CubemapMaxMip - 1 - LevelFrom1x1;
}

float3 GetOffSpecularPeakReflectionDir(float3 Normal, float3 ReflectionVector, float Roughness)
{
	float a = Pow2(Roughness);
	return lerp(Normal, ReflectionVector, (1 - a) * (sqrt(1 - a) + a));	
}

float GetSpecularOcclusion(float NoV, float Roughness, float AO)
{
	float a = Pow2(Roughness);
	return saturate(pow(abs(NoV + AO), a) - 1 + AO);
}

float3 EnvBRDFApprox(float3 SpecularColor, float Roughness, float NoV)
{
	const float4 c0 = { -1, -0.0275, -0.572, 0.022 };
	const float4 c1 = { 1, 0.0425, 1.04, -0.04 };
	float4 r = Roughness * c0 + c1;
	float a004 = min(r.x * r.x, exp2(-9.28 * NoV)) * r.x + r.y;
	float2 AB = float2(-1.04, 1.04) * a004 + r.zw;

	AB.y *= saturate(50.0 * SpecularColor.g);

	return SpecularColor * AB.x + AB.y;
}

float3 GetSkyLightReflection(float3 ReflectionVector, float Roughness)
{
	if (g_vEnvCubemapRotation.x != 0.0f && g_vEnvCubemapRotation.y != 1.0f)
		ReflectionVector.xy = float2(dot(ReflectionVector.xy, float2(g_vEnvCubemapRotation.y, -g_vEnvCubemapRotation.x)), dot(ReflectionVector.xy, g_vEnvCubemapRotation));
		
	if (g_bEnvCubemapSwapYZ)
		ReflectionVector.yz = ReflectionVector.zy;
		
	float AbsoluteSpecularMip = ComputeReflectionCaptureMipFromRoughness(Roughness, 8.0f);
	float3 Reflection = texCUBElod(envMap, float4(ReflectionVector, AbsoluteSpecularMip));
	
	return Reflection * g_fCubemapBrightness;
}

float3 ImageBasedLighting(float3 specularColor, float roughness, float3 normal, float3 viewDir, float3 worldPos, float2 screenCoord, float fAO)
{
	float NoV = saturate(dot(normal, viewDir));
	float3 ReflectionVector = 2 * dot(viewDir, normal) * normal - viewDir;
	
	// Parallax Correction
	/*if (g_bParallaxCorrection)
	{
		// Coordinates of the room in the sample map
		const float3 g_vBoxPos = float3(5025.0f, -800.0f, 200.0f);
		const float3 g_vBoxMin = float3(4570.0f, -1212.0f, 12.0f);
		const float3 g_vBoxMax = float3(5555.0f, -434.0f, 390.0f);

		float3 firstPlaneIntersect = (g_vBoxMax - worldPos) / ReflectionVector;
		float3 secondPlaneIntersect = (g_vBoxMin - worldPos) / ReflectionVector;
		float3 furthestPlane = max(firstPlaneIntersect, secondPlaneIntersect);
		float dist = min(min(furthestPlane.x, furthestPlane.y), furthestPlane.z);
		float3 intersectPositionWS = worldPos + ReflectionVector * dist;
		ReflectionVector = intersectPositionWS - g_vBoxPos;
	}*/
	
	ReflectionVector = GetOffSpecularPeakReflectionDir(normal, ReflectionVector, roughness);
	
	float4 SSR = tex2D(reflectionSampler, screenCoord);
	float3 SkyLighting = GetSkyLightReflection(ReflectionVector, roughness);
	
	float blendFactor = SSR.a;
	blendFactor *= GetSpecularOcclusion(NoV, roughness, fAO);
	
	float3 ImageBasedReflections = SkyLighting * blendFactor + SSR.rgb;
	ImageBasedReflections *= EnvBRDFApprox(specularColor, roughness, NoV);
	ImageBasedReflections = -min(-ImageBasedReflections, 0.0f);
	
	return ImageBasedReflections;
}

// ======================================

float3 SkyLight(float3 albedoColor, float3 normal, float fAO)
{
	float3 ambientColor = 0.0f;
	if (g_bSkyLight)
	{
		float skyFactor = saturate(g_fSkyLightBlendFactor + 0.5f * normal.z);
		ambientColor = lerp(g_vIndColor, g_vSkyColor, skyFactor);
	}
	else
		ambientColor = g_vAmbColor;
	
	ambientColor *= albedoColor * g_fSkyLightIntensity * fAO;
	
	return ambientColor;
}

// ======================================

float3 DirectionalLight(float3 albedoColor, float3 specularColor, float roughness, float3 normal, float3 lightDir, float3 viewDir, float3 lightColor, float fShadowTerm)
{
	//float NoL = saturate(dot(normal, lightDir));
	//if (NoL <= 0.0f) return 0.0f;
	
	float3 light = 0.0f;
	if (g_bPBS)
		light = StandardShading(albedoColor, specularColor, roughness, normal, lightDir, viewDir);
	else
		light = albedoColor * saturate(dot(normal, lightDir));
		
	light *= lightColor * fShadowTerm;

	return light;
}

// ======================================


float3 PointLight(float3 albedoColor, float3 specularColor, float roughness, float3 worldPos, float3 normal, float3 viewDir, float3 lightPos, float3 lightColor, float lightIntensity, float lightInvRadius, float fAO)
{
	float3 ToLight = lightPos - worldPos;
	float DistanceSqr = dot(ToLight, ToLight);
	float3 LightDir = ToLight * rsqrt(DistanceSqr);
	//float NoL = saturate(dot(normal, LightDir));
	//if (NoL <= 0.0f) return 0.0f;

	float DistanceAttenuation = 1.0f / (DistanceSqr + 1.0f);
	DistanceAttenuation *= Pow2(saturate(1.0f - Pow2(DistanceSqr * Pow2(lightInvRadius))));
	if (DistanceAttenuation <= 0.0f) return 0.0f;
	
	float3 light = 0.0f;
	if (g_bPBS)
		light = StandardShading(albedoColor, specularColor, roughness, normal, LightDir, viewDir);
	else
		light = albedoColor * saturate(dot(normal, LightDir));
		
	light *= lightColor * lightIntensity * DistanceAttenuation * fAO;

	return light;
}

#endif // __SHADINGMODELS__