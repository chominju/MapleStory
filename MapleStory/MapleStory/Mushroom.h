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
//	virtual void Render_GameObject(HDC hDC) override;
	virtual void Release_GameObject() override;
//	virtual void UpdateRect_GameObject() override;

	void Mushroom_Jump();

	void Set_Animation(HDC hdc, Mushroom_Animation animScene, Mushroom_Animation_Index frameEnd);

	int m_jumpHeight;
	int m_currentHeight;

	float m_power;
	float m_accel;

public:
	static CGameObject * Create();
};

