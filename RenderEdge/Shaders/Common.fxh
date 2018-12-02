#ifndef __COMMON__
#define __COMMON__

//#pragma warning (disable : 3205) // conversion of larger type to smaller
//#pragma warning (disable : 3568) // unknown pragma ignored
//#pragma warning (disable : 3571) // "pow(f,e) will not work for negative f"; however in majority of our calls to pow we know f is not negative
//#pragma warning (disable : 3206) // implicit truncation of vector type

float3 g_vCameraPos;
float g_fDebugValue;
float3 g_vMouseTerrain;

float4 g_vScreenScaleBias;

static const float PI = 3.1415926535897932f;


float Pow2(float x)
{
	return (x * x);
}

float Pow5(float x)
{
	float x2 = x*x;
	return x2 * x2 * x;
}

float3 Luminance(float3 linearColor)
{
	return dot(linearColor, float3(0.3f, 0.59f, 0.11f));
}

float remap(float t, float a, float b)
{
	return clamp((t - a) / (b - a), 0.0, 1.0);
}
float2 remap(float2 t, float2 a, float2 b)
{
	return clamp((t - a) / (b - a), 0.0, 1.0);
}

float max3(float3 color)
{
	return max(color.r, max(color.g, color.b));
}

float2 ScreenToUV(float4 screenPos)
{
	return (screenPos.xy / screenPos.w) * g_vScreenScaleBias.xy + g_vScreenScaleBias.zw;
}

float3x3 CalcCotangentFrame(float3 wsNormal, float3 wsInvViewDir, float2 tsCoord)
{
    float3 dp1 = ddx(wsInvViewDir);
    float3 dp2 = ddy(wsInvViewDir);
    float2 duv1 = ddx(tsCoord);
    float2 duv2 = ddy(tsCoord);
 
    float3 dp2perp = cross(dp2, wsNormal);
    float3 dp1perp = cross(wsNormal, dp1);
    float3 T = dp2perp * duv1.x + dp1perp * duv2.x;
    float3 B = dp2perp * duv1.y + dp1perp * duv2.y;
 
    float invmax = rsqrt(max(dot(T,T), dot(B,B)));
    return float3x3(T * invmax, B * invmax, wsNormal);
}

#endif // __COMMON__