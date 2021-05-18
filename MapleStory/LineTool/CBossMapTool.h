#pragma once
#include "Scene.h"
class CBossMapTool :
	public CScene
{
private:
	explicit CBossMapTool();
	virtual ~CBossMapTool();

public:
	// CScene��(��) ���� ��ӵ�
	virtual int Ready_Scene() override;
	virtual void Update_Scene() override;
	virtual void Render_Scene(HDC hDC) override;
	virtual void Release_Scene() override;

	static CScene* Create();

};

