#pragma once
#include "DxLib.h"
#include "stdlib.h"
#include "math.h"

const int WIDTH = 960;
const int HEIGHT = 640;
const int CATCHER_SIZE = 20;

struct VECTOR2
{
	int x;
	int y;
};

struct PLAYINFO
{
	VECTOR2 pos;
	bool circleFlag;
};

struct DROP
{
	PLAYINFO info;
	int dropSpeed;
	int color;
	int size;
};

struct INFO
{
	int timer;
	int combo;
	int highCombo;
};

enum SCENE
{
	TITLE,
	PLAY,
	END
};