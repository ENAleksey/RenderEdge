#include "JassNatives.h"
#include "GameOffsets.h"


namespace JassNatives
{
	__declspec(naked) jInteger jNATIVE AbilityId(jString abilityIdString)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3BB5F0
			jmp eax
		}
	}

	__declspec(naked) jString jNATIVE AbilityId2String(jInteger abilityId)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3BB620
			jmp eax
		}
	}

	__declspec(naked) jReal jNATIVE Acos(jReal* x)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3B2AB0
			jmp eax
		}
	}

	__declspec(naked) jBoolean jNATIVE AddAssault(jInteger arg1, jInteger arg2)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x2DD9C0
			jmp eax
		}
	}

	__declspec(naked) jBoolean jNATIVE AddDefenders(jInteger arg1, jInteger arg2)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x2DDA00
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE AddGuardPost(jInteger arg1, jReal* arg2, jReal* arg3)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x2DCE30
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE AddHeroXP(HUNIT whichHero, jInteger xpToAdd, jBoolean showEyeCandy)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3C6CF0
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE AddIndicator(HWIDGET whichWidget, jInteger red, jInteger green, jInteger blue, jInteger alpha)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3C6C60
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE AddItemToAllStock(jInteger itemId, jInteger currentStock, jInteger stockMax)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3B3270
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE AddItemToStock(HUNIT whichUnit, jInteger itemId, jInteger currentStock, jInteger stockMax)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3C9350
			jmp eax
		}
	}

	__declspec(naked) HLIGHTNING jNATIVE AddLightning(jString codeName, jBoolean checkVisibility, jReal* x1, jReal* y1, jReal* x2, jReal* y2)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3BCC20
			jmp eax
		}
	}

	__declspec(naked) HLIGHTNING jNATIVE AddLightningEx(jString codeName, jBoolean checkVisibility, jReal* x1, jReal* y1, jReal* z1, jReal* x2, jReal* y2, jReal* z2)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3BCB30
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE AddPlayerTechResearched(HPLAYER whichPlayer, jInteger techid, jInteger levels)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3C96D0
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE AddResourceAmount(HUNIT whichUnit, jInteger amount)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3C7850
			jmp eax
		}
	}

	__declspec(naked) HEFFECT jNATIVE AddSpecialEffect(jString modelName, jReal* x, jReal* y)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3BCA90
			jmp eax
		}
	}

	__declspec(naked) HEFFECT jNATIVE AddSpecialEffectLoc(jString modelName, HLOCATION where)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3CD260
			jmp eax
		}
	}

	__declspec(naked) HEFFECT jNATIVE AddSpecialEffectTarget(jString modelName, HWIDGET targetWidget, jString attachPointName)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3CD2A0
			jmp eax
		}
	}

	__declspec(naked) HEFFECT jNATIVE AddSpellEffect(jString abilityString, HEFFECTTYPE t, jReal* x, jReal* y)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3BCB10
			jmp eax
		}
	}

	__declspec(naked) HEFFECT jNATIVE AddSpellEffectById(jInteger abilityId, HEFFECTTYPE t, jReal* x, jReal* y)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3BCAE0
			jmp eax
		}
	}

	__declspec(naked) HEFFECT jNATIVE AddSpellEffectByIdLoc(jInteger abilityId, HEFFECTTYPE t, HLOCATION where)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3CD2D0
			jmp eax
		}
	}

	__declspec(naked) HEFFECT jNATIVE AddSpellEffectLoc(jString abilityString, HEFFECTTYPE t, HLOCATION where)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3CD320
			jmp eax
		}
	}

	__declspec(naked) HEFFECT jNATIVE AddSpellEffectTarget(jString modelName, HEFFECTTYPE t, HWIDGET targetWidget, jString attachPoint)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3CD4A0
			jmp eax
		}
	}

	__declspec(naked) HEFFECT jNATIVE AddSpellEffectTargetById(jInteger abilityId, HEFFECTTYPE t, HWIDGET targetWidget, jString attachPoint)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3CD380
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE AddUnitAnimationProperties(HUNIT whichUnit, jString animProperties, jBoolean add)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3C6220
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE AddUnitToAllStock(jInteger unitId, jInteger currentStock, jInteger stockMax)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3B3290
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE AddUnitToStock(HUNIT whichUnit, jInteger unitId, jInteger currentStock, jInteger stockMax)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3C93A0
			jmp eax
		}
	}

	__declspec(naked) HWEATHEREFFECT jNATIVE AddWeatherEffect(HRECT where, jInteger effectID)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3CCFE0
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE AdjustCameraField(ECameraField whichField, jReal* offset, jReal* duration)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3B48F0
			jmp eax
		}
	}

	__declspec(naked) HBOOLEXPR jNATIVE And(HBOOLEXPR operandA, HBOOLEXPR operandB)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3D05F0
			jmp eax
		}
	}

	__declspec(naked) jReal jNATIVE Asin(jReal* y)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3B2A70
			jmp eax
		}
	}

	__declspec(naked) jReal jNATIVE Atan(jReal* x)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3B2AF0
			jmp eax
		}
	}

	__declspec(naked) jReal jNATIVE Atan2(jReal* y, jReal* x)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3B2B10
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE AttachSoundToUnit(HSOUND soundHandle, HUNIT whichUnit)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3CCE50
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE AttackMoveKill(HUNIT arg1)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x2E0A40
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE AttackMoveXY(jInteger arg1, jInteger arg2)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x2DDC10
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE CachePlayerHeroData(HPLAYER whichPlayer)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3C9DE0
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE CameraSetSmoothingFactor(jReal* factor)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3B4BB0
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE CameraSetSourceNoise(jReal* mag, jReal* velocity)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3B49E0
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE CameraSetSourceNoiseEx(jReal* mag, jReal* velocity, jBoolean vertOnly)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3B4B20
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE CameraSetTargetNoise(jReal* mag, jReal* velocity)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3B4930
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE CameraSetTargetNoiseEx(jReal* mag, jReal* velocity, jBoolean vertOnly)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3B4A70
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE CameraSetupApply(HCAMERASETUP whichSetup, jBoolean doPan, jBoolean panTimed)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3CD900
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE CameraSetupApplyForceDuration(HCAMERASETUP whichSetup, jBoolean doPan, jReal* forceDuration)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3CD960
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE CameraSetupApplyForceDurationWithZ(HCAMERASETUP whichSetup, jReal* zDestOffset, jReal* forceDuration)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3CD990
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE CameraSetupApplyWithZ(HCAMERASETUP whichSetup, jReal* zDestOffset)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3CD930
			jmp eax
		}
	}

	__declspec(naked) HLOCATION jNATIVE CameraSetupGetDestPositionLoc(HCAMERASETUP whichSetup)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3D3E40
			jmp eax
		}
	}

	__declspec(naked) jReal jNATIVE CameraSetupGetDestPositionX(HCAMERASETUP whichSetup)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3CD8C0
			jmp eax
		}
	}

	__declspec(naked) jReal jNATIVE CameraSetupGetDestPositionY(HCAMERASETUP whichSetup)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3CD8E0
			jmp eax
		}
	}

	__declspec(naked) jReal jNATIVE CameraSetupGetField(HCAMERASETUP whichSetup, ECameraField whichField)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3CD830
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE CameraSetupSetDestPosition(HCAMERASETUP whichSetup, jReal* x, jReal* y, jReal* duration)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3CD870
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE CameraSetupSetField(HCAMERASETUP whichSetup, ECameraField whichField, jReal* value, jReal* duration)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3CD800
			jmp eax
		}
	}

	__declspec(naked) jBoolean jNATIVE CaptainAtGoal()
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x2DD930
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE CaptainAttack(jReal* arg1, jReal* arg2)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x2DD700
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE CaptainGoHome()
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x2DD800
			jmp eax
		}
	}

	__declspec(naked) jInteger jNATIVE CaptainGroupSize()
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x2DDB90
			jmp eax
		}
	}

	__declspec(naked) jBoolean jNATIVE CaptainInCombat(jBoolean arg1)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x2DD8A0
			jmp eax
		}
	}

	__declspec(naked) jBoolean jNATIVE CaptainIsEmpty()
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x2DDB50
			jmp eax
		}
	}

	__declspec(naked) jBoolean jNATIVE CaptainIsFull()
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x2DDB10
			jmp eax
		}
	}

	__declspec(naked) jBoolean jNATIVE CaptainIsHome()
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x2DD870
			jmp eax
		}
	}

	__declspec(naked) jInteger jNATIVE CaptainReadiness()
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x2DDA40
			jmp eax
		}
	}

	__declspec(naked) jInteger jNATIVE CaptainReadinessHP()
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x2DDA90
			jmp eax
		}
	}

	__declspec(naked) jInteger jNATIVE CaptainReadinessMa()
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x2DDAD0
			jmp eax
		}
	}

	__declspec(naked) jBoolean jNATIVE CaptainRetreating()
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x2DD830
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE CaptainVsPlayer(HPLAYER arg1)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x2E2C80
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE CaptainVsUnits(HPLAYER arg1)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x2E2BF0
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE ChangeLevel(jString newLevel, jBoolean doScoreScreen)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3BBC30
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE Cheat(jString cheatStr)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3B3BC0
			jmp eax
		}
	}

	__declspec(naked) jInteger jNATIVE ChooseRandomCreep(jInteger level)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3B3660
			jmp eax
		}
	}

	__declspec(naked) jInteger jNATIVE ChooseRandomItem(jInteger level)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3B3690
			jmp eax
		}
	}

	__declspec(naked) jInteger jNATIVE ChooseRandomItemEx(HITEMTYPE whichType, jInteger level)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3B36B0
			jmp eax
		}
	}

	__declspec(naked) jInteger jNATIVE ChooseRandomNPBuilding()
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3B3680
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE ClearCaptainTargets()
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x2DD6C0
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE ClearHarvestAI()
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x2DD5B0
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE ClearMapMusic()
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3B3D20
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE ClearSelection()
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3BBAA0
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE ClearStackedSound(jString arg1, jReal* arg2, jReal* arg3)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3B3C80
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE ClearStackedSoundRect(jString arg1, HRECT arg2)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3CCB20
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE ClearTextMessages()
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3B4E60
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE CommandAI(HPLAYER num, jInteger command, jInteger data)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3CB7A0
			jmp eax
		}
	}

	__declspec(naked) jInteger jNATIVE CommandsWaiting()
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x2DCDD0
			jmp eax
		}
	}

	__declspec(naked) HCONDITIONFUNC jNATIVE Condition(jCode func)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3BB0A0
			jmp eax
		}
	}

	__declspec(naked) HAIDIFFICULTY jNATIVE ConvertAIDifficulty(jInteger i)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3B2690
			jmp eax
		}
	}

	__declspec(naked) HALLIANCETYPE jNATIVE ConvertAllianceType(jInteger i)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3B2610
			jmp eax
		}
	}

	__declspec(naked) HATTACKTYPE jNATIVE ConvertAttackType(jInteger i)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3B2870
			jmp eax
		}
	}

	__declspec(naked) HBLENDMODE jNATIVE ConvertBlendMode(jInteger i)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3B2810
			jmp eax
		}
	}

	__declspec(naked) ECameraField jNATIVE ConvertCameraField(jInteger i)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3B27F0
			jmp eax
		}
	}

	__declspec(naked) HDAMAGETYPE jNATIVE ConvertDamageType(jInteger i)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3B2880
			jmp eax
		}
	}

	__declspec(naked) HDIALOGEVENT jNATIVE ConvertDialogEvent(jInteger i)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3B26F0
			jmp eax
		}
	}

	__declspec(naked) HEFFECTTYPE jNATIVE ConvertEffectType(jInteger i)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3B2840
			jmp eax
		}
	}

	__declspec(naked) HFGAMESTATE jNATIVE ConvertFGameState(jInteger i)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3B2640
			jmp eax
		}
	}

	__declspec(naked) HFOGSTATE jNATIVE ConvertFogState(jInteger i)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3B2830
			jmp eax
		}
	}

	__declspec(naked) HGAMEDIFFICULTY jNATIVE ConvertGameDifficulty(jInteger i)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3B2750
			jmp eax
		}
	}

	__declspec(naked) HGAMEEVENT jNATIVE ConvertGameEvent(jInteger i)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3B26A0
			jmp eax
		}
	}

	__declspec(naked) HGAMESPEED jNATIVE ConvertGameSpeed(jInteger i)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3B2720
			jmp eax
		}
	}

	__declspec(naked) HGAMETYPE jNATIVE ConvertGameType(jInteger i)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3B2760
			jmp eax
		}
	}

	__declspec(naked) HIGAMESTATE jNATIVE ConvertIGameState(jInteger i)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3B2630
			jmp eax
		}
	}

	__declspec(naked) HITEMTYPE jNATIVE ConvertItemType(jInteger i)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3B2860
			jmp eax
		}
	}

	__declspec(naked) HLIMITOP jNATIVE ConvertLimitOp(jInteger i)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3B2700
			jmp eax
		}
	}

	__declspec(naked) HMAPCONTROL jNATIVE ConvertMapControl(jInteger i)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3B27B0
			jmp eax
		}
	}

	__declspec(naked) HMAPDENSITY jNATIVE ConvertMapDensity(jInteger i)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3B27A0
			jmp eax
		}
	}

	__declspec(naked) HMAPFLAG jNATIVE ConvertMapFlag(jInteger i)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3B2770
			jmp eax
		}
	}

	__declspec(naked) HMAPSETTING jNATIVE ConvertMapSetting(jInteger i)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3B2790
			jmp eax
		}
	}

	__declspec(naked) HMAPVISIBILITY jNATIVE ConvertMapVisibility(jInteger i)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3B2780
			jmp eax
		}
	}

	__declspec(naked) HPATHINGTYPE jNATIVE ConvertPathingType(jInteger i)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3B28B0
			jmp eax
		}
	}

	__declspec(naked) HPLACEMENT jNATIVE ConvertPlacement(jInteger i)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3B2730
			jmp eax
		}
	}

	__declspec(naked) HPLAYERCOLOR jNATIVE ConvertPlayerColor(jInteger i)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3B27C0
			jmp eax
		}
	}

	__declspec(naked) HPLAYEREVENT jNATIVE ConvertPlayerEvent(jInteger i)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3B26B0
			jmp eax
		}
	}

	__declspec(naked) HPLAYERGAMERESULT jNATIVE ConvertPlayerGameResult(jInteger i)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3B2670
			jmp eax
		}
	}

	__declspec(naked) HPLAYERSCORE jNATIVE ConvertPlayerScore(jInteger i)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3B2660
			jmp eax
		}
	}

	__declspec(naked) HPLAYERSLOTSTATE jNATIVE ConvertPlayerSlotState(jInteger i)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3B27D0
			jmp eax
		}
	}

	__declspec(naked) HPLAYERSTATE jNATIVE ConvertPlayerState(jInteger i)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3B2650
			jmp eax
		}
	}

	__declspec(naked) HPLAYERUNITEVENT jNATIVE ConvertPlayerUnitEvent(jInteger i)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3B26C0
			jmp eax
		}
	}

	__declspec(naked) HRACE jNATIVE ConvertRace(jInteger i)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3B2600
			jmp eax
		}
	}

	__declspec(naked) HRACEPREFERENCE jNATIVE ConvertRacePref(jInteger i)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3B2620
			jmp eax
		}
	}

	__declspec(naked) HRARITYCONTROL jNATIVE ConvertRarityControl(jInteger i)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3B2800
			jmp eax
		}
	}

	__declspec(naked) HSOUNDTYPE jNATIVE ConvertSoundType(jInteger i)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3B28A0
			jmp eax
		}
	}

	__declspec(naked) HSTARTLOCPRIO jNATIVE ConvertStartLocPrio(jInteger i)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3B2740
			jmp eax
		}
	}

	__declspec(naked) HTEXMAPFLAGS jNATIVE ConvertTexMapFlags(jInteger i)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3B2820
			jmp eax
		}
	}

	__declspec(naked) HUNITEVENT jNATIVE ConvertUnitEvent(jInteger i)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3B26D0
			jmp eax
		}
	}

	__declspec(naked) HUNITSTATE jNATIVE ConvertUnitState(jInteger i)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3B2680
			jmp eax
		}
	}

	__declspec(naked) HUNITTYPE jNATIVE ConvertUnitType(jInteger i)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3B2710
			jmp eax
		}
	}

	__declspec(naked) jBoolean jNATIVE ConvertUnits(jInteger arg1, jInteger arg2)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x2DD2E0
			jmp eax
		}
	}

	__declspec(naked) HVERSION jNATIVE ConvertVersion(jInteger i)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3B2850
			jmp eax
		}
	}

	__declspec(naked) HVOLUMEGROUP jNATIVE ConvertVolumeGroup(jInteger i)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3B27E0
			jmp eax
		}
	}

	__declspec(naked) HWEAPONTYPE jNATIVE ConvertWeaponType(jInteger i)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3B2890
			jmp eax
		}
	}

	__declspec(naked) HWIDGETEVENT jNATIVE ConvertWidgetEvent(jInteger i)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3B26E0
			jmp eax
		}
	}

	__declspec(naked) jBoolean jNATIVE CopySaveGame(jString sourceSaveName, jString destSaveName)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3BC180
			jmp eax
		}
	}

	__declspec(naked) jReal jNATIVE Cos(jReal* radians)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3B2A30
			jmp eax
		}
	}

	__declspec(naked) HUNIT jNATIVE CreateBlightedGoldmine(HPLAYER id, jReal* x, jReal* y, jReal* face)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3CD630
			jmp eax
		}
	}

	__declspec(naked) HCAMERASETUP jNATIVE CreateCameraSetup()
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3D3D40
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE CreateCaptains()
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x2DD960
			jmp eax
		}
	}

	__declspec(naked) HUNIT jNATIVE CreateCorpse(HPLAYER whichPlayer, jInteger unitid, jReal* x, jReal* y, jReal* face)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3C5350
			jmp eax
		}
	}

	__declspec(naked) HDESTRUCTABLE jNATIVE CreateDeadDestructable(jInteger objectid, jReal* x, jReal* y, jReal* face, jReal* scale, jInteger variation)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3BB840
			jmp eax
		}
	}

	__declspec(naked) HDESTRUCTABLE jNATIVE CreateDeadDestructableZ(jInteger objectid, jReal* x, jReal* y, jReal* z, jReal* face, jReal* scale, jInteger variation)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3BB890
			jmp eax
		}
	}

	__declspec(naked) HDEFEATCONDITION jNATIVE CreateDefeatCondition()
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3BC9E0
			jmp eax
		}
	}

	__declspec(naked) HDESTRUCTABLE jNATIVE CreateDestructable(jInteger objectid, jReal* x, jReal* y, jReal* face, jReal* scale, jInteger variation)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3BB790
			jmp eax
		}
	}

	__declspec(naked) HDESTRUCTABLE jNATIVE CreateDestructableZ(jInteger objectid, jReal* x, jReal* y, jReal* z, jReal* face, jReal* scale, jInteger variation)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3BB7E0
			jmp eax
		}
	}

	__declspec(naked) HFOGMODIFIER jNATIVE CreateFogModifierRadius(HPLAYER forWhichPlayer, HFOGSTATE whichState, jReal* centerx, jReal* centerY, jReal* radius, jBoolean useSharedVision, jBoolean afterUnits)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3D0F90
			jmp eax
		}
	}

	__declspec(naked) HFOGMODIFIER jNATIVE CreateFogModifierRadiusLoc(HPLAYER forWhichPlayer, HFOGSTATE whichState, HLOCATION center, jReal* radius, jBoolean useSharedVision, jBoolean afterUnits)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3D10F0
			jmp eax
		}
	}

	__declspec(naked) HFOGMODIFIER jNATIVE CreateFogModifierRect(HPLAYER forWhichPlayer, HFOGSTATE whichState, HRECT where, jBoolean useSharedVision, jBoolean afterUnits)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3D0E70
			jmp eax
		}
	}

	__declspec(naked) HFORCE jNATIVE CreateForce()
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3D29F0
			jmp eax
		}
	}

	__declspec(naked) HGROUP jNATIVE CreateGroup()
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3D2900
			jmp eax
		}
	}

	__declspec(naked) HIMAGE jNATIVE CreateImage(jString file, jReal* sizeX, jReal* sizeY, jReal* sizeZ, jReal* posX, jReal* posY, jReal* posZ, jReal* originX, jReal* originY, jReal* originZ, jInteger imageType)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3B4320
			jmp eax
		}
	}

	__declspec(naked) HITEM jNATIVE CreateItem(jInteger itemid, jReal* x, jReal* y)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3BB9A0
			jmp eax
		}
	}

	__declspec(naked) HITEMPOOL jNATIVE CreateItemPool()
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3D2FC0
			jmp eax
		}
	}

	__declspec(naked) HLEADERBOARD jNATIVE CreateLeaderboard()
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3D35B0
			jmp eax
		}
	}

	__declspec(naked) HSOUND jNATIVE CreateMIDISound(jString soundLabel, jInteger fadeInRate, jInteger fadeOutRate)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3D3C30
			jmp eax
		}
	}

	__declspec(naked) HMULTIBOARD jNATIVE CreateMultiboard()
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3D36B0
			jmp eax
		}
	}

	__declspec(naked) HQUEST jNATIVE CreateQuest()
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3BC970
			jmp eax
		}
	}

	__declspec(naked) HREGION jNATIVE CreateRegion()
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3D0930
			jmp eax
		}
	}

	__declspec(naked) HSOUND jNATIVE CreateSound(jString fileName, jBoolean looping, jBoolean is3D, jBoolean stopwhenoutofrange, jInteger fadeInRate, jInteger fadeOutRate, jString eaxSetting)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3D38D0
			jmp eax
		}
	}

	__declspec(naked) HSOUND jNATIVE CreateSoundFilenameWithLabel(jString fileName, jBoolean looping, jBoolean is3D, jBoolean stopwhenoutofrange, jInteger fadeInRate, jInteger fadeOutRate, jString SLKEntryName)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3D39F0
			jmp eax
		}
	}

	__declspec(naked) HSOUND jNATIVE CreateSoundFromLabel(jString soundLabel, jBoolean looping, jBoolean is3D, jBoolean stopwhenoutofrange, jInteger fadeInRate, jInteger fadeOutRate)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3D3B10
			jmp eax
		}
	}

	__declspec(naked) HTEXTTAG jNATIVE CreateTextTag()
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3BC580
			jmp eax
		}
	}

	__declspec(naked) HTIMER jNATIVE CreateTimer()
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3D0500
			jmp eax
		}
	}

	__declspec(naked) HTIMERDIALOG jNATIVE CreateTimerDialog(HTIMER t)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3D34B0
			jmp eax
		}
	}

	__declspec(naked) HTRACKABLE jNATIVE CreateTrackable(jString trackableModelPath, jReal* x, jReal* y, jReal* facing)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3D30B0
			jmp eax
		}
	}

	__declspec(naked) jTrigger jNATIVE CreateTrigger()
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3D11F0
			jmp eax
		}
	}

	__declspec(naked) HUBERSPLAT jNATIVE CreateUbersplat(jReal* x, jReal* y, jString name, jInteger red, jInteger green, jInteger blue, jInteger alpha, jBoolean forcePaused, jBoolean noBirthTime)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3B85F0
			jmp eax
		}
	}

	__declspec(naked) HUNIT jNATIVE CreateUnit(HPLAYER id, jInteger unitid, jReal* x, jReal* y, jReal* face)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3C5230
			jmp eax
		}
	}

	__declspec(naked) HUNIT jNATIVE CreateUnitAtLoc(HPLAYER id, jInteger unitid, HLOCATION whichLocation, jReal* face)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3C52D0
			jmp eax
		}
	}

	__declspec(naked) HUNIT jNATIVE CreateUnitAtLocByName(HPLAYER id, jString unitname, HLOCATION whichLocation, jReal* face)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3C5320
			jmp eax
		}
	}

	__declspec(naked) HUNIT jNATIVE CreateUnitByName(HPLAYER whichPlayer, jString unitname, jReal* x, jReal* y, jReal* face)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3C52A0
			jmp eax
		}
	}

	__declspec(naked) HUNITPOOL jNATIVE CreateUnitPool()
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3D2ED0
			jmp eax
		}
	}

	__declspec(naked) jBoolean jNATIVE CreepsOnMap()
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x2DC0F0
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE CripplePlayer(HPLAYER whichPlayer, HFORCE toWhichPlayers, jBoolean flag)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3C1310
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE DebugBreak(jInteger arg1)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x2DC050
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE DebugFI(jString arg1, jInteger arg2)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x2DC0B0
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE DebugS(jString arg1)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x2DC0A0
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE DebugUnitID(jString arg1, jInteger arg2)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x2DC0C0
			jmp eax
		}
	}

	__declspec(naked) jInteger jNATIVE DecUnitAbilityLevel(HUNIT whichUnit, jInteger abilcode)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3C70B0
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE DefeatConditionSetDescription(HDEFEATCONDITION whichCondition, jString description)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3CBE00
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE DefineStartLocation(jInteger whichStartLoc, jReal* x, jReal* y)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3BAF70
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE DefineStartLocationLoc(jInteger whichStartLoc, HLOCATION whichLocation)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3C0EA0
			jmp eax
		}
	}

	__declspec(naked) jReal jNATIVE Deg2Rad(jReal* degrees)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3B29D0
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE DestroyBoolExpr(HBOOLEXPR e)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3C14A0
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE DestroyCondition(HCONDITIONFUNC c)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3C1440
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE DestroyDefeatCondition(HDEFEATCONDITION whichCondition)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3CBDB0
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE DestroyEffect(HEFFECT whichEffect)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3CD240
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE DestroyFilter(HFILTERFUNC f)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3C1470
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE DestroyFogModifier(HFOGMODIFIER whichFogModifier)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3C1BA0
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE DestroyForce(HFORCE whichForce)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3C44C0
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE DestroyGroup(HGROUP whichGroup)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3C3FA0
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE DestroyImage(HIMAGE whichImage)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3B43B0
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE DestroyItemPool(HITEMPOOL whichItemPool)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3CB6A0
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE DestroyLeaderboard(HLEADERBOARD lb)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3CBFD0
			jmp eax
		}
	}

	__declspec(naked) jBoolean jNATIVE DestroyLightning(HLIGHTNING whichBolt)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3B4150
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE DestroyMultiboard(HMULTIBOARD lb)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3CC650
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE DestroyQuest(HQUEST whichQuest)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3CBB20
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE DestroyTextTag(HTEXTTAG t)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3BC5A0
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE DestroyTimer(HTIMER whichTimer)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3C1350
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE DestroyTimerDialog(HTIMERDIALOG whichDialog)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3CBE30
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE DestroyTrigger(jTrigger whichTrigger)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3C1C00
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE DestroyUbersplat(HUBERSPLAT whichSplat)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3B44C0
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE DestroyUnitPool(HUNITPOOL whichPool)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3CB5C0
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE DestructableRestoreLife(HDESTRUCTABLE d, jReal* life, jBoolean birth)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3C4870
			jmp eax
		}
	}

	__declspec(naked) HBUTTON jNATIVE DialogAddButton(HDIALOG whichDialog, jString buttonText, jInteger hotkey)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3C9F90
			jmp eax
		}
	}

	__declspec(naked) HBUTTON jNATIVE DialogAddQuitButton(HDIALOG whichDialog, jBoolean doScoreScreen, jString buttonText, jInteger hotkey)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3C9FE0
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE DialogClear(HDIALOG whichDialog)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3C9F40
			jmp eax
		}
	}

	__declspec(naked) HDIALOG jNATIVE DialogCreate()
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3D2BC0
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE DialogDestroy(HDIALOG whichDialog)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3C9F00
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE DialogDisplay(HPLAYER whichPlayer, HDIALOG whichDialog, jBoolean flag)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3CA030
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE DialogSetAsync(HDIALOG arg1)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3C9F20
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE DialogSetMessage(HDIALOG whichDialog, jString messageText)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3C9F60
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE DisablePathing()
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x2E06E0
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE DisableRestartMission(jBoolean flag)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3B38C0
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE DisableTrigger(jTrigger whichTrigger)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3C1C60
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE DisplayCineFilter(jBoolean flag)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3B5120
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE DisplayLoadDialog()
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3B3A10
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE DisplayText(jInteger arg1, jString arg2)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x2DC060
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE DisplayTextI(jInteger arg1, jString arg2, jInteger arg3)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x2DC070
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE DisplayTextII(jInteger arg1, jString arg2, jInteger arg3, jInteger arg4)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x2DC080
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE DisplayTextIII(jInteger arg1, jString arg2, jInteger arg3, jInteger arg4, jInteger arg5)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x2DC090
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE DisplayTextToPlayer(HPLAYER toPlayer, jReal* x, jReal* y, jString msg)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3CB900
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE DisplayTimedTextFromPlayer(HPLAYER toPlayer, jReal* x, jReal* y, jReal* duration, jString msg)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3CBA30
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE DisplayTimedTextToPlayer(HPLAYER toPlayer, jReal* x, jReal* y, jReal* duration, jString msg)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3CB9B0
			jmp eax
		}
	}

	__declspec(naked) jBoolean jNATIVE DoAiScriptDebug()
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x2DC0D0
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE DoNotSaveReplay()
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3B3550
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE EnableDragSelect(jBoolean state, jBoolean ui)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3B3B30
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE EnableMinimapFilterButtons(jBoolean enableAlly, jBoolean enableCreep)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3B3AF0
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE EnableOcclusion(jBoolean flag)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3B3B90
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE EnablePreSelect(jBoolean state, jBoolean ui)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3B3B50
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE EnableSelect(jBoolean state, jBoolean ui)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3B3B70
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE EnableTrigger(jTrigger whichTrigger)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3C1C40
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE EnableUserControl(jBoolean b)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3B3880
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE EnableUserUI(jBoolean b)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3B38A0
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE EnableWeatherEffect(HWEATHEREFFECT whichEffect, jBoolean enable)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3B3E80
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE EnableWorldFogBoundary(jBoolean b)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3B3BB0
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE EndCinematicScene()
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3B4E20
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE EndGame(jBoolean doScoreScreen)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3BBBB0
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE EndThematicMusic()
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3B3DE0
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE EnumDestructablesInRect(HRECT r, HBOOLEXPR filter, jCode actionFunc)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3C4A90
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE EnumItemsInRect(HRECT r, HBOOLEXPR filter, jCode actionFunc)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3C5110
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE ExecuteFunc(jString funcName)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3D3F30
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE FillGuardPosts()
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x2DCF80
			jmp eax
		}
	}

	__declspec(naked) HFILTERFUNC jNATIVE Filter(jCode func)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3BB140
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE FinishUbersplat(HUBERSPLAT whichSplat)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3B44E0
			jmp eax
		}
	}

	__declspec(naked) HUNIT jNATIVE FirstOfGroup(HGROUP whichGroup)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3C4460
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE FlashQuestDialogButton()
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3BC920
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE FlushChildHashtable(HHASHTABLE table, jInteger parentKey)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3CB590
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE FlushGameCache(HGAMECACHE cache)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3CB200
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE FlushParentHashtable(HHASHTABLE table)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3CB550
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE FlushStoredBoolean(HGAMECACHE cache, jString missionKey, jString key)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3CB320
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE FlushStoredInteger(HGAMECACHE cache, jString missionKey, jString key)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3CB280
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE FlushStoredMission(HGAMECACHE cache, jString missionKey)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3CB240
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE FlushStoredReal(HGAMECACHE cache, jString missionKey, jString key)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3CB2D0
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE FlushStoredString(HGAMECACHE cache, jString missionKey, jString key)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3CB3C0
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE FlushStoredUnit(HGAMECACHE cache, jString missionKey, jString key)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3CB370
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE FogEnable(jBoolean enable)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3BB1E0
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE FogMaskEnable(jBoolean enable)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3BB210
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE FogModifierStart(HFOGMODIFIER whichFogModifier)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3C1BC0
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE FogModifierStop(HFOGMODIFIER whichFogModifier)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3C1BE0
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE ForForce(HFORCE whichForce, jCode callback)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3C4640
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE ForGroup(HGROUP whichGroup, jCode callback)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3C44A0
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE ForceAddPlayer(HFORCE whichForce, HPLAYER whichPlayer)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3C44E0
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE ForceCampaignSelectScreen()
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3BC400
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE ForceCinematicSubtitles(jBoolean flag)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3B4E40
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE ForceClear(HFORCE whichForce)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3C4540
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE ForceEnumAllies(HFORCE whichForce, HPLAYER whichPlayer, HBOOLEXPR filter)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3C45C0
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE ForceEnumEnemies(HFORCE whichForce, HPLAYER whichPlayer, HBOOLEXPR filter)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3C4600
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE ForceEnumPlayers(HFORCE whichForce, HBOOLEXPR filter)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3C4560
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE ForceEnumPlayersCounted(HFORCE whichForce, HBOOLEXPR filter, jInteger countLimit)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3C4590
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE ForcePlayerStartLocation(HPLAYER whichPlayer, jInteger startLocIndex)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3C0FA0
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE ForceQuestDialogUpdate()
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3B3BE0
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE ForceRemovePlayer(HFORCE whichForce, HPLAYER whichPlayer)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3C4510
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE ForceUICancel()
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3B3990
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE ForceUIKey(jString key)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3B38E0
			jmp eax
		}
	}

	__declspec(naked) HAIDIFFICULTY jNATIVE GetAIDifficulty(HPLAYER num)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3CB7E0
			jmp eax
		}
	}

	__declspec(naked) jString jNATIVE GetAbilityEffect(jString abilityString, HEFFECTTYPE t, jInteger index)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3BCAB0
			jmp eax
		}
	}

	__declspec(naked) jString jNATIVE GetAbilityEffectById(jInteger abilityId, HEFFECTTYPE t, jInteger index)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3BCE40
			jmp eax
		}
	}

	__declspec(naked) jString jNATIVE GetAbilitySound(jString abilityString, HSOUNDTYPE t)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3BCE60
			jmp eax
		}
	}

	__declspec(naked) jString jNATIVE GetAbilitySoundById(jInteger abilityId, HSOUNDTYPE t)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3BCEA0
			jmp eax
		}
	}

	__declspec(naked) jInteger jNATIVE GetAiPlayer()
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x2DCFE0
			jmp eax
		}
	}

	__declspec(naked) HUNIT jNATIVE GetAllianceTarget()
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x2DD570
			jmp eax
		}
	}

	__declspec(naked) jInteger jNATIVE GetAllyColorFilterState()
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3B3A50
			jmp eax
		}
	}

	__declspec(naked) HUNIT jNATIVE GetAttacker()
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3C20F0
			jmp eax
		}
	}

	__declspec(naked) HUNIT jNATIVE GetBuilding(HPLAYER arg1)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x2E2E80
			jmp eax
		}
	}

	__declspec(naked) HUNIT jNATIVE GetBuyingUnit()
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3C27B0
			jmp eax
		}
	}

	__declspec(naked) jReal jNATIVE GetCameraBoundMaxX()
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3B4C90
			jmp eax
		}
	}

	__declspec(naked) jReal jNATIVE GetCameraBoundMaxY()
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3B4CB0
			jmp eax
		}
	}

	__declspec(naked) jReal jNATIVE GetCameraBoundMinX()
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3B4C50
			jmp eax
		}
	}

	__declspec(naked) jReal jNATIVE GetCameraBoundMinY()
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3B4C70
			jmp eax
		}
	}

	__declspec(naked) HLOCATION jNATIVE GetCameraEyePositionLoc()
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3D3EE0
			jmp eax
		}
	}

	__declspec(naked) jReal jNATIVE GetCameraEyePositionX()
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3B4D90
			jmp eax
		}
	}

	__declspec(naked) jReal jNATIVE GetCameraEyePositionY()
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3B4DC0
			jmp eax
		}
	}

	__declspec(naked) jReal jNATIVE GetCameraEyePositionZ()
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3B4DF0
			jmp eax
		}
	}

	__declspec(naked) jReal jNATIVE GetCameraField(ECameraField whichField)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3B4CD0
			jmp eax
		}
	}

	__declspec(naked) jReal jNATIVE GetCameraMargin(jInteger whichMargin)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3B4BE0
			jmp eax
		}
	}

	__declspec(naked) HLOCATION jNATIVE GetCameraTargetPositionLoc()
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3D3E90
			jmp eax
		}
	}

	__declspec(naked) jReal jNATIVE GetCameraTargetPositionX()
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3B4D00
			jmp eax
		}
	}

	__declspec(naked) jReal jNATIVE GetCameraTargetPositionY()
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3B4D30
			jmp eax
		}
	}

	__declspec(naked) jReal jNATIVE GetCameraTargetPositionZ()
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3B4D60
			jmp eax
		}
	}

	__declspec(naked) HUNIT jNATIVE GetCancelledStructure()
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3BB470
			jmp eax
		}
	}

	__declspec(naked) HUNIT jNATIVE GetChangingUnit()
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3C2680
			jmp eax
		}
	}

	__declspec(naked) HPLAYER jNATIVE GetChangingUnitPrevOwner()
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3C26E0
			jmp eax
		}
	}

	__declspec(naked) HBUTTON jNATIVE GetClickedButton()
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3C1DE0
			jmp eax
		}
	}

	__declspec(naked) HDIALOG jNATIVE GetClickedDialog()
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3C1E30
			jmp eax
		}
	}

	__declspec(naked) HUNIT jNATIVE GetConstructedStructure()
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3BB490
			jmp eax
		}
	}

	__declspec(naked) HUNIT jNATIVE GetConstructingStructure()
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3BB450
			jmp eax
		}
	}

	__declspec(naked) HMAPDENSITY jNATIVE GetCreatureDensity()
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3BAF60
			jmp eax
		}
	}

	__declspec(naked) HUNIT jNATIVE GetCreepCamp(jInteger arg1, jInteger arg2, jBoolean arg3)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x2E3D50
			jmp eax
		}
	}

	__declspec(naked) jBoolean jNATIVE GetCreepCampFilterState()
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3B3AA0
			jmp eax
		}
	}

	__declspec(naked) jBoolean jNATIVE GetCustomCampaignButtonVisible(jInteger whichButton)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3B3530
			jmp eax
		}
	}

	__declspec(naked) HUNIT jNATIVE GetDecayingUnit()
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3BB430
			jmp eax
		}
	}

	__declspec(naked) HGAMEDIFFICULTY jNATIVE GetDefaultDifficulty()
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3B33A0
			jmp eax
		}
	}

	__declspec(naked) jReal jNATIVE GetDestructableLife(HDESTRUCTABLE d)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3C4890
			jmp eax
		}
	}

	__declspec(naked) jReal jNATIVE GetDestructableMaxLife(HDESTRUCTABLE d)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3C4920
			jmp eax
		}
	}

	__declspec(naked) jString jNATIVE GetDestructableName(HDESTRUCTABLE d)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3C4C10
			jmp eax
		}
	}

	__declspec(naked) jReal jNATIVE GetDestructableOccluderHeight(HDESTRUCTABLE d)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3C4BB0
			jmp eax
		}
	}

	__declspec(naked) jInteger jNATIVE GetDestructableTypeId(HDESTRUCTABLE d)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3C47B0
			jmp eax
		}
	}

	__declspec(naked) jReal jNATIVE GetDestructableX(HDESTRUCTABLE d)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3C47D0
			jmp eax
		}
	}

	__declspec(naked) jReal jNATIVE GetDestructableY(HDESTRUCTABLE d)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3C4810
			jmp eax
		}
	}

	__declspec(naked) HUNIT jNATIVE GetDetectedUnit()
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3BB4B0
			jmp eax
		}
	}

	__declspec(naked) HUNIT jNATIVE GetDyingUnit()
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3BB410
			jmp eax
		}
	}

	__declspec(naked) HUNIT jNATIVE GetEnemyBase()
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x2DDD20
			jmp eax
		}
	}

	__declspec(naked) HUNIT jNATIVE GetEnemyExpansion()
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x2DD4F0
			jmp eax
		}
	}

	__declspec(naked) jInteger jNATIVE GetEnemyPower()
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x2DC150
			jmp eax
		}
	}

	__declspec(naked) HUNIT jNATIVE GetEnteringUnit()
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3BB6D0
			jmp eax
		}
	}

	__declspec(naked) HDESTRUCTABLE jNATIVE GetEnumDestructable()
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3BB360
			jmp eax
		}
	}

	__declspec(naked) HITEM jNATIVE GetEnumItem()
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3BB3A0
			jmp eax
		}
	}

	__declspec(naked) HPLAYER jNATIVE GetEnumPlayer()
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3BB320
			jmp eax
		}
	}

	__declspec(naked) HUNIT jNATIVE GetEnumUnit()
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3BB300
			jmp eax
		}
	}

	__declspec(naked) jReal jNATIVE GetEventDamage()
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3C3C40
			jmp eax
		}
	}

	__declspec(naked) HUNIT jNATIVE GetEventDamageSource()
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3C3C60
			jmp eax
		}
	}

	__declspec(naked) HPLAYER jNATIVE GetEventDetectingPlayer()
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3C3CB0
			jmp eax
		}
	}

	__declspec(naked) HGAMESTATE jNATIVE GetEventGameState()
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3C2020
			jmp eax
		}
	}

	__declspec(naked) jString jNATIVE GetEventPlayerChatString()
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3C20B0
			jmp eax
		}
	}

	__declspec(naked) jString jNATIVE GetEventPlayerChatStringMatched()
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3C2080
			jmp eax
		}
	}

	__declspec(naked) HPLAYERSTATE jNATIVE GetEventPlayerState()
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3C2050
			jmp eax
		}
	}

	__declspec(naked) HUNIT jNATIVE GetEventTargetUnit()
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3C3D00
			jmp eax
		}
	}

	__declspec(naked) HUNITSTATE jNATIVE GetEventUnitState()
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3C3C10
			jmp eax
		}
	}

	__declspec(naked) HUNIT jNATIVE GetExpansionFoe()
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x2E2E40
			jmp eax
		}
	}

	__declspec(naked) HUNIT jNATIVE GetExpansionPeon()
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x2DD530
			jmp eax
		}
	}

	__declspec(naked) jInteger jNATIVE GetExpansionX()
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x2E2DA0
			jmp eax
		}
	}

	__declspec(naked) jInteger jNATIVE GetExpansionY()
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x2E2DF0
			jmp eax
		}
	}

	__declspec(naked) HTIMER jNATIVE GetExpiredTimer()
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3C1D80
			jmp eax
		}
	}

	__declspec(naked) HDESTRUCTABLE jNATIVE GetFilterDestructable()
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3BB380
			jmp eax
		}
	}

	__declspec(naked) HITEM jNATIVE GetFilterItem()
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3BB3C0
			jmp eax
		}
	}

	__declspec(naked) HPLAYER jNATIVE GetFilterPlayer()
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3BB340
			jmp eax
		}
	}

	__declspec(naked) HUNIT jNATIVE GetFilterUnit()
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3BB2E0
			jmp eax
		}
	}

	__declspec(naked) jReal jNATIVE GetFloatGameState(HFGAMESTATE whichFloatGameState)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3BC310
			jmp eax
		}
	}

	__declspec(naked) jInteger jNATIVE GetFoodMade(jInteger unitId)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3B2E00
			jmp eax
		}
	}

	__declspec(naked) jInteger jNATIVE GetFoodUsed(jInteger unitId)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3B2E10
			jmp eax
		}
	}

	__declspec(naked) HGAMEDIFFICULTY jNATIVE GetGameDifficulty()
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3BAF20
			jmp eax
		}
	}

	__declspec(naked) HPLACEMENT jNATIVE GetGamePlacement()
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3BAF00
			jmp eax
		}
	}

	__declspec(naked) HGAMESPEED jNATIVE GetGameSpeed()
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3BAEC0
			jmp eax
		}
	}

	__declspec(naked) HGAMETYPE jNATIVE GetGameTypeSelected()
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3BAE60
			jmp eax
		}
	}

	__declspec(naked) jInteger jNATIVE GetGoldOwned()
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x2DE000
			jmp eax
		}
	}

	__declspec(naked) jInteger jNATIVE GetHandleId(HHANDLE2 h)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3B2D00
			jmp eax
		}
	}

	__declspec(naked) jInteger jNATIVE GetHeroAgi(HUNIT whichHero, jBoolean includeBonuses)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3C6850
			jmp eax
		}
	}

	__declspec(naked) jInteger jNATIVE GetHeroId()
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x2DDF50
			jmp eax
		}
	}

	__declspec(naked) jInteger jNATIVE GetHeroInt(HUNIT whichHero, jBoolean includeBonuses)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3C68C0
			jmp eax
		}
	}

	__declspec(naked) jInteger jNATIVE GetHeroLevel(HUNIT whichHero)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3C6ED0
			jmp eax
		}
	}

	__declspec(naked) jInteger jNATIVE GetHeroLevelAI()
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x2DE0E0
			jmp eax
		}
	}

	__declspec(naked) jString jNATIVE GetHeroProperName(HUNIT whichHero)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3C6FA0
			jmp eax
		}
	}

	__declspec(naked) jInteger jNATIVE GetHeroSkillPoints(HUNIT whichHero)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3C6780
			jmp eax
		}
	}

	__declspec(naked) jInteger jNATIVE GetHeroStr(HUNIT whichHero, jBoolean includeBonuses)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3C67E0
			jmp eax
		}
	}

	__declspec(naked) jInteger jNATIVE GetHeroXP(HUNIT whichHero)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3C6A10
			jmp eax
		}
	}

	__declspec(naked) jInteger jNATIVE GetIntegerGameState(HIGAMESTATE whichIntegerGameState)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3BC380
			jmp eax
		}
	}

	__declspec(naked) jInteger jNATIVE GetIssuedOrderId()
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3C2C80
			jmp eax
		}
	}

	__declspec(naked) jInteger jNATIVE GetItemCharges(HITEM whichItem)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3C5050
			jmp eax
		}
	}

	__declspec(naked) jInteger jNATIVE GetItemLevel(HITEM whichItem)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3C4E50
			jmp eax
		}
	}

	__declspec(naked) jString jNATIVE GetItemName(HITEM whichItem)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3C4E90
			jmp eax
		}
	}

	__declspec(naked) HPLAYER jNATIVE GetItemPlayer(HITEM whichItem)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3C4E10
			jmp eax
		}
	}

	__declspec(naked) HITEMTYPE jNATIVE GetItemType(HITEM whichItem)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3C4E70
			jmp eax
		}
	}

	__declspec(naked) jInteger jNATIVE GetItemTypeId(HITEM i)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3C4C60
			jmp eax
		}
	}

	__declspec(naked) jInteger jNATIVE GetItemUserData(HITEM whichItem)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3C50D0
			jmp eax
		}
	}

	__declspec(naked) jReal jNATIVE GetItemX(HITEM i)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3C4D90
			jmp eax
		}
	}

	__declspec(naked) jReal jNATIVE GetItemY(HITEM i)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3C4DD0
			jmp eax
		}
	}

	__declspec(naked) HUNIT jNATIVE GetKillingUnit()
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3C23F0
			jmp eax
		}
	}

	__declspec(naked) jInteger jNATIVE GetLastCommand()
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x2E0450
			jmp eax
		}
	}

	__declspec(naked) jInteger jNATIVE GetLastData()
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x2E0490
			jmp eax
		}
	}

	__declspec(naked) jInteger jNATIVE GetLearnedSkill()
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3C2210
			jmp eax
		}
	}

	__declspec(naked) jInteger jNATIVE GetLearnedSkillLevel()
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3C2250
			jmp eax
		}
	}

	__declspec(naked) HUNIT jNATIVE GetLearningUnit()
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3C21B0
			jmp eax
		}
	}

	__declspec(naked) HUNIT jNATIVE GetLeavingUnit()
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3BB6F0
			jmp eax
		}
	}

	__declspec(naked) HUNIT jNATIVE GetLevelingUnit()
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3C2150
			jmp eax
		}
	}

	__declspec(naked) jReal jNATIVE GetLightningColorA(HLIGHTNING whichBolt)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3B8310
			jmp eax
		}
	}

	__declspec(naked) jReal jNATIVE GetLightningColorB(HLIGHTNING whichBolt)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3B8430
			jmp eax
		}
	}

	__declspec(naked) jReal jNATIVE GetLightningColorG(HLIGHTNING whichBolt)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3B83D0
			jmp eax
		}
	}

	__declspec(naked) jReal jNATIVE GetLightningColorR(HLIGHTNING whichBolt)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3B8370
			jmp eax
		}
	}

	__declspec(naked) HUNIT jNATIVE GetLoadedUnit()
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3C2A00
			jmp eax
		}
	}

	__declspec(naked) HPLAYER jNATIVE GetLocalPlayer()
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3BBB60
			jmp eax
		}
	}

	__declspec(naked) jInteger jNATIVE GetLocalizedHotkey(jString source)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3B2D80
			jmp eax
		}
	}

	__declspec(naked) jString jNATIVE GetLocalizedString(jString source)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3BACF0
			jmp eax
		}
	}

	__declspec(naked) jReal jNATIVE GetLocationX(HLOCATION whichLocation)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3C0E10
			jmp eax
		}
	}

	__declspec(naked) jReal jNATIVE GetLocationY(HLOCATION whichLocation)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3C0E30
			jmp eax
		}
	}

	__declspec(naked) jReal jNATIVE GetLocationZ(HLOCATION whichLocation)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3C0E50
			jmp eax
		}
	}

	__declspec(naked) HITEM jNATIVE GetManipulatedItem()
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3C2B00
			jmp eax
		}
	}

	__declspec(naked) HUNIT jNATIVE GetManipulatingUnit()
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3C2A60
			jmp eax
		}
	}

	__declspec(naked) HUNIT jNATIVE GetMegaTarget()
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x2DDD60
			jmp eax
		}
	}

	__declspec(naked) jInteger jNATIVE GetMinesOwned()
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x2DDFD0
			jmp eax
		}
	}

	__declspec(naked) jInteger jNATIVE GetNextExpansion()
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x2E2BC0
			jmp eax
		}
	}

	__declspec(naked) jString jNATIVE GetObjectName(jInteger objectId)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3BB6B0
			jmp eax
		}
	}

	__declspec(naked) HLOCATION jNATIVE GetOrderPointLoc()
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3D1FF0
			jmp eax
		}
	}

	__declspec(naked) jReal jNATIVE GetOrderPointX()
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3C2D00
			jmp eax
		}
	}

	__declspec(naked) jReal jNATIVE GetOrderPointY()
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3C2D50
			jmp eax
		}
	}

	__declspec(naked) HWIDGET jNATIVE GetOrderTarget()
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3C2DE0
			jmp eax
		}
	}

	__declspec(naked) HDESTRUCTABLE jNATIVE GetOrderTargetDestructable()
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3C2F10
			jmp eax
		}
	}

	__declspec(naked) HITEM jNATIVE GetOrderTargetItem()
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3C3040
			jmp eax
		}
	}

	__declspec(naked) HUNIT jNATIVE GetOrderTargetUnit()
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3C3170
			jmp eax
		}
	}

	__declspec(naked) HUNIT jNATIVE GetOrderedUnit()
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3BB530
			jmp eax
		}
	}

	__declspec(naked) HPLAYER jNATIVE GetOwningPlayer(HUNIT whichUnit)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3C8190
			jmp eax
		}
	}

	__declspec(naked) jBoolean jNATIVE GetPlayerAlliance(HPLAYER sourcePlayer, HPLAYER otherPlayer, HALLIANCETYPE whichAllianceSetting)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3C9D70
			jmp eax
		}
	}

	__declspec(naked) HPLAYERCOLOR jNATIVE GetPlayerColor(HPLAYER whichPlayer)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3C1240
			jmp eax
		}
	}

	__declspec(naked) HMAPCONTROL jNATIVE GetPlayerController(HPLAYER whichPlayer)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3C12B0
			jmp eax
		}
	}

	__declspec(naked) jReal jNATIVE GetPlayerHandicap(HPLAYER whichPlayer)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3C9E10
			jmp eax
		}
	}

	__declspec(naked) jReal jNATIVE GetPlayerHandicapXP(HPLAYER whichPlayer)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3C9EC0
			jmp eax
		}
	}

	__declspec(naked) jInteger jNATIVE GetPlayerId(HPLAYER whichPlayer)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3C9640
			jmp eax
		}
	}

	__declspec(naked) jString jNATIVE GetPlayerName(HPLAYER whichPlayer)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3C0F60
			jmp eax
		}
	}

	__declspec(naked) HRACE jNATIVE GetPlayerRace(HPLAYER whichPlayer)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3C9620
			jmp eax
		}
	}

	__declspec(naked) jInteger jNATIVE GetPlayerScore(HPLAYER whichPlayer, HPLAYERSCORE whichPlayerScore)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3C9B70
			jmp eax
		}
	}

	__declspec(naked) jBoolean jNATIVE GetPlayerSelectable(HPLAYER whichPlayer)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3C1290
			jmp eax
		}
	}

	__declspec(naked) HPLAYERSLOTSTATE jNATIVE GetPlayerSlotState(HPLAYER whichPlayer)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3C12D0
			jmp eax
		}
	}

	__declspec(naked) jInteger jNATIVE GetPlayerStartLocation(HPLAYER whichPlayer)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3C0FD0
			jmp eax
		}
	}

	__declspec(naked) jReal jNATIVE GetPlayerStartLocationX(HPLAYER arg1)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3C0FF0
			jmp eax
		}
	}

	__declspec(naked) jReal jNATIVE GetPlayerStartLocationY(HPLAYER arg1)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3C1020
			jmp eax
		}
	}

	__declspec(naked) jInteger jNATIVE GetPlayerState(HPLAYER whichPlayer, HPLAYERSTATE whichPlayerState)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3C9B00
			jmp eax
		}
	}

	__declspec(naked) jInteger jNATIVE GetPlayerStructureCount(HPLAYER whichPlayer, jBoolean includeIncomplete)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3C98C0
			jmp eax
		}
	}

	__declspec(naked) jInteger jNATIVE GetPlayerTaxRate(HPLAYER sourcePlayer, HPLAYER otherPlayer, HPLAYERSTATE whichResource)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3C1150
			jmp eax
		}
	}

	__declspec(naked) jInteger jNATIVE GetPlayerTeam(HPLAYER whichPlayer)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3C0F40
			jmp eax
		}
	}

	__declspec(naked) jInteger jNATIVE GetPlayerTechCount(HPLAYER whichPlayer, jInteger techid, jBoolean specificonly)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3C97A0
			jmp eax
		}
	}

	__declspec(naked) jInteger jNATIVE GetPlayerTechMaxAllowed(HPLAYER whichPlayer, jInteger techid)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3C9690
			jmp eax
		}
	}

	__declspec(naked) jBoolean jNATIVE GetPlayerTechResearched(HPLAYER whichPlayer, jInteger techid, jBoolean specificonly)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3C9770
			jmp eax
		}
	}

	__declspec(naked) jInteger jNATIVE GetPlayerTypedUnitCount(HPLAYER whichPlayer, jString unitName, jBoolean includeIncomplete, jBoolean includeUpgrades)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3C9850
			jmp eax
		}
	}

	__declspec(naked) jInteger jNATIVE GetPlayerUnitCount(HPLAYER whichPlayer, jBoolean includeIncomplete)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3C9820
			jmp eax
		}
	}

	__declspec(naked) jInteger jNATIVE GetPlayerUnitTypeCount(HPLAYER arg1, jInteger arg2)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x2E2B60
			jmp eax
		}
	}

	__declspec(naked) jInteger jNATIVE GetPlayers()
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3BAE00
			jmp eax
		}
	}

	__declspec(naked) jInteger jNATIVE GetRandomInt(jInteger lowBound, jInteger highBound)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3B3560
			jmp eax
		}
	}

	__declspec(naked) jReal jNATIVE GetRandomReal(jReal* lowBound, jReal* highBound)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3B35A0
			jmp eax
		}
	}

	__declspec(naked) jReal jNATIVE GetRectCenterX(HRECT whichRect)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3C18E0
			jmp eax
		}
	}

	__declspec(naked) jReal jNATIVE GetRectCenterY(HRECT whichRect)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3C1910
			jmp eax
		}
	}

	__declspec(naked) jReal jNATIVE GetRectMaxX(HRECT whichRect)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3C1980
			jmp eax
		}
	}

	__declspec(naked) jReal jNATIVE GetRectMaxY(HRECT whichRect)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3C19A0
			jmp eax
		}
	}

	__declspec(naked) jReal jNATIVE GetRectMinX(HRECT whichRect)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3C1940
			jmp eax
		}
	}

	__declspec(naked) jReal jNATIVE GetRectMinY(HRECT whichRect)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3C1960
			jmp eax
		}
	}

	__declspec(naked) HUNIT jNATIVE GetRescuer()
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3C2390
			jmp eax
		}
	}

	__declspec(naked) jInteger jNATIVE GetResearched()
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3C2870
			jmp eax
		}
	}

	__declspec(naked) HUNIT jNATIVE GetResearchingUnit()
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3BB4D0
			jmp eax
		}
	}

	__declspec(naked) jInteger jNATIVE GetResourceAmount(HUNIT whichUnit)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3C78B0
			jmp eax
		}
	}

	__declspec(naked) HMAPDENSITY jNATIVE GetResourceDensity()
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3BAF40
			jmp eax
		}
	}

	__declspec(naked) HUNIT jNATIVE GetRevivableUnit()
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3C2290
			jmp eax
		}
	}

	__declspec(naked) HUNIT jNATIVE GetRevivingUnit()
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3C22F0
			jmp eax
		}
	}

	__declspec(naked) jString jNATIVE GetSaveBasicFilename()
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3C1F80
			jmp eax
		}
	}

	__declspec(naked) HUNIT jNATIVE GetSellingUnit()
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3C2560
			jmp eax
		}
	}

	__declspec(naked) HITEM jNATIVE GetSoldItem()
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3C25F0
			jmp eax
		}
	}

	__declspec(naked) HUNIT jNATIVE GetSoldUnit()
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3C2750
			jmp eax
		}
	}

	__declspec(naked) jInteger jNATIVE GetSoundDuration(HSOUND soundHandle)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3CCF20
			jmp eax
		}
	}

	__declspec(naked) jInteger jNATIVE GetSoundFileDuration(jString musicFileName)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3B3E20
			jmp eax
		}
	}

	__declspec(naked) jBoolean jNATIVE GetSoundIsLoading(HSOUND soundHandle)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3CCF60
			jmp eax
		}
	}

	__declspec(naked) jBoolean jNATIVE GetSoundIsPlaying(HSOUND soundHandle)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3CCF40
			jmp eax
		}
	}

	__declspec(naked) HABILITY jNATIVE GetSpellAbility()
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3C3380
			jmp eax
		}
	}

	__declspec(naked) jInteger jNATIVE GetSpellAbilityId()
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3C32A0
			jmp eax
		}
	}

	__declspec(naked) HUNIT jNATIVE GetSpellAbilityUnit()
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3C3470
			jmp eax
		}
	}

	__declspec(naked) HDESTRUCTABLE jNATIVE GetSpellTargetDestructable()
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3C3760
			jmp eax
		}
	}

	__declspec(naked) HITEM jNATIVE GetSpellTargetItem()
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3C38F0
			jmp eax
		}
	}

	__declspec(naked) HLOCATION jNATIVE GetSpellTargetLoc()
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3D2090
			jmp eax
		}
	}

	__declspec(naked) HUNIT jNATIVE GetSpellTargetUnit()
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3C3A80
			jmp eax
		}
	}

	__declspec(naked) jReal jNATIVE GetSpellTargetX()
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3C3580
			jmp eax
		}
	}

	__declspec(naked) jReal jNATIVE GetSpellTargetY()
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3C3670
			jmp eax
		}
	}

	__declspec(naked) HSTARTLOCPRIO jNATIVE GetStartLocPrio(jInteger whichStartLoc, jInteger prioSlotIndex)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3BB030
			jmp eax
		}
	}

	__declspec(naked) jInteger jNATIVE GetStartLocPrioSlot(jInteger whichStartLoc, jInteger prioSlotIndex)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3BB000
			jmp eax
		}
	}

	__declspec(naked) HLOCATION jNATIVE GetStartLocationLoc(jInteger whichStartLocation)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3D04B0
			jmp eax
		}
	}

	__declspec(naked) jReal jNATIVE GetStartLocationX(jInteger whichStartLocation)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3BB060
			jmp eax
		}
	}

	__declspec(naked) jReal jNATIVE GetStartLocationY(jInteger whichStartLocation)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3BB080
			jmp eax
		}
	}

	__declspec(naked) jBoolean jNATIVE GetStoredBoolean(HGAMECACHE cache, jString missionKey, jString key)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3CA920
			jmp eax
		}
	}

	__declspec(naked) jInteger jNATIVE GetStoredInteger(HGAMECACHE cache, jString missionKey, jString key)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3CA870
			jmp eax
		}
	}

	__declspec(naked) jReal jNATIVE GetStoredReal(HGAMECACHE cache, jString missionKey, jString key)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3CA8C0
			jmp eax
		}
	}

	__declspec(naked) jString jNATIVE GetStoredString(HGAMECACHE cache, jString missionKey, jString key)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3CAA40
			jmp eax
		}
	}

	__declspec(naked) HUNIT jNATIVE GetSummonedUnit()
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3C2950
			jmp eax
		}
	}

	__declspec(naked) HUNIT jNATIVE GetSummoningUnit()
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3C28F0
			jmp eax
		}
	}

	__declspec(naked) jInteger jNATIVE GetTeams()
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3BADE0
			jmp eax
		}
	}

	__declspec(naked) jInteger jNATIVE GetTerrainCliffLevel(jReal* x, jReal* y)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3B4190
			jmp eax
		}
	}

	__declspec(naked) jInteger jNATIVE GetTerrainType(jReal* x, jReal* y)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3BCED0
			jmp eax
		}
	}

	__declspec(naked) jInteger jNATIVE GetTerrainVariance(jReal* x, jReal* y)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3B4250
			jmp eax
		}
	}

	__declspec(naked) jReal jNATIVE GetTimeOfDayScale()
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3BC4B0
			jmp eax
		}
	}

	__declspec(naked) HPLAYER jNATIVE GetTournamentFinishNowPlayer()
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3C1F00
			jmp eax
		}
	}

	__declspec(naked) jInteger jNATIVE GetTournamentFinishNowRule()
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3C1ED0
			jmp eax
		}
	}

	__declspec(naked) jReal jNATIVE GetTournamentFinishSoonTimeRemaining()
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3C1EA0
			jmp eax
		}
	}

	__declspec(naked) jInteger jNATIVE GetTournamentScore(HPLAYER whichPlayer)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3C1F60
			jmp eax
		}
	}

	__declspec(naked) jInteger jNATIVE GetTownUnitCount(jInteger arg1, jInteger arg2, jBoolean arg3)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x2DD0C0
			jmp eax
		}
	}

	__declspec(naked) HUNIT jNATIVE GetTrainedUnit()
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3C2500
			jmp eax
		}
	}

	__declspec(naked) jInteger jNATIVE GetTrainedUnitType()
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3C2450
			jmp eax
		}
	}

	__declspec(naked) HUNIT jNATIVE GetTransportUnit()
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3C29A0
			jmp eax
		}
	}

	__declspec(naked) HDESTRUCTABLE jNATIVE GetTriggerDestructable()
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3C1D20
			jmp eax
		}
	}

	__declspec(naked) jInteger jNATIVE GetTriggerEvalCount(jTrigger whichTrigger)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3C1CE0
			jmp eax
		}
	}

	__declspec(naked) HEVENTID jNATIVE GetTriggerEventId()
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3BB2C0
			jmp eax
		}
	}

	__declspec(naked) jInteger jNATIVE GetTriggerExecCount(jTrigger whichTrigger)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3C1D00
			jmp eax
		}
	}

	__declspec(naked) HPLAYER jNATIVE GetTriggerPlayer()
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3BB280
			jmp eax
		}
	}

	__declspec(naked) HUNIT jNATIVE GetTriggerUnit()
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3BB240
			jmp eax
		}
	}

	__declspec(naked) HWIDGET jNATIVE GetTriggerWidget()
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3BB260
			jmp eax
		}
	}

	__declspec(naked) HREGION jNATIVE GetTriggeringRegion()
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3C3D50
			jmp eax
		}
	}

	__declspec(naked) HTRACKABLE jNATIVE GetTriggeringTrackable()
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3C3DA0
			jmp eax
		}
	}

	__declspec(naked) jTrigger jNATIVE GetTriggeringTrigger()
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3BB2A0
			jmp eax
		}
	}

	__declspec(naked) jInteger jNATIVE GetUnitAbilityLevel(HUNIT whichUnit, jInteger abilcode)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3C7290
			jmp eax
		}
	}

	__declspec(naked) jReal jNATIVE GetUnitAcquireRange(HUNIT whichUnit)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3C5D10
			jmp eax
		}
	}

	__declspec(naked) jInteger jNATIVE GetUnitBuildTime(jInteger arg1)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x2DD190
			jmp eax
		}
	}

	__declspec(naked) jInteger jNATIVE GetUnitCount(jInteger arg1)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x2DD050
			jmp eax
		}
	}

	__declspec(naked) jInteger jNATIVE GetUnitCountDone(jInteger arg1)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x2DD010
			jmp eax
		}
	}

	__declspec(naked) jInteger jNATIVE GetUnitCurrentOrder(HUNIT whichUnit)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3C7780
			jmp eax
		}
	}

	__declspec(naked) jReal jNATIVE GetUnitDefaultAcquireRange(HUNIT whichUnit)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3C5DC0
			jmp eax
		}
	}

	__declspec(naked) jReal jNATIVE GetUnitDefaultFlyHeight(HUNIT whichUnit)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3C5E50
			jmp eax
		}
	}

	__declspec(naked) jReal jNATIVE GetUnitDefaultMoveSpeed(HUNIT whichUnit)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3C5870
			jmp eax
		}
	}

	__declspec(naked) jReal jNATIVE GetUnitDefaultPropWindow(HUNIT whichUnit)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3C5E20
			jmp eax
		}
	}

	__declspec(naked) jReal jNATIVE GetUnitDefaultTurnSpeed(HUNIT whichUnit)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3C5DF0
			jmp eax
		}
	}

	__declspec(naked) jReal jNATIVE GetUnitFacing(HUNIT whichUnit)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3C5790
			jmp eax
		}
	}

	__declspec(naked) jReal jNATIVE GetUnitFlyHeight(HUNIT whichUnit)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3C5DA0
			jmp eax
		}
	}

	__declspec(naked) jInteger jNATIVE GetUnitFoodMade(HUNIT whichUnit)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3C5460
			jmp eax
		}
	}

	__declspec(naked) jInteger jNATIVE GetUnitFoodUsed(HUNIT whichUnit)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3C5440
			jmp eax
		}
	}

	__declspec(naked) jInteger jNATIVE GetUnitGoldCost(jInteger arg1)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x2DD1E0
			jmp eax
		}
	}

	__declspec(naked) jInteger jNATIVE GetUnitLevel(HUNIT whichUnit)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3C6F30
			jmp eax
		}
	}

	__declspec(naked) HLOCATION jNATIVE GetUnitLoc(HUNIT whichUnit)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3D2AE0
			jmp eax
		}
	}

	__declspec(naked) jReal jNATIVE GetUnitMoveSpeed(HUNIT whichUnit)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3C5810
			jmp eax
		}
	}

	__declspec(naked) jString jNATIVE GetUnitName(HUNIT whichUnit)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3C5950
			jmp eax
		}
	}

	__declspec(naked) jInteger jNATIVE GetUnitPointValue(HUNIT whichUnit)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3C5E80
			jmp eax
		}
	}

	__declspec(naked) jInteger jNATIVE GetUnitPointValueByType(jInteger unitType)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3B2E20
			jmp eax
		}
	}

	__declspec(naked) jReal jNATIVE GetUnitPropWindow(HUNIT whichUnit)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3C5D70
			jmp eax
		}
	}

	__declspec(naked) HRACE jNATIVE GetUnitRace(HUNIT whichUnit)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3C5930
			jmp eax
		}
	}

	__declspec(naked) HDESTRUCTABLE jNATIVE GetUnitRallyDestructable(HUNIT whichUnit)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3C5690
			jmp eax
		}
	}

	__declspec(naked) HLOCATION jNATIVE GetUnitRallyPoint(HUNIT whichUnit)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3D2B40
			jmp eax
		}
	}

	__declspec(naked) HUNIT jNATIVE GetUnitRallyUnit(HUNIT whichUnit)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3C5590
			jmp eax
		}
	}

	__declspec(naked) jReal jNATIVE GetUnitState(HUNIT whichUnit, HUNITSTATE whichUnitState)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3C5400
			jmp eax
		}
	}

	__declspec(naked) jReal jNATIVE GetUnitTurnSpeed(HUNIT whichUnit)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3C5D40
			jmp eax
		}
	}

	__declspec(naked) jInteger jNATIVE GetUnitTypeId(HUNIT whichUnit)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3C5910
			jmp eax
		}
	}

	__declspec(naked) jInteger jNATIVE GetUnitUserData(HUNIT whichUnit)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3C94F0
			jmp eax
		}
	}

	__declspec(naked) jInteger jNATIVE GetUnitWoodCost(jInteger arg1)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x2DD240
			jmp eax
		}
	}

	__declspec(naked) jReal jNATIVE GetUnitX(HUNIT whichUnit)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3C5510
			jmp eax
		}
	}

	__declspec(naked) jReal jNATIVE GetUnitY(HUNIT whichUnit)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3C5550
			jmp eax
		}
	}

	__declspec(naked) jInteger jNATIVE GetUpgradeGoldCost(jInteger arg1)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x2DD2A0
			jmp eax
		}
	}

	__declspec(naked) jInteger jNATIVE GetUpgradeLevel(jInteger arg1)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x2DD130
			jmp eax
		}
	}

	__declspec(naked) jInteger jNATIVE GetUpgradeWoodCost(jInteger arg1)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x2DD2C0
			jmp eax
		}
	}

	__declspec(naked) jReal jNATIVE GetWidgetLife(HWIDGET whichWidget)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3C4660
			jmp eax
		}
	}

	__declspec(naked) jReal jNATIVE GetWidgetX(HWIDGET whichWidget)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3C46B0
			jmp eax
		}
	}

	__declspec(naked) jReal jNATIVE GetWidgetY(HWIDGET whichWidget)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3C46F0
			jmp eax
		}
	}

	__declspec(naked) HPLAYER jNATIVE GetWinningPlayer()
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3BB3E0
			jmp eax
		}
	}

	__declspec(naked) HRECT jNATIVE GetWorldBounds()
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3D0D60
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE GroupAddUnit(HGROUP whichGroup, HUNIT whichUnit)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3C3FC0
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE GroupClear(HGROUP whichGroup)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3C4020
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE GroupEnumUnitsInRange(HGROUP whichGroup, jReal* x, jReal* y, jReal* radius, HBOOLEXPR filter)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3C41A0
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE GroupEnumUnitsInRangeCounted(HGROUP whichGroup, jReal* x, jReal* y, jReal* radius, HBOOLEXPR filter, jInteger countLimit)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3C4230
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE GroupEnumUnitsInRangeOfLoc(HGROUP whichGroup, HLOCATION whichLocation, jReal* radius, HBOOLEXPR filter)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3C41E0
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE GroupEnumUnitsInRangeOfLocCounted(HGROUP whichGroup, HLOCATION whichLocation, jReal* radius, HBOOLEXPR filter, jInteger countLimit)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3C4270
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE GroupEnumUnitsInRect(HGROUP whichGroup, HRECT r, HBOOLEXPR filter)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3C40E0
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE GroupEnumUnitsInRectCounted(HGROUP whichGroup, HRECT r, HBOOLEXPR filter, jInteger countLimit)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3C4140
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE GroupEnumUnitsOfPlayer(HGROUP whichGroup, HPLAYER whichPlayer, HBOOLEXPR filter)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3C42C0
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE GroupEnumUnitsOfType(HGROUP whichGroup, jString unitname, HBOOLEXPR filter)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3C4040
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE GroupEnumUnitsOfTypeCounted(HGROUP whichGroup, jString unitname, HBOOLEXPR filter, jInteger countLimit)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3C4090
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE GroupEnumUnitsSelected(HGROUP whichGroup, HPLAYER whichPlayer, HBOOLEXPR filter)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3CE590
			jmp eax
		}
	}

	__declspec(naked) jBoolean jNATIVE GroupImmediateOrder(HGROUP whichGroup, jString order)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3C4320
			jmp eax
		}
	}

	__declspec(naked) jBoolean jNATIVE GroupImmediateOrderById(HGROUP whichGroup, jInteger order)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3C4300
			jmp eax
		}
	}

	__declspec(naked) jBoolean jNATIVE GroupPointOrder(HGROUP whichGroup, jString order, jReal* x, jReal* y)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3C4370
			jmp eax
		}
	}

	__declspec(naked) jBoolean jNATIVE GroupPointOrderById(HGROUP whichGroup, jInteger order, jReal* x, jReal* y)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3C4340
			jmp eax
		}
	}

	__declspec(naked) jBoolean jNATIVE GroupPointOrderByIdLoc(HGROUP whichGroup, jInteger order, HLOCATION whichLocation)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3C4390
			jmp eax
		}
	}

	__declspec(naked) jBoolean jNATIVE GroupPointOrderLoc(HGROUP whichGroup, jString order, HLOCATION whichLocation)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3C43E0
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE GroupRemoveUnit(HGROUP whichGroup, HUNIT whichUnit)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3C3FF0
			jmp eax
		}
	}

	__declspec(naked) jBoolean jNATIVE GroupTargetOrder(HGROUP whichGroup, jString order, HWIDGET targetWidget)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3C4440
			jmp eax
		}
	}

	__declspec(naked) jBoolean jNATIVE GroupTargetOrderById(HGROUP whichGroup, jInteger order, HWIDGET targetWidget)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3C4400
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE GroupTimedLife(jBoolean arg1)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x2E2D60
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE HarvestGold(jInteger arg1, jInteger arg2)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x2DD5E0
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE HarvestWood(jInteger arg1, jInteger arg2)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x2DD630
			jmp eax
		}
	}

	__declspec(naked) jBoolean jNATIVE HaveSavedBoolean(HHASHTABLE table, jInteger parentKey, jInteger childKey)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3CB140
			jmp eax
		}
	}

	__declspec(naked) jBoolean jNATIVE HaveSavedHandle(HHASHTABLE table, jInteger parentKey, jInteger childKey)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3CB1C0
			jmp eax
		}
	}

	__declspec(naked) jBoolean jNATIVE HaveSavedInteger(HHASHTABLE table, jInteger parentKey, jInteger childKey)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3CB0C0
			jmp eax
		}
	}

	__declspec(naked) jBoolean jNATIVE HaveSavedReal(HHASHTABLE table, jInteger parentKey, jInteger childKey)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3CB100
			jmp eax
		}
	}

	__declspec(naked) jBoolean jNATIVE HaveSavedString(HHASHTABLE table, jInteger parentKey, jInteger childKey)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3CB180
			jmp eax
		}
	}

	__declspec(naked) jBoolean jNATIVE HaveStoredBoolean(HGAMECACHE cache, jString missionKey, jString key)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3CAFD0
			jmp eax
		}
	}

	__declspec(naked) jBoolean jNATIVE HaveStoredInteger(HGAMECACHE cache, jString missionKey, jString key)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3CAF30
			jmp eax
		}
	}

	__declspec(naked) jBoolean jNATIVE HaveStoredReal(HGAMECACHE cache, jString missionKey, jString key)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3CAF80
			jmp eax
		}
	}

	__declspec(naked) jBoolean jNATIVE HaveStoredString(HGAMECACHE cache, jString missionKey, jString key)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3CB070
			jmp eax
		}
	}

	__declspec(naked) jBoolean jNATIVE HaveStoredUnit(HGAMECACHE cache, jString missionKey, jString key)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3CB020
			jmp eax
		}
	}

	__declspec(naked) jReal jNATIVE I2R(jInteger i)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3B2CC0
			jmp eax
		}
	}

	__declspec(naked) jString jNATIVE I2S(jInteger i)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3BAAA0
			jmp eax
		}
	}

	__declspec(naked) jInteger jNATIVE IgnoredUnits(jInteger arg1)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x2DCE80
			jmp eax
		}
	}

	__declspec(naked) jInteger jNATIVE IncUnitAbilityLevel(HUNIT whichUnit, jInteger abilcode)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3C7130
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE InitAssault()
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x2DD990
			jmp eax
		}
	}

	__declspec(naked) HGAMECACHE jNATIVE InitGameCache(jString campaignFile)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3D2CC0
			jmp eax
		}
	}

	__declspec(naked) HHASHTABLE jNATIVE InitHashtable()
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3D2DF0
			jmp eax
		}
	}

	__declspec(naked) jBoolean jNATIVE IsCineFilterDisplayed()
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3B5150
			jmp eax
		}
	}

	__declspec(naked) jBoolean jNATIVE IsDestructableInvulnerable(HDESTRUCTABLE d)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3C4790
			jmp eax
		}
	}

	__declspec(naked) jBoolean jNATIVE IsFogEnabled()
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3BB200
			jmp eax
		}
	}

	__declspec(naked) jBoolean jNATIVE IsFogMaskEnabled()
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3BB230
			jmp eax
		}
	}

	__declspec(naked) jBoolean jNATIVE IsFoggedToPlayer(jReal* x, jReal* y, HPLAYER whichPlayer)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3C9980
			jmp eax
		}
	}

	__declspec(naked) jBoolean jNATIVE IsGameTypeSupported(HGAMETYPE whichGameType)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3BAE40
			jmp eax
		}
	}

	__declspec(naked) jBoolean jNATIVE IsHeroUnitId(jInteger unitId)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3B2E90
			jmp eax
		}
	}

	__declspec(naked) jBoolean jNATIVE IsItemIdPawnable(jInteger itemId)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3B2DF0
			jmp eax
		}
	}

	__declspec(naked) jBoolean jNATIVE IsItemIdPowerup(jInteger itemId)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3B2DD0
			jmp eax
		}
	}

	__declspec(naked) jBoolean jNATIVE IsItemIdSellable(jInteger itemId)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3B2DE0
			jmp eax
		}
	}

	__declspec(naked) jBoolean jNATIVE IsItemInvulnerable(HITEM whichItem)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3C4F00
			jmp eax
		}
	}

	__declspec(naked) jBoolean jNATIVE IsItemOwned(HITEM whichItem)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3C4F90
			jmp eax
		}
	}

	__declspec(naked) jBoolean jNATIVE IsItemPawnable(HITEM whichItem)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3C5010
			jmp eax
		}
	}

	__declspec(naked) jBoolean jNATIVE IsItemPowerup(HITEM whichItem)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3C4FD0
			jmp eax
		}
	}

	__declspec(naked) jBoolean jNATIVE IsItemSellable(HITEM whichItem)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3C4FF0
			jmp eax
		}
	}

	__declspec(naked) jBoolean jNATIVE IsItemVisible(HITEM whichItem)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3C4F70
			jmp eax
		}
	}

	__declspec(naked) jBoolean jNATIVE IsLeaderboardDisplayed(HLEADERBOARD lb)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3CC220
			jmp eax
		}
	}

	__declspec(naked) jBoolean jNATIVE IsLocationFoggedToPlayer(HLOCATION whichLocation, HPLAYER whichPlayer)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3C99D0
			jmp eax
		}
	}

	__declspec(naked) jBoolean jNATIVE IsLocationInRegion(HREGION whichRegion, HLOCATION whichLocation)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3C16B0
			jmp eax
		}
	}

	__declspec(naked) jBoolean jNATIVE IsLocationMaskedToPlayer(HLOCATION whichLocation, HPLAYER whichPlayer)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3C9A60
			jmp eax
		}
	}

	__declspec(naked) jBoolean jNATIVE IsLocationVisibleToPlayer(HLOCATION whichLocation, HPLAYER whichPlayer)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3C9940
			jmp eax
		}
	}

	__declspec(naked) jBoolean jNATIVE IsMapFlagSet(HMAPFLAG whichMapFlag)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3BAEA0
			jmp eax
		}
	}

	__declspec(naked) jBoolean jNATIVE IsMaskedToPlayer(jReal* x, jReal* y, HPLAYER whichPlayer)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3C9A10
			jmp eax
		}
	}

	__declspec(naked) jBoolean jNATIVE IsMultiboardDisplayed(HMULTIBOARD lb)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3CC690
			jmp eax
		}
	}

	__declspec(naked) jBoolean jNATIVE IsMultiboardMinimized(HMULTIBOARD lb)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3CC6D0
			jmp eax
		}
	}

	__declspec(naked) jBoolean jNATIVE IsNoDefeatCheat()
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3BC8F0
			jmp eax
		}
	}

	__declspec(naked) jBoolean jNATIVE IsNoVictoryCheat()
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3BC8C0
			jmp eax
		}
	}

	__declspec(naked) jBoolean jNATIVE IsPlayerAlly(HPLAYER whichPlayer, HPLAYER otherPlayer)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3C9530
			jmp eax
		}
	}

	__declspec(naked) jBoolean jNATIVE IsPlayerEnemy(HPLAYER whichPlayer, HPLAYER otherPlayer)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3C9580
			jmp eax
		}
	}

	__declspec(naked) jBoolean jNATIVE IsPlayerInForce(HPLAYER whichPlayer, HFORCE whichForce)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3C95D0
			jmp eax
		}
	}

	__declspec(naked) jBoolean jNATIVE IsPlayerObserver(HPLAYER whichPlayer)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3C9600
			jmp eax
		}
	}

	__declspec(naked) jBoolean jNATIVE IsPlayerRacePrefSet(HPLAYER whichPlayer, HRACEPREFERENCE pref)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3C1260
			jmp eax
		}
	}

	__declspec(naked) jBoolean jNATIVE IsPointBlighted(jReal* x, jReal* y)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3B4550
			jmp eax
		}
	}

	__declspec(naked) jBoolean jNATIVE IsPointInRegion(HREGION whichRegion, jReal* x, jReal* y)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3C1690
			jmp eax
		}
	}

	__declspec(naked) jBoolean jNATIVE IsQuestCompleted(HQUEST whichQuest)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3CBCC0
			jmp eax
		}
	}

	__declspec(naked) jBoolean jNATIVE IsQuestDiscovered(HQUEST whichQuest)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3CBCE0
			jmp eax
		}
	}

	__declspec(naked) jBoolean jNATIVE IsQuestEnabled(HQUEST whichQuest)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3CBD20
			jmp eax
		}
	}

	__declspec(naked) jBoolean jNATIVE IsQuestFailed(HQUEST whichQuest)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3CBD00
			jmp eax
		}
	}

	__declspec(naked) jBoolean jNATIVE IsQuestItemCompleted(HQUESTITEM whichQuestItem)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3CBD90
			jmp eax
		}
	}

	__declspec(naked) jBoolean jNATIVE IsQuestRequired(HQUEST whichQuest)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3CBCA0
			jmp eax
		}
	}

	__declspec(naked) jBoolean jNATIVE IsSuspendedXP(HUNIT whichHero)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3C6E70
			jmp eax
		}
	}

	__declspec(naked) jBoolean jNATIVE IsTerrainPathable(jReal* x, jReal* y, HPATHINGTYPE t)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3B42D0
			jmp eax
		}
	}

	__declspec(naked) jBoolean jNATIVE IsTimerDialogDisplayed(HTIMERDIALOG whichDialog)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3CBF70
			jmp eax
		}
	}

	__declspec(naked) jBoolean jNATIVE IsTowered(HUNIT arg1)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x2E0950
			jmp eax
		}
	}

	__declspec(naked) jBoolean jNATIVE IsTriggerEnabled(jTrigger whichTrigger)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3C1C80
			jmp eax
		}
	}

	__declspec(naked) jBoolean jNATIVE IsTriggerWaitOnSleeps(jTrigger whichTrigger)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3C1CC0
			jmp eax
		}
	}

	__declspec(naked) jBoolean jNATIVE IsUnit(HUNIT whichUnit, HUNIT whichSpecifiedUnit)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3C8020
			jmp eax
		}
	}

	__declspec(naked) jBoolean jNATIVE IsUnitAlly(HUNIT whichUnit, HPLAYER whichPlayer)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3C7A70
			jmp eax
		}
	}

	__declspec(naked) jBoolean jNATIVE IsUnitDetected(HUNIT whichUnit, HPLAYER whichPlayer)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3C7C80
			jmp eax
		}
	}

	__declspec(naked) jBoolean jNATIVE IsUnitEnemy(HUNIT whichUnit, HPLAYER whichPlayer)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3C7AD0
			jmp eax
		}
	}

	__declspec(naked) jBoolean jNATIVE IsUnitFogged(HUNIT whichUnit, HPLAYER whichPlayer)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3C7D00
			jmp eax
		}
	}

	__declspec(naked) jBoolean jNATIVE IsUnitHidden(HUNIT whichUnit)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3C7B30
			jmp eax
		}
	}

	__declspec(naked) jBoolean jNATIVE IsUnitIdType(jInteger unitId, HUNITTYPE whichUnitType)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3B7F60
			jmp eax
		}
	}

	__declspec(naked) jBoolean jNATIVE IsUnitIllusion(HUNIT whichUnit)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3C7B50
			jmp eax
		}
	}

	__declspec(naked) jBoolean jNATIVE IsUnitInForce(HUNIT whichUnit, HFORCE whichForce)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3C79C0
			jmp eax
		}
	}

	__declspec(naked) jBoolean jNATIVE IsUnitInGroup(HUNIT whichUnit, HGROUP whichGroup)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3C7A00
			jmp eax
		}
	}

	__declspec(naked) jBoolean jNATIVE IsUnitInRange(HUNIT whichUnit, HUNIT otherUnit, jReal* distance)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3C8090
			jmp eax
		}
	}

	__declspec(naked) jBoolean jNATIVE IsUnitInRangeLoc(HUNIT whichUnit, HLOCATION whichLocation, jReal* distance)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3C8140
			jmp eax
		}
	}

	__declspec(naked) jBoolean jNATIVE IsUnitInRangeXY(HUNIT whichUnit, jReal* x, jReal* y, jReal* distance)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3C80E0
			jmp eax
		}
	}

	__declspec(naked) jBoolean jNATIVE IsUnitInRegion(HREGION whichRegion, HUNIT whichUnit)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3C1660
			jmp eax
		}
	}

	__declspec(naked) jBoolean jNATIVE IsUnitInTransport(HUNIT whichUnit, HUNIT whichTransport)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3C7B70
			jmp eax
		}
	}

	__declspec(naked) jBoolean jNATIVE IsUnitInvisible(HUNIT whichUnit, HPLAYER whichPlayer)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3C7CC0
			jmp eax
		}
	}

	__declspec(naked) jBoolean jNATIVE IsUnitLoaded(HUNIT whichUnit)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3C7BA0
			jmp eax
		}
	}

	__declspec(naked) jBoolean jNATIVE IsUnitMasked(HUNIT whichUnit, HPLAYER whichPlayer)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3C7D80
			jmp eax
		}
	}

	__declspec(naked) jBoolean jNATIVE IsUnitOwnedByPlayer(HUNIT whichUnit, HPLAYER whichPlayer)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3C7A30
			jmp eax
		}
	}

	__declspec(naked) jBoolean jNATIVE IsUnitPaused(HUNIT whichHero)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3C73A0
			jmp eax
		}
	}

	__declspec(naked) jBoolean jNATIVE IsUnitRace(HUNIT whichUnit, HRACE whichRace)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3C7E60
			jmp eax
		}
	}

	__declspec(naked) jBoolean jNATIVE IsUnitSelected(HUNIT whichUnit, HPLAYER whichPlayer)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3C7E00
			jmp eax
		}
	}

	__declspec(naked) jBoolean jNATIVE IsUnitType(HUNIT whichUnit, HUNITTYPE whichUnitType)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3C7E90
			jmp eax
		}
	}

	__declspec(naked) jBoolean jNATIVE IsUnitVisible(HUNIT whichUnit, HPLAYER whichPlayer)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3C7AF0
			jmp eax
		}
	}

	__declspec(naked) jBoolean jNATIVE IsVisibleToPlayer(jReal* x, jReal* y, HPLAYER whichPlayer)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3C98F0
			jmp eax
		}
	}

	__declspec(naked) jBoolean jNATIVE IssueBuildOrder(HUNIT whichPeon, jString unitToBuild, jReal* x, jReal* y)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3C8E80
			jmp eax
		}
	}

	__declspec(naked) jBoolean jNATIVE IssueBuildOrderById(HUNIT whichPeon, jInteger unitId, jReal* x, jReal* y)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3C8BE0
			jmp eax
		}
	}

	__declspec(naked) jBoolean jNATIVE IssueImmediateOrder(HUNIT whichUnit, jString order)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3C8D80
			jmp eax
		}
	}

	__declspec(naked) jBoolean jNATIVE IssueImmediateOrderById(HUNIT whichUnit, jInteger order)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3C8900
			jmp eax
		}
	}

	__declspec(naked) jBoolean jNATIVE IssueInstantPointOrder(HUNIT whichUnit, jString order, jReal* x, jReal* y, HWIDGET instantTargetWidget)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3C8E40
			jmp eax
		}
	}

	__declspec(naked) jBoolean jNATIVE IssueInstantPointOrderById(HUNIT whichUnit, jInteger order, jReal* x, jReal* y, HWIDGET instantTargetWidget)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3C8A20
			jmp eax
		}
	}

	__declspec(naked) jBoolean jNATIVE IssueInstantTargetOrder(HUNIT whichUnit, jString order, HWIDGET targetWidget, HWIDGET instantTargetWidget)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3C8E60
			jmp eax
		}
	}

	__declspec(naked) jBoolean jNATIVE IssueInstantTargetOrderById(HUNIT whichUnit, jInteger order, HWIDGET targetWidget, HWIDGET instantTargetWidget)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3C8AB0
			jmp eax
		}
	}

	__declspec(naked) jBoolean jNATIVE IssueNeutralImmediateOrder(HPLAYER forWhichPlayer, HUNIT neutralStructure, jString unitToBuild)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3C8EA0
			jmp eax
		}
	}

	__declspec(naked) jBoolean jNATIVE IssueNeutralImmediateOrderById(HPLAYER forWhichPlayer, HUNIT neutralStructure, jInteger unitId)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3C8CA0
			jmp eax
		}
	}

	__declspec(naked) jBoolean jNATIVE IssueNeutralPointOrder(HPLAYER forWhichPlayer, HUNIT neutralStructure, jString unitToBuild, jReal* x, jReal* y)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3C8EC0
			jmp eax
		}
	}

	__declspec(naked) jBoolean jNATIVE IssueNeutralPointOrderById(HPLAYER forWhichPlayer, HUNIT neutralStructure, jInteger unitId, jReal* x, jReal* y)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3C8CE0
			jmp eax
		}
	}

	__declspec(naked) jBoolean jNATIVE IssueNeutralTargetOrder(HPLAYER forWhichPlayer, HUNIT neutralStructure, jString unitToBuild, HWIDGET target)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3C8EE0
			jmp eax
		}
	}

	__declspec(naked) jBoolean jNATIVE IssueNeutralTargetOrderById(HPLAYER forWhichPlayer, HUNIT neutralStructure, jInteger unitId, HWIDGET target)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3C8D30
			jmp eax
		}
	}

	__declspec(naked) jBoolean jNATIVE IssuePointOrder(HUNIT whichUnit, jString order, jReal* x, jReal* y)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3C8DA0
			jmp eax
		}
	}

	__declspec(naked) jBoolean jNATIVE IssuePointOrderById(HUNIT whichUnit, jInteger order, jReal* x, jReal* y)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3C8940
			jmp eax
		}
	}

	__declspec(naked) jBoolean jNATIVE IssuePointOrderByIdLoc(HUNIT whichUnit, jInteger order, HLOCATION whichLocation)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3C8980
			jmp eax
		}
	}

	__declspec(naked) jBoolean jNATIVE IssuePointOrderLoc(HUNIT whichUnit, jString order, HLOCATION whichLocation)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3C8DC0
			jmp eax
		}
	}

	__declspec(naked) jBoolean jNATIVE IssueTargetOrder(HUNIT whichUnit, jString order, HWIDGET targetWidget)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3C8E20
			jmp eax
		}
	}

	__declspec(naked) jBoolean jNATIVE IssueTargetOrderById(HUNIT whichUnit, jInteger order, HWIDGET targetWidget)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3C89D0
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE ItemPoolAddItemType(HITEMPOOL whichItemPool, jInteger itemId, jReal* weight)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3CB6C0
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE ItemPoolRemoveItemType(HITEMPOOL whichItemPool, jInteger itemId)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3CB6E0
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE KillDestructable(HDESTRUCTABLE d)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3C4750
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE KillSoundWhenDone(HSOUND soundHandle)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3CCED0
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE KillUnit(HUNIT whichUnit)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3C8040
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE LeaderboardAddItem(HLEADERBOARD lb, jString label, jInteger value, HPLAYER p)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3CC060
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE LeaderboardClear(HLEADERBOARD lb)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3CC1B0
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE LeaderboardDisplay(HLEADERBOARD lb, jBoolean show)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3CC1D0
			jmp eax
		}
	}

	__declspec(naked) jInteger jNATIVE LeaderboardGetItemCount(HLEADERBOARD lb)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3CC000
			jmp eax
		}
	}

	__declspec(naked) jString jNATIVE LeaderboardGetLabelText(HLEADERBOARD lb)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3CC2F0
			jmp eax
		}
	}

	__declspec(naked) jInteger jNATIVE LeaderboardGetPlayerIndex(HLEADERBOARD lb, HPLAYER p)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3CC2A0
			jmp eax
		}
	}

	__declspec(naked) jBoolean jNATIVE LeaderboardHasPlayerItem(HLEADERBOARD lb, HPLAYER p)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3CC250
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE LeaderboardRemoveItem(HLEADERBOARD lb, jInteger index)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3CC0B0
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE LeaderboardRemovePlayerItem(HLEADERBOARD lb, HPLAYER p)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3CC0E0
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE LeaderboardSetItemLabel(HLEADERBOARD lb, jInteger whichItem, jString val)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3CC520
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE LeaderboardSetItemLabelColor(HLEADERBOARD lb, jInteger whichItem, jInteger red, jInteger green, jInteger blue, jInteger alpha)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3CC5B0
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE LeaderboardSetItemStyle(HLEADERBOARD lb, jInteger whichItem, jBoolean showLabel, jBoolean showValue, jBoolean showIcon)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3CC560
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE LeaderboardSetItemValue(HLEADERBOARD lb, jInteger whichItem, jInteger val)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3CC4F0
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE LeaderboardSetItemValueColor(HLEADERBOARD lb, jInteger whichItem, jInteger red, jInteger green, jInteger blue, jInteger alpha)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3CC600
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE LeaderboardSetLabel(HLEADERBOARD lb, jString label)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3CC3D0
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE LeaderboardSetLabelColor(HLEADERBOARD lb, jInteger red, jInteger green, jInteger blue, jInteger alpha)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3CC400
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE LeaderboardSetSizeByItemCount(HLEADERBOARD lb, jInteger count)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3CC030
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE LeaderboardSetStyle(HLEADERBOARD lb, jBoolean showLabel, jBoolean showNames, jBoolean showValues, jBoolean showIcons)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3CC4A0
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE LeaderboardSetValueColor(HLEADERBOARD lb, jInteger red, jInteger green, jInteger blue, jInteger alpha)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3CC450
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE LeaderboardSortItemsByLabel(HLEADERBOARD lb, jBoolean ascending)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3CC180
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE LeaderboardSortItemsByPlayer(HLEADERBOARD lb, jBoolean ascending)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3CC150
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE LeaderboardSortItemsByValue(HLEADERBOARD lb, jBoolean ascending)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3CC120
			jmp eax
		}
	}

	__declspec(naked) HABILITY jNATIVE LoadAbilityHandle(HHASHTABLE table, jInteger parentKey, jInteger childKey)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3CEA60
			jmp eax
		}
	}

	__declspec(naked) jBoolean jNATIVE LoadBoolean(HHASHTABLE table, jInteger parentKey, jInteger childKey)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3CAB10
			jmp eax
		}
	}

	__declspec(naked) HBOOLEXPR jNATIVE LoadBooleanExprHandle(HHASHTABLE table, jInteger parentKey, jInteger childKey)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3CAD70
			jmp eax
		}
	}

	__declspec(naked) HBUTTON jNATIVE LoadButtonHandle(HHASHTABLE table, jInteger parentKey, jInteger childKey)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3CADD0
			jmp eax
		}
	}

	__declspec(naked) HDEFEATCONDITION jNATIVE LoadDefeatConditionHandle(HHASHTABLE table, jInteger parentKey, jInteger childKey)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3CEB20
			jmp eax
		}
	}

	__declspec(naked) HDESTRUCTABLE jNATIVE LoadDestructableHandle(HHASHTABLE table, jInteger parentKey, jInteger childKey)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3CABD0
			jmp eax
		}
	}

	__declspec(naked) HDIALOG jNATIVE LoadDialogHandle(HHASHTABLE table, jInteger parentKey, jInteger childKey)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3CADB0
			jmp eax
		}
	}

	__declspec(naked) HEFFECT jNATIVE LoadEffectHandle(HHASHTABLE table, jInteger parentKey, jInteger childKey)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3CEA80
			jmp eax
		}
	}

	__declspec(naked) HFOGMODIFIER jNATIVE LoadFogModifierHandle(HHASHTABLE table, jInteger parentKey, jInteger childKey)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3CAEF0
			jmp eax
		}
	}

	__declspec(naked) HFOGSTATE jNATIVE LoadFogStateHandle(HHASHTABLE table, jInteger parentKey, jInteger childKey)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3CAED0
			jmp eax
		}
	}

	__declspec(naked) HFORCE jNATIVE LoadForceHandle(HHASHTABLE table, jInteger parentKey, jInteger childKey)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3CACF0
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE LoadGame(jString saveFileName, jBoolean doScoreScreen)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3BBE60
			jmp eax
		}
	}

	__declspec(naked) HGROUP jNATIVE LoadGroupHandle(HHASHTABLE table, jInteger parentKey, jInteger childKey)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3CAD10
			jmp eax
		}
	}

	__declspec(naked) HHASHTABLE jNATIVE LoadHashtableHandle(HHASHTABLE table, jInteger parentKey, jInteger childKey)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3CAF10
			jmp eax
		}
	}

	__declspec(naked) HIMAGE jNATIVE LoadImageHandle(HHASHTABLE table, jInteger parentKey, jInteger childKey)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3CAE90
			jmp eax
		}
	}

	__declspec(naked) jInteger jNATIVE LoadInteger(HHASHTABLE table, jInteger parentKey, jInteger childKey)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3CAA90
			jmp eax
		}
	}

	__declspec(naked) HITEM jNATIVE LoadItemHandle(HHASHTABLE table, jInteger parentKey, jInteger childKey)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3CABF0
			jmp eax
		}
	}

	__declspec(naked) HITEMPOOL jNATIVE LoadItemPoolHandle(HHASHTABLE table, jInteger parentKey, jInteger childKey)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3CEAC0
			jmp eax
		}
	}

	__declspec(naked) HLEADERBOARD jNATIVE LoadLeaderboardHandle(HHASHTABLE table, jInteger parentKey, jInteger childKey)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3CEB60
			jmp eax
		}
	}

	__declspec(naked) HLIGHTNING jNATIVE LoadLightningHandle(HHASHTABLE table, jInteger parentKey, jInteger childKey)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3CAE70
			jmp eax
		}
	}

	__declspec(naked) HLOCATION jNATIVE LoadLocationHandle(HHASHTABLE table, jInteger parentKey, jInteger childKey)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3CAD30
			jmp eax
		}
	}

	__declspec(naked) HMULTIBOARD jNATIVE LoadMultiboardHandle(HHASHTABLE table, jInteger parentKey, jInteger childKey)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3CEB80
			jmp eax
		}
	}

	__declspec(naked) HMULTIBOARDITEM jNATIVE LoadMultiboardItemHandle(HHASHTABLE table, jInteger parentKey, jInteger childKey)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3CEBA0
			jmp eax
		}
	}

	__declspec(naked) HPLAYER jNATIVE LoadPlayerHandle(HHASHTABLE table, jInteger parentKey, jInteger childKey)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3CAB90
			jmp eax
		}
	}

	__declspec(naked) HQUEST jNATIVE LoadQuestHandle(HHASHTABLE table, jInteger parentKey, jInteger childKey)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3CEAE0
			jmp eax
		}
	}

	__declspec(naked) HQUESTITEM jNATIVE LoadQuestItemHandle(HHASHTABLE table, jInteger parentKey, jInteger childKey)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3CEB00
			jmp eax
		}
	}

	__declspec(naked) jReal jNATIVE LoadReal(HHASHTABLE table, jInteger parentKey, jInteger childKey)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3CAAD0
			jmp eax
		}
	}

	__declspec(naked) HRECT jNATIVE LoadRectHandle(HHASHTABLE table, jInteger parentKey, jInteger childKey)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3CAD50
			jmp eax
		}
	}

	__declspec(naked) HREGION jNATIVE LoadRegionHandle(HHASHTABLE table, jInteger parentKey, jInteger childKey)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3CAC50
			jmp eax
		}
	}

	__declspec(naked) HSOUND jNATIVE LoadSoundHandle(HHASHTABLE table, jInteger parentKey, jInteger childKey)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3CAD90
			jmp eax
		}
	}

	__declspec(naked) jString jNATIVE LoadStr(HHASHTABLE table, jInteger parentKey, jInteger childKey)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3CAB50
			jmp eax
		}
	}

	__declspec(naked) HTEXTTAG jNATIVE LoadTextTagHandle(HHASHTABLE table, jInteger parentKey, jInteger childKey)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3CAE50
			jmp eax
		}
	}

	__declspec(naked) HTIMERDIALOG jNATIVE LoadTimerDialogHandle(HHASHTABLE table, jInteger parentKey, jInteger childKey)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3CEB40
			jmp eax
		}
	}

	__declspec(naked) HTIMER jNATIVE LoadTimerHandle(HHASHTABLE table, jInteger parentKey, jInteger childKey)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3CAC30
			jmp eax
		}
	}

	__declspec(naked) HTRACKABLE jNATIVE LoadTrackableHandle(HHASHTABLE table, jInteger parentKey, jInteger childKey)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3CEBC0
			jmp eax
		}
	}

	__declspec(naked) HTRIGGERACTION jNATIVE LoadTriggerActionHandle(HHASHTABLE table, jInteger parentKey, jInteger childKey)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3CACB0
			jmp eax
		}
	}

	__declspec(naked) HTRIGGERCONDITION jNATIVE LoadTriggerConditionHandle(HHASHTABLE table, jInteger parentKey, jInteger childKey)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3CAC90
			jmp eax
		}
	}

	__declspec(naked) HEVENT jNATIVE LoadTriggerEventHandle(HHASHTABLE table, jInteger parentKey, jInteger childKey)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3CACD0
			jmp eax
		}
	}

	__declspec(naked) jTrigger jNATIVE LoadTriggerHandle(HHASHTABLE table, jInteger parentKey, jInteger childKey)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3CAC70
			jmp eax
		}
	}

	__declspec(naked) HUBERSPLAT jNATIVE LoadUbersplatHandle(HHASHTABLE table, jInteger parentKey, jInteger childKey)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3CAEB0
			jmp eax
		}
	}

	__declspec(naked) HUNIT jNATIVE LoadUnitHandle(HHASHTABLE table, jInteger parentKey, jInteger childKey)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3CAC10
			jmp eax
		}
	}

	__declspec(naked) HUNITPOOL jNATIVE LoadUnitPoolHandle(HHASHTABLE table, jInteger parentKey, jInteger childKey)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3CEAA0
			jmp eax
		}
	}

	__declspec(naked) HWIDGET jNATIVE LoadWidgetHandle(HHASHTABLE table, jInteger parentKey, jInteger childKey)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3CABB0
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE LoadZepWave(jInteger arg1, jInteger arg2)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x2DDC50
			jmp eax
		}
	}

	__declspec(naked) HLOCATION jNATIVE Location(jReal* x, jReal* y)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3D03B0
			jmp eax
		}
	}

	__declspec(naked) jInteger jNATIVE MeleeDifficulty()
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x2E0500
			jmp eax
		}
	}

	__declspec(naked) jBoolean jNATIVE MergeUnits(jInteger arg1, jInteger arg2, jInteger arg3, jInteger arg4)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x2DD320
			jmp eax
		}
	}

	__declspec(naked) jBoolean jNATIVE MoveLightning(HLIGHTNING whichBolt, jBoolean checkVisibility, jReal* x1, jReal* y1, jReal* x2, jReal* y2)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3BCDA0
			jmp eax
		}
	}

	__declspec(naked) jBoolean jNATIVE MoveLightningEx(HLIGHTNING whichBolt, jBoolean checkVisibility, jReal* x1, jReal* y1, jReal* z1, jReal* x2, jReal* y2, jReal* z2)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3BCCC0
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE MoveLocation(HLOCATION whichLocation, jReal* newX, jReal* newY)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3C0DF0
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE MoveRectTo(HRECT whichRect, jReal* newCenterX, jReal* newCenterY)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3C19C0
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE MoveRectToLoc(HRECT whichRect, HLOCATION newCenterLoc)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3C19F0
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE MultiboardClear(HMULTIBOARD lb)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3CC6F0
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE MultiboardDisplay(HMULTIBOARD lb, jBoolean show)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3CC670
			jmp eax
		}
	}

	__declspec(naked) jInteger jNATIVE MultiboardGetColumnCount(HMULTIBOARD lb)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3CC7D0
			jmp eax
		}
	}

	__declspec(naked) HMULTIBOARDITEM jNATIVE MultiboardGetItem(HMULTIBOARD lb, jInteger row, jInteger column)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3D37B0
			jmp eax
		}
	}

	__declspec(naked) jInteger jNATIVE MultiboardGetRowCount(HMULTIBOARD lb)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3CC7B0
			jmp eax
		}
	}

	__declspec(naked) jString jNATIVE MultiboardGetTitleText(HMULTIBOARD lb)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3CC750
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE MultiboardMinimize(HMULTIBOARD lb, jBoolean minimize)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3CC6B0
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE MultiboardReleaseItem(HMULTIBOARDITEM mbi)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3CC950
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE MultiboardSetColumnCount(HMULTIBOARD lb, jInteger count)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3CC7F0
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE MultiboardSetItemIcon(HMULTIBOARDITEM mbi, jString iconFileName)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3CCA20
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE MultiboardSetItemStyle(HMULTIBOARDITEM mbi, jBoolean showValue, jBoolean showIcon)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3CC970
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE MultiboardSetItemValue(HMULTIBOARDITEM mbi, jString val)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3CC990
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE MultiboardSetItemValueColor(HMULTIBOARDITEM mbi, jInteger red, jInteger green, jInteger blue, jInteger alpha)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3CC9C0
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE MultiboardSetItemWidth(HMULTIBOARDITEM mbi, jReal* width)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3CCA00
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE MultiboardSetItemsIcon(HMULTIBOARD lb, jString iconPath)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3CC920
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE MultiboardSetItemsStyle(HMULTIBOARD lb, jBoolean showValues, jBoolean showIcons)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3CC830
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE MultiboardSetItemsValue(HMULTIBOARD lb, jString value)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3CC870
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE MultiboardSetItemsValueColor(HMULTIBOARD lb, jInteger red, jInteger green, jInteger blue, jInteger alpha)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3CC8A0
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE MultiboardSetItemsWidth(HMULTIBOARD lb, jReal* width)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3CC8F0
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE MultiboardSetRowCount(HMULTIBOARD lb, jInteger count)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3CC810
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE MultiboardSetTitleText(HMULTIBOARD lb, jString label)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3CC720
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE MultiboardSetTitleTextColor(HMULTIBOARD lb, jInteger red, jInteger green, jInteger blue, jInteger alpha)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3CC770
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE MultiboardSuppressDisplay(jBoolean flag)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3B3C00
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE NewSoundEnvironment(jString environmentName)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3B3E60
			jmp eax
		}
	}

	__declspec(naked) HBOOLEXPR jNATIVE Not(HBOOLEXPR operand)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3D0830
			jmp eax
		}
	}

	__declspec(naked) HBOOLEXPR jNATIVE Or(HBOOLEXPR operandA, HBOOLEXPR operandB)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3D0710
			jmp eax
		}
	}

	__declspec(naked) jInteger jNATIVE OrderId(jString orderIdString)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3BB590
			jmp eax
		}
	}

	__declspec(naked) jString jNATIVE OrderId2String(jInteger orderId)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3BB5C0
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE PanCameraTo(jReal* x, jReal* y)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3B4700
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE PanCameraToTimed(jReal* x, jReal* y, jReal* duration)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3B4740
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE PanCameraToTimedWithZ(jReal* x, jReal* y, jReal* zOffsetDest, jReal* duration)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3B47D0
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE PanCameraToWithZ(jReal* x, jReal* y, jReal* zOffsetDest)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3B4790
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE PauseCompAI(HPLAYER p, jBoolean pause)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3CB7C0
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE PauseGame(jBoolean flag)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3BC4D0
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE PauseTimer(HTIMER whichTimer)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3C1400
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE PauseUnit(HUNIT whichUnit, jBoolean flag)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3C7340
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE PingMinimap(jReal* x, jReal* y, jReal* duration)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3B4650
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE PingMinimapEx(jReal* x, jReal* y, jReal* duration, jInteger red, jInteger green, jInteger blue, jBoolean extraEffects)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3B8660
			jmp eax
		}
	}

	__declspec(naked) HITEM jNATIVE PlaceRandomItem(HITEMPOOL whichItemPool, jReal* x, jReal* y)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3CB700
			jmp eax
		}
	}

	__declspec(naked) HUNIT jNATIVE PlaceRandomUnit(HUNITPOOL whichPool, HPLAYER forWhichPlayer, jReal* x, jReal* y, jReal* facing)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3CB620
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE PlayCinematic(jString movieName)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3BC520
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE PlayModelCinematic(jString modelName)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3BC500
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE PlayMusic(jString musicName)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3B3D30
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE PlayMusicEx(jString musicName, jInteger frommsecs, jInteger fadeinmsecs)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3B3D50
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE PlayThematicMusic(jString musicFileName)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3B3DA0
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE PlayThematicMusicEx(jString musicFileName, jInteger frommsecs)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3B3DC0
			jmp eax
		}
	}

	__declspec(naked) HPLAYER jNATIVE Player(jInteger number)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3BBB30
			jmp eax
		}
	}

	__declspec(naked) HLEADERBOARD jNATIVE PlayerGetLeaderboard(HPLAYER toPlayer)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3CC380
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE PlayerSetLeaderboard(HPLAYER toPlayer, HLEADERBOARD lb)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3CC340
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE PopLastCommand()
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x2E04D0
			jmp eax
		}
	}

	__declspec(naked) jReal jNATIVE Pow(jReal* x, jReal* power)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3B2C00
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE Preload(jString filename)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3B5170
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE PreloadEnd(jReal* timeout)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3B5190
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE PreloadEndEx()
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3B5220
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE PreloadGenClear()
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3B52B0
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE PreloadGenEnd(jString filename)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3B52D0
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE PreloadGenStart()
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3B5290
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE PreloadRefresh()
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3B5210
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE PreloadStart()
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3B51F0
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE Preloader(jString filename)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3B5310
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE PurchaseZeppelin()
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x2DD410
			jmp eax
		}
	}

	__declspec(naked) HQUESTITEM jNATIVE QuestCreateItem(HQUEST whichQuest)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3D3380
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE QuestItemSetCompleted(HQUESTITEM whichQuestItem, jBoolean completed)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3CBD70
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE QuestItemSetDescription(HQUESTITEM whichQuestItem, jString description)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3CBD40
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE QuestSetCompleted(HQUEST whichQuest, jBoolean completed)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3CBC20
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE QuestSetDescription(HQUEST whichQuest, jString description)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3CBBA0
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE QuestSetDiscovered(HQUEST whichQuest, jBoolean discovered)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3CBC60
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE QuestSetEnabled(HQUEST whichQuest, jBoolean enabled)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3CBC80
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE QuestSetFailed(HQUEST whichQuest, jBoolean failed)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3CBC40
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE QuestSetIconPath(HQUEST whichQuest, jString iconPath)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3CBBD0
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE QuestSetRequired(HQUEST whichQuest, jBoolean required)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3CBC00
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE QuestSetTitle(HQUEST whichQuest, jString title)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3CBB70
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE QueueDestructableAnimation(HDESTRUCTABLE d, jString whichAnimation)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3C4A00
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE QueueUnitAnimation(HUNIT whichUnit, jString whichAnimation)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3C6180
			jmp eax
		}
	}

	__declspec(naked) jInteger jNATIVE R2I(jReal* r)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3B2CE0
			jmp eax
		}
	}

	__declspec(naked) jString jNATIVE R2S(jReal* r)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3BAAF0
			jmp eax
		}
	}

	__declspec(naked) jString jNATIVE R2SW(jReal* r, jInteger width, jInteger precision)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3BAB40
			jmp eax
		}
	}

	__declspec(naked) jReal jNATIVE Rad2Deg(jReal* radians)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3B29F0
			jmp eax
		}
	}

	__declspec(naked) HRECT jNATIVE Rect(jReal* minx, jReal* miny, jReal* maxx, jReal* maxy)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3D0A20
			jmp eax
		}
	}

	__declspec(naked) HRECT jNATIVE RectFromLoc(HLOCATION min, HLOCATION max)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3D0BD0
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE RecycleGuardPosition(HUNIT hUnit)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3CB800
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE RegionAddCell(HREGION whichRegion, jReal* x, jReal* y)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3C1580
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE RegionAddCellAtLoc(HREGION whichRegion, HLOCATION whichLocation)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3C15B0
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE RegionAddRect(HREGION whichRegion, HRECT r)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3C14E0
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE RegionClearCell(HREGION whichRegion, jReal* x, jReal* y)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3C15F0
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE RegionClearCellAtLoc(HREGION whichRegion, HLOCATION whichLocation)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3C1620
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE RegionClearRect(HREGION whichRegion, HRECT r)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3C1530
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE RegisterStackedSound(HSOUND soundHandle, jBoolean byPosition, jReal* rectwidth, jReal* rectheight)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3CCF80
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE ReloadGame()
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3BBBE0
			jmp eax
		}
	}

	__declspec(naked) jBoolean jNATIVE ReloadGameCachesFromDisk()
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3BC430
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE RemoveAllGuardPositions(HPLAYER num)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3CB840
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE RemoveDestructable(HDESTRUCTABLE d)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3C4730
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE RemoveGuardPosition(HUNIT hUnit)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3CB820
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE RemoveInjuries()
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x2DDDA0
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE RemoveItem(HITEM whichItem)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3C4C30
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE RemoveItemFromAllStock(jInteger itemId)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3B32B0
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE RemoveItemFromStock(HUNIT whichUnit, jInteger itemId)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3C93F0
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE RemoveLocation(HLOCATION whichLocation)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3C0DD0
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE RemovePlayer(HPLAYER whichPlayer, HPLAYERGAMERESULT gameResult)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3C9DC0
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE RemoveRect(HRECT whichRect)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3C16F0
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE RemoveRegion(HREGION whichRegion)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3C14C0
			jmp eax
		}
	}

	__declspec(naked) jBoolean jNATIVE RemoveSaveDirectory(jString sourceDirName)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3BC070
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE RemoveSavedBoolean(HHASHTABLE table, jInteger parentKey, jInteger childKey)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3CB490
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE RemoveSavedHandle(HHASHTABLE table, jInteger parentKey, jInteger childKey)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3CB510
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE RemoveSavedInteger(HHASHTABLE table, jInteger parentKey, jInteger childKey)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3CB410
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE RemoveSavedReal(HHASHTABLE table, jInteger parentKey, jInteger childKey)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3CB450
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE RemoveSavedString(HHASHTABLE table, jInteger parentKey, jInteger childKey)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3CB4D0
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE RemoveSiege()
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x2DDE00
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE RemoveUnit(HUNIT whichUnit)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3C8060
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE RemoveUnitFromAllStock(jInteger unitId)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3B32C0
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE RemoveUnitFromStock(HUNIT whichUnit, jInteger unitId)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3C9430
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE RemoveWeatherEffect(HWEATHEREFFECT whichEffect)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3B3E70
			jmp eax
		}
	}

	__declspec(naked) jBoolean jNATIVE RenameSaveDirectory(jString sourceDirName, jString destDirName)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3BBFB0
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE ResetCaptainLocs()
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x2DD780
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE ResetTerrainFog()
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3B3860
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE ResetToGameCamera(jReal* duration)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3B46B0
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE ResetTrigger(jTrigger whichTrigger)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3C1C20
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE ResetUbersplat(HUBERSPLAT whichSplat)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3B44D0
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE ResetUnitLookAt(HUNIT whichUnit)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3C65F0
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE RestartGame(jBoolean doScoreScreen)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3BBC00
			jmp eax
		}
	}

	__declspec(naked) HUNIT jNATIVE RestoreUnit(HGAMECACHE cache, jString missionKey, jString key, HPLAYER forWhichPlayer, jReal* x, jReal* y, jReal* facing)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3CA970
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE ResumeMusic()
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3B3D90
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE ResumeTimer(HTIMER whichTimer)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3C1420
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE ReturnGuardPosts()
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x2DCFB0
			jmp eax
		}
	}

	__declspec(naked) jBoolean jNATIVE ReviveHero(HUNIT whichHero, jReal* x, jReal* y, jBoolean doEyecandy)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3C6AF0
			jmp eax
		}
	}

	__declspec(naked) jBoolean jNATIVE ReviveHeroLoc(HUNIT whichHero, HLOCATION loc, jBoolean doEyecandy)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3C6B80
			jmp eax
		}
	}

	__declspec(naked) jInteger jNATIVE S2I(jString s)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3B2D10
			jmp eax
		}
	}

	__declspec(naked) jReal jNATIVE S2R(jString s)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3B2D50
			jmp eax
		}
	}

	__declspec(naked) jBoolean jNATIVE SaveAbilityHandle(HHASHTABLE table, jInteger parentKey, jInteger childKey, HABILITY whichAbility)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3CE8C0
			jmp eax
		}
	}

	__declspec(naked) jBoolean jNATIVE SaveAgentHandle(HHASHTABLE table, jInteger parentKey, jInteger childKey, HAGENT whichAgent)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3CEA40
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE SaveBoolean(HHASHTABLE table, jInteger parentKey, jInteger childKey, jBoolean value)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3CA280
			jmp eax
		}
	}

	__declspec(naked) jBoolean jNATIVE SaveBooleanExprHandle(HHASHTABLE table, jInteger parentKey, jInteger childKey, HBOOLEXPR whichBoolexpr)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3CA4E0
			jmp eax
		}
	}

	__declspec(naked) jBoolean jNATIVE SaveButtonHandle(HHASHTABLE table, jInteger parentKey, jInteger childKey, HBUTTON whichButton)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3CA540
			jmp eax
		}
	}

	__declspec(naked) jBoolean jNATIVE SaveDefeatConditionHandle(HHASHTABLE table, jInteger parentKey, jInteger childKey, HDEFEATCONDITION whichDefeatcondition)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3CE980
			jmp eax
		}
	}

	__declspec(naked) jBoolean jNATIVE SaveDestructableHandle(HHASHTABLE table, jInteger parentKey, jInteger childKey, HDESTRUCTABLE whichDestructable)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3CA340
			jmp eax
		}
	}

	__declspec(naked) jBoolean jNATIVE SaveDialogHandle(HHASHTABLE table, jInteger parentKey, jInteger childKey, HDIALOG whichDialog)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3CA520
			jmp eax
		}
	}

	__declspec(naked) jBoolean jNATIVE SaveEffectHandle(HHASHTABLE table, jInteger parentKey, jInteger childKey, HEFFECT whichEffect)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3CE8E0
			jmp eax
		}
	}

	__declspec(naked) jBoolean jNATIVE SaveFogModifierHandle(HHASHTABLE table, jInteger parentKey, jInteger childKey, HFOGMODIFIER whichFogModifier)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3CA640
			jmp eax
		}
	}

	__declspec(naked) jBoolean jNATIVE SaveFogStateHandle(HHASHTABLE table, jInteger parentKey, jInteger childKey, HFOGSTATE whichFogState)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3CA620
			jmp eax
		}
	}

	__declspec(naked) jBoolean jNATIVE SaveForceHandle(HHASHTABLE table, jInteger parentKey, jInteger childKey, HFORCE whichForce)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3CA460
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE SaveGame(jString saveFileName)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3BBEE0
			jmp eax
		}
	}

	__declspec(naked) jBoolean jNATIVE SaveGameCache(HGAMECACHE whichCache)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3CA080
			jmp eax
		}
	}

	__declspec(naked) jBoolean jNATIVE SaveGameExists(jString saveName)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3BC100
			jmp eax
		}
	}

	__declspec(naked) jBoolean jNATIVE SaveGroupHandle(HHASHTABLE table, jInteger parentKey, jInteger childKey, HGROUP whichGroup)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3CA480
			jmp eax
		}
	}

	__declspec(naked) jBoolean jNATIVE SaveHashtableHandle(HHASHTABLE table, jInteger parentKey, jInteger childKey, HHASHTABLE whichHashtable)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3CA660
			jmp eax
		}
	}

	__declspec(naked) jBoolean jNATIVE SaveImageHandle(HHASHTABLE table, jInteger parentKey, jInteger childKey, HIMAGE whichImage)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3CA5E0
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE SaveInteger(HHASHTABLE table, jInteger parentKey, jInteger childKey, jInteger value)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3CA200
			jmp eax
		}
	}

	__declspec(naked) jBoolean jNATIVE SaveItemHandle(HHASHTABLE table, jInteger parentKey, jInteger childKey, HITEM whichItem)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3CA360
			jmp eax
		}
	}

	__declspec(naked) jBoolean jNATIVE SaveItemPoolHandle(HHASHTABLE table, jInteger parentKey, jInteger childKey, HITEMPOOL whichItempool)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3CE920
			jmp eax
		}
	}

	__declspec(naked) jBoolean jNATIVE SaveLeaderboardHandle(HHASHTABLE table, jInteger parentKey, jInteger childKey, HLEADERBOARD whichLeaderboard)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3CE9C0
			jmp eax
		}
	}

	__declspec(naked) jBoolean jNATIVE SaveLightningHandle(HHASHTABLE table, jInteger parentKey, jInteger childKey, HLIGHTNING whichLightning)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3CA5C0
			jmp eax
		}
	}

	__declspec(naked) jBoolean jNATIVE SaveLocationHandle(HHASHTABLE table, jInteger parentKey, jInteger childKey, HLOCATION whichLocation)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3CA4A0
			jmp eax
		}
	}

	__declspec(naked) jBoolean jNATIVE SaveMultiboardHandle(HHASHTABLE table, jInteger parentKey, jInteger childKey, HMULTIBOARD whichMultiboard)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3CE9E0
			jmp eax
		}
	}

	__declspec(naked) jBoolean jNATIVE SaveMultiboardItemHandle(HHASHTABLE table, jInteger parentKey, jInteger childKey, HMULTIBOARDITEM whichMultiboarditem)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3CEA00
			jmp eax
		}
	}

	__declspec(naked) jBoolean jNATIVE SavePlayerHandle(HHASHTABLE table, jInteger parentKey, jInteger childKey, HPLAYER whichPlayer)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3CA300
			jmp eax
		}
	}

	__declspec(naked) jBoolean jNATIVE SaveQuestHandle(HHASHTABLE table, jInteger parentKey, jInteger childKey, HQUEST whichQuest)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3CE940
			jmp eax
		}
	}

	__declspec(naked) jBoolean jNATIVE SaveQuestItemHandle(HHASHTABLE table, jInteger parentKey, jInteger childKey, HQUESTITEM whichQuestitem)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3CE960
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE SaveReal(HHASHTABLE table, jInteger parentKey, jInteger childKey, jReal* value)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3CA240
			jmp eax
		}
	}

	__declspec(naked) jBoolean jNATIVE SaveRectHandle(HHASHTABLE table, jInteger parentKey, jInteger childKey, HRECT whichRect)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3CA4C0
			jmp eax
		}
	}

	__declspec(naked) jBoolean jNATIVE SaveRegionHandle(HHASHTABLE table, jInteger parentKey, jInteger childKey, HREGION whichRegion)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3CA3C0
			jmp eax
		}
	}

	__declspec(naked) jBoolean jNATIVE SaveSoundHandle(HHASHTABLE table, jInteger parentKey, jInteger childKey, HSOUND whichSound)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3CA500
			jmp eax
		}
	}

	__declspec(naked) jBoolean jNATIVE SaveStr(HHASHTABLE table, jInteger parentKey, jInteger childKey, jString value)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3CA2C0
			jmp eax
		}
	}

	__declspec(naked) jBoolean jNATIVE SaveTextTagHandle(HHASHTABLE table, jInteger parentKey, jInteger childKey, HTEXTTAG whichTexttag)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3CA5A0
			jmp eax
		}
	}

	__declspec(naked) jBoolean jNATIVE SaveTimerDialogHandle(HHASHTABLE table, jInteger parentKey, jInteger childKey, HTIMERDIALOG whichTimerdialog)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3CE9A0
			jmp eax
		}
	}

	__declspec(naked) jBoolean jNATIVE SaveTimerHandle(HHASHTABLE table, jInteger parentKey, jInteger childKey, HTIMER whichTimer)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3CA3A0
			jmp eax
		}
	}

	__declspec(naked) jBoolean jNATIVE SaveTrackableHandle(HHASHTABLE table, jInteger parentKey, jInteger childKey, HTRACKABLE whichTrackable)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3CEA20
			jmp eax
		}
	}

	__declspec(naked) jBoolean jNATIVE SaveTriggerActionHandle(HHASHTABLE table, jInteger parentKey, jInteger childKey, HTRIGGERACTION whichTriggeraction)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3CA420
			jmp eax
		}
	}

	__declspec(naked) jBoolean jNATIVE SaveTriggerConditionHandle(HHASHTABLE table, jInteger parentKey, jInteger childKey, HTRIGGERCONDITION whichTriggercondition)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3CA400
			jmp eax
		}
	}

	__declspec(naked) jBoolean jNATIVE SaveTriggerEventHandle(HHASHTABLE table, jInteger parentKey, jInteger childKey, HEVENT whichEvent)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3CA440
			jmp eax
		}
	}

	__declspec(naked) jBoolean jNATIVE SaveTriggerHandle(HHASHTABLE table, jInteger parentKey, jInteger childKey, jTrigger whichTrigger)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3CA3E0
			jmp eax
		}
	}

	__declspec(naked) jBoolean jNATIVE SaveUbersplatHandle(HHASHTABLE table, jInteger parentKey, jInteger childKey, HUBERSPLAT whichUbersplat)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3CA600
			jmp eax
		}
	}

	__declspec(naked) jBoolean jNATIVE SaveUnitHandle(HHASHTABLE table, jInteger parentKey, jInteger childKey, HUNIT whichUnit)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3CA380
			jmp eax
		}
	}

	__declspec(naked) jBoolean jNATIVE SaveUnitPoolHandle(HHASHTABLE table, jInteger parentKey, jInteger childKey, HUNITPOOL whichUnitpool)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3CE900
			jmp eax
		}
	}

	__declspec(naked) jBoolean jNATIVE SaveWidgetHandle(HHASHTABLE table, jInteger parentKey, jInteger childKey, HWIDGET whichWidget)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3CA320
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE SelectHeroSkill(HUNIT whichHero, jInteger abilcode)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3C7050
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE SelectUnit(HUNIT whichUnit, jBoolean flag)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3C7910
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE SetAllItemTypeSlots(jInteger slots)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3B32D0
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE SetAllUnitTypeSlots(jInteger slots)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3B32E0
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE SetAllianceTarget(HUNIT arg1)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x2E0630
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE SetAllyColorFilterState(jInteger state)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3B3A70
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE SetAltMinimapIcon(jString iconPath)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3BC540
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE SetAmphibious()
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x2E0720
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE SetBlight(HPLAYER whichPlayer, jReal* x, jReal* y, jReal* radius, jBoolean addBlight)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3CD4C0
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE SetBlightLoc(HPLAYER whichPlayer, HLOCATION whichLocation, jReal* radius, jBoolean addBlight)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3CD5D0
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE SetBlightPoint(HPLAYER whichPlayer, jReal* x, jReal* y, jBoolean addBlight)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3CD580
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE SetBlightRect(HPLAYER whichPlayer, HRECT r, jBoolean addBlight)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3CD520
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE SetCameraBounds(jReal* x1, jReal* y1, jReal* x2, jReal* y2, jReal* x3, jReal* y3, jReal* x4, jReal* y4)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3B86F0
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE SetCameraField(ECameraField whichField, jReal* value, jReal* duration)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3B48B0
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE SetCameraOrientController(HUNIT whichUnit, jReal* xoffset, jReal* yoffset)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3CD7B0
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE SetCameraPosition(jReal* x, jReal* y)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3B45D0
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE SetCameraQuickPosition(jReal* x, jReal* y)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3B4610
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE SetCameraRotateMode(jReal* x, jReal* y, jReal* radiansToSweep, jReal* duration)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3B4850
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE SetCameraTargetController(HUNIT whichUnit, jReal* xoffset, jReal* yoffset, jBoolean inheritOrientation)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3CD760
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE SetCampaignAI()
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x2DDEA0
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE SetCampaignAvailable(jInteger campaignNumber, jBoolean available)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3B3370
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE SetCampaignMenuRace(HRACE r)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3BC3D0
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE SetCampaignMenuRaceEx(jInteger campaignIndex)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3BC3B0
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE SetCaptainChanges(jBoolean arg1)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x2E2D20
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE SetCaptainHome(jInteger arg1, jReal* arg2, jReal* arg3)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x2DD7B0
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE SetCineFilterBlendMode(HBLENDMODE whichMode)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3B4EB0
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE SetCineFilterDuration(jReal* duration)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3B5100
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE SetCineFilterEndColor(jInteger red, jInteger green, jInteger blue, jInteger alpha)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3CECD0
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE SetCineFilterEndUV(jReal* minu, jReal* minv, jReal* maxu, jReal* maxv)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3B5020
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE SetCineFilterStartColor(jInteger red, jInteger green, jInteger blue, jInteger alpha)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3CEBE0
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE SetCineFilterStartUV(jReal* minu, jReal* minv, jReal* maxu, jReal* maxv)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3B4F40
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE SetCineFilterTexMapFlags(HTEXMAPFLAGS whichFlags)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3B4EF0
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE SetCineFilterTexture(jString filename)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3B4E80
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE SetCinematicCamera(jString cameraModelFile)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3B4820
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE SetCinematicScene(jInteger portraitUnitId, HPLAYERCOLOR color, jString speakerTitle, jString text, jReal* sceneDuration, jReal* voiceoverDuration)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3BCF80
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE SetCreatureDensity(HMAPDENSITY whichdensity)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3BAF50
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE SetCreepCampFilterState(jBoolean state)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3B3AC0
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE SetCustomCampaignButtonVisible(jInteger whichButton, jBoolean visible)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3B3510
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE SetDayNightModels(jString terrainDNCFile, jString unitDNCFile)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3B3790
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE SetDefaultDifficulty(HGAMEDIFFICULTY g)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3B33D0
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE SetDefendPlayer(jBoolean arg1)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x2E30E0
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE SetDestructableAnimation(HDESTRUCTABLE d, jString whichAnimation)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3C4A20
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE SetDestructableAnimationSpeed(HDESTRUCTABLE d, jReal* speedFactor)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3C4A40
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE SetDestructableInvulnerable(HDESTRUCTABLE d, jBoolean flag)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3C4770
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE SetDestructableLife(HDESTRUCTABLE d, jReal* life)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3C4850
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE SetDestructableMaxLife(HDESTRUCTABLE d, jReal* max)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3C48D0
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE SetDestructableOccluderHeight(HDESTRUCTABLE d, jReal* height)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3C4BD0
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE SetDoodadAnimation(jReal* x, jReal* y, jReal* radius, jInteger doodadID, jBoolean nearestOnly, jString animName, jBoolean animRandom)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3B4570
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE SetDoodadAnimationRect(HRECT r, jInteger doodadID, jString animName, jBoolean animRandom)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3CD6F0
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE SetEdCinematicAvailable(jInteger campaignNumber, jBoolean available)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3B3460
			jmp eax
		}
	}

	__declspec(naked) jBoolean jNATIVE SetExpansion(HUNIT arg1, jInteger arg2)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x2E0570
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE SetFloatGameState(HFGAMESTATE whichFloatGameState, jReal* value)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3BC2E0
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE SetFogStateRadius(HPLAYER forWhichPlayer, HFOGSTATE whichState, jReal* centerx, jReal* centerY, jReal* radius, jBoolean useSharedVision)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3C1AB0
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE SetFogStateRadiusLoc(HPLAYER forWhichPlayer, HFOGSTATE whichState, HLOCATION center, jReal* radius, jBoolean useSharedVision)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3C1B20
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE SetFogStateRect(HPLAYER forWhichPlayer, HFOGSTATE whichState, HRECT where, jBoolean useSharedVision)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3C1A30
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE SetGameDifficulty(HGAMEDIFFICULTY whichdifficulty)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3BAF10
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE SetGamePlacement(HPLACEMENT whichPlacementType)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3BAEF0
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE SetGameSpeed(HGAMESPEED whichspeed)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3BAED0
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE SetGameTypeSupported(HGAMETYPE whichGameType, jBoolean value)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3BAE10
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE SetGroupsFlee(jBoolean arg1)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x2E32A0
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE SetHeroAgi(HUNIT whichHero, jInteger newAgi, jBoolean permanent)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3C66A0
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE SetHeroInt(HUNIT whichHero, jInteger newInt, jBoolean permanent)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3C6710
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE SetHeroLevel(HUNIT whichHero, jInteger level, jBoolean showEyeCandy)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3C6D70
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE SetHeroLevels(jCode arg1)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x2E0B00
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE SetHeroStr(HUNIT whichHero, jInteger newStr, jBoolean permanent)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3C6630
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE SetHeroXP(HUNIT whichHero, jInteger newXpVal, jBoolean showEyeCandy)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3C6A70
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE SetHeroesBuyItems(jBoolean arg1)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x2E3160
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE SetHeroesFlee(jBoolean arg1)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x2E3120
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE SetHeroesTakeItems(jBoolean arg1)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x2E3220
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE SetIgnoreInjured(jBoolean arg1)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x2E31E0
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE SetImageAboveWater(HIMAGE whichImage, jBoolean flag, jBoolean useWaterAlpha)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3B4480
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE SetImageColor(HIMAGE whichImage, jInteger red, jInteger green, jInteger blue, jInteger alpha)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3B85B0
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE SetImageConstantHeight(HIMAGE whichImage, jBoolean flag, jReal* height)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3B43E0
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE SetImagePosition(HIMAGE whichImage, jReal* x, jReal* y, jReal* z)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3B4400
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE SetImageRender(HIMAGE whichImage, jBoolean flag)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3B4440
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE SetImageRenderAlways(HIMAGE whichImage, jBoolean flag)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3B4460
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE SetImageType(HIMAGE whichImage, jInteger imageType)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3B44A0
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE SetIntegerGameState(HIGAMESTATE whichIntegerGameState, jInteger value)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3BC350
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE SetIntroShotModel(jString introModelPath)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3BC8A0
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE SetIntroShotText(jString introText)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3BC880
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE SetItemCharges(HITEM whichItem, jInteger charges)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3C5070
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE SetItemDropID(HITEM whichItem, jInteger unitId)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3C5030
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE SetItemDropOnDeath(HITEM whichItem, jBoolean flag)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3C4D00
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE SetItemDroppable(HITEM i, jBoolean flag)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3C4D30
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE SetItemInvulnerable(HITEM whichItem, jBoolean flag)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3C4EE0
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE SetItemPawnable(HITEM i, jBoolean flag)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3C4D60
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE SetItemPlayer(HITEM whichItem, HPLAYER whichPlayer, jBoolean changeColor)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3C4EB0
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE SetItemPosition(HITEM i, jReal* x, jReal* y)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3C4C80
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE SetItemTypeSlots(HUNIT whichUnit, jInteger slots)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3C9470
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE SetItemUserData(HITEM whichItem, jInteger data)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3C50F0
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE SetItemVisible(HITEM whichItem, jBoolean show)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3C4F20
			jmp eax
		}
	}

	__declspec(naked) jBoolean jNATIVE SetLightningColor(HLIGHTNING whichBolt, jReal* r, jReal* g, jReal* b, jReal* a)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3B8490
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE SetMapDescription(jString description)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3BADC0
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE SetMapFlag(HMAPFLAG whichMapFlag, jBoolean value)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3BAE70
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE SetMapMusic(jString musicName, jBoolean random, jInteger index)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3B3CE0
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE SetMapName(jString name)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3BADA0
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE SetMeleeAI()
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x2DDEE0
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE SetMissionAvailable(jInteger campaignNumber, jInteger missionNumber, jBoolean available)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3B3340
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE SetMusicPlayPosition(jInteger millisecs)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3B3E00
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE SetMusicVolume(jInteger volume)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3B3DF0
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE SetNewHeroes(jBoolean arg1)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x2E3020
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE SetOpCinematicAvailable(jInteger campaignNumber, jBoolean available)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3B3400
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE SetPeonsRepair(jBoolean arg1)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x2E3060
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE SetPlayerAbilityAvailable(HPLAYER whichPlayer, jInteger abilid, jBoolean avail)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3C97D0
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE SetPlayerAlliance(HPLAYER sourcePlayer, HPLAYER otherPlayer, HALLIANCETYPE whichAllianceSetting, jBoolean value)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3C1050
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE SetPlayerColor(HPLAYER whichPlayer, HPLAYERCOLOR color)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3C1220
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE SetPlayerController(HPLAYER whichPlayer, HMAPCONTROL controlType)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3C1200
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE SetPlayerHandicap(HPLAYER whichPlayer, jReal* handicap)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3C9E30
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE SetPlayerHandicapXP(HPLAYER whichPlayer, jReal* handicap)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3C9EE0
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE SetPlayerName(HPLAYER whichPlayer, jString name)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3C0F10
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE SetPlayerOnScoreScreen(HPLAYER whichPlayer, jBoolean flag)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3C9800
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE SetPlayerRacePreference(HPLAYER whichPlayer, HRACEPREFERENCE whichRacePreference)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3C11A0
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE SetPlayerRaceSelectable(HPLAYER whichPlayer, jBoolean value)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3C11D0
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE SetPlayerStartLocation(HPLAYER whichPlayer, jInteger startLocIndex)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3C0F80
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE SetPlayerState(HPLAYER whichPlayer, HPLAYERSTATE whichPlayerState, jInteger value)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3C9AA0
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE SetPlayerTaxRate(HPLAYER sourcePlayer, HPLAYER otherPlayer, HPLAYERSTATE whichResource, jInteger rate)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3C10E0
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE SetPlayerTeam(HPLAYER whichPlayer, jInteger whichTeam)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3C0EE0
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE SetPlayerTechMaxAllowed(HPLAYER whichPlayer, jInteger techid, jInteger maximum)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3C9660
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE SetPlayerTechResearched(HPLAYER whichPlayer, jInteger techid, jInteger setToLevel)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3C9730
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE SetPlayerUnitsOwner(HPLAYER whichPlayer, jInteger newOwner)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3C12F0
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE SetPlayers(jInteger playercount)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3BADF0
			jmp eax
		}
	}

	__declspec(naked) jBoolean jNATIVE SetProduce(jInteger arg1, jInteger arg2, jInteger arg3)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x2DD450
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE SetRandomPaths(jBoolean arg1)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x2E30A0
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE SetRandomSeed(jInteger seed)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3B36D0
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE SetRect(HRECT whichRect, jReal* minx, jReal* miny, jReal* maxx, jReal* maxy)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3C1710
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE SetRectFromLoc(HRECT whichRect, HLOCATION min, HLOCATION max)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3C17F0
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE SetReplacementCount(jInteger arg1)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x2E0B30
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE SetReservedLocalHeroButtons(jInteger reserved)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3B3A30
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE SetResourceAmount(HUNIT whichUnit, jInteger amount)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3C77F0
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE SetResourceDensity(HMAPDENSITY whichdensity)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3BAF30
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE SetSkyModel(jString skyModelFile)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3B37D0
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE SetSlowChopping(jBoolean arg1)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x2E32E0
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE SetSmartArtillery(jBoolean arg1)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x2DDF10
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE SetSoundChannel(HSOUND soundHandle, jInteger channel)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3CCC20
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE SetSoundConeAngles(HSOUND soundHandle, jReal* inside, jReal* outside, jInteger outsideVolume)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3CCCF0
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE SetSoundConeOrientation(HSOUND soundHandle, jReal* x, jReal* y, jReal* z)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3CCD30
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE SetSoundDistanceCutoff(HSOUND soundHandle, jReal* cutoff)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3CCCD0
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE SetSoundDistances(HSOUND soundHandle, jReal* minDist, jReal* maxDist)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3CCCA0
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE SetSoundDuration(HSOUND soundHandle, jInteger duration)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3CCEF0
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE SetSoundParamsFromLabel(HSOUND soundHandle, jString soundLabel)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3CCBF0
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE SetSoundPitch(HSOUND soundHandle, jReal* pitch)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3CCC60
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE SetSoundPlayPosition(HSOUND soundHandle, jInteger millisecs)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3CCC80
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE SetSoundPosition(HSOUND soundHandle, jReal* x, jReal* y, jReal* z)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3CCD90
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE SetSoundVelocity(HSOUND soundHandle, jReal* x, jReal* y, jReal* z)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3CCDF0
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE SetSoundVolume(HSOUND soundHandle, jInteger volume)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3CCC40
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE SetStackedSound(jString arg1, jReal* arg2, jReal* arg3)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3B3C20
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE SetStackedSoundRect(jString arg1, HRECT arg2)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3CCA50
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE SetStagePoint(jReal* arg1, jReal* arg2)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x2DDBD0
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE SetStartLocPrio(jInteger whichStartLoc, jInteger prioSlotIndex, jInteger otherStartLocIndex, HSTARTLOCPRIO priority)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3BAFC0
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE SetStartLocPrioCount(jInteger whichStartLoc, jInteger prioSlotCount)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3BAF90
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE SetTargetHeroes(jBoolean arg1)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x2DDE60
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE SetTeams(jInteger teamcount)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3D4000
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE SetTerrainFog(jReal* a, jReal* b, jReal* c, jReal* d, jReal* e)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3B3840
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE SetTerrainFogEx(jInteger style, jReal* zstart, jReal* zend, jReal* density, jReal* red, jReal* green, jReal* blue)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3B81B0
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE SetTerrainPathable(jReal* x, jReal* y, HPATHINGTYPE t, jBoolean flag)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3B42F0
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE SetTerrainType(jReal* x, jReal* y, jInteger terrainType, jInteger variation, jInteger area, jInteger shape)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3BCF20
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE SetTextTagAge(HTEXTTAG t, jReal* age)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3BC7F0
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE SetTextTagColor(HTEXTTAG t, jInteger red, jInteger green, jInteger blue, jInteger alpha)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3BC6A0
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE SetTextTagFadepoint(HTEXTTAG t, jReal* fadepoint)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3BC850
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE SetTextTagLifespan(HTEXTTAG t, jReal* lifespan)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3BC820
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE SetTextTagPermanent(HTEXTTAG t, jBoolean flag)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3BC7C0
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE SetTextTagPos(HTEXTTAG t, jReal* x, jReal* y, jReal* heightOffset)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3BC610
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE SetTextTagPosUnit(HTEXTTAG t, HUNIT whichUnit, jReal* heightOffset)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3CB890
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE SetTextTagSuspended(HTEXTTAG t, jBoolean flag)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3BC790
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE SetTextTagText(HTEXTTAG t, jString s, jReal* height)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3BC5D0
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE SetTextTagVelocity(HTEXTTAG t, jReal* xvel, jReal* yvel)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3BC700
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE SetTextTagVisibility(HTEXTTAG t, jBoolean flag)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3BC760
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE SetThematicMusicPlayPosition(jInteger millisecs)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3B3E10
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE SetTimeOfDayScale(jReal* r)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3BC490
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE SetTutorialCleared(jBoolean cleared)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3B3430
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE SetUbersplatRender(HUBERSPLAT whichSplat, jBoolean flag)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3B4510
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE SetUbersplatRenderAlways(HUBERSPLAT whichSplat, jBoolean flag)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3B4530
			jmp eax
		}
	}

	__declspec(naked) jInteger jNATIVE SetUnitAbilityLevel(HUNIT whichUnit, jInteger abilcode, jInteger level)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3C71B0
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE SetUnitAcquireRange(HUNIT whichUnit, jReal* newAcquireRange)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3C5CF0
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE SetUnitAnimation(HUNIT whichUnit, jString whichAnimation)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3C61A0
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE SetUnitAnimationByIndex(HUNIT whichUnit, jInteger whichAnimation)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3C61F0
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE SetUnitAnimationWithRarity(HUNIT whichUnit, jString whichAnimation, HRARITYCONTROL rarity)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3C61C0
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE SetUnitBlendTime(HUNIT whichUnit, jReal* blendTime)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3C6320
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE SetUnitColor(HUNIT whichUnit, HPLAYERCOLOR whichColor)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3C5F60
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE SetUnitCreepGuard(HUNIT whichUnit, jBoolean creepGuard)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3C5480
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE SetUnitExploded(HUNIT whichUnit, jBoolean exploded)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3CE6D0
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE SetUnitFacing(HUNIT whichUnit, jReal* facingAngle)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3C5AF0
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE SetUnitFacingTimed(HUNIT whichUnit, jReal* facingAngle, jReal* duration)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3C5B30
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE SetUnitFlyHeight(HUNIT whichUnit, jReal* newHeight, jReal* rate)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3C5C60
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE SetUnitFog(jReal* a, jReal* b, jReal* c, jReal* d, jReal* e)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3B3850
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE SetUnitInvulnerable(HUNIT whichUnit, jBoolean flag)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3C72F0
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE SetUnitLookAt(HUNIT whichUnit, jString whichBone, HUNIT lookAtTarget, jReal* offsetX, jReal* offsetY, jReal* offsetZ)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3C64C0
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE SetUnitMoveSpeed(HUNIT whichUnit, jReal* newSpeed)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3C5C40
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE SetUnitOwner(HUNIT whichUnit, HPLAYER whichPlayer, jBoolean changeColor)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3C5ED0
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE SetUnitPathing(HUNIT whichUnit, jBoolean flag)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3C5FA0
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE SetUnitPosition(HUNIT whichUnit, jReal* newX, jReal* newY)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3C5A50
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE SetUnitPositionLoc(HUNIT whichUnit, HLOCATION whichLocation)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3C5AB0
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE SetUnitPropWindow(HUNIT whichUnit, jReal* newPropWindowAngle)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3C5CD0
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE SetUnitRescuable(HUNIT whichUnit, HPLAYER byWhichPlayer, jBoolean flag)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3C5F10
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE SetUnitRescueRange(HUNIT whichUnit, jReal* range)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3C5F40
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE SetUnitScale(HUNIT whichUnit, jReal* scaleX, jReal* scaleY, jReal* scaleZ)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3C62D0
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE SetUnitState(HUNIT whichUnit, HUNITSTATE whichUnitState, jReal* newVal)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3C5EA0
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE SetUnitTimeScale(HUNIT whichUnit, jReal* timeScale)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3C6300
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE SetUnitTurnSpeed(HUNIT whichUnit, jReal* newTurnSpeed)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3C5CB0
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE SetUnitTypeSlots(HUNIT whichUnit, jInteger slots)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3C94B0
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE SetUnitUseFood(HUNIT whichUnit, jBoolean useFood)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3C54A0
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE SetUnitUserData(HUNIT whichUnit, jInteger data)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3C9510
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE SetUnitVertexColor(HUNIT whichUnit, jInteger red, jInteger green, jInteger blue, jInteger alpha)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3C6340
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE SetUnitX(HUNIT whichUnit, jReal* newX)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3C5970
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE SetUnitY(HUNIT whichUnit, jReal* newY)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3C59E0
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE SetUnitsFlee(jBoolean arg1)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x2E3260
			jmp eax
		}
	}

	__declspec(naked) jBoolean jNATIVE SetUpgrade(jInteger arg1)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x2DD4B0
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE SetWatchMegaTargets(jBoolean arg1)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x2E31A0
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE SetWaterBaseColor(jInteger red, jInteger green, jInteger blue, jInteger alpha)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3B8580
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE SetWaterDeforms(jBoolean val)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3B4240
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE SetWidgetLife(HWIDGET whichWidget, jReal* newLife)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3C4690
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE ShiftTownSpot(jReal* arg1, jReal* arg2)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x2DD740
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE ShowDestructable(HDESTRUCTABLE d, jBoolean flag)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3C4A60
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE ShowImage(HIMAGE whichImage, jBoolean flag)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3B43C0
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE ShowInterface(jBoolean flag, jReal* fadeDuration)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3B3810
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE ShowUbersplat(HUBERSPLAT whichSplat, jBoolean flag)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3B44F0
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE ShowUnit(HUNIT whichUnit, jBoolean show)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3CE730
			jmp eax
		}
	}

	__declspec(naked) jReal jNATIVE Sin(jReal* radians)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3B2A10
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE Sleep(jReal* arg1)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x2DE380
			jmp eax
		}
	}

	__declspec(naked) jReal jNATIVE SquareRoot(jReal* x)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3B2BA0
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE StartCampaignAI(HPLAYER num, jString script)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3CB770
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE StartGetEnemyBase()
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x2DDCC0
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE StartMeleeAI(HPLAYER num, jString script)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3CB740
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE StartSound(HSOUND soundHandle)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3CCE80
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE StartThread(jCode arg1)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x2DE2A0
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE StopCamera()
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3B46E0
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE StopGathering()
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x2DCE00
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE StopMusic(jBoolean fadeOut)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3B3D80
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE StopSound(HSOUND soundHandle, jBoolean killWhenDone, jBoolean fadeOut)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3CCEB0
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE StoreBoolean(HGAMECACHE cache, jString missionKey, jString key, jBoolean value)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3CA140
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE StoreInteger(HGAMECACHE cache, jString missionKey, jString key, jInteger value)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3CA0A0
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE StoreReal(HGAMECACHE cache, jString missionKey, jString key, jReal* value)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3CA0F0
			jmp eax
		}
	}

	__declspec(naked) jBoolean jNATIVE StoreString(HGAMECACHE cache, jString missionKey, jString key, jString value)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3CA680
			jmp eax
		}
	}

	__declspec(naked) jBoolean jNATIVE StoreUnit(HGAMECACHE cache, jString missionKey, jString key, HUNIT whichUnit)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3CA1A0
			jmp eax
		}
	}

	__declspec(naked) jString jNATIVE StringCase(jString source, jBoolean upper)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3BAC40
			jmp eax
		}
	}

	__declspec(naked) jInteger jNATIVE StringHash(jString s)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3B2D30
			jmp eax
		}
	}

	__declspec(naked) jInteger jNATIVE StringLength(jString s)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3BAC20
			jmp eax
		}
	}

	__declspec(naked) jString jNATIVE SubString(jString source, jInteger start, jInteger end)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3BABA0
			jmp eax
		}
	}

	__declspec(naked) jBoolean jNATIVE SuicidePlayer(HPLAYER arg1, jBoolean arg2)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x2E2F00
			jmp eax
		}
	}

	__declspec(naked) jBoolean jNATIVE SuicidePlayerUnits(HPLAYER arg1, jBoolean arg2)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x2E2F90
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE SuicideUnit(jInteger arg1, jInteger arg2)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x2DE330
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE SuicideUnitEx(jInteger arg1, jInteger arg2, jInteger arg3)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x2DE2E0
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE SuspendHeroXP(HUNIT whichHero, jBoolean flag)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3C6E10
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE SuspendTimeOfDay(jBoolean b)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3BC460
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE SyncSelections()
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3BB740
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE SyncStoredBoolean(HGAMECACHE cache, jString missionKey, jString key)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3CA780
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE SyncStoredInteger(HGAMECACHE cache, jString missionKey, jString key)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3CA6E0
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE SyncStoredReal(HGAMECACHE cache, jString missionKey, jString key)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3CA730
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE SyncStoredString(HGAMECACHE cache, jString missionKey, jString key)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3CA820
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE SyncStoredUnit(HGAMECACHE cache, jString missionKey, jString key)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3CA7D0
			jmp eax
		}
	}

	__declspec(naked) jReal jNATIVE Tan(jReal* radians)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3B2A50
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE TeleportCaptain(jReal* arg1, jReal* arg2)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x2DD680
			jmp eax
		}
	}

	__declspec(naked) HTERRAINDEFORMATION jNATIVE TerrainDeformCrater(jReal* x, jReal* y, jReal* radius, jReal* depth, jInteger duration, jBoolean permanent)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3B3E90
			jmp eax
		}
	}

	__declspec(naked) HTERRAINDEFORMATION jNATIVE TerrainDeformRandom(jReal* x, jReal* y, jReal* radius, jReal* minDelta, jReal* maxDelta, jInteger duration, jInteger updateInterval)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3B4040
			jmp eax
		}
	}

	__declspec(naked) HTERRAINDEFORMATION jNATIVE TerrainDeformRipple(jReal* x, jReal* y, jReal* radius, jReal* depth, jInteger duration, jInteger count, jReal* spaceWaves, jReal* timeWaves, jReal* radiusStartPct, jBoolean limitNeg)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3B3F00
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE TerrainDeformStop(HTERRAINDEFORMATION deformation, jInteger duration)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3B40B0
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE TerrainDeformStopAll()
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3B40C0
			jmp eax
		}
	}

	__declspec(naked) HTERRAINDEFORMATION jNATIVE TerrainDeformWave(jReal* x, jReal* y, jReal* dirX, jReal* dirY, jReal* distance, jReal* speed, jReal* radius, jReal* depth, jInteger trailTime, jInteger count)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3B3FA0
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE TimerDialogDisplay(HTIMERDIALOG whichDialog, jBoolean display)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3CBF50
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE TimerDialogSetRealTimeRemaining(HTIMERDIALOG whichDialog, jReal* timeRemaining)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3CBFA0
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE TimerDialogSetSpeed(HTIMERDIALOG whichDialog, jReal* speedMultFactor)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3CBF20
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE TimerDialogSetTimeColor(HTIMERDIALOG whichDialog, jInteger red, jInteger green, jInteger blue, jInteger alpha)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3CBED0
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE TimerDialogSetTitle(HTIMERDIALOG whichDialog, jString title)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3CBE50
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE TimerDialogSetTitleColor(HTIMERDIALOG whichDialog, jInteger red, jInteger green, jInteger blue, jInteger alpha)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3CBE80
			jmp eax
		}
	}

	__declspec(naked) jReal jNATIVE TimerGetElapsed(HTIMER whichTimer)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3C13A0
			jmp eax
		}
	}

	__declspec(naked) jReal jNATIVE TimerGetRemaining(HTIMER whichTimer)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3C13C0
			jmp eax
		}
	}

	__declspec(naked) jReal jNATIVE TimerGetTimeout(HTIMER whichTimer)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3C13E0
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE TimerStart(HTIMER whichTimer, jReal* timeout, jBoolean periodic, jCode handlerFunc)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3C1370
			jmp eax
		}
	}

	__declspec(naked) jBoolean jNATIVE TownHasHall(jInteger arg1)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x2DE0A0
			jmp eax
		}
	}

	__declspec(naked) jBoolean jNATIVE TownHasMine(jInteger arg1)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x2DE060
			jmp eax
		}
	}

	__declspec(naked) jBoolean jNATIVE TownThreatened()
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x2DD8E0
			jmp eax
		}
	}

	__declspec(naked) jInteger jNATIVE TownWithMine()
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x2DE030
			jmp eax
		}
	}

	__declspec(naked) HTRIGGERACTION jNATIVE TriggerAddAction(jTrigger whichTrigger, jCode actionFunc)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3C3E90
			jmp eax
		}
	}

	__declspec(naked) HTRIGGERCONDITION jNATIVE TriggerAddCondition(jTrigger whichTrigger, HBOOLEXPR condition)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3C3DF0
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE TriggerClearActions(jTrigger whichTrigger)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3C3F00
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE TriggerClearConditions(jTrigger whichTrigger)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3C3E70
			jmp eax
		}
	}

	__declspec(naked) jBoolean jNATIVE TriggerEvaluate(jTrigger whichTrigger)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3C3F80
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE TriggerExecute(jTrigger whichTrigger)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3C3F40
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE TriggerExecuteWait(jTrigger whichTrigger)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3C3F60
			jmp eax
		}
	}

	__declspec(naked) HEVENT jNATIVE TriggerRegisterDeathEvent(jTrigger whichTrigger, HWIDGET whichWidget)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3D22C0
			jmp eax
		}
	}

	__declspec(naked) HEVENT jNATIVE TriggerRegisterDialogButtonEvent(jTrigger whichTrigger, HBUTTON whichButton)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3D1880
			jmp eax
		}
	}

	__declspec(naked) HEVENT jNATIVE TriggerRegisterDialogEvent(jTrigger whichTrigger, HDIALOG whichDialog)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3D17A0
			jmp eax
		}
	}

	__declspec(naked) HEVENT jNATIVE TriggerRegisterEnterRegion(jTrigger whichTrigger, HREGION whichRegion, HBOOLEXPR filter)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3D2700
			jmp eax
		}
	}

	__declspec(naked) HEVENT jNATIVE TriggerRegisterFilterUnitEvent(jTrigger whichTrigger, HUNIT whichUnit, HUNITEVENT whichEvent, HBOOLEXPR filter)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3D24D0
			jmp eax
		}
	}

	__declspec(naked) HEVENT jNATIVE TriggerRegisterGameEvent(jTrigger whichTrigger, HGAMEEVENT whichGameEvent)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3D1960
			jmp eax
		}
	}

	__declspec(naked) HEVENT jNATIVE TriggerRegisterGameStateEvent(jTrigger whichTrigger, HGAMESTATE whichState, HLIMITOP opcode, jReal* limitval)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3D1630
			jmp eax
		}
	}

	__declspec(naked) HEVENT jNATIVE TriggerRegisterLeaveRegion(jTrigger whichTrigger, HREGION whichRegion, HBOOLEXPR filter)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3D2800
			jmp eax
		}
	}

	__declspec(naked) HEVENT jNATIVE TriggerRegisterPlayerAllianceChange(jTrigger whichTrigger, HPLAYER whichPlayer, HALLIANCETYPE whichAlliance)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3D1BA0
			jmp eax
		}
	}

	__declspec(naked) HEVENT jNATIVE TriggerRegisterPlayerChatEvent(jTrigger whichTrigger, HPLAYER whichPlayer, jString chatMessageToDetect, jBoolean exactMatchOnly)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3D1EF0
			jmp eax
		}
	}

	__declspec(naked) HEVENT jNATIVE TriggerRegisterPlayerEvent(jTrigger whichTrigger, HPLAYER whichPlayer, HPLAYEREVENT whichPlayerEvent)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3D1C90
			jmp eax
		}
	}

	__declspec(naked) HEVENT jNATIVE TriggerRegisterPlayerStateEvent(jTrigger whichTrigger, HPLAYER whichPlayer, HPLAYERSTATE whichState, HLIMITOP opcode, jReal* limitval)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3D1A60
			jmp eax
		}
	}

	__declspec(naked) HEVENT jNATIVE TriggerRegisterPlayerUnitEvent(jTrigger whichTrigger, HPLAYER whichPlayer, HPLAYERUNITEVENT whichPlayerUnitEvent, HBOOLEXPR filter)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3D1DD0
			jmp eax
		}
	}

	__declspec(naked) HEVENT jNATIVE TriggerRegisterTimerEvent(jTrigger whichTrigger, jReal* timeout, jBoolean periodic)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3D1420
			jmp eax
		}
	}

	__declspec(naked) HEVENT jNATIVE TriggerRegisterTimerExpireEvent(jTrigger whichTrigger, HTIMER t)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3D1550
			jmp eax
		}
	}

	__declspec(naked) HEVENT jNATIVE TriggerRegisterTrackableHitEvent(jTrigger whichTrigger, HTRACKABLE t)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3D31C0
			jmp eax
		}
	}

	__declspec(naked) HEVENT jNATIVE TriggerRegisterTrackableTrackEvent(jTrigger whichTrigger, HTRACKABLE t)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3D32A0
			jmp eax
		}
	}

	__declspec(naked) HEVENT jNATIVE TriggerRegisterUnitEvent(jTrigger whichTrigger, HUNIT whichUnit, HUNITEVENT whichEvent)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3D23B0
			jmp eax
		}
	}

	__declspec(naked) HEVENT jNATIVE TriggerRegisterUnitInRange(jTrigger whichTrigger, HUNIT whichUnit, jReal* range, HBOOLEXPR filter)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3D25F0
			jmp eax
		}
	}

	__declspec(naked) HEVENT jNATIVE TriggerRegisterUnitStateEvent(jTrigger whichTrigger, HUNIT whichUnit, HUNITSTATE whichState, HLIMITOP opcode, jReal* limitval)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3D21B0
			jmp eax
		}
	}

	__declspec(naked) HEVENT jNATIVE TriggerRegisterVariableEvent(jTrigger whichTrigger, jString varName, HLIMITOP opcode, jReal* limitval)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3D12E0
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE TriggerRemoveAction(jTrigger whichTrigger, HTRIGGERACTION whichAction)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3C3ED0
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE TriggerRemoveCondition(jTrigger whichTrigger, HTRIGGERCONDITION whichCondition)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3C3E40
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE TriggerSleepAction(jReal* timeout)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3B2DB0
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE TriggerSyncReady()
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3BB710
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE TriggerSyncStart()
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3B2DC0
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE TriggerWaitForSound(HSOUND s, jReal* offset)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3C3F20
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE TriggerWaitOnSleeps(jTrigger whichTrigger, jBoolean flag)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3C1CA0
			jmp eax
		}
	}

	__declspec(naked) jBoolean jNATIVE UnitAddAbility(HUNIT whichUnit, jInteger abilityId)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3C82A0
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE UnitAddIndicator(HUNIT whichUnit, jInteger red, jInteger green, jInteger blue, jInteger alpha)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3C6BD0
			jmp eax
		}
	}

	__declspec(naked) jBoolean jNATIVE UnitAddItem(HUNIT whichUnit, HITEM whichItem)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3C73F0
			jmp eax
		}
	}

	__declspec(naked) HITEM jNATIVE UnitAddItemById(HUNIT whichUnit, jInteger itemId)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3C74F0
			jmp eax
		}
	}

	__declspec(naked) jBoolean jNATIVE UnitAddItemToSlotById(HUNIT whichUnit, jInteger itemId, jInteger itemSlot)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3C75B0
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE UnitAddSleep(HUNIT whichUnit, jBoolean add)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3C8450
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE UnitAddSleepPerm(HUNIT whichUnit, jBoolean add)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3C84D0
			jmp eax
		}
	}

	__declspec(naked) jBoolean jNATIVE UnitAddType(HUNIT whichUnit, HUNITTYPE whichUnitType)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3C7BC0
			jmp eax
		}
	}

	__declspec(naked) jBoolean jNATIVE UnitAlive(HUNIT arg1)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x2E0760
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE UnitApplyTimedLife(HUNIT whichUnit, jInteger buffId, jReal* duration)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3C85D0
			jmp eax
		}
	}

	__declspec(naked) jBoolean jNATIVE UnitCanSleep(HUNIT whichUnit)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3C84A0
			jmp eax
		}
	}

	__declspec(naked) jBoolean jNATIVE UnitCanSleepPerm(HUNIT whichUnit)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3C8520
			jmp eax
		}
	}

	__declspec(naked) jInteger jNATIVE UnitCountBuffsEx(HUNIT whichUnit, jBoolean removePositive, jBoolean removeNegative, jBoolean magic, jBoolean physical, jBoolean timedLife, jBoolean aura, jBoolean autoDispel)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3C83A0
			jmp eax
		}
	}

	__declspec(naked) jBoolean jNATIVE UnitDamagePoint(HUNIT whichUnit, jReal* delay, jReal* radius, jReal* x, jReal* y, jReal* amount, jBoolean attack, jBoolean ranged, HATTACKTYPE attackType, HDAMAGETYPE damageType, HWEAPONTYPE weaponType)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3C8770
			jmp eax
		}
	}

	__declspec(naked) jBoolean jNATIVE UnitDamageTarget(HUNIT whichUnit, HWIDGET target, jReal* amount, jBoolean attack, jBoolean ranged, HATTACKTYPE attackType, HDAMAGETYPE damageType, HWEAPONTYPE weaponType)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3C8850
			jmp eax
		}
	}

	__declspec(naked) jBoolean jNATIVE UnitDropItemPoint(HUNIT whichUnit, HITEM whichItem, jReal* x, jReal* y)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3C8F30
			jmp eax
		}
	}

	__declspec(naked) jBoolean jNATIVE UnitDropItemSlot(HUNIT whichUnit, HITEM whichItem, jInteger slot)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3C9010
			jmp eax
		}
	}

	__declspec(naked) jBoolean jNATIVE UnitDropItemTarget(HUNIT whichUnit, HITEM whichItem, HWIDGET target)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3C8FA0
			jmp eax
		}
	}

	__declspec(naked) jBoolean jNATIVE UnitHasBuffsEx(HUNIT whichUnit, jBoolean removePositive, jBoolean removeNegative, jBoolean magic, jBoolean physical, jBoolean timedLife, jBoolean aura, jBoolean autoDispel)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3C8360
			jmp eax
		}
	}

	__declspec(naked) jBoolean jNATIVE UnitHasItem(HUNIT whichUnit, HITEM whichItem)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3C76F0
			jmp eax
		}
	}

	__declspec(naked) jInteger jNATIVE UnitId(jString unitIdString)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3BB650
			jmp eax
		}
	}

	__declspec(naked) jString jNATIVE UnitId2String(jInteger unitId)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3BB680
			jmp eax
		}
	}

	__declspec(naked) jBoolean jNATIVE UnitIgnoreAlarm(HUNIT whichUnit, jBoolean flag)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3C8640
			jmp eax
		}
	}

	__declspec(naked) jBoolean jNATIVE UnitIgnoreAlarmToggled(HUNIT whichUnit)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3C8690
			jmp eax
		}
	}

	__declspec(naked) jInteger jNATIVE UnitInventorySize(HUNIT whichUnit)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3C8F00
			jmp eax
		}
	}

	__declspec(naked) jBoolean jNATIVE UnitInvis(HUNIT arg1)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x2E07C0
			jmp eax
		}
	}

	__declspec(naked) jBoolean jNATIVE UnitIsSleeping(HUNIT whichUnit)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3C8550
			jmp eax
		}
	}

	__declspec(naked) HITEM jNATIVE UnitItemInSlot(HUNIT whichUnit, jInteger itemSlot)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3C7730
			jmp eax
		}
	}

	__declspec(naked) jBoolean jNATIVE UnitMakeAbilityPermanent(HUNIT whichUnit, jBoolean permanent, jInteger abilityId)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3C8250
			jmp eax
		}
	}

	__declspec(naked) jBoolean jNATIVE UnitModifySkillPoints(HUNIT whichHero, jInteger skillPointDelta)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3C69A0
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE UnitPauseTimedLife(HUNIT whichUnit, jBoolean flag)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3C8750
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE UnitPoolAddUnitType(HUNITPOOL whichPool, jInteger unitId, jReal* weight)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3CB5E0
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE UnitPoolRemoveUnitType(HUNITPOOL whichPool, jInteger unitId)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3CB600
			jmp eax
		}
	}

	__declspec(naked) jBoolean jNATIVE UnitRemoveAbility(HUNIT whichUnit, jInteger abilityId)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3C8310
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE UnitRemoveBuffs(HUNIT whichUnit, jBoolean removePositive, jBoolean removeNegative)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3C83E0
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE UnitRemoveBuffsEx(HUNIT whichUnit, jBoolean removePositive, jBoolean removeNegative, jBoolean magic, jBoolean physical, jBoolean timedLife, jBoolean aura, jBoolean autoDispel)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3C8410
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE UnitRemoveItem(HUNIT whichUnit, HITEM whichItem)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3C7660
			jmp eax
		}
	}

	__declspec(naked) HITEM jNATIVE UnitRemoveItemFromSlot(HUNIT whichUnit, jInteger itemSlot)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3C76A0
			jmp eax
		}
	}

	__declspec(naked) jBoolean jNATIVE UnitRemoveType(HUNIT whichUnit, HUNITTYPE whichUnitType)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3C7C20
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE UnitResetCooldown(HUNIT whichUnit)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3C86D0
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE UnitSetConstructionProgress(HUNIT whichUnit, jInteger constructionPercentage)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3C86F0
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE UnitSetUpgradeProgress(HUNIT whichUnit, jInteger upgradePercentage)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3C8720
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE UnitSetUsesAltIcon(HUNIT whichUnit, jBoolean flag)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3CB860
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE UnitShareVision(HUNIT whichUnit, HPLAYER whichPlayer, jBoolean share)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3C81C0
			jmp eax
		}
	}

	__declspec(naked) jBoolean jNATIVE UnitStripHeroLevel(HUNIT whichHero, jInteger howManyLevels)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3C6930
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE UnitSuspendDecay(HUNIT whichUnit, jBoolean suspend)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3C81F0
			jmp eax
		}
	}

	__declspec(naked) jBoolean jNATIVE UnitUseItem(HUNIT whichUnit, HITEM whichItem)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3C9090
			jmp eax
		}
	}

	__declspec(naked) jBoolean jNATIVE UnitUseItemPoint(HUNIT whichUnit, HITEM whichItem, jReal* x, jReal* y)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3C9100
			jmp eax
		}
	}

	__declspec(naked) jBoolean jNATIVE UnitUseItemTarget(HUNIT whichUnit, HITEM whichItem, HWIDGET target)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3C9170
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE UnitWakeUp(HUNIT whichUnit)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3C8590
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE UnregisterStackedSound(HSOUND soundHandle, jBoolean byPosition, jReal* rectwidth, jReal* rectheight)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3CCFB0
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE Unsummon(HUNIT arg1)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x2E08A0
			jmp eax
		}
	}

	__declspec(naked) jBoolean jNATIVE VersionCompatible(HVERSION whichVersion)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3B3300
			jmp eax
		}
	}

	__declspec(naked) HVERSION jNATIVE VersionGet()
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3B32F0
			jmp eax
		}
	}

	__declspec(naked) jBoolean jNATIVE VersionSupported(HVERSION whichVersion)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3B3310
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE VolumeGroupReset()
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3B3E50
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE VolumeGroupSetVolume(HVOLUMEGROUP vgroup, jReal* scale)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3B3E30
			jmp eax
		}
	}

	__declspec(naked) jBoolean jNATIVE WaitGetEnemyBase()
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x2DDCF0
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE WaygateActivate(HUNIT waygate, jBoolean activate)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3C92D0
			jmp eax
		}
	}

	__declspec(naked) jReal jNATIVE WaygateGetDestinationX(HUNIT waygate)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3C91F0
			jmp eax
		}
	}

	__declspec(naked) jReal jNATIVE WaygateGetDestinationY(HUNIT waygate)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3C9240
			jmp eax
		}
	}

	__declspec(naked) jBoolean jNATIVE WaygateIsActive(HUNIT waygate)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3C9310
			jmp eax
		}
	}

	__declspec(naked) jNothing jNATIVE WaygateSetDestination(HUNIT waygate, jReal* x, jReal* y)
	{
		_asm
		{
			mov eax, address_GameBase
			add eax, 0x3C9290
			jmp eax
		}
	}
}