#pragma once
#include "Mecro.h"

enum MOUSECLICK
{
	MOUSECLICK_IDLE,
	MOUSECLICK_LEFT,
	MOUSECLICK_RIGHT
};

class Player
{
private:
	MOUSECLICK		m_MouseClick;
	POINT				m_MousePoint;

public:
	Player();
	~Player();

public:
	void Init();
	void Input(LPARAM lParam);

public:
	inline MOUSECLICK GetMouseClick()
	{
		return m_MouseClick;
	}
	inline POINT GetMousePoint()
	{
		return m_MousePoint;
	}
};

