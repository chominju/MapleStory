#include "stdafx.h"
#include "Player.h"
#include "Key_Manager.h"
#include "LoadData.h"
#include "MyBitmap.h"
#include "Bitmap_Manager.h"
#include "Line_Manager.h"


CGameObject * CPlayer::m_instance = nullptr;

CPlayer::CPlayer()
	:m_power(0.f)
	, m_accel(0.f)
	, m_gravity(0.f)
	, m_isJump(false)
	, m_currentKey(NONE)

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
	m_speed = 2.f;

	UpdateRect_GameObject();

	return 0;
}

int CPlayer::Update_GameObject()
{
	//if (CKey_Manager::Get_Instance()->Key_Down(KEY_LEFT))
	if (GetAsyncKeyState(VK_LEFT) & 0x8000)
		m_info.x -= m_speed;
	else if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
		m_info.x += m_speed;
	else if (GetAsyncKeyState(VK_UP) & 0x8000)
		m_info.y -= m_speed;
	else if (GetAsyncKeyState(VK_DOWN) & 0x8000)
		m_info.y += m_speed;

	if (GetAsyncKeyState(VK_SPACE) & 0x8000)
		//m_bIsJumping = true;
	return 0;
}

void CPlayer::Late_Update_GameObject()
{
	float fY = 0.f;
	bool bCollLine= CLine_Manager::Get_Instance()->Collision_Line_Manager(m_info.x, &fY);
	if (bCollLine)
		m_info.y = fY - m_info.sizeY;
}

void CPlayer::Render_GameObject(HDC hDC)
{
	UpdateRect_GameObject();
	if (m_hdc == nullptr)
		return;
	GdiTransparentBlt(hDC, // 그림을 복사하고자 하는 대상. 
		m_info.x,//위치 x,y
		m_info.y,
		m_info.sizeX,// 크기 xy
		m_info.sizeY,
		m_hdc,// 복사 할 대상
		0, 0,// 그림의 시작 위치 x,y
		m_info.sizeX,// 그리고자 하는 영역의 크기 x,y
		m_info.sizeY,
		RGB(255, 255, 255));

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
	//m_rect.left = LONG(m_tInfo.fX - (m_tInfo.iCX >> 1));
	//m_rect.top = static_cast<LONG>(m_tInfo.fY - (m_tInfo.iCY >> 1));
	//m_rect.right = static_cast<LONG>(m_tInfo.fX + (m_tInfo.iCX * 0.5f));
	//m_rect.bottom = static_cast<LONG>(m_tInfo.fY + (m_tInfo.iCY / 2));
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
}
