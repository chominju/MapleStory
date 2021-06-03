#include "stdafx.h"
#include "Clock.h"
#include "Bitmap_Manager.h"
#include "GameObject_Manager.h"
#include "Scene_Manager.h"
#include "Scroll_Manager.h"

CClock::CClock()
{
}


CClock::~CClock()
{
}

int CClock::Ready_GameObject()
{
	int num = rand() % 10;
	if (num >=8) // ����
	{
		m_hdc = CBitmap_Manager::Get_Instance()->Get_memDC(L"Boss_Purple_Clock");
		m_info.sizeX = 167;
		m_info.sizeY = 164;
		m_damage = 7;
		m_clockNum = 1;
	}
	else if (num >=5)	// �Ķ��
	{
		m_hdc = CBitmap_Manager::Get_Instance()->Get_memDC(L"Boss_Blue_Clock");
		m_info.sizeX = 108;
		m_info.sizeY = 107;
		m_damage = 3;
		m_clockNum = 2;
	}
	else	// �ʷϿ
	{
		m_hdc = CBitmap_Manager::Get_Instance()->Get_memDC(L"Boss_Green_Clock");
		m_info.sizeX = 63;
		m_info.sizeY = 63;
		m_damage = 1;
		m_clockNum = 3;
	}

	m_die_hdc= CBitmap_Manager::Get_Instance()->Get_memDC(L"Clock_Die");

	m_speed = (float)(rand() % 6 + 2);
	m_info.x = (float)(rand() % CScene_Manager::Get_Instance()->Get_SceneSize().x);
	m_info.y = (float)(-m_info.sizeY/2);

	m_animFrame.frame_start = 0;
	m_animFrame.frame_end = 6;
	m_animFrame.frame_speed = 100;
	m_animFrame.frame_time = GetTickCount();
	UpdateRect_GameObject();
	m_hitMonsterNum = 99;
	m_hitNum = 1;
	m_isDeadAnimation = false;
	return 0;
}

int CClock::Update_GameObject()
{
	if (m_isDead&&!m_isDeadAnimation)
	{
		m_animFrame.frame_start = 0;
		m_animFrame.frame_end = 7;
		m_info.sizeX = 272;
		m_info.sizeY = 207;
		m_hdc = m_die_hdc;
		m_isDeadAnimation = true;
		if (m_clockNum == 1)
			m_info.y -= 30;
		else if (m_clockNum == 2)
			m_info.y -= 60;
		else if (m_clockNum == 3)
			m_info.y -= 80;
	}
	if (m_isDeadAnimation)
	{
		if (m_animFrame.frame_start >= m_animFrame.frame_end - 1)
		{
			return OBJ_DEAD;
		}
	}
	if (!m_isDead)
		m_info.y += m_speed;

	Play_Animation();
	return 0;
}

void CClock::Late_Update_GameObject()
{
	if (m_rect.bottom >= 628)
		Set_IsDead();
}

void CClock::Render_GameObject(HDC hDC)
{
	UpdateRect_GameObject();
	int scrollX = CScroll_Manager::Get_ScrollX();
	int scrollY = CScroll_Manager::Get_ScrollY();
	GdiTransparentBlt(hDC, // �׸��� �����ϰ��� �ϴ� ���. 
		m_rect.left + scrollX,//��ġ x,y
		m_rect.top + scrollY,
		m_info.sizeX,// ũ�� xy
		m_info.sizeY,
		m_hdc,// ���� �� ���
		m_animFrame.frame_start * m_info.sizeX,0,// �׸��� ���� ��ġ x,y
		m_info.sizeX,// �׸����� �ϴ� ������ ũ�� x,y
		m_info.sizeY,
		RGB(255, 255, 255));
}

void CClock::Play_Animation()
{
	if (m_animFrame.frame_time + m_animFrame.frame_speed < GetTickCount())
	{
		++m_animFrame.frame_start;
		m_animFrame.frame_time = GetTickCount();
		if (m_animFrame.frame_start >= m_animFrame.frame_end)
			m_animFrame.frame_start = 0;
	}
}

CGameObject * CClock::Create()
{
	CGameObject * instance = new CClock;
	instance->Ready_GameObject();
	CGameObject_Manager::Get_Instance()->Add_GameObject_Manager(Object_ID::BOSS_SKILL, instance);

	return instance;
}
