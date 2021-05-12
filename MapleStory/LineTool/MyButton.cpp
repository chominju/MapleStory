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
				// Scene이 변경되는 상황이면 이미 버튼은 삭제된 상태. 
				// 이때 소실된 공간에 있는 멤버를 건드린다?? 
				// 당연 안되지. 이거 잊어버리지마. 
				// 지금 수업때야 안 터지고 있는데 언제든지 정말 뭐 하나 생성할 때 터질수도 있고
				// 안 터질수도 있고 아주 지멋대로 코드 완성 시키지 말고 
				// 이러한 곳에서는 바로 빠져나갈 수 잇게 코드를 작성하자. 
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
