#pragma once
#include "Skill.h"
class CBoomerangStab :
	public CSkill
{
private:
	explicit CBoomerangStab();
public:
	virtual ~CBoomerangStab();

	virtual int Ready_GameObject() override;
	virtual int Update_GameObject() override;
	virtual void Late_Update_GameObject() override;

public:
	static CGameObject* Create(CGameObject* player);
private:
	static CGameObject* m_instance;
};

