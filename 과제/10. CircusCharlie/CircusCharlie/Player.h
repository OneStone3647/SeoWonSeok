#pragma once
#include "Bitmap.h"

enum STATE
{
	STATE_IDLE,
	STATE_MOVE,
	STATE_JUMP
};

enum PLAYERINDEX
{
	PLAYERINDEX_IDLE,
	PLAYERINDEX_MOVE1,
	PLAYERINDEX_MOVE2,
	PLAYERINDEX_WIN1,
	PLAYERINDEX_WIN2,
	PLAYERINDEX_DIE
};

class Player
{
private:
	HWND		m_hWnd;
	HDC			m_MemDC;
	HBITMAP		m_NewBitmap;
	HBITMAP		m_OldBitmap;

	Bitmap		m_PlayerBitmap[6];

	STATE		m_EState;
	bool		m_bIsJump;

	float		m_Player_X;
	float		m_Player_Y;

public:
	Player();
	~Player();

	void Init(HWND hWnd);
	void Update();
	void Input();
	void Move();
	void Jump();
};

