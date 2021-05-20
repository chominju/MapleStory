#pragma once
class CScene abstract
{
public:
	explicit CScene();
	virtual ~CScene();

public:
	virtual int Ready_Scene() = 0;
	virtual void Update_Scene() = 0;
	virtual void Render_Scene(HDC hdc) = 0;
	virtual void Release_Scene() = 0;
	virtual void Create_Rope_Scene() = 0;
	Pos_int& GetSceneSize()
	{
		return m_SceneSize;
	}


protected:
	HDC m_hdc;
	Pos_int m_SceneSize;
};

