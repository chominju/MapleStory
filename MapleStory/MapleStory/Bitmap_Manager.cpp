#include "stdafx.h"
#include "Bitmap_Manager.h"
#include "MyBitmap.h"
CBitmap_Manager* CBitmap_Manager::m_instance = nullptr;
CBitmap_Manager::CBitmap_Manager()
{
}


CBitmap_Manager::~CBitmap_Manager()
{
	Release_Bitmap_Manager();
}

HDC CBitmap_Manager::Get_memDC(const TCHAR * imageKey)
{
	auto& iter = find_if(m_mapBitmap.begin(), m_mapBitmap.end(), [&](auto& rPair)
	{
		return !lstrcmp(imageKey, rPair.first);
	});

	if (m_mapBitmap.end() == iter)
		return nullptr;

	return iter->second->Get_memDC();
}

void CBitmap_Manager::Insert_Bitmap_Manager(const TCHAR* imageKey, const TCHAR* imagePath)
{
	auto& iter = find_if(m_mapBitmap.begin(), m_mapBitmap.end(), [&](auto& rPair)
	{
		return !lstrcmp(imageKey, rPair.first);
	});

	if (m_mapBitmap.end() != iter)
		return;

	CMyBitmap* pBitmap = new CMyBitmap;
	pBitmap->Insert_Bitmap(imagePath);
	m_mapBitmap.emplace(imageKey, pBitmap);

}

void CBitmap_Manager::Release_Bitmap_Manager()
{
	for (auto& rPair : m_mapBitmap)
		Safe_Delete(rPair.second);
	m_mapBitmap.clear();
}
