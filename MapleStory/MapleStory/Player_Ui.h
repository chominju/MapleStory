#pragma once
#include "Ui.h"
class CPlayer_Ui :
	public CUi
{
private:
	CPlayer_Ui();
public:
	~CPlayer_Ui();

	virtual int Ready_GameObject() override;
	virtual int Update_GameObject() override;
	virtual void Late_Update_GameObject() override;
	virtual void Render_GameObject(HDC hDC) override;
	virtual void Release_GameObject() override;

public:
	static CGameObject * Create();
private:
	static CGameObject * instance;
	HDC m_skillKey;
	HDC m_playerDie_Message_hdc;
	CGameObject* m_Player_Die_Button;
};

