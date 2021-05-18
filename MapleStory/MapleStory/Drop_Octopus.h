#pragma once
#include "Item.h"
class CDrop_Octopus :
	public CItem
{
private:
	explicit CDrop_Octopus();
public:
	virtual ~CDrop_Octopus();

	// CGameObject��(��) ���� ��ӵ�
	virtual int Ready_GameObject() override;
	//virtual int Update_GameObject() override;
	virtual void Late_Update_GameObject() override;
	virtual void Render_GameObject(HDC hDC) override;
	virtual void Release_GameObject() override;

	static CGameObject * Create(float posX, float posY);
};

