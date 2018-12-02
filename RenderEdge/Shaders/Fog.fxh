#ifndef __FOG__
#define __FOG__

int g_iFogTech;
float3 g_vFogColor;
float g_fFogStartDistance;
float g_fFogEndDistance;
float g_fFogDensity;
float g_fFogHeight;
float g_fFogMinOpacity;
float g_fFogHeightFalloff;
float g_fFogCutoffDistance;
float g_fCollapsedFogParameter; // FogDensity * exp2(-FogHeightFalloff * (CameraWorldPosition.z - FogHeight))

bool g_bFogSun;
float3 g_vFogSunColor;
float g_fFogSunIntensity;
float g_fFogSunStartDistance;


/*float mBetaRs;       // Scattering coef. of Rayleigh scattering [1/m]
float  mBetaMs;       // Scattering coef. of Mie scattering [1/m]
float  mBetaMa;       // Absorption coef. of Mie scattering [1/m]
float  mMieAsymmetry; // Asymmetry factor of Mie scattering [-]
float  mScaleHeight;  // Scale Height [m]
float3 mAlbedoR;      // Control parameter of Rayleigh scattering color [-]
float3 mAlbedoM;      // Control parameter of Mie scattering color [-]
float3 mSunColor;     // [-]
float3 mAmbColor;     // [-]

float Rayleigh(float mu)
{
  return 3.0 / 4.0 * 1.0 / (4.0*3.14159265359f)*(1.0 + mu*mu);
}

float Mie(float mu, float g)
{
  // Henyey-Greenstein phase function
  return (1.0 - g*g) / ((4.0*3.14159265359f) * pow(abs(1.0 + g*g - 2.0*g*mu), 1.5));
}

void HeightFog(
  float          inDistance,       // Distance [m]
  float          inCameraPosY,     // Altitude of the camera position [m]
  float          inWorldPosY,      // Altitude of the world position [m]
  float          inSoV,            // dot(sun_dir, view_dir) [-]
  out float3     outInscatter,     // in-scatter [-]
  out float3     outTransmittance) // transmittance [-]
{
  
  const float3 beta_t = mBetaRs + (mBetaMs + mBetaMa);

  // Transmittance
  float t = max(1e-2, (inCameraPosY - inWorldPosY) / mScaleHeight);
  t = (1.0 - exp(-t)) / t * exp(-inWorldPosY / mScaleHeight);
  float3 transmittance = exp(-inDistance * t * beta_t);
  
  // Inscatter
  float3 single_r = mAlbedoR * mBetaRs * Rayleigh(inSoV);
  float3 single_m = mAlbedoM * mBetaMs * Mie(inSoV, mMieAsymmetry);
  float3 inscatter = mSunColor * (single_r + single_m);
  inscatter += mAmbColor * (mBetaRs + mBetaMs);
  inscatter /= beta_t;
  
  outInscatter = inscatter * (1.0 - transmittance);
  outTransmittance = transmittance;
}*/


float4 GetExponentialHeightFog(float3 CameraToReceiver, float camZ, float3 viewDir, float3 lightDir)
{
    float CameraToReceiverLengthSqr = dot(CameraToReceiver, CameraToReceiver);
    float CameraToReceiverLengthInv = rsqrt(CameraToReceiverLengthSqr);
    float CameraToReceiverLength = CameraToReceiverLengthSqr * CameraToReceiverLengthInv;

    float RayOriginTerms = g_fCollapsedFogParameter;
    float RayLength = CameraToReceiverLength;
    float RayDirectionZ = CameraToReceiver.z;

    if (g_fFogStartDistance > 0)
    {
        float ExcludeIntersectionTime = g_fFogStartDistance * CameraToReceiverLengthInv;
        float CameraToExclusionIntersectionZ = ExcludeIntersectionTime * RayDirectionZ;
        float ExclusionIntersectionZ = camZ + CameraToExclusionIntersectionZ;
        float ExclusionIntersectionToReceiverZ = RayDirectionZ - CameraToExclusionIntersectionZ;
		
        RayLength = (1.0f - ExcludeIntersectionTime) * CameraToReceiverLength;
        RayDirectionZ = ExclusionIntersectionToReceiverZ;

        float Exponent = max(-127.0f, g_fFogHeightFalloff * (ExclusionIntersectionZ - g_fFogHeight));
        RayOriginTerms = g_fFogDensity * exp2(-Exponent);
    }
	
    float Falloff = max(-127.0f, g_fFogHeightFalloff * RayDirectionZ);
    float LineIntegral = (1.0f - exp2(-Falloff)) / Falloff;
    float log2 = log(2.0);
    float LineIntegralTaylor = log2 - (0.5 * log2 * log2) * Falloff;
    float ExponentialHeightLineIntegralShared = RayOriginTerms * (abs(Falloff) > 0.01f ? LineIntegral : LineIntegralTaylor);
    float ExponentialHeightLineIntegral = ExponentialHeightLineIntegralShared * RayLength;

    float3 InscatteringColor = g_vFogColor;
    float3 DirectionalInscattering = 0;

    if (g_bFogSun)
    {
        float3 DirectionalLightInscattering = g_vFogSunColor * pow(saturate(dot(viewDir, lightDir)), g_fFogSunIntensity);
        float DirExponentialHeightLineIntegral = ExponentialHeightLineIntegralShared * max(RayLength - g_fFogSunStartDistance, 0.0f);
        float DirectionalInscatteringFogFactor = saturate(exp2(-DirExponentialHeightLineIntegral));
        DirectionalInscattering = DirectionalLightInscattering * (1 - DirectionalInscatteringFogFactor);
    }
	
    float ExpFogFactor = max(saturate(exp2(-ExponentialHeightLineIntegral)), g_fFogMinOpacity);

    if (g_fFogCutoffDistance > 0 && CameraToReceiverLength > g_fFogCutoffDistance)
    {
        ExpFogFactor = 1;
        DirectionalInscattering = 0;
    }

    return float4(InscatteringColor * (1 - ExpFogFactor) + DirectionalInscattering, ExpFogFactor);
}

float3 PixelFog(float3 sceneColor, float3 worldPos, float3 camPos, float3 viewDir, float3 lightDir)
{
	const float dist = distance(worldPos, camPos);
	float fogFactor = 0.0f;

	if (g_iFogTech == 0)
	{
        fogFactor = (g_fFogStartDistance - dist) / (g_fFogStartDistance - g_fFogEndDistance);
    }
	else if (g_iFogTech == 1)
	{
        fogFactor = 1.0f - exp(-dist * g_fFogDensity);
    }
	else if (g_iFogTech == 2)
	{
        fogFactor = 1.0f - exp(-(dist * g_fFogDensity) * (dist * g_fFogDensity));
    }
	else if (g_iFogTech == 3)
	{
        float4 fogInscatteringAndOpacity = GetExponentialHeightFog(worldPos - camPos, camPos.z, viewDir, lightDir);
        return sceneColor.rgb * fogInscatteringAndOpacity.a + fogInscatteringAndOpacity.rgb;
    }
	
    return lerp(sceneColor, g_vFogColor, saturate(fogFactor));
}

#endif // __FOG__