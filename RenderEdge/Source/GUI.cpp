#include "GUI.h"

#include <windows.h>
#include <algorithm>

#include "Input.h"
#include "TextureManager.h"
#include "FontManager.h"
#include "Utils.h"
#include "Engine.h"


ICtrl::ICtrl()
{
	m_iOffsetX = 0;
	m_iOffsetY = 0;
	m_iHeight = 0;
	m_iWidth = 0;

	m_fAngle = 0;
	m_iColor = 0xFFFFFFFF;
	m_fDepth = 1.0f;
	m_iId = 0;
	m_bIsShow = true;
	m_pTexture = nullptr;
	m_iZOrder = 0;

	m_Text = "";
	m_bWrap = false;
	m_TextAlignment = TextAlignment::Left;
	m_pFont = nullptr;

	m_pParentCtrl = nullptr;
	m_Anchor = Anchor::TopLeft;
	m_iRelativeX = 0;
	m_iRelativeY = 0;
}

void ICtrl::UpdateAnchor()
{
	int32 offsetX = 0;
	int32 offsetY = 0;
	uint32 relativeWidth = 0;
	uint32 relativeHeight = 0;

	if (m_pParentCtrl != nullptr)
	{
		offsetX = m_pParentCtrl->GetX();
		offsetY = m_pParentCtrl->GetY();
		relativeWidth = m_pParentCtrl->m_iWidth;
		relativeHeight = m_pParentCtrl->m_iHeight;
	}
	else
	{
		offsetX = 0;
		offsetY = 0;
		relativeWidth = GetWindowWidth();
		relativeHeight = GetWindowHeight();
	}

	switch (m_Anchor)
	{
	case Anchor::TopLeft:
		m_iRelativeX = offsetX;
		m_iRelativeY = offsetY;
		break;
	case Anchor::Top:
		m_iRelativeX = offsetX + relativeWidth / 2;
		m_iRelativeY = offsetY;
		break;
	case Anchor::TopRight:
		m_iRelativeX = offsetX + relativeWidth;
		m_iRelativeY = offsetY;
		break;
	case Anchor::Left:
		m_iRelativeX = offsetX;
		m_iRelativeY = offsetY + relativeHeight / 2;
		break;
	case Anchor::Center:
		m_iRelativeX = offsetX + relativeWidth / 2;
		m_iRelativeY = offsetY + relativeHeight / 2;
		break;
	case Anchor::Right:
		m_iRelativeX = offsetX + relativeWidth;
		m_iRelativeY = offsetY + relativeHeight / 2;
		break;
	case Anchor::BottomLeft:
		m_iRelativeX = offsetX;
		m_iRelativeY = offsetY + relativeHeight;
		break;
	case Anchor::Bottom:
		m_iRelativeX = offsetX + relativeWidth / 2;
		m_iRelativeY = offsetY + relativeHeight;
		break;
	case Anchor::BottomRight:
		m_iRelativeX = offsetX + relativeWidth;
		m_iRelativeY = offsetY + relativeHeight;
		break;
	}
}

void ICtrl::SetTexture(Texture* pTexture)
{
	m_pTexture = pTexture;
}

void ICtrl::SetFont(Font* pFont)
{
	m_pFont = pFont;
}

int32 ICtrl::GetX()
{
	return m_iOffsetX + m_iRelativeX;
}

int32 ICtrl::GetY()
{
	return m_iOffsetY + m_iRelativeY;
}

void ICtrl::Render(ID3DXSprite* pSprite)
{
	if (!m_Text.empty())
		return;

	if (m_bIsShow)
	{
		//if (m_pTexture == nullptr || m_pTexture->texture == nullptr)
		//	m_pTexture = MainTextureManager->GetDefaultTexture();

		UpdateAnchor();

		D3DXMATRIX matAll;
		D3DXVECTOR2 trans = D3DXVECTOR2((float)GetX(), (float)GetY());
		D3DXVECTOR2 scaling((float)m_iWidth / (float)m_pTexture->width, (float)m_iHeight / (float)m_pTexture->height);
		D3DXVECTOR2 spriteCentre = D3DXVECTOR2((float)m_iWidth / 2, (float)m_iHeight / 2);
		D3DXMatrixTransformation2D(&matAll, nullptr, 0.0f, &scaling, &spriteCentre, m_fAngle, &trans);
		pSprite->SetTransform(&matAll);

		pSprite->Draw(m_pTexture->texture, nullptr, nullptr, nullptr, m_iColor);
	}
}

void ICtrl::RenderText(ID3DXSprite* pSprite)
{
	if (m_Text.empty())
		return;

	if (m_bIsShow)
	{
		UpdateAnchor();

		if (m_pFont == nullptr) return;
		BaseFont* curFont = m_pFont->GetNormal();
		if (curFont == nullptr) return;

		uint32 lineWidth = 0;
		uint32 totalHeight = curFont->pMetrics.height; // + curFont->pMetrics.externalleading;

		int32 drawX = GetX();
		int32 drawY = GetY();

		float rotCenterW = (float)m_iWidth / 2;
		float rotCenterH = (float)m_iHeight / 2;

		uint32 curColor = m_iColor;
		bool colorChanged = false;
		bool fontBold = false;
		bool fontItalic = false;

		for (uint32 i = 0; i < m_Text.size(); i++)
		{
			const auto& curCharInfo = curFont->pInfo[(uint8)m_Text[i] - curFont->pFirst];

			//================================================

			if (m_Text[i] == '|')
			{
				if (m_Text[i + 1] == 'n' || m_Text[i + 1] == 'N')
				{
					lineWidth = 0;
					drawX = GetX();
					drawY += curFont->pMetrics.height + curFont->pMetrics.externalleading;

					//rotCenterH -= curFont->pMetrics.height + curFont->pMetrics.externalleading;
					totalHeight += curFont->pMetrics.height + curFont->pMetrics.externalleading;

					i++;
					continue;
				}
				else if (m_Text[i + 1] == 'c' || m_Text[i + 1] == 'C')
				{
					std::string hexColorStr = m_Text.substr(i + 2, 8);
					if (utils::IsHexColor(hexColorStr))
					{
						curColor = std::stoul(hexColorStr, nullptr, 16);
						colorChanged = true;

						i += 9;
						continue;
					}
				}
				else if (m_Text[i + 1] == 'b' || m_Text[i + 1] == 'B')
				{
					if (!fontBold)
					{
						curFont = m_pFont->GetBold();
						fontBold = true;
					}
					else if (fontItalic)
						curFont = m_pFont->GetBoldItalic();

					i++;
					continue;
				}
				else if (m_Text[i + 1] == 'i' || m_Text[i + 1] == 'I')
				{
					if (!fontItalic)
					{
						curFont = m_pFont->GetItalic();
						fontItalic = true;
					}
					else if (fontBold)
						curFont = m_pFont->GetBoldItalic();

					i++;
					continue;
				}
				else if (m_Text[i + 1] == 'r' || m_Text[i + 1] == 'R')
				{
					if (colorChanged)
					{
						curColor = m_iColor;
						colorChanged = false;
					}

					if (fontItalic || fontBold)
					{
						curFont = m_pFont->GetNormal();
						fontBold = false;
						fontItalic = false;
					}

					i++;
					continue;
				}
			}
			
			if (m_bWrap)
			{
				if (m_Text[i] == ' ')
				{
					uint32 wordWidth = curCharInfo.abc.a + curCharInfo.abc.b + curCharInfo.abc.c;

					uint32 j = i + 1;
					while (m_Text[j] != '\0' && m_Text[j] != ' ')
					{
						const auto& wordCharInfo = curFont->pInfo[(uint8)m_Text[j] - curFont->pFirst];

						if (m_Text[j] == '|')
						{
							if (m_Text[j + 1] == 'c' || m_Text[j + 1] == 'C')
							{
								std::string hexColorStr = m_Text.substr(j + 2, 8);
								if (utils::IsHexColor(hexColorStr))
								{
									j += 9;
									continue;
								}
							}
							else if (m_Text[j + 1] == 'b' || m_Text[j + 1] == 'B'
								|| m_Text[j + 1] == 'i' || m_Text[j + 1] == 'I'
								|| m_Text[j + 1] == 'r' || m_Text[j + 1] == 'R'
								|| m_Text[j + 1] == 'n' || m_Text[j + 1] == 'N')
							{
								j++;
								continue;
							}
						}

						wordWidth += wordCharInfo.abc.a + wordCharInfo.abc.b + wordCharInfo.abc.c;
						j++;
					}

					if (lineWidth + wordWidth > m_iWidth)
					{
						if (m_TextAlignment == TextAlignment::Left)
							drawX = GetX();
						else if (m_TextAlignment == TextAlignment::Center)
							drawX = GetX() + m_iWidth / 2 - lineWidth / 2;
						else if (m_TextAlignment == TextAlignment::Right)
							drawX = GetX() + m_iWidth - lineWidth;

						drawY += curFont->pMetrics.height + curFont->pMetrics.externalleading;
						//rotCenterH -= curFont->pMetrics.height + curFont->pMetrics.externalleading;
						totalHeight += curFont->pMetrics.height + curFont->pMetrics.externalleading;

						lineWidth = 0;

						continue;
					}
				}
			}

			lineWidth += curCharInfo.abc.a + curCharInfo.abc.b + curCharInfo.abc.c;

			if (m_iHeight != totalHeight)
				m_iHeight = totalHeight;

			
			drawX += curCharInfo.abc.a;

			//================================================

			D3DXMATRIX mat;
			D3DXVECTOR2 spriteCentre = D3DXVECTOR2(rotCenterW, rotCenterH);
			D3DXVECTOR2 trans = D3DXVECTOR2((float)drawX, (float)drawY);
			D3DXMatrixTransformation2D(&mat, nullptr, 0.0f, nullptr, &spriteCentre, m_fAngle, &trans);
			pSprite->SetTransform(&mat);

			RECT rectChar = { curCharInfo.x, curCharInfo.y, curCharInfo.x + curCharInfo.image_width + curFont->pMargin, curCharInfo.y + curFont->pMetrics.height };
			pSprite->Draw(curFont->pTexture->texture, &rectChar, 0, 0, curColor);

			//================================================

			drawX += curCharInfo.abc.b + curCharInfo.abc.c;
			rotCenterW -= curCharInfo.abc.a + curCharInfo.abc.b + curCharInfo.abc.c;
		}
	}
}



GUI* MainGUI;

GUI::GUI(IDirect3DDevice9* pDevice) : m_pDevice(pDevice)
{
	if (D3DXCreateSprite(m_pDevice, &m_pSprite) != S_OK)
		Message("D3DXCreateSprite failed!", "GUI::GUI");
}

GUI::~GUI()
{
	Release();
}

uint32 GUI::GetHeight(uint32 id)
{
	ICtrl* pCtrl = GetCtrlFromID(id);

	if (pCtrl == nullptr)
		return 0;

	return pCtrl->m_iHeight;
}

uint32 GUI::GetWidth(uint32 id)
{
	ICtrl* pCtrl = GetCtrlFromID(id);

	if (pCtrl == nullptr)
		return 0;

	return pCtrl->m_iWidth;
}

void GUI::SetSize(uint32 id, int32 width, int32 height)
{
	ICtrl* pCtrl = GetCtrlFromID(id);

	if (pCtrl == nullptr)
		return;

	if (width >= 0)
		pCtrl->m_iWidth = width;
	if (height >= 0)
		pCtrl->m_iHeight = height;
}


bool GUI::IsText(uint32 id)
{
	ICtrl* pCtrl = GetCtrlFromID(id);

	if (pCtrl == nullptr)
		return false;

	return (pCtrl->m_Text.empty() == false);
}

void GUI::Show(uint32 id, bool isShow)
{
	ICtrl* pCtrl = GetCtrlFromID(id);

	if (pCtrl == nullptr)
		return;

	pCtrl->m_bIsShow = isShow;
}

void GUI::SetDepth(uint32 id, float fDepth)
{
	ICtrl* pCtrl = GetCtrlFromID(id);

	if (pCtrl == nullptr)
		return;

	pCtrl->m_fDepth = fDepth;
}

void GUI::SetZOrder(uint32 id, int32 iZOrder)
{
	ICtrl* pCtrl = GetCtrlFromID(id);

	if (pCtrl == nullptr)
		return;

	pCtrl->m_iZOrder = iZOrder;
	Sort();
}

void GUI::SetAngle(uint32 id, float val)
{
	ICtrl* pCtrl = GetCtrlFromID(id);

	if (pCtrl == nullptr)
		return;
	
	pCtrl->m_fAngle = val;
}

void GUI::SetTexture(uint32 id, const std::string& filename)
{
	ICtrl* pCtrl = GetCtrlFromID(id);

	if (pCtrl == nullptr)
		return;

	if (!pCtrl->m_Text.empty())
		pCtrl->m_Text.clear();

	if (MainTextureManager->GetTexture(filename) == nullptr)
	{
		if (MainTextureManager->CreateTextureFromMPQ(nullptr, filename))
			pCtrl->SetTexture(MainTextureManager->GetTexture(filename));
		else
			pCtrl->SetTexture(MainTextureManager->GetDefaultTexture());
	}
	else
		pCtrl->SetTexture(MainTextureManager->GetTexture(filename));
}

void GUI::SetFont(uint32 id, const std::string& name, uint32 size)
{
	ICtrl* pCtrl = GetCtrlFromID(id);

	if (pCtrl == nullptr)
		return;

	if (MainFontManager->GetFont(name, size) == nullptr)
	{
		//if (MainFontManager->CreateFontFromMPQ(nullptr, name, size))
		if (MainFontManager->CreateFontFromFile(name, size))
			pCtrl->SetFont(MainFontManager->GetFont(name, size));
		else
			pCtrl->SetFont(MainFontManager->GetDefaultFont());
	}
	else
		pCtrl->SetFont(MainFontManager->GetFont(name, size));
}

void GUI::SetAnchor(uint32 id, int32 parentId, Anchor anchor)
{
	ICtrl* pCtrl = GetCtrlFromID(id);

	if (pCtrl == nullptr)
		return;

	pCtrl->m_Anchor = anchor;

	if (parentId >= 0)
		pCtrl->m_pParentCtrl = GetCtrlFromID(parentId);
	else
		pCtrl->m_pParentCtrl = nullptr;
}

void GUI::SetTextAlignment(uint32 id, TextAlignment alignment)
{
	ICtrl* pCtrl = GetCtrlFromID(id);

	if (pCtrl == nullptr)
		return;

	pCtrl->m_TextAlignment = alignment;
}

void GUI::SetText(uint32 id, const std::string& text, bool bWrap)
{
	if (text.empty())
		return;

	ICtrl* pCtrl = GetCtrlFromID(id);

	if (pCtrl == nullptr)
		return;

	pCtrl->m_Text = text;
	pCtrl->m_bWrap = bWrap;

	if (pCtrl->m_pFont == nullptr) return;
	BaseFont* curFont = pCtrl->m_pFont->GetNormal();
	if (curFont == nullptr) return;

	int32 curWidth = 0;

	bool fontBold = false;
	bool fontItalic = false;

	uint32 lineWidth = 0;
	uint32 maxLineWidth = 0;
	uint32 totalHeight = curFont->pMetrics.height; // + curFont->pMetrics.externalleading;

	for (uint32 i = 0; i < pCtrl->m_Text.size(); i++)
	{
		const auto& curCharInfo = curFont->pInfo[(uint8)pCtrl->m_Text[i] - curFont->pFirst];

		//================================================

		if (pCtrl->m_Text[i] == '|')
		{
			if (pCtrl->m_Text[i + 1] == 'n' || pCtrl->m_Text[i + 1] == 'N')
			{
				lineWidth = 0;
				curWidth = 0;
				totalHeight += curFont->pMetrics.height + curFont->pMetrics.externalleading;

				i++;
				continue;
			}
			else if (pCtrl->m_Text[i + 1] == 'c' || pCtrl->m_Text[i + 1] == 'C')
			{
				std::string hexColorStr = pCtrl->m_Text.substr(i + 2, 8);
				if (utils::IsHexColor(hexColorStr))
				{
					i += 9;
					continue;
				}
			}
			else if (pCtrl->m_Text[i + 1] == 'b' || pCtrl->m_Text[i + 1] == 'B')
			{
				if (!fontBold)
				{
					curFont = pCtrl->m_pFont->GetBold();
					fontBold = true;
				}
				else if (fontItalic)
					curFont = pCtrl->m_pFont->GetBoldItalic();

				i++;
				continue;
			}
			else if (pCtrl->m_Text[i + 1] == 'i' || pCtrl->m_Text[i + 1] == 'I')
			{
				if (!fontItalic)
				{
					curFont = pCtrl->m_pFont->GetItalic();
					fontItalic = true;
				}
				else if (fontBold)
					curFont = pCtrl->m_pFont->GetBoldItalic();

				i++;
				continue;
			}
			else if (pCtrl->m_Text[i + 1] == 'r' || pCtrl->m_Text[i + 1] == 'R')
			{
				if (fontItalic || fontBold)
				{
					curFont = pCtrl->m_pFont->GetNormal();
					fontBold = false;
					fontItalic = false;
				}

				i++;
				continue;
			}
		}
		
		if (pCtrl->m_bWrap)
		{
			if (pCtrl->m_Text[i] == ' ')
			{
				uint32 wordWidth = curCharInfo.abc.a + curCharInfo.abc.b + curCharInfo.abc.c;

				uint32 j = i + 1;
				while (pCtrl->m_Text[j] != '\0' && pCtrl->m_Text[j] != ' ')
				{
					const auto& wordCharInfo = curFont->pInfo[(uint8)pCtrl->m_Text[j] - curFont->pFirst];

					if (pCtrl->m_Text[j] == '|')
					{
						if (pCtrl->m_Text[j + 1] == 'c' || pCtrl->m_Text[j + 1] == 'C')
						{
							std::string hexColorStr = pCtrl->m_Text.substr(j + 2, 8);
							if (utils::IsHexColor(hexColorStr))
							{
								j += 9;
								continue;
							}
						}
						else if (pCtrl->m_Text[j + 1] == 'b' || pCtrl->m_Text[j + 1] == 'B'
							|| pCtrl->m_Text[j + 1] == 'i' || pCtrl->m_Text[j + 1] == 'I'
							|| pCtrl->m_Text[j + 1] == 'r' || pCtrl->m_Text[j + 1] == 'R'
							|| pCtrl->m_Text[j + 1] == 'n' || pCtrl->m_Text[j + 1] == 'N')
						{
							j++;
							continue;
						}
					}

					wordWidth += wordCharInfo.abc.a + wordCharInfo.abc.b + wordCharInfo.abc.c;
					j++;
				}

				if (curWidth + wordWidth > pCtrl->m_iWidth)
				{
					curWidth = 0;
					totalHeight += curFont->pMetrics.height + curFont->pMetrics.externalleading;

					continue;
				}
			}

			curWidth += curCharInfo.abc.a + curCharInfo.abc.b + curCharInfo.abc.c;
		}
		else
		{
			lineWidth += curCharInfo.abc.a + curCharInfo.abc.b + curCharInfo.abc.c;

			if (lineWidth > maxLineWidth)
				maxLineWidth = lineWidth;

			pCtrl->m_iWidth = maxLineWidth;
		}
	}

	pCtrl->m_iHeight = totalHeight;
}

void GUI::SetColor(uint32 id, uint32 argb)
{
	ICtrl* pCtrl = GetCtrlFromID(id);

	if (pCtrl == nullptr)
		return;

	pCtrl->m_iColor = argb;
}

void GUI::SetPosition(uint32 id, int32 offsetX, int32 offsetY)
{
	ICtrl* pCtrl = GetCtrlFromID(id);

	if (pCtrl == nullptr)
		return;

	pCtrl->m_iOffsetX = offsetX;
	pCtrl->m_iOffsetY = offsetY;
}

void GUI::Sort()
{
	auto sortCtrlsL =
		[](const auto& first, const auto& second)
		{
			return first->m_iZOrder < second->m_iZOrder;
		};

	std::sort(m_vecCtrls.begin(), m_vecCtrls.end(), sortCtrlsL);
}

void GUI::New(uint32 id, int32 offsetX, int32 offsetY, uint32 width, uint32 height)
{
	ICtrl* pCtrl = new ICtrl;

	pCtrl->m_iOffsetY = offsetY;
	pCtrl->m_iOffsetX = offsetX;
	pCtrl->m_iHeight = height;
	pCtrl->m_iWidth = width;
	pCtrl->m_iId = id;
	pCtrl->m_pFont = MainFontManager->GetDefaultFont();
	pCtrl->m_pTexture = MainTextureManager->GetDefaultTexture();

	m_vecCtrls.push_back(pCtrl);
}


void GUI::Delete(uint32 id)
{
	ICtrl* pCtrl = GetCtrlFromID(id);

	if (pCtrl == nullptr)
		return;

	//delete pCtrl;
	//m_vecCtrls.erase();
}


void GUI::Draw()
{
	if (m_vecCtrls.size() > 0)
	{
		//================================================

		m_pSprite->Begin(D3DXSPRITE_ALPHABLEND);

		for (const auto& pCtrl : m_vecCtrls)
			pCtrl->Render(m_pSprite);

		m_pSprite->End();

		//================================================

		m_pSprite->Begin(D3DXSPRITE_ALPHABLEND);
		m_pDevice->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_DIFFUSE); // Optimize!

		for (const auto& pCtrl : m_vecCtrls)
			pCtrl->RenderText(m_pSprite);

		m_pSprite->End();

		//================================================
	}
}

int32 GUI::GetCtrlFromMousePoint()
{
    return GetCtrlFromPoint(GetMouseXRelative(), GetMouseYRelative());
}

int32 GUI::GetCtrlFromPoint(int32 x, int32 y)
{
	float minDepth = FLT_MAX;
	int32 id = -1;

	for (const auto& pCtrl : m_vecCtrls)
	{
		if ((x >= pCtrl->GetX()) && (x <= pCtrl->GetX() + pCtrl->m_iWidth) && (y >= pCtrl->GetY()) && (y <= pCtrl->GetY() + pCtrl->m_iHeight))
		{
			if ((pCtrl->m_fDepth < minDepth) && pCtrl->m_bIsShow)
			{
				id = pCtrl->m_iId;
				minDepth = pCtrl->m_fDepth;
			}
		}
	}

	return id;
}

ICtrl* GUI::GetCtrlFromID(uint32 id)
{
	for (const auto& pCtrl : m_vecCtrls)
	{
		if (pCtrl->m_iId == id)
		{
			return pCtrl;
			break;
		}
	}

	return nullptr;
}

void GUI::Release()
{
	for (const auto& pCtrl : m_vecCtrls)
		delete pCtrl;

	m_vecCtrls.clear();
}

void GUI::OnLostDevice()
{
	m_pSprite->OnLostDevice();
}

void GUI::OnResetDevice()
{
	m_pSprite->OnResetDevice();
}