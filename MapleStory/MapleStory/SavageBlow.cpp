#include "stdafx.h"
#include "SavageBlow.h"
#include "Bitmap_Manager.h"
#include "Player.h"
#include "GameObject_Manager.h"

CGameObject* CSavageBlow::m_instance = nullptr;

CSavageBlow::CSavageBlow()
{
}

CSavageBlow::~CSavageBlow()
{
	m_instance = nullptr;
}

int CSavageBlow::Ready_GameObject()
{
	m_left_hdc = CBitmap_Manager::Get_Instance()->Get_memDC(L"SavageBlow_Left");
	m_right_hdc = CBitmap_Manager::Get_Instance()->Get_memDC(L"SavageBlow_Right");

	m_info.sizeX = 408;
	m_info.sizeY = 200;

	m_currentKey = m_target->Get_CurrentKey();

	if (m_currentKey == CurrentKey::CUR_LEFT)
	{
		m_hdc = m_left_hdc;
		m_info.x = m_target->GetRect()->left - m_info.sizeX / 2;
	}
	else if (m_currentKey == CurrentKey::CUR_RIGHT)
	{
		m_hdc = m_right_hdc;
		m_info.x = m_target->GetRect()->right + m_info.sizeX / 2;
	}
	m_info.y = m_target->GetInfo()->y;

	m_animFrame.frame_animation = 0;
	m_animFrame.frame_start = 0;
	m_animFrame.frame_end = 11;
	m_animFrame.frame_speed = 50;
	m_animFrame.frame_time = GetTickCount();

	return 0;
}

void CSavageBlow::Late_Update_GameObject()
{
}

CGameObject * CSavageBlow::Create(CGameObject * player)
{
	if (nullptr == m_instance)
	{
		m_instance = new CSavageBlow;
		m_instance->Set_Target(player);
		m_instance->Ready_GameObject();
		CGameObject_Manager::Get_Instance()->Add_GameObject_Manager(Object_ID::ATTACK_SKILL, m_instance);
	}
	return m_instance;
}
