#pragma once
#include "Monster.h"
class COctopus :
	public CMonster
{
private:
	explicit COctopus();
	virtual ~COctopus();
public:
	virtual int Ready_GameObject() override;
	virtual int Update_GameObject() override;
	virtual void Late_Update_GameObject() override;
	//	virtual void Render_GameObject(HDC hDC) override;
	virtual void Release_GameObject() override;
	//	virtual void UpdateRect_GameObject() override;

	void Set_Animation(HDC hdc, Octopus_Animation animScene, Octopus_Animation_Index frameEnd);


public:
	static CGameObject * Create();
};

