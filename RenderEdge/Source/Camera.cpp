#include "Camera.h"

#include "JassNatives.h"
#include "fp_call.h"
#include "Engine.h"

CCamera* FreeCamera = nullptr;

const float kMetersToWorldUnits = 100.0f;



CCamera::CCamera()
{
	m_bActive = false;
	m_bRMB = false;
	m_bShift = false;

	m_fYaw = 90.0f;
	m_fPitch = 0.0f;

	m_fSensX = 0.05f;
	m_fSensY = 0.05f;
	m_fSpeed = 4.0f;

	m_fDistance = 0.0f;
	m_vEyePosition = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_vTargetPosition = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
}

CCamera::~CCamera()
{
}



void SetCameraField(ECameraField field, float fValue, float fDuration = 0.0f)
{
	jReal value = Jass::to_jReal(fValue);
	jReal duration = Jass::to_jReal(fDuration);
	JassNatives::SetCameraField(field, &value, &duration);
}

float GetCameraField(ECameraField field)
{
	return Jass::from_jReal(JassNatives::GetCameraField(field));
}

float NormalizeYaw(float fYaw)
{
	if (fYaw > 180.0f)
		fYaw -= 360.0f;
	else if (fYaw < -180.0f)
		fYaw += 360.0f;

	return fYaw;
}

float NormalizePitch(float fPitch)
{
	if (fPitch > 89.0f && fPitch <= 180.0f)
		fPitch = 89.0f;

	if (fPitch > 180.0f)
		fPitch -= 360.0f;
	else if (fPitch < -89.0f)
		fPitch = -89.0f;

	return fPitch;
}

//void SetCameraEyePosition(const D3DXVECTOR3& pos)
//{
//	uint32 pGameUI = GetGameUI(1, 0);
//	uint32 pWorldFrame = *((uint32*)pGameUI + 239);
//	uint32 pGameCamera = *((uint32*)pWorldFrame + 80);
//
//	*(float*)(pGameCamera + 60) = pos.x;
//	*(float*)(pGameCamera + 64) = pos.y;
//	*(float*)(pGameCamera + 68) = pos.z;
//}
//
//void SetCameraTargetPosition(const D3DXVECTOR3& pos)
//{
//	uint32 pGameUI = GetGameUI(1, 0);
//	uint32 pWorldFrame = *((uint32*)pGameUI + 239);
//	uint32 pGameCamera = *((uint32*)pWorldFrame + 80);
//
//	*(float*)(pGameCamera + 100) = pos.x;
//	*(float*)(pGameCamera + 104) = pos.y;
//	*(float*)(pGameCamera + 108) = pos.z;
//}



const D3DXVECTOR3& CCamera::GetEyePosition()
{
	return m_vEyePosition;
}

const D3DXVECTOR3& CCamera::GetTargetPosition()
{
	return m_vTargetPosition;
}

const D3DXVECTOR3& CCamera::GetRotation()
{
	return D3DXVECTOR3(m_fYaw, m_fPitch, 0.0f);
}

const D3DXVECTOR3& CCamera::GetForwardVector()
{
	float fYaw = D3DXToRadian(m_fYaw);
	float fPitch = D3DXToRadian(m_fPitch);

	D3DXVECTOR3 forward;
	forward.x = cos(fPitch) * cos(fYaw);
	forward.y = cos(fPitch) * sin(fYaw);
	forward.z = sin(fPitch);

	return forward;
}

const D3DXVECTOR3& CCamera::GetRightVector()
{
	float fYaw = D3DXToRadian(m_fYaw - 90);

	D3DXVECTOR3 right;
	right.x = cos(fYaw);
	right.y = sin(fYaw);
	right.z = 0.0f;

	return right;
}

void CCamera::SetActive(bool value)
{
	m_bActive = value;

	if (m_bActive)
	{
		m_fYaw = D3DXToDegree(g_vCameraRotation.x);
		m_fPitch = D3DXToDegree(g_vCameraRotation.y);

		m_vEyePosition.x = g_vCameraPos.x;
		m_vEyePosition.y = g_vCameraPos.y;
		m_vEyePosition.z = g_vCameraPos.z;

		m_vTargetPosition = m_vEyePosition + GetForwardVector() * 100.0f;
	}
	else
	{
		// Fix offset

		SetCameraField(ECameraField::Yaw, m_fYaw);
		SetCameraField(ECameraField::Pitch, m_fPitch);
		SetCameraField(ECameraField::Distance, D3DXVec3Length(&(m_vTargetPosition - m_vEyePosition)));
		SetCameraField(ECameraField::ZOffset, m_vTargetPosition.z);

		jReal x = Jass::to_jReal(m_vTargetPosition.x);
		jReal y = Jass::to_jReal(m_vTargetPosition.y);
		jReal zero = Jass::to_jReal(0.0f);
		JassNatives::PanCameraToTimed(&x, &y, &zero);
	}
}

bool CCamera::GetActive()
{
	return m_bActive;
}



void CCamera::Update(float deltaTime)
{
	if (!m_bActive || !m_bRMB)
		return;

	bool bUpdatePosition = false;

	const int mouseX = Input::GetMouseX();
	const int mouseY = Input::GetMouseY();
	const int centerX = Input::GetWindowCenterX();
	const int centerY = Input::GetWindowCenterY();
	const float deltaX = float(centerX - mouseX);
	const float deltaY = float(centerY - mouseY);

	if (mouseX != centerX)
	{
		m_fYaw += deltaX * m_fSensX;
		m_fYaw = NormalizeYaw(m_fYaw);

		bUpdatePosition = true;
	}

	if (mouseY != centerY)
	{
		m_fPitch += deltaY * m_fSensY;
		m_fPitch = NormalizePitch(m_fPitch);

		bUpdatePosition = true;
	}

	SetCursorPos(centerX, centerY);


	const bool bKeyDownW = Input::IsKeyDown('W');
	const bool bKeyDownS = Input::IsKeyDown('S');
	const bool bKeyDownA = Input::IsKeyDown('A');
	const bool bKeyDownD = Input::IsKeyDown('D');
	const bool bKeyDownE = Input::IsKeyDown('E');
	const bool bKeyDownQ = Input::IsKeyDown('Q');

	if (bKeyDownW || bKeyDownS || bKeyDownA || bKeyDownD || bKeyDownE || bKeyDownQ)
	{
		D3DXVECTOR3 forward = GetForwardVector();
		D3DXVECTOR3 right = GetRightVector();
		D3DXVECTOR3 up = D3DXVECTOR3(0.0f, 0.0f, 1.0f);

		D3DXVECTOR3 dir = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		float fSpeed = m_fSpeed * kMetersToWorldUnits;

		if (bKeyDownW)
			dir += forward;
		if (bKeyDownS)
			dir -= forward;
		if (bKeyDownD)
			dir += right;
		if (bKeyDownA)
			dir -= right;
		if (bKeyDownE)
			dir += up;
		if (bKeyDownQ)
			dir -= up;

		if (m_bShift)
			fSpeed *= 2.0f;

		D3DXVec3Normalize(&dir, &dir);
		m_vEyePosition += dir * fSpeed * deltaTime;

		bUpdatePosition = true;
	}

	if (bUpdatePosition)
		m_vTargetPosition = m_vEyePosition + GetForwardVector() * 100.0f;
}

void CCamera::OnMouseButtonDown(EMouseButton button)
{
	if (!m_bActive)
		return;

	if (button == EMouseButton::Right)
	{
		m_bRMB = true;

		Input::CenterMouse();
	}
}

void CCamera::OnMouseButtonUp(EMouseButton button)
{
	if (!m_bActive)
		return;

	if (button == EMouseButton::Right)
		m_bRMB = false;
}

void CCamera::OnMouseWheel(int delta)
{
	if (!m_bActive)
		return;
}

void CCamera::OnKeyboardDown(WPARAM getKey)
{
	if (!m_bActive)
		return;

	if (getKey == 16)
		m_bShift = true;
}

void CCamera::OnKeyboardUp(WPARAM getKey)
{
	if (!m_bActive)
		return;

	if (getKey == 16)
		m_bShift = false;
}