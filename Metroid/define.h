﻿#ifndef _DEFINE_H__
#define _DEFINE_H__

#define _USE_MATH_DEFINES

#include <d3d9.h>
#include <d3dx9.h>
using namespace std;

#define WINDOW_WIDTH 512
#define WINDOW_HEIGHT 450
#define SCALE_FACTOR 2.0f

#define COLOR_WHITE D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f) // màu trắng
#define COLOR_KEY D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f) // màu đen, màu mà khi load hình nó sẽ bỏ qua thành trong suốt

// ID của Sprite, object
enum eID
{
	PLAYER = 0,
	INTRO_BACKGROUND = 1,
	FONT = 2,

	INFO = 3,
	LIFE_ICON = 4,
	ENERGY_ICON = 5,

	TILESET_METROID = 6,

	WALL = 20,
	CHANGE_MAP_DIRECTION = 21,
	AUTO_MOVE_VIEWPORT = 22,
	
	FIRE = 30,

	DOOR = 35,
	BLUE_DOOR = 36,
	RED_DOOR = 37,
	
	BREAKABLE_WALL = 38,
	BREAKABLE_BLUE_WALL = 39,
	BREAKABLE_RED_WALL = 40,

	ITEM_BALL = 41,
	BLUE_ITEM_BALL = 42,
	RED_ITEM_BALL = 43,

	ENEMY = 49,
	SKREE_BULLET = 50,
	RIPPER = 51,
	WAVER = 52,
	SKREE = 53,
	MELLOW = 54,
	RIO = 55,
	ZEB = 56,
	ZEB_PIPE = 57,
	ZOOMER = 58,

	BOSS_STAGE = 59,
	ZEEBETITE = 60,
	METROID = 61,
	MOTHER_BRAIN = 62,
	RINKA = 63,
	RINKA_CANNON = 64,
	CANNON_BULLET = 65,
	LEFT_CANNON = 66,
	MIDDLE_CANNON = 67,
	RIGHT_CANNON = 68,

	RIDLEY_BULLET = 69,
	RIDLEY = 70,

	ITEM = 80,
	ENERGY_TANK = 81,
	ENERGY_BALL = 82,
	MARU_MARI = 83,
	LONG_BEAM = 84,
	ICE_BEAM = 85,
	MISSILE_ROCKET_BALL = 86,
	ROCKET_BALL = 87,
	BOMB_BALL = 88,
	VARIA = 89,

	BULLET_EFFECT = 100,
	NORMAL_BULLET = 101,
	ICE_BULLET = 102,
	MISSILE_ROCKET = 103,
	BOMB = 104,

	EXPLOSION = 105,

	PLAYER_VICTORY = 106
};

// Trạng thái của object
enum eStatus
{
	NORMAL = 0,
	MOVING_LEFT = (1 << 0),
	MOVING_RIGHT = (1 << 1),
	JUMPING = (1 << 2),
	FALLING = (1 << 3),
	RUNNING = (1 << 4),
	LOOKING_UP = (1 << 5),
	ROLLING_DOWN = (1 << 6),
	ATTACKING = (1 << 7),
	DIE = (1 << 8),
	DESTROY = (1 << 9)
};

// Hướng bị va chạm của object
// Hướng đạn
enum eDirection
{
	NONE = 0,
	TOP = (1 << 0),
	LEFT = (1 << 1),
	RIGHT = (1 << 2),
	BOTTOM = (1 << 3)
};

// Hướng map
enum eMapDirection
{
	VERTICAL = 0,
	HORIZONTAL = 1
};

// ID của Sound
enum eSoundID
{
	INTRO_SCENE,
	PLAY_SCENE,
	OVER_SCENE,
	VICTORY_SCENE,
	
	PLAYER_JUMP,
	PLAYER_BE_HIT,
	PLAYER_DIE,

	FIRE_NORMAL_BULLET,
	FIRE_ICE_BULLET,
	FIRE_MISSILE_ROCKET,
	SET_BOMB,

	GET_ENERGY_TANK,
	GET_ENERGY_BALL,
	GET_MISSILE_ROCKET_BALL,

	HIT_ENEMY,
	HIT_RIPPER,
	HIT_MOTHER_BRAIN,

	EXPLOSION_SOUND
};

typedef D3DXVECTOR3 GVector3;
typedef D3DXVECTOR2 GVector2;
#define VECTOR2ZERO GVector2(0.0f, 0.0f)

#ifndef SAFE_DELETE

#define SAFE_DELETE(ptr) \
if(ptr) \
{\
	delete (ptr); \
	ptr = nullptr; \
} \

#endif // !SAFE_DELETE

#endif // !_DEFINE_H__
