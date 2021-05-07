#pragma once
class CEditor_Manager
{
public:
	CEditor_Manager();
	~CEditor_Manager();

public:
	void Ready_Editor_Manager();
	void Update_Editor_Manager();
	void Render_Editor_Manager();
	void Release_Editor_Manager();

private:
	HDC m_hdc;
};

