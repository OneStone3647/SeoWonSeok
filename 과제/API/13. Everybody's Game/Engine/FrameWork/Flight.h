#pragma once
#include "GlobalDefine.h"
#include "JEngine.h"

class Flight
{
private:
	JEngine::BitMap*	ObjectBitmap;
	JEngine::RECT		m_Collision;
	JEngine::BitMap*	m_Explosion[3];

	float				m_X;
	float				m_Y;
	float				m_Speed;

	bool				m_bIsHit;

	int					m_BitmapIndex;
	float				m_AnimTime;
	float				m_StartAnimTimer;
	float				m_CurAnimTimer;


public:
	Flight();
	~Flight();

public:
	void Init();
	void Draw();
	void Move(float x, float y);
	void SetCollision(float x, float y);
	void PlayAnim();

public:
	inline JEngine::RECT GetCollision()
	{
		return m_Collision;
	}

	inline float GetX()
	{
		return m_X;
	}
	inline float GetY()
	{
		return m_Y;
	}

	inline float GetSpeed()
	{
		return m_Speed;
	}

	inline JEngine::BitMap* GetBitmap()
	{
		return ObjectBitmap;
	}

	inline void SetHit(bool bFlag)
	{
		m_bIsHit = bFlag;
	}
	inline bool GetHit()
	{
		return m_bIsHit;
	}
};

