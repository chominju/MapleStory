#include "stdafx.h"
#include "Field1.h"
#include "Tool_Key_Manager.h"
#include "Tool_Line_Manager.h"
#include "Tool_SaveData.h"
#include "Tool_LoadData.h"
#include "Tool_Scroll_Manager.h"
#include "Tool_Scene_Manager.h"

CField1::CField1()
{
}

CField1::~CField1()
{
}

int CField1::Ready_Scene()
{
	CLine_Manager::Get_Instance()->Release_Line_Manager();
	CScroll_Manager::Reset_ScrollX();
	CScroll_Manager::Reset_ScrollY();
	return 0;
}

void CField1::Update_Scene()
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

void CField1::Render_Scene(HDC hDC)
{
	POINT pt{ 0,(LONG)m_startPos.y - WINCY };
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

void CField1::Release_Scene()
{
}

CScene * CField1::Create()
{
	CScene* instance = new CField1;
	if (0 > instance->Ready_Scene())
	{
		Safe_Delete(instance);
		return nullptr;
	}

	return instance;
}
