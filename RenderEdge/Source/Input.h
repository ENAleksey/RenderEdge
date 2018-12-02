#pragma once

#include "Utils.h"

enum class EMouseButton
{
	Left,
	Middle,
	Right,
	X1,
	X2
};

namespace Input
{
	extern HWND hWnd;
	extern D3DXVECTOR2 vMousePos;
	extern D3DXVECTOR2 vMousePosUI;
	extern D3DXVECTOR3 vMousePosTerrain;

	bool IsKeyDown(uint32 Key);
	int32 GetWindowX();
	int32 GetWindowY();
	int32 GetWindowCenterX();
	int32 GetWindowCenterY();
	uint32 GetWindowWidth();
	uint32 GetWindowHeight();
	void CenterMouse();
	int32 GetMouseX();
	int32 GetMouseY();
	int32 GetMouseXRelative();
	int32 GetMouseYRelative();
	D3DXVECTOR2 GetMousePos();
	void BlockMouse(bool bBlock);
	bool IsMouseOverUI();

	bool Init();
}