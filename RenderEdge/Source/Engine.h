#pragma once

#include <iostream>
#include <sstream>
#include "Utils.h"
#include "TextureRenderTarget2D.h"
#include "Input.h"

extern const std::string RenderEdgeVersion;

extern bool g_bWindowed;
extern bool g_bVsyncEnabled;
extern float g_fDebugValue;
extern std::string RenderEdgePath;
extern HANDLE mpqRenderEdge;

extern bool g_bDefaultProjectionMatrix;
extern float g_fCameraFoV;
extern float g_fCameraNearZ;
extern float g_fCameraFarZ;
extern D3DXVECTOR3 g_vCameraPos;
extern D3DXVECTOR3 g_vCameraRotation;


extern bool g_presented;
extern bool g_presentedShadows;

extern D3DXVECTOR4 g_vScreenPositionScaleBias;
extern D3DXVECTOR4 g_vViewportRect;
extern D3DXVECTOR4 g_vViewportSize;
extern D3DXVECTOR4 g_vBufferSize;
extern float g_fWideScreenMul;

extern float g_fFPS;
extern float g_fDeltaTime;
extern float g_fTimer;

extern bool g_bDefaultLightDir;
extern D3DXVECTOR3 g_vGlobalLightDir;
extern D3DXVECTOR3 g_vLightDir;

extern bool g_bAnisoFiltering;
extern uint32 g_iMaxAnisotropy;

extern D3DXMATRIX g_mProj;
extern D3DXMATRIX g_mView;
extern D3DXMATRIX g_mProjNonJittered;;

extern IDirect3DSurface9* g_pBackBuffer;
extern TextureRenderTarget2D g_depthRT;
extern TextureRenderTarget2D g_mainRT;
extern uint32 g_iFrameIndexMod8;


class CEngine
{
private:
	IDirect3DDevice9* m_pDevice;
	bool bMapInit;

public:
	CEngine(IDirect3DDevice9* pDevice);
	~CEngine();
	void Release();

	void OnCreateDevice();
	void OnLostDevice();
	void OnResetDevice();

	void OnPresent();
	void OnMapStart();
	void OnMapEnd();
	void OnGameState();
	void OnBeginScene();
	void OnEndScene();

	void InitTemporaryResources();
	void ReleaseTemporaryResources();
	void ReloadShaders();
	
	void GetBackBufferSize();
	void GetSupportedDepthFormat();
	void OnFrameRenderingSetup(uint32 SampleCount);
	bool ReadConfigFile(const std::string& fileName);
	void TakeScreenshot();
	void RenderText();

	void UpdateLightAndFog();
	void OnCalcSceneView_before(uint32 pCamera);
	void OnCalcSceneView_after();

	void OnRenderWorld();
	void OnRenderUI();

	HRESULT OnDrawIndexedPrimitive(D3DPRIMITIVETYPE primitiveType, int32 baseVertexIndex, uint32 minIndex, uint32 numVertices, uint32 startIndex, uint32 primitiveCount, uint32 stride, IDirect3DTexture9* currentTexture);

	bool OnMouseMove(uint32 x, uint32 y);
	bool OnMouseButtonDown(EMouseButton button);
	bool OnMouseButtonUp(EMouseButton button);
	bool OnMouseWheel(int delta);
	bool OnKeyboardDown(WPARAM getKey);
	bool OnKeyboardUp(WPARAM getKey);
	bool OnGetMessage(HWND ah_Wnd, uint32 uMsg, WPARAM wParam, LPARAM lParam);
};

extern CEngine* Engine;