#include "stdafx.h"
#include "Scroll_Manager.h"
#include "Scene_Manager.h"


Pos_int CScroll_Manager::m_scrollPos{};

CScroll_Manager::CScroll_Manager()
{
}


CScroll_Manager::~CScroll_Manager()
{
}

bool CScroll_Manager::ScrollLock()
{
	if (0 < m_scrollPos.x)
		m_scrollPos.x = 0;
	if (0 > m_scrollPos.y)
		m_scrollPos.y = 0;
	if (WINCX - CScene_Manager::Get_Instance()->Get_SceneSize().x > m_scrollPos.x)
		m_scrollPos.x = WINCX - CScene_Manager::Get_Instance()->Get_SceneSize().x;
	if (CScene_Manager::Get_Instance()->Get_SceneSize().y - WINCY - 12 < m_scrollPos.y)
	{
		m_scrollPos.y = CScene_Manager::Get_Instance()->Get_SceneSize().y  - WINCY -12;
		return true;
	}
	return false;
}
