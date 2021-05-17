#pragma once
#include "GameObject.h"
class CInventory_Button :
	public CGameObject
{
private:
	explicit CInventory_Button();
	virtual ~CInventory_Button();
public:
	void Set_FrameKey(const wstring& bitMapKey) { m_BitMapKey = bitMapKey; }
	// CGameObject을(를) 통해 상속됨
	virtual int Ready_GameObject() override;
	virtual int Update_GameObject() override;
	virtual void Late_Update_GameObject() override;
	virtual void Render_GameObject(HDC hDC) override;
	virtual void Release_GameObject() override;
	virtual void UpdateRect_GameObject() override;

	bool Get_IsEquipmentClick()
	{
		return m_isEquipmentClick;
	}

	bool Get_IsConsumeClick()
	{
		return m_isConsumeClick;
	}

	bool Get_IsEtcClick()
	{
		return m_isEtcClick;
	}

public:
	static CGameObject*Create();
private:
	wstring m_BitMapKey;
	DWORD m_dwDrawID;
	static bool m_isEquipmentClick;
	static bool m_isConsumeClick;
	static bool m_isEtcClick;
};	