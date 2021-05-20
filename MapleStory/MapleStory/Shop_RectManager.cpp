#include "stdafx.h"
#include "Shop_RectManager.h"
#include "Item.h"
#include "GameObject_Manager.h"
#include "Inventory_RectManager.h"
#include "Red_Potion.h"
#include "White_Potion.h"


CShop_RectManager* CShop_RectManager::instance = nullptr;
CShop_RectManager::CShop_RectManager()
{
}

CShop_RectManager::~CShop_RectManager()
{
}

int CShop_RectManager::Ready_GameObject()
{
	m_info.sizeX = 33;
	m_info.sizeY = 33;

	CItem* temp;

	for (int i = 0; i < 5; i++)
	{
			temp = new CItem;
			temp->Set_Size(33, 33);
			temp->Set_Pos(m_info.x + 30, m_info.y + 130 + 40 * i);
			m_shopList.push_back(temp);
	}

	for (int i = 0; i < 5; i++)
	{
		temp = new CItem;
		temp->Set_Size(33, 33);
		temp->Set_Pos(m_info.x + 30 + 230, m_info.y + 130 + 40 * i);
		m_equipmentList.push_back(temp);
	}


	for (int i = 0; i < 5; i++)
	{
		temp = new CItem;
		temp->Set_Size(33, 33);
		temp->Set_Pos(m_info.x + 30 + 230, m_info.y + 130 + 40 * i);
		m_consumeList.push_back(temp);
	}

	for (int i = 0; i < 5; i++)
	{
		temp = new CItem;
		temp->Set_Size(33, 33);
		temp->Set_Pos(m_info.x + 30 + 230, m_info.y + 130 + 40 * i);
		m_etcList.push_back(temp);
	}

	return 0;
}

int CShop_RectManager::Update_GameObject()
{
	list<CItem*>* tempEquip = CInventory_RectManager::Get_Instance()->Get_EquipmentList();
	list<CItem*>* tempConsume = CInventory_RectManager::Get_Instance()->Get_ConsumeList();
	list<CItem*>* tempEtc = CInventory_RectManager::Get_Instance()->Get_EtcList();
	for (auto & temp : *tempEquip)
	{
		if (!strcmp(temp->Get_ItemInfo()->itemName, "NONE"))
			continue;

		for (auto & shop : m_equipmentList)
		{
			if (!strcmp(shop->Get_ItemInfo()->itemName, "NONE"))
			{
				Object_Info tempPos = *shop->Get_Info();
				shop = temp;
				shop->Set_Pos(tempPos.x, tempPos.y);
			}
		}
	}

	for (auto & temp : *tempConsume)
	{
		if (!strcmp(temp->Get_ItemInfo()->itemName, "»¡°£ Æ÷¼Ç"))
		{
			for (auto & shop : m_consumeList)
			{
				if (!strcmp(shop->Get_ItemInfo()->itemName, "»¡°£ Æ÷¼Ç"))
				{
					shop->Set_Quantity(temp->Get_ItemInfo()->quantity);
					break;
				}
				else if (!strcmp(shop->Get_ItemInfo()->itemName, "NONE"))
				{
					CGameObject* item = CRed_Potion::Create(shop->Get_Info()->x, shop->Get_Info()->y);
					dynamic_cast<CItem*>(item)->Set_m_isFieldOut(true);
					dynamic_cast<CItem*>(item)->Set_ItemInfo(*temp->Get_ItemInfo());
					shop = dynamic_cast<CItem*>(item);
					break;
				}
			}
		}
		else if (!strcmp(temp->Get_ItemInfo()->itemName, "ÇÏ¾á Æ÷¼Ç"))
		{
			for (auto & shop : m_consumeList)
			{
				if (!strcmp(shop->Get_ItemInfo()->itemName, "ÇÏ¾á Æ÷¼Ç"))
				{
					shop->Set_Quantity(temp->Get_ItemInfo()->quantity);
					break;
				}
				else if (!strcmp(shop->Get_ItemInfo()->itemName, "NONE"))
				{
					CGameObject* item = CWhite_Potion::Create(shop->Get_Info()->x, shop->Get_Info()->y);
					dynamic_cast<CItem*>(item)->Set_m_isFieldOut(true);
					dynamic_cast<CItem*>(item)->Set_ItemInfo(*temp->Get_ItemInfo());
					shop = dynamic_cast<CItem*>(item);
					break;
				}
			}
		}
	}

	for (auto & temp : *tempEtc)
	{
		if (!strcmp(temp->Get_ItemInfo()->itemName, "NONE"))
			continue;
		for (auto & shop : m_etcList)
		{
			if (!strcmp(shop->Get_ItemInfo()->itemName, "NONE"))
			{
				Object_Info tempPos = *shop->Get_Info();
				shop = temp;
				shop->Set_Pos(tempPos.x, tempPos.y);
			}
		}
	}

	//for (auto & temp : *tempEquip)
	//{
	//	if (!strcmp(temp->Get_ItemInfo()->itemName, "NONE"))
	//		continue;
	//	m_equipmentList.push_back(temp);
	//}
	
	return 0;
}

void CShop_RectManager::Late_Update_GameObject()
{
}

void CShop_RectManager::Render_GameObject(HDC hDC)
{
	RECT rc;
	list<CItem*> tempList;
	if (m_isEquipmentClick)
		tempList = m_equipmentList;
	if (m_isConsumeClick)
		tempList = m_consumeList;
	if (m_isEtcClick)
		tempList = m_etcList;
	for (auto& list : tempList)
	{
		list->Render_GameObject(hDC);
	}

	for (auto & list : m_shopList)
	{
		list->Render_GameObject(hDC);
	}
}

void CShop_RectManager::Release_GameObject()
{
}

void CShop_RectManager::UpdateRect_GameObject()
{
}

void CShop_RectManager::Push_EquipmentList(CItem * item)
{
}

void CShop_RectManager::Push_ConsumeList(CItem * item)
{
}

void CShop_RectManager::Push_EtcList(CItem * item)
{
}

void CShop_RectManager::Find_EquipmentList(char * itemName)
{
}

void CShop_RectManager::Find_ConsumeList(char * itemName)
{
}

void CShop_RectManager::Find_EtcList(char * itemName)
{
}

void CShop_RectManager::Use_Item(char * itemName)
{
}

void CShop_RectManager::Drop_Item(char * itemName, Object_Info pos)
{
}

void CShop_RectManager::Create(RECT pos)
{
	if (instance == nullptr)
	{
		instance = new CShop_RectManager;
		instance->SetPos(pos);
		instance->Ready_GameObject();
	}
}
