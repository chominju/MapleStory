#include "stdafx.h"
#include "Eilxir.h"
#include "Bitmap_Manager.h"
#include "GameObject_Manager.h"
#include "Line_Manager.h"
#include "Monster.h"
#include "Scroll_Manager.h"


CEilxir::CEilxir()
{
}


CEilxir::~CEilxir()
{
}

int CEilxir::Ready_GameObject()
{
	m_hdc = CBitmap_Manager::Get_Instance()->Get_memDC(L"Item");
	m_State_Num_hdc = CBitmap_Manager::Get_Instance()->Get_memDC(L"State_Num");
	m_info.sizeX = 33;
	m_info.sizeY = 33;

	m_itemInfo.id = Object_ID::DROP_ITEM;
	m_itemInfo.type = Item_type::CONSUME;
	m_itemInfo.money = 0;
	m_itemInfo.buyMoney = 1000;
	m_itemInfo.sellMoney = 500;
	m_itemInfo.quantity = 1;
	strcpy_s(m_itemInfo.itemName, "¿¤¸¯¼­");

	m_speed = 1;

	m_selectImageX = 1;
	m_selectImageY = 0;

	UpdateRect_GameObject();
	return 0;
}

void CEilxir::Late_Update_GameObject()
{
	float fY = 0.f;
	bool bCollLine = CLine_Manager::Get_Instance()->Collision_Line_Manager(this, &fY);
	if (abs(m_info.y - (fY - m_info.sizeY / 2)) >= 5)
		m_info.y += m_speed;
	else
		m_info.y = fY - m_info.sizeY / 2;
}

void CEilxir::Release_GameObject()
{
}

CGameObject * CEilxir::Create(float posX, float posY)
{
	CGameObject * instance = new CEilxir;
	if (0 > instance->Ready_GameObject())
	{
		Safe_Delete(instance);
		instance = nullptr;
	}
	instance->Set_Pos(posX, posY);
	CGameObject_Manager::Get_Instance()->Add_GameObject_Manager(Object_ID::DROP_ITEM, instance);
	return instance;
}

int CEilxir::Get_ItemInfoHp()
{
	float playerMaxHp = CGameObject_Manager::Get_Instance()->GetPlayer()->Get_Data()->maxHp;
	m_itemInfo.hp = (int)playerMaxHp / 2;
	return m_itemInfo.hp;
}
