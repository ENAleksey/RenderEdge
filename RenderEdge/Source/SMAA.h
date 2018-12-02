#pragma once

#include "Engine.h"
#include "Texture2D.h"
#include "TextureRenderTarget2D.h"

class SMAA
{
public:
	enum Input
	{
		INPUT_LUMA,
		INPUT_COLOR,
		INPUT_DEPTH
	};

	SMAA(IDirect3DDevice9 *device);
	~SMAA();

	void go(TextureRenderTarget2D* edges, TextureRenderTarget2D* src, IDirect3DSurface9* dst, Input input);

	void OnLostDevice();
	void OnResetDevice();

	float getThreshold() const { return threshold; }
	void setThreshold(float threshold) { this->threshold = threshold; }

	int getMaxSearchSteps() const { return maxSearchSteps; }
	void setMaxSearchSteps(uint32 maxSearchSteps) { this->maxSearchSteps = maxSearchSteps; }

	int getMaxSearchStepsDiag() const { return maxSearchStepsDiag; }
	void setMaxSearchStepsDiag(uint32 maxSearchStepsDiag) { this->maxSearchStepsDiag = maxSearchStepsDiag; }

	float getCornerRounding() const { return cornerRounding; }
	void setCornerRounding(float cornerRounding) { this->cornerRounding = cornerRounding; }

private:
	void edgesDetectionPass(TextureRenderTarget2D* edges, Input input);
	void blendingWeightsCalculationPass();
	void neighborhoodBlendingPass(TextureRenderTarget2D* src, IDirect3DSurface9* dst);
	void InitTemporaryResources();
	void ReleaseTemporaryResources();
	void quad();

	IDirect3DDevice9* m_pDevice;
	ID3DXEffect* pEffect;

	TextureRenderTarget2D edgeRT;
	TextureRenderTarget2D blendRT;

	Texture2D areaTex;
	Texture2D searchTex;

	IDirect3DVertexDeclaration9* vertexDeclaration;

	uint32 maxSearchSteps;
	uint32 maxSearchStepsDiag;
	float cornerRounding;
	float threshold;
};

extern SMAA* Smaa;