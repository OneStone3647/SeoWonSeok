#pragma once
#include <Windows.h>

enum STATE
{
	STATE_IDLE = 0,
	STATE_MOVE,
	STATE_JUMPSTART,
	STATE_JUMPEND
};

enum DIRECTION
{
	DIRECTION_DOWN = 0,
	DIRECTION_UP,
	DIRECTION_LEFT,
	DIRECTION_RIGHT
};

class Player
{
private:
	HDC				MainMemDC;
	HDC				SubMemDC;
	HBITMAP			m_NewBitmap;
	HBITMAP			m_OldBitmap;
	SIZE				m_size;

	int					m_X;
	int					m_Y;

	STATE				m_State;
	DIRECTION		m_Direction;

	int					m_Anim;
	int					m_AnimTimer;

	bool				m_bIsJump;
	int					m_JumpAnim;
	int					m_JumpTimer;
	int					m_JumpForce;
	int					m_JumpPosY;

public:
	Player();

	void Init(HDC mainDC, HDC subDC, HBITMAP* newBitmap, HBITMAP* oldBitmap);
	void Draw();
	void Input(HWND hWnd);
	void Move(int x, int y);
	void AnimMove();
	void Jump();
	void JumpStart();
	void JumpEnd();

	~Player();
};

