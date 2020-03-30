#pragma once
#include "Mecro.h"

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

public:
	inline RECT GetCollision()
	{
		return m_Collision;
	}
	inline void SetCollision(int x, int y)
	{
		m_Collision = { BlockSizeX * x, BlockSizeY * y,	BlockSizeX * (x + 1), BlockSizeY * (y + 1) };
	}
};

