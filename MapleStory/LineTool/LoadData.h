#pragma once
class CMyBitmap;
class CGameObject;

class CLoadData
{
private:
	explicit CLoadData();
	~CLoadData();

public:
	static CLoadData* Get_Instance()
	{
		if (nullptr == m_instance)
			m_instance = new CLoadData;
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
	bool Load_Image();

	map<const TCHAR*, CMyBitmap*>* Get_Map()
	{
		return &m_map_bitMap;
	}

private:
	static CLoadData* m_instance;
	map<const TCHAR*, CMyBitmap*> m_map_bitMap;
};

