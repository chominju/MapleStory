#include "stdafx.h"
#include "DoubleJump.h"
#include "Bitmap_Manager.h"
#include "Player.h"
#include "GameObject_Manager.h"

//CGameObject* CDoubleJump::m_instance;

CDoubleJump::CDoubleJump()
{
}

CDoubleJump::~CDoubleJump()
{
	//m_instance = nullptr;
}

int CDoubleJump::Ready_GameObject()
{
	m_left_hdc = CBitmap_Manager::Get_Instance()->Get_memDC(L"DoubleJump_Left");
	m_right_hdc = CBitmap_Manager::Get_Instance()->Get_memDC(L"DoubleJump_Right");

	m_info.sizeX = 342;
	m_info.sizeY = 145;

	m_currentKey = m_target->Get_CurrentKey();

	if (m_currentKey == CurrentKey::CUR_LEFT)
	{
		m_hdc = m_left_hdc;
		m_info.x = m_target->GetRect()->right;
	}
	else if (m_currentKey == CurrentKey::CUR_RIGHT)
	{
		m_hdc = m_right_hdc;
		m_info.x = m_target->GetRect()->left;
	}
	m_info.y = m_target->Get_Info()->y + 70;

	m_animFrame.frame_animation = 0;
	m_animFrame.frame_start = 0;
	m_animFrame.frame_end = 7;
	m_animFrame.frame_speed = 100;
	m_animFrame.frame_time = GetTickCount();

	return S_OK;
}

int CDoubleJump::Update_GameObject()
{
	Set_Target(CGameObject_Manager::Get_Instance()->GetPlayer());
	if (m_currentKey == CurrentKey::CUR_LEFT)
	{
		m_hdc = m_left_hdc;
		m_info.x = m_target->GetRect()->right + m_info.sizeX / 2;
	}
	else if (m_currentKey == CurrentKey::CUR_RIGHT)
	{
		m_hdc = m_right_hdc;
		m_info.x = m_target->GetRect()->left - m_info.sizeX / 2;
	}
	m_info.y = m_target->Get_Info()->y -30;
	Play_Animation();

	if (m_isDead)
		return OBJ_DEAD;

	return OBJ_NOEVENT;
}

void CDoubleJump::Late_Update_GameObject()
{
}

CGameObject * CDoubleJump::Create(CGameObject * player)
{
	
	CGameObject*instance = new CDoubleJump;
	instance->Set_Target(player);
	instance->Ready_GameObject();
	CGameObject_Manager::Get_Instance()->Add_GameObject_Manager(Object_ID::BUFF_SKILL, instance);
	CSoundMgr::Get_Instance()->PlaySound(L"DoubleJump_Use.mp3", CSoundMgr::PLAYER);

	return instance;
}
