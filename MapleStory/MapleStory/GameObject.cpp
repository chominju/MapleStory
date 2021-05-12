#include "stdafx.h"
#include "GameObject.h"

CGameObject::CGameObject()
	:m_isDead(false)
	, m_speed(0.f)
{
	ZeroMemory(&m_rect, sizeof(RECT));
}

CGameObject::~CGameObject()
{
}

void CGameObject::Play_Animation()
{
	if (m_animFrame.frame_time + m_animFrame.frame_speed < GetTickCount())
	{
		++m_animFrame.frame_start;
		m_animFrame.frame_time = GetTickCount();
		if (m_animFrame.frame_start >= m_animFrame.frame_end)
			m_animFrame.frame_start = 0;
	}
}
