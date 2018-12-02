#include "JassApi.h"
#include <list>
#include "fp_call.h"
#include "Engine.h"
#include "Detour.h"
#include "GameOffsets.h"
#include "CustomJassNatives.h"

namespace Jass
{
	float from_jReal(jReal val)
	{
		return *(float*)&val;
	}

	jReal to_jReal(float val)
	{
		return *(jReal*)&val;
	}

	const char* from_jString(jString val)
	{
		if (!val)
			return nullptr;

		val = *(uint32*)(val + 8);

		if (!val)
			return nullptr;

		char* string = (char*)(*(uint32*)(val + 28));

		return utils::from_utf8(string);
	}

	uint32 GetTerrain()
	{
		return fast_call<uint32>(address_GetTerrain);
	}

	uint32 GetGxDevice()
	{
		uint32 pGxDevice = *(uint32*)address_gxDevice;
		return pGxDevice;
	}

	void __fastcall BindNative(uintptr_t callback, char* name, char* arguments)
	{
		fast_call<int>(address_BindJassNative, callback, name, arguments);
	}


	int InitJassNatives_proxy()
	{
		int result = fast_call<int>(address_InitJassNatives);

		InitCustomNatives();

		return result;
	}

	bool Init()
	{
		bool bResult = Detour::Install(&address_InitJassNatives, (uintptr_t)InitJassNatives_proxy);

		return bResult;
	}
}