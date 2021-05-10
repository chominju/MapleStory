#pragma once
class CMyBitmap
{
public:
	CMyBitmap();
	~CMyBitmap();
public:
	HDC Get_memDC() { return m_memDC; }
	void Insert_Bitmap(const TCHAR* imagePath);
	Pos_float& GetSize() 
	{
		return m_scale;
	}
	void Release_Bitmap();

private:
	HDC m_memDC;
	HBITMAP m_oldBitmap;
	HBITMAP m_bitmap;

	Pos_float m_scale;
};
