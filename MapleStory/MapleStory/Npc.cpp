#include "stdafx.h"
#include "Npc.h"
#include "GameObject_Manager.h"
#include "Scroll_Manager.h"
#include "Bitmap_Manager.h"
#include "Scroll_Manager.h"
#include "Key_Manager.h"
#include "Shop_Ui.h"

CGameObject * CNpc::m_instance=nullptr;

CNpc::CNpc()
{
}

CNpc::~CNpc()
{
	m_instance = nullptr;
}

int CNpc::Ready_GameObject()
{
	m_hdc = CBitmap_Manager::Get_Instance()->Get_memDC(L"Npc_store");
	m_info.x = 500;
	m_info.y = 530;
	m_info.sizeX = 50;
	m_info.sizeY = 69;
	return 0;
}

int CNpc::Update_GameObject()
{
	POINT pt = {};
	GetCursorPos(&pt);
	ScreenToClient(g_hwnd, &pt);

	int scrollX = CScroll_Manager::Get_ScrollX();
	int scrollY = CScroll_Manager::Get_ScrollY();

	RECT temp = m_rect;
	temp.left += scrollX;
	temp.right += scrollX;
	temp.top += scrollY;
	temp.bottom += scrollY;
	if (PtInRect(&temp, pt))
	{
		if (CKey_Manager::Get_Instance()->Key_Up(KEY_LBUTTON))
		{
			m_shopUi = CShop_Ui::Create(this);
			
			m_isNpcClick = true;
		}
	}

	return 0;
}

void CNpc::Late_Update_GameObject()
{
	if (m_isNpcClick)
		m_shopUi->Update_GameObject();
}

void CNpc::Render_GameObject(HDC hDC)
{
	UpdateRect_GameObject();

	int scrollX = CScroll_Manager::Get_ScrollX();
	int scrollY = CScroll_Manager::Get_ScrollY();


	GdiTransparentBlt(hDC, // 그림을 복사하고자 하는 대상. 
		m_rect.left + scrollX,//위치 x,y
		m_rect.top + scrollY,
		m_info.sizeX,// 크기 xy
		m_info.sizeY,
		m_hdc,// 복사 할 대상
		0,0,// 그림의 시작 위치 x,y
		m_info.sizeX,// 그리고자 하는 영역의 크기 x,y
		m_info.sizeY,
		RGB(255, 0, 255));

	if (m_isNpcClick)
		m_shopUi->Render_GameObject(hDC);
}

void CNpc::Release_GameObject()
{
}

void CNpc::UpdateRect_GameObject()
{
	m_rect.left = static_cast<LONG>(m_info.x - (m_info.sizeX / 2));
	m_rect.top = static_cast<LONG>(m_info.y - (m_info.sizeY / 2));
	m_rect.right = static_cast<LONG>(m_info.x + (m_info.sizeX / 2));
	m_rect.bottom = static_cast<LONG>(m_info.y + (m_info.sizeY / 2));
}

CGameObject * CNpc::Create()
{
	if (nullptr == m_instance)
	{
		m_instance = new CNpc;
		if (nullptr == m_instance)
		{
			Safe_Delete(m_instance);
			m_instance = nullptr;
			return m_instance;
		}

		m_instance->Ready_GameObject();
		CGameObject_Manager::Get_Instance()->Add_GameObject_Manager(Object_ID::NPC, m_instance);
	}

	return m_instance;
}
