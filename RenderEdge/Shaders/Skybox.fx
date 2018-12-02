#include "GammaCorrection.fxh"
#include "Fog.fxh"

float4x4 g_mWorld;
float4x4 g_mWorldViewProjection;
float4x4 g_mTextureTransform;
float3 g_vCameraPos;

bool g_bLinearOutput;
bool g_bLighting;
float4 g_vMaterialDiffuse;
float3 g_vLightAmbient;
float3 g_vLightDiffuse;
float3 g_vLightDirection;
float g_fBrightness;

bool g_bFog;
//float3 g_vFogColor;
//bool g_bFogSun;
//float3 g_vFogSunColor;
//float g_fFogSunIntensity;

sampler2D diffuseMap : register(s0);

texture g_envTexture2;
sampler2D envMap2 = sampler_state
{
    Texture = <g_envTexture2>;
    MinFilter = Linear;
    MipFilter = Linear;
    MagFilter = Linear;
    AddressU = Clamp;
    AddressV = Clamp;
};

float2 vector2ll(float3 v)
{
    float2 vo = 0.0f;
    vo.x = atan2(v.x, v.z) / 3.1415926535897932f;
    vo.y = -v.y;
    vo = vo * 0.5f + 0.5f;
    return vo;
}


struct SkyboxVS_Input
{
    float4 position : POSITION;
    float2 texCoord : TEXCOORD0;
	float3 normal : NORMAL;
};

struct SkyboxVS_Output
{
    float4 position : POSITION;
    float2 texCoord : TEXCOORD0;
	float3 worldPos : TEXCOORD1;
	float3 pixelPos : TEXCOORD2;
	float3 normal : NORMAL;
};

SkyboxVS_Output SkyboxVS(SkyboxVS_Input IN)
{
    SkyboxVS_Output OUT;
    
    OUT.position = mul(float4(IN.position.xyz, 1.0f), g_mWorldViewProjection).xyww;
    OUT.texCoord = mul(float4(IN.texCoord, 1.0f, 1.0f), g_mTextureTransform);
	
	OUT.normal = normalize(mul(IN.normal, (float3x3)g_mWorld));
	OUT.worldPos = mul(float4(IN.position.xyz, 1.0f), g_mWorld);
	OUT.pixelPos = IN.position.xyz;
    
    return OUT;
}

float4 SkyboxPS(SkyboxVS_Output IN) : COLOR0
{
	float4 textureColor = tex2D(diffuseMap, IN.texCoord);
	//float4 textureColor = tex2D(envMap2, vector2ll(normalize(IN.worldPos - g_vCameraPos).xzy));
	
    float3 baseColor = textureColor.rgb;
	float alpha = textureColor.a;
	
	//float height = saturate(IN.pixelPos.z / 3000.0f/*mScaleHeight*/);
    //baseColor = lerp(g_vFogSunColor, g_vFogColor, height);
	
	// Material
	baseColor *= g_vMaterialDiffuse.rgb * g_fBrightness;
	alpha *= g_vMaterialDiffuse.a;
	
	// Lighting
	if (g_bLighting)
	{
		float3 lightDir = -normalize(g_vLightDirection);
		float3 normal = normalize(IN.normal);
		float3 NdotL = saturate(dot(normal, lightDir) * 0.5f + 0.5f);
		baseColor *= g_vLightAmbient + g_vLightDiffuse * NdotL;
	}
	
	// Fog
	if (g_bFog)
	{
		float3 fogColor = 0.0f;
		if (g_bFogSun)
		{
			float3 viewDir = normalize(g_vCameraPos - IN.worldPos);
			float3 lightDir = normalize(g_vLightDirection);
			float sunAmount = saturate(dot(viewDir, lightDir));
			fogColor = lerp(g_vFogColor, g_vFogSunColor, pow(sunAmount, g_fFogSunIntensity));
			
			/* float cosSunAngle = dot(viewDir, lightDir);
			if(cosSunAngle >= cos(g_fFogSunIntensity / 180.0f * 3.14f))
				fogColor = g_vFogSunColor * 100;
			else
				fogColor = g_vFogColor; */
			
			//float3 inscatter;
			//float3 transmittance;
			//float dist = 100000.0f;//distance(IN.worldPos, g_vCameraPos);
			//HeightFog(dist, 0, IN.worldPos.z - g_vCameraPos.z, sunAmount, inscatter, transmittance);
			//fogColor = baseColor * transmittance + inscatter;
		}
		else
        {
            fogColor = g_vFogColor;
        }
		
		baseColor = fogColor;
	}
	
	// Gamma Correction
	if (!g_bLinearOutput)
		baseColor = toGamma(baseColor);
	
    return float4(baseColor, alpha);
}

//-----------------------------------------------------------------------------

technique Standard
{
    pass p0
    {
        VertexShader = compile vs_3_0 SkyboxVS();
        PixelShader = compile ps_3_0 SkyboxPS();
    }
}
