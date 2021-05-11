#include "stdafx.h"
#include "GameObject_Manager.h"
#include "GameObject.h"


CGameObject_Manager* CGameObject_Manager::m_instance = nullptr;
CGameObject_Manager::CGameObject_Manager()
{
}

CGameObject_Manager::~CGameObject_Manager()
{
	Release_GameObject_Manager();
}

CGameObject * CGameObject_Manager::Get_Target(Object_ID eID, CGameObject * pObject)
{
	// º¸·ù 
	/*if (m_listGameObject[eID].empty() || nullptr == pObject || eID >= Object_ID::END)
		return nullptr;

	CGameObject* pTarget = m_listGameObject[eID].front();
	float fx1 = pTarget->Get_Info()->fX - pObject->Get_Info()->fX;
	float fy1 = pTarget->Get_Info()->fY - pObject->Get_Info()->fY;
	float fDist1 = sqrtf(fx1 * fx1 + fy1 * fy1);

	for (auto& pForTarget : m_listGameObject[eID])
	{
		float fx2 = pForTarget->Get_Info()->fX - pObject->Get_Info()->fX;
		float fy2 = pForTarget->Get_Info()->fY - pObject->Get_Info()->fY;
		float fDist2 = sqrtf(fx2 * fx2 + fy2 * fy2);

		if (fDist1 > fDist2)
		{
			fDist1 = fDist2;
			pTarget = pForTarget;
		}
	}
	return pTarget;*/
	return nullptr;
}

void CGameObject_Manager::DeleteID(Object_ID id)
{
	for (auto& object : m_listGameObject[id])
		Safe_Delete(object);
	m_listGameObject[id].clear();
}

void CGameObject_Manager::Add_GameObject_Manager(Object_ID id, CGameObject * object)
{
	if (nullptr == object || id >= Object_ID::END)
		return;

	m_listGameObject[id].emplace_back(object);
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

//	CCollision_Manager::Collision_RectEx(&m_listGameObject[OBJECT::MOUSE], &m_listGameObject[OBJECT::MONSTER]);

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
