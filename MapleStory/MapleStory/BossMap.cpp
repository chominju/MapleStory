#include "stdafx.h"
#include "BossMap.h"
#include "Player.h"
#include "Line_Manager.h";
#include "Bitmap_Manager.h"
#include "Scroll_Manager.h"
#include "GameObject_Manager.h"
#include "LoadData.h"
#include "Portal.h"
#include "Player_Ui.h"
#include "Player_StatUi.h"
#include "Inventory_Ui.h"
#include "Boss.h"
#include "Clock.h"
CBossMap::CBossMap()
{
}

CBossMap::~CBossMap()
{
	CGameObject_Manager::Get_Instance()->DeleteID(Object_ID::PORTAL);
	CGameObject_Manager::Get_Instance()->DeleteID(Object_ID::ROPE);
	CGameObject_Manager::Get_Instance()->DeleteID(Object_ID::MONSTER);
	CGameObject_Manager::Get_Instance()->DeleteID(Object_ID::DROP_ITEM);
	CGameObject_Manager::Get_Instance()->DeleteID(Object_ID::BOSS);
	CGameObject_Manager::Get_Instance()->DeleteID(Object_ID::BOSS_SKILL);
	CSoundMgr::Get_Instance()->StopAll();
}

int CBossMap::Ready_Scene()
{
	m_hdc = CBitmap_Manager::Get_Instance()->Get_memDC(L"BossMap");
	m_SceneSize = CBitmap_Manager::Get_Instance()->Get_Image_Size(L"BossMap");
	CLine_Manager::Get_Instance()->Release_Line_Manager();
	CLoadData::Get_Instance()->Load_Line(L"../ResourceList/BossMap_lineList.dat");

	CGameObject* portal = CPortal::Create();
	portal->Set_Pos(50, 550);
	dynamic_cast<CPortal*>(portal)->Set_NextSceneID(SCENE_Kerning_City);
	CGameObject_Manager::Get_Instance()->Add_GameObject_Manager(Object_ID::PORTAL, portal);

	if (CGameObject_Manager::Get_Instance()->GetPlayer()->Get_isPortal())
		CGameObject_Manager::Get_Instance()->GetPlayer()->Set_Pos(100, 500);

	boss = CBoss::Create();
	CGameObject_Manager::Get_Instance()->Add_GameObject_Manager(Object_ID::BOSS, boss);

	CScroll_Manager::Set_ResetX();
	CScroll_Manager::Set_ResetY();

	m_createClockTime = GetTickCount();
	m_createClockSpeed = 300;

	CSoundMgr::Get_Instance()->StopAll();
	CSoundMgr::Get_Instance()->PlayBGM(L"TimeChaos.mp3");

	return 0;
}

void CBossMap::Update_Scene()
{
	if (boss->Get_Hp() / boss->Get_MaxHp() <= 0.3f)
	{
		if (m_createClockTime + m_createClockSpeed < GetTickCount())
		{
			CClock::Create();
			m_createClockTime = GetTickCount();
		}

	}
	CGameObject_Manager::Get_Instance()->Update_GameObject_Manager();
	CGameObject_Manager::Get_Instance()->Late_Update_GameObject_Manager();
}

void CBossMap::Render_Scene(HDC hdc)
{
	if (nullptr == m_hdc)
		return;
	int scrollX = CScroll_Manager::Get_ScrollX();
	int scrollY = CScroll_Manager::Get_ScrollY();

	BitBlt(hdc, 0, 0, WINCX, WINCY, m_hdc, -scrollX, (m_SceneSize.y - WINCY) - scrollY, SRCCOPY);

	CLine_Manager::Get_Instance()->Render_Line_Manager(hdc);
	CGameObject_Manager::Get_Instance()->Render_GameObject_Manager(hdc);
}

void CBossMap::Release_Scene()
{
}

void CBossMap::Create_Rope_Scene()
{
}

CScene * CBossMap::Create()
{
	CScene* instance = new CBossMap;
	if (0 > instance->Ready_Scene())
	{
		Safe_Delete(instance);
		return nullptr;
	}
	return instance;
}
