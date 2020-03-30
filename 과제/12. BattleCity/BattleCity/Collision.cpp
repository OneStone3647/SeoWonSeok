#include "Collision.h"



Collision::Collision()
{
}


Collision::~Collision()
{
}

// 타겟의 콜리전과 겹치는지 체크한다.
bool Collision::CheckOverlap(RECT TargetCollision)
{
	// 교집합 Rect
	RECT tmpRect;

	if (IntersectRect(&tmpRect, &m_Collision, &TargetCollision))
	{
		return true;
	}

	return false;
}

bool Collision::CheckMouseHit(POINT MousePoint)
{
	if (PtInRect(&m_Collision, MousePoint))
	{
		return true;
	}

	return false;
}
