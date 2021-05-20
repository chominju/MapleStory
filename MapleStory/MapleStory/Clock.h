#pragma once
#include "Skill.h"
class CClock :
	public CSkill
{
private:
	explicit CClock();
public:
	virtual ~CClock();

	virtual int Ready_GameObject() override;
	virtual int Update_GameObject() override;
	virtual void Late_Update_GameObject() override;
	virtual void Render_GameObject(HDC hDC) override;
	//virtual void Release_GameObject() override;
	//virtual void UpdateRect_GameObject() override;
	virtual void Play_Animation() override;
public:
	static CGameObject* Create();
private:
	Direction dir;
};

