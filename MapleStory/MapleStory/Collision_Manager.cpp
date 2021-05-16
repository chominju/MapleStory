#include "stdafx.h"
#include "Collision_Manager.h"
#include "GameObject.h"
#include "Player.h"
#include "Portal.h"
#include "Skill.h"
#include "GameObject_Manager.h"
#include "DamageSkin.h"

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
				dstObject->Set_IsDead();
				srcObject->Set_IsDead();
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
				if(player_object->GetInfo()->y >= portalRect->top &&player_object->GetInfo()->y <= portalRect->bottom)
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

void CCollision_Manager::Collision_Monster(list<CGameObject*>* player, list<CGameObject*>* monster)
{
	bool check = false;
	for (auto & player_object : *player)
	{
		for (auto& monster_object : *monster)
		{
			const RECT* playerRect = player_object->GetRect();
			const RECT* monsterRect = monster_object->GetRect();

			if (playerRect->left >= monsterRect->left-5 && playerRect->right <= monsterRect->right-5)
			{
				if (player_object->GetInfo()->y >= monsterRect->top &&player_object->GetInfo()->y <= monsterRect->bottom)
				{
					check = true;
					player_object->Set_IsHit(true);
					if (!player_object->Get_IsInvincibility())
					{
						player_object->Set_IsInvincibility(true);
						player_object->Set_Change_Hp(-monster_object->Get_MaxAttack());
					}
				}
			}
			//}
		}
	}

	/*if (!check)
	{
		for (auto & player_object : *player)
		{
			for (auto& portal_object : *monster)
			{
				player_object->Set_IsHit(false);
			}
		}
	}*/
}

void CCollision_Manager::Collision_Skill(list<CGameObject*>* skill, list<CGameObject*>* monster)
{
	bool check = false;

	for (auto & skill_object : *skill)
	{
		monster->sort([&](auto& monster1, auto& monster2) {
			return abs(skill_object->GetInfo()->x - monster1->GetInfo()->x) < abs(skill_object->GetInfo()->x - monster2->GetInfo()->x);
		});
			for (auto& monster_object : *monster)
			{
				const RECT* skillRect = skill_object->GetRect();
				const RECT* monsterRect = monster_object->GetRect();

				/*if (playerRect->left >= monsterRect->left - 5 && playerRect->right <= monsterRect->right - 5)
				{
					if (skill_object->GetInfo()->y >= monsterRect->top &&skill_object->GetInfo()->y <= monsterRect->bottom)
					{
						check = true;
						monster_object->SetHit(true);

					}
				}*/
				RECT temp = {};
				if (IntersectRect(&temp, skillRect, monsterRect))
				{
					if (!monster_object->Get_IsSkillHit() &&!monster_object->Get_IsDead())
					{
						if (dynamic_cast<CSkill*>(skill_object)->isHitMonsterNum())
						{
							monster_object->Set_IsSkillHit(true); // 스킬 맞음 ON
							monster_object->Set_IsHit(true);
							int damage = dynamic_cast<CSkill*>(skill_object)->Get_Damage();
							int skillHit = dynamic_cast<CSkill*>(skill_object)->Get_hitNum();


							monster_object->Set_Change_Hp(-(skillHit * damage));

							for (int i = 0; i < skillHit; i++)
							{
								CGameObject * damageSkin = CDamageSkin::Create(damage);
								damageSkin->Set_Pos(monster_object->GetInfo()->x, monster_object->GetRect()->top - (49)*(i+1));
								CGameObject_Manager::Get_Instance()->Add_GameObject_Manager(Object_ID::UI, damageSkin);
							}
							if (monster_object->Get_Hp() <= 0)
							{
								monster_object->Set_IsDead();
								CGameObject_Manager::Get_Instance()->GetPlayer()->Set_Change_Exp(monster_object->Get_Exp());
								CGameObject_Manager::Get_Instance()->GetPlayer()->Set_Change_Money(monster_object->Get_Money());
							}
						}
					}
				}
				else
				{
					monster_object->Set_IsSkillHit(false); // 스킬 끝나서 OFF
				}

				//}
			}
	}

	/*if (!check)
	{
		for (auto & player_object : *player)
		{
			for (auto& portal_object : *monster)
			{
				player_object->SetHit(false);
				portal_object->SetHit(false);
			}
		}
	}*/
}

bool CCollision_Manager::Collision_Rope(list<CGameObject*>* player, list<CGameObject*>* rope, const RECT** rc)
{
	for (auto & player_object : *player)
	{
		for (auto& rope_object : *rope)
		{
			float playerX = player_object->GetInfo()->x;
			float player_top = player_object->GetRect()->top;
			float player_bottom = player_object->GetRect()->bottom;
			const RECT* ropeRect = rope_object->GetRect();

			/*if (ropeRect->left <= playerX && playerX <= ropeRect->right)
			{
				if (player_top <= ropeRect->bottom - WINCY || player_bottom >= ropeRect->top)
				{
				*rc = ropeRect;
				return true;
				}
			}*/
			RECT temp = {};
			RECT temp2 = *ropeRect;
			temp2.bottom -= WINCY;
			temp2.top -= WINCY;
			if (IntersectRect(&temp, player_object->GetRect(), &temp2))
			{
				/*if (ropeRect->left <= playerX && playerX <= ropeRect->right)
				{*/
					*rc = ropeRect;
					return true;
				//}
			}
		}
	}
	return false;
}