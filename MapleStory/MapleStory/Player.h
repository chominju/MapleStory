#pragma once
#include "GameObject.h"
class CPlayer :
	public CGameObject
{
private:
	explicit CPlayer();
	virtual ~CPlayer();

public:
	// CGameObject을(를) 통해 상속됨
	virtual int Ready_GameObject() override;
	virtual int Update_GameObject() override;
	virtual void Late_Update_GameObject() override;
	virtual void Render_GameObject(HDC hDC) override;
	virtual void Release_GameObject() override;
	virtual void UpdateRect_GameObject() override;

public:
	static CGameObject* Create();
	void IsJump();
private:
	static CGameObject * m_instance;
	Player_Info m_player_info;
	float m_power;
	float m_accel;
	float m_gravity;

	CurrentKey m_currentKey;
	bool m_isJump;

	HDC m_hdc;
};

