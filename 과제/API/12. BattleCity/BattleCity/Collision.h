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
	bool CheckOverlapPoint(POINT TargetPoint);
	void SetCollision(int x, int y, COLLISIONTYPE CollisionType);

public:
	inline RECT GetRect()
	{
		return m_Collision;
	}
	inline void SetCollision(int x, int y, float Size = 1.0f)
	{
		m_Collision = { x, y,	 (int)(x + BlockSizeX * Size), (int)(y + BlockSizeY * Size) };
	}
	inline void SetCollision(RECT Rect)
	{
		m_Collision = { Rect.left, Rect.top, Rect.right, Rect.bottom };
	}
	inline void SetCollision(int left, int top, int right, int bottom)
	{
		m_Collision = { left, top, right, bottom };
	}

	inline void DrawCollision(HDC MemDC)
	{
		Rectangle(MemDC, m_Collision.left, m_Collision.top, m_Collision.right, m_Collision.bottom);
	}
};

