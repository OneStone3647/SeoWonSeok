#pragma once
#include "Bitmap.h"

class Object
{
protected:
	HDC			m_MemDC;

	RECT			m_Collision;
	RECT			m_ScoreCollision;

	float			m_X;
	float			m_Y;

	float			m_AnimTime;
	float			m_StartAnimTimer;
	float			m_CurAnimTimer;

public:
	Object();
	virtual ~Object();

public:
	virtual void Init(HDC MemDC) = 0;
	virtual void SetCollision(float CameraX = 0.0f) = 0;
	virtual void SetScoreCollision(float CameraX = 0.0f) = 0;

public:
	inline RECT GetCollision()
	{
		return m_Collision;
	}

	inline RECT GetScoreCollision()
	{
		return m_ScoreCollision;
	}
};

enum FRONTINDEX
{
	FRONTINDEX_1,
	FRONTINDEX_2
};

class Front : public Object
{
private:
	Bitmap		m_FrontBitmap[2];
	int				m_FrontIndex;

public:
	void Init(HDC MemDC);
	void Update(float* CameraX, int FieldIndex, float FieldWidth);
	void SetCollision(float CameraX = 0.0f);
	void SetScoreCollision(float CameraX = 0.0f);
};

enum ENEMYINDEX
{
	ENEMYINDEX_ENEMY1_B,
	ENEMYINDEX_ENEMY1_F,
	ENEMYINDEX_ENEMY2_B,
	ENEMYINDEX_ENEMY2_F,
	ENEMYINDEX_ENEMY_L_B,
	ENEMYINDEX_ENEMY_L_F,
};

class Enemy : public Object
{
private:
	Bitmap		m_EnemyBitmap[6];
	int				m_EnemyIndex;

	bool			m_bHaveMoney;

public:
	void Init(HDC MemDC);
	void Update(float* CameraX, int FieldIndex, float FieldWidth);
	void FrontDraw(float* CameraX);
	void BackDraw(float* CameraX);
	void SetCollision(float CameraX = 0.0f);
	void SetScoreCollision(float CameraX = 0.0f);
};

