#pragma once
#include "GameObject.h"
class CRope :
	public CGameObject
{
private:
	explicit CRope();
	virtual ~CRope();

public:
	// CGameObject을(를) 통해 상속됨
	virtual int Ready_GameObject() override;
	virtual int Update_GameObject() override;
	virtual void Late_Update_GameObject() override;
	virtual void Render_GameObject(HDC hDC) override;
	virtual void Release_GameObject() override;
	virtual void UpdateRect_GameObject() override;

	static CGameObject* Create();
};

