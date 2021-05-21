#include "stdafx.h"
#include "White_Potion.h"
#include "Bitmap_Manager.h"
#include "GameObject_Manager.h"
#include "Line_Manager.h"
#include "Monster.h"
#include "Scroll_Manager.h"


CWhite_Potion::CWhite_Potion()
{
}


CWhite_Potion::~CWhite_Potion()
{
}

int CWhite_Potion::Ready_GameObject()
{
	m_hdc = CBitmap_Manager::Get_Instance()->Get_memDC(L"Item");
	m_State_Num_hdc = CBitmap_Manager::Get_Instance()->Get_memDC(L"State_Num");
	m_info.sizeX = 33;
	m_info.sizeY = 33;

	m_itemInfo.id = Object_ID::DROP_ITEM;
	m_itemInfo.type = Item_type::CONSUME;
	m_itemInfo.money = 0;
	m_itemInfo.buyMoney = 0;
	m_itemInfo.sellMoney = 10;
	m_itemInfo.quantity = 1;
	m_itemInfo.hp = 500;
	strcpy_s(m_itemInfo.itemName, "�Ͼ� ����");

	m_speed = 1;

	m_selectImageX = 1;
	m_selectImageY = 1;

	UpdateRect_GameObject();
	return 0;
}

void CWhite_Potion::Late_Update_GameObject()
{
	float fY = 0.f;
	bool bCollLine = CLine_Manager::Get_Instance()->Collision_Line_Manager(this, &fY);
	if (abs(m_info.y - (fY - m_info.sizeY / 2)) >= 5)
		m_info.y += m_speed;
	else
		m_info.y = fY - m_info.sizeY / 2;
}

//void CWhite_Potion::Render_GameObject(HDC hDC)
//{
//	UpdateRect_GameObject();
//	int scrollX = 0;
//	int scrollY = 0;
//	if (!m_isFieldOut)
//	{
//		scrollX = CScroll_Manager::Get_ScrollX();
//		scrollY = CScroll_Manager::Get_ScrollY();
//	}
//	GdiTransparentBlt(hDC, // �׸��� �����ϰ��� �ϴ� ���. 
//		m_rect.left + scrollX,//��ġ x,y
//		m_rect.top + scrollY,
//		m_info.sizeX,// ũ�� xy
//		m_info.sizeY,
//		m_hdc,// ���� �� ���
//		m_info.sizeX * 1, m_info.sizeY * 1,// �׸��� ���� ��ġ x,y
//		m_info.sizeX,// �׸����� �ϴ� ������ ũ�� x,y
//		m_info.sizeY,
//		RGB(255, 0, 255));
//
//	if (m_isFieldOut)
//	{
//		int temp = m_itemInfo.quantity;
//		int num = 0;
//		int temp3 = m_itemInfo.quantity;
//		while (true)
//		{
//			num++;
//			temp3 /= 10;
//			if (temp3 == 0)
//				break;
//		}
//
//		for (int i = 0; i < num; i++)
//		{
//			int temp2 = temp % 10;
//			GdiTransparentBlt(hDC, // �׸��� �����ϰ��� �ϴ� ���. 
//				m_rect.right - 5 - i * 7,//��ġ x,y+ i) * 7,//��ġ x,y
//				m_rect.bottom - 10,
//				7,// ũ�� xy
//				10,
//				m_State_Num_hdc,// ���� �� ���
//				7 * temp2, 0,// �׸��� ���� ��ġ x,y
//				7,// �׸����� �ϴ� ������ ũ�� x,y
//				10,
//				RGB(255, 0, 255));
//			temp /= 10;
//			if (temp == 0)
//				break;
//		}
//	}
//}

void CWhite_Potion::Release_GameObject()
{
}

CGameObject * CWhite_Potion::Create(float posX, float posY)
{
	CGameObject * instance = new CWhite_Potion;
	if (0 > instance->Ready_GameObject())
	{
		Safe_Delete(instance);
		instance = nullptr;
	}
	instance->Set_Pos(posX, posY);
	CGameObject_Manager::Get_Instance()->Add_GameObject_Manager(Object_ID::DROP_ITEM, instance);
	return instance;
}
