#include "Object.h"



Object::Object()
{
}


Object::~Object()
{
}

void Front::Init(HDC MemDC)
{
	m_MemDC = MemDC;

	m_FrontBitmap[FRONTINDEX_1].Init(m_MemDC, "Bitmap\\front.bmp");
	m_FrontBitmap[FRONTINDEX_2].Init(m_MemDC, "Bitmap\\front2.bmp");
	m_FrontIndex = FRONTINDEX_1;

	m_X = 1450.0f;
	m_Y = 460.0f;

	SetCollision();
	SetScoreCollision();

	m_AnimTime = 100.0f;
	m_StartAnimTimer = GetTickCount();
	m_CurAnimTimer = 0.0f;
}

void Front::Update(float * CameraX, int FieldIndex, float FieldWidth)
{
	m_CurAnimTimer = GetTickCount();

	SetCollision(*CameraX - FieldWidth * FieldIndex);
	SetScoreCollision(*CameraX - FieldWidth * FieldIndex);

	// 디버그용
	Rectangle(m_MemDC, m_Collision.left, m_Collision.top,
		m_Collision.right, m_Collision.bottom);
	//Rectangle(m_MemDC, m_ScoreCollision.left, m_ScoreCollision.top,
	//	m_ScoreCollision.right, m_ScoreCollision.bottom);

	if (m_CurAnimTimer - m_StartAnimTimer >= m_AnimTime)
	{
		m_FrontIndex++;
		if (m_FrontIndex > 1)
		{
			m_FrontIndex = 0;
		}
		m_StartAnimTimer = m_CurAnimTimer;
	}
	m_FrontBitmap[m_FrontIndex].Draw(m_MemDC, m_X - *CameraX - FieldWidth * (-FieldIndex), m_Y);
}

void Front::SetCollision(float CameraX)
{
	m_Collision.left = m_X + m_FrontBitmap[m_FrontIndex].GetSize().cx * 0.3 - CameraX;
	m_Collision.right = m_X + m_FrontBitmap[m_FrontIndex].GetSize().cx * 1.2f - CameraX;
	m_Collision.top = m_Y + m_FrontBitmap[m_FrontIndex].GetSize().cy * 0.4f;
	m_Collision.bottom = m_Y + m_FrontBitmap[m_FrontIndex].GetSize().cy * 1.5f;
}

void Front::SetScoreCollision(float CameraX)
{
	m_ScoreCollision.left = m_X + m_FrontBitmap[m_FrontIndex].GetSize().cx * 1.5f - CameraX;
	m_ScoreCollision.right = m_X + m_FrontBitmap[m_FrontIndex].GetSize().cx * 6.0f - CameraX;
	m_ScoreCollision.top = m_Y + m_FrontBitmap[m_FrontIndex].GetSize().cy * 1.4f;
	m_ScoreCollision.bottom = m_Y + m_FrontBitmap[m_FrontIndex].GetSize().cy * 1.5f;
}

void Enemy::Init(HDC MemDC)
{
	m_MemDC = MemDC;

	m_EnemyBitmap[ENEMYINDEX_ENEMY1_B].Init(m_MemDC, "Bitmap\\enemy_b.bmp");
	m_EnemyBitmap[ENEMYINDEX_ENEMY1_F].Init(m_MemDC, "Bitmap\\enemy_f.bmp");
	m_EnemyBitmap[ENEMYINDEX_ENEMY2_B].Init(m_MemDC, "Bitmap\\enemy_1b.bmp");
	m_EnemyBitmap[ENEMYINDEX_ENEMY2_F].Init(m_MemDC, "Bitmap\\enemy_1f.bmp");
	m_EnemyBitmap[ENEMYINDEX_ENEMY_L_B].Init(m_MemDC, "Bitmap\\enemy_l_b.bmp");
	m_EnemyBitmap[ENEMYINDEX_ENEMY_L_F].Init(m_MemDC, "Bitmap\\enemy_l_f.bmp");
	m_EnemyIndex = ENEMYINDEX_ENEMY1_B;

	m_Speed = -1.0f;

	m_bHaveMoney = false;

	m_X = 1500.0f;
	m_Y = 250.0f;

	SetCollision();
	SetScoreCollision();

	m_AnimTime = 100.0f;
	m_StartAnimTimer = GetTickCount();
	m_CurAnimTimer = 0.0f;
}

void Enemy::Update(STATE PlayerState, float * CameraX, bool * bWinFlag, bool * bExitFlag)
{
	m_CurAnimTimer = GetTickCount();

	SetCollision();
	SetScoreCollision();

	// 디버그용
	Rectangle(m_MemDC, m_Collision.left, m_Collision.top,
		m_Collision.right, m_Collision.bottom);
	Rectangle(m_MemDC, m_ScoreCollision.left, m_ScoreCollision.top,
		m_ScoreCollision.right, m_ScoreCollision.bottom);

	if (m_CurAnimTimer - m_StartAnimTimer >= m_AnimTime)
	{
		m_EnemyIndex += 2;
		if (m_EnemyIndex > 2)
		{
			m_EnemyIndex = 0;
		}
		m_StartAnimTimer = m_CurAnimTimer;
	}

	if (*bExitFlag == false && *bWinFlag == false)
	{
		// 맵의 끝에 도달하지 않았을 경우
		if (*CameraX < LastFieldWidth)
		{
			// 플레이어의 상태에 따라이동 속도를 조절한다.
			if (PlayerState == STATE_MOVERIGHT || PlayerState == STATE_RIGHTJUMP)
			{
				m_Speed = -3.0f;
			}
			else if (PlayerState == STATE_MOVELEFT || PlayerState == STATE_LEFTJUMP)
			{
				m_Speed = 1.0f;
			}
			else
			{
				m_Speed = -2.0f;
			}
		}
		// 맵의 끝에 도달했을 경우
		else
		{
			m_Speed = -2.0f;
		}

		m_X += m_Speed;
	}
}

void Enemy::SetCollision(float CameraX)
{
	m_Collision.left = m_X + m_EnemyBitmap[ENEMYINDEX_ENEMY1_B].GetSize().cx * 0.6f;
	m_Collision.right = m_X + m_EnemyBitmap[ENEMYINDEX_ENEMY1_B].GetSize().cx * 1.6f;
	m_Collision.top = m_Y + m_EnemyBitmap[ENEMYINDEX_ENEMY1_B].GetSize().cy * 1.4f;
	m_Collision.bottom = m_Y + m_EnemyBitmap[ENEMYINDEX_ENEMY1_B].GetSize().cy * 1.5f;
}

void Enemy::SetScoreCollision(float CameraX)
{
	m_ScoreCollision.left = m_X + m_EnemyBitmap[ENEMYINDEX_ENEMY1_B].GetSize().cx * 2.7f;;
	m_ScoreCollision.right = m_X + m_EnemyBitmap[ENEMYINDEX_ENEMY1_B].GetSize().cx * 15.0f;
	m_ScoreCollision.top = m_Y + m_EnemyBitmap[ENEMYINDEX_ENEMY1_B].GetSize().cy * 2.0f;
	m_ScoreCollision.bottom = m_Y + m_EnemyBitmap[ENEMYINDEX_ENEMY1_B].GetSize().cy * 2.1f;
}
