#ifndef __RANDOM__
#define __RANDOM__

float random(float3 seed, float freq)
{
	float dt = dot(floor(seed * freq), float3(53.1215, 21.1352, 9.1322));
	return frac(sin(dt) * 2105.2354);
}

float nrand(float2 n)
{
	return frac(sin(dot(n.xy, float2(12.9898, 78.233))) * 43758.5453);
}

int randomInt(float3 seed, float freq, int maxInt)
{
	return int(float(maxInt) * random(seed, freq)) % maxInt;
}

float randomAngle(float3 seed, in float freq)
{
	return random(seed, freq) * 6.283285;
}

float2 GetRandom2FromCoord(float2 coords)
{
	coords *= 1000.0;
	float3 coords3 = frac(float3(coords.xyx) * 0.1031);
		coords3 += dot(coords3.xyz, coords3.yzx+19.19);
		return frac(float2((coords3.x + coords3.y)*coords3.z, (coords3.x+coords3.z)*coords3.y));
}

float PseudoRandom(float2 xy)
{
	float2 pos = frac(xy / 128.0f) * 128.0f + float2(-64.340622f, -72.465622f);

	// found by experimentation
	return frac(dot(pos.xyx * pos.xyy, float3(20.390625f, 60.703125f, 2.4281209f)));
}

float InterleavedGradientNoise(float2 uv, float FrameId)
{
	// magic values are found by experimentation
	uv += FrameId * (float2(47, 17) * 0.695f);

    const float3 magic = float3(0.06711056f, 0.00583715f, 52.9829189f);
    return frac(magic.z * frac(dot(uv, magic.xy)));
}

#endif // __RANDOM__