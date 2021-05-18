#pragma once
#include "Scene.h"
class CBossMap :
	public CScene
{
private:
	explicit CBossMap();
public:
	virtual ~CBossMap();

	// CScene을(를) 통해 상속됨
	virtual int Ready_Scene() override;
	virtual void Update_Scene() override;
	virtual void Render_Scene(HDC hdc) override;
	virtual void Release_Scene() override;
	virtual void Create_Rope_Scene() override;

public:
	static CScene* Create();
};

