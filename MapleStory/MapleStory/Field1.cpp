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
#include "Mushroom.h"
#include "Octopus.h"

CField1::CField1()
{
}


CField1::~CField1()
{
	CGameObject_Manager::Get_Instance()->DeleteID(Object_ID::PORTAL);
	CGameObject_Manager::Get_Instance()->DeleteID(Object_ID::ROPE);
	CGameObject_Manager::Get_Instance()->DeleteID(Object_ID::MONSTER);
	CGameObject_Manager::Get_Instance()->DeleteID(Object_ID::DROP_ITEM);
}

int CField1::Ready_Scene()
{
	m_hdc = CBitmap_Manager::Get_Instance()->Get_memDC(L"Field1");
	m_SceneSize = CBitmap_Manager::Get_Instance()->Get_Image_Size(L"Field1");
	CLine_Manager::Get_Instance()->Release_Line_Manager();
	CLoadData::Get_Instance()->Load_Line(L"../ResourceList/Field1_lineList.dat");

	CGameObject* portal = CPortal::Create();
	portal->Set_Pos(100, 380);
	dynamic_cast<CPortal*>(portal)->Set_NextSceneID(SCENE_Kerning_City);
	CGameObject_Manager::Get_Instance()->Add_GameObject_Manager(Object_ID::PORTAL, portal);

	Create_Rope_Scene();

	if(CGameObject_Manager::Get_Instance()->GetPlayer()->Get_isPortal())
		CGameObject_Manager::Get_Instance()->GetPlayer()->Set_Pos(100, 380);
	else
		CGameObject_Manager::Get_Instance()->GetPlayer()->Set_Pos(100, 100);

	//CreateMonster();
	m_createMonsterTime=GetTickCount();
	m_createMonsterSpeed=20000;

	CScroll_Manager::Set_ResetX();
	CScroll_Manager::Set_ResetY();
	CreateMonster();

	return 0;
}

void CField1::Update_Scene()
{
	if (m_createMonsterTime + m_createMonsterSpeed < GetTickCount())
	{
		CreateMonster();
		m_createMonsterTime = GetTickCount();
	}
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
	rope->Set_Pos(906, 1220);
	rope->Set_Size(10, 80);
	CGameObject_Manager::Get_Instance()->Add_GameObject_Manager(Object_ID::ROPE, rope);

	rope = CRope::Create();
	rope->Set_Pos(1747, 1220);
	rope->Set_Size(10, 80);
	CGameObject_Manager::Get_Instance()->Add_GameObject_Manager(Object_ID::ROPE, rope);

	rope = CRope::Create();
	rope->Set_Pos(2125, 1010);
	rope->Set_Size(50, 140);
	CGameObject_Manager::Get_Instance()->Add_GameObject_Manager(Object_ID::ROPE, rope);

	rope = CRope::Create();
	rope->Set_Pos(1190, 172);
	rope->Set_Size(10, 110);
	CGameObject_Manager::Get_Instance()->Add_GameObject_Manager(Object_ID::ROPE, rope);

}

void CField1::CreateMonster()
{
	CGameObject * mushroom = CMushroom::Create();
	mushroom->Set_Pos(200, 400);
	CGameObject_Manager::Get_Instance()->Add_GameObject_Manager(Object_ID::MONSTER, mushroom);
	
	mushroom = CMushroom::Create();
	mushroom->Set_Pos(500, 530);
	CGameObject_Manager::Get_Instance()->Add_GameObject_Manager(Object_ID::MONSTER, mushroom);

	mushroom = CMushroom::Create();
	mushroom->Set_Pos(500, 530);
	CGameObject_Manager::Get_Instance()->Add_GameObject_Manager(Object_ID::MONSTER, mushroom);

	mushroom = CMushroom::Create();
	mushroom->Set_Pos(500, 200);
	CGameObject_Manager::Get_Instance()->Add_GameObject_Manager(Object_ID::MONSTER, mushroom);

	mushroom = CMushroom::Create();
	mushroom->Set_Pos(550, 200);
	CGameObject_Manager::Get_Instance()->Add_GameObject_Manager(Object_ID::MONSTER, mushroom);

	
	mushroom = CMushroom::Create();
	mushroom->Set_Pos(700, 530);
	CGameObject_Manager::Get_Instance()->Add_GameObject_Manager(Object_ID::MONSTER, mushroom);

	mushroom = CMushroom::Create();
	mushroom->Set_Pos(900, 530);
	CGameObject_Manager::Get_Instance()->Add_GameObject_Manager(Object_ID::MONSTER, mushroom);

	mushroom = CMushroom::Create();
	mushroom->Set_Pos(900, 380);
	CGameObject_Manager::Get_Instance()->Add_GameObject_Manager(Object_ID::MONSTER, mushroom);

	mushroom = CMushroom::Create();
	mushroom->Set_Pos(1000, 530);
	CGameObject_Manager::Get_Instance()->Add_GameObject_Manager(Object_ID::MONSTER, mushroom);

	mushroom = CMushroom::Create();
	mushroom->Set_Pos(1200, 380);
	CGameObject_Manager::Get_Instance()->Add_GameObject_Manager(Object_ID::MONSTER, mushroom);

	mushroom = CMushroom::Create();
	mushroom->Set_Pos(1200, 530);
	CGameObject_Manager::Get_Instance()->Add_GameObject_Manager(Object_ID::MONSTER, mushroom);

	mushroom = CMushroom::Create();
	mushroom->Set_Pos(1400, 530);
	CGameObject_Manager::Get_Instance()->Add_GameObject_Manager(Object_ID::MONSTER, mushroom);


	mushroom = CMushroom::Create();
	mushroom->Set_Pos(1700, 530);
	CGameObject_Manager::Get_Instance()->Add_GameObject_Manager(Object_ID::MONSTER, mushroom);

	mushroom = CMushroom::Create();
	mushroom->Set_Pos(1800, 530);
	CGameObject_Manager::Get_Instance()->Add_GameObject_Manager(Object_ID::MONSTER, mushroom);




	CGameObject* octopus = COctopus::Create();
	octopus->Set_Pos(900, 100);
	dynamic_cast<COctopus*>(octopus)->Set_DistanceX(800, 2000);
	CGameObject_Manager::Get_Instance()->Add_GameObject_Manager(Object_ID::MONSTER, octopus);

	octopus = COctopus::Create();
	octopus->Set_Pos(1000, 100);
	dynamic_cast<COctopus*>(octopus)->Set_DistanceX(800, 2000);
	CGameObject_Manager::Get_Instance()->Add_GameObject_Manager(Object_ID::MONSTER, octopus);

	octopus = COctopus::Create();
	octopus->Set_Pos(1200, 100);
	dynamic_cast<COctopus*>(octopus)->Set_DistanceX(800, 2000);
	CGameObject_Manager::Get_Instance()->Add_GameObject_Manager(Object_ID::MONSTER, octopus);

	octopus = COctopus::Create();
	octopus->Set_Pos(1500, 100);
	dynamic_cast<COctopus*>(octopus)->Set_DistanceX(800, 2000);
	CGameObject_Manager::Get_Instance()->Add_GameObject_Manager(Object_ID::MONSTER, octopus);

	octopus = COctopus::Create();
	octopus->Set_Pos(1600, 100);
	dynamic_cast<COctopus*>(octopus)->Set_DistanceX(800, 2000);
	CGameObject_Manager::Get_Instance()->Add_GameObject_Manager(Object_ID::MONSTER, octopus);

	octopus = COctopus::Create();
	octopus->Set_Pos(1900, 100);
	dynamic_cast<COctopus*>(octopus)->Set_DistanceX(800, 2000);
	CGameObject_Manager::Get_Instance()->Add_GameObject_Manager(Object_ID::MONSTER, octopus);

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
