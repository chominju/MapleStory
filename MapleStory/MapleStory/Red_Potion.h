#pragma once
#include "Item.h"
class CRed_Potion :
	public CItem
{
private:
	explicit CRed_Potion();
public:
	virtual ~CRed_Potion();

	// CGameObject을(를) 통해 상속됨
	virtual int Ready_GameObject() override;
	virtual void Late_Update_GameObject() override;
	virtual void Release_GameObject() override;

	static CGameObject * Create(float posX, float posY);
};

