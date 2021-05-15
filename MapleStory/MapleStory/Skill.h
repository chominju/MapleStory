#pragma once
#include "GameObject.h"

class CSkill :
	public CGameObject
{
public:
	explicit CSkill();
	virtual ~CSkill();

public:
	// CGameObject을(를) 통해 상속됨
	virtual int Ready_GameObject() override;
	virtual int Update_GameObject() override;
	virtual void Late_Update_GameObject() override;
	virtual void Render_GameObject(HDC hDC) override;
	virtual void Release_GameObject() override;
	virtual void UpdateRect_GameObject() override;

	virtual void Play_Animation() override;

	int Get_Damage()
	{
		return m_damage;
	}

	int Get_hitNum()
	{
		return m_hitNum;
	}

	bool isHitMonsterNum()
	{
		if (m_hitMonsterNum > 0)
		{
			m_hitMonsterNum--;
			return true;
		}
		else
			return false;
	}

protected:
	int m_damage;				// 데미지
	int m_hitMonsterNum;		// 최대 공격 가능한 몬스터 수
	int m_hitNum;				// 타수
};