#pragma once
#include <Windows.h>

enum PLAYERPOISTION
{
	PLAYERPOSITION_DOWN = 0,
	PLAYERPOSITION_UP,
	PLAYERPOSITION_LEFT,
	PLAYERPOSITION_RIGHT
};

enum PLAYERSTATE
{
	PLAYERSTATE_IDLE = 0,
	PLAYERSTATE_MOVE,
	PLAYERSTATE_JUMP
};

class Player
{
private:
	HDC				MemDC;
	HBITMAP			m_NewBitmap;
	HBITMAP			m_OldBitmap;
	SIZE			m_size;

	PLAYERSTATE		m_PlayerState;

	int				m_X;
	int				m_Y;

	PLAYERPOISTION	m_Position;
	int				m_Anim;
	int				m_AnimTimer;

	bool			m_bIsJump;
	int				m_JumpTimer;
	int				m_JumpForce = 10;
	int				m_JumpPositionY = 0;

public:
	Player();

	void Init(HDC hdc, HINSTANCE hInst);
	void Draw(HDC hdc);
	void Input(HWND hWnd);
	void Idle();
	void Move(int x, int y);
	void AnimMove();
	void Jump();
	void JumpStart();
	void JumpEnd();
	void AnimJump();

	~Player();
};

