#pragma once
#include "Bitmap.h"
#include "Collision.h"

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
	PLAYERSTATE	m_CurPosition;

	int					m_Life;

	POINT				m_Point;

	float				m_AnimTime;
	float				m_StartAnimTimer;
	float				m_CurAnimTimer;

	int					m_Speed;

	Collision			m_Collision;

	bool				m_Movealbe;

public:
	Player();
	~Player();

public:
	void Init(HDC MemDC);
	void Update(bool Moveable);
	void Input();
	void Move(int x, int y);
	void Draw();
	void PlayAnim();
	void Spawn(POINT point);

public:
	inline int GetPlayerLife()
	{
		return m_Life;
	}

	inline POINT GetPlayerPoint()
	{
		return m_Point;
	}
	inline void SetPlayerPoint(POINT point)
	{
		m_Point = point;
	}

	inline PLAYERSTATE GetPlayerState()
	{
		return m_State;
	}
	inline PLAYERSTATE GetCurPosition()
	{
		return m_CurPosition
	}

	inline Collision GetCollision()
	{
		return m_Collision;
	}
};

