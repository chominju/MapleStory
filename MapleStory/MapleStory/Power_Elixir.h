#pragma once
#include "Item.h"
class CPower_Elixir :
	public CItem
{
private:
	explicit CPower_Elixir();
public:
	virtual ~CPower_Elixir();

	// CGameObject��(��) ���� ��ӵ�
	virtual int Ready_GameObject() override;
	virtual void Late_Update_GameObject() override;
	virtual void Release_GameObject() override;

	static CGameObject * Create(float posX, float posY);
	static CItem * Create();

	virtual int Get_ItemInfoHp();
};