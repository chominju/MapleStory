#pragma once
#include "Ui.h"
class CItem;
class CInventory_Ui :
	public CUi
{
private:
	explicit CInventory_Ui();
public:
	virtual ~CInventory_Ui();

	virtual int Ready_GameObject() override;
	virtual int Update_GameObject() override;
	virtual void Late_Update_GameObject() override;
	virtual void Render_GameObject(HDC hDC) override;
	virtual void Release_GameObject() override;

public:
	static CGameObject * Create();

private:
	static CGameObject* instance;
	CGameObject * m_player;

	HDC m_equipment_hdc;
	HDC m_consume_hdc;
	HDC m_etc_hdc;

	CGameObject* m_EquipmentButton;
	CGameObject* m_ConsumeButton;
	CGameObject* m_EtcButton;

	CItem * temp;
	list<CItem*>::iterator beforeIter;
	Object_Info m_beforePos;
	bool m_isItemMove;
};

