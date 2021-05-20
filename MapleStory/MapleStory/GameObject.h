#pragma once
class CGameObject
{
public:
	explicit CGameObject();
	virtual ~CGameObject();

public:
	virtual int Ready_GameObject() = 0;
	virtual int Update_GameObject() = 0;
	virtual void Late_Update_GameObject() = 0;
	virtual void Render_GameObject(HDC hDC) = 0;
	virtual void Release_GameObject() = 0;
	virtual void UpdateRect_GameObject() = 0;
public:
	RECT* GetRect()
	{
		return &m_rect;
	}

	Object_Info* Get_Info()
	{
		return &m_info;
	}

	Object_Data* Get_Data()
	{
		return &m_data;
	}

	void Set_Pos(float x, float y)
	{
		m_info.x = x;
		m_info.y = y;
	}

	void Set_Size(float x, float y)
	{
		m_info.sizeX = x;
		m_info.sizeY = y;
	}

	void Set_IsDead()
	{
		m_isDead = true;
	}

	bool Get_IsDead()
	{
		return m_isDead;
	}

	void Set_IsHit(bool hit)
	{
		m_isHit = hit;
	}

	void Set_IsSkillHit(bool skillHit)
	{
		m_isSkillHit = skillHit;
	}

	bool Get_IsSkillHit()
	{
		return m_isSkillHit;
	}

	void Set_IsInvincibility(bool invincibility)
	{
		m_isInvincibility = invincibility;
	}

	bool Get_IsInvincibility()
	{
		return m_isInvincibility;
	}


	void Set_Change_Hp(float hp)
	{
		m_data.hp += hp;
		if (m_data.hp >= m_data.maxHp)
			m_data.hp = m_data.maxHp;
		if (m_data.hp <= 0)
			m_data.hp = 0;
	}

	float  Get_Hp()
	{
		return m_data.hp;
	}

	float  Get_MaxHp()
	{
		return m_data.maxHp;
	}

	int Get_MinAttack()
	{
		return m_data.minAttack;
	}

	int Get_MaxAttack()
	{
		return m_data.maxAttack;
	}

	void  Set_Change_Exp(float exp)
	{
		m_data.exp += exp;
	}

	float Get_Exp()
	{
		return m_data.exp;
	}

	float Get_MaxExp()
	{
		return m_data.maxExp;
	}

	void Set_Change_Money(int money)
	{
		m_data.money += money;
	}


	int Get_Money()
	{
		return m_data.money;
	}

	void Set_isPortal(bool isCollsion)
	{
		m_isPortal = isCollsion;
	}

	bool Get_isPortal()
	{
		return m_isPortal;
	}

	virtual void Play_Animation();

	void Set_Target(CGameObject* target)
	{
		m_target = target;
	}

	CurrentKey Get_CurrentKey()
	{
		return m_currentKey;
	}


protected:
	HDC m_hdc;
	RECT m_rect;
	Object_Info m_info;
	Object_Data m_data;
	CurrentKey m_currentKey;
	float m_speed;
	bool m_isDead;
	bool m_isHit;
	bool m_isInvincibility;
	bool m_isSkillHit;
	bool m_isPortal;
	HDC m_left_hdc;
	HDC m_right_hdc;

	HDC m_hpBar_hdc;
	HDC m_hpBackBar_hdc;
	HDC m_objectDie_hdc;
	Animation_Frame m_animFrame;
	CGameObject* m_target;

};

