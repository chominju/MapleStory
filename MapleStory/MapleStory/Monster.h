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

protected:
	Direction m_dir;
	Monster_State m_state;
	float m_attackTime;
	float m_changeStateTime;
	float m_changeStateSpeed;
	float m_changeDirectionTime;
	float m_changeDirectionSpeed;

	bool m_isHit;
	bool m_isWalk;
	bool m_isJump;

	float m_jumpSpeed;
};

