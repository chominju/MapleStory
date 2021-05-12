#pragma once
#include "Scene.h"
class CMap1 :
	public CScene
{
private:
	explicit CMap1();
public:
	virtual ~CMap1();

	// CScene을(를) 통해 상속됨
	virtual int Ready_Scene() override;
	virtual void Update_Scene() override;
	virtual void Render_Scene(HDC hdc) override;
	virtual void Release_Scene() override;

public:
	static CScene* Create();
};

