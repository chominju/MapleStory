#include "stdafx.h"
#include "Meso.h"
#include "Bitmap_Manager.h"
#include "GameObject_Manager.h"
#include "Line_Manager.h"
#include "Monster.h"
#include "Scroll_Manager.h"

CMeso::CMeso()
{
}

CMeso::~CMeso()
{
}

int CMeso::Ready_GameObject()
{
	m_hdc = CBitmap_Manager::Get_Instance()->Get_memDC(L"Meso");

	m_info.sizeX = 25;
	m_info.sizeY = 24;

	m_itemInfo.id = Object_ID::DROP_ITEM;
	m_itemInfo.type = Item_type::MESO;
	m_itemInfo.buyMoney = 0;
	m_itemInfo.sellMoney = 0;
	m_itemInfo.quantity = 1;
	strcpy_s(m_itemInfo.itemName, "�޼�");

	m_animFrame.frame_animation = 0;
	m_animFrame.frame_start = 0;
	m_animFrame.frame_end = 4;
	m_animFrame.frame_speed = 100;
	m_animFrame.frame_time = GetTickCount();
	m_speed = 1;

	UpdateRect_GameObject();

	return S_OK;
}

void CMeso::Late_Update_GameObject()
{
	float fY = 0.f;
	bool bCollLine = CLine_Manager::Get_Instance()->Collision_Line_Manager(this, &fY);
	if (bCollLine)
	{
		if (abs(m_info.y - (fY - m_info.sizeY / 2)) >= 5)
			m_info.y += m_speed;
		else
			m_info.y = fY - m_info.sizeY / 2;
	}
}

void CMeso::Render_GameObject(HDC hDC)
{
	UpdateRect_GameObject();
	int scrollX = CScroll_Manager::Get_ScrollX();
	int scrollY = CScroll_Manager::Get_ScrollY();
	GdiTransparentBlt(hDC, // �׸��� �����ϰ��� �ϴ� ���. 
		m_rect.left + scrollX,//��ġ x,y
		m_rect.top + scrollY,
		m_info.sizeX,// ũ�� xy
		m_info.sizeY,
		m_hdc,// ���� �� ���
		m_animFrame.frame_start * m_info.sizeX, m_animFrame.frame_animation * m_info.sizeY,// �׸��� ���� ��ġ x,y
		m_info.sizeX,// �׸����� �ϴ� ������ ũ�� x,y
		m_info.sizeY,
		RGB(255, 0, 255));
}


void CMeso::Release_GameObject()
{
}

CGameObject * CMeso::Create(float posX, float posY , int money)
{
	CGameObject * instance = new CMeso;
	if (0 > instance->Ready_GameObject())
	{
		Safe_Delete(instance);
		instance = nullptr;
	}
	instance->Set_Pos(posX, posY);
	dynamic_cast<CMeso*>(instance)->Set_Money(money);
	CGameObject_Manager::Get_Instance()->Add_GameObject_Manager(Object_ID::DROP_ITEM, instance);
	return instance;
}
