#include "stdafx.h"
#include "Skill.h"
#include "Scroll_Manager.h"
#include "GameObject_Manager.h"
CSkill::CSkill()
{
}

CSkill::~CSkill()
{
}

int CSkill::Ready_GameObject()
{
	return 0;
}

int CSkill::Update_GameObject()
{
	Set_Target(CGameObject_Manager::Get_Instance()->GetPlayer());
	if (m_currentKey == CurrentKey::CUR_LEFT)
		m_info.x = m_target->GetRect()->left - m_info.sizeX / 2;
	else if (m_currentKey == CurrentKey::CUR_RIGHT)
		m_info.x = m_target->GetRect()->right + m_info.sizeX / 2;
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

void CSkill::Late_Update_GameObject()
{
}

void CSkill::Render_GameObject(HDC hDC)
{
	UpdateRect_GameObject();
	int scrollX = CScroll_Manager::Get_ScrollX();
	int scrollY = CScroll_Manager::Get_ScrollY();
	GdiTransparentBlt(hDC, // �׸��� �����ϰ��� �ϴ� ���. 
		m_rect.left + scrollX,//��ġ x,y
		m_rect.top + scrollY,
		m_info.sizeX,// ũ�� xy
		m_info.sizeY,
		m_hdc,// ���� �� ���
		m_animFrame.frame_start * m_info.sizeX, m_animFrame.frame_animation * m_info.sizeY,// �׸��� ���� ��ġ x,y
		m_info.sizeX,// �׸����� �ϴ� ������ ũ�� x,y
		m_info.sizeY,
		RGB(255, 255, 255));
}

void CSkill::Release_GameObject()
{
}

void CSkill::UpdateRect_GameObject()
{
	m_rect.left = static_cast<LONG>(m_info.x - (m_info.sizeX / 2));
	m_rect.top = static_cast<LONG>(m_info.y - (m_info.sizeY / 2));
	m_rect.right = static_cast<LONG>(m_info.x + (m_info.sizeX / 2));
	m_rect.bottom = static_cast<LONG>(m_info.y + (m_info.sizeY / 2));
}

void CSkill::Play_Animation()
{
	if (m_animFrame.frame_time + m_animFrame.frame_speed < GetTickCount())
	{
		++m_animFrame.frame_start;
		m_animFrame.frame_time = GetTickCount();
		if (m_animFrame.frame_start >= m_animFrame.frame_end)
			Set_IsDead();
	}
}
