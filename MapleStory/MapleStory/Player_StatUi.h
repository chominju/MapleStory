#pragma once
#include "Ui.h"
class CPlayer_StatUi :
	public CUi
{
private:
	CPlayer_StatUi();
public:
	virtual ~CPlayer_StatUi();

	virtual int Ready_GameObject() override;
	virtual int Update_GameObject() override;
	virtual void Late_Update_GameObject() override;
	virtual void Render_GameObject(HDC hDC) override;
	virtual void Release_GameObject() override;

public:
	static CGameObject* Create();

private:
	static CGameObject*instance;
	CGameObject * m_player;
};

