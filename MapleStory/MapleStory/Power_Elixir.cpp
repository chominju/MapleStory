#include "stdafx.h"
#include "Power_Elixir.h"
#include "Bitmap_Manager.h"
#include "GameObject_Manager.h"
#include "Line_Manager.h"
#include "Monster.h"
#include "Scroll_Manager.h"

CPower_Elixir::CPower_Elixir()
{
}


CPower_Elixir::~CPower_Elixir()
{
}

int CPower_Elixir::Ready_GameObject()
{
	m_hdc = CBitmap_Manager::Get_Instance()->Get_memDC(L"Item");
	m_State_Num_hdc = CBitmap_Manager::Get_Instance()->Get_memDC(L"State_Num");
	m_info.sizeX = 33;
	m_info.sizeY = 33;

	m_itemInfo.id = Object_ID::DROP_ITEM;
	m_itemInfo.type = Item_type::CONSUME;
	m_itemInfo.money = 0;
	m_itemInfo.buyMoney = 2000;
	m_itemInfo.sellMoney = 1000;
	m_itemInfo.quantity = 1;
	strcpy_s(m_itemInfo.itemName, "ÆÄ¿ö ¿¤¸¯¼­");
	m_itemPlace = SHOP_ITEM;
	m_speed = 1;

	m_selectImageX = 2;
	m_selectImageY = 0;

	UpdateRect_GameObject();
	return 0;
}

void CPower_Elixir::Late_Update_GameObject()
{
	float fY = 0.f;
	bool bCollLine = CLine_Manager::Get_Instance()->Collision_Line_Manager(this, &fY);
	if (abs(m_info.y - (fY - m_info.sizeY / 2)) >= 5)
		m_info.y += m_speed;
	else
		m_info.y = fY - m_info.sizeY / 2;
}

void CPower_Elixir::Release_GameObject()
{
}

CGameObject * CPower_Elixir::Create(float posX, float posY)
{
	CGameObject * instance = new CPower_Elixir;
	if (0 > instance->Ready_GameObject())
	{
		Safe_Delete(instance);
		instance = nullptr;
	}
	instance->Set_Pos(posX, posY);
	CGameObject_Manager::Get_Instance()->Add_GameObject_Manager(Object_ID::DROP_ITEM, instance);
	return instance;
}

CItem * CPower_Elixir::Create()
{
	CItem * instance = new CPower_Elixir;
	if (0 > instance->Ready_GameObject())
	{
		Safe_Delete(instance);
		instance = nullptr;
	}
	instance->Set_m_isFieldOut(true);
	return instance;
}

int CPower_Elixir::Get_ItemInfoHp()
{
	float playerMaxHp = CGameObject_Manager::Get_Instance()->GetPlayer()->Get_Data()->maxHp;
	m_itemInfo.hp = (int)playerMaxHp;
	return m_itemInfo.hp;
}
