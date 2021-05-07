#pragma once
class CLine;
class CLine_Manager
{
public:
	static CLine_Manager* Get_Instance()
	{
		if (nullptr == m_instance)
			m_instance = new CLine_Manager;
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
private:
	CLine_Manager();
	~CLine_Manager();
public:
	bool Collision_Line_Manager(float otherX, float* outY);
public:
	void Ready_Line_Manager();
	void Update_Line_Manager();
	void Render_Line_Manager(HDC hdc);
	void Release_Line_Manager();

private:
	static CLine_Manager* m_instance;
	list<CLine*> m_listLine;
};

