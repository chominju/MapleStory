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
	//BitBlt(m_hDC,// �����ϰ��� �ϴ� ��� 
	//	0, 0,// �׸� ���� ��ġ
	//	WINCX, WINCY, // �׸��� ũ�� 
	//	tempDC,//������ ��� 
	//	0, 0, //�׸������� ���� ��ġ 
	//	SRCCOPY); // �׸� ����. 

	HDC doubleBuffer = CBitmap_Manager::Get_Instance()->Get_memDC(L"BackBuffer");
	if (nullptr == doubleBuffer)
		return;

	HDC backBuffer = CBitmap_Manager::Get_Instance()->Get_memDC(L"BackBuffer");
	if (nullptr == backBuffer)
		return;

	BitBlt(doubleBuffer,// �����ϰ��� �ϴ� ��� 
		0, 0,// �׸� ���� ��ġ
		WINCX, WINCY, // �׸��� ũ�� 
		backBuffer,//������ ��� 
		0, 0, //�׸������� ���� ��ġ 
		SRCCOPY); // �׸� ����. 
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
	if (0 > pInstance->Ready_MainApp())// ���� ���н� ������ ��ȯ�ϰԲ� ����� �ٰ�! 
	{
		delete pInstance;
		pInstance = nullptr;
		return pInstance;
	}
	return pInstance;
}
/*
������ ���� - *�����������̶� �̷��� ��Ȳ�̶�� �̷��� ������ Ŭ���� �������� ����ϴ� ����
��� ������* ��� ���� ���̰� �̸� �������� Ŭ�������� ����, Ŭ�������� �ൿ ����� �з��ϰ�
������ ���� ��ü�������� ���踦 ���� ���Ͽ���� ���� ���� �����Ǿ� �ڵ��� �������� ������
���·� ����� �����ϱ� ���ϰ� ���� ������ �����̶� �����ϸ� �ǰ�
�̰� ó�� �����Ѱ���
GOF�� �Ҹ��� 4���� ��ǻ�� ������ �����ڵ��� �� å (�̰� ����� ���̿� ������ ��ü���� ����Ʈ
������ ��� - ������ ���� ) �̶�� å�������� ���̱� ������.

���ͷ����� ����(�ݺ��� ���� ) - ���� ǥ������� �������� �ʰ� �������� ���� ����� �����ϴ� ����.
�̰� �⺻���� �̷��̰�.
*/