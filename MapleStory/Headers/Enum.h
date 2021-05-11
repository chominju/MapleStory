#pragma once

//namespace BULLET
//{
//	enum DIR {UP, DOWN, LEFT, RIGHT, END};
//}

enum Object_ID
{
	BULLET,
	SHIELD,
	MONSTER,
	BOSS,
	PLAYER,
	UI,
	MOUSE,
	END
};


enum Scene_ID
{
	SCENE_LOADING,
	SCENE_Kerning_City,
	SCENE_STAGE1, 
	SCENE_STAGE2, 
	SCENE_END
};

enum CurrentKey
{
	CUR_LEFT,
	CUR_RIGHT,
	CUR_UP,
	CUR_DOWN,
	CUR_JUMP,
	CUR_SKILL,
	CUR_NONE,
};

enum Animation
{
	STAND,
	WALK,
	SWING,
	ALERT,
	JUMP,
	ROPE,
	DEAD
};

enum Animation_index
{
	STAND_INDEX = 3,
	WALK_INDEX = 4,
	SWING_INDEX = 3,
	ALERT_INDEX = 3,
	JUMP_INDEX = 1,
	ROPE_INDEX = 2,
	DEAD_INDEX = 1
};
