﻿#ifndef __NS_FRAMEWORK__
#define __NS_FRAMEWORK__

#define _USE_MATH_DEFINES

#include <d3d9.h>		// d3d9.lib
#include <d3dx9.h>		// d3dx9.lib
#include <dinput.h>		// dinput8.lib, dxguid.lib
#include <dsound.h>		// dsound.lib

#include <windows.h>
#include <exception>
#include <math.h>
#include <string>
#include <map>
#include <vector>
#include "utils.h"
using namespace std;

#define WINDOW_WIDTH 512
#define WINDOW_HEIGHT 448
#define SCALE_FACTOR 2.0f

#define COLOR_WHITE D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f)	// màu trắnng
#define COLOR_KEY D3DXCOLOR(1.0f, 0.0f, 1.0f, 1.0f)		// màu khi mà load hình nó bỏ qua -> trong suốt

enum eID
{
	PLAYER = 0,
	MAIN_MENU = 1,
	FONTFULL = 2,
};

enum eStatus
{
	NORMAL = 0,
	MOVING_LEFT = (1 << 0),
	MOVING_RIGHT = (1 << 1),
	JUMPING = (1 << 2),
	RUNNING = (1 << 3),
	DIE = (1 << 4),
	SIT_DOWN = (1 << 5),
	FALLING = (1 << 6),

	DESTROY = (1 << 7),

	ATTACKING = (1 << 8),

	MOVING_UP = (1 << 9),
	MOVING_DOWN = (1 << 10),

	STAND_UP = (1 << 11),
	STAND_DOWN = (1 << 12),

	BEING_HIT = (1 << 13),
};

enum eDirection
{
	NONE = 0,
	TOP = 1,
	BOTTOM = 2,
	LEFT = 4,
	RIGHT = 8,
	TOP_BOTTOM = (TOP | BOTTOM),
	ALL = (TOP | BOTTOM | LEFT | RIGHT),
};

enum eMapType
{
	VERTICAL = 0,
	HORIZONTAL = 1
};

enum eSoundId
{
	INTRO_SCENE,
	PLAY_SCENE,
	OVER_SCENE,
};

typedef D3DXVECTOR3 GVector3;
typedef D3DXVECTOR2 GVector2;
#define VECTOR2ZERO GVector2(0.0f, 0.0f)
#define VECTOR2ONE  GVector2(1.0f, 1.0f)

#define EVENT_RECEIVER [event_receiver(native)]

#ifndef SAFE_DELETE

#define SAFE_DELETE(p) \
if(p) \
{\
	delete (p); \
	p = nullptr; \
} \

#endif // !SAFE_DELETE


#endif // !__NS_FRAMEWORK__
