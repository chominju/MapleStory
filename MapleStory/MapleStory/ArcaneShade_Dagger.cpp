#include "stdafx.h"
#include "ArcaneShade_Dagger.h"
#include "Bitmap_Manager.h"
#include "GameObject_Manager.h"
#include "Line_Manager.h"
#include "Monster.h"
#include "Scroll_Manager.h"


CArcaneShade_Dagger::CArcaneShade_Dagger()
{

}

CArcaneShade_Dagger::~CArcaneShade_Dagger()
{

}

int CArcaneShade_Dagger::Ready_GameObject()
{
	m_hdc = CBitmap_Manager::Get_Instance()->Get_memDC(L"Item");
	m_State_Num_hdc = CBitmap_Manager::Get_Instance()->Get_memDC(L"State_Num");
	m_info.sizeX = 33;
	m_info.sizeY = 33;

	m_itemInfo.id = Object_ID::DROP_ITEM;
	m_itemInfo.type = Item_type::EQUIPMENT;
	m_itemInfo.money = 0;
	m_itemInfo.buyMoney = 10000;
	m_itemInfo.sellMoney = 5000;
	m_itemInfo.quantity = 1;
	m_itemInfo.attack = 5000;
	strcpy_s(m_itemInfo.itemName, "아케인셰이드 대거");
	m_itemPlace = SHOP_ITEM;

	m_speed = 1;

	m_selectImageX = 1;
	m_selectImageY = 2;

	UpdateRect_GameObject();
	return 0;
}

void CArcaneShade_Dagger::Late_Update_GameObject()
{
	float fY = 0.f;
	bool bCollLine = CLine_Manager::Get_Instance()->Collision_Line_Manager(this, &fY);
	if (abs(m_info.y - (fY - m_info.sizeY / 2)) >= 5)
		m_info.y += m_speed;
	else
		m_info.y = fY - m_info.sizeY / 2;
}

void CArcaneShade_Dagger::Release_GameObject()
{
}

CGameObject * CArcaneShade_Dagger::Create(float posX, float posY)
{
	CGameObject * instance = new CArcaneShade_Dagger;
	if (0 > instance->Ready_GameObject())
	{
		Safe_Delete(instance);
		instance = nullptr;
	}
	instance->Set_Pos(posX, posY);
	CGameObject_Manager::Get_Instance()->Add_GameObject_Manager(Object_ID::DROP_ITEM, instance);
	return instance;
}

CItem * CArcaneShade_Dagger::Create()
{
	CItem * instance = new CArcaneShade_Dagger;
	if (0 > instance->Ready_GameObject())
	{
		Safe_Delete(instance);
		instance = nullptr;
	}
	instance->Set_m_isFieldOut(true);
	return instance;
}
