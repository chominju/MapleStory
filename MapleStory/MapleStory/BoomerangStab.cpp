#include "stdafx.h"
#include "BoomerangStab.h"
#include "Bitmap_Manager.h"
#include "Player.h"
#include "GameObject_Manager.h"

CGameObject* CBoomerangStab::m_instance = nullptr;

CBoomerangStab::CBoomerangStab()
{
}

CBoomerangStab::~CBoomerangStab()
{
	m_instance = nullptr;
}

int CBoomerangStab::Ready_GameObject()
{
	m_left_hdc = CBitmap_Manager::Get_Instance()->Get_memDC(L"BoomerangStab_Left");
	m_right_hdc = CBitmap_Manager::Get_Instance()->Get_memDC(L"BoomerangStab_Right");

	m_info.sizeX = 580;
	m_info.sizeY = 185;

	m_currentKey = m_target->Get_CurrentKey();

	if (m_currentKey == CurrentKey::CUR_LEFT)
	{
		m_hdc = m_left_hdc;
		m_info.x = (float)(m_target->GetRect()->left - m_info.sizeX / 2) + 200;
	}
	else if (m_currentKey == CurrentKey::CUR_RIGHT)
	{
		m_hdc = m_right_hdc;
		m_info.x = (float)(m_target->GetRect()->right + m_info.sizeX / 2) - 200;
	}
	m_info.y = m_target->Get_Info()->y;

	m_animFrame.frame_animation = 0;
	m_animFrame.frame_start = 0;
	m_animFrame.frame_end = 15;
	m_animFrame.frame_speed = 40;
	m_animFrame.frame_time = GetTickCount();

	m_damage = 7;
	m_hitMonsterNum = 6;
	m_hitNum = 2;

	return 0;
}

int CBoomerangStab::Update_GameObject()
{
	Set_Target(CGameObject_Manager::Get_Instance()->GetPlayer());
	if (m_currentKey == CurrentKey::CUR_LEFT)
		m_info.x = (float)m_target->GetRect()->left - m_info.sizeX / 2 + 50;
	else if (m_currentKey == CurrentKey::CUR_RIGHT)
		m_info.x = (float)m_target->GetRect()->right + m_info.sizeX / 2 - 50;
	m_info.y = m_target->Get_Info()->y;
	Play_Animation();

	if (m_isDead)
	{
		for (auto & monster : CGameObject_Manager::Get_Instance()->GetObejct(Object_ID::MONSTER))
		{
			monster->Set_IsSkillHit(false);
		}
		return OBJ_DEAD;
	}

	return OBJ_NOEVENT;
}

void CBoomerangStab::Late_Update_GameObject()
{
}

CGameObject * CBoomerangStab::Create(CGameObject * player)
{
	if (nullptr == m_instance)
	{
		m_instance = new CBoomerangStab;
		m_instance->Set_Target(player);
		m_instance->Ready_GameObject();
		CGameObject_Manager::Get_Instance()->Add_GameObject_Manager(Object_ID::ATTACK_SKILL, m_instance);
		CSoundMgr::Get_Instance()->PlaySound(L"BoomerangStab_Use.mp3", CSoundMgr::PLAYER);
	}
	return m_instance;
}
