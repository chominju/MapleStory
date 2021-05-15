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
	const RECT* GetRect()
	{
		return &m_rect;
	}

	Object_Info* GetInfo()
	{
		return &m_info;
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

	void Set_Dead()
	{
		m_isDead = true;
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

	void Change_Hp(int hp)
	{
		m_data.hp += hp;
		if (m_data.hp >= m_data.maxHp)
			m_data.hp = m_data.maxHp;
		if (m_data.hp <= 0)
			m_data.hp = 0;
	}

	float Get_Hp()
	{
		return m_data.hp;
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
	bool m_isSkillHit;
	bool m_isPortal;
	HDC m_left_hdc;
	HDC m_right_hdc;

	HDC m_hpBar_hdc;
	HDC m_hpBackBar_hdc;
	Animation_Frame m_animFrame;
	CGameObject* m_target;

};

