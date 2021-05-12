#include "stdafx.h"
#include "Tool_GameObject_Manager.h"
#include "Tool_GameObject.h"
//#include "Collision_Manager.h"
CGameObject_Manager* CGameObject_Manager::m_pInstance = nullptr;
CGameObject_Manager::CGameObject_Manager()
{
}


CGameObject_Manager::~CGameObject_Manager()
{
	Release_GameObject_Manager();
}

CGameObject * CGameObject_Manager::Get_Target(Object_ID eID, CGameObject * pObject)
{
	if(m_listGameObject[eID].empty() || nullptr == pObject || eID >= Object_ID::END)
		return nullptr;

	CGameObject* pTarget = m_listGameObject[eID].front(); 
	float fx1 = pTarget->Get_Info()->x - pObject->Get_Info()->x; 
	float fy1 = pTarget->Get_Info()->y - pObject->Get_Info()->y; 
	float fDist1 = sqrtf(fx1 * fx1 + fy1 * fy1); 

	for (auto& pForTarget : m_listGameObject[eID])
	{
		float fx2 = pForTarget->Get_Info()->x - pObject->Get_Info()->x;
		float fy2 = pForTarget->Get_Info()->y - pObject->Get_Info()->y;
		float fDist2 = sqrtf(fx2 * fx2 + fy2 * fy2);

		if (fDist1 > fDist2)
		{
			fDist1 = fDist2; 
			pTarget = pForTarget; 
		}
	}
	return pTarget; 
}

void CGameObject_Manager::DeleteID(Object_ID eID)
{
	for (auto& pObject : m_listGameObject[eID])
		Safe_Delete(pObject); 
	m_listGameObject[eID].clear();
}

void CGameObject_Manager::Add_GameObject_Manager(Object_ID eID, CGameObject * pObject)
{
	
	if (nullptr == pObject || eID >= Object_ID::END )
		return; 

	m_listGameObject[eID].emplace_back(pObject);
}

void CGameObject_Manager::Update_GameObject_Manager()
{
	for (int i = 0; i < Object_ID::END; ++i)
	{
		for (auto& iter = m_listGameObject[i].begin(); iter != m_listGameObject[i].end(); )
		{
			int iEvent = (*iter)->Update_GameObject();
			if (OBJ_DEAD == iEvent)
			{
				Safe_Delete(*iter);
				iter = m_listGameObject[i].erase(iter);
			}
			else
				++iter;
		}
	}
}

void CGameObject_Manager::Late_Update_GameObject_Manager()
{
	for (int i = 0; i < Object_ID::END; ++i)
	{
		for (auto& pObject : m_listGameObject[i])
		{
			pObject->Late_Update_GameObject();
			if (m_listGameObject[i].empty())
				break; 
		}
	}
	
	//CCollision_Manager::Collision_RectEx(&m_listGameObject[OBJECT::MOUSE], &m_listGameObject[OBJECT::MONSTER]);

}

void CGameObject_Manager::Render_GameObject_Manager(HDC hDC)
{
	for (int i = 0; i < Object_ID::END; ++i)
	{
		for (auto& pObject : m_listGameObject[i])
			pObject->Render_GameObject(hDC);
	}
}

void CGameObject_Manager::Release_GameObject_Manager()
{
	for (int i = 0; i < Object_ID::END; ++i)
	{
		for (auto& pObject : m_listGameObject[i])
		{
			Safe_Delete(pObject);
		}
		m_listGameObject[i].clear();
	}
}
