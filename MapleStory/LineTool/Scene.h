#pragma once
class CScene abstract
{
public:
	explicit CScene();
	virtual ~CScene();
public:
	virtual int Ready_Scene() =0;
	virtual void Update_Scene() = 0; 
	virtual void Render_Scene(HDC hDC) = 0; 
	virtual void Release_Scene() = 0; 

	void Set_MapName(TCHAR * mapName)
	{
		m_mapName = mapName;
	}

	void Set_SaveName(TCHAR * saveName)
	{
		m_saveName = saveName;
	}
	void Set_Hdc(TCHAR * keyName);
	void Set_StartPos(TCHAR * keyName);

protected:
	TCHAR* m_mapName;
	TCHAR* m_saveName;
	HDC m_hdc;
	Pos_float m_startPos;
};

