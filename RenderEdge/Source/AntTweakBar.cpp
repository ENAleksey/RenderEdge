#include "AntTweakBar.h"

#include "Engine.h"
#include "RenderingHook.h"
#include "PostProcessing.h"
#include "CascadedShadows.h"
#include "Camera.h"
#include "GameUI.h"
#include "JassNatives.h"
#include "Log.h"


CAntTweakBar* AntTweakBar = nullptr;

CAntTweakBar::CAntTweakBar(IDirect3DDevice9* pDevice)
{
	LOG(DEBUG) << __func__;

	m_pDevice = pDevice;
	bActive = true;

	Init();
}

CAntTweakBar::~CAntTweakBar()
{
	LOG(DEBUG) << __func__;
	TwTerminate();
}


void CAntTweakBar::OnResetDevice()
{
	TwWindowSize(Engine->vBufferSize.x, Engine->vBufferSize.y);
}

void CAntTweakBar::OnLostDevice()
{
	TwWindowSize(0, 0);
}

bool CAntTweakBar::OnGetMessage(HWND ah_Wnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	if (!bActive)
		return false;

	return TwEventWin(ah_Wnd, uMsg, wParam, lParam);
}

void CAntTweakBar::Render()
{
	if (!bActive)
		return;

	TwDraw();
}

void CAntTweakBar::SetActive(bool value)
{
	bActive = value;

	if (bActive)
	{
	}
}

bool CAntTweakBar::GetActive()
{
	return bActive;
}


void TW_CALL SetPauseGame_cb(const void *value, void *clientData)
{
	if (!IsGaming() || IsInGameMenu())
		return;

	Engine->bGamePaused = *(const bool*)value;
	JassNatives::PauseGame(Engine->bGamePaused);
}
void TW_CALL GetPauseGame_cb(void *value, void *clientData)
{
	*(bool*)value = IsGamePaused();
}

void TW_CALL SetFreeCamera_cb(const void *value, void *clientData)
{
	if (!FreeCamera || !IsGaming())
		return;

	Engine->bFreeCamera = *(const bool*)value;
	Engine->UpdateFreeCamera();
}
void TW_CALL GetFreeCamera_cb(void *value, void *clientData)
{
	*(bool*)value = Engine->bFreeCamera;
}

void TW_CALL SetVsync_cb(const void *value, void *clientData)
{
	const bool bValue = *(const bool*)value;

	if (Engine->bVsyncEnabled != bValue)
	{
		Engine->bVsyncEnabled = bValue;
		ForceResetDevice8();
	}
}
void TW_CALL GetVsync_cb(void *value, void *clientData)
{
	*(bool*)value = Engine->bVsyncEnabled;
}

void TW_CALL SetScreenMode_cb(const void *value, void *clientData)
{
	const bool bValue = *(const bool*)value;

	if (Engine->bWindowed != bValue)
	{
		Engine->bWindowed = bValue;
		Input::CenterMouse();
		Engine->UpdateScreenMode();
		ForceResetDevice8();
	}
}
void TW_CALL GetScreenMode_cb(void *value, void *clientData)
{
	*(bool*)value = Engine->bWindowed;
}

void TW_CALL SetUserInterface_cb(const void *value, void *clientData)
{
	Engine->bUserInterface = *(const bool*)value;
	Engine->UpdateUserInterface();
}
void TW_CALL GetUserInterface_cb(void *value, void *clientData)
{
	*(bool*)value = Engine->bUserInterface;
}

void TW_CALL SetMaskedObject_cb(const void *value, void *clientData)
{
	if (!IsGaming())
		return;

	Engine->bMaskedObjects = *(const bool*)value;
	Engine->UpdateMaskedObjectColor();
}
void TW_CALL GetMaskedObject_cb(void *value, void *clientData)
{
	*(bool*)value = Engine->bMaskedObjects;
}

void TW_CALL SetBuildingsShadows_cb(const void *value, void *clientData)
{
	if (!IsGaming())
		return;

	Engine->bBuildingsShadows = *(const bool*)value;
	Engine->UpdateBuildingsShadowsColor();
}
void TW_CALL GetBuildingsShadows_cb(void *value, void *clientData)
{
	*(bool*)value = Engine->bBuildingsShadows;
}

void TW_CALL SetMapBounds_cb(const void *value, void *clientData)
{
	if (!IsGaming())
		return;

	Engine->bMapBounds = *(const bool*)value;
	Engine->UpdateMapBoundsColor();
}
void TW_CALL GetMapBounds_cb(void *value, void *clientData)
{
	*(bool*)value = Engine->bMapBounds;
}

void TW_CALL SetLutFloat_cb(const void *value, void *clientData)
{
	*static_cast<float*>(clientData) = *static_cast<const float*>(value);

	if (PostProcessing)
		PostProcessing->bUpdateLUT = true;
}
void TW_CALL SetLutBool_cb(const void *value, void *clientData)
{
	*static_cast<bool*>(clientData) = *static_cast<const bool*>(value);

	if (PostProcessing)
		PostProcessing->bUpdateLUT = true;
}
void TW_CALL SetLutColor_cb(const void *value, void *clientData)
{
	*static_cast<D3DXVECTOR3*>(clientData) = *static_cast<const D3DXVECTOR3*>(value);

	if (PostProcessing)
		PostProcessing->bUpdateLUT = true;
}
void TW_CALL GetLutFloat_cb(void *value, void *clientData)
{
	*static_cast<float*>(value) = *static_cast<const float*>(clientData);
}
void TW_CALL GetLutBool_cb(void *value, void *clientData)
{
	*static_cast<bool*>(value) = *static_cast<const bool*>(clientData);
}
void TW_CALL GetLutColor_cb(void *value, void *clientData)
{
	*static_cast<D3DXVECTOR3*>(value) = *static_cast<const D3DXVECTOR3*>(clientData);
}

void TW_CALL CheckAllRenderStages_cb(void *clientData)
{
	static bool bRenderStagesChecked = true;

	bRenderStagesChecked = !bRenderStagesChecked;

	RenderingHook::bRenderSkybox = bRenderStagesChecked;
	RenderingHook::bRenderTerrain = bRenderStagesChecked;
	RenderingHook::bRenderFogOfWar = bRenderStagesChecked;
	RenderingHook::bRenderTerrainShadow = bRenderStagesChecked;
	RenderingHook::bRenderWaterShadow = bRenderStagesChecked;
	RenderingHook::bRenderWeather = bRenderStagesChecked;
	RenderingHook::bRenderSelectionCircle = bRenderStagesChecked;
	RenderingHook::bRenderFootprint = bRenderStagesChecked;
	RenderingHook::bRenderDecoration = bRenderStagesChecked;
	RenderingHook::bRenderUnit = bRenderStagesChecked;
	RenderingHook::bRenderDestructible = bRenderStagesChecked;
	RenderingHook::bRenderWater = bRenderStagesChecked;
	RenderingHook::bRenderSelectionBox = bRenderStagesChecked;
	RenderingHook::bRenderBuilding = bRenderStagesChecked;
	RenderingHook::bRenderUbersplat = bRenderStagesChecked;
	RenderingHook::bRenderUnknown1 = bRenderStagesChecked;
	RenderingHook::bRenderIndicator = bRenderStagesChecked;
	RenderingHook::bRenderUnknown2 = bRenderStagesChecked;
	RenderingHook::bRenderUnknown3 = bRenderStagesChecked;
	RenderingHook::bRenderOcclusionMask = bRenderStagesChecked;
	RenderingHook::bRenderLightning = bRenderStagesChecked;
	RenderingHook::bRenderFloatingText = bRenderStagesChecked;
	RenderingHook::bRenderCineFilter = bRenderStagesChecked;
}

void TW_CALL ReloadShaders_cb(void *clientData)
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

	TwWindowSize(Engine->vBufferSize.x, Engine->vBufferSize.y);

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
	TwAddVarRW(bar, "bDefaultRenderer", TW_TYPE_BOOLCPP, &Engine->bDefaultRenderer, " group='Engine' label='Default Renderer' ");
	TwAddVarCB(bar, "bGamePaused", TW_TYPE_BOOLCPP, SetPauseGame_cb, GetPauseGame_cb, nullptr, " group='Engine' label='Pause Game' ");
	TwAddVarRW(bar, "bDebugInfo", TW_TYPE_BOOLCPP, &Engine->bDebugInfo, " group='Engine' label='Debug Info' ");
	TwAddSeparator(bar, "", " group='Engine' ");
	TwAddVarCB(bar, "bWindowed", TW_TYPE_BOOLCPP, SetScreenMode_cb, GetScreenMode_cb, nullptr, " group='Engine' readonly=true label='Windowed' ");
	TwAddVarCB(bar, "bVsyncEnabled", TW_TYPE_BOOLCPP, SetVsync_cb, GetVsync_cb, nullptr, " group='Engine' label='V-Sync' ");
	TwAddSeparator(bar, "", " group='Engine' ");
	TwAddButton(bar, "ReloadShaders", ReloadShaders_cb, nullptr, " group='Engine' label='Reload Shaders' ");
	TwDefine(" RenderEdge/'Engine' opened=true");

	// Camera
	// ===========================================================
	TwAddVarCB(bar, "bFreeCamera", TW_TYPE_BOOLCPP, SetFreeCamera_cb, GetFreeCamera_cb, nullptr, " group='Camera' label='Free Camera' ");
	TwAddVarRW(bar, "bDefaultProjectionMatrix", TW_TYPE_BOOLCPP, &Engine->bDefaultProjectionMatrix, " group='Camera' label='Constant Vertical FoV' ");
	if (FreeCamera)
		TwAddVarRW(bar, "fCameraSpeed", TW_TYPE_FLOAT, &FreeCamera->m_fSpeed, " group='Camera' min=0.01 step=0.01 label='Free Camera Speed' ");
	TwAddVarRW(bar, "fCameraFoV", TW_TYPE_FLOAT, &Engine->fCameraFoV, " group='Camera' min=5 max=220 step=1 label='FoV' ");
	TwAddVarRW(bar, "fCameraNearZ", TW_TYPE_FLOAT, &Engine->fCameraNearZ, " group='Camera' min=1 step=1 label='NearZ' ");
	TwAddVarRW(bar, "fCameraFarZ", TW_TYPE_FLOAT, &Engine->fCameraFarZ, " group='Camera' min=1 step=1 label='FarZ' ");
	TwAddVarRW(bar, "fCameraPosition", pointType, &Engine->vCameraPos, " group='Camera' readonly=true label='Position' ");
	TwDefine(" RenderEdge/'Camera' opened=false");

	// Render Stages
	// ===========================================================
	TwAddVarCB(bar, "bUserInterface", TW_TYPE_BOOLCPP, SetUserInterface_cb, GetUserInterface_cb, nullptr, " group='Render Stages' label='User Interface' ");
	TwAddVarRW(bar, "bCustomUserInterface", TW_TYPE_BOOLCPP, &Engine->bCustomUserInterface, " group='Render Stages' label='Custom User Interface' ");
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

	// Sky Light
	// ===========================================================
	TwAddVarRW(bar, "bUseDefLightAmbient", TW_TYPE_BOOLCPP, &Engine->bDefaultAmbientColor, " group='Sky Light' label='Default Color' ");
	TwAddVarRW(bar, "bSRGBAmbientLightColor", TW_TYPE_BOOLCPP, &Engine->bAmbientColorSRGB, " group='Sky Light' label='sRGB Color' ");
	TwAddVarRW(bar, "vAmbColor", TW_TYPE_COLOR3F, &Engine->vAmbColor, " group='Sky Light' label='Ambient Color' ");
	TwAddSeparator(bar, "", " group='Sky Light' ");
	TwAddVarRW(bar, "bEnableSkyLight", TW_TYPE_BOOLCPP, &Engine->bSkyLight, " group='Sky Light' label='Enabled' ");
	TwAddVarRW(bar, "fSkyLightIntensity", TW_TYPE_FLOAT, &Engine->fSkyLightIntensity, " group='Sky Light' min=0 step=0.01 label='Intensity' ");
	TwAddVarRW(bar, "vSkyColor", TW_TYPE_COLOR3F, &Engine->vSkyColor, " group='Sky Light' label='Sky' ");
	TwAddVarRW(bar, "vIndColor", TW_TYPE_COLOR3F, &Engine->vIndColor, " group='Sky Light' label='Indirect' ");
	TwDefine(" RenderEdge/'Sky Light' opened=false");

	// Directional Light
	// ===========================================================
	TwAddVarRW(bar, "bUseDefLightDir", TW_TYPE_BOOLCPP, &Engine->bDefaultLightDir, " group='Directional Light' label='Default Direction' ");
	TwAddVarRW(bar, "bUseDefLightColor", TW_TYPE_BOOLCPP, &Engine->bDefaultLightColor, " group='Directional Light' label='Default Color' ");
	TwAddVarRW(bar, "bSRGBLightColor", TW_TYPE_BOOLCPP, &Engine->bLightColorSRGB, " group='Directional Light' label='sRGB Color' ");
	TwAddSeparator(bar, "", " group='Directional Light' ");
	TwAddVarRW(bar, "fLightIntensity", TW_TYPE_FLOAT, &Engine->fLightIntensity, " group='Directional Light' min=0 step=0.01 label='Intensity' ");
	TwAddVarRW(bar, "vLightColor", TW_TYPE_COLOR3F, &Engine->vLightColor, " group='Directional Light' label='Color' ");
	TwAddVarRW(bar, "vLightDir", TW_TYPE_DIR3F, &Engine->vLightDir, " group='Directional Light' opened=false axisz=z showval=true label='Direction' ");
	TwAddVarRW(bar, "fLightTemperature", TW_TYPE_FLOAT, &Engine->fLightTemperature, " group='Directional Light' min=1700 max=12000 step=1 label='Temperature' ");
	TwAddVarRW(bar, "bUseTemperature", TW_TYPE_BOOLCPP, &Engine->bUseTemperature, " group='Directional Light' label='Use Temperature' ");
	TwDefine(" RenderEdge/'Directional Light' opened=false");

	// Point Light
	// ===========================================================
	TwAddVarRW(bar, "bEnablePointLight", TW_TYPE_BOOLCPP, &Engine->bPointLight, " group='Point Light' label='Enabled' ");
	TwAddVarRW(bar, "bSRGBPointLightColor", TW_TYPE_BOOLCPP, &Engine->bPointLightColorSRGB, " group='Point Light' label='sRGB Color' ");
	TwAddVarRW(bar, "DefaultPointLightIntensityUnits", lightUnitsListType, &Engine->DefaultPointLightIntensityUnits, " group='Point Light' label='Intensity Units' ");
	TwAddVarRW(bar, "fDefaultPointLightIntensity", TW_TYPE_FLOAT, &Engine->fDefaultPointLightIntensity, " group='Point Light' min=0 step=0.01 label='Intensity Multiplier' ");
	TwAddVarRW(bar, "fDefaultPointLightRadius", TW_TYPE_FLOAT, &Engine->fDefaultPointLightRadius, " group='Point Light' min=0 max=10000.0 step=1 label='Radius' ");
	TwDefine(" RenderEdge/'Point Light' opened=false");

	// Image Based Lighting
	// ===========================================================
	TwAddVarRW(bar, "bEnableIBL", TW_TYPE_BOOLCPP, &Engine->bIBL, " group='Image Based Lighting' label='Enabled' ");
	TwAddVarRW(bar, "fCubemapBrightness", TW_TYPE_FLOAT, &Engine->fCubemapBrightness, " group='Image Based Lighting' min=0 max=5 step=0.01 label='Cubemap Brightness' ");
	TwAddVarRW(bar, "fEnvCubemapRotation", TW_TYPE_FLOAT, &Engine->fEnvCubemapRotation, " group='Image Based Lighting' min=0 max=360 step=1.0 label='Source Cubemap Angle' ");
	TwAddVarRW(bar, "bEnvCubemapSwapYZ", TW_TYPE_BOOLCPP, &Engine->bEnvCubemapSwapYZ, " group='Image Based Lighting' label='Swap YZ' ");
	TwDefine(" RenderEdge/'Image Based Lighting' opened=false");

	TwAddSeparator(bar, "", "");

	// Terrain
	// ===========================================================
	if (CascadedShadows)
	{
		TwAddVarRW(bar, "bTerrainShadows", TW_TYPE_BOOLCPP, &CascadedShadows->bTerrainShadows, " group='Terrain' label='Cast Shadows' ");
		TwAddSeparator(bar, "", " group='Terrain' ");
	}
	TwAddVarRW(bar, "bNormalMapping", TW_TYPE_BOOLCPP, &Engine->bNormalMapping, " group='Terrain' label='Normal Mapping' ");
	TwAddVarRW(bar, "fTerrainRoughness", TW_TYPE_FLOAT, &Engine->fTerrainRoughness, " group='Terrain' min=0 max=1 step=0.01 label='Roughness' ");
	TwAddVarRW(bar, "fTerrainMetallic", TW_TYPE_FLOAT, &Engine->fTerrainMetallic, " group='Terrain' min=0 max=1 step=0.01 label='Metallic' ");
	TwAddVarRW(bar, "fTerrainSpecular", TW_TYPE_FLOAT, &Engine->fTerrainSpecular, " group='Terrain' min=0 max=1 step=0.01 label='Specular' ");
	TwDefine(" RenderEdge/'Terrain' opened=false");

	// Objects
	// ===========================================================
	if (CascadedShadows)
	{
		TwAddVarRW(bar, "bObjectsShadows", TW_TYPE_BOOLCPP, &CascadedShadows->bObjectsShadows, " group='Objects' label='Cast Shadows' ");
		TwAddSeparator(bar, "", " group='Objects' ");
	}
	TwAddVarRW(bar, "fMaterialRoughness", TW_TYPE_FLOAT, &Engine->fMaterialRoughness, " group='Objects' min=0 max=1 step=0.01 label='Roughness' ");
	TwAddVarRW(bar, "fMaterialMetallic", TW_TYPE_FLOAT, &Engine->fMaterialMetallic, " group='Objects' min=0 max=1 step=0.01 label='Metallic' ");
	TwAddVarRW(bar, "fMaterialSpecular", TW_TYPE_FLOAT, &Engine->fMaterialSpecular, " group='Objects' min=0 max=1 step=0.01 label='Specular' ");
	TwAddVarRW(bar, "fMaterialTranslucent", TW_TYPE_FLOAT, &Engine->fMaterialTranslucent, " group='Objects' min=0 max=1 step=0.01 label='Translucent' ");
	TwAddSeparator(bar, "", " group='Objects' ");
	//TwAddVarRW(bar, "bNormalMapping", TW_TYPE_BOOLCPP, &g_bNormalMapping, " group='Objects' label='Normal Mapping' ");
	TwAddVarRW(bar, "bMaterialColor", TW_TYPE_BOOLCPP, &Engine->bMaterialColor, " group='Objects' label='Material Color' ");
	TwAddVarRW(bar, "bMaterialVertexColor", TW_TYPE_BOOLCPP, &Engine->bMaterialVertexColor, " group='Objects' label='Vertex Color' ");
	TwAddVarRW(bar, "bUnshadedMaterials", TW_TYPE_BOOLCPP, &Engine->bUnshadedMaterials, " group='Objects' label='Unshaded Materials' ");
	TwAddVarRW(bar, "bUnfoggedMaterials", TW_TYPE_BOOLCPP, &Engine->bUnfoggedMaterials, " group='Objects' label='Unfogged Materials' ");
	TwAddSeparator(bar, "", " group='Objects' ");
	TwAddVarRW(bar, "bSRGBMaterialColor", TW_TYPE_BOOLCPP, &Engine->bMaterialColorSRGB, " group='Objects' label='sRGB Material Color' ");
	TwAddVarRW(bar, "bSRGBVertexColor", TW_TYPE_BOOLCPP, &Engine->bVertexColorSRGB, " group='Objects' label='sRGB Vertex Color' ");
	TwDefine(" RenderEdge/'Objects' opened=false");

	// Skybox
	// ===========================================================
	TwAddVarRW(bar, "bSkyboxLighting", TW_TYPE_BOOLCPP, &Engine->bSkyboxShading, " group='Skybox' label='Shading' ");
	TwAddVarRW(bar, "bSkyboxFog", TW_TYPE_BOOLCPP, &Engine->bSkyboxFog, " group='Skybox' label='Use Fog Color' ");
	TwAddVarRW(bar, "bFixSkyboxTwitching", TW_TYPE_BOOLCPP, &Engine->bSkyboxFixTwitching, " group='Skybox' label='Fix Twitching' ");
	TwAddVarRW(bar, "fSkyboxLightIntensity", TW_TYPE_FLOAT, &Engine->fSkyboxLightIntensity, " group='Skybox' min=0 step=0.01 label='Brightness' ");
	TwDefine(" RenderEdge/'Skybox' opened=false");

	// Fog of War
	// ===========================================================
	TwAddVarCB(bar, "bBuildingsShadows", TW_TYPE_BOOLCPP, SetBuildingsShadows_cb, GetBuildingsShadows_cb, nullptr, " group='Fog of War' label='Buildings Shadows' ");
	TwAddVarCB(bar, "bMaskedObjects", TW_TYPE_BOOLCPP, SetMaskedObject_cb, GetMaskedObject_cb, nullptr, " group='Fog of War' label='Masked Objects' ");
	TwAddVarCB(bar, "bMapBounds", TW_TYPE_BOOLCPP, SetMapBounds_cb, GetMapBounds_cb, nullptr, " group='Fog of War' label='Map Bounds' ");
	TwDefine(" RenderEdge/'Fog of War' opened=false");

	TwAddSeparator(bar, "", "");

	// Material
	// ===========================================================
	TwAddVarRW(bar, "bEnablePBS", TW_TYPE_BOOLCPP, &Engine->bPBS, " group='Material' label='Physically Based Shading' ");
	TwAddVarRW(bar, "bSimpleMaterial", TW_TYPE_BOOLCPP, &Engine->bSimpleMaterial, " group='Material' label='Simple Material' ");
	TwAddVarRW(bar, "bEnableTextures", TW_TYPE_BOOLCPP, &Engine->bTexture, " group='Material' label='Textures' ");
	TwAddVarRW(bar, "bAnisoFiltering", TW_TYPE_BOOLCPP, &Engine->bAnisoFiltering, " group='Material' label='Anisotropic Filtering' ");
	TwAddVarRW(bar, "iMaxAnisotropy", TW_TYPE_UINT16, &Engine->iMaxAnisotropy, " group='Material' min=1 max=16 label='Anisotropy Level' ");
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
	TwAddVarRW(bar, "bEnableFog", TW_TYPE_BOOLCPP, &Engine->bEnableFog, " group='Fog' label='Enabled' ");
	TwAddVarRW(bar, "bDefaultFog", TW_TYPE_BOOLCPP, &Engine->bDefaultFog, " group='Fog' label='Default Fog' ");
	TwAddVarRW(bar, "bSRGBFogColor", TW_TYPE_BOOLCPP, &Engine->bFogColorSRGB, " group='Fog' label='sRGB Color' ");
	TwAddSeparator(bar, "", " group='Fog' ");
	TwAddVarRW(bar, "iFogTech", fogTechListType, &Engine->iFogTech, " group='Fog' label='Technique' ");
	TwAddVarRW(bar, "vFogColor", TW_TYPE_COLOR3F, &Engine->vFogColor, " group='Fog' label='Color' ");
	TwAddVarRW(bar, "fFogStart", TW_TYPE_FLOAT, &Engine->fFogStart, " group='Fog' min=0 step=1.0 precision=2 label='Start Distance' ");
	TwAddVarRW(bar, "fFogEnd", TW_TYPE_FLOAT, &Engine->fFogEnd, " group='Fog' min=0 step=1.0 precision=2 label='End Distance' ");
	TwAddVarRW(bar, "fFogDensity", TW_TYPE_FLOAT, &Engine->fFogDensity, " group='Fog' min=0.0001 max=10 step=0.01 precision=4 label='Density' ");
	TwAddVarRW(bar, "fFogHeight", TW_TYPE_FLOAT, &Engine->fFogHeight, " group='Fog' step=1.0 precision=2 label='Height' ");
	TwAddVarRW(bar, "fFogHeightFalloff", TW_TYPE_FLOAT, &Engine->fFogHeightFalloff, " group='Fog' min=0.001 max=10 step=0.02 precision=4 label='Height Falloff' ");
	TwAddVarRW(bar, "fFogCutoffDistance", TW_TYPE_FLOAT, &Engine->fFogCutoffDistance, " group='Fog' min=0 step=0.1 label='Cutoff Distance' ");
	TwAddVarRW(bar, "fFogMaxOpacity", TW_TYPE_FLOAT, &Engine->fFogMaxOpacity, " group='Fog' min=0 max=1 step=0.001 precision=4 label='Max Opacity' ");
	TwAddSeparator(bar, "", " group='Fog' ");
	TwAddVarRW(bar, "bFogSun", TW_TYPE_BOOLCPP, &Engine->bFogSun, " group='Fog' label='Sun' ");
	TwAddVarRW(bar, "vFogSunColor", TW_TYPE_COLOR3F, &Engine->vFogSunColor, " group='Fog' label='Sun Color' ");
	TwAddVarRW(bar, "fFogSunIntensity", TW_TYPE_FLOAT, &Engine->fFogSunIntensity, " group='Fog' min=2 max=64 step=0.1 label='Sun Intensity' ");
	TwAddVarRW(bar, "fFogSunStartDistance", TW_TYPE_FLOAT, &Engine->fFogSunStartDistance, " group='Fog' min=0 step=0.1 label='Sun Start Distance' ");
	TwDefine(" RenderEdge/'Fog' opened=false");

	TwAddSeparator(bar, "", "");

	// Post Effect
	// ===========================================================
	if (PostProcessing)
	{
		TwAddVarRW(bar, "bEnableHDR", TW_TYPE_BOOLCPP, &Engine->bEnableHDR, " group='Post Effect' label='Enabled' ");
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
	TwAddVarRW(bar, "fDebugValue", TW_TYPE_FLOAT, &Engine->fDebugValue, " group='Debug View' step=0.01 precision=4 label='Debug Value' ");
	TwDefine(" RenderEdge/'Debug View' opened=false");
}
