#pragma once

#include <vector>
#include <string>

#include "Texture2D.h"
#include "Font.h"
#include "Utils.h"

enum class EAnchor : uint32
{
	TopLeft,
	Top,
	TopRight,
	Left,
	Center,
	Right,
	BottomLeft,
	Bottom,
	BottomRight
};

enum class ETextAlignment : uint32
{
	Left,
	Center,
	Right
};

class ICtrl
{
public:
	ICtrl();

	int32 m_iOffsetX, m_iOffsetY;
	uint32 m_iHeight, m_iWidth;

	Texture2D* m_pTexture;
	float m_fAngle;
	uint32 m_iColor;
	float m_fDepth;
	uint32 m_iId;
	bool m_bIsShow;
	int32 m_iZOrder;

	std::string m_Text;
	bool m_bWrap;
	ETextAlignment m_TextAlignment;
	CFont* m_pFont;

	EAnchor m_Anchor;
	ICtrl* m_pParentCtrl;
	int32 m_iRelativeX, m_iRelativeY;

	void UpdateAnchor();
	void SetTexture(Texture2D* texture);
	void SetFont(CFont* pFont);
	int32 GetX();
	int32 GetY();

	void Render(ID3DXSprite* pSprite);
	void RenderText(ID3DXSprite* pSprite);
};


class CGUI
{
public:
	CGUI(IDirect3DDevice9* pDevice);
	~CGUI();

	int32 GetCtrlFromPoint(int32 x, int32 y);
	int32 GetCtrlFromMousePoint();
	ICtrl* GetCtrlFromID(uint32 id);

	void NewCtrl(uint32 id, int32 offsetX, int32 offsetY, uint32 width, uint32 height);
	void DeleteCtrl(uint32 id);

	void SetCtrlTexture(uint32 id, const std::string& filename);
	void SetCtrlFont(uint32 id, const std::string& name, uint32 size);
	void SetCtrlText(uint32 id, const std::string& text, bool bWrap);
	void SetCtrlTextAlignment(uint32 id, ETextAlignment alignment);
	void SetCtrlColor(uint32 id, uint32 argb);
	void SetCtrlPosition(uint32 id, int32 offsetX, int32 offsetY);
	void SetCtrlAnchor(uint32 id, int32 parentId, EAnchor anchor);
	void SetCtrlAngle(uint32 id, float val);
	void SetCtrlDepth(uint32 id, float fDepth);
	void SetCtrlZOrder(uint32 id, int32 iZOrder);
	void SetCtrlSize(uint32 id, int32 width, int32 height);

	uint32 GetCtrlHeight(uint32 id);
	uint32 GetCtrlWidth(uint32 id);
	bool CtrlIsText(uint32 id);
	void ShowCtrl(uint32 id, bool isShow);
	
	void Render();
	void Release();
	void OnLostDevice();
	void OnResetDevice();

private:
	void Sort();

	std::vector<ICtrl*> m_vecCtrls;

	IDirect3DDevice9* m_pDevice;
	ID3DXSprite*      m_pSprite;
};

extern CGUI* CustomUI;