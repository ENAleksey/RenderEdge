#include "Input.h"

#include "Engine.h"
#include "GameUI.h"
#include "Detour.h"
#include "fp_call.h"
#include "GameOffsets.h"
#include "CustomJassNatives.h"

namespace Input
{
	HWND hWnd;
	D3DXVECTOR2 vMousePos;
	D3DXVECTOR2 vMousePosUI;
	D3DXVECTOR3 vMousePosTerrain;
	bool bMouseOverUI = false;
	bool bMouseBlock = false;


	bool IsKeyDown(uint32 Key)
	{
		return (GetKeyState(Key) & 0x8000) != 0;
	}

	uint32 GetWindowWidth()
	{
		return g_vBufferSize.x;
	}

	uint32 GetWindowHeight()
	{
		return g_vBufferSize.y;
	}

	int32 GetWindowX()
	{
		RECT r;
		GetWindowRect(hWnd, &r);
		return lround(r.left);
	}

	int32 GetWindowY()
	{
		RECT r;
		GetWindowRect(hWnd, &r);
		return lround(r.top);
	}

	int32 GetWindowCenterX()
	{
		return GetWindowX() + GetWindowWidth() * 0.5f;
	}

	int32 GetWindowCenterY()
	{
		return GetWindowY() + GetWindowHeight() * 0.5f;
	}

	void CenterMouse()
	{
		SetCursorPos(GetWindowCenterX(), GetWindowCenterY());
	}

	int32 GetMouseX()
	{
		POINT p;
		GetCursorPos(&p);
		return p.x;
	}

	int32 GetMouseY()
	{
		POINT p;
		GetCursorPos(&p);
		return p.y;
	}

	int32 GetMouseXRelative()
	{
		POINT pt;
		GetCursorPos(&pt);
		ScreenToClient(hWnd, &pt);
		return pt.x;
	}

	int32 GetMouseYRelative()
	{
		POINT pt;
		GetCursorPos(&pt);
		ScreenToClient(hWnd, &pt);
		return pt.y;
	}

	D3DXVECTOR2 GetMousePos()
	{
		return D3DXVECTOR2(GetMouseX(), GetMouseY());
	}

	void BlockMouse(bool bBlock)
	{
		bMouseBlock = bBlock;
	}

	bool IsMouseOverUI()
	{
		return bMouseOverUI != 0;
	}


	int32 __stdcall MouseEvent_proxy(float uiX, float uiY, uint32 terrainPtr, int32 a4)
	{
		CGameUI* pGameUI = GetGameUI(0, 0);
		uint32 pWorldFrame = pGameUI->WorldFrameWar3;
		int32 result = this_call<int32>(address_MouseEvent, pWorldFrame, uiX, uiY, terrainPtr, a4);

		bMouseOverUI = !result;
		vMousePosUI = D3DXVECTOR2(uiX, uiY);
		vMousePosTerrain = *(D3DXVECTOR3*)terrainPtr;

		return result;
	}

	int32 __stdcall WndProc_proc(HWND hWnd, uint32 Msg, WPARAM wParam, LPARAM lParam)
	{
		Input::hWnd = hWnd;

		if (!Engine)
			return std_call<int32>(address_WndProc, hWnd, Msg, wParam, lParam);

		if (Engine->OnGetMessage(hWnd, Msg, wParam, lParam))
			Msg = WM_NULL;
		
		switch (Msg)
		{
		case WM_KEYDOWN:
			if ((((lParam >> 30) & 1) == 0))
			{
				if (Engine->OnKeyboardDown(wParam))
					Msg = WM_NULL;

				ExecuteKeyTriggers(wParam, 0);
			}
			break;
		case WM_KEYUP:
			if (Engine->OnKeyboardUp(wParam))
				Msg = WM_NULL;

			ExecuteKeyTriggers(wParam, 1);
			break;
		case WM_CHAR:
			break;

		case WM_MOUSEMOVE:
			if (Engine->OnMouseMove(LOWORD(lParam), HIWORD(lParam)) || bMouseBlock)
				Msg = WM_NULL;

			ExecuteMouseMoveTriggers(LOWORD(lParam), HIWORD(lParam));
			break;

		case WM_LBUTTONDOWN:
			if (Engine->OnMouseButtonDown(EMouseButton::Left) || bMouseBlock)
				Msg = WM_NULL;

			ExecuteMouseTriggers(0, 0);
			break;
		case WM_LBUTTONUP:
			if (Engine->OnMouseButtonUp(EMouseButton::Left) || bMouseBlock)
				Msg = WM_NULL;

			ExecuteMouseTriggers(0, 1);
			break;
		case WM_LBUTTONDBLCLK:
			break;

		case WM_RBUTTONDOWN:
			if (Engine->OnMouseButtonDown(EMouseButton::Right) || bMouseBlock)
				Msg = WM_NULL;

			ExecuteMouseTriggers(2, 0);
			break;
		case WM_RBUTTONUP:
			if (Engine->OnMouseButtonUp(EMouseButton::Right) || bMouseBlock)
				Msg = WM_NULL;

			ExecuteMouseTriggers(2, 1);
			break;
		case WM_RBUTTONDBLCLK:
			break;

		case WM_MBUTTONDOWN:
			if (Engine->OnMouseButtonDown(EMouseButton::Middle) || bMouseBlock)
				Msg = WM_NULL;

			ExecuteMouseTriggers(1, 0);
			break;
		case WM_MBUTTONUP:
			if (Engine->OnMouseButtonUp(EMouseButton::Middle) || bMouseBlock)
				Msg = WM_NULL;

			ExecuteMouseTriggers(1, 1);
			break;
		case WM_MBUTTONDBLCLK:
			break;

		case WM_XBUTTONDOWN:
			if (HIWORD(wParam) == 1)
			{
				if (Engine->OnMouseButtonDown(EMouseButton::X1) || bMouseBlock)
					Msg = WM_NULL;

				ExecuteMouseTriggers(3, 0);
			}
			if (HIWORD(wParam) == 2)
			{
				if (Engine->OnMouseButtonDown(EMouseButton::X2) || bMouseBlock)
					Msg = WM_NULL;

				ExecuteMouseTriggers(4, 0);
			}
			break;
		case WM_XBUTTONUP:
			if (HIWORD(wParam) == 1)
			{
				if (Engine->OnMouseButtonUp(EMouseButton::X1) || bMouseBlock)
					Msg = WM_NULL;

				ExecuteMouseTriggers(3, 1);
			}
			if (HIWORD(wParam) == 2)
			{
				if (Engine->OnMouseButtonUp(EMouseButton::X2) || bMouseBlock)
					Msg = WM_NULL;

				ExecuteMouseTriggers(4, 1);
			}
		case WM_XBUTTONDBLCLK:
			break;

		case WM_MOUSEWHEEL:
			if (Engine->OnMouseWheel((short)HIWORD(wParam)) || bMouseBlock)
				Msg = WM_NULL;

			ExecuteWheelTriggers((short)HIWORD(wParam));
			break;

		default:
			break;
		}

		return std_call<int32>(address_WndProc, hWnd, Msg, wParam, lParam);
	}


	bool Init()
	{
		bool bResult = true;

		bResult &= Detour::Install(&address_MouseEvent, (uintptr_t)MouseEvent_proxy);
		bResult &= Detour::Install(&address_WndProc, (uintptr_t)WndProc_proc);

		return bResult;
	}
}