#include "stdafx.h"
#include "Rope.h"
#include "Scroll_Manager.h"


CRope::CRope()
{
}


CRope::~CRope()
{
}

int CRope::Ready_GameObject()
{
	m_info.sizeX = 20;
	m_info.sizeY = 110;
	return 0;
}

int CRope::Update_GameObject()
{

	return 0;
}

void CRope::Late_Update_GameObject()
{
}

void CRope::Render_GameObject(HDC hDC)
{
	UpdateRect_GameObject();
	int X = CScroll_Manager::Get_ScrollX();
	int Y = CScroll_Manager::Get_ScrollY();
	Rectangle(hDC, m_rect.left +X, m_rect.top-WINCY +Y, m_rect.right + X, m_rect.bottom - WINCY + Y);
}

void CRope::Release_GameObject()
{
}

void CRope::UpdateRect_GameObject()
{
	m_rect.left = static_cast<LONG>(m_info.x - (m_info.sizeX / 2));
	m_rect.top = static_cast<LONG>(m_info.y - (m_info.sizeY / 2));
	m_rect.right = static_cast<LONG>(m_info.x + (m_info.sizeX / 2));
	m_rect.bottom = static_cast<LONG>(m_info.y + (m_info.sizeY / 2));
}

CGameObject * CRope::Create()
{
	CGameObject * instance = new CRope();
	if (0 > instance->Ready_GameObject())
	{
		Safe_Delete(instance);
		return nullptr;
	}
	return instance;
}
