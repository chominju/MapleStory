#include "stdafx.h"
#include "MainApp.h"
#include "LoadData.h"
#include "Bitmap_Manager.h"
#include "MyBitmap.h"
#include "Player.h"
#include "Line_Manager.h"
#include "Scene_Manager.h"
#include "Key_Manager.h"
#include "GameObject_Manager.h"
#include "Scroll_Manager.h"

CMainApp::CMainApp()
	: m_szFPS(L"")
	, m_iFPS(0)
	, m_dwFPSTime(0)
{
}


CMainApp::~CMainApp()
{
	Release_MainApp();
}

int CMainApp::Ready_MainApp()
{
	CLoadData::Get_Instance()->Load_Image();

	m_hDC = GetDC(g_hwnd);
	m_dwFPSTime = GetTickCount();

	CSoundMgr::Get_Instance()->Initialize();
	CScene_Manager::Get_Instance()->Change_Scene_Manager(Scene_ID::SCENE_MENU);
	return READY_OK;
}

void CMainApp::Update_MainApp()
{
	CKey_Manager::Get_Instance()->Update_Key_Manager();
	CScene_Manager::Get_Instance()->Update_Scene_Manager();

	CScroll_Manager::ScrollLock();
}

void CMainApp::Render_MainApp()
{
	++m_iFPS;
	if (m_dwFPSTime + 1000 < GetTickCount())
	{
		swprintf_s(m_szFPS, L"FPS : %d", m_iFPS);
		m_iFPS = 0;
		m_dwFPSTime = GetTickCount();
	}

	HDC doubleBuffer = CBitmap_Manager::Get_Instance()->Get_memDC(L"BackBuffer");
	if (nullptr == doubleBuffer)
		return;

	HDC backBuffer = CBitmap_Manager::Get_Instance()->Get_memDC(L"BackBuffer");
	if (nullptr == backBuffer)
		return;

	BitBlt(doubleBuffer,// 복사하고자 하는 대상 
		0, 0,// 그릴 시작 위치
		WINCX, WINCY, // 그림의 크기 
		backBuffer,//복사할 대상 
		0, 0, //그림에서의 시작 위치 
		SRCCOPY); // 그릴 형식. 
	TextOut(doubleBuffer, 100, 100, m_szFPS, lstrlen(m_szFPS));

	
	CScene_Manager::Get_Instance()->Render_Scene_Manager(doubleBuffer);
	BitBlt(m_hDC, 0, 0, WINCX, WINCY, doubleBuffer, 0, 0, SRCCOPY);
}

void CMainApp::Release_MainApp()
{
	ReleaseDC(g_hwnd, m_hDC);
	CScene_Manager::Destroy_Instance();
}

CMainApp * CMainApp::Create()
{
	CMainApp* pInstance = new CMainApp;
	if (0 > pInstance->Ready_MainApp())// 나는 실패시 음수를 반환하게끔 만들어 줄거! 
	{
		delete pInstance;
		pInstance = nullptr;
		return pInstance;
	}
	return pInstance;
}