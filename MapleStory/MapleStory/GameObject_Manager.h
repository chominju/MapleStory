#pragma once
class CGameObject;
class CGameObject_Manager
{
private:
	CGameObject_Manager();
	~CGameObject_Manager();
public:
	static CGameObject_Manager* Get_Instance()
	{
		if (nullptr == m_instance)
			m_instance = new CGameObject_Manager;

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
	CGameObject* Get_Target(Object_ID eID, CGameObject* pObject);
public:
	void DeleteID(Object_ID id);
public:
	void Add_GameObject_Manager(Object_ID eID, CGameObject* pObject);
	void Update_GameObject_Manager();
	void Late_Update_GameObject_Manager();
	void Render_GameObject_Manager(HDC hDC);
	void Release_GameObject_Manager();
	void Release_Specific_GameObject_Manager(Object_ID eID);

	CGameObject*& GetPlayer()
	{
		return m_listGameObject[Object_ID::PLAYER].front();
	}

private:
	static CGameObject_Manager* m_instance;
	list<CGameObject*> m_listGameObject[Object_ID::END];
};

