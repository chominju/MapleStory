#include "stdafx.h"
#include "Tool_Line.h"
#include "Tool_Scroll_Manager.h"

CLine::CLine()
{
}


CLine::~CLine()
{
}

void CLine::Render_Line(HDC hDC)
{
	float fScrollX = CScroll_Manager::Get_ScrollX();
	float fScrollY = CScroll_Manager::Get_ScrollY();
	MoveToEx(hDC, m_lineInfo.left_pos.x + fScrollX, m_lineInfo.left_pos.y + fScrollY, nullptr);
	LineTo(hDC, m_lineInfo.right_pos.x + fScrollX, m_lineInfo.right_pos.y + fScrollY);
}

CLine * CLine::Create(Line_Info* pLineInfo /*= nullptr*/)
{
	CLine* pInstance = new CLine;
	if (nullptr != pLineInfo)
		pInstance->Set_LineInfo(*pLineInfo);

	return pInstance;
}

