#pragma once

#include <vector>
#include <string>

#include "Texture.h"
#include "Font.h"
#include "int_t.h"

enum class Anchor : uint32
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

enum class TextAlignment : uint32
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

	Texture* m_pTexture;
	float m_fAngle;
	uint32 m_iColor;
	float m_fDepth;
	uint32 m_iId;
	bool m_bIsShow;
	int32 m_iZOrder;

	std::string m_Text;
	bool m_bWrap;
	TextAlignment m_TextAlignment;
	Font* m_pFont;

	Anchor m_Anchor;
	ICtrl* m_pParentCtrl;
	int32 m_iRelativeX, m_iRelativeY;

	void UpdateAnchor();
	void SetTexture(Texture* texture);
	void SetFont(Font* pFont);
	int32 GetX();
	int32 GetY();

	void Render(ID3DXSprite* pSprite);
	void RenderText(ID3DXSprite* pSprite);
};


class GUI
{
public:
	GUI(IDirect3DDevice9* pDevice);
	~GUI();

	int32 GetCtrlFromPoint(int32 x, int32 y);
	int32 GetCtrlFromMousePoint();
	ICtrl* GetCtrlFromID(uint32 id);

	void New(uint32 id, int32 offsetX, int32 offsetY, uint32 width, uint32 height);

	void SetTexture(uint32 id, const std::string& filename);
	void SetFont(uint32 id, const std::string& name, uint32 size);
	void SetText(uint32 id, const std::string& text, bool bWrap);
	void SetTextAlignment(uint32 id, TextAlignment alignment);
	void SetColor(uint32 id, uint32 argb);
	void SetPosition(uint32 id, int32 offsetX, int32 offsetY);
	void SetAnchor(uint32 id, int32 parentId, Anchor anchor);
	void SetAngle(uint32 id, float val);
	void SetDepth(uint32 id, float fDepth);
	void SetZOrder(uint32 id, int32 iZOrder);
	void SetSize(uint32 id, int32 width, int32 height);

	uint32 GetHeight(uint32 id);
	uint32 GetWidth(uint32 id);
	bool IsText(uint32 id);

	void Show(uint32 id, bool isShow);
	void Delete(uint32 id);
	void Draw();

	void Release();
	void OnLostDevice();
	void OnResetDevice();

private:
	void Sort();

	std::vector<ICtrl*> m_vecCtrls;

	IDirect3DDevice9* m_pDevice;
	ID3DXSprite*      m_pSprite;
};

extern GUI* MainGUI;