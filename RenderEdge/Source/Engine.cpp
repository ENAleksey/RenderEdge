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


const std::string RenderEdgeVersion = "RenderEdge v0.3.0dev";
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



void TW_CALL CAntTweakBar::SetPauseGame_cb(const void *value, void *clientData)
{
	if (!IsGaming() || IsInGameMenu())
		return;

	Engine->bGamePaused = *(const bool*)value;
	JassNatives::PauseGame(Engine->bGamePaused);
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

	bool bUserControl = !Engine->bFreeCamera;
	if (bUserControl != pGameUI->isUserInputEnabled)
		JassNatives::EnableUserControl(bUserControl);

	if (FreeCamera)
		FreeCamera->SetActive(Engine->bFreeCamera);
}
void TW_CALL CAntTweakBar::SetFreeCamera_cb(const void *value, void *clientData)
{
	if (!FreeCamera || !IsGaming())
		return;

	Engine->bFreeCamera = *(const bool*)value;

	UpdateFreeCamera();
}
void TW_CALL CAntTweakBar::GetFreeCamera_cb(void *value, void *clientData)
{
	*(bool*)value = Engine->bFreeCamera;
}

void TW_CALL CAntTweakBar::SetVsync_cb(const void *value, void *clientData)
{
	const bool bValue = *(const bool*)value;

	if (Engine->bVsyncEnabled != bValue)
	{
		Engine->bVsyncEnabled = bValue;
		ForceResetDevice8();
	}
}
void TW_CALL CAntTweakBar::GetVsync_cb(void *value, void *clientData)
{
	*(bool*)value = Engine->bVsyncEnabled;
}

void TW_CALL CAntTweakBar::SetScreenMode_cb(const void *value, void *clientData)
{
	const bool bValue = *(const bool*)value;

	if (Engine->bWindowed != bValue)
	{
		Engine->bWindowed = bValue;
		Input::CenterMouse();
		SetScreenMode(Engine->bWindowed);
		ForceResetDevice8();
	}
}
void TW_CALL CAntTweakBar::GetScreenMode_cb(void *value, void *clientData)
{
	*(bool*)value = Engine->bWindowed;
}

void UpdateUserInterface()
{
	CGameUI* pGameUI = GetGameUI(0, 0);
	if (!pGameUI)
		return;

	uint32 pWorldFrameWar3 = pGameUI->WorldFrameWar3 + 180;
	uint32 pRootFrame = (uint32)pGameUI + 180;

	if (Engine->bUserInterface)
	{
		SetFramePoint(pWorldFrameWar3, EFramePoint::TopRight, pRootFrame, EFramePoint::TopRight, 0.0f, Engine->vBlackBorders.x);
		SetFramePoint(pWorldFrameWar3, EFramePoint::BottomLeft, pRootFrame, EFramePoint::BottomLeft, 0.0f, Engine->vBlackBorders.y);
	}
	else
	{
		Engine->vBlackBorders.x = GetFramePointY(pWorldFrameWar3, EFramePoint::TopRight);
		Engine->vBlackBorders.y = GetFramePointY(pWorldFrameWar3, EFramePoint::BottomLeft);

		SetFramePoint(pWorldFrameWar3, EFramePoint::TopRight, pRootFrame, EFramePoint::TopRight, 0.0f, 0.0f);
		SetFramePoint(pWorldFrameWar3, EFramePoint::BottomLeft, pRootFrame, EFramePoint::BottomLeft, 0.0f, 0.0f);
	}
}
void TW_CALL CAntTweakBar::SetUserInterface_cb(const void *value, void *clientData)
{
	Engine->bUserInterface = *(const bool*)value;

	UpdateUserInterface();
}
void TW_CALL CAntTweakBar::GetUserInterface_cb(void *value, void *clientData)
{
	*(bool*)value = Engine->bUserInterface;
}

void UpdateMaskedObject()
{
	if (Engine->bMaskedObjects)
		ApplyFogOfWarEx(2, 0xFFFFFFFF, Engine->iFoggedObjectColor, Engine->iMaskedObjectColor);
	else
		ApplyFogOfWarEx(2, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF);
}
void TW_CALL CAntTweakBar::SetMaskedObject_cb(const void *value, void *clientData)
{
	if (!IsGaming())
		return;

	Engine->bMaskedObjects = *(const bool*)value;

	UpdateMaskedObject();
}
void TW_CALL CAntTweakBar::GetMaskedObject_cb(void *value, void *clientData)
{
	*(bool*)value = Engine->bMaskedObjects;
}

void UpdateBuildingsShadows()
{
	if (Engine->bBuildingsShadows)
		ApplyFogOfWarEx(0, 0x00000000, Engine->iFoggedTerrainColor, Engine->iMaskedTerrainColor);
	else
		ApplyFogOfWarEx(0, 0x00000000, 0x00000000, Engine->iMaskedTerrainColor);
}
void TW_CALL CAntTweakBar::SetBuildingsShadows_cb(const void *value, void *clientData)
{
	if (!IsGaming())
		return;

	Engine->bBuildingsShadows = *(const bool*)value;

	UpdateBuildingsShadows();
}
void TW_CALL CAntTweakBar::GetBuildingsShadows_cb(void *value, void *clientData)
{
	*(bool*)value = Engine->bBuildingsShadows;
}

void UpdateMapBounds()
{
	if (Engine->bMapBounds)
	{
		ApplyFogOfWarEx(1, Engine->iBoundaryTerrainColor, Engine->iFoggedBoundaryTerrainColor, Engine->iMaskedTerrainColor);
		ApplyFogOfWarEx(3, Engine->iBoundaryObjectColor, Engine->iFoggedBoundaryObjectColor, Engine->iMaskedObjectColor);
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

	Engine->bMapBounds = *(const bool*)value;

	UpdateMapBounds();
}
void TW_CALL CAntTweakBar::GetMapBounds_cb(void *value, void *clientData)
{
	*(bool*)value = Engine->bMapBounds;
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

void TW_CALL CAntTweakBar::CheckAllRenderStages_cb(void *clientData)
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



CEngine* Engine = nullptr;

CEngine::CEngine(IDirect3DDevice9* pDevice)
{
	Engine = this; // WTF?

	LOG(DEBUG) << "========= On Create Engine ============";
	LOG(INFO) << RenderEdgeVersion;

	m_pDevice = pDevice;
	bMapInit = false;

	hRenderEdgeMpq = nullptr;

	hotkey_ShowAntTweakBar = 0x76;
	hotkey_PauseGame = -1;
	hotkey_TakeScreenshot = -1;

	fWideScreenMul = 1.0f;

	fDeltaTime = 0.0f;
	fFPS = 0.0f;
	fTimer = 0.0f;

	bDefaultRenderer = false;
	bVsyncEnabled = false;
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
	ConfigINI.GetBool("IBL", "bEnabled", bIBL);
	ConfigINI.GetString("IBL", "CubemapTexture", envTextureFileName);
	ConfigINI.GetFloat("IBL", "CubemapBrightness", fCubemapBrightness);
	ConfigINI.GetFloat("IBL", "CubemapRotation", fEnvCubemapRotation);
	ConfigINI.GetBool("IBL", "bCubemapSwapYZ", bEnvCubemapSwapYZ);

	// Material
	ConfigINI.GetBool("Material", "bEnablePBS", bPBS);
	ConfigINI.GetFloat("Material", "Roughness", fMaterialRoughness);
	ConfigINI.GetFloat("Material", "Metallic", fMaterialMetallic);
	ConfigINI.GetFloat("Material", "Specular", fMaterialSpecular);
	ConfigINI.GetFloat("Material", "Translucent", fMaterialTranslucent);
	ConfigINI.GetString("Material", "NormalMapTexture", normalTextureFileName);
	ConfigINI.GetBool("Material", "bNormalMap", bNormalMapping);
	ConfigINI.GetBool("Material", "bAnisoFiltering", bAnisoFiltering);
	ConfigINI.GetBool("Material", "bTextures", bTexture);
	ConfigINI.GetBool("Material", "bMaterialColor", bMaterialColor);
	ConfigINI.GetBool("Material", "bMaterialVertexColor", bMaterialVertexColor);
	ConfigINI.GetBool("Material", "bUnshadedMaterials", bUnshadedMaterials);
	ConfigINI.GetBool("Material", "bUnfoggedMaterials", bUnfoggedMaterials);
	ConfigINI.GetBool("Material", "bMaterialColorSRGB", bMaterialColorSRGB);
	ConfigINI.GetBool("Material", "bVertexColorSRGB", bVertexColorSRGB);

	// Skybox
	ConfigINI.GetBool("Skybox", "bShading", bSkyboxShading);
	ConfigINI.GetBool("Skybox", "bFog", bSkyboxFog);
	ConfigINI.GetBool("Skybox", "bFixTwitching", bSkyboxFixTwitching);
	ConfigINI.GetFloat("Skybox", "Intensity", fSkyboxLightIntensity);

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

	// Fog of War
	ConfigINI.GetBool("FogOfWar", "bBuildingsShadows", bBuildingsShadows);
	ConfigINI.GetBool("FogOfWar", "bMaskedObjects", bMaskedObjects);
	ConfigINI.GetBool("FogOfWar", "bMapBounds", bMapBounds);

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
		UpdateMaskedObject();
	if (!bBuildingsShadows)
		UpdateBuildingsShadows();
	if (!bMapBounds)
		UpdateMapBounds();
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