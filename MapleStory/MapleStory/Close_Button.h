#pragma once
#include "GameObject.h"
class CClose_Button :
	public CGameObject
{
private:
	explicit CClose_Button();
	virtual ~CClose_Button();
public:
	void Set_FrameKey(const wstring& bitMapKey) { m_BitMapKey = bitMapKey; }
	// CGameObject을(를) 통해 상속됨
	virtual int Ready_GameObject() override;
	virtual int Update_GameObject() override;
	virtual void Late_Update_GameObject() override;
	virtual void Render_GameObject(HDC hDC) override;
	virtual void Release_GameObject() override;
	virtual void UpdateRect_GameObject() override;

	bool Get_isCloseButton()
	{
		return m_isCloseButton;
	}

	void Set_isCloseButton(bool isCloseButton)
	{
		m_isCloseButton = isCloseButton;
	}
public:
	static CGameObject*Create();
private:
	wstring m_BitMapKey;
	DWORD m_dwDrawID;
	bool m_isCloseButton;
};