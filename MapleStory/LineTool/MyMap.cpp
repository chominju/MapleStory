#include "stdafx.h"
#include "MyMap.h"
#include "Key_Manager.h"
#include "Line_Manager.h"
#include "Bitmap_Manager.h"
#include "Scroll_Manager.h"
#include "SaveData.h"
CMyMap * CMyMap::m_instance=nullptr;

CMyMap::CMyMap(TCHAR * mapName)
	:m_mapName(mapName)
{
	//m_mapName = mapName;
}

CMyMap::~CMyMap()
{
}

void CMyMap::Update_MyMap()
{
	CKey_Manager::Get_Instance()->Update_Key_Manager();
	CLine_Manager::Get_Instance()->Update_Line_Manager();
	if (CKey_Manager::Get_Instance()->Key_Up(VK_SPACE))
		CSaveData::Get_Instance()->Save_Data(m_mapName);

}

void CMyMap::Render_MyMap(HDC hDC)
{
	POINT pt{};
	pt.x -= CScroll_Manager::Get_ScrollX();
	pt.y -= CScroll_Manager::Get_ScrollY();
	BitBlt(hDC,// �����ϰ��� �ϴ� ��� 
		0,0,// �׸� ���� ��ġ
		WINCX, WINCY, // �׸��� ũ�� 
		m_hdc,//������ ��� 
		pt.x, pt.y, //�׸������� ���� ��ġ 
		SRCCOPY); // �׸� ����. 
	CLine_Manager::Get_Instance()->Render_Line_Manager(hDC);
}

void CMyMap::Ready_MyMap()
{
	m_hdc = CBitmap_Manager::Get_Instance()->Get_memDC(m_mapName);
}

CMyMap * CMyMap::Get_Instance()
{
	return m_instance;
}

void CMyMap::Create_MyMap(TCHAR * mapName)
{
	if (m_instance == nullptr)
		m_instance = new CMyMap(mapName);
	m_instance->Ready_MyMap();
}