#include "stdafx.h"
#include "Player_StatUi.h"
#include "GameObject_Manager.h"
#include "Bitmap_Manager.h"
#include "Player.h"

CGameObject* CPlayer_StatUi::instance = nullptr;

CPlayer_StatUi::CPlayer_StatUi()
{
}


CPlayer_StatUi::~CPlayer_StatUi()
{
}

int CPlayer_StatUi::Ready_GameObject()
{
	m_hdc= CBitmap_Manager::Get_Instance()->Get_memDC(L"Stat_Main");
	m_State_Num_hdc = CBitmap_Manager::Get_Instance()->Get_memDC(L"State_Num");
	m_info.x = 750;
	m_info.y = 200;
	m_info.sizeX = 212;
	m_info.sizeY = 336;
	return S_OK;
}

int CPlayer_StatUi::Update_GameObject()
{
	m_player = CGameObject_Manager::Get_Instance()->GetPlayer();
	Set_UiData(m_player->Get_Data());

	return 0;
}

void CPlayer_StatUi::Late_Update_GameObject()
{
}

void CPlayer_StatUi::Render_GameObject(HDC hDC)
{
	UpdateRect_GameObject();
	if (dynamic_cast<CPlayer*>(m_player)->Get_IsStatOpen())
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

		int temp = m_data.minAttack;
		int num = 0;
		int temp3 = m_data.minAttack;
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
				m_rect.left + 140 - (num / 2 + i) * 7,//위치 x,y+ i) * 7,//위치 x,y
				m_rect.top + 102,
				7,// 크기 xy
				10,
				m_State_Num_hdc,// 복사 할 대상
				7 * temp2, 0,// 그림의 시작 위치 x,y
				7,// 그리고자 하는 영역의 크기 x,y
				10,
				RGB(255,0 , 255));
			temp /= 10;
			if (temp == 0)
				break;
		}

		temp = m_data.maxAttack;
		num = 0;
		temp3 = m_data.maxAttack;
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
				m_rect.left + 140 - (num / 2 + i) * 7,//위치 x,y+ i) * 7,//위치 x,y
				m_rect.top + 120,
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


		// hp 표시

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
				m_rect.left + 130 - (num / 2 + i) * 7, //위치 x,y
				m_rect.top + 138,
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
			m_rect.left + 135,
			m_rect.top + 138,
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
				m_rect.left + 190 - (num / 2 + i) * 7,
				m_rect.top + 138,
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

void CPlayer_StatUi::Release_GameObject()
{
}


CGameObject * CPlayer_StatUi::Create()
{
	if (instance == nullptr)
	{
		instance = new CPlayer_StatUi;
		if (0 > instance->Ready_GameObject())
		{
			Safe_Delete(instance);
			instance = nullptr;
		}
		CGameObject_Manager::Get_Instance()->Add_GameObject_Manager(Object_ID::UI, instance);
	}
	return instance;
}
