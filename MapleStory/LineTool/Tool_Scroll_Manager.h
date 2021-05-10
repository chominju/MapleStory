#pragma once
class CScroll_Manager
{
public:
	CScroll_Manager();
	~CScroll_Manager();
public:
	static void Set_ScrollX(int _fx) { m_scrollPos.x += _fx; }
	static void Set_ScrollY(int _fy) { m_scrollPos.y += _fy; }
	static int Get_ScrollX() { return m_scrollPos.x; }
	static int Get_ScrollY() { return m_scrollPos.y; }
private:
	static Pos_int m_scrollPos;
};