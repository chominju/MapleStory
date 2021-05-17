#include "stdafx.h"
#include "Inventory_Button.h"
#include "Key_Manager.h"
#include "Bitmap_Manager.h"

bool CInventory_Button::m_isEquipmentClick=false;
bool CInventory_Button::m_isConsumeClick=true;
bool CInventory_Button::m_isEtcClick=false;
CInventory_Button::CInventory_Button()
{
}

CInventory_Button::~CInventory_Button()
{
}

int CInventory_Button::Ready_GameObject()
{
	m_info.sizeX = 29;
	m_info.sizeY = 19;
	return 0;
}

int CInventory_Button::Update_GameObject()
{
	return 0;
}

void CInventory_Button::Late_Update_GameObject()
{
	POINT pt = {};
	GetCursorPos(&pt);
	ScreenToClient(g_hwnd, &pt);

	if (PtInRect(&m_rect, pt))
	{
		if (CKey_Manager::Get_Instance()->Key_Up(KEY_LBUTTON))
		{
			if (!lstrcmp(m_BitMapKey.c_str(), L"Inventory_Equipment_Button"))
			{
				m_isEquipmentClick = true;
				m_isConsumeClick = false;
				m_isEtcClick = false;
			}
			else if (m_BitMapKey == L"Inventory_Consume_Button")
			{
				m_isEquipmentClick = false;
				m_isConsumeClick = true;
				m_isEtcClick = false;
			}
			else if (m_BitMapKey == L"Inventory_Etc_Button")
			{
				m_isEquipmentClick = false;
				m_isConsumeClick = false;
				m_isEtcClick = true;
			}
		}

	}
	
}

void CInventory_Button::Render_GameObject(HDC hDC)
{
	UpdateRect_GameObject();
	HDC hMemDC = CBitmap_Manager::Get_Instance()->Get_memDC(m_BitMapKey.c_str());
	if (nullptr == hMemDC)
		return;

	if (m_BitMapKey == L"Inventory_Equipment_Button")
	{
		GdiTransparentBlt(hDC,
			m_rect.left, m_rect.top,
			m_info.sizeX, m_info.sizeY,
			hMemDC,
			m_isEquipmentClick * m_info.sizeX, 0,
			m_info.sizeX, m_info.sizeY, RGB(255, 0, 255));
	}

	if (m_BitMapKey == L"Inventory_Consume_Button")
	{
		GdiTransparentBlt(hDC,
			m_rect.left, m_rect.top,
			m_info.sizeX, m_info.sizeY,
			hMemDC,
			m_isConsumeClick * m_info.sizeX, 0,
			m_info.sizeX, m_info.sizeY, RGB(255, 0, 255));
	}

	if (m_BitMapKey == L"Inventory_Etc_Button")
	{
		GdiTransparentBlt(hDC,
			m_rect.left, m_rect.top,
			m_info.sizeX, m_info.sizeY,
			hMemDC,
			m_isEtcClick * m_info.sizeX, 0,
			m_info.sizeX, m_info.sizeY, RGB(255, 0, 255));
	}
}

void CInventory_Button::Release_GameObject()
{
}

void CInventory_Button::UpdateRect_GameObject()
{
	m_rect.left = static_cast<LONG>(m_info.x - (m_info.sizeX / 2));
	m_rect.top = static_cast<LONG>(m_info.y - (m_info.sizeY / 2));
	m_rect.right = static_cast<LONG>(m_info.x + (m_info.sizeX / 2));
	m_rect.bottom = static_cast<LONG>(m_info.y + (m_info.sizeY / 2));
}

CGameObject * CInventory_Button::Create()
{
	CGameObject*instance = new CInventory_Button;
	if (0 > instance->Ready_GameObject())
	{
		Safe_Delete(instance);
		return nullptr;
	}
	return instance;
}
