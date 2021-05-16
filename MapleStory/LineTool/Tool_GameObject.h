#pragma once
class CGameObject abstract
{
public:
	explicit CGameObject();
	virtual ~CGameObject();
public:
	void Set_Pos(float fX, float fY); 
	void Set_Angle(float fDegree) { m_fAngle = fDegree; }
	void Set_IsDead() { m_bIsDead = true; }
	const RECT* Get_Rect() const;
	const Object_Info* Get_Info() const;
public:
	virtual int Ready_GameObject()=0; 
	virtual int Update_GameObject() = 0;
	virtual void Late_Update_GameObject() = 0;
	virtual void Render_GameObject(HDC hDC) = 0;
	virtual void Release_GameObject() = 0;
public:
	void UpdateRect_GameObject(); 
protected:
	Object_Info m_info;
	RECT m_rect; 
	float m_fSpeed; 
	float m_fAngle; 
	bool m_bIsDead; 
	
};

