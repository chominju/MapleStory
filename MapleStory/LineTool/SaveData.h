#pragma once
class CSaveData
{
private:
	explicit CSaveData();
	~CSaveData();

public:
	static CSaveData* Get_Instance()
	{
		if (nullptr == m_instance)
			m_instance = new CSaveData;
		return m_instance;
	}

	void Save_Data(TCHAR * mapName);
private:
	static CSaveData* m_instance;
};

