#pragma once
#include "GameObject.h"
class CDamageSkin :
	public CGameObject
{
private:
	explicit CDamageSkin();
public:
	virtual ~CDamageSkin();
	// CGameObject을(를) 통해 상속됨
	virtual int Ready_GameObject() override;
	virtual int Update_GameObject() override;
	virtual void Late_Update_GameObject() override;
	virtual void Render_GameObject(HDC hDC) override;
	virtual void Release_GameObject() override;
	virtual void UpdateRect_GameObject() override;

	void Set_PrintDamageNum(int damage)
	{
		m_printDamageNum = damage;
	}

	static CGameObject* Create(int damage);
private:
	float m_disappearTime;
	float m_disappearSpeed;

	int m_printDamageNum;
	int printNum;
};

