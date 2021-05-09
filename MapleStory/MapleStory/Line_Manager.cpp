#include "stdafx.h"
#include "Line_Manager.h"
#include "Line.h"

CLine_Manager* CLine_Manager::m_pInstance = nullptr;

CLine_Manager::CLine_Manager()
{
}


CLine_Manager::~CLine_Manager()
{
	Release_Line_Manager();
}

bool CLine_Manager::Collision_Line_Manager(float finX, float * pOutY)
{
	CLine* pTarget = nullptr;

	for (auto& pLine : m_listLine)
	{
		if (pLine->Get_LineInfo()->left_pos.x < finX &&pLine->Get_LineInfo()->right_pos.x > finX)
			pTarget = pLine;
	}
	if (nullptr == pTarget)
		return false;

	// 여기에서부터 직선의 방정식을 사용할 것. 
	// y = (y2 - y1) / (x2- x1) * (fInx - x1) + y1; 
	float fx1 = pTarget->Get_LineInfo()->left_pos.x;
	float fy1 = pTarget->Get_LineInfo()->left_pos.y;
	float fx2 = pTarget->Get_LineInfo()->right_pos.x;
	float fy2 = pTarget->Get_LineInfo()->right_pos.y;

	*pOutY = (fy2 - fy1) / (fx2 - fx1) * (finX - fx1) + fy1;

	return true;
}

void CLine_Manager::Insert_Line_Manager(Pos left, Pos right)
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
