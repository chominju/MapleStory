#include "stdafx.h"
#include "Player_Ui.h"
#include "GameObject_Manager.h"
#include "Bitmap_Manager.h"

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
	return S_OK;
}

int CPlayer_Ui::Update_GameObject()
{
	Set_UiData(CGameObject_Manager::Get_Instance()->GetPlayer()->Get_Data());
	return 0;
}

void CPlayer_Ui::Late_Update_GameObject()
{
}

void CPlayer_Ui::Render_GameObject(HDC hDC)
{
	// HP바

	GdiTransparentBlt(hDC, // 그림을 복사하고자 하는 대상. 
		1024 / 2 - 102,//위치 x,y
		768 - 54 - 10,
		204,// 크기 xy
		54,
		m_hpBackBar_hdc,// 복사 할 대상
		0, 0,// 그림의 시작 위치 x,y
		204,// 그리고자 하는 영역의 크기 x,y
		54,
		RGB(255, 0, 255));

	GdiTransparentBlt(hDC, // 그림을 복사하고자 하는 대상. 
		1024 / 2 - 79,//위치 x,y
		768 - 28 - 10,
		175 * (m_data.hp / m_data.maxHp),// 크기 xy
		17,
		m_hpBar_hdc,// 복사 할 대상
		0, 0,// 그림의 시작 위치 x,y
		175,// 그리고자 하는 영역의 크기 x,y
		17,
		RGB(255, 255, 255));


	// Lv.  << 출력
	GdiTransparentBlt(hDC, // 그림을 복사하고자 하는 대상. 
		1024 / 2 - 75,//위치 x,y
		768 - 10 - 47,
		15,// 크기 xy
		10,
		m_State_Lv_hdc,// 복사 할 대상
		0, 0,// 그림의 시작 위치 x,y
		15,// 그리고자 하는 영역의 크기 x,y
		10,
		RGB(255, 255, 255));

	// Lv. 숫자 출력
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

	for (int i = 0; i<num; i++)
	{
		int temp2 = temp % 10;
		GdiTransparentBlt(hDC, // 그림을 복사하고자 하는 대상. 
			1024 / 2 - 40 - (num / 2 + i) * 7,//위치 x,y
			768 - 10 - 47,
			7,// 크기 xy
			10,
			m_State_LvNum_hdc,// 복사 할 대상
			7 * temp2, 0,// 그림의 시작 위치 x,y
			7,// 그리고자 하는 영역의 크기 x,y
			10,
			RGB(255, 255, 255));
		temp /= 10;
		if (temp == 0)
			break;
	}


	// EXP바

	GdiTransparentBlt(hDC, // 그림을 복사하고자 하는 대상. 
		0,//위치 x,y
		768 - 10,
		1024,// 크기 xy
		10,
		m_expBackBar_hdc,// 복사 할 대상
		0, 0,// 그림의 시작 위치 x,y
		1024,// 그리고자 하는 영역의 크기 x,y
		10,
		RGB(255, 0, 255));

	GdiTransparentBlt(hDC, // 그림을 복사하고자 하는 대상. 
		0 + 15,//위치 x,y
		768 - 7,
		1008 * (m_data.exp / m_data.maxExp),// 크기 xy
		7,
		m_expBar_hdc,// 복사 할 대상
		0, 0,// 그림의 시작 위치 x,y
		1008,// 그리고자 하는 영역의 크기 x,y
		7,
		RGB(255, 255, 255));

	// key 바
		GdiTransparentBlt(hDC, // 그림을 복사하고자 하는 대상. 
			WINCX - 211,//위치 x,y
			WINCY - 73 -8,
			211,// 크기 xy
			73,
			m_skillKey,// 복사 할 대상
			0, 0,// 그림의 시작 위치 x,y
			211,// 그리고자 하는 영역의 크기 x,y
			73,
			RGB(255, 0, 255));




	// hp. 숫자 출력
	temp = m_data.hp;
	num = 0;
	temp3 = m_data.hp;
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
			1024 / 2 - 10 - (num / 2 + i) * 7,//위치 x,y
			768 - 10 - 25,
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

	GdiTransparentBlt(hDC, // 그림을 복사하고자 하는 대상. 
		1024 / 2 + 5,//위치 x,y
		768 - 10 - 25,
		7,// 크기 xy
		10,
		m_State_Num_hdc,// 복사 할 대상
		7 * 10, 0,// 그림의 시작 위치 x,y
		7,// 그리고자 하는 영역의 크기 x,y
		10,
		RGB(255, 0, 255));


	// MaxHp. 숫자 출력
	temp = m_data.maxHp;
	num = 0;
	temp3 = m_data.maxHp;
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
			1024 / 2 + 60 - (num / 2 + i) * 7,//위치 x,y
			768 - 10 - 25,
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


















	// exp. 숫자 출력
	temp = m_data.exp;
	num = 0;
	temp3 = m_data.exp;
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
			1024 / 2 - 40 - (num / 2 + i) * 7,//위치 x,y
			768 - 10,
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

	GdiTransparentBlt(hDC, // 그림을 복사하고자 하는 대상. 
		1024 / 2 + 5,//위치 x,y
		768 - 10,
		7,// 크기 xy
		10,
		m_State_Num_hdc,// 복사 할 대상
		7 * 10, 0,// 그림의 시작 위치 x,y
		7,// 그리고자 하는 영역의 크기 x,y
		10,
		RGB(255, 0, 255));


	// MaxHp. 숫자 출력
	temp = m_data.maxExp;
	num = 0;
	temp3 = m_data.maxExp;
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
			1024 / 2 + 60 - (num / 2 + i) * 7,//위치 x,y
			768 - 10,
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
