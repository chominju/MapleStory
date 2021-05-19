#include "stdafx.h"
#include "Boss_Attack2_Ball.h"
#include "Bitmap_Manager.h"
#include "GameObject_Manager.h"
#include "Scene_Manager.h"
#include "Monster.h"
#include "Scroll_Manager.h"
CGameObject* CBoss_Attack2_Ball::m_instance = nullptr;

CBoss_Attack2_Ball::CBoss_Attack2_Ball()
{
}

CBoss_Attack2_Ball::~CBoss_Attack2_Ball()
{
	m_instance = nullptr;
}

int CBoss_Attack2_Ball::Ready_GameObject()
{
	m_hdc = CBitmap_Manager::Get_Instance()->Get_memDC(L"Boss_Attack2_Ball");

	m_info.sizeX = 137;
	m_info.sizeY = 50;

	dir = dynamic_cast<CMonster*>(m_target)->Get_Direction();

	if (dir == Direction::DIR_LEFT)
	{
		m_info.x = m_target->GetRect()->left - m_info.sizeX / 2 + 85;
		m_animFrame.frame_animation = 0;
	}
	else if (dir == Direction::DIR_RIGHT)
	{
		m_info.x = m_target->GetRect()->right + m_info.sizeX / 2 - 85;
		m_animFrame.frame_animation = 1;
	}
	m_info.y = m_target->Get_Info()->y +30;
	m_animFrame.frame_start = 0;
	m_animFrame.frame_end = 4;
	m_animFrame.frame_speed = 100;
	m_animFrame.frame_time = GetTickCount();
	UpdateRect_GameObject();
	m_damage = 2000;
	m_hitMonsterNum = 99;
	m_hitNum = 1;
	return 0;
}

int CBoss_Attack2_Ball::Update_GameObject()
{
	if(m_rect.right <=0 || m_rect.left >=CScene_Manager::Get_Instance()->Get_SceneSize().x)
		Set_IsDead();

	if (m_isDead)
		return OBJ_DEAD;

	Play_Animation();

	return OBJ_NOEVENT;
}

void CBoss_Attack2_Ball::Late_Update_GameObject()
{
	if (dir == Direction::DIR_LEFT)
		m_info.x -= 5;

	if (dir == Direction::DIR_RIGHT)
		m_info.x += 5;
}

void CBoss_Attack2_Ball::Render_GameObject(HDC hDC)
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
		RGB(255, 0, 255));
}

void CBoss_Attack2_Ball::Play_Animation()
{
	if (m_animFrame.frame_time + m_animFrame.frame_speed < GetTickCount())
	{
		++m_animFrame.frame_start;
		m_animFrame.frame_time = GetTickCount();
		if (m_animFrame.frame_start >= m_animFrame.frame_end)
			m_animFrame.frame_start = 0;
	}
}

CGameObject * CBoss_Attack2_Ball::Create(CGameObject * boss)
{
	if (nullptr == m_instance)
	{
		m_instance = new CBoss_Attack2_Ball;
		m_instance->Set_Target(boss);
		m_instance->Ready_GameObject();
		CGameObject_Manager::Get_Instance()->Add_GameObject_Manager(Object_ID::BOSS_SKILL, m_instance);
	}

	return m_instance;
}
