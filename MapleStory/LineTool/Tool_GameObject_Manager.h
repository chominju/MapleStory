#pragma once
class CGameObject; 
class CGameObject_Manager
{
	// 싱글톤 패턴 - 객체 생성을 제한하는 디자인 패턴. 여기서부터 
public:
	static CGameObject_Manager* Get_Instance()
	{
		if (nullptr == m_pInstance)
			m_pInstance = new CGameObject_Manager; 

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
	CGameObject_Manager();
	~CGameObject_Manager();
	// 여기까지
public:
	CGameObject* Get_Target(Object_ID eID, CGameObject* pObject);
public:
	void DeleteID(Object_ID eID);
public:
	void Add_GameObject_Manager(Object_ID eID, CGameObject* pObject);
	void Update_GameObject_Manager();
	void Late_Update_GameObject_Manager();
	void Render_GameObject_Manager(HDC hDC);
	void Release_GameObject_Manager();
private:
	static CGameObject_Manager* m_pInstance; 
	list<CGameObject*>			m_listGameObject[Object_ID::END];
};

