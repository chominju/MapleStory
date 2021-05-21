#pragma once
#include "Item.h"
class CWhite_Potion :
	public CItem
{
private:
	explicit CWhite_Potion();
public:
	virtual ~CWhite_Potion();

	// CGameObject을(를) 통해 상속됨
	virtual int Ready_GameObject() override;
	//virtual int Update_GameObject() override;
	virtual void Late_Update_GameObject() override;
//	virtual void Render_GameObject(HDC hDC) override;
	virtual void Release_GameObject() override;

	static CGameObject * Create(float posX, float posY);
};