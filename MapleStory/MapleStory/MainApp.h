#pragma once
class CGameObject;
class CMainApp final
{
private:
	CMainApp();
public:
	~CMainApp();
public:
	int Ready_MainApp();
	void Update_MainApp();
	void Render_MainApp();
	void Release_MainApp();
public:
	static CMainApp* Create();
private:
	TCHAR						m_szFPS[32];
	int							m_iFPS;
	DWORD						m_dwFPSTime;
	HDC							m_hDC;

	CGameObject * m_player;
};
