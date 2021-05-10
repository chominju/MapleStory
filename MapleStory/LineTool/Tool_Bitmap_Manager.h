#pragma once
class CMyBitmap;
class CBitmap_Manager
{
private:
	CBitmap_Manager();
	~CBitmap_Manager();

public:
	static CBitmap_Manager* Get_Instance()
	{
		if (nullptr == m_instance)
			m_instance = new CBitmap_Manager;
		return m_instance;
	}
	static void Destroy_Instance()
	{
		if (m_instance)
		{
			delete m_instance;
			m_instance = nullptr;
		}
	}
public:
	HDC Get_memDC(const TCHAR* imageKey);
	Pos_float Get_Image_Size(const TCHAR* imageKey);
	void Insert_Bitmap_Manager(const TCHAR* imageKey, const TCHAR* imagePath);
	void Release_Bitmap_Manager();
private:
	static CBitmap_Manager* m_instance;
	map<const TCHAR*, CMyBitmap*> m_mapBitmap;
};

