#include "stdafx.h"
#include "Inventory_RectManager.h"
#include "Item.h"
#include "GameObject_Manager.h"
#include "Red_Potion.h"
#include "Eilxir.h"
#include "Drop_Mushroom.h"
#include "Drop_Octopus.h"
#include "Power_Elixir.h"
#include "Shop_RectManager.h"
#include "Player.h"

CInventory_RectManager * CInventory_RectManager::instance = nullptr;
CInventory_RectManager::CInventory_RectManager()
{
}

CInventory_RectManager::~CInventory_RectManager()
{
}

int CInventory_RectManager::Ready_GameObject()
{
	m_info.sizeX = 33;
	m_info.sizeY = 33;

	CItem* temp;
	for (int i = 0; i < 6; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			temp = new CItem;
			temp->Set_Size(33, 33);
			temp->Set_Pos(m_info.x + 30 + 40 * j, m_info.y + 50 + 40 * i);
			m_equipmentList.push_back(temp);
		}
	}

	for (int i = 0; i < 6; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			temp = new CItem;
			temp->Set_Size(33, 33);
			temp->Set_Pos(m_info.x + 30 + 40 * j, m_info.y + 50 + 40 * i);
			m_consumeList.push_back(temp);
		}
	}

	for (int i = 0; i < 6; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			temp = new CItem;
			temp->Set_Size(33, 33);
			temp->Set_Pos(m_info.x + 30 + 40 * j, m_info.y + 50 + 40 * i);
			m_etcList.push_back(temp);
		}
	}
	return 0;
}

int CInventory_RectManager::Update_GameObject()
{
	return 0;
}

void CInventory_RectManager::Late_Update_GameObject()
{
}

void CInventory_RectManager::Render_GameObject(HDC hDC)
{
	list<CItem*> tempList;
	if (m_isEquipmentClick)
		tempList = m_equipmentList;
	if (m_isConsumeClick)
		tempList = m_consumeList;
	if (m_isEtcClick)
		tempList = m_etcList;

	for (auto& list : tempList)
		list->Render_GameObject(hDC);
}

void CInventory_RectManager::Release_GameObject()
{
}

void CInventory_RectManager::Push_EquipmentList(CItem * item)
{
	if (item->Get_ItemInfo()->type == Item_type::EQUIPMENT)
	{
		for (auto & list : m_equipmentList)
		{
			if (!strcmp(list->Get_ItemInfo()->itemName, "NONE"))
			{
				Object_Info tempInfo = *(list->Get_Info());
				Safe_Delete(list);
				list = item;
				list->Set_Pos(tempInfo.x, tempInfo.y);
				break;
			}
		}
	}
}

void CInventory_RectManager::Push_ConsumeList(CItem * item)
{
	if (item->Get_ItemInfo()->type == Item_type::CONSUME)
	{
		bool check = false;
		for (auto & list : m_consumeList)
		{
			if (!strcmp(list->Get_ItemInfo()->itemName, item->Get_ItemInfo()->itemName))
			{
				check = true;
				list->Set_Change_Quantity(item->Get_ItemInfo()->quantity);
			}
		}
		if (!check)
		{
			for (auto & list : m_consumeList)
			{
				if (!strcmp(list->Get_ItemInfo()->itemName, "NONE"))
				{
					Object_Info tempInfo = *(list->Get_Info());
					Safe_Delete(list);
					list = item;
					list->Set_Pos(tempInfo.x, tempInfo.y);
					break;
				}
			}
		}
	}

}

void CInventory_RectManager::Push_EtcList(CItem * item)
{
	bool check = false;
	for (auto & list : m_etcList)
	{
		if (!strcmp(list->Get_ItemInfo()->itemName, item->Get_ItemInfo()->itemName))
		{
			check = true;
			list->Set_Change_Quantity(item->Get_ItemInfo()->quantity);
		}
	}

	if (!check)
	{
		for (auto & list : m_etcList)
		{
			if (!strcmp(list->Get_ItemInfo()->itemName, "NONE"))
			{
				Object_Info tempInfo = *(list->Get_Info());
				Safe_Delete(list);
				list = item;
				list->Set_Pos(tempInfo.x, tempInfo.y);
				break;
			}
		}
	}

}

void CInventory_RectManager::Use_Item(CItem*& useItem)
{
	if (m_isEquipmentClick)
	{
		if (strcmp(useItem->Get_ItemInfo()->itemName, "NONE"))
		{
			CPlayer *getPlayer = dynamic_cast<CPlayer*>(CGameObject_Manager::Get_Instance()->GetPlayer());
			CSoundMgr::Get_Instance()->PlaySound(L"DropItem.mp3", CSoundMgr::PLAYER);
			if (getPlayer->Get_Weapon() == nullptr)
			{
				// ÀåÂø Àåºñ°¡ ¾øÀ» ¶§
				float invenPosX = useItem->Get_Info()->x;
				float invenPosY = useItem->Get_Info()->y;
				useItem->Set_ItemPlace(Item_Place::EQUIPMENT_ITEM);
				getPlayer->Set_Weapon(useItem);
				useItem = new CItem();
				useItem->Set_Size(33, 33);
				useItem->Set_Pos(invenPosX, invenPosY);
			}
			else
			{
				float invenPosX = useItem->Get_Info()->x;
				float invenPosY = useItem->Get_Info()->y;
				Pos_float shop_pos = useItem->Get_shopPos();
				CItem* getWeapon = getPlayer->Get_Weapon();
				useItem->Set_ItemPlace(Item_Place::EQUIPMENT_ITEM);
				getPlayer->Set_Weapon(useItem);

				getWeapon->Set_ItemPlace(Item_Place::INVENTORY_ITEM);
				getWeapon->Set_Pos(invenPosX, invenPosY);
				getWeapon->Set_shopPos(shop_pos.x, shop_pos.y);
				useItem = getWeapon;
			}
		}
	}

	else if (m_isConsumeClick)
	{
			if (strcmp(useItem->Get_ItemInfo()->itemName, "NONE"))
			{
				CGameObject_Manager::Get_Instance()->GetPlayer()->Set_Change_Hp((float)useItem->Get_ItemInfoHp());
				useItem->Set_Change_Quantity(-1);
				CSoundMgr::Get_Instance()->PlaySound(L"Potion_Use.mp3", CSoundMgr::PLAYER);
				if (useItem->Get_ItemInfo()->quantity == 0)
				{
					if (dynamic_cast<CPlayer*>(CGameObject_Manager::Get_Instance()->GetPlayer())->Get_IsShopClick())
						CShop_RectManager::Get_Instance()->Find_DeleteItem(useItem->Get_ItemInfo()->itemName);
					Object_Info tempInfo = *useItem->Get_Info();
					CItem * temp = new CItem;
					temp->Set_Pos(tempInfo.x, tempInfo.y);
					temp->Set_Size(tempInfo.sizeX, tempInfo.sizeY);

					Safe_Delete(useItem);
					useItem = temp;
					if (dynamic_cast<CPlayer*>(CGameObject_Manager::Get_Instance()->GetPlayer())->Get_IsShopClick())
						CShop_RectManager::Get_Instance()->DeleteItem(useItem);
				}
			}
		if (m_isEtcClick)
		{
			//m_etcList
		}
	}
}

void CInventory_RectManager::Use_ItemQuickSlot(char * itemName)
{
	for (auto & list : m_consumeList)
	{
		if (!strcmp(list->Get_ItemInfo()->itemName, itemName))
		{
			if (list->Get_ItemInfo()->quantity == 0)
				return;
			CGameObject_Manager::Get_Instance()->GetPlayer()->Set_Change_Hp((float)list->Get_ItemInfoHp());
			list->Set_Change_Quantity(-1);
			CSoundMgr::Get_Instance()->PlaySound(L"Potion_Use.mp3", CSoundMgr::PLAYER);
			if (list->Get_ItemInfo()->quantity == 0)
			{
				if (dynamic_cast<CPlayer*>(CGameObject_Manager::Get_Instance()->GetPlayer())->Get_IsShopClick())
					CShop_RectManager::Get_Instance()->Find_DeleteItem(list->Get_ItemInfo()->itemName);
				Object_Info tempInfo = *list->Get_Info();
				CItem * temp = new CItem;
				temp->Set_Pos(tempInfo.x, tempInfo.y);
				temp->Set_Size(tempInfo.sizeX, tempInfo.sizeY);

				Safe_Delete(list);
				list = temp;
				if (dynamic_cast<CPlayer*>(CGameObject_Manager::Get_Instance()->GetPlayer())->Get_IsShopClick())
					CShop_RectManager::Get_Instance()->DeleteItem(list);
			}
		}
	}
}

void CInventory_RectManager::Drop_Item(char * itemName , Object_Info pos , CItem*& item , list<CItem*>::iterator* Dropiter)
{
	list<CItem*>* tempList;
	if (m_isEquipmentClick)
		tempList = &m_equipmentList;
	else if (m_isConsumeClick)
		tempList = &m_consumeList;
	else if (m_isEtcClick)
		tempList = &m_etcList;
	else
		return;

	if (item->Get_ItemInfo()->type == Item_type::EQUIPMENT)
	{
		CItem* temp = new CItem();
		temp->Set_Size(33, 33);
		temp->Set_Pos(pos.x, pos.y);
		item->Set_ItemPlace(Item_Place::FIELD_ITEM);
		item->Set_m_isFieldOut(false);
		item->Set_Pos(CGameObject_Manager::Get_Instance()->GetPlayer()->Get_Info()->x, CGameObject_Manager::Get_Instance()->GetPlayer()->Get_Info()->y);
		CGameObject_Manager::Get_Instance()->Add_GameObject_Manager(Object_ID::DROP_ITEM, dynamic_cast<CGameObject*>(item));
		*(*Dropiter) = temp;
	}

	if (item->Get_ItemInfo()->type == Item_type::CONSUME || item->Get_ItemInfo()->type == Item_type::ETC)
	{
		for (auto& list : *tempList)
		{
			if (!strcmp(list->Get_ItemInfo()->itemName, itemName))
			{
				list->Set_Change_Quantity(-1);
				if (!strcmp(itemName, "»¡°£ Æ÷¼Ç"))
					CGameObject * item = CRed_Potion::Create(CGameObject_Manager::Get_Instance()->GetPlayer()->Get_Info()->x, CGameObject_Manager::Get_Instance()->GetPlayer()->Get_Info()->y);
				else if (!strcmp(itemName, "¿¤¸¯¼­"))
					CGameObject * item = CEilxir::Create(CGameObject_Manager::Get_Instance()->GetPlayer()->Get_Info()->x, CGameObject_Manager::Get_Instance()->GetPlayer()->Get_Info()->y);
				else if (!strcmp(itemName, "ÆÄ¿ö ¿¤¸¯¼­"))
					CGameObject * item = CPower_Elixir::Create(CGameObject_Manager::Get_Instance()->GetPlayer()->Get_Info()->x, CGameObject_Manager::Get_Instance()->GetPlayer()->Get_Info()->y);
				else if (!strcmp(itemName, "¿ÁÅäÆÛ½º ´Ù¸®"))
					CGameObject * item = CDrop_Octopus::Create(CGameObject_Manager::Get_Instance()->GetPlayer()->Get_Info()->x, CGameObject_Manager::Get_Instance()->GetPlayer()->Get_Info()->y);
				else if (!strcmp(itemName, "ÁÖÈ²¹ö¼¸ °«"))
					CGameObject * item = CDrop_Mushroom::Create(CGameObject_Manager::Get_Instance()->GetPlayer()->Get_Info()->x, CGameObject_Manager::Get_Instance()->GetPlayer()->Get_Info()->y);

				if (list->Get_ItemInfo()->quantity == 0)
				{
					//CShop_RectManager::Get_Instance()->Find_DeleteItem(itemName);
					Object_Info tempInfo = *list->Get_Info();
					CItem * temp = new CItem;
					temp->Set_Pos(pos.x, pos.y);
					temp->Set_Size(pos.sizeX, pos.sizeY);

					Safe_Delete(list);
					list = temp;
					//CShop_RectManager::Get_Instance()->DeleteItem(list);
				}
				else
					list->Set_Pos(pos.x, pos.y);
			}
		}
	}

	//for (auto& list : *tempList)
	//{
	//	if (!strcmp(list->Get_ItemInfo()->itemName, itemName))
	//	{
	//		list->Set_Change_Quantity(-1);
	//		if (!strcmp(itemName,"»¡°£ Æ÷¼Ç"))
	//			CGameObject * item = CRed_Potion::Create(CGameObject_Manager::Get_Instance()->GetPlayer()->Get_Info()->x, CGameObject_Manager::Get_Instance()->GetPlayer()->Get_Info()->y);
	//		else if (!strcmp(itemName, "¿¤¸¯¼­"))
	//			CGameObject * item = CEilxir::Create(CGameObject_Manager::Get_Instance()->GetPlayer()->Get_Info()->x, CGameObject_Manager::Get_Instance()->GetPlayer()->Get_Info()->y);
	//		else if (!strcmp(itemName, "ÆÄ¿ö ¿¤¸¯¼­"))
	//			CGameObject * item = CPower_Elixir::Create(CGameObject_Manager::Get_Instance()->GetPlayer()->Get_Info()->x, CGameObject_Manager::Get_Instance()->GetPlayer()->Get_Info()->y);
	//		else if (!strcmp(itemName, "¿ÁÅäÆÛ½º ´Ù¸®"))
	//			CGameObject * item = CDrop_Octopus::Create(CGameObject_Manager::Get_Instance()->GetPlayer()->Get_Info()->x, CGameObject_Manager::Get_Instance()->GetPlayer()->Get_Info()->y);
	//		else if (!strcmp(itemName, "ÁÖÈ²¹ö¼¸ °«"))
	//			CGameObject * item = CDrop_Mushroom::Create(CGameObject_Manager::Get_Instance()->GetPlayer()->Get_Info()->x, CGameObject_Manager::Get_Instance()->GetPlayer()->Get_Info()->y);	
	//		
	//		/*else if (!strcmp(itemName, "ºí·¯µå ´ë°Å"))
	//		{
	//			CItem* temp = new CItem();
	//			temp->Set_Size(33, 33);
	//			temp->Set_Pos(item->Get_Info()->x, item->Get_Info()->y);
	//			item->Set_ItemPlace(Item_Place::FIELD_ITEM);
	//			item->Set_m_isFieldOut(false);
	//			item->Set_Pos(CGameObject_Manager::Get_Instance()->GetPlayer()->Get_Info()->x, CGameObject_Manager::Get_Instance()->GetPlayer()->Get_Info()->y);
	//			CGameObject_Manager::Get_Instance()->Add_GameObject_Manager(Object_ID::DROP_ITEM, item);
	//			list = temp;
	//		}
	//		else if (!strcmp(itemName, "¾ÆÄÉÀÎ¼ÎÀÌµå ´ë°Å"))
	//		{

	//		}*/

	//		if (!list->Get_ItemInfo()->type == Item_type::EQUIPMENT)
	//		{
	//			if (list->Get_ItemInfo()->quantity == 0)
	//			{
	//				//CShop_RectManager::Get_Instance()->Find_DeleteItem(itemName);
	//				Object_Info tempInfo = *list->Get_Info();
	//				CItem * temp = new CItem;
	//				temp->Set_Pos(pos.x, pos.y);
	//				temp->Set_Size(pos.sizeX, pos.sizeY);

	//				Safe_Delete(list);
	//				list = temp;
	//				//CShop_RectManager::Get_Instance()->DeleteItem(list);
	//			}
	//			else
	//				list->Set_Pos(pos.x, pos.y);
	//		}
	//	}
	//}

	////if (!strcmp(item->Get_ItemInfo()->itemName, "ºí·¯µå ´ë°Å"))
	////{
	////	CItem* temp = new CItem();
	////	temp->Set_Size(33, 33);
	////	temp->Set_Pos(pos.x, pos.y);
	////	item->Set_ItemPlace(Item_Place::FIELD_ITEM);
	////	item->Set_m_isFieldOut(false);
	////	item->Set_Pos(CGameObject_Manager::Get_Instance()->GetPlayer()->Get_Info()->x, CGameObject_Manager::Get_Instance()->GetPlayer()->Get_Info()->y);
	////	CGameObject_Manager::Get_Instance()->Add_GameObject_Manager(Object_ID::DROP_ITEM, dynamic_cast<CGameObject*>(item));
	////	*(*Dropiter) = temp;
	////}

	////if (!strcmp(item->Get_ItemInfo()->itemName, "¾ÆÄÉÀÎ¼ÎÀÌµå ´ë°Å"))
	////{
	////	CItem* temp = new CItem();
	////	temp->Set_Size(33, 33);
	////	temp->Set_Pos(pos.x, pos.y);
	////	item->Set_ItemPlace(Item_Place::FIELD_ITEM);
	////	item->Set_m_isFieldOut(false);
	////	item->Set_Pos(CGameObject_Manager::Get_Instance()->GetPlayer()->Get_Info()->x, CGameObject_Manager::Get_Instance()->GetPlayer()->Get_Info()->y);
	////	CGameObject_Manager::Get_Instance()->Add_GameObject_Manager(Object_ID::DROP_ITEM, dynamic_cast<CGameObject*>(item));
	////	*(*Dropiter) = temp;
	////}
}

void CInventory_RectManager::Find_DeleteItem(char * itemName , CItem*& useItem)
{
	list<CItem*>* tempList = Get_CurrentList();
	for (list<CItem*>::iterator iter = tempList->begin(); iter != tempList->end(); iter++)
	{
		if (*iter == useItem)
		{
			m_deleteIter = iter;
			m_deleteItemPos = *(*iter)->Get_Info();
		}
	}
}

void CInventory_RectManager::DeleteItem(CItem * item, Pos_float shopPos)
{
	m_consumeList.empty();
	*m_deleteIter = nullptr;
	*m_deleteIter = new CItem();
	(*m_deleteIter)->Set_Pos(m_deleteItemPos.x, m_deleteItemPos.y);
	(*m_deleteIter)->Set_Size(m_deleteItemPos.sizeX, m_deleteItemPos.sizeY);
	(*m_deleteIter)->Set_shopPos(shopPos.x, shopPos.y);
}

int CInventory_RectManager::Get_ItemQuantity(char * itemName)
{
	for (auto & list : m_consumeList)
	{
		if (!strcmp(list->Get_ItemInfo()->itemName, itemName))
		{
			return list->Get_ItemInfo()->quantity;
		}
	}
	return 0;
}

void CInventory_RectManager::Create(RECT pos)
{
	if (instance == nullptr)
	{
		instance = new CInventory_RectManager;
		instance->SetPos(pos);
		instance->Ready_GameObject();
	}
}
