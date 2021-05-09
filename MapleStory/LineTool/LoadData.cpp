#include "stdafx.h"
#include "LoadData.h"
#include "MyBitmap.h"
#include "Bitmap_Manager.h"
#include "Line_Manager.h"
#include <iostream>
#include <fstream>
#include <string>
#include <atlstr.h>


CLoadData* CLoadData::m_instance = nullptr;

CLoadData::CLoadData()
{
}

CLoadData::~CLoadData()
{
}

bool CLoadData::Load_Image()
{
	ifstream readFile;
	readFile.open("../ResourceList/MapList.txt");
	
	if (readFile.is_open())
	{
		while (!readFile.eof())
		{
			string temp;
			getline(readFile, temp);
			int len = temp.size();
			char *ch = new char[len+1];
			strcpy_s(ch, len+1, temp.c_str());
			TCHAR *imageKey = new TCHAR[len+1];
			MultiByteToWideChar(CP_ACP, 0, ch, -1, imageKey, len + 1);

			string temp2;
			getline(readFile, temp2);
			len = temp2.size();
			char *ch2 = new char[len + 1];
			strcpy_s(ch2, len+1, temp2.c_str());
			TCHAR *imagePath = new TCHAR[len + 1];
			MultiByteToWideChar(CP_ACP, 0, ch2, -1, imagePath, len + 1);

			CBitmap_Manager::Get_Instance()->Insert_Bitmap_Manager(imageKey, imagePath);
			
		/*	imageKey[str.size()] = 0;
			wcstombs_s(str.size(),str.c_str(), imageKey, str.size());

			copy_s(str.begin(), str.end(), imageKey);
			copy
			if (readFile.eof())
				return false;

			string str2;
			getline(readFile, str2);
			TCHAR *imagePath = new TCHAR[str2.size() + 1];
			imageKey[str2.size()] = 0;
			copy(str2.begin(), str2.end(), imagePath);*/


			/*CMyBitmap *newBitmap = new CMyBitmap;
			newBitmap->Insert_Bitmap(imagePath);
			m_map_bitMap.insert(make_pair(imageKey, newBitmap));*/

		}
	}
	else
		return false;

	return true;
}
