#include "stdafx.h"
#include "Tool_LoadData.h"
#include "Tool_MyBitmap.h"
#include "Tool_Bitmap_Manager.h"
#include "Tool_Line.h"
#include "Tool_Line_Manager.h"
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

void CLoadData::Load_Line(TCHAR * fileName)
{
	HANDLE hFile = CreateFile(fileName, GENERIC_READ, 0, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr);
	if (INVALID_HANDLE_VALUE == hFile)
	{
		MessageBox(nullptr, L"�ε����...", L"LoadFail", MB_OK);
		return;
	}
	list<CLine*>* line_list = CLine_Manager::Get_Instance()->Get_listLine();
	//���� �����ʹ� �ʿ� ������ ������!////////////////////////////////////////////////////////////////////////
	for (auto& pLine : *line_list)
		Safe_Delete(pLine);
	line_list->clear();
	//�ҷ����� �ڵ�. 
	// ��¿����ڶ� �޾��� ���� ���������. 
	//�󸶳� �������� �ƹ��� ��. ////////////////////////////////////////////////////////////////////
	DWORD dwByte = 0;
	Line_Info tLineInfo = {};
	CLine* pLine = nullptr;
	while (true)
	{
		ReadFile(hFile, &tLineInfo, sizeof(Line_Info), &dwByte, nullptr);
		if (0 == dwByte)
			break;

		pLine = CLine::Create(&tLineInfo);
		line_list->push_back(pLine);
	}
	CloseHandle(hFile);
	MessageBox(nullptr, L"�ε强��", L"LoadSuccess", MB_OK);
}

bool CLoadData::Load_Image()
{
	ifstream readFile;
	readFile.open("../ResourceList/Tool_List.txt");
	
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
		}
	}
	else
		return false;

	return true;
}
