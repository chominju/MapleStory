#include "stdafx.h"
#include "Tool_Editor_Manager.h"
#include "Tool_Key_Manager.h"
#include "Tool_Line_Manager.h"
#include "Tool_Scene_Manager.h"
#include "Tool_LoadData.h"
#include "Tool_MyMap.h"


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
	CLoadData::Get_Instance()->Load_Image();
	
	CScene_Manager::Get_Instance()->Change_Scene_Manager(CScene_Manager::TOOL_ID::TOOL_MENU);
	//CMyMap::Create_MyMap(L"Kerning_City");
	
	
}

void CEditor_Manager::Update_Editor_Manager()
{
	CKey_Manager::Get_Instance()->Update_Key_Manager();
	CScene_Manager::Get_Instance()->Update_Scene_Manager();
}

void CEditor_Manager::Render_Editor_Manager()
{
	CScene_Manager::Get_Instance()->Render_Scene_Manager(m_hdc);
}

void CEditor_Manager::Release_Editor_Manager()
{
	ReleaseDC(g_hwnd, m_hdc);
	CKey_Manager::Destroy_Instance();
	CLine_Manager::Destroy_Instance();
}
