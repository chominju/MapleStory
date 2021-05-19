#pragma once
#include "GameObject.h"

class CMonster :
	public CGameObject
{
public:
	explicit CMonster();
	virtual ~CMonster();

public:
	// CGameObject을(를) 통해 상속됨
	virtual int Ready_GameObject() override;
	virtual int Update_GameObject() override;
	virtual void Late_Update_GameObject() override;
	virtual void Render_GameObject(HDC hDC) override;
	virtual void Release_GameObject() override;
	virtual void UpdateRect_GameObject() override;

	void Set_DistanceX(int min, int max)
	{
		m_minX = min;
		m_maxX = max;
	}

	Direction Get_Direction()
	{
		return m_dir;
	}


protected:
	Direction m_dir;
	Monster_State m_state;
	float m_attackTime;
	float m_changeStateTime;
	float m_changeStateSpeed;
	float m_changeDirectionTime;
	float m_changeDirectionSpeed;

	bool m_isWalk;
	bool m_isJump;
	bool m_isDie;
	bool m_isFall;
	bool m_trace;
	
	float m_jumpSpeed;

	float m_minX;
	float m_maxX;

	CGameObject* m_player;

};

