#pragma once

#include <windows.h>
#include <stdio.h>
#include "int_t.h"

#define jNATIVE __cdecl

typedef void   jNothing;
typedef uint32 jBoolean;
typedef uint32 jCode;
typedef uint32 jHandle;
typedef int32  jInteger;
typedef uint32 jReal;
typedef uint32 jString;
typedef uint32 jTrigger;

const static jBoolean jTrue = 1;
const static jBoolean jFalse = 0;
const static jHandle jNull = 0;

float from_jReal(jReal val);
jReal to_jReal(float val);


bool JassApiInit();
void InitializeMutilWar3();
bool AddNative(uintptr_t routine, const char *name, const char *prototype);


uint32 GetGameUI(uint32 unk0, uint32 unk1);
uint32 ReadGameUIArray(uint32 element);

bool IsGamePaused();
bool IsGaming();


void ExecuteFrameUpdateTriggers();
void ClearExecuteTriggers();

enum class GameState : int32
{
	NONE = -1,
	NOTHING = 0,
	LOBBY = 1,
	LOADING = 3,
	INGAME = 4,
	PAUSED = 6
};

GameState GetGameState();

enum class GameVersion : uint32
{
	v124a = 6372,
	v124b = 6374,
	v124c = 6378,
	v124d = 6384,
	v124e = 6387,
	v125a = 6396,
	v125b = 6397,
	v126a = 6401,
	v127a = 52240,
	v127b = 7085,
	v128a = 7205,
	v128b = 7365,
	v128c = 7395,
	v128f = 7680,
};

GameVersion GetGameVersion();