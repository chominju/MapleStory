#include "stdafx.h"
#include "Kerning_City.h"
#include "Tool_Key_Manager.h"
#include "Tool_Line_Manager.h"
#include "Tool_SaveData.h"
#include "Tool_LoadData.h"
#include "Tool_Scroll_Manager.h"
#include "Tool_Scene_Manager.h"

CKerning_City::CKerning_City()
{

}
CKerning_City::~CKerning_City()
{

}

int CKerning_City::Ready_Scene()
{
	CLine_Manager::Get_Instance()->Release_Line_Manager();
	CScroll_Manager::Reset_ScrollX();
	CScroll_Manager::Reset_ScrollY();
	return 0;
}

void CKerning_City::Update_Scene()
{
	CKey_Manager::Get_Instance()->Update_Key_Manager();
	CLine_Manager::Get_Instance()->Update_Line_Manager();
	if (CKey_Manager::Get_Instance()->Key_Down(KEY_S))
		CSaveData::Get_Instance()->Save_Data(m_saveName);
	if (CKey_Manager::Get_Instance()->Key_Down(KEY_L))
		CLoadData::Get_Instance()->Load_Line(m_saveName);
	if (CKey_Manager::Get_Instance()->Key_Down(KEY_BACK))
		CScene_Manager::Get_Instance()->Change_Scene_Manager(CScene_Manager::TOOL_ID::TOOL_MENU);
}

void CKerning_City::Render_Scene(HDC hDC)
{
	POINT pt{ 0,m_startPos.y - WINCY };
	pt.x -= CScroll_Manager::Get_ScrollX();
	pt.y -= CScroll_Manager::Get_ScrollY();
	BitBlt(hDC,// 복사하고자 하는 대상 
		0, 0,// 그릴 시작 위치
		WINCX, WINCY, // 그림의 크기 
		m_hdc,//복사할 대상 
		pt.x, pt.y, //그림에서의 시작 위치 
		SRCCOPY); // 그릴 형식. 
	CLine_Manager::Get_Instance()->Render_Line_Manager(hDC);
}

void CKerning_City::Release_Scene()
{
}

CScene * CKerning_City::Create()
{
	CScene* instance = new CKerning_City;
	if (0 > instance->Ready_Scene())
	{
		Safe_Delete(instance);
		return nullptr;
	}

	return instance;
}
