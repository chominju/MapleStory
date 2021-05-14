#pragma once
#include "Scene.h"
class CField1 :
	public CScene
{
private:
	explicit CField1();
public:
	virtual ~CField1();

	// CScene을(를) 통해 상속됨
	virtual int Ready_Scene() override;
	virtual void Update_Scene() override;
	virtual void Render_Scene(HDC hdc) override;
	virtual void Release_Scene() override;
	virtual void Create_Rope_Scene() override;

	void CreateMonster();

public:
	static CScene* Create();
};

