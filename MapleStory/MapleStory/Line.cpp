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

	HPEN hpen;
	HPEN hpenOld;
	HBRUSH hbr;
	HBRUSH hbrOld;
	hbr = CreateSolidBrush(RGB(0, 255, 0));
	hbrOld = (HBRUSH)::SelectObject(hDC, hbr);
	hpen = CreatePen(PS_SOLID, 2, RGB(255, 255, 0));
	hpenOld = (HPEN)::SelectObject(hDC, (HGDIOBJ)hpen);

	MoveToEx(hDC, m_line_info.left_pos.x + scrollX, m_line_info.left_pos.y+ scrollY, nullptr);
	LineTo(hDC, m_line_info.right_pos.x + scrollX, m_line_info.right_pos.y+ scrollY);
	
	hbr = (HBRUSH)::SelectObject(hDC, hbrOld);
	DeleteObject(hbr); // 생성한 브러쉬 삭제
	hpen = (HPEN)::SelectObject(hDC, hpenOld);
	DeleteObject(hpen); // 생성한 펜 삭제
}

CLine * CLine::Create(Line_Info* pLineInfo /*= nullptr*/)
{
	CLine* pInstance = new CLine;
	if (nullptr != pLineInfo)
		pInstance->Set_LineInfo(*pLineInfo);

	return pInstance;
}
