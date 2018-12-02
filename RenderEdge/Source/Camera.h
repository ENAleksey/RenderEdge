#pragma once

#include "Input.h"

class CCamera
{
public:
	CCamera();
	~CCamera();

	void Update(float deltaTime);

	void OnMouseWheel(int delta);
	void OnMouseButtonDown(EMouseButton button);
	void OnMouseButtonUp(EMouseButton button);
	void OnKeyboardDown(WPARAM getKey);
	void OnKeyboardUp(WPARAM getKey);

	const D3DXVECTOR3& GetEyePosition();
	const D3DXVECTOR3& GetTargetPosition();
	const D3DXVECTOR3& GetRotation();
	const D3DXVECTOR3& GetForwardVector();
	const D3DXVECTOR3& GetRightVector();

	void SetActive(bool value);
	bool GetActive();

	float m_fSpeed;
	D3DXVECTOR3 m_vEyePosition;
	D3DXVECTOR3 m_vTargetPosition;

private:
	bool m_bActive;

	bool m_bRMB;
	bool m_bShift;
	
	float m_fDistance;

	float m_fYaw;
	float m_fPitch;
	float m_fSensX;
	float m_fSensY;
};

extern CCamera* FreeCamera;