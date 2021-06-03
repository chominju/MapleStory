#include "stdafx.h"
#include "Player_Ui.h"
#include "GameObject_Manager.h"
#include "Bitmap_Manager.h"
#include "Player_Die_Button.h"
#include "Inventory_RectManager.h"

CGameObject * CPlayer_Ui::instance = nullptr;
CPlayer_Ui::CPlayer_Ui()
{
}


CPlayer_Ui::~CPlayer_Ui()
{
}

int CPlayer_Ui::Ready_GameObject()
{
	m_hpBar_hdc = CBitmap_Manager::Get_Instance()->Get_memDC(L"Player_Hp_Bar");
	m_hpBackBar_hdc = CBitmap_Manager::Get_Instance()->Get_memDC(L"Player_Hp_BackBar");
	m_expBar_hdc = CBitmap_Manager::Get_Instance()->Get_memDC(L"Player_Exp_Bar");
	m_expBackBar_hdc = CBitmap_Manager::Get_Instance()->Get_memDC(L"Player_Exp_BackBar");
	m_State_Lv_hdc = CBitmap_Manager::Get_Instance()->Get_memDC(L"State_Lv");
	m_State_LvNum_hdc = CBitmap_Manager::Get_Instance()->Get_memDC(L"State_LvNum");
	m_State_Num_hdc = CBitmap_Manager::Get_Instance()->Get_memDC(L"State_Num");
	m_skillKey = CBitmap_Manager::Get_Instance()->Get_memDC(L"Skill_Key");
	m_playerDie_Message_hdc = CBitmap_Manager::Get_Instance()->Get_memDC(L"Die_Message");

	m_Player_Die_Button = Player_Die_Button::Create();
	m_Player_Die_Button->Set_Pos((float)m_rect.left + 20, (float)m_rect.top + 15);
	dynamic_cast<Player_Die_Button*>(m_Player_Die_Button)->Set_FrameKey(L"Player_Die_Message_Button");

	
	return READY_OK;
}

int CPlayer_Ui::Update_GameObject()
{
	Set_UiData(CGameObject_Manager::Get_Instance()->GetPlayer()->Get_Data());
	return 0;
}

void CPlayer_Ui::Late_Update_GameObject()
{
	m_Player_Die_Button->Late_Update_GameObject();
}

void CPlayer_Ui::Render_GameObject(HDC hDC)
{
	// HP��

	GdiTransparentBlt(hDC, // �׸��� �����ϰ��� �ϴ� ���. 
		1024 / 2 - 102,//��ġ x,y
		768 - 54 - 10,
		204,// ũ�� xy
		54,
		m_hpBackBar_hdc,// ���� �� ���
		0, 0,// �׸��� ���� ��ġ x,y
		204,// �׸����� �ϴ� ������ ũ�� x,y
		54,
		RGB(255, 0, 255));

	GdiTransparentBlt(hDC, // �׸��� �����ϰ��� �ϴ� ���. 
		1024 / 2 - 76,//��ġ x,y
		768 - 28 - 7,
		(int)(169 * (m_data.hp / m_data.maxHp)),// ũ�� xy
		11,
		m_hpBar_hdc,// ���� �� ���
		0, 0,// �׸��� ���� ��ġ x,y
		169,// �׸����� �ϴ� ������ ũ�� x,y
		11,
		RGB(255, 255, 255));


	// Lv.  << ���
	GdiTransparentBlt(hDC, // �׸��� �����ϰ��� �ϴ� ���. 
		1024 / 2 - 75,//��ġ x,y
		768 - 10 - 47,
		15,// ũ�� xy
		10,
		m_State_Lv_hdc,// ���� �� ���
		0, 0,// �׸��� ���� ��ġ x,y
		15,// �׸����� �ϴ� ������ ũ�� x,y
		10,
		RGB(255, 255, 255));

	// Lv. ���� ���
	int temp = m_data.level;
	int num = 0;
	int temp3 = m_data.level;
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
		GdiTransparentBlt(hDC, // �׸��� �����ϰ��� �ϴ� ���. 
			1024 / 2 - 40 - (num / 2 + i) * 7,//��ġ x,y
			768 - 10 - 47,
			7,// ũ�� xy
			10,
			m_State_LvNum_hdc,// ���� �� ���
			7 * temp2, 0,// �׸��� ���� ��ġ x,y
			7,// �׸����� �ϴ� ������ ũ�� x,y
			10,
			RGB(255, 255, 255));
		temp /= 10;
		if (temp == 0)
			break;
	}


	// EXP��

	GdiTransparentBlt(hDC, // �׸��� �����ϰ��� �ϴ� ���. 
		0,//��ġ x,y
		768 - 10,
		1024,// ũ�� xy
		10,
		m_expBackBar_hdc,// ���� �� ���
		0, 0,// �׸��� ���� ��ġ x,y
		1024,// �׸����� �ϴ� ������ ũ�� x,y
		10,
		RGB(255, 0, 255));

	GdiTransparentBlt(hDC, // �׸��� �����ϰ��� �ϴ� ���. 
		0 + 15,//��ġ x,y
		768 - 7,
		(int)(1008 * (m_data.exp / m_data.maxExp)),// ũ�� xy
		7,
		m_expBar_hdc,// ���� �� ���
		0, 0,// �׸��� ���� ��ġ x,y
		1008,// �׸����� �ϴ� ������ ũ�� x,y
		7,
		RGB(255, 255, 255));


	// hp. ���� ���
	temp = (int)m_data.hp;
	num = 0;
	temp3 = (int)m_data.hp;
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
		GdiTransparentBlt(hDC, // �׸��� �����ϰ��� �ϴ� ���. 
			1024 / 2 - 10 - (num / 2 + i) * 7,//��ġ x,y
			768 - 10 - 25,
			7,// ũ�� xy
			10,
			m_State_Num_hdc,// ���� �� ���
			7 * temp2, 0,// �׸��� ���� ��ġ x,y
			7,// �׸����� �ϴ� ������ ũ�� x,y
			10,
			RGB(255, 0, 255));
		temp /= 10;
		if (temp == 0)
			break;
	}

	GdiTransparentBlt(hDC, // �׸��� �����ϰ��� �ϴ� ���. 
		1024 / 2 + 5,//��ġ x,y
		768 - 10 - 25,
		7,// ũ�� xy
		10,
		m_State_Num_hdc,// ���� �� ���
		7 * 10, 0,// �׸��� ���� ��ġ x,y
		7,// �׸����� �ϴ� ������ ũ�� x,y
		10,
		RGB(255, 0, 255));


	// MaxHp. ���� ���
	temp = (int)m_data.maxHp;
	num = 0;
	temp3 = (int)m_data.maxHp;
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
		GdiTransparentBlt(hDC, // �׸��� �����ϰ��� �ϴ� ���. 
			1024 / 2 + 60 - (num / 2 + i) * 7,//��ġ x,y
			768 - 10 - 25,
			7,// ũ�� xy
			10,
			m_State_Num_hdc,// ���� �� ���
			7 * temp2, 0,// �׸��� ���� ��ġ x,y
			7,// �׸����� �ϴ� ������ ũ�� x,y
			10,
			RGB(255, 0, 255));
		temp /= 10;
		if (temp == 0)
			break;
	}




	// exp. ���� ���
	temp = (int)m_data.exp;
	num = 0;
	temp3 = (int)m_data.exp;
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
		GdiTransparentBlt(hDC, // �׸��� �����ϰ��� �ϴ� ���. 
			1024 / 2 - 40 - (num / 2 + i) * 7,//��ġ x,y
			768 - 10,
			7,// ũ�� xy
			10,
			m_State_Num_hdc,// ���� �� ���
			7 * temp2, 0,// �׸��� ���� ��ġ x,y
			7,// �׸����� �ϴ� ������ ũ�� x,y
			10,
			RGB(255, 0, 255));
		temp /= 10;
		if (temp == 0)
			break;
	}

	GdiTransparentBlt(hDC, // �׸��� �����ϰ��� �ϴ� ���. 
		1024 / 2 + 5,//��ġ x,y
		768 - 10,
		7,// ũ�� xy
		10,
		m_State_Num_hdc,// ���� �� ���
		7 * 10, 0,// �׸��� ���� ��ġ x,y
		7,// �׸����� �ϴ� ������ ũ�� x,y
		10,
		RGB(255, 0, 255));


	// MaxHp. ���� ���
	temp = (int)m_data.maxExp;
	num = 0;
	temp3 = (int)m_data.maxExp;
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
		GdiTransparentBlt(hDC, // �׸��� �����ϰ��� �ϴ� ���. 
			1024 / 2 + 60 - (num / 2 + i) * 7,//��ġ x,y
			768 - 10,
			7,// ũ�� xy
			10,
			m_State_Num_hdc,// ���� �� ���
			7 * temp2, 0,// �׸��� ���� ��ġ x,y
			7,// �׸����� �ϴ� ������ ũ�� x,y
			10,
			RGB(255, 0, 255));
		temp /= 10;
		if (temp == 0)
			break;
	}



	// key ��
	GdiTransparentBlt(hDC, // �׸��� �����ϰ��� �ϴ� ���. 
		WINCX - 176,//��ġ x,y
		WINCY - 71 - 8,
		176,// ũ�� xy
		71,
		m_skillKey,// ���� �� ���
		0, 0,// �׸��� ���� ��ġ x,y
		176,// �׸����� �ϴ� ������ ũ�� x,y
		71,
		RGB(255, 0, 255));


	// ��������. ���� ���
	temp = CInventory_RectManager::Get_Instance()->Get_ItemQuantity("���� ����");
	num = 0;
	temp3 = temp;
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
		GdiTransparentBlt(hDC, // �׸��� �����ϰ��� �ϴ� ���. 
			WINCX - 176 + 27 - (num / 2 + i) * 7,//��ġ x,y
			WINCY - 71 - 8 + 23,
			7,// ũ�� xy
			10,
			m_State_Num_hdc,// ���� �� ���
			7 * temp2, 0,// �׸��� ���� ��ġ x,y
			7,// �׸����� �ϴ� ������ ũ�� x,y
			10,
			RGB(255, 0, 255));
		temp /= 10;
		if (temp == 0)
			break;
	}

	// ������. ���� ���
	temp = CInventory_RectManager::Get_Instance()->Get_ItemQuantity("������");
	num = 0;
	temp3 = temp;
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
		GdiTransparentBlt(hDC, // �׸��� �����ϰ��� �ϴ� ���. 
			WINCX - 176 + 62 - (num / 2 + i) * 7,//��ġ x,y
			WINCY - 71 - 8 + 23,
			7,// ũ�� xy
			10,
			m_State_Num_hdc,// ���� �� ���
			7 * temp2, 0,// �׸��� ���� ��ġ x,y
			7,// �׸����� �ϴ� ������ ũ�� x,y
			10,
			RGB(255, 0, 255));
		temp /= 10;
		if (temp == 0)
			break;
	}


	// �Ŀ� ������. ���� ���
	temp = CInventory_RectManager::Get_Instance()->Get_ItemQuantity("�Ŀ� ������");
	num = 0;
	temp3 = temp;
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
		GdiTransparentBlt(hDC, // �׸��� �����ϰ��� �ϴ� ���. 
			WINCX - 176 + 97 - (num / 2 + i) * 7,//��ġ x,y
			WINCY - 71 - 8 + 23,
			7,// ũ�� xy
			10,
			m_State_Num_hdc,// ���� �� ���
			7 * temp2, 0,// �׸��� ���� ��ġ x,y
			7,// �׸����� �ϴ� ������ ũ�� x,y
			10,
			RGB(255, 0, 255));
		temp /= 10;
		if (temp == 0)
			break;
	}





	if (m_data.hp <= 0)
	{
		GdiTransparentBlt(hDC, // �׸��� �����ϰ��� �ϴ� ���. 
			WINCX /2-170,//��ġ x,y
			WINCY/2 -100,
			405,// ũ�� xy
			155,
			m_playerDie_Message_hdc,// ���� �� ���
			0,0,// �׸��� ���� ��ġ x,y
			405,// �׸����� �ϴ� ������ ũ�� x,y
			155,
			RGB(255, 0, 255));

		m_Player_Die_Button->Render_GameObject(hDC);
	}
}

void CPlayer_Ui::Release_GameObject()
{
}


CGameObject * CPlayer_Ui::Create()
{
	if (instance == nullptr)
	{
		instance = new CPlayer_Ui;
		if (0 > instance->Ready_GameObject())
		{
			Safe_Delete(instance);
			instance = nullptr;
		}
		CGameObject_Manager::Get_Instance()->Add_GameObject_Manager(Object_ID::UI, instance);
	}
	return instance;
}
