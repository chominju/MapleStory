#include "stdafx.h"
#include "Scene_Manager.h"
#include "Kerning_City.h"
#include "Field1.h"
#include "BossMap.h"
#include "Menu.h"

CScene_Manager* CScene_Manager::m_instance = nullptr;

CScene_Manager::CScene_Manager()
	:m_scene(nullptr)
	, m_currentScene(Scene_ID::SCENE_END)
	, m_nextScene(Scene_ID::SCENE_END)
{
}


CScene_Manager::~CScene_Manager()
{
	Release_Scene_Manager();
}

Pos_int & CScene_Manager::Get_SceneSize()
{
	return m_scene->GetSceneSize();
}

void CScene_Manager::Change_Scene_Manager(Scene_ID nextScene)
{
	m_nextScene = nextScene;
	if (m_currentScene != m_nextScene)
	{
		Safe_Delete(m_scene);
		switch (m_nextScene)
		{
		case Scene_ID::SCENE_MENU:
			m_scene = CMenu::Create();
			break;
		case Scene_ID::SCENE_Kerning_City:
			m_scene = Kerning_City::Create();
			break;
		case Scene_ID::SCENE_MAP1:
			m_scene = CField1::Create();
			break;
		case Scene_ID::SCENE_BOSS:
			m_scene = CBossMap::Create();
		default:
			break;
		}
		m_currentScene = nextScene;
	}
}

void CScene_Manager::Update_Scene_Manager()
{
	m_scene->Update_Scene();
}

void CScene_Manager::Render_Scene_Manager(HDC hdc)
{
	m_scene->Render_Scene(hdc);
}

void CScene_Manager::Release_Scene_Manager()
{
	Safe_Delete(m_scene);
}
