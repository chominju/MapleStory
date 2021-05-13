#pragma once
#include "Skill.h"
class CDoubleStab :
	public CSkill
{
private:
	explicit CDoubleStab();
public:
	virtual ~CDoubleStab();

	virtual int Ready_GameObject() override;
	//virtual int Update_GameObject() override;
	virtual void Late_Update_GameObject() override;
	//virtual void Render_GameObject(HDC hDC) override;
	//virtual void Release_GameObject() override;
	//virtual void UpdateRect_GameObject() override;

public:
	static CGameObject* Create(CGameObject* player);
private:
	static CGameObject* m_instance;
};

