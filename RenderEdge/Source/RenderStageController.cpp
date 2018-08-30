#include "RenderStageController.h"

RenderStage GetRenderStage()
{
	HOOK::RENDER_STATE rs = HOOK::getCurrentRenderState();

	if (rs == HOOK::STATE_PORTRAIT)
		return RenderStage::PORTRAIT;
	else if (rs != HOOK::STATE_UNIT_AND_EFFECT)
		return RenderStage::UI;

	switch (HOOK::g_CurrentRenderTarget)
	{
	case 0x00:
		return RenderStage::SKYBOX;
		break;
	case 0x01:
		return RenderStage::TERRAIN;
		break;
	case 0x02:
		return RenderStage::WAR_FOG;
		break;
	case 0x03:
		return RenderStage::UNIT_SHADOW;
		break;
	case 0x06:
		return RenderStage::PARTICLES;
		break;
	case 0x07:
		return RenderStage::UNIT_SELECTION_CIRCLE;
		break;
	case 0x09:
		return RenderStage::FOOT_PRINT;
		break;
	case 0x0A:
		return RenderStage::TERRAIN_DECORATION;
		break;
	case 0x0B:
		return RenderStage::UNIT;
		break;
	case 0x0D:
		return RenderStage::DESTRUCTIBLE;
		break;
	case 0x0E:
		return RenderStage::WATER;
		break;
	case 0x0F:
		return RenderStage::SCREEN_SELECTION_BOX;
		break;
	case 0x12:
		return RenderStage::BUILDING;
		break;
	case 0x13:
		return RenderStage::BUILDING_TERRAIN;
		break;
	case 0x14:
		return RenderStage::MAIN_MENU_UI;
		break;
	case 0x15:
		return RenderStage::UI;
		break;
	default:
		return RenderStage::UNKNOWN;
		break;
	}
}