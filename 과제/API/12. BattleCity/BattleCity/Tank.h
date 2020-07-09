#pragma once
#include "Missile.h"

enum BITMAPINDEX
{
	BITMAPINDEX_DOWN00,
	BITMAPINDEX_DOWN01,
	BITMAPINDEX_LEFT00,
	BITMAPINDEX_LEFT01,
	BITMAPINDEX_RIGHT00,
	BITMAPINDEX_RIGHT01,
	BITMAPINDEX_UP00,
	BITMAPINDEX_UP01
};

enum STATE
{
	STATE_IDLE,
	STATE_MOVE,
	STATE_ATTACK,
	STATE_DIE
};

enum TANKTYPE
{
	TANKTYPE_PLAYER,
	TANKTYPE_ENEMY
};

class Tank
{
protected:
	HDC					m_MemDC;

	Bitmap				m_TankBitmap[8];
	int						m_BitmapIndex;

	STATE					m_State;
	DIRECTION			m_CurDirection;
	DIRECTION			m_BeforeDirection;
	TANKTYPE			m_TankType;

	POINT					m_Point;
	Collision				m_MainCollision;
	Collision				m_DirectionCollision[4];

	float					m_AnimTime;
	float					m_StartAnimTimer;
	float					m_CurAnimTimer;

	bool					m_bIsAlive;
	bool					m_bIsSpawn;

	int						m_Speed;
	bool					m_bMoveable;

	Missile*				m_Missile;
	bool					m_bIsFire;

public:
	Tank();
	virtual ~Tank();

public:
	void Init();
	void Move(int x, int y);
	void Draw();
	void PlayAnim();
	void Spawn(POINT Point);
	void SetTankCollision(POINT Point);
	void Fire();
	virtual void GetHit() = 0;

	BITMAPINDEX SetBitmapIndex(DIRECTION Direction);

public:
	inline Collision GetMainCollision()
	{
		return m_MainCollision;
	}
	inline Collision GetDirectionCollision(DIRECTION Direction)
	{
		return m_DirectionCollision[Direction];
	}

	inline DIRECTION GetCurDirection()
	{
		return m_CurDirection;
	}

	inline bool GetAliveFlag()
	{
		return m_bIsAlive;
	}
	inline void SetAliveFlag(bool bFlag)
	{
		m_bIsAlive = bFlag;
	}

	inline bool GetSpawnFlag()
	{
		return m_bIsSpawn;
	}
	inline void SetSpawnFlag(bool bFlag)
	{
		m_bIsSpawn = bFlag;
	}

	inline POINT GetPoint()
	{
		return m_Point;
	}

	inline TANKTYPE GetTankType()
	{
		return m_TankType;
	}

	inline Missile* GetMissile()
	{
		return m_Missile;
	}

	inline int GetIndex()
	{
		return m_BitmapIndex;
	}
	inline int GetStart()
	{
		return m_StartAnimTimer;
	}
	inline int GetCur()
	{
		return m_CurAnimTimer;
	}
};

class Player : public Tank
{
private:
	int		m_Life;

public:
	Player();
	virtual ~Player();

public:
	void Init(HDC MemDC);
	void Input();
	void Update(bool MoveableFlag, bool ExitFlag);
	void GetHit();

public:
	inline int GetLife()
	{
		return m_Life;
	}
};

class Enemy : public Tank
{
private:
	int			m_TankNum;

	float					m_FireTime;
	float					m_StartFireTimer;
	float					m_CurFireTimer;

public:
	Enemy();
	virtual ~Enemy();

public:
	void Init(HDC MemDC, int TankNum);
	void Update(bool MoveableFlag);
	void GetHit();
	void Fire();
	void SearchMove();

public:
	inline int GetTankNum()
	{
		return m_TankNum;
	}
};

