#include "stdafx.h"
#include "Octopus.h"
#include "Bitmap_Manager.h"
#include "Line_Manager.h"
#include "GameObject_Manager.h"
#include "Meso.h"
#include "Drop_Octopus.h"
#include "Eilxir.h"

COctopus::COctopus()
{
}

COctopus::~COctopus()
{
}

int COctopus::Ready_GameObject()
{
	m_hdc = CBitmap_Manager::Get_Instance()->Get_memDC(L"Octopus");
	m_info.sizeX = 90;
	m_info.sizeY = 80;
	m_info.x = 300;
	m_info.y = 100;
	UpdateRect_GameObject();
	m_speed = 2.f;

	m_dir = Direction::DIR_RIGHT;
	m_state = Monster_State::STATE_NOHIT;

	m_isWalk = true;
	m_isHit = false;
	m_isFall = false;
	m_jumpSpeed = 5;

	m_animFrame.frame_start = 0;
	m_animFrame.frame_end = Octopus_Animation_Index::OCTOPUS_WALK_INDEX;
	m_animFrame.frame_animation = Octopus_Animation::OCTOPUS_WALK;
	m_animFrame.frame_speed = 500;
	m_animFrame.frame_time = GetTickCount();
	m_changeDirectionSpeed = 2000;
	m_changeDirectionTime = GetTickCount();
	m_changeStateTime = GetTickCount();
	m_changeStateSpeed = 5000;

	m_data.maxExp = 1000;
	m_data.exp = m_data.maxExp;
	m_data.maxHp = 3000;
	m_data.hp = m_data.maxHp;
	m_data.maxAttack = 200;
	m_data.minAttack = m_data.maxAttack;
	m_data.money = 1000;

	return READY_OK;
}

int COctopus::Update_GameObject()
{
	m_player = CGameObject_Manager::Get_Instance()->GetPlayer();
	if (m_isDead)
	{
		if (m_dir == Direction::DIR_LEFT)
		{
			Set_Animation(m_hdc, Octopus_Animation::OCTOPUS_DIE, Octopus_Animation_Index::OCTOPUS_DIE_INDEX);
		}
		else if (m_dir == Direction::DIR_RIGHT)
		{
			Set_Animation(m_hdc, Octopus_Animation::OCTOPUS_DIE, Octopus_Animation_Index::OCTOPUS_DIE_INDEX);
		}
		if (m_animFrame.frame_start >= m_animFrame.frame_end - 1)
			m_isDie = true;
	}
	if (m_isDie)
	{
		int temp = rand() % 10;
		if (temp > 7)
			CMeso::Create((float)m_info.x, (float)m_rect.top, m_data.money);
		else if (temp > 5)
			CDrop_Octopus::Create(m_info.x, (float)m_rect.top);
		else if (temp > 3)
			CEilxir::Create(m_info.x, (float)m_rect.top);
		return OBJ_DEAD;
	}

	if (m_changeStateTime + m_changeStateSpeed < GetTickCount())
	{
		if (m_state == Monster_State::STATE_NOHIT)
		{
			int num = rand() % 10;
			if (num >= 2)
				m_isWalk = true;
			else
				m_isWalk = false;
		}
		m_changeStateTime = GetTickCount();
	}

	if (!m_isDead)
	{
		if (m_changeDirectionTime + m_changeDirectionSpeed < GetTickCount())
		{
			int num = rand() % 2;
			if (num == 0)
				m_dir = Direction::DIR_LEFT;
			else
				m_dir = Direction::DIR_RIGHT;
			m_changeDirectionTime = GetTickCount();
		}

		if (m_isWalk && !m_isFall && !m_isSkillHit)
		{
			if (m_dir == Direction::DIR_LEFT)
				m_info.x -= m_speed;
			else if (m_dir == Direction::DIR_RIGHT)
				m_info.x += m_speed;
		}
		if (m_isSkillHit)
		{
			if (m_dir == Direction::DIR_LEFT)
			{
				Set_Animation(m_hdc, Octopus_Animation::OCTOPUS_HIT, Octopus_Animation_Index::OCTOPUS_HIT_INDEX);
			}
			else if (m_dir == Direction::DIR_RIGHT)
			{
				Set_Animation(m_hdc, Octopus_Animation::OCTOPUS_HIT, Octopus_Animation_Index::OCTOPUS_HIT_INDEX);
			}
		}

		if (!m_isSkillHit)
		{
			if (m_dir == Direction::DIR_LEFT)
			{
				Set_Animation(m_hdc, Octopus_Animation::OCTOPUS_WALK, Octopus_Animation_Index::OCTOPUS_WALK_INDEX);
			}
			else if (m_dir == Direction::DIR_RIGHT)
			{
				Set_Animation(m_hdc, Octopus_Animation::OCTOPUS_WALK, Octopus_Animation_Index::OCTOPUS_WALK_INDEX);
			}
		}
	}


	return 0;
}

void COctopus::Late_Update_GameObject()
{
	Play_Animation();
	if (m_rect.left <= m_minX)
		m_dir = Direction::DIR_RIGHT;
	else if (m_rect.right >= m_maxX)
		m_dir = Direction::DIR_LEFT;

	float fY = 0.f;
	bool bCollLine = CLine_Manager::Get_Instance()->Collision_Line_Manager(this, &fY);

	if (bCollLine)
	{
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

void COctopus::Release_GameObject()
{
}

CGameObject * COctopus::Create()
{
	CGameObject * instance = new COctopus;
	if (0 > instance->Ready_GameObject())
	{
		Safe_Delete(instance);
		instance = nullptr;
	}

	return instance;
}

void COctopus::Set_Animation(HDC hdc, Octopus_Animation animScene, Octopus_Animation_Index frameEnd)
{
	if (m_animFrame.frame_animation != animScene)
		m_animFrame.frame_start = 0;

	m_hdc = hdc;
	m_animFrame.frame_animation = animScene;
	m_animFrame.frame_end = frameEnd;
}
