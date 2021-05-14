#include "stdafx.h"
#include "Field1.h"
#include "Player.h"
#include "Line_Manager.h"
#include "Bitmap_Manager.h"
#include "Scroll_Manager.h"
#include "LoadData.h"
#include "GameObject_Manager.h"
#include "Portal.h"
#include "Rope.h"

CField1::CField1()
{
}


CField1::~CField1()
{
}

int CField1::Ready_Scene()
{
	m_hdc = CBitmap_Manager::Get_Instance()->Get_memDC(L"Field1");
	m_SceneSize = CBitmap_Manager::Get_Instance()->Get_Image_Size(L"Field1");
	CLine_Manager::Get_Instance()->Release_Line_Manager();
	CLoadData::Get_Instance()->Load_Line(L"../ResourceList/Field1_lineList.dat");

	CGameObject_Manager::Get_Instance()->Release_Specific_GameObject_Manager(Object_ID::PORTAL);
	CGameObject* portal = CPortal::Create();
	portal->SetPos(100, 380);
	dynamic_cast<CPortal*>(portal)->Set_NextSceneID(SCENE_Kerning_City);
	CGameObject_Manager::Get_Instance()->Add_GameObject_Manager(Object_ID::PORTAL, portal);
	CGameObject_Manager::Get_Instance()->DeleteID(Object_ID::ROPE);

	Create_Rope_Scene();

	if(CGameObject_Manager::Get_Instance()->GetPlayer()->Get_isPortal())
		CGameObject_Manager::Get_Instance()->GetPlayer()->SetPos(100, 380);
	else
		CGameObject_Manager::Get_Instance()->GetPlayer()->SetPos(100, 100);

	CScroll_Manager::Set_ResetX();
	CScroll_Manager::Set_ResetY();

	return 0;
}

void CField1::Update_Scene()
{
	CGameObject_Manager::Get_Instance()->Update_GameObject_Manager();
	CGameObject_Manager::Get_Instance()->Late_Update_GameObject_Manager();
}

void CField1::Render_Scene(HDC hdc)
{
	if (nullptr == m_hdc)
		return;
	int scrollX = CScroll_Manager::Get_ScrollX();
	int scrollY = CScroll_Manager::Get_ScrollY();

	BitBlt(hdc, 0, 0, WINCX, WINCY, m_hdc, -scrollX, m_SceneSize.y - WINCY - scrollY, SRCCOPY);

	CLine_Manager::Get_Instance()->Render_Line_Manager(hdc);
	CGameObject_Manager::Get_Instance()->Render_GameObject_Manager(hdc);

}

void CField1::Release_Scene()
{
}

void CField1::Create_Rope_Scene()
{
	CGameObject*rope = CRope::Create();
	rope->SetPos(906, 1225);
	rope->SetSize(10, 80);
	CGameObject_Manager::Get_Instance()->Add_GameObject_Manager(Object_ID::ROPE, rope);

	rope = CRope::Create();
	rope->SetPos(1747, 1225);
	rope->SetSize(10, 80);
	CGameObject_Manager::Get_Instance()->Add_GameObject_Manager(Object_ID::ROPE, rope);

	rope = CRope::Create();
	rope->SetPos(2125, 1010);
	rope->SetSize(50, 140);
	CGameObject_Manager::Get_Instance()->Add_GameObject_Manager(Object_ID::ROPE, rope);

	rope = CRope::Create();
	rope->SetPos(1190, 175);
	rope->SetSize(10, 110);
	CGameObject_Manager::Get_Instance()->Add_GameObject_Manager(Object_ID::ROPE, rope);

}

CScene * CField1::Create()
{
	CScene* instacne = new CField1;
	if (0 > instacne->Ready_Scene())
	{
		Safe_Delete(instacne);
		return nullptr;
	}
	return instacne;
}
