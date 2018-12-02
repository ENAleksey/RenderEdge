#include <sstream>
#include <vector>
#include "SMAA.h"
#include "MPQ.h"
#include "ResourceManager.h"
using namespace std;

SMAA* Smaa = nullptr;

SMAA::SMAA(IDirect3DDevice9* pDevice)
{
	m_pDevice = pDevice;
	threshold = 0.1f;
	cornerRounding = 25.0f;
	maxSearchSteps = 16;
	maxSearchStepsDiag = 8;

	InitTemporaryResources();

	if (ResourceManager)
	{
		ResourceManager->LoadTexture2D("Textures\\AreaTexDX9.dds", &areaTex, true, D3DFMT_A8L8);
		ResourceManager->LoadTexture2D("Textures\\SearchTex.dds", &searchTex, true, D3DFMT_L8);
		ResourceManager->LoadShader("Shaders\\SMAA.cso", nullptr, &pEffect);
	}

	const D3DVERTEXELEMENT9 vertexElements[3] =
	{
		{ 0, 0,  D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION, 0 },
		{ 0, 12, D3DDECLTYPE_FLOAT2, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD,  0 },
		D3DDECL_END()
	};

	m_pDevice->CreateVertexDeclaration(vertexElements, &vertexDeclaration);
}

SMAA::~SMAA()
{
	SAFE_RELEASE(pEffect);
	SAFE_RELEASE(vertexDeclaration);

	ReleaseTemporaryResources();
}

void SMAA::OnLostDevice()
{
	if (pEffect)
		pEffect->OnLostDevice();

	ReleaseTemporaryResources();
}

void SMAA::OnResetDevice()
{
	if (pEffect)
		pEffect->OnResetDevice();

	InitTemporaryResources();
}

void SMAA::InitTemporaryResources()
{
	edgeRT.Create(m_pDevice, g_vBufferSize.x, g_vBufferSize.y, 1, ETextureUsage::RenderTarget, ETextureFormat::RGBAHalf);
	blendRT.Create(m_pDevice, g_vBufferSize.x, g_vBufferSize.y, 1, ETextureUsage::RenderTarget, ETextureFormat::RGBAHalf);
}

void SMAA::ReleaseTemporaryResources()
{
	edgeRT.Release();
	blendRT.Release();
}



void SMAA::go(TextureRenderTarget2D* edges, TextureRenderTarget2D* src, IDirect3DSurface9 *dst, Input input)
{
	m_pDevice->SetVertexDeclaration(vertexDeclaration);

	edgesDetectionPass(edges, input);
	blendingWeightsCalculationPass();
	neighborhoodBlendingPass(src, dst);
}


void SMAA::edgesDetectionPass(TextureRenderTarget2D* edges, Input input)
{
	m_pDevice->SetRenderTarget(0, edgeRT.GetSurface());
	m_pDevice->Clear(0, nullptr, D3DCLEAR_TARGET, D3DCOLOR_ARGB(0, 0, 0, 0), 1.0f, 0);

	pEffect->SetValue("pixelSize", &D3DXVECTOR2(g_vBufferSize.z, g_vBufferSize.w), sizeof(D3DXVECTOR2));
	pEffect->SetFloat("threshld", threshold);
	pEffect->SetFloat("maxSearchSteps", float(maxSearchSteps));
	pEffect->SetFloat("maxSearchStepsDiag", float(maxSearchStepsDiag));
	pEffect->SetFloat("cornerRounding", cornerRounding);

	switch (input)
	{
	case INPUT_LUMA:
		pEffect->SetTexture("colorTex2D", edges->GetTexture());
		pEffect->SetTechnique("LumaEdgeDetection");
		break;
	case INPUT_COLOR:
		pEffect->SetTexture("colorTex2D", edges->GetTexture());
		pEffect->SetTechnique("ColorEdgeDetection");
		break;
	case INPUT_DEPTH:
		pEffect->SetTexture("depthTex2D", edges->GetTexture());
		pEffect->SetTechnique("DepthEdgeDetection");
		break;
	default:
		throw logic_error("unexpected error");
	}

	UINT passes;
	pEffect->Begin(&passes, 0);
	pEffect->BeginPass(0);
	quad();
	pEffect->EndPass();
	pEffect->End();
}


void SMAA::blendingWeightsCalculationPass()
{
	m_pDevice->SetRenderTarget(0, blendRT.GetSurface());
	m_pDevice->Clear(0, nullptr, D3DCLEAR_TARGET, D3DCOLOR_ARGB(0, 0, 0, 0), 1.0f, 0);

	pEffect->SetTexture("edgesTex2D", edgeRT.GetTexture());
	pEffect->SetTexture("areaTex2D", areaTex.GetTexture());
	pEffect->SetTexture("searchTex2D", searchTex.GetTexture());
	pEffect->SetTechnique("BlendWeightCalculation");

	UINT passes;
	pEffect->Begin(&passes, 0);
	pEffect->BeginPass(0);
	quad();
	pEffect->EndPass();
	pEffect->End();
}


void SMAA::neighborhoodBlendingPass(TextureRenderTarget2D* src, IDirect3DSurface9 *dst)
{
	m_pDevice->SetRenderTarget(0, dst);
	pEffect->SetTexture("colorTex2D", src->GetTexture());
	pEffect->SetTexture("blendTex2D", blendRT.GetTexture());
	pEffect->SetTechnique("NeighborhoodBlending");

	UINT passes;
	pEffect->Begin(&passes, 0);
	pEffect->BeginPass(0);
	quad();
	pEffect->EndPass();
	pEffect->End();
}


void SMAA::quad()
{
	float quad[4][5] =
	{
		{ -1.0f - g_vBufferSize.z,  1.0f + g_vBufferSize.w, 0.5f, 0.0f, 0.0f },
		{  1.0f - g_vBufferSize.z,  1.0f + g_vBufferSize.w, 0.5f, 1.0f, 0.0f },
		{ -1.0f - g_vBufferSize.z, -1.0f + g_vBufferSize.w, 0.5f, 0.0f, 1.0f },
		{  1.0f - g_vBufferSize.z, -1.0f + g_vBufferSize.w, 0.5f, 1.0f, 1.0f }
	};
	m_pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, quad, sizeof(quad[0]));
}

