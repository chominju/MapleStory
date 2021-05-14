#include "stdafx.h"
#include "Monster.h"
#include "Scroll_Manager.h"

CMonster::CMonster()
{
}

CMonster::~CMonster()
{
}

int CMonster::Ready_GameObject()
{
	return 0;
}

int CMonster::Update_GameObject()
{
	Play_Animation();

	return 0;
}

void CMonster::Late_Update_GameObject()
{
	Play_Animation();
}

void CMonster::Render_GameObject(HDC hDC)
{
	UpdateRect_GameObject();

	int scrollX = CScroll_Manager::Get_ScrollX();
	int scrollY = CScroll_Manager::Get_ScrollY();


	GdiTransparentBlt(hDC, // 그림을 복사하고자 하는 대상. 
		m_rect.left + scrollX,//위치 x,y
		m_rect.top + scrollY,
		m_info.sizeX,// 크기 xy
		m_info.sizeY,
		m_hdc,// 복사 할 대상
		m_animFrame.frame_start*m_info.sizeX, m_animFrame.frame_animation * m_info.sizeY,// 그림의 시작 위치 x,y
		m_info.sizeX,// 그리고자 하는 영역의 크기 x,y
		m_info.sizeY,
		RGB(255, 0, 255));


	GdiTransparentBlt(hDC, // 그림을 복사하고자 하는 대상. 
		m_rect.left + scrollX,//위치 x,y
		m_rect.top -20 + scrollY,
		m_info.sizeX,// 크기 xy
		10,
		m_hpBackBar_hdc,// 복사 할 대상
		0,0,// 그림의 시작 위치 x,y
		182,// 그리고자 하는 영역의 크기 x,y
		21,
		RGB(255, 0, 255));



	GdiTransparentBlt(hDC, // 그림을 복사하고자 하는 대상. 
		m_rect.left + scrollX,//위치 x,y
		m_rect.top -20 + scrollY,
		m_info.sizeX *(10.f/100.f),// 크기 xy
		10,
		m_hpBar_hdc,// 복사 할 대상
		0, 0,// 그림의 시작 위치 x,y
		182,// 그리고자 하는 영역의 크기 x,y
		21,
		RGB(255, 0, 255));
}

void CMonster::Release_GameObject()
{
}

void CMonster::UpdateRect_GameObject()
{
	m_rect.left = static_cast<LONG>(m_info.x - (m_info.sizeX / 2));
	m_rect.top = static_cast<LONG>(m_info.y - (m_info.sizeY / 2));
	m_rect.right = static_cast<LONG>(m_info.x + (m_info.sizeX / 2));
	m_rect.bottom = static_cast<LONG>(m_info.y + (m_info.sizeY / 2));
}
