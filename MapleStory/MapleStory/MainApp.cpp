#include "stdafx.h"
#include "MainApp.h"
#include "LoadData.h"
#include "MyBitmap.h"
#include "Player.h"
#include "Line_Manager.h"

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
	return READY_OK;
}

void CMainApp::Update_MainApp()
{
	m_player->Update_GameObject();
	m_player->Late_Update_GameObject();
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



	//if(CLoadData::Get_Instance()->Get_Map().end()==iter)
	Rectangle(m_hDC, 0, 0, WINCX, WINCY);
	// 	Rectangle(m_hDC, 100, 100, WINCX - 100, WINCY - 100);

	//HDC hDoubleBuffer = ;
	//HDC hMemDC;
	//BitBlt(hDoubleBuffer,// �����ϰ��� �ϴ� ��� 
	//	0, 0,// �׸� ���� ��ġ
	//	WINCX, WINCY, // �׸��� ũ�� 
	//	hMemDC,//������ ��� 
	//	0, 0, //�׸������� ���� ��ġ 
	//	SRCCOPY); // �׸� ����. 
	//TextOut(hDoubleBuffer, 100, 100, m_szFPS, lstrlen(m_szFPS));
	//
	m_player->Render_GameObject(m_hDC);
	CLine_Manager::Get_Instance()->Render_Line_Manager(m_hDC);
	//BitBlt(m_hDC, 0, 0, WINCX, WINCY, hDoubleBuffer, 0, 0, SRCCOPY);
}

void CMainApp::Release_MainApp()
{
	ReleaseDC(g_hwnd, m_hDC);
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