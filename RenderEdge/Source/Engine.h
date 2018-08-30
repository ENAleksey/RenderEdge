#pragma once

#include <d3d9.h>
#include <d3dx9.h>
#include <iostream>
#include "int_t.h"

//#define REDEBUG

extern uintptr_t address_GameBase;

extern uint32 g_Stride;
extern IDirect3DTexture9* g_pTexture9;
extern D3DTRANSFORMSTATETYPE g_TransformState;

extern std::string RenderEdgePath;
extern HANDLE g_hRenderEdgeMpq;

extern uint32 g_wndWidth, g_wndHeight;
extern HWND g_hWnd;
extern float fWideScreenMul;

extern bool g_bAnisoFiltering;
extern int g_iMaxAnisotropy;

extern bool g_bVsyncEnabled;
extern float g_fFPS;
extern float g_fDeltaTime;
extern bool bWidescreen;
extern bool g_bDebug;
extern bool g_bAllowLocalFiles;

extern std::string message;

extern IDirect3DIndexBuffer9* g_pIndexData9;
extern IDirect3DVertexBuffer9* g_pStreamData9;

extern bool startFrameHook;

void ResetDevice();

enum class EFramePoint
{
	TopLeft = 0,
	Top = 1,
	TopRight = 2,
	Left = 3,
	Center = 4,
	Right = 5,
	BottomLeft = 6,
	Bottom = 7,
	BottomRight = 8
};

void SetFramePointPos(uint32 pFrame, EFramePoint point, uint32 pParentFrame, EFramePoint relativePoint, const D3DXVECTOR2& pos);
void SetFramePoint(uint32 pFrame, EFramePoint point, uint32 pParentFrame, EFramePoint relativePoint, float offsetX, float offsetY);
void SetFrameWidth(uint32 pFrame, float width);
void SetFrameHeight(uint32 pFrame, float height);
float GetFrameWidth(uint32 pFrame);
float GetFrameHeight(uint32 pFrame);
uint32 GetFramePointParent(uint32 pFrame, EFramePoint point);
uint32 GetFramePointRelativePoint(uint32 pFrame, EFramePoint point);
float GetFramePointX(uint32 pFrame, EFramePoint point);
float GetFramePointY(uint32 pFrame, EFramePoint point);
D3DXVECTOR2 GetFramePointPos(uint32 pFrame, EFramePoint point);
void EditFrame(uint32 pFrame, EFramePoint relativePoint, int32 offsetX, int32 offsetY, uint32 width, uint32 height);

uint32 GetCommandBarButton(uint8 row, uint8 column);
uint32 GetItemBarButton(uint8 id);
uint32 GetUpperButtonBarButton(uint8 id);
uint32 GetHeroBarButton(uint8 id);


class Engine
{
public:
	Engine(IDirect3DDevice9* pDevice);
	~Engine();

	IDirect3DDevice9* m_pDevice;
	bool bMapInit;

	void OnRender();
	void RenderText();
	void OnCreateDevice();
	void OnMapStart();
	void OnMapEnd();

	HRESULT OnDrawIndexedPrimitive(int32 baseVertexIndex, IDirect3DTexture9* currentTexture,
		uint32 stride, DWORD FVF, D3DTRANSFORMSTATETYPE state, D3DPRIMITIVETYPE type,
		uint32 minIndex, uint32 numVertices, uint32 startIndex, uint32 primCount);

	void OnLostDevice();
	void OnResetDevice();

	void OnBeginScene();
	void OnEndScene();
};

extern Engine* MainEngine;