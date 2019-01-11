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
#include "MPQ.h"
#include "INIReader.h"
#include "Log.h"

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


CEngine* Engine = nullptr;

const std::string RenderEdgeVersion = "RenderEdge v0.3.0b";
std::string RenderEdgePath;

std::chrono::high_resolution_clock::time_point start_time, last_present_time;
std::chrono::high_resolution_clock::duration last_frame_duration;


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

double GetTime()
{
	auto beginningOfTime = std::chrono::system_clock::now().time_since_epoch();
	auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(beginningOfTime).count();

	return ms * 0.001;
}


CEngine::CEngine(IDirect3DDevice9* pDevice)
{
	Engine = this;

	LOG(DEBUG) << "========= On Create Engine ============";
	LOG(INFO) << RenderEdgeVersion;

	m_pDevice = pDevice;

	hRenderEdgeMpq = nullptr;

	hotkey_ShowAntTweakBar = 0x76;
	hotkey_PauseGame = -1;
	hotkey_TakeScreenshot = -1;

	fWideScreenMul = 1.0f;

	fDeltaTime = 0.0f;
	fFPS = 0.0f;
	fTimer = 0.0f;

	bDefaultRenderer = false;
	bVsyncEnabled = true;
	bDebugInfo = true;
	bGamePaused = false;
	bTakeScreenshot = false;
	bWindowed = true;

	bFreeCamera = false;
	bDefaultProjectionMatrix = true;
	fCameraFoV = 70.0f;
	fCameraNearZ = 100.0f;
	fCameraFarZ = 5000.0f;
	vCameraPos = D3DXVECTOR3(0.0f, 0.0f, 1368.0f);
	//vCameraRotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	pStandardFX = nullptr;
	pSkyboxFX = nullptr;

	bHDRStarted = false;
	bPostProcessRendered = false;
	bSceneUpdated = false;
	bMapLoaded = false;

	bDefaultLightDir = true;
	bDefaultLightColor = true;
	bDefaultAmbientColor = true;
	bSkyLight = false;
	bUseTemperature = false;
	fSkyLightIntensity = 1.0f;
	fLightIntensity = 1.0f;
	fLightTemperature = 6500.0f;
	vSkyColor = D3DXVECTOR3(0.314f, 0.392f, 0.471f);
	vIndColor = D3DXVECTOR3(0.40f, 0.28f, 0.20f);
	vAmbColor = vGlobalAmbientColor = D3DXVECTOR3(0.2f, 0.2f, 0.2f);
	vLightDir = vGlobalLightDir = D3DXVECTOR3(-0.4f, 0.8f, -0.5f);
	vLightColor = vGlobalLightColor = D3DXVECTOR3(1.0f, 1.0f, 1.0f);

	bMaterialColorSRGB = true;
	bVertexColorSRGB = true;
	bAmbientColorSRGB = true;
	bLightColorSRGB = true;
	bPointLightColorSRGB = true;
	bFogColorSRGB = true;

	bEnableFog = true;
	bDefaultFog = true;
	//bGlobalFog = false;
	iFogTech = iGlobalFogTech = EFogTech::Linear;
	vFogColor = vGlobalFogColor = D3DXVECTOR3(0.5f, 0.6f, 0.7f);
	fFogStart = fGlobalFogStart = 0.0f;
	fFogEnd = fGlobalFogEnd = 5000.0f;
	fFogDensity = fGlobalFogDensity = 0.1f;
	fFogHeight = 1000.0f;
	fFogMaxOpacity = 1.0f;
	fFogHeightFalloff = 1.0f;
	fFogCutoffDistance = 0.0f;
	bFogSun = false;
	vFogSunColor = D3DXVECTOR3(1.0f, 0.9f, 0.7f);
	fFogSunIntensity = 8.0f;
	fFogSunStartDistance = 3000.0f;

	bDebugPointLight = false;
	bDebugLightMousePos = false;
	bDebugLightUseTemperature = false;
	fDebugLightTemperature = 6500.0f;
	vDebugLightColorAndIntensity = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 5000.0f);
	vDebugLightPosAndInvRadius = D3DXVECTOR4(0.0f, 0.0f, 150.0f, 1000.0f);
	DebugLightIntensityUnits = ELightUnits::Unitless;

	bTexture = true;
	bMaterialColor = true;
	bMaterialVertexColor = true;
	bTranslucentMaterials = true;
	bUnshadedMaterials = true;
	bUnfoggedMaterials = true;
	bAnisoFiltering = true;
	iMaxAnisotropy = 16;

	bGlobalPointLight = false;
	bPointLight = false;
	iPointLightCount = 0;
	DefaultPointLightIntensityUnits = ELightUnits::Unitless;
	fDefaultPointLightIntensity = 100.0f;
	fDefaultPointLightRadius = 10000.0f;

	bUserInterface = true;
	bCustomUserInterface = true;
	fDebugValue = 1.0f;
	vBlackBorders = D3DXVECTOR2(-0.02f, 0.13f);

	bFogOfWar = true;
	bMaskedObjects = true;
	bBuildingsShadows = true;
	bUnitsShadows = false;
	bMapBounds = true;
	iFoggedObjectColor = 0;
	iFoggedTerrainColor = 0;
	iMaskedObjectColor = 0;
	iMaskedTerrainColor = 0;
	iBoundaryTerrainColor = 0;
	iBoundaryObjectColor = 0;
	iFoggedBoundaryTerrainColor = 0;
	iFoggedBoundaryObjectColor = 0;

	bIBL = false;
	fEnvCubemapRotation = 0.0f;
	fCubemapBrightness = 1.0f;
	bEnvCubemapSwapYZ = true;
	envTextureFileName = "Textures\\Environment.dds";

	bPBS = false;
	bSimpleMaterial = false;
	fMaterialRoughness = 0.9f;
	fMaterialMetallic = 0.0f;
	fMaterialSpecular = 0.5f;
	fMaterialTranslucent = 0.0f;

	fTerrainRoughness = 0.9f;
	fTerrainMetallic = 0.0f;
	fTerrainSpecular = 0.5f;
	bNormalMapping = false;
	normalTextureFileName = "Textures\\test_normal.png";

	pBackBufferSurface = nullptr;
	depthFormat = ETextureFormat::Unknown;
	bEnableHDR = false;
	iFrameIndexMod8 = 0;

	bSkyboxShading = true;
	bSkyboxFog = false;
	bSkyboxFixTwitching = false;
	fSkyboxLightIntensity = 1.0f;

	pFont = nullptr;

	OnCreateDevice();
}

CEngine::~CEngine()
{
	LOG(DEBUG) << "========= On Destroy Engine ===========\n\n";

	Release();
}


void CEngine::InitTemporaryResources()
{
	if (!depthRT.Create(m_pDevice, vBufferSize.x, vBufferSize.y, 1, ETextureUsage::DepthStencil, depthFormat))
		Message("Failed to create DepthTexture");

	if (!mainRT.Create(m_pDevice, vBufferSize.x, vBufferSize.y, 1, ETextureUsage::RenderTarget, ETextureFormat::RGBAHalf))
		Message("Failed to create HDRTexture");
}

void CEngine::ReleaseTemporaryResources()
{
	SAFE_RELEASE(pBackBufferSurface);

	mainRT.Release();
	depthRT.Release();
	normalTexture.Release();
	envTexture.Release();
}

void CEngine::ReloadShaders()
{
	if (ResourceManager)
	{
		SAFE_RELEASE(pStandardFX);
		ResourceManager->LoadShader("Shaders\\Standard.cso", nullptr, &pStandardFX);

		SAFE_RELEASE(pSkyboxFX);
		ResourceManager->LoadShader("Shaders\\Skybox.cso", nullptr, &pSkyboxFX);
	}

	if (CascadedShadows)
		CascadedShadows->ReloadShaders();

	if (PostProcessing)
		PostProcessing->ReloadShaders();
}

void CEngine::OnCreateDevice()
{
	start_time = std::chrono::high_resolution_clock::now();
	last_frame_duration = std::chrono::milliseconds(1);

	GetBackBufferSize();
	UpdateWidescreenFix(vBufferSize.x * vBufferSize.w);
	GetSupportedDepthFormat();

	const std::string mpqPath = RenderEdgePath + "RenderEdge.mpq";
	if (!MPQ::OpenArchive(mpqPath, &hRenderEdgeMpq))
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

	D3DXCreateFontW(m_pDevice, 0, 0, FW_BOLD, 1, FALSE, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, ANTIALIASED_QUALITY, DEFAULT_PITCH | FF_DONTCARE, L"Arial", &pFont);

	InitTemporaryResources();

	if (ResourceManager)
	{
		ResourceManager->LoadShader("Shaders\\Standard.cso", nullptr, &pStandardFX);
		ResourceManager->LoadShader("Shaders\\Skybox.cso", nullptr, &pSkyboxFX);
	}

	ReadConfigFile("RenderEdge.ini");
}

void CEngine::OnLostDevice()
{
	if (AntTweakBar)
		AntTweakBar->OnLostDevice();

	if (pFont)
		pFont->OnLostDevice();

	if (pStandardFX)
		pStandardFX->OnLostDevice();

	if (pSkyboxFX)
		pSkyboxFX->OnLostDevice();

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
	UpdateWidescreenFix(vBufferSize.x * vBufferSize.w);

	if (AntTweakBar)
		AntTweakBar->OnResetDevice();

	if (pFont)
		pFont->OnResetDevice();

	if (pStandardFX)
		pStandardFX->OnResetDevice();

	if (pSkyboxFX)
		pSkyboxFX->OnResetDevice();

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

void CEngine::Release()
{
	SAFE_RELEASE(pFont);

	SAFE_RELEASE(pSkyboxFX);
	SAFE_RELEASE(pStandardFX);

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

	vBufferSize = D3DXVECTOR4(
		desc.Width,
		desc.Height,
		1.0f / desc.Width,
		1.0f / desc.Height);
}

void CEngine::UpdateWidescreenFix(float aspectRatio)
{
	fWideScreenMul = aspectRatio * 0.75f;
}

void CEngine::UpdateScreenMode()
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
		depthFormat = isINTZ ? ETextureFormat::INTZ : ETextureFormat::RAWZ;
	else
		Message("INTZ and RAWZ depth formats are not supported", "GetSupportedDepthFormat");
}

void CEngine::OnFrameRenderingSetup(uint32 SampleCount)
{
	if (PostProcessing)
	{
		PostProcessing->iTemporalAASampleIndex++;
		iFrameIndexMod8 = (iFrameIndexMod8 + 1) % 8;

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
	ConfigINI.GetBool("Engine", "bDefaultRenderer", bDefaultRenderer);
	ConfigINI.GetBool("Engine", "bDebugInfo", bDebugInfo);

	bool bShowSettings = false;
	ConfigINI.GetBool("Engine", "bShowSettings", bShowSettings);
	if (AntTweakBar)
		AntTweakBar->SetActive(bShowSettings);

	bool bVSync = false;
	ConfigINI.GetBool("Engine", "bVSync", bVSync);
	if (bVSync != bVsyncEnabled)
	{
		bVsyncEnabled = bVSync;
		ForceResetDevice8();
	}

	// Camera
	ConfigINI.GetBool("Camera", "bConstantVerticalFoV", bDefaultProjectionMatrix);
	ConfigINI.GetBool("Camera", "bFreeCamera", bFreeCamera);
	ConfigINI.GetFloat("Camera", "FoV", fCameraFoV);
	ConfigINI.GetFloat("Camera", "NearZ", fCameraNearZ);
	ConfigINI.GetFloat("Camera", "FarZ", fCameraFarZ);
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
	ConfigINI.GetBool("RenderStage", "bUserInterface", bUserInterface);
	ConfigINI.GetBool("RenderStage", "bCustomUserInterface", bCustomUserInterface);

	// Lighting
	ConfigINI.GetBool("Lighting", "SkyLight.bEnabled", bSkyLight);
	ConfigINI.GetBool("Lighting", "SkyLight.bDefaultColor", bDefaultAmbientColor);
	ConfigINI.GetBool("Lighting", "SkyLight.bColorSRGB", bAmbientColorSRGB);
	ConfigINI.GetColor("Lighting", "SkyLight.AmbColor", vAmbColor);
	ConfigINI.GetColor("Lighting", "SkyLight.SkyColor", vSkyColor);
	ConfigINI.GetColor("Lighting", "SkyLight.IndColor", vIndColor);
	ConfigINI.GetFloat("Lighting", "SkyLight.Intensity", fSkyLightIntensity);

	ConfigINI.GetBool("Lighting", "DirectionalLight.bDefaultColor", bDefaultLightColor);
	ConfigINI.GetBool("Lighting", "DirectionalLight.bColorSRGB", bLightColorSRGB);
	ConfigINI.GetBool("Lighting", "DirectionalLight.bDefaultDirection", bDefaultLightDir);
	ConfigINI.GetColor("Lighting", "DirectionalLight.Color", vLightColor);
	ConfigINI.GetVector3("Lighting", "DirectionalLight.Direction", vLightDir);
	ConfigINI.GetFloat("Lighting", "DirectionalLight.Intensity", fLightIntensity);
	ConfigINI.GetBool("Lighting", "DirectionalLight.bUseTemperature", bUseTemperature);
	ConfigINI.GetFloat("Lighting", "DirectionalLight.Temperature", fLightTemperature);

	ConfigINI.GetBool("Lighting", "PointLight.bEnabled", bPointLight);
	ConfigINI.GetBool("Lighting", "PointLight.bColorSRGB", bPointLightColorSRGB);
	ConfigINI.GetFloat("Lighting", "PointLight.Intensity", fDefaultPointLightIntensity);
	ConfigINI.GetFloat("Lighting", "PointLight.Radius", fDefaultPointLightRadius);
	uint32 pointLightUnits = 0;
	ConfigINI.GetUInt("Lighting", "PointLight.IntensityUnits", pointLightUnits);
	DefaultPointLightIntensityUnits = static_cast<ELightUnits>(pointLightUnits);

	// Image Based Lighting
	ConfigINI.GetBool("IBL", "bEnabled", bIBL);
	ConfigINI.GetString("IBL", "CubemapTexture", envTextureFileName);
	ConfigINI.GetFloat("IBL", "CubemapBrightness", fCubemapBrightness);
	ConfigINI.GetFloat("IBL", "CubemapRotation", fEnvCubemapRotation);
	ConfigINI.GetBool("IBL", "bCubemapSwapYZ", bEnvCubemapSwapYZ);

	// Terrain
	if (CascadedShadows)
		ConfigINI.GetBool("Terrain", "bCastShadows", CascadedShadows->bTerrainShadows);
	ConfigINI.GetFloat("Terrain", "Roughness", fTerrainRoughness);
	ConfigINI.GetFloat("Terrain", "Metallic", fTerrainMetallic);
	ConfigINI.GetFloat("Terrain", "Specular", fTerrainSpecular);
	ConfigINI.GetBool("Terrain", "bNormalMap", bNormalMapping);
	ConfigINI.GetString("Terrain", "NormalMapTexture", normalTextureFileName);

	// Objects
	if (CascadedShadows)
		ConfigINI.GetBool("Objects", "bCastShadows", CascadedShadows->bObjectsShadows);
	ConfigINI.GetFloat("Objects", "Roughness", fMaterialRoughness);
	ConfigINI.GetFloat("Objects", "Metallic", fMaterialMetallic);
	ConfigINI.GetFloat("Objects", "Specular", fMaterialSpecular);
	ConfigINI.GetFloat("Objects", "Translucent", fMaterialTranslucent);
	ConfigINI.GetBool("Objects", "bMaterialColor", bMaterialColor);
	ConfigINI.GetBool("Objects", "bMaterialVertexColor", bMaterialVertexColor);
	ConfigINI.GetBool("Objects", "bUnshadedMaterials", bUnshadedMaterials);
	ConfigINI.GetBool("Objects", "bUnfoggedMaterials", bUnfoggedMaterials);
	ConfigINI.GetBool("Objects", "bMaterialColorSRGB", bMaterialColorSRGB);
	ConfigINI.GetBool("Objects", "bVertexColorSRGB", bVertexColorSRGB);

	// Skybox
	ConfigINI.GetBool("Skybox", "bShading", bSkyboxShading);
	ConfigINI.GetBool("Skybox", "bUseFogColor", bSkyboxFog);
	ConfigINI.GetBool("Skybox", "bFixTwitching", bSkyboxFixTwitching);
	ConfigINI.GetFloat("Skybox", "Intensity", fSkyboxLightIntensity);

	// Fog of War
	ConfigINI.GetBool("FogOfWar", "bBuildingsShadows", bBuildingsShadows);
	ConfigINI.GetBool("FogOfWar", "bMaskedObjects", bMaskedObjects);
	ConfigINI.GetBool("FogOfWar", "bMapBounds", bMapBounds);

	// Shadows
	if (CascadedShadows)
	{
		ConfigINI.GetFloat("Shadows", "SoftTransitionScale", CascadedShadows->fSoftTransitionScale);
		ConfigINI.GetFloat("Shadows", "BlurRadius", CascadedShadows->fRadius);
		ConfigINI.GetFloat("Shadows", "AlphaThreshold", CascadedShadows->fAlphaThreshold);
		ConfigINI.GetFloat("Shadows", "FarZ", CascadedShadows->fFarZ);
		ConfigINI.GetFloat("Shadows", "FoV", CascadedShadows->fFoV);
		ConfigINI.GetUInt("Shadows", "ShadowMapSize", CascadedShadows->iShadowMapSize);
		uint32 cullMode = D3DCULL::D3DCULL_NONE;
		ConfigINI.GetUInt("Shadows", "CullMode", cullMode);
		CascadedShadows->iShadowCullMode = static_cast<D3DCULL>(cullMode);
	}

	// Material
	ConfigINI.GetBool("Material", "bEnablePBS", bPBS);
	ConfigINI.GetBool("Material", "bSimpleMaterial", bSimpleMaterial);
	ConfigINI.GetBool("Material", "bTextures", bTexture);
	ConfigINI.GetBool("Material", "bAnisoFiltering", bAnisoFiltering);
	ConfigINI.GetUInt("Material", "iMaxAnisotropy", iMaxAnisotropy);

	// Fog
	ConfigINI.GetBool("Fog", "bEnabled", bEnableFog);
	ConfigINI.GetBool("Fog", "bDefaultFog", bDefaultFog);
	ConfigINI.GetBool("Fog", "bColorSRGB", bFogColorSRGB);
	ConfigINI.GetBool("Fog", "bSun", bFogSun);
	ConfigINI.GetColor("Fog", "FogColor", vFogColor);
	ConfigINI.GetColor("Fog", "SunColor", vFogSunColor);
	ConfigINI.GetFloat("Fog", "SunIntensity", fFogSunIntensity);
	ConfigINI.GetFloat("Fog", "SunStartDistance", fFogSunStartDistance);
	ConfigINI.GetFloat("Fog", "Start", fFogStart);
	ConfigINI.GetFloat("Fog", "End", fFogEnd);
	ConfigINI.GetFloat("Fog", "Density", fFogDensity);
	ConfigINI.GetFloat("Fog", "Height", fFogHeight);
	ConfigINI.GetFloat("Fog", "MaxOpacity", fFogMaxOpacity);
	ConfigINI.GetFloat("Fog", "HeightFalloff", fFogHeightFalloff);
	ConfigINI.GetFloat("Fog", "CutoffDistance", fFogCutoffDistance);
	uint32 fogTech = 0;
	ConfigINI.GetUInt("Fog", "Technique", fogTech);
	iFogTech = static_cast<EFogTech>(fogTech);

	// PostProcess
	if (PostProcessing)
	{
		ConfigINI.GetBool("PostProcess", "bEnabled", bEnableHDR);

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

void CEngine::CalculateFrameRate()
{
	static double framesPerSecond = 0.0;
	static double startTime = GetTime();
	static double lastTime = GetTime();
	static double currentFPS = 0.0;

	double CurrentTime = GetTime();

	fDeltaTime = CurrentTime - lastTime;
	lastTime = CurrentTime;
	++framesPerSecond;

	if (CurrentTime - startTime > 1.0)
	{
		startTime = CurrentTime;
		fFPS = framesPerSecond;
		framesPerSecond = 0;
	}
}


void CEngine::UpdateFreeCamera()
{
	CGameUI* pGameUI = GetGameUI(0, 0);
	if (!pGameUI)
		return;

	bool bUserControl = !bFreeCamera;
	if (bUserControl != pGameUI->isUserInputEnabled)
		JassNatives::EnableUserControl(bUserControl);

	if (FreeCamera)
		FreeCamera->SetActive(bFreeCamera);
}

void CEngine::UpdateUserInterface()
{
	CGameUI* pGameUI = GetGameUI(0, 0);
	if (!pGameUI)
		return;

	uint32 pWorldFrameWar3 = pGameUI->WorldFrameWar3 + 180;
	uint32 pRootFrame = (uint32)pGameUI + 180;

	if (bUserInterface)
	{
		SetFramePoint(pWorldFrameWar3, EFramePoint::TopRight, pRootFrame, EFramePoint::TopRight, 0.0f, vBlackBorders.x);
		SetFramePoint(pWorldFrameWar3, EFramePoint::BottomLeft, pRootFrame, EFramePoint::BottomLeft, 0.0f, vBlackBorders.y);
	}
	else
	{
		vBlackBorders.x = GetFramePointY(pWorldFrameWar3, EFramePoint::TopRight);
		vBlackBorders.y = GetFramePointY(pWorldFrameWar3, EFramePoint::BottomLeft);

		SetFramePoint(pWorldFrameWar3, EFramePoint::TopRight, pRootFrame, EFramePoint::TopRight, 0.0f, 0.0f);
		SetFramePoint(pWorldFrameWar3, EFramePoint::BottomLeft, pRootFrame, EFramePoint::BottomLeft, 0.0f, 0.0f);
	}
}

void CEngine::UpdateMaskedObjectColor()
{
	if (bMaskedObjects)
		ApplyFogOfWarEx(2, 0xFFFFFFFF, iFoggedObjectColor, iMaskedObjectColor);
	else
		ApplyFogOfWarEx(2, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF);
}

void CEngine::UpdateBuildingsShadowsColor()
{
	if (bBuildingsShadows)
		ApplyFogOfWarEx(0, 0x00000000, iFoggedTerrainColor, iMaskedTerrainColor);
	else
		ApplyFogOfWarEx(0, 0x00000000, 0x00000000, iMaskedTerrainColor);
}

void CEngine::UpdateMapBoundsColor()
{
	if (bMapBounds)
	{
		ApplyFogOfWarEx(1, iBoundaryTerrainColor, iFoggedBoundaryTerrainColor, iMaskedTerrainColor);
		ApplyFogOfWarEx(3, iBoundaryObjectColor, iFoggedBoundaryObjectColor, iMaskedObjectColor);
	}
	else
	{
		ApplyFogOfWarEx(1, 0x00000000, 0x00000000, 0x00000000);
		ApplyFogOfWarEx(3, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF);
	}
}


void CEngine::OnGameState()
{
	static bool bMapInit = false;

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
				SAFE_RELEASE(pStandardFX);
				ResourceManager->LoadShader("Shaders\\Standard.cso", nullptr, &pStandardFX, true);
			}
			if (listFile.find("Shaders\\Skybox.cso") != -1)
			{
				SAFE_RELEASE(pSkyboxFX);
				ResourceManager->LoadShader("Shaders\\Skybox.cso", nullptr, &pSkyboxFX, true);
			}
			if (PostProcessing && listFile.find("Shaders\\PostProcess.cso") != -1)
			{
				PostProcessing->ReloadShaders();
			}
			if (CascadedShadows && listFile.find("Shaders\\Shadows.cso") != -1)
			{
				CascadedShadows->ReloadShaders();
			}
		}
	}

	iFoggedTerrainColor = MiscDataGetColor("FogOfWar", "FoggedTerrain");
	iFoggedObjectColor = MiscDataGetColor("FogOfWar", "FoggedObject");
	iBoundaryTerrainColor = MiscDataGetColor("FogOfWar", "BoundaryTerrain");
	iBoundaryObjectColor = MiscDataGetColor("FogOfWar", "BoundaryObject");
	iFoggedBoundaryTerrainColor = MiscDataGetColor("FogOfWar", "FoggedBoundaryTerrain");
	iFoggedBoundaryObjectColor = MiscDataGetColor("FogOfWar", "FoggedBoundaryObject");

	if (*((uint32*)Jass::GetTerrain() + 2167))
	{
		iMaskedTerrainColor = MiscDataGetColor("FogOfWar", "DarkMaskedTerrain");
		iMaskedObjectColor = MiscDataGetColor("FogOfWar", "DarkMaskedObject");
	}
	else
	{
		iMaskedTerrainColor = MiscDataGetColor("FogOfWar", "BlackMaskedTerrain");
		iMaskedObjectColor = MiscDataGetColor("FogOfWar", "BlackMaskedObject");
	}

	if (bFreeCamera)
		UpdateFreeCamera();
	if (!bUserInterface)
		UpdateUserInterface();
	if (!bMaskedObjects)
		UpdateMaskedObjectColor();
	if (!bBuildingsShadows)
		UpdateBuildingsShadowsColor();
	if (!bMapBounds)
		UpdateMapBoundsColor();
}

void CEngine::OnMapEnd()
{
	LOG(DEBUG) << "========= On Map End ==================";

	if (CustomUI)
		CustomUI->Release();

	bMapLoaded = false;
	ClearExecuteTriggers();
}


void CEngine::UpdateLightAndFog()
{
	// Get graphic device interface
	uint32 pGxDevice = Jass::GetGxDevice();

	// Update Directional and Point Light
	const float fInvRadius = 1.0f / fDefaultPointLightRadius;
	float fIntensityMul = fDefaultPointLightIntensity;

	if (DefaultPointLightIntensityUnits == ELightUnits::Candelas)
		fIntensityMul *= (100.0f * 100.0f);
	else if (DefaultPointLightIntensityUnits == ELightUnits::Lumens)
		fIntensityMul *= (100.0f * 100.0f / 4 / D3DX_PI);
	else
		fIntensityMul *= 16.0f;

	iPointLightCount = 0;
	bGlobalPointLight = false;

	vGlobalLightDir = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	vGlobalLightColor = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	vGlobalAmbientColor = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	uint32 index = 0;
	uint32 pLightData = pGxDevice + 572;
	for (uint32 i = 0; i < 8; i++, pLightData += 36)
	{
		vPointLightColorAndIntensity[i] = 0;
		vPointLightPosAndInvRadius[i] = 0;

		const bool bEnabled = *(uint32*)(pLightData - 16) != 0;
		if (bEnabled)
		{
			const bool bPointLight = *(uint32*)(pLightData - 12) != 0;
			if (bPointLight)
			{
				const D3DXVECTOR3 color = D3DXVECTOR3(*(BYTE*)(pLightData + 10), *(BYTE*)(pLightData + 9), *(BYTE*)(pLightData + 8)) / 255.0f;
				const D3DXVECTOR3 pos = D3DXVECTOR3(*(float*)(pLightData - 8), *(float*)(pLightData - 4), *(float*)(pLightData));
				const float intensity = *(float*)(pLightData + 16) * fIntensityMul;

				FColor linearColor = bPointLightColorSRGB ? FColor::ToLinear(color) : color;
				vPointLightColorAndIntensity[index] = FColor(linearColor, intensity);
				vPointLightPosAndInvRadius[index] = FColor(pos, fInvRadius);

				index++;
				iPointLightCount++;
				bGlobalPointLight = true;
			}
			else
			{
				const float lightIntensity = *(float*)(pLightData + 16);
				const float ambientIntensity = *(float*)(pLightData + 12);
				FColor lightColor = FColor(*(BYTE*)(pLightData + 10), *(BYTE*)(pLightData + 9), *(BYTE*)(pLightData + 8)) / 255.0f;
				FColor ambientColor = FColor(*(BYTE*)(pLightData + 6), *(BYTE*)(pLightData + 5), *(BYTE*)(pLightData + 4)) / 255.0f;

				if (bLightColorSRGB)
					lightColor.ToLinear();
				if (bAmbientColorSRGB)
					ambientColor.ToLinear();

				vGlobalLightColor = lightColor * lightIntensity;
				vGlobalAmbientColor = ambientColor * ambientIntensity;
				vGlobalLightDir = D3DXVECTOR3(*(float*)(pLightData - 8), *(float*)(pLightData - 4), *(float*)(pLightData));
			}
		}
	}

	// Update Fog
	if (bDefaultFog)
	{
		DWORD dwFogMode = ((DWORD*)address_dwSceneSettings1)[*(DWORD*)(pGxDevice + 884)];
		DWORD dwFogColor = *(DWORD*)(pGxDevice + 900);

		FColor linearColor = D3DXVECTOR3(GetBValue(dwFogColor) / 255.0f, GetGValue(dwFogColor) / 255.0f, GetRValue(dwFogColor) / 255.0f);
		if (bFogColorSRGB)
			linearColor.ToLinear();
		vGlobalFogColor = linearColor;

		if (dwFogMode == D3DFOG_LINEAR)
		{
			DWORD dwFogStart = *(DWORD*)(pGxDevice + 888);
			DWORD dwFogEnd = *(DWORD*)(pGxDevice + 892);

			iGlobalFogTech = EFogTech::Linear;
			fGlobalFogStart = *reinterpret_cast<float*>(&dwFogStart);
			fGlobalFogEnd = *reinterpret_cast<float*>(&dwFogEnd);
		}
		else if (dwFogMode == D3DFOG_EXP)
		{
			DWORD dwFogDensity = *(DWORD*)(pGxDevice + 896);

			iGlobalFogTech = EFogTech::Exponential;
			fGlobalFogDensity = *reinterpret_cast<float*>(&dwFogDensity);
		}
		else if (dwFogMode == D3DFOG_EXP2)
		{
			DWORD dwFogDensity = *(DWORD*)(pGxDevice + 896);

			iGlobalFogTech = EFogTech::Exponential2;
			fGlobalFogDensity = *reinterpret_cast<float*>(&dwFogDensity);
		}
	}


	if (!bSceneUpdated)
	{
		bSceneUpdated = true;

		// Fog
		const float fogDensity = (bDefaultFog ? fGlobalFogDensity : fFogDensity) * 0.001f;
		const float fogHeightFalloff = fFogHeightFalloff * 0.001f;
		const float collapsedFogParameterPower = math::Clamp(-fogHeightFalloff * (vCameraPos.z - fFogHeight), -126.0f + 1.0f, +127.0f - 1.0f);
		const float collapsedFogParameter = fogDensity * pow(2.0f, collapsedFogParameterPower);

		pStandardFX->SetInt("g_iFogTech", bDefaultFog ? (uint32)iGlobalFogTech : (uint32)iFogTech);
		pStandardFX->SetValue("g_vFogColor", bDefaultFog ? &vGlobalFogColor : &vFogColor, sizeof(D3DXVECTOR3));
		pStandardFX->SetFloat("g_fFogStartDistance", bDefaultFog ? fGlobalFogStart : fFogStart);
		pStandardFX->SetFloat("g_fFogEndDistance", bDefaultFog ? fGlobalFogEnd : fFogEnd);
		pStandardFX->SetFloat("g_fFogDensity", fogDensity);
		pStandardFX->SetFloat("g_fFogHeight", fFogHeight);
		pStandardFX->SetFloat("g_fFogMinOpacity", 1.0f - fFogMaxOpacity);
		pStandardFX->SetFloat("g_fFogHeightFalloff", fogHeightFalloff);
		pStandardFX->SetFloat("g_fFogCutoffDistance", fFogCutoffDistance);
		pStandardFX->SetFloat("g_fCollapsedFogParameter", collapsedFogParameter);
		pStandardFX->SetBool("g_bFogSun", bFogSun);
		pStandardFX->SetValue("g_vFogSunColor", &vFogSunColor, sizeof(vFogSunColor));
		pStandardFX->SetFloat("g_fFogSunIntensity", fFogSunIntensity);
		pStandardFX->SetFloat("g_fFogSunStartDistance", fFogSunStartDistance);
	}

	// Sky and Directional Light
	pStandardFX->SetBool("g_bSkyLight", bSkyLight && !bDefaultAmbientColor);
	pStandardFX->SetFloat("g_fSkyLightIntensity", fSkyLightIntensity);
	pStandardFX->SetValue("g_vSkyColor", &vSkyColor, sizeof(vSkyColor));
	pStandardFX->SetValue("g_vIndColor", &vIndColor, sizeof(vIndColor));
	pStandardFX->SetValue("g_vAmbColor", bDefaultAmbientColor ? &vGlobalAmbientColor : &vAmbColor, sizeof(D3DXVECTOR3));
	pStandardFX->SetValue("g_vLightDir", bDefaultLightDir ? &vGlobalLightDir : &vLightDir, sizeof(D3DXVECTOR3));
	FColor lightColor = bDefaultLightColor ? vGlobalLightColor : FColor(vLightColor) * (bUseTemperature ? FColor::FromTemperature(fLightTemperature) : 1.0f);
	lightColor *= fLightIntensity;
	pStandardFX->SetValue("g_vLightColor", &lightColor, sizeof(D3DXVECTOR3));

	// Point Light
	pStandardFX->SetValue("g_vPointLightColorAndIntensity", &vPointLightColorAndIntensity, sizeof(vPointLightColorAndIntensity));
	pStandardFX->SetValue("g_vPointLightPosAndInvRadius", &vPointLightPosAndInvRadius, sizeof(vPointLightPosAndInvRadius));
	pStandardFX->SetFloat("g_iPointLightCount", (bPointLight && bGlobalPointLight) ? iPointLightCount : 0);
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

		*(float*)(pCamera + 276) = D3DXToRadian(fCameraFoV);
		*(float*)(pCamera + 204) = fCameraNearZ;
		*(float*)(pCamera + 172) = fCameraFarZ;

		vCameraPos = FreeCamera->GetEyePosition();
		vCameraRotation = FreeCamera->GetRotation() * D3DX_PI / 180.0f;
	}
	// Get camera parameters
	else
	{
		fCameraFoV = D3DXToDegree(*(float*)(pCamera + 276));
		fCameraNearZ = *(float*)(pCamera + 204);
		fCameraFarZ = *(float*)(pCamera + 172);

		vCameraPos = D3DXVECTOR3(
			*(float*)(pCamera + 60),
			*(float*)(pCamera + 64),
			*(float*)(pCamera + 68));

		vCameraRotation = D3DXVECTOR3(
			*(float*)(pCamera + 356),
			*(float*)(pCamera + 236),
			*(float*)(pCamera + 316));
	}

	// Get viewport and screen size
	D3DVIEWPORT9 viewport;
	m_pDevice->GetViewport(&viewport);

	vViewportSize = D3DXVECTOR4(
		viewport.Width,
		viewport.Height,
		1.0f / viewport.Width,
		1.0f / viewport.Height);

	vViewportRect = D3DXVECTOR4(
		viewport.X * vBufferSize.z,
		viewport.Y * vBufferSize.w,
		(viewport.X + vViewportSize.x) * vBufferSize.z,
		(viewport.Y + vViewportSize.y) * vBufferSize.w);

	vScreenPositionScaleBias = D3DXVECTOR4(
		vViewportSize.x * vBufferSize.z * 0.5f,
		vViewportSize.y * vBufferSize.w * -0.5f,
		(viewport.X + vViewportSize.x * 0.5f) * vBufferSize.z,
		(viewport.Y + vViewportSize.y * 0.5f) * vBufferSize.w);

	D3DXVECTOR4 vScreenPositionScaleBiasHalfPixelOffset = vScreenPositionScaleBias + D3DXVECTOR4(0.0f, 0.0f, 0.5f * vBufferSize.z, 0.5f * vBufferSize.w);

	// Common values
	pStandardFX->SetValue("g_vScreenScaleBias", &vScreenPositionScaleBiasHalfPixelOffset, sizeof(vScreenPositionScaleBiasHalfPixelOffset));
	pStandardFX->SetValue("g_vCameraPos", vCameraPos, sizeof(vCameraPos));
	pStandardFX->SetBool("g_bLinearOutput", bHDRStarted);
	pStandardFX->SetFloat("g_fDebugValue", fDebugValue);
	pStandardFX->SetValue("g_vMouseTerrain", &Input::vMousePosTerrain, sizeof(Input::vMousePosTerrain));
}

void CEngine::OnCalcSceneView_after()
{
	// Get Matrices
	m_pDevice->GetTransform(D3DTS_VIEW, &mViewGlobal);
	m_pDevice->GetTransform(D3DTS_PROJECTION, &mProjGlobal);
	mProjNonJittered = mProjGlobal;

	// Temporal Anti-Aliasing
	if (bEnableHDR && PostProcessing)
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

void CEngine::OnRenderWorld()
{
	// Load textures if nessesary
	if (bIBL)
		if (ResourceManager && envTexture.IsEmpty())
			ResourceManager->LoadTextureCube(envTextureFileName, &envTexture);

	if (bNormalMapping)
		if (ResourceManager && normalTexture.IsEmpty())
			ResourceManager->LoadTexture2D(normalTextureFileName, &normalTexture);

	/*static Texture2D envTexture2;
	if (ResourceManager && envTexture2.IsEmpty())
		ResourceManager->LoadTexture2D("Textures\\HDR\\fireplace_2k.hdr", &envTexture2);
	pStandardFX->SetTexture("g_envTexture2", envTexture2.GetTexture());
	pSkyboxFX->SetTexture("g_envTexture2", envTexture2.GetTexture());*/

	// Image Based Lighting
	float fEnvCubemapReflectionAngle = D3DXToRadian(fEnvCubemapRotation);
	D3DXVECTOR2 vEnvCubemapRotation = D3DXVECTOR2(sinf(fEnvCubemapReflectionAngle), cosf(fEnvCubemapReflectionAngle));
	pStandardFX->SetValue("g_vEnvCubemapRotation", &vEnvCubemapRotation, sizeof(D3DXVECTOR2));
	pStandardFX->SetFloat("g_fCubemapBrightness", fCubemapBrightness);
	pStandardFX->SetBool("g_bEnvCubemapSwapYZ", bEnvCubemapSwapYZ);
	pStandardFX->SetTexture("g_envTexture", envTexture.GetTexture());
	if (SystemTextures)
		pStandardFX->SetTexture("g_preIntegratedGFTexture", SystemTextures->preIntegratedGFRT.GetTexture());

	// Shadows
	if (CascadedShadows)
	{
		pStandardFX->SetBool("g_bSoftShadows", CascadedShadows->bSoftShadows);
		pStandardFX->SetBool("g_bVisCascades", CascadedShadows->bVisCascades);
		pStandardFX->SetValue("g_vCascades", CascadedShadows->splitDepths, sizeof(CascadedShadows->splitDepths));
		pStandardFX->SetValue("g_mShadow", CascadedShadows->mShadow, sizeof(CascadedShadows->mShadow));
		pStandardFX->SetFloat("g_fSoftTransitionScale", CascadedShadows->fSoftTransitionScale);
		pStandardFX->SetFloat("g_fShadowSharpen", CascadedShadows->fShadowSharpen);
		pStandardFX->SetFloat("g_fRadius", CascadedShadows->fRadius);
		pStandardFX->SetValue("g_vShadowBufferSize", CascadedShadows->vShadowBufferSize, sizeof(CascadedShadows->vShadowBufferSize));
		pStandardFX->SetFloat("g_fShadowPartitionSize", 1.0f / NUM_CASCADES);
		pStandardFX->SetTexture("g_shadowTexture", CascadedShadows->GetTexture());
	}

	// Other
	pStandardFX->SetTexture("g_normalTexture", normalTexture.GetTexture());

	if (PostProcessing)
	{
		pStandardFX->SetTexture("g_reflectionTexture", (bEnableHDR && PostProcessing->bSSR) ? PostProcessing->ssrRT.GetTexture() : nullptr);
		pStandardFX->SetTexture("g_contactShadowsTexture", PostProcessing->contactShadowsRT.GetTexture());
		pStandardFX->SetTexture("g_aoTexture", PostProcessing->ssaoRT.GetTexture());
	}
}

void CEngine::OnRenderUI()
{
	if (!bMapLoaded)
		bMapLoaded = true;

	if (CustomUI && bCustomUserInterface)
	{
		IDirect3DStateBlock9* pStateBlock = nullptr;
		m_pDevice->CreateStateBlock(D3DSBT_ALL, &pStateBlock);

		CustomUI->Render();

		pStateBlock->Apply();
		pStateBlock->Release();
	}
}


void CEngine::OnBeginScene()
{
	// Reset values
	bPostProcessRendered = false;
	bSceneUpdated = false;
	RenderingHook::iCurrentRenderStage = ERenderStage::Unknown;

	iPointLightCount = 0;

	if (CascadedShadows)
	{
		CascadedShadows->iUnitsCount = 0;
		CascadedShadows->iChunksCount = 0;
	}

	// Set custom depth surface
	m_pDevice->SetDepthStencilSurface(depthRT.GetSurface());
	m_pDevice->Clear(0, nullptr, D3DCLEAR_ZBUFFER, 0x00000000, 1.0f, 0);

	// Set HDR render target
	if (bEnableHDR && !bDefaultRenderer && !bHDRStarted && IsGaming() && bMapLoaded)
	{
		bHDRStarted = true;

		m_pDevice->GetBackBuffer(0, 0, D3DBACKBUFFER_TYPE_MONO, &pBackBufferSurface);
		m_pDevice->SetRenderTarget(0, mainRT.GetSurface());
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
	if (bHDRStarted)
	{
		m_pDevice->SetRenderTarget(0, pBackBufferSurface);
		SAFE_RELEASE(pBackBufferSurface);
		bHDRStarted = false;
	}
}

void CEngine::OnPresent()
{
	// Update values for Post Processing
	{
		last_frame_duration = std::chrono::high_resolution_clock::now() - last_present_time;
		last_present_time += last_frame_duration;
		fTimer = std::fmod(std::chrono::duration_cast<std::chrono::nanoseconds>(last_present_time - start_time).count() * 1e-6f, 16777216.0f);
	}

	// Check is map loaded or not. TODO: find better way
	OnGameState();

	// Get FPS
	CalculateFrameRate();

	// Update FreeCamera
	if (FreeCamera)
		FreeCamera->Update(fDeltaTime);

	ExecuteFrameUpdateTriggers();

	// Render helper UI
	if (m_pDevice->BeginScene() == D3D_OK)
	{
		// Render AntTweakBar
		if (AntTweakBar)
			AntTweakBar->Render();

		// Debug Info
		if (bDebugInfo)
			RenderText();

		m_pDevice->EndScene();
	}

	// Capture back buffer
	if (bTakeScreenshot)
	{
		TakeScreenshot();
		bTakeScreenshot = false;
	}
}


HRESULT CEngine::OnDrawIndexedPrimitive(D3DPRIMITIVETYPE primitiveType, int32 baseVertexIndex, uint32 minIndex, uint32 numVertices, uint32 startIndex, uint32 primitiveCount, uint32 stride, IDirect3DTexture9* currentTexture)
{
	const ERenderStage curRenderStage = RenderingHook::GetRenderStage();

	if (bDefaultRenderer)
	{
		if (curRenderStage == ERenderStage::UI)
		{
			// Hide UI
			if (!bUserInterface)
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

			if (bSkyboxFixTwitching)
			{
				D3DXMatrixTranslation(&mWorld, vCameraPos.x, vCameraPos.y, vCameraPos.z);
			}
			else
			{
				m_pDevice->GetTransform(D3DTS_WORLD, &mWorld);
			}

			pSkyboxFX->SetMatrix("g_mTextureTransform", &mTextureTransform);
			pSkyboxFX->SetMatrix("g_mWorld", &mWorld);
			pSkyboxFX->SetMatrix("g_mWorldViewProjection", &(mWorld * mViewGlobal * mProjGlobal));
			pSkyboxFX->SetBool("g_bLinearOutput", bHDRStarted);

			// Material
			D3DMATERIAL9 material;
			m_pDevice->GetMaterial(&material);
			bool bEmissive = (material.Emissive.r != 0.0f || material.Emissive.g != 0.0f || material.Emissive.b != 0.0f || material.Emissive.a != 0.0f);
			FColor matDiffuse = bEmissive ? material.Emissive : material.Diffuse;
			if (bMaterialColorSRGB) matDiffuse.ToLinear();
			pSkyboxFX->SetValue("g_vMaterialDiffuse", &matDiffuse, sizeof(FColor));
			pSkyboxFX->SetFloat("g_fBrightness", fSkyboxLightIntensity);

			// Fog
			pSkyboxFX->SetBool("g_bFog", bSkyboxFog);
			pSkyboxFX->SetValue("g_vFogColor", bDefaultFog ? &vGlobalFogColor : &vFogColor, sizeof(D3DXVECTOR3));
			pSkyboxFX->SetBool("g_bFogSun", bFogSun);
			pSkyboxFX->SetValue("g_vFogSunColor", &vFogSunColor, sizeof(vFogSunColor));
			pSkyboxFX->SetFloat("g_fFogSunIntensity", fFogSunIntensity);

			// Skybox Shading
			bool bLit = !bEmissive && bSkyboxShading;
			pSkyboxFX->SetBool("g_bLighting", bLit);
			pSkyboxFX->SetValue("g_vLightDirection", (bDefaultLightDir || bSkyboxFog) ? &vGlobalLightDir : &vLightDir, sizeof(D3DXVECTOR3));
			if (bLit && !bSkyboxFog)
			{
				pSkyboxFX->SetValue("g_vLightDiffuse", bDefaultAmbientColor ? &vGlobalAmbientColor : &vAmbColor, sizeof(D3DXVECTOR3));
				pSkyboxFX->SetValue("g_vLightAmbient", bDefaultLightColor ? &vGlobalLightColor : &vLightColor, sizeof(D3DXVECTOR3));
			}

			// Other
			pSkyboxFX->SetValue("g_vCameraPos", vCameraPos, sizeof(vCameraPos));

			// Technique
			pSkyboxFX->SetTechnique("Standard");


			//=============== Render Object ==================
			uint32 uPasses = 0;
			pSkyboxFX->Begin(&uPasses, 0);
			pSkyboxFX->BeginPass(0);

			//m_pDevice->SetVertexDeclaration(g_pVertexDecl);
			m_pDevice->DrawIndexedPrimitive(primitiveType, baseVertexIndex, minIndex, numVertices, startIndex, primitiveCount);

			pSkyboxFX->EndPass();
			pSkyboxFX->End();
			//===============================================


			return D3D_OK;
		}
		else if (curRenderStage == ERenderStage::Terrain || curRenderStage == ERenderStage::Ubersplat)
		{
			UpdateLightAndFog();

			// Texture Filtering and Gamma Correction
			m_pDevice->SetSamplerState(0, D3DSAMP_SRGBTEXTURE, 1);
			if (bAnisoFiltering)
			{
				m_pDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_ANISOTROPIC);
				m_pDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_ANISOTROPIC);
				m_pDevice->SetSamplerState(0, D3DSAMP_MIPFILTER, D3DTEXF_ANISOTROPIC);
				m_pDevice->SetSamplerState(0, D3DSAMP_MAXANISOTROPY, iMaxAnisotropy);
			}

			// Matrices
			D3DXMATRIX mWorld;
			m_pDevice->GetTransform(D3DTS_WORLD, &mWorld);
			pStandardFX->SetMatrix("g_mWorld", &mWorld);
			pStandardFX->SetMatrix("g_mWorldViewProjection", &(mWorld * mViewGlobal * mProjGlobal));

			// Material
			DWORD bFog;
			m_pDevice->GetRenderState(D3DRS_FOGENABLE, &bFog);
			pStandardFX->SetBool("g_bTexture", bTexture);
			pStandardFX->SetBool("g_bMaterialUnshaded", bSimpleMaterial);
			pStandardFX->SetBool("g_bMaterialUnfogged", !(bFog && bEnableFog) || bSimpleMaterial);
			pStandardFX->SetBool("g_bPBS", bPBS);
			pStandardFX->SetFloat("g_fMaterialRoughness", fTerrainRoughness);
			pStandardFX->SetFloat("g_fMaterialMetallic", fTerrainMetallic);
			pStandardFX->SetFloat("g_fMaterialSpecular", fTerrainSpecular);
			pStandardFX->SetFloat("g_fMaterialTranslucent", 0.0f);

			// Other
			pStandardFX->SetBool("g_bIBL", bIBL);
			pStandardFX->SetBool("g_bShadows", CascadedShadows && CascadedShadows->IsEnabled());
			pStandardFX->SetBool("g_bNormalMapping", bNormalMapping && !normalTexture.IsEmpty());
			pStandardFX->SetBool("g_bContactShadows", bEnableHDR && PostProcessing && PostProcessing->bContactShadows && !PostProcessing->contactShadowsRT.IsEmpty());
			pStandardFX->SetBool("g_bSSAO", bEnableHDR && PostProcessing && PostProcessing->bSSAO && !PostProcessing->ssaoRT.IsEmpty());
			pStandardFX->SetBool("g_bPointLight", bPointLight && bGlobalPointLight);

			// Technique
			pStandardFX->SetTechnique("Terrain");


			//=============== Render Object =================
			uint32 uPasses = 0;
			pStandardFX->Begin(&uPasses, 0);
			pStandardFX->BeginPass(0);

			m_pDevice->DrawIndexedPrimitive(primitiveType, baseVertexIndex, minIndex, numVertices, startIndex, primitiveCount);

			pStandardFX->EndPass();
			pStandardFX->End();
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
			pStandardFX->SetMatrix("g_mWorld", &mWorld);
			pStandardFX->SetMatrix("g_mWorldViewProjection", &(mWorld * mViewGlobal * mProjGlobal));

			// Material
			DWORD bFog;
			m_pDevice->GetRenderState(D3DRS_FOGENABLE, &bFog);
			pStandardFX->SetBool("g_bTexture", true);
			pStandardFX->SetBool("g_bMaterialUnshaded", bSimpleMaterial);
			pStandardFX->SetBool("g_bMaterialUnfogged", !(bFog && bEnableFog) || bSimpleMaterial);
			pStandardFX->SetBool("g_bPBS", false);

			// Other
			pStandardFX->SetBool("g_bPointLight", false);
			pStandardFX->SetBool("g_bIBL", false);
			pStandardFX->SetBool("g_bNormalMapping", false);
			pStandardFX->SetBool("g_bContactShadows", false);
			pStandardFX->SetBool("g_bSSAO", false);
			pStandardFX->SetBool("g_bShadows", false);

			// Technique
			pStandardFX->SetTechnique("Terrain");


			//=============== Render Object ==================
			uint32 uPasses = 0;
			pStandardFX->Begin(&uPasses, 0);
			pStandardFX->BeginPass(0);

			//m_pDevice->SetVertexDeclaration(g_pVertexDecl);
			m_pDevice->DrawIndexedPrimitive(primitiveType, baseVertexIndex, minIndex, numVertices, startIndex, primitiveCount);

			pStandardFX->EndPass();
			pStandardFX->End();
			//===============================================


			return D3D_OK;
		}
		else if (curRenderStage == ERenderStage::Unit || curRenderStage == ERenderStage::Destructible || curRenderStage == ERenderStage::Decoration || curRenderStage == ERenderStage::Building || curRenderStage == ERenderStage::Indicator || curRenderStage == ERenderStage::OcclusionMask || curRenderStage == ERenderStage::Lightning || curRenderStage == ERenderStage::Weather || curRenderStage == ERenderStage::TerrainShadow || curRenderStage == ERenderStage::WaterShadow || curRenderStage == ERenderStage::Footprint || curRenderStage == ERenderStage::SelectionCircle || curRenderStage == ERenderStage::Water)
		{
			UpdateLightAndFog();

			// Texture Filtering and Gamma Correction
			m_pDevice->SetSamplerState(0, D3DSAMP_SRGBTEXTURE, 1);
			if (bAnisoFiltering)
			{
				m_pDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_ANISOTROPIC);
				m_pDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_ANISOTROPIC);
				m_pDevice->SetSamplerState(0, D3DSAMP_MIPFILTER, D3DTEXF_ANISOTROPIC);
				m_pDevice->SetSamplerState(0, D3DSAMP_MAXANISOTROPY, iMaxAnisotropy);
			}

			// Matrices
			D3DXMATRIX mWorld, mView, mTextureTransform;
			m_pDevice->GetTransform(D3DTS_TEXTURE0, &mTextureTransform);
			m_pDevice->GetTransform(D3DTS_WORLD, &mWorld);
			//if (stride == 36)
			m_pDevice->GetTransform(D3DTS_VIEW, &mView);
			pStandardFX->SetMatrix("g_mTextureTransform", &mTextureTransform);
			pStandardFX->SetMatrix("g_mWorld", &mWorld);
			pStandardFX->SetMatrix("g_mWorldViewProjection", &(mWorld * mView * mProjGlobal));

			// Material
			D3DMATERIAL9 material;
			DWORD bFog, bLighting;
			m_pDevice->GetMaterial(&material);
			m_pDevice->GetRenderState(D3DRS_FOGENABLE, &bFog);
			m_pDevice->GetRenderState(D3DRS_LIGHTING, &bLighting);
			bool bEmissive = (material.Emissive.r != 0.0f || material.Emissive.g != 0.0f || material.Emissive.b != 0.0f || material.Emissive.a != 0.0f);
			bool bVertexColor = (stride == 36) && bMaterialVertexColor;
			bool bUnshaded = (!bLighting || bEmissive) && bUnshadedMaterials;
			bool bUnfogged = (!bFog && bUnfoggedMaterials) || !bEnableFog;
			FColor matDiffuse = bEmissive ? material.Emissive : material.Diffuse;
			if (bMaterialColor && bMaterialColorSRGB)
				matDiffuse.ToLinear();
			pStandardFX->SetBool("g_bTexture", bTexture);
			pStandardFX->SetBool("g_bVertexColor", bVertexColor);
			pStandardFX->SetBool("g_bVertexColorSRGB", bVertexColorSRGB);
			pStandardFX->SetBool("g_bMaterialColor", bMaterialColor);
			pStandardFX->SetBool("g_bMaterialUnshaded", bUnshaded || bSimpleMaterial);
			pStandardFX->SetBool("g_bMaterialUnfogged", bUnfogged || bSimpleMaterial);
			if (curRenderStage == ERenderStage::Lightning)
				pStandardFX->SetValue("g_vMaterialEmissive", &D3DXVECTOR4(0.0f, 0.0f, 0.0f, 4.0f), sizeof(D3DXVECTOR4));
			else
				pStandardFX->SetValue("g_vMaterialEmissive", &D3DXVECTOR4(0.0f, 0.0f, 0.0f, 1.0f), sizeof(D3DXVECTOR4));
			pStandardFX->SetValue("g_vMaterialDiffuse", &matDiffuse, sizeof(FColor));
			pStandardFX->SetBool("g_bPBS", bPBS);
			pStandardFX->SetFloat("g_fMaterialRoughness", fMaterialRoughness);
			pStandardFX->SetFloat("g_fMaterialMetallic", fMaterialMetallic);
			pStandardFX->SetFloat("g_fMaterialSpecular", fMaterialSpecular);
			pStandardFX->SetFloat("g_fMaterialTranslucent", fMaterialTranslucent);

			// Other
			pStandardFX->SetBool("g_bIBL", bIBL);
			pStandardFX->SetBool("g_bShadows", CascadedShadows && CascadedShadows->IsEnabled());
			pStandardFX->SetBool("g_bNormalMapping", false);
			pStandardFX->SetBool("g_bContactShadows", bEnableHDR && PostProcessing && PostProcessing->bContactShadows && !PostProcessing->contactShadowsRT.IsEmpty());
			pStandardFX->SetBool("g_bSSAO", bEnableHDR && PostProcessing && PostProcessing->bSSAO && !PostProcessing->ssaoRT.IsEmpty());
			pStandardFX->SetBool("g_bPointLight", bPointLight && bGlobalPointLight);

			// Technique
			pStandardFX->SetTechnique("Standard");


			//=============== Render Object ==================
			uint32 uPasses = 0;
			pStandardFX->Begin(&uPasses, 0);
			pStandardFX->BeginPass(0);

			//m_pDevice->SetVertexDeclaration(g_pVertexDecl);
			m_pDevice->DrawIndexedPrimitive(primitiveType, baseVertexIndex, minIndex, numVertices, startIndex, primitiveCount);

			pStandardFX->EndPass();
			pStandardFX->End();
			//===============================================


			return D3D_OK;
		}
		else if (curRenderStage == ERenderStage::UI || curRenderStage == ERenderStage::FloatingText || curRenderStage == ERenderStage::SelectionBox)
		{
			// Texture Filtering and Gamma Correction
			m_pDevice->SetSamplerState(0, D3DSAMP_SRGBTEXTURE, 0);

			// Render Post Process
			if (!bPostProcessRendered)
			{
				if (PostProcessing && bHDRStarted)
				{
					IDirect3DStateBlock9* pStateBlock = nullptr;
					m_pDevice->CreateStateBlock(D3DSBT_ALL, &pStateBlock);

					PostProcessing->Render();

					SAFE_RELEASE(pBackBufferSurface);
					bHDRStarted = false;

					pStateBlock->Apply();
					pStateBlock->Release();
				}

				bPostProcessRendered = true;
			}

			// Hide Standard UI
			if (curRenderStage == ERenderStage::UI && !bUserInterface)
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
		bGamePaused = !bGamePaused;
		JassNatives::PauseGame(bGamePaused);
	}
	else if (getKey == hotkey_TakeScreenshot)
	{
		bTakeScreenshot = true;
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

	output << std::endl << fFPS << " FPS" << std::endl;
	std::streamsize ss = output.precision();
	output << std::fixed << std::setprecision(0) << fDeltaTime * 1000.0f << std::defaultfloat << std::setprecision(ss) << " ms" << std::endl;
	output << memoryUsed << " MB" << std::endl << std::endl;

	output << "MouseX: " << mX << "  (" << mX * vBufferSize.z << ")" << std::endl;
	output << "MouseY: " << mY << "  (" << mY * vBufferSize.w << ")" << std::endl;

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

	pFont->DrawTextA(0, output.str().c_str(), -1, nullptr, DT_EXPANDTABS | DT_LEFT, 0xEEEEEEFF);
}