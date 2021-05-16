#pragma once
#include "Enum.h"

typedef struct tagInfo
{
	float	x; 
	float	y; 
	int		sizeX; 
	int		sizeY; 
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
}Pos_float;

typedef struct tagLINEINFO
{
	tagLINEINFO()
	{
		ZeroMemory(this, sizeof(tagLINEINFO)); 
	}
	tagLINEINFO(Pos_float tLP, Pos_float tRP)
		:left_pos(tLP)
		,right_pos(tRP)
		{}
	Pos_float left_pos; 
	Pos_float right_pos; 
}Line_Info;

typedef struct
{
	Object_ID id;
	int level;
	float hp;
	float maxHp;
	int minAttack;
	int maxAttack;
	float exp;
	float maxExp;
	int money;

}Object_Data;
//typedef struct
//{
//	char imageKey[32];
//	char dropKey[32];
//
//	DWORD respawnTime;
//	DWORD respawnPos;
//	DWORD attackTime;
//
//}Monster_Info;
//
//
//typedef struct
//{
//	char imageKey[32];
//	int hp;
//	int maxHp;
//	int exp;
//	int maxExp;
//	DWORD attackTime;
//
//}Player_Info;

typedef struct posInt
{
	posInt() :x(0), y(0)
	{

	}
	posInt(int _x, int _y)
	{
		x = _x;
		y = _y;
	}
	int x;
	int y;
}Pos_int;


typedef struct
{
	DWORD frame_start;
	DWORD frame_end;
	DWORD frame_animation;
	DWORD frame_speed;
	DWORD frame_time;
}Animation_Frame;

typedef struct
{
	bool isLeft;
	bool isRight;
	bool isDown;
	bool isJump;
	bool isDoubleJump;
	bool isDoubleJumpReady;
	bool isAttack;
	bool isRope;
	bool isRopeMove;
	bool isSkill;
}Key_Push;
