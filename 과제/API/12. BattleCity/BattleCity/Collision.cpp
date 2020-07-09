#include "Collision.h"



Collision::Collision()
{
}


Collision::~Collision()
{
}

// Ÿ���� �ݸ����� ��ġ���� üũ�Ѵ�.
bool Collision::CheckOverlap(RECT TargetCollision)
{
	// ������ Rect
	RECT tmpRect;

	if (IntersectRect(&tmpRect, &m_Collision, &TargetCollision))
	{
		return true;
	}

	return false;
}

bool Collision::CheckOverlapPoint(POINT TargetPoint)
{
	if (PtInRect(&m_Collision, TargetPoint))
	{
		return true;
	}

	return false;
}

void Collision::SetCollision(int x, int y, COLLISIONTYPE CollisionType)
{
	switch (CollisionType)
	{
	case COLLISIONTYPE_UP:
		m_Collision = { x, y,	 x + BlockSizeX, y + BlockSizeY / 2 };
		break;
	case COLLISIONTYPE_LEFT:
		m_Collision = { x, y,	 x + BlockSizeX / 2, y + BlockSizeY };
		break;
	case COLLISIONTYPE_DOWN:
		m_Collision = { x, y + BlockSizeY / 2, x + BlockSizeX, y + BlockSizeY };
		break;
	case COLLISIONTYPE_RIGHT:
		m_Collision = { x + BlockSizeX / 2, y, x + BlockSizeX, y + BlockSizeY };
		break;
	}
}
