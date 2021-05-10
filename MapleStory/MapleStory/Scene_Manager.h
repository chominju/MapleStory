#pragma once
class CScene; 
class CScene_Manager
{
public:
private:
	CScene_Manager();
	~CScene_Manager();

public:
	static CScene_Manager* Get_Instance()
	{
		if (nullptr == m_instance)
			m_instance = new CScene_Manager;
		return m_instance;
	}

	static void Destroy_Instance()
	{
		if (m_instance)
		{
			delete m_instance;
			m_instance = nullptr;
		}
	}

public:
	void Change_Scene_Manager(Scene_ID nextScene);
	void Update_Scene_Manager();
	void Render_Scene_Manager(HDC hdc);
	void Release_Scene_Manager();

private:
	static CScene_Manager* m_instance;
	CScene* m_scene;
	Scene_ID m_currentScene;
	Scene_ID m_nextScene;
};

