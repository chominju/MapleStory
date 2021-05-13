#include "stdafx.h"
#include "Tool_SaveData.h"
#include "Tool_Line.h"
#include "Tool_Line_Manager.h"
#include <iostream>
#include <fstream>
#include <string>

CSaveData*  CSaveData::m_instance=nullptr;
CSaveData::CSaveData()
{
}

CSaveData::~CSaveData()
{
}

void CSaveData::Save_Data(TCHAR * fileName)
{
	HANDLE hFile;
	hFile = CreateFile(fileName, GENERIC_WRITE, 0, 0, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, nullptr);

	if (INVALID_HANDLE_VALUE == hFile)
	{
		MessageBox(nullptr, L"실패!", L"systemError", MB_OK);
		return;
	}
	DWORD dwByte = 0;
	list<CLine*>* line_list = CLine_Manager::Get_Instance()->Get_listLine();
	for (auto& pLine : *line_list)
		WriteFile(hFile, pLine->Get_LineInfo(), sizeof(Line_Info), &dwByte, nullptr);

	CloseHandle(hFile);
	MessageBox(nullptr, L"저장완료!", L"오예!", MB_OK);

}
