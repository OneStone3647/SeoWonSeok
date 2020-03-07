#pragma once
#include "Bitmap.h"
#include <math.h>

enum STATE
{
	STATE_IDLE,
	STATE_MOVE,
	STATE_JUMP,
	STATE_LEFTJUMP,
	STATE_RIGHTJUMP,
	STATE_WIN,
	STATE_DIE
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
	HDC					m_MemDC;

	Bitmap				m_PlayerBitmap[6];
	int						m_BitmapIndex;

	STATE					m_State;

	float					m_X;
	float					m_Y;
	float					m_CameraX;
	int*					m_FieldIndex;
	float					m_Speed;
	bool*					m_bWinFlag;

	RECT					m_Collision;

	float					m_AnimMoveForwardTime;
	float					m_AnimMoveBackTime;
	float					m_AnimWinTime;
	float					m_StartAnimTimer;
	float					m_CurAnimTimer;

	bool					m_bIsJump;
	float					m_JumpForce;
	float					m_JumpY;
	float					m_JumpTime;
	float					m_JumpSpeed;

public:
	Player();
	~Player();

public:
	void Init(HDC MemDC);
	void Update(int* FieldIndex, bool* bWinFlag, float EndX, float EndY);
	void Input();
	void Draw(float x, float y);
	void Move(float x, float y);
	void SetCollision();

	void StopAnim();
	void AnimMoveForward();
	void AnimMoveBack();

	void Jump();
	void Win(float x, float y);
	void Die();

public:
	inline RECT GetCollision()
	{
		return m_Collision;
	}

	inline float GetCameraX()
	{
		return m_CameraX;
	}
};

