#pragma once

#include <AntTweakBar.h>
#include "Utils.h"

class CAntTweakBar
{
private:
	IDirect3DDevice9* m_pDevice;
	bool bActive;

	void Init();

public:
	CAntTweakBar(IDirect3DDevice9* pDevice);
	~CAntTweakBar();

	void Render();
	void OnResetDevice();
	void OnLostDevice();
	bool OnGetMessage(HWND ah_Wnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

	void SetActive(bool value);
	bool GetActive();
};

extern CAntTweakBar* AntTweakBar;
