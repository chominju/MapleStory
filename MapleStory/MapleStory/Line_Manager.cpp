#include "stdafx.h"
#include "Line_Manager.h"
#include "Line.h"
#include "Player.h"
#include <vector>

CLine_Manager* CLine_Manager::m_pInstance = nullptr;

CLine_Manager::CLine_Manager()
{
}


CLine_Manager::~CLine_Manager()
{
	Release_Line_Manager();
}

bool CLine_Manager::Collision_Line_Manager(CPlayer*player, float finX, float finY, float * pOutY, CurrentKey currentKey)
{
	float min=10000;
	for (auto& pLine : m_listLine)
	{
		if (pLine->Get_LineInfo()->left_pos.x <= finX && pLine->Get_LineInfo()->right_pos.x >= finX)
		{
			float fx1 = pLine->Get_LineInfo()->left_pos.x;
			float fy1 = pLine->Get_LineInfo()->left_pos.y;
			float fx2 = pLine->Get_LineInfo()->right_pos.x;
			float fy2 = pLine->Get_LineInfo()->right_pos.y;
			float y = (fy2 - fy1) / (fx2 - fx1) * (finX - fx1) + fy1;

			float dis = y - player->GetInfo()->y;// -player->GetInfo().sizeY;
			//float dis = y - *(player->GetInfo()).y;// -player->GetInfo().sizeY;
			if (dis < min && dis>= player->GetInfo()->sizeY/2-10)
			{
				min = dis;
				*pOutY = y;
			}
		}
	}







	//vector< CLine*> vecLine;
	//CLine* pTarget = nullptr;
	//float dis = 9999;
	//float temp2;
	//float y;
	//for (auto& pLine : m_listLine)
	//{
	//	if (pLine->Get_LineInfo()->left_pos.x <= finX &&pLine->Get_LineInfo()->right_pos.x >= finX)
	//	{
	//		float fx1 = pLine->Get_LineInfo()->left_pos.x;
	//		float fy1 = pLine->Get_LineInfo()->left_pos.y;
	//		float fx2 = pLine->Get_LineInfo()->right_pos.x;
	//		float fy2 = pLine->Get_LineInfo()->right_pos.y;
	//		y = (fy2 - fy1) / (fx2 - fx1) * (finX - fx1) + fy1;
	//		temp2 = abs(y - finX);
	//		if (temp2 <= dis)
	//		{
	//			if (y >= finX)
	//			{
	//			dis = temp2;
	//			*pOutY = y;

	//			}
	//			
	//		}
	//			//pTarget = pLine;
	//			//vecLine.push_back(pLine);
	//	}
	//}
	/*if (vecLine.empty())
		return false;

	if (vecLine.size() == 1)
	{
		float fx1 = vecLine[0]->Get_LineInfo()->left_pos.x;
		float fy1 = vecLine[0]->Get_LineInfo()->left_pos.y;
		float fx2 = vecLine[0]->Get_LineInfo()->right_pos.x;
		float fy2 = vecLine[0]->Get_LineInfo()->right_pos.y;
		float y = (fy2 - fy1) / (fx2 - fx1) * (finX - fx1) + fy1;

		*pOutY = (fy2 - fy1) / (fx2 - fx1) * (finX - fx1) + fy1;

	}
	else
	{
		float dif = 99999;

		for (int i = 0; i < vecLine.size(); i++)
		{
			float fx1 = vecLine[i]->Get_LineInfo()->left_pos.x;
			float fy1 = vecLine[i]->Get_LineInfo()->left_pos.y;
			float fx2 = vecLine[i]->Get_LineInfo()->right_pos.x;
			float fy2 = vecLine[i]->Get_LineInfo()->right_pos.y;
			float y = (fy2 - fy1) / (fx2 - fx1) * (finX - fx1) + fy1;

			if (currentKey == CurrentKey::LEFT)
			{
				float temp = y - finY + 1;
				if (abs(temp) <= dif)
				{
					dif = abs(temp);
					*pOutY = (fy2 - fy1) / (fx2 - fx1) * (finX - fx1) + fy1;
				}

			}
			else if (currentKey == CurrentKey::RIGHT)
			{
				float temp = y - finY + 1;

					if (abs(temp) <= dif)
					{
						dif = abs(temp);
						*pOutY = (fy2 - fy1) / (fx2 - fx1) * (finX - fx1) + fy1;
					}

			}
		}
	}*/

	//// 여기에서부터 직선의 방정식을 사용할 것. 
	//// y = (y2 - y1) / (x2- x1) * (fInx - x1) + y1; 
	//float fx1 = pTarget->Get_LineInfo()->left_pos.x;
	//float fy1 = pTarget->Get_LineInfo()->left_pos.y;
	//float fx2 = pTarget->Get_LineInfo()->right_pos.x;
	//float fy2 = pTarget->Get_LineInfo()->right_pos.y;

	//*pOutY = (fy2 - fy1) / (fx2 - fx1) * (finX - fx1) + fy1;

	return true;
}

bool CLine_Manager::Floor_Collision_Line_Manager_Line_Manager(CPlayer * player)
{
	float min = 10000;
	for (auto& pLine : m_listLine)
	{
		if (pLine->Get_LineInfo()->left_pos.x <= player->GetInfo()->x && pLine->Get_LineInfo()->right_pos.x >= player->GetInfo()->x)
		{
			float fx1 = pLine->Get_LineInfo()->left_pos.x;
			float fy1 = pLine->Get_LineInfo()->left_pos.y;
			float fx2 = pLine->Get_LineInfo()->right_pos.x;
			float fy2 = pLine->Get_LineInfo()->right_pos.y;
			float y = (fy2 - fy1) / (fx2 - fx1) * (player->GetInfo()->x - fx1) + fy1;

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

void CLine_Manager::Ready_Line_Manager()
{
	/*CLine* pLine = CLine::Create();
	pLine->Set_LineInfo({ {50.f, 150.f},{150.f, 500.f} });
	m_listLine.emplace_back(pLine);

	pLine = CLine::Create();
	pLine->Set_LineInfo({ { 150.f, 500.f },{ 300.f, 500.f } });
	m_listLine.emplace_back(pLine);

	pLine = CLine::Create();
	pLine->Set_LineInfo({ { 300.f, 500.f },{ 500.f, 150.f } });
	m_listLine.emplace_back(pLine);

	pLine = CLine::Create();
	pLine->Set_LineInfo({ { 500.f, 150.f },{ 800.f, 150.f} });
	m_listLine.emplace_back(pLine);*/
}

void CLine_Manager::Render_Line_Manager(HDC hDC)
{
	for (auto& pLine : m_listLine)
	{
		pLine->Render_Line(hDC);
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
