#pragma once

#include "Utils.h"

#define jNATIVE __cdecl

typedef void   jNothing;
typedef uint32 jBoolean;
typedef uint32 jCode;
typedef uint32 jHandle;
typedef int32  jInteger;
typedef uint32 jReal;
typedef uint32 jString;
typedef uint32 jTrigger;

const jBoolean jTrue = 1;
const jBoolean jFalse = 0;
const jHandle jNull = 0;

namespace Jass
{
	float from_jReal(jReal val);
	jReal to_jReal(float val);
	const char* from_jString(jString val);

	uint32 GetTerrain();
	uint32 GetGxDevice();
	void __fastcall BindNative(uintptr_t callback, char* name, char* arguments);

	bool Init();
}