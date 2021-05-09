#include "stdafx.h"
#include "SaveData.h"
#include "Line.h"
#include "Line_Manager.h"
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

void CSaveData::Save_Data(TCHAR * mapName)
{
	ofstream writeFile;
	if (!lstrcmp(mapName, L"Kerning_City"))
	{
		writeFile.open("../ResourceList/lineList.txt");
	}
	
	list<CLine*>* line_list = CLine_Manager::Get_Instance()->Get_listLine();

	for (auto iter : *line_list)
	{
		string x1 = to_string(iter->Get_LineInfo()->left_pos.x) + "\n";
		string y1 = to_string(iter->Get_LineInfo()->left_pos.y) + "\n";
		string x2 = to_string(iter->Get_LineInfo()->right_pos.x) + "\n";
		string y2 = to_string(iter->Get_LineInfo()->right_pos.y) + "\n";
		writeFile.write(x1.c_str(),x1.size());
		writeFile.write(y1.c_str(),y1.size());
		writeFile.write(x2.c_str(),x2.size());
		writeFile.write(y2.c_str(),y2.size());
	}
}
