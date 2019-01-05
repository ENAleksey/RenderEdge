#pragma once

#include "Utils.h"

enum class ERenderStage : uint32
{
	Skybox = 0,
	Terrain = 1,
	FogOfWar = 2,
	TerrainShadow = 3,
	WaterShadow = 4,
	Unknown1 = 5,
	Weather = 6,
	SelectionCircle = 7,
	Indicator = 8,
	Footprint = 9,
	Decoration = 10,
	Unit = 11,
	Unknown2 = 12,
	Destructible = 13,
	Water = 14,
	SelectionBox = 15,
	Unknown3 = 16,
	OcclusionMask = 17,
	Building = 18,
	Ubersplat = 19,
	Lightning = 20,
	FloatingText = 21,
	CineFilter,
	UI,
	Unknown
};

namespace RenderingHook
{
	extern bool bRenderSkybox;
	extern bool bRenderTerrain;
	extern bool bRenderFogOfWar;
	extern bool bRenderTerrainShadow;
	extern bool bRenderWaterShadow;
	extern bool bRenderWeather;
	extern bool bRenderSelectionCircle;
	extern bool bRenderFootprint;
	extern bool bRenderDecoration;
	extern bool bRenderUnit;
	extern bool bRenderDestructible;
	extern bool bRenderWater;
	extern bool bRenderSelectionBox;
	extern bool bRenderBuilding;
	extern bool bRenderUbersplat;
	extern bool bRenderUnknown1;
	extern bool bRenderIndicator;
	extern bool bRenderUnknown2;
	extern bool bRenderUnknown3;
	extern bool bRenderOcclusionMask;
	extern bool bRenderLightning;
	extern bool bRenderFloatingText;
	extern bool bRenderCineFilter;

	extern ERenderStage iCurrentRenderStage;

	ERenderStage GetRenderStage();
	bool IsTranslucent();

	bool Init();
}