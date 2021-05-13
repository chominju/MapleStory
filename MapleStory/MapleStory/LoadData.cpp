#include "stdafx.h"
#include "LoadData.h"
#include "MyBitmap.h"
#include "Bitmap_Manager.h"
#include "Line_Manager.h"
#include "Line.h"
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
	readFile.open("../ResourceList/imageList.txt");
	
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

bool CLoadData::Load_Monster()
{
	return true;
}

bool CLoadData::Load_Line(TCHAR * fileName)
{
	HANDLE hFile = CreateFile(fileName, GENERIC_READ, 0, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr);
	if (INVALID_HANDLE_VALUE == hFile)
	{
		MessageBox(nullptr, L"�ε����...", L"LoadFail", MB_OK);
		return false;
	}
	//list<CLine*>* line_list = CLine_Manager::Get_Instance()->Get_listLine();
	////���� �����ʹ� �ʿ� ������ ������!////////////////////////////////////////////////////////////////////////
	//for (auto& pLine : *line_list)
	//	Safe_Delete(pLine);
	//line_list->clear();
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
		CLine_Manager::Get_Instance()->Insert_Line_Manager(pLine->Get_LineInfo()->left_pos, pLine->Get_LineInfo()->right_pos);
		//line_list->push_back(pLine);
	}
	CloseHandle(hFile);
	//MessageBox(nullptr, L"�ε强��", L"LoadSuccess", MB_OK);

	/*ifstream readFile;
	readFile.open("../ResourceList/lineList.txt");
	if (readFile.is_open())
	{
		while (!readFile.eof())
		{
			string leftX;
			string leftY;
			string rightX;
			string rightY;
			Pos_float leftPos;
			Pos_float rightPos;
			getline(readFile, leftX);
			leftPos.x= stoi(leftX);

			getline(readFile, leftY);
			leftPos.y = stoi(leftY);

			getline(readFile, rightX);
			rightPos.x = stoi(rightX);
			getline(readFile, rightY);
			rightPos.y = stoi(rightY);

			CLine_Manager::Get_Instance()->Insert_Line_Manager(leftPos, rightPos);
		}

	}*/

	return true;
}
