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

	static CInventory_RectManager* Get_Instance()
	{
		return instance;
	}

	void SetPos(RECT pos)
	{
		m_info.x = (float)pos.left;
		m_info.y = (float)pos.top;
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

	void Use_Item(CItem*& useItem);
	void Use_ItemQuickSlot(char * itemName);
	void Drop_Item(char * itemName, Object_Info pos, CItem*& item, list<CItem*>::iterator * Dropiter);
	void Find_DeleteItem(char * itemName , CItem*& useItem);
	void DeleteItem(CItem* item, Pos_float shopPos);

	int Get_ItemQuantity(char * itemName);

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
		else if (m_isConsumeClick)
			return &m_consumeList;
		else if (m_isEtcClick)
			return &m_etcList;
		else
			return nullptr;
	}

	static void Create(RECT pos);

private:
	static CInventory_RectManager* instance;

	list<CItem*> m_equipmentList;
	list<CItem*> m_consumeList;
	list<CItem*> m_etcList;
	Object_Info m_info;
	bool m_isEquipmentClick;
	bool m_isConsumeClick;
	bool m_isEtcClick;

	list<CItem*>::iterator m_deleteIter;
	Object_Info m_deleteItemPos;
};

