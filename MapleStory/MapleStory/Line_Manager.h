#pragma once
class CLine;
class CGameObject;
class CPlayer;
class CLine_Manager
{
public:
	static CLine_Manager* Get_Instance()
	{
		if (nullptr == m_pInstance)
			m_pInstance = new CLine_Manager;
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
	CLine_Manager();
	~CLine_Manager();
public:
	bool Collision_Line_Manager(CGameObject*object, float * pOutY);
	bool Floor_Collision_Line_Manager_Line_Manager(CPlayer*player);
public:
	void Insert_Line_Manager(Pos_float left, Pos_float right);
	void Render_Line_Manager(HDC hDC);
	void Release_Line_Manager();

private:
	static CLine_Manager* m_pInstance;
	list<CLine*> m_listLine;

	bool m_isLinePrint;
};

