#include "stdafx.h"
#include "Line.h"
#include "Scroll_Manager.h"

CLine::CLine()
{
}


CLine::~CLine()
{
}

void CLine::Render_Line(HDC hDC)
{
	int scrollX = CScroll_Manager::Get_ScrollX();
	int scrollY = CScroll_Manager::Get_ScrollY();
	MoveToEx(hDC, m_line_info.left_pos.x + scrollX, m_line_info.left_pos.y+ scrollY, nullptr);
	LineTo(hDC, m_line_info.right_pos.x + scrollX, m_line_info.right_pos.y+ scrollY);
}

CLine * CLine::Create(Line_Info* pLineInfo /*= nullptr*/)
{
	CLine* pInstance = new CLine;
	if (nullptr != pLineInfo)
		pInstance->Set_LineInfo(*pLineInfo);

	return pInstance;
}
