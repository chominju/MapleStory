#include "stdafx.h"
#include "Close_Button.h"
#include "Key_Manager.h"
#include "Bitmap_Manager.h"
#include "GameObject_Manager.h"

CClose_Button::CClose_Button()
{
}

CClose_Button::~CClose_Button()
{
}

int CClose_Button::Ready_GameObject()
{
	m_info.sizeX = 60;
	m_info.sizeY = 18;

	UpdateRect_GameObject();
	return 0;
}

int CClose_Button::Update_GameObject()
{
	return 0;
}

void CClose_Button::Late_Update_GameObject()
{
		POINT pt = {};
		GetCursorPos(&pt);
		ScreenToClient(g_hwnd, &pt);

		if (PtInRect(&m_rect, pt))
		{
			if (CKey_Manager::Get_Instance()->Key_Up(KEY_LBUTTON))
			{
				if (m_BitMapKey == L"Close_Ui")
				{
					m_isCloseButton = true;
				}
			}
		}
}

void CClose_Button::Render_GameObject(HDC hDC)
{
	UpdateRect_GameObject();
	m_hdc = CBitmap_Manager::Get_Instance()->Get_memDC(m_BitMapKey.c_str());
	GdiTransparentBlt(hDC,
		m_rect.left, m_rect.top,
		m_info.sizeX, m_info.sizeY,
		m_hdc,
		0, 0,
		m_info.sizeX, m_info.sizeY, RGB(255, 0, 255));
}

void CClose_Button::Release_GameObject()
{
}

void CClose_Button::UpdateRect_GameObject()
{
	m_rect.left = static_cast<LONG>(m_info.x - (m_info.sizeX / 2));
	m_rect.top = static_cast<LONG>(m_info.y - (m_info.sizeY / 2));
	m_rect.right = static_cast<LONG>(m_info.x + (m_info.sizeX / 2));
	m_rect.bottom = static_cast<LONG>(m_info.y + (m_info.sizeY / 2));
}

CGameObject * CClose_Button::Create()
{
	CGameObject*instance = new CClose_Button;
	if (0 > instance->Ready_GameObject())
	{
		Safe_Delete(instance);
		return nullptr;
	}
	return instance;
}
