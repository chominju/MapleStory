#include "stdafx.h"
#include "Mushroom.h"
#include "GameObject.h"
#include "Bitmap_Manager.h"
#include "Line_Manager.h"
#include "GameObject_Manager.h"
#include "Meso.h"
#include "Drop_Mushroom.h"
#include "Red_Potion.h"
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
	//m_hpBar_hdc= CBitmap_Manager::Get_Instance()->Get_memDC(L"Monster_Hp_Bar");
	//m_hpBackBar_hdc= CBitmap_Manager::Get_Instance()->Get_memDC(L"Monster_Hp_BackBar");
	m_hdc = m_right_hdc;
	m_info.x = 300;
	m_info.y = 100;
	m_info.sizeX = 65;
	m_info.sizeY = 65;

	m_speed = 3.f;
	UpdateRect_GameObject();

	int temp = rand() % 2;
	if (temp == 0)
		m_dir = Direction::DIR_RIGHT;
	else
		m_dir = Direction::DIR_LEFT;


	m_isWalk = true;
	m_isHit = false;
	m_isFall = false;
	m_jumpHeight = 80;
	m_currentHeight = 0;
	m_jumpSpeed = 5;
	m_power = 15;
	m_accel = 0;
	m_power = 5;

	m_changeStateTime = GetTickCount();
	m_changeStateSpeed = 5000;
	m_state = Monster_State::STATE_NOHIT;

	m_animFrame.frame_start = 0;
	m_animFrame.frame_end = Mushroom_Animation_Index::MUSHROOM_WALK_INDEX;
	m_animFrame.frame_animation = Mushroom_Animation::MUSHROOM_WALK;
	m_animFrame.frame_speed = 500;
	m_animFrame.frame_time = GetTickCount();
	m_changeDirectionSpeed = 7000;
	m_changeDirectionTime = GetTickCount();

	m_data.maxExp = 100;
	m_data.exp = m_data.maxExp;
	m_data.maxHp = 2500;
	m_data.hp = m_data.maxHp;
	m_data.money = 100;
	m_data.maxAttack = 50;
	m_data.minAttack = m_data.maxAttack;
	jumpDelay = 200;
	m_player = CGameObject_Manager::Get_Instance()->GetPlayer();
	UpdateRect_GameObject();

	return S_OK;
}

int CMushroom::Update_GameObject()
{
	m_player = CGameObject_Manager::Get_Instance()->GetPlayer();

	if (m_isDead)
	{
		if (m_dir == Direction::DIR_LEFT)
		{
			Set_Animation(m_left_hdc, Mushroom_Animation::MUSHROOM_DIE, Mushroom_Animation_Index::MUSHROOM_DIE_INDEX);
		}
		else if (m_dir == Direction::DIR_RIGHT)
		{
			Set_Animation(m_right_hdc, Mushroom_Animation::MUSHROOM_DIE, Mushroom_Animation_Index::MUSHROOM_DIE_INDEX);
		}
		if (m_animFrame.frame_start >= m_animFrame.frame_end - 1)
			m_isDie = true;
	}

	if (m_isDie)
	{
		int temp = rand() % 10;
		if (temp > 7)
			CMeso::Create(m_info.x, m_rect.top , m_data.money);
		else if (temp > 5)
			CDrop_Mushroom::Create(m_info.x, m_rect.top);
		else if (temp > 3)
			CRed_Potion::Create(m_info.x, m_rect.top);
		return OBJ_DEAD;
	}
	if (!m_isHit)
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
					//m_isWalk = false;
					if (m_dir == Direction::DIR_LEFT)
						Set_Animation(m_left_hdc, Mushroom_Animation::MUSHROOM_JUMP, Mushroom_Animation_Index::MUSHROOM_JUMP_INDEX);
					else if (m_dir == Direction::DIR_RIGHT)
						Set_Animation(m_right_hdc, Mushroom_Animation::MUSHROOM_JUMP, Mushroom_Animation_Index::MUSHROOM_JUMP_INDEX);
					m_animFrame.frame_speed = 1000;
				}
			}
			m_changeStateTime = GetTickCount();
		}
	}

	if (!m_isDead)
	{
		if (!m_isHit)
		{
			if (m_changeDirectionTime + m_changeDirectionSpeed < GetTickCount())
			{
				//m_isJump = true;
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
		}

		float fY;
		if (m_isWalk && !m_isFall && !m_isSkillHit)
		{
			if (m_dir == Direction::DIR_LEFT)
			{
				m_info.x -= m_speed;
				if (!CLine_Manager::Get_Instance()->Collision_Line_Manager(this, &fY))
					m_info.x += m_speed;

			}
			else if (m_dir == Direction::DIR_RIGHT)
			{
				m_info.x += m_speed;
				if (!CLine_Manager::Get_Instance()->Collision_Line_Manager(this, &fY))
					m_info.x -= m_speed;
			}
		}
		if (m_isSkillHit)
		{
			if (m_dir == Direction::DIR_LEFT)
			{
				Set_Animation(m_left_hdc, Mushroom_Animation::MUSHROOM_HIT, Mushroom_Animation_Index::MUSHROOM_HIT_INDEX);
			}
			else if (m_dir == Direction::DIR_RIGHT)
			{
				Set_Animation(m_right_hdc, Mushroom_Animation::MUSHROOM_HIT, Mushroom_Animation_Index::MUSHROOM_HIT_INDEX);
			}
		}

		if (!m_isSkillHit)
		{
			if (m_dir == Direction::DIR_LEFT)
			{
				Set_Animation(m_left_hdc, Mushroom_Animation::MUSHROOM_STAND, Mushroom_Animation_Index::MUSHROOM_STAND_INDEX);
			}
			else if (m_dir == Direction::DIR_RIGHT)
			{
				Set_Animation(m_right_hdc, Mushroom_Animation::MUSHROOM_STAND, Mushroom_Animation_Index::MUSHROOM_STAND_INDEX);
			}
		}
	}


	if (m_isHit && !m_isSkillHit && !m_trace)
	{

		if (m_info.x > m_player->Get_Info()->x)
			m_dir = Direction::DIR_LEFT;
		else
			m_dir = Direction::DIR_RIGHT;

		m_trace = true;
		m_isWalk = true;
	}
	return 0;
}

void CMushroom::Late_Update_GameObject()
{
	//jumpDelay++;
	if (m_trace)
	{
		//if (m_rect.top > m_player->GetRect()->bottom && jumpDelay>200)
		//	m_isJump = true;
		//else
		//	m_isJump = false;
		if ((m_dir == Direction::DIR_LEFT && m_rect.right < m_player->GetRect()->left) || m_rect.left <= 5)
		{
			m_dir = Direction::DIR_RIGHT;
			m_hdc = m_right_hdc;
		}
		if ((m_dir == Direction::DIR_RIGHT && m_rect.left > m_player->GetRect()->right) || m_rect.right >= 2595)
		{
			m_dir = Direction::DIR_LEFT;
			m_hdc = m_left_hdc;
		}
	}
	Mushroom_Jump();
	Play_Animation();
	if (!m_isHit)
	{

		if (m_rect.left <= 5)
		{
			m_dir = Direction::DIR_RIGHT;
			m_hdc = m_right_hdc;
		}
		else if (m_rect.right >= 2595)
		{
			m_dir = Direction::DIR_LEFT;
			m_hdc = m_left_hdc;
		}
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


void CMushroom::Mushroom_Jump()
{
	float fY = 0.f;
	bool bCollLine = CLine_Manager::Get_Instance()->Collision_Line_Manager(this, &fY);
	if (m_isJump)
	{
		if (bCollLine)
		{
			if (m_currentHeight < 0)
				m_currentHeight++;
			else
			{
				if (m_currentHeight < m_jumpHeight)
					m_info.y -= m_jumpSpeed;
				else
				{
					//if (m_currentHeight < m_jumpHeight * 2 && bCollLine)
					if (fY - m_info.sizeY / 2 >= m_info.y + m_jumpSpeed)
						m_info.y += m_jumpSpeed;
					else
					{
						m_currentHeight = -20;
						m_info.y = fY - m_info.sizeY / 2;
						m_isJump = false;
						jumpDelay = 0;
					}
				}
				m_currentHeight += m_jumpSpeed;
			}
		}
	}
	else if (bCollLine)
	{

		if (abs(m_info.y - (fY - m_info.sizeY / 2)) >= 5)
		{
			if (m_dir == Direction::DIR_LEFT)
			{
				Set_Animation(m_left_hdc, Mushroom_Animation::MUSHROOM_JUMP, Mushroom_Animation_Index::MUSHROOM_JUMP_INDEX);
			}
			else if (m_dir == Direction::DIR_RIGHT)
			{
				Set_Animation(m_right_hdc, Mushroom_Animation::MUSHROOM_JUMP, Mushroom_Animation_Index::MUSHROOM_JUMP_INDEX);
			}
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

void CMushroom::Set_Animation(HDC hdc, Mushroom_Animation animScene, Mushroom_Animation_Index frameEnd)
{
	if (m_animFrame.frame_animation != animScene)
		m_animFrame.frame_start = 0;

	m_hdc = hdc;
	m_animFrame.frame_animation = animScene;
	m_animFrame.frame_end = frameEnd;
}
