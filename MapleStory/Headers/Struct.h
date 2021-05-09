#pragma once

typedef struct tagInfo
{
	float	fX; 
	float	fY; 
	int		iCX; 
	int		iCY; 
}Object_Info;


typedef struct tagLinePoint
{
	tagLinePoint() :x(0.f),y(0.f){}
	tagLinePoint(float _fx, float _fy)
		:x(_fx)
		, y(_fy)
	{}
	float x; 
	float y; 
}Pos;

typedef struct tagLINEINFO
{
	tagLINEINFO()
	{
		ZeroMemory(this, sizeof(tagLINEINFO)); 
	}
	tagLINEINFO(Pos tLP, Pos tRP)
		:left_pos(tLP)
		,right_pos(tRP)
		{}
	Pos left_pos; 
	Pos right_pos; 
}Line_Info;


typedef struct
{
	char imageKey[32];
	char dropKey[32];
	int hp;
	int maxHp;
	int exp;
	int money;
	DWORD respawnTime;
	DWORD respawnPos;
	DWORD attackTime;

}Monster_Info;


typedef struct
{
	char imageKey[32];
	int hp;
	int maxHp;
	int exp;
	int maxExp;
	DWORD attackTime;

}Player_Info;