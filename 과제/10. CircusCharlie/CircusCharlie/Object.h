#pragma once
#include "Bitmap.h"

class Object
{
protected:
	HDC				m_BackDC;

	RECT			m_Collision;
	
	float			m_X;
	float			m_Y;

public:
	Object();
	virtual ~Object();

public:
	virtual void Update(float CameraX) = 0;
	void SetCollision(Bitmap* bitmap, float CameraX = 0.0f);

public:
	inline RECT GetCollision()
	{
		return m_Collision;
	}
};

enum ENEMYINDEX
{
	ENEMYINDEX_ENEMY1,
	ENEMYINDEX_ENEMY2
};

enum ENEMYBITMAPINDEX
{
	ENEMYBITMAPINDEX_ENEMY1,
	ENEMYBITMAPINDEX_ENEMY1_B,
	ENEMYBITMAPINDEX_ENEMY1_F,
	ENEMYBITMAPINDEX_ENEMY2,
	ENEMYBITMAPINDEX_ENEMY2_B,
	ENEMYBITMAPINDEX_ENEMY2_F,
	ENEMYBITMAPINDEX_ENEMY_L,
	ENEMYBITMAPINDEX_ENEMY_L_B,
	ENEMYBITMAPINDEX_ENEMY_L_F,
};

class Enemy : public Object
{
private:
	Bitmap			m_EnemyBitmap[9];

	int				m_EnemyIndex;

public:
	void Init(HDC BackDC);
	void Update(float CameraX);
	void Draw(float x, float y);
};

enum FRONTBITMAPINDEX
{
	FRONTBITMAPINDEX_FRONT1,
	FRONTBITMAPINDEX_FRONT2
};

class Front : public Object
{
private:
	Bitmap			m_FrontBitmap[2];

public:
	void Init(HDC BackDC);
	void Update();
};

class Cash : public Object
{
private:
	Bitmap			m_CashBitmap;

public:
	void Init(HDC BackDC);
	void Update();
};
