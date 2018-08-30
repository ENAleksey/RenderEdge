#include "Input.h"
#include "Engine.h"
#include "JassApi.h"
#include "inline.h"
#include "fp_call.h"
#include "CJass.h"
#include "GameOffsets.h"

bool bIsMouseOverUI = false;
D3DXVECTOR2 MouseUI;
D3DXVECTOR3 MouseTerrain;

bool IsKeyDown(int32 Key)
{
	return (GetKeyState(Key) & 0x8000) != 0;
}

bool IsMouseOverUI()
{
	return bIsMouseOverUI != 0;
}

uint32 GetWindowWidth()
{
	return g_wndWidth;
}

uint32 GetWindowHeight()
{
	return g_wndHeight;
}

float GetAspectRatio()
{
	return (float)g_wndWidth / (float)g_wndHeight;
}

uint32 GetWindowX()
{
	RECT r;
	GetWindowRect(g_hWnd, &r);
	return lround(r.left);
}

uint32 GetWindowY()
{
	RECT r;
	GetWindowRect(g_hWnd, &r);
	return lround(r.top);
}

int32 GetMouseXRelative()
{
	POINT pt;
	GetCursorPos(&pt);
	ScreenToClient(g_hWnd, &pt);
	return pt.x;
}

int32 GetMouseYRelative()
{
	POINT pt;
	GetCursorPos(&pt);
	ScreenToClient(g_hWnd, &pt);
	return pt.y;
}


D3DXVECTOR2 MousePos;

uint32 GetMouseX()
{
	POINT pt;
	GetCursorPos(&pt);
	return pt.x;
}

uint32 GetMouseY()
{
	POINT pt;
	GetCursorPos(&pt);
	return pt.y;
}

D3DXVECTOR2 GetMousePos()
{
	POINT pt;
	GetCursorPos(&pt);
	return D3DXVECTOR2(pt.x, pt.y);
}

bool bMouseBlock = false;
void BlockMouse(bool bBlock)
{
	bMouseBlock = bBlock;
}


int32 __fastcall MouseEvent_proxy(float* cworldframe, int32 unused, float uiX, float uiY, uint32 terrainPtr, int32 a4)
{
	//uint32 cgameui = GetGameUI(0, 0);
	//uintptr_t cworldframe = *(uintptr_t*)(cgameui + 0x3BC);
	int32 retval = this_call<int32>(address_MouseEvent, cworldframe, uiX, uiY, terrainPtr, a4);

	bIsMouseOverUI = !retval;
	MouseUI = D3DXVECTOR2(uiX, uiY);
	MouseTerrain = *(D3DXVECTOR3*)terrainPtr;

	return retval;
}

int32 __stdcall WndProc_proxy(HWND hWnd, uint32 Msg, WPARAM wParam, LPARAM lParam)
{
	g_hWnd = hWnd;

	if (OnGetMessage(hWnd, Msg, wParam, lParam))
		Msg = WM_NULL;

	switch (Msg)
	{
	case WM_KEYDOWN:
		if ((((lParam >> 30) & 1) == 0))
		{
			OnKeyboardDown(wParam);
			ExecuteKeyTriggers(wParam, 0);
		}
		break;
	case WM_KEYUP:
		if(OnKeyboardUp(wParam))
			Msg = WM_NULL;
		ExecuteKeyTriggers(wParam, 1);
		break;
	case WM_CHAR:
		break;

	case WM_MOUSEMOVE:
		MousePos.x = LOWORD(lParam);
		MousePos.y = HIWORD(lParam);
		if(OnMouseMove(LOWORD(lParam), HIWORD(lParam)) || bMouseBlock)
			Msg = WM_NULL;
		ExecuteMouseMoveTriggers(LOWORD(lParam), HIWORD(lParam));
		break;

	case WM_LBUTTONDOWN:
		if (OnMouseButtonDown(0) || bMouseBlock)
			Msg = WM_NULL;
		ExecuteMouseTriggers(0, 0);
		break;
	case WM_LBUTTONUP:
		if (OnMouseButtonUp(0) || bMouseBlock)
			Msg = WM_NULL;
		ExecuteMouseTriggers(0, 1);
		break;
	case WM_LBUTTONDBLCLK:
		break;

	case WM_RBUTTONDOWN:
		if (OnMouseButtonDown(2) || bMouseBlock)
			Msg = WM_NULL;
		ExecuteMouseTriggers(2, 0);
		break;
	case WM_RBUTTONUP:
		if (OnMouseButtonUp(2) || bMouseBlock)
			Msg = WM_NULL;
		ExecuteMouseTriggers(2, 1);
		break;
	case WM_RBUTTONDBLCLK:
		break;

	case WM_MBUTTONDOWN:
		if (OnMouseButtonDown(1) || bMouseBlock)
			Msg = WM_NULL;
		ExecuteMouseTriggers(1, 0);
		break;
	case WM_MBUTTONUP:
		if (OnMouseButtonUp(1) || bMouseBlock)
			Msg = WM_NULL;
		ExecuteMouseTriggers(1, 1);
		break;
	case WM_MBUTTONDBLCLK:
		break;

	case WM_XBUTTONDOWN:
		if (HIWORD(wParam) == 1)
		{
			if (OnMouseButtonDown(3) || bMouseBlock)
				Msg = WM_NULL;
			ExecuteMouseTriggers(3, 0);
		}
		if (HIWORD(wParam) == 2)
		{
			if (OnMouseButtonDown(4) || bMouseBlock)
				Msg = WM_NULL;
			ExecuteMouseTriggers(4, 0);
		}
		break;
	case WM_XBUTTONUP:
		if (HIWORD(wParam) == 1)
		{
			if (OnMouseButtonUp(3) || bMouseBlock)
				Msg = WM_NULL;
			ExecuteMouseTriggers(3, 1);
		}
		if (HIWORD(wParam) == 2)
		{
			if (OnMouseButtonUp(4) || bMouseBlock)
				Msg = WM_NULL;
			ExecuteMouseTriggers(4, 1);
		}
	case WM_XBUTTONDBLCLK:
		break;

	case WM_MOUSEWHEEL:
		if (OnMouseWheel((short)HIWORD(wParam)) || bMouseBlock)
			Msg = WM_NULL;
		ExecuteWheelTriggers((short)HIWORD(wParam));
		break;

	default:
		break;
	}

	return std_call<int32>(address_WndProc, hWnd, Msg, wParam, lParam);
}



bool InitInputSystem()
{
	base::hook::inline_install(&address_MouseEvent, (uintptr_t)MouseEvent_proxy);
	base::hook::inline_install(&address_WndProc, (uintptr_t)WndProc_proxy);

	return true;
}