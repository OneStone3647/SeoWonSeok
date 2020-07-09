#pragma once
#include "Bitmap.h"
#include "Collision.h"

enum MISSILEKIND
{
	MISSILEKIND_PLAYER,
	MISSILEKIND_ENEMY
};

class Missile
{
private:
	HDC				m_MemDC;
	MISSILEKIND		m_MissileKind;
	POINT				m_Point;
	Collision			m_Collision;
	Bitmap			m_MissileBitmap;
	Bitmap			m_Explosion[5];
	int					m_ExplosionIndex;
	int					m_ExplosionCount;

	DIRECTION		m_Direction;

	bool				m_bIsAlive;
	bool				m_bIsExplosion;

	int					m_Speed;

	float				m_AnimTime;
	float				m_StartAnimTimer;
	float				m_CurAnimTimer;

public:
	Missile();
	~Missile();

public:
	void Init();
	void Init(HDC MemDC, MISSILEKIND MissileKind);
	void Spawn(DIRECTION Direction, int x, int y);
	void Update();
	void Move(int x, int y);
	void Draw();

public:
	inline Collision GetCollision()
	{
		return m_Collision;
	}

	inline bool GetAliveFlag()
	{
		return m_bIsAlive;
	}
	inline void SetAliveFlag(bool bFlag)
	{
		m_bIsAlive = bFlag;
	}

	inline bool GetExplosionFlag()
	{
		return m_bIsExplosion;
	}
	inline void SetExplosionFlag(bool bFlag)
	{
		m_bIsExplosion = bFlag;
	}

	inline MISSILEKIND GetMissileKind()
	{
		return m_MissileKind;
	}

	inline DIRECTION GetDirection()
	{
		return m_Direction;
	}
};

