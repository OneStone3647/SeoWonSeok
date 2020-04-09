#pragma once
#include "Bitmap.h"

enum PLAYERINDEX
{
	PLAYERINDEX_DOWN00,
	PLAYERINDEX_DOWN01,
	PLAYERINDEX_LEFT00,
	PLAYERINDEX_LEFT01,
	PLAYERINDEX_RIGHT00,
	PLAYERINDEX_RIGHT01,
	PLAYERINDEX_UP00,
	PLAYERINDEX_UP01
};

enum PLAYERSTATE
{
	PLAYERSTATE_IDLE,
	PLAYERSTATE_MOVEDOWN,
	PLAYERSTATE_MOVELEFT,
	PLAYERSTATE_MOVERIGHT,
	PLAYERSTATE_MOVEUP
};

class Player
{
private:
	HDC				m_MemDC;

	Bitmap			m_PlayerBitmap[8];
	int					m_PlayerBitmapIndex;

	PLAYERSTATE	m_State;

	int					m_Life;

	POINT				m_Point;

	float				m_AnimTime;
	float				m_StartAnimTimer;
	float				m_CurAnimTimer;

public:
	Player();
	~Player();

public:
	void Init(HDC MemDC);
	void Update();
	void Input();
	void Move(float x, float y);
	void Draw();
	void PlayAnim();

public:
	inline int GetPlayerLife()
	{
		return m_Life;
	}

	inline void SetPlayerPoint(int x, int y)
	{
		m_Point = { x, y };
	}
};

