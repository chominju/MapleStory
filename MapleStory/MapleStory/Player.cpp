#include "stdafx.h"
#include "Player.h"
#include "Key_Manager.h"
#include "LoadData.h"
#include "MyBitmap.h"
#include "Bitmap_Manager.h"
#include "Line_Manager.h"
#include "Scroll_Manager.h"
#include "Scene_Manager.h"


CGameObject * CPlayer::m_instance = nullptr;

CPlayer::CPlayer()
	: m_isJump(false)
	,m_isDoubleJump(false)
	,m_isJumpLeft(false)
	,m_isJumpRight(false)
	,m_isDownJump(false)
	,m_moveLock(false)
	, m_power(0.f)
	, current_jumpHeight(0)
	, m_currentKey(CurrentKey::CUR_RIGHT)

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

	m_hdc = m_left_hdc;
	m_info.x = 100;
	m_info.y = 100;
	m_info.sizeX = 48;
	m_info.sizeY = 66;


	/*auto temp = CLoadData::Get_Instance()->Get_Map();
	auto& iter = find_if(temp->begin(), temp->end(), [&](auto pair){
		return !lstrcmp(L"Player1", pair.first);
	});
	m_currnet_pos.x = 100;
	m_currnet_pos.y = 100;

	m_hdc = iter->second->Get_memDC();*/
	m_speed = 4.f;
	jumpHeight = 100;
	m_power = 5;
	fall = 5;
	UpdateRect_GameObject();


	m_animFrame.frame_start = 0;
	m_animFrame.frame_end = Animation_index::STAND_INDEX;
	m_animFrame.frame_animation = Animation::STAND;
	m_animFrame.frame_speed = 200;
	m_animFrame.frame_time = GetTickCount();

	m_beforeY = m_info.y;

	return 0;
}

int CPlayer::Update_GameObject()
{
	//if (CKey_Manager::Get_Instance()->Key_Down(KEY_LEFT))
	if (!m_keyPush.isAttack)
	{
		if (CKey_Manager::Get_Instance()->Key_Pressing(KEY_LEFT))
			Player_MoveLeft();
		if (CKey_Manager::Get_Instance()->Key_Up(KEY_LEFT))
			m_keyPush.isLeft = false;


		if (CKey_Manager::Get_Instance()->Key_Pressing(KEY_RIGHT))
			Player_MoveRight();
		if (CKey_Manager::Get_Instance()->Key_Up(KEY_RIGHT))
			m_keyPush.isRight = false;


		if (CKey_Manager::Get_Instance()->Key_Pressing(KEY_UP))
		{
			/*m_info.y -= m_speed;
			if (m_info.y <= WINCY / 2 - CScroll_Manager::Get_ScrollY())
				CScroll_Manager::Set_ScrollY(-m_speed);*/
		}
	}

	if (!m_isDownJump)
	{
		if (CKey_Manager::Get_Instance()->Key_Pressing(KEY_DOWN)) // 아래점프
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
					m_info.y -= m_speed;
				else
				{
					jump_before = m_info.y;
					m_keyPush.isJump = true;
					m_isDownJump = true;
					m_moveLock = true;
				}
				// m_info.sizeY;
			}
			/*	m_info.y += m_speed;
				if (m_info.y >= WINCY / 2 + CScroll_Manager::Get_ScrollY())
					CScroll_Manager::Set_ScrollY(+m_speed);*/
		}
	}
	if (CKey_Manager::Get_Instance()->Key_Up(KEY_DOWN)) // 아래점프
		m_keyPush.isDown = false;

	if (GetAsyncKeyState(VK_SPACE) & 0x8000)
	{
		m_info.y--;
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
					jump_before = m_info.y;
					m_isJump = true;

				}
			}
		}
	}
	
	if (m_isPortal)	// 포탈 위
		if (CKey_Manager::Get_Instance()->Key_Down(KEY_UP))
			return MOVE_PORTAL;

	if (CKey_Manager::Get_Instance()->Key_Pressing(KEY_A))
		Player_Swing();
	if (CKey_Manager::Get_Instance()->Key_Up(KEY_A))
		m_keyPush.isAttack = false;


	if (!m_keyPush.isJump && !m_keyPush.isLeft &&!m_keyPush.isRight &&!m_keyPush.isDown && !m_keyPush.isAttack)
		Player_Idle();
	if (m_isJump || m_isDownJump)
		Player_Jump();



	//if (m_info.y <= 100 && m_isJump && current_jumpHeight <= jumpHeight)
		//CScroll_Manager::Set_ScrollY(2);
	//else if (m_info.y > 300 && m_isJump)
	//	CScroll_Manager::Set_ResetY();
	return 0;
}

void CPlayer::Late_Update_GameObject()
{
	IsJump();
	Play_Animation();
}

void CPlayer::Render_GameObject(HDC hDC)
{
	UpdateRect_GameObject();
	//if (m_hdc == nullptr)
	//	return;

	int scrollX = CScroll_Manager::Get_ScrollX();
	int scrollY = CScroll_Manager::Get_ScrollY();

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
	
	//GdiTransparentBlt(hDC, // 그림을 복사하고자 하는 대상. 
	//	m_info.x,//위치 x,y
	//	m_info.y,
	//	m_info.sizeX,// 크기 xy
	//	m_info.sizeY,
	//	m_hdc,// 복사 할 대상
	//	0, 0,// 그림의 시작 위치 x,y
	//	m_info.sizeX,// 그리고자 하는 영역의 크기 x,y
	//	m_info.sizeY,
	//	RGB(255, 255, 255));

	//BitBlt(hDC,// 복사하고자 하는 대상 
	//	m_info.x, m_info.y,// 그릴 시작 위치
	//	WINCX, WINCY, // 그림의 크기 
	//	m_hdc,//복사할 대상 
	//	0, 0, //그림에서의 시작 위치 
	//	SRCCOPY); // 그릴 형식. 
	


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
	}

	return m_instance;
}

void CPlayer::IsJump()
{
	float fY = 0.f;
	bool bCollLine = CLine_Manager::Get_Instance()->Collision_Line_Manager(this,m_info.x, m_rect.bottom/*m_info.y + m_info.sizeY / 2*/, &fY, m_currentKey);
	if (m_isJump)
	{
		if (current_jumpHeight <= jumpHeight)
		{
			m_info.y -= m_power;
			if ((m_info.y + WINCY / 2 > 0 && m_info.y < 0)|| m_info.y>=0)
				CScroll_Manager::Set_ScrollY(m_power);

			current_jumpHeight += m_power;
		}
		else if (bCollLine)
		{
			if (abs(m_info.y - (fY - m_info.sizeY / 2)) >= 5)
			{
				m_info.y += fall;
				if ((m_info.y + WINCY / 2 > 0 && m_info.y < 0) || m_info.y >= 0)
					CScroll_Manager::Set_ScrollY(-fall);
			}
			else
			{
				m_info.y = fY - m_info.sizeY / 2;
				//m_difY = jump_before - m_info.y;
				m_difY= jump_before - m_info.y;
				//CScroll_Manager::Set_ScrollY(m_difY);
				current_jumpHeight = 0;
				m_isJump = false;
				m_isJumpRight = false;
				m_isJumpLeft = false;
				m_moveLock = false;
				m_keyPush.isJump = false;
			}
		}

		/*if (bCollLine && (current_jumpHeight<=0))
		{
			m_isJump = false;
			m_power *= -1;
			current_jumpHeight = 0;
		}
		else if (bCollLine && (m_rect.bottom >= fY &&m_power < 0))
		{
			m_isJump = false;
			m_power *= -1;
			current_jumpHeight = 0;
		}*/
	}
	else if (bCollLine)
	{
		if (abs(m_info.y - (fY - m_info.sizeY / 2)) >= 5)
		{
			m_info.y += fall;
			CScroll_Manager::Set_ScrollY(-fall);
		}
		else
		{
			CScroll_Manager::Set_ScrollY(-((fY - m_info.sizeY / 2)-m_info.y));
			m_info.y = fY - m_info.sizeY / 2;
			m_isDownJump = false;
			m_moveLock = false;
			m_isJump = false;
			m_keyPush.isJump = false;
		}
	}
}

void CPlayer::Player_MoveLeft()
{
	if (!m_isJump)
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
					jump_before = m_info.y;
				}
			}
			//if (CKey_Manager::Get_Instance()->Key_Up(KEY_C))
			//	m_isJump = true;
			m_info.x -= m_speed;

			if (m_info.x - WINCX / 2 >= 0)
				if (m_info.x + CScroll_Manager::Get_ScrollX() < WINCX / 2)
					CScroll_Manager::Set_ScrollX(m_speed);
		}
	}
}

void CPlayer::Player_MoveRight()
{
	if (!m_isJump)
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
					jump_before = m_info.y;
				}
			}
			/*if (CKey_Manager::Get_Instance()->Key_Up(KEY_C))
				m_isJump = true;*/

			m_info.x += m_speed;

			if (m_info.x > WINCX / 2)
				if (m_info.x + WINCX / 2 < CScene_Manager::Get_Instance()->Get_SceneSize().x)
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
	if (m_currentKey == CurrentKey::CUR_LEFT)
		Set_Animation(m_left_hdc, Animation::JUMP, Animation_index::JUMP_INDEX);
	if (m_currentKey == CurrentKey::CUR_RIGHT)
		Set_Animation(m_right_hdc, Animation::JUMP, Animation_index::JUMP_INDEX);
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

void CPlayer::Set_Animation(HDC hdc, Animation animScene, Animation_index frameEnd)
{
	if (m_animFrame.frame_animation != animScene)
			m_animFrame.frame_start = 0;

		//if (Animation::JUMP == animScene || Animation::DEAD == animScene || Animation::PRONE == animScene)
	m_hdc = hdc;
	m_animFrame.frame_animation = animScene;
	m_animFrame.frame_end = frameEnd;
	m_info.sizeX = 48;
	m_info.sizeY = 66;
}
