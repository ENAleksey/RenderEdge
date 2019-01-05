#include "Random.fxh"
#include "GammaCorrection.fxh"
#include "PostProcessCommon.fxh"
#include "SSAO.fxh"
#include "SSR.fxh"
#include "Bloom.fxh"
#include "EyeAdaptation.fxh"
#include "ContactShadows.fxh"
#include "LutBaker.fxh"
#include "TAA.fxh"

bool g_bDebugScreenOneChannel;
float2 g_vDebugScreenTiling;

bool g_bChromaticAberration;
float g_fChromaticAberrationIntensity;

bool g_bLensDirt;
float g_fLensDirtIntensity;
float4 g_vLensDirtTileOffset;

bool g_bVignette;
bool g_bVignetteRounded;
float3 g_vVignetteColor;
float g_fVignetteSmoothness;
float g_fVignetteIntensity;
float g_fVignetteRoundness;

bool g_bFilmGrain;
float g_fFilmGrainIntensity;
float g_fFilmGrainVariance;
int g_iFilmGrainSignalToNoiseRatio;

bool g_bDithering;
float4 g_vDitheringCoords;

#define MAX_CHROMATIC_SAMPLES 16


texture g_debugTexture;
sampler2D debugSampler = sampler_state
{
	Texture = <g_debugTexture>;
	MipFilter = None;
	MinFilter = Linear;
    MagFilter = Linear;
	AddressU = Border;
    AddressV = Border;
	BorderColor = 0x000000;
};

texture g_bloomTexture;
sampler2D bloomSampler = sampler_state
{
	Texture = <g_bloomTexture>;
	MipFilter = None;
	MinFilter = Linear;
	MagFilter = Linear;
	AddressU = Border;
	AddressV = Border;
	BorderColor = 0x000000;
};

texture g_hdrLutTexture;
sampler2D hdrLutSampler = sampler_state
{
	Texture = <g_hdrLutTexture>;
	MipFilter = Point;
	MinFilter = Linear;
	MagFilter = Linear;
	AddressU = Clamp;
	AddressV = Clamp;
};

texture g_lensDirtTexture;
sampler2D lensdirtSampler = sampler_state
{
	Texture = <g_lensDirtTexture>;
	MipFilter = None;
	MinFilter = Linear;
	MagFilter = Linear;
	AddressU = Border;
	AddressV = Border;
	BorderColor = 0x000000;
};

texture g_spectralLutTexture;
sampler2D spectrumSampler = sampler_state
{
	Texture = <g_spectralLutTexture>;
	MipFilter = None;
	MinFilter = Linear;
	MagFilter = Linear;
	AddressU = Clamp;
	AddressV = Clamp;
};

texture g_ditheringTexture;
sampler2D ditheringSampler = sampler_state
{
	Texture = <g_ditheringTexture>;
	MipFilter = None;
	MinFilter = Point;
	MagFilter = Point;
	AddressU = Wrap;
	AddressV = Wrap;
};



float3 ColorLookupTable(float3 LinearColor)
{
	float3 LUTEncodedColor = LinToLog(LinearColor + LogToLin(0));
	
	const float LUTSize = 32;
	float3 UVW = LUTEncodedColor * ((LUTSize - 1) / LUTSize) + (0.5f / LUTSize);

	float3 OutDeviceColor = UnwrappedTexture3DSample(hdrLutSampler, UVW, LUTSize).rgb;
	
	return OutDeviceColor * 1.05;
}


float3 FilmGrain(float3 color, float2 texcoord)
{
	float inv_luma = dot(color, float3(-1.0/3.0, -1.0/3.0, -1.0/3.0)) + 1.0;

	float t = g_fTimer * 0.0022337;
	
	float seed = dot(texcoord, float2(12.9898, 78.233));
	float sine = sin(seed);
	float cosine = cos(seed);
	float uniform_noise1 = frac(sine * 43758.5453 + t);
	float uniform_noise2 = frac(cosine * 53758.5453 - t);

	float stn = g_iFilmGrainSignalToNoiseRatio != 0 ? pow(abs(inv_luma), (float)g_iFilmGrainSignalToNoiseRatio) : 1.0;
	float variance = (g_fFilmGrainVariance*g_fFilmGrainVariance) * stn;
	float mean = 0.5f;

	uniform_noise1 = (uniform_noise1 < 0.0001) ? 0.0001 : uniform_noise1;
		
	float r = sqrt(-log(uniform_noise1));
	r = (uniform_noise1 < 0.0001) ? 3.1415927f : r;
	float theta = 6.2831854f * uniform_noise2;
	
	float gauss_noise1 = variance * r * cos(theta) + mean;

	float grain = lerp(1.0 + g_fFilmGrainIntensity,  1.0 - g_fFilmGrainIntensity, gauss_noise1);
	return color * grain;
}


float3 Dither(float3 color, float2 texCoord)
{
    float noise = tex2D(ditheringSampler, texCoord * g_vDitheringCoords.xy + g_vDitheringCoords.zw).r * 2.0 - 1.0;
    noise = FastSign(noise) * (1.0 - sqrt(1.0 - abs(noise)));
	
    return color + noise / 255.0;
}


float3 ChromaticAberration(sampler2D tex, float2 texCoord)
{
	float2 coords = 2.0f * texCoord - 1.0f;
	float2 end = texCoord - coords * dot(coords, coords) * g_fChromaticAberrationIntensity;

	float2 diff = end - texCoord;
	int samples = clamp(int(length(g_vBufferSize.xy * diff / 2.0f)), 3, MAX_CHROMATIC_SAMPLES);
	float2 delta = diff / samples;
	float2 pos = texCoord;
	float3 sum = 0.0f, filterSum = 0.0f;

	for (int i = 0; i < samples; i++)
	{
		float t = (i + 0.5f) / samples;
		float3 s = tex2Dlod(tex, float4(pos, 0, 0)).rgb;
		float3 filter = tex2Dlod(spectrumSampler, float4(t, 0, 0, 0)).rgb;

		sum += s * filter;
		filterSum += filter;
		pos += delta;
	}

	return sum / filterSum;
}


/*float3 Sharpen(sampler2D tex, float2 texCoord)
{
	float2 step = (g_fSharpenIntensity * 0.360f) * g_vBufferSize.zw;
	
	float3 color = saturate(tex2Dlod(tex, float4(texCoord, 0, 0)).rgb) * 5.0f;
	color -= saturate(tex2Dlod(tex, float4(texCoord + float2(0, -step.y), 0, 0)).rgb);
	color -= saturate(tex2Dlod(tex, float4(texCoord + float2(-step.x, 0), 0, 0)).rgb);
	color -= saturate(tex2Dlod(tex, float4(texCoord + float2(step.x, 0), 0, 0)).rgb);
	color -= saturate(tex2Dlod(tex, float4(texCoord + float2(0, step.y), 0, 0)).rgb);
	
	return color;
}*/


/*float3 VisualizeHDR(float3 linearColor)
{
    float LuminanceVal = max(linearColor.r, max(linearColor.g, linearColor.b));
    float x = log2(LuminanceVal) * g_fHistogramMultiply + g_fHistogramAdd;

    x = saturate(x);

    float3 Heat = float3(1.0f, 0.0f, 0.0f);
    float3 Middle = float3(0.0f, 1.0f, 0.0f);
    float3 Cold = float3(0.0f, 0.0f, 1.0f);

    float3 ColdHeat = lerp(Cold, Heat, x);

    return lerp(Middle, ColdHeat, abs(0.5f - x) * 2);
}*/


float4 FinalPassPS(float2 texCoord : TEXCOORD0) : COLOR
{
	[branch] if (IsOutsideViewport(texCoord))
		discard;

	// Chromatic Aberration
	float3 linearColor = 0.0f;
	if (g_bChromaticAberration)
		linearColor = ChromaticAberration(mainSampler, texCoord);
	else
		linearColor = tex2D(mainSampler, texCoord).rgb;

    //if (g_bVignette)
    //    return float4(VisualizeHDR(linearColor), 1.0f);

	// Auto Exposure
	[branch] if (g_bAutoExposure)
	{
		float fAutoExposure = tex2D(exposureSampler, float2(0.5f, 0.5f)).r;
		linearColor *= fAutoExposure;
	}

	// Bloom
	[branch] if (g_bBloom)
	{
		float3 bloom = UpsampleFilter(bloomSampler, texCoord, g_vMainTextureSize, g_fBloomScale) * g_fBloomIntensity;
		//bloom = max(pow(bloom, g_fLensDirtIntensity), 0.0f) * g_fBloomIntensity;
		linearColor += bloom;
		
		[branch] if (g_bLensDirt)
		{
			float3 dirt = tex2D(lensdirtSampler, texCoord * g_vLensDirtTileOffset.xy + g_vLensDirtTileOffset.zw).rgb * g_fLensDirtIntensity;
			linearColor += bloom * dirt;
		}
	}

	// Vignetting
	[branch] if (g_bVignette)
    {
		float2 ScreenPos = UVToScreen(texCoord);
		float2 d = abs(ScreenPos) * g_fVignetteIntensity;
		if (g_bVignetteRounded)
			d.x *= g_vViewportSize.x / g_vViewportSize.y;
		else
			d = pow(saturate(d), g_fVignetteRoundness);
		float vfactor = pow(saturate(1.0f - dot(d, d)), g_fVignetteSmoothness);
		linearColor *= lerp(g_vVignetteColor, 1.0f, vfactor);
	}

	// Color Grading
    float3 outDeviceColor = ColorLookupTable(linearColor);
	/* if (abs(g_fBloomThreshold - 1.0f) < 0.001f)
		outDeviceColor = toGamma(GranTurismoTonemapper(linearColor));
	else if (abs(g_fBloomThreshold - 2.0f) < 0.001f)
		outDeviceColor = toGamma(toneHejl(linearColor));
	else if (abs(g_fBloomThreshold - 3.0f) < 0.001f)
		outDeviceColor = toGamma(Uncharted2Tonemap(2*linearColor)/Uncharted2Tonemap(11.2));
	else if (abs(g_fBloomThreshold - 4.0f) < 0.001f)
		outDeviceColor = ColorLookupTable(linearColor);
	else
		outDeviceColor = toGamma(linearColor);  */

	// Dithering
	[branch] if (g_bDithering)
		outDeviceColor = Dither(outDeviceColor, texCoord);
		
	// Film Grain
	[branch] if (g_bFilmGrain)
		outDeviceColor = FilmGrain(outDeviceColor, texCoord);

	return float4(outDeviceColor, 1.0f);
}

float4 FinalPassDebugPS(float2 texCoord : TEXCOORD0) : COLOR
{
	float3 debugColor = tex2D(debugSampler, texCoord * g_vDebugScreenTiling.xy).rgb;
	if (g_bDebugScreenOneChannel)
		debugColor = debugColor.rrr;
	
	return float4(debugColor, 1.0f);
}

float4 FinalPassDebugDepthPS(float2 texCoord : TEXCOORD0) : COLOR
{
	float linearDepth = Linear01Depth(tex2D(debugSampler, texCoord).r);
	
	return float4(linearDepth.rrr, 1.0f);
}

//-----------------------------------------------------------------------------

technique FinalPass
{
    pass Main
    {
        PixelShader = compile ps_3_0 FinalPassPS();
    }
	
	pass Debug
    {
        PixelShader = compile ps_2_0 FinalPassDebugPS();
    }
	
	pass DebugDepth
    {
        PixelShader = compile ps_2_0 FinalPassDebugDepthPS();
    }
}
