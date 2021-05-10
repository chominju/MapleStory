#include "stdafx.h"
#include "MyBitmap.h"


CMyBitmap::CMyBitmap()
{
}


CMyBitmap::~CMyBitmap()
{
	Release_Bitmap();
}

void CMyBitmap::Insert_Bitmap(const TCHAR * pFilePath)
{
	HDC hDC = GetDC(g_hwnd);

	m_memDC = CreateCompatibleDC(hDC);

	ReleaseDC(g_hwnd, hDC);

	m_bitmap = (HBITMAP)LoadImage(NULL, pFilePath, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);

	m_oldBitmap = (HBITMAP)SelectObject(m_memDC, m_bitmap);

	BITMAP bit;
	GetObject(m_bitmap, sizeof(BITMAP), &bit);
	m_bitmapSize.x = bit.bmWidth;
	m_bitmapSize.y = bit.bmHeight;

}

void CMyBitmap::Release_Bitmap()
{
	SelectObject(m_memDC, m_oldBitmap);
	DeleteObject(m_bitmap);
	DeleteDC(m_memDC);
}
