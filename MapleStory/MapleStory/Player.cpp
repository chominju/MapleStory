#include "stdafx.h"
#include "Player.h"
#include "Key_Manager.h"
#include "LoadData.h"
#include "MyBitmap.h"
#include "Bitmap_Manager.h"
#include "Line_Manager.h"
#include "Scroll_Manager.h"
#include "Scene_Manager.h"


CGameObject * CPlayer::m_instance = nullptr;

CPlayer::CPlayer()
	: m_isJump(false)
	, m_power(0.f)
	, current_jumpHeight(0)
	, m_currentKey(CurrentKey::RIGHT)

{
	ZeroMemory(&m_player_info, sizeof(Player_Info));
}

CPlayer::~CPlayer()
{
}

int CPlayer::Ready_GameObject()
{
	m_hdc = CBitmap_Manager::Get_Instance()->Get_memDC(L"Player1");
	m_info.sizeX =  CBitmap_Manager::Get_Instance()->Get_Image_Size(L"Player1").x;
	m_info.sizeY = CBitmap_Manager::Get_Instance()->Get_Image_Size(L"Player1").y;

	m_info.x = 100;
	m_info.y = 100;
	/*auto temp = CLoadData::Get_Instance()->Get_Map();
	auto& iter = find_if(temp->begin(), temp->end(), [&](auto pair){
		return !lstrcmp(L"Player1", pair.first);
	});
	m_currnet_pos.x = 100;
	m_currnet_pos.y = 100;

	m_hdc = iter->second->Get_memDC();*/
	m_speed = 3.f;
	jumpHeight = 100;
	m_power = 5;
	fall = 5;
	UpdateRect_GameObject();

	return 0;
}

int CPlayer::Update_GameObject()
{
	//if (CKey_Manager::Get_Instance()->Key_Down(KEY_LEFT))
	if (GetAsyncKeyState(VK_LEFT) & 0x8000)
	{
		if (m_rect.left >= 0)
		{
			m_currentKey = CurrentKey::LEFT;
			m_info.x -= m_speed;
			if (m_info.x - WINCX / 2 >= 0)
				if (m_info.x + CScroll_Manager::Get_ScrollX() < WINCX / 2)
					CScroll_Manager::Set_ScrollX(m_speed);
			/*else
				CScroll_Manager::Set_ResetX();*/
		}
	}
	else if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
	{
		if (m_rect.right <= CScene_Manager::Get_Instance()->Get_SceneSize().x)
		{
			m_currentKey = CurrentKey::RIGHT;
			m_info.x += m_speed;
			//CScene_Manager::Get_Instance()->Get_SceneSize().x
			if (m_info.x >= WINCX / 2 && m_info.x + WINCX / 2 < CScene_Manager::Get_Instance()->Get_SceneSize().x)
				CScroll_Manager::Set_ScrollX(-m_speed);
			/*	else
					CScroll_Manager::Set_ResetX();*/
		}
	}
	else if (GetAsyncKeyState(VK_UP) & 0x8000)
	{
		/*m_info.y -= m_speed;
		if (m_info.y <= WINCY / 2 - CScroll_Manager::Get_ScrollY())
			CScroll_Manager::Set_ScrollY(-m_speed);*/
	}
	if (CKey_Manager::Get_Instance()->Key_Pressing(KEY_DOWN))
	{
		if (CKey_Manager::Get_Instance()->Key_Pressing(KEY_C))
		{
			m_info.y += 5;
			float fY = 0.f;
			bool bCollLine = CLine_Manager::Get_Instance()->Floor_Collision_Line_Manager_Line_Manager(this);
			if (!bCollLine)
				m_info.y -= 3;
			// m_info.sizeY;
		}
	/*	m_info.y += m_speed;
		if (m_info.y >= WINCY / 2 + CScroll_Manager::Get_ScrollY())
			CScroll_Manager::Set_ScrollY(+m_speed);*/
	}

	if (GetAsyncKeyState(VK_SPACE) & 0x8000)
	{
		m_info.y--;
	}

	if (CKey_Manager::Get_Instance()->Key_Pressing(KEY_C))
	{
		if (!CKey_Manager::Get_Instance()->Key_Pressing(KEY_DOWN))
		{
			if (!m_isJump)
			{
				jump_before = m_info.y;
				m_isJump = true;

			}
		}
	}
	return 0;
}

void CPlayer::Late_Update_GameObject()
{
	IsJump();
}

void CPlayer::Render_GameObject(HDC hDC)
{
	UpdateRect_GameObject();
	if (m_hdc == nullptr)
		return;

	int scrollX = CScroll_Manager::Get_ScrollX();
	int scrollY = CScroll_Manager::Get_ScrollY();

	GdiTransparentBlt(hDC, // 그림을 복사하고자 하는 대상. 
		m_rect.left+ scrollX,//위치 x,y
		m_rect.top+ scrollY,
		m_info.sizeX,// 크기 xy
		m_info.sizeY,
		m_hdc,// 복사 할 대상
		0, 0,// 그림의 시작 위치 x,y
		m_info.sizeX,// 그리고자 하는 영역의 크기 x,y
		m_info.sizeY,
		RGB(255, 255, 255));

	//GdiTransparentBlt(hDC, // 그림을 복사하고자 하는 대상. 
	//	m_info.x,//위치 x,y
	//	m_info.y,
	//	m_info.sizeX,// 크기 xy
	//	m_info.sizeY,
	//	m_hdc,// 복사 할 대상
	//	0, 0,// 그림의 시작 위치 x,y
	//	m_info.sizeX,// 그리고자 하는 영역의 크기 x,y
	//	m_info.sizeY,
	//	RGB(255, 255, 255));

	//BitBlt(hDC,// 복사하고자 하는 대상 
	//	m_info.x, m_info.y,// 그릴 시작 위치
	//	WINCX, WINCY, // 그림의 크기 
	//	m_hdc,//복사할 대상 
	//	0, 0, //그림에서의 시작 위치 
	//	SRCCOPY); // 그릴 형식. 
	


}

void CPlayer::Release_GameObject()
{
}

void CPlayer::UpdateRect_GameObject()
{
	m_rect.left = static_cast<LONG>(m_info.x - (m_info.sizeX / 2));
	m_rect.top = static_cast<LONG>(m_info.y - (m_info.sizeY / 2));
	m_rect.right = static_cast<LONG>(m_info.x + (m_info.sizeX / 2));
	m_rect.bottom = static_cast<LONG>(m_info.y + (m_info.sizeY / 2));
}

CGameObject * CPlayer::Create()
{
	if (nullptr == m_instance)
	{
		m_instance = new CPlayer;
		if (nullptr == m_instance)
		{
			Safe_Delete(m_instance);
			m_instance = nullptr;
			return m_instance;
		}

		m_instance->Ready_GameObject();
	}

	return m_instance;
}

void CPlayer::IsJump()
{
	float fY = 0.f;
	bool bCollLine = CLine_Manager::Get_Instance()->Collision_Line_Manager(this,m_info.x, m_rect.bottom/*m_info.y + m_info.sizeY / 2*/, &fY, m_currentKey);
	if (m_isJump)
	{
		if (current_jumpHeight <= jumpHeight)
		{
			m_info.y -= m_power;
			current_jumpHeight += m_power;
		}
		else if (bCollLine)
		{
			if (abs(m_info.y - (fY - m_info.sizeY / 2)) >= 5)
				m_info.y += fall;
			else
			{
				m_info.y = fY - m_info.sizeY / 2;
				current_jumpHeight = 0;
				m_isJump = false;
			}
		}

		/*if (bCollLine && (current_jumpHeight<=0))
		{
			m_isJump = false;
			m_power *= -1;
			current_jumpHeight = 0;
		}
		else if (bCollLine && (m_rect.bottom >= fY &&m_power < 0))
		{
			m_isJump = false;
			m_power *= -1;
			current_jumpHeight = 0;
		}*/
	}
	else if (bCollLine)
	{
		if (abs(m_info.y - (fY - m_info.sizeY / 2)) >= 5)
			m_info.y += fall;
		else
			m_info.y = fY - m_info.sizeY / 2;
	}
}
