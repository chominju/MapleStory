#include "stdafx.h"
#include "MyButton.h"
#include "Tool_Key_Manager.h"
#include "Tool_Scroll_Manager.h"
#include "Tool_Scene_Manager.h"
#include "Tool_Bitmap_Manager.h"
CMyButton::CMyButton()
	:m_dwDrawID(0)
{
}


CMyButton::~CMyButton()
{
}

int CMyButton::Ready_GameObject()
{
	m_info.sizeX = 150;
	m_info.sizeY= 150;
	m_wstrFrameKey = L"";
	return 0;
}

int CMyButton::Update_GameObject()
{
	return 0;
}

void CMyButton::Late_Update_GameObject()
{
	POINT pt = {}; 
	GetCursorPos(&pt); 
	ScreenToClient(g_hwnd, &pt); 
	
	if (PtInRect(&m_rect, pt))
	{
		if (CKey_Manager::Get_Instance()->Key_Up(KEY_LBUTTON))
		{
			if (!lstrcmp(m_wstrFrameKey.c_str(), L"Tool_Button1"))
			{
				CScene_Manager::Get_Instance()->Change_Scene_Manager(CScene_Manager::TOOL_ID::TOOL_KERNINGCITY);
				// Scene�� ����Ǵ� ��Ȳ�̸� �̹� ��ư�� ������ ����. 
				// �̶� �ҽǵ� ������ �ִ� ����� �ǵ帰��?? 
				// �翬 �ȵ���. �̰� �ؾ��������. 
				// ���� �������� �� ������ �ִµ� �������� ���� �� �ϳ� ������ �� �������� �ְ�
				// �� �������� �ְ� ���� ���ڴ�� �ڵ� �ϼ� ��Ű�� ���� 
				// �̷��� �������� �ٷ� �������� �� �հ� �ڵ带 �ۼ�����. 
				return; 
			}
			else if (m_wstrFrameKey == L"Tool_Button2")
			{
				CScene_Manager::Get_Instance()->Change_Scene_Manager(CScene_Manager::TOOL_ID::TOOL_FIELD);
				return; 
			}
			else if (m_wstrFrameKey == L"Tool_Button3")
			{
				CScene_Manager::Get_Instance()->Change_Scene_Manager(CScene_Manager::TOOL_ID::TOOL_BOSS);
				return;
			}
		}
		//m_dwDrawID = 1;
		
	}
	//else
		//m_dwDrawID = 0; 
}

void CMyButton::Render_GameObject(HDC hDC)
{
	CGameObject::UpdateRect_GameObject(); 
	HDC hMemDC = CBitmap_Manager::Get_Instance()->Get_memDC(m_wstrFrameKey.c_str());
	if (nullptr == hMemDC)
		return; 
	GdiTransparentBlt(hDC,
		m_rect.left, m_rect.top,
		m_info.sizeX, m_info.sizeY,
		hMemDC,
		0, 0,
		m_info.sizeX, m_info.sizeY, RGB(10,10,10));
}

void CMyButton::Release_GameObject()
{
}

CGameObject * CMyButton::Create()
{
	CGameObject* pInstance = new CMyButton; 
	if (0> pInstance->Ready_GameObject())
	{
		Safe_Delete(pInstance); 
		return nullptr;
	}
	return pInstance; 
}
