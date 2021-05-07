#include "stdafx.h"
#include "Editor_Manager.h"
#include "Key_Manager.h"
#include "Line_Manager.h"


CEditor_Manager::CEditor_Manager()
{
}


CEditor_Manager::~CEditor_Manager()
{
	Release_Editor_Manager();
}

void CEditor_Manager::Ready_Editor_Manager()
{
	m_hdc = GetDC(g_hwnd);
}

void CEditor_Manager::Update_Editor_Manager()
{
	CKey_Manager::Get_Instance()->Update_Key_Manager();
	CLine_Manager::Get_Instance()->Update_Line_Manager();
}

void CEditor_Manager::Render_Editor_Manager()
{
	Rectangle(m_hdc, 0, 0, WINCX, WINCY);
	CLine_Manager::Get_Instance()->Render_Line_Manager(m_hdc);
}

void CEditor_Manager::Release_Editor_Manager()
{
	ReleaseDC(g_hwnd, m_hdc);
	CKey_Manager::Destroy_Instance();
	CLine_Manager::Destroy_Instance();
}
