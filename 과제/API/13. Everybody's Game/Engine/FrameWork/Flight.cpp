#include "Flight.h"
#include "ResoucesManager.h"
#include "defines.h"



Flight::Flight()
{
}


Flight::~Flight()
{
}

void Flight::Init()
{
	m_bIsHit = false;
	ObjectBitmap = JEngine::ResoucesManager::GetInstance()->GetBitmap("Bitmap\\FlightGameFlight.bmp");
	ObjectBitmap->SetAnchor(JEngine::ANCHOR_CENTER);

	char buf[256];
	for (int i = 0; i < 3; i++)
	{
		sprintf(buf, "Bitmap\\explosion%d.bmp", i + 1);
		m_Explosion[i] = JEngine::ResoucesManager::GetInstance()->GetBitmap(buf);
		m_Explosion[i]->SetAnchor(JEngine::ANCHOR_CENTER);
	}

	m_X = WindowX / 2;
	m_Y = WindowY / 2;
	m_Speed = 200;
	SetCollision(m_X, m_Y);

	m_BitmapIndex = 0;
	m_AnimTime = 100.0f;
	m_StartAnimTimer = GetTickCount();
	m_CurAnimTimer = 0.0f;
}

void Flight::Draw()
{
	if (!m_bIsHit)
	{
		ObjectBitmap->Draw((int)m_X, (int)m_Y);
	}
	else
	{
		m_CurAnimTimer = GetTickCount();
		PlayAnim();
		m_Explosion[m_BitmapIndex]->Draw((int)m_X, (int)m_Y);
	}
}

void Flight::Move(float x, float y)
{
	m_X += x * m_Speed;
	m_Y += y * m_Speed;
	SetCollision(m_X, m_Y);
}

void Flight::SetCollision(float x, float y)
{
	m_Collision.left = m_X - (ObjectBitmap->GetWidth() / 4);
	m_Collision.right = m_X + (ObjectBitmap->GetWidth() / 4);
	m_Collision.top = m_Y - (ObjectBitmap->GetHeight() / 4);
	m_Collision.bottom = m_Y + (ObjectBitmap->GetHeight() / 4);
}

void Flight::PlayAnim()
{
	if (m_CurAnimTimer - m_StartAnimTimer >= m_AnimTime)
	{
		m_BitmapIndex++;
		if (m_BitmapIndex > 2)
		{
			m_BitmapIndex = 0;
		}

		m_StartAnimTimer = m_CurAnimTimer;
	}
}
