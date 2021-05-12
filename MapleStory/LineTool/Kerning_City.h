#pragma once
#include "Scene.h"
class CKerning_City :
	public CScene
{
private:
	explicit CKerning_City();
	virtual ~CKerning_City();

public:
	// CScene��(��) ���� ��ӵ�
	virtual int Ready_Scene() override;
	virtual void Update_Scene() override;
	virtual void Render_Scene(HDC hDC) override;
	virtual void Release_Scene() override;
	
	static CScene* Create();
};

