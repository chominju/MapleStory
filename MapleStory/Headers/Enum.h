#pragma once

namespace BULLET
{
	enum DIR {UP, DOWN, LEFT, RIGHT, END};
}
namespace OBJECT
{
	enum ID {BULLET, SHIELD, MONSTER, BOSS, PLAYER, MOUSE,END};
}

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
	LEFT,
	RIGHT,
	UP,
	DOWN,
	JUMP,
	SKILL,
	NONE,
};
