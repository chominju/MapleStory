#pragma once
#include "GameObject.h"
class CNpc :
	public CGameObject
{
private:
	explicit CNpc();
	virtual ~CNpc();

public:
	// CGameObject을(를) 통해 상속됨
	virtual int Ready_GameObject() override;
	virtual int Update_GameObject() override;
	virtual void Late_Update_GameObject() override;
	virtual void Render_GameObject(HDC hDC) override;
	virtual void Release_GameObject() override;
	virtual void UpdateRect_GameObject() override;

	bool Get_isNpcClick()
	{
		return m_isNpcClick;
	}

	void Set_isNpcClick(bool npcClick)
	{
		m_isNpcClick= npcClick;
	}

public:
	static CGameObject* Create();
private:
	static CGameObject * m_instance;
	CGameObject* m_shopUi;
	bool m_isNpcClick;
};

