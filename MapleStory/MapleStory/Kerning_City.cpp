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
#include "Player_Ui.h"
#include "Player_StatUi.h"
#include "Inventory_Ui.h"
#include "Scene_Manager.h"
#include "Npc.h"

Kerning_City::Kerning_City()
{
}


Kerning_City::~Kerning_City()
{
	CGameObject_Manager::Get_Instance()->DeleteID(Object_ID::PORTAL);
	CGameObject_Manager::Get_Instance()->DeleteID(Object_ID::ROPE);
	CGameObject_Manager::Get_Instance()->DeleteID(Object_ID::MONSTER);
	CGameObject_Manager::Get_Instance()->DeleteID(Object_ID::DROP_ITEM);
	CGameObject_Manager::Get_Instance()->DeleteID(Object_ID::NPC);
}

int Kerning_City::Ready_Scene()
{
	CPlayer::Create();
	CPlayer_Ui::Create();
	CPlayer_StatUi::Create();
	CInventory_Ui::Create();
	CNpc::Create();
	m_hdc = CBitmap_Manager::Get_Instance()->Get_memDC(L"Kerning_City");
	m_SceneSize = CBitmap_Manager::Get_Instance()->Get_Image_Size(L"Kerning_City");
	CLine_Manager::Get_Instance()->Release_Line_Manager();
	CLoadData::Get_Instance()->Load_Line(L"../ResourceList/Kerning_City_lineList.dat");

	CGameObject_Manager::Get_Instance()->DeleteID(Object_ID::PORTAL);
	CGameObject* portal = CPortal::Create();
	portal->Set_Pos(300, 200);
	dynamic_cast<CPortal*>(portal)->Set_NextSceneID(SCENE_BOSS);
	dynamic_cast<CPortal*>(portal)->Set_NextScenePos(50, 550);
	CGameObject_Manager::Get_Instance()->Add_GameObject_Manager(Object_ID::PORTAL, portal);

	CGameObject*portal2 = CPortal::Create();
	//portal2->SetPos(3780, 375);
	portal2->Set_Pos(100, 380);
	dynamic_cast<CPortal*>(portal2)->Set_NextSceneID(SCENE_MAP1);
	dynamic_cast<CPortal*>(portal2)->Set_NextScenePos(100, 380);
	CGameObject_Manager::Get_Instance()->Add_GameObject_Manager(Object_ID::PORTAL, portal2);

	CGameObject_Manager::Get_Instance()->DeleteID(Object_ID::ROPE);
	CGameObject_Manager::Get_Instance()->DeleteID(Object_ID::MONSTER);
	Create_Rope_Scene();


	if (!CGameObject_Manager::Get_Instance()->GetPlayer()->Get_isPortal())
		CGameObject_Manager::Get_Instance()->GetPlayer()->Set_Pos(100, 100);
	//else
	//	CGameObject_Manager::Get_Instance()->GetPlayer()->Set_Pos(100, 100);
	//dynamic_cast<CPlayer*>(CGameObject_Manager::Get_Instance()->GetPlayer())->Set_CheckKeepY(-593);

	CScroll_Manager::Set_ResetX();
	CScroll_Manager::Set_ResetY();

	CSoundMgr::Get_Instance()->PlayBGM(L"Kerning_City.mp3");

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
	rope->Set_Pos(2372, 218);
	rope->Set_Size(5, 160);
	CGameObject_Manager::Get_Instance()->Add_GameObject_Manager(Object_ID::ROPE, rope);

	rope = CRope::Create();
	rope->Set_Pos(2408, 1175);
	CGameObject_Manager::Get_Instance()->Add_GameObject_Manager(Object_ID::ROPE, rope);

	rope = CRope::Create();
	rope->Set_Pos(2490, 550);
	rope->Set_Size(30, 83);
	CGameObject_Manager::Get_Instance()->Add_GameObject_Manager(Object_ID::ROPE, rope);

	rope = CRope::Create();
	rope->Set_Pos(2892, 605);
	rope->Set_Size(40, 60);
	CGameObject_Manager::Get_Instance()->Add_GameObject_Manager(Object_ID::ROPE, rope);

	rope = CRope::Create();
	rope->Set_Pos(2930, 800);
	rope->Set_Size(40, 60);
	CGameObject_Manager::Get_Instance()->Add_GameObject_Manager(Object_ID::ROPE, rope);

	rope = CRope::Create();
	rope->Set_Pos(3148, 1017);
	rope->Set_Size(40, 83);
	CGameObject_Manager::Get_Instance()->Add_GameObject_Manager(Object_ID::ROPE, rope);

	rope = CRope::Create();
	rope->Set_Pos(3412, 832);
	rope->Set_Size(40, 63);
	CGameObject_Manager::Get_Instance()->Add_GameObject_Manager(Object_ID::ROPE, rope);

	rope = CRope::Create();
	rope->Set_Pos(3685 , 738);
	rope->Set_Size(40, 115);
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
