#pragma once

#include <iostream>
#include <sstream>
#include "Utils.h"
#include "Texture2D.h"
#include "TextureCube.h"
#include "TextureRenderTarget2D.h"
#include "Input.h"
#include "FColor.h"

enum class EFogTech : uint32
{
	Linear,
	Exponential,
	Exponential2,
	HeightBased
};

enum class ELightUnits : uint32
{
	Unitless,
	Candelas,
	Lumens,
};

extern const std::string RenderEdgeVersion;
extern std::string RenderEdgePath;

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
	
	void UpdateWidescreenFix(float aspectRatio);
	void GetBackBufferSize();
	void GetSupportedDepthFormat();
	void OnFrameRenderingSetup(uint32 SampleCount);
	bool ReadConfigFile(const std::string& fileName);
	void TakeScreenshot();
	void RenderText();
	void CalculateFrameRate();

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


	HANDLE hRenderEdgeMpq;

	uint32 hotkey_ShowAntTweakBar;
	uint32 hotkey_PauseGame;
	uint32 hotkey_TakeScreenshot;

	D3DXVECTOR4 vScreenPositionScaleBias;
	D3DXVECTOR4 vViewportRect;
	D3DXVECTOR4 vViewportSize;
	D3DXVECTOR4 vBufferSize;

	float fWideScreenMul;
	float fDeltaTime;
	float fFPS;
	float fTimer;

	bool bDefaultRenderer;
	bool bVsyncEnabled;
	bool bDebugInfo;
	bool bGamePaused;
	bool bTakeScreenshot;
	bool bWindowed;

	bool bFreeCamera;
	bool bDefaultProjectionMatrix;
	float fCameraFoV;
	float fCameraNearZ;
	float fCameraFarZ;
	D3DXVECTOR3 vCameraPos;
	D3DXVECTOR3 vCameraRotation;

	ID3DXEffect* pStandardFX;
	ID3DXEffect* pSkyboxFX;

	D3DXMATRIX mViewProjectionInverse;
	//D3DXMATRIX mViewProjectionInversePrev;
	D3DXMATRIX mProjPrev;
	D3DXMATRIX mProjGlobal, mViewGlobal;
	D3DXMATRIX mProjNonJittered;

	bool bHDRStarted;
	bool bPostProcessRendered;
	bool bSceneUpdated;
	bool bMapLoaded;

	bool bDefaultLightDir;
	bool bDefaultLightColor;
	bool bDefaultAmbientColor;
	bool bSkyLight;
	bool bUseTemperature;
	float fSkyLightIntensity;
	float fLightIntensity;
	float fLightTemperature;
	D3DXVECTOR3 vAmbColor;
	D3DXVECTOR3 vSkyColor;
	D3DXVECTOR3 vIndColor;
	D3DXVECTOR3 vLightDir;
	D3DXVECTOR3 vLightColor;

	bool bMaterialColorSRGB;
	bool bVertexColorSRGB;
	bool bAmbientColorSRGB;
	bool bLightColorSRGB;
	bool bPointLightColorSRGB;
	bool bFogColorSRGB;

	bool bEnableFog;
	bool bDefaultFog;
	EFogTech iFogTech;
	D3DXVECTOR3 vFogColor;
	float fFogStart;
	float fFogEnd;
	float fFogDensity;
	float fFogHeight;
	float fFogMaxOpacity;
	float fFogHeightFalloff;
	float fFogCutoffDistance;
	bool bFogSun;
	D3DXVECTOR3 vFogSunColor;
	float fFogSunIntensity;
	float fFogSunStartDistance;

	//bool bGlobalFog = false;
	D3DXVECTOR3 vGlobalFogColor;
	float fGlobalFogStart;
	float fGlobalFogEnd;
	float fGlobalFogDensity;
	EFogTech iGlobalFogTech;

	bool bDebugPointLight;
	bool bDebugLightMousePos;
	bool bDebugLightUseTemperature;
	float fDebugLightTemperature;
	D3DXVECTOR4 vDebugLightColorAndIntensity;
	D3DXVECTOR4 vDebugLightPosAndInvRadius;
	ELightUnits DebugLightIntensityUnits;

	bool bTexture;
	bool bMaterialColor;
	bool bMaterialVertexColor;
	bool bTranslucentMaterials;
	bool bUnshadedMaterials;
	bool bUnfoggedMaterials;
	bool bAnisoFiltering;
	uint32 iMaxAnisotropy;

	D3DXVECTOR3 vGlobalLightDir;
	D3DXVECTOR3 vGlobalLightColor;
	D3DXVECTOR3 vGlobalAmbientColor;

	bool bGlobalPointLight;
	bool bPointLight;
	uint32 iPointLightCount;
	ELightUnits DefaultPointLightIntensityUnits;
	float fDefaultPointLightIntensity;
	float fDefaultPointLightRadius;
	FColor vPointLightColorAndIntensity[8];
	FColor vPointLightPosAndInvRadius[8];

	bool bUserInterface;
	bool bCustomUserInterface;
	float fDebugValue;
	D3DXVECTOR2 vBlackBorders;

	bool bFogOfWar;
	bool bMaskedObjects;
	bool bBuildingsShadows;
	bool bUnitsShadows;
	bool bMapBounds;
	uint32 iFoggedObjectColor;
	uint32 iFoggedTerrainColor;
	uint32 iMaskedObjectColor;
	uint32 iMaskedTerrainColor;
	uint32 iBoundaryTerrainColor;
	uint32 iBoundaryObjectColor;
	uint32 iFoggedBoundaryTerrainColor;
	uint32 iFoggedBoundaryObjectColor;

	bool bIBL;
	float fEnvCubemapRotation;
	float fCubemapBrightness;
	bool bEnvCubemapSwapYZ;
	TextureCube envTexture;
	std::string envTextureFileName;

	bool bPBS;
	bool bSimpleMaterial;
	float fMaterialRoughness;
	float fMaterialMetallic;
	float fMaterialSpecular;
	float fMaterialTranslucent;

	float fTerrainRoughness;
	float fTerrainMetallic;
	float fTerrainSpecular;
	bool bNormalMapping;
	Texture2D normalTexture;
	std::string normalTextureFileName;

	IDirect3DSurface9* pBackBufferSurface;
	TextureRenderTarget2D depthRT;
	TextureRenderTarget2D mainRT;
	ETextureFormat depthFormat;
	bool bEnableHDR;
	uint32 iFrameIndexMod8;

	bool bSkyboxShading;
	bool bSkyboxFog;
	bool bSkyboxFixTwitching;
	float fSkyboxLightIntensity;

	ID3DXFont* pFont;
};

extern CEngine* Engine;