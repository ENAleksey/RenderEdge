#pragma once

#include <d3d9.h>
#include <d3dx9.h>
#include "int_t.h"

extern D3DXVECTOR2 MousePos;
extern D3DXVECTOR2 MouseUI;
extern bool bIsMouseOverUI;
extern D3DXVECTOR3 MouseTerrain;

int32 Screen2World(float rx, float ry, float& wx, float& wy);

bool IsKeyDown(int32 Key);
bool IsMouseOverUI();
uint32 GetMouseX();
uint32 GetMouseY();
int32 GetMouseXRelative();
int32 GetMouseYRelative();
D3DXVECTOR2 GetMousePos();
uint32 GetWindowWidth();
uint32 GetWindowHeight();
float GetAspectRatio();
uint32 GetWindowX();
uint32 GetWindowY();
void BlockMouse(bool bBlock);

bool InitInputSystem();

bool OnMouseMove(uint32 x, uint32 y);
bool OnMouseButtonDown(int32 button);
bool OnMouseButtonUp(int32 button);
bool OnMouseWheel(int32 delta);
bool OnKeyboardDown(WPARAM getKey);
bool OnKeyboardUp(WPARAM getKey);
bool OnGetMessage(HWND ah_Wnd, uint32 uMsg, WPARAM wParam, LPARAM lParam);

void ExecuteKeyTriggers(int32 key, int32 state);
void ExecuteMouseTriggers(int32 key, int32 state);
void ExecuteWheelTriggers(int32 delta);
void ExecuteMouseMoveTriggers(int32 x, int32 y);
void ExecuteWindowResizeTriggers();