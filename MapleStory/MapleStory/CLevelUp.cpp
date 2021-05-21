#include "stdafx.h"
#include "CLevelUp.h"
#include "Bitmap_Manager.h"
#include "Player.h"
#include "GameObject_Manager.h"
#include "Scroll_Manager.h"

CLevelUp::CLevelUp()
{
}

CLevelUp::~CLevelUp()
{
}

int CLevelUp::Ready_GameObject()
{
	m_hdc = CBitmap_Manager::Get_Instance()->Get_memDC(L"LevelUp");
	m_info.sizeX = 904;
	m_info.sizeY = 904;

	m_info.x = m_target->Get_Info()->x;
	m_info.y = m_target->Get_Info()->y;

	m_animFrame.frame_animation = 0;
	m_animFrame.frame_start = 0;
	m_animFrame.frame_end = 21;
	m_animFrame.frame_speed = 100;
	m_animFrame.frame_time = GetTickCount();

	m_damage = 99999;
	m_hitMonsterNum = 100;
	m_hitNum = 1;

	return S_OK;
}

int CLevelUp::Update_GameObject()
{
	Set_Target(CGameObject_Manager::Get_Instance()->GetPlayer());
	m_info.x = m_target->Get_Info()->x;
	m_info.y = m_target->Get_Info()->y - 250;
	Play_Animation();
	if (m_isDead)
		return OBJ_DEAD;

	return OBJ_NOEVENT;
}

void CLevelUp::Late_Update_GameObject()
{
}

void CLevelUp::Render_GameObject(HDC hDC)
{
	UpdateRect_GameObject();
	int scrollX = CScroll_Manager::Get_ScrollX();
	int scrollY = CScroll_Manager::Get_ScrollY();
	GdiTransparentBlt(hDC, // 그림을 복사하고자 하는 대상. 
		m_rect.left + scrollX,//위치 x,y
		m_rect.top + scrollY,
		m_info.sizeX,// 크기 xy
		m_info.sizeY,
		m_hdc,// 복사 할 대상
		m_animFrame.frame_start * m_info.sizeX, m_animFrame.frame_animation * m_info.sizeY,// 그림의 시작 위치 x,y
		m_info.sizeX,// 그리고자 하는 영역의 크기 x,y
		m_info.sizeY,
		RGB(255, 255, 224));
}

void CLevelUp::Release_GameObject()
{
}

void CLevelUp::UpdateRect_GameObject()
{
	m_rect.left = static_cast<LONG>(m_info.x - (m_info.sizeX / 2));
	m_rect.top = static_cast<LONG>(m_info.y - (m_info.sizeY / 2));
	m_rect.right = static_cast<LONG>(m_info.x + (m_info.sizeX / 2));
	m_rect.bottom = static_cast<LONG>(m_info.y + (m_info.sizeY / 2));
}

//void CLevelUp::Play_Animation()
//{
//	if (m_animFrame.frame_time + m_animFrame.frame_speed < GetTickCount())
//	{
//		++m_animFrame.frame_start;
//		m_animFrame.frame_time = GetTickCount();
//		if (m_animFrame.frame_start >= m_animFrame.frame_end)
//			Set_IsDead();
//	}
//}

CGameObject * CLevelUp::Create(CGameObject * player)
{
	CGameObject* instance = new CLevelUp;
	instance->Set_Target(player);
	instance->Ready_GameObject();
	CGameObject_Manager::Get_Instance()->Add_GameObject_Manager(Object_ID::ATTACK_SKILL, instance);
	CSoundMgr::Get_Instance()->PlaySound(L"LevelUp.mp3", CSoundMgr::PLAYER);
	return nullptr;
}
