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
