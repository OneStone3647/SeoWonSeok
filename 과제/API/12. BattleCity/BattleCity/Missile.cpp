#include "Missile.h"



Missile::Missile()
{
}


Missile::~Missile()
{
}

void Missile::Init()
{
	m_bIsAlive = false;
	m_bIsExplosion = false;

	m_Speed = 4;

	m_ExplosionIndex = 0;
	m_ExplosionCount = 0;
}

void Missile::Init(HDC MemDC, MISSILEKIND MissileKind)
{
	Init();
	m_MemDC = MemDC;

	m_MissileBitmap.Init(m_MemDC, "Bitmap\\missile_00.bmp");

	m_MissileKind = MissileKind;

	m_Explosion[0].Init(m_MemDC, "Bitmap\\explosion_00.bmp");
	m_Explosion[1].Init(m_MemDC, "Bitmap\\explosion_01.bmp");
	m_Explosion[2].Init(m_MemDC, "Bitmap\\explosion_02.bmp");
	m_Explosion[3].Init(m_MemDC, "Bitmap\\explosion_03.bmp");
	m_Explosion[4].Init(m_MemDC, "Bitmap\\explosion_04.bmp");

	m_AnimTime = 100.0f;
	m_StartAnimTimer = GetTickCount();
	m_CurAnimTimer = 0.0f;
}

void Missile::Spawn(DIRECTION Direction, int x, int y)
{
	m_bIsAlive = true;
	m_Direction = Direction;
	switch (m_Direction)
	{
	case DIRECTION_DOWN:
		m_Point.x = x - 10;
		m_Point.y = y;
		break;
	case DIRECTION_LEFT:
		m_Point.x = x;
		m_Point.y = y - 4;
		break;
	case DIRECTION_RIGHT:
		m_Point.x = x;
		m_Point.y = y - 4;
		break;
	case DIRECTION_UP:
		m_Point.x = x - 10;
		m_Point.y = y;
		break;
	}
}

void Missile::Update()
{
	m_CurAnimTimer = GetTickCount();

	if (m_bIsAlive)
	{
		if (!m_bIsExplosion)
		{
			switch (m_Direction)
			{
			case DIRECTION_DOWN:
				Move(0, m_Speed);
				break;
			case DIRECTION_LEFT:
				Move(-m_Speed, 0);
				break;
			case DIRECTION_RIGHT:
				Move(m_Speed, 0);
				break;
			case DIRECTION_UP:
				Move(0, -m_Speed);
				break;
			}
		}
		else
		{
			m_Collision.SetCollision(0, 0);
		}

		if (m_ExplosionCount > 2)
		{
			m_bIsAlive = false;
			m_bIsExplosion = false;
			m_ExplosionCount = 0;
		}
	}
}

void Missile::Move(int x, int y)
{
	m_Point.x += x;
	m_Point.y += y;
	RECT tmpRect = { m_Point.x, m_Point.y, m_Point.x + m_MissileBitmap.GetSize().cx + 10, m_Point.y + m_MissileBitmap.GetSize().cy + 10 };
	m_Collision.SetCollision(tmpRect);
}

void Missile::Draw()
{
	//m_Collision.DrawCollision(m_MemDC);
	if (m_bIsAlive)
	{
		if (!m_bIsExplosion)
		{
			m_MissileBitmap.Draw(m_MemDC, m_Point.x, m_Point.y, 2.0f);
		}
		else
		{
			if (m_CurAnimTimer - m_StartAnimTimer >= m_AnimTime)
			{
				m_ExplosionIndex++;
				if (m_ExplosionIndex > 2)
				{
					m_ExplosionIndex = 0;
					m_ExplosionCount++;
				}

				m_StartAnimTimer = m_CurAnimTimer;
			}

			POINT tmpPoint;
			switch (m_Direction)
			{
			case DIRECTION_DOWN:
				tmpPoint.x = m_Point.x - 25;
				tmpPoint.y = m_Point.y - 25;
				break;
			case DIRECTION_LEFT:
				tmpPoint.x = m_Point.x - 30;
				tmpPoint.y = m_Point.y - 22;
				break;
			case DIRECTION_RIGHT:
				tmpPoint.x = m_Point.x - 30;
				tmpPoint.y = m_Point.y - 22;
				break;
			case DIRECTION_UP:
				tmpPoint.x = m_Point.x - 25;
				tmpPoint.y = m_Point.y - 25;
				break;
			}

			m_Explosion[m_ExplosionIndex].Draw(m_MemDC, tmpPoint.x, tmpPoint.y, 2.0f);
		}
	}	
}
