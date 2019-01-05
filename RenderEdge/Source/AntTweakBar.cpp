#include "AntTweakBar.h"
#include "Engine.h"


CAntTweakBar* AntTweakBar = nullptr;

CAntTweakBar::CAntTweakBar(IDirect3DDevice9* pDevice)
{
	m_pDevice = pDevice;
	bActive = true;

	Init();
}

CAntTweakBar::~CAntTweakBar()
{
	TwTerminate();
}


void CAntTweakBar::OnResetDevice()
{
	TwWindowSize(Engine->vBufferSize.x, Engine->vBufferSize.y);
}

void CAntTweakBar::OnLostDevice()
{
	TwWindowSize(0, 0);
}

bool CAntTweakBar::OnGetMessage(HWND ah_Wnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	if (!bActive)
		return false;

	return TwEventWin(ah_Wnd, uMsg, wParam, lParam);
}

void CAntTweakBar::Render()
{
	if (!bActive)
		return;

	TwDraw();
}

void CAntTweakBar::SetActive(bool value)
{
	bActive = value;

	if (bActive)
	{
	}
}

bool CAntTweakBar::GetActive()
{
	return bActive;
}