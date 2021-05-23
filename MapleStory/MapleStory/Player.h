#pragma once
#include "GameObject.h"
class CItem;
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
	void Is_Jump();
	void Is_OffSet();
	void Is_LevelUp();
	void Player_MoveLeft();
	void Player_MoveRight();
	void Player_Idle();
	void Player_Jump();
	void Player_Prone();
	void Player_Swing();
	void Player_Rope();
	void Player_Hit();
	void Player_StatUiOpen();
	void Player_InventoryOpen();
	void Player_Skill(Animation animScene, Animation_index frameEnd);
	void Set_Animation(HDC hdc, Animation animScene, Animation_index frameEnd);
	void Set_CheckKeepY(float y)
	{
		m_checkKeepY = y;
		m_checkScrollY = false;
	}

	bool Get_IsStatOpen()
	{
		return m_isStatOpen;
	}

	bool Get_IsInventoryOpen()
	{
		return m_isInventoryOpen;
	}

	bool Get_IsShopClick()
	{
		return m_isShopClick;
	}

	void Set_IsShopClick(bool click)
	{
		m_isShopClick = click;
	}

	Key_Push GetKeyPush()
	{
		return m_keyPush;
	}

	bool Get_IsJump()
	{
		return m_isJump;
	}

	CItem* Get_Weapon()
	{
		return m_weapon;
	}

	void Set_Weapon(CItem * weapon)
	{
		m_weapon = weapon;
	}

private:
	static CGameObject * m_instance;

	bool m_isJump;
	bool m_isDoubleJump;
	bool m_isJumpLeft;
	bool m_isJumpRight;
	bool m_isDownJump;
	bool m_moveLock;
	bool m_isFall;
	bool m_isStatOpen;
	bool m_isInventoryOpen;
	bool m_isShopClick;

	float m_jumpHeight;
	float m_DoublejumpHeight;
	float m_power;
	float current_jumpHeight;
	float current_DoublejumpHeight;
	float m_beforeJumpY;

	float m_fallSpeed;
	Key_Push m_keyPush;

	CurrentKey jumpDir;

	bool m_checkScrollY;
	float m_checkKeepY;

	HDC m_expBar_hdc;
	HDC m_expBackBar_hdc;
	HDC m_State_Lv_hdc;
	HDC m_State_LvNum_hdc;
	HDC m_State_Num_hdc;
	int m_hitAnimationNum;

	CItem* m_weapon;
};

