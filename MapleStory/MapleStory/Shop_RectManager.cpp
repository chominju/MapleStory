#include "stdafx.h"
#include "Shop_RectManager.h"
#include "Item.h"
#include "GameObject_Manager.h"
#include "Inventory_RectManager.h"
#include "Red_Potion.h"
#include "Eilxir.h"
#include "Power_Elixir.h"
#include "Blood_Dagger.h"
#include "ArcaneShade_Dagger.h"

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
	CItem* tempItem;
	for (int i = 0; i < 5; i++)
	{
		if (i == 0)
		{
			tempItem = CPower_Elixir::Create();
			tempItem->Set_Size(33, 33);
			tempItem->Set_shopPos(m_info.x + 30, m_info.y + 130 + 40 * i);
			tempItem->Set_Quantity(99);
			m_shopList.push_back(tempItem);
		}
		else if (i == 1)
		{
			tempItem = CBlood_Dagger::Create();
			tempItem->Set_Size(33, 33);
			tempItem->Set_shopPos(m_info.x + 30, m_info.y + 130 + 40 * i);
			m_shopList.push_back(tempItem);
		}
		else if (i == 2)
		{
			tempItem = CArcaneShade_Dagger::Create();
			tempItem->Set_Size(33, 33);
			tempItem->Set_shopPos(m_info.x + 30, m_info.y + 130 + 40 * i);
			m_shopList.push_back(tempItem);
		}
		else
		{
			temp = new CItem;
			temp->Set_Size(33, 33);
			temp->Set_Pos(m_info.x + 30, m_info.y + 130 + 40 * i);
			m_shopList.push_back(temp);
		}
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

	list<CItem*>* curlist =  Get_CurrentList();
	list<CItem*>::iterator finditer = curlist->end();
	Object_Info findInfo;

	for (list<CItem*>::iterator iter = curlist->begin(); iter != curlist->end(); iter++)
	{
		if (!strcmp((*iter)->Get_ItemInfo()->itemName, "NONE"))
		{
			finditer = iter;
			findInfo = *(*iter)->Get_Info();
		}
		else
		{
			if (finditer == curlist->end())
				continue;
			else
			{
				Pos_float pos = (*iter)->Get_shopPos();
				iter_swap(finditer, iter);
				(*iter)->Set_Pos(pos.x, pos.y);
				(*finditer)->Set_shopPos(findInfo.x, findInfo.y);
				finditer = curlist->end();
			}
		}
	}


	for (auto & inven : *invenEquip)
	{
		bool check = false;
		if (!strcmp(inven->Get_ItemInfo()->itemName, "NONE"))
			continue;
		for (auto & shop : m_equipmentList)
		{
			if (shop == inven)
			{
				check = true;
				break;
			}
		}

		if (!check)
		{
			for (auto & shop : m_equipmentList)
			{
				if (!strcmp(shop->Get_ItemInfo()->itemName, "NONE"))
				{
					Object_Info tempPos = *shop->Get_Info();
					shop = inven;
					shop->Set_shopPos(tempPos.x, tempPos.y);
					break;
				}
			}
		}
	}
	for (auto & inven : *invenConsume)
	{
		bool check = false;
		if (!strcmp(inven->Get_ItemInfo()->itemName, "NONE"))
			continue;
		for (auto & shop : m_consumeList)
		{
			if (shop == inven)
			{
				check = true;
				break;
			}
		}

		if (!check)
		{
			for (auto & shop : m_consumeList)
			{
				if (!strcmp(shop->Get_ItemInfo()->itemName, "NONE"))
				{
					Object_Info tempPos = *shop->Get_Info();
					shop = inven;
					shop->Set_shopPos(tempPos.x, tempPos.y);
					break;
				}
			}
		}
		/*if (!strcmp(inven->Get_ItemInfo()->itemName,"NONE"))
			continue;
		for (auto & shop : m_consumeList)
		{
			if (shop == inven)
				break;
			if (!strcmp(shop->Get_ItemInfo()->itemName, "NONE"))
			{
				Object_Info tempPos = *shop->Get_Info();
				shop = inven;
				shop->Set_shopPos(tempPos.x, tempPos.y);
				break;
			}
		}*/
	}

	
	for (auto & inven : *invenEtc)
	{
		if (!strcmp(inven->Get_ItemInfo()->itemName, "NONE"))
			continue;
		for (auto & shop : m_etcList)
		{
			if (shop == inven)
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
	return 0;
}

void CShop_RectManager::Late_Update_GameObject()
{
	
}

void CShop_RectManager::Render_GameObject(HDC hDC)
{
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
}

void CShop_RectManager::DeleteItem(CItem * item)
{
	m_consumeList.empty();
	*m_deleteIter = new CItem();
	(*m_deleteIter)->Set_Pos(m_deleteItemPos.x, m_deleteItemPos.y);
	(*m_deleteIter)->Set_Size(33, 33);
}

void CShop_RectManager::SellItem(char * itemName, CItem*& useItem)
{
	list<CItem*>* tempList = Get_CurrentList();

	for (auto & list : *tempList)
	{
		if(list == useItem)
		{
			CSoundMgr::Get_Instance()->PlaySound(L"DropItem.mp3", CSoundMgr::PLAYER);
			CGameObject_Manager::Get_Instance()->GetPlayer()->Set_Change_Money(list->Get_ItemInfo()->sellMoney);
			list->Set_Change_Quantity(-1);
			if (list->Get_ItemInfo()->quantity == 0)
			{
				CInventory_RectManager::Get_Instance()->Find_DeleteItem(itemName , list);
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

void CShop_RectManager::BuyItem(CItem*& item)
{
	if (strcmp(item->Get_ItemInfo()->itemName, "NONE"))
	{
		if (item->Get_ItemInfo()->buyMoney <= CGameObject_Manager::Get_Instance()->GetPlayer()->Get_Money())
		{
			CGameObject_Manager::Get_Instance()->GetPlayer()->Set_Change_Money(-item->Get_ItemInfo()->buyMoney);
			if (item->Get_ItemInfo()->type == Item_type::CONSUME)
			{
				CItem* item = CPower_Elixir::Create();
				item->Set_m_isFieldOut(true);
				item->Set_ItemPlace(Item_Place::INVENTORY_ITEM);
				CInventory_RectManager::Get_Instance()->Push_ConsumeList(item);
			}
			else if (item->Get_ItemInfo()->type == Item_type::EQUIPMENT)
			{
				if (!strcmp(item->Get_ItemInfo()->itemName, "아케인셰이드 대거"))
				{
					CItem* item = CArcaneShade_Dagger::Create();
					item->Set_m_isFieldOut(true);
					item->Set_ItemPlace(Item_Place::INVENTORY_ITEM);
					CInventory_RectManager::Get_Instance()->Push_EquipmentList(item);
				}
				else if (!strcmp(item->Get_ItemInfo()->itemName, "블러드 대거"))
				{
					CItem* item = CBlood_Dagger::Create();
					item->Set_m_isFieldOut(true);
					item->Set_ItemPlace(Item_Place::INVENTORY_ITEM);
					CInventory_RectManager::Get_Instance()->Push_EquipmentList(item);
				}
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
