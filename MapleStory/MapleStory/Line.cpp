#include "stdafx.h"
#include "Line.h"

CLine::CLine()
{
}


CLine::~CLine()
{
}

void CLine::Render_Line(HDC hDC)
{
	//float fScrollX = CScroll_Manager::Get_ScrollX();
	//float fScrollY = CScroll_Manager::Get_ScrollY();
	MoveToEx(hDC, m_line_info.left_pos.x /*+ fScrollX*/, m_line_info.left_pos.y /*+ fScrollY*/, nullptr);
	LineTo(hDC, m_line_info.right_pos.x /*+ fScrollX*/, m_line_info.right_pos.y /*+ fScrollY*/);
}

CLine * CLine::Create(Line_Info* pLineInfo /*= nullptr*/)
{
	CLine* pInstance = new CLine;
	if (nullptr != pLineInfo)
		pInstance->Set_LineInfo(*pLineInfo);

	return pInstance;
}
