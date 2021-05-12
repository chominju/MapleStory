#pragma once

//namespace BULLET
//{
//	enum DIR {UP, DOWN, LEFT, RIGHT, END};
//}

enum Object_ID
{
	MONSTER,
	BOSS,
	PORTAL,
	PLAYER,
	UI,
	MOUSE,
	END
};


enum Scene_ID
{
	SCENE_LOADING,
	SCENE_Kerning_City,
	SCENE_MAP1, 
	SCENE_MAP2, 
	SCENE_BOSS,
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
	DEAD,
	PRONE
};

enum Animation_index
{
	STAND_INDEX = 3,
	WALK_INDEX = 4,
	PRONE_INDEX = 1,
	PRONE_SWING_INDEX = 2,
	SWING_INDEX = 3,
	ALERT_INDEX = 3,
	JUMP_INDEX = 1,
	ROPE_INDEX = 2,
	DEAD_INDEX = 1
};
