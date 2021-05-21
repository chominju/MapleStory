#pragma once
#include "GameObject.h"
class CItem :
	public CGameObject
{
public:
	explicit CItem();
	virtual ~CItem();

	// CGameObject을(를) 통해 상속됨
	virtual int Ready_GameObject() override;
	virtual int Update_GameObject() override;
	virtual void Late_Update_GameObject() override;
	virtual void Render_GameObject(HDC hDC) override;
	virtual void Release_GameObject() override;
	virtual void UpdateRect_GameObject() override;

	Item_Info* Get_ItemInfo()
	{
		return &m_itemInfo;
	}

	void Set_ItemInfo(Item_Info itemInfo)
	{
		m_itemInfo = itemInfo;
	}

	void Set_Change_Quantity(int quantity)
	{
		m_itemInfo.quantity += quantity;
	}

	void Set_Quantity(int quantity)
	{
		m_itemInfo.quantity = quantity;
	}

	void Set_m_isFieldOut(bool fieldOut)
	{
		m_isFieldOut = fieldOut;
	}

	void Set_Money(int money)
	{
		m_itemInfo.money = money;
	}

	void Set_shopPos(float x, float y)
	{
		m_shopPos.x = x;
		m_shopPos.y = y;
	}

	Pos_float Get_shopPos()
	{
		return m_shopPos;
	}

	RECT* Get_ShopRect()
	{
		return &m_shopRect;
	}

protected:
	Item_Info m_itemInfo;
	Pos_float m_shopPos;
	bool m_isFieldOut;
	HDC m_State_Num_hdc;
	int m_selectImageX;
	int m_selectImageY;
	RECT m_shopRect;
};

