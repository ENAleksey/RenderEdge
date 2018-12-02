float4x4 g_mLightViewProj;
float g_fAlphaThreshold;

texture g_albedoTexture;
sampler2D colorMap = sampler_state
{
	Texture = <g_albedoTexture>;
	MipFilter = None;
    MagFilter = Linear;
    MinFilter = Linear;
	AddressU = Wrap;
    AddressV = Wrap;
};


struct VS_OUTPUT
{
	float4 position	: POSITION;
	float2 texCoord : TEXCOORD0;
	float2 fDepth : TEXCOORD1;
};

VS_OUTPUT BuildDepthBufferVS(float3 position : POSITION, float2 texCoord : TEXCOORD0)
{
	VS_OUTPUT OUT = (VS_OUTPUT)0;

	OUT.position = mul(float4(position, 1.0f), g_mLightViewProj);
	OUT.texCoord = texCoord;
	OUT.fDepth = OUT.position.zw;

	return OUT;
}

float4 BuildDepthBufferPS(VS_OUTPUT IN) : COLOR0
{
	if (g_fAlphaThreshold > 0.0f)
	{
		float alpha = tex2D(colorMap, IN.texCoord).a;
		if (alpha < g_fAlphaThreshold)
			discard;
	}

	float depth = IN.fDepth.x / IN.fDepth.y;
	
	return float4(depth, 0.0f, 0.0f, 1.0f);
}


technique BuildDepthBuffer
{
	pass p0
	{
		Lighting = False;
		
		VertexShader = compile vs_2_0 BuildDepthBufferVS();
		PixelShader  = compile ps_2_0 BuildDepthBufferPS();
	}
}