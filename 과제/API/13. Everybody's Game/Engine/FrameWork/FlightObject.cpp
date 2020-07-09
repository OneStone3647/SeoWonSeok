#include "FlightObject.h"



FlightObject::FlightObject()
{
}


FlightObject::~FlightObject()
{
}

void FlightObject::Draw()
{
	if (m_bIsSpawn)
	{
		ObjectBitmap->Draw((int)m_X, (int)m_Y);
	}
}

void FlightObject::Move(float x, float y)
{
	if (m_bIsSpawn)
	{
		m_X += x * m_Speed;
		m_Y += y * m_Speed;
		SetCollision(m_X, m_Y);
	}
}

void FlightObject::SetCollision(float x, float y)
{
	m_Collision.left = m_X - (ObjectBitmap->GetWidth() / 2);
	m_Collision.right = m_X + (ObjectBitmap->GetWidth() / 2);
	m_Collision.top = m_Y - (ObjectBitmap->GetHeight() / 2);
	m_Collision.bottom = m_Y + (ObjectBitmap->GetHeight() / 2);
}

void FlightObject::Spawn(float x, float y)
{
	if (!m_bIsSpawn)
	{
		m_bIsSpawn = true;
		m_X = x;
		m_Y = y;
		SetCollision(m_X, m_Y);
	}
}

void FlightObject::Update(float fETime)
{
	switch (m_Direction)
	{
	case DIRECTION_UP:
		Move(0, -fETime);
		break;
	case DIRECTION_DOWN:
		Move(0, fETime);
		break;
	case DIRECTION_RIGHT:
		Move(fETime, 0);
		break;
	case DIRECTION_LEFT:
		Move(-fETime, 0);
		break;
	case DIRECTION_RU:
		Move(fETime, -fETime);
		break;
	case DIRECTION_RD:
		Move(fETime, fETime);
		break;
	case DIRECTION_LU:
		Move(-fETime, -fETime);
		break;
	case DIRECTION_LD:
		Move(-fETime, fETime);
		break;
	}
}
