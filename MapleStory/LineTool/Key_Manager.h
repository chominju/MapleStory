#pragma once

//0000	0001
#define KEY_LBUTTON 0x0001
//0000	0010
#define KEY_RBUTTON 0x0002
//0000	0100
#define KEY_LEFT	0x0004
//0000	1000
#define KEY_RIGHT	0x0008
//0001	0000
#define KEY_UP		0x0010
//0010	0000
#define KEY_DOWN	0x0020


class CKey_Manager
{
public:
	static CKey_Manager* Get_Instance()
	{
		static CKey_Manager* instance = nullptr;
		if (nullptr == instance)
			instance = new CKey_Manager;
		return instance;
	}
	static void Destroy_Instance()
	{
		CKey_Manager* instance = Get_Instance();
		if (instance)
		{
			delete instance;
		}
	}
private:
	explicit CKey_Manager();
	~CKey_Manager();
public:
	void Update_Key_Manager();
	bool Key_Up(DWORD key);
	bool Key_Down(DWORD key);
	bool Key_Pressing(DWORD key);

private:
	DWORD m_key;
	DWORD m_keyDown;
	DWORD m_keyUP;

};

