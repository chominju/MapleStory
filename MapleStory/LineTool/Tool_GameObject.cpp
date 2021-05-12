#include "stdafx.h"
#include "Tool_GameObject.h"


CGameObject::CGameObject()
	:m_bIsDead(false)
	, m_fSpeed(0.f)
	, m_fAngle(0.f)
{
	ZeroMemory(&m_info, sizeof(Object_Info)); 
	ZeroMemory(&m_rect, sizeof(RECT));
}


CGameObject::~CGameObject()
{
}

void CGameObject::Set_Pos(float fX, float fY)
{
	m_info.x = fX; 
	m_info.y = fY; 
}

const RECT * CGameObject::Get_Rect() const
{
	return &m_rect;
}

const Object_Info * CGameObject::Get_Info() const
{
	return &m_info;
}

void CGameObject::UpdateRect_GameObject()
{
	m_rect.left = LONG(m_info.x - (m_info.sizeX >> 1));
	m_rect.top = static_cast<LONG>(m_info.y - (m_info.sizeY >> 1));
	m_rect.right = static_cast<LONG>(m_info.x + (m_info.sizeX * 0.5f));
	m_rect.bottom = static_cast<LONG>(m_info.y + (m_info.sizeY / 2));
}
