#pragma once
#include "Bitmap.h"
#include <math.h>

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

	Bitmap					m_LifeBitmap;
	int						m_Life;

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

	void DrawLife(float x, float y);

public:
	inline RECT GetCollision()
	{
		return m_Collision;
	}

	inline float GetCameraX()
	{
		return m_CameraX;
	}
	inline void SetCameraX(float x)
	{
		m_CameraX = x;
	}

	inline bool GetJumpFlag()
	{
		return m_bIsJump;
	}
	inline STATE GetState()
	{
		return m_State;
	}
	inline int GetLife()
	{
		return m_Life;
	}
	inline void SetLife(int life)
	{
		m_Life = life;
	}
};

