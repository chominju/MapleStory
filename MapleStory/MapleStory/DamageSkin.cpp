#include "stdafx.h"
#include "DamageSkin.h"
#include "Bitmap_Manager.h"
#include "Scroll_Manager.h"
CDamageSkin::CDamageSkin()
{
}

CDamageSkin::~CDamageSkin()
{
}

int CDamageSkin::Ready_GameObject()
{
	m_hdc = CBitmap_Manager::Get_Instance()->Get_memDC(L"Damage_Skin");
	m_info.sizeX = 43;
	m_info.sizeY = 49;
	m_disappearTime = GetTickCount();
	m_disappearSpeed = 500;
	printNum = 0;
	int temp = m_printDamageNum;
	while (true)
	{
		printNum++;
		temp /= 10;
		if (temp == 0)
			break;
	}
	UpdateRect_GameObject();

	return 0;
}

int CDamageSkin::Update_GameObject()
{
	if (m_isDead)
		return OBJ_DEAD;
	if (m_disappearTime + m_disappearSpeed < GetTickCount())
		Set_IsDead();
	return 0;
}

void CDamageSkin::Late_Update_GameObject()
{
}

void CDamageSkin::Render_GameObject(HDC hDC)
{
	UpdateRect_GameObject();

	int scrollX = CScroll_Manager::Get_ScrollX();
	int scrollY = CScroll_Manager::Get_ScrollY();

	int temp2 = m_printDamageNum;
	for(int i=0; i< printNum; i++)
	{
		int temp = temp2 % 10;
		temp2 /= 10;
		GdiTransparentBlt(hDC, // 그림을 복사하고자 하는 대상. 
			(m_rect.left + scrollX) + m_info.sizeX*(printNum/2 - i),//위치 x,y
			m_rect.top + scrollY,
			m_info.sizeX,// 크기 xy
			m_info.sizeY,
			m_hdc,// 복사 할 대상
			temp * m_info.sizeX,0,// 그림의 시작 위치 x,y
			m_info.sizeX,// 그리고자 하는 영역의 크기 x,y
			m_info.sizeY,
			RGB(255, 0, 255));
	}

}

void CDamageSkin::Release_GameObject()
{
}

void CDamageSkin::UpdateRect_GameObject()
{
	m_rect.left = static_cast<LONG>(m_info.x - (m_info.sizeX / 2));
	m_rect.top = static_cast<LONG>(m_info.y - (m_info.sizeY / 2));
	m_rect.right = static_cast<LONG>(m_info.x + (m_info.sizeX / 2));
	m_rect.bottom = static_cast<LONG>(m_info.y + (m_info.sizeY / 2));
}

CGameObject * CDamageSkin::Create(int damage)
{
	CGameObject * instance = new CDamageSkin;
	dynamic_cast<CDamageSkin*>(instance)->Set_PrintDamageNum(damage);
	if (0 > instance->Ready_GameObject())
	{
		Safe_Delete(instance);
		instance = nullptr;
	}

	return instance;
}
