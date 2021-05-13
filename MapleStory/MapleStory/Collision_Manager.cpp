#include "stdafx.h"
#include "Collision_Manager.h"
#include "GameObject.h"
#include "Player.h"
#include "Portal.h"

CCollision_Manager::CCollision_Manager()
{
}

CCollision_Manager::~CCollision_Manager()
{
}

void CCollision_Manager::Collision_Rect(list<CGameObject*>* listDest, list<CGameObject*>* listSrc)
{
	RECT rc = {};
	for (auto& dstObject : *listDest)
	{
		for (auto& srcObject : *listSrc)
		{
			if (IntersectRect(&rc, dstObject->GetRect(), srcObject->GetRect()))
			{
				dstObject->SetDead();
				srcObject->SetDead();
			}
		}
	}
}

void CCollision_Manager::Collision_Portal(list<CGameObject*>* player, list<CGameObject*>* portal)
{
	bool check = false;
	for (auto & player_object : *player)
	{
		for (auto& portal_object : *portal)
		{
			const RECT* playerRect = player_object->GetRect();
			const RECT* portalRect = portal_object->GetRect();

			if (playerRect->left >= portalRect->left+20 && playerRect->right <= portalRect->right-20)
			{
				check = true;
				player_object->Set_isPortal(true);
				portal_object->Set_isPortal(true);
			}
			//}
		}
	}

	if (!check)
	{
		for (auto & player_object : *player)
		{
			for (auto& portal_object : *portal)
			{
				player_object->Set_isPortal(false);
				portal_object->Set_isPortal(false);
			}
		}
	}
}

bool CCollision_Manager::Collision_Rope(list<CGameObject*>* player, list<CGameObject*>* rope, const RECT** rc)
{
	for (auto & player_object : *player)
	{
		for (auto& rope_object : *rope)
		{
			float playerX = player_object->GetInfo()->x;
			const RECT* ropeRect = rope_object->GetRect();

			if (ropeRect->left <= playerX && playerX <= ropeRect->right)
			{
				*rc = ropeRect;
				return true;
			}
		}
	}
	return false;
}