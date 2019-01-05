#include "Engine.h"

#include <chrono>
#include <psapi.h>
#include <iomanip>

#include "d3d8to9.hpp"
#include "Storm.h"
#include "JassNatives.h"
#include "JassApi.h"

#include "Mesh.h"
#include "SMAA.h"
#include "FColor.h"
#include "MPQ.h"
#include "INIReader.h"
#include "Log.h"

#include "Texture2D.h"
#include "TextureCube.h"

#include "ResourceManager.h"
#include "FontManager.h"
#include "TextureManager.h"
#include "SystemTextures.h"
#include "PostProcessing.h"
#include "CascadedShadows.h"
#include "RenderingHook.h"
#include "AntTweakBar.h"
#include "Camera.h"
#include "GUI.h"

#include "fp_call.h"
#include "GameUI.h"
#include "GameOffsets.h"
#include "CustomJassNatives.h"

//#define USE_ANTTWEAKBAR

const std::string RenderEdgeVersion = "RenderEdge v0.3.0dev";

std::string RenderEdgePath;
HANDLE mpqRenderEdge;

uint32 hotkey_ShowAntTweakBar = 0x76;
uint32 hotkey_PauseGame = -1;
uint32 hotkey_TakeScreenshot = -1;

std::chrono::high_resolution_clock::time_point start_time, last_present_time;
std::chrono::high_resolution_clock::duration last_frame_duration;

D3DXVECTOR4 g_vScreenPositionScaleBias;
D3DXVECTOR4 g_vViewportRect;
D3DXVECTOR4 g_vViewportSize;
D3DXVECTOR4 g_vBufferSize;


float g_fWideScreenMul = 1.0f;

float g_fDeltaTime = 0.0f;
float g_fFPS = 0.0f;
float g_fTimer = 0.0f;

bool g_bDefaultRenderer = false;
bool g_bVsyncEnabled = false;
bool g_bDebugInfo = true;
bool g_bGamePaused = false;
bool g_bTakeScreenshot = false;
bool g_bWindowed = true;

bool g_bFreeCamera = false;
bool g_bDefaultProjectionMatrix = true;
float g_fCameraFoV = 70.0f;
float g_fCameraNearZ = 100.0f;
float g_fCameraFarZ = 5000.0f;
D3DXVECTOR3 g_vCameraPos;
D3DXVECTOR3 g_vCameraRotation;

ID3DXEffect* g_pStandardFX = nullptr;
ID3DXEffect* g_pSkyboxFX = nullptr;


D3DXMATRIX g_mViewProjectionInverse;
//D3DXMATRIX g_mViewProjectionInversePrev;
D3DXMATRIX g_mProjPrev;
D3DXMATRIX g_mProj, g_mView;
D3DXMATRIX g_mProjNonJittered;


bool g_bHDRStarted = false;
bool g_bPostProcessRendered = false;
bool g_bSceneUpdated = false;
bool g_bMapLoaded = false;


bool g_bDefaultLightDir = true;
bool g_bDefaultLightColor = true;
bool g_bDefaultAmbientColor = true;
bool g_bSkyLight = false;
bool g_bUseTemperature = false;
float g_fSkyLightIntensity = 1.0f;
float g_fLightIntensity = 1.0f;
float g_fLightTemperature = 6500.0f;
D3DXVECTOR3 g_vAmbColor = D3DXVECTOR3(0.2f, 0.2f, 0.2f);
D3DXVECTOR3 g_vSkyColor = D3DXVECTOR3(0.314f, 0.392f, 0.471f);
D3DXVECTOR3 g_vIndColor = D3DXVECTOR3(0.40f, 0.28f, 0.20f);
D3DXVECTOR3 g_vLightDir = D3DXVECTOR3(-0.4f, 0.8f, -0.5f);
D3DXVECTOR3 g_vLightColor = D3DXVECTOR3(1.0f, 1.0f, 1.0f);


bool g_bMaterialColorSRGB = true;
bool g_bVertexColorSRGB = true;
bool g_bAmbientColorSRGB = true;
bool g_bLightColorSRGB = true;
bool g_bPointLightColorSRGB = true;
bool g_bFogColorSRGB = true;


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


bool g_bEnableFog = true;
bool g_bDefaultFog = true;
EFogTech g_iFogTech = EFogTech::Linear;
D3DXVECTOR3 g_vFogColor = D3DXVECTOR3(0.5f, 0.6f, 0.7f);
float g_fFogStart = 0.0f;
float g_fFogEnd = 5000.0f;
float g_fFogDensity = 0.1f;
float g_fFogHeight = 1000.0f;
float g_fFogMaxOpacity = 1.0f;
float g_fFogHeightFalloff = 1.0f;
float g_fFogCutoffDistance = 0.0f;
bool g_bFogSun = false;
D3DXVECTOR3 g_vFogSunColor = D3DXVECTOR3(1.0f, 0.9f, 0.7f);
float g_fFogSunIntensity = 8.0f;
float g_fFogSunStartDistance = 3000.0f;

//bool g_bGlobalFog = false;
D3DXVECTOR3 g_vGlobalFogColor;
float g_fGlobalFogStart;
float g_fGlobalFogEnd;
float g_fGlobalFogDensity;
EFogTech g_iGlobalFogTech;


bool g_bDebugPointLight = false;
bool g_bDebugLightMousePos = false;
bool g_bDebugLightUseTemperature = false;
float g_fDebugLightTemperature = 6500.0f;
D3DXVECTOR4 g_vDebugLightColorAndIntensity = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 5000.0f);
D3DXVECTOR4 g_vDebugLightPosAndInvRadius = D3DXVECTOR4(0.0f, 0.0f, 150.0f, 1000.0f);
ELightUnits g_DebugLightIntensityUnits = ELightUnits::Unitless;


bool g_bTexture = true;
bool g_bMaterialColor = true;
bool g_bVertexColor = true;
bool g_bTranslucentMaterials = true;
bool g_bUnshadedMaterials = true;
bool g_bUnfoggedMaterials = true;
bool g_bAnisoFiltering = true;
uint32 g_iMaxAnisotropy = 16;

D3DXVECTOR3 g_vGlobalLightDir;
D3DXVECTOR3 g_vGlobalLightColor;
D3DXVECTOR3 g_vGlobalAmbientColor;


bool g_bGlobalPointLight = false;
bool g_bPointLight = false;
uint32 g_iPointLightCount = 0;
ELightUnits g_DefaultPointLightIntensityUnits = ELightUnits::Unitless;
float g_fDefaultPointLightIntensity = 100.0f;
float g_fDefaultPointLightRadius = 10000.0f;
FColor g_vPointLightColorAndIntensity[8];
FColor g_vPointLightPosAndInvRadius[8];


bool g_bUserInterface = true;
bool g_bCustomUserInterface = true;
float g_fDebugValue = 1.0f;
D3DXVECTOR2 g_vBlackBorders = D3DXVECTOR2(-0.02f, 0.13f);

bool g_bFogOfWar = true;
bool g_bMaskedObjects = true;
bool g_bBuildingsShadows = true;
bool g_bUnitsShadows = false;
bool g_bMapBounds = true;
uint32 g_iFoggedObjectColor = 0;
uint32 g_iFoggedTerrainColor = 0;
uint32 g_iMaskedObjectColor = 0;
uint32 g_iMaskedTerrainColor = 0;
uint32 g_iBoundaryTerrainColor = 0;
uint32 g_iBoundaryObjectColor = 0;
uint32 g_iFoggedBoundaryTerrainColor = 0;
uint32 g_iFoggedBoundaryObjectColor = 0;

bool g_bIBL = false;
float g_fEnvCubemapRotation = 0.0f;
float g_fCubemapBrightness = 1.0f;
bool g_bEnvCubemapSwapYZ = true;
TextureCube g_envTexture;
std::string g_envTextureFileName = "Textures\\Environment.dds";

float g_fTerrainRoughness = 0.9f;
float g_fTerrainMetallic = 0.0f;
float g_fTerrainSpecular = 0.5f;
bool g_bNormalMapping = false;
Texture2D g_normalTexture;
std::string g_normalTextureFileName = "Textures\\test_normal.png";

bool g_bPBS = false;
bool g_bSimpleMaterial = false;
float g_fMaterialRoughness = 0.9f;
float g_fMaterialMetallic = 0.0f;
float g_fMaterialSpecular = 0.5f;
float g_fMaterialTranslucent = 0.0f;


IDirect3DSurface9* g_pBackBuffer;
TextureRenderTarget2D g_depthRT;
TextureRenderTarget2D g_mainRT;
ETextureFormat g_depthFormat;
bool g_bEnableHDR = false;
uint32 g_iFrameIndexMod8 = 0;


bool g_bSkyboxShading = true;
bool g_bSkyboxFog = false;
bool g_bSkyboxFixTwitching = false;
float g_fSkyboxLightIntensity = 1.0f;


ID3DXFont* g_pFont;



void ApplyFogOfWarEx(uint32 id, uint32 boundedColor, uint32 foggedColor, uint32 maskedColor)
{
	uint32 pTerrain = Jass::GetTerrain();
	this_call<int>(address_ApplyFogOfWarEx, pTerrain, id, &boundedColor, &foggedColor, &maskedColor);
}

uint32 MiscDataGetColor(char* section, char* key)
{
	uint32 color;
	return *fast_call<uint32*>(address_MiscDataGetColor, &color, section, key, 0);
}

void UpdateWidescreenFix(float aspectRatio)
{
	g_fWideScreenMul = aspectRatio * 0.75f;
}

void SetScreenMode(bool bWindowed)
{
	static LONG DefaultWindowStyle = 382664704;
	static LONG DefaultWindowExStyle = WS_EX_APPWINDOW | WS_EX_WINDOWEDGE;
	static RECT OldWindowRect = { 100, 100, 900, 700 };

	if (bWindowed)
	{
		uint32 width = OldWindowRect.right - OldWindowRect.left;
		uint32 height = OldWindowRect.bottom - OldWindowRect.top;

		SetWindowLongPtr(Input::hWnd, GWL_EXSTYLE, DefaultWindowExStyle);
		SetWindowLongPtr(Input::hWnd, GWL_STYLE, DefaultWindowStyle);
		SetWindowPos(Input::hWnd, HWND_NOTOPMOST, OldWindowRect.left, OldWindowRect.top, width, height, 0);
	}
	else
	{
		GetWindowRect(Input::hWnd, &OldWindowRect);
		DefaultWindowStyle = GetWindowLong(Input::hWnd, GWL_STYLE);
		DefaultWindowExStyle = GetWindowLong(Input::hWnd, GWL_EXSTYLE);

		HDC windowHDC = GetDC(Input::hWnd);
		uint32 width = GetDeviceCaps(windowHDC, HORZRES);
		uint32 height = GetDeviceCaps(windowHDC, VERTRES);

		SetWindowLongPtr(Input::hWnd, GWL_EXSTYLE, WS_EX_APPWINDOW);
		SetWindowLongPtr(Input::hWnd, GWL_STYLE, WS_POPUP | WS_VISIBLE);
		SetWindowPos(Input::hWnd, HWND_TOPMOST, 0, 0, width, height, SWP_SHOWWINDOW);
	}
}

double GetTime()
{
	auto beginningOfTime = std::chrono::system_clock::now().time_since_epoch();
	auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(beginningOfTime).count();

	return ms * 0.001;
}

void CalculateFrameRate()
{
	static double framesPerSecond = 0.0;
	static double startTime = GetTime();
	static double lastTime = GetTime();
	static double currentFPS = 0.0;

	double CurrentTime = GetTime();

	g_fDeltaTime = CurrentTime - lastTime;
	lastTime = CurrentTime;
	++framesPerSecond;

	if (CurrentTime - startTime > 1.0)
	{
		startTime = CurrentTime;
		g_fFPS = framesPerSecond;
		framesPerSecond = 0;
	}
}



void TW_CALL CAntTweakBar::SetPauseGame_cb(const void *value, void *clientData)
{
	if (!IsGaming() || IsInGameMenu())
		return;

	g_bGamePaused = *(const bool*)value;
	JassNatives::PauseGame(g_bGamePaused);
}
void TW_CALL CAntTweakBar::GetPauseGame_cb(void *value, void *clientData)
{
	*(bool*)value = IsGamePaused();
}

void UpdateFreeCamera()
{
	CGameUI* pGameUI = GetGameUI(0, 0);
	if (!pGameUI)
		return;

	bool bUserControl = !g_bFreeCamera;
	if (bUserControl != pGameUI->isUserInputEnabled)
		JassNatives::EnableUserControl(bUserControl);

	if (FreeCamera)
		FreeCamera->SetActive(g_bFreeCamera);
}
void TW_CALL CAntTweakBar::SetFreeCamera_cb(const void *value, void *clientData)
{
	if (!FreeCamera || !IsGaming())
		return;

	g_bFreeCamera = *(const bool*)value;

	UpdateFreeCamera();
}
void TW_CALL CAntTweakBar::GetFreeCamera_cb(void *value, void *clientData)
{
	*(bool*)value = g_bFreeCamera;
}

void TW_CALL CAntTweakBar::SetVsync_cb(const void *value, void *clientData)
{
	const bool bValue = *(const bool*)value;

	if (g_bVsyncEnabled != bValue)
	{
		g_bVsyncEnabled = bValue;
		ForceResetDevice8();
	}
}
void TW_CALL CAntTweakBar::GetVsync_cb(void *value, void *clientData)
{
	*(bool*)value = g_bVsyncEnabled;
}

void TW_CALL CAntTweakBar::SetScreenMode_cb(const void *value, void *clientData)
{
	const bool bValue = *(const bool*)value;

	if (g_bWindowed != bValue)
	{
		g_bWindowed = bValue;
		Input::CenterMouse();
		SetScreenMode(g_bWindowed);
		ForceResetDevice8();
	}
}
void TW_CALL CAntTweakBar::GetScreenMode_cb(void *value, void *clientData)
{
	*(bool*)value = g_bWindowed;
}

void UpdateUserInterface()
{
	CGameUI* pGameUI = GetGameUI(0, 0);
	if (!pGameUI)
		return;

	uint32 pWorldFrameWar3 = pGameUI->WorldFrameWar3 + 180;
	uint32 pRootFrame = (uint32)pGameUI + 180;

	if (g_bUserInterface)
	{
		SetFramePoint(pWorldFrameWar3, EFramePoint::TopRight, pRootFrame, EFramePoint::TopRight, 0.0f, g_vBlackBorders.x);
		SetFramePoint(pWorldFrameWar3, EFramePoint::BottomLeft, pRootFrame, EFramePoint::BottomLeft, 0.0f, g_vBlackBorders.y);
	}
	else
	{
		g_vBlackBorders.x = GetFramePointY(pWorldFrameWar3, EFramePoint::TopRight);
		g_vBlackBorders.y = GetFramePointY(pWorldFrameWar3, EFramePoint::BottomLeft);

		SetFramePoint(pWorldFrameWar3, EFramePoint::TopRight, pRootFrame, EFramePoint::TopRight, 0.0f, 0.0f);
		SetFramePoint(pWorldFrameWar3, EFramePoint::BottomLeft, pRootFrame, EFramePoint::BottomLeft, 0.0f, 0.0f);
	}
}
void TW_CALL CAntTweakBar::SetUserInterface_cb(const void *value, void *clientData)
{
	g_bUserInterface = *(const bool*)value;

	UpdateUserInterface();
}
void TW_CALL CAntTweakBar::GetUserInterface_cb(void *value, void *clientData)
{
	*(bool*)value = g_bUserInterface;
}

void UpdateMaskedObject()
{
	if (g_bMaskedObjects)
		ApplyFogOfWarEx(2, 0xFFFFFFFF, g_iFoggedObjectColor, g_iMaskedObjectColor);
	else
		ApplyFogOfWarEx(2, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF);
}
void TW_CALL CAntTweakBar::SetMaskedObject_cb(const void *value, void *clientData)
{
	if (!IsGaming())
		return;

	g_bMaskedObjects = *(const bool*)value;

	UpdateMaskedObject();
}
void TW_CALL CAntTweakBar::GetMaskedObject_cb(void *value, void *clientData)
{
	*(bool*)value = g_bMaskedObjects;
}

void UpdateBuildingsShadows()
{
	if (g_bBuildingsShadows)
		ApplyFogOfWarEx(0, 0x00000000, g_iFoggedTerrainColor, g_iMaskedTerrainColor);
	else
		ApplyFogOfWarEx(0, 0x00000000, 0x00000000, g_iMaskedTerrainColor);
}
void TW_CALL CAntTweakBar::SetBuildingsShadows_cb(const void *value, void *clientData)
{
	if (!IsGaming())
		return;

	g_bBuildingsShadows = *(const bool*)value;

	UpdateBuildingsShadows();
}
void TW_CALL CAntTweakBar::GetBuildingsShadows_cb(void *value, void *clientData)
{
	*(bool*)value = g_bBuildingsShadows;
}

void UpdateMapBounds()
{
	if (g_bMapBounds)
	{
		ApplyFogOfWarEx(1, g_iBoundaryTerrainColor, g_iFoggedBoundaryTerrainColor, g_iMaskedTerrainColor);
		ApplyFogOfWarEx(3, g_iBoundaryObjectColor, g_iFoggedBoundaryObjectColor, g_iMaskedObjectColor);
	}
	else
	{
		ApplyFogOfWarEx(1, 0x00000000, 0x00000000, 0x00000000);
		ApplyFogOfWarEx(3, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF);
	}
}
void TW_CALL CAntTweakBar::SetMapBounds_cb(const void *value, void *clientData)
{
	if (!IsGaming())
		return;

	g_bMapBounds = *(const bool*)value;

	UpdateMapBounds();
}
void TW_CALL CAntTweakBar::GetMapBounds_cb(void *value, void *clientData)
{
	*(bool*)value = g_bMapBounds;
}

void TW_CALL CAntTweakBar::SetLutFloat_cb(const void *value, void *clientData)
{
	*static_cast<float*>(clientData) = *static_cast<const float*>(value);

	if (PostProcessing)
		PostProcessing->bUpdateLUT = true;
}
void TW_CALL CAntTweakBar::SetLutBool_cb(const void *value, void *clientData)
{
	*static_cast<bool*>(clientData) = *static_cast<const bool*>(value);

	if (PostProcessing)
		PostProcessing->bUpdateLUT = true;
}
void TW_CALL CAntTweakBar::SetLutColor_cb(const void *value, void *clientData)
{
	*static_cast<D3DXVECTOR3*>(clientData) = *static_cast<const D3DXVECTOR3*>(value);

	if (PostProcessing)
		PostProcessing->bUpdateLUT = true;
}
void TW_CALL CAntTweakBar::GetLutFloat_cb(void *value, void *clientData)
{
	*static_cast<float*>(value) = *static_cast<const float*>(clientData);
}
void TW_CALL CAntTweakBar::GetLutBool_cb(void *value, void *clientData)
{
	*static_cast<bool*>(value) = *static_cast<const bool*>(clientData);
}
void TW_CALL CAntTweakBar::GetLutColor_cb(void *value, void *clientData)
{
	*static_cast<D3DXVECTOR3*>(value) = *static_cast<const D3DXVECTOR3*>(clientData);
}

bool g_bRenderStagesChecked = true;
void TW_CALL CAntTweakBar::CheckAllRenderStages_cb(void *clientData)
{
	g_bRenderStagesChecked = !g_bRenderStagesChecked;

	RenderingHook::bRenderSkybox = g_bRenderStagesChecked;
	RenderingHook::bRenderTerrain = g_bRenderStagesChecked;
	RenderingHook::bRenderFogOfWar = g_bRenderStagesChecked;
	RenderingHook::bRenderTerrainShadow = g_bRenderStagesChecked;
	RenderingHook::bRenderWaterShadow = g_bRenderStagesChecked;
	RenderingHook::bRenderWeather = g_bRenderStagesChecked;
	RenderingHook::bRenderSelectionCircle = g_bRenderStagesChecked;
	RenderingHook::bRenderFootprint = g_bRenderStagesChecked;
	RenderingHook::bRenderDecoration = g_bRenderStagesChecked;
	RenderingHook::bRenderUnit = g_bRenderStagesChecked;
	RenderingHook::bRenderDestructible = g_bRenderStagesChecked;
	RenderingHook::bRenderWater = g_bRenderStagesChecked;
	RenderingHook::bRenderSelectionBox = g_bRenderStagesChecked;
	RenderingHook::bRenderBuilding = g_bRenderStagesChecked;
	RenderingHook::bRenderUbersplat = g_bRenderStagesChecked;
	RenderingHook::bRenderUnknown1 = g_bRenderStagesChecked;
	RenderingHook::bRenderIndicator = g_bRenderStagesChecked;
	RenderingHook::bRenderUnknown2 = g_bRenderStagesChecked;
	RenderingHook::bRenderUnknown3 = g_bRenderStagesChecked;
	RenderingHook::bRenderOcclusionMask = g_bRenderStagesChecked;
	RenderingHook::bRenderLightning = g_bRenderStagesChecked;
	RenderingHook::bRenderFloatingText = g_bRenderStagesChecked;
	RenderingHook::bRenderCineFilter = g_bRenderStagesChecked;
}

void TW_CALL CAntTweakBar::ReloadShaders_cb(void *clientData)
{
	if (Engine)
		Engine->ReloadShaders();
}

void CAntTweakBar::Init()
{
	if (!TwInit(TW_DIRECT3D9, m_pDevice))
	{
		Message(TwGetLastError(), "Failed to initialize AntTweakBar");
		return;
	}

	TwWindowSize(g_vBufferSize.x, g_vBufferSize.y);


	TwEnumVal debugScreenEV[] =
	{
		{ (uint32)EDebugScreen::SceneColor, "Scene Color" },
		{ (uint32)EDebugScreen::SceneDepth, "Scene Depth" },
		{ (uint32)EDebugScreen::CascadedShadows, "Cascaded Shadows" },
		{ (uint32)EDebugScreen::ContactShadows, "Contact Shadows" },
		{ (uint32)EDebugScreen::BloomBrightPass, "Bloom Bright Pass" },
		{ (uint32)EDebugScreen::SSAO, "Ambient Occlusion" },
		{ (uint32)EDebugScreen::SSR, "Screen Space Reflections" }
	};

	TwEnumVal smaaInputEV[] =
	{
		{ (uint32)SMAA::INPUT_LUMA, "Luma" },
		{ (uint32)SMAA::INPUT_COLOR, "Color" },
		{ (uint32)SMAA::INPUT_DEPTH, "Depth" }
	};

	TwEnumVal fogTechEV[] =
	{
		{ (uint32)EFogTech::Linear, "Linear" },
		{ (uint32)EFogTech::Exponential, "Exponential" },
		{ (uint32)EFogTech::Exponential2, "Exponential Squared" },
		{ (uint32)EFogTech::HeightBased, "Height Based" }
	};

	TwEnumVal lightUnitsEV[] =
	{
		{ (uint32)ELightUnits::Unitless, "Unitless" },
		{ (uint32)ELightUnits::Candelas, "Candelas" },
		{ (uint32)ELightUnits::Lumens, "Lumens" }
	};

	TwEnumVal cullModeEV[] =
	{
		{ (uint32)D3DCULL::D3DCULL_NONE, "None" },
		{ (uint32)D3DCULL::D3DCULL_CW, "Clockwise" },
		{ (uint32)D3DCULL::D3DCULL_CCW, "Counterclockwise" }
	};

	TwEnumVal colorGamutEV[] =
	{
		{ 0, "Rec709 / sRGB, D65" },
		{ 1, "DCI-P3, D65" },
		{ 2, "Rec2020 / BT2020, D65" },
		{ 3, "ACES, D60" },
		{ 4, "ACEScg, D60" }
	};

	TwEnumVal outputDeviceEV[] =
	{
		{ 0, "sRGB (LDR)" },
		{ 1, "Rec709 (LDR)" },
		{ 2, "Explicit gamma mapping (LDR)" },
		{ 3, "ACES 1000 nit ST-2084 (Dolby PQ) (HDR)" },
		{ 4, "ACES 2000 nit ST-2084 (Dolby PQ) (HDR)" },
		{ 5, "ACES 1000 nit ScRGB (HDR)" },
		{ 6, "ACES 2000 nit ScRGB (HDR)" }
	};

	TwStructMember pointMembers[] = {
		{ "X", TW_TYPE_FLOAT, offsetof(D3DXVECTOR3, x), " step=1 precision=3 " },
		{ "Y", TW_TYPE_FLOAT, offsetof(D3DXVECTOR3, y), " step=1 precision=3 " },
		{ "Z", TW_TYPE_FLOAT, offsetof(D3DXVECTOR3, z), " step=1 precision=3 " }
	};

	TwType debugScreenListType = TwDefineEnum("Debug Screen", debugScreenEV, 7);
	TwType smaaInputListType = TwDefineEnum("SMAA Input", smaaInputEV, 3);
	TwType fogTechListType = TwDefineEnum("Fog Tech", fogTechEV, 4);
	TwType lightUnitsListType = TwDefineEnum("Intensity Units", lightUnitsEV, 3);
	TwType cullModeListType = TwDefineEnum("Culling Mode", cullModeEV, 3);
	TwType colorGamutListType = TwDefineEnum("Color Gamut", colorGamutEV, 5);
	TwType outputDeviceListType = TwDefineEnum("Output Device", outputDeviceEV, 3);
	TwType pointType = TwDefineStruct("POINT", pointMembers, 3, sizeof(D3DXVECTOR3), NULL, NULL);


	TwBar* bar = TwNewBar("RenderEdge");
	TwDefine(" RenderEdge color='128 128 128' alpha=128 fontsize=3 refresh=0 size='280 460' position='10 32' contained=true ");

	// Engine
	// ===========================================================
	TwAddVarRW(bar, "bDefaultRenderer", TW_TYPE_BOOLCPP, &g_bDefaultRenderer, " group='Engine' label='Default Renderer' ");
	TwAddVarCB(bar, "bGamePaused", TW_TYPE_BOOLCPP, SetPauseGame_cb, GetPauseGame_cb, nullptr, " group='Engine' label='Pause Game' ");
	TwAddVarRW(bar, "bDebugInfo", TW_TYPE_BOOLCPP, &g_bDebugInfo, " group='Engine' label='Debug Info' ");
	TwAddSeparator(bar, "", " group='Engine' ");
	TwAddVarCB(bar, "bWindowed", TW_TYPE_BOOLCPP, SetScreenMode_cb, GetScreenMode_cb, nullptr, " group='Engine' readonly=true label='Windowed' ");
	TwAddVarCB(bar, "bVsyncEnabled", TW_TYPE_BOOLCPP, SetVsync_cb, GetVsync_cb, nullptr, " group='Engine' label='V-Sync' ");
	TwAddSeparator(bar, "", " group='Engine' ");
	TwAddButton(bar, "ReloadShaders", ReloadShaders_cb, nullptr, " group='Engine' label='Reload Shaders' ");
	TwDefine(" RenderEdge/'Engine' opened=true");

	// Camera
	// ===========================================================
	TwAddVarCB(bar, "bFreeCamera", TW_TYPE_BOOLCPP, SetFreeCamera_cb, GetFreeCamera_cb, nullptr, " group='Camera' label='Free Camera' ");
	TwAddVarRW(bar, "bDefaultProjectionMatrix", TW_TYPE_BOOLCPP, &g_bDefaultProjectionMatrix, " group='Camera' label='Constant Vertical FoV' ");
	if (FreeCamera)
		TwAddVarRW(bar, "fCameraSpeed", TW_TYPE_FLOAT, &FreeCamera->m_fSpeed, " group='Camera' min=0.01 step=0.01 label='Free Camera Speed' ");
	TwAddVarRW(bar, "fCameraFoV", TW_TYPE_FLOAT, &g_fCameraFoV, " group='Camera' min=5 max=220 step=1 label='FoV' ");
	TwAddVarRW(bar, "fCameraNearZ", TW_TYPE_FLOAT, &g_fCameraNearZ, " group='Camera' min=1 step=1 label='NearZ' ");
	TwAddVarRW(bar, "fCameraFarZ", TW_TYPE_FLOAT, &g_fCameraFarZ, " group='Camera' min=1 step=1 label='FarZ' ");
	TwAddVarRW(bar, "fCameraPosition", pointType, &g_vCameraPos, " group='Camera' readonly=true label='Position' ");
	TwDefine(" RenderEdge/'Camera' opened=false");

	// Render Stages
	// ===========================================================
	TwAddVarCB(bar, "bUserInterface", TW_TYPE_BOOLCPP, SetUserInterface_cb, GetUserInterface_cb, nullptr, " group='Render Stages' label='User Interface' ");
	TwAddVarRW(bar, "bCustomUserInterface", TW_TYPE_BOOLCPP, &g_bCustomUserInterface, " group='Render Stages' label='Custom User Interface' ");
	TwAddSeparator(bar, "", " group='Render Stages' ");
	TwAddButton(bar, "CheckUncheckAllCB", CheckAllRenderStages_cb, nullptr, " group='Render Stages' label='Check/Uncheck All' ");
	TwAddSeparator(bar, "", " group='Render Stages' ");
	TwAddVarRW(bar, "bRenderSkybox", TW_TYPE_BOOLCPP, &RenderingHook::bRenderSkybox, " group='Render Stages' label='Skybox' ");
	TwAddVarRW(bar, "bRenderTerrain", TW_TYPE_BOOLCPP, &RenderingHook::bRenderTerrain, " group='Render Stages' label='Terrain' ");
	TwAddVarRW(bar, "bRenderDestructible", TW_TYPE_BOOLCPP, &RenderingHook::bRenderDestructible, " group='Render Stages' label='Destructibles' ");
	TwAddVarRW(bar, "bRenderUbersplat", TW_TYPE_BOOLCPP, &RenderingHook::bRenderUbersplat, " group='Render Stages' label='Ubersplats' ");
	TwAddVarRW(bar, "bRenderFootprint", TW_TYPE_BOOLCPP, &RenderingHook::bRenderFootprint, " group='Render Stages' label='Footprints' ");
	TwAddVarRW(bar, "bRenderFogOfWar", TW_TYPE_BOOLCPP, &RenderingHook::bRenderFogOfWar, " group='Render Stages' label='Fog Of War' ");
	TwAddVarRW(bar, "bRenderTerrainShadow", TW_TYPE_BOOLCPP, &RenderingHook::bRenderTerrainShadow, " group='Render Stages' label='Units Shadows (Terrain)' ");
	TwAddVarRW(bar, "bRenderIndicator", TW_TYPE_BOOLCPP, &RenderingHook::bRenderIndicator, " group='Render Stages' label='Indicator' ");
	TwAddVarRW(bar, "bRenderOcclusionMask", TW_TYPE_BOOLCPP, &RenderingHook::bRenderOcclusionMask, " group='Render Stages' label='OcclusionMask' ");
	TwAddVarRW(bar, "bRenderWater", TW_TYPE_BOOLCPP, &RenderingHook::bRenderWater, " group='Render Stages' label='Water' ");
	TwAddVarRW(bar, "bRenderUnknown1", TW_TYPE_BOOLCPP, &RenderingHook::bRenderUnknown1, " group='Render Stages' label='Unknown1' ");
	TwAddVarRW(bar, "bRenderDecoration", TW_TYPE_BOOLCPP, &RenderingHook::bRenderDecoration, " group='Render Stages' label='Decorations' ");
	TwAddVarRW(bar, "bRenderUnknown2", TW_TYPE_BOOLCPP, &RenderingHook::bRenderUnknown2, " group='Render Stages' label='Unknown2' ");
	TwAddVarRW(bar, "bRenderUnit", TW_TYPE_BOOLCPP, &RenderingHook::bRenderUnit, " group='Render Stages' label='Units' ");
	TwAddVarRW(bar, "bRenderWaterShadow", TW_TYPE_BOOLCPP, &RenderingHook::bRenderWaterShadow, " group='Render Stages' label='Units Shadows (Water)' ");
	TwAddVarRW(bar, "bRenderSelectionCircle", TW_TYPE_BOOLCPP, &RenderingHook::bRenderSelectionCircle, " group='Render Stages' label='Selection Circles' ");
	TwAddVarRW(bar, "bRenderWeather", TW_TYPE_BOOLCPP, &RenderingHook::bRenderWeather, " group='Render Stages' label='Weather Effects' ");
	TwAddVarRW(bar, "bRenderLightning", TW_TYPE_BOOLCPP, &RenderingHook::bRenderLightning, " group='Render Stages' label='Lightnings' ");
	TwAddVarRW(bar, "bRenderSelectionBox", TW_TYPE_BOOLCPP, &RenderingHook::bRenderSelectionBox, " group='Render Stages' label='Selection Box' ");
	TwAddVarRW(bar, "bRenderBuilding", TW_TYPE_BOOLCPP, &RenderingHook::bRenderBuilding, " group='Render Stages' label='Buildings' ");
	TwAddVarRW(bar, "bRenderFloatingText", TW_TYPE_BOOLCPP, &RenderingHook::bRenderFloatingText, " group='Render Stages' label='Floating Text' ");
	TwAddVarRW(bar, "bRenderCineFilter", TW_TYPE_BOOLCPP, &RenderingHook::bRenderCineFilter, " group='Render Stages' label='Cine Filter' ");
	TwDefine(" RenderEdge/'Render Stages' opened=false");

	TwAddSeparator(bar, "", "");

	// Terrain
	// ===========================================================
	if (CascadedShadows)
	{
		TwAddVarRW(bar, "bTerrainShadows", TW_TYPE_BOOLCPP, &CascadedShadows->bTerrainShadows, " group='Terrain' label='Cast Shadows' ");
		TwAddSeparator(bar, "", " group='Terrain' ");
	}
	TwAddVarRW(bar, "bNormalMapping", TW_TYPE_BOOLCPP, &g_bNormalMapping, " group='Terrain' label='Normal Mapping' ");
	TwAddVarRW(bar, "fTerrainRoughness", TW_TYPE_FLOAT, &g_fTerrainRoughness, " group='Terrain' min=0 max=1 step=0.01 label='Roughness' ");
	TwAddVarRW(bar, "fTerrainMetallic", TW_TYPE_FLOAT, &g_fTerrainMetallic, " group='Terrain' min=0 max=1 step=0.01 label='Metallic' ");
	TwAddVarRW(bar, "fTerrainSpecular", TW_TYPE_FLOAT, &g_fTerrainSpecular, " group='Terrain' min=0 max=1 step=0.01 label='Specular' ");
	TwDefine(" RenderEdge/'Terrain' opened=false");

	// Objects
	// ===========================================================
	if (CascadedShadows)
	{
		TwAddVarRW(bar, "bObjectsShadows", TW_TYPE_BOOLCPP, &CascadedShadows->bObjectsShadows, " group='Objects' label='Cast Shadows' ");
		TwAddSeparator(bar, "", " group='Objects' ");
	}
	TwAddVarRW(bar, "fMaterialRoughness", TW_TYPE_FLOAT, &g_fMaterialRoughness, " group='Objects' min=0 max=1 step=0.01 label='Roughness' ");
	TwAddVarRW(bar, "fMaterialMetallic", TW_TYPE_FLOAT, &g_fMaterialMetallic, " group='Objects' min=0 max=1 step=0.01 label='Metallic' ");
	TwAddVarRW(bar, "fMaterialSpecular", TW_TYPE_FLOAT, &g_fMaterialSpecular, " group='Objects' min=0 max=1 step=0.01 label='Specular' ");
	TwAddVarRW(bar, "fMaterialTranslucent", TW_TYPE_FLOAT, &g_fMaterialTranslucent, " group='Objects' min=0 max=1 step=0.01 label='Translucent' ");
	TwAddSeparator(bar, "", " group='Objects' ");
	//TwAddVarRW(bar, "bNormalMapping", TW_TYPE_BOOLCPP, &g_bNormalMapping, " group='Objects' label='Normal Mapping' ");
	TwAddVarRW(bar, "bEnableMaterialColor", TW_TYPE_BOOLCPP, &g_bMaterialColor, " group='Objects' label='Material Color' ");
	TwAddVarRW(bar, "bEnableVertexColor", TW_TYPE_BOOLCPP, &g_bVertexColor, " group='Objects' label='Vertex Color' ");
	TwAddVarRW(bar, "bUnshadedMaterials", TW_TYPE_BOOLCPP, &g_bUnshadedMaterials, " group='Objects' label='Unshaded Materials' ");
	TwAddVarRW(bar, "bUnfoggedMaterials", TW_TYPE_BOOLCPP, &g_bUnfoggedMaterials, " group='Objects' label='Unfogged Materials' ");
	TwAddSeparator(bar, "", " group='Objects' ");
	TwAddVarRW(bar, "bSRGBMaterialColor", TW_TYPE_BOOLCPP, &g_bMaterialColorSRGB, " group='Objects' label='sRGB Material Color' ");
	TwAddVarRW(bar, "bSRGBVertexColor", TW_TYPE_BOOLCPP, &g_bVertexColorSRGB, " group='Objects' label='sRGB Vertex Color' ");
	TwDefine(" RenderEdge/'Objects' opened=false");

	// Skybox
	// ===========================================================
	TwAddVarRW(bar, "bSkyboxLighting", TW_TYPE_BOOLCPP, &g_bSkyboxShading, " group='Skybox' label='Shading' ");
	TwAddVarRW(bar, "bSkyboxFog", TW_TYPE_BOOLCPP, &g_bSkyboxFog, " group='Skybox' label='Use Fog Color' ");
	TwAddVarRW(bar, "bFixSkyboxTwitching", TW_TYPE_BOOLCPP, &g_bSkyboxFixTwitching, " group='Skybox' label='Fix Twitching' ");
	TwAddVarRW(bar, "fSkyboxLightIntensity", TW_TYPE_FLOAT, &g_fSkyboxLightIntensity, " group='Skybox' min=0 step=0.01 label='Brightness' ");
	TwDefine(" RenderEdge/'Skybox' opened=false");

	// Fog of War
	// ===========================================================
	TwAddVarCB(bar, "bBuildingsShadows", TW_TYPE_BOOLCPP, SetBuildingsShadows_cb, GetBuildingsShadows_cb, nullptr, " group='Fog of War' label='Buildings Shadows' ");
	TwAddVarCB(bar, "bMaskedObjects", TW_TYPE_BOOLCPP, SetMaskedObject_cb, GetMaskedObject_cb, nullptr, " group='Fog of War' label='Masked Objects' ");
	TwAddVarCB(bar, "bMapBounds", TW_TYPE_BOOLCPP, SetMapBounds_cb, GetMapBounds_cb, nullptr, " group='Fog of War' label='Map Bounds' ");
	TwDefine(" RenderEdge/'Fog of War' opened=false");

	TwAddSeparator(bar, "", "");

	// Sky Light
	// ===========================================================
	TwAddVarRW(bar, "bUseDefLightAmbient", TW_TYPE_BOOLCPP, &g_bDefaultAmbientColor, " group='Sky Light' label='Default Color' ");
	TwAddVarRW(bar, "bSRGBAmbientLightColor", TW_TYPE_BOOLCPP, &g_bAmbientColorSRGB, " group='Sky Light' label='sRGB Color' ");
	TwAddVarRW(bar, "vAmbColor", TW_TYPE_COLOR3F, &g_vAmbColor, " group='Sky Light' label='Ambient Color' ");
	TwAddSeparator(bar, "", " group='Sky Light' ");
	TwAddVarRW(bar, "bEnableSkyLight", TW_TYPE_BOOLCPP, &g_bSkyLight, " group='Sky Light' label='Enabled' ");
	TwAddVarRW(bar, "fSkyLightIntensity", TW_TYPE_FLOAT, &g_fSkyLightIntensity, " group='Sky Light' min=0 step=0.01 label='Intensity' ");
	TwAddVarRW(bar, "vSkyColor", TW_TYPE_COLOR3F, &g_vSkyColor, " group='Sky Light' label='Sky' ");
	TwAddVarRW(bar, "vIndColor", TW_TYPE_COLOR3F, &g_vIndColor, " group='Sky Light' label='Indirect' ");
	TwDefine(" RenderEdge/'Sky Light' opened=false");

	// Directional Light
	// ===========================================================
	TwAddVarRW(bar, "bUseDefLightDir", TW_TYPE_BOOLCPP, &g_bDefaultLightDir, " group='Directional Light' label='Default Direction' ");
	TwAddVarRW(bar, "bUseDefLightColor", TW_TYPE_BOOLCPP, &g_bDefaultLightColor, " group='Directional Light' label='Default Color' ");
	TwAddVarRW(bar, "bSRGBLightColor", TW_TYPE_BOOLCPP, &g_bLightColorSRGB, " group='Directional Light' label='sRGB Color' ");
	TwAddSeparator(bar, "", " group='Directional Light' ");
	TwAddVarRW(bar, "fLightIntensity", TW_TYPE_FLOAT, &g_fLightIntensity, " group='Directional Light' min=0 step=0.01 label='Intensity' ");
	TwAddVarRW(bar, "vLightColor", TW_TYPE_COLOR3F, &g_vLightColor, " group='Directional Light' label='Color' ");
	TwAddVarRW(bar, "vLightDir", TW_TYPE_DIR3F, &g_vLightDir, " group='Directional Light' opened=false axisz=z showval=true label='Direction' ");
	TwAddVarRW(bar, "fLightTemperature", TW_TYPE_FLOAT, &g_fLightTemperature, " group='Directional Light' min=1700 max=12000 step=1 label='Temperature' ");
	TwAddVarRW(bar, "bUseTemperature", TW_TYPE_BOOLCPP, &g_bUseTemperature, " group='Directional Light' label='Use Temperature' ");
	TwDefine(" RenderEdge/'Directional Light' opened=false");

	// Point Light
	// ===========================================================
	TwAddVarRW(bar, "bEnablePointLight", TW_TYPE_BOOLCPP, &g_bPointLight, " group='Point Light' label='Enabled' ");
	TwAddVarRW(bar, "bSRGBPointLightColor", TW_TYPE_BOOLCPP, &g_bPointLightColorSRGB, " group='Point Light' label='sRGB Color' ");
	TwAddVarRW(bar, "DefaultPointLightIntensityUnits", lightUnitsListType, &g_DefaultPointLightIntensityUnits, " group='Point Light' label='Intensity Units' ");
	TwAddVarRW(bar, "fDefaultPointLightIntensity", TW_TYPE_FLOAT, &g_fDefaultPointLightIntensity, " group='Point Light' min=0 step=0.01 label='Intensity Multiplier' ");
	TwAddVarRW(bar, "fDefaultPointLightRadius", TW_TYPE_FLOAT, &g_fDefaultPointLightRadius, " group='Point Light' min=0 max=10000.0 step=1 label='Radius' ");
	TwDefine(" RenderEdge/'Point Light' opened=false");

	// Image Based Lighting
	// ===========================================================
	TwAddVarRW(bar, "bEnableIBL", TW_TYPE_BOOLCPP, &g_bIBL, " group='Image Based Lighting' label='Enabled' ");
	TwAddVarRW(bar, "fCubemapBrightness", TW_TYPE_FLOAT, &g_fCubemapBrightness, " group='Image Based Lighting' min=0 max=5 step=0.01 label='Cubemap Brightness' ");
	TwAddVarRW(bar, "fEnvCubemapRotation", TW_TYPE_FLOAT, &g_fEnvCubemapRotation, " group='Image Based Lighting' min=0 max=360 step=1.0 label='Source Cubemap Angle' ");
	TwAddVarRW(bar, "bEnvCubemapSwapYZ", TW_TYPE_BOOLCPP, &g_bEnvCubemapSwapYZ, " group='Image Based Lighting' label='Swap YZ' ");
	TwDefine(" RenderEdge/'Image Based Lighting' opened=false");

	TwAddSeparator(bar, "", "");

	// Material
	// ===========================================================
	TwAddVarRW(bar, "bEnablePBS", TW_TYPE_BOOLCPP, &g_bPBS, " group='Material' label='Physically Based Shading' ");
	TwAddVarRW(bar, "bSimpleMaterial", TW_TYPE_BOOLCPP, &g_bSimpleMaterial, " group='Material' label='Simple Material' ");
	TwAddVarRW(bar, "bEnableTextures", TW_TYPE_BOOLCPP, &g_bTexture, " group='Material' label='Textures' ");
	TwAddVarRW(bar, "bAnisoFiltering", TW_TYPE_BOOLCPP, &g_bAnisoFiltering, " group='Material' label='Anisotropic Filtering' ");
	TwAddVarRW(bar, "iMaxAnisotropy", TW_TYPE_UINT16, &g_iMaxAnisotropy, " group='Material' min=1 max=16 label='Anisotropy Level' ");
	//TwAddVarRW(bar, "iTextureFilter", textureFilterListType, &g_iTextureFilter, " group='Material' label='Texture Filter' ");
	TwDefine(" RenderEdge/'Material' opened=false");

	// Shadows
	// ===========================================================
	if (CascadedShadows)
	{
		//TwAddVarRW(bar, "bSoftShadows", TW_TYPE_BOOLCPP, &CascadedShadows->bSoftShadows, " group='Shadows' label='Soft Shadows' ");
		TwAddVarRW(bar, "bVisCascades", TW_TYPE_BOOLCPP, &CascadedShadows->bVisCascades, " group='Shadows' label='Show Cascades' ");
		TwAddVarRW(bar, "iShadowCullMode", cullModeListType, &CascadedShadows->iShadowCullMode, " group='Shadows' label='Culling Mode' ");
		TwAddVarRW(bar, "iShadowMapSize", TW_TYPE_UINT16, &CascadedShadows->iShadowMapSize, " group='Shadows' min=128 max=4096 label='Shadow Map Size' ");
		TwAddVarRW(bar, "fAlphaThreshold", TW_TYPE_FLOAT, &CascadedShadows->fAlphaThreshold, " group='Shadows' min=0 max=1 step=0.01 label='Alpha Threshold' ");
		TwAddVarRW(bar, "fSoftTransitionScale", TW_TYPE_FLOAT, &CascadedShadows->fSoftTransitionScale, " group='Shadows' min=0 max=1000 step=1.0 label='Soft Transition Scale' ");
		//TwAddVarRW(bar, "fShadowSharpen", TW_TYPE_FLOAT, &CascadedShadows->fShadowSharpen, " group='Shadows' min=1 max=10 step=0.01 label='Shadow Sharpen' ");
		TwAddVarRW(bar, "fRadius", TW_TYPE_FLOAT, &CascadedShadows->fRadius, " group='Shadows' min=0 step=0.01 label='Blur Radius' ");
		TwAddVarRW(bar, "fShadowFarZ", TW_TYPE_FLOAT, &CascadedShadows->fFarZ, " group='Shadows' label='FarZ' ");
		TwAddVarRW(bar, "fSplitWeight", TW_TYPE_FLOAT, &CascadedShadows->fSplitWeight, " group='Shadows' max=1 step=0.01 label='Split Weight' ");
		TwAddVarRW(bar, "fShadowFoV", TW_TYPE_FLOAT, &CascadedShadows->fFoV, " group='Shadows' min=1 max=220 step=0.1 label='Field of View' ");
		TwDefine(" RenderEdge/'Shadows' opened=false");
	}

	// Fog
	// ===========================================================
	TwAddVarRW(bar, "bEnableFog", TW_TYPE_BOOLCPP, &g_bEnableFog, " group='Fog' label='Enabled' ");
	TwAddVarRW(bar, "bDefaultFog", TW_TYPE_BOOLCPP, &g_bDefaultFog, " group='Fog' label='Default Fog' ");
	TwAddVarRW(bar, "bSRGBFogColor", TW_TYPE_BOOLCPP, &g_bFogColorSRGB, " group='Fog' label='sRGB Color' ");
	TwAddSeparator(bar, "", " group='Fog' ");
	TwAddVarRW(bar, "iFogTech", fogTechListType, &g_iFogTech, " group='Fog' label='Technique' ");
	TwAddVarRW(bar, "vFogColor", TW_TYPE_COLOR3F, &g_vFogColor, " group='Fog' label='Color' ");
	TwAddVarRW(bar, "fFogStart", TW_TYPE_FLOAT, &g_fFogStart, " group='Fog' min=0 step=1.0 precision=2 label='Start Distance' ");
	TwAddVarRW(bar, "fFogEnd", TW_TYPE_FLOAT, &g_fFogEnd, " group='Fog' min=0 step=1.0 precision=2 label='End Distance' ");
	TwAddVarRW(bar, "fFogDensity", TW_TYPE_FLOAT, &g_fFogDensity, " group='Fog' min=0.0001 max=10 step=0.01 precision=4 label='Density' ");
	TwAddVarRW(bar, "fFogHeight", TW_TYPE_FLOAT, &g_fFogHeight, " group='Fog' step=1.0 precision=2 label='Height' ");
	TwAddVarRW(bar, "fFogHeightFalloff", TW_TYPE_FLOAT, &g_fFogHeightFalloff, " group='Fog' min=0.001 max=10 step=0.02 precision=4 label='Height Falloff' ");
	TwAddVarRW(bar, "fFogCutoffDistance", TW_TYPE_FLOAT, &g_fFogCutoffDistance, " group='Fog' min=0 step=0.1 label='Cutoff Distance' ");
	TwAddVarRW(bar, "fFogMaxOpacity", TW_TYPE_FLOAT, &g_fFogMaxOpacity, " group='Fog' min=0 max=1 step=0.001 precision=4 label='Max Opacity' ");
	TwAddSeparator(bar, "", " group='Fog' ");
	TwAddVarRW(bar, "bFogSun", TW_TYPE_BOOLCPP, &g_bFogSun, " group='Fog' label='Sun' ");
	TwAddVarRW(bar, "vFogSunColor", TW_TYPE_COLOR3F, &g_vFogSunColor, " group='Fog' label='Sun Color' ");
	TwAddVarRW(bar, "fFogSunIntensity", TW_TYPE_FLOAT, &g_fFogSunIntensity, " group='Fog' min=2 max=64 step=0.1 label='Sun Intensity' ");
	TwAddVarRW(bar, "fFogSunStartDistance", TW_TYPE_FLOAT, &g_fFogSunStartDistance, " group='Fog' min=0 step=0.1 label='Sun Start Distance' ");
	TwDefine(" RenderEdge/'Fog' opened=false");

	TwAddSeparator(bar, "", "");

	// Post Effect
	// ===========================================================
	if (PostProcessing)
	{
		TwAddVarRW(bar, "bEnableHDR", TW_TYPE_BOOLCPP, &g_bEnableHDR, " group='Post Effect' label='Enabled' ");
		TwDefine(" RenderEdge/'Post Effect' opened=false");

		TwAddVarCB(bar, "fFilmSlope", TW_TYPE_FLOAT, SetLutFloat_cb, GetLutFloat_cb, &PostProcessing->fFilmSlope, " group='Tonemapper' min=0 max=1 step=0.01 label='Slope' ");
		TwAddVarCB(bar, "fFilmToe", TW_TYPE_FLOAT, SetLutFloat_cb, GetLutFloat_cb, &PostProcessing->fFilmToe, " group='Tonemapper' min=0 max=1 step=0.01 label='Toe' ");
		TwAddVarCB(bar, "fFilmShoulder", TW_TYPE_FLOAT, SetLutFloat_cb, GetLutFloat_cb, &PostProcessing->fFilmShoulder, " group='Tonemapper' min=0 max=1 step=0.01 label='Shoulder' ");
		TwAddVarCB(bar, "fFilmBlackClip", TW_TYPE_FLOAT, SetLutFloat_cb, GetLutFloat_cb, &PostProcessing->fFilmBlackClip, " group='Tonemapper' min=0 max=1 step=0.01 label='Black Clip' ");
		TwAddVarCB(bar, "fFilmWhiteClip", TW_TYPE_FLOAT, SetLutFloat_cb, GetLutFloat_cb, &PostProcessing->fFilmWhiteClip, " group='Tonemapper' min=0 max=1 step=0.01 label='White Clip' ");
		TwDefine(" RenderEdge/'Tonemapper' group='Post Effect' opened=false");

		TwAddVarCB(bar, "fWhiteTemp", TW_TYPE_FLOAT, SetLutFloat_cb, GetLutFloat_cb, &PostProcessing->fWhiteTemp, " group='White Balance' min=1500 max=15000 step=1.0 precision=2 label='Temp' ");
		TwAddVarCB(bar, "fWhiteTint", TW_TYPE_FLOAT, SetLutFloat_cb, GetLutFloat_cb, &PostProcessing->fWhiteTint, " group='White Balance' min=-1 max=1 step=0.01 precision=4 label='Tint' ");
		TwDefine(" RenderEdge/'White Balance' group='Color Grading' opened=false");
		TwAddVarCB(bar, "fColorSaturation", TW_TYPE_FLOAT, SetLutFloat_cb, GetLutFloat_cb, &PostProcessing->vColorSaturation.w, " group='CCGlobal' min=0 max=2 step=0.01 precision=3 label='Saturation' ");
		TwAddVarCB(bar, "vColorSaturation", TW_TYPE_COLOR3F, SetLutColor_cb, GetLutColor_cb, &PostProcessing->vColorSaturation, " group='CCGlobal' label='Saturation Color' ");
		TwAddSeparator(bar, "", " group='CCGlobal' ");
		TwAddVarCB(bar, "fColorContrast", TW_TYPE_FLOAT, SetLutFloat_cb, GetLutFloat_cb, &PostProcessing->vColorContrast.w, " group='CCGlobal' min=0 max=2 step=0.01 precision=3 label='Contrast' ");
		TwAddVarCB(bar, "vColorContrast", TW_TYPE_COLOR3F, SetLutColor_cb, GetLutColor_cb, &PostProcessing->vColorContrast, " group='CCGlobal' label='Contrast Color' ");
		TwAddSeparator(bar, "", " group='CCGlobal' ");
		TwAddVarCB(bar, "fColorGamma", TW_TYPE_FLOAT, SetLutFloat_cb, GetLutFloat_cb, &PostProcessing->vColorGamma.w, " group='CCGlobal' min=0 max=2 step=0.01 precision=3 label='Gamma' ");
		TwAddVarCB(bar, "vColorGamma", TW_TYPE_COLOR3F, SetLutColor_cb, GetLutColor_cb, &PostProcessing->vColorGamma, " group='CCGlobal' label='Gamma Color' ");
		TwAddSeparator(bar, "", " group='CCGlobal' ");
		TwAddVarCB(bar, "fColorGain", TW_TYPE_FLOAT, SetLutFloat_cb, GetLutFloat_cb, &PostProcessing->vColorGain.w, " group='CCGlobal' min=0 max=2 step=0.01 precision=3 label='Gain' ");
		TwAddVarCB(bar, "vColorGain", TW_TYPE_COLOR3F, SetLutColor_cb, GetLutColor_cb, &PostProcessing->vColorGain, " group='CCGlobal' label='Gain Color' ");
		TwAddSeparator(bar, "", " group='CCGlobal' ");
		TwAddVarCB(bar, "fColorOffset", TW_TYPE_FLOAT, SetLutFloat_cb, GetLutFloat_cb, &PostProcessing->vColorOffset.w, " group='CCGlobal' min=-1 max=1 step=0.001 label='Offset' ");
		TwAddVarCB(bar, "vColorOffset", TW_TYPE_COLOR3F, SetLutColor_cb, GetLutColor_cb, &PostProcessing->vColorOffset, " group='CCGlobal' label='Offset Color' ");
		TwDefine(" RenderEdge/'CCGlobal' group='Color Grading' opened=false label='Global'");
		TwAddVarCB(bar, "fColorSaturationShadows", TW_TYPE_FLOAT, SetLutFloat_cb, GetLutFloat_cb, &PostProcessing->vColorSaturationShadows.w, " group='CCShadows' min=0 max=2 step=0.01 precision=3 label='Saturation' ");
		TwAddVarCB(bar, "vColorSaturationShadows", TW_TYPE_COLOR3F, SetLutColor_cb, GetLutColor_cb, &PostProcessing->vColorSaturationShadows, " group='CCShadows' label='Saturation Color' ");
		TwAddSeparator(bar, "", " group='CCShadows' ");
		TwAddVarCB(bar, "fColorContrastShadows", TW_TYPE_FLOAT, SetLutFloat_cb, GetLutFloat_cb, &PostProcessing->vColorContrastShadows.w, " group='CCShadows' min=0 max=2 step=0.01 precision=3 label='Contrast' ");
		TwAddVarCB(bar, "vColorContrastShadows", TW_TYPE_COLOR3F, SetLutColor_cb, GetLutColor_cb, &PostProcessing->vColorContrastShadows, " group='CCShadows' label='Contrast Color' ");
		TwAddSeparator(bar, "", " group='CCShadows' ");
		TwAddVarCB(bar, "fColorGammaShadows", TW_TYPE_FLOAT, SetLutFloat_cb, GetLutFloat_cb, &PostProcessing->vColorGammaShadows.w, " group='CCShadows' min=0 max=2 step=0.01 precision=3 label='Gamma' ");
		TwAddVarCB(bar, "vColorGammaShadows", TW_TYPE_COLOR3F, SetLutColor_cb, GetLutColor_cb, &PostProcessing->vColorGammaShadows, " group='CCShadows' label='Gamma Color' ");
		TwAddSeparator(bar, "", " group='CCShadows' ");
		TwAddVarCB(bar, "fColorGainShadows", TW_TYPE_FLOAT, SetLutFloat_cb, GetLutFloat_cb, &PostProcessing->vColorGainShadows.w, " group='CCShadows' min=0 max=2 step=0.01 precision=3 label='Gain' ");
		TwAddVarCB(bar, "vColorGainShadows", TW_TYPE_COLOR3F, SetLutColor_cb, GetLutColor_cb, &PostProcessing->vColorGainShadows, " group='CCShadows' label='Gain Color' ");
		TwAddSeparator(bar, "", " group='CCShadows' ");
		TwAddVarCB(bar, "fColorOffsetShadows", TW_TYPE_FLOAT, SetLutFloat_cb, GetLutFloat_cb, &PostProcessing->vColorOffsetShadows.w, " group='CCShadows' min=-1 max=1 step=0.001 label='Offset' ");
		TwAddVarCB(bar, "vColorOffsetShadows", TW_TYPE_COLOR3F, SetLutColor_cb, GetLutColor_cb, &PostProcessing->vColorOffsetShadows, " group='CCShadows' label='Offset Color' ");
		TwAddSeparator(bar, "", " group='CCShadows' ");
		TwAddVarCB(bar, "fColorCorrectionShadowsMax", TW_TYPE_FLOAT, SetLutFloat_cb, GetLutFloat_cb, &PostProcessing->fColorCorrectionShadowsMax, " group='CCShadows' min=-1 max=1 step=0.001 label='Shadows Max' ");
		TwDefine(" RenderEdge/'CCShadows' group='Color Grading' opened=false label='Shadows'");
		TwAddVarCB(bar, "fColorSaturationMidtones", TW_TYPE_FLOAT, SetLutFloat_cb, GetLutFloat_cb, &PostProcessing->vColorSaturationMidtones.w, " group='CCMidtones' min=0 max=2 step=0.01 precision=3 label='Saturation' ");
		TwAddVarCB(bar, "vColorSaturationMidtones", TW_TYPE_COLOR3F, SetLutColor_cb, GetLutColor_cb, &PostProcessing->vColorSaturationMidtones, " group='CCMidtones' label='Saturation Color' ");
		TwAddSeparator(bar, "", " group='CCMidtones' ");
		TwAddVarCB(bar, "fColorContrastMidtones", TW_TYPE_FLOAT, SetLutFloat_cb, GetLutFloat_cb, &PostProcessing->vColorContrastMidtones.w, " group='CCMidtones' min=0 max=2 step=0.01 precision=3 label='Contrast' ");
		TwAddVarCB(bar, "vColorContrastMidtones", TW_TYPE_COLOR3F, SetLutColor_cb, GetLutColor_cb, &PostProcessing->vColorContrastMidtones, " group='CCMidtones' label='Contrast Color' ");
		TwAddSeparator(bar, "", " group='CCMidtones' ");
		TwAddVarCB(bar, "fColorGammaMidtones", TW_TYPE_FLOAT, SetLutFloat_cb, GetLutFloat_cb, &PostProcessing->vColorGammaMidtones.w, " group='CCMidtones' min=0 max=2 step=0.01 precision=3 label='Gamma' ");
		TwAddVarCB(bar, "vColorGammaMidtones", TW_TYPE_COLOR3F, SetLutColor_cb, GetLutColor_cb, &PostProcessing->vColorGammaMidtones, " group='CCMidtones' label='Gamma Color' ");
		TwAddSeparator(bar, "", " group='CCMidtones' ");
		TwAddVarCB(bar, "fColorGainMidtones", TW_TYPE_FLOAT, SetLutFloat_cb, GetLutFloat_cb, &PostProcessing->vColorGainMidtones.w, " group='CCMidtones' min=0 max=2 step=0.01 precision=3 label='Gain' ");
		TwAddVarCB(bar, "vColorGainMidtones", TW_TYPE_COLOR3F, SetLutColor_cb, GetLutColor_cb, &PostProcessing->vColorGainMidtones, " group='CCMidtones' label='Gain Color' ");
		TwAddSeparator(bar, "", " group='CCMidtones' ");
		TwAddVarCB(bar, "fColorOffsetMidtones", TW_TYPE_FLOAT, SetLutFloat_cb, GetLutFloat_cb, &PostProcessing->vColorOffsetMidtones.w, " group='CCMidtones' min=-1 max=1 step=0.001 label='Offset' ");
		TwAddVarCB(bar, "vColorOffsetMidtones", TW_TYPE_COLOR3F, SetLutColor_cb, GetLutColor_cb, &PostProcessing->vColorOffsetMidtones, " group='CCMidtones' label='Offset Color' ");
		TwDefine(" RenderEdge/'CCMidtones' group='Color Grading' opened=false label='Midtones'");
		TwAddVarCB(bar, "fColorSaturationHighlights", TW_TYPE_FLOAT, SetLutFloat_cb, GetLutFloat_cb, &PostProcessing->vColorSaturationHighlights.w, " group='CCHighlights' min=0 max=2 step=0.01 precision=3 label='Saturation' ");
		TwAddVarCB(bar, "vColorSaturationHighlights", TW_TYPE_COLOR3F, SetLutColor_cb, GetLutColor_cb, &PostProcessing->vColorSaturationHighlights, " group='CCHighlights' label='Saturation Color' ");
		TwAddSeparator(bar, "", " group='CCHighlights' ");
		TwAddVarCB(bar, "fColorContrastHighlights", TW_TYPE_FLOAT, SetLutFloat_cb, GetLutFloat_cb, &PostProcessing->vColorContrastHighlights.w, " group='CCHighlights' min=0 max=2 step=0.01 precision=3 label='Contrast' ");
		TwAddVarCB(bar, "vColorContrastHighlights", TW_TYPE_COLOR3F, SetLutColor_cb, GetLutColor_cb, &PostProcessing->vColorContrastHighlights, " group='CCHighlights' label='Contrast Color' ");
		TwAddSeparator(bar, "", " group='CCHighlights' ");
		TwAddVarCB(bar, "fColorGammaHighlights", TW_TYPE_FLOAT, SetLutFloat_cb, GetLutFloat_cb, &PostProcessing->vColorGammaHighlights.w, " group='CCHighlights' min=0 max=2 step=0.01 precision=3 label='Gamma' ");
		TwAddVarCB(bar, "vColorGammaHighlights", TW_TYPE_COLOR3F, SetLutColor_cb, GetLutColor_cb, &PostProcessing->vColorGammaHighlights, " group='CCHighlights' label='Gamma Color' ");
		TwAddSeparator(bar, "", " group='CCHighlights' ");
		TwAddVarCB(bar, "fColorGainHighlights", TW_TYPE_FLOAT, SetLutFloat_cb, GetLutFloat_cb, &PostProcessing->vColorGainHighlights.w, " group='CCHighlights' min=0 max=2 step=0.01 precision=3 label='Gain' ");
		TwAddVarCB(bar, "vColorGainHighlights", TW_TYPE_COLOR3F, SetLutColor_cb, GetLutColor_cb, &PostProcessing->vColorGainHighlights, " group='CCHighlights' label='Gain Color' ");
		TwAddSeparator(bar, "", " group='CCHighlights' ");
		TwAddVarCB(bar, "fColorOffsetHighlights", TW_TYPE_FLOAT, SetLutFloat_cb, GetLutFloat_cb, &PostProcessing->vColorOffsetHighlights.w, " group='CCHighlights' min=-1 max=1 step=0.001 label='Offset' ");
		TwAddVarCB(bar, "vColorOffsetHighlights", TW_TYPE_COLOR3F, SetLutColor_cb, GetLutColor_cb, &PostProcessing->vColorOffsetHighlights, " group='CCHighlights' label='Offset Color' ");
		TwAddSeparator(bar, "", " group='CCHighlights' ");
		TwAddVarCB(bar, "fColorCorrectionHighlightsMin", TW_TYPE_FLOAT, SetLutFloat_cb, GetLutFloat_cb, &PostProcessing->fColorCorrectionHighlightsMin, " group='CCHighlights' min=-1 max=1 step=0.001 label='Highlights Min' ");
		TwDefine(" RenderEdge/'CCHighlights' group='Color Grading' opened=false label='Highlights'");
		TwAddVarCB(bar, "fBlueCorrection", TW_TYPE_FLOAT, SetLutFloat_cb, GetLutFloat_cb, &PostProcessing->fBlueCorrection, " group='CCMisc' min=0 max=1 step=0.01 label='Blue Correction' ");
		TwAddVarCB(bar, "fExpandGamut", TW_TYPE_FLOAT, SetLutFloat_cb, GetLutFloat_cb, &PostProcessing->fExpandGamut, " group='CCMisc' min=0 max=1 step=0.01 label='Expand Gamut' ");
		TwAddSeparator(bar, "", " group='CCMisc' ");
		TwAddVarCB(bar, "bUserLUT", TW_TYPE_BOOLCPP, SetLutBool_cb, GetLutBool_cb, &PostProcessing->bUserLUT, " group='CCMisc' label='User LUT' ");
		TwAddVarCB(bar, "fUserLutIntensity", TW_TYPE_FLOAT, SetLutFloat_cb, GetLutFloat_cb, &PostProcessing->fUserLutIntensity, " group='CCMisc' min=0 max=1 step=0.01 precision=3 label='Intensity' ");
		TwDefine(" RenderEdge/'CCMisc' group='Color Grading' opened=false label='Misc'");
		TwDefine(" RenderEdge/'Color Grading' group='Post Effect' opened=false");

		TwAddVarRW(bar, "bAutoExposure", TW_TYPE_BOOLCPP, &PostProcessing->bAutoExposure, " group='Auto Exposure' label='Enabled' ");
		TwAddVarRW(bar, "fMinBrightness", TW_TYPE_FLOAT, &PostProcessing->fAutoExposureMinBrightness, " group='Auto Exposure' min=0 max=10 step=0.001 label='Min Brightness' ");
		TwAddVarRW(bar, "fMaxBrightness", TW_TYPE_FLOAT, &PostProcessing->fAutoExposureMaxBrightness, " group='Auto Exposure' min=0 max=10 step=0.001 label='Max Brightness' ");
		TwAddVarRW(bar, "fEyeAdaptationSpeedUp", TW_TYPE_FLOAT, &PostProcessing->fAutoExposureSpeedUp, " group='Auto Exposure' min=0.02 max=20 step=0.01 label='Speed Up' ");
		TwAddVarRW(bar, "fEyeAdaptationSpeedDown", TW_TYPE_FLOAT, &PostProcessing->fAutoExposureSpeedDown, " group='Auto Exposure' min=0.02 max=20 step=0.01 label='Speed Down' ");
		TwAddVarRW(bar, "fAutoExposureBias", TW_TYPE_FLOAT, &PostProcessing->fAutoExposureBias, " group='Auto Exposure' min=-8 max=8 step=0.001 label='Exposure Compensation' ");
		//TwAddVarRW(bar, "fHistogramLogMin", TW_TYPE_FLOAT, &PostProcessing->fAutoExposureHistogramLogMin, " group='Auto Exposure' min=-16 max=0 step=0.01 label='Histogram Log Min' ");
		//TwAddVarRW(bar, "fHistogramLogMax", TW_TYPE_FLOAT, &PostProcessing->fAutoExposureHistogramLogMax, " group='Auto Exposure' min=0 max=16 step=0.01 label='Histogram Log Max' ");
		TwAddVarRW(bar, "fCalibrationConstant", TW_TYPE_FLOAT, &PostProcessing->fAutoExposureCalibrationConstant, " group='Auto Exposure' min=0 max=100 step=0.01 label='Calibration Constant' ");
		TwDefine(" RenderEdge/'Auto Exposure' group='Post Effect' opened=false");

		TwAddVarRW(bar, "bBloom", TW_TYPE_BOOLCPP, &PostProcessing->bBloom, " group='Bloom' label='Enabled' ");
		TwAddVarRW(bar, "fBloomTreshhold", TW_TYPE_FLOAT, &PostProcessing->fBloomThreshold, " group='Bloom' min=-1 step=0.01 label='Treshhold' ");
		TwAddVarRW(bar, "fBloomIntensity", TW_TYPE_FLOAT, &PostProcessing->fBloomIntensity, " group='Bloom' min=0 step=0.01 label='Intensity' ");
		TwAddVarRW(bar, "iBloomPasses", TW_TYPE_UINT16, &PostProcessing->iBloomPasses, " group='Bloom' min=2 max=10 label='Passes' ");
		TwAddVarRW(bar, "fBloomAnamorphicRatio", TW_TYPE_FLOAT, &PostProcessing->fBloomAnamorphicRatio, " group='Bloom' min=-1 max=1 step=0.01 label='Anamorphic Ratio' ");
		TwAddSeparator(bar, "", " group='Bloom' ");
		TwAddVarRW(bar, "bDirtMask", TW_TYPE_BOOLCPP, &PostProcessing->bLensDirt, " group='Bloom' label='Lens Dirt' ");
		TwAddVarRW(bar, "fLensDirtIntensity", TW_TYPE_FLOAT, &PostProcessing->fLensDirtIntensity, " group='Bloom' min=0 step=0.01 label='Intensity' ");
		/*TwAddVarRW(bar, "BloomSizeScale", TW_TYPE_FLOAT, &PostProcessing->BloomSizeScale, " group='Bloom Advanced' min=1 step=0.01 label='BloomSizeScale' ");
		TwAddVarRW(bar, "Bloom1Size", TW_TYPE_FLOAT, &PostProcessing->Bloom1Size, " group='Bloom Advanced' min=0.3 step=1.0 precision=2 label='Bloom1Size' ");
		TwAddVarRW(bar, "Bloom1Tint", TW_TYPE_COLOR3F, &PostProcessing->Bloom1Tint, " group='Bloom Advanced' label='Bloom1Tint' ");
		TwAddVarRW(bar, "Bloom2Size", TW_TYPE_FLOAT, &PostProcessing->Bloom2Size, " group='Bloom Advanced' min=1 step=1.0 precision=2 label='Bloom2Size' ");
		TwAddVarRW(bar, "Bloom2Tint", TW_TYPE_COLOR3F, &PostProcessing->Bloom2Tint, " group='Bloom Advanced' label='Bloom2Tint' ");
		TwAddVarRW(bar, "Bloom3Size", TW_TYPE_FLOAT, &PostProcessing->Bloom3Size, " group='Bloom Advanced' min=1 step=1.0 precision=2 label='Bloom3Size' ");
		TwAddVarRW(bar, "Bloom3Tint", TW_TYPE_COLOR3F, &PostProcessing->Bloom3Tint, " group='Bloom Advanced' label='Bloom3Tint' ");
		TwAddVarRW(bar, "Bloom4Size", TW_TYPE_FLOAT, &PostProcessing->Bloom4Size, " group='Bloom Advanced' min=1 step=1.0 precision=2 label='Bloom4Size' ");
		TwAddVarRW(bar, "Bloom4Tint", TW_TYPE_COLOR3F, &PostProcessing->Bloom4Tint, " group='Bloom Advanced' label='Bloom4Tint' ");
		TwAddVarRW(bar, "Bloom5Size", TW_TYPE_FLOAT, &PostProcessing->Bloom5Size, " group='Bloom Advanced' min=1 step=1.0 precision=2 label='Bloom5Size' ");
		TwAddVarRW(bar, "Bloom5Tint", TW_TYPE_COLOR3F, &PostProcessing->Bloom5Tint, " group='Bloom Advanced' label='Bloom5Tint' ");
		TwAddVarRW(bar, "Bloom6Size", TW_TYPE_FLOAT, &PostProcessing->Bloom6Size, " group='Bloom Advanced' min=1 step=1.0 precision=2 label='Bloom6Size' ");
		TwAddVarRW(bar, "Bloom6Tint", TW_TYPE_COLOR3F, &PostProcessing->Bloom6Tint, " group='Bloom Advanced' label='Bloom6Tint' ");
		TwDefine(" RenderEdge/'Bloom Advanced' group='Bloom' opened=false label='Advanced'");*/
		TwDefine(" RenderEdge/'Bloom' group='Post Effect' opened=false");

		TwAddVarRW(bar, "bSSAO", TW_TYPE_BOOLCPP, &PostProcessing->bSSAO, " group='Ambient Occlusion' label='Enabled'");
		TwAddVarRW(bar, "bSSAODownsample", TW_TYPE_BOOLCPP, &PostProcessing->bSSAODownsample, " group='Ambient Occlusion' label='Downsample'");
		TwAddVarRW(bar, "fSSAOIntensity", TW_TYPE_FLOAT, &PostProcessing->fSSAOIntensity, " group='Ambient Occlusion' min=0 max=10 step=0.01 label='Intensity' ");
		TwAddVarRW(bar, "fSSAORadius", TW_TYPE_FLOAT, &PostProcessing->fSSAORadius, " group='Ambient Occlusion' min=0.1 max=500.0 step=0.1 label='Radius' ");
		TwAddSeparator(bar, "", " group='Ambient Occlusion' ");
		TwAddVarRW(bar, "fSSAOContrast", TW_TYPE_FLOAT, &PostProcessing->fSSAOContrast, " group='Ambient Occlusion' min=0 max=1 step=0.01 precision=3 label='Contrast' ");
		TwAddVarRW(bar, "fSSAOGeometryCoeff", TW_TYPE_FLOAT, &PostProcessing->fSSAOGeometryCoeff, " group='Ambient Occlusion' min=0.5 max=1 step=0.01 precision=4 label='GeometryCoeff' ");
		TwAddVarRW(bar, "fSSAOBeta", TW_TYPE_FLOAT, &PostProcessing->fSSAOBeta, " group='Ambient Occlusion' min=0 max=0.01 step=0.0001 label='Beta' ");
		TwDefine(" RenderEdge/'Ambient Occlusion' group='Post Effect' opened=false");

		TwAddVarRW(bar, "bSSR", TW_TYPE_BOOLCPP, &PostProcessing->bSSR, " group='Screen Space Reflections' label='Enabled'");
		TwAddVarRW(bar, "bSSRDownsample", TW_TYPE_BOOLCPP, &PostProcessing->bSSRDownsample, " group='Screen Space Reflections' label='Downsample'");
		//TwAddVarRW(bar, "fSSRMinRayStep", TW_TYPE_FLOAT, &PostProcessing->fSSRMinRayStep, " group='Screen Space Reflections' min=0.01 step=0.01 label='Min Ray Step' ");
		TwAddVarRW(bar, "fSSRRayStep", TW_TYPE_FLOAT, &PostProcessing->fSSRRayStep, " group='Screen Space Reflections' min=0.01 step=0.01 label='Ray Step' ");
		//TwAddVarRW(bar, "fSSRJitter", TW_TYPE_FLOAT, &PostProcessing->fSSRJitter, " group='Screen Space Reflections' min=0 max=1 step=0.01 label='Jitter Spread' ");
		TwAddVarRW(bar, "fSSRRayhitThreshold", TW_TYPE_FLOAT, &PostProcessing->fSSRRayhitThreshold, " group='Screen Space Reflections' min=0.001 max=1.0 step=0.001 label='Rayhit Threshold' ");
		//TwAddVarRW(bar, "fSSRDepthThreshold", TW_TYPE_FLOAT, &PostProcessing->fSSRDepthThreshold, " group='Screen Space Reflections' min=0 step=0.01 label='DepthThreshold' ");
		TwDefine(" RenderEdge/'Screen Space Reflections' group='Post Effect' opened=false");

		TwAddVarRW(bar, "bContactShadows", TW_TYPE_BOOLCPP, &PostProcessing->bContactShadows, " group='Contact Shadows' label='Enabled'");
		TwAddVarRW(bar, "bContactShadowsDownsample", TW_TYPE_BOOLCPP, &PostProcessing->bContactShadowsDownsample, " group='Contact Shadows' label='Downsample'");
		TwAddVarRW(bar, "fContactShadowsRayLength", TW_TYPE_FLOAT, &PostProcessing->fContactShadowsRayLength, " group='Contact Shadows' min=0 max=1 step=0.001 label='Ray Length' ");
		TwDefine(" RenderEdge/'Contact Shadows' group='Post Effect' opened=false");

		TwAddVarRW(bar, "bChromaticAberration", TW_TYPE_BOOLCPP, &PostProcessing->bChromaticAberration, " group='Chromatic Aberration' label='Enabled' ");
		TwAddVarRW(bar, "fChromaticAberrationIntensity", TW_TYPE_FLOAT, &PostProcessing->fChromaticAberrationIntensity, " group='Chromatic Aberration' min=0 max=1 step=0.001 label='Intensity' ");
		TwDefine(" RenderEdge/'Chromatic Aberration' group='Post Effect' opened=false");

		TwAddVarRW(bar, "bEnableVignette", TW_TYPE_BOOLCPP, &PostProcessing->bVignette, " group='Vignette' label='Enabled' ");
		TwAddVarRW(bar, "bVignetteRounded", TW_TYPE_BOOLCPP, &PostProcessing->bVignetteRounded, " group='Vignette' label='Rounded' ");
		TwAddVarRW(bar, "vVignettingColor", TW_TYPE_COLOR3F, &PostProcessing->vVignetteColor, " group='Vignette' label='Color' ");
		TwAddVarRW(bar, "fVignetteIntensity", TW_TYPE_FLOAT, &PostProcessing->fVignetteIntensity, " group='Vignette' min=0 max=1 step=0.001 label='Intensity' ");
		TwAddVarRW(bar, "fVignetteSmoothness", TW_TYPE_FLOAT, &PostProcessing->fVignetteSmoothness, " group='Vignette' min=0.01 max=1 step=0.001 label='Smoothness' ");
		TwAddVarRW(bar, "fVignetteRoundness", TW_TYPE_FLOAT, &PostProcessing->fVignetteRoundness, " group='Vignette' min=0 max=1 step=0.001 label='Roundness' ");
		TwDefine(" RenderEdge/'Vignette' group='Post Effect' opened=false");

		TwAddVarRW(bar, "bFilmGrain", TW_TYPE_BOOLCPP, &PostProcessing->bFilmGrain, " group='Film Grain' label='Enabled' ");
		TwAddVarRW(bar, "fFilmGrainIntensity", TW_TYPE_FLOAT, &PostProcessing->fFilmGrainIntensity, " group='Film Grain' min=0 max=1 step=0.001 label='Intensity' ");
		TwAddVarRW(bar, "fFilmGrainVariance", TW_TYPE_FLOAT, &PostProcessing->fFilmGrainVariance, " group='Film Grain' min=0 max=1 step=0.001 label='Variance' ");
		TwAddVarRW(bar, "iFilmGrainSignalToNoiseRatio", TW_TYPE_UINT16, &PostProcessing->iFilmGrainSignalToNoiseRatio, " group='Film Grain' min=0 max=16 label='Signal To Noise Ratio' ");
		TwDefine(" RenderEdge/'Film Grain' group='Post Effect' opened=false");

		TwAddVarRW(bar, "bDithering", TW_TYPE_BOOLCPP, &PostProcessing->bDithering, " group='Dithering' label='Enabled' ");
		TwDefine(" RenderEdge/'Dithering' group='Post Effect' opened=false");

		TwAddVarRW(bar, "bSMAA", TW_TYPE_BOOLCPP, &PostProcessing->bSMAA, " group='Anti-aliasing' label='SMAA' ");
		TwAddVarRW(bar, "iSMAAInput", smaaInputListType, &PostProcessing->iSMAAInput, " group='Anti-aliasing' label='Input' ");
		TwAddVarRW(bar, "fSMAAThreshold", TW_TYPE_FLOAT, &PostProcessing->fSMAAThreshold, " group='Anti-aliasing' min=0.05 max=0.5 step=0.001 label='Threshold' ");
		TwAddVarRW(bar, "iSMAASearchSteps", TW_TYPE_UINT16, &PostProcessing->iSMAASearchSteps, " group='Anti-aliasing' min=0 max=98 label='Search Steps' ");
		TwAddVarRW(bar, "iSMADiagSearchSteps", TW_TYPE_UINT16, &PostProcessing->iSMADiagSearchSteps, " group='Anti-aliasing' min=0 max=20 label='Diagonal Search Steps' ");
		TwAddVarRW(bar, "fSMAACornerRounding", TW_TYPE_FLOAT, &PostProcessing->fSMAACornerRounding, " group='Anti-aliasing' min=0 max=100 step=0.01 label='Corner Rounding' ");
		TwAddSeparator(bar, "", " group='Anti-aliasing' ");
		TwAddVarRW(bar, "bTemporalAA", TW_TYPE_BOOLCPP, &PostProcessing->bTemporalAA, " group='Anti-aliasing' label='Temporal AA' ");
		TwAddVarRW(bar, "bUseVelocity", TW_TYPE_BOOLCPP, &PostProcessing->bUseVelocity, " group='Anti-aliasing' readonly=true label='Use Velocity' ");
		TwAddVarRW(bar, "fJitterSpreadTAA", TW_TYPE_FLOAT, &PostProcessing->fJitterSpreadTAA, " group='Anti-aliasing' min=0.0 max=1.0 step=0.01 label='Jitter Spread' ");
		TwAddVarRW(bar, "fSharpnessTAA", TW_TYPE_FLOAT, &PostProcessing->fSharpnessTAA, " group='Anti-aliasing' min=0.0 max=3.0 step=0.01 label='Sharpness' ");
		TwAddVarRW(bar, "fStationaryBlendingTAA", TW_TYPE_FLOAT, &PostProcessing->fStationaryBlendingTAA, " group='Anti-aliasing' min=0.0 max=0.99 step=0.01 label='Stationary Blending' ");
		TwAddVarRW(bar, "fMotionBlendingTAA", TW_TYPE_FLOAT, &PostProcessing->fMotionBlendingTAA, " group='Anti-aliasing' min=0.0 max=0.99 step=0.01 label='Motion Blending' ");
		TwDefine(" RenderEdge/'Anti-aliasing' group='Post Effect' opened=false");

		TwAddVarRW(bar, "iOutputDevice", outputDeviceListType, &PostProcessing->iOutputDevice, " group='Gamma Correction' label='Output Device' ");
		TwAddVarRW(bar, "iColorGamut", colorGamutListType, &PostProcessing->iColorGamut, " group='Gamma Correction' label='Color Gamut' ");
		TwAddVarRW(bar, "fGamma", TW_TYPE_FLOAT, &PostProcessing->fGamma, " group='Gamma Correction' min=1 step=0.01 label='Gamma' ");
		TwDefine(" RenderEdge/'Gamma Correction' group='Post Effect' opened=false");
	}

	// Debug View
	// ===========================================================
	if (PostProcessing)
	{
		TwAddVarRW(bar, "bDebugView", TW_TYPE_BOOLCPP, &PostProcessing->bDebugView, " group='Debug View' label='Enabled' ");;
		TwAddVarRW(bar, "iDebugScreen", debugScreenListType, &PostProcessing->iDebugScreen, " group='Debug View' label='Mode' ");
	}
	TwAddVarRW(bar, "fDebugValue", TW_TYPE_FLOAT, &g_fDebugValue, " group='Debug View' step=0.01 precision=4 label='Debug Value' ");
	TwDefine(" RenderEdge/'Debug View' opened=false");
}



CEngine* Engine = nullptr;

CEngine::CEngine(IDirect3DDevice9* pDevice)
{
	LOG(DEBUG) << "========= On Create Engine ============";
	LOG(INFO) << RenderEdgeVersion;

	m_pDevice = pDevice;
	bMapInit = false;
	OnCreateDevice();
}

CEngine::~CEngine()
{
	LOG(DEBUG) << "========= On Destroy Engine ===========\n\n";

	Release();
}

void CEngine::Release()
{
	SAFE_RELEASE(g_pFont);

	SAFE_RELEASE(g_pSkyboxFX);
	SAFE_RELEASE(g_pStandardFX);

	SAFE_DELETE(AntTweakBar);
	SAFE_DELETE(ResourceManager);
	SAFE_DELETE(FontManager);
	SAFE_DELETE(TextureManager);
	SAFE_DELETE(SystemTextures);
	SAFE_DELETE(CascadedShadows);
	SAFE_DELETE(FreeCamera);
	SAFE_DELETE(PostProcessing);
	SAFE_DELETE(CustomUI);

	ReleaseTemporaryResources();
}


void CEngine::GetBackBufferSize()
{
	IDirect3DSurface9* pSurface;
	D3DSURFACE_DESC desc;

	m_pDevice->GetBackBuffer(0, 0, D3DBACKBUFFER_TYPE_MONO, &pSurface);
	pSurface->GetDesc(&desc);
	pSurface->Release();

	g_vBufferSize = D3DXVECTOR4(
		desc.Width,
		desc.Height,
		1.0f / desc.Width,
		1.0f / desc.Height);
}

void CEngine::GetSupportedDepthFormat()
{
	D3DDISPLAYMODE currentDisplayMode;
	IDirect3D9* d3d = nullptr;
	m_pDevice->GetDirect3D(&d3d);
	d3d->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &currentDisplayMode);

	//bool isRESZ = d3d->CheckDeviceFormat(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, currentDisplayMode.Format, D3DUSAGE_RENDERTARGET, D3DRTYPE_SURFACE, (D3DFORMAT)ETextureFormat::RESZ) == D3D_OK;
	bool isINTZ = d3d->CheckDeviceFormat(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, currentDisplayMode.Format, D3DUSAGE_DEPTHSTENCIL, D3DRTYPE_SURFACE, (D3DFORMAT)ETextureFormat::INTZ) == D3D_OK;
	bool isRAWZ = d3d->CheckDeviceFormat(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, currentDisplayMode.Format, D3DUSAGE_DEPTHSTENCIL, D3DRTYPE_SURFACE, (D3DFORMAT)ETextureFormat::RAWZ) == D3D_OK;

	d3d->Release();

	if (isRAWZ || isINTZ)
		g_depthFormat = isINTZ ? ETextureFormat::INTZ : ETextureFormat::RAWZ;
	else
		Message("INTZ and RAWZ depth formats are not supported", "GetSupportedDepthFormat");
}

void CEngine::OnFrameRenderingSetup(uint32 SampleCount)
{
	if (PostProcessing)
	{
		PostProcessing->iTemporalAASampleIndex++;
		g_iFrameIndexMod8 = (g_iFrameIndexMod8 + 1) % 8;

		if (PostProcessing->iTemporalAASampleIndex >= SampleCount)
			PostProcessing->iTemporalAASampleIndex = 0;
	}
}

bool CEngine::ReadConfigFile(const std::string& fileName)
{
	INIReader ConfigINI;

	if (utils::FileExists(RenderEdgePath + fileName))
	{
		ConfigINI.Open(RenderEdgePath + fileName);
	}
	else
	{
		BUFFER buffer;
		if (MPQ::LoadFile(0, fileName, buffer))
			ConfigINI.Open(buffer.GetData());
	}

	if (!ConfigINI.Success())
	{
		LOG(ERROR) << "Failed to load config file: " << fileName;
		Message("Failed to load config file:\n" + fileName);

		return false;
	}

	// Engine
	ConfigINI.GetBool("Engine", "bDefaultRenderer", g_bDefaultRenderer);
	ConfigINI.GetBool("Engine", "bDebugInfo", g_bDebugInfo);

	bool bShowSettings = false;
	ConfigINI.GetBool("Engine", "bShowSettings", bShowSettings);
	if (AntTweakBar)
		AntTweakBar->SetActive(bShowSettings);

	bool bVSync = false;
	ConfigINI.GetBool("Engine", "bVSync", bVSync);
	if (bVSync != g_bVsyncEnabled)
	{
		g_bVsyncEnabled = bVSync;
		ForceResetDevice8();
	}

	// Camera
	ConfigINI.GetBool("Camera", "bConstantVerticalFoV", g_bDefaultProjectionMatrix);
	ConfigINI.GetBool("Camera", "bFreeCamera", g_bFreeCamera);
	ConfigINI.GetFloat("Camera", "FoV", g_fCameraFoV);
	ConfigINI.GetFloat("Camera", "NearZ", g_fCameraNearZ);
	ConfigINI.GetFloat("Camera", "FarZ", g_fCameraFarZ);
	if (FreeCamera)
		ConfigINI.GetFloat("Camera", "Speed", FreeCamera->m_fSpeed);

	// Render Stage
	ConfigINI.GetBool("RenderStage", "bSkybox", RenderingHook::bRenderSkybox);
	ConfigINI.GetBool("RenderStage", "bTerrain", RenderingHook::bRenderTerrain);
	ConfigINI.GetBool("RenderStage", "bFogOfWar", RenderingHook::bRenderFogOfWar);
	ConfigINI.GetBool("RenderStage", "bTerrainShadow", RenderingHook::bRenderTerrainShadow);
	ConfigINI.GetBool("RenderStage", "bWaterShadow", RenderingHook::bRenderWaterShadow);
	ConfigINI.GetBool("RenderStage", "bWeather", RenderingHook::bRenderWeather);
	ConfigINI.GetBool("RenderStage", "bSelectionCircle", RenderingHook::bRenderSelectionCircle);
	ConfigINI.GetBool("RenderStage", "bFootprint", RenderingHook::bRenderFootprint);
	ConfigINI.GetBool("RenderStage", "bDecoration", RenderingHook::bRenderDecoration);
	ConfigINI.GetBool("RenderStage", "bUnit", RenderingHook::bRenderUnit);
	ConfigINI.GetBool("RenderStage", "bDestructible", RenderingHook::bRenderDestructible);
	ConfigINI.GetBool("RenderStage", "bWater", RenderingHook::bRenderWater);
	ConfigINI.GetBool("RenderStage", "bSelectionBox", RenderingHook::bRenderSelectionBox);
	ConfigINI.GetBool("RenderStage", "bBuilding", RenderingHook::bRenderBuilding);
	ConfigINI.GetBool("RenderStage", "bUbersplat", RenderingHook::bRenderUbersplat);
	ConfigINI.GetBool("RenderStage", "bUnknown1", RenderingHook::bRenderUnknown1);
	ConfigINI.GetBool("RenderStage", "bIndicator", RenderingHook::bRenderIndicator);
	ConfigINI.GetBool("RenderStage", "bUnknown2", RenderingHook::bRenderUnknown2);
	ConfigINI.GetBool("RenderStage", "bOcclusionMask", RenderingHook::bRenderOcclusionMask);
	ConfigINI.GetBool("RenderStage", "bLightning", RenderingHook::bRenderLightning);
	ConfigINI.GetBool("RenderStage", "bFloatingText", RenderingHook::bRenderFloatingText);
	ConfigINI.GetBool("RenderStage", "bCineFilter", RenderingHook::bRenderCineFilter);
	ConfigINI.GetBool("RenderStage", "bUserInterface", g_bUserInterface);
	ConfigINI.GetBool("RenderStage", "bCustomUserInterface", g_bCustomUserInterface);

	// Lighting
	ConfigINI.GetBool("Lighting", "SkyLight.bEnabled", g_bSkyLight);
	ConfigINI.GetBool("Lighting", "SkyLight.bDefaultColor", g_bDefaultAmbientColor);
	ConfigINI.GetBool("Lighting", "SkyLight.bColorSRGB", g_bAmbientColorSRGB);
	ConfigINI.GetColor("Lighting", "SkyLight.AmbColor", g_vAmbColor);
	ConfigINI.GetColor("Lighting", "SkyLight.SkyColor", g_vSkyColor);
	ConfigINI.GetColor("Lighting", "SkyLight.IndColor", g_vIndColor);
	ConfigINI.GetFloat("Lighting", "SkyLight.Intensity", g_fSkyLightIntensity);

	ConfigINI.GetBool("Lighting", "DirectionalLight.bDefaultColor", g_bDefaultLightColor);
	ConfigINI.GetBool("Lighting", "DirectionalLight.bColorSRGB", g_bLightColorSRGB);
	ConfigINI.GetBool("Lighting", "DirectionalLight.bDefaultDirection", g_bDefaultLightDir);
	ConfigINI.GetColor("Lighting", "DirectionalLight.Color", g_vLightColor);
	ConfigINI.GetVector3("Lighting", "DirectionalLight.Direction", g_vLightDir);
	ConfigINI.GetFloat("Lighting", "DirectionalLight.Intensity", g_fLightIntensity);
	ConfigINI.GetBool("Lighting", "DirectionalLight.bUseTemperature", g_bUseTemperature);
	ConfigINI.GetFloat("Lighting", "DirectionalLight.Temperature", g_fLightTemperature);

	ConfigINI.GetBool("Lighting", "PointLight.bEnabled", g_bPointLight);
	ConfigINI.GetBool("Lighting", "PointLight.bColorSRGB", g_bPointLightColorSRGB);
	ConfigINI.GetFloat("Lighting", "PointLight.Intensity", g_fDefaultPointLightIntensity);
	ConfigINI.GetFloat("Lighting", "PointLight.Radius", g_fDefaultPointLightRadius);
	uint32 pointLightUnits = 0;
	ConfigINI.GetUInt("Lighting", "PointLight.IntensityUnits", pointLightUnits);
	g_DefaultPointLightIntensityUnits = static_cast<ELightUnits>(pointLightUnits);

	// Shadows
	if (CascadedShadows)
	{
		ConfigINI.GetBool("Shadows", "bEnabled", CascadedShadows->bObjectsShadows);
		ConfigINI.GetFloat("Shadows", "SoftTransitionScale", CascadedShadows->fSoftTransitionScale);
		ConfigINI.GetFloat("Shadows", "ShadowSharpen", CascadedShadows->fShadowSharpen);
		ConfigINI.GetFloat("Shadows", "BlurRadius", CascadedShadows->fRadius);
		ConfigINI.GetFloat("Shadows", "AlphaThreshold", CascadedShadows->fAlphaThreshold);
		ConfigINI.GetFloat("Shadows", "FarZ", CascadedShadows->fFarZ);
		ConfigINI.GetFloat("Shadows", "FoV", CascadedShadows->fFoV);
		ConfigINI.GetUInt("Shadows", "ShadowMapSize", CascadedShadows->iShadowMapSize);
		uint32 cullMode = D3DCULL::D3DCULL_NONE;
		ConfigINI.GetUInt("Shadows", "CullMode", cullMode);
		CascadedShadows->iShadowCullMode = static_cast<D3DCULL>(cullMode);
	}

	// Image Based Lighting
	ConfigINI.GetBool("IBL", "bEnabled", g_bIBL);
	ConfigINI.GetString("IBL", "CubemapTexture", g_envTextureFileName);
	ConfigINI.GetFloat("IBL", "CubemapBrightness", g_fCubemapBrightness);
	ConfigINI.GetFloat("IBL", "CubemapRotation", g_fEnvCubemapRotation);
	ConfigINI.GetBool("IBL", "bCubemapSwapYZ", g_bEnvCubemapSwapYZ);

	// Material
	ConfigINI.GetBool("Material", "bEnablePBS", g_bPBS);
	ConfigINI.GetFloat("Material", "Roughness", g_fMaterialRoughness);
	ConfigINI.GetFloat("Material", "Metallic", g_fMaterialMetallic);
	ConfigINI.GetFloat("Material", "Specular", g_fMaterialSpecular);
	ConfigINI.GetFloat("Material", "Translucent", g_fMaterialTranslucent);
	ConfigINI.GetString("Material", "NormalMapTexture", g_normalTextureFileName);
	ConfigINI.GetBool("Material", "bNormalMap", g_bNormalMapping);
	ConfigINI.GetBool("Material", "bAnisoFiltering", g_bAnisoFiltering);
	ConfigINI.GetBool("Material", "bTextures", g_bTexture);
	ConfigINI.GetBool("Material", "bMaterialColor", g_bMaterialColor);
	ConfigINI.GetBool("Material", "bVertexColor", g_bVertexColor);
	ConfigINI.GetBool("Material", "bUnshadedMaterials", g_bUnshadedMaterials);
	ConfigINI.GetBool("Material", "bUnfoggedMaterials", g_bUnfoggedMaterials);
	ConfigINI.GetBool("Material", "bMaterialColorSRGB", g_bMaterialColorSRGB);
	ConfigINI.GetBool("Material", "bVertexColorSRGB", g_bVertexColorSRGB);

	// Skybox
	ConfigINI.GetBool("Skybox", "bShading", g_bSkyboxShading);
	ConfigINI.GetBool("Skybox", "bFog", g_bSkyboxFog);
	ConfigINI.GetBool("Skybox", "bFixTwitching", g_bSkyboxFixTwitching);
	ConfigINI.GetFloat("Skybox", "Intensity", g_fSkyboxLightIntensity);

	// Fog
	ConfigINI.GetBool("Fog", "bEnabled", g_bEnableFog);
	ConfigINI.GetBool("Fog", "bDefaultFog", g_bDefaultFog);
	ConfigINI.GetBool("Fog", "bColorSRGB", g_bFogColorSRGB);
	ConfigINI.GetBool("Fog", "bSun", g_bFogSun);
	ConfigINI.GetColor("Fog", "FogColor", g_vFogColor);
	ConfigINI.GetColor("Fog", "SunColor", g_vFogSunColor);
	ConfigINI.GetFloat("Fog", "SunIntensity", g_fFogSunIntensity);
	ConfigINI.GetFloat("Fog", "SunStartDistance", g_fFogSunStartDistance);
	ConfigINI.GetFloat("Fog", "Start", g_fFogStart);
	ConfigINI.GetFloat("Fog", "End", g_fFogEnd);
	ConfigINI.GetFloat("Fog", "Density", g_fFogDensity);
	ConfigINI.GetFloat("Fog", "Height", g_fFogHeight);
	ConfigINI.GetFloat("Fog", "MaxOpacity", g_fFogMaxOpacity);
	ConfigINI.GetFloat("Fog", "HeightFalloff", g_fFogHeightFalloff);
	ConfigINI.GetFloat("Fog", "CutoffDistance", g_fFogCutoffDistance);
	uint32 fogTech = 0;
	ConfigINI.GetUInt("Fog", "Technique", fogTech);
	g_iFogTech = static_cast<EFogTech>(fogTech);

	// Fog of War
	ConfigINI.GetBool("FogOfWar", "bBuildingsShadows", g_bBuildingsShadows);
	ConfigINI.GetBool("FogOfWar", "bMaskedObjects", g_bMaskedObjects);
	ConfigINI.GetBool("FogOfWar", "bMapBounds", g_bMapBounds);

	// PostProcess
	if (PostProcessing)
	{
		ConfigINI.GetBool("PostProcess", "bEnabled", g_bEnableHDR);

		ConfigINI.GetFloat("PostProcess", "Tonemapper.FilmSlope", PostProcessing->fFilmSlope);
		ConfigINI.GetFloat("PostProcess", "Tonemapper.FilmToe", PostProcessing->fFilmToe);
		ConfigINI.GetFloat("PostProcess", "Tonemapper.FilmShoulder", PostProcessing->fFilmShoulder);
		ConfigINI.GetFloat("PostProcess", "Tonemapper.FilmBlackClip", PostProcessing->fFilmBlackClip);
		ConfigINI.GetFloat("PostProcess", "Tonemapper.FilmWhiteClip", PostProcessing->fFilmWhiteClip);

		ConfigINI.GetFloat("PostProcess", "ColorGrading.WhiteBalance.Temp", PostProcessing->fWhiteTemp);
		ConfigINI.GetFloat("PostProcess", "ColorGrading.WhiteBalance.Tint", PostProcessing->fWhiteTint);

		ConfigINI.GetColor("PostProcess", "ColorGrading.Global.Saturation", PostProcessing->vColorSaturation);
		ConfigINI.GetColor("PostProcess", "ColorGrading.Global.Contrast", PostProcessing->vColorContrast);
		ConfigINI.GetColor("PostProcess", "ColorGrading.Global.Gamma", PostProcessing->vColorGamma);
		ConfigINI.GetColor("PostProcess", "ColorGrading.Global.Gain", PostProcessing->vColorGain);
		ConfigINI.GetColor("PostProcess", "ColorGrading.Global.Offset", PostProcessing->vColorOffset);

		ConfigINI.GetColor("PostProcess", "ColorGrading.Shadows.Saturation", PostProcessing->vColorSaturationShadows);
		ConfigINI.GetColor("PostProcess", "ColorGrading.Shadows.Contrast", PostProcessing->vColorContrastShadows);
		ConfigINI.GetColor("PostProcess", "ColorGrading.Shadows.Gamma", PostProcessing->vColorGammaShadows);
		ConfigINI.GetColor("PostProcess", "ColorGrading.Shadows.Gain", PostProcessing->vColorGainShadows);
		ConfigINI.GetColor("PostProcess", "ColorGrading.Shadows.Offset", PostProcessing->vColorOffsetShadows);
		ConfigINI.GetFloat("PostProcess", "ColorGrading.Shadows.ShadowsMax", PostProcessing->fColorCorrectionShadowsMax);

		ConfigINI.GetColor("PostProcess", "ColorGrading.Midtones.Saturation", PostProcessing->vColorSaturationMidtones);
		ConfigINI.GetColor("PostProcess", "ColorGrading.Midtones.Contrast", PostProcessing->vColorContrastMidtones);
		ConfigINI.GetColor("PostProcess", "ColorGrading.Midtones.Gamma", PostProcessing->vColorGammaMidtones);
		ConfigINI.GetColor("PostProcess", "ColorGrading.Midtones.Gain", PostProcessing->vColorGainMidtones);
		ConfigINI.GetColor("PostProcess", "ColorGrading.Midtones.Offset", PostProcessing->vColorOffsetMidtones);

		ConfigINI.GetColor("PostProcess", "ColorGrading.Highlights.Saturation", PostProcessing->vColorSaturationHighlights);
		ConfigINI.GetColor("PostProcess", "ColorGrading.Highlights.Contrast", PostProcessing->vColorContrastHighlights);
		ConfigINI.GetColor("PostProcess", "ColorGrading.Highlights.Gamma", PostProcessing->vColorGammaHighlights);
		ConfigINI.GetColor("PostProcess", "ColorGrading.Highlights.Gain", PostProcessing->vColorGainHighlights);
		ConfigINI.GetColor("PostProcess", "ColorGrading.Highlights.Offset", PostProcessing->vColorOffsetHighlights);
		ConfigINI.GetFloat("PostProcess", "ColorGrading.Highlights.HighlightsMin", PostProcessing->fColorCorrectionHighlightsMin);

		ConfigINI.GetBool("PostProcess", "ColorGrading.UserLUT.bEnabled", PostProcessing->bUserLUT);
		ConfigINI.GetString("PostProcess", "ColorGrading.UserLUT.Texture", PostProcessing->userLutTextureFileName);
		ConfigINI.GetFloat("PostProcess", "ColorGrading.UserLUT.Intensity", PostProcessing->fUserLutIntensity);

		ConfigINI.GetFloat("PostProcess", "ColorGrading.BlueCorrection", PostProcessing->fBlueCorrection);
		ConfigINI.GetFloat("PostProcess", "ColorGrading.ExpandGamut", PostProcessing->fExpandGamut);

		ConfigINI.GetBool("PostProcess", "AutoExposure.bEnabled", PostProcessing->bAutoExposure);
		ConfigINI.GetFloat("PostProcess", "AutoExposure.MinBrightness", PostProcessing->fAutoExposureMinBrightness);
		ConfigINI.GetFloat("PostProcess", "AutoExposure.MaxBrightness", PostProcessing->fAutoExposureMaxBrightness);
		ConfigINI.GetFloat("PostProcess", "AutoExposure.SpeedUp", PostProcessing->fAutoExposureSpeedUp);
		ConfigINI.GetFloat("PostProcess", "AutoExposure.SpeedDown", PostProcessing->fAutoExposureSpeedDown);
		ConfigINI.GetFloat("PostProcess", "AutoExposure.ExposureBias", PostProcessing->fAutoExposureBias);
		ConfigINI.GetFloat("PostProcess", "AutoExposure.HistogramLogMin", PostProcessing->fAutoExposureHistogramLogMin);
		ConfigINI.GetFloat("PostProcess", "AutoExposure.HistogramLogMax", PostProcessing->fAutoExposureHistogramLogMax);
		ConfigINI.GetFloat("PostProcess", "AutoExposure.CalibrationConstant", PostProcessing->fAutoExposureCalibrationConstant);

		ConfigINI.GetBool("PostProcess", "SSAO.bEnabled", PostProcessing->bSSAO);
		ConfigINI.GetBool("PostProcess", "SSAO.bDownsample", PostProcessing->bSSAODownsample);
		ConfigINI.GetFloat("PostProcess", "SSAO.Intensity", PostProcessing->fSSAOIntensity);
		ConfigINI.GetFloat("PostProcess", "SSAO.Radius", PostProcessing->fSSAORadius);
		ConfigINI.GetFloat("PostProcess", "SSAO.Contrast", PostProcessing->fSSAOContrast);
		ConfigINI.GetFloat("PostProcess", "SSAO.GeometryCoeff", PostProcessing->fSSAOGeometryCoeff);
		ConfigINI.GetFloat("PostProcess", "SSAO.Beta", PostProcessing->fSSAOBeta);

		ConfigINI.GetBool("PostProcess", "SSR.bEnabled", PostProcessing->bSSR);
		ConfigINI.GetBool("PostProcess", "SSR.bDownsample", PostProcessing->bSSRDownsample);
		ConfigINI.GetFloat("PostProcess", "SSR.Step", PostProcessing->fSSRRayStep);
		ConfigINI.GetFloat("PostProcess", "SSR.RayhitThreshold", PostProcessing->fSSRRayhitThreshold);

		ConfigINI.GetBool("PostProcess", "ContactShadows.bEnabled", PostProcessing->bContactShadows);
		ConfigINI.GetBool("PostProcess", "ContactShadows.bDownsample", PostProcessing->bContactShadowsDownsample);
		ConfigINI.GetFloat("PostProcess", "ContactShadows.RayLength", PostProcessing->fContactShadowsRayLength);

		ConfigINI.GetBool("PostProcess", "Bloom.bEnabled", PostProcessing->bBloom);
		ConfigINI.GetFloat("PostProcess", "Bloom.Treshhold", PostProcessing->fBloomThreshold);
		ConfigINI.GetFloat("PostProcess", "Bloom.Intensity", PostProcessing->fBloomIntensity);
		ConfigINI.GetUInt("PostProcess", "Bloom.Passes", PostProcessing->iBloomPasses);
		ConfigINI.GetFloat("PostProcess", "Bloom.AnamorphicRatio", PostProcessing->fBloomAnamorphicRatio);

		ConfigINI.GetBool("PostProcess", "Bloom.bLensDirt", PostProcessing->bLensDirt);
		ConfigINI.GetString("PostProcess", "Bloom.LensDirtTexture", PostProcessing->lensDirtTextureFileName);
		ConfigINI.GetFloat("PostProcess", "Bloom.LensDirtIntensity", PostProcessing->fLensDirtIntensity);

		ConfigINI.GetBool("PostProcess", "CA.bEnabled", PostProcessing->bChromaticAberration);
		ConfigINI.GetFloat("PostProcess", "CA.Intensity", PostProcessing->fChromaticAberrationIntensity);

		ConfigINI.GetBool("PostProcess", "Vignette.bEnabled", PostProcessing->bVignette);
		ConfigINI.GetBool("PostProcess", "Vignette.bRounded", PostProcessing->bVignetteRounded);
		ConfigINI.GetColor("PostProcess", "Vignette.Color", PostProcessing->vVignetteColor);
		ConfigINI.GetFloat("PostProcess", "Vignette.Intensity", PostProcessing->fVignetteIntensity);
		ConfigINI.GetFloat("PostProcess", "Vignette.Smoothness", PostProcessing->fVignetteSmoothness);
		ConfigINI.GetFloat("PostProcess", "Vignette.Roundness", PostProcessing->fVignetteRoundness);

		ConfigINI.GetBool("PostProcess", "FilmGrain.bEnabled", PostProcessing->bFilmGrain);
		ConfigINI.GetFloat("PostProcess", "FilmGrain.Intensity", PostProcessing->fFilmGrainIntensity);
		ConfigINI.GetFloat("PostProcess", "FilmGrain.Variance", PostProcessing->fFilmGrainVariance);
		ConfigINI.GetUInt("PostProcess", "FilmGrain.SignalToNoiseRatio", PostProcessing->iFilmGrainSignalToNoiseRatio);

		ConfigINI.GetBool("PostProcess", "Dithering.bEnabled", PostProcessing->bDithering);

		ConfigINI.GetBool("PostProcess", "AA.SMAA.bEnabled", PostProcessing->bSMAA);
		ConfigINI.GetFloat("PostProcess", "AA.SMAA.Threshold", PostProcessing->fSMAAThreshold);
		ConfigINI.GetUInt("PostProcess", "AA.SMAA.SearchSteps", PostProcessing->iSMAASearchSteps);
		ConfigINI.GetUInt("PostProcess", "AA.SMAA.DiagSearchSteps", PostProcessing->iSMADiagSearchSteps);
		ConfigINI.GetFloat("PostProcess", "AA.SMAA.CornerRounding", PostProcessing->fSMAACornerRounding);
		uint32 smaaInput = 0;
		ConfigINI.GetUInt("PostProcess", "AA.SMAA.Input", smaaInput);
		PostProcessing->iSMAAInput = static_cast<SMAA::Input>(smaaInput);

		ConfigINI.GetBool("PostProcess", "AA.TAA.bEnabled", PostProcessing->bTemporalAA);
		ConfigINI.GetFloat("PostProcess", "AA.TAA.JitterSpread", PostProcessing->fJitterSpreadTAA);
		ConfigINI.GetFloat("PostProcess", "AA.TAA.Sharpness", PostProcessing->fSharpnessTAA);
		ConfigINI.GetFloat("PostProcess", "AA.TAA.StationaryBlending", PostProcessing->fStationaryBlendingTAA);
		ConfigINI.GetFloat("PostProcess", "AA.TAA.MotionBlending", PostProcessing->fMotionBlendingTAA);

		ConfigINI.GetUInt("PostProcess", "GammaCorrection.OutputDevice", PostProcessing->iOutputDevice);
		ConfigINI.GetUInt("PostProcess", "GammaCorrection.ColorGamut", PostProcessing->iColorGamut);
		ConfigINI.GetFloat("PostProcess", "GammaCorrection.Gamma", PostProcessing->fGamma);
	}

	// Hotkeys
	ConfigINI.GetUInt("Hotkeys", "ShowSettings", hotkey_ShowAntTweakBar);
	ConfigINI.GetUInt("Hotkeys", "PauseGame", hotkey_PauseGame);
	ConfigINI.GetUInt("Hotkeys", "TakeScreenshot", hotkey_TakeScreenshot);

	return true;
}

void CEngine::TakeScreenshot()
{
	IDirect3DSurface9* pRenderTarget = nullptr;
	if (m_pDevice->GetBackBuffer(0, 0, D3DBACKBUFFER_TYPE_MONO, &pRenderTarget) == D3D_OK)
	{
		CreateDirectoryA((RenderEdgePath + "Screenshots").c_str(), 0);

		static uint32 screenshotNumber = 0;
		if (++screenshotNumber == 100)
			screenshotNumber = 1;

		SYSTEMTIME time;
		GetSystemTime(&time);

		std::ostringstream filePath;
		filePath << std::right << std::setfill('0')
			<< RenderEdgePath << "Screenshots\\RenderEdge_"
			<< std::setw(2) << time.wMonth
			<< std::setw(2) << time.wDay
			<< std::setw(2) << time.wYear % 100 << '_'
			<< std::setw(2) << time.wHour
			<< std::setw(2) << time.wMinute
			<< std::setw(2) << time.wSecond << '_'
			<< std::setw(2) << screenshotNumber << ".png";

		D3DXSaveSurfaceToFileA(filePath.str().c_str(), D3DXIFF_PNG, pRenderTarget, nullptr, nullptr);
		pRenderTarget->Release();
	}
}


void CEngine::InitTemporaryResources()
{
	if (!g_depthRT.Create(m_pDevice, g_vBufferSize.x, g_vBufferSize.y, 1, ETextureUsage::DepthStencil, g_depthFormat))
		Message("Failed to create DepthTexture");

	if (!g_mainRT.Create(m_pDevice, g_vBufferSize.x, g_vBufferSize.y, 1, ETextureUsage::RenderTarget, ETextureFormat::RGBAHalf))
		Message("Failed to create HDRTexture");
}

void CEngine::ReleaseTemporaryResources()
{
	SAFE_RELEASE(g_pBackBuffer);

	g_mainRT.Release();
	g_depthRT.Release();
	g_normalTexture.Release();
	g_envTexture.Release();
}

void CEngine::ReloadShaders()
{
	if (ResourceManager)
	{
		SAFE_RELEASE(g_pStandardFX);
		ResourceManager->LoadShader("Shaders\\Standard.cso", nullptr, &g_pStandardFX);

		SAFE_RELEASE(g_pSkyboxFX);
		ResourceManager->LoadShader("Shaders\\Skybox.cso", nullptr, &g_pSkyboxFX);

		if (CascadedShadows)
		{
			SAFE_RELEASE(CascadedShadows->m_pEffect);
			ResourceManager->LoadShader("Shaders\\Shadows.cso", nullptr, &CascadedShadows->m_pEffect);
		}

		if (PostProcessing)
		{
			SAFE_RELEASE(PostProcessing->m_pEffect);
			ResourceManager->LoadShader("Shaders\\PostProcess.cso", nullptr, &PostProcessing->m_pEffect);
		}
	}
}

void CEngine::OnCreateDevice()
{
	start_time = std::chrono::high_resolution_clock::now();
	last_frame_duration = std::chrono::milliseconds(1);

	GetBackBufferSize();
	UpdateWidescreenFix(g_vBufferSize.x * g_vBufferSize.w);
	GetSupportedDepthFormat();

	const std::string mpqPath = RenderEdgePath + "RenderEdge.mpq";
	if (!MPQ::OpenArchive(mpqPath, &mpqRenderEdge))
		Message("Failed to load MPQ:\n" + mpqPath);

	FreeCamera = new CCamera();
	ResourceManager = new CResourceManager(m_pDevice);
	PostProcessing = new CPostProcessing(m_pDevice);
	CascadedShadows = new CCascadedShadows(m_pDevice);
	AntTweakBar = new CAntTweakBar(m_pDevice);
	FontManager = new CFontManager(m_pDevice);
	TextureManager = new CTextureManager(m_pDevice);
	SystemTextures = new CSystemTextures(m_pDevice);
	CustomUI = new CGUI(m_pDevice);

	D3DXCreateFontW(m_pDevice, 0, 0, FW_BOLD, 1, FALSE, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, ANTIALIASED_QUALITY, DEFAULT_PITCH | FF_DONTCARE, L"Arial", &g_pFont);

	InitTemporaryResources();

	if (ResourceManager)
	{
		ResourceManager->LoadShader("Shaders\\Standard.cso", nullptr, &g_pStandardFX);
		ResourceManager->LoadShader("Shaders\\Skybox.cso", nullptr, &g_pSkyboxFX);
	}

	ReadConfigFile("RenderEdge.ini");
}

void CEngine::OnLostDevice()
{
	if (AntTweakBar)
		AntTweakBar->OnLostDevice();

	if (g_pFont)
		g_pFont->OnLostDevice();

	if (g_pStandardFX)
		g_pStandardFX->OnLostDevice();

	if (g_pSkyboxFX)
		g_pSkyboxFX->OnLostDevice();

	if (CascadedShadows)
		CascadedShadows->OnLostDevice();

	if (PostProcessing)
		PostProcessing->OnLostDevice();

	if (CustomUI)
		CustomUI->OnLostDevice();

	if (SystemTextures)
		SystemTextures->OnLostDevice();

	ReleaseTemporaryResources();
}

void CEngine::OnResetDevice()
{
	GetBackBufferSize();
	UpdateWidescreenFix(g_vBufferSize.x * g_vBufferSize.w);

	if (AntTweakBar)
		AntTweakBar->OnResetDevice();

	if (g_pFont)
		g_pFont->OnResetDevice();

	if (g_pStandardFX)
		g_pStandardFX->OnResetDevice();

	if (g_pSkyboxFX)
		g_pSkyboxFX->OnResetDevice();

	if (CascadedShadows)
		CascadedShadows->OnResetDevice();

	if (PostProcessing)
		PostProcessing->OnResetDevice();

	if (CustomUI)
		CustomUI->OnResetDevice();

	if (SystemTextures)
		SystemTextures->OnResetDevice();

	InitTemporaryResources();
}


void CEngine::OnGameState()
{
	if (IsGaming())
	{
		if (!bMapInit)
		{
			bMapInit = true;
			OnMapStart();
		}
	}
	else
	{
		if (bMapInit)
		{
			bMapInit = false;
			OnMapEnd();
		}
	}
}

void CEngine::OnMapStart()
{
	LOG(DEBUG) << "========= On Map Start ================";

	BUFFER buffer;
	if (MPQ::LoadFile(nullptr, "(listfile)", buffer, true))
	{
		std::string listFile = (char*)buffer.GetData();

		// Reload config file from map
		if (listFile.find("RenderEdge.ini") != -1)
			ReadConfigFile("RenderEdge.ini");

		// Reload Shaders
		if (ResourceManager)
		{
			if (listFile.find("Shaders\\Standard.cso") != -1)
			{
				SAFE_RELEASE(g_pStandardFX);
				ResourceManager->LoadShader("Shaders\\Standard.cso", nullptr, &g_pStandardFX, true);
			}
			if (listFile.find("Shaders\\PostProcess.cso") != -1 && PostProcessing)
			{
				SAFE_RELEASE(PostProcessing->m_pEffect);
				ResourceManager->LoadShader("Shaders\\PostProcess.cso", nullptr, &PostProcessing->m_pEffect, true);
			}
			if (listFile.find("Shaders\\Skybox.cso") != -1)
			{
				SAFE_RELEASE(g_pSkyboxFX);
				ResourceManager->LoadShader("Shaders\\Skybox.cso", nullptr, &g_pSkyboxFX, true);
			}
		}
	}

	g_iFoggedTerrainColor = MiscDataGetColor("FogOfWar", "FoggedTerrain");
	g_iFoggedObjectColor = MiscDataGetColor("FogOfWar", "FoggedObject");
	g_iBoundaryTerrainColor = MiscDataGetColor("FogOfWar", "BoundaryTerrain");
	g_iBoundaryObjectColor = MiscDataGetColor("FogOfWar", "BoundaryObject");
	g_iFoggedBoundaryTerrainColor = MiscDataGetColor("FogOfWar", "FoggedBoundaryTerrain");
	g_iFoggedBoundaryObjectColor = MiscDataGetColor("FogOfWar", "FoggedBoundaryObject");

	if (*((uint32*)Jass::GetTerrain() + 2167))
	{
		g_iMaskedTerrainColor = MiscDataGetColor("FogOfWar", "DarkMaskedTerrain");
		g_iMaskedObjectColor = MiscDataGetColor("FogOfWar", "DarkMaskedObject");
	}
	else
	{
		g_iMaskedTerrainColor = MiscDataGetColor("FogOfWar", "BlackMaskedTerrain");
		g_iMaskedObjectColor = MiscDataGetColor("FogOfWar", "BlackMaskedObject");
	}

	if (g_bFreeCamera)
		UpdateFreeCamera();
	if (!g_bUserInterface)
		UpdateUserInterface();
	if (!g_bMaskedObjects)
		UpdateMaskedObject();
	if (!g_bBuildingsShadows)
		UpdateBuildingsShadows();
	if (!g_bMapBounds)
		UpdateMapBounds();
}

void CEngine::OnMapEnd()
{
	LOG(DEBUG) << "========= On Map End ==================";

	if (CustomUI)
		CustomUI->Release();

	g_bMapLoaded = false;
	ClearExecuteTriggers();
}


void CEngine::UpdateLightAndFog()
{
	// Get graphic device interface
	uint32 pGxDevice = Jass::GetGxDevice();

	// Update Directional and Point Light
	const float fInvRadius = 1.0f / g_fDefaultPointLightRadius;
	float fIntensityMul = g_fDefaultPointLightIntensity;

	if (g_DefaultPointLightIntensityUnits == ELightUnits::Candelas)
		fIntensityMul *= (100.0f * 100.0f);
	else if (g_DefaultPointLightIntensityUnits == ELightUnits::Lumens)
		fIntensityMul *= (100.0f * 100.0f / 4 / D3DX_PI);
	else
		fIntensityMul *= 16.0f;

	g_iPointLightCount = 0;
	g_bGlobalPointLight = false;

	g_vGlobalLightDir = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_vGlobalLightColor = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_vGlobalAmbientColor = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	uint32 index = 0;
	uint32 pLightData = pGxDevice + 572;
	for (uint32 i = 0; i < 8; i++, pLightData += 36)
	{
		g_vPointLightColorAndIntensity[i] = 0;
		g_vPointLightPosAndInvRadius[i] = 0;

		const bool bEnabled = *(uint32*)(pLightData - 16) != 0;
		if (bEnabled)
		{
			const bool bPointLight = *(uint32*)(pLightData - 12) != 0;
			if (bPointLight)
			{
				const D3DXVECTOR3 color = D3DXVECTOR3(*(BYTE*)(pLightData + 10), *(BYTE*)(pLightData + 9), *(BYTE*)(pLightData + 8)) / 255.0f;
				const D3DXVECTOR3 pos = D3DXVECTOR3(*(float*)(pLightData - 8), *(float*)(pLightData - 4), *(float*)(pLightData));
				const float intensity = *(float*)(pLightData + 16) * fIntensityMul;

				FColor linearColor = g_bPointLightColorSRGB ? FColor::ToLinear(color) : color;
				g_vPointLightColorAndIntensity[index] = FColor(linearColor, intensity);
				g_vPointLightPosAndInvRadius[index] = FColor(pos, fInvRadius);

				index++;
				g_iPointLightCount++;
				g_bGlobalPointLight = true;
			}
			else
			{
				const float lightIntensity = *(float*)(pLightData + 16);
				const float ambientIntensity = *(float*)(pLightData + 12);
				FColor lightColor = FColor(*(BYTE*)(pLightData + 10), *(BYTE*)(pLightData + 9), *(BYTE*)(pLightData + 8)) / 255.0f;
				FColor ambientColor = FColor(*(BYTE*)(pLightData + 6), *(BYTE*)(pLightData + 5), *(BYTE*)(pLightData + 4)) / 255.0f;

				if (g_bLightColorSRGB)
					lightColor.ToLinear();
				if (g_bAmbientColorSRGB)
					ambientColor.ToLinear();

				g_vGlobalLightColor = lightColor * lightIntensity;
				g_vGlobalAmbientColor = ambientColor * ambientIntensity;
				g_vGlobalLightDir = D3DXVECTOR3(*(float*)(pLightData - 8), *(float*)(pLightData - 4), *(float*)(pLightData));
			}
		}
	}

	// Update Fog
	if (g_bDefaultFog)
	{
		DWORD dwFogMode = ((DWORD*)address_dwSceneSettings1)[*(DWORD*)(pGxDevice + 884)];
		DWORD dwFogColor = *(DWORD*)(pGxDevice + 900);

		FColor linearColor = D3DXVECTOR3(GetBValue(dwFogColor) / 255.0f, GetGValue(dwFogColor) / 255.0f, GetRValue(dwFogColor) / 255.0f);
		if (g_bFogColorSRGB)
			linearColor.ToLinear();
		g_vGlobalFogColor = linearColor;

		if (dwFogMode == D3DFOG_LINEAR)
		{
			DWORD dwFogStart = *(DWORD*)(pGxDevice + 888);
			DWORD dwFogEnd = *(DWORD*)(pGxDevice + 892);

			g_iGlobalFogTech = EFogTech::Linear;
			g_fGlobalFogStart = *reinterpret_cast<float*>(&dwFogStart);
			g_fGlobalFogEnd = *reinterpret_cast<float*>(&dwFogEnd);
		}
		else if (dwFogMode == D3DFOG_EXP)
		{
			DWORD dwFogDensity = *(DWORD*)(pGxDevice + 896);

			g_iGlobalFogTech = EFogTech::Exponential;
			g_fGlobalFogDensity = *reinterpret_cast<float*>(&dwFogDensity);
		}
		else if (dwFogMode == D3DFOG_EXP2)
		{
			DWORD dwFogDensity = *(DWORD*)(pGxDevice + 896);

			g_iGlobalFogTech = EFogTech::Exponential2;
			g_fGlobalFogDensity = *reinterpret_cast<float*>(&dwFogDensity);
		}
	}


	if (!g_bSceneUpdated)
	{
		g_bSceneUpdated = true;

		// Fog
		const float fogDensity = (g_bDefaultFog ? g_fGlobalFogDensity : g_fFogDensity) * 0.001f;
		const float fogHeightFalloff = g_fFogHeightFalloff * 0.001f;
		const float collapsedFogParameterPower = math::Clamp(-fogHeightFalloff * (g_vCameraPos.z - g_fFogHeight), -126.0f + 1.0f, +127.0f - 1.0f);
		const float collapsedFogParameter = fogDensity * pow(2.0f, collapsedFogParameterPower);

		g_pStandardFX->SetInt("g_iFogTech", g_bDefaultFog ? (uint32)g_iGlobalFogTech : (uint32)g_iFogTech);
		g_pStandardFX->SetValue("g_vFogColor", g_bDefaultFog ? &g_vGlobalFogColor : &g_vFogColor, sizeof(D3DXVECTOR3));
		g_pStandardFX->SetFloat("g_fFogStartDistance", g_bDefaultFog ? g_fGlobalFogStart : g_fFogStart);
		g_pStandardFX->SetFloat("g_fFogEndDistance", g_bDefaultFog ? g_fGlobalFogEnd : g_fFogEnd);
		g_pStandardFX->SetFloat("g_fFogDensity", fogDensity);
		g_pStandardFX->SetFloat("g_fFogHeight", g_fFogHeight);
		g_pStandardFX->SetFloat("g_fFogMinOpacity", 1.0f - g_fFogMaxOpacity);
		g_pStandardFX->SetFloat("g_fFogHeightFalloff", fogHeightFalloff);
		g_pStandardFX->SetFloat("g_fFogCutoffDistance", g_fFogCutoffDistance);
		g_pStandardFX->SetFloat("g_fCollapsedFogParameter", collapsedFogParameter);
		g_pStandardFX->SetBool("g_bFogSun", g_bFogSun);
		g_pStandardFX->SetValue("g_vFogSunColor", &g_vFogSunColor, sizeof(g_vFogSunColor));
		g_pStandardFX->SetFloat("g_fFogSunIntensity", g_fFogSunIntensity);
		g_pStandardFX->SetFloat("g_fFogSunStartDistance", g_fFogSunStartDistance);

		/*g_pStandardFX->SetFloat("mBetaRs", 1.0f / (mBetaRs * 100.0f));
		g_pStandardFX->SetFloat("mBetaMs", 1.0f / (mBetaMs * 100.0f));
		g_pStandardFX->SetFloat("mBetaMa", 1.0f / (mBetaMa * 100.0f));
		g_pStandardFX->SetFloat("mMieAsymmetry", mMieAsymmetry);
		g_pStandardFX->SetFloat("mScaleHeight", g_fFogHeight);
		g_pStandardFX->SetValue("mAlbedoR", &mAlbedoR, sizeof(mAlbedoR));
		g_pStandardFX->SetValue("mAlbedoM", &mAlbedoM, sizeof(mAlbedoM));
		g_pStandardFX->SetValue("mSunColor", &g_vFogSunColor, sizeof(g_vFogSunColor));
		g_pStandardFX->SetValue("mAmbColor", &g_vFogColor, sizeof(g_vFogColor));*/
	}

	// Sky and Directional Light
	g_pStandardFX->SetBool("g_bSkyLight", g_bSkyLight && !g_bDefaultAmbientColor);
	g_pStandardFX->SetFloat("g_fSkyLightIntensity", g_fSkyLightIntensity);
	g_pStandardFX->SetValue("g_vSkyColor", &g_vSkyColor, sizeof(g_vSkyColor));
	g_pStandardFX->SetValue("g_vIndColor", &g_vIndColor, sizeof(g_vIndColor));
	g_pStandardFX->SetValue("g_vAmbColor", g_bDefaultAmbientColor ? &g_vGlobalAmbientColor : &g_vAmbColor, sizeof(D3DXVECTOR3));
	g_pStandardFX->SetValue("g_vLightDir", g_bDefaultLightDir ? &g_vGlobalLightDir : &g_vLightDir, sizeof(D3DXVECTOR3));
	FColor lightColor = g_bDefaultLightColor ? g_vGlobalLightColor : FColor(g_vLightColor) * (g_bUseTemperature ? FColor::FromTemperature(g_fLightTemperature) : 1.0f);
	lightColor *= g_fLightIntensity;
	g_pStandardFX->SetValue("g_vLightColor", &lightColor, sizeof(D3DXVECTOR3));

	// Point Light
	g_pStandardFX->SetValue("g_vPointLightColorAndIntensity", &g_vPointLightColorAndIntensity, sizeof(g_vPointLightColorAndIntensity));
	g_pStandardFX->SetValue("g_vPointLightPosAndInvRadius", &g_vPointLightPosAndInvRadius, sizeof(g_vPointLightPosAndInvRadius));
	g_pStandardFX->SetFloat("g_iPointLightCount", (g_bPointLight && g_bGlobalPointLight) ? g_iPointLightCount : 0);
}

void CEngine::OnCalcSceneView_before(uint32 pCamera)
{
	// Override camera parameters
	if (FreeCamera && FreeCamera->GetActive())
	{
		*(float*)(pCamera + 60) = FreeCamera->m_vEyePosition.x;
		*(float*)(pCamera + 64) = FreeCamera->m_vEyePosition.y;
		*(float*)(pCamera + 68) = FreeCamera->m_vEyePosition.z;

		*(float*)(pCamera + 100) = FreeCamera->m_vTargetPosition.x;
		*(float*)(pCamera + 104) = FreeCamera->m_vTargetPosition.y;
		*(float*)(pCamera + 108) = FreeCamera->m_vTargetPosition.z;

		*(float*)(pCamera + 276) = D3DXToRadian(g_fCameraFoV);
		*(float*)(pCamera + 204) = g_fCameraNearZ;
		*(float*)(pCamera + 172) = g_fCameraFarZ;

		g_vCameraPos = FreeCamera->GetEyePosition();
		g_vCameraRotation = FreeCamera->GetRotation() * D3DX_PI / 180.0f;
	}
	// Get camera parameters
	else
	{
		g_fCameraFoV = D3DXToDegree(*(float*)(pCamera + 276));
		g_fCameraNearZ = *(float*)(pCamera + 204);
		g_fCameraFarZ = *(float*)(pCamera + 172);

		g_vCameraPos = D3DXVECTOR3(
			*(float*)(pCamera + 60),
			*(float*)(pCamera + 64),
			*(float*)(pCamera + 68));

		g_vCameraRotation = D3DXVECTOR3(
			*(float*)(pCamera + 356),
			*(float*)(pCamera + 236),
			*(float*)(pCamera + 316));
	}

	// Get viewport and screen size
	D3DVIEWPORT9 viewport;
	m_pDevice->GetViewport(&viewport);

	g_vViewportSize = D3DXVECTOR4(
		viewport.Width,
		viewport.Height,
		1.0f / viewport.Width,
		1.0f / viewport.Height);

	g_vViewportRect = D3DXVECTOR4(
		viewport.X * g_vBufferSize.z,
		viewport.Y * g_vBufferSize.w,
		(viewport.X + g_vViewportSize.x) * g_vBufferSize.z,
		(viewport.Y + g_vViewportSize.y) * g_vBufferSize.w);

	g_vScreenPositionScaleBias = D3DXVECTOR4(
		g_vViewportSize.x * g_vBufferSize.z * 0.5f,
		g_vViewportSize.y * g_vBufferSize.w * -0.5f,
		(viewport.X + g_vViewportSize.x * 0.5f) * g_vBufferSize.z,
		(viewport.Y + g_vViewportSize.y * 0.5f) * g_vBufferSize.w);

	D3DXVECTOR4 vScreenPositionScaleBiasHalfPixelOffset = g_vScreenPositionScaleBias + D3DXVECTOR4(0.0f, 0.0f, 0.5f * g_vBufferSize.z, 0.5f * g_vBufferSize.w);

	// Common values
	g_pStandardFX->SetValue("g_vScreenScaleBias", &vScreenPositionScaleBiasHalfPixelOffset, sizeof(D3DXVECTOR4));
	g_pStandardFX->SetValue("g_vCameraPos", g_vCameraPos, sizeof(D3DXVECTOR3));
	g_pStandardFX->SetBool("g_bLinearOutput", g_bHDRStarted);
	g_pStandardFX->SetFloat("g_fDebugValue", g_fDebugValue);
	g_pStandardFX->SetValue("g_vMouseTerrain", &Input::vMousePosTerrain, sizeof(D3DXVECTOR3));
}

void CEngine::OnCalcSceneView_after()
{
	// Get Matrices
	m_pDevice->GetTransform(D3DTS_VIEW, &g_mView);
	m_pDevice->GetTransform(D3DTS_PROJECTION, &g_mProj);
	g_mProjNonJittered = g_mProj;

	// Temporal Anti-Aliasing
	if (g_bEnableHDR && PostProcessing)
	{
		if (PostProcessing->bTemporalAA)
		{
			OnFrameRenderingSetup(8);
			PostProcessing->SetJitteredProjectionMatrix();
		}
		else
		{
			OnFrameRenderingSetup(1);
		}
	}
}


void CEngine::OnBeginScene()
{
	// Reset values
	g_bPostProcessRendered = false;
	g_bSceneUpdated = false;
	RenderingHook::iCurrentRenderStage = ERenderStage::Unknown;

	g_iPointLightCount = 0;

	if (CascadedShadows)
	{
		CascadedShadows->iUnitsCount = 0;
		CascadedShadows->iChunksCount = 0;
	}

	// Set custom depth surface
	m_pDevice->SetDepthStencilSurface(g_depthRT.GetSurface());
	m_pDevice->Clear(0, nullptr, D3DCLEAR_ZBUFFER, 0x00000000, 1.0f, 0);

	// Set HDR render target
	if (g_bEnableHDR && !g_bDefaultRenderer && !g_bHDRStarted && IsGaming() && g_bMapLoaded)
	{
		g_bHDRStarted = true;

		m_pDevice->GetBackBuffer(0, 0, D3DBACKBUFFER_TYPE_MONO, &g_pBackBuffer);
		m_pDevice->SetRenderTarget(0, g_mainRT.GetSurface());
		m_pDevice->Clear(0, nullptr, D3DCLEAR_TARGET | D3DCLEAR_STENCIL, 0x00000000, 1.0f, 0);
	}

	// Render Shadows
	if (CascadedShadows && CascadedShadows->IsEnabled() && !IsInGameMenu() && IsGaming())
	{
		IDirect3DStateBlock9* pStateBlock = nullptr;
		m_pDevice->CreateStateBlock(D3DSBT_ALL, &pStateBlock);

		CascadedShadows->Render();

		pStateBlock->Apply();
		pStateBlock->Release();
	}

	// Release hooked meshes
	if (CascadedShadows)
		CascadedShadows->ReleaseMeshes();
}

void CEngine::OnEndScene()
{
	if (g_bHDRStarted)
	{
		m_pDevice->SetRenderTarget(0, g_pBackBuffer);
		SAFE_RELEASE(g_pBackBuffer);
		g_bHDRStarted = false;
	}
}

void CEngine::OnPresent()
{
	// Update values for Post Processing
	{
		last_frame_duration = std::chrono::high_resolution_clock::now() - last_present_time;
		last_present_time += last_frame_duration;
		g_fTimer = std::fmod(std::chrono::duration_cast<std::chrono::nanoseconds>(last_present_time - start_time).count() * 1e-6f, 16777216.0f);
	}

	// Check is map loaded or not. TODO: find better way
	OnGameState();

	// Get FPS
	CalculateFrameRate();

	// Update FreeCamera
	if (FreeCamera)
		FreeCamera->Update(g_fDeltaTime);

	ExecuteFrameUpdateTriggers();

	// Render helper UI
	if (m_pDevice->BeginScene() == D3D_OK)
	{
		// Render AntTweakBar
		if (AntTweakBar)
			AntTweakBar->Render();

		// Debug Info
		if (g_bDebugInfo)
			RenderText();

		m_pDevice->EndScene();
	}

	// Capture back buffer
	if (g_bTakeScreenshot)
	{
		TakeScreenshot();
		g_bTakeScreenshot = false;
	}
}


void CEngine::OnRenderWorld()
{
	// Load textures if nessesary
	if (g_bIBL)
		if (ResourceManager && g_envTexture.IsEmpty())
			ResourceManager->LoadTextureCube(g_envTextureFileName, &g_envTexture);

	if (g_bNormalMapping)
		if (ResourceManager && g_normalTexture.IsEmpty())
			ResourceManager->LoadTexture2D(g_normalTextureFileName, &g_normalTexture);

	/*static Texture2D envTexture;
	if (ResourceManager && envTexture.IsEmpty())
		ResourceManager->LoadTexture2D("Textures\\HDR\\fireplace_2k.hdr", &envTexture);
	g_pStandardFX->SetTexture("g_envTexture2", envTexture.GetTexture());
	g_pSkyboxFX->SetTexture("g_envTexture2", envTexture.GetTexture());*/

	// Image Based Lighting
	float fEnvCubemapReflectionAngle = D3DXToRadian(g_fEnvCubemapRotation);
	D3DXVECTOR2 vEnvCubemapRotation = D3DXVECTOR2(sinf(fEnvCubemapReflectionAngle), cosf(fEnvCubemapReflectionAngle));
	g_pStandardFX->SetValue("g_vEnvCubemapRotation", &vEnvCubemapRotation, sizeof(D3DXVECTOR2));
	g_pStandardFX->SetFloat("g_fCubemapBrightness", g_fCubemapBrightness);
	g_pStandardFX->SetBool("g_bEnvCubemapSwapYZ", g_bEnvCubemapSwapYZ);
	g_pStandardFX->SetTexture("g_envTexture", g_envTexture.GetTexture());
	if (SystemTextures)
		g_pStandardFX->SetTexture("g_preIntegratedGFTexture", SystemTextures->preIntegratedGFRT.GetTexture());

	// Shadows
	if (CascadedShadows)
	{
		g_pStandardFX->SetBool("g_bSoftShadows", CascadedShadows->bSoftShadows);
		g_pStandardFX->SetBool("g_bVisCascades", CascadedShadows->bVisCascades);
		g_pStandardFX->SetValue("g_vCascades", CascadedShadows->splitDepths, sizeof(CascadedShadows->splitDepths));
		g_pStandardFX->SetValue("g_mShadow", CascadedShadows->mShadow, sizeof(CascadedShadows->mShadow));
		g_pStandardFX->SetFloat("g_fSoftTransitionScale", CascadedShadows->fSoftTransitionScale);
		g_pStandardFX->SetFloat("g_fShadowSharpen", CascadedShadows->fShadowSharpen);
		g_pStandardFX->SetFloat("g_fRadius", CascadedShadows->fRadius);
		g_pStandardFX->SetValue("g_vShadowBufferSize", CascadedShadows->vShadowBufferSize, sizeof(CascadedShadows->vShadowBufferSize));
		g_pStandardFX->SetFloat("g_fShadowPartitionSize", 1.0f / NUM_CASCADES);
		g_pStandardFX->SetTexture("g_shadowTexture", CascadedShadows->GetTexture());
	}

	// Other
	g_pStandardFX->SetTexture("g_normalTexture", g_normalTexture.GetTexture());

	if (PostProcessing)
	{
		g_pStandardFX->SetTexture("g_reflectionTexture", (g_bEnableHDR && PostProcessing->bSSR) ? PostProcessing->ssrRT.GetTexture() : nullptr);
		g_pStandardFX->SetTexture("g_contactShadowsTexture", PostProcessing->contactShadowsRT.GetTexture());
		g_pStandardFX->SetTexture("g_aoTexture", PostProcessing->ssaoRT.GetTexture());
	}
}

void CEngine::OnRenderUI()
{
	if (!g_bMapLoaded)
		g_bMapLoaded = true;

	if (CustomUI && g_bCustomUserInterface)
	{
		IDirect3DStateBlock9* pStateBlock = nullptr;
		m_pDevice->CreateStateBlock(D3DSBT_ALL, &pStateBlock);

		CustomUI->Render();

		pStateBlock->Apply();
		pStateBlock->Release();
	}
}


HRESULT CEngine::OnDrawIndexedPrimitive(D3DPRIMITIVETYPE primitiveType, int32 baseVertexIndex, uint32 minIndex, uint32 numVertices, uint32 startIndex, uint32 primitiveCount, uint32 stride, IDirect3DTexture9* currentTexture)
{
	const ERenderStage curRenderStage = RenderingHook::GetRenderStage();

	if (g_bDefaultRenderer)
	{
		if (curRenderStage == ERenderStage::UI)
		{
			// Hide UI
			if (!g_bUserInterface)
				return D3D_OK;
		}

		return m_pDevice->DrawIndexedPrimitive(primitiveType, baseVertexIndex, minIndex, numVertices, startIndex, primitiveCount);
	}
	else
	{
		// Hooking meshes
		if (CascadedShadows)
		{
			if (curRenderStage == ERenderStage::Terrain)
			{
				CascadedShadows->iChunksCount++;

				// Hook Terrain Meshes
				if (CascadedShadows->bTerrainShadows && !IsInGameMenu())
					CascadedShadows->terrainMeshes.push_back(new Mesh(m_pDevice, currentTexture, primitiveType, numVertices, primitiveCount));
			}
			else if (curRenderStage == ERenderStage::Unit || curRenderStage == ERenderStage::Destructible || curRenderStage == ERenderStage::Decoration)
			{
				if (!RenderingHook::IsTranslucent())
				{
					CascadedShadows->iUnitsCount++;

					// Hook Unit Meshes
					if (CascadedShadows->bObjectsShadows && !IsInGameMenu())
						CascadedShadows->unitMeshes.push_back(new Mesh(m_pDevice, currentTexture, primitiveType, numVertices, primitiveCount));
				}
			}
		}

		// Rendering
		if (curRenderStage == ERenderStage::Skybox)
		{
			UpdateLightAndFog();

			// Texture Filtering and Gamma Correction
			m_pDevice->SetSamplerState(0, D3DSAMP_SRGBTEXTURE, 1);

			// Matrices
			D3DXMATRIX mWorld, mTextureTransform;
			m_pDevice->GetTransform(D3DTS_TEXTURE0, &mTextureTransform);

			if (g_bSkyboxFixTwitching)
			{
				D3DXMatrixTranslation(&mWorld, g_vCameraPos.x, g_vCameraPos.y, g_vCameraPos.z);
			}
			else
			{
				m_pDevice->GetTransform(D3DTS_WORLD, &mWorld);
			}

			g_pSkyboxFX->SetMatrix("g_mTextureTransform", &mTextureTransform);
			g_pSkyboxFX->SetMatrix("g_mWorld", &mWorld);
			g_pSkyboxFX->SetMatrix("g_mWorldViewProjection", &(mWorld * g_mView * g_mProj));
			g_pSkyboxFX->SetBool("g_bLinearOutput", g_bHDRStarted);

			// Material
			D3DMATERIAL9 material;
			m_pDevice->GetMaterial(&material);
			bool bEmissive = (material.Emissive.r != 0.0f || material.Emissive.g != 0.0f || material.Emissive.b != 0.0f || material.Emissive.a != 0.0f);
			FColor matDiffuse = bEmissive ? material.Emissive : material.Diffuse;
			if (g_bMaterialColorSRGB) matDiffuse.ToLinear();
			g_pSkyboxFX->SetValue("g_vMaterialDiffuse", &matDiffuse, sizeof(FColor));
			g_pSkyboxFX->SetFloat("g_fBrightness", g_fSkyboxLightIntensity);

			// Fog
			g_pSkyboxFX->SetBool("g_bFog", g_bSkyboxFog);
			g_pSkyboxFX->SetValue("g_vFogColor", g_bDefaultFog ? &g_vGlobalFogColor : &g_vFogColor, sizeof(D3DXVECTOR3));
			g_pSkyboxFX->SetBool("g_bFogSun", g_bFogSun);
			g_pSkyboxFX->SetValue("g_vFogSunColor", &g_vFogSunColor, sizeof(g_vFogSunColor));
			g_pSkyboxFX->SetFloat("g_fFogSunIntensity", g_fFogSunIntensity);

			/*g_pSkyboxFX->SetFloat("mBetaRs", 1.0f / (mBetaRs * 100.0f));
			g_pSkyboxFX->SetFloat("mBetaMs", 1.0f / (mBetaMs * 100.0f));
			g_pSkyboxFX->SetFloat("mBetaMa", 1.0f / (mBetaMa * 100.0f));
			g_pSkyboxFX->SetFloat("mMieAsymmetry", mMieAsymmetry);
			g_pSkyboxFX->SetFloat("mScaleHeight", g_fFogHeight);
			g_pSkyboxFX->SetValue("mAlbedoR", &mAlbedoR, sizeof(mAlbedoR));
			g_pSkyboxFX->SetValue("mAlbedoM", &mAlbedoM, sizeof(mAlbedoM));
			g_pSkyboxFX->SetValue("mSunColor", &g_vFogSunColor, sizeof(g_vFogSunColor));
			g_pSkyboxFX->SetValue("mAmbColor", &g_vFogColor, sizeof(g_vFogColor));*/

			// Skybox Shading
			bool bLit = !bEmissive && g_bSkyboxShading;
			g_pSkyboxFX->SetBool("g_bLighting", bLit);
			g_pSkyboxFX->SetValue("g_vLightDirection", (g_bDefaultLightDir || g_bSkyboxFog) ? &g_vGlobalLightDir : &g_vLightDir, sizeof(D3DXVECTOR3));
			if (bLit && !g_bSkyboxFog)
			{
				g_pSkyboxFX->SetValue("g_vLightDiffuse", g_bDefaultAmbientColor ? &g_vGlobalAmbientColor : &g_vAmbColor, sizeof(D3DXVECTOR3));
				g_pSkyboxFX->SetValue("g_vLightAmbient", g_bDefaultLightColor ? &g_vGlobalLightColor : &g_vLightColor, sizeof(D3DXVECTOR3));
			}

			// Other
			g_pSkyboxFX->SetValue("g_vCameraPos", g_vCameraPos, sizeof(D3DXVECTOR3));

			// Technique
			g_pSkyboxFX->SetTechnique("Standard");


			//=============== Render Object ==================
			uint32 uPasses = 0;
			g_pSkyboxFX->Begin(&uPasses, 0);
			g_pSkyboxFX->BeginPass(0);

			//m_pDevice->SetVertexDeclaration(g_pVertexDecl);
			m_pDevice->DrawIndexedPrimitive(primitiveType, baseVertexIndex, minIndex, numVertices, startIndex, primitiveCount);

			g_pSkyboxFX->EndPass();
			g_pSkyboxFX->End();
			//===============================================


			return D3D_OK;
		}
		else if (curRenderStage == ERenderStage::Terrain || curRenderStage == ERenderStage::Ubersplat)
		{
			UpdateLightAndFog();

			// Texture Filtering and Gamma Correction
			m_pDevice->SetSamplerState(0, D3DSAMP_SRGBTEXTURE, 1);
			if (g_bAnisoFiltering)
			{
				m_pDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_ANISOTROPIC);
				m_pDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_ANISOTROPIC);
				m_pDevice->SetSamplerState(0, D3DSAMP_MIPFILTER, D3DTEXF_ANISOTROPIC);
				m_pDevice->SetSamplerState(0, D3DSAMP_MAXANISOTROPY, g_iMaxAnisotropy);
			}

			// Matrices
			D3DXMATRIX mWorld;
			m_pDevice->GetTransform(D3DTS_WORLD, &mWorld);
			g_pStandardFX->SetMatrix("g_mWorld", &mWorld);
			g_pStandardFX->SetMatrix("g_mWorldViewProjection", &(mWorld * g_mView * g_mProj));

			// Material
			DWORD bFog;
			m_pDevice->GetRenderState(D3DRS_FOGENABLE, &bFog);
			g_pStandardFX->SetBool("g_bTexture", g_bTexture);
			g_pStandardFX->SetBool("g_bMaterialUnshaded", g_bSimpleMaterial);
			g_pStandardFX->SetBool("g_bMaterialUnfogged", !(bFog && g_bEnableFog) || g_bSimpleMaterial);
			g_pStandardFX->SetBool("g_bPBS", g_bPBS);
			g_pStandardFX->SetFloat("g_fMaterialRoughness", g_fTerrainRoughness);
			g_pStandardFX->SetFloat("g_fMaterialMetallic", g_fTerrainMetallic);
			g_pStandardFX->SetFloat("g_fMaterialSpecular", g_fTerrainSpecular);
			g_pStandardFX->SetFloat("g_fMaterialTranslucent", 0.0f);

			// Other
			g_pStandardFX->SetBool("g_bIBL", g_bIBL);
			g_pStandardFX->SetBool("g_bShadows", CascadedShadows && CascadedShadows->IsEnabled());
			g_pStandardFX->SetBool("g_bNormalMapping", g_bNormalMapping && !g_normalTexture.IsEmpty());
			g_pStandardFX->SetBool("g_bContactShadows", g_bEnableHDR && PostProcessing && PostProcessing->bContactShadows && !PostProcessing->contactShadowsRT.IsEmpty());
			g_pStandardFX->SetBool("g_bSSAO", g_bEnableHDR && PostProcessing && PostProcessing->bSSAO && !PostProcessing->ssaoRT.IsEmpty());
			g_pStandardFX->SetBool("g_bPointLight", g_bPointLight && g_bGlobalPointLight);

			// Technique
			g_pStandardFX->SetTechnique("Terrain");


			//=============== Render Object =================
			uint32 uPasses = 0;
			g_pStandardFX->Begin(&uPasses, 0);
			g_pStandardFX->BeginPass(0);

			m_pDevice->DrawIndexedPrimitive(primitiveType, baseVertexIndex, minIndex, numVertices, startIndex, primitiveCount);

			g_pStandardFX->EndPass();
			g_pStandardFX->End();
			//===============================================


			return D3D_OK;
		}
		else if (curRenderStage == ERenderStage::FogOfWar)
		{
			UpdateLightAndFog();

			// Texture Filtering and Gamma Correction
			m_pDevice->SetSamplerState(0, D3DSAMP_SRGBTEXTURE, 1);

			// Matrices
			D3DXMATRIX mWorld;
			m_pDevice->GetTransform(D3DTS_WORLD, &mWorld);
			g_pStandardFX->SetMatrix("g_mWorld", &mWorld);
			g_pStandardFX->SetMatrix("g_mWorldViewProjection", &(mWorld * g_mView * g_mProj));

			// Material
			DWORD bFog;
			m_pDevice->GetRenderState(D3DRS_FOGENABLE, &bFog);
			g_pStandardFX->SetBool("g_bTexture", true);
			g_pStandardFX->SetBool("g_bMaterialUnshaded", g_bSimpleMaterial);
			g_pStandardFX->SetBool("g_bMaterialUnfogged", !(bFog && g_bEnableFog) || g_bSimpleMaterial);
			g_pStandardFX->SetBool("g_bPBS", false);

			// Other
			g_pStandardFX->SetBool("g_bPointLight", false);
			g_pStandardFX->SetBool("g_bIBL", false);
			g_pStandardFX->SetBool("g_bNormalMapping", false);
			g_pStandardFX->SetBool("g_bContactShadows", false);
			g_pStandardFX->SetBool("g_bSSAO", false);
			g_pStandardFX->SetBool("g_bShadows", false);

			// Technique
			g_pStandardFX->SetTechnique("Terrain");


			//=============== Render Object ==================
			uint32 uPasses = 0;
			g_pStandardFX->Begin(&uPasses, 0);
			g_pStandardFX->BeginPass(0);

			//m_pDevice->SetVertexDeclaration(g_pVertexDecl);
			m_pDevice->DrawIndexedPrimitive(primitiveType, baseVertexIndex, minIndex, numVertices, startIndex, primitiveCount);

			g_pStandardFX->EndPass();
			g_pStandardFX->End();
			//===============================================


			return D3D_OK;
		}
		else if (curRenderStage == ERenderStage::Unit || curRenderStage == ERenderStage::Destructible || curRenderStage == ERenderStage::Decoration || curRenderStage == ERenderStage::Building || curRenderStage == ERenderStage::Indicator || curRenderStage == ERenderStage::OcclusionMask || curRenderStage == ERenderStage::Lightning || curRenderStage == ERenderStage::Weather || curRenderStage == ERenderStage::TerrainShadow || curRenderStage == ERenderStage::WaterShadow || curRenderStage == ERenderStage::Footprint || curRenderStage == ERenderStage::SelectionCircle || curRenderStage == ERenderStage::Water)
		{
			UpdateLightAndFog();

			// Texture Filtering and Gamma Correction
			m_pDevice->SetSamplerState(0, D3DSAMP_SRGBTEXTURE, 1);
			if (g_bAnisoFiltering)
			{
				m_pDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_ANISOTROPIC);
				m_pDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_ANISOTROPIC);
				m_pDevice->SetSamplerState(0, D3DSAMP_MIPFILTER, D3DTEXF_ANISOTROPIC);
				m_pDevice->SetSamplerState(0, D3DSAMP_MAXANISOTROPY, g_iMaxAnisotropy);
			}

			// Matrices
			D3DXMATRIX mWorld, mView, mTextureTransform;
			m_pDevice->GetTransform(D3DTS_TEXTURE0, &mTextureTransform);
			m_pDevice->GetTransform(D3DTS_WORLD, &mWorld);
			//if (stride == 36)
			m_pDevice->GetTransform(D3DTS_VIEW, &mView);
			g_pStandardFX->SetMatrix("g_mTextureTransform", &mTextureTransform);
			g_pStandardFX->SetMatrix("g_mWorld", &mWorld);
			g_pStandardFX->SetMatrix("g_mWorldViewProjection", &(mWorld * mView * g_mProj));

			// Material
			D3DMATERIAL9 material;
			DWORD bFog, bLighting;
			m_pDevice->GetMaterial(&material);
			m_pDevice->GetRenderState(D3DRS_FOGENABLE, &bFog);
			m_pDevice->GetRenderState(D3DRS_LIGHTING, &bLighting);
			bool bEmissive = (material.Emissive.r != 0.0f || material.Emissive.g != 0.0f || material.Emissive.b != 0.0f || material.Emissive.a != 0.0f);
			bool bVertexColor = (stride == 36) && g_bVertexColor;
			bool bUnshaded = (!bLighting || bEmissive) && g_bUnshadedMaterials;
			bool bUnfogged = (!bFog && g_bUnfoggedMaterials) || !g_bEnableFog;
			FColor matDiffuse = bEmissive ? material.Emissive : material.Diffuse;
			if (g_bMaterialColor && g_bMaterialColorSRGB)
				matDiffuse.ToLinear();
			g_pStandardFX->SetBool("g_bTexture", g_bTexture);
			g_pStandardFX->SetBool("g_bVertexColor", bVertexColor);
			g_pStandardFX->SetBool("g_bVertexColorSRGB", g_bVertexColorSRGB);
			g_pStandardFX->SetBool("g_bMaterialColor", g_bMaterialColor);
			g_pStandardFX->SetBool("g_bMaterialUnshaded", bUnshaded || g_bSimpleMaterial);
			g_pStandardFX->SetBool("g_bMaterialUnfogged", bUnfogged || g_bSimpleMaterial);
			if (curRenderStage == ERenderStage::Lightning)
				g_pStandardFX->SetValue("g_vMaterialEmissive", &D3DXVECTOR4(0.0f, 0.0f, 0.0f, 4.0f), sizeof(D3DXVECTOR4));
			else
				g_pStandardFX->SetValue("g_vMaterialEmissive", &D3DXVECTOR4(0.0f, 0.0f, 0.0f, 1.0f), sizeof(D3DXVECTOR4));
			g_pStandardFX->SetValue("g_vMaterialDiffuse", &matDiffuse, sizeof(FColor));
			g_pStandardFX->SetBool("g_bPBS", g_bPBS);
			g_pStandardFX->SetFloat("g_fMaterialRoughness", g_fMaterialRoughness);
			g_pStandardFX->SetFloat("g_fMaterialMetallic", g_fMaterialMetallic);
			g_pStandardFX->SetFloat("g_fMaterialSpecular", g_fMaterialSpecular);
			g_pStandardFX->SetFloat("g_fMaterialTranslucent", g_fMaterialTranslucent);

			// Other
			g_pStandardFX->SetBool("g_bIBL", g_bIBL);
			g_pStandardFX->SetBool("g_bShadows", CascadedShadows && CascadedShadows->IsEnabled());
			g_pStandardFX->SetBool("g_bNormalMapping", false);
			g_pStandardFX->SetBool("g_bContactShadows", g_bEnableHDR && PostProcessing && PostProcessing->bContactShadows && !PostProcessing->contactShadowsRT.IsEmpty());
			g_pStandardFX->SetBool("g_bSSAO", g_bEnableHDR && PostProcessing && PostProcessing->bSSAO && !PostProcessing->ssaoRT.IsEmpty());
			g_pStandardFX->SetBool("g_bPointLight", g_bPointLight && g_bGlobalPointLight);

			// Technique
			g_pStandardFX->SetTechnique("Standard");


			//=============== Render Object ==================
			uint32 uPasses = 0;
			g_pStandardFX->Begin(&uPasses, 0);
			g_pStandardFX->BeginPass(0);

			//m_pDevice->SetVertexDeclaration(g_pVertexDecl);
			m_pDevice->DrawIndexedPrimitive(primitiveType, baseVertexIndex, minIndex, numVertices, startIndex, primitiveCount);

			g_pStandardFX->EndPass();
			g_pStandardFX->End();
			//===============================================


			return D3D_OK;
		}
		else if (curRenderStage == ERenderStage::UI || curRenderStage == ERenderStage::FloatingText || curRenderStage == ERenderStage::SelectionBox)
		{
			// Texture Filtering and Gamma Correction
			m_pDevice->SetSamplerState(0, D3DSAMP_SRGBTEXTURE, 0);

			// Render Post Process
			if (!g_bPostProcessRendered)
			{
				if (PostProcessing && g_bHDRStarted)
				{
					IDirect3DStateBlock9* pStateBlock = nullptr;
					m_pDevice->CreateStateBlock(D3DSBT_ALL, &pStateBlock);

					PostProcessing->Render();

					SAFE_RELEASE(g_pBackBuffer);
					g_bHDRStarted = false;

					pStateBlock->Apply();
					pStateBlock->Release();
				}

				g_bPostProcessRendered = true;
			}

			// Hide Standard UI
			if (curRenderStage == ERenderStage::UI && !g_bUserInterface)
				return D3D_OK;

			m_pDevice->DrawIndexedPrimitive(primitiveType, baseVertexIndex, minIndex, numVertices, startIndex, primitiveCount);
		}
		else if (curRenderStage == ERenderStage::CineFilter || curRenderStage == ERenderStage::Unknown)
		{
			// Texture Filtering and Gamma Correction
			m_pDevice->SetSamplerState(0, D3DSAMP_SRGBTEXTURE, 0);

			m_pDevice->DrawIndexedPrimitive(primitiveType, baseVertexIndex, minIndex, numVertices, startIndex, primitiveCount);
		}
	}

	return D3D_OK;
}


bool CEngine::OnGetMessage(HWND ah_Wnd, uint32 uMsg, WPARAM wParam, LPARAM lParam)
{
	if (AntTweakBar)
		return AntTweakBar->OnGetMessage(ah_Wnd, uMsg, wParam, lParam);

	return false;
}

bool CEngine::OnMouseMove(uint32 x, uint32 y)
{
	return false;
}

bool CEngine::OnMouseButtonDown(EMouseButton button)
{
	if (FreeCamera)
		FreeCamera->OnMouseButtonDown(button);

	return false;
}

bool CEngine::OnMouseButtonUp(EMouseButton button)
{
	if (FreeCamera)
		FreeCamera->OnMouseButtonUp(button);

	return false;
}

bool CEngine::OnMouseWheel(int delta)
{
	if (FreeCamera)
		FreeCamera->OnMouseWheel(delta);

	return false;
}

bool CEngine::OnKeyboardDown(WPARAM getKey)
{
	if (getKey == hotkey_ShowAntTweakBar && AntTweakBar)
	{
		AntTweakBar->SetActive(!AntTweakBar->GetActive());
	}
	else if (getKey == hotkey_PauseGame && IsGaming() && !IsInGameMenu())
	{
		g_bGamePaused = !g_bGamePaused;
		JassNatives::PauseGame(g_bGamePaused);
	}
	else if (getKey == hotkey_TakeScreenshot)
	{
		g_bTakeScreenshot = true;
	}

	if (getKey == 'Z')
	{
		//ScreenLog::Clear();
		//char* dword_6FAAE64C = (char*)(address_GameBase + 0xAAE64C);
		//ScreenLog::Message() << fast_call<int>(address_GameBase + 0x4CA130, *(int **)dword_6FAAE64C, (int)"Rows");
	}

	if (FreeCamera)
		FreeCamera->OnKeyboardDown(getKey);

	return false;
}

bool CEngine::OnKeyboardUp(WPARAM getKey)
{
	if (FreeCamera)
		FreeCamera->OnKeyboardUp(getKey);

	return false;
}


void CEngine::RenderText()
{
	std::ostringstream output;

	uint32 mX = Input::GetMouseX();
	uint32 mY = Input::GetMouseY();

	PROCESS_MEMORY_COUNTERS memCounter;
	GetProcessMemoryInfo(GetCurrentProcess(), &memCounter, sizeof(memCounter));
	size_t memoryUsed = memCounter.WorkingSetSize >> 20;

	output << std::endl << RenderEdgeVersion << std::endl;

	output << std::endl << g_fFPS << " FPS" << std::endl;
	std::streamsize ss = output.precision();
	output << std::fixed << std::setprecision(0) << g_fDeltaTime * 1000.0f << std::defaultfloat << std::setprecision(ss) << " ms" << std::endl;
	output << memoryUsed << " MB" << std::endl << std::endl;

	output << "MouseX: " << mX << "  (" << mX * g_vBufferSize.z << ")" << std::endl;
	output << "MouseY: " << mY << "  (" << mY * g_vBufferSize.w << ")" << std::endl;

	if (CustomUI)
	{
		output << "Control ID: " << CustomUI->GetCtrlFromMousePoint() << std::endl << std::endl;
	}

	if (CascadedShadows)
	{
		output << "Objects in frame:" << std::endl;
		output << "Chunks: " << CascadedShadows->iChunksCount << std::endl;
		output << "Units:  " << CascadedShadows->iUnitsCount << std::endl << std::endl;
	}

	output << ScreenLog::stream.str() << std::endl;

	g_pFont->DrawTextA(0, output.str().c_str(), -1, nullptr, DT_EXPANDTABS | DT_LEFT, 0xEEEEEEFF);
}