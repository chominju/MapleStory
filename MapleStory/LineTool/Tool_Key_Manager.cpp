#include "stdafx.h"
#include "Tool_Key_Manager.h"


CKey_Manager::CKey_Manager()
	:m_key(0)
	, m_keyDown(0)
	, m_keyUP(0)
{
}


CKey_Manager::~CKey_Manager()
{
}

void CKey_Manager::Update_Key_Manager()
{
	m_key = 0;
	if (GetAsyncKeyState(VK_LBUTTON) & 0x8000)
		m_key |= KEY_LBUTTON;
	if (GetAsyncKeyState(VK_RBUTTON) & 0x8000)
		m_key |= KEY_RBUTTON;
	if (GetAsyncKeyState(VK_UP) & 0x8000)
		m_key |= KEY_UP;
	if (GetAsyncKeyState(VK_DOWN) & 0x8000)
		m_key |= KEY_DOWN;
	if (GetAsyncKeyState(VK_LEFT) & 0x8000)
		m_key |= KEY_LEFT;
	if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
		m_key |= KEY_RIGHT;
	if (GetAsyncKeyState('S') & 0x8000)
		m_key |= KEY_S;
	if (GetAsyncKeyState('L') & 0x8000)
		m_key |= KEY_L;

}

bool CKey_Manager::Key_Up(DWORD dwKey)
{
	if (m_key & dwKey)
	{
		m_keyUP |= dwKey;
		return false;
	}
	else if (m_keyUP & dwKey)
	{
		m_keyUP ^= dwKey;
		return true;
	}
	return false;
}

bool CKey_Manager::Key_Down(DWORD dwKey)
{
	//0000 0000
	//0000 0001
	//0000 0000 
	if ((m_key & dwKey) && !(m_keyDown & dwKey))
	{
		m_keyDown |= dwKey;
		return true;
	}
	else if (!(m_key & dwKey) && (m_keyDown & dwKey))
	{
		m_keyDown ^= dwKey;
		return false;
	}
	return false;
}

bool CKey_Manager::Key_Pressing(DWORD dwKey)
{
	if (m_key & dwKey)
		return true;
	return false;
}
