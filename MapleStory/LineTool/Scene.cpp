#include "stdafx.h"
#include "Scene.h"
#include "Tool_Bitmap_Manager.h"

CScene::CScene()
{
}


CScene::~CScene()
{
}

void CScene::Set_Hdc(TCHAR * keyName)
{
	m_hdc = CBitmap_Manager::Get_Instance()->Get_memDC(keyName);
}

void CScene::Set_StartPos(TCHAR * keyName)
{
	m_startPos = CBitmap_Manager::Get_Instance()->Get_Image_Size(keyName);
}

