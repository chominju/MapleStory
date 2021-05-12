#pragma once
class CScene; 
class CScene_Manager
{
public:
	enum TOOL_ID {TOOL_MENU, TOOL_KERNINGCITY,TOOL_FIELD ,TOOL_BOSS, TOOL_END};
public:
	static CScene_Manager* Get_Instance()
	{
		if (nullptr == m_pInstance)
			m_pInstance = new CScene_Manager; 

		return m_pInstance; 
	}
	static void Destroy_Instance()
	{
		if (m_pInstance)
		{
			delete m_pInstance; 
			m_pInstance = nullptr; 
		}
	}
private:
	CScene_Manager();
	~CScene_Manager();
public:
	void Change_Scene_Manager(TOOL_ID eNextScene);
public:
	void Update_Scene_Manager(); 
	void Render_Scene_Manager(HDC hDC);
	void Release_Scene_Manager(); 

private:
	static	CScene_Manager* m_pInstance; 
	CScene* m_pScene; 
	TOOL_ID		m_eCurScene;
	TOOL_ID		m_eNextScene;
};

