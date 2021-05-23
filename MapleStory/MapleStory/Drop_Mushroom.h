#pragma once
#include "Item.h"
class CDrop_Mushroom :
	public CItem
{
private:
	explicit CDrop_Mushroom();
public:
	virtual ~CDrop_Mushroom();

	// CGameObject��(��) ���� ��ӵ�
	virtual int Ready_GameObject() override;
	virtual void Late_Update_GameObject() override;
	virtual void Release_GameObject() override;

	static CGameObject * Create(float posX, float posY);
};