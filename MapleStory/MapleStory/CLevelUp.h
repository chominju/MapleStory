#pragma once
#include "Skill.h"

class CLevelUp :
	public CSkill
{
private:
	explicit CLevelUp();
public:
	virtual ~CLevelUp();
	// CGameObject을(를) 통해 상속됨
	virtual int Ready_GameObject() override;
	virtual int Update_GameObject() override;
	virtual void Late_Update_GameObject() override;
	virtual void Render_GameObject(HDC hDC) override;
	virtual void Release_GameObject() override;
	virtual void UpdateRect_GameObject() override;

	static CGameObject* Create(CGameObject* player);

};

