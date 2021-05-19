#pragma once
#include "Skill.h"
class CBoss_Attack2_Ball :
	public CSkill
{
private:
	explicit CBoss_Attack2_Ball();
public:
	virtual ~CBoss_Attack2_Ball();

	virtual int Ready_GameObject() override;
	virtual int Update_GameObject() override;
	virtual void Late_Update_GameObject() override;
	virtual void Render_GameObject(HDC hDC) override;
	//virtual void Release_GameObject() override;
	//virtual void UpdateRect_GameObject() override;
	virtual void Play_Animation() override;
public:
	static CGameObject* Create(CGameObject* boss);
private:
	static CGameObject* m_instance;

	Direction dir;
};