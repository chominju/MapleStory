#pragma once
#include "Item.h"
class CMeso :
	public CItem
{
private:
	explicit CMeso();
public:
	virtual ~CMeso();

	// CGameObject��(��) ���� ��ӵ�
	virtual int Ready_GameObject() override;
	//virtual int Update_GameObject() override;
	virtual void Late_Update_GameObject() override;
	virtual void Render_GameObject(HDC hDC) override;
	virtual void Release_GameObject() override;

	static CGameObject * Create(CGameObject * player);

};

