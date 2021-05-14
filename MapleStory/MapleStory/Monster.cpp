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


	GdiTransparentBlt(hDC, // �׸��� �����ϰ��� �ϴ� ���. 
		m_rect.left + scrollX,//��ġ x,y
		m_rect.top + scrollY,
		m_info.sizeX,// ũ�� xy
		m_info.sizeY,
		m_hdc,// ���� �� ���
		m_animFrame.frame_start*m_info.sizeX, m_animFrame.frame_animation * m_info.sizeY,// �׸��� ���� ��ġ x,y
		m_info.sizeX,// �׸����� �ϴ� ������ ũ�� x,y
		m_info.sizeY,
		RGB(255, 0, 255));


	GdiTransparentBlt(hDC, // �׸��� �����ϰ��� �ϴ� ���. 
		m_rect.left + scrollX,//��ġ x,y
		m_rect.top -20 + scrollY,
		m_info.sizeX,// ũ�� xy
		10,
		m_hpBackBar_hdc,// ���� �� ���
		0,0,// �׸��� ���� ��ġ x,y
		182,// �׸����� �ϴ� ������ ũ�� x,y
		21,
		RGB(255, 0, 255));



	GdiTransparentBlt(hDC, // �׸��� �����ϰ��� �ϴ� ���. 
		m_rect.left + scrollX,//��ġ x,y
		m_rect.top -20 + scrollY,
		m_info.sizeX *(10.f/100.f),// ũ�� xy
		10,
		m_hpBar_hdc,// ���� �� ���
		0, 0,// �׸��� ���� ��ġ x,y
		182,// �׸����� �ϴ� ������ ũ�� x,y
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
