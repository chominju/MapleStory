#pragma once

//namespace BULLET
//{
//	enum DIR {UP, DOWN, LEFT, RIGHT, END};
//}

enum Object_ID
{
	PORTAL,
	BOSS,
	MONSTER,
	ROPE,
	PLAYER,
	DROP_ITEM,
	INVENTORY_ITEM,
	BUTTON,
	ATTACK_SKILL,
	BUFF_SKILL,
	BOSS_SKILL,
	SKILL_EFFECT,
	UI,
	MOUSE,
	END
};


enum Scene_ID
{
	SCENE_LOADING,
	SCENE_Kerning_City,
	SCENE_MAP1,
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
	ROPING,
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
	ALERT_INDEX = 4,
	JUMP_INDEX = 1,
	ROPE_INDEX = 2,
	ROPE_STOP_INDEX = 1,
	DEAD_INDEX = 1
};

enum Item_type
{
	MESO,
	CONSUME,
	ETC,
	EQUIPMENT,
	WEAR_EQUIPMENT,
};

enum Direction
{
	DIR_LEFT,
	DIR_RIGHT
};

enum Mushroom_Animation
{
	MUSHROOM_STAND,
	MUSHROOM_WALK,
	MUSHROOM_HIT,
	MUSHROOM_DIE,
	MUSHROOM_JUMP
};


enum Mushroom_Animation_Index
{
	MUSHROOM_STAND_INDEX = 2,
	MUSHROOM_WALK_INDEX = 3,
	MUSHROOM_HIT_INDEX = 1,
	MUSHROOM_DIE_INDEX = 3,
	MUSHROOM_JUMP_INDEX = 1
};

enum Octopus_Animation
{
	OCTOPUS_WALK,
	OCTOPUS_HIT,
	OCTOPUS_DIE
};

enum Octopus_Animation_Index
{
	OCTOPUS_WALK_INDEX = 5,
	OCTOPUS_HIT_INDEX = 1,
	OCTOPUS_DIE_INDEX = 4
};

enum Boss_Animation
{
	Boss_STAND,
	Boss_WALK,
	Boss_ATTACK1=0,
	Boss_ATTACK2=0,
	Boss_ATTACK3=0,
	Boss_DIE=0
};

enum Boss_Animation_Index
{
	Boss_STAND_INDEX = 6,
	Boss_WALK_INDEX = 6,
	Boss_ATTACK1_INDEX,
	Boss_ATTACK2_INDEX,
	Boss_ATTACK3_INDEX,
	Boss_DIE_INDEX = 4
};


enum Monster_State
{
	STATE_WALK,
	STATE_TRACE,
	STATE_JUMP,
	STATE_HIT,
	STATE_NOHIT,
	STATE_DIE
};