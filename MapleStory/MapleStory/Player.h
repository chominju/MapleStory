#pragma once
#include "GameObject.h"
class CPlayer :
	public CGameObject
{
private:
	explicit CPlayer();
	virtual ~CPlayer();

public:
	// CGameObject��(��) ���� ��ӵ�
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

	CurrentKey m_currentKey;
	bool m_isJump;
	float jumpHeight;
	float m_power;
	float current_jumpHeight;
	float jump_before;
	HDC m_hdc;
	float fall;
};

