#pragma once
#include "GameObject.h"
class CUi :
	public CGameObject
{
public:
	explicit CUi();
	virtual ~CUi();

	// CGameObject을(를) 통해 상속됨
	virtual int Ready_GameObject() override;
	virtual int Update_GameObject() override;
	virtual void Late_Update_GameObject() override;
	virtual void Render_GameObject(HDC hDC) override;
	virtual void Release_GameObject() override;
	virtual void UpdateRect_GameObject() override;


	void Set_UiData(Object_Data* data)
	{
		m_data = *data;
	}


protected:
	HDC m_expBar_hdc;
	HDC m_expBackBar_hdc;
	HDC m_State_Lv_hdc;
	HDC m_State_LvNum_hdc;
	HDC m_State_Num_hdc;
};

