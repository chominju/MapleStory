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

	void SetPos(float x, float y)
	{
		m_info.x = x;
		m_info.y = y;
	}

	void SetDead()
	{
		m_isDead = true;
	}

	void Change_Hp(int hp)
	{
		m_data.hp += hp;
	}

	void Set_isPortal(bool isCollsion)
	{
		m_isPortal = isCollsion;
	}

	bool Get_isPortal()
	{
		return m_isPortal;
	}

	void Play_Animation();

protected:
	HDC m_hdc;
	RECT m_rect;
	Object_Info m_info;
	Object_Data m_data;
	float m_speed;
	bool m_isDead;
	bool m_isPortal;
	Animation_Frame m_animFrame;
};

