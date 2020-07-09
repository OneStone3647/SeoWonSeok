#pragma once
#include "GlobalDefine.h"
#include "JEngine.h"
#include <time.h>
#include <stdlib.h>

enum DIRECTION
{
	DIRECTION_UP,
	DIRECTION_DOWN,
	DIRECTION_RIGHT,
	DIRECTION_LEFT,
	DIRECTION_RU,
	DIRECTION_RD,
	DIRECTION_LU,
	DIRECTION_LD
};

enum TYPE
{
	TYPE_BULLET,
	TYPE_STAR
};

class FlightObject
{
protected:
	JEngine::BitMap*	ObjectBitmap;
	JEngine::RECT		m_Collision;

	float				m_X;
	float				m_Y;
	float				m_Speed;

	bool				m_bIsSpawn;

	DIRECTION		m_Direction;

public:
	FlightObject();
	virtual ~FlightObject();

public:
	virtual void Init() = 0;
	void Draw();
	void Move(float x, float y);
	void SetCollision(float x, float y);
	void Spawn(float x, float y);
	void Update(float fETime);

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

	inline bool GetSpawn()
	{
		return m_bIsSpawn;
	}
	inline void SetSpawn(bool bFlag)
	{
		m_bIsSpawn = bFlag;
	}

	inline DIRECTION GetDirection()
	{
		return m_Direction;
	}
	inline void SetDirection(DIRECTION direction)
	{
		m_Direction = direction;
	}
};

