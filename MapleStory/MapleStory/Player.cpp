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
	/*auto temp = CLoadData::Get_Instance()->Get_Map();
	auto& iter = find_if(temp->begin(), temp->end(), [&](auto pair){
		return !lstrcmp(L"Player1", pair.first);
	});
	m_currnet_pos.x = 100;
	m_currnet_pos.y = 100;

	m_hdc = iter->second->Get_memDC();*/
	m_speed = 2.f;

	return 0;
}

int CPlayer::Update_GameObject()
{
	//if (CKey_Manager::Get_Instance()->Key_Down(KEY_LEFT))
	if (GetAsyncKeyState(VK_LEFT) & 0x8000)
		m_currnet_pos.x -= m_speed;
	else if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
		m_currnet_pos.x += m_speed;
	else if (GetAsyncKeyState(VK_UP) & 0x8000)
		m_currnet_pos.y -= m_speed;
	else if (GetAsyncKeyState(VK_DOWN) & 0x8000)
		m_currnet_pos.y += m_speed;

	if (GetAsyncKeyState(VK_SPACE) & 0x8000)
		//m_bIsJumping = true;
	return 0;
}

void CPlayer::Late_Update_GameObject()
{
	float fY = 0.f;
	bool bCollLine= CLine_Manager::Get_Instance()->Collision_Line_Manager(m_currnet_pos.x, &fY);
	if (bCollLine)
		m_currnet_pos.y = fY;
}

void CPlayer::Render_GameObject(HDC hDC)
{
	if (m_hdc == nullptr)
		return;
	//GdiTransparentBlt(hDC, // �׸��� �����ϰ��� �ϴ� ���. 
	//	m_tRect.left,//��ġ x,y
	//	m_tRect.top,
	//	m_tInfo.iCX,// ũ�� xy
	//	m_tInfo.iCY,
	//	m_hdc,// ���� �� ���
	//	0, 0,// �׸��� ���� ��ġ x,y
	//	m_tInfo.iCX,// �׸����� �ϴ� ������ ũ�� x,y
	//	m_tInfo.iCY,
	//	RGB(255, 255, 255));

	BitBlt(hDC,// �����ϰ��� �ϴ� ��� 
		m_currnet_pos.x, m_currnet_pos.y,// �׸� ���� ��ġ
		WINCX, WINCY, // �׸��� ũ�� 
		m_hdc,//������ ��� 
		0, 0, //�׸������� ���� ��ġ 
		SRCCOPY); // �׸� ����. 
	


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
