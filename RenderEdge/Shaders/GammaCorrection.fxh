#ifndef __GAMMA__
#define __GAMMA__

float3 LinearTo709(float3 linearColor) 
{
	linearColor = max(6.10352e-5, linearColor);
	return min(linearColor * 4.5, pow(max(linearColor, 0.018), 0.45) * 1.099 - 0.099);
}

float3 LinearToSrgb(float3 linearColor) 
{
	linearColor = max(6.10352e-5, linearColor);
	return min(linearColor * 12.92, pow(max(linearColor, 0.00313067), 1.0/2.4) * 1.055 - 0.055);
}

float3 toLinear(float3 color)
{
	color = max(6.10352e-5, color);
	return color > 0.04045 ? pow(color * (1.0 / 1.055) + 0.0521327, 2.4) : color * (1.0 / 12.92);
}

float4 toLinear(float4 color)
{
	return float4(toLinear(color.rgb), color.a);
}

float toLinearFloat(float x)
{
	float sRGB = (x*x)*(x*0.2848 + 0.7152);
	return sRGB;
}

float3 toGamma(float3 linearColor)
{
	return LinearToSrgb(linearColor);
}

float3 LogToLin(float3 logColor)
{
	const float linearRange = 14.0f;
	const float linearGrey = 0.18f;
	const float exposureGrey = 444.0f;

	float3 linearColor = exp2((logColor - exposureGrey / 1023.0f) * linearRange) * linearGrey;

	return linearColor;
}

float3 LinToLog(float3 linearColor)
{
	const float linearRange = 14.0f;
	const float linearGrey = 0.18f;
	const float exposureGrey = 444.0f;

	float3 logColor = log2(linearColor) / linearRange - log2(linearGrey) / linearRange + exposureGrey / 1023.0f;
	logColor = saturate(logColor);

	return logColor;
}

#endif // __GAMMA__