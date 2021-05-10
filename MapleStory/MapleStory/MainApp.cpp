#include "stdafx.h"
#include "MainApp.h"
#include "LoadData.h"
#include "Bitmap_Manager.h"
#include "MyBitmap.h"
#include "Player.h"
#include "Line_Manager.h"
#include "Scene_Manager.h"

CMainApp::CMainApp()
//:m_pPlayer(nullptr)
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
	CLoadData::Get_Instance()->Load_Line();

	m_hDC = GetDC(g_hwnd);
	m_dwFPSTime = GetTickCount();
	m_player = CPlayer::Create();
	/*CBitmap_Manager::Get_Instance()->Insert_Bitmap_Manager(L"Maja", L"../Image/maja2.bmp");
	CBitmap_Manager::Get_Instance()->Insert_Bitmap_Manager(L"BackBuffer", L"../Image/BackBuffer.bmp");
	CBitmap_Manager::Get_Instance()->Insert_Bitmap_Manager(L"DoubleBuff", L"../Image/Back.bmp");
	CGameObject* pObject = CPlayer::Create();
	CGameObject_Manager::Get_Instance()->Add_GameObject_Manager(OBJECT::PLAYER, pObject);

	pObject = CMonster::Create();
	CGameObject_Manager::Get_Instance()->Add_GameObject_Manager(OBJECT::MONSTER, pObject);

	pObject = CMouse::Create();
	CGameObject_Manager::Get_Instance()->Add_GameObject_Manager(OBJECT::MOUSE, pObject);

	CLine_Manager::Get_Instance()->Ready_Line_Manager();*/
	CScene_Manager::Get_Instance()->Change_Scene_Manager(Scene_ID::SCENE_Kerning_City);
	return READY_OK;
}

void CMainApp::Update_MainApp()
{
	m_player->Update_GameObject();
	m_player->Late_Update_GameObject();
	CScene_Manager::Get_Instance()->Update_Scene_Manager();
	//CKey_Manager::Get_Instance()->Update_Key_Manager();
	//CGameObject_Manager::Get_Instance()->Update_GameObject_Manager();
	//CGameObject_Manager::Get_Instance()->Late_Update_GameObject_Manager();

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

	//map<const TCHAR*, CMyBitmap*>* m_map_bitMap = CLoadData::Get_Instance()->Get_Map();
	//auto& iter = find_if(m_map_bitMap->begin(), m_map_bitMap->end(), [&](auto& rpair )
	//{
	//	return !lstrcmp(L"Player1", rpair.first);
	//});
	//HDC tempDC = iter->second->Get_memDC();
	//if (tempDC == nullptr)
	//	return;
	//BitBlt(m_hDC,// 복사하고자 하는 대상 
	//	0, 0,// 그릴 시작 위치
	//	WINCX, WINCY, // 그림의 크기 
	//	tempDC,//복사할 대상 
	//	0, 0, //그림에서의 시작 위치 
	//	SRCCOPY); // 그릴 형식. 

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
	CLine_Manager::Get_Instance()->Render_Line_Manager(doubleBuffer);
	m_player->Render_GameObject(doubleBuffer);
	BitBlt(m_hDC, 0, 0, WINCX, WINCY, doubleBuffer, 0, 0, SRCCOPY);
}

void CMainApp::Release_MainApp()
{
	ReleaseDC(g_hwnd, m_hDC);
	CScene_Manager::Destroy_Instance();
	//CBitmap_Manager::Destroy_Instance();
	//CKey_Manager::Destroy_Instance();
	//CGameObject_Manager::Destroy_Instance();
	//CLine_Manager::Destroy_Instance();
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
/*
디자인 패턴 - *디자인패턴이란 이러한 상황이라면 이러한 형태의 클래스 디자인을 사용하는 것이
대게 좋더라* 라는 것이 모이고 이를 바탕으로 클래스간의 관계, 클래스간의 행동 양식을 분류하고
각각에 대해 객체지향적인 설계를 따른 노하우들이 차곡 차곡 정리되어 코드의 구조들을 일정한
형태로 만들어 재사용하기 편리하게 만든 일정한 패턴이라 생각하면 되고
이걸 처음 제시한것이
GOF라 불리는 4명의 컴퓨터 과학자 연구자들이 쓴 책 (이건 영어로 재이용 가능한 객체지향 소프트
웨어의 요소 - 디자인 패턴 ) 이라는 책에서부터 쓰이기 시작함.

이터레이터 패턴(반복자 패턴 ) - 내부 표현방식은 공개하지 않고 순차적인 접근 방법을 제공하는 패턴.
이게 기본적인 이론이고.
*/