#include "stdafx.h"
#include "MyMenu.h"
#include "MyButton.h"
#include "Tool_Bitmap_Manager.h"
#include "Tool_GameObject_Manager.h"

CMyMenu::CMyMenu()
{
}


CMyMenu::~CMyMenu()
{
	Release_Scene(); 
}

int CMyMenu::Ready_Scene()
{
	CGameObject* pObject = CMyButton::Create(); 
	pObject->Set_Pos(150.f, 150.f); 
	dynamic_cast<CMyButton*>(pObject)->Set_FrameKey(L"Tool_Button1"); 
	CGameObject_Manager::Get_Instance()->Add_GameObject_Manager(Object_ID::UI, pObject); 

	pObject = CMyButton::Create();
	pObject->Set_Pos(400.f, 150.f);
	dynamic_cast<CMyButton*>(pObject)->Set_FrameKey(L"Tool_Button2");
	CGameObject_Manager::Get_Instance()->Add_GameObject_Manager(Object_ID::UI, pObject);

	pObject = CMyButton::Create();
	pObject->Set_Pos(650.f, 150.f);
	dynamic_cast<CMyButton*>(pObject)->Set_FrameKey(L"Tool_Button3");
	CGameObject_Manager::Get_Instance()->Add_GameObject_Manager(Object_ID::UI, pObject);
	return 0;
}

void CMyMenu::Update_Scene()
{
	CGameObject_Manager::Get_Instance()->Update_GameObject_Manager(); 
	CGameObject_Manager::Get_Instance()->Late_Update_GameObject_Manager(); 
}

void CMyMenu::Render_Scene(HDC hDC)
{
	HDC hMemDC = CBitmap_Manager::Get_Instance()->Get_memDC(L"Menu"); 
	if (nullptr == hMemDC)
		return; 
	BitBlt(hDC, 0, 0, WINCX, WINCY, hMemDC, 0, 0, SRCCOPY); 

	CGameObject_Manager::Get_Instance()->Render_GameObject_Manager(hDC); 

}

void CMyMenu::Release_Scene()
{
	CGameObject_Manager::Get_Instance()->DeleteID(Object_ID::UI);
}

CScene * CMyMenu::Create()
{
	CScene* pInstance = new CMyMenu;
	if (0 > pInstance->Ready_Scene())
	{
		Safe_Delete(pInstance);
		return nullptr;
	}
	return pInstance;
}
