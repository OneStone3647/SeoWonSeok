#pragma once
#include "Bitmap.h"
#include <math.h>

enum STATE
{
	STATE_IDLE,
	STATE_MOVE,
	STATE_JUMP,
	STATE_LEFTJUMP,
	STATE_RIGHTJUMP
};

enum BITMAPINDEX
{
	BITMAPINDEX_IDLE,
	BITMAPINDEX_MOVE1,
	BITMAPINDEX_MOVE2,
	BITMAPINDEX_WIN1,
	BITMAPINDEX_WIN2,
	BITMAPINDEX_DIE
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

	float				m_X;
	float				m_Y;
	float				m_CameraX;

	RECT				m_Collision;

	float				m_Speed;

	int					m_BitmapIndex;

	float				m_AnimMoveForwardTime;
	float				m_AnimMoveBackTime;
	float				m_StartAnimTimer;
	float				m_CurAnimTimer;

	STATE				m_State;

	bool				m_bIsJump;
	float				m_JumpForce;
	float				m_JumpY;
	float				m_JumpTime;
	float				m_JumpSpeed;

	int					m_FieldIndex;

public:
	Player();
	~Player();
	
	void Init(HDC BackDC);
	void Update(int FieldIndex);
	void Input();
	void Draw(float x, float y);
	void Move(float x, float y);
	void StopAnim();
	void AnimMoveForward();
	void AnimMoveBack();
	void Jump();

public:
	inline RECT GetCollision()
	{
		return m_Collision;
	}

	inline float GetPlayerX()
	{
		return m_X;
	}

	inline float GetCameraX()
	{
		return m_CameraX;
	}
};

