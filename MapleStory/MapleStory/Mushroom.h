#pragma once
#include "Monster.h"
class CMushroom :
	public CMonster
{
private:
	explicit CMushroom();
	virtual ~CMushroom();
public:
	virtual int Ready_GameObject() override;
	virtual int Update_GameObject() override;
	virtual void Late_Update_GameObject() override;
//	virtual void Render_GameObject(HDC hDC) override;
	virtual void Release_GameObject() override;
//	virtual void UpdateRect_GameObject() override;

	void Set_Animation(HDC hdc, Mushroom_Animation animScene, Mushroom_Animation_Index frameEnd);

	int m_jumpHeight;
	int m_currentHeight;

public:
	static CGameObject * Create();
};

