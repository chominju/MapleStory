#include "stdafx.h"
#include "Kerning_City.h"
#include "Bitmap_Manager.h"
#include "Scroll_Manager.h"

Kerning_City::Kerning_City()
{
}


Kerning_City::~Kerning_City()
{
}

int Kerning_City::Ready_Scene()
{
	m_hdc = CBitmap_Manager::Get_Instance()->Get_memDC(L"Kerning_City");
	m_SceneSize = CBitmap_Manager::Get_Instance()->Get_Image_Size(L"Kerning_City");
	return S_OK;
}

void Kerning_City::Update_Scene()
{
}

void Kerning_City::Render_Scene(HDC hdc)
{
	if (nullptr == m_hdc)
		return;
	int scrollX = CScroll_Manager::Get_ScrollX();
	int scrollY = CScroll_Manager::Get_ScrollY();
	if (scrollX >= 0)
		scrollX = 0;
	BitBlt(hdc, 0, 0, WINCX, WINCY, m_hdc, -scrollX, m_SceneSize.y-WINCY + scrollY, SRCCOPY);
	//CGameObject_Manager::Get_Instance()->Render_GameObject_Manager(hDC);
}

void Kerning_City::Release_Scene()
{
}

CScene * Kerning_City::Create()
{
	CScene* instance = new Kerning_City;
	if (0 > instance->Ready_Scene())
	{
		Safe_Delete(instance);
		return nullptr;
	}
	return instance;
}
