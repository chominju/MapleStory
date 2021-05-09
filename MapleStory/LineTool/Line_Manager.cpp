#include "stdafx.h"
#include "Line_Manager.h"
#include "Line.h"
#include "Scroll_Manager.h"
#include "Key_Manager.h"



CLine_Manager* CLine_Manager::m_instance = nullptr;

CLine_Manager::CLine_Manager()
{
}


CLine_Manager::~CLine_Manager()
{
	Release_Line_Manager();
}

bool CLine_Manager::Collision_Line_Manager(float finX, float * pOutY)
{
	CLine* target = nullptr;

	for (auto& pLine : m_listLine)
	{
		if (pLine->Get_LineInfo()->left_pos.x < finX &&pLine->Get_LineInfo()->right_pos.x > finX)
			target = pLine;
	}
	if (nullptr == target)
		return false;

	// 여기에서부터 직선의 방정식을 사용할 것. 
	// y = (y2 - y1) / (x2- x1) * (fInx - x1) + y1; 
	float x1 = target->Get_LineInfo()->left_pos.x;
	float x2 = target->Get_LineInfo()->left_pos.y;
	float y1 = target->Get_LineInfo()->right_pos.x;
	float y2 = target->Get_LineInfo()->right_pos.y;

	*pOutY = (y2 - x2) / (y1 - x1) * (finX - x1) + x2;

	return true;
}

void CLine_Manager::Ready_Line_Manager()
{
	CLine* pLine = CLine::Create();
	pLine->Set_LineInfo({ { 50.f, 150.f },{ 150.f, 500.f } });
	m_listLine.emplace_back(pLine);

	pLine = CLine::Create();
	pLine->Set_LineInfo({ { 150.f, 500.f },{ 300.f, 500.f } });
	m_listLine.emplace_back(pLine);

	pLine = CLine::Create();
	pLine->Set_LineInfo({ { 300.f, 500.f },{ 500.f, 150.f } });
	m_listLine.emplace_back(pLine);

	pLine = CLine::Create();
	pLine->Set_LineInfo({ { 500.f, 150.f },{ 800.f, 150.f } });
	m_listLine.emplace_back(pLine);
}

void CLine_Manager::Update_Line_Manager()
{
	POINT pt = {};
	GetCursorPos(&pt);
	ScreenToClient(g_hwnd, &pt);
	pt.x -= CScroll_Manager::Get_ScrollX();
	pt.y -= CScroll_Manager::Get_ScrollY();
	if (CKey_Manager::Get_Instance()->Key_Pressing(KEY_LEFT))
		CScroll_Manager::Set_ScrollX(5.f);
	if (CKey_Manager::Get_Instance()->Key_Pressing(KEY_RIGHT))
		CScroll_Manager::Set_ScrollX(-5.f);
	if (CKey_Manager::Get_Instance()->Key_Pressing(KEY_UP))
		CScroll_Manager::Set_ScrollY(5.f);
	if (CKey_Manager::Get_Instance()->Key_Pressing(KEY_DOWN))
		CScroll_Manager::Set_ScrollY(-5.f);


	if (CKey_Manager::Get_Instance()->Key_Down(KEY_LBUTTON))
	{
		CLine* pLine = CLine::Create();
		pLine->Set_LineInfo({ { (float)pt.x, (float)pt.y },{ (float)pt.x, (float)pt.y } });
		m_listLine.emplace_back(pLine);
	}
	if (CKey_Manager::Get_Instance()->Key_Up(KEY_LBUTTON))
	{
		m_listLine.back()->Set_RightPos({ (float)pt.x, (float)pt.y });
	}

	if (CKey_Manager::Get_Instance()->Key_Up(KEY_RBUTTON))
	{
		if (!m_listLine.empty())
			m_listLine.pop_back(); 
	}
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
