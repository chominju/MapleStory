#include "stdafx.h"
#include "Collision_Manager.h"
#include "GameObject.h"
#include "Player.h"
#include "Portal.h"
#include "Skill.h"
#include "GameObject_Manager.h"
#include "DamageSkin.h"
#include "Item.h"
#include "Inventory_RectManager.h"
#include "Key_Manager.h"
#include "Boss.h"

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

			if (playerRect->left >= portalRect->left + 20 && playerRect->right <= portalRect->right - 20)
			{
				if (player_object->Get_Info()->y >= portalRect->top &&player_object->Get_Info()->y <= portalRect->bottom)
					check = true;
				player_object->Set_isPortal(true);
				portal_object->Set_isPortal(true);
			}
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

			if (!monster_object->Get_IsDead())
			{
				if (playerRect->left >= monsterRect->left - 5 && playerRect->right <= monsterRect->right - 5)
				{
					if (player_object->Get_Info()->y >= monsterRect->top &&player_object->Get_Info()->y <= monsterRect->bottom)
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
			}
		}
	}
}

void CCollision_Manager::Collision_Skill(list<CGameObject*>* skill, list<CGameObject*>* monster)
{
	bool check = false;

	for (auto & skill_object : *skill)
	{
		monster->sort([&](auto& monster1, auto& monster2) {
			return abs(skill_object->Get_Info()->x - monster1->Get_Info()->x) < abs(skill_object->Get_Info()->x - monster2->Get_Info()->x);
		});
		for (auto& monster_object : *monster)
		{
			const RECT* skillRect = skill_object->GetRect();
			const RECT* monsterRect = monster_object->GetRect();

			RECT temp = {};
			if (IntersectRect(&temp, skillRect, monsterRect))
			{
				if (!monster_object->Get_IsSkillHit() && !monster_object->Get_IsDead())
				{
					if (dynamic_cast<CSkill*>(skill_object)->isHitMonsterNum())
					{
						monster_object->Set_IsSkillHit(true); // 스킬 맞음 ON
						monster_object->Set_IsHit(true);
						int damage = dynamic_cast<CSkill*>(skill_object)->Get_Damage();
						int skillHit = dynamic_cast<CSkill*>(skill_object)->Get_hitNum();



						int minAttack = (int)CGameObject_Manager::Get_Instance()->GetPlayer()->Get_TotalMinAttack();
						int maxAttack = (int)CGameObject_Manager::Get_Instance()->GetPlayer()->Get_TotalMaxAttack();
						int *randAttack = new int[skillHit + 1];
						int attackSum = 0;
						for (int i = 0; i < skillHit; i++)
						{
							randAttack[i] = rand() % 100 + minAttack;
							attackSum += randAttack[i];
						}
						monster_object->Set_Change_Hp((float)-(skillHit * damage * attackSum));

						for (int i = 0; i < skillHit; i++)
						{
							CGameObject * damageSkin = CDamageSkin::Create(damage * randAttack[i]);
							damageSkin->Set_Pos(monster_object->Get_Info()->x, (float)monster_object->GetRect()->top - (49)*(i + 1));
							CGameObject_Manager::Get_Instance()->Add_GameObject_Manager(Object_ID::UI, damageSkin);
						}
						if (monster_object->Get_Hp() <= 0)
						{
							monster_object->Set_IsDead();
							CSoundMgr::Get_Instance()->PlaySound(L"Mushroom_Die.mp3", CSoundMgr::MONSTER);
							CGameObject_Manager::Get_Instance()->GetPlayer()->Set_Change_Exp(monster_object->Get_Exp());
						}

						delete[] randAttack;
					}
				}
			}
			else
			{
				monster_object->Set_IsSkillHit(false); // 스킬 끝나서 OFF
			}
		}
	}
}

void CCollision_Manager::Collision_Boss(list<CGameObject*>* skill, list<CGameObject*>* boss)
{
	bool check = false;

	for (auto & skill_object : *skill)
	{
		for (auto& boss_object : *boss)
		{
			if (dynamic_cast<CBoss*>(boss_object)->Get_Isvisibility())
			{
				const RECT skillRect = *skill_object->GetRect();
				const RECT monsterRect = *boss_object->GetRect();

				RECT temp = {};
				if (IntersectRect(&temp, &skillRect, &monsterRect))
				{
					if (!boss_object->Get_IsSkillHit() && !boss_object->Get_IsDead())
					{
						if (dynamic_cast<CSkill*>(skill_object)->isHitMonsterNum())
						{
							boss_object->Set_IsSkillHit(true); // 스킬 맞음 ON
							boss_object->Set_IsHit(true);
							int damage = dynamic_cast<CSkill*>(skill_object)->Get_Damage();
							int skillHit = dynamic_cast<CSkill*>(skill_object)->Get_hitNum();

							int minAttack = (int)CGameObject_Manager::Get_Instance()->GetPlayer()->Get_TotalMinAttack();
							int maxAttack = (int)CGameObject_Manager::Get_Instance()->GetPlayer()->Get_TotalMaxAttack();
							int *randAttack = new int[skillHit + 1];
							int attackSum = 0;
							for (int i = 0; i < skillHit; i++)
							{
								randAttack[i] = rand() % 100 + minAttack;
								attackSum += randAttack[i];
							}

							boss_object->Set_Change_Hp((float)-(skillHit * damage * attackSum));

							for (int i = 0; i < skillHit; i++)
							{
								CGameObject * damageSkin = CDamageSkin::Create(damage * randAttack[i]);
								damageSkin->Set_Pos(boss_object->Get_Info()->x, (float)boss_object->GetRect()->top - (49)*(i + 1));
								CGameObject_Manager::Get_Instance()->Add_GameObject_Manager(Object_ID::UI, damageSkin);
							}
							if (boss_object->Get_Hp() <= 0)
							{
								boss_object->Set_IsDead();
								CGameObject_Manager::Get_Instance()->GetPlayer()->Set_Change_Exp(boss_object->Get_Exp());
							}

							delete[] randAttack;
						}
					}
				}
				else
				{
					boss_object->Set_IsSkillHit(false); // 스킬 끝나서 OFF
				}
			}
		}
	}
}

void CCollision_Manager::Collision_BossSkill(list<CGameObject*>* skill, list<CGameObject*>* player)
{
	bool check = false;

	for (auto & skill_object : *skill)
	{
		for (auto& player_object : *player)
		{
			RECT skillRect = *skill_object->GetRect();
			RECT playerRect = *player_object->GetRect();
			if (dynamic_cast<CPlayer*>(player_object)->GetKeyPush().isDown)
				playerRect.top += 35;

			RECT temp = {};
			if (IntersectRect(&temp, &skillRect, &playerRect))
			{
				if (!player_object->Get_IsSkillHit() && !player_object->Get_IsDead())
				{
					if (dynamic_cast<CSkill*>(skill_object)->isHitMonsterNum())
					{
						CSoundMgr::Get_Instance()->PlaySound(L"Boss_CharDam2.mp3", CSoundMgr::PLAYER);
						player_object->Set_IsSkillHit(true); // 스킬 맞음 ON
						player_object->Set_IsHit(true);
						int damage = dynamic_cast<CSkill*>(skill_object)->Get_Damage();
						int skillHit = dynamic_cast<CSkill*>(skill_object)->Get_hitNum();

						if (!player_object->Get_IsInvincibility())
						{
							player_object->Set_IsInvincibility(true);
							player_object->Set_Change_Hp(-(player_object->Get_Data()->maxHp*0.1 * damage));
						}

						if (player_object->Get_Hp() <= 0)
						{
							//player_object->Set_IsDead();
						}
						skill_object->Set_IsDead();

					}
				}
			}
			else
			{
				player_object->Set_IsSkillHit(false); // 스킬 끝나서 OFF
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
			const RECT* ropeRect = rope_object->GetRect();

			RECT temp = {};
			RECT temp2 = *ropeRect;
			temp2.bottom -= WINCY;
			temp2.top -= WINCY;
			if (IntersectRect(&temp, player_object->GetRect(), &temp2))
			{
				*rc = ropeRect;
				return true;
			}
		}
	}
	return false;
}

void CCollision_Manager::Collision_DropItem(list<CGameObject*>* player, list<CGameObject*>* dropItem)
{
	if (CKey_Manager::Get_Instance()->Key_Pressing(KEY_Z) || CKey_Manager::Get_Instance()->Key_Pressing(KEY_NUMPAD0))
	{
		for (auto & player_object : *player)
		{
			for (auto& dropItem_object : *dropItem)
			{
				const RECT* playerRect = player_object->GetRect();
				const RECT* dropItem_objectRect = dropItem_object->GetRect();
				RECT temp = {};
				if (IntersectRect(&temp, playerRect, dropItem_objectRect))
				{
					CSoundMgr::Get_Instance()->PlaySound(L"PickUpItem.mp3",CSoundMgr::PLAYER);
					CItem* tempItem = dynamic_cast<CItem*>(dropItem_object);
					if (tempItem->Get_ItemInfo()->type == Item_type::MESO)
					{
						player_object->Set_Change_Money(dynamic_cast<CItem*>(dropItem_object)->Get_ItemInfo()->money);
						dropItem_object->Set_IsDead();
					}
					if (tempItem->Get_ItemInfo()->type == Item_type::ETC)
					{
						tempItem->Set_m_isFieldOut(true);
						tempItem->Set_ItemPlace(Item_Place::INVENTORY_ITEM);
						CInventory_RectManager::Get_Instance()->Push_EtcList(tempItem);
					}
					else if (tempItem->Get_ItemInfo()->type == Item_type::CONSUME)
					{
						tempItem->Set_m_isFieldOut(true);
						tempItem->Set_ItemPlace(Item_Place::INVENTORY_ITEM);
						CInventory_RectManager::Get_Instance()->Push_ConsumeList(tempItem);
					}
					else if (tempItem->Get_ItemInfo()->type == Item_type::EQUIPMENT)
					{
						tempItem->Set_m_isFieldOut(true);
						tempItem->Set_ItemPlace(Item_Place::INVENTORY_ITEM);
						CInventory_RectManager::Get_Instance()->Push_EquipmentList(tempItem);
					}
				}
			}
		}
	}
}
