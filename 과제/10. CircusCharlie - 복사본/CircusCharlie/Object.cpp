#include "Object.h"



Object::Object()
{
}


Object::~Object()
{
}

void Enemy::Init(HDC BackDC)
{
	m_BackDC = BackDC;

	m_EnemyBitmap[ENEMYBITMAPINDEX_ENEMY1].Init(m_BackDC, "Bitmap\\enemy.bmp");
	m_EnemyBitmap[ENEMYBITMAPINDEX_ENEMY1_B].Init(m_BackDC, "Bitmap\\enemy_b.bmp");
	m_EnemyBitmap[ENEMYBITMAPINDEX_ENEMY1_F].Init(m_BackDC, "Bitmap\\enemy_f.bmp");
	m_EnemyBitmap[ENEMYBITMAPINDEX_ENEMY2].Init(m_BackDC, "Bitmap\\enemy1.bmp");
	m_EnemyBitmap[ENEMYBITMAPINDEX_ENEMY2_B].Init(m_BackDC, "Bitmap\\enemy_1b.bmp");
	m_EnemyBitmap[ENEMYBITMAPINDEX_ENEMY2_F].Init(m_BackDC, "Bitmap\\enemy_1f.bmp");
	m_EnemyBitmap[ENEMYBITMAPINDEX_ENEMY_L].Init(m_BackDC, "Bitmap\\enemy_l.bmp");
	m_EnemyBitmap[ENEMYBITMAPINDEX_ENEMY_L_B].Init(m_BackDC, "Bitmap\\enemy_l_b.bmp");
	m_EnemyBitmap[ENEMYBITMAPINDEX_ENEMY_L_F].Init(m_BackDC, "Bitmap\\enemy_l_f.bmp");

	m_X = MaxField;
	m_Y = 230.0f;

	m_EnemyBitmapIndex = ENEMYBITMAPINDEX_ENEMY1;

	SetCollision();
	SetScoreCollision();

	m_AnimTime = 100.0f;
	m_StartAnimTimer = GetTickCount();
	m_CurAnimTimer = 0.0f;
}

void Enemy::Update(float CameraX, bool bEndFlag)
{
	m_CurAnimTimer = GetTickCount();

	if (!bEndFlag)
	{
		m_X -= 2.0f;
		m_Collision.left -= 2.0f;
		m_Collision.right -= 2.0f;
	}
	SetCollision(CameraX);

	// 디버그용
	//Rectangle(m_BackDC, m_ScoreCollision.left, m_ScoreCollision.top,
	//	m_ScoreCollision.right, m_ScoreCollision.bottom);
	Rectangle(m_BackDC, m_Collision.left, m_Collision.top,
		m_Collision.right, m_Collision.bottom);

	if (m_CurAnimTimer - m_StartAnimTimer >= m_AnimTime)
	{
		m_EnemyBitmapIndex += 3;
		if (m_EnemyBitmapIndex > 3)
		{
			m_EnemyBitmapIndex = 0;
		}
		m_StartAnimTimer = m_CurAnimTimer;
	}

	m_EnemyBitmap[m_EnemyBitmapIndex].Draw(m_BackDC, m_X - CameraX, m_Y, 2.0f, 2.0f);
}

void Enemy::SetCollision(float CameraX)
{
	m_Collision.left = m_X + m_EnemyBitmap[m_EnemyBitmapIndex].GetSize().cx * 0.3f - CameraX;
	m_Collision.right = m_X + m_EnemyBitmap[m_EnemyBitmapIndex].GetSize().cx * 1.7f - CameraX;
	m_Collision.top = m_Y + m_EnemyBitmap[m_EnemyBitmapIndex].GetSize().cy * 1.8f;
	m_Collision.bottom = m_Y + m_EnemyBitmap[m_EnemyBitmapIndex].GetSize().cy * 2.0f;
}

void Enemy::SetScoreCollision(float CameraX)
{
	m_ScoreCollision.left = m_X + m_EnemyBitmap[m_EnemyBitmapIndex].GetSize().cx * 0.3f - CameraX;
	m_ScoreCollision.right = m_X + m_EnemyBitmap[m_EnemyBitmapIndex].GetSize().cx * 1.7f - CameraX;
	m_ScoreCollision.top = m_Y + m_EnemyBitmap[m_EnemyBitmapIndex].GetSize().cy * 1.8f;
	m_ScoreCollision.bottom = m_Y + m_EnemyBitmap[m_EnemyBitmapIndex].GetSize().cy * 2.0f;
}

void Front::Init(HDC BackDC)
{
	m_BackDC = BackDC;

	m_FrontBitmap[FRONTBITMAPINDEX_FRONT1].Init(m_BackDC, "Bitmap\\front.bmp");
	m_FrontBitmap[FRONTBITMAPINDEX_FRONT2].Init(m_BackDC, "Bitmap\\front2.bmp");

	m_X = 1400;
	m_Y = 460.0f;

	m_FrontBitmapIndex = FRONTBITMAPINDEX_FRONT1;

	SetCollision();
	SetScoreCollision();

	m_AnimTime = 100.0f;
	m_StartAnimTimer = GetTickCount();
	m_CurAnimTimer = 0.0f;
}

void Front::Update(float CameraX, int FieldIndex)
{
	m_CurAnimTimer = GetTickCount();

	SetCollision(CameraX - FieldWidth * (FieldIndex + 2));
	SetScoreCollision(CameraX - FieldWidth * (FieldIndex + 2));

	// 디버그용
	Rectangle(m_BackDC, m_ScoreCollision.left, m_ScoreCollision.top,
		m_ScoreCollision.right, m_ScoreCollision.bottom);
	Rectangle(m_BackDC, m_Collision.left, m_Collision.top,
		m_Collision.right, m_Collision.bottom);

	if (m_CurAnimTimer - m_StartAnimTimer >= m_AnimTime)
	{
		m_FrontBitmapIndex++;
		if (m_FrontBitmapIndex > 1)
		{
			m_FrontBitmapIndex = 0;
		}
		m_StartAnimTimer = m_CurAnimTimer;
	}
	m_FrontBitmap[m_FrontBitmapIndex].Draw(m_BackDC, m_X - CameraX - FieldWidth * (-FieldIndex - 2), m_Y);
}

void Front::SetCollision(float CameraX)
{
	m_Collision.left = m_X - CameraX;
	m_Collision.right = m_X + m_FrontBitmap[m_FrontBitmapIndex].GetSize().cx * 1.5f - CameraX;
	m_Collision.top = m_Y + m_FrontBitmap[m_FrontBitmapIndex].GetSize().cy * 0.3f;
	m_Collision.bottom = m_Y + m_FrontBitmap[m_FrontBitmapIndex].GetSize().cy * 1.5f;
}

void Front::SetScoreCollision(float CameraX)
{
	m_ScoreCollision.left = m_X + m_FrontBitmap[m_FrontBitmapIndex].GetSize().cx * 1.5f  - CameraX;
	m_ScoreCollision.right = m_X + m_FrontBitmap[m_FrontBitmapIndex].GetSize().cx * 6.0f - CameraX;
	m_ScoreCollision.top = m_Y + m_FrontBitmap[m_FrontBitmapIndex].GetSize().cy * 1.4f;
	m_ScoreCollision.bottom = m_Y + m_FrontBitmap[m_FrontBitmapIndex].GetSize().cy * 1.5f;
}
