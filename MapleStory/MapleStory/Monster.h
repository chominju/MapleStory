#pragma once
#include "GameObject.h"
class CMonster :
	public CGameObject
{
private:
	explicit CMonster();
	virtual ~CMonster();

private:

	// CGameObject��(��) ���� ��ӵ�
	virtual int Ready_GameObject() override;
	virtual int Update_GameObject() override;
	virtual void Late_Update_GameObject() override;
	virtual void Render_GameObject(HDC hDC) override;
	virtual void Release_GameObject() override;
};

