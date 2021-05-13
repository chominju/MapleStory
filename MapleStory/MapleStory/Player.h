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
	void Player_MoveLeft();
	void Player_MoveRight();
	void Player_Idle();
	void Player_Jump();
	void Player_Prone();
	void Player_Swing();
	void Player_Rope();
	void Player_Skill(Animation animScene, Animation_index frameEnd);
	void Set_Animation(HDC hdc, Animation animScene, Animation_index frameEnd);
	//void Play_Animation();
private:
	static CGameObject * m_instance;

	bool m_isJump;
	bool m_isDoubleJump;
	bool m_isJumpLeft;
	bool m_isJumpRight;
	bool m_isDownJump;
	bool m_moveLock;

	//bool m_jumpKeyUp;

	float m_jumpHeight;
	float m_DoublejumpHeight;
	float m_power;
	float current_jumpHeight;
	float current_DoublejumpHeight;

	float m_fallSpeed;
	Key_Push m_keyPush;

	CurrentKey jumpDir;

	//HDC m_temptemp; 스킬 체험
};

