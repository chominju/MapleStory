#include "stdafx.h"
#include "Line_Manager.h"
#include "Line.h"
#include "Player.h"
#include <vector>
#include "Key_Manager.h"

CLine_Manager* CLine_Manager::m_pInstance = nullptr;

CLine_Manager::CLine_Manager()
{
}


CLine_Manager::~CLine_Manager()
{
	Release_Line_Manager();
}

bool CLine_Manager::Collision_Line_Manager(CGameObject*object,float * pOutY)
{
	float min=10000;
	bool check=false;
	for (auto& pLine : m_listLine)
	{
		if (pLine->Get_LineInfo()->left_pos.x <= object->Get_Info()->x && pLine->Get_LineInfo()->right_pos.x >= object->Get_Info()->x)
		{
			float fx1 = pLine->Get_LineInfo()->left_pos.x;
			float fy1 = pLine->Get_LineInfo()->left_pos.y;
			float fx2 = pLine->Get_LineInfo()->right_pos.x;
			float fy2 = pLine->Get_LineInfo()->right_pos.y;
			float y = (fy2 - fy1) / (fx2 - fx1) * (object->Get_Info()->x - fx1) + fy1;

			float dis = y - object->Get_Info()->y;
			if (dis < min && dis>= object->Get_Info()->sizeY/2-10)
			{
				min = dis;
				*pOutY = y;
				check = true;
			}
		}
	}

	return check;
}

bool CLine_Manager::Floor_Collision_Line_Manager_Line_Manager(CPlayer * player)
{
	float min = 10000;
	for (auto& pLine : m_listLine)
	{
		if (pLine->Get_LineInfo()->left_pos.x <= player->Get_Info()->x && pLine->Get_LineInfo()->right_pos.x >= player->Get_Info()->x)
		{
			float fx1 = pLine->Get_LineInfo()->left_pos.x;
			float fy1 = pLine->Get_LineInfo()->left_pos.y;
			float fx2 = pLine->Get_LineInfo()->right_pos.x;
			float fy2 = pLine->Get_LineInfo()->right_pos.y;
			float y = (fy2 - fy1) / (fx2 - fx1) * (player->Get_Info()->x - fx1) + fy1;

			if (player->GetRect()->bottom + 5 <= y)
				return true;
		}
	}
	return false;
}

void CLine_Manager::Insert_Line_Manager(Pos_float left, Pos_float right)
{
	CLine* line = CLine::Create();
	line->Set_LineInfo({ { left.x , left.y }, { right.x , right.y } });
	m_listLine.push_back(line);
}

void CLine_Manager::Render_Line_Manager(HDC hDC)
{
	if(CKey_Manager::Get_Instance()->Key_Down(KEY_F5))
	{
		if (m_isLinePrint)
			m_isLinePrint = false;
		else
			m_isLinePrint = true;
	}
	if (m_isLinePrint)
	{
		for (auto& pLine : m_listLine)
		{
			pLine->Render_Line(hDC);
		}
	}
}

void CLine_Manager::Release_Line_Manager()
{
	for (auto& pLine : m_listLine)
	{
		Safe_Delete(pLine);
	}
	m_listLine.clear();
}
