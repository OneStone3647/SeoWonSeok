#pragma once
#include "Mecro.h"

enum PLAYERMODE
{
	PLAYERMODE_IDLE,
	PLAYERMODE_GAME,
	PLAYERMODE_MAPTOOL
};

class Player
{
private:
	PLAYERMODE	m_PlayerMode;

public:
	Player();
	~Player();

public:
	void Init();

public:
	inline PLAYERMODE GetPlayerMode()
	{
		return m_PlayerMode;
	}
};

