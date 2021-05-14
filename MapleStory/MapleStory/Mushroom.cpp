#include "stdafx.h"
#include "Mushroom.h"
#include "GameObject.h"
#include "Bitmap_Manager.h"

CMushroom::CMushroom()
{
}

CMushroom::~CMushroom()
{
}

int CMushroom::Ready_GameObject()
{
	m_left_hdc = CBitmap_Manager::Get_Instance()->Get_memDC(L"Mushroom_Left");
	m_right_hdc = CBitmap_Manager::Get_Instance()->Get_memDC(L"Mushroom_Right");
	m_hpBar_hdc= CBitmap_Manager::Get_Instance()->Get_memDC(L"Monster_Hp_Bar");
	m_hpBackBar_hdc= CBitmap_Manager::Get_Instance()->Get_memDC(L"Monster_Hp_BackBar");
	m_hdc = m_right_hdc;
	m_info.x = 300;
	m_info.y = 100;
	m_info.sizeX = 65;
	m_info.sizeY = 65;

	m_speed = 2.f;
	UpdateRect_GameObject();

	m_dir = Direction::DIR_RIGHT;
	m_state = Monster_State::STATE_NOHIT;

	m_isWalk = true;
	m_isHit = false;
	m_jumpHeight=100;
	m_currentHeight=0;
	m_jumpSpeed = 5;

	m_changeStateTime=GetTickCount();
	m_changeStateSpeed=3000;

	m_animFrame.frame_start = 0;
	m_animFrame.frame_end = Mushroom_Animation_Index::MUSHROOM_WALK_INDEX;
	m_animFrame.frame_animation = Mushroom_Animation::MUSHROOM_WALK;
	m_animFrame.frame_speed =500;
	m_animFrame.frame_time = GetTickCount();
	m_changeDirectionSpeed = 2000;
	m_changeDirectionTime = GetTickCount();
	return S_OK;
}

int CMushroom::Update_GameObject()
{
	if (m_changeStateTime + m_changeStateSpeed < GetTickCount())
	{
		if (m_state == Monster_State::STATE_NOHIT)
		{
			int num = rand() % 10;
			if (num >= 4)
			{
				m_isJump = false;
				m_isWalk = true;
				if (m_dir == Direction::DIR_LEFT)
					Set_Animation(m_left_hdc, Mushroom_Animation::MUSHROOM_WALK, Mushroom_Animation_Index::MUSHROOM_WALK_INDEX);
				else if (m_dir == Direction::DIR_RIGHT)
					Set_Animation(m_right_hdc, Mushroom_Animation::MUSHROOM_WALK, Mushroom_Animation_Index::MUSHROOM_WALK_INDEX);

				m_animFrame.frame_speed = 300;
			}
			else if (num >= 1)
			{
				m_isJump = false;
				m_isWalk = false;
				if (m_dir == Direction::DIR_LEFT)
					Set_Animation(m_left_hdc, Mushroom_Animation::MUSHROOM_STAND, Mushroom_Animation_Index::MUSHROOM_STAND_INDEX);
				else if (m_dir == Direction::DIR_RIGHT)
					Set_Animation(m_right_hdc, Mushroom_Animation::MUSHROOM_STAND, Mushroom_Animation_Index::MUSHROOM_STAND_INDEX);
				m_animFrame.frame_speed = 300;
			}
			else
			{
				m_isJump = true;
				if (m_dir == Direction::DIR_LEFT)
					Set_Animation(m_left_hdc, Mushroom_Animation::MUSHROOM_JUMP, Mushroom_Animation_Index::MUSHROOM_JUMP_INDEX);
				else if (m_dir == Direction::DIR_RIGHT)
					Set_Animation(m_right_hdc, Mushroom_Animation::MUSHROOM_JUMP, Mushroom_Animation_Index::MUSHROOM_JUMP_INDEX);
				m_animFrame.frame_speed = 1000;
			}
		}
		m_changeStateTime = GetTickCount();
	}
	
	if (m_changeDirectionTime + m_changeDirectionSpeed < GetTickCount())
	{
		int num = rand() % 2;
		if (num == 0)
		{
			m_dir = Direction::DIR_LEFT;
			m_hdc = m_left_hdc;
		}
		else
		{
			m_dir = Direction::DIR_RIGHT;
			m_hdc = m_right_hdc;
		}
		m_changeDirectionTime = GetTickCount();
	}

	if (m_isJump)
	{
		if (m_currentHeight < 0)
			m_currentHeight++;
		else
		{
			if (m_currentHeight < m_jumpHeight)
				m_info.y -= m_jumpSpeed;
			else
			{
				if (m_currentHeight < m_jumpHeight * 2)
					m_info.y += m_jumpSpeed;
				else
					m_currentHeight = -20;
			}
			m_currentHeight += m_jumpSpeed;
		}
	}

	if (m_isWalk)
	{
		if (m_dir == Direction::DIR_LEFT)
			m_info.x -= m_speed;
		else if (m_dir == Direction::DIR_RIGHT)
			m_info.x += m_speed;
	}

	return 0;
}

void CMushroom::Late_Update_GameObject()
{
	Play_Animation();
	if (m_info.x <= 100)
	{
		m_dir = Direction::DIR_RIGHT;
		m_hdc = m_right_hdc;
	}
	else if (m_info.x >= 700)
	{
		m_dir = Direction::DIR_LEFT;
		m_hdc = m_left_hdc;
	}
}

void CMushroom::Release_GameObject()
{
}

CGameObject * CMushroom::Create()
{
	CGameObject * instance = new CMushroom;
	if (0 > instance->Ready_GameObject())
	{
		Safe_Delete(instance);
		instance = nullptr;
	}

	return instance;
}


void CMushroom::Set_Animation(HDC hdc, Mushroom_Animation animScene, Mushroom_Animation_Index frameEnd)
{
	if (m_animFrame.frame_animation != animScene)
		m_animFrame.frame_start = 0;

	m_hdc = hdc;
	m_animFrame.frame_animation = animScene;
	m_animFrame.frame_end = frameEnd;
}
