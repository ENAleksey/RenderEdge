#include "RenderingHook.h"

#include "Engine.h"
#include "Camera.h"
#include "fp_call.h"
#include "Detour.h"
#include "GameUI.h"
#include "GameOffsets.h"

namespace RenderingHook
{
	ERenderStage iCurrentRenderStage = ERenderStage::MainMenuUI;
	bool bTranslucent = false;
	bool bGameCamera = false;

	bool bRenderSkybox = true;
	bool bRenderTerrain = true;
	bool bRenderFogOfWar = true;
	bool bRenderTerrainShadow = true;
	bool bRenderWaterShadow = true;
	bool bRenderWeather = true;
	bool bRenderSelectionCircle = true;
	bool bRenderFootprint = true;
	bool bRenderDecoration = true;
	bool bRenderUnit = true;
	bool bRenderDestructible = true;
	bool bRenderWater = true;
	bool bRenderSelectionBox = true;
	bool bRenderBuilding = true;
	bool bRenderUbersplat = true;
	bool bRenderUnknown1 = true;
	bool bRenderIndicator = true;
	bool bRenderUnknown2 = true;
	bool bRenderUnknown3 = true;
	bool bRenderOcclusionMask = true;
	bool bRenderLightning = true;
	bool bRenderFloatingText = true;


	ERenderStage GetRenderStage()
	{
		return iCurrentRenderStage;
	}

	bool IsTranslucent()
	{
		return bTranslucent;
	}


	void __fastcall RenderWorldObjects_proxy(int pWorldFrame, int unused, int iRenderStage, signed int lightPreset, int fogPreset, int bInMenu)
	{
		iCurrentRenderStage = static_cast<ERenderStage>(iRenderStage);

		if ((iCurrentRenderStage == ERenderStage::Skybox && !bRenderSkybox) ||
			(iCurrentRenderStage == ERenderStage::Terrain && !bRenderTerrain) ||
			(iCurrentRenderStage == ERenderStage::FogOfWar && !bRenderFogOfWar) ||
			(iCurrentRenderStage == ERenderStage::TerrainShadow && !bRenderTerrainShadow) ||
			(iCurrentRenderStage == ERenderStage::WaterShadow && !bRenderWaterShadow) ||
			(iCurrentRenderStage == ERenderStage::Unknown1 && !bRenderUnknown1) ||
			(iCurrentRenderStage == ERenderStage::Weather && !bRenderWeather) ||
			(iCurrentRenderStage == ERenderStage::SelectionCircle && !bRenderSelectionCircle) ||
			(iCurrentRenderStage == ERenderStage::Indicator && !bRenderIndicator) ||
			(iCurrentRenderStage == ERenderStage::Footprint && !bRenderFootprint) ||
			(iCurrentRenderStage == ERenderStage::Decoration && !bRenderDecoration) ||
			(iCurrentRenderStage == ERenderStage::Unit && !bRenderUnit) ||
			(iCurrentRenderStage == ERenderStage::Unknown2 && !bRenderUnknown2) ||
			(iCurrentRenderStage == ERenderStage::Destructible && !bRenderDestructible) ||
			(iCurrentRenderStage == ERenderStage::Water && !bRenderWater) ||
			(iCurrentRenderStage == ERenderStage::SelectionBox && !bRenderSelectionBox) ||
			(iCurrentRenderStage == ERenderStage::Unknown3 && !bRenderUnknown3) ||
			(iCurrentRenderStage == ERenderStage::OcclusionMask && !bRenderOcclusionMask) ||
			(iCurrentRenderStage == ERenderStage::Building && !bRenderBuilding) ||
			(iCurrentRenderStage == ERenderStage::Lightning && !bRenderLightning) ||
			(iCurrentRenderStage == ERenderStage::FloatingText && !bRenderFloatingText) ||
			(iCurrentRenderStage == ERenderStage::Ubersplat && !bRenderUbersplat))
			return;

		this_call<void>(address_RenderWorldObjects, pWorldFrame, iRenderStage, lightPreset, fogPreset, bInMenu);
	}

	int __fastcall RenderTranslucent_proxy()
	{
		bTranslucent = true;
		return fast_call<int>(address_RenderTranslucent);
	}

	int __fastcall RenderOpaque_proxy()
	{
		bTranslucent = false;
		return fast_call<int>(address_RenderOpaque);
	}

	int __fastcall RenderWorld_proxy(uint32 pWorldFrame, uint32 unused)
	{
		if (Engine)
			Engine->OnRenderWorld_before();

		int result = this_call<int>(address_RenderWorld, pWorldFrame);

		iCurrentRenderStage = ERenderStage::UI;

		if (Engine)
			Engine->OnRenderWorld_after();

		return result;
	}

	void __fastcall BuildMainMenu_proxy(CGameUI* pGameUI, int unused, int a2, int a3)
	{
		this_call<void>(address_BuildMainMenu, pGameUI, a2, a3);

		if (pGameUI->field024C)
			SetFrameText(pGameUI->field024C, RenderEdgeVersion);
	}

	void __fastcall BuildHPBars_proxy(uint32 a1, uint32 unused, uint32 a2, uint32 a3)
	{
		fast_call<void>(address_BuildHPBars, a1, unused, a2, a3);

		uint32 pHPBarFrame = *((uint32*)a1 + 3);
		if (pHPBarFrame)
			*((float*)pHPBarFrame + 22) /= g_fWideScreenMul;
	}

	void __fastcall MatrixPerspectiveFov_proxy(int matrix, int unused, float fovY, float aspectRatio, float nearZ, float farZ)
	{
		if (g_bDefaultProjectionMatrix)
		{
			float yScale = 1.0f / tan(1.0f / sqrt(aspectRatio * aspectRatio + 1.0f) * fovY * 0.5f);
			float xScale = yScale / (aspectRatio * g_fWideScreenMul);

			*(float*)matrix = xScale;
			*(float*)(matrix + 16) = 0.0f;
			*(float*)(matrix + 32) = 0.0f;
			*(float*)(matrix + 48) = 0.0f;

			*(float*)(matrix + 4) = 0.0f;
			*(float*)(matrix + 20) = yScale;
			*(float*)(matrix + 36) = 0.0f;
			*(float*)(matrix + 52) = 0.0f;

			*(float*)(matrix + 8) = 0.0f;
			*(float*)(matrix + 24) = 0.0f;
			*(float*)(matrix + 40) = (nearZ + farZ) / (farZ - nearZ);
			*(float*)(matrix + 56) = nearZ * (-2.0f * farZ) / (farZ - nearZ);

			*(float*)(matrix + 12) = 0.0f;
			*(float*)(matrix + 28) = 0.0f;
			*(float*)(matrix + 44) = 1.0f;
			*(float*)(matrix + 60) = 0.0f;
		}
		else
		{
			float fXAxisMultiplier;
			float fYAxisMultiplier;

			if (g_vBufferSize.x > g_vBufferSize.y)
			{
				const float fixValue = aspectRatio * 0.75f;
				fXAxisMultiplier = 1.0f;
				fYAxisMultiplier = (g_vBufferSize.x * g_vBufferSize.w) * fixValue;
			}
			else
			{
				const float fixValue = 1.0f / (aspectRatio * 0.75f);
				fXAxisMultiplier = (g_vBufferSize.y * g_vBufferSize.z) * fixValue;
				fYAxisMultiplier = 1.0f;
			}

			float fScale = 1.0f / tan(fovY * 0.5f);
			float xScale = fXAxisMultiplier * fScale;
			float yScale = fYAxisMultiplier * fScale;
			float zScale = farZ / (farZ - nearZ);

			*(float*)matrix = xScale;
			*(float*)(matrix + 16) = 0.0f;
			*(float*)(matrix + 32) = 0.0f;
			*(float*)(matrix + 48) = 0.0f;

			*(float*)(matrix + 4) = 0.0f;
			*(float*)(matrix + 20) = yScale;
			*(float*)(matrix + 36) = 0.0f;
			*(float*)(matrix + 52) = 0.0f;

			*(float*)(matrix + 8) = 0.0f;
			*(float*)(matrix + 24) = 0.0f;
			*(float*)(matrix + 40) = ((nearZ == farZ) ? 1.0f : zScale);
			*(float*)(matrix + 56) = -nearZ * ((nearZ == farZ) ? 1.0f : zScale);

			*(float*)(matrix + 12) = 0.0f;
			*(float*)(matrix + 28) = 0.0f;
			*(float*)(matrix + 44) = 1.0f;
			*(float*)(matrix + 60) = 0.0f;
		}
	}

	uint32 __fastcall MatrixLookAt_proxy(D3DXVECTOR3* pEye, D3DXVECTOR3* pAt, D3DXVECTOR3* pUp, uint32 pOutMatrix)
	{
		if (FreeCamera && FreeCamera->GetActive())
		{
			pUp->x = 0.0f;
			pUp->y = 0.0f;
			pUp->z = 1.0f;
		}

		D3DXVECTOR3 axisX, axisY, axisZ;

		// default
		D3DXVec3Subtract(&axisZ, pAt, pEye);
		D3DXVec3Normalize(&axisZ, &axisZ);
		D3DXVec3Cross(&axisX, &axisZ, pUp);
		D3DXVec3Normalize(&axisX, &axisX);
		D3DXVec3Cross(&axisY, &axisX, &axisZ);
		D3DXVec3Normalize(&axisY, &axisY);

		/*D3DXVec3Subtract(&axisZ, pAt, pEye);
		D3DXVec3Normalize(&axisZ, &axisZ);
		D3DXVec3Cross(&axisX, pUp, &axisZ);
		D3DXVec3Normalize(&axisX, &axisX);
		D3DXVec3Cross(&axisY, &axisZ, &axisX);
		D3DXVec3Normalize(&axisY, &axisY);
		axisX = -axisX;*/

		*(float*)(pOutMatrix) = axisX.x;
		*(float*)(pOutMatrix + 4) = axisY.x;
		*(float*)(pOutMatrix + 8) = axisZ.x;

		*(float*)(pOutMatrix + 12) = axisX.y;
		*(float*)(pOutMatrix + 16) = axisY.y;
		*(float*)(pOutMatrix + 20) = axisZ.y;

		*(float*)(pOutMatrix + 24) = axisX.z;
		*(float*)(pOutMatrix + 28) = axisY.z;
		*(float*)(pOutMatrix + 32) = axisZ.z;

		*(float*)(pOutMatrix + 36) = -D3DXVec3Dot(&axisX, pEye);
		*(float*)(pOutMatrix + 40) = -D3DXVec3Dot(&axisY, pEye);
		*(float*)(pOutMatrix + 44) = -D3DXVec3Dot(&axisZ, pEye);

		return pOutMatrix;
	}

	int __fastcall InitSceneView_proxy(uint32 pCamera, int unused, int pRect, int a4)
	{
		bGameCamera = (pCamera == GetGameCamera());

		if (bGameCamera)
		{
			if (Engine)
				Engine->OnCalcSceneView_before(pCamera);

			int result = this_call<int>(address_InitSceneView, pCamera, pRect, a4);

			if (Engine)
				Engine->OnCalcSceneView_after();

			return result;
		}

		return this_call<int>(address_InitSceneView, pCamera, pRect, a4);
	}


	bool Init()
	{
		bool bResult = true;

		bResult &= Detour::Install(&address_MatrixPerspectiveFov, (uintptr_t)MatrixPerspectiveFov_proxy);
		bResult &= Detour::Install(&address_InitSceneView, (uintptr_t)InitSceneView_proxy);
		bResult &= Detour::Install(&address_MatrixLookAt, (uintptr_t)MatrixLookAt_proxy);

		bResult &= Detour::Install(&address_RenderWorldObjects, (uintptr_t)RenderWorldObjects_proxy);
		bResult &= Detour::Install(&address_RenderTranslucent, (uintptr_t)RenderTranslucent_proxy);
		bResult &= Detour::Install(&address_RenderOpaque, (uintptr_t)RenderOpaque_proxy);
		bResult &= Detour::Install(&address_RenderWorld, (uintptr_t)RenderWorld_proxy);
		bResult &= Detour::Install(&address_BuildHPBars, (uintptr_t)BuildHPBars_proxy);
		bResult &= Detour::Install(&address_BuildMainMenu, (uintptr_t)BuildMainMenu_proxy);

		return bResult;
	}
}