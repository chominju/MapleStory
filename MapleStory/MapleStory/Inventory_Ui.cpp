#include "stdafx.h"
#include "Inventory_Ui.h"
#include "GameObject_Manager.h"
#include "Bitmap_Manager.h"
#include "Player.h"
#include "Inventory_Button.h"
#include "Inventory_RectManager.h"
#include "Item.h"
#include "Key_Manager.h"
#include "Item.h"
#include <algorithm>


CGameObject* CInventory_Ui::instance = nullptr;

CInventory_Ui::CInventory_Ui()
{
}


CInventory_Ui::~CInventory_Ui()
{
}

int CInventory_Ui::Ready_GameObject()
{
	m_hdc = CBitmap_Manager::Get_Instance()->Get_memDC(L"Inventory_Ui");
	m_State_Num_hdc = CBitmap_Manager::Get_Instance()->Get_memDC(L"State_Num");
	m_info.x = 900;
	m_info.y = 500;
	m_info.sizeX = 185;
	m_info.sizeY = 351;
	UpdateRect_GameObject();

	m_EquipmentButton = CInventory_Button::Create();
	m_EquipmentButton->Set_Pos(m_rect.left + 20, m_rect.top + 15);
	dynamic_cast<CInventory_Button*>(m_EquipmentButton)->Set_FrameKey(L"Inventory_Equipment_Button");

	m_ConsumeButton = CInventory_Button::Create();
	m_ConsumeButton->Set_Pos(m_rect.left + 60, m_rect.top + 15);
	dynamic_cast<CInventory_Button*>(m_ConsumeButton)->Set_FrameKey(L"Inventory_Consume_Button");

	m_EtcButton = CInventory_Button::Create();
	m_EtcButton->Set_Pos(m_rect.left + 100, m_rect.top + 15);
	dynamic_cast<CInventory_Button*>(m_EtcButton)->Set_FrameKey(L"Inventory_Etc_Button");

	CInventory_RectManager::Create(m_rect);

	return 0;
}

int CInventory_Ui::Update_GameObject()
{
	m_player = CGameObject_Manager::Get_Instance()->GetPlayer();
	Set_UiData(m_player->Get_Data());

	//if (!dynamic_cast<CPlayer*>(CGameObject_Manager::Get_Instance()->GetPlayer())->Get_IsShopClick())
	//{
		if (dynamic_cast<CPlayer*>(m_player)->Get_IsInventoryOpen())
		{
			POINT pt = {};
			GetCursorPos(&pt);
			ScreenToClient(g_hwnd, &pt);
			list<CItem*>* getList = CInventory_RectManager::Get_Instance()->Get_CurrentList();

			for (list<CItem*>::iterator iter = getList->begin(); iter != getList->end(); iter++)
			{
				//for (auto& list : *getList)
				//{
				if (PtInRect((*iter)->GetRect(), pt))
				{
					if (!m_isItemMove)
					{
						if (CKey_Manager::Get_Instance()->Key_Up(KEY_RBUTTON))
						{
							CInventory_RectManager::Get_Instance()->Use_Item((*iter)->Get_ItemInfo()->itemName);
						}

						if (CKey_Manager::Get_Instance()->Key_Up(KEY_LBUTTON))
						{
							temp = (*iter);
							m_beforePos = *(*iter)->Get_Info();
							beforeIter = iter;
							m_isItemMove = true;
						}
					}
					else
					{
						if (beforeIter != iter)
						{
							if (CKey_Manager::Get_Instance()->Key_Up(KEY_LBUTTON))
							{
								getList->empty();
								Object_Info temp2 = *(*iter)->Get_Info();
								iter_swap(beforeIter, iter);
								getList->empty();
								(*iter)->Set_Pos(temp2.x, temp2.y);
								(*beforeIter)->Set_Pos(m_beforePos.x, m_beforePos.y);
								/*Object_Info m_afterInfo = *(*iter)->Get_Info();
								temp->Set_Pos(m_afterInfo.x, m_afterInfo.y);
								list->Set_Pos(m_beforePos.x, m_beforePos.y);*/
								m_isItemMove = false;

								temp = nullptr;
							}
						}
					}
				}
			}
			if (m_isItemMove)
			{
				temp->Set_Pos(pt.x, pt.y);

				if (!PtInRect(&m_rect, pt))
				{
					if (CKey_Manager::Get_Instance()->Key_Up(KEY_LBUTTON))
					{
						CInventory_RectManager::Get_Instance()->Drop_Item(temp->Get_ItemInfo()->itemName, m_beforePos);
						CSoundMgr::Get_Instance()->PlaySound(L"DropItem.mp3", CSoundMgr::PLAYER);
						m_isItemMove = false;
						temp = nullptr;
					}
				}
			}
		//}
	}
	return 0;
}

void CInventory_Ui::Late_Update_GameObject()
{
	m_EquipmentButton->Late_Update_GameObject();
	m_ConsumeButton->Late_Update_GameObject();
	m_EtcButton->Late_Update_GameObject();
	CInventory_RectManager::Get_Instance()->Set_isEquipmentClick(dynamic_cast<CInventory_Button*>(m_EquipmentButton)->Get_IsEquipmentClick());
	CInventory_RectManager::Get_Instance()->Set_isConsumeClick(dynamic_cast<CInventory_Button*>(m_ConsumeButton)->Get_IsConsumeClick());
	CInventory_RectManager::Get_Instance()->Set_m_isEtcClick(dynamic_cast<CInventory_Button*>(m_EtcButton)->Get_IsEtcClick());
}

void CInventory_Ui::Render_GameObject(HDC hDC)
{
	UpdateRect_GameObject();
	if (dynamic_cast<CPlayer*>(m_player)->Get_IsInventoryOpen())
	{
		GdiTransparentBlt(hDC, // 그림을 복사하고자 하는 대상. 
			m_rect.left,//위치 x,y
			m_rect.top,
			m_info.sizeX,// 크기 xy
			m_info.sizeY,
			m_hdc,// 복사 할 대상
			0, 0,// 그림의 시작 위치 x,y
			m_info.sizeX,// 그리고자 하는 영역의 크기 x,y
			m_info.sizeY,
			RGB(255, 0, 255));

		m_EquipmentButton->Render_GameObject(hDC);
		m_ConsumeButton->Render_GameObject(hDC);
		m_EtcButton->Render_GameObject(hDC);

		CInventory_RectManager::Get_Instance()->Render_GameObject(hDC);

		// 돈 출력
		int temp = m_data.money;
		int num = 0;
		int temp3 = m_data.money;
		while (true)
		{
			num++;
			temp3 /= 10;
			if (temp3 == 0)
				break;
		}

		for (int i = 0; i < num; i++)
		{
			int temp2 = temp % 10;
			GdiTransparentBlt(hDC, // 그림을 복사하고자 하는 대상. 
				m_rect.left + 120 - (num / 2 + i) * 7,//위치 x,y+ i) * 7,//위치 x,y
				m_rect.bottom - 62,
				7,// 크기 xy
				10,
				m_State_Num_hdc,// 복사 할 대상
				7 * temp2, 0,// 그림의 시작 위치 x,y
				7,// 그리고자 하는 영역의 크기 x,y
				10,
				RGB(255, 0, 255));
			temp /= 10;
			if (temp == 0)
				break;
		}
	}
}

void CInventory_Ui::Release_GameObject()
{
}

CGameObject * CInventory_Ui::Create()
{
	if (instance == nullptr)
	{
		instance = new CInventory_Ui;
		if (0 > instance->Ready_GameObject())
		{
			Safe_Delete(instance);
			instance = nullptr;
		}
		CGameObject_Manager::Get_Instance()->Add_GameObject_Manager(Object_ID::UI, instance);
	}
	return instance;
}
