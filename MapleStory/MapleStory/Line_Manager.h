#pragma once
class CLine;
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
	bool Collision_Line_Manager(float finX, float* pOutY);
public:
	void Insert_Line_Manager(Pos left, Pos right);
	void Ready_Line_Manager();
	void Render_Line_Manager(HDC hDC);
	void Release_Line_Manager();

private:
	static CLine_Manager* m_pInstance;
	list<CLine*> m_listLine;
};

