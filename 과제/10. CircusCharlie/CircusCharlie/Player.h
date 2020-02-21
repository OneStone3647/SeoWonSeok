#pragma once
#include "Bitmap.h"
#include <math.h>

enum STATE
{
	STATE_IDLE,
	STATE_MOVE,
	STATE_JUMP
};

enum ANIMMOVE
{
	ANIMMOVE_IDLE,
	ANIMMOVE_MOVE1,
	ANIMMOVE_MOVE2
};

class Player
{
private:
	HDC				m_BackDC;

	Bitmap			m_Player_Idle;
	Bitmap			m_Player_Move1;
	Bitmap			m_Player_Move2;
	Bitmap			m_Player_Win1;
	Bitmap			m_Player_Win2;
	Bitmap			m_Player_Die;

	float			m_X;
	float			m_Y;

	DWORD			m_LastTime;
	DWORD			m_CurTime;
	float			m_DeltaTime;

	int				m_Anim;
	int				m_AnimTimer;

	STATE			m_State;

	bool			m_bIsJump;
	float			m_CurJumpTime;
	int				m_JumpAnim;
	int				m_JumpTimer;
	int				m_JumpForce;
	float			m_JumpX;
	float			m_JumpY;

	float			m_VectorX;
	float			m_VectorY;

public:
	Player();
	~Player();
	
	void Init(HDC BackDC);
	void Update();
	void Input();
	void Move(float x, float y);
	void AnimMove();
	void Jump();
};

