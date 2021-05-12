#pragma once
#include "GameObject.h"
class CPortal :
	public CGameObject
{
private:
	explicit CPortal();
public:
	virtual ~CPortal();

	// CGameObject��(��) ���� ��ӵ�
	virtual int Ready_GameObject() override;
	virtual int Update_GameObject() override;
	virtual void Late_Update_GameObject() override;
	virtual void Render_GameObject(HDC hDC) override;
	virtual void Release_GameObject() override;
	virtual void UpdateRect_GameObject() override;

public:
	static CGameObject* Create();
};

