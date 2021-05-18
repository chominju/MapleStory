#include "stdafx.h"
#include "Tool_Scene_Manager.h"
#include "MyMenu.h"
#include "Kerning_City.h"
#include "Field1.h"
#include "CBossMapTool.h"
CScene_Manager* CScene_Manager::m_pInstance =nullptr;
CScene_Manager::CScene_Manager()
	:m_pScene(nullptr)
, m_eCurScene(TOOL_END)
, m_eNextScene(TOOL_END)

{
}


CScene_Manager::~CScene_Manager()
{
	Release_Scene_Manager(); 
}

void CScene_Manager::Change_Scene_Manager(TOOL_ID eNextScene)
{
	m_eNextScene = eNextScene;
	if (m_eCurScene != m_eNextScene)
	{
		//씬이 교체되야 하는 상황. 
		Safe_Delete(m_pScene);
		switch (m_eNextScene)
		{
		case CScene_Manager::TOOL_ID::TOOL_MENU:
			m_pScene = CMyMenu::Create();
			break;
		case CScene_Manager::TOOL_ID::TOOL_KERNINGCITY:
			m_pScene = CKerning_City::Create();
			dynamic_cast<CKerning_City*>(m_pScene)->Set_Hdc(L"Kerning_City");
			dynamic_cast<CKerning_City*>(m_pScene)->Set_StartPos(L"Kerning_City");
			dynamic_cast<CKerning_City*>(m_pScene)->Set_MapName(L"Kerning_City");
			dynamic_cast<CKerning_City*>(m_pScene)->Set_SaveName(L"../ResourceList/Kerning_City_lineList.dat");
			break;
		case CScene_Manager::TOOL_ID::TOOL_FIELD:
			 m_pScene = CField1::Create();
			 dynamic_cast<CField1*>(m_pScene)->Set_Hdc(L"Field1");
			 dynamic_cast<CField1*>(m_pScene)->Set_StartPos(L"Field1");
			 dynamic_cast<CField1*>(m_pScene)->Set_MapName(L"Field1");
			 dynamic_cast<CField1*>(m_pScene)->Set_SaveName(L"../ResourceList/Field1_lineList.dat");
			break;
		case CScene_Manager::TOOL_ID::TOOL_BOSS:
			m_pScene = CBossMapTool::Create();
			dynamic_cast<CBossMapTool*>(m_pScene)->Set_Hdc(L"BossMap");
			dynamic_cast<CBossMapTool*>(m_pScene)->Set_StartPos(L"BossMap");
			dynamic_cast<CBossMapTool*>(m_pScene)->Set_MapName(L"BossMap");
			dynamic_cast<CBossMapTool*>(m_pScene)->Set_SaveName(L"../ResourceList/BossMap_lineList.dat");
			break;
		case CScene_Manager::TOOL_ID::TOOL_END:
			break;
		default:
			break;
		}
		m_eCurScene = m_eNextScene; 
	}
}

void CScene_Manager::Update_Scene_Manager()
{
	m_pScene->Update_Scene(); 
}

void CScene_Manager::Render_Scene_Manager(HDC hDC)
{
	m_pScene->Render_Scene(hDC);
}

void CScene_Manager::Release_Scene_Manager()
{
	Safe_Delete(m_pScene);
}
