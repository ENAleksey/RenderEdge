#pragma once

#include <AntTweakBar.h>
#include "Utils.h"

class CAntTweakBar
{
private:
	IDirect3DDevice9* m_pDevice;
	bool bActive;

public:
	CAntTweakBar(IDirect3DDevice9* pDevice);
	~CAntTweakBar();

	void Render();
	void OnResetDevice();
	void OnLostDevice();
	bool OnGetMessage(HWND ah_Wnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

	void SetActive(bool value);
	bool GetActive();

	static void TW_CALL SetPauseGame_cb(const void *value, void *clientData);
	static void TW_CALL GetPauseGame_cb(void *value, void *clientData);
	static void TW_CALL SetFreeCamera_cb(const void *value, void *clientData);
	static void TW_CALL GetFreeCamera_cb(void *value, void *clientData);
	static void TW_CALL SetVsync_cb(const void *value, void *clientData);
	static void TW_CALL GetVsync_cb(void *value, void *clientData);
	static void TW_CALL SetUserInterface_cb(const void *value, void *clientData);
	static void TW_CALL GetUserInterface_cb(void *value, void *clientData);
	static void TW_CALL SetMaskedObject_cb(const void *value, void *clientData);
	static void TW_CALL GetMaskedObject_cb(void *value, void *clientData);
	static void TW_CALL SetBuildingsShadows_cb(const void *value, void *clientData);
	static void TW_CALL GetBuildingsShadows_cb(void *value, void *clientData);
	static void TW_CALL SetMapBounds_cb(const void *value, void *clientData);
	static void TW_CALL GetMapBounds_cb(void *value, void *clientData);
	static void TW_CALL SetLutFloat_cb(const void *value, void *clientData);
	static void TW_CALL SetLutBool_cb(const void *value, void *clientData);
	static void TW_CALL SetLutColor_cb(const void *value, void *clientData);
	static void TW_CALL GetLutFloat_cb(void *value, void *clientData);
	static void TW_CALL GetLutBool_cb(void *value, void *clientData);
	static void TW_CALL GetLutColor_cb(void *value, void *clientData);
	static void TW_CALL CheckAllRenderStages_cb(void *clientData);
};

extern CAntTweakBar* AntTweakBar;
