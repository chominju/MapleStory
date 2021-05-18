#include "stdafx.h"
#include "Boss.h"
#include "GameObject_Manager.h"
#include "Bitmap_Manager.h"
#include "Line_Manager.h"
#include "Scroll_Manager.h"
#include "Scene_Manager.h"
CBoss::CBoss()
{
}

CBoss::~CBoss()
{
}

int CBoss::Ready_GameObject()
{
	m_left_hdc = CBitmap_Manager::Get_Instance()->Get_memDC(L"Boss_Left");
	m_right_hdc = CBitmap_Manager::Get_Instance()->Get_memDC(L"Boss_Right");

	m_hdc = m_left_hdc;

	m_dir = Direction::DIR_LEFT;

	m_info.x = 500;
	m_info.y = 530;
	m_info.sizeX = 130;
	m_info.sizeY = 161;

	m_speed = 3.f;
	UpdateRect_GameObject();


	m_animFrame.frame_start = 0;
	m_animFrame.frame_animation = Boss_Animation::Boss_STAND;
	m_animFrame.frame_end = Boss_Animation_Index::Boss_STAND_INDEX;
	m_animFrame.frame_speed = 500;
	m_animFrame.frame_time = GetTickCount();
	m_changeStateTime = GetTickCount();
	m_changeStateSpeed = 5000;

	m_Attack1Time = GetTickCount();
	m_Attack1Speed = 3000;
	m_Attack2Time = GetTickCount();
	m_Attack2Speed = 10000;
	m_Attack3Time = GetTickCount();
	m_Attack3Speed = 20000;
	m_Attack4Time = GetTickCount();
	m_Attack4Speed = 5000;



	m_data.maxExp = 1000000;
	m_data.exp = m_data.maxExp;
	m_data.maxHp = 100000;
	m_data.hp = m_data.maxHp;
	m_data.money = 1000000;
	m_data.maxAttack = 5000;
	m_data.minAttack = m_data.maxAttack;
	m_player = CGameObject_Manager::Get_Instance()->GetPlayer();

	return 0;
}

int CBoss::Update_GameObject()
{
	float fY;
	if (!m_isFall)
	{
		if (m_dir == Direction::DIR_LEFT)
		{
			m_info.x -= m_speed;
			Set_Animation(m_left_hdc, Boss_Animation::Boss_WALK, Boss_Animation_Index::Boss_WALK_INDEX);
		}
		else if (m_dir == Direction::DIR_RIGHT)
		{
			m_info.x += m_speed;
		}
	}

	return 0;
}

void CBoss::Late_Update_GameObject()
{
	Play_Animation();

	if (m_rect.left <= 5)
	{
		m_dir = Direction::DIR_RIGHT;
		m_hdc = m_right_hdc;
	}
	if (m_rect.right >= CScene_Manager::Get_Instance()->Get_SceneSize().x - 5)
	{
		m_dir = Direction::DIR_LEFT;
		m_hdc = m_left_hdc;
	}

	float fY = 0.f;
	bool bCollLine = CLine_Manager::Get_Instance()->Collision_Line_Manager(this, &fY);
	if (bCollLine)
	{
		fY += 10;
		if (abs(m_info.y - (fY - m_info.sizeY / 2)) >= 5)
		{
			m_isFall = true;
			m_info.y += m_speed;
		}
		else
		{
			m_info.y = fY - m_info.sizeY / 2;
			m_isFall = false;
		}
	}
}

void CBoss::Render_GameObject(HDC hDC)
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
		m_animFrame.frame_start*m_info.sizeX, m_animFrame.frame_animation * m_info.sizeY,// 그림의 시작 위치 x,y
		m_info.sizeX,// 그리고자 하는 영역의 크기 x,y
		m_info.sizeY,
		RGB(255, 0, 255));


	GdiTransparentBlt(hDC, // 그림을 복사하고자 하는 대상. 
		0,//위치 x,y
		0,
		WINCX,// 크기 xy
		10*3,
		m_hpBackBar_hdc,// 복사 할 대상
		0, 0,// 그림의 시작 위치 x,y
		182,// 그리고자 하는 영역의 크기 x,y
		21,
		RGB(255, 0, 255));



	GdiTransparentBlt(hDC, // 그림을 복사하고자 하는 대상. 
		0,//위치 x,y
		0,
		WINCX *(m_data.hp / m_data.maxHp),// 크기 xy
		10*3,
		m_hpBar_hdc,// 복사 할 대상
		0, 0,// 그림의 시작 위치 x,y
		182,// 그리고자 하는 영역의 크기 x,y
		21,
		RGB(255, 0, 255));
}

void CBoss::Release_GameObject()
{
}

void CBoss::UpdateRect_GameObject()
{
	m_rect.left = static_cast<LONG>(m_info.x - (m_info.sizeX / 2));
	m_rect.top = static_cast<LONG>(m_info.y - (m_info.sizeY / 2));
	m_rect.right = static_cast<LONG>(m_info.x + (m_info.sizeX / 2));
	m_rect.bottom = static_cast<LONG>(m_info.y + (m_info.sizeY / 2));
}

void CBoss::Set_Animation(HDC hdc, Boss_Animation animScene, Boss_Animation_Index frameEnd)
{
	if (m_animFrame.frame_animation != animScene)
		m_animFrame.frame_start = 0;

	m_hdc = hdc;
	m_animFrame.frame_animation = animScene;
	m_animFrame.frame_end = frameEnd;
}

CGameObject * CBoss::Create()
{
	CGameObject * instance = new CBoss;
	if (0 > instance->Ready_GameObject())
	{
		Safe_Delete(instance);
		instance = nullptr;
	}

	return instance;
}
