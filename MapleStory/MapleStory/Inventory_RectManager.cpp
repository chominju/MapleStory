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

	//Object_Info temp;
	CItem* temp;
	//temp.sizeX = 33;
	//temp.sizeY = 33;
	for (int i = 0; i < 6; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			temp = new CItem;
			temp->Set_Size(33, 33);
			//temp.x = m_info.x +30 + 40 * j;
			//temp.y = m_info.y +50+ 40 * i;

			temp->Set_Pos(m_info.x + 30 + 40 * j, m_info.y + 50 + 40 * i);

			//m_info.x += 40 * j;
			//m_info.y += 40 * i;
			m_equipmentList.push_back(temp);
		}
	}

	for (int i = 0; i < 6; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			temp = new CItem;
			temp->Set_Size(33, 33);
			//temp.x = m_info.x +30 + 40 * j;
			//temp.y = m_info.y +50+ 40 * i;

			temp->Set_Pos(m_info.x + 30 + 40 * j, m_info.y + 50 + 40 * i);

			//m_info.x += 40 * j;
			//m_info.y += 40 * i;
			m_consumeList.push_back(temp);
		}
	}

	for (int i = 0; i < 6; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			temp = new CItem;
			temp->Set_Size(33, 33);
			//temp.x = m_info.x +30 + 40 * j;
			//temp.y = m_info.y +50+ 40 * i;

			temp->Set_Pos(m_info.x + 30 + 40 * j, m_info.y + 50 + 40 * i);

			//m_info.x += 40 * j;
			//m_info.y += 40 * i;
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
	RECT rc;
	//list<Object_Info> tempList;
	list<CItem*> tempList;
	if (m_isEquipmentClick)
		tempList = m_equipmentList;
	if (m_isConsumeClick)
		tempList = m_consumeList;
	if (m_isEtcClick)
		tempList = m_etcList;
	for (auto& list : tempList)
	{
		//Rectangle(hDC, rc.left, rc.top, rc.right, rc.bottom);
		list->Render_GameObject(hDC);
		//if (list->Get_ItemInfo()->itemName != "NONE")
		//{
		//	int temp2 = m_printDamageNum;
		//	for (int i = 0; i < printNum; i++)
		//	{
		//		int temp = temp2 % 10;
		//		temp2 /= 10;
		//		GdiTransparentBlt(hDC, // 그림을 복사하고자 하는 대상. 
		//			(m_rect.left + scrollX) + m_info.sizeX*(printNum / 2 - i),//위치 x,y
		//			m_rect.top + scrollY,
		//			m_info.sizeX,// 크기 xy
		//			m_info.sizeY,
		//			m_hdc,// 복사 할 대상
		//			temp * m_info.sizeX, 0,// 그림의 시작 위치 x,y
		//			m_info.sizeX,// 그리고자 하는 영역의 크기 x,y
		//			m_info.sizeY,
		//			RGB(255, 0, 255));
		//	}
		//}
		//rc.left = static_cast<LONG>(list.x - (list.sizeX / 2));
		//rc.top = static_cast<LONG>(list.y - (list.sizeY / 2));
		//rc.right = static_cast<LONG>(list.x + (list.sizeX / 2));
		//rc.bottom = static_cast<LONG>(list.y + (list.sizeY / 2));

	}
}

void CInventory_RectManager::Release_GameObject()
{
}

void CInventory_RectManager::UpdateRect_GameObject()
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

void CInventory_RectManager::Find_EquipmentList(char * itemName)
{

}

void CInventory_RectManager::Find_ConsumeList(char * itemName)
{
}

void CInventory_RectManager::Find_EtcList(char * itemName)
{
}

void CInventory_RectManager::Use_Item(char * itemName , CItem*& useItem)
{
	if (m_isEquipmentClick)
	{
		//for (auto & list : m_equipmentList)
		//{
		//	if (!strcmp(list->Get_ItemInfo()->itemName, itemName) && strcmp(itemName, "NONE"))
		//	{
		//		CPlayer *getPlayer = dynamic_cast<CPlayer*>(CGameObject_Manager::Get_Instance()->GetPlayer());
		//		if (getPlayer->Get_Weapon() == nullptr)
		//		{
		//			// 장착 장비가 없을 때
		//			int invenPosX = list->Get_Info()->x;
		//			int invenPosY = list->Get_Info()->y;
		//			list->Set_ItemPlace(Item_Place::EQUIPMENT_ITEM);
		//			getPlayer->Set_Weapon(list);
		//			list = new CItem();
		//			list->Set_Size(33, 33);
		//			list->Set_Pos(invenPosX, invenPosY);
		//		}
		//		else
		//		{
		//			int invenPosX = list->Get_Info()->x;
		//			int invenPosY = list->Get_Info()->y;
		//			Pos_float shop_pos = list->Get_shopPos();
		//			CItem* getWeapon = getPlayer->Get_Weapon();
		//			list->Set_ItemPlace(Item_Place::EQUIPMENT_ITEM);
		//			getPlayer->Set_Weapon(list);

		//			getWeapon->Set_ItemPlace(Item_Place::INVENTORY_ITEM);
		//			getWeapon->Set_Pos(invenPosX, invenPosY);
		//			getWeapon->Set_shopPos(shop_pos.x, shop_pos.y);
		//			list = getWeapon;
		//		}
		//	}
		//}
		if (!strcmp(useItem->Get_ItemInfo()->itemName, itemName) && strcmp(itemName, "NONE"))
		{
			CPlayer *getPlayer = dynamic_cast<CPlayer*>(CGameObject_Manager::Get_Instance()->GetPlayer());
			if (getPlayer->Get_Weapon() == nullptr)
			{
				// 장착 장비가 없을 때
				int invenPosX = useItem->Get_Info()->x;
				int invenPosY = useItem->Get_Info()->y;
				useItem->Set_ItemPlace(Item_Place::EQUIPMENT_ITEM);
				getPlayer->Set_Weapon(useItem);
				useItem = new CItem();
				useItem->Set_Size(33, 33);
				useItem->Set_Pos(invenPosX, invenPosY);
			}
			else
			{
				int invenPosX = useItem->Get_Info()->x;
				int invenPosY = useItem->Get_Info()->y;
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
		for (auto & list : m_consumeList)
		{
			if (!strcmp(list->Get_ItemInfo()->itemName, itemName) && strcmp(itemName, "NONE"))
			{
				CGameObject_Manager::Get_Instance()->GetPlayer()->Set_Change_Hp(list->Get_ItemInfoHp());
				list->Set_Change_Quantity(-1);
				CSoundMgr::Get_Instance()->PlaySound(L"Potion_Use.mp3", CSoundMgr::PLAYER);
				if (list->Get_ItemInfo()->quantity == 0)
				{
					if (dynamic_cast<CPlayer*>(CGameObject_Manager::Get_Instance()->GetPlayer())->Get_IsShopClick())
						CShop_RectManager::Get_Instance()->Find_DeleteItem(itemName);
					Object_Info tempInfo = *list->Get_Info();
					CItem * temp = new CItem;
					temp->Set_Pos(tempInfo.x, tempInfo.y);
					temp->Set_Size(tempInfo.sizeX, tempInfo.sizeY);

					Safe_Delete(list);
					list = temp;
					if (dynamic_cast<CPlayer*>(CGameObject_Manager::Get_Instance()->GetPlayer())->Get_IsShopClick())
						CShop_RectManager::Get_Instance()->DeleteItem(list);
					int i;
					i = 10;
				}
			}
		}
		if (m_isEtcClick)
		{
			//m_etcList
		}
	}
}

void CInventory_RectManager::Drop_Item(char * itemName , Object_Info pos)
{
	RECT rc;
	//list<Object_Info> tempList;
	list<CItem*>* tempList;
	if (m_isEquipmentClick)
		tempList = &m_equipmentList;
	else if (m_isConsumeClick)
		tempList = &m_consumeList;
	else if (m_isEtcClick)
		tempList = &m_etcList;
	else
		return;
	for (auto& list : *tempList)
	{
		if (!strcmp(list->Get_ItemInfo()->itemName, itemName))
		{
			//CGameObject_Manager::Get_Instance()->Add_GameObject_Manager(Object_ID::DROP_ITEM , )
			list->Set_Change_Quantity(-1);
			if (!strcmp(itemName,"빨간 포션"))
				CGameObject * item = CRed_Potion::Create(CGameObject_Manager::Get_Instance()->GetPlayer()->Get_Info()->x, CGameObject_Manager::Get_Instance()->GetPlayer()->Get_Info()->y);
			else if (!strcmp(itemName, "엘릭서"))
				CGameObject * item = CEilxir::Create(CGameObject_Manager::Get_Instance()->GetPlayer()->Get_Info()->x, CGameObject_Manager::Get_Instance()->GetPlayer()->Get_Info()->y);
			else if (!strcmp(itemName, "파워 엘릭서"))
			{
				/*	CGameObject * item = CPower_Elixir::Create();
					item->Set_Pos(CGameObject_Manager::Get_Instance()->GetPlayer()->Get_Info()->x, CGameObject_Manager::Get_Instance()->GetPlayer()->Get_Info()->y);
					CGameObject_Manager::Get_Instance()->Add_GameObject_Manager(Object_ID::DROP_ITEM, item);*/
			}
			else if (!strcmp(itemName, "옥토퍼스 다리"))
				CGameObject * item = CDrop_Octopus::Create(CGameObject_Manager::Get_Instance()->GetPlayer()->Get_Info()->x, CGameObject_Manager::Get_Instance()->GetPlayer()->Get_Info()->y);
			else if (!strcmp(itemName, "주황버섯 갓"))
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
				int i;
				i = 10;
			}
			else
				list->Set_Pos(pos.x, pos.y);

		}
	}
}

void CInventory_RectManager::Find_DeleteItem(char * itemName)
{
	list<CItem*>* tempList = Get_CurrentList();
	for (list<CItem*>::iterator iter = tempList->begin(); iter != tempList->end(); iter++)
	{
		if (!strcmp((*iter)->Get_ItemInfo()->itemName, itemName))
		{
			m_deleteIter = iter;
			m_deleteItemPos = *(*iter)->Get_Info();
		}
	}
}

void CInventory_RectManager::DeleteItem(CItem * item, Pos_float shopPos)
{
	m_consumeList.empty();
	//*m_deleteIter = item;
	//Safe_Delete(m_deleteIter);
	*m_deleteIter = nullptr;
	*m_deleteIter = new CItem();
	(*m_deleteIter)->Set_Pos(m_deleteItemPos.x, m_deleteItemPos.y);
	(*m_deleteIter)->Set_Size(m_deleteItemPos.sizeX, m_deleteItemPos.sizeY);
	(*m_deleteIter)->Set_shopPos(shopPos.x, shopPos.y);
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
