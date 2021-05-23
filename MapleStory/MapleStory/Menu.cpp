#include "stdafx.h"
#include "Menu.h"
#include "Bitmap_Manager.h"
#include "Key_Manager.h"
#include "Scene_Manager.h"
#include "GameObject_Manager.h"
#include "SoundMgr.h"

CMenu::CMenu()
{
}

CMenu::~CMenu()
{
	Release_Scene();
}

int CMenu::Ready_Scene()
{
	CSoundMgr::Get_Instance()->PlayBGM(L"Menu.mp3");
	return 0;
}

void CMenu::Update_Scene()
{
	if (CKey_Manager::Get_Instance()->Key_Up(KEY_RETURN))
		CScene_Manager::Get_Instance()->Change_Scene_Manager(Scene_ID::SCENE_Kerning_City);
	CGameObject_Manager::Get_Instance()->Update_GameObject_Manager();
	CGameObject_Manager::Get_Instance()->Late_Update_GameObject_Manager();
}

void CMenu::Render_Scene(HDC hdc)
{
	HDC hMemDC = CBitmap_Manager::Get_Instance()->Get_memDC(L"Menu");
	if (nullptr == hMemDC)
		return;
	BitBlt(hdc, 0, 0, WINCX, WINCY, hMemDC, 0, 0, SRCCOPY);
}

void CMenu::Release_Scene()
{
}

void CMenu::Create_Rope_Scene()
{
}

CScene * CMenu::Create()
{
	CScene* pInstance = new CMenu;
	if (0 > pInstance->Ready_Scene())
	{
		Safe_Delete(pInstance);
		return nullptr;
	}
	return pInstance;
}
