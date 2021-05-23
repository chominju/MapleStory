#pragma once
#include "Scene.h"
class CMenu :
	public CScene
{
private:
	explicit CMenu();
public:
	virtual ~CMenu();

	// CScene을(를) 통해 상속됨
	virtual int Ready_Scene() override;
	virtual void Update_Scene() override;
	virtual void Render_Scene(HDC hdc) override;
	virtual void Release_Scene() override;
	virtual void Create_Rope_Scene() override;
public:
	static CScene* Create();
};

