#pragma once
#include "Item.h"
class CDrop_Mushroom :
	public CItem
{
private:
	explicit CDrop_Mushroom();
public:
	virtual ~CDrop_Mushroom();

	// CGameObject을(를) 통해 상속됨
	virtual int Ready_GameObject() override;
	//virtual int Update_GameObject() override;
	virtual void Late_Update_GameObject() override;
	virtual void Render_GameObject(HDC hDC) override;
	virtual void Release_GameObject() override;

	static CGameObject * Create(CGameObject * monster);
};