#include "stdafx.h"
#include "Monster.h"

CMonster::CMonster()
{
	ZeroMemory(&m_monster_info, sizeof(Monster_Info));
}

CMonster::~CMonster()
{
}

int CMonster::Ready_GameObject()
{
	return 0;
}

int CMonster::Update_GameObject()
{
	return 0;
}

void CMonster::Late_Update_GameObject()
{
}

void CMonster::Render_GameObject(HDC hDC)
{
}

void CMonster::Release_GameObject()
{
}
