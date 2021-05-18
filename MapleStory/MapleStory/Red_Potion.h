#pragma once
#include "Item.h"
class CRed_Potion :
	public CItem
{
private:
	explicit CRed_Potion();
public:
	virtual ~CRed_Potion();

	// CGameObject��(��) ���� ��ӵ�
	virtual int Ready_GameObject() override;
	//virtual int Update_GameObject() override;
	virtual void Late_Update_GameObject() override;
	virtual void Render_GameObject(HDC hDC) override;
	virtual void Release_GameObject() override;

	static CGameObject * Create(float posX, float posY);
};

