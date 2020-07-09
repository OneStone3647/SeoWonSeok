#include "FlightStar.h"
#include "ResoucesManager.h"
#include "defines.h"



FlightStar::FlightStar()
{
}


FlightStar::~FlightStar()
{
}

void FlightStar::Init()
{
	m_bIsSpawn = false;
	m_X = 0;
	m_Y = 0;
	SetScore(SCORE_100);
	m_Speed = 100;

	srand((unsigned int)time(NULL));
	int random = GetTickCount() % 8;
	m_Direction = (DIRECTION)random;
}

void FlightStar::SetScore(int scoreIndex)
{
	switch (scoreIndex)
	{
	case SCORE_100:
		ObjectBitmap = JEngine::ResoucesManager::GetInstance()->GetBitmap("Bitmap\\FlightGameStar1.bmp");
		m_Score = 100;
		break;
	case SCORE_1400:
		ObjectBitmap = JEngine::ResoucesManager::GetInstance()->GetBitmap("Bitmap\\FlightGameStar2.bmp");
		m_Score = 1400;
		break;
	}
	ObjectBitmap->SetAnchor(JEngine::ANCHOR_CENTER);
	SetCollision(m_X, m_Y);
}
