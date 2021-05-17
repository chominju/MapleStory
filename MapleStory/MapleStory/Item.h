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

	void Set_Change_Quantity(int quantity)
	{
		m_itemInfo.quantity += quantity;
	}

	void Set_m_isFieldOut(bool fieldOut)
	{
		m_isFieldOut = fieldOut;
	}

protected:
	Item_Info m_itemInfo;
	bool m_isFieldOut;
	HDC m_State_Num_hdc;
};

