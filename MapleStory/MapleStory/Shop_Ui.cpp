#include "stdafx.h"
#include "Shop_Ui.h"
#include "GameObject_Manager.h"
#include "Bitmap_Manager.h"
#include "Player.h"
#include "Inventory_Button.h"
#include "Npc.h"
#include "Close_Button.h"
#include "Shop_RectManager.h"
#include "Key_Manager.h"
#include "Item.h"


CGameObject* CShop_Ui::instance = nullptr;

CShop_Ui::CShop_Ui()
{
}

CShop_Ui::~CShop_Ui()
{
	instance = nullptr;
}

int CShop_Ui::Ready_GameObject()
{
	m_hdc = CBitmap_Manager::Get_Instance()->Get_memDC(L"Shop_Ui");
	m_State_Num_hdc = CBitmap_Manager::Get_Instance()->Get_memDC(L"State_Num");

	m_info.x = 300;
	m_info.y = 300;
	m_info.sizeX = 465;
	m_info.sizeY = 328;
	UpdateRect_GameObject();

	m_EquipmentButton = CInventory_Button::Create();
	m_EquipmentButton->Set_Pos((float)m_rect.left + 270, (float)m_rect.top + 100);
	dynamic_cast<CInventory_Button*>(m_EquipmentButton)->Set_FrameKey(L"Inventory_Equipment_Button");

	m_ConsumeButton = CInventory_Button::Create();
	m_ConsumeButton->Set_Pos((float)m_rect.left + 310, (float)m_rect.top + 100);
	dynamic_cast<CInventory_Button*>(m_ConsumeButton)->Set_FrameKey(L"Inventory_Consume_Button");

	m_EtcButton = CInventory_Button::Create();
	m_EtcButton->Set_Pos((float)m_rect.left + 350, (float)m_rect.top + 100);
	dynamic_cast<CInventory_Button*>(m_EtcButton)->Set_FrameKey(L"Inventory_Etc_Button");

	m_CloseButton = CClose_Button::Create();
	m_CloseButton->Set_Pos((float)m_rect.left + 180, (float)m_rect.top + 70);
	dynamic_cast<CClose_Button*>(m_CloseButton)->Set_FrameKey(L"Close_Ui");

	CShop_RectManager::Create(m_rect);
	CShop_RectManager::Get_Instance()->Set_isEquipmentClick(dynamic_cast<CInventory_Button*>(m_EquipmentButton)->Get_IsEquipmentClick());
	CShop_RectManager::Get_Instance()->Set_isConsumeClick(dynamic_cast<CInventory_Button*>(m_ConsumeButton)->Get_IsConsumeClick());
	CShop_RectManager::Get_Instance()->Set_m_isEtcClick(dynamic_cast<CInventory_Button*>(m_EtcButton)->Get_IsEtcClick());
	return 0;
}

int CShop_Ui::Update_GameObject()
{
	if (dynamic_cast<CNpc*>(m_target)->Get_isNpcClick())
	{
		m_player = CGameObject_Manager::Get_Instance()->GetPlayer();
		CShop_RectManager::Get_Instance()->Update_GameObject();

		POINT pt = {};
		GetCursorPos(&pt);
		ScreenToClient(g_hwnd, &pt);
		list<CItem*>* getList = CShop_RectManager::Get_Instance()->Get_CurrentList();
		for (list<CItem*>::iterator iter = getList->begin(); iter != getList->end(); iter++)
		{
			if (PtInRect((*iter)->Get_ShopRect(), pt))
			{
				if (CKey_Manager::Get_Instance()->Key_Up(KEY_RBUTTON))
				{
					CShop_RectManager::Get_Instance()->SellItem((*iter)->Get_ItemInfo()->itemName, (*iter));
				}
			}
		}



		POINT pt2 = {};
		GetCursorPos(&pt2);
		ScreenToClient(g_hwnd, &pt2);
		list<CItem*>* shopList = CShop_RectManager::Get_Instance()->Get_ShopList();
		for (list<CItem*>::iterator iter = shopList->begin(); iter != shopList->end(); iter++)
		{
			if (PtInRect((*iter)->Get_ShopRect(), pt2))
			{
				if (CKey_Manager::Get_Instance()->Key_Up(KEY_RBUTTON))
				{
					CShop_RectManager::Get_Instance()->BuyItem((*iter));
				}
			}
		}

	}

	if (dynamic_cast<CClose_Button*>(m_CloseButton)->Get_isCloseButton())
	{
		dynamic_cast<CClose_Button*>(m_CloseButton)->Set_isCloseButton(false);
		dynamic_cast<CNpc*>(m_target)->Set_isNpcClick(false);
		dynamic_cast<CPlayer*>(CGameObject_Manager::Get_Instance()->GetPlayer())->Set_IsShopClick(false);
		CShop_RectManager::Get_Instance()->Release_GameObject();
		return OBJ_DEAD;
	}

	return 0;
}

void CShop_Ui::Late_Update_GameObject()
{
	if (dynamic_cast<CNpc*>(m_target)->Get_isNpcClick())
	{
		m_EquipmentButton->Late_Update_GameObject();
		m_ConsumeButton->Late_Update_GameObject();
		m_EtcButton->Late_Update_GameObject();
		m_CloseButton->Late_Update_GameObject();
		CShop_RectManager::Get_Instance()->Set_isEquipmentClick(dynamic_cast<CInventory_Button*>(m_EquipmentButton)->Get_IsEquipmentClick());
		CShop_RectManager::Get_Instance()->Set_isConsumeClick(dynamic_cast<CInventory_Button*>(m_ConsumeButton)->Get_IsConsumeClick());
		CShop_RectManager::Get_Instance()->Set_m_isEtcClick(dynamic_cast<CInventory_Button*>(m_EtcButton)->Get_IsEtcClick());
	}
}

void CShop_Ui::Render_GameObject(HDC hDC)
{
	if (dynamic_cast<CNpc*>(m_target)->Get_isNpcClick())
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
		m_CloseButton->Render_GameObject(hDC);

		CShop_RectManager::Get_Instance()->Render_GameObject(hDC);


		int temp = m_player->Get_Data()->money;
		int num = 0;
		int temp3 = m_player->Get_Data()->money;
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
				m_rect.right - 30 - 5 - i * 7,//위치 x,y+ i) * 7,//위치 x,y
				m_rect.top + 64,
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

void CShop_Ui::Release_GameObject()
{
}

CGameObject * CShop_Ui::Create(CGameObject * npc)
{
	if (instance == nullptr)
	{
		instance = new CShop_Ui;
		if (0 > instance->Ready_GameObject())
		{
			Safe_Delete(instance);
			instance = nullptr;
		}
		instance->Set_Target(npc);
		CGameObject_Manager::Get_Instance()->Add_GameObject_Manager(Object_ID::UI, instance);
	}
	return instance;
}
