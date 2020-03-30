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
	POINT				m_MousePoint;

public:
	Player();
	~Player();

public:
	void Init();
	void Input(MODE GameMode, LPARAM lParam);

public:
	inline PLAYERMODE GetPlayerMode()
	{
		return m_PlayerMode;
	}

	inline POINT GetMousePoint()
	{
		return m_MousePoint;
	}
};

