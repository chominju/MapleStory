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
	list<CItem*>* invenEquip = CInventory_RectManager::Get_Instance()->Get_EquipmentList();
	list<CItem*>* invenConsume = CInventory_RectManager::Get_Instance()->Get_ConsumeList();
	list<CItem*>* invenEtc = CInventory_RectManager::Get_Instance()->Get_EtcList();
	for (auto & inven : *invenEquip)
	{
		if (!strcmp(inven->Get_ItemInfo()->itemName, "NONE"))
			continue;
		for (auto & shop : m_equipmentList)
		{
			if (!strcmp(shop->Get_ItemInfo()->itemName, inven->Get_ItemInfo()->itemName))
				break;
			if (!strcmp(shop->Get_ItemInfo()->itemName, "NONE"))
			{
				Object_Info tempPos = *shop->Get_Info();
				shop = inven;
				shop->Set_shopPos(tempPos.x, tempPos.y);
				break;
			}
		}
	}
	for (auto & inven : *invenConsume)
	{
		if (!strcmp(inven->Get_ItemInfo()->itemName,"NONE"))
			continue;
		for (auto & shop : m_consumeList)
		{
			if (!strcmp(shop->Get_ItemInfo()->itemName, inven->Get_ItemInfo()->itemName))
				break;
			if (!strcmp(shop->Get_ItemInfo()->itemName, "NONE"))
			{
				Object_Info tempPos = *shop->Get_Info();
				shop = inven;
				shop->Set_shopPos(tempPos.x, tempPos.y);
				break;
			}
		}
	}

	
	for (auto & inven : *invenEtc)
	{
		if (!strcmp(inven->Get_ItemInfo()->itemName, "NONE"))
			continue;
		for (auto & shop : m_etcList)
		{
			if (!strcmp(shop->Get_ItemInfo()->itemName, inven->Get_ItemInfo()->itemName))
				break;
			if (!strcmp(shop->Get_ItemInfo()->itemName, "NONE"))
			{
				Object_Info tempPos = *shop->Get_Info();
				shop = inven;
				shop->Set_shopPos(tempPos.x, tempPos.y);
				break;
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
	list<CItem*>* tempList = Get_CurrentList();

	for (auto& list : *tempList)
		list->Render_GameObject(hDC);

	for (auto & list : m_shopList)
		list->Render_GameObject(hDC);
}

void CShop_RectManager::Release_GameObject()
{
	m_shopList.clear();
	m_equipmentList.clear();
	m_consumeList.clear();
	m_etcList.clear();
	instance = nullptr;
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

void CShop_RectManager::Find_DeleteItem(char * itemName)
{
	list<CItem*>* tempList = Get_CurrentList();
	for (list<CItem*>::iterator iter = tempList->begin(); iter != tempList->end(); iter++)
	{
		if (!strcmp((*iter)->Get_ItemInfo()->itemName, itemName))
		{
			m_deleteIter = iter;
			m_deleteItemPos=(*iter)->Get_shopPos();
		}
	}

	/*for (auto & list : m_consumeList)
	{
		if (!strcmp(list->Get_ItemInfo()->itemName, itemName))
		{
			deleteItem = list;
			m_deleteItemPos = list->Get_shopPos();
		}
	}*/
}

void CShop_RectManager::DeleteItem(CItem * item)
{
	m_consumeList.empty();
	//*m_deleteIter = item;
	//Safe_Delete(*m_deleteIter);
	*m_deleteIter = new CItem();
	(*m_deleteIter)->Set_Pos(m_deleteItemPos.x, m_deleteItemPos.y);
	(*m_deleteIter)->Set_Size(33, 33);
	//Safe_Delete(deleteItem);
	//deleteItem = new CItem();
	//deleteItem->Set_Pos(m_deleteItemPos.x, m_deleteItemPos.y);

	/*Object_Info tempObjInfo = *list->Get_Info();
	Pos_float tempInfo = list->Get_shopPos();
	CItem * temp = new CItem;
	temp->Set_shopPos(tempInfo.x, tempInfo.y);
	temp->Set_Size(tempObjInfo.sizeX, tempObjInfo.sizeY);

	Safe_Delete(list);
	list = temp;
	int i;
	i = 10;*/
	m_consumeList.empty();
	int j;
	j = 0;
}

void CShop_RectManager::SellItem(char * itemName)
{
	list<CItem*>* tempList = Get_CurrentList();

	for (auto & list : *tempList)
	{
		if (!strcmp(list->Get_ItemInfo()->itemName, itemName))
		{
			CGameObject_Manager::Get_Instance()->GetPlayer()->Set_Change_Money(list->Get_ItemInfo()->sellMoney);
			list->Set_Change_Quantity(-1);
			if (list->Get_ItemInfo()->quantity == 0)
			{
				CInventory_RectManager::Get_Instance()->Find_DeleteItem(itemName);
				Pos_float tempInfo = list->Get_shopPos();
				CItem * temp = new CItem;
				temp->Set_Pos(tempInfo.x, tempInfo.y);
				temp->Set_Size(33, 33);

				Safe_Delete(list);
				list = temp;
				CInventory_RectManager::Get_Instance()->DeleteItem(list, tempInfo);
				m_consumeList.empty();
				int i;
				i = 10;
			}
		}
	}
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