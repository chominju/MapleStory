#include "stdafx.h"
#include "Portal.h"
#include "Bitmap_Manager.h"
#include "Scroll_Manager.h"

CPortal::CPortal()
{
}


CPortal::~CPortal()
{
}

int CPortal::Ready_GameObject()
{
	m_hdc = CBitmap_Manager::Get_Instance()->Get_memDC(L"Portal");
	m_info.sizeX = 104;
	m_info.sizeY = 142;
	m_animFrame.frame_animation = 0;
	m_animFrame.frame_end = 8;
	m_animFrame.frame_speed = 300;
	m_animFrame.frame_start = 0;
	m_animFrame.frame_time = GetTickCount();

	return S_OK;
}

int CPortal::Update_GameObject()
{
	Play_Animation();
	return 0;
}

void CPortal::Late_Update_GameObject()
{
}

void CPortal::Render_GameObject(HDC hDC)
{
	UpdateRect_GameObject();
	int scrollX = CScroll_Manager::Get_ScrollX();
	int scrollY = CScroll_Manager::Get_ScrollY();

	GdiTransparentBlt(hDC, // �׸��� �����ϰ��� �ϴ� ���. 
		m_rect.left + scrollX,//��ġ x,y
		m_rect.top + scrollY,
		m_info.sizeX,// ũ�� xy
		m_info.sizeY,
		m_hdc,// ���� �� ���
		m_animFrame.frame_start*m_info.sizeX, m_animFrame.frame_animation * m_info.sizeY,// �׸��� ���� ��ġ x,y
		m_info.sizeX,// �׸����� �ϴ� ������ ũ�� x,y
		m_info.sizeY,
		RGB(242, 242, 242));
}

void CPortal::Release_GameObject()
{
}

void CPortal::UpdateRect_GameObject()
{
	m_rect.left = static_cast<LONG>(m_info.x - (m_info.sizeX / 2));
	m_rect.top = static_cast<LONG>(m_info.y - (m_info.sizeY / 2));
	m_rect.right = static_cast<LONG>(m_info.x + (m_info.sizeX / 2));
	m_rect.bottom = static_cast<LONG>(m_info.y + (m_info.sizeY / 2));
}

CGameObject * CPortal::Create()
{
	CGameObject *instance = new CPortal();
	if (0 > instance->Ready_GameObject())
	{
		Safe_Delete(instance);
		return nullptr;
	}
	return instance;
}
