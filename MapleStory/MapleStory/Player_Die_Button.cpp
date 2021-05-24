#include "stdafx.h"
#include "Player_Die_Button.h"
#include "Key_Manager.h"
#include "Bitmap_Manager.h"
#include "GameObject_Manager.h"
#include "Scene_Manager.h"

Player_Die_Button::Player_Die_Button()
{
}


Player_Die_Button::~Player_Die_Button()
{
}

int Player_Die_Button::Ready_GameObject()
{

//	WINCX / 2 - 10, WINCY / 2 + 19
	m_info.x = 543;
	m_info.y = 417;
	m_info.sizeX = 82;
	m_info.sizeY = 29;

	UpdateRect_GameObject();

	return 0;
}

int Player_Die_Button::Update_GameObject()
{
	return 0;
}

void Player_Die_Button::Late_Update_GameObject()
{
	if (CGameObject_Manager::Get_Instance()->GetPlayer()->Get_Hp() <= 0)
	{
		POINT pt = {};
		GetCursorPos(&pt);
		ScreenToClient(g_hwnd, &pt);

		if (PtInRect(&m_rect, pt))
		{
			if (CKey_Manager::Get_Instance()->Key_Up(KEY_LBUTTON))
			{
				if (m_BitMapKey == L"Player_Die_Message_Button")
				{
					CGameObject_Manager::Get_Instance()->GetPlayer()->Set_Change_Hp(CGameObject_Manager::Get_Instance()->GetPlayer()->Get_Data()->maxHp);
					//CGameObject_Manager::Get_Instance()->GetPlayer()->Set_IsDead(false);
					CScene_Manager::Get_Instance()->Change_Scene_Manager(Scene_ID::SCENE_Kerning_City);
				}
			}
		}
	}
}

void Player_Die_Button::Render_GameObject(HDC hDC)
{
	m_hdc = CBitmap_Manager::Get_Instance()->Get_memDC(m_BitMapKey.c_str());
		GdiTransparentBlt(hDC,
			m_rect.left,m_rect.top,
			m_info.sizeX, m_info.sizeY +5,
			m_hdc,
			0, 0,
			m_info.sizeX, m_info.sizeY, RGB(255, 0, 255));
}

void Player_Die_Button::Release_GameObject()
{
}

void Player_Die_Button::UpdateRect_GameObject()
{
	m_rect.left = static_cast<LONG>(m_info.x - (m_info.sizeX / 2));
	m_rect.top = static_cast<LONG>(m_info.y - (m_info.sizeY / 2));
	m_rect.right = static_cast<LONG>(m_info.x + (m_info.sizeX / 2));
	m_rect.bottom = static_cast<LONG>(m_info.y + (m_info.sizeY / 2));
}

CGameObject * Player_Die_Button::Create()
{
	CGameObject*instance = new Player_Die_Button;
	if (0 > instance->Ready_GameObject())
	{
		Safe_Delete(instance);
		return nullptr;
	}
	return instance;
}
