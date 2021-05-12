#pragma once
#include "Tool_GameObject.h"

class CMyButton final:
	public CGameObject
{
private:
	CMyButton();
public:
	virtual ~CMyButton();
public:
	void Set_FrameKey(const wstring& wstrFrameKey) { m_wstrFrameKey = wstrFrameKey; }
public:
	// CGameObject을(를) 통해 상속됨
	virtual int Ready_GameObject() override;
	virtual int Update_GameObject() override;
	virtual void Late_Update_GameObject() override;
	virtual void Render_GameObject(HDC hDC) override;
	virtual void Release_GameObject() override;
public:
	static CGameObject* Create();
	wstring m_wstrFrameKey; 
	DWORD m_dwDrawID; 
};

