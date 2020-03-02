#include "Object.h"



Object::Object()
{
}


Object::~Object()
{
}

void Object::SetCollision(Bitmap * bitmap, float CameraX)
{
	m_Collision.left = m_X - CameraX;
	m_Collision.right = m_X + bitmap->GetSize().cx * 2.0f - CameraX;
	m_Collision.top = m_Y - 50.0f;
	m_Collision.bottom = m_Y + bitmap->GetSize().cy * 2.0f;
}

void Enemy::Init(HDC BackDC)
{
	m_BackDC = BackDC;

	m_EnemyBitmap[ENEMYBITMAPINDEX_ENEMY1].Init(m_BackDC, "Bitmap\\enemy.bmp");
	m_EnemyBitmap[ENEMYBITMAPINDEX_ENEMY1_B].Init(m_BackDC, "Bitmap\\enemy.bmp");
	m_EnemyBitmap[ENEMYBITMAPINDEX_ENEMY1_F].Init(m_BackDC, "Bitmap\\enemy.bmp");
	m_EnemyBitmap[ENEMYBITMAPINDEX_ENEMY2].Init(m_BackDC, "Bitmap\\enemy.bmp");
	m_EnemyBitmap[ENEMYBITMAPINDEX_ENEMY2_B].Init(m_BackDC, "Bitmap\\enemy.bmp");
	m_EnemyBitmap[ENEMYBITMAPINDEX_ENEMY2_F].Init(m_BackDC, "Bitmap\\enemy.bmp");
	m_EnemyBitmap[ENEMYBITMAPINDEX_ENEMY_L].Init(m_BackDC, "Bitmap\\enemy.bmp");
	m_EnemyBitmap[ENEMYBITMAPINDEX_ENEMY_L_B].Init(m_BackDC, "Bitmap\\enemy.bmp");
	m_EnemyBitmap[ENEMYBITMAPINDEX_ENEMY_L_F].Init(m_BackDC, "Bitmap\\enemy.bmp");

	m_X = MaxField;
	m_Y = 230.0f;

	m_EnemyIndex = ENEMYBITMAPINDEX_ENEMY1;

	SetCollision(&m_EnemyBitmap[ENEMYBITMAPINDEX_ENEMY1]);
}

void Enemy::Update(float CameraX)
{
	m_X-=2.0f;
	m_Collision.left -= 2.0f;
	m_Collision.right -= 2.0f;
	SetCollision(&m_EnemyBitmap[m_EnemyIndex], CameraX);

	// 디버그용
	Rectangle(m_BackDC, m_Collision.left, m_Collision.top,
		m_Collision.right, m_Collision.bottom);

	Draw(m_X - CameraX, m_Y);
}

void Enemy::Draw(float x, float y)
{
	m_EnemyBitmap[m_EnemyIndex].Draw(m_BackDC, x, y, 2.0f, 2.0f);
}

void Front::Init(HDC BackDC)
{
	m_BackDC = BackDC;

	m_FrontBitmap[FRONTBITMAPINDEX_FRONT1].Init(m_BackDC, "Bitmap\\front.bmp");
	m_FrontBitmap[FRONTBITMAPINDEX_FRONT2].Init(m_BackDC, "Bitmap\\front2.bmp");
}

void Cash::Init(HDC BackDC)
{
	m_BackDC = BackDC;

	m_CashBitmap.Init(m_BackDC, "Bitmap\\cash.bmp");
}
