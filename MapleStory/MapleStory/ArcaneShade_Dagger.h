#pragma once
#include "Item.h"
class CArcaneShade_Dagger :
	public CItem
{
private:
	explicit CArcaneShade_Dagger();
public:
	virtual ~CArcaneShade_Dagger();

	// CGameObject을(를) 통해 상속됨
	virtual int Ready_GameObject() override;
	//virtual int Update_GameObject() override;
	virtual void Late_Update_GameObject() override;
	//	virtual void Render_GameObject(HDC hDC) override;
	virtual void Release_GameObject() override;

	static CGameObject * Create(float posX, float posY);
	static CItem * Create();
};