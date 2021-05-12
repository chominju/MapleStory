#pragma once
#include "GameObject.h"
class CPortal :
	public CGameObject
{
private:
	explicit CPortal();
public:
	virtual ~CPortal();

	// CGameObject을(를) 통해 상속됨
	virtual int Ready_GameObject() override;
	virtual int Update_GameObject() override;
	virtual void Late_Update_GameObject() override;
	virtual void Render_GameObject(HDC hDC) override;
	virtual void Release_GameObject() override;
	virtual void UpdateRect_GameObject() override;

	void Set_NextSceneID(Scene_ID id)
	{
		m_nextScene = id;
	}

	Scene_ID Get_NextSceneID()
	{
		return m_nextScene;
	}

public:
	static CGameObject* Create();
private:
	Scene_ID m_nextScene;
};

