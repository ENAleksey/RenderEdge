#include "CJass.h"
#include "Engine.h"

HCAMERAFIELD CAMERA_FIELD_TARGET_DISTANCE = 0;
HCAMERAFIELD CAMERA_FIELD_FARZ = 1;
HCAMERAFIELD CAMERA_FIELD_ANGLE_OF_ATTACK = 2;
HCAMERAFIELD CAMERA_FIELD_FIELD_OF_VIEW = 3;
HCAMERAFIELD CAMERA_FIELD_ROLL = 4;
HCAMERAFIELD CAMERA_FIELD_ROTATION = 5;
HCAMERAFIELD CAMERA_FIELD_ZOFFSET = 6;
HCAMERAFIELD CAMERA_FIELD_NEARZ = 7;

__declspec(naked) jInteger jNATIVE jass::AbilityId(jString abilityIdString)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3BB5F0
		jmp eax
	}
}

__declspec(naked) jString jNATIVE jass::AbilityId2String(jInteger abilityId)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3BB620
		jmp eax
	}
}

__declspec(naked) jReal jNATIVE jass::Acos(jReal x)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3B2AB0
		jmp eax
	}
}

__declspec(naked) jBoolean jNATIVE jass::AddAssault(jInteger arg1, jInteger arg2)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x2DD9C0
		jmp eax
	}
}

__declspec(naked) jBoolean jNATIVE jass::AddDefenders(jInteger arg1, jInteger arg2)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x2DDA00
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::AddGuardPost(jInteger arg1, jReal arg2, jReal arg3)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x2DCE30
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::AddHeroXP(HUNIT whichHero, jInteger xpToAdd, jBoolean showEyeCandy)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3C6CF0
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::AddIndicator(HWIDGET whichWidget, jInteger red, jInteger green, jInteger blue, jInteger alpha)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3C6C60
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::AddItemToAllStock(jInteger itemId, jInteger currentStock, jInteger stockMax)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3B3270
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::AddItemToStock(HUNIT whichUnit, jInteger itemId, jInteger currentStock, jInteger stockMax)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3C9350
		jmp eax
	}
}

__declspec(naked) HLIGHTNING jNATIVE jass::AddLightning(jString codeName, jBoolean checkVisibility, jReal x1, jReal y1, jReal x2, jReal y2)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3BCC20
		jmp eax
	}
}

__declspec(naked) HLIGHTNING jNATIVE jass::AddLightningEx(jString codeName, jBoolean checkVisibility, jReal x1, jReal y1, jReal z1, jReal x2, jReal y2, jReal z2)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3BCB30
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::AddPlayerTechResearched(HPLAYER whichPlayer, jInteger techid, jInteger levels)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3C96D0
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::AddResourceAmount(HUNIT whichUnit, jInteger amount)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3C7850
		jmp eax
	}
}

__declspec(naked) HEFFECT jNATIVE jass::AddSpecialEffect(jString modelName, jReal x, jReal y)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3BCA90
		jmp eax
	}
}

__declspec(naked) HEFFECT jNATIVE jass::AddSpecialEffectLoc(jString modelName, HLOCATION where)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3CD260
		jmp eax
	}
}

__declspec(naked) HEFFECT jNATIVE jass::AddSpecialEffectTarget(jString modelName, HWIDGET targetWidget, jString attachPointName)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3CD2A0
		jmp eax
	}
}

__declspec(naked) HEFFECT jNATIVE jass::AddSpellEffect(jString abilityString, HEFFECTTYPE t, jReal x, jReal y)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3BCB10
		jmp eax
	}
}

__declspec(naked) HEFFECT jNATIVE jass::AddSpellEffectById(jInteger abilityId, HEFFECTTYPE t, jReal x, jReal y)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3BCAE0
		jmp eax
	}
}

__declspec(naked) HEFFECT jNATIVE jass::AddSpellEffectByIdLoc(jInteger abilityId, HEFFECTTYPE t, HLOCATION where)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3CD2D0
		jmp eax
	}
}

__declspec(naked) HEFFECT jNATIVE jass::AddSpellEffectLoc(jString abilityString, HEFFECTTYPE t, HLOCATION where)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3CD320
		jmp eax
	}
}

__declspec(naked) HEFFECT jNATIVE jass::AddSpellEffectTarget(jString modelName, HEFFECTTYPE t, HWIDGET targetWidget, jString attachPoint)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3CD4A0
		jmp eax
	}
}

__declspec(naked) HEFFECT jNATIVE jass::AddSpellEffectTargetById(jInteger abilityId, HEFFECTTYPE t, HWIDGET targetWidget, jString attachPoint)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3CD380
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::AddUnitAnimationProperties(HUNIT whichUnit, jString animProperties, jBoolean add)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3C6220
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::AddUnitToAllStock(jInteger unitId, jInteger currentStock, jInteger stockMax)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3B3290
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::AddUnitToStock(HUNIT whichUnit, jInteger unitId, jInteger currentStock, jInteger stockMax)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3C93A0
		jmp eax
	}
}

__declspec(naked) HWEATHEREFFECT jNATIVE jass::AddWeatherEffect(HRECT where, jInteger effectID)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3CCFE0
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::AdjustCameraField(HCAMERAFIELD whichField, jReal offset, jReal duration)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3B48F0
		jmp eax
	}
}

__declspec(naked) HBOOLEXPR jNATIVE jass::And(HBOOLEXPR operandA, HBOOLEXPR operandB)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3D05F0
		jmp eax
	}
}

__declspec(naked) jReal jNATIVE jass::Asin(jReal y)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3B2A70
		jmp eax
	}
}

__declspec(naked) jReal jNATIVE jass::Atan(jReal x)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3B2AF0
		jmp eax
	}
}

__declspec(naked) jReal jNATIVE jass::Atan2(jReal y, jReal x)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3B2B10
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::AttachSoundToUnit(HSOUND soundHandle, HUNIT whichUnit)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3CCE50
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::AttackMoveKill(HUNIT arg1)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x2E0A40
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::AttackMoveXY(jInteger arg1, jInteger arg2)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x2DDC10
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::CachePlayerHeroData(HPLAYER whichPlayer)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3C9DE0
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::CameraSetSmoothingFactor(jReal factor)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3B4BB0
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::CameraSetSourceNoise(jReal mag, jReal velocity)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3B49E0
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::CameraSetSourceNoiseEx(jReal mag, jReal velocity, jBoolean vertOnly)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3B4B20
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::CameraSetTargetNoise(jReal mag, jReal velocity)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3B4930
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::CameraSetTargetNoiseEx(jReal mag, jReal velocity, jBoolean vertOnly)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3B4A70
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::CameraSetupApply(HCAMERASETUP whichSetup, jBoolean doPan, jBoolean panTimed)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3CD900
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::CameraSetupApplyForceDuration(HCAMERASETUP whichSetup, jBoolean doPan, jReal forceDuration)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3CD960
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::CameraSetupApplyForceDurationWithZ(HCAMERASETUP whichSetup, jReal zDestOffset, jReal forceDuration)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3CD990
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::CameraSetupApplyWithZ(HCAMERASETUP whichSetup, jReal zDestOffset)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3CD930
		jmp eax
	}
}

__declspec(naked) HLOCATION jNATIVE jass::CameraSetupGetDestPositionLoc(HCAMERASETUP whichSetup)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3D3E40
		jmp eax
	}
}

__declspec(naked) jReal jNATIVE jass::CameraSetupGetDestPositionX(HCAMERASETUP whichSetup)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3CD8C0
		jmp eax
	}
}

__declspec(naked) jReal jNATIVE jass::CameraSetupGetDestPositionY(HCAMERASETUP whichSetup)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3CD8E0
		jmp eax
	}
}

__declspec(naked) jReal jNATIVE jass::CameraSetupGetField(HCAMERASETUP whichSetup, HCAMERAFIELD whichField)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3CD830
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::CameraSetupSetDestPosition(HCAMERASETUP whichSetup, jReal x, jReal y, jReal duration)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3CD870
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::CameraSetupSetField(HCAMERASETUP whichSetup, HCAMERAFIELD whichField, jReal value, jReal duration)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3CD800
		jmp eax
	}
}

__declspec(naked) jBoolean jNATIVE jass::CaptainAtGoal()
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x2DD930
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::CaptainAttack(jReal arg1, jReal arg2)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x2DD700
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::CaptainGoHome()
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x2DD800
		jmp eax
	}
}

__declspec(naked) jInteger jNATIVE jass::CaptainGroupSize()
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x2DDB90
		jmp eax
	}
}

__declspec(naked) jBoolean jNATIVE jass::CaptainInCombat(jBoolean arg1)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x2DD8A0
		jmp eax
	}
}

__declspec(naked) jBoolean jNATIVE jass::CaptainIsEmpty()
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x2DDB50
		jmp eax
	}
}

__declspec(naked) jBoolean jNATIVE jass::CaptainIsFull()
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x2DDB10
		jmp eax
	}
}

__declspec(naked) jBoolean jNATIVE jass::CaptainIsHome()
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x2DD870
		jmp eax
	}
}

__declspec(naked) jInteger jNATIVE jass::CaptainReadiness()
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x2DDA40
		jmp eax
	}
}

__declspec(naked) jInteger jNATIVE jass::CaptainReadinessHP()
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x2DDA90
		jmp eax
	}
}

__declspec(naked) jInteger jNATIVE jass::CaptainReadinessMa()
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x2DDAD0
		jmp eax
	}
}

__declspec(naked) jBoolean jNATIVE jass::CaptainRetreating()
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x2DD830
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::CaptainVsPlayer(HPLAYER arg1)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x2E2C80
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::CaptainVsUnits(HPLAYER arg1)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x2E2BF0
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::ChangeLevel(jString newLevel, jBoolean doScoreScreen)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3BBC30
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::Cheat(jString cheatStr)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3B3BC0
		jmp eax
	}
}

__declspec(naked) jInteger jNATIVE jass::ChooseRandomCreep(jInteger level)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3B3660
		jmp eax
	}
}

__declspec(naked) jInteger jNATIVE jass::ChooseRandomItem(jInteger level)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3B3690
		jmp eax
	}
}

__declspec(naked) jInteger jNATIVE jass::ChooseRandomItemEx(HITEMTYPE whichType, jInteger level)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3B36B0
		jmp eax
	}
}

__declspec(naked) jInteger jNATIVE jass::ChooseRandomNPBuilding()
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3B3680
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::ClearCaptainTargets()
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x2DD6C0
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::ClearHarvestAI()
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x2DD5B0
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::ClearMapMusic()
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3B3D20
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::ClearSelection()
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3BBAA0
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::ClearStackedSound(jString arg1, jReal arg2, jReal arg3)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3B3C80
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::ClearStackedSoundRect(jString arg1, HRECT arg2)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3CCB20
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::ClearTextMessages()
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3B4E60
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::CommandAI(HPLAYER num, jInteger command, jInteger data)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3CB7A0
		jmp eax
	}
}

__declspec(naked) jInteger jNATIVE jass::CommandsWaiting()
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x2DCDD0
		jmp eax
	}
}

__declspec(naked) HCONDITIONFUNC jNATIVE jass::Condition(jCode func)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3BB0A0
		jmp eax
	}
}

__declspec(naked) HAIDIFFICULTY jNATIVE jass::ConvertAIDifficulty(jInteger i)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3B2690
		jmp eax
	}
}

__declspec(naked) HALLIANCETYPE jNATIVE jass::ConvertAllianceType(jInteger i)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3B2610
		jmp eax
	}
}

__declspec(naked) HATTACKTYPE jNATIVE jass::ConvertAttackType(jInteger i)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3B2870
		jmp eax
	}
}

__declspec(naked) HBLENDMODE jNATIVE jass::ConvertBlendMode(jInteger i)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3B2810
		jmp eax
	}
}

__declspec(naked) HCAMERAFIELD jNATIVE jass::ConvertCameraField(jInteger i)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3B27F0
		jmp eax
	}
}

__declspec(naked) HDAMAGETYPE jNATIVE jass::ConvertDamageType(jInteger i)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3B2880
		jmp eax
	}
}

__declspec(naked) HDIALOGEVENT jNATIVE jass::ConvertDialogEvent(jInteger i)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3B26F0
		jmp eax
	}
}

__declspec(naked) HEFFECTTYPE jNATIVE jass::ConvertEffectType(jInteger i)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3B2840
		jmp eax
	}
}

__declspec(naked) HFGAMESTATE jNATIVE jass::ConvertFGameState(jInteger i)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3B2640
		jmp eax
	}
}

__declspec(naked) HFOGSTATE jNATIVE jass::ConvertFogState(jInteger i)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3B2830
		jmp eax
	}
}

__declspec(naked) HGAMEDIFFICULTY jNATIVE jass::ConvertGameDifficulty(jInteger i)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3B2750
		jmp eax
	}
}

__declspec(naked) HGAMEEVENT jNATIVE jass::ConvertGameEvent(jInteger i)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3B26A0
		jmp eax
	}
}

__declspec(naked) HGAMESPEED jNATIVE jass::ConvertGameSpeed(jInteger i)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3B2720
		jmp eax
	}
}

__declspec(naked) HGAMETYPE jNATIVE jass::ConvertGameType(jInteger i)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3B2760
		jmp eax
	}
}

__declspec(naked) HIGAMESTATE jNATIVE jass::ConvertIGameState(jInteger i)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3B2630
		jmp eax
	}
}

__declspec(naked) HITEMTYPE jNATIVE jass::ConvertItemType(jInteger i)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3B2860
		jmp eax
	}
}

__declspec(naked) HLIMITOP jNATIVE jass::ConvertLimitOp(jInteger i)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3B2700
		jmp eax
	}
}

__declspec(naked) HMAPCONTROL jNATIVE jass::ConvertMapControl(jInteger i)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3B27B0
		jmp eax
	}
}

__declspec(naked) HMAPDENSITY jNATIVE jass::ConvertMapDensity(jInteger i)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3B27A0
		jmp eax
	}
}

__declspec(naked) HMAPFLAG jNATIVE jass::ConvertMapFlag(jInteger i)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3B2770
		jmp eax
	}
}

__declspec(naked) HMAPSETTING jNATIVE jass::ConvertMapSetting(jInteger i)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3B2790
		jmp eax
	}
}

__declspec(naked) HMAPVISIBILITY jNATIVE jass::ConvertMapVisibility(jInteger i)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3B2780
		jmp eax
	}
}

__declspec(naked) HPATHINGTYPE jNATIVE jass::ConvertPathingType(jInteger i)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3B28B0
		jmp eax
	}
}

__declspec(naked) HPLACEMENT jNATIVE jass::ConvertPlacement(jInteger i)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3B2730
		jmp eax
	}
}

__declspec(naked) HPLAYERCOLOR jNATIVE jass::ConvertPlayerColor(jInteger i)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3B27C0
		jmp eax
	}
}

__declspec(naked) HPLAYEREVENT jNATIVE jass::ConvertPlayerEvent(jInteger i)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3B26B0
		jmp eax
	}
}

__declspec(naked) HPLAYERGAMERESULT jNATIVE jass::ConvertPlayerGameResult(jInteger i)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3B2670
		jmp eax
	}
}

__declspec(naked) HPLAYERSCORE jNATIVE jass::ConvertPlayerScore(jInteger i)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3B2660
		jmp eax
	}
}

__declspec(naked) HPLAYERSLOTSTATE jNATIVE jass::ConvertPlayerSlotState(jInteger i)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3B27D0
		jmp eax
	}
}

__declspec(naked) HPLAYERSTATE jNATIVE jass::ConvertPlayerState(jInteger i)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3B2650
		jmp eax
	}
}

__declspec(naked) HPLAYERUNITEVENT jNATIVE jass::ConvertPlayerUnitEvent(jInteger i)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3B26C0
		jmp eax
	}
}

__declspec(naked) HRACE jNATIVE jass::ConvertRace(jInteger i)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3B2600
		jmp eax
	}
}

__declspec(naked) HRACEPREFERENCE jNATIVE jass::ConvertRacePref(jInteger i)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3B2620
		jmp eax
	}
}

__declspec(naked) HRARITYCONTROL jNATIVE jass::ConvertRarityControl(jInteger i)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3B2800
		jmp eax
	}
}

__declspec(naked) HSOUNDTYPE jNATIVE jass::ConvertSoundType(jInteger i)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3B28A0
		jmp eax
	}
}

__declspec(naked) HSTARTLOCPRIO jNATIVE jass::ConvertStartLocPrio(jInteger i)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3B2740
		jmp eax
	}
}

__declspec(naked) HTEXMAPFLAGS jNATIVE jass::ConvertTexMapFlags(jInteger i)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3B2820
		jmp eax
	}
}

__declspec(naked) HUNITEVENT jNATIVE jass::ConvertUnitEvent(jInteger i)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3B26D0
		jmp eax
	}
}

__declspec(naked) HUNITSTATE jNATIVE jass::ConvertUnitState(jInteger i)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3B2680
		jmp eax
	}
}

__declspec(naked) HUNITTYPE jNATIVE jass::ConvertUnitType(jInteger i)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3B2710
		jmp eax
	}
}

__declspec(naked) jBoolean jNATIVE jass::ConvertUnits(jInteger arg1, jInteger arg2)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x2DD2E0
		jmp eax
	}
}

__declspec(naked) HVERSION jNATIVE jass::ConvertVersion(jInteger i)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3B2850
		jmp eax
	}
}

__declspec(naked) HVOLUMEGROUP jNATIVE jass::ConvertVolumeGroup(jInteger i)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3B27E0
		jmp eax
	}
}

__declspec(naked) HWEAPONTYPE jNATIVE jass::ConvertWeaponType(jInteger i)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3B2890
		jmp eax
	}
}

__declspec(naked) HWIDGETEVENT jNATIVE jass::ConvertWidgetEvent(jInteger i)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3B26E0
		jmp eax
	}
}

__declspec(naked) jBoolean jNATIVE jass::CopySaveGame(jString sourceSaveName, jString destSaveName)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3BC180
		jmp eax
	}
}

__declspec(naked) jReal jNATIVE jass::Cos(jReal radians)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3B2A30
		jmp eax
	}
}

__declspec(naked) HUNIT jNATIVE jass::CreateBlightedGoldmine(HPLAYER id, jReal x, jReal y, jReal face)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3CD630
		jmp eax
	}
}

__declspec(naked) HCAMERASETUP jNATIVE jass::CreateCameraSetup()
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3D3D40
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::CreateCaptains()
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x2DD960
		jmp eax
	}
}

__declspec(naked) HUNIT jNATIVE jass::CreateCorpse(HPLAYER whichPlayer, jInteger unitid, jReal x, jReal y, jReal face)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3C5350
		jmp eax
	}
}

__declspec(naked) HDESTRUCTABLE jNATIVE jass::CreateDeadDestructable(jInteger objectid, jReal x, jReal y, jReal face, jReal scale, jInteger variation)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3BB840
		jmp eax
	}
}

__declspec(naked) HDESTRUCTABLE jNATIVE jass::CreateDeadDestructableZ(jInteger objectid, jReal x, jReal y, jReal z, jReal face, jReal scale, jInteger variation)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3BB890
		jmp eax
	}
}

__declspec(naked) HDEFEATCONDITION jNATIVE jass::CreateDefeatCondition()
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3BC9E0
		jmp eax
	}
}

__declspec(naked) HDESTRUCTABLE jNATIVE jass::CreateDestructable(jInteger objectid, jReal x, jReal y, jReal face, jReal scale, jInteger variation)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3BB790
		jmp eax
	}
}

__declspec(naked) HDESTRUCTABLE jNATIVE jass::CreateDestructableZ(jInteger objectid, jReal x, jReal y, jReal z, jReal face, jReal scale, jInteger variation)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3BB7E0
		jmp eax
	}
}

__declspec(naked) HFOGMODIFIER jNATIVE jass::CreateFogModifierRadius(HPLAYER forWhichPlayer, HFOGSTATE whichState, jReal centerx, jReal centerY, jReal radius, jBoolean useSharedVision, jBoolean afterUnits)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3D0F90
		jmp eax
	}
}

__declspec(naked) HFOGMODIFIER jNATIVE jass::CreateFogModifierRadiusLoc(HPLAYER forWhichPlayer, HFOGSTATE whichState, HLOCATION center, jReal radius, jBoolean useSharedVision, jBoolean afterUnits)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3D10F0
		jmp eax
	}
}

__declspec(naked) HFOGMODIFIER jNATIVE jass::CreateFogModifierRect(HPLAYER forWhichPlayer, HFOGSTATE whichState, HRECT where, jBoolean useSharedVision, jBoolean afterUnits)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3D0E70
		jmp eax
	}
}

__declspec(naked) HFORCE jNATIVE jass::CreateForce()
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3D29F0
		jmp eax
	}
}

__declspec(naked) HGROUP jNATIVE jass::CreateGroup()
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3D2900
		jmp eax
	}
}

__declspec(naked) HIMAGE jNATIVE jass::CreateImage(jString file, jReal sizeX, jReal sizeY, jReal sizeZ, jReal posX, jReal posY, jReal posZ, jReal originX, jReal originY, jReal originZ, jInteger imageType)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3B4320
		jmp eax
	}
}

__declspec(naked) HITEM jNATIVE jass::CreateItem(jInteger itemid, jReal x, jReal y)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3BB9A0
		jmp eax
	}
}

__declspec(naked) HITEMPOOL jNATIVE jass::CreateItemPool()
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3D2FC0
		jmp eax
	}
}

__declspec(naked) HLEADERBOARD jNATIVE jass::CreateLeaderboard()
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3D35B0
		jmp eax
	}
}

__declspec(naked) HSOUND jNATIVE jass::CreateMIDISound(jString soundLabel, jInteger fadeInRate, jInteger fadeOutRate)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3D3C30
		jmp eax
	}
}

__declspec(naked) HMULTIBOARD jNATIVE jass::CreateMultiboard()
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3D36B0
		jmp eax
	}
}

__declspec(naked) HQUEST jNATIVE jass::CreateQuest()
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3BC970
		jmp eax
	}
}

__declspec(naked) HREGION jNATIVE jass::CreateRegion()
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3D0930
		jmp eax
	}
}

__declspec(naked) HSOUND jNATIVE jass::CreateSound(jString fileName, jBoolean looping, jBoolean is3D, jBoolean stopwhenoutofrange, jInteger fadeInRate, jInteger fadeOutRate, jString eaxSetting)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3D38D0
		jmp eax
	}
}

__declspec(naked) HSOUND jNATIVE jass::CreateSoundFilenameWithLabel(jString fileName, jBoolean looping, jBoolean is3D, jBoolean stopwhenoutofrange, jInteger fadeInRate, jInteger fadeOutRate, jString SLKEntryName)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3D39F0
		jmp eax
	}
}

__declspec(naked) HSOUND jNATIVE jass::CreateSoundFromLabel(jString soundLabel, jBoolean looping, jBoolean is3D, jBoolean stopwhenoutofrange, jInteger fadeInRate, jInteger fadeOutRate)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3D3B10
		jmp eax
	}
}

__declspec(naked) HTEXTTAG jNATIVE jass::CreateTextTag()
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3BC580
		jmp eax
	}
}

__declspec(naked) HTIMER jNATIVE jass::CreateTimer()
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3D0500
		jmp eax
	}
}

__declspec(naked) HTIMERDIALOG jNATIVE jass::CreateTimerDialog(HTIMER t)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3D34B0
		jmp eax
	}
}

__declspec(naked) HTRACKABLE jNATIVE jass::CreateTrackable(jString trackableModelPath, jReal x, jReal y, jReal facing)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3D30B0
		jmp eax
	}
}

__declspec(naked) jTrigger jNATIVE jass::CreateTrigger()
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3D11F0
		jmp eax
	}
}

__declspec(naked) HUBERSPLAT jNATIVE jass::CreateUbersplat(jReal x, jReal y, jString name, jInteger red, jInteger green, jInteger blue, jInteger alpha, jBoolean forcePaused, jBoolean noBirthTime)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3B85F0
		jmp eax
	}
}

__declspec(naked) HUNIT jNATIVE jass::CreateUnit(HPLAYER id, jInteger unitid, jReal x, jReal y, jReal face)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3C5230
		jmp eax
	}
}

__declspec(naked) HUNIT jNATIVE jass::CreateUnitAtLoc(HPLAYER id, jInteger unitid, HLOCATION whichLocation, jReal face)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3C52D0
		jmp eax
	}
}

__declspec(naked) HUNIT jNATIVE jass::CreateUnitAtLocByName(HPLAYER id, jString unitname, HLOCATION whichLocation, jReal face)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3C5320
		jmp eax
	}
}

__declspec(naked) HUNIT jNATIVE jass::CreateUnitByName(HPLAYER whichPlayer, jString unitname, jReal x, jReal y, jReal face)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3C52A0
		jmp eax
	}
}

__declspec(naked) HUNITPOOL jNATIVE jass::CreateUnitPool()
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3D2ED0
		jmp eax
	}
}

__declspec(naked) jBoolean jNATIVE jass::CreepsOnMap()
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x2DC0F0
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::CripplePlayer(HPLAYER whichPlayer, HFORCE toWhichPlayers, jBoolean flag)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3C1310
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::DebugBreak(jInteger arg1)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x2DC050
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::DebugFI(jString arg1, jInteger arg2)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x2DC0B0
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::DebugS(jString arg1)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x2DC0A0
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::DebugUnitID(jString arg1, jInteger arg2)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x2DC0C0
		jmp eax
	}
}

__declspec(naked) jInteger jNATIVE jass::DecUnitAbilityLevel(HUNIT whichUnit, jInteger abilcode)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3C70B0
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::DefeatConditionSetDescription(HDEFEATCONDITION whichCondition, jString description)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3CBE00
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::DefineStartLocation(jInteger whichStartLoc, jReal x, jReal y)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3BAF70
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::DefineStartLocationLoc(jInteger whichStartLoc, HLOCATION whichLocation)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3C0EA0
		jmp eax
	}
}

__declspec(naked) jReal jNATIVE jass::Deg2Rad(jReal degrees)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3B29D0
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::DestroyBoolExpr(HBOOLEXPR e)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3C14A0
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::DestroyCondition(HCONDITIONFUNC c)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3C1440
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::DestroyDefeatCondition(HDEFEATCONDITION whichCondition)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3CBDB0
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::DestroyEffect(HEFFECT whichEffect)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3CD240
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::DestroyFilter(HFILTERFUNC f)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3C1470
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::DestroyFogModifier(HFOGMODIFIER whichFogModifier)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3C1BA0
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::DestroyForce(HFORCE whichForce)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3C44C0
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::DestroyGroup(HGROUP whichGroup)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3C3FA0
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::DestroyImage(HIMAGE whichImage)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3B43B0
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::DestroyItemPool(HITEMPOOL whichItemPool)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3CB6A0
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::DestroyLeaderboard(HLEADERBOARD lb)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3CBFD0
		jmp eax
	}
}

__declspec(naked) jBoolean jNATIVE jass::DestroyLightning(HLIGHTNING whichBolt)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3B4150
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::DestroyMultiboard(HMULTIBOARD lb)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3CC650
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::DestroyQuest(HQUEST whichQuest)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3CBB20
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::DestroyTextTag(HTEXTTAG t)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3BC5A0
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::DestroyTimer(HTIMER whichTimer)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3C1350
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::DestroyTimerDialog(HTIMERDIALOG whichDialog)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3CBE30
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::DestroyTrigger(jTrigger whichTrigger)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3C1C00
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::DestroyUbersplat(HUBERSPLAT whichSplat)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3B44C0
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::DestroyUnitPool(HUNITPOOL whichPool)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3CB5C0
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::DestructableRestoreLife(HDESTRUCTABLE d, jReal life, jBoolean birth)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3C4870
		jmp eax
	}
}

__declspec(naked) HBUTTON jNATIVE jass::DialogAddButton(HDIALOG whichDialog, jString buttonText, jInteger hotkey)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3C9F90
		jmp eax
	}
}

__declspec(naked) HBUTTON jNATIVE jass::DialogAddQuitButton(HDIALOG whichDialog, jBoolean doScoreScreen, jString buttonText, jInteger hotkey)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3C9FE0
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::DialogClear(HDIALOG whichDialog)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3C9F40
		jmp eax
	}
}

__declspec(naked) HDIALOG jNATIVE jass::DialogCreate()
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3D2BC0
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::DialogDestroy(HDIALOG whichDialog)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3C9F00
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::DialogDisplay(HPLAYER whichPlayer, HDIALOG whichDialog, jBoolean flag)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3CA030
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::DialogSetAsync(HDIALOG arg1)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3C9F20
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::DialogSetMessage(HDIALOG whichDialog, jString messageText)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3C9F60
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::DisablePathing()
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x2E06E0
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::DisableRestartMission(jBoolean flag)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3B38C0
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::DisableTrigger(jTrigger whichTrigger)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3C1C60
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::DisplayCineFilter(jBoolean flag)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3B5120
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::DisplayLoadDialog()
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3B3A10
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::DisplayText(jInteger arg1, jString arg2)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x2DC060
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::DisplayTextI(jInteger arg1, jString arg2, jInteger arg3)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x2DC070
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::DisplayTextII(jInteger arg1, jString arg2, jInteger arg3, jInteger arg4)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x2DC080
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::DisplayTextIII(jInteger arg1, jString arg2, jInteger arg3, jInteger arg4, jInteger arg5)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x2DC090
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::DisplayTextToPlayer(HPLAYER toPlayer, jReal x, jReal y, jString message)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3CB900
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::DisplayTimedTextFromPlayer(HPLAYER toPlayer, jReal x, jReal y, jReal duration, jString message)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3CBA30
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::DisplayTimedTextToPlayer(HPLAYER toPlayer, jReal x, jReal y, jReal duration, jString message)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3CB9B0
		jmp eax
	}
}

__declspec(naked) jBoolean jNATIVE jass::DoAiScriptDebug()
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x2DC0D0
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::DoNotSaveReplay()
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3B3550
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::EnableDragSelect(jBoolean state, jBoolean ui)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3B3B30
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::EnableMinimapFilterButtons(jBoolean enableAlly, jBoolean enableCreep)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3B3AF0
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::EnableOcclusion(jBoolean flag)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3B3B90
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::EnablePreSelect(jBoolean state, jBoolean ui)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3B3B50
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::EnableSelect(jBoolean state, jBoolean ui)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3B3B70
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::EnableTrigger(jTrigger whichTrigger)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3C1C40
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::EnableUserControl(jBoolean b)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3B3880
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::EnableUserUI(jBoolean b)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3B38A0
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::EnableWeatherEffect(HWEATHEREFFECT whichEffect, jBoolean enable)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3B3E80
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::EnableWorldFogBoundary(jBoolean b)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3B3BB0
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::EndCinematicScene()
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3B4E20
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::EndGame(jBoolean doScoreScreen)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3BBBB0
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::EndThematicMusic()
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3B3DE0
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::EnumDestructablesInRect(HRECT r, HBOOLEXPR filter, jCode actionFunc)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3C4A90
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::EnumItemsInRect(HRECT r, HBOOLEXPR filter, jCode actionFunc)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3C5110
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::ExecuteFunc(jString funcName)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3D3F30
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::FillGuardPosts()
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x2DCF80
		jmp eax
	}
}

__declspec(naked) HFILTERFUNC jNATIVE jass::Filter(jCode func)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3BB140
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::FinishUbersplat(HUBERSPLAT whichSplat)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3B44E0
		jmp eax
	}
}

__declspec(naked) HUNIT jNATIVE jass::FirstOfGroup(HGROUP whichGroup)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3C4460
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::FlashQuestDialogButton()
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3BC920
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::FlushChildHashtable(HHASHTABLE table, jInteger parentKey)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3CB590
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::FlushGameCache(HGAMECACHE cache)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3CB200
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::FlushParentHashtable(HHASHTABLE table)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3CB550
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::FlushStoredBoolean(HGAMECACHE cache, jString missionKey, jString key)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3CB320
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::FlushStoredInteger(HGAMECACHE cache, jString missionKey, jString key)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3CB280
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::FlushStoredMission(HGAMECACHE cache, jString missionKey)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3CB240
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::FlushStoredReal(HGAMECACHE cache, jString missionKey, jString key)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3CB2D0
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::FlushStoredString(HGAMECACHE cache, jString missionKey, jString key)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3CB3C0
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::FlushStoredUnit(HGAMECACHE cache, jString missionKey, jString key)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3CB370
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::FogEnable(jBoolean enable)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3BB1E0
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::FogMaskEnable(jBoolean enable)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3BB210
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::FogModifierStart(HFOGMODIFIER whichFogModifier)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3C1BC0
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::FogModifierStop(HFOGMODIFIER whichFogModifier)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3C1BE0
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::ForForce(HFORCE whichForce, jCode callback)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3C4640
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::ForGroup(HGROUP whichGroup, jCode callback)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3C44A0
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::ForceAddPlayer(HFORCE whichForce, HPLAYER whichPlayer)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3C44E0
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::ForceCampaignSelectScreen()
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3BC400
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::ForceCinematicSubtitles(jBoolean flag)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3B4E40
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::ForceClear(HFORCE whichForce)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3C4540
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::ForceEnumAllies(HFORCE whichForce, HPLAYER whichPlayer, HBOOLEXPR filter)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3C45C0
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::ForceEnumEnemies(HFORCE whichForce, HPLAYER whichPlayer, HBOOLEXPR filter)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3C4600
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::ForceEnumPlayers(HFORCE whichForce, HBOOLEXPR filter)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3C4560
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::ForceEnumPlayersCounted(HFORCE whichForce, HBOOLEXPR filter, jInteger countLimit)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3C4590
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::ForcePlayerStartLocation(HPLAYER whichPlayer, jInteger startLocIndex)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3C0FA0
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::ForceQuestDialogUpdate()
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3B3BE0
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::ForceRemovePlayer(HFORCE whichForce, HPLAYER whichPlayer)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3C4510
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::ForceUICancel()
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3B3990
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::ForceUIKey(jString key)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3B38E0
		jmp eax
	}
}

__declspec(naked) HAIDIFFICULTY jNATIVE jass::GetAIDifficulty(HPLAYER num)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3CB7E0
		jmp eax
	}
}

__declspec(naked) jString jNATIVE jass::GetAbilityEffect(jString abilityString, HEFFECTTYPE t, jInteger index)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3BCAB0
		jmp eax
	}
}

__declspec(naked) jString jNATIVE jass::GetAbilityEffectById(jInteger abilityId, HEFFECTTYPE t, jInteger index)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3BCE40
		jmp eax
	}
}

__declspec(naked) jString jNATIVE jass::GetAbilitySound(jString abilityString, HSOUNDTYPE t)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3BCE60
		jmp eax
	}
}

__declspec(naked) jString jNATIVE jass::GetAbilitySoundById(jInteger abilityId, HSOUNDTYPE t)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3BCEA0
		jmp eax
	}
}

__declspec(naked) jInteger jNATIVE jass::GetAiPlayer()
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x2DCFE0
		jmp eax
	}
}

__declspec(naked) HUNIT jNATIVE jass::GetAllianceTarget()
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x2DD570
		jmp eax
	}
}

__declspec(naked) jInteger jNATIVE jass::GetAllyColorFilterState()
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3B3A50
		jmp eax
	}
}

__declspec(naked) HUNIT jNATIVE jass::GetAttacker()
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3C20F0
		jmp eax
	}
}

__declspec(naked) HUNIT jNATIVE jass::GetBuilding(HPLAYER arg1)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x2E2E80
		jmp eax
	}
}

__declspec(naked) HUNIT jNATIVE jass::GetBuyingUnit()
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3C27B0
		jmp eax
	}
}

__declspec(naked) jReal jNATIVE jass::GetCameraBoundMaxX()
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3B4C90
		jmp eax
	}
}

__declspec(naked) jReal jNATIVE jass::GetCameraBoundMaxY()
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3B4CB0
		jmp eax
	}
}

__declspec(naked) jReal jNATIVE jass::GetCameraBoundMinX()
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3B4C50
		jmp eax
	}
}

__declspec(naked) jReal jNATIVE jass::GetCameraBoundMinY()
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3B4C70
		jmp eax
	}
}

__declspec(naked) HLOCATION jNATIVE jass::GetCameraEyePositionLoc()
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3D3EE0
		jmp eax
	}
}

__declspec(naked) jReal jNATIVE jass::GetCameraEyePositionX()
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3B4D90
		jmp eax
	}
}

__declspec(naked) jReal jNATIVE jass::GetCameraEyePositionY()
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3B4DC0
		jmp eax
	}
}

__declspec(naked) jReal jNATIVE jass::GetCameraEyePositionZ()
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3B4DF0
		jmp eax
	}
}

__declspec(naked) jReal jNATIVE jass::GetCameraField(HCAMERAFIELD whichField)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3B4CD0
		jmp eax
	}
}

__declspec(naked) jReal jNATIVE jass::GetCameraMargin(jInteger whichMargin)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3B4BE0
		jmp eax
	}
}

__declspec(naked) HLOCATION jNATIVE jass::GetCameraTargetPositionLoc()
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3D3E90
		jmp eax
	}
}

__declspec(naked) jReal jNATIVE jass::GetCameraTargetPositionX()
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3B4D00
		jmp eax
	}
}

__declspec(naked) jReal jNATIVE jass::GetCameraTargetPositionY()
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3B4D30
		jmp eax
	}
}

__declspec(naked) jReal jNATIVE jass::GetCameraTargetPositionZ()
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3B4D60
		jmp eax
	}
}

__declspec(naked) HUNIT jNATIVE jass::GetCancelledStructure()
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3BB470
		jmp eax
	}
}

__declspec(naked) HUNIT jNATIVE jass::GetChangingUnit()
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3C2680
		jmp eax
	}
}

__declspec(naked) HPLAYER jNATIVE jass::GetChangingUnitPrevOwner()
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3C26E0
		jmp eax
	}
}

__declspec(naked) HBUTTON jNATIVE jass::GetClickedButton()
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3C1DE0
		jmp eax
	}
}

__declspec(naked) HDIALOG jNATIVE jass::GetClickedDialog()
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3C1E30
		jmp eax
	}
}

__declspec(naked) HUNIT jNATIVE jass::GetConstructedStructure()
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3BB490
		jmp eax
	}
}

__declspec(naked) HUNIT jNATIVE jass::GetConstructingStructure()
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3BB450
		jmp eax
	}
}

__declspec(naked) HMAPDENSITY jNATIVE jass::GetCreatureDensity()
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3BAF60
		jmp eax
	}
}

__declspec(naked) HUNIT jNATIVE jass::GetCreepCamp(jInteger arg1, jInteger arg2, jBoolean arg3)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x2E3D50
		jmp eax
	}
}

__declspec(naked) jBoolean jNATIVE jass::GetCreepCampFilterState()
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3B3AA0
		jmp eax
	}
}

__declspec(naked) jBoolean jNATIVE jass::GetCustomCampaignButtonVisible(jInteger whichButton)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3B3530
		jmp eax
	}
}

__declspec(naked) HUNIT jNATIVE jass::GetDecayingUnit()
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3BB430
		jmp eax
	}
}

__declspec(naked) HGAMEDIFFICULTY jNATIVE jass::GetDefaultDifficulty()
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3B33A0
		jmp eax
	}
}

__declspec(naked) jReal jNATIVE jass::GetDestructableLife(HDESTRUCTABLE d)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3C4890
		jmp eax
	}
}

__declspec(naked) jReal jNATIVE jass::GetDestructableMaxLife(HDESTRUCTABLE d)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3C4920
		jmp eax
	}
}

__declspec(naked) jString jNATIVE jass::GetDestructableName(HDESTRUCTABLE d)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3C4C10
		jmp eax
	}
}

__declspec(naked) jReal jNATIVE jass::GetDestructableOccluderHeight(HDESTRUCTABLE d)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3C4BB0
		jmp eax
	}
}

__declspec(naked) jInteger jNATIVE jass::GetDestructableTypeId(HDESTRUCTABLE d)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3C47B0
		jmp eax
	}
}

__declspec(naked) jReal jNATIVE jass::GetDestructableX(HDESTRUCTABLE d)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3C47D0
		jmp eax
	}
}

__declspec(naked) jReal jNATIVE jass::GetDestructableY(HDESTRUCTABLE d)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3C4810
		jmp eax
	}
}

__declspec(naked) HUNIT jNATIVE jass::GetDetectedUnit()
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3BB4B0
		jmp eax
	}
}

__declspec(naked) HUNIT jNATIVE jass::GetDyingUnit()
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3BB410
		jmp eax
	}
}

__declspec(naked) HUNIT jNATIVE jass::GetEnemyBase()
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x2DDD20
		jmp eax
	}
}

__declspec(naked) HUNIT jNATIVE jass::GetEnemyExpansion()
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x2DD4F0
		jmp eax
	}
}

__declspec(naked) jInteger jNATIVE jass::GetEnemyPower()
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x2DC150
		jmp eax
	}
}

__declspec(naked) HUNIT jNATIVE jass::GetEnteringUnit()
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3BB6D0
		jmp eax
	}
}

__declspec(naked) HDESTRUCTABLE jNATIVE jass::GetEnumDestructable()
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3BB360
		jmp eax
	}
}

__declspec(naked) HITEM jNATIVE jass::GetEnumItem()
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3BB3A0
		jmp eax
	}
}

__declspec(naked) HPLAYER jNATIVE jass::GetEnumPlayer()
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3BB320
		jmp eax
	}
}

__declspec(naked) HUNIT jNATIVE jass::GetEnumUnit()
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3BB300
		jmp eax
	}
}

__declspec(naked) jReal jNATIVE jass::GetEventDamage()
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3C3C40
		jmp eax
	}
}

__declspec(naked) HUNIT jNATIVE jass::GetEventDamageSource()
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3C3C60
		jmp eax
	}
}

__declspec(naked) HPLAYER jNATIVE jass::GetEventDetectingPlayer()
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3C3CB0
		jmp eax
	}
}

__declspec(naked) HGAMESTATE jNATIVE jass::GetEventGameState()
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3C2020
		jmp eax
	}
}

__declspec(naked) jString jNATIVE jass::GetEventPlayerChatString()
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3C20B0
		jmp eax
	}
}

__declspec(naked) jString jNATIVE jass::GetEventPlayerChatStringMatched()
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3C2080
		jmp eax
	}
}

__declspec(naked) HPLAYERSTATE jNATIVE jass::GetEventPlayerState()
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3C2050
		jmp eax
	}
}

__declspec(naked) HUNIT jNATIVE jass::GetEventTargetUnit()
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3C3D00
		jmp eax
	}
}

__declspec(naked) HUNITSTATE jNATIVE jass::GetEventUnitState()
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3C3C10
		jmp eax
	}
}

__declspec(naked) HUNIT jNATIVE jass::GetExpansionFoe()
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x2E2E40
		jmp eax
	}
}

__declspec(naked) HUNIT jNATIVE jass::GetExpansionPeon()
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x2DD530
		jmp eax
	}
}

__declspec(naked) jInteger jNATIVE jass::GetExpansionX()
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x2E2DA0
		jmp eax
	}
}

__declspec(naked) jInteger jNATIVE jass::GetExpansionY()
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x2E2DF0
		jmp eax
	}
}

__declspec(naked) HTIMER jNATIVE jass::GetExpiredTimer()
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3C1D80
		jmp eax
	}
}

__declspec(naked) HDESTRUCTABLE jNATIVE jass::GetFilterDestructable()
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3BB380
		jmp eax
	}
}

__declspec(naked) HITEM jNATIVE jass::GetFilterItem()
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3BB3C0
		jmp eax
	}
}

__declspec(naked) HPLAYER jNATIVE jass::GetFilterPlayer()
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3BB340
		jmp eax
	}
}

__declspec(naked) HUNIT jNATIVE jass::GetFilterUnit()
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3BB2E0
		jmp eax
	}
}

__declspec(naked) jReal jNATIVE jass::GetFloatGameState(HFGAMESTATE whichFloatGameState)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3BC310
		jmp eax
	}
}

__declspec(naked) jInteger jNATIVE jass::GetFoodMade(jInteger unitId)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3B2E00
		jmp eax
	}
}

__declspec(naked) jInteger jNATIVE jass::GetFoodUsed(jInteger unitId)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3B2E10
		jmp eax
	}
}

__declspec(naked) HGAMEDIFFICULTY jNATIVE jass::GetGameDifficulty()
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3BAF20
		jmp eax
	}
}

__declspec(naked) HPLACEMENT jNATIVE jass::GetGamePlacement()
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3BAF00
		jmp eax
	}
}

__declspec(naked) HGAMESPEED jNATIVE jass::GetGameSpeed()
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3BAEC0
		jmp eax
	}
}

__declspec(naked) HGAMETYPE jNATIVE jass::GetGameTypeSelected()
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3BAE60
		jmp eax
	}
}

__declspec(naked) jInteger jNATIVE jass::GetGoldOwned()
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x2DE000
		jmp eax
	}
}

__declspec(naked) jInteger jNATIVE jass::GetHandleId(HHANDLE2 h)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3B2D00
		jmp eax
	}
}

__declspec(naked) jInteger jNATIVE jass::GetHeroAgi(HUNIT whichHero, jBoolean includeBonuses)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3C6850
		jmp eax
	}
}

__declspec(naked) jInteger jNATIVE jass::GetHeroId()
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x2DDF50
		jmp eax
	}
}

__declspec(naked) jInteger jNATIVE jass::GetHeroInt(HUNIT whichHero, jBoolean includeBonuses)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3C68C0
		jmp eax
	}
}

__declspec(naked) jInteger jNATIVE jass::GetHeroLevel(HUNIT whichHero)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3C6ED0
		jmp eax
	}
}

__declspec(naked) jInteger jNATIVE jass::GetHeroLevelAI()
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x2DE0E0
		jmp eax
	}
}

__declspec(naked) jString jNATIVE jass::GetHeroProperName(HUNIT whichHero)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3C6FA0
		jmp eax
	}
}

__declspec(naked) jInteger jNATIVE jass::GetHeroSkillPoints(HUNIT whichHero)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3C6780
		jmp eax
	}
}

__declspec(naked) jInteger jNATIVE jass::GetHeroStr(HUNIT whichHero, jBoolean includeBonuses)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3C67E0
		jmp eax
	}
}

__declspec(naked) jInteger jNATIVE jass::GetHeroXP(HUNIT whichHero)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3C6A10
		jmp eax
	}
}

__declspec(naked) jInteger jNATIVE jass::GetIntegerGameState(HIGAMESTATE whichIntegerGameState)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3BC380
		jmp eax
	}
}

__declspec(naked) jInteger jNATIVE jass::GetIssuedOrderId()
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3C2C80
		jmp eax
	}
}

__declspec(naked) jInteger jNATIVE jass::GetItemCharges(HITEM whichItem)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3C5050
		jmp eax
	}
}

__declspec(naked) jInteger jNATIVE jass::GetItemLevel(HITEM whichItem)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3C4E50
		jmp eax
	}
}

__declspec(naked) jString jNATIVE jass::GetItemName(HITEM whichItem)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3C4E90
		jmp eax
	}
}

__declspec(naked) HPLAYER jNATIVE jass::GetItemPlayer(HITEM whichItem)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3C4E10
		jmp eax
	}
}

__declspec(naked) HITEMTYPE jNATIVE jass::GetItemType(HITEM whichItem)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3C4E70
		jmp eax
	}
}

__declspec(naked) jInteger jNATIVE jass::GetItemTypeId(HITEM i)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3C4C60
		jmp eax
	}
}

__declspec(naked) jInteger jNATIVE jass::GetItemUserData(HITEM whichItem)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3C50D0
		jmp eax
	}
}

__declspec(naked) jReal jNATIVE jass::GetItemX(HITEM i)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3C4D90
		jmp eax
	}
}

__declspec(naked) jReal jNATIVE jass::GetItemY(HITEM i)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3C4DD0
		jmp eax
	}
}

__declspec(naked) HUNIT jNATIVE jass::GetKillingUnit()
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3C23F0
		jmp eax
	}
}

__declspec(naked) jInteger jNATIVE jass::GetLastCommand()
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x2E0450
		jmp eax
	}
}

__declspec(naked) jInteger jNATIVE jass::GetLastData()
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x2E0490
		jmp eax
	}
}

__declspec(naked) jInteger jNATIVE jass::GetLearnedSkill()
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3C2210
		jmp eax
	}
}

__declspec(naked) jInteger jNATIVE jass::GetLearnedSkillLevel()
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3C2250
		jmp eax
	}
}

__declspec(naked) HUNIT jNATIVE jass::GetLearningUnit()
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3C21B0
		jmp eax
	}
}

__declspec(naked) HUNIT jNATIVE jass::GetLeavingUnit()
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3BB6F0
		jmp eax
	}
}

__declspec(naked) HUNIT jNATIVE jass::GetLevelingUnit()
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3C2150
		jmp eax
	}
}

__declspec(naked) jReal jNATIVE jass::GetLightningColorA(HLIGHTNING whichBolt)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3B8310
		jmp eax
	}
}

__declspec(naked) jReal jNATIVE jass::GetLightningColorB(HLIGHTNING whichBolt)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3B8430
		jmp eax
	}
}

__declspec(naked) jReal jNATIVE jass::GetLightningColorG(HLIGHTNING whichBolt)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3B83D0
		jmp eax
	}
}

__declspec(naked) jReal jNATIVE jass::GetLightningColorR(HLIGHTNING whichBolt)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3B8370
		jmp eax
	}
}

__declspec(naked) HUNIT jNATIVE jass::GetLoadedUnit()
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3C2A00
		jmp eax
	}
}

__declspec(naked) HPLAYER jNATIVE jass::GetLocalPlayer()
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3BBB60
		jmp eax
	}
}

__declspec(naked) jInteger jNATIVE jass::GetLocalizedHotkey(jString source)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3B2D80
		jmp eax
	}
}

__declspec(naked) jString jNATIVE jass::GetLocalizedString(jString source)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3BACF0
		jmp eax
	}
}

__declspec(naked) jReal jNATIVE jass::GetLocationX(HLOCATION whichLocation)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3C0E10
		jmp eax
	}
}

__declspec(naked) jReal jNATIVE jass::GetLocationY(HLOCATION whichLocation)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3C0E30
		jmp eax
	}
}

__declspec(naked) jReal jNATIVE jass::GetLocationZ(HLOCATION whichLocation)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3C0E50
		jmp eax
	}
}

__declspec(naked) HITEM jNATIVE jass::GetManipulatedItem()
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3C2B00
		jmp eax
	}
}

__declspec(naked) HUNIT jNATIVE jass::GetManipulatingUnit()
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3C2A60
		jmp eax
	}
}

__declspec(naked) HUNIT jNATIVE jass::GetMegaTarget()
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x2DDD60
		jmp eax
	}
}

__declspec(naked) jInteger jNATIVE jass::GetMinesOwned()
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x2DDFD0
		jmp eax
	}
}

__declspec(naked) jInteger jNATIVE jass::GetNextExpansion()
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x2E2BC0
		jmp eax
	}
}

__declspec(naked) jString jNATIVE jass::GetObjectName(jInteger objectId)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3BB6B0
		jmp eax
	}
}

__declspec(naked) HLOCATION jNATIVE jass::GetOrderPointLoc()
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3D1FF0
		jmp eax
	}
}

__declspec(naked) jReal jNATIVE jass::GetOrderPointX()
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3C2D00
		jmp eax
	}
}

__declspec(naked) jReal jNATIVE jass::GetOrderPointY()
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3C2D50
		jmp eax
	}
}

__declspec(naked) HWIDGET jNATIVE jass::GetOrderTarget()
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3C2DE0
		jmp eax
	}
}

__declspec(naked) HDESTRUCTABLE jNATIVE jass::GetOrderTargetDestructable()
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3C2F10
		jmp eax
	}
}

__declspec(naked) HITEM jNATIVE jass::GetOrderTargetItem()
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3C3040
		jmp eax
	}
}

__declspec(naked) HUNIT jNATIVE jass::GetOrderTargetUnit()
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3C3170
		jmp eax
	}
}

__declspec(naked) HUNIT jNATIVE jass::GetOrderedUnit()
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3BB530
		jmp eax
	}
}

__declspec(naked) HPLAYER jNATIVE jass::GetOwningPlayer(HUNIT whichUnit)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3C8190
		jmp eax
	}
}

__declspec(naked) jBoolean jNATIVE jass::GetPlayerAlliance(HPLAYER sourcePlayer, HPLAYER otherPlayer, HALLIANCETYPE whichAllianceSetting)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3C9D70
		jmp eax
	}
}

__declspec(naked) HPLAYERCOLOR jNATIVE jass::GetPlayerColor(HPLAYER whichPlayer)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3C1240
		jmp eax
	}
}

__declspec(naked) HMAPCONTROL jNATIVE jass::GetPlayerController(HPLAYER whichPlayer)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3C12B0
		jmp eax
	}
}

__declspec(naked) jReal jNATIVE jass::GetPlayerHandicap(HPLAYER whichPlayer)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3C9E10
		jmp eax
	}
}

__declspec(naked) jReal jNATIVE jass::GetPlayerHandicapXP(HPLAYER whichPlayer)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3C9EC0
		jmp eax
	}
}

__declspec(naked) jInteger jNATIVE jass::GetPlayerId(HPLAYER whichPlayer)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3C9640
		jmp eax
	}
}

__declspec(naked) jString jNATIVE jass::GetPlayerName(HPLAYER whichPlayer)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3C0F60
		jmp eax
	}
}

__declspec(naked) HRACE jNATIVE jass::GetPlayerRace(HPLAYER whichPlayer)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3C9620
		jmp eax
	}
}

__declspec(naked) jInteger jNATIVE jass::GetPlayerScore(HPLAYER whichPlayer, HPLAYERSCORE whichPlayerScore)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3C9B70
		jmp eax
	}
}

__declspec(naked) jBoolean jNATIVE jass::GetPlayerSelectable(HPLAYER whichPlayer)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3C1290
		jmp eax
	}
}

__declspec(naked) HPLAYERSLOTSTATE jNATIVE jass::GetPlayerSlotState(HPLAYER whichPlayer)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3C12D0
		jmp eax
	}
}

__declspec(naked) jInteger jNATIVE jass::GetPlayerStartLocation(HPLAYER whichPlayer)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3C0FD0
		jmp eax
	}
}

__declspec(naked) jReal jNATIVE jass::GetPlayerStartLocationX(HPLAYER arg1)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3C0FF0
		jmp eax
	}
}

__declspec(naked) jReal jNATIVE jass::GetPlayerStartLocationY(HPLAYER arg1)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3C1020
		jmp eax
	}
}

__declspec(naked) jInteger jNATIVE jass::GetPlayerState(HPLAYER whichPlayer, HPLAYERSTATE whichPlayerState)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3C9B00
		jmp eax
	}
}

__declspec(naked) jInteger jNATIVE jass::GetPlayerStructureCount(HPLAYER whichPlayer, jBoolean includeIncomplete)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3C98C0
		jmp eax
	}
}

__declspec(naked) jInteger jNATIVE jass::GetPlayerTaxRate(HPLAYER sourcePlayer, HPLAYER otherPlayer, HPLAYERSTATE whichResource)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3C1150
		jmp eax
	}
}

__declspec(naked) jInteger jNATIVE jass::GetPlayerTeam(HPLAYER whichPlayer)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3C0F40
		jmp eax
	}
}

__declspec(naked) jInteger jNATIVE jass::GetPlayerTechCount(HPLAYER whichPlayer, jInteger techid, jBoolean specificonly)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3C97A0
		jmp eax
	}
}

__declspec(naked) jInteger jNATIVE jass::GetPlayerTechMaxAllowed(HPLAYER whichPlayer, jInteger techid)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3C9690
		jmp eax
	}
}

__declspec(naked) jBoolean jNATIVE jass::GetPlayerTechResearched(HPLAYER whichPlayer, jInteger techid, jBoolean specificonly)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3C9770
		jmp eax
	}
}

__declspec(naked) jInteger jNATIVE jass::GetPlayerTypedUnitCount(HPLAYER whichPlayer, jString unitName, jBoolean includeIncomplete, jBoolean includeUpgrades)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3C9850
		jmp eax
	}
}

__declspec(naked) jInteger jNATIVE jass::GetPlayerUnitCount(HPLAYER whichPlayer, jBoolean includeIncomplete)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3C9820
		jmp eax
	}
}

__declspec(naked) jInteger jNATIVE jass::GetPlayerUnitTypeCount(HPLAYER arg1, jInteger arg2)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x2E2B60
		jmp eax
	}
}

__declspec(naked) jInteger jNATIVE jass::GetPlayers()
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3BAE00
		jmp eax
	}
}

__declspec(naked) jInteger jNATIVE jass::GetRandomInt(jInteger lowBound, jInteger highBound)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3B3560
		jmp eax
	}
}

__declspec(naked) jReal jNATIVE jass::GetRandomReal(jReal lowBound, jReal highBound)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3B35A0
		jmp eax
	}
}

__declspec(naked) jReal jNATIVE jass::GetRectCenterX(HRECT whichRect)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3C18E0
		jmp eax
	}
}

__declspec(naked) jReal jNATIVE jass::GetRectCenterY(HRECT whichRect)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3C1910
		jmp eax
	}
}

__declspec(naked) jReal jNATIVE jass::GetRectMaxX(HRECT whichRect)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3C1980
		jmp eax
	}
}

__declspec(naked) jReal jNATIVE jass::GetRectMaxY(HRECT whichRect)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3C19A0
		jmp eax
	}
}

__declspec(naked) jReal jNATIVE jass::GetRectMinX(HRECT whichRect)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3C1940
		jmp eax
	}
}

__declspec(naked) jReal jNATIVE jass::GetRectMinY(HRECT whichRect)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3C1960
		jmp eax
	}
}

__declspec(naked) HUNIT jNATIVE jass::GetRescuer()
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3C2390
		jmp eax
	}
}

__declspec(naked) jInteger jNATIVE jass::GetResearched()
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3C2870
		jmp eax
	}
}

__declspec(naked) HUNIT jNATIVE jass::GetResearchingUnit()
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3BB4D0
		jmp eax
	}
}

__declspec(naked) jInteger jNATIVE jass::GetResourceAmount(HUNIT whichUnit)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3C78B0
		jmp eax
	}
}

__declspec(naked) HMAPDENSITY jNATIVE jass::GetResourceDensity()
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3BAF40
		jmp eax
	}
}

__declspec(naked) HUNIT jNATIVE jass::GetRevivableUnit()
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3C2290
		jmp eax
	}
}

__declspec(naked) HUNIT jNATIVE jass::GetRevivingUnit()
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3C22F0
		jmp eax
	}
}

__declspec(naked) jString jNATIVE jass::GetSaveBasicFilename()
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3C1F80
		jmp eax
	}
}

__declspec(naked) HUNIT jNATIVE jass::GetSellingUnit()
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3C2560
		jmp eax
	}
}

__declspec(naked) HITEM jNATIVE jass::GetSoldItem()
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3C25F0
		jmp eax
	}
}

__declspec(naked) HUNIT jNATIVE jass::GetSoldUnit()
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3C2750
		jmp eax
	}
}

__declspec(naked) jInteger jNATIVE jass::GetSoundDuration(HSOUND soundHandle)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3CCF20
		jmp eax
	}
}

__declspec(naked) jInteger jNATIVE jass::GetSoundFileDuration(jString musicFileName)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3B3E20
		jmp eax
	}
}

__declspec(naked) jBoolean jNATIVE jass::GetSoundIsLoading(HSOUND soundHandle)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3CCF60
		jmp eax
	}
}

__declspec(naked) jBoolean jNATIVE jass::GetSoundIsPlaying(HSOUND soundHandle)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3CCF40
		jmp eax
	}
}

__declspec(naked) HABILITY jNATIVE jass::GetSpellAbility()
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3C3380
		jmp eax
	}
}

__declspec(naked) jInteger jNATIVE jass::GetSpellAbilityId()
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3C32A0
		jmp eax
	}
}

__declspec(naked) HUNIT jNATIVE jass::GetSpellAbilityUnit()
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3C3470
		jmp eax
	}
}

__declspec(naked) HDESTRUCTABLE jNATIVE jass::GetSpellTargetDestructable()
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3C3760
		jmp eax
	}
}

__declspec(naked) HITEM jNATIVE jass::GetSpellTargetItem()
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3C38F0
		jmp eax
	}
}

__declspec(naked) HLOCATION jNATIVE jass::GetSpellTargetLoc()
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3D2090
		jmp eax
	}
}

__declspec(naked) HUNIT jNATIVE jass::GetSpellTargetUnit()
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3C3A80
		jmp eax
	}
}

__declspec(naked) jReal jNATIVE jass::GetSpellTargetX()
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3C3580
		jmp eax
	}
}

__declspec(naked) jReal jNATIVE jass::GetSpellTargetY()
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3C3670
		jmp eax
	}
}

__declspec(naked) HSTARTLOCPRIO jNATIVE jass::GetStartLocPrio(jInteger whichStartLoc, jInteger prioSlotIndex)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3BB030
		jmp eax
	}
}

__declspec(naked) jInteger jNATIVE jass::GetStartLocPrioSlot(jInteger whichStartLoc, jInteger prioSlotIndex)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3BB000
		jmp eax
	}
}

__declspec(naked) HLOCATION jNATIVE jass::GetStartLocationLoc(jInteger whichStartLocation)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3D04B0
		jmp eax
	}
}

__declspec(naked) jReal jNATIVE jass::GetStartLocationX(jInteger whichStartLocation)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3BB060
		jmp eax
	}
}

__declspec(naked) jReal jNATIVE jass::GetStartLocationY(jInteger whichStartLocation)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3BB080
		jmp eax
	}
}

__declspec(naked) jBoolean jNATIVE jass::GetStoredBoolean(HGAMECACHE cache, jString missionKey, jString key)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3CA920
		jmp eax
	}
}

__declspec(naked) jInteger jNATIVE jass::GetStoredInteger(HGAMECACHE cache, jString missionKey, jString key)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3CA870
		jmp eax
	}
}

__declspec(naked) jReal jNATIVE jass::GetStoredReal(HGAMECACHE cache, jString missionKey, jString key)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3CA8C0
		jmp eax
	}
}

__declspec(naked) jString jNATIVE jass::GetStoredString(HGAMECACHE cache, jString missionKey, jString key)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3CAA40
		jmp eax
	}
}

__declspec(naked) HUNIT jNATIVE jass::GetSummonedUnit()
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3C2950
		jmp eax
	}
}

__declspec(naked) HUNIT jNATIVE jass::GetSummoningUnit()
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3C28F0
		jmp eax
	}
}

__declspec(naked) jInteger jNATIVE jass::GetTeams()
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3BADE0
		jmp eax
	}
}

__declspec(naked) jInteger jNATIVE jass::GetTerrainCliffLevel(jReal x, jReal y)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3B4190
		jmp eax
	}
}

__declspec(naked) jInteger jNATIVE jass::GetTerrainType(jReal x, jReal y)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3BCED0
		jmp eax
	}
}

__declspec(naked) jInteger jNATIVE jass::GetTerrainVariance(jReal x, jReal y)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3B4250
		jmp eax
	}
}

__declspec(naked) jReal jNATIVE jass::GetTimeOfDayScale()
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3BC4B0
		jmp eax
	}
}

__declspec(naked) HPLAYER jNATIVE jass::GetTournamentFinishNowPlayer()
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3C1F00
		jmp eax
	}
}

__declspec(naked) jInteger jNATIVE jass::GetTournamentFinishNowRule()
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3C1ED0
		jmp eax
	}
}

__declspec(naked) jReal jNATIVE jass::GetTournamentFinishSoonTimeRemaining()
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3C1EA0
		jmp eax
	}
}

__declspec(naked) jInteger jNATIVE jass::GetTournamentScore(HPLAYER whichPlayer)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3C1F60
		jmp eax
	}
}

__declspec(naked) jInteger jNATIVE jass::GetTownUnitCount(jInteger arg1, jInteger arg2, jBoolean arg3)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x2DD0C0
		jmp eax
	}
}

__declspec(naked) HUNIT jNATIVE jass::GetTrainedUnit()
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3C2500
		jmp eax
	}
}

__declspec(naked) jInteger jNATIVE jass::GetTrainedUnitType()
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3C2450
		jmp eax
	}
}

__declspec(naked) HUNIT jNATIVE jass::GetTransportUnit()
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3C29A0
		jmp eax
	}
}

__declspec(naked) HDESTRUCTABLE jNATIVE jass::GetTriggerDestructable()
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3C1D20
		jmp eax
	}
}

__declspec(naked) jInteger jNATIVE jass::GetTriggerEvalCount(jTrigger whichTrigger)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3C1CE0
		jmp eax
	}
}

__declspec(naked) HEVENTID jNATIVE jass::GetTriggerEventId()
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3BB2C0
		jmp eax
	}
}

__declspec(naked) jInteger jNATIVE jass::GetTriggerExecCount(jTrigger whichTrigger)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3C1D00
		jmp eax
	}
}

__declspec(naked) HPLAYER jNATIVE jass::GetTriggerPlayer()
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3BB280
		jmp eax
	}
}

__declspec(naked) HUNIT jNATIVE jass::GetTriggerUnit()
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3BB240
		jmp eax
	}
}

__declspec(naked) HWIDGET jNATIVE jass::GetTriggerWidget()
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3BB260
		jmp eax
	}
}

__declspec(naked) HREGION jNATIVE jass::GetTriggeringRegion()
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3C3D50
		jmp eax
	}
}

__declspec(naked) HTRACKABLE jNATIVE jass::GetTriggeringTrackable()
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3C3DA0
		jmp eax
	}
}

__declspec(naked) jTrigger jNATIVE jass::GetTriggeringTrigger()
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3BB2A0
		jmp eax
	}
}

__declspec(naked) jInteger jNATIVE jass::GetUnitAbilityLevel(HUNIT whichUnit, jInteger abilcode)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3C7290
		jmp eax
	}
}

__declspec(naked) jReal jNATIVE jass::GetUnitAcquireRange(HUNIT whichUnit)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3C5D10
		jmp eax
	}
}

__declspec(naked) jInteger jNATIVE jass::GetUnitBuildTime(jInteger arg1)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x2DD190
		jmp eax
	}
}

__declspec(naked) jInteger jNATIVE jass::GetUnitCount(jInteger arg1)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x2DD050
		jmp eax
	}
}

__declspec(naked) jInteger jNATIVE jass::GetUnitCountDone(jInteger arg1)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x2DD010
		jmp eax
	}
}

__declspec(naked) jInteger jNATIVE jass::GetUnitCurrentOrder(HUNIT whichUnit)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3C7780
		jmp eax
	}
}

__declspec(naked) jReal jNATIVE jass::GetUnitDefaultAcquireRange(HUNIT whichUnit)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3C5DC0
		jmp eax
	}
}

__declspec(naked) jReal jNATIVE jass::GetUnitDefaultFlyHeight(HUNIT whichUnit)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3C5E50
		jmp eax
	}
}

__declspec(naked) jReal jNATIVE jass::GetUnitDefaultMoveSpeed(HUNIT whichUnit)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3C5870
		jmp eax
	}
}

__declspec(naked) jReal jNATIVE jass::GetUnitDefaultPropWindow(HUNIT whichUnit)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3C5E20
		jmp eax
	}
}

__declspec(naked) jReal jNATIVE jass::GetUnitDefaultTurnSpeed(HUNIT whichUnit)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3C5DF0
		jmp eax
	}
}

__declspec(naked) jReal jNATIVE jass::GetUnitFacing(HUNIT whichUnit)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3C5790
		jmp eax
	}
}

__declspec(naked) jReal jNATIVE jass::GetUnitFlyHeight(HUNIT whichUnit)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3C5DA0
		jmp eax
	}
}

__declspec(naked) jInteger jNATIVE jass::GetUnitFoodMade(HUNIT whichUnit)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3C5460
		jmp eax
	}
}

__declspec(naked) jInteger jNATIVE jass::GetUnitFoodUsed(HUNIT whichUnit)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3C5440
		jmp eax
	}
}

__declspec(naked) jInteger jNATIVE jass::GetUnitGoldCost(jInteger arg1)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x2DD1E0
		jmp eax
	}
}

__declspec(naked) jInteger jNATIVE jass::GetUnitLevel(HUNIT whichUnit)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3C6F30
		jmp eax
	}
}

__declspec(naked) HLOCATION jNATIVE jass::GetUnitLoc(HUNIT whichUnit)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3D2AE0
		jmp eax
	}
}

__declspec(naked) jReal jNATIVE jass::GetUnitMoveSpeed(HUNIT whichUnit)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3C5810
		jmp eax
	}
}

__declspec(naked) jString jNATIVE jass::GetUnitName(HUNIT whichUnit)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3C5950
		jmp eax
	}
}

__declspec(naked) jInteger jNATIVE jass::GetUnitPointValue(HUNIT whichUnit)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3C5E80
		jmp eax
	}
}

__declspec(naked) jInteger jNATIVE jass::GetUnitPointValueByType(jInteger unitType)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3B2E20
		jmp eax
	}
}

__declspec(naked) jReal jNATIVE jass::GetUnitPropWindow(HUNIT whichUnit)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3C5D70
		jmp eax
	}
}

__declspec(naked) HRACE jNATIVE jass::GetUnitRace(HUNIT whichUnit)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3C5930
		jmp eax
	}
}

__declspec(naked) HDESTRUCTABLE jNATIVE jass::GetUnitRallyDestructable(HUNIT whichUnit)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3C5690
		jmp eax
	}
}

__declspec(naked) HLOCATION jNATIVE jass::GetUnitRallyPoint(HUNIT whichUnit)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3D2B40
		jmp eax
	}
}

__declspec(naked) HUNIT jNATIVE jass::GetUnitRallyUnit(HUNIT whichUnit)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3C5590
		jmp eax
	}
}

__declspec(naked) jReal jNATIVE jass::GetUnitState(HUNIT whichUnit, HUNITSTATE whichUnitState)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3C5400
		jmp eax
	}
}

__declspec(naked) jReal jNATIVE jass::GetUnitTurnSpeed(HUNIT whichUnit)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3C5D40
		jmp eax
	}
}

__declspec(naked) jInteger jNATIVE jass::GetUnitTypeId(HUNIT whichUnit)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3C5910
		jmp eax
	}
}

__declspec(naked) jInteger jNATIVE jass::GetUnitUserData(HUNIT whichUnit)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3C94F0
		jmp eax
	}
}

__declspec(naked) jInteger jNATIVE jass::GetUnitWoodCost(jInteger arg1)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x2DD240
		jmp eax
	}
}

__declspec(naked) jReal jNATIVE jass::GetUnitX(HUNIT whichUnit)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3C5510
		jmp eax
	}
}

__declspec(naked) jReal jNATIVE jass::GetUnitY(HUNIT whichUnit)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3C5550
		jmp eax
	}
}

__declspec(naked) jInteger jNATIVE jass::GetUpgradeGoldCost(jInteger arg1)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x2DD2A0
		jmp eax
	}
}

__declspec(naked) jInteger jNATIVE jass::GetUpgradeLevel(jInteger arg1)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x2DD130
		jmp eax
	}
}

__declspec(naked) jInteger jNATIVE jass::GetUpgradeWoodCost(jInteger arg1)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x2DD2C0
		jmp eax
	}
}

__declspec(naked) jReal jNATIVE jass::GetWidgetLife(HWIDGET whichWidget)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3C4660
		jmp eax
	}
}

__declspec(naked) jReal jNATIVE jass::GetWidgetX(HWIDGET whichWidget)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3C46B0
		jmp eax
	}
}

__declspec(naked) jReal jNATIVE jass::GetWidgetY(HWIDGET whichWidget)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3C46F0
		jmp eax
	}
}

__declspec(naked) HPLAYER jNATIVE jass::GetWinningPlayer()
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3BB3E0
		jmp eax
	}
}

__declspec(naked) HRECT jNATIVE jass::GetWorldBounds()
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3D0D60
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::GroupAddUnit(HGROUP whichGroup, HUNIT whichUnit)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3C3FC0
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::GroupClear(HGROUP whichGroup)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3C4020
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::GroupEnumUnitsInRange(HGROUP whichGroup, jReal x, jReal y, jReal radius, HBOOLEXPR filter)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3C41A0
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::GroupEnumUnitsInRangeCounted(HGROUP whichGroup, jReal x, jReal y, jReal radius, HBOOLEXPR filter, jInteger countLimit)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3C4230
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::GroupEnumUnitsInRangeOfLoc(HGROUP whichGroup, HLOCATION whichLocation, jReal radius, HBOOLEXPR filter)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3C41E0
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::GroupEnumUnitsInRangeOfLocCounted(HGROUP whichGroup, HLOCATION whichLocation, jReal radius, HBOOLEXPR filter, jInteger countLimit)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3C4270
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::GroupEnumUnitsInRect(HGROUP whichGroup, HRECT r, HBOOLEXPR filter)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3C40E0
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::GroupEnumUnitsInRectCounted(HGROUP whichGroup, HRECT r, HBOOLEXPR filter, jInteger countLimit)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3C4140
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::GroupEnumUnitsOfPlayer(HGROUP whichGroup, HPLAYER whichPlayer, HBOOLEXPR filter)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3C42C0
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::GroupEnumUnitsOfType(HGROUP whichGroup, jString unitname, HBOOLEXPR filter)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3C4040
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::GroupEnumUnitsOfTypeCounted(HGROUP whichGroup, jString unitname, HBOOLEXPR filter, jInteger countLimit)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3C4090
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::GroupEnumUnitsSelected(HGROUP whichGroup, HPLAYER whichPlayer, HBOOLEXPR filter)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3CE590
		jmp eax
	}
}

__declspec(naked) jBoolean jNATIVE jass::GroupImmediateOrder(HGROUP whichGroup, jString order)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3C4320
		jmp eax
	}
}

__declspec(naked) jBoolean jNATIVE jass::GroupImmediateOrderById(HGROUP whichGroup, jInteger order)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3C4300
		jmp eax
	}
}

__declspec(naked) jBoolean jNATIVE jass::GroupPointOrder(HGROUP whichGroup, jString order, jReal x, jReal y)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3C4370
		jmp eax
	}
}

__declspec(naked) jBoolean jNATIVE jass::GroupPointOrderById(HGROUP whichGroup, jInteger order, jReal x, jReal y)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3C4340
		jmp eax
	}
}

__declspec(naked) jBoolean jNATIVE jass::GroupPointOrderByIdLoc(HGROUP whichGroup, jInteger order, HLOCATION whichLocation)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3C4390
		jmp eax
	}
}

__declspec(naked) jBoolean jNATIVE jass::GroupPointOrderLoc(HGROUP whichGroup, jString order, HLOCATION whichLocation)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3C43E0
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::GroupRemoveUnit(HGROUP whichGroup, HUNIT whichUnit)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3C3FF0
		jmp eax
	}
}

__declspec(naked) jBoolean jNATIVE jass::GroupTargetOrder(HGROUP whichGroup, jString order, HWIDGET targetWidget)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3C4440
		jmp eax
	}
}

__declspec(naked) jBoolean jNATIVE jass::GroupTargetOrderById(HGROUP whichGroup, jInteger order, HWIDGET targetWidget)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3C4400
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::GroupTimedLife(jBoolean arg1)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x2E2D60
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::HarvestGold(jInteger arg1, jInteger arg2)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x2DD5E0
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::HarvestWood(jInteger arg1, jInteger arg2)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x2DD630
		jmp eax
	}
}

__declspec(naked) jBoolean jNATIVE jass::HaveSavedBoolean(HHASHTABLE table, jInteger parentKey, jInteger childKey)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3CB140
		jmp eax
	}
}

__declspec(naked) jBoolean jNATIVE jass::HaveSavedHandle(HHASHTABLE table, jInteger parentKey, jInteger childKey)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3CB1C0
		jmp eax
	}
}

__declspec(naked) jBoolean jNATIVE jass::HaveSavedInteger(HHASHTABLE table, jInteger parentKey, jInteger childKey)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3CB0C0
		jmp eax
	}
}

__declspec(naked) jBoolean jNATIVE jass::HaveSavedReal(HHASHTABLE table, jInteger parentKey, jInteger childKey)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3CB100
		jmp eax
	}
}

__declspec(naked) jBoolean jNATIVE jass::HaveSavedString(HHASHTABLE table, jInteger parentKey, jInteger childKey)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3CB180
		jmp eax
	}
}

__declspec(naked) jBoolean jNATIVE jass::HaveStoredBoolean(HGAMECACHE cache, jString missionKey, jString key)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3CAFD0
		jmp eax
	}
}

__declspec(naked) jBoolean jNATIVE jass::HaveStoredInteger(HGAMECACHE cache, jString missionKey, jString key)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3CAF30
		jmp eax
	}
}

__declspec(naked) jBoolean jNATIVE jass::HaveStoredReal(HGAMECACHE cache, jString missionKey, jString key)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3CAF80
		jmp eax
	}
}

__declspec(naked) jBoolean jNATIVE jass::HaveStoredString(HGAMECACHE cache, jString missionKey, jString key)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3CB070
		jmp eax
	}
}

__declspec(naked) jBoolean jNATIVE jass::HaveStoredUnit(HGAMECACHE cache, jString missionKey, jString key)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3CB020
		jmp eax
	}
}

__declspec(naked) jReal jNATIVE jass::I2R(jInteger i)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3B2CC0
		jmp eax
	}
}

__declspec(naked) jString jNATIVE jass::I2S(jInteger i)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3BAAA0
		jmp eax
	}
}

__declspec(naked) jInteger jNATIVE jass::IgnoredUnits(jInteger arg1)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x2DCE80
		jmp eax
	}
}

__declspec(naked) jInteger jNATIVE jass::IncUnitAbilityLevel(HUNIT whichUnit, jInteger abilcode)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3C7130
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::InitAssault()
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x2DD990
		jmp eax
	}
}

__declspec(naked) HGAMECACHE jNATIVE jass::InitGameCache(jString campaignFile)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3D2CC0
		jmp eax
	}
}

__declspec(naked) HHASHTABLE jNATIVE jass::InitHashtable()
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3D2DF0
		jmp eax
	}
}

__declspec(naked) jBoolean jNATIVE jass::IsCineFilterDisplayed()
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3B5150
		jmp eax
	}
}

__declspec(naked) jBoolean jNATIVE jass::IsDestructableInvulnerable(HDESTRUCTABLE d)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3C4790
		jmp eax
	}
}

__declspec(naked) jBoolean jNATIVE jass::IsFogEnabled()
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3BB200
		jmp eax
	}
}

__declspec(naked) jBoolean jNATIVE jass::IsFogMaskEnabled()
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3BB230
		jmp eax
	}
}

__declspec(naked) jBoolean jNATIVE jass::IsFoggedToPlayer(jReal x, jReal y, HPLAYER whichPlayer)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3C9980
		jmp eax
	}
}

__declspec(naked) jBoolean jNATIVE jass::IsGameTypeSupported(HGAMETYPE whichGameType)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3BAE40
		jmp eax
	}
}

__declspec(naked) jBoolean jNATIVE jass::IsHeroUnitId(jInteger unitId)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3B2E90
		jmp eax
	}
}

__declspec(naked) jBoolean jNATIVE jass::IsItemIdPawnable(jInteger itemId)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3B2DF0
		jmp eax
	}
}

__declspec(naked) jBoolean jNATIVE jass::IsItemIdPowerup(jInteger itemId)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3B2DD0
		jmp eax
	}
}

__declspec(naked) jBoolean jNATIVE jass::IsItemIdSellable(jInteger itemId)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3B2DE0
		jmp eax
	}
}

__declspec(naked) jBoolean jNATIVE jass::IsItemInvulnerable(HITEM whichItem)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3C4F00
		jmp eax
	}
}

__declspec(naked) jBoolean jNATIVE jass::IsItemOwned(HITEM whichItem)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3C4F90
		jmp eax
	}
}

__declspec(naked) jBoolean jNATIVE jass::IsItemPawnable(HITEM whichItem)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3C5010
		jmp eax
	}
}

__declspec(naked) jBoolean jNATIVE jass::IsItemPowerup(HITEM whichItem)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3C4FD0
		jmp eax
	}
}

__declspec(naked) jBoolean jNATIVE jass::IsItemSellable(HITEM whichItem)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3C4FF0
		jmp eax
	}
}

__declspec(naked) jBoolean jNATIVE jass::IsItemVisible(HITEM whichItem)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3C4F70
		jmp eax
	}
}

__declspec(naked) jBoolean jNATIVE jass::IsLeaderboardDisplayed(HLEADERBOARD lb)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3CC220
		jmp eax
	}
}

__declspec(naked) jBoolean jNATIVE jass::IsLocationFoggedToPlayer(HLOCATION whichLocation, HPLAYER whichPlayer)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3C99D0
		jmp eax
	}
}

__declspec(naked) jBoolean jNATIVE jass::IsLocationInRegion(HREGION whichRegion, HLOCATION whichLocation)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3C16B0
		jmp eax
	}
}

__declspec(naked) jBoolean jNATIVE jass::IsLocationMaskedToPlayer(HLOCATION whichLocation, HPLAYER whichPlayer)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3C9A60
		jmp eax
	}
}

__declspec(naked) jBoolean jNATIVE jass::IsLocationVisibleToPlayer(HLOCATION whichLocation, HPLAYER whichPlayer)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3C9940
		jmp eax
	}
}

__declspec(naked) jBoolean jNATIVE jass::IsMapFlagSet(HMAPFLAG whichMapFlag)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3BAEA0
		jmp eax
	}
}

__declspec(naked) jBoolean jNATIVE jass::IsMaskedToPlayer(jReal x, jReal y, HPLAYER whichPlayer)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3C9A10
		jmp eax
	}
}

__declspec(naked) jBoolean jNATIVE jass::IsMultiboardDisplayed(HMULTIBOARD lb)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3CC690
		jmp eax
	}
}

__declspec(naked) jBoolean jNATIVE jass::IsMultiboardMinimized(HMULTIBOARD lb)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3CC6D0
		jmp eax
	}
}

__declspec(naked) jBoolean jNATIVE jass::IsNoDefeatCheat()
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3BC8F0
		jmp eax
	}
}

__declspec(naked) jBoolean jNATIVE jass::IsNoVictoryCheat()
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3BC8C0
		jmp eax
	}
}

__declspec(naked) jBoolean jNATIVE jass::IsPlayerAlly(HPLAYER whichPlayer, HPLAYER otherPlayer)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3C9530
		jmp eax
	}
}

__declspec(naked) jBoolean jNATIVE jass::IsPlayerEnemy(HPLAYER whichPlayer, HPLAYER otherPlayer)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3C9580
		jmp eax
	}
}

__declspec(naked) jBoolean jNATIVE jass::IsPlayerInForce(HPLAYER whichPlayer, HFORCE whichForce)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3C95D0
		jmp eax
	}
}

__declspec(naked) jBoolean jNATIVE jass::IsPlayerObserver(HPLAYER whichPlayer)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3C9600
		jmp eax
	}
}

__declspec(naked) jBoolean jNATIVE jass::IsPlayerRacePrefSet(HPLAYER whichPlayer, HRACEPREFERENCE pref)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3C1260
		jmp eax
	}
}

__declspec(naked) jBoolean jNATIVE jass::IsPointBlighted(jReal x, jReal y)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3B4550
		jmp eax
	}
}

__declspec(naked) jBoolean jNATIVE jass::IsPointInRegion(HREGION whichRegion, jReal x, jReal y)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3C1690
		jmp eax
	}
}

__declspec(naked) jBoolean jNATIVE jass::IsQuestCompleted(HQUEST whichQuest)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3CBCC0
		jmp eax
	}
}

__declspec(naked) jBoolean jNATIVE jass::IsQuestDiscovered(HQUEST whichQuest)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3CBCE0
		jmp eax
	}
}

__declspec(naked) jBoolean jNATIVE jass::IsQuestEnabled(HQUEST whichQuest)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3CBD20
		jmp eax
	}
}

__declspec(naked) jBoolean jNATIVE jass::IsQuestFailed(HQUEST whichQuest)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3CBD00
		jmp eax
	}
}

__declspec(naked) jBoolean jNATIVE jass::IsQuestItemCompleted(HQUESTITEM whichQuestItem)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3CBD90
		jmp eax
	}
}

__declspec(naked) jBoolean jNATIVE jass::IsQuestRequired(HQUEST whichQuest)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3CBCA0
		jmp eax
	}
}

__declspec(naked) jBoolean jNATIVE jass::IsSuspendedXP(HUNIT whichHero)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3C6E70
		jmp eax
	}
}

__declspec(naked) jBoolean jNATIVE jass::IsTerrainPathable(jReal x, jReal y, HPATHINGTYPE t)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3B42D0
		jmp eax
	}
}

__declspec(naked) jBoolean jNATIVE jass::IsTimerDialogDisplayed(HTIMERDIALOG whichDialog)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3CBF70
		jmp eax
	}
}

__declspec(naked) jBoolean jNATIVE jass::IsTowered(HUNIT arg1)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x2E0950
		jmp eax
	}
}

__declspec(naked) jBoolean jNATIVE jass::IsTriggerEnabled(jTrigger whichTrigger)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3C1C80
		jmp eax
	}
}

__declspec(naked) jBoolean jNATIVE jass::IsTriggerWaitOnSleeps(jTrigger whichTrigger)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3C1CC0
		jmp eax
	}
}

__declspec(naked) jBoolean jNATIVE jass::IsUnit(HUNIT whichUnit, HUNIT whichSpecifiedUnit)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3C8020
		jmp eax
	}
}

__declspec(naked) jBoolean jNATIVE jass::IsUnitAlly(HUNIT whichUnit, HPLAYER whichPlayer)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3C7A70
		jmp eax
	}
}

__declspec(naked) jBoolean jNATIVE jass::IsUnitDetected(HUNIT whichUnit, HPLAYER whichPlayer)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3C7C80
		jmp eax
	}
}

__declspec(naked) jBoolean jNATIVE jass::IsUnitEnemy(HUNIT whichUnit, HPLAYER whichPlayer)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3C7AD0
		jmp eax
	}
}

__declspec(naked) jBoolean jNATIVE jass::IsUnitFogged(HUNIT whichUnit, HPLAYER whichPlayer)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3C7D00
		jmp eax
	}
}

__declspec(naked) jBoolean jNATIVE jass::IsUnitHidden(HUNIT whichUnit)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3C7B30
		jmp eax
	}
}

__declspec(naked) jBoolean jNATIVE jass::IsUnitIdType(jInteger unitId, HUNITTYPE whichUnitType)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3B7F60
		jmp eax
	}
}

__declspec(naked) jBoolean jNATIVE jass::IsUnitIllusion(HUNIT whichUnit)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3C7B50
		jmp eax
	}
}

__declspec(naked) jBoolean jNATIVE jass::IsUnitInForce(HUNIT whichUnit, HFORCE whichForce)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3C79C0
		jmp eax
	}
}

__declspec(naked) jBoolean jNATIVE jass::IsUnitInGroup(HUNIT whichUnit, HGROUP whichGroup)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3C7A00
		jmp eax
	}
}

__declspec(naked) jBoolean jNATIVE jass::IsUnitInRange(HUNIT whichUnit, HUNIT otherUnit, jReal distance)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3C8090
		jmp eax
	}
}

__declspec(naked) jBoolean jNATIVE jass::IsUnitInRangeLoc(HUNIT whichUnit, HLOCATION whichLocation, jReal distance)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3C8140
		jmp eax
	}
}

__declspec(naked) jBoolean jNATIVE jass::IsUnitInRangeXY(HUNIT whichUnit, jReal x, jReal y, jReal distance)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3C80E0
		jmp eax
	}
}

__declspec(naked) jBoolean jNATIVE jass::IsUnitInRegion(HREGION whichRegion, HUNIT whichUnit)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3C1660
		jmp eax
	}
}

__declspec(naked) jBoolean jNATIVE jass::IsUnitInTransport(HUNIT whichUnit, HUNIT whichTransport)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3C7B70
		jmp eax
	}
}

__declspec(naked) jBoolean jNATIVE jass::IsUnitInvisible(HUNIT whichUnit, HPLAYER whichPlayer)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3C7CC0
		jmp eax
	}
}

__declspec(naked) jBoolean jNATIVE jass::IsUnitLoaded(HUNIT whichUnit)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3C7BA0
		jmp eax
	}
}

__declspec(naked) jBoolean jNATIVE jass::IsUnitMasked(HUNIT whichUnit, HPLAYER whichPlayer)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3C7D80
		jmp eax
	}
}

__declspec(naked) jBoolean jNATIVE jass::IsUnitOwnedByPlayer(HUNIT whichUnit, HPLAYER whichPlayer)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3C7A30
		jmp eax
	}
}

__declspec(naked) jBoolean jNATIVE jass::IsUnitPaused(HUNIT whichHero)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3C73A0
		jmp eax
	}
}

__declspec(naked) jBoolean jNATIVE jass::IsUnitRace(HUNIT whichUnit, HRACE whichRace)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3C7E60
		jmp eax
	}
}

__declspec(naked) jBoolean jNATIVE jass::IsUnitSelected(HUNIT whichUnit, HPLAYER whichPlayer)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3C7E00
		jmp eax
	}
}

__declspec(naked) jBoolean jNATIVE jass::IsUnitType(HUNIT whichUnit, HUNITTYPE whichUnitType)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3C7E90
		jmp eax
	}
}

__declspec(naked) jBoolean jNATIVE jass::IsUnitVisible(HUNIT whichUnit, HPLAYER whichPlayer)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3C7AF0
		jmp eax
	}
}

__declspec(naked) jBoolean jNATIVE jass::IsVisibleToPlayer(jReal x, jReal y, HPLAYER whichPlayer)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3C98F0
		jmp eax
	}
}

__declspec(naked) jBoolean jNATIVE jass::IssueBuildOrder(HUNIT whichPeon, jString unitToBuild, jReal x, jReal y)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3C8E80
		jmp eax
	}
}

__declspec(naked) jBoolean jNATIVE jass::IssueBuildOrderById(HUNIT whichPeon, jInteger unitId, jReal x, jReal y)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3C8BE0
		jmp eax
	}
}

__declspec(naked) jBoolean jNATIVE jass::IssueImmediateOrder(HUNIT whichUnit, jString order)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3C8D80
		jmp eax
	}
}

__declspec(naked) jBoolean jNATIVE jass::IssueImmediateOrderById(HUNIT whichUnit, jInteger order)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3C8900
		jmp eax
	}
}

__declspec(naked) jBoolean jNATIVE jass::IssueInstantPointOrder(HUNIT whichUnit, jString order, jReal x, jReal y, HWIDGET instantTargetWidget)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3C8E40
		jmp eax
	}
}

__declspec(naked) jBoolean jNATIVE jass::IssueInstantPointOrderById(HUNIT whichUnit, jInteger order, jReal x, jReal y, HWIDGET instantTargetWidget)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3C8A20
		jmp eax
	}
}

__declspec(naked) jBoolean jNATIVE jass::IssueInstantTargetOrder(HUNIT whichUnit, jString order, HWIDGET targetWidget, HWIDGET instantTargetWidget)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3C8E60
		jmp eax
	}
}

__declspec(naked) jBoolean jNATIVE jass::IssueInstantTargetOrderById(HUNIT whichUnit, jInteger order, HWIDGET targetWidget, HWIDGET instantTargetWidget)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3C8AB0
		jmp eax
	}
}

__declspec(naked) jBoolean jNATIVE jass::IssueNeutralImmediateOrder(HPLAYER forWhichPlayer, HUNIT neutralStructure, jString unitToBuild)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3C8EA0
		jmp eax
	}
}

__declspec(naked) jBoolean jNATIVE jass::IssueNeutralImmediateOrderById(HPLAYER forWhichPlayer, HUNIT neutralStructure, jInteger unitId)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3C8CA0
		jmp eax
	}
}

__declspec(naked) jBoolean jNATIVE jass::IssueNeutralPointOrder(HPLAYER forWhichPlayer, HUNIT neutralStructure, jString unitToBuild, jReal x, jReal y)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3C8EC0
		jmp eax
	}
}

__declspec(naked) jBoolean jNATIVE jass::IssueNeutralPointOrderById(HPLAYER forWhichPlayer, HUNIT neutralStructure, jInteger unitId, jReal x, jReal y)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3C8CE0
		jmp eax
	}
}

__declspec(naked) jBoolean jNATIVE jass::IssueNeutralTargetOrder(HPLAYER forWhichPlayer, HUNIT neutralStructure, jString unitToBuild, HWIDGET target)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3C8EE0
		jmp eax
	}
}

__declspec(naked) jBoolean jNATIVE jass::IssueNeutralTargetOrderById(HPLAYER forWhichPlayer, HUNIT neutralStructure, jInteger unitId, HWIDGET target)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3C8D30
		jmp eax
	}
}

__declspec(naked) jBoolean jNATIVE jass::IssuePointOrder(HUNIT whichUnit, jString order, jReal x, jReal y)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3C8DA0
		jmp eax
	}
}

__declspec(naked) jBoolean jNATIVE jass::IssuePointOrderById(HUNIT whichUnit, jInteger order, jReal x, jReal y)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3C8940
		jmp eax
	}
}

__declspec(naked) jBoolean jNATIVE jass::IssuePointOrderByIdLoc(HUNIT whichUnit, jInteger order, HLOCATION whichLocation)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3C8980
		jmp eax
	}
}

__declspec(naked) jBoolean jNATIVE jass::IssuePointOrderLoc(HUNIT whichUnit, jString order, HLOCATION whichLocation)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3C8DC0
		jmp eax
	}
}

__declspec(naked) jBoolean jNATIVE jass::IssueTargetOrder(HUNIT whichUnit, jString order, HWIDGET targetWidget)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3C8E20
		jmp eax
	}
}

__declspec(naked) jBoolean jNATIVE jass::IssueTargetOrderById(HUNIT whichUnit, jInteger order, HWIDGET targetWidget)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3C89D0
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::ItemPoolAddItemType(HITEMPOOL whichItemPool, jInteger itemId, jReal weight)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3CB6C0
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::ItemPoolRemoveItemType(HITEMPOOL whichItemPool, jInteger itemId)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3CB6E0
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::KillDestructable(HDESTRUCTABLE d)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3C4750
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::KillSoundWhenDone(HSOUND soundHandle)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3CCED0
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::KillUnit(HUNIT whichUnit)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3C8040
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::LeaderboardAddItem(HLEADERBOARD lb, jString label, jInteger value, HPLAYER p)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3CC060
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::LeaderboardClear(HLEADERBOARD lb)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3CC1B0
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::LeaderboardDisplay(HLEADERBOARD lb, jBoolean show)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3CC1D0
		jmp eax
	}
}

__declspec(naked) jInteger jNATIVE jass::LeaderboardGetItemCount(HLEADERBOARD lb)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3CC000
		jmp eax
	}
}

__declspec(naked) jString jNATIVE jass::LeaderboardGetLabelText(HLEADERBOARD lb)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3CC2F0
		jmp eax
	}
}

__declspec(naked) jInteger jNATIVE jass::LeaderboardGetPlayerIndex(HLEADERBOARD lb, HPLAYER p)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3CC2A0
		jmp eax
	}
}

__declspec(naked) jBoolean jNATIVE jass::LeaderboardHasPlayerItem(HLEADERBOARD lb, HPLAYER p)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3CC250
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::LeaderboardRemoveItem(HLEADERBOARD lb, jInteger index)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3CC0B0
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::LeaderboardRemovePlayerItem(HLEADERBOARD lb, HPLAYER p)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3CC0E0
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::LeaderboardSetItemLabel(HLEADERBOARD lb, jInteger whichItem, jString val)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3CC520
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::LeaderboardSetItemLabelColor(HLEADERBOARD lb, jInteger whichItem, jInteger red, jInteger green, jInteger blue, jInteger alpha)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3CC5B0
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::LeaderboardSetItemStyle(HLEADERBOARD lb, jInteger whichItem, jBoolean showLabel, jBoolean showValue, jBoolean showIcon)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3CC560
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::LeaderboardSetItemValue(HLEADERBOARD lb, jInteger whichItem, jInteger val)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3CC4F0
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::LeaderboardSetItemValueColor(HLEADERBOARD lb, jInteger whichItem, jInteger red, jInteger green, jInteger blue, jInteger alpha)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3CC600
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::LeaderboardSetLabel(HLEADERBOARD lb, jString label)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3CC3D0
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::LeaderboardSetLabelColor(HLEADERBOARD lb, jInteger red, jInteger green, jInteger blue, jInteger alpha)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3CC400
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::LeaderboardSetSizeByItemCount(HLEADERBOARD lb, jInteger count)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3CC030
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::LeaderboardSetStyle(HLEADERBOARD lb, jBoolean showLabel, jBoolean showNames, jBoolean showValues, jBoolean showIcons)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3CC4A0
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::LeaderboardSetValueColor(HLEADERBOARD lb, jInteger red, jInteger green, jInteger blue, jInteger alpha)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3CC450
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::LeaderboardSortItemsByLabel(HLEADERBOARD lb, jBoolean ascending)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3CC180
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::LeaderboardSortItemsByPlayer(HLEADERBOARD lb, jBoolean ascending)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3CC150
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::LeaderboardSortItemsByValue(HLEADERBOARD lb, jBoolean ascending)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3CC120
		jmp eax
	}
}

__declspec(naked) HABILITY jNATIVE jass::LoadAbilityHandle(HHASHTABLE table, jInteger parentKey, jInteger childKey)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3CEA60
		jmp eax
	}
}

__declspec(naked) jBoolean jNATIVE jass::LoadBoolean(HHASHTABLE table, jInteger parentKey, jInteger childKey)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3CAB10
		jmp eax
	}
}

__declspec(naked) HBOOLEXPR jNATIVE jass::LoadBooleanExprHandle(HHASHTABLE table, jInteger parentKey, jInteger childKey)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3CAD70
		jmp eax
	}
}

__declspec(naked) HBUTTON jNATIVE jass::LoadButtonHandle(HHASHTABLE table, jInteger parentKey, jInteger childKey)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3CADD0
		jmp eax
	}
}

__declspec(naked) HDEFEATCONDITION jNATIVE jass::LoadDefeatConditionHandle(HHASHTABLE table, jInteger parentKey, jInteger childKey)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3CEB20
		jmp eax
	}
}

__declspec(naked) HDESTRUCTABLE jNATIVE jass::LoadDestructableHandle(HHASHTABLE table, jInteger parentKey, jInteger childKey)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3CABD0
		jmp eax
	}
}

__declspec(naked) HDIALOG jNATIVE jass::LoadDialogHandle(HHASHTABLE table, jInteger parentKey, jInteger childKey)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3CADB0
		jmp eax
	}
}

__declspec(naked) HEFFECT jNATIVE jass::LoadEffectHandle(HHASHTABLE table, jInteger parentKey, jInteger childKey)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3CEA80
		jmp eax
	}
}

__declspec(naked) HFOGMODIFIER jNATIVE jass::LoadFogModifierHandle(HHASHTABLE table, jInteger parentKey, jInteger childKey)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3CAEF0
		jmp eax
	}
}

__declspec(naked) HFOGSTATE jNATIVE jass::LoadFogStateHandle(HHASHTABLE table, jInteger parentKey, jInteger childKey)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3CAED0
		jmp eax
	}
}

__declspec(naked) HFORCE jNATIVE jass::LoadForceHandle(HHASHTABLE table, jInteger parentKey, jInteger childKey)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3CACF0
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::LoadGame(jString saveFileName, jBoolean doScoreScreen)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3BBE60
		jmp eax
	}
}

__declspec(naked) HGROUP jNATIVE jass::LoadGroupHandle(HHASHTABLE table, jInteger parentKey, jInteger childKey)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3CAD10
		jmp eax
	}
}

__declspec(naked) HHASHTABLE jNATIVE jass::LoadHashtableHandle(HHASHTABLE table, jInteger parentKey, jInteger childKey)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3CAF10
		jmp eax
	}
}

__declspec(naked) HIMAGE jNATIVE jass::LoadImageHandle(HHASHTABLE table, jInteger parentKey, jInteger childKey)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3CAE90
		jmp eax
	}
}

__declspec(naked) jInteger jNATIVE jass::LoadInteger(HHASHTABLE table, jInteger parentKey, jInteger childKey)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3CAA90
		jmp eax
	}
}

__declspec(naked) HITEM jNATIVE jass::LoadItemHandle(HHASHTABLE table, jInteger parentKey, jInteger childKey)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3CABF0
		jmp eax
	}
}

__declspec(naked) HITEMPOOL jNATIVE jass::LoadItemPoolHandle(HHASHTABLE table, jInteger parentKey, jInteger childKey)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3CEAC0
		jmp eax
	}
}

__declspec(naked) HLEADERBOARD jNATIVE jass::LoadLeaderboardHandle(HHASHTABLE table, jInteger parentKey, jInteger childKey)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3CEB60
		jmp eax
	}
}

__declspec(naked) HLIGHTNING jNATIVE jass::LoadLightningHandle(HHASHTABLE table, jInteger parentKey, jInteger childKey)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3CAE70
		jmp eax
	}
}

__declspec(naked) HLOCATION jNATIVE jass::LoadLocationHandle(HHASHTABLE table, jInteger parentKey, jInteger childKey)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3CAD30
		jmp eax
	}
}

__declspec(naked) HMULTIBOARD jNATIVE jass::LoadMultiboardHandle(HHASHTABLE table, jInteger parentKey, jInteger childKey)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3CEB80
		jmp eax
	}
}

__declspec(naked) HMULTIBOARDITEM jNATIVE jass::LoadMultiboardItemHandle(HHASHTABLE table, jInteger parentKey, jInteger childKey)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3CEBA0
		jmp eax
	}
}

__declspec(naked) HPLAYER jNATIVE jass::LoadPlayerHandle(HHASHTABLE table, jInteger parentKey, jInteger childKey)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3CAB90
		jmp eax
	}
}

__declspec(naked) HQUEST jNATIVE jass::LoadQuestHandle(HHASHTABLE table, jInteger parentKey, jInteger childKey)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3CEAE0
		jmp eax
	}
}

__declspec(naked) HQUESTITEM jNATIVE jass::LoadQuestItemHandle(HHASHTABLE table, jInteger parentKey, jInteger childKey)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3CEB00
		jmp eax
	}
}

__declspec(naked) jReal jNATIVE jass::LoadReal(HHASHTABLE table, jInteger parentKey, jInteger childKey)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3CAAD0
		jmp eax
	}
}

__declspec(naked) HRECT jNATIVE jass::LoadRectHandle(HHASHTABLE table, jInteger parentKey, jInteger childKey)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3CAD50
		jmp eax
	}
}

__declspec(naked) HREGION jNATIVE jass::LoadRegionHandle(HHASHTABLE table, jInteger parentKey, jInteger childKey)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3CAC50
		jmp eax
	}
}

__declspec(naked) HSOUND jNATIVE jass::LoadSoundHandle(HHASHTABLE table, jInteger parentKey, jInteger childKey)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3CAD90
		jmp eax
	}
}

__declspec(naked) jString jNATIVE jass::LoadStr(HHASHTABLE table, jInteger parentKey, jInteger childKey)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3CAB50
		jmp eax
	}
}

__declspec(naked) HTEXTTAG jNATIVE jass::LoadTextTagHandle(HHASHTABLE table, jInteger parentKey, jInteger childKey)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3CAE50
		jmp eax
	}
}

__declspec(naked) HTIMERDIALOG jNATIVE jass::LoadTimerDialogHandle(HHASHTABLE table, jInteger parentKey, jInteger childKey)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3CEB40
		jmp eax
	}
}

__declspec(naked) HTIMER jNATIVE jass::LoadTimerHandle(HHASHTABLE table, jInteger parentKey, jInteger childKey)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3CAC30
		jmp eax
	}
}

__declspec(naked) HTRACKABLE jNATIVE jass::LoadTrackableHandle(HHASHTABLE table, jInteger parentKey, jInteger childKey)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3CEBC0
		jmp eax
	}
}

__declspec(naked) HTRIGGERACTION jNATIVE jass::LoadTriggerActionHandle(HHASHTABLE table, jInteger parentKey, jInteger childKey)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3CACB0
		jmp eax
	}
}

__declspec(naked) HTRIGGERCONDITION jNATIVE jass::LoadTriggerConditionHandle(HHASHTABLE table, jInteger parentKey, jInteger childKey)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3CAC90
		jmp eax
	}
}

__declspec(naked) HEVENT jNATIVE jass::LoadTriggerEventHandle(HHASHTABLE table, jInteger parentKey, jInteger childKey)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3CACD0
		jmp eax
	}
}

__declspec(naked) jTrigger jNATIVE jass::LoadTriggerHandle(HHASHTABLE table, jInteger parentKey, jInteger childKey)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3CAC70
		jmp eax
	}
}

__declspec(naked) HUBERSPLAT jNATIVE jass::LoadUbersplatHandle(HHASHTABLE table, jInteger parentKey, jInteger childKey)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3CAEB0
		jmp eax
	}
}

__declspec(naked) HUNIT jNATIVE jass::LoadUnitHandle(HHASHTABLE table, jInteger parentKey, jInteger childKey)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3CAC10
		jmp eax
	}
}

__declspec(naked) HUNITPOOL jNATIVE jass::LoadUnitPoolHandle(HHASHTABLE table, jInteger parentKey, jInteger childKey)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3CEAA0
		jmp eax
	}
}

__declspec(naked) HWIDGET jNATIVE jass::LoadWidgetHandle(HHASHTABLE table, jInteger parentKey, jInteger childKey)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3CABB0
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::LoadZepWave(jInteger arg1, jInteger arg2)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x2DDC50
		jmp eax
	}
}

__declspec(naked) HLOCATION jNATIVE jass::Location(jReal x, jReal y)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3D03B0
		jmp eax
	}
}

__declspec(naked) jInteger jNATIVE jass::MeleeDifficulty()
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x2E0500
		jmp eax
	}
}

__declspec(naked) jBoolean jNATIVE jass::MergeUnits(jInteger arg1, jInteger arg2, jInteger arg3, jInteger arg4)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x2DD320
		jmp eax
	}
}

__declspec(naked) jBoolean jNATIVE jass::MoveLightning(HLIGHTNING whichBolt, jBoolean checkVisibility, jReal x1, jReal y1, jReal x2, jReal y2)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3BCDA0
		jmp eax
	}
}

__declspec(naked) jBoolean jNATIVE jass::MoveLightningEx(HLIGHTNING whichBolt, jBoolean checkVisibility, jReal x1, jReal y1, jReal z1, jReal x2, jReal y2, jReal z2)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3BCCC0
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::MoveLocation(HLOCATION whichLocation, jReal newX, jReal newY)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3C0DF0
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::MoveRectTo(HRECT whichRect, jReal newCenterX, jReal newCenterY)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3C19C0
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::MoveRectToLoc(HRECT whichRect, HLOCATION newCenterLoc)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3C19F0
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::MultiboardClear(HMULTIBOARD lb)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3CC6F0
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::MultiboardDisplay(HMULTIBOARD lb, jBoolean show)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3CC670
		jmp eax
	}
}

__declspec(naked) jInteger jNATIVE jass::MultiboardGetColumnCount(HMULTIBOARD lb)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3CC7D0
		jmp eax
	}
}

__declspec(naked) HMULTIBOARDITEM jNATIVE jass::MultiboardGetItem(HMULTIBOARD lb, jInteger row, jInteger column)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3D37B0
		jmp eax
	}
}

__declspec(naked) jInteger jNATIVE jass::MultiboardGetRowCount(HMULTIBOARD lb)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3CC7B0
		jmp eax
	}
}

__declspec(naked) jString jNATIVE jass::MultiboardGetTitleText(HMULTIBOARD lb)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3CC750
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::MultiboardMinimize(HMULTIBOARD lb, jBoolean minimize)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3CC6B0
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::MultiboardReleaseItem(HMULTIBOARDITEM mbi)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3CC950
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::MultiboardSetColumnCount(HMULTIBOARD lb, jInteger count)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3CC7F0
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::MultiboardSetItemIcon(HMULTIBOARDITEM mbi, jString iconFileName)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3CCA20
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::MultiboardSetItemStyle(HMULTIBOARDITEM mbi, jBoolean showValue, jBoolean showIcon)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3CC970
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::MultiboardSetItemValue(HMULTIBOARDITEM mbi, jString val)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3CC990
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::MultiboardSetItemValueColor(HMULTIBOARDITEM mbi, jInteger red, jInteger green, jInteger blue, jInteger alpha)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3CC9C0
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::MultiboardSetItemWidth(HMULTIBOARDITEM mbi, jReal width)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3CCA00
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::MultiboardSetItemsIcon(HMULTIBOARD lb, jString iconPath)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3CC920
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::MultiboardSetItemsStyle(HMULTIBOARD lb, jBoolean showValues, jBoolean showIcons)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3CC830
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::MultiboardSetItemsValue(HMULTIBOARD lb, jString value)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3CC870
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::MultiboardSetItemsValueColor(HMULTIBOARD lb, jInteger red, jInteger green, jInteger blue, jInteger alpha)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3CC8A0
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::MultiboardSetItemsWidth(HMULTIBOARD lb, jReal width)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3CC8F0
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::MultiboardSetRowCount(HMULTIBOARD lb, jInteger count)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3CC810
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::MultiboardSetTitleText(HMULTIBOARD lb, jString label)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3CC720
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::MultiboardSetTitleTextColor(HMULTIBOARD lb, jInteger red, jInteger green, jInteger blue, jInteger alpha)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3CC770
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::MultiboardSuppressDisplay(jBoolean flag)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3B3C00
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::NewSoundEnvironment(jString environmentName)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3B3E60
		jmp eax
	}
}

__declspec(naked) HBOOLEXPR jNATIVE jass::Not(HBOOLEXPR operand)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3D0830
		jmp eax
	}
}

__declspec(naked) HBOOLEXPR jNATIVE jass::Or(HBOOLEXPR operandA, HBOOLEXPR operandB)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3D0710
		jmp eax
	}
}

__declspec(naked) jInteger jNATIVE jass::OrderId(jString orderIdString)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3BB590
		jmp eax
	}
}

__declspec(naked) jString jNATIVE jass::OrderId2String(jInteger orderId)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3BB5C0
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::PanCameraTo(jReal x, jReal y)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3B4700
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::PanCameraToTimed(jReal x, jReal y, jReal duration)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3B4740
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::PanCameraToTimedWithZ(jReal x, jReal y, jReal zOffsetDest, jReal duration)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3B47D0
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::PanCameraToWithZ(jReal x, jReal y, jReal zOffsetDest)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3B4790
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::PauseCompAI(HPLAYER p, jBoolean pause)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3CB7C0
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::PauseGame(jBoolean flag)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3BC4D0
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::PauseTimer(HTIMER whichTimer)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3C1400
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::PauseUnit(HUNIT whichUnit, jBoolean flag)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3C7340
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::PingMinimap(jReal x, jReal y, jReal duration)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3B4650
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::PingMinimapEx(jReal x, jReal y, jReal duration, jInteger red, jInteger green, jInteger blue, jBoolean extraEffects)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3B8660
		jmp eax
	}
}

__declspec(naked) HITEM jNATIVE jass::PlaceRandomItem(HITEMPOOL whichItemPool, jReal x, jReal y)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3CB700
		jmp eax
	}
}

__declspec(naked) HUNIT jNATIVE jass::PlaceRandomUnit(HUNITPOOL whichPool, HPLAYER forWhichPlayer, jReal x, jReal y, jReal facing)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3CB620
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::PlayCinematic(jString movieName)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3BC520
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::PlayModelCinematic(jString modelName)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3BC500
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::PlayMusic(jString musicName)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3B3D30
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::PlayMusicEx(jString musicName, jInteger frommsecs, jInteger fadeinmsecs)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3B3D50
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::PlayThematicMusic(jString musicFileName)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3B3DA0
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::PlayThematicMusicEx(jString musicFileName, jInteger frommsecs)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3B3DC0
		jmp eax
	}
}

__declspec(naked) HPLAYER jNATIVE jass::Player(jInteger number)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3BBB30
		jmp eax
	}
}

__declspec(naked) HLEADERBOARD jNATIVE jass::PlayerGetLeaderboard(HPLAYER toPlayer)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3CC380
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::PlayerSetLeaderboard(HPLAYER toPlayer, HLEADERBOARD lb)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3CC340
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::PopLastCommand()
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x2E04D0
		jmp eax
	}
}

__declspec(naked) jReal jNATIVE jass::Pow(jReal x, jReal power)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3B2C00
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::Preload(jString filename)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3B5170
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::PreloadEnd(jReal timeout)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3B5190
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::PreloadEndEx()
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3B5220
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::PreloadGenClear()
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3B52B0
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::PreloadGenEnd(jString filename)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3B52D0
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::PreloadGenStart()
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3B5290
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::PreloadRefresh()
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3B5210
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::PreloadStart()
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3B51F0
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::Preloader(jString filename)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3B5310
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::PurchaseZeppelin()
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x2DD410
		jmp eax
	}
}

__declspec(naked) HQUESTITEM jNATIVE jass::QuestCreateItem(HQUEST whichQuest)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3D3380
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::QuestItemSetCompleted(HQUESTITEM whichQuestItem, jBoolean completed)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3CBD70
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::QuestItemSetDescription(HQUESTITEM whichQuestItem, jString description)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3CBD40
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::QuestSetCompleted(HQUEST whichQuest, jBoolean completed)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3CBC20
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::QuestSetDescription(HQUEST whichQuest, jString description)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3CBBA0
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::QuestSetDiscovered(HQUEST whichQuest, jBoolean discovered)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3CBC60
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::QuestSetEnabled(HQUEST whichQuest, jBoolean enabled)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3CBC80
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::QuestSetFailed(HQUEST whichQuest, jBoolean failed)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3CBC40
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::QuestSetIconPath(HQUEST whichQuest, jString iconPath)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3CBBD0
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::QuestSetRequired(HQUEST whichQuest, jBoolean required)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3CBC00
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::QuestSetTitle(HQUEST whichQuest, jString title)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3CBB70
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::QueueDestructableAnimation(HDESTRUCTABLE d, jString whichAnimation)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3C4A00
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::QueueUnitAnimation(HUNIT whichUnit, jString whichAnimation)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3C6180
		jmp eax
	}
}

__declspec(naked) jInteger jNATIVE jass::R2I(jReal r)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3B2CE0
		jmp eax
	}
}

__declspec(naked) jString jNATIVE jass::R2S(jReal r)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3BAAF0
		jmp eax
	}
}

__declspec(naked) jString jNATIVE jass::R2SW(jReal r, jInteger width, jInteger precision)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3BAB40
		jmp eax
	}
}

__declspec(naked) jReal jNATIVE jass::Rad2Deg(jReal radians)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3B29F0
		jmp eax
	}
}

__declspec(naked) HRECT jNATIVE jass::Rect(jReal minx, jReal miny, jReal maxx, jReal maxy)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3D0A20
		jmp eax
	}
}

__declspec(naked) HRECT jNATIVE jass::RectFromLoc(HLOCATION min, HLOCATION max)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3D0BD0
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::RecycleGuardPosition(HUNIT hUnit)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3CB800
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::RegionAddCell(HREGION whichRegion, jReal x, jReal y)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3C1580
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::RegionAddCellAtLoc(HREGION whichRegion, HLOCATION whichLocation)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3C15B0
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::RegionAddRect(HREGION whichRegion, HRECT r)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3C14E0
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::RegionClearCell(HREGION whichRegion, jReal x, jReal y)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3C15F0
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::RegionClearCellAtLoc(HREGION whichRegion, HLOCATION whichLocation)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3C1620
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::RegionClearRect(HREGION whichRegion, HRECT r)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3C1530
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::RegisterStackedSound(HSOUND soundHandle, jBoolean byPosition, jReal rectwidth, jReal rectheight)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3CCF80
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::ReloadGame()
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3BBBE0
		jmp eax
	}
}

__declspec(naked) jBoolean jNATIVE jass::ReloadGameCachesFromDisk()
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3BC430
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::RemoveAllGuardPositions(HPLAYER num)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3CB840
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::RemoveDestructable(HDESTRUCTABLE d)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3C4730
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::RemoveGuardPosition(HUNIT hUnit)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3CB820
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::RemoveInjuries()
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x2DDDA0
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::RemoveItem(HITEM whichItem)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3C4C30
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::RemoveItemFromAllStock(jInteger itemId)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3B32B0
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::RemoveItemFromStock(HUNIT whichUnit, jInteger itemId)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3C93F0
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::RemoveLocation(HLOCATION whichLocation)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3C0DD0
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::RemovePlayer(HPLAYER whichPlayer, HPLAYERGAMERESULT gameResult)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3C9DC0
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::RemoveRect(HRECT whichRect)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3C16F0
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::RemoveRegion(HREGION whichRegion)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3C14C0
		jmp eax
	}
}

__declspec(naked) jBoolean jNATIVE jass::RemoveSaveDirectory(jString sourceDirName)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3BC070
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::RemoveSavedBoolean(HHASHTABLE table, jInteger parentKey, jInteger childKey)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3CB490
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::RemoveSavedHandle(HHASHTABLE table, jInteger parentKey, jInteger childKey)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3CB510
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::RemoveSavedInteger(HHASHTABLE table, jInteger parentKey, jInteger childKey)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3CB410
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::RemoveSavedReal(HHASHTABLE table, jInteger parentKey, jInteger childKey)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3CB450
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::RemoveSavedString(HHASHTABLE table, jInteger parentKey, jInteger childKey)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3CB4D0
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::RemoveSiege()
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x2DDE00
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::RemoveUnit(HUNIT whichUnit)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3C8060
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::RemoveUnitFromAllStock(jInteger unitId)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3B32C0
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::RemoveUnitFromStock(HUNIT whichUnit, jInteger unitId)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3C9430
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::RemoveWeatherEffect(HWEATHEREFFECT whichEffect)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3B3E70
		jmp eax
	}
}

__declspec(naked) jBoolean jNATIVE jass::RenameSaveDirectory(jString sourceDirName, jString destDirName)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3BBFB0
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::ResetCaptainLocs()
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x2DD780
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::ResetTerrainFog()
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3B3860
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::ResetToGameCamera(jReal duration)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3B46B0
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::ResetTrigger(jTrigger whichTrigger)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3C1C20
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::ResetUbersplat(HUBERSPLAT whichSplat)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3B44D0
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::ResetUnitLookAt(HUNIT whichUnit)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3C65F0
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::RestartGame(jBoolean doScoreScreen)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3BBC00
		jmp eax
	}
}

__declspec(naked) HUNIT jNATIVE jass::RestoreUnit(HGAMECACHE cache, jString missionKey, jString key, HPLAYER forWhichPlayer, jReal x, jReal y, jReal facing)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3CA970
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::ResumeMusic()
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3B3D90
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::ResumeTimer(HTIMER whichTimer)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3C1420
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::ReturnGuardPosts()
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x2DCFB0
		jmp eax
	}
}

__declspec(naked) jBoolean jNATIVE jass::ReviveHero(HUNIT whichHero, jReal x, jReal y, jBoolean doEyecandy)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3C6AF0
		jmp eax
	}
}

__declspec(naked) jBoolean jNATIVE jass::ReviveHeroLoc(HUNIT whichHero, HLOCATION loc, jBoolean doEyecandy)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3C6B80
		jmp eax
	}
}

__declspec(naked) jInteger jNATIVE jass::S2I(jString s)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3B2D10
		jmp eax
	}
}

__declspec(naked) jReal jNATIVE jass::S2R(jString s)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3B2D50
		jmp eax
	}
}

__declspec(naked) jBoolean jNATIVE jass::SaveAbilityHandle(HHASHTABLE table, jInteger parentKey, jInteger childKey, HABILITY whichAbility)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3CE8C0
		jmp eax
	}
}

__declspec(naked) jBoolean jNATIVE jass::SaveAgentHandle(HHASHTABLE table, jInteger parentKey, jInteger childKey, HAGENT whichAgent)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3CEA40
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::SaveBoolean(HHASHTABLE table, jInteger parentKey, jInteger childKey, jBoolean value)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3CA280
		jmp eax
	}
}

__declspec(naked) jBoolean jNATIVE jass::SaveBooleanExprHandle(HHASHTABLE table, jInteger parentKey, jInteger childKey, HBOOLEXPR whichBoolexpr)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3CA4E0
		jmp eax
	}
}

__declspec(naked) jBoolean jNATIVE jass::SaveButtonHandle(HHASHTABLE table, jInteger parentKey, jInteger childKey, HBUTTON whichButton)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3CA540
		jmp eax
	}
}

__declspec(naked) jBoolean jNATIVE jass::SaveDefeatConditionHandle(HHASHTABLE table, jInteger parentKey, jInteger childKey, HDEFEATCONDITION whichDefeatcondition)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3CE980
		jmp eax
	}
}

__declspec(naked) jBoolean jNATIVE jass::SaveDestructableHandle(HHASHTABLE table, jInteger parentKey, jInteger childKey, HDESTRUCTABLE whichDestructable)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3CA340
		jmp eax
	}
}

__declspec(naked) jBoolean jNATIVE jass::SaveDialogHandle(HHASHTABLE table, jInteger parentKey, jInteger childKey, HDIALOG whichDialog)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3CA520
		jmp eax
	}
}

__declspec(naked) jBoolean jNATIVE jass::SaveEffectHandle(HHASHTABLE table, jInteger parentKey, jInteger childKey, HEFFECT whichEffect)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3CE8E0
		jmp eax
	}
}

__declspec(naked) jBoolean jNATIVE jass::SaveFogModifierHandle(HHASHTABLE table, jInteger parentKey, jInteger childKey, HFOGMODIFIER whichFogModifier)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3CA640
		jmp eax
	}
}

__declspec(naked) jBoolean jNATIVE jass::SaveFogStateHandle(HHASHTABLE table, jInteger parentKey, jInteger childKey, HFOGSTATE whichFogState)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3CA620
		jmp eax
	}
}

__declspec(naked) jBoolean jNATIVE jass::SaveForceHandle(HHASHTABLE table, jInteger parentKey, jInteger childKey, HFORCE whichForce)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3CA460
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::SaveGame(jString saveFileName)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3BBEE0
		jmp eax
	}
}

__declspec(naked) jBoolean jNATIVE jass::SaveGameCache(HGAMECACHE whichCache)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3CA080
		jmp eax
	}
}

__declspec(naked) jBoolean jNATIVE jass::SaveGameExists(jString saveName)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3BC100
		jmp eax
	}
}

__declspec(naked) jBoolean jNATIVE jass::SaveGroupHandle(HHASHTABLE table, jInteger parentKey, jInteger childKey, HGROUP whichGroup)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3CA480
		jmp eax
	}
}

__declspec(naked) jBoolean jNATIVE jass::SaveHashtableHandle(HHASHTABLE table, jInteger parentKey, jInteger childKey, HHASHTABLE whichHashtable)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3CA660
		jmp eax
	}
}

__declspec(naked) jBoolean jNATIVE jass::SaveImageHandle(HHASHTABLE table, jInteger parentKey, jInteger childKey, HIMAGE whichImage)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3CA5E0
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::SaveInteger(HHASHTABLE table, jInteger parentKey, jInteger childKey, jInteger value)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3CA200
		jmp eax
	}
}

__declspec(naked) jBoolean jNATIVE jass::SaveItemHandle(HHASHTABLE table, jInteger parentKey, jInteger childKey, HITEM whichItem)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3CA360
		jmp eax
	}
}

__declspec(naked) jBoolean jNATIVE jass::SaveItemPoolHandle(HHASHTABLE table, jInteger parentKey, jInteger childKey, HITEMPOOL whichItempool)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3CE920
		jmp eax
	}
}

__declspec(naked) jBoolean jNATIVE jass::SaveLeaderboardHandle(HHASHTABLE table, jInteger parentKey, jInteger childKey, HLEADERBOARD whichLeaderboard)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3CE9C0
		jmp eax
	}
}

__declspec(naked) jBoolean jNATIVE jass::SaveLightningHandle(HHASHTABLE table, jInteger parentKey, jInteger childKey, HLIGHTNING whichLightning)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3CA5C0
		jmp eax
	}
}

__declspec(naked) jBoolean jNATIVE jass::SaveLocationHandle(HHASHTABLE table, jInteger parentKey, jInteger childKey, HLOCATION whichLocation)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3CA4A0
		jmp eax
	}
}

__declspec(naked) jBoolean jNATIVE jass::SaveMultiboardHandle(HHASHTABLE table, jInteger parentKey, jInteger childKey, HMULTIBOARD whichMultiboard)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3CE9E0
		jmp eax
	}
}

__declspec(naked) jBoolean jNATIVE jass::SaveMultiboardItemHandle(HHASHTABLE table, jInteger parentKey, jInteger childKey, HMULTIBOARDITEM whichMultiboarditem)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3CEA00
		jmp eax
	}
}

__declspec(naked) jBoolean jNATIVE jass::SavePlayerHandle(HHASHTABLE table, jInteger parentKey, jInteger childKey, HPLAYER whichPlayer)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3CA300
		jmp eax
	}
}

__declspec(naked) jBoolean jNATIVE jass::SaveQuestHandle(HHASHTABLE table, jInteger parentKey, jInteger childKey, HQUEST whichQuest)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3CE940
		jmp eax
	}
}

__declspec(naked) jBoolean jNATIVE jass::SaveQuestItemHandle(HHASHTABLE table, jInteger parentKey, jInteger childKey, HQUESTITEM whichQuestitem)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3CE960
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::SaveReal(HHASHTABLE table, jInteger parentKey, jInteger childKey, jReal value)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3CA240
		jmp eax
	}
}

__declspec(naked) jBoolean jNATIVE jass::SaveRectHandle(HHASHTABLE table, jInteger parentKey, jInteger childKey, HRECT whichRect)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3CA4C0
		jmp eax
	}
}

__declspec(naked) jBoolean jNATIVE jass::SaveRegionHandle(HHASHTABLE table, jInteger parentKey, jInteger childKey, HREGION whichRegion)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3CA3C0
		jmp eax
	}
}

__declspec(naked) jBoolean jNATIVE jass::SaveSoundHandle(HHASHTABLE table, jInteger parentKey, jInteger childKey, HSOUND whichSound)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3CA500
		jmp eax
	}
}

__declspec(naked) jBoolean jNATIVE jass::SaveStr(HHASHTABLE table, jInteger parentKey, jInteger childKey, jString value)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3CA2C0
		jmp eax
	}
}

__declspec(naked) jBoolean jNATIVE jass::SaveTextTagHandle(HHASHTABLE table, jInteger parentKey, jInteger childKey, HTEXTTAG whichTexttag)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3CA5A0
		jmp eax
	}
}

__declspec(naked) jBoolean jNATIVE jass::SaveTimerDialogHandle(HHASHTABLE table, jInteger parentKey, jInteger childKey, HTIMERDIALOG whichTimerdialog)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3CE9A0
		jmp eax
	}
}

__declspec(naked) jBoolean jNATIVE jass::SaveTimerHandle(HHASHTABLE table, jInteger parentKey, jInteger childKey, HTIMER whichTimer)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3CA3A0
		jmp eax
	}
}

__declspec(naked) jBoolean jNATIVE jass::SaveTrackableHandle(HHASHTABLE table, jInteger parentKey, jInteger childKey, HTRACKABLE whichTrackable)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3CEA20
		jmp eax
	}
}

__declspec(naked) jBoolean jNATIVE jass::SaveTriggerActionHandle(HHASHTABLE table, jInteger parentKey, jInteger childKey, HTRIGGERACTION whichTriggeraction)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3CA420
		jmp eax
	}
}

__declspec(naked) jBoolean jNATIVE jass::SaveTriggerConditionHandle(HHASHTABLE table, jInteger parentKey, jInteger childKey, HTRIGGERCONDITION whichTriggercondition)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3CA400
		jmp eax
	}
}

__declspec(naked) jBoolean jNATIVE jass::SaveTriggerEventHandle(HHASHTABLE table, jInteger parentKey, jInteger childKey, HEVENT whichEvent)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3CA440
		jmp eax
	}
}

__declspec(naked) jBoolean jNATIVE jass::SaveTriggerHandle(HHASHTABLE table, jInteger parentKey, jInteger childKey, jTrigger whichTrigger)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3CA3E0
		jmp eax
	}
}

__declspec(naked) jBoolean jNATIVE jass::SaveUbersplatHandle(HHASHTABLE table, jInteger parentKey, jInteger childKey, HUBERSPLAT whichUbersplat)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3CA600
		jmp eax
	}
}

__declspec(naked) jBoolean jNATIVE jass::SaveUnitHandle(HHASHTABLE table, jInteger parentKey, jInteger childKey, HUNIT whichUnit)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3CA380
		jmp eax
	}
}

__declspec(naked) jBoolean jNATIVE jass::SaveUnitPoolHandle(HHASHTABLE table, jInteger parentKey, jInteger childKey, HUNITPOOL whichUnitpool)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3CE900
		jmp eax
	}
}

__declspec(naked) jBoolean jNATIVE jass::SaveWidgetHandle(HHASHTABLE table, jInteger parentKey, jInteger childKey, HWIDGET whichWidget)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3CA320
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::SelectHeroSkill(HUNIT whichHero, jInteger abilcode)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3C7050
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::SelectUnit(HUNIT whichUnit, jBoolean flag)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3C7910
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::SetAllItemTypeSlots(jInteger slots)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3B32D0
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::SetAllUnitTypeSlots(jInteger slots)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3B32E0
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::SetAllianceTarget(HUNIT arg1)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x2E0630
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::SetAllyColorFilterState(jInteger state)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3B3A70
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::SetAltMinimapIcon(jString iconPath)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3BC540
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::SetAmphibious()
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x2E0720
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::SetBlight(HPLAYER whichPlayer, jReal x, jReal y, jReal radius, jBoolean addBlight)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3CD4C0
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::SetBlightLoc(HPLAYER whichPlayer, HLOCATION whichLocation, jReal radius, jBoolean addBlight)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3CD5D0
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::SetBlightPoint(HPLAYER whichPlayer, jReal x, jReal y, jBoolean addBlight)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3CD580
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::SetBlightRect(HPLAYER whichPlayer, HRECT r, jBoolean addBlight)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3CD520
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::SetCameraBounds(jReal x1, jReal y1, jReal x2, jReal y2, jReal x3, jReal y3, jReal x4, jReal y4)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3B86F0
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::SetCameraField(HCAMERAFIELD whichField, jReal value, jReal duration)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3B48B0
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::SetCameraOrientController(HUNIT whichUnit, jReal xoffset, jReal yoffset)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3CD7B0
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::SetCameraPosition(jReal x, jReal y)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3B45D0
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::SetCameraQuickPosition(jReal x, jReal y)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3B4610
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::SetCameraRotateMode(jReal x, jReal y, jReal radiansToSweep, jReal duration)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3B4850
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::SetCameraTargetController(HUNIT whichUnit, jReal xoffset, jReal yoffset, jBoolean inheritOrientation)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3CD760
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::SetCampaignAI()
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x2DDEA0
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::SetCampaignAvailable(jInteger campaignNumber, jBoolean available)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3B3370
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::SetCampaignMenuRace(HRACE r)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3BC3D0
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::SetCampaignMenuRaceEx(jInteger campaignIndex)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3BC3B0
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::SetCaptainChanges(jBoolean arg1)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x2E2D20
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::SetCaptainHome(jInteger arg1, jReal arg2, jReal arg3)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x2DD7B0
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::SetCineFilterBlendMode(HBLENDMODE whichMode)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3B4EB0
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::SetCineFilterDuration(jReal duration)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3B5100
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::SetCineFilterEndColor(jInteger red, jInteger green, jInteger blue, jInteger alpha)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3CECD0
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::SetCineFilterEndUV(jReal minu, jReal minv, jReal maxu, jReal maxv)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3B5020
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::SetCineFilterStartColor(jInteger red, jInteger green, jInteger blue, jInteger alpha)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3CEBE0
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::SetCineFilterStartUV(jReal minu, jReal minv, jReal maxu, jReal maxv)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3B4F40
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::SetCineFilterTexMapFlags(HTEXMAPFLAGS whichFlags)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3B4EF0
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::SetCineFilterTexture(jString filename)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3B4E80
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::SetCinematicCamera(jString cameraModelFile)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3B4820
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::SetCinematicScene(jInteger portraitUnitId, HPLAYERCOLOR color, jString speakerTitle, jString text, jReal sceneDuration, jReal voiceoverDuration)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3BCF80
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::SetCreatureDensity(HMAPDENSITY whichdensity)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3BAF50
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::SetCreepCampFilterState(jBoolean state)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3B3AC0
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::SetCustomCampaignButtonVisible(jInteger whichButton, jBoolean visible)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3B3510
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::SetDayNightModels(jString terrainDNCFile, jString unitDNCFile)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3B3790
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::SetDefaultDifficulty(HGAMEDIFFICULTY g)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3B33D0
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::SetDefendPlayer(jBoolean arg1)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x2E30E0
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::SetDestructableAnimation(HDESTRUCTABLE d, jString whichAnimation)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3C4A20
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::SetDestructableAnimationSpeed(HDESTRUCTABLE d, jReal speedFactor)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3C4A40
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::SetDestructableInvulnerable(HDESTRUCTABLE d, jBoolean flag)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3C4770
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::SetDestructableLife(HDESTRUCTABLE d, jReal life)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3C4850
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::SetDestructableMaxLife(HDESTRUCTABLE d, jReal max)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3C48D0
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::SetDestructableOccluderHeight(HDESTRUCTABLE d, jReal height)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3C4BD0
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::SetDoodadAnimation(jReal x, jReal y, jReal radius, jInteger doodadID, jBoolean nearestOnly, jString animName, jBoolean animRandom)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3B4570
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::SetDoodadAnimationRect(HRECT r, jInteger doodadID, jString animName, jBoolean animRandom)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3CD6F0
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::SetEdCinematicAvailable(jInteger campaignNumber, jBoolean available)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3B3460
		jmp eax
	}
}

__declspec(naked) jBoolean jNATIVE jass::SetExpansion(HUNIT arg1, jInteger arg2)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x2E0570
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::SetFloatGameState(HFGAMESTATE whichFloatGameState, jReal value)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3BC2E0
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::SetFogStateRadius(HPLAYER forWhichPlayer, HFOGSTATE whichState, jReal centerx, jReal centerY, jReal radius, jBoolean useSharedVision)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3C1AB0
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::SetFogStateRadiusLoc(HPLAYER forWhichPlayer, HFOGSTATE whichState, HLOCATION center, jReal radius, jBoolean useSharedVision)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3C1B20
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::SetFogStateRect(HPLAYER forWhichPlayer, HFOGSTATE whichState, HRECT where, jBoolean useSharedVision)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3C1A30
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::SetGameDifficulty(HGAMEDIFFICULTY whichdifficulty)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3BAF10
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::SetGamePlacement(HPLACEMENT whichPlacementType)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3BAEF0
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::SetGameSpeed(HGAMESPEED whichspeed)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3BAED0
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::SetGameTypeSupported(HGAMETYPE whichGameType, jBoolean value)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3BAE10
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::SetGroupsFlee(jBoolean arg1)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x2E32A0
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::SetHeroAgi(HUNIT whichHero, jInteger newAgi, jBoolean permanent)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3C66A0
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::SetHeroInt(HUNIT whichHero, jInteger newInt, jBoolean permanent)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3C6710
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::SetHeroLevel(HUNIT whichHero, jInteger level, jBoolean showEyeCandy)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3C6D70
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::SetHeroLevels(jCode arg1)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x2E0B00
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::SetHeroStr(HUNIT whichHero, jInteger newStr, jBoolean permanent)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3C6630
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::SetHeroXP(HUNIT whichHero, jInteger newXpVal, jBoolean showEyeCandy)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3C6A70
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::SetHeroesBuyItems(jBoolean arg1)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x2E3160
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::SetHeroesFlee(jBoolean arg1)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x2E3120
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::SetHeroesTakeItems(jBoolean arg1)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x2E3220
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::SetIgnoreInjured(jBoolean arg1)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x2E31E0
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::SetImageAboveWater(HIMAGE whichImage, jBoolean flag, jBoolean useWaterAlpha)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3B4480
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::SetImageColor(HIMAGE whichImage, jInteger red, jInteger green, jInteger blue, jInteger alpha)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3B85B0
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::SetImageConstantHeight(HIMAGE whichImage, jBoolean flag, jReal height)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3B43E0
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::SetImagePosition(HIMAGE whichImage, jReal x, jReal y, jReal z)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3B4400
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::SetImageRender(HIMAGE whichImage, jBoolean flag)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3B4440
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::SetImageRenderAlways(HIMAGE whichImage, jBoolean flag)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3B4460
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::SetImageType(HIMAGE whichImage, jInteger imageType)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3B44A0
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::SetIntegerGameState(HIGAMESTATE whichIntegerGameState, jInteger value)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3BC350
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::SetIntroShotModel(jString introModelPath)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3BC8A0
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::SetIntroShotText(jString introText)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3BC880
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::SetItemCharges(HITEM whichItem, jInteger charges)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3C5070
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::SetItemDropID(HITEM whichItem, jInteger unitId)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3C5030
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::SetItemDropOnDeath(HITEM whichItem, jBoolean flag)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3C4D00
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::SetItemDroppable(HITEM i, jBoolean flag)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3C4D30
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::SetItemInvulnerable(HITEM whichItem, jBoolean flag)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3C4EE0
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::SetItemPawnable(HITEM i, jBoolean flag)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3C4D60
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::SetItemPlayer(HITEM whichItem, HPLAYER whichPlayer, jBoolean changeColor)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3C4EB0
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::SetItemPosition(HITEM i, jReal x, jReal y)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3C4C80
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::SetItemTypeSlots(HUNIT whichUnit, jInteger slots)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3C9470
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::SetItemUserData(HITEM whichItem, jInteger data)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3C50F0
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::SetItemVisible(HITEM whichItem, jBoolean show)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3C4F20
		jmp eax
	}
}

__declspec(naked) jBoolean jNATIVE jass::SetLightningColor(HLIGHTNING whichBolt, jReal r, jReal g, jReal b, jReal a)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3B8490
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::SetMapDescription(jString description)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3BADC0
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::SetMapFlag(HMAPFLAG whichMapFlag, jBoolean value)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3BAE70
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::SetMapMusic(jString musicName, jBoolean random, jInteger index)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3B3CE0
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::SetMapName(jString name)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3BADA0
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::SetMeleeAI()
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x2DDEE0
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::SetMissionAvailable(jInteger campaignNumber, jInteger missionNumber, jBoolean available)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3B3340
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::SetMusicPlayPosition(jInteger millisecs)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3B3E00
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::SetMusicVolume(jInteger volume)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3B3DF0
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::SetNewHeroes(jBoolean arg1)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x2E3020
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::SetOpCinematicAvailable(jInteger campaignNumber, jBoolean available)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3B3400
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::SetPeonsRepair(jBoolean arg1)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x2E3060
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::SetPlayerAbilityAvailable(HPLAYER whichPlayer, jInteger abilid, jBoolean avail)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3C97D0
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::SetPlayerAlliance(HPLAYER sourcePlayer, HPLAYER otherPlayer, HALLIANCETYPE whichAllianceSetting, jBoolean value)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3C1050
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::SetPlayerColor(HPLAYER whichPlayer, HPLAYERCOLOR color)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3C1220
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::SetPlayerController(HPLAYER whichPlayer, HMAPCONTROL controlType)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3C1200
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::SetPlayerHandicap(HPLAYER whichPlayer, jReal handicap)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3C9E30
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::SetPlayerHandicapXP(HPLAYER whichPlayer, jReal handicap)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3C9EE0
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::SetPlayerName(HPLAYER whichPlayer, jString name)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3C0F10
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::SetPlayerOnScoreScreen(HPLAYER whichPlayer, jBoolean flag)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3C9800
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::SetPlayerRacePreference(HPLAYER whichPlayer, HRACEPREFERENCE whichRacePreference)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3C11A0
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::SetPlayerRaceSelectable(HPLAYER whichPlayer, jBoolean value)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3C11D0
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::SetPlayerStartLocation(HPLAYER whichPlayer, jInteger startLocIndex)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3C0F80
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::SetPlayerState(HPLAYER whichPlayer, HPLAYERSTATE whichPlayerState, jInteger value)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3C9AA0
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::SetPlayerTaxRate(HPLAYER sourcePlayer, HPLAYER otherPlayer, HPLAYERSTATE whichResource, jInteger rate)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3C10E0
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::SetPlayerTeam(HPLAYER whichPlayer, jInteger whichTeam)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3C0EE0
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::SetPlayerTechMaxAllowed(HPLAYER whichPlayer, jInteger techid, jInteger maximum)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3C9660
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::SetPlayerTechResearched(HPLAYER whichPlayer, jInteger techid, jInteger setToLevel)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3C9730
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::SetPlayerUnitsOwner(HPLAYER whichPlayer, jInteger newOwner)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3C12F0
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::SetPlayers(jInteger playercount)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3BADF0
		jmp eax
	}
}

__declspec(naked) jBoolean jNATIVE jass::SetProduce(jInteger arg1, jInteger arg2, jInteger arg3)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x2DD450
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::SetRandomPaths(jBoolean arg1)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x2E30A0
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::SetRandomSeed(jInteger seed)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3B36D0
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::SetRect(HRECT whichRect, jReal minx, jReal miny, jReal maxx, jReal maxy)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3C1710
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::SetRectFromLoc(HRECT whichRect, HLOCATION min, HLOCATION max)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3C17F0
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::SetReplacementCount(jInteger arg1)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x2E0B30
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::SetReservedLocalHeroButtons(jInteger reserved)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3B3A30
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::SetResourceAmount(HUNIT whichUnit, jInteger amount)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3C77F0
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::SetResourceDensity(HMAPDENSITY whichdensity)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3BAF30
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::SetSkyModel(jString skyModelFile)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3B37D0
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::SetSlowChopping(jBoolean arg1)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x2E32E0
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::SetSmartArtillery(jBoolean arg1)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x2DDF10
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::SetSoundChannel(HSOUND soundHandle, jInteger channel)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3CCC20
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::SetSoundConeAngles(HSOUND soundHandle, jReal inside, jReal outside, jInteger outsideVolume)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3CCCF0
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::SetSoundConeOrientation(HSOUND soundHandle, jReal x, jReal y, jReal z)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3CCD30
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::SetSoundDistanceCutoff(HSOUND soundHandle, jReal cutoff)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3CCCD0
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::SetSoundDistances(HSOUND soundHandle, jReal minDist, jReal maxDist)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3CCCA0
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::SetSoundDuration(HSOUND soundHandle, jInteger duration)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3CCEF0
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::SetSoundParamsFromLabel(HSOUND soundHandle, jString soundLabel)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3CCBF0
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::SetSoundPitch(HSOUND soundHandle, jReal pitch)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3CCC60
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::SetSoundPlayPosition(HSOUND soundHandle, jInteger millisecs)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3CCC80
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::SetSoundPosition(HSOUND soundHandle, jReal x, jReal y, jReal z)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3CCD90
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::SetSoundVelocity(HSOUND soundHandle, jReal x, jReal y, jReal z)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3CCDF0
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::SetSoundVolume(HSOUND soundHandle, jInteger volume)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3CCC40
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::SetStackedSound(jString arg1, jReal arg2, jReal arg3)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3B3C20
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::SetStackedSoundRect(jString arg1, HRECT arg2)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3CCA50
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::SetStagePoint(jReal arg1, jReal arg2)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x2DDBD0
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::SetStartLocPrio(jInteger whichStartLoc, jInteger prioSlotIndex, jInteger otherStartLocIndex, HSTARTLOCPRIO priority)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3BAFC0
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::SetStartLocPrioCount(jInteger whichStartLoc, jInteger prioSlotCount)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3BAF90
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::SetTargetHeroes(jBoolean arg1)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x2DDE60
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::SetTeams(jInteger teamcount)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3D4000
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::SetTerrainFog(jReal a, jReal b, jReal c, jReal d, jReal e)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3B3840
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::SetTerrainFogEx(jInteger style, jReal zstart, jReal zend, jReal density, jReal red, jReal green, jReal blue)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3B81B0
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::SetTerrainPathable(jReal x, jReal y, HPATHINGTYPE t, jBoolean flag)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3B42F0
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::SetTerrainType(jReal x, jReal y, jInteger terrainType, jInteger variation, jInteger area, jInteger shape)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3BCF20
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::SetTextTagAge(HTEXTTAG t, jReal age)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3BC7F0
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::SetTextTagColor(HTEXTTAG t, jInteger red, jInteger green, jInteger blue, jInteger alpha)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3BC6A0
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::SetTextTagFadepoint(HTEXTTAG t, jReal fadepoint)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3BC850
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::SetTextTagLifespan(HTEXTTAG t, jReal lifespan)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3BC820
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::SetTextTagPermanent(HTEXTTAG t, jBoolean flag)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3BC7C0
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::SetTextTagPos(HTEXTTAG t, jReal x, jReal y, jReal heightOffset)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3BC610
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::SetTextTagPosUnit(HTEXTTAG t, HUNIT whichUnit, jReal heightOffset)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3CB890
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::SetTextTagSuspended(HTEXTTAG t, jBoolean flag)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3BC790
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::SetTextTagText(HTEXTTAG t, jString s, jReal height)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3BC5D0
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::SetTextTagVelocity(HTEXTTAG t, jReal xvel, jReal yvel)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3BC700
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::SetTextTagVisibility(HTEXTTAG t, jBoolean flag)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3BC760
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::SetThematicMusicPlayPosition(jInteger millisecs)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3B3E10
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::SetTimeOfDayScale(jReal r)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3BC490
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::SetTutorialCleared(jBoolean cleared)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3B3430
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::SetUbersplatRender(HUBERSPLAT whichSplat, jBoolean flag)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3B4510
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::SetUbersplatRenderAlways(HUBERSPLAT whichSplat, jBoolean flag)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3B4530
		jmp eax
	}
}

__declspec(naked) jInteger jNATIVE jass::SetUnitAbilityLevel(HUNIT whichUnit, jInteger abilcode, jInteger level)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3C71B0
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::SetUnitAcquireRange(HUNIT whichUnit, jReal newAcquireRange)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3C5CF0
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::SetUnitAnimation(HUNIT whichUnit, jString whichAnimation)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3C61A0
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::SetUnitAnimationByIndex(HUNIT whichUnit, jInteger whichAnimation)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3C61F0
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::SetUnitAnimationWithRarity(HUNIT whichUnit, jString whichAnimation, HRARITYCONTROL rarity)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3C61C0
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::SetUnitBlendTime(HUNIT whichUnit, jReal blendTime)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3C6320
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::SetUnitColor(HUNIT whichUnit, HPLAYERCOLOR whichColor)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3C5F60
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::SetUnitCreepGuard(HUNIT whichUnit, jBoolean creepGuard)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3C5480
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::SetUnitExploded(HUNIT whichUnit, jBoolean exploded)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3CE6D0
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::SetUnitFacing(HUNIT whichUnit, jReal facingAngle)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3C5AF0
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::SetUnitFacingTimed(HUNIT whichUnit, jReal facingAngle, jReal duration)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3C5B30
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::SetUnitFlyHeight(HUNIT whichUnit, jReal newHeight, jReal rate)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3C5C60
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::SetUnitFog(jReal a, jReal b, jReal c, jReal d, jReal e)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3B3850
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::SetUnitInvulnerable(HUNIT whichUnit, jBoolean flag)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3C72F0
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::SetUnitLookAt(HUNIT whichUnit, jString whichBone, HUNIT lookAtTarget, jReal offsetX, jReal offsetY, jReal offsetZ)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3C64C0
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::SetUnitMoveSpeed(HUNIT whichUnit, jReal newSpeed)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3C5C40
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::SetUnitOwner(HUNIT whichUnit, HPLAYER whichPlayer, jBoolean changeColor)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3C5ED0
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::SetUnitPathing(HUNIT whichUnit, jBoolean flag)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3C5FA0
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::SetUnitPosition(HUNIT whichUnit, jReal newX, jReal newY)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3C5A50
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::SetUnitPositionLoc(HUNIT whichUnit, HLOCATION whichLocation)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3C5AB0
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::SetUnitPropWindow(HUNIT whichUnit, jReal newPropWindowAngle)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3C5CD0
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::SetUnitRescuable(HUNIT whichUnit, HPLAYER byWhichPlayer, jBoolean flag)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3C5F10
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::SetUnitRescueRange(HUNIT whichUnit, jReal range)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3C5F40
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::SetUnitScale(HUNIT whichUnit, jReal scaleX, jReal scaleY, jReal scaleZ)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3C62D0
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::SetUnitState(HUNIT whichUnit, HUNITSTATE whichUnitState, jReal newVal)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3C5EA0
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::SetUnitTimeScale(HUNIT whichUnit, jReal timeScale)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3C6300
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::SetUnitTurnSpeed(HUNIT whichUnit, jReal newTurnSpeed)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3C5CB0
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::SetUnitTypeSlots(HUNIT whichUnit, jInteger slots)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3C94B0
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::SetUnitUseFood(HUNIT whichUnit, jBoolean useFood)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3C54A0
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::SetUnitUserData(HUNIT whichUnit, jInteger data)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3C9510
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::SetUnitVertexColor(HUNIT whichUnit, jInteger red, jInteger green, jInteger blue, jInteger alpha)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3C6340
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::SetUnitX(HUNIT whichUnit, jReal newX)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3C5970
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::SetUnitY(HUNIT whichUnit, jReal newY)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3C59E0
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::SetUnitsFlee(jBoolean arg1)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x2E3260
		jmp eax
	}
}

__declspec(naked) jBoolean jNATIVE jass::SetUpgrade(jInteger arg1)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x2DD4B0
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::SetWatchMegaTargets(jBoolean arg1)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x2E31A0
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::SetWaterBaseColor(jInteger red, jInteger green, jInteger blue, jInteger alpha)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3B8580
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::SetWaterDeforms(jBoolean val)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3B4240
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::SetWidgetLife(HWIDGET whichWidget, jReal newLife)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3C4690
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::ShiftTownSpot(jReal arg1, jReal arg2)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x2DD740
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::ShowDestructable(HDESTRUCTABLE d, jBoolean flag)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3C4A60
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::ShowImage(HIMAGE whichImage, jBoolean flag)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3B43C0
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::ShowInterface(jBoolean flag, jReal fadeDuration)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3B3810
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::ShowUbersplat(HUBERSPLAT whichSplat, jBoolean flag)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3B44F0
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::ShowUnit(HUNIT whichUnit, jBoolean show)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3CE730
		jmp eax
	}
}

__declspec(naked) jReal jNATIVE jass::Sin(jReal radians)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3B2A10
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::Sleep(jReal arg1)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x2DE380
		jmp eax
	}
}

__declspec(naked) jReal jNATIVE jass::SquareRoot(jReal x)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3B2BA0
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::StartCampaignAI(HPLAYER num, jString script)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3CB770
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::StartGetEnemyBase()
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x2DDCC0
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::StartMeleeAI(HPLAYER num, jString script)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3CB740
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::StartSound(HSOUND soundHandle)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3CCE80
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::StartThread(jCode arg1)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x2DE2A0
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::StopCamera()
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3B46E0
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::StopGathering()
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x2DCE00
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::StopMusic(jBoolean fadeOut)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3B3D80
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::StopSound(HSOUND soundHandle, jBoolean killWhenDone, jBoolean fadeOut)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3CCEB0
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::StoreBoolean(HGAMECACHE cache, jString missionKey, jString key, jBoolean value)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3CA140
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::StoreInteger(HGAMECACHE cache, jString missionKey, jString key, jInteger value)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3CA0A0
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::StoreReal(HGAMECACHE cache, jString missionKey, jString key, jReal value)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3CA0F0
		jmp eax
	}
}

__declspec(naked) jBoolean jNATIVE jass::StoreString(HGAMECACHE cache, jString missionKey, jString key, jString value)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3CA680
		jmp eax
	}
}

__declspec(naked) jBoolean jNATIVE jass::StoreUnit(HGAMECACHE cache, jString missionKey, jString key, HUNIT whichUnit)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3CA1A0
		jmp eax
	}
}

__declspec(naked) jString jNATIVE jass::StringCase(jString source, jBoolean upper)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3BAC40
		jmp eax
	}
}

__declspec(naked) jInteger jNATIVE jass::StringHash(jString s)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3B2D30
		jmp eax
	}
}

__declspec(naked) jInteger jNATIVE jass::StringLength(jString s)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3BAC20
		jmp eax
	}
}

__declspec(naked) jString jNATIVE jass::SubString(jString source, jInteger start, jInteger end)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3BABA0
		jmp eax
	}
}

__declspec(naked) jBoolean jNATIVE jass::SuicidePlayer(HPLAYER arg1, jBoolean arg2)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x2E2F00
		jmp eax
	}
}

__declspec(naked) jBoolean jNATIVE jass::SuicidePlayerUnits(HPLAYER arg1, jBoolean arg2)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x2E2F90
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::SuicideUnit(jInteger arg1, jInteger arg2)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x2DE330
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::SuicideUnitEx(jInteger arg1, jInteger arg2, jInteger arg3)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x2DE2E0
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::SuspendHeroXP(HUNIT whichHero, jBoolean flag)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3C6E10
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::SuspendTimeOfDay(jBoolean b)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3BC460
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::SyncSelections()
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3BB740
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::SyncStoredBoolean(HGAMECACHE cache, jString missionKey, jString key)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3CA780
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::SyncStoredInteger(HGAMECACHE cache, jString missionKey, jString key)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3CA6E0
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::SyncStoredReal(HGAMECACHE cache, jString missionKey, jString key)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3CA730
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::SyncStoredString(HGAMECACHE cache, jString missionKey, jString key)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3CA820
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::SyncStoredUnit(HGAMECACHE cache, jString missionKey, jString key)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3CA7D0
		jmp eax
	}
}

__declspec(naked) jReal jNATIVE jass::Tan(jReal radians)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3B2A50
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::TeleportCaptain(jReal arg1, jReal arg2)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x2DD680
		jmp eax
	}
}

__declspec(naked) HTERRAINDEFORMATION jNATIVE jass::TerrainDeformCrater(jReal x, jReal y, jReal radius, jReal depth, jInteger duration, jBoolean permanent)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3B3E90
		jmp eax
	}
}

__declspec(naked) HTERRAINDEFORMATION jNATIVE jass::TerrainDeformRandom(jReal x, jReal y, jReal radius, jReal minDelta, jReal maxDelta, jInteger duration, jInteger updateInterval)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3B4040
		jmp eax
	}
}

__declspec(naked) HTERRAINDEFORMATION jNATIVE jass::TerrainDeformRipple(jReal x, jReal y, jReal radius, jReal depth, jInteger duration, jInteger count, jReal spaceWaves, jReal timeWaves, jReal radiusStartPct, jBoolean limitNeg)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3B3F00
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::TerrainDeformStop(HTERRAINDEFORMATION deformation, jInteger duration)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3B40B0
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::TerrainDeformStopAll()
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3B40C0
		jmp eax
	}
}

__declspec(naked) HTERRAINDEFORMATION jNATIVE jass::TerrainDeformWave(jReal x, jReal y, jReal dirX, jReal dirY, jReal distance, jReal speed, jReal radius, jReal depth, jInteger trailTime, jInteger count)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3B3FA0
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::TimerDialogDisplay(HTIMERDIALOG whichDialog, jBoolean display)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3CBF50
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::TimerDialogSetRealTimeRemaining(HTIMERDIALOG whichDialog, jReal timeRemaining)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3CBFA0
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::TimerDialogSetSpeed(HTIMERDIALOG whichDialog, jReal speedMultFactor)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3CBF20
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::TimerDialogSetTimeColor(HTIMERDIALOG whichDialog, jInteger red, jInteger green, jInteger blue, jInteger alpha)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3CBED0
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::TimerDialogSetTitle(HTIMERDIALOG whichDialog, jString title)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3CBE50
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::TimerDialogSetTitleColor(HTIMERDIALOG whichDialog, jInteger red, jInteger green, jInteger blue, jInteger alpha)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3CBE80
		jmp eax
	}
}

__declspec(naked) jReal jNATIVE jass::TimerGetElapsed(HTIMER whichTimer)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3C13A0
		jmp eax
	}
}

__declspec(naked) jReal jNATIVE jass::TimerGetRemaining(HTIMER whichTimer)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3C13C0
		jmp eax
	}
}

__declspec(naked) jReal jNATIVE jass::TimerGetTimeout(HTIMER whichTimer)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3C13E0
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::TimerStart(HTIMER whichTimer, jReal timeout, jBoolean periodic, jCode handlerFunc)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3C1370
		jmp eax
	}
}

__declspec(naked) jBoolean jNATIVE jass::TownHasHall(jInteger arg1)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x2DE0A0
		jmp eax
	}
}

__declspec(naked) jBoolean jNATIVE jass::TownHasMine(jInteger arg1)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x2DE060
		jmp eax
	}
}

__declspec(naked) jBoolean jNATIVE jass::TownThreatened()
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x2DD8E0
		jmp eax
	}
}

__declspec(naked) jInteger jNATIVE jass::TownWithMine()
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x2DE030
		jmp eax
	}
}

__declspec(naked) HTRIGGERACTION jNATIVE jass::TriggerAddAction(jTrigger whichTrigger, jCode actionFunc)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3C3E90
		jmp eax
	}
}

__declspec(naked) HTRIGGERCONDITION jNATIVE jass::TriggerAddCondition(jTrigger whichTrigger, HBOOLEXPR condition)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3C3DF0
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::TriggerClearActions(jTrigger whichTrigger)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3C3F00
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::TriggerClearConditions(jTrigger whichTrigger)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3C3E70
		jmp eax
	}
}

__declspec(naked) jBoolean jNATIVE jass::TriggerEvaluate(jTrigger whichTrigger)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3C3F80
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::TriggerExecute(jTrigger whichTrigger)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3C3F40
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::TriggerExecuteWait(jTrigger whichTrigger)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3C3F60
		jmp eax
	}
}

__declspec(naked) HEVENT jNATIVE jass::TriggerRegisterDeathEvent(jTrigger whichTrigger, HWIDGET whichWidget)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3D22C0
		jmp eax
	}
}

__declspec(naked) HEVENT jNATIVE jass::TriggerRegisterDialogButtonEvent(jTrigger whichTrigger, HBUTTON whichButton)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3D1880
		jmp eax
	}
}

__declspec(naked) HEVENT jNATIVE jass::TriggerRegisterDialogEvent(jTrigger whichTrigger, HDIALOG whichDialog)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3D17A0
		jmp eax
	}
}

__declspec(naked) HEVENT jNATIVE jass::TriggerRegisterEnterRegion(jTrigger whichTrigger, HREGION whichRegion, HBOOLEXPR filter)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3D2700
		jmp eax
	}
}

__declspec(naked) HEVENT jNATIVE jass::TriggerRegisterFilterUnitEvent(jTrigger whichTrigger, HUNIT whichUnit, HUNITEVENT whichEvent, HBOOLEXPR filter)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3D24D0
		jmp eax
	}
}

__declspec(naked) HEVENT jNATIVE jass::TriggerRegisterGameEvent(jTrigger whichTrigger, HGAMEEVENT whichGameEvent)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3D1960
		jmp eax
	}
}

__declspec(naked) HEVENT jNATIVE jass::TriggerRegisterGameStateEvent(jTrigger whichTrigger, HGAMESTATE whichState, HLIMITOP opcode, jReal limitval)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3D1630
		jmp eax
	}
}

__declspec(naked) HEVENT jNATIVE jass::TriggerRegisterLeaveRegion(jTrigger whichTrigger, HREGION whichRegion, HBOOLEXPR filter)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3D2800
		jmp eax
	}
}

__declspec(naked) HEVENT jNATIVE jass::TriggerRegisterPlayerAllianceChange(jTrigger whichTrigger, HPLAYER whichPlayer, HALLIANCETYPE whichAlliance)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3D1BA0
		jmp eax
	}
}

__declspec(naked) HEVENT jNATIVE jass::TriggerRegisterPlayerChatEvent(jTrigger whichTrigger, HPLAYER whichPlayer, jString chatMessageToDetect, jBoolean exactMatchOnly)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3D1EF0
		jmp eax
	}
}

__declspec(naked) HEVENT jNATIVE jass::TriggerRegisterPlayerEvent(jTrigger whichTrigger, HPLAYER whichPlayer, HPLAYEREVENT whichPlayerEvent)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3D1C90
		jmp eax
	}
}

__declspec(naked) HEVENT jNATIVE jass::TriggerRegisterPlayerStateEvent(jTrigger whichTrigger, HPLAYER whichPlayer, HPLAYERSTATE whichState, HLIMITOP opcode, jReal limitval)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3D1A60
		jmp eax
	}
}

__declspec(naked) HEVENT jNATIVE jass::TriggerRegisterPlayerUnitEvent(jTrigger whichTrigger, HPLAYER whichPlayer, HPLAYERUNITEVENT whichPlayerUnitEvent, HBOOLEXPR filter)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3D1DD0
		jmp eax
	}
}

__declspec(naked) HEVENT jNATIVE jass::TriggerRegisterTimerEvent(jTrigger whichTrigger, jReal timeout, jBoolean periodic)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3D1420
		jmp eax
	}
}

__declspec(naked) HEVENT jNATIVE jass::TriggerRegisterTimerExpireEvent(jTrigger whichTrigger, HTIMER t)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3D1550
		jmp eax
	}
}

__declspec(naked) HEVENT jNATIVE jass::TriggerRegisterTrackableHitEvent(jTrigger whichTrigger, HTRACKABLE t)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3D31C0
		jmp eax
	}
}

__declspec(naked) HEVENT jNATIVE jass::TriggerRegisterTrackableTrackEvent(jTrigger whichTrigger, HTRACKABLE t)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3D32A0
		jmp eax
	}
}

__declspec(naked) HEVENT jNATIVE jass::TriggerRegisterUnitEvent(jTrigger whichTrigger, HUNIT whichUnit, HUNITEVENT whichEvent)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3D23B0
		jmp eax
	}
}

__declspec(naked) HEVENT jNATIVE jass::TriggerRegisterUnitInRange(jTrigger whichTrigger, HUNIT whichUnit, jReal range, HBOOLEXPR filter)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3D25F0
		jmp eax
	}
}

__declspec(naked) HEVENT jNATIVE jass::TriggerRegisterUnitStateEvent(jTrigger whichTrigger, HUNIT whichUnit, HUNITSTATE whichState, HLIMITOP opcode, jReal limitval)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3D21B0
		jmp eax
	}
}

__declspec(naked) HEVENT jNATIVE jass::TriggerRegisterVariableEvent(jTrigger whichTrigger, jString varName, HLIMITOP opcode, jReal limitval)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3D12E0
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::TriggerRemoveAction(jTrigger whichTrigger, HTRIGGERACTION whichAction)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3C3ED0
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::TriggerRemoveCondition(jTrigger whichTrigger, HTRIGGERCONDITION whichCondition)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3C3E40
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::TriggerSleepAction(jReal timeout)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3B2DB0
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::TriggerSyncReady()
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3BB710
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::TriggerSyncStart()
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3B2DC0
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::TriggerWaitForSound(HSOUND s, jReal offset)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3C3F20
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::TriggerWaitOnSleeps(jTrigger whichTrigger, jBoolean flag)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3C1CA0
		jmp eax
	}
}

__declspec(naked) jBoolean jNATIVE jass::UnitAddAbility(HUNIT whichUnit, jInteger abilityId)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3C82A0
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::UnitAddIndicator(HUNIT whichUnit, jInteger red, jInteger green, jInteger blue, jInteger alpha)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3C6BD0
		jmp eax
	}
}

__declspec(naked) jBoolean jNATIVE jass::UnitAddItem(HUNIT whichUnit, HITEM whichItem)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3C73F0
		jmp eax
	}
}

__declspec(naked) HITEM jNATIVE jass::UnitAddItemById(HUNIT whichUnit, jInteger itemId)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3C74F0
		jmp eax
	}
}

__declspec(naked) jBoolean jNATIVE jass::UnitAddItemToSlotById(HUNIT whichUnit, jInteger itemId, jInteger itemSlot)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3C75B0
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::UnitAddSleep(HUNIT whichUnit, jBoolean add)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3C8450
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::UnitAddSleepPerm(HUNIT whichUnit, jBoolean add)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3C84D0
		jmp eax
	}
}

__declspec(naked) jBoolean jNATIVE jass::UnitAddType(HUNIT whichUnit, HUNITTYPE whichUnitType)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3C7BC0
		jmp eax
	}
}

__declspec(naked) jBoolean jNATIVE jass::UnitAlive(HUNIT arg1)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x2E0760
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::UnitApplyTimedLife(HUNIT whichUnit, jInteger buffId, jReal duration)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3C85D0
		jmp eax
	}
}

__declspec(naked) jBoolean jNATIVE jass::UnitCanSleep(HUNIT whichUnit)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3C84A0
		jmp eax
	}
}

__declspec(naked) jBoolean jNATIVE jass::UnitCanSleepPerm(HUNIT whichUnit)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3C8520
		jmp eax
	}
}

__declspec(naked) jInteger jNATIVE jass::UnitCountBuffsEx(HUNIT whichUnit, jBoolean removePositive, jBoolean removeNegative, jBoolean magic, jBoolean physical, jBoolean timedLife, jBoolean aura, jBoolean autoDispel)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3C83A0
		jmp eax
	}
}

__declspec(naked) jBoolean jNATIVE jass::UnitDamagePoint(HUNIT whichUnit, jReal delay, jReal radius, jReal x, jReal y, jReal amount, jBoolean attack, jBoolean ranged, HATTACKTYPE attackType, HDAMAGETYPE damageType, HWEAPONTYPE weaponType)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3C8770
		jmp eax
	}
}

__declspec(naked) jBoolean jNATIVE jass::UnitDamageTarget(HUNIT whichUnit, HWIDGET target, jReal amount, jBoolean attack, jBoolean ranged, HATTACKTYPE attackType, HDAMAGETYPE damageType, HWEAPONTYPE weaponType)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3C8850
		jmp eax
	}
}

__declspec(naked) jBoolean jNATIVE jass::UnitDropItemPoint(HUNIT whichUnit, HITEM whichItem, jReal x, jReal y)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3C8F30
		jmp eax
	}
}

__declspec(naked) jBoolean jNATIVE jass::UnitDropItemSlot(HUNIT whichUnit, HITEM whichItem, jInteger slot)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3C9010
		jmp eax
	}
}

__declspec(naked) jBoolean jNATIVE jass::UnitDropItemTarget(HUNIT whichUnit, HITEM whichItem, HWIDGET target)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3C8FA0
		jmp eax
	}
}

__declspec(naked) jBoolean jNATIVE jass::UnitHasBuffsEx(HUNIT whichUnit, jBoolean removePositive, jBoolean removeNegative, jBoolean magic, jBoolean physical, jBoolean timedLife, jBoolean aura, jBoolean autoDispel)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3C8360
		jmp eax
	}
}

__declspec(naked) jBoolean jNATIVE jass::UnitHasItem(HUNIT whichUnit, HITEM whichItem)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3C76F0
		jmp eax
	}
}

__declspec(naked) jInteger jNATIVE jass::UnitId(jString unitIdString)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3BB650
		jmp eax
	}
}

__declspec(naked) jString jNATIVE jass::UnitId2String(jInteger unitId)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3BB680
		jmp eax
	}
}

__declspec(naked) jBoolean jNATIVE jass::UnitIgnoreAlarm(HUNIT whichUnit, jBoolean flag)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3C8640
		jmp eax
	}
}

__declspec(naked) jBoolean jNATIVE jass::UnitIgnoreAlarmToggled(HUNIT whichUnit)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3C8690
		jmp eax
	}
}

__declspec(naked) jInteger jNATIVE jass::UnitInventorySize(HUNIT whichUnit)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3C8F00
		jmp eax
	}
}

__declspec(naked) jBoolean jNATIVE jass::UnitInvis(HUNIT arg1)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x2E07C0
		jmp eax
	}
}

__declspec(naked) jBoolean jNATIVE jass::UnitIsSleeping(HUNIT whichUnit)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3C8550
		jmp eax
	}
}

__declspec(naked) HITEM jNATIVE jass::UnitItemInSlot(HUNIT whichUnit, jInteger itemSlot)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3C7730
		jmp eax
	}
}

__declspec(naked) jBoolean jNATIVE jass::UnitMakeAbilityPermanent(HUNIT whichUnit, jBoolean permanent, jInteger abilityId)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3C8250
		jmp eax
	}
}

__declspec(naked) jBoolean jNATIVE jass::UnitModifySkillPoints(HUNIT whichHero, jInteger skillPointDelta)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3C69A0
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::UnitPauseTimedLife(HUNIT whichUnit, jBoolean flag)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3C8750
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::UnitPoolAddUnitType(HUNITPOOL whichPool, jInteger unitId, jReal weight)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3CB5E0
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::UnitPoolRemoveUnitType(HUNITPOOL whichPool, jInteger unitId)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3CB600
		jmp eax
	}
}

__declspec(naked) jBoolean jNATIVE jass::UnitRemoveAbility(HUNIT whichUnit, jInteger abilityId)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3C8310
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::UnitRemoveBuffs(HUNIT whichUnit, jBoolean removePositive, jBoolean removeNegative)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3C83E0
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::UnitRemoveBuffsEx(HUNIT whichUnit, jBoolean removePositive, jBoolean removeNegative, jBoolean magic, jBoolean physical, jBoolean timedLife, jBoolean aura, jBoolean autoDispel)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3C8410
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::UnitRemoveItem(HUNIT whichUnit, HITEM whichItem)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3C7660
		jmp eax
	}
}

__declspec(naked) HITEM jNATIVE jass::UnitRemoveItemFromSlot(HUNIT whichUnit, jInteger itemSlot)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3C76A0
		jmp eax
	}
}

__declspec(naked) jBoolean jNATIVE jass::UnitRemoveType(HUNIT whichUnit, HUNITTYPE whichUnitType)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3C7C20
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::UnitResetCooldown(HUNIT whichUnit)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3C86D0
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::UnitSetConstructionProgress(HUNIT whichUnit, jInteger constructionPercentage)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3C86F0
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::UnitSetUpgradeProgress(HUNIT whichUnit, jInteger upgradePercentage)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3C8720
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::UnitSetUsesAltIcon(HUNIT whichUnit, jBoolean flag)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3CB860
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::UnitShareVision(HUNIT whichUnit, HPLAYER whichPlayer, jBoolean share)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3C81C0
		jmp eax
	}
}

__declspec(naked) jBoolean jNATIVE jass::UnitStripHeroLevel(HUNIT whichHero, jInteger howManyLevels)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3C6930
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::UnitSuspendDecay(HUNIT whichUnit, jBoolean suspend)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3C81F0
		jmp eax
	}
}

__declspec(naked) jBoolean jNATIVE jass::UnitUseItem(HUNIT whichUnit, HITEM whichItem)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3C9090
		jmp eax
	}
}

__declspec(naked) jBoolean jNATIVE jass::UnitUseItemPoint(HUNIT whichUnit, HITEM whichItem, jReal x, jReal y)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3C9100
		jmp eax
	}
}

__declspec(naked) jBoolean jNATIVE jass::UnitUseItemTarget(HUNIT whichUnit, HITEM whichItem, HWIDGET target)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3C9170
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::UnitWakeUp(HUNIT whichUnit)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3C8590
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::UnregisterStackedSound(HSOUND soundHandle, jBoolean byPosition, jReal rectwidth, jReal rectheight)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3CCFB0
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::Unsummon(HUNIT arg1)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x2E08A0
		jmp eax
	}
}

__declspec(naked) jBoolean jNATIVE jass::VersionCompatible(HVERSION whichVersion)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3B3300
		jmp eax
	}
}

__declspec(naked) HVERSION jNATIVE jass::VersionGet()
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3B32F0
		jmp eax
	}
}

__declspec(naked) jBoolean jNATIVE jass::VersionSupported(HVERSION whichVersion)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3B3310
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::VolumeGroupReset()
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3B3E50
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::VolumeGroupSetVolume(HVOLUMEGROUP vgroup, jReal scale)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3B3E30
		jmp eax
	}
}

__declspec(naked) jBoolean jNATIVE jass::WaitGetEnemyBase()
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x2DDCF0
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::WaygateActivate(HUNIT waygate, jBoolean activate)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3C92D0
		jmp eax
	}
}

__declspec(naked) jReal jNATIVE jass::WaygateGetDestinationX(HUNIT waygate)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3C91F0
		jmp eax
	}
}

__declspec(naked) jReal jNATIVE jass::WaygateGetDestinationY(HUNIT waygate)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3C9240
		jmp eax
	}
}

__declspec(naked) jBoolean jNATIVE jass::WaygateIsActive(HUNIT waygate)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3C9310
		jmp eax
	}
}

__declspec(naked) jNothing jNATIVE jass::WaygateSetDestination(HUNIT waygate, jReal x, jReal y)
{
	_asm
	{
		mov eax, address_GameBase
		add eax, 0x3C9290
		jmp eax
	}
}