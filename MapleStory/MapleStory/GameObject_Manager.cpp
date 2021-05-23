#include "stdafx.h"
#include "GameObject_Manager.h"
#include "GameObject.h"
#include "Collision_Manager.h"
#include "Portal.h"
#include "Scene_Manager.h"

CGameObject_Manager* CGameObject_Manager::m_instance = nullptr;
CGameObject_Manager::CGameObject_Manager()
{
}

CGameObject_Manager::~CGameObject_Manager()
{
	Release_GameObject_Manager();
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
	int iEvent;
	int potal = 0;
	for (int i =0; i < Object_ID::END; ++i)
	{
		for (auto& iter = m_listGameObject[i].begin(); iter != m_listGameObject[i].end(); )
		{
			iEvent = (*iter)->Update_GameObject();
			if (OBJ_DEAD == iEvent)
			{
				Safe_Delete(*iter);
				iter = m_listGameObject[i].erase(iter);
			}
			else if(OBJ_FIELD_OUT == iEvent)
				iter = m_listGameObject[i].erase(iter);

			else if (iEvent == MOVE_PORTAL)
				potal = MOVE_PORTAL;
			else
				++iter;
		}
	}
	if (potal == MOVE_PORTAL)
	{
		for (auto & portal : m_listGameObject[Object_ID::PORTAL])
		{
			if (portal->Get_isPortal())
			{
				Scene_ID nextScene = dynamic_cast<CPortal*>(portal)->Get_NextSceneID();
				m_listGameObject[Object_ID::PLAYER].front()->Set_Pos(dynamic_cast<CPortal*>(portal)->Get_NextScenePos().x, dynamic_cast<CPortal*>(portal)->Get_NextScenePos().y);
				CScene_Manager::Get_Instance()->Change_Scene_Manager(nextScene);
				break;
			}
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

	CCollision_Manager::Collision_Portal(&m_listGameObject[Object_ID::PLAYER], &m_listGameObject[Object_ID::PORTAL]);
	if (!m_listGameObject[Object_ID::MONSTER].empty())
		CCollision_Manager::Collision_Monster(&m_listGameObject[Object_ID::PLAYER], &m_listGameObject[Object_ID::MONSTER]);
	if (!m_listGameObject[Object_ID::ATTACK_SKILL].empty())
		CCollision_Manager::Collision_Skill(&m_listGameObject[Object_ID::ATTACK_SKILL], &m_listGameObject[Object_ID::MONSTER]);
	if (!m_listGameObject[Object_ID::BOSS_SKILL].empty())
		CCollision_Manager::Collision_BossSkill(&m_listGameObject[Object_ID::BOSS_SKILL], &m_listGameObject[Object_ID::PLAYER]);
	if (!m_listGameObject[Object_ID::DROP_ITEM].empty())
		CCollision_Manager::Collision_DropItem(&m_listGameObject[Object_ID::PLAYER], &m_listGameObject[Object_ID::DROP_ITEM]);
	if (!m_listGameObject[Object_ID::BOSS].empty())
		CCollision_Manager::Collision_Boss(&m_listGameObject[Object_ID::ATTACK_SKILL], &m_listGameObject[Object_ID::BOSS]);

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

void CGameObject_Manager::Release_Specific_GameObject_Manager(Object_ID eID)
{
	for (auto& pObject : m_listGameObject[eID])
	{
		Safe_Delete(pObject);
	}
	m_listGameObject[eID].clear();
}
