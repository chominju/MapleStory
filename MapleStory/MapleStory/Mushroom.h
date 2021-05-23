#pragma once
#include "Monster.h"
class CMushroom :
	public CMonster
{
private:
	explicit CMushroom();
	virtual ~CMushroom();
public:
	virtual int Ready_GameObject() override;
	virtual int Update_GameObject() override;
	virtual void Late_Update_GameObject() override;
	virtual void Release_GameObject() override;

	void Mushroom_Jump();

	void Set_Animation(HDC hdc, Mushroom_Animation animScene, Mushroom_Animation_Index frameEnd);

	int m_jumpHeight;
	float m_currentHeight;

	float m_power;
	float m_accel;
	float jumpDelay;

public:
	static CGameObject * Create();
};

