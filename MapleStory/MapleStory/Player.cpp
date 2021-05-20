#include "stdafx.h"
#include "Player.h"
#include "Key_Manager.h"
#include "LoadData.h"
#include "MyBitmap.h"
#include "Bitmap_Manager.h"
#include "Line_Manager.h"
#include "Scroll_Manager.h"
#include "Scene_Manager.h"
#include "Collision_Manager.h"
#include "GameObject_Manager.h"
#include "DoubleStab.h"
#include "DoubleJump.h"
#include "SavageBlow.h"
#include "CLevelUp.h"

CGameObject * CPlayer::m_instance = nullptr;

CPlayer::CPlayer()
	: m_isJump(false)
	, m_isDoubleJump(false)
	, m_isJumpLeft(false)
	, m_isJumpRight(false)
	, m_isDownJump(false)
	, m_moveLock(false)
	, m_isFall(false)
	, m_power(0.f)
	, m_isStatOpen(false)
	, m_isInventoryOpen(false)
	, current_jumpHeight(0)
{
	ZeroMemory(&m_animFrame, sizeof(Animation_Frame));
	ZeroMemory(&m_keyPush, sizeof(Key_Push));
}

CPlayer::~CPlayer()
{
}

int CPlayer::Ready_GameObject()
{
	m_left_hdc = CBitmap_Manager::Get_Instance()->Get_memDC(L"Player_Left");
	m_right_hdc = CBitmap_Manager::Get_Instance()->Get_memDC(L"Player_Right");
	m_hpBar_hdc = CBitmap_Manager::Get_Instance()->Get_memDC(L"Player_Hp_Bar");
	m_hpBackBar_hdc = CBitmap_Manager::Get_Instance()->Get_memDC(L"Player_Hp_BackBar");
	m_expBar_hdc = CBitmap_Manager::Get_Instance()->Get_memDC(L"Player_Exp_Bar");
	m_expBackBar_hdc = CBitmap_Manager::Get_Instance()->Get_memDC(L"Player_Exp_BackBar");
	m_State_Lv_hdc = CBitmap_Manager::Get_Instance()->Get_memDC(L"State_Lv");
	m_State_LvNum_hdc = CBitmap_Manager::Get_Instance()->Get_memDC(L"State_LvNum");
	m_State_Num_hdc = CBitmap_Manager::Get_Instance()->Get_memDC(L"State_Num");

	m_hdc = m_left_hdc;
	m_info.x = 100;
	m_info.y = 100;
	m_info.sizeX = 48;
	m_info.sizeY = 66;

	m_speed = 4.f;
	m_jumpHeight = 100;
	m_DoublejumpHeight = 0;
	current_DoublejumpHeight = 0;
	m_power = 5;
	m_fallSpeed = 5;
	m_checkKeepY = -768;
	UpdateRect_GameObject();

	m_animFrame.frame_start = 0;
	m_animFrame.frame_end = Animation_index::STAND_INDEX;
	m_animFrame.frame_animation = Animation::STAND;
	m_animFrame.frame_speed = 200;
	m_animFrame.frame_time = GetTickCount();

	m_data.level = 1;
	m_data.maxHp = 2000;

	m_data.hp = m_data.maxHp;
	m_data.minAttack = 100;
	m_data.maxAttack = 200;
	m_data.maxExp = 500;
	m_data.exp = 0;
	m_data.money = 0;

	m_hitAnimationNum = 0;
	m_isInvincibility = false;

	m_checkScrollY = false;

	return 0;
}

int CPlayer::Update_GameObject()
{
	if (m_data.hp <= 0)
	{
		if (m_currentKey == CurrentKey::CUR_LEFT)
			Set_Animation(m_left_hdc, Animation::DEAD, Animation_index::DEAD_INDEX);
		if (m_currentKey == CurrentKey::CUR_RIGHT)
			Set_Animation(m_right_hdc, Animation::DEAD, Animation_index::DEAD_INDEX);
	}
	else
	{
		if (!m_keyPush.isAttack && !m_keyPush.isDown && !m_keyPush.isRope && !m_keyPush.isRopeMove)
		{
			if (CKey_Manager::Get_Instance()->Key_Pressing(KEY_Q))												// 스킬 Q(더블스탭)
			{
				if (!m_keyPush.isSkill)
				{
					CGameObject * DoubleStab = CDoubleStab::Create(this);
					Player_Skill(Animation::SWING, Animation_index::SWING_INDEX);
				}
			}

			if (CKey_Manager::Get_Instance()->Key_Pressing(KEY_W))												// 스킬 W(새비지블로우)
			{
				if (!m_keyPush.isSkill)
				{
					CGameObject * DoubleStab = CSavageBlow::Create(this);
					Player_Skill(Animation::SWING, Animation_index::SWING_INDEX);
				}
			}

			if (m_isJump)
			{
				if (m_keyPush.isDoubleJumpReady && !m_keyPush.isDoubleJump)
				{
					if (CKey_Manager::Get_Instance()->Key_Pressing(KEY_F))										// 스킬 (더블점프)
					{
						m_keyPush.isDoubleJump = true;
						jumpDir = m_currentKey;
						m_DoublejumpHeight = 20;
						CGameObject * DoubleStab = CDoubleJump::Create(this);
						//Player_Skill(Animation::JUMP , Animation_index::JUMP_INDEX);
					}
				}
			}
		}

		if (!m_keyPush.isAttack && !m_keyPush.isDown)															// 좌우키 + 로프(위아래)
		{
			if (CKey_Manager::Get_Instance()->Key_Pressing(KEY_LEFT))
				Player_MoveLeft();
			if (CKey_Manager::Get_Instance()->Key_Up(KEY_LEFT))
				m_keyPush.isLeft = false;

			if (CKey_Manager::Get_Instance()->Key_Pressing(KEY_RIGHT))
				Player_MoveRight();
			if (CKey_Manager::Get_Instance()->Key_Up(KEY_RIGHT))
				m_keyPush.isRight = false;


			//	if (CKey_Manager::Get_Instance()->Key_Pressing(KEY_UP) || (CKey_Manager::Get_Instance()->Key_Pressing(KEY_DOWN)))
			if (m_keyPush.isRopeMove)
				if (CKey_Manager::Get_Instance()->Key_Up(KEY_UP) || (CKey_Manager::Get_Instance()->Key_Up(KEY_DOWN)))
					m_keyPush.isRopeMove = false;
		}

		if (!m_isDownJump && !m_keyPush.isRope)
		{
			if (!m_keyPush.isSkill)
			{
				if (CKey_Manager::Get_Instance()->Key_Pressing(KEY_DOWN))										// 아래모션 / 아래점프
				{
					m_keyPush.isDown = true;
					if (!m_isJump)
						Player_Prone();
					if (CKey_Manager::Get_Instance()->Key_Down(KEY_F))
					{
						m_info.y += 5;
						float fY = 0.f;
						bool bCollLine = CLine_Manager::Get_Instance()->Floor_Collision_Line_Manager_Line_Manager(this);
						if (!bCollLine)
							m_info.y -= 5;
						else
						{
							m_keyPush.isJump = true;
							m_isDownJump = true;
							m_moveLock = true;
						}
					}
				}
				if (CKey_Manager::Get_Instance()->Key_Up(KEY_DOWN))
					m_keyPush.isDown = false;
			}
		}



		if (!m_isDownJump)
		{
			if (CKey_Manager::Get_Instance()->Key_Pressing(KEY_F))
			{
				if (!CKey_Manager::Get_Instance()->Key_Pressing(KEY_DOWN))
				{
					if (!m_isJump)
					{
						if (m_isJumpLeft == false && m_isJumpRight == false)
							m_moveLock = true;
						m_isJump = true;
						m_beforeJumpY = m_info.y;
					}
				}
			}
		}

		if (m_isJump)
		{
			if (CKey_Manager::Get_Instance()->Key_Up(KEY_F))
			{
				m_keyPush.isDoubleJumpReady = true;
			}
		}


		if (!m_keyPush.isSkill)
		{
			if (m_isPortal)	// 포탈 위
				if (CKey_Manager::Get_Instance()->Key_Down(KEY_UP))
					return MOVE_PORTAL;

			if (CKey_Manager::Get_Instance()->Key_Pressing(KEY_A))
				Player_Swing();
			if (CKey_Manager::Get_Instance()->Key_Up(KEY_A))
				m_keyPush.isAttack = false;
		}

		if (CKey_Manager::Get_Instance()->Key_Down(KEY_P))
		{
			Player_StatUiOpen();
		}

		if (CKey_Manager::Get_Instance()->Key_Down(KEY_I))
		{
			Player_InventoryOpen();
		}



		if (!m_keyPush.isJump && !m_keyPush.isLeft && !m_keyPush.isRight && !m_keyPush.isDown && !m_keyPush.isAttack && !m_keyPush.isRope && !m_keyPush.isSkill && !m_isHit)
			Player_Idle();
		if ((m_isJump || m_isDownJump) && !m_keyPush.isRope && !m_keyPush.isSkill && !m_isHit)
			Player_Jump();
		if (m_keyPush.isRope && !m_keyPush.isRopeMove)
			Set_Animation(m_left_hdc, Animation::ROPING, Animation_index::ROPE_STOP_INDEX);

		if (m_isHit)
		{
			//if(m_hitAnimationNum == 0)
			Player_Hit();
			m_hitAnimationNum++;

			if (m_hitAnimationNum >= 50)
			{
				m_isHit = false;
				m_isInvincibility = false;
				m_hitAnimationNum = 0;
			}
		}

		if (CGameObject_Manager::Get_Instance()->GetObejct(Object_ID::ATTACK_SKILL).empty())
			m_keyPush.isSkill = false;


		if (CScroll_Manager::ScrollLock())
			if (!m_checkScrollY)
			{
				m_checkScrollY = true;
				m_checkKeepY = m_info.y;
			}

	}
	return 0;
}

void CPlayer::Late_Update_GameObject()
{
	Is_OffSet();
	Player_Rope();
	Is_Jump();
	Is_LevelUp();
	Play_Animation();
}

void CPlayer::Render_GameObject(HDC hDC)
{
	UpdateRect_GameObject();
	//if (m_hdc == nullptr)
	//	return;

	int scrollX = CScroll_Manager::Get_ScrollX();
	int scrollY = CScroll_Manager::Get_ScrollY();

	int i;
	int j;

	GdiTransparentBlt(hDC, // 그림을 복사하고자 하는 대상. 
		m_rect.left+ scrollX,//위치 x,y
		m_rect.top+ scrollY,
		m_info.sizeX,// 크기 xy
		m_info.sizeY,
		m_hdc,// 복사 할 대상
		m_animFrame.frame_start*m_info.sizeX, m_animFrame.frame_animation * m_info.sizeY,// 그림의 시작 위치 x,y
		m_info.sizeX,// 그리고자 하는 영역의 크기 x,y
		m_info.sizeY,
		RGB(255, 0, 255));
}

void CPlayer::Release_GameObject()
{
}

void CPlayer::UpdateRect_GameObject()
{
	m_rect.left = static_cast<LONG>(m_info.x - (m_info.sizeX / 2));
	m_rect.top = static_cast<LONG>(m_info.y - (m_info.sizeY / 2));
	m_rect.right = static_cast<LONG>(m_info.x + (m_info.sizeX / 2));
	m_rect.bottom = static_cast<LONG>(m_info.y + (m_info.sizeY / 2));
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
		CGameObject_Manager::Get_Instance()->Add_GameObject_Manager(Object_ID::PLAYER, m_instance);
	}

	return m_instance;
}

void CPlayer::Is_Jump()
{
	float fY = 0.f;
	bool bCollLine = CLine_Manager::Get_Instance()->Collision_Line_Manager(this ,&fY);
	if (m_isJump && !m_keyPush.isRope)
	{
		if (current_jumpHeight <= m_jumpHeight + m_DoublejumpHeight  &&!m_isFall)
		{
			m_info.y -= m_power;
			//if ((m_info.y + WINCY / 2 > 0 && m_info.y < 0)|| m_info.y>=0)
				//CScroll_Manager::Set_ScrollY(m_power);
			
			current_jumpHeight += m_power;
		}
		else if (bCollLine)
		{
			if (abs(m_info.y - (fY - m_info.sizeY / 2)) >= 5)
			{
				m_info.y += m_fallSpeed;
				//if ((m_info.y + WINCY / 2 > 0 && m_info.y < 0) || m_info.y >= 0)
				//if (m_checkKeepY<m_info.y)
					//CScroll_Manager::Set_ScrollY(-m_fallSpeed);
			}
			else
			{
				m_info.y = fY - m_info.sizeY / 2;
				float temp = m_beforeJumpY - m_info.y;
				//CScroll_Manager::Set_ScrollY(temp);
				current_jumpHeight = 0;
				m_isJump = false;
				m_isJumpRight = false;
				m_isJumpLeft = false;
				m_moveLock = false;
				m_keyPush.isJump = false;
				m_keyPush.isDoubleJumpReady = false;
				m_keyPush.isDoubleJump = false;
				m_DoublejumpHeight = 0;
				current_DoublejumpHeight = 0;
			}
		}

		if(m_keyPush.isDoubleJump)
		{
			if (jumpDir == CurrentKey::CUR_LEFT)
			{
				if (m_rect.left >= 0)
				{
					m_info.x -= m_speed;
					//if (m_info.x - WINCX / 2 >= 0)
						//if (m_info.x + CScroll_Manager::Get_ScrollX() < WINCX / 2)
							CScroll_Manager::Set_ScrollX(m_speed);

					current_DoublejumpHeight += m_power;
					//if (current_DoublejumpHeight <= m_DoublejumpHeight)
					//{
					//	m_info.y -= m_power;
					//		CScroll_Manager::Set_ScrollY(m_power);
					//	//if ((m_info.y + WINCY / 2 > 0 && m_info.y < 0) || m_info.y >= 0)
					//}
				}

			}
			else if (jumpDir == CurrentKey::CUR_RIGHT)
			{
				if (m_rect.right <= CScene_Manager::Get_Instance()->Get_SceneSize().x)
				{
					m_info.x += m_speed;
					//if (m_info.x > WINCX / 2)
						//if (m_info.x + WINCX / 2 < CScene_Manager::Get_Instance()->Get_SceneSize().x)
							CScroll_Manager::Set_ScrollX(-m_speed);

					current_DoublejumpHeight += m_power;
					//if (current_DoublejumpHeight <= m_DoublejumpHeight)
					//{
					//	m_info.y -= m_power;
					//	CScroll_Manager::Set_ScrollY(m_power);
					//	//if ((m_info.y + WINCY / 2 > 0 && m_info.y < 0) || m_info.y >= 0)
					//}
				}
			}
		}
	}
	else if (bCollLine &&!m_keyPush.isRope)
	{
		if (abs(m_info.y - (fY - m_info.sizeY / 2)) >= 5)
		{
			m_isFall = true;
			if (!m_keyPush.isSkill)
				Player_Jump();
			m_info.y += m_fallSpeed;
			if (m_checkKeepY<m_info.y)
				CScroll_Manager::Set_ScrollY(-m_fallSpeed);
		}
		else
		{
			if (m_checkKeepY < m_info.y)
				CScroll_Manager::Set_ScrollY(-((fY - m_info.sizeY / 2) - m_info.y));
			m_info.y = fY - m_info.sizeY / 2;
			m_isDownJump = false;
			m_moveLock = false;
			m_isJump = false;
			m_keyPush.isJump = false;
			m_keyPush.isDoubleJumpReady = false;
			m_keyPush.isDoubleJump = false;
			m_isFall = false;
			m_DoublejumpHeight = 0;
			current_DoublejumpHeight = 0;
		}
	}
}

void CPlayer::Player_MoveLeft()
{
	if (!m_isJump && !m_isFall && !m_keyPush.isSkill && !m_isHit)
		Set_Animation(m_left_hdc, Animation::WALK, Animation_index::WALK_INDEX);
	m_keyPush.isLeft = true;

	if (m_rect.left >= 0)
	{
		m_currentKey = CurrentKey::CUR_LEFT;
		if (!m_moveLock && !m_isJumpRight)
		{
			if (CKey_Manager::Get_Instance()->Key_Pressing(KEY_F))
			{
				if (!m_isJump)
				{
					m_isJump = true;
					m_isJumpLeft = true;
				}
			}
			if (!m_keyPush.isRope && !m_isFall &&!m_keyPush.isSkill/* && !m_keyPush.isDoubleJump*/)
			{
				m_info.x -= m_speed;
				//if (m_info.x - WINCX / 2 >= 0)
					//if (m_info.x + CScroll_Manager::Get_ScrollX() < WINCX / 2)
						CScroll_Manager::Set_ScrollX(m_speed);
			}
		}
		else if (m_keyPush.isDoubleJump && m_currentKey == jumpDir &&!m_isFall)
		{
			m_info.x -= m_speed;
			//if (m_info.x - WINCX / 2 >= 0)
				//if (m_info.x + CScroll_Manager::Get_ScrollX() < WINCX / 2)
					CScroll_Manager::Set_ScrollX(m_speed);
		}
	}
}

void CPlayer::Player_MoveRight()
{
	if (!m_isJump && !m_isFall && !m_keyPush.isSkill && !m_isHit)
		Set_Animation(m_right_hdc, Animation::WALK, Animation_index::WALK_INDEX);
	m_keyPush.isRight = true;

	if (m_rect.right <= CScene_Manager::Get_Instance()->Get_SceneSize().x)
	{
		m_currentKey = CurrentKey::CUR_RIGHT;
		if (!m_moveLock && !m_isJumpLeft)
		{
			if (CKey_Manager::Get_Instance()->Key_Pressing(KEY_F))
			{
				if (!m_isJump)
				{
					m_isJumpRight = true;
					m_isJump = true;
				}
			}
			if (!m_keyPush.isRope && !m_isFall && !m_keyPush.isSkill/*&& !m_keyPush.isDoubleJump*/)
			{
				m_info.x += m_speed;

				//if (m_info.x > WINCX / 2)
					//if (m_info.x + WINCX / 2 < CScene_Manager::Get_Instance()->Get_SceneSize().x)
						CScroll_Manager::Set_ScrollX(-m_speed);
			}
		}
		else if (m_keyPush.isDoubleJump&& m_currentKey == jumpDir &&!m_isFall)
		{
			m_info.x += m_speed;

			//if (m_info.x > WINCX / 2)
				//if (m_info.x + WINCX / 2 < CScene_Manager::Get_Instance()->Get_SceneSize().x)
					CScroll_Manager::Set_ScrollX(-m_speed);
		}
	}
}

void CPlayer::Player_Idle()
{
	if (m_currentKey == CurrentKey::CUR_LEFT)
		Set_Animation(m_left_hdc, Animation::STAND, Animation_index::STAND_INDEX);
	if (m_currentKey == CurrentKey::CUR_RIGHT)
		Set_Animation(m_right_hdc, Animation::STAND, Animation_index::STAND_INDEX);
}

void CPlayer::Player_Jump()
{
	if (!m_isHit)
	{
		if (m_currentKey == CurrentKey::CUR_LEFT)
			Set_Animation(m_left_hdc, Animation::JUMP, Animation_index::JUMP_INDEX);
		if (m_currentKey == CurrentKey::CUR_RIGHT)
			Set_Animation(m_right_hdc, Animation::JUMP, Animation_index::JUMP_INDEX);
	}
}

void CPlayer::Player_Prone()
{
	if (m_currentKey == CurrentKey::CUR_LEFT)
		Set_Animation(m_left_hdc, Animation::PRONE, Animation_index::PRONE_INDEX);
	if (m_currentKey == CurrentKey::CUR_RIGHT)
		Set_Animation(m_right_hdc, Animation::PRONE, Animation_index::PRONE_INDEX);

	m_info.sizeX = 70;
}

void CPlayer::Player_Swing()
{
	m_keyPush.isAttack = true;
	if (!m_keyPush.isDown)
	{
		if (m_currentKey == CurrentKey::CUR_LEFT)
			Set_Animation(m_left_hdc, Animation::SWING, Animation_index::SWING_INDEX);
		if (m_currentKey == CurrentKey::CUR_RIGHT)
			Set_Animation(m_right_hdc, Animation::SWING, Animation_index::SWING_INDEX);
	}
	else
	{
		if (m_currentKey == CurrentKey::CUR_LEFT)
			Set_Animation(m_left_hdc, Animation::PRONE, Animation_index::PRONE_SWING_INDEX);
		if (m_currentKey == CurrentKey::CUR_RIGHT)
			Set_Animation(m_right_hdc, Animation::PRONE, Animation_index::PRONE_SWING_INDEX);

		m_info.sizeX = 70;
	}
}

void CPlayer::Player_Rope()
{
	const RECT* ropeRect{};
	list<CGameObject*> player = CGameObject_Manager::Get_Instance()->GetObejct(Object_ID::PLAYER);
	if (CCollision_Manager::Collision_Rope(&CGameObject_Manager::Get_Instance()->GetObejct(Object_ID::PLAYER), &CGameObject_Manager::Get_Instance()->GetObejct(Object_ID::ROPE), &ropeRect))
	{
		if (!m_keyPush.isSkill)
		{
			if (CKey_Manager::Get_Instance()->Key_Pressing(KEY_DOWN))
			{
				float dis = m_info.x - (ropeRect->right + ropeRect->left) / 2;
				m_info.x -= dis;
				//CScroll_Manager::Set_ScrollX(dis);

				if (m_rect.top <= ropeRect->bottom - WINCY)
				{
					m_info.y += m_speed;
					Set_Animation(m_left_hdc, Animation::ROPING, Animation_index::ROPE_INDEX);
					m_keyPush.isRope = true;
					m_keyPush.isRopeMove = true;
					m_isJump = true;
					m_keyPush.isDoubleJump = false;
					m_keyPush.isDoubleJumpReady = false;
					//CScroll_Manager::Set_ScrollY(-m_speed);
				}

				UpdateRect_GameObject();

				if (m_rect.top >= ropeRect->bottom - WINCY)
				{
					if (m_keyPush.isRope)
						m_isJump = false;
					m_keyPush.isRope = false;
					m_isJumpRight = false;
					m_isJumpLeft = false;
					m_keyPush.isRopeMove = false;
				}
			}



			if (CKey_Manager::Get_Instance()->Key_Pressing(KEY_UP))
			{
				float dis = m_info.x - (ropeRect->right + ropeRect->left)/2;
				m_info.x -= dis;
				//CScroll_Manager::Set_ScrollX(dis);

				if (m_rect.bottom >= ropeRect->top - WINCY)
				{
					int scrollY = CScroll_Manager::Get_ScrollY();
					m_info.y -= m_speed;
					Set_Animation(m_left_hdc, Animation::ROPING, Animation_index::ROPE_INDEX);
					m_keyPush.isRope = true;
					m_keyPush.isRopeMove = true;
					m_keyPush.isDoubleJump = false;
					m_keyPush.isDoubleJumpReady = false;
					//CScroll_Manager::Set_ScrollY(m_speed);
				}
				UpdateRect_GameObject();

				if (m_rect.bottom <= ropeRect->top - WINCY)
				{
					if (m_keyPush.isRope)
						m_isJump = false;
					m_keyPush.isRope = false;
					m_isJump = false;
					m_isJumpRight = false;
					m_isJumpLeft = false;
					m_keyPush.isRopeMove = false;
				}

			}
		}
	}
}

void CPlayer::Player_Hit()
{
	if (m_currentKey == CurrentKey::CUR_LEFT)
		Set_Animation(m_left_hdc, Animation::ALERT, Animation_index::ALERT_INDEX);
	if (m_currentKey == CurrentKey::CUR_RIGHT)
		Set_Animation(m_right_hdc, Animation::ALERT, Animation_index::ALERT_INDEX);
}

void CPlayer::Player_StatUiOpen()
{
	if (m_isStatOpen)
		m_isStatOpen = false;
	else
		m_isStatOpen = true;
}

void CPlayer::Player_InventoryOpen()
{
	if (m_isInventoryOpen)
		m_isInventoryOpen = false;
	else
		m_isInventoryOpen = true;
}

void CPlayer::Player_Skill(Animation animScene, Animation_index frameEnd)
{
	m_keyPush.isSkill = true;
	if (m_currentKey == CurrentKey::CUR_LEFT)
		Set_Animation(m_left_hdc, animScene, frameEnd);
	if (m_currentKey == CurrentKey::CUR_RIGHT)
		Set_Animation(m_right_hdc, animScene, frameEnd);
}

void CPlayer::Is_OffSet()
{
	float scrollX = CScroll_Manager::Get_ScrollX();
	float scrollY = CScroll_Manager::Get_ScrollY();
	float X = m_info.x + scrollX;
	float Y = m_info.y + scrollY;
	if ((WINCX >> 1) + 100 < X)
		CScroll_Manager::Set_ScrollX(-m_speed);
	if ((WINCX >> 1) - 100 > X)
		CScroll_Manager::Set_ScrollX(m_speed);
	if ((WINCY >> 1)+ 100 < Y)
		CScroll_Manager::Set_ScrollY(-m_speed);
	if ((WINCY >> 1)- 100 > Y)
		CScroll_Manager::Set_ScrollY(m_speed);
}

void CPlayer::Is_LevelUp()
{
	while (m_data.exp >= m_data.maxExp)
	{
		CLevelUp::Create(this);
		m_data.level++;
		m_data.maxHp += 500;
		m_data.hp = m_data.maxHp;
		m_data.maxAttack += 100;
		m_data.minAttack += 100;
		m_data.exp -= m_data.maxExp;
		m_data.maxExp += 500;
	}
}

void CPlayer::Set_Animation(HDC hdc, Animation animScene, Animation_index frameEnd)
{
	if (m_animFrame.frame_animation != animScene)
		m_animFrame.frame_start = 0;

	m_hdc = hdc;
	m_animFrame.frame_animation = animScene;
	m_animFrame.frame_end = frameEnd;
	m_info.sizeX = 48;
	m_info.sizeY = 66;
}
