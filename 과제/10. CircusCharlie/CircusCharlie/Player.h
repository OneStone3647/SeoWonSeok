#pragma once
#include "Bitmap.h"

enum PLAYERSTATE
{
	PLAYERSTATE_IDLE,
	PLAYERSTATE_MOVE,
	PLAYERSTATE_JUMP
};

class Player
{
private:
	Bitmap m_PlayerBitmap[6];
public:
	Player();
	~Player();

	void Input();
};

