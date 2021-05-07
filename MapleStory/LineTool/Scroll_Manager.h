#pragma once
class CScroll_Manager
{
public:
	CScroll_Manager();
	~CScroll_Manager();
public:
	static void Set_ScrollX(float _fx) { m_scrollPos.x += _fx; }
	static void Set_ScrollY(float _fy) { m_scrollPos.y += _fy; }
	static float Get_ScrollX() { return m_scrollPos.x; }
	static float Get_ScrollY() { return m_scrollPos.y; }
private:
	static Pos m_scrollPos;
};
