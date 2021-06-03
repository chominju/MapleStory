#include "stdafx.h"
#include "Boss.h"
#include "GameObject_Manager.h"
#include "Bitmap_Manager.h"
#include "Line_Manager.h"
#include "Scroll_Manager.h"
#include "Scene_Manager.h"
#include "Boss_Attack2_Ball.h"
#include "Player.h"

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
	m_teleport_hdc = CBitmap_Manager::Get_Instance()->Get_memDC(L"Boss_Teleport");
	m_attack1_hdc = CBitmap_Manager::Get_Instance()->Get_memDC(L"Boss_Attack1");
	m_attack2_hdc = CBitmap_Manager::Get_Instance()->Get_memDC(L"Boss_Attack2");
	m_attack3_hdc = CBitmap_Manager::Get_Instance()->Get_memDC(L"Boss_Attack3");
	m_objectDie_hdc = CBitmap_Manager::Get_Instance()->Get_memDC(L"Boss_Die");	
	m_icon = CBitmap_Manager::Get_Instance()->Get_memDC(L"Boss_Icon");

	m_hdc = m_left_hdc;

	m_dir = Direction::DIR_LEFT;

	m_info.x = 500;
	m_info.y = 530;
	m_info.sizeX = 130;
	m_info.sizeY = 161;
	m_TeleportSizeX = 64;
	m_TeleportSizeY = 165;

	m_Attack1SizeX = 196;
	m_Attack1SizeY = 223;

	m_Attack2SizeX = 322;
	m_Attack2SizeY = 243;

	m_Attack3SizeX = 413;
	m_Attack3SizeY = 360;

	m_DieSizeX = 341;
	m_DieSizeY = 345;

	m_speed = 2.f;
	UpdateRect_GameObject();


	m_animFrame.frame_start = 0;
	m_animFrame.frame_animation = Boss_Animation::BOSS_STAND;
	m_animFrame.frame_end = Boss_Animation_Index::BOSS_STAND_INDEX;
	m_animFrame.frame_speed = 200;
	m_animFrame.frame_time = GetTickCount();
	m_changeStateTime = GetTickCount();
	m_changeStateSpeed = 2000;


	m_animTeleportFrame.frame_start = 0;
	m_animTeleportFrame.frame_animation = Boss_Animation::BOSS_TELEPORT;
	m_animTeleportFrame.frame_end = Boss_Animation_Index::BOSS_TELEPORT_INDEX;
	m_animTeleportFrame.frame_speed = 200;
	m_animTeleportFrame.frame_time = GetTickCount();


	m_Attack1Time = GetTickCount();
	m_Attack1Speed = 1000;

	m_Attack2Time = GetTickCount();
	m_Attack2Speed = 15000;

	m_Attack3Time = GetTickCount();
	m_Attack3Speed = 40000;

	m_TeleportTime = GetTickCount();
	m_TeleportSpeed = 20000;

	m_TeleportAfterTime=GetTickCount();
	m_TeleportAfterSpeed=3000;



	m_data.maxExp = 50000;
	m_data.exp = m_data.maxExp;
	//m_data.maxHp = 5000;
	m_data.maxHp = 1000000;
	m_data.hp = m_data.maxHp;
	m_data.money = 10000;
	m_data.maxAttack = 5000;
	m_data.minAttack = m_data.maxAttack;
	m_player = CGameObject_Manager::Get_Instance()->GetPlayer();

	m_isCollisionOn = false;
	m_isAttackOn = false;
	m_isvisibility = true;
	m_isTeleportBefore = false;
	m_isTeleportAfter=false;

	return 0;
}

int CBoss::Update_GameObject()
{
	if (m_isDead)
	{
			m_isCollisionOn = false;
			m_isAttackOn = false;
			m_isvisibility = true;
			m_isTeleport = false;
			m_isAttack1 = false;
			m_isAttack2 = false;
			m_isAttack3 = false;
			m_info.sizeX = m_DieSizeX;
			m_info.sizeY = m_DieSizeY;
			if (m_dir == Direction::DIR_LEFT)
				Set_Animation(m_objectDie_hdc, Boss_Animation::BOSS_LEFT, Boss_Animation_Index::Boss_DIE_INDEX);
			else if (m_dir == Direction::DIR_RIGHT)
				Set_Animation(m_objectDie_hdc, Boss_Animation::BOSS_RIGHT, Boss_Animation_Index::Boss_DIE_INDEX);
			if (m_animFrame.frame_start == m_animFrame.frame_end - 1)
				return OBJ_DEAD;
	}
	else
	{
		m_player = CGameObject_Manager::Get_Instance()->GetPlayer();

		if (!m_isAttackOn)	// 공격스킬을 사용하지 않았을 때
		{
			//if (m_changeStateTime + m_changeStateSpeed < GetTickCount() && m_isvisibility)
			if (m_isvisibility)
			{
				if (m_Attack3Time + m_Attack3Speed < GetTickCount())
				{
					if (m_dir == Direction::DIR_LEFT)
						Set_Animation(m_attack3_hdc, Boss_Animation::BOSS_LEFT, Boss_Animation_Index::BOSS_ATTACK3_INDEX);
					else if (m_dir == Direction::DIR_RIGHT)
						Set_Animation(m_attack3_hdc, Boss_Animation::BOSS_RIGHT, Boss_Animation_Index::BOSS_ATTACK3_INDEX);
					m_isAttackOn = true;
					m_info.y = 475;
					m_info.sizeX = m_Attack3SizeX;
					m_info.sizeY = m_Attack3SizeY;
					m_animFrame.frame_speed = 100;
					m_Attack3Time = GetTickCount();
					m_isAttack1 = false;
					m_isAttack2 = false;
					m_isAttack3 = true;
					CSoundMgr::Get_Instance()->PlaySound(L"Boss_Attack3.mp3", CSoundMgr::MONSTER);
				}

				else if (m_TeleportTime + m_TeleportSpeed < GetTickCount())
				{
					m_isvisibility = false;
					m_isTeleport = true;
					m_isAttackOn = true;
					m_TeleportAfterTime = GetTickCount();
					m_TeleportTime = GetTickCount();
					Set_TelePortAnimation(m_teleport_hdc, Boss_Animation::BOSS_TELEPORT, Boss_Animation_Index::BOSS_TELEPORT_INDEX);
					CSoundMgr::Get_Instance()->PlaySound(L"Boss_Teleport.mp3", CSoundMgr::MONSTER);

				}
				else if (m_Attack2Time + m_Attack2Speed < GetTickCount())
				{
					if (m_dir == Direction::DIR_LEFT)
						Set_Animation(m_attack2_hdc, Boss_Animation::BOSS_LEFT, Boss_Animation_Index::BOSS_ATTACK2_INDEX);
					else if (m_dir == Direction::DIR_RIGHT)
						Set_Animation(m_attack2_hdc, Boss_Animation::BOSS_RIGHT, Boss_Animation_Index::BOSS_ATTACK2_INDEX);
					m_isAttackOn = true;
					m_info.y = 527;
					m_info.sizeX = m_Attack2SizeX;
					m_info.sizeY = m_Attack2SizeY;
					m_Attack2Time = GetTickCount();
					m_isAttack1 = false;
					m_isAttack2 = true;
					m_isAttack3 = false;
					CSoundMgr::Get_Instance()->PlaySound(L"Boss_Attack2.mp3", CSoundMgr::MONSTER);
				}
				else if (m_Attack1Time + m_Attack1Speed < GetTickCount())
				{
					if (m_dir == Direction::DIR_LEFT)
					{
						if (m_player->GetRect()->right - 40 > m_rect.left/* && m_player->Get_Info()->x < m_info.x +10*/)
						{
							m_isAttackOn = true;
							Set_Animation(m_attack1_hdc, Boss_Animation::BOSS_LEFT, Boss_Animation_Index::BOSS_ATTACK1_INDEX);
						}
					}
					else if (m_dir == Direction::DIR_RIGHT)
					{
						if (m_player->GetRect()->left + 40 < m_rect.right/* && m_player->Get_Info()->x >m_info.x -10*/)
						{
							m_isAttackOn = true;
							Set_Animation(m_attack1_hdc, Boss_Animation::BOSS_RIGHT, Boss_Animation_Index::BOSS_ATTACK1_INDEX);
						}
					}
					if (m_isAttackOn)
					{
						m_isAttack1 = true;
						m_isAttack2 = false;
						m_isAttack3 = false;
						m_info.sizeX = m_Attack1SizeX;
						m_info.sizeY = m_Attack1SizeY;
						m_info.y = 517;
						m_animFrame.frame_speed = 100;
						m_Attack1Time = GetTickCount();
						CSoundMgr::Get_Instance()->PlaySound(L"Boss_Attack1.mp3", CSoundMgr::MONSTER);
					}
				}
			}
		}

		if (m_isTeleport && !m_isTeleportAfter)
		{
			if (m_TeleportAfterTime + m_TeleportAfterSpeed < GetTickCount())
			{
				m_info.x = m_player->Get_Info()->x;
				Set_TelePortAnimation(m_teleport_hdc, Boss_Animation::BOSS_TELEPORT_AFTER, Boss_Animation_Index::BOSS_TELEPORT_INDEX);
				m_isTeleportAfter = true;
			}
		}

		if (!m_isFall & !m_isAttackOn & !m_isTeleport)
		{
			if (m_dir == Direction::DIR_LEFT && m_player->GetRect()->right - 40 < m_rect.left)
			{
				m_info.x -= m_speed;
				Set_Animation(m_left_hdc, Boss_Animation::BOSS_WALK, Boss_Animation_Index::BOSS_WALK_INDEX);
			}
			else if (m_dir == Direction::DIR_RIGHT && m_player->GetRect()->left + 40 > m_rect.right)
			{
				m_info.x += m_speed;
				Set_Animation(m_right_hdc, Boss_Animation::BOSS_WALK, Boss_Animation_Index::BOSS_WALK_INDEX);
			}
			else
			{
				if (m_dir == Direction::DIR_LEFT)
					Set_Animation(m_left_hdc, Boss_Animation::BOSS_STAND, Boss_Animation_Index::BOSS_STAND_INDEX);
				else if (m_dir == Direction::DIR_RIGHT)
					Set_Animation(m_right_hdc, Boss_Animation::BOSS_STAND, Boss_Animation_Index::BOSS_STAND_INDEX);
			}
		}

	}
		return 0;
}

void CBoss::Late_Update_GameObject()
{
	Play_Animation();
	Play_AttackAnimation();
	Boss_Attack();
	Play_TeleportAnimation();
	if (!m_isDead)
	{
		if (m_rect.left <= 5 || m_rect.right < m_player->GetRect()->left - 20 || m_info.x < m_player->Get_Info()->x)
		{
			if (!m_isAttackOn)
			{
				m_dir = Direction::DIR_RIGHT;
				m_hdc = m_right_hdc;
			}
		}
		if (m_rect.right >= CScene_Manager::Get_Instance()->Get_SceneSize().x - 5 || m_info.x > m_player->Get_Info()->x)
		{
			if (!m_isAttackOn)
			{
				m_dir = Direction::DIR_LEFT;
				m_hdc = m_left_hdc;
			}
		}
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

	if (m_isvisibility)
	{
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
	}
	else
	{
		GdiTransparentBlt(hDC, // 그림을 복사하고자 하는 대상. 
			m_rect.left + scrollX,//위치 x,y
			m_rect.top + scrollY,
			m_TeleportSizeX,// 크기 xy
			m_TeleportSizeY,
			m_teleport_hdc,// 복사 할 대상
			m_animTeleportFrame.frame_start*m_TeleportSizeX, m_animTeleportFrame.frame_animation *m_TeleportSizeY,// 그림의 시작 위치 x,y
			m_TeleportSizeX,// 그리고자 하는 영역의 크기 x,y
			m_TeleportSizeY,
			RGB(255, 0, 255));
	}


	GdiTransparentBlt(hDC, // 그림을 복사하고자 하는 대상. 
		WINCX / 4,//위치 x,y
		0,
		WINCX/2,// 크기 xy
		35,
		m_hpBackBar_hdc,// 복사 할 대상
		0, 0,// 그림의 시작 위치 x,y
		182,// 그리고자 하는 영역의 크기 x,y
		21,
		RGB(255, 0, 255));



	GdiTransparentBlt(hDC, // 그림을 복사하고자 하는 대상. 
		WINCX / 4 + 8,//위치 x,y
		5,
		(int)((WINCX / 2 - 16)*(m_data.hp / m_data.maxHp)),// 크기 xy
		24,
		m_hpBar_hdc,// 복사 할 대상
		0, 0,// 그림의 시작 위치 x,y
		176,// 그리고자 하는 영역의 크기 x,y
		15,
		RGB(255, 0, 255));

	GdiTransparentBlt(hDC, // 그림을 복사하고자 하는 대상. 
		WINCX / 4 - 35,//위치 x,y
		0,
		35,// 크기 xy
		35,
		m_icon,// 복사 할 대상
		0, 0,// 그림의 시작 위치 x,y
		35,// 그리고자 하는 영역의 크기 x,y
		35,
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
		if (m_animFrame.frame_animation != animScene || m_hdc!= hdc)
			m_animFrame.frame_start = 0;

		m_hdc = hdc;
		m_animFrame.frame_animation = animScene;
		m_animFrame.frame_end = frameEnd;
}

//void CBoss::Set_Animation(HDC hdc, BossAttack_Animation animScene, Boss_Animation_Index frameEnd)
//{
//	if (m_animFrame.frame_animation != animScene && m_hdc!= hdc)
//		m_animFrame.frame_start = 0;
//
//	m_hdc = hdc;
//	m_animFrame.frame_animation = animScene;
//	m_animFrame.frame_end = frameEnd;
//}

void CBoss::Set_TelePortAnimation(HDC hdc, Boss_Animation animScene, Boss_Animation_Index frameEnd)
{
	if (m_animTeleportFrame.frame_animation != animScene)
		m_animTeleportFrame.frame_start = 0;

	m_teleport_hdc = hdc;
	m_animTeleportFrame.frame_animation = animScene;
	m_animTeleportFrame.frame_end = frameEnd;
}


void CBoss::Play_Animation()
{
	if (!m_isAttackOn)
	{
		if (m_animFrame.frame_time + m_animFrame.frame_speed < GetTickCount())
		{
			++m_animFrame.frame_start;
			m_animFrame.frame_time = GetTickCount();
			if (m_animFrame.frame_start >= m_animFrame.frame_end)
				m_animFrame.frame_start = 0;
		}
	}
}

void CBoss::Play_TeleportAnimation()
{
	if (m_isTeleport)
	{
		if (m_animTeleportFrame.frame_time + m_animTeleportFrame.frame_speed < GetTickCount())
		{
			++m_animTeleportFrame.frame_start;
			m_animTeleportFrame.frame_time = GetTickCount();
			if (m_animTeleportFrame.frame_start >= m_animTeleportFrame.frame_end)
			{
				if (m_isTeleportAfter)
				{
					m_isvisibility = true;
					m_isTeleportAfter = false;
					m_isTeleport = false;
					m_isAttackOn = false;
					m_isAttack1 = false;
					m_isAttack2 = false;
					m_isAttack3 = false;
				}
				//m_animTeleportFrame.frame_start = 0;
			}
		}
	}
}

void CBoss::Play_AttackAnimation()
{
	if (m_isAttackOn)
	{
		if (m_animFrame.frame_time + m_animFrame.frame_speed < GetTickCount())
		{
			++m_animFrame.frame_start;
			m_animFrame.frame_time = GetTickCount();
			if (m_animFrame.frame_start >= m_animFrame.frame_end)
			{
				m_info.sizeX = 130;
				m_info.sizeY = 161;
				m_info.y = 548;
				m_animFrame.frame_speed = 200;
				m_isAttackOn = false;
				m_animFrame.frame_start = -1;
				m_player->Set_IsSkillHit(false);
				m_changeStateTime = GetTickCount();
				if (m_dir == Direction::DIR_LEFT)
					Set_Animation(m_left_hdc, Boss_Animation::BOSS_STAND, Boss_Animation_Index::BOSS_STAND_INDEX);
				else if (m_dir == Direction::DIR_RIGHT)
					Set_Animation(m_right_hdc,Boss_Animation::BOSS_STAND, Boss_Animation_Index::BOSS_STAND_INDEX);

			}
		}
	}
}

void CBoss::Boss_Attack()
{
	if (m_isAttackOn)
	{
		if (m_isAttack1)
		{
			if (m_animFrame.frame_start == 5)
			{
				if (m_dir == Direction::DIR_LEFT)
				{
					if (m_player->Get_Info()->x < m_rect.right-50 && m_player->GetRect()->right>= m_rect.left)
					{
						if (!m_player->Get_IsInvincibility())
						{
							m_player->Set_Change_Hp(-(m_player->Get_Data()->maxHp*0.1));
							m_player->Set_IsSkillHit(true); // 스킬 맞음 ON
							m_player->Set_IsHit(true);
							m_player->Set_IsInvincibility(true);
							CSoundMgr::Get_Instance()->PlaySound(L"Boss_CharDam1.mp3", CSoundMgr::PLAYER);
						}
					}
				}
				else if (m_dir == Direction::DIR_RIGHT)
				{
					if (m_player->Get_Info()->x > m_rect.left+50 && m_player->GetRect()->left <= m_rect.right)
					{
						if (!m_player->Get_IsInvincibility())
						{
							m_player->Set_Change_Hp(-(m_player->Get_Data()->maxHp*0.1));
							m_player->Set_IsSkillHit(true); // 스킬 맞음 ON
							m_player->Set_IsHit(true);
							m_player->Set_IsInvincibility(true);
							CSoundMgr::Get_Instance()->PlaySound(L"Boss_CharDam1.mp3", CSoundMgr::PLAYER);
						}
					}
				}

			}
		}
		if (m_isAttack2)
		{
			if (m_animFrame.frame_start == 9)
			{
				CBoss_Attack2_Ball::Create(this);
			}
		}
		if (m_isAttack3)
		{
			if (m_animFrame.frame_start == 8)
			{
				if (!dynamic_cast<CPlayer*>(m_player)->Get_IsJump())
				{
					if (!m_player->Get_IsInvincibility())
					{
						m_player->Set_Change_Hp(-(m_player->Get_Data()->maxHp*0.9));
						m_player->Set_IsSkillHit(true); // 스킬 맞음 ON
						m_player->Set_IsHit(true);
						m_player->Set_IsInvincibility(true);
						CSoundMgr::Get_Instance()->PlaySound(L"Boss_CharDam3.mp3", CSoundMgr::PLAYER);
					}
				}
			}
		}
	}
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

