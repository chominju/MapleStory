#pragma once
#include "GameObject.h"

class CItem;
class CInventory_RectManager
{
private:
	explicit CInventory_RectManager();
public:
	~CInventory_RectManager();


	// CGameObject을(를) 통해 상속됨
	int Ready_GameObject();
	int Update_GameObject();
	void Late_Update_GameObject();
	void Render_GameObject(HDC hDC);
	void Release_GameObject();
	void UpdateRect_GameObject();

	static CInventory_RectManager* Get_Instance()
	{
		return instance;
	}

	void SetPos(RECT pos)
	{
		m_info.x = pos.left;
		m_info.y = pos.top;
	}

	void Set_isEquipmentClick(bool equipment)
	{
		m_isEquipmentClick = equipment;
	}

	void Set_isConsumeClick(bool consume)
	{
		m_isConsumeClick = consume;
	}


	void Set_m_isEtcClick(bool etc)
	{
		m_isEtcClick = etc;
	}

	void Push_EquipmentList(CItem * item);
	void Push_ConsumeList(CItem * item);
	void Push_EtcList(CItem * item);

	void Find_EquipmentList(char * itemName);
	void Find_ConsumeList(char * itemName);
	void Find_EtcList(char * itemName);

	void Use_Item(char * itemName);
	void Drop_Item(char * itemName, Object_Info pos);

	list<CItem*>* Get_EquipmentList()
	{
		return &m_equipmentList;
	}

	list<CItem*>* Get_ConsumeList()
	{
		return &m_consumeList;
	}

	list<CItem*>* Get_EtcList()
	{
		return &m_etcList;
	}

	list<CItem*>* Get_CurrentList()
	{
		if (m_isEquipmentClick)
			return &m_equipmentList;
		if (m_isConsumeClick)
			return &m_consumeList;
		if (m_isEtcClick)
			return &m_etcList;
	}

	static void Create(RECT pos);

private:
	static CInventory_RectManager* instance;
	//list<Object_Info> m_equipmentList;
	//list<Object_Info> m_consumeList;
	//list<Object_Info> m_etcList;

	list<CItem*> m_equipmentList;
	list<CItem*> m_consumeList;
	list<CItem*> m_etcList;
	Object_Info m_info;
	bool m_isEquipmentClick;
	bool m_isConsumeClick;
	bool m_isEtcClick;

};

