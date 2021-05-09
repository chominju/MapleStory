#pragma once
class CMyMap
{
public:
	CMyMap(TCHAR* mapName);
	~CMyMap();

	void Update_MyMap();
	void Render_MyMap(HDC hDC);
	void Ready_MyMap();
	static CMyMap* Get_Instance();
	static void Create_MyMap(TCHAR* mapName);
private:
	static CMyMap * m_instance;
	TCHAR* m_mapName;
	HDC m_hdc;
};

