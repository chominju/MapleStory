#include "stdafx.h"
#include "Kerning_City.h"
#include "Player.h"
#include "Line_Manager.h";
#include "Bitmap_Manager.h"
#include "Scroll_Manager.h"
#include "GameObject_Manager.h"
#include "LoadData.h"
#include "Portal.h"
#include "Rope.h"

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
	CLine_Manager::Get_Instance()->Release_Line_Manager();
	CLoadData::Get_Instance()->Load_Line(L"../ResourceList/Kerning_City_lineList.dat");

	CGameObject_Manager::Get_Instance()->Release_Specific_GameObject_Manager(Object_ID::PORTAL);
	CGameObject* portal = CPortal::Create();
	portal->Set_Pos(300, 200);
	dynamic_cast<CPortal*>(portal)->Set_NextSceneID(SCENE_BOSS);
	CGameObject_Manager::Get_Instance()->Add_GameObject_Manager(Object_ID::PORTAL, portal);

	CGameObject*portal2 = CPortal::Create();
	//portal2->SetPos(3780, 375);
	portal2->Set_Pos(100, 380);
	dynamic_cast<CPortal*>(portal2)->Set_NextSceneID(SCENE_MAP1);
	CGameObject_Manager::Get_Instance()->Add_GameObject_Manager(Object_ID::PORTAL, portal2);
	CGameObject_Manager::Get_Instance()->DeleteID(Object_ID::ROPE);
	Create_Rope_Scene();

	if (CGameObject_Manager::Get_Instance()->GetPlayer()->Get_isPortal())
		CGameObject_Manager::Get_Instance()->GetPlayer()->Set_Pos(100, 380);
	else
		CGameObject_Manager::Get_Instance()->GetPlayer()->Set_Pos(100, 100);


	CScroll_Manager::Set_ResetX();
	CScroll_Manager::Set_ResetY();

	return S_OK;
}

void Kerning_City::Update_Scene()
{
	CGameObject_Manager::Get_Instance()->Update_GameObject_Manager();
	CGameObject_Manager::Get_Instance()->Late_Update_GameObject_Manager();
}

void Kerning_City::Render_Scene(HDC hdc)
{
	if (nullptr == m_hdc)
		return;
	int scrollX = CScroll_Manager::Get_ScrollX();
	int scrollY = CScroll_Manager::Get_ScrollY();

	BitBlt(hdc, 0, 0, WINCX, WINCY, m_hdc, -scrollX, (m_SceneSize.y-WINCY) -scrollY, SRCCOPY);

	CLine_Manager::Get_Instance()->Render_Line_Manager(hdc);
	CGameObject_Manager::Get_Instance()->Render_GameObject_Manager(hdc);
}

void Kerning_City::Release_Scene()
{
}

void Kerning_City::Create_Rope_Scene()
{
	CGameObject*rope = CRope::Create();
	rope->Set_Pos(495, 495);
	rope->Set_Size(5, 580);
	CGameObject_Manager::Get_Instance()->Add_GameObject_Manager(Object_ID::ROPE, rope);

	rope = CRope::Create();
	rope->Set_Pos(1215, 740);
	rope->Set_Size(50, 200);
	CGameObject_Manager::Get_Instance()->Add_GameObject_Manager(Object_ID::ROPE, rope);

	rope = CRope::Create();
	rope->Set_Pos(1318, 882);
	rope->Set_Size(50, 200);
	CGameObject_Manager::Get_Instance()->Add_GameObject_Manager(Object_ID::ROPE, rope);

	rope = CRope::Create();
	rope->Set_Pos(1505, 1175);
	CGameObject_Manager::Get_Instance()->Add_GameObject_Manager(Object_ID::ROPE, rope);

	rope = CRope::Create();
	rope->Set_Pos(1932, 980);
	rope->Set_Size(40, 90);
	CGameObject_Manager::Get_Instance()->Add_GameObject_Manager(Object_ID::ROPE, rope);

	rope = CRope::Create();
	rope->Set_Pos(2408, 1175);
	CGameObject_Manager::Get_Instance()->Add_GameObject_Manager(Object_ID::ROPE, rope);

	rope = CRope::Create();
	rope->Set_Pos(3148, 1015);
	rope->Set_Size(40, 80);
	CGameObject_Manager::Get_Instance()->Add_GameObject_Manager(Object_ID::ROPE, rope);
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
