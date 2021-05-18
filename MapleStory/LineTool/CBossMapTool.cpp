#include "stdafx.h"
#include "CBossMapTool.h"
#include "Tool_Key_Manager.h"
#include "Tool_Line_Manager.h"
#include "Tool_SaveData.h"
#include "Tool_LoadData.h"
#include "Tool_Scroll_Manager.h"
#include "Tool_Scene_Manager.h"

CBossMapTool::CBossMapTool()
{
}

CBossMapTool::~CBossMapTool()
{
}

int CBossMapTool::Ready_Scene()
{
	CLine_Manager::Get_Instance()->Release_Line_Manager();
	CScroll_Manager::Reset_ScrollX();
	CScroll_Manager::Reset_ScrollY();
	return 0;
}

void CBossMapTool::Update_Scene()
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

void CBossMapTool::Render_Scene(HDC hDC)
{
	POINT pt{ 0,m_startPos.y - WINCY };
	pt.x -= CScroll_Manager::Get_ScrollX();
	pt.y -= CScroll_Manager::Get_ScrollY();
	BitBlt(hDC,// �����ϰ��� �ϴ� ��� 
		0, 0,// �׸� ���� ��ġ
		WINCX, WINCY, // �׸��� ũ�� 
		m_hdc,//������ ��� 
		pt.x, pt.y, //�׸������� ���� ��ġ 
		SRCCOPY); // �׸� ����. 
	CLine_Manager::Get_Instance()->Render_Line_Manager(hDC);
}

void CBossMapTool::Release_Scene()
{
}

CScene * CBossMapTool::Create()
{
	CScene* instance = new CBossMapTool;
	if (0 > instance->Ready_Scene())
	{
		Safe_Delete(instance);
		return nullptr;
	}

	return instance;
}
