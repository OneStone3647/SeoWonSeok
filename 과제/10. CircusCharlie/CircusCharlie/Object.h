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

	int				m_Score;

public:
	Object();
	virtual ~Object();

public:
	virtual void Init(HDC MemDC) = 0;
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

	inline int GetScore()
	{
		return m_Score;
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
	ENEMYINDEX_ENEMY_L_F
};

class Enemy : public Object
{
private:
	Bitmap		m_EnemyBitmap[4];
	int				m_EnemyIndex;

	Bitmap		m_CashBitmap;
	RECT			m_CashCollision;

	int				m_Speed;

	bool			m_bHaveCash;
	int				m_CashScore;

public:
	void Init(HDC MemDC);
	void Update(STATE PlayerState, float* CameraX, bool* bWinFlag, bool* bExitFlag);
	void SetCollision();
	void SetScoreCollision(float CameraX = 0.0f);
	void SetCashCollision();
	bool CheckCashCollision(RECT PlayerCollision);

public:
	inline void DrawFront()
	{
		m_EnemyBitmap[m_EnemyIndex].Draw(m_MemDC, m_X, m_Y);
	}
	inline void DrawBack()
	{
		m_EnemyBitmap[m_EnemyIndex + 1].Draw(m_MemDC, m_X + m_EnemyBitmap[m_EnemyIndex].GetSize().cx * 1.5f, m_Y);
	}
	inline void DrawCash()
	{
		m_CashBitmap.Draw(m_MemDC, m_X + m_CashBitmap.GetSize().cx * 0.7f, m_Y + 20.0f);
	}

	inline float GetX()
	{
		return m_X;
	}

	inline bool GetCashFlag()
	{
		return m_bHaveCash;
	}
	inline void SetCashFlag(bool bFlag)
	{
		m_bHaveCash = bFlag;
	}

	inline RECT GetCashCollision()
	{
		return m_CashCollision;
	}
	inline int GetCashScore()
	{
		return m_CashScore;
	}
};

