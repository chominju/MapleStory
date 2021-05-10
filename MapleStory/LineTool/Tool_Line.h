#pragma once
class CLine final
{
private:
	CLine();
public:
	~CLine();

public:
	const Line_Info* Get_LineInfo() { return &m_lineInfo; }
	void Set_LineInfo(const Line_Info& rLineInfo) { m_lineInfo = rLineInfo; }
	void Set_RightPos(const Pos_float& rRightPos) { m_lineInfo.right_pos = rRightPos; }


public:
	void Render_Line(HDC hdc);
public:
	static CLine* Create(Line_Info* lineInfo = nullptr);

private:
	Line_Info m_lineInfo;
};

