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
	//void Set_Animation(HDC hdc, BossAttack_Animation animScene, Boss_Animation_Index frameEnd);
	void Set_TelePortAnimation(HDC hdc, Boss_Animation animScene, Boss_Animation_Index frameEnd);
	void Play_Animation();
	void Play_TeleportAnimation();
	void Play_AttackAnimation();
	void Boss_Attack();
	bool Get_Isvisibility()
	{
		return m_isvisibility;
	}
public:
	static CGameObject * Create();

private:
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
	float m_TeleportTime;
	float m_TeleportSpeed;
	float m_TeleportAfterTime;
	float m_TeleportAfterSpeed;

	bool m_isCollisionOn;
	bool m_isAttackOn;
	bool m_isvisibility;
	bool m_isTeleport;

	bool m_isTeleportBefore;
	bool m_isTeleportAfter;

	float m_TeleportSizeX;
	float m_TeleportSizeY;

	float m_Attack1SizeX;
	float m_Attack1SizeY;

	float m_Attack2SizeX;
	float m_Attack2SizeY;

	float m_Attack3SizeX;
	float m_Attack3SizeY;

	float m_DieSizeX;
	float m_DieSizeY;

	bool m_isAttack1;
	bool m_isAttack2;
	bool m_isAttack3;

	HDC m_teleport_hdc;
	HDC m_attack1_hdc;
	HDC m_attack2_hdc;
	HDC m_attack3_hdc;
	Animation_Frame m_animTeleportFrame;
};

