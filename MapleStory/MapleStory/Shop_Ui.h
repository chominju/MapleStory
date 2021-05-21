#pragma once
#include "Ui.h"

class CItem;
class CShop_Ui :
	public CUi
{
private:
	explicit CShop_Ui();
public:
	virtual ~CShop_Ui();

	virtual int Ready_GameObject() override;
	virtual int Update_GameObject() override;
	virtual void Late_Update_GameObject() override;
	virtual void Render_GameObject(HDC hDC) override;
	virtual void Release_GameObject() override;

public:
	static CGameObject * Create(CGameObject * npc);
private:
	static CGameObject* instance;
	CGameObject * m_player;

	HDC m_equipment_hdc;
	HDC m_consume_hdc;
	HDC m_etc_hdc;
	HDC m_close_hdc;

	CGameObject* m_EquipmentButton;
	CGameObject* m_ConsumeButton;
	CGameObject* m_EtcButton;
	CGameObject* m_CloseButton;

	bool m_isEquipmentClick;
	bool m_isConsumeClick;
	bool m_isEtcClick;
};

