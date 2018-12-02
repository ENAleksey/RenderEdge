//-----------------------------------------------------------------------------
// Globals
//-----------------------------------------------------------------------------

#include "Common.fxh"
#include "Shading.fxh"
#include "ShadowCommon.fxh"
#include "GammaCorrection.fxh"
#include "Fog.fxh"

float4x4 g_mWorld;
float4x4 g_mWorldViewProjection;
float4x4 g_mTextureTransform;

bool g_bTexture;
bool g_bVertexColor;
bool g_bMaterialColor;
bool g_bVertexColorSRGB;
bool g_bMaterialUnshaded;
bool g_bMaterialUnfogged;
float4 g_vMaterialEmissive;
float4 g_vMaterialDiffuse;

bool g_bContactShadows;
bool g_bSSAO;
bool g_bLinearOutput;


//-----------------------------------------------------------------------------
// Textures
//-----------------------------------------------------------------------------

sampler2D colorMap : register(s0);

texture g_albedoTexture;
sampler2D albedoSampler = sampler_state
{
	Texture = <g_albedoTexture>;
    MagFilter = Anisotropic;
    MinFilter = Anisotropic;
    MipFilter = Anisotropic;
    MaxAnisotropy = 16;
	AddressU = Wrap;
    AddressV = Wrap;
};

texture g_normalTexture;
sampler2D normalSampler = sampler_state
{
    Texture = <g_normalTexture>;
    MagFilter = Anisotropic;
    MinFilter = Anisotropic;
    MipFilter = Anisotropic;
    MaxAnisotropy = 16;
	AddressU = Wrap;
    AddressV = Wrap;
};

texture g_aoTexture;
sampler2D aoSampler = sampler_state
{
	Texture = <g_aoTexture>;
	MipFilter = None;
	MinFilter = Linear;
	MagFilter = Linear;
	BorderColor = 0xFFFFFF;
	AddressU = Border;
    AddressV = Border;
};

texture g_contactShadowsTexture;
sampler2D contactShadowsSampler = sampler_state
{
	Texture = <g_contactShadowsTexture>;
	MipFilter = None;
	MinFilter = Linear;
	MagFilter = Linear;
	BorderColor = 0xFFFFFF;
	AddressU = Border;
    AddressV = Border;
};


//-----------------------------------------------------------------------------
// Vertex Shaders
//-----------------------------------------------------------------------------

struct STANDARD_IN
{
	float3 position		:  POSITION;
	float2 texCoord		:  TEXCOORD0;
	float3 normal		:  NORMAL;
	float4 vertexColor	:  COLOR;
};

struct STANDARD_OUT
{
	float4 position			:  POSITION;
	float2 texCoord			:  TEXCOORD0;
	float3 worldNormal		:  TEXCOORD1;
	float3 worldPos			:  TEXCOORD2;
	float4 vertexPos		:  TEXCOORD3;
	float4 vertexColor		:  COLOR;
};

STANDARD_OUT StandardVS(STANDARD_IN IN)
{
	STANDARD_OUT OUT;

	OUT.position = mul(float4(IN.position, 1.0f), g_mWorldViewProjection);
	OUT.texCoord = mul(float4(IN.texCoord, 1.0f, 1.0f), g_mTextureTransform);
	OUT.worldPos = mul(float4(IN.position, 1.0f), g_mWorld).xyz;
	OUT.vertexPos = OUT.position;
	OUT.vertexColor = g_bVertexColorSRGB ? toLinear(IN.vertexColor) : IN.vertexColor; // TODO: vertexColor input in linear space
	OUT.worldNormal = normalize(mul(IN.normal, (float3x3)g_mWorld));

	return OUT;
}

//-----------------------------------------------------------------------------

struct TERRAIN_IN
{
	float3 position		:  POSITION;
	float2 texCoord		:  TEXCOORD0;
	float3 normal		:  NORMAL;
};

struct TERRAIN_OUT
{
	float4 position			:  POSITION;
	float2 texCoord			:  TEXCOORD0;
	float3 worldNormal		:  TEXCOORD1;
	float3 worldPos			:  TEXCOORD2;
	float4 vertexPos		:  TEXCOORD3;
};

TERRAIN_OUT TerrainVS(TERRAIN_IN IN)
{
	TERRAIN_OUT OUT;

	OUT.position = mul(float4(IN.position, 1.0f), g_mWorldViewProjection);
	OUT.worldPos = mul(float4(IN.position, 1.0f), g_mWorld).xyz;
	OUT.texCoord = IN.texCoord;
	OUT.vertexPos = OUT.position;
	OUT.worldNormal = normalize(mul(IN.normal, (float3x3)g_mWorld));

	return OUT;
}


//-----------------------------------------------------------------------------
// Common Functions
//-----------------------------------------------------------------------------

float3 VisualizeCascades(float3 color, float dist)
{
	if (dist < g_vCascades.x)
		color += float3(0.2f, 0.0f, 0.0f);
	else if (dist < g_vCascades.y)
		color += float3(0.0f, 0.2f, 0.0f);
	else if (dist < g_vCascades.z)
		color += float3(0.0f, 0.0f, 0.2f);
		
	return color;
}

float3 MaterialEmissive(float3 color, float intensity)
{
    return color * intensity;
}

/*void GetTriplanarUV(float3 worldPos, float2 texCoord, float2 invTexSize, float tileSize, out float2 uvXY, out float2 uvXZ, out float2 uvYZ)
{
	//worldPos *= 0.5f;
	//worldPos.y *= -1;
	//worldPos.y += 1 / invTexSize.y;
	
	float2 invTileSize = tileSize * invTexSize;
	float2 offset = texCoord - invTileSize;
	float2 offset2 = (worldPos.xy) * texCoord - invTileSize;
	float2 uvMin = offset;
	float2 uvMax = offset + invTileSize; // g_fDebugValue
	
	//texCoord.y = 1 - texCoord.y;
	float2 k = texCoord / worldPos.xy;

	uvXY = (worldPos.xy * invTexSize) * (texCoord + floor(worldPos.xy / 128));//clamp(worldPos.xy * invTileSize, worldPos.xy * invTileSize, worldPos.xy * invTileSize + invTileSize);
	uvXZ = texCoord;//worldPos.xz * k;//worldPos.xz* invTexSize+ float2(0.75f, 0.25f);//clamp(abs(worldPos.xz) * invTexSize + offset2, uvMin, uvMax);
	uvYZ = texCoord;//worldPos.yz * k;//worldPos.yz* invTexSize+ float2(0.75f, 0.25f);//clamp(abs(worldPos.yz) * invTexSize + offset2, uvMin, uvMax);
}

float4 SampleTextureTriplanar(sampler2D samp, float2 invTexSize, float2 texCoord, float3 worldNormal)
{
	float2 uvXY;
	float2 uvXZ;
	float2 uvYZ;
	GetTriplanarUV(worldPos, IN.texCoord, invTexSize, 64.0f, uvXY, uvXZ, uvYZ);
		
	float4 cX = tex2D(samp, uvYZ);
	float4 cY = tex2D(samp, uvXZ);
	float4 cZ = tex2D(samp, uvXY);

	float3 blend = abs(worldNormal);
	blend /= blend.x + blend.y + blend.z + 0.001f;
	
	return blend.x * cX + blend.y * cY + blend.z * cZ;
}*/


//-----------------------------------------------------------------------------
// Pixel Shaders
//-----------------------------------------------------------------------------

float4 StandardPS(STANDARD_OUT IN) : COLOR0
{
	const float3 worldPos = IN.worldPos;
	const float3 lightDir = -normalize(g_vLightDir);
    const float3 viewDir = normalize(g_vCameraPos - worldPos);
	float3 outColor = 0.0f;
	
	// Material
	float3 baseColor = 1.0f;
	float alpha = 1.0f;
	if (g_bVertexColor)
	{
        baseColor *= IN.vertexColor.rgb;
		alpha *= IN.vertexColor.a;
	}
	if (g_bMaterialColor)
	{
		baseColor *= g_vMaterialDiffuse.rgb;
		alpha *= g_vMaterialDiffuse.a;
	}
	if (g_bTexture)
	{
		const float4 textureColor = tex2D(colorMap, IN.texCoord);
	    baseColor *= textureColor.rgb;
		alpha *= textureColor.a;
	}
	
	// Light
	if (!g_bMaterialUnshaded)
	{
        const float2 screenCoord = ScreenToUV(IN.vertexPos);
        const float roughness = max(0.08f, g_fMaterialRoughness);
        const float3 specularColor = lerp(0.08f * g_fMaterialSpecular, baseColor, g_fMaterialMetallic);
		const float3 normal = SampleNormal(normalSampler, IN.texCoord, normalize(IN.worldNormal), viewDir);

		float3 diffuseColor = baseColor;
		if (g_bPBS)
            diffuseColor *= (1.0f - g_fMaterialMetallic);

		// Cascaded Shadows
		float fShadowTerm = 1.0f;
		if (g_bShadows)
			fShadowTerm = GetShadowTerm(worldPos, IN.vertexPos.xyz);
		
		// Contact Shadows
		if (g_bContactShadows)
			fShadowTerm *= tex2D(contactShadowsSampler, screenCoord).r;
		
		// Ambient Occlusion
		float fAO = 1.0f;
		if (g_bSSAO)
			fAO = tex2D(aoSampler, screenCoord).r;
		
		// Sky Light
		outColor += SkyLight(diffuseColor, normal, fAO);
		
		// Directional Light
        outColor += DirectionalLight(diffuseColor, specularColor, roughness, normal, lightDir, viewDir, g_vLightColor, fShadowTerm);
		
		// Point Light
		for (int i = 0; i < g_iPointLightCount; i++)
			outColor += PointLight(diffuseColor, specularColor, roughness, worldPos, normal, viewDir, g_vPointLightPosAndInvRadius[i].xyz, g_vPointLightColorAndIntensity[i].rgb, g_vPointLightColorAndIntensity[i].w, g_vPointLightPosAndInvRadius[i].w, fAO);
		
		//outColor += PointLight(diffuseColor, specularColor, roughness, worldPos, normal, viewDir, g_vMouseTerrain + float3(0, 0, g_fFogHeight), g_vFogSunColor, g_fFogEndDistance, 0.0001f, fAO);
		
		// Image Based Lighting
		if (g_bIBL)
			outColor += ImageBasedLighting(specularColor, roughness, normal, viewDir, worldPos, screenCoord, fAO);
	}
	else
    {
        outColor = baseColor;
    }
	
	// Emissive
	outColor = outColor * g_vMaterialEmissive.a + g_vMaterialEmissive.rgb;
	
	//outColor = 0;
	//if ((g_vMaterialDiffuse.r == 0.0f) && (g_vMaterialDiffuse.g == 0.0f) && (g_vMaterialDiffuse.b == 1.0f))
	//	outColor = g_vLightColor;
	
	// Fog
	if (!g_bMaterialUnfogged)
		outColor = PixelFog(outColor, worldPos, g_vCameraPos, viewDir, -lightDir);
	
	// Debug
	if (g_bVisCascades)
		outColor = VisualizeCascades(outColor, IN.vertexPos.z);
	
	// Gamma Correction
	if (!g_bLinearOutput)
		outColor = toGamma(outColor);
		
	return float4(outColor, alpha);
}

//-----------------------------------------------------------------------------

float4 TerrainPS(TERRAIN_OUT IN) : COLOR0
{
	const float3 worldPos = IN.worldPos;
	const float3 lightDir = -normalize(g_vLightDir);
    const float3 viewDir = normalize(g_vCameraPos - worldPos);
	float3 outColor = 0.0f;
	
	// Material
	float3 baseColor = 1.0f;
	float alpha = 1.0f;
	if (g_bTexture)
	{
		const float4 textureColor = tex2D(colorMap, IN.texCoord);
	    baseColor *= textureColor.rgb;
		alpha *= textureColor.a;
	}
	
	// Light
	if (!g_bMaterialUnshaded)
	{
        const float2 screenCoord = ScreenToUV(IN.vertexPos);
        const float roughness = max(0.08f, g_fMaterialRoughness);
        const float3 specularColor = lerp(0.08f * g_fMaterialSpecular, baseColor, g_fMaterialMetallic);
		const float3 normal = SampleNormal(normalSampler, IN.texCoord, normalize(IN.worldNormal), viewDir);

		float3 diffuseColor = baseColor;
		if (g_bPBS)
            diffuseColor *= (1.0f - g_fMaterialMetallic);

		// Cascaded Shadows
		float fShadowTerm = 1.0f;
		if (g_bShadows)
			fShadowTerm = GetShadowTerm(worldPos, IN.vertexPos.xyz);
		
		// Contact Shadows
		if (g_bContactShadows)
			fShadowTerm *= tex2D(contactShadowsSampler, screenCoord).r;
		
		// Ambient Occlusion
		float fAO = 1.0f;
		if (g_bSSAO)
			fAO = tex2D(aoSampler, screenCoord).r;
		
		// Sky Light
		outColor += SkyLight(diffuseColor, normal, fAO);
		
		// Directional Light
        outColor += DirectionalLight(diffuseColor, specularColor, roughness, normal, lightDir, viewDir, g_vLightColor, fShadowTerm);
		
		// Point Light
		for (int i = 0; i < g_iPointLightCount; i++)
			outColor += PointLight(diffuseColor, specularColor, roughness, worldPos, normal, viewDir, g_vPointLightPosAndInvRadius[i].xyz, g_vPointLightColorAndIntensity[i].rgb, g_vPointLightColorAndIntensity[i].w, g_vPointLightPosAndInvRadius[i].w, fAO);
		
		//outColor += PointLight(diffuseColor, specularColor, roughness, worldPos, normal, viewDir, g_vMouseTerrain + float3(0, 0, g_fFogHeight), g_vFogSunColor, g_fFogEndDistance, 0.0001f, fAO);
		
		// Image Based Lighting
		if (g_bIBL)
			outColor += ImageBasedLighting(specularColor, roughness, normal, viewDir, worldPos, screenCoord, fAO);
	}
	else
    {
        outColor = baseColor;
    }
	
	// Fog
	if (!g_bMaterialUnfogged)
		outColor = PixelFog(outColor, worldPos, g_vCameraPos, viewDir, -lightDir);
	
	// Debug
	if (g_bVisCascades)
		outColor = VisualizeCascades(outColor, IN.vertexPos.z);
		
	// Gamma Correction
	if (!g_bLinearOutput)
		outColor = toGamma(outColor);
		
	return float4(outColor, alpha);
}


//-----------------------------------------------------------------------------
// Techniques
//-----------------------------------------------------------------------------

technique Standard
{
	pass Main
	{
		VertexShader = compile vs_3_0 StandardVS();
		PixelShader = compile ps_3_0 StandardPS();
	}
}

technique Terrain
{
	pass Main
	{
		VertexShader = compile vs_3_0 TerrainVS();
		PixelShader = compile ps_3_0 TerrainPS();
	}
}
