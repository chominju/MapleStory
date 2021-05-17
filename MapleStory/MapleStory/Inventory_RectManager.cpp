#include "stdafx.h"
#include "Inventory_RectManager.h"
#include "Item.h"
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

}

void CInventory_RectManager::Push_ConsumeList(CItem * item)
{
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

void CInventory_RectManager::Create(RECT pos)
{
	if (instance == nullptr)
	{
		instance = new CInventory_RectManager;
		instance->SetPos(pos);
		instance->Ready_GameObject();
	}
}
