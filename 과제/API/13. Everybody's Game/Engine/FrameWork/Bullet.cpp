#include "Bullet.h"
#include "ResoucesManager.h"
#include "defines.h"



Bullet::Bullet()
{
}


Bullet::~Bullet()
{
}

void Bullet::Init()
{
	m_bIsSpawn = false;
	ObjectBitmap = JEngine::ResoucesManager::GetInstance()->GetBitmap("Bitmap\\FlightGameBullet.bmp");
	ObjectBitmap->SetAnchor(JEngine::ANCHOR_CENTER);
	m_X = 0;
	m_Y = 0;
	SetCollision(m_X, m_Y);
	m_Speed = 100;

	srand((unsigned int)time(NULL));
	int random = GetTickCount() % 8;
	m_Direction = (DIRECTION)random;
}
