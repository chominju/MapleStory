#pragma once
class CLine
{
private:
	CLine();
public:
	~CLine();

public:
	const Line_Info* Get_LineInfo() { return &m_line_info; }
	void Set_LineInfo(const Line_Info& rLineInfo) { m_line_info = rLineInfo; }
public:
	void Render_Line(HDC hdc);
	static CLine* Create(Line_Info* line_Info = nullptr);
private:
	Line_Info m_line_info;
};

