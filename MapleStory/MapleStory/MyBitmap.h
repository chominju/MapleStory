#pragma once
class CMyBitmap
{
public:
	CMyBitmap();
	~CMyBitmap();
public:
	HDC Get_memDC() { return m_memDC; }
	void Insert_Bitmap(const TCHAR* imagePath);
	Pos_int& GetSize()
	{
		return m_bitmapSize;
	}
	void Release_Bitmap();

private:
	HDC m_memDC;
	HBITMAP m_oldBitmap;
	HBITMAP m_bitmap;

	Pos_int m_bitmapSize;
};
