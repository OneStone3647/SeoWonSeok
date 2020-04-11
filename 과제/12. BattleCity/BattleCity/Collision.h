#pragma once
#include "Mecro.h"

enum COLLISIONTYPE
{
	COLLISIONTYPE_UP,
	COLLISIONTYPE_LEFT,
	COLLISIONTYPE_DOWN,
	COLLISIONTYPE_RIGHT
};

class Collision
{
private:
	RECT		m_Collision;

public:
	Collision();
	~Collision();

public:
	bool CheckOverlap(RECT TargetCollision);
	bool CheckMouseHit(POINT MousePoint);
	void SetCollision(int x, int y, COLLISIONTYPE CollisionType);

public:
	inline RECT GetCollision()
	{
		return m_Collision;
	}
	inline void SetCollision(int x, int y, LONG Size = 1.0f)
	{
		m_Collision = { x, y,	 (BlockSizeX + x) * Size, (BlockSizeY + y) * Size };
	}

	inline void DrawCollision(HDC MemDC)
	{
		Rectangle(MemDC, m_Collision.left, m_Collision.top, m_Collision.right, m_Collision.bottom);
	}
};

