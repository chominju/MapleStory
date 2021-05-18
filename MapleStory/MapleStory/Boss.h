#pragma once
#include "Monster.h"
class CBoss :
	public CMonster
{
private:
	explicit CBoss();
	virtual ~CBoss();
public:
	virtual int Ready_GameObject() override;
	virtual int Update_GameObject() override;
	virtual void Late_Update_GameObject() override;
	virtual void Render_GameObject(HDC hDC) override;
	virtual void Release_GameObject() override;
	virtual void UpdateRect_GameObject() override;

	void Set_Animation(HDC hdc, Boss_Animation animScene, Boss_Animation_Index frameEnd);

	int m_jumpHeight;
	int m_currentHeight;

	float m_power;
	float m_accel;

	float m_Attack1Time;
	float m_Attack1Speed;
	float m_Attack2Time;
	float m_Attack2Speed;
	float m_Attack3Time;
	float m_Attack3Speed;
	float m_Attack4Time;
	float m_Attack4Speed;

public:
	static CGameObject * Create();
};

