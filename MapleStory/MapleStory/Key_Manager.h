#pragma once
//0000	0001
#define KEY_LBUTTON 0x0001
//0000	0010
#define KEY_RBUTTON 0x00000002
//0000	0100
#define KEY_LEFT	0x00000004
//0000	1000		 
#define KEY_RIGHT	0x00000008
//0001	0000		  
#define KEY_UP		0x00000010
//0010	0000		 
#define KEY_DOWN	0x00000020
					 
#define KEY_F		0x00000040
#define KEY_A		0x00000080
#define KEY_Q		0x00000100
#define KEY_W		0x00000200
#define KEY_E		0x00000400
#define KEY_R		0x00000800
					 
#define KEY_P		0x00001000
#define KEY_I		0x00002000
					
#define KEY_F5		0x00004000

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
