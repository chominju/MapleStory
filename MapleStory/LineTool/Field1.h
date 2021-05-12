#pragma once
#include "Scene.h"
class CField1 :
	public CScene
{
private:
	explicit CField1();
	virtual ~CField1();
public:
	// CScene을(를) 통해 상속됨
	virtual int Ready_Scene() override;
	virtual void Update_Scene() override;
	virtual void Render_Scene(HDC hDC) override;
	virtual void Release_Scene() override;

	static CScene* Create();
};

