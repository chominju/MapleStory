#include "stdafx.h"
#include "Inventory_Ui.h"
#include "GameObject_Manager.h"
#include "Bitmap_Manager.h"
#include "Player.h"

CGameObject* CInventory_Ui::instance=nullptr;

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
	m_info.x = 450;
	m_info.y = 200;
	m_info.sizeX = 185;
	m_info.sizeY = 351;
	return 0;
}

int CInventory_Ui::Update_GameObject()
{
	m_player = CGameObject_Manager::Get_Instance()->GetPlayer();
	Set_UiData(m_player->Get_Data());
	return 0;
}

void CInventory_Ui::Late_Update_GameObject()
{
}

void CInventory_Ui::Render_GameObject(HDC hDC)
{
	UpdateRect_GameObject();
	if (dynamic_cast<CPlayer*>(m_player)->Get_IsInventoryOpen())
	{
		GdiTransparentBlt(hDC, // �׸��� �����ϰ��� �ϴ� ���. 
			m_rect.left,//��ġ x,y
			m_rect.top,
			m_info.sizeX,// ũ�� xy
			m_info.sizeY,
			m_hdc,// ���� �� ���
			0, 0,// �׸��� ���� ��ġ x,y
			m_info.sizeX,// �׸����� �ϴ� ������ ũ�� x,y
			m_info.sizeY,
			RGB(255, 0, 255));
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
