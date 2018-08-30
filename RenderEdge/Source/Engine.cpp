#include "Engine.h"
#include "JassApi.h"
#include "Storm.h"
#include "CJass.h"
#include "Log.h"
#include "Input.h"
#include "RenderStageController.h"
#include "GUI.h"
#include "TextureManager.h"
#include "FontManager.h"
#include "PostProcessManager.h"
#include "GameOffsets.h"
#include "MPQ.h"
#include "fp_call.h"
#include <chrono>
#include <psapi.h>
#include <iomanip>
#include "Utils.h"

#include "CGameUI.h"
CGameUI* GameUI = nullptr;


const std::string RenderEdgeVersion = "v0.2.7a";

uintptr_t address_GameBase;

uint32 g_Stride;
IDirect3DTexture9* g_pTexture9;
D3DTRANSFORMSTATETYPE g_TransformState;

bool g_presented = false;
uint32 g_wndWidth = 0;
uint32 g_wndHeight = 0;
HWND g_hWnd;
std::string RenderEdgePath;
HANDLE g_hRenderEdgeMpq;
float fWideScreenMul = 1.0f;
bool bWidescreen = false;
bool g_bDebug = false;
bool g_bAllowLocalFiles = false;

bool g_bAnisoFiltering = false;
int g_iMaxAnisotropy = 16;

bool g_bVsyncEnabled = true;
float g_fDeltaTime;
float g_fFPS;


IDirect3DVertexBuffer9* g_pWar3VertexData;
IDirect3DVertexDeclaration9 *g_pVertexDecl;

IDirect3DIndexBuffer9* g_pIndexData9;
IDirect3DVertexBuffer9* g_pStreamData9;



ID3DXFont *g_pFont;




void SetFramePointPos(uint32 pFrame, EFramePoint point, uint32 pParentFrame, EFramePoint relativePoint, const D3DXVECTOR2& pos)
{
	this_call<void**>(address_SetFramePoint, pFrame, point, pParentFrame, relativePoint, pos.x, pos.y, 1);
}

void SetFramePoint(uint32 pFrame, EFramePoint point, uint32 pParentFrame, EFramePoint relativePoint, float offsetX, float offsetY)
{
	this_call<void**>(address_SetFramePoint, pFrame, point, pParentFrame, relativePoint, offsetX, offsetY, 1);
}

void SetFramePointSimple(uint32 pFrame, EFramePoint point, float offsetX, float offsetY)
{
	fast_call<int>(address_GameBase + 0x629490, pFrame, offsetX, offsetY);
}

void SetFrameWidth(uint32 pFrame, float width)
{
	this_call<void**>(address_SetFrameWidth, pFrame, width);
}

void SetFrameHeight(uint32 pFrame, float height)
{
	this_call<void**>(address_SetFrameHeight, pFrame, height);
}

float GetFrameWidth(uint32 pFrame)
{
	return *(float*)(pFrame + 88);
}

float GetFrameHeight(uint32 pFrame)
{
	return *(float*)(pFrame + 92);
}

void UpdateFrame(char* pFrame, int a)
{
	this_call<void**>(address_GameBase + 0x605CC0, pFrame, a);
}

uint32 GetFramePoint(uint32 pFrame, EFramePoint point)
{
	return *(uint32*)(pFrame + 4 * static_cast<uint32>(point) + 8);
}

uint32 GetFramePointParent(uint32 pFrame, EFramePoint point)
{
	return *(uint32*)(GetFramePoint(pFrame, point) + 4);
}

uint32 GetFramePointRelativePoint(uint32 pFrame, EFramePoint point)
{
	return *(uint32*)(GetFramePoint(pFrame, point) + 8);
}

float GetFramePointX(uint32 pFrame, EFramePoint point)
{
	return *(float*)(GetFramePoint(pFrame, point) + 12);
}

float GetFramePointY(uint32 pFrame, EFramePoint point)
{
	return *(float*)(GetFramePoint(pFrame, point) + 16);
}

D3DXVECTOR2 GetFramePointPos(uint32 pFrame, EFramePoint point)
{
	uint32 pFramePoint = GetFramePoint(pFrame, point);
	return D3DXVECTOR2(*(float*)(pFramePoint + 12), *(float*)(pFramePoint + 16));
}

int32 GetFrameAddress(const char* name)
{
	return this_call<int32>(address_GameBase + 0x5FA970, name);
}

int32 ShowFrame(BYTE* a1, int a2, int a3)
{
	return this_call<int32>(address_GameBase + 0x5FDEC0, a1, a2, a3);
}

uint32 DisableUI(void* gameUI, uint32 bReset, uint32 bDisable, uint32 bUserControl)
{
	return this_call<uint32>(address_GameBase + 0x2FC0F0, gameUI, bReset, bDisable, bUserControl);
}

void EditFrameAdv(uint32 pFrame, EFramePoint relativePoint, int32 offsetX, int32 offsetY, uint32 width, uint32 height)
{
	uint32 pRootFrame = GetGameUI(0, 0) + 180;
	SetFramePoint(pFrame, EFramePoint::TopLeft, pRootFrame, relativePoint, offsetX, offsetY);
	SetFramePoint(pFrame, EFramePoint::BottomLeft, pRootFrame, relativePoint, offsetX, offsetY - height);
	SetFramePoint(pFrame, EFramePoint::TopRight, pRootFrame, relativePoint, offsetX + width, offsetY);
	SetFramePoint(pFrame, EFramePoint::BottomRight, pRootFrame, relativePoint, offsetX + width, offsetY - height);
}

void EditFrame(uint32 pFrame, EFramePoint relativePoint, int32 offsetX, int32 offsetY, uint32 width, uint32 height)
{
	int32 pRootFrame = GetGameUI(0, 0) + 180;
	SetFramePoint(pFrame, EFramePoint::TopLeft, pRootFrame, relativePoint, offsetX, offsetY);
	SetFrameWidth(pFrame, width);
	SetFrameHeight(pFrame, height);
}

uint32 GetPanelButton(uint32 pFrame, uint8 row, uint8 column)
{
	return *(DWORD*)(*(DWORD*)(16 * row + *((DWORD*)pFrame + 85) + 8) + 4 * column);
}

uint32 GetUpperButtonBarButton(uint8 id)
{
	uint32 pUpperButtonBar = GameUI->UpperButtonBarFrame;
	if (id == 0)
		return *((uint32*)pUpperButtonBar + 78);
	else if (id == 1)
		return *((uint32*)pUpperButtonBar + 76);
	else if (id == 2)
		return *((uint32*)pUpperButtonBar + 77);
	else if (id == 3)
		return *((uint32*)pUpperButtonBar + 88);

	return 0;
}

uint32 GetCommandBarButton(uint8 row, uint8 column)
{
	return GetPanelButton(GameUI->CommandBar, row, column);
}

uint32 GetItemBarButton(uint8 id)
{
	uint32 pItemBar = *((uint32*)GameUI->InfoBar + 82);
	return *(uint32*)(*((uint32*)pItemBar + 76) + 8 * id + 4);
}

uint32 GetHeroBarButton(uint8 id)
{
	return GetPanelButton(GameUI->HeroBar, id, 0);
}

int GetCursorSkillID()
{
	int pOffset = *(int*)(GetGameUI(0, 0) + 0x1B4);
	if (pOffset > 0)
		return *(int*)(pOffset + 0xC);

	return 0;
}



void GetScreenSize(IDirect3DDevice9* pDevice9)
{
	IDirect3DSurface9* t_pSurface = nullptr;
	D3DSURFACE_DESC t_Desc;
	pDevice9->GetBackBuffer(0, 0, D3DBACKBUFFER_TYPE_MONO, &t_pSurface);
	t_pSurface->GetDesc(&t_Desc);
	g_wndWidth = t_Desc.Width;
	g_wndHeight = t_Desc.Height;
	t_pSurface->Release();
}




Engine* MainEngine;

Engine::Engine(IDirect3DDevice9* pDevice)
{
	LOG(logINFO) << "========= On Create Engine ============";
	LOG(logINFO) << "RenderEdge " << RenderEdgeVersion + (g_bDebug ? " (Debug)" : "");
	LOG(logINFO) << "WarCraft III build " << static_cast<uint32>(GetGameVersion());

	m_pDevice = pDevice;
	bMapInit = false;
	OnCreateDevice();
}

Engine::~Engine()
{
	LOG(logINFO) << "========= On Destroy Engine ===========\n\n";

	SAFE_RELEASE(g_pFont);

	SAFE_DELETE(MainGUI);
	SAFE_DELETE(MainTextureManager);
	SAFE_DELETE(MainFontManager);
	//SAFE_DELETE(PP_Manager);
}

void UpdateWidescreenFix(float width, float height)
{
	fWideScreenMul = (width * 3.0f) / (height * 4.0f);
}

void Engine::OnCreateDevice()
{
	GetScreenSize(m_pDevice);
	UpdateWidescreenFix(g_wndWidth, g_wndHeight);

	MPQ::OpenArchive(RenderEdgePath + "RenderEdge.mpq", &g_hRenderEdgeMpq);

	MainTextureManager = new TextureManager(m_pDevice);
	MainFontManager = new FontManager(m_pDevice);
	MainGUI = new GUI(m_pDevice);
	//PP_Manager = new PostProcessManager(m_pDevice);

	if (!g_pFont)
		D3DXCreateFontA(m_pDevice, 0, 0, FW_BOLD, 1, FALSE, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, ANTIALIASED_QUALITY, DEFAULT_PITCH | FF_DONTCARE, "Arial", &g_pFont);
}

void Engine::OnLostDevice()
{
	g_pFont->OnLostDevice();
	MainGUI->OnLostDevice();

	//PP_Manager->OnLostDevice();
}

void Engine::OnResetDevice()
{
	GetScreenSize(m_pDevice);
	UpdateWidescreenFix(g_wndWidth, g_wndHeight);

	ExecuteWindowResizeTriggers();

	g_pFont->OnResetDevice();
	MainGUI->OnResetDevice();

	//PP_Manager->OnResetDevice();
}

void Engine::OnMapStart()
{
	GameUI = (CGameUI*)GetGameUI(0, 0);
}

void Engine::OnMapEnd()
{
	MainGUI->Release();

	ClearExecuteTriggers();
}


double GetTime()
{
	auto beginningOfTime = std::chrono::system_clock::now().time_since_epoch();
	auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(beginningOfTime).count();

	return ms * 0.001;
}

void CalculateFrameRate()
{
	static double framesPerSecond = 0.0;
	static double startTime = GetTime();
	static double lastTime = GetTime();
	static double currentFPS = 0.0;

	double CurrentTime = GetTime();

	g_fDeltaTime = (CurrentTime - lastTime);

	lastTime = CurrentTime;

	++framesPerSecond;

	if (CurrentTime - startTime > 1.0)
	{
		startTime = CurrentTime;

		g_fFPS = framesPerSecond;

		framesPerSecond = 0;
	}
}

void OnGameState()
{
	if (IsGaming())
	{
		if (!MainEngine->bMapInit)
		{
			MainEngine->OnMapStart();
			MainEngine->bMapInit = true;
			LOG(logDEBUG) << "========= On Map Start ================";
		}
	}
	else
	{
		if (MainEngine->bMapInit)
		{
			MainEngine->OnMapEnd();
			MainEngine->bMapInit = false;
			LOG(logDEBUG) << "========= On Map End ==================";
		}
	}
}

bool bHDRStarted = false;
void Engine::OnBeginScene()
{
	/*m_pDevice->SetDepthStencilSurface(g_pDepthSurface);
	m_pDevice->Clear(0, nullptr, D3DCLEAR_ZBUFFER, 0x00000000, g_bReverseZ ? 0.0f : 1.0f, 0);

	if (g_bEnableHDR && !g_bDefRenderer)
	{
		if (!bHDRStarted)
			bHDRStarted = true;

		m_pDevice->GetBackBuffer(0, 0, D3DBACKBUFFER_TYPE_MONO, &g_pLDRSurface);
		m_pDevice->SetRenderTarget(0, g_pHDRSurface);
		m_pDevice->Clear(0, nullptr, D3DCLEAR_TARGET | D3DCLEAR_STENCIL, 0x00000000, g_bReverseZ ? 0.0f : 1.0f, 0);
	}*/
}

void Engine::OnEndScene()
{
	/*if (bHDRStarted)
	{
		m_pDevice->SetRenderTarget(0, g_pLDRSurface);
		SAFE_RELEASE(g_pLDRSurface);
		bHDRStarted = false;
	}*/
}

void Engine::OnRender()
{
	g_presented = false;

	OnGameState();
	CalculateFrameRate();

	ExecuteFrameUpdateTriggers();

	RenderText();
}


HRESULT Engine::OnDrawIndexedPrimitive(int32 baseVertexIndex, IDirect3DTexture9* currentTexture, uint32 stride, DWORD FVF, D3DTRANSFORMSTATETYPE state, D3DPRIMITIVETYPE type, uint32 minIndex, uint32 numVertices, uint32 startIndex, uint32 primCount)
{
	RenderStage curRenderStage = GetRenderStage();

	if (g_bAnisoFiltering)
	{
		DWORD minFilter;
		m_pDevice->GetSamplerState(0, D3DSAMP_MINFILTER, &minFilter);
		if (minFilter != D3DTEXF_POINT)
		{
			m_pDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_ANISOTROPIC);
			m_pDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_ANISOTROPIC);
			m_pDevice->SetSamplerState(0, D3DSAMP_MIPFILTER, D3DTEXF_ANISOTROPIC);
			m_pDevice->SetSamplerState(0, D3DSAMP_MAXANISOTROPY, g_iMaxAnisotropy);
		}
	}

	if (curRenderStage == RenderStage::PORTRAIT)
	{
		//D3DVIEWPORT9 oldViewport;
		//m_pDevice->GetViewport(&oldViewport);
		//D3DVIEWPORT9 newViewport = { oldViewport.X, oldViewport.Y, oldViewport.Width, oldViewport.Height, 0.0f, 0.0f };

		//m_pDevice->SetViewport(&newViewport);
		return m_pDevice->DrawIndexedPrimitive(type, baseVertexIndex, minIndex, numVertices, startIndex, primCount);
		//m_pDevice->SetViewport(&oldViewport);
	}
	else if (curRenderStage == RenderStage::UI || curRenderStage == RenderStage::PARTICLES)
	{
		if (!g_presented)
		{
			g_presented = true;

			if (bMapInit)
			{
				if (GetGameState() != GameState::LOADING)
				{
					//PP_Manager->Render();

					MainGUI->Draw();
				}
			}
		}
		return m_pDevice->DrawIndexedPrimitive(type, baseVertexIndex, minIndex, numVertices, startIndex, primCount);
	}

	return m_pDevice->DrawIndexedPrimitive(type, baseVertexIndex, minIndex, numVertices, startIndex, primCount);
}






bool OnGetMessage(HWND ah_Wnd, uint32 uMsg, WPARAM wParam, LPARAM lParam)
{
	return false;
}

bool OnMouseMove(uint32 x, uint32 y)
{
	return false;
}

bool OnMouseButtonDown(int32 button)
{
	return false;
}

bool OnMouseButtonUp(int32 button)
{
	return false;
}

bool OnMouseWheel(int32 delta)
{
	return false;
}

bool OnKeyboardDown(WPARAM getKey)
{
	if (getKey == 'H')
	{
		//uint32 pTestFrame = GameUI->FrameB + 180;
		//EditFrame(pTestFrame, EFramePoint::BottomLeft, 0.4f, 0.3f, 0.2f / fWideScreenMul, 0.2f);

		//ShowFrame((BYTE*)GameUI->field0404, 0, 0);

		int32 pRootFrame = GetGameUI(0, 0) + 180;

		//uint32 pCursorFrame = this_call<uint32>(address_GameBase + 0x60A6E0, GetGameUI(1, 0), 1);
		//if (pCursorFrame)
		//	SetFramePoint(pCursorFrame + 180, EFramePoint::TopLeft, pRootFrame, EFramePoint::Center, 0.0f, 0.0f);
		
		//int32 pTestFrame = GameUI->field015C + 0;// *(uint32*)(GameUI->SimpleConsole + 340);
		//SetFramePoint(pTestFrame, EFramePoint::TopLeft, pRootFrame, EFramePoint::TopLeft, 0.4f, -0.3f);
		//SetFrameWidth(pTestFrame, 0.2f);

		/*int pTestFrame = fast_call<int>(address_GameBase + 0x608490, GetGameUI(0, 0), 0, 0);
		int pTexture = fast_call<int>(address_GameBase + 0x31F530, (int)"SimpleProgressBarConsole", 0);
		SetFrameWidth(pTestFrame + 180, 0.2f);
		SetFrameHeight(pTestFrame + 180, 0.2f);
		SetFramePoint(pTestFrame + 180, EFramePoint::TopLeft, GetGameUI(0, 0) + 180, EFramePoint::Center, 0, 0);
		this_call<void>(address_GameBase + 0x60E090, GameUI->InfoBar, pTexture, 0);*/

		//message = (const char *)pTexture;// std::to_string(pTexture);

		//uint32 pFrame = GetCommandBarButton(2, 0);
		//uint32 pCooldownFrame = *((uint32*)pFrame + 108);
		//float* a1 = (float*)pCooldownFrame;
		//message = std::to_string(GetFramePointX(pCooldownFrame + 180, EFramePoint::TopLeft)) + " " + std::to_string(a1[91]) + " " + std::to_string(a1[103]) + " " + std::to_string(a1[106]);

		//*(float*)(GetFramePoint(pCooldownFrame , EFramePoint::TopLeft) + 12) = 0.1f;
		//SetFrameWidth(*((DWORD*)GetHeroBarButton(0) + 101), 0.015625f / fWideScreenMul);

		//a1[22] = 0.1f;
		//SetFrameWidth(*((DWORD*)pFrame + 103) + 180, 0.2f);
		//UpdateFrame((char*)(*((DWORD*)pFrame + 103) + 180), 1);
		//SetFramePointSimple(*((DWORD*)pFrame + 103) + 180, EFramePoint::TopLeft, 0.0f, 0.0f);
		//SetFramePoint(*((DWORD*)pFrame + 103) + 180, EFramePoint::BottomRight, pRootFrame, EFramePoint::Center, 0.1f, 0.1f);

		//SetFramePoint(pFrame, EFramePoint::TopLeft, pRootFrame, EFramePoint::Center, 0.0f, 0.0f);
		//SetFrameWidth(*((DWORD*)pFrame + 115), 0.2f); // health
		//SetFrameWidth(*((DWORD*)pFrame + 116), 0.2f); // mana

		//SetFramePoint(*(DWORD*)(pFrame + 115), EFramePoint::Top, pRootFrame, EFramePoint::Bottom, 0.0f, 0.1f);
		//SetFrameWidth(*(DWORD*)(pFrame + 115), 0.08f); // health
		//SetFrameHeight(*(DWORD*)(pFrame + 115), 0.01f); // health
		//SetFrameWidth(*(DWORD*)(pFrame + 116), 0.08f); // mana
		//SetFrameHeight(*(DWORD*)(pFrame + 116), 0.01f); // mana

		//SetFramePoint(*(DWORD*)(pFrame + 472) + 180, EFramePoint::TopLeft, pRootFrame, EFramePoint::Center, 0.0f, 0.0f);
		//SetFramePoint(*(DWORD*)(pFrame + 472) + 180, EFramePoint::BottomRight, pRootFrame, EFramePoint::Center, 0.1f, -0.1f);

		//int32 v3 = GetGameUI(0, 0);
		//TestInterface((void *)v3, 0, 1, 0);
		//ShowChatLine(*(DWORD *)(v3 + 1020), 0);
		//HideInterfaceTest(*(DWORD *)(v3 + 1064), 0);
		//ShowFrame(*(BYTE**)(v3 + 1052), 0, 0); // Hide Clock
		//ShowFrame(*(BYTE**)(v3 + 1060), 0, 0); // Hide Portrait
		//ShowFrame(*(BYTE**)(v3 + 1024), 255, 0); // Show CinematicPanel

		//*(DWORD *)(*(DWORD *)(v3 + 960) + 1572) = 0;
		//*(DWORD *)(*(DWORD *)(v3 + 960) + 1564) = 1;
		//*(DWORD *)(*(DWORD *)(v3 + 1004) + 144) = 0; // 144 - bShow
		//*(DWORD *)(*(DWORD *)(v3 + 1008) + 144) = 0;
		//*(DWORD *)(*(DWORD *)(v3 + 996) + 144) = 0;

		//*(DWORD *)(v3 + 384) = 3;
		//*(DWORD *)(*(DWORD *)(v3 + 1064) + 144) = 0;
	}
	else if (getKey == 'Z')
	{
		bWidescreen = !bWidescreen;
	}
	return false;
}

bool OnKeyboardUp(WPARAM getKey)
{
	return false;
}




std::string message;

void Engine::RenderText()
{
	std::ostringstream output;

	output << std::endl;

	if (bMapInit)
	{
		if (g_bDebug)
		{
			uint32 mX = GetMouseX();
			uint32 mY = GetMouseY();

			PROCESS_MEMORY_COUNTERS memCounter;
			GetProcessMemoryInfo(GetCurrentProcess(), &memCounter, sizeof(memCounter));
			uint32 memoryUsed = memCounter.WorkingSetSize / 1048576;

			output
				<< g_fFPS << " FPS" << std::endl
				<< std::fixed << std::setprecision(0) << g_fDeltaTime*1000.0f << " ms" << std::endl
				<< memoryUsed << " MB" << std::endl << std::endl

				<< "MouseX: " << mX << "  (" << (float)mX / GetWindowWidth() << ")" << std::endl
				<< "MouseY: " << mY << "  (" << (float)mY / GetWindowHeight() << ")" << std::endl << std::endl

				//<< "MouseUI X: " << MouseUI.x << std::endl
				//<< "MouseUI Y: " << MouseUI.y << std::endl << std::endl

				<< "Control ID: " << MainGUI->GetCtrlFromMousePoint() << std::endl;

			output << std::endl << message << std::endl;
		}
	}
	else
	{
		output << "RenderEdge " << RenderEdgeVersion << (g_bDebug ? " (Debug)" : "") << std::endl;
	}

	g_pFont->DrawTextA(0, output.str().c_str(), -1, nullptr, DT_EXPANDTABS | DT_LEFT, D3DCOLOR_XRGB(230, 230, 230));
}


