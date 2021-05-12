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
	//CMyMap::Get_Instance()->Update_MyMap();
	CKey_Manager::Get_Instance()->Update_Key_Manager();
	CScene_Manager::Get_Instance()->Update_Scene_Manager();
	//CLine_Manager::Get_Instance()->Update_Line_Manager();
}

void CEditor_Manager::Render_Editor_Manager()
{
	//Rectangle(m_hdc, 0, 0, WINCX, WINCY);


	/*HDC m_MemDC;
	HBITMAP m_OldBitmap;
	HBITMAP m_Bitmap;

	HDC hDC = GetDC(g_hwnd);
	m_MemDC = CreateCompatibleDC(hDC);
	m_Bitmap = (HBITMAP)LoadImage(NULL, L"../Image/player_alert1.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
	m_OldBitmap = (HBITMAP)SelectObject(m_MemDC, m_Bitmap);

	GdiTransparentBlt(hDC, 10, 10, 68, 82, m_MemDC, 0, 0, 68, 82, RGB(255, 0, 255));*/

	CScene_Manager::Get_Instance()->Render_Scene_Manager(m_hdc);
	//CMyMap::Get_Instance()->Render_MyMap(m_hdc);
	//CLine_Manager::Get_Instance()->Render_Line_Manager(m_hdc);
}

void CEditor_Manager::Release_Editor_Manager()
{
	ReleaseDC(g_hwnd, m_hdc);
	CKey_Manager::Destroy_Instance();
	CLine_Manager::Destroy_Instance();
}
