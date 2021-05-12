#include "stdafx.h"
#include "Map1.h"
#include "Player.h"
#include "Line_Manager.h"
#include "Bitmap_Manager.h"
#include "Scroll_Manager.h"
#include "GameObject_Manager.h"


CMap1::CMap1()
{
}


CMap1::~CMap1()
{
}

int CMap1::Ready_Scene()
{
	m_hdc = CBitmap_Manager::Get_Instance()->Get_memDC(L"Map1");
	m_SceneSize = CBitmap_Manager::Get_Instance()->Get_Image_Size(L"Map1");
	CScroll_Manager::Set_ResetX();
	CScroll_Manager::Set_ResetY();

	return 0;
}

void CMap1::Update_Scene()
{
	CGameObject_Manager::Get_Instance()->Update_GameObject_Manager();
	CGameObject_Manager::Get_Instance()->Late_Update_GameObject_Manager();
}

void CMap1::Render_Scene(HDC hdc)
{
	if (nullptr == m_hdc)
		return;
	int scrollX = CScroll_Manager::Get_ScrollX();
	int scrollY = CScroll_Manager::Get_ScrollY();
	if (scrollX >= 0)
		scrollX = 0;

	BitBlt(hdc, 0, 0, WINCX, WINCY, m_hdc, -scrollX, m_SceneSize.y + scrollY, SRCCOPY);

	CLine_Manager::Get_Instance()->Render_Line_Manager(hdc);
	CGameObject_Manager::Get_Instance()->Render_GameObject_Manager(hdc);

}

void CMap1::Release_Scene()
{
}

CScene * CMap1::Create()
{
	CScene* instacne = new CMap1;
	if (0 > instacne->Ready_Scene())
	{
		Safe_Delete(instacne);
		return nullptr;
	}
	return instacne;
}
