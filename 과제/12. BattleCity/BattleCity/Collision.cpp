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
