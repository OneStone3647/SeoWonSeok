#include "Tank.h"



Tank::Tank()
{
}


Tank::~Tank()
{
}

void Tank::Init()
{
	m_State = STATE_IDLE;
	m_CurDirection = DIRECTION_UP;
	m_BeforeDirection = m_CurDirection;

	m_AnimTime = 100.0f;
	m_StartAnimTimer = GetTickCount();
	m_CurAnimTimer = 0.0f;

	m_bIsAlive = true;
	m_bIsSpawn = false;

	m_Speed = 2;
	m_bMoveable = true;

	m_Point = { 0, 0 };
}

void Tank::Move(int x, int y)
{
	if (m_bMoveable)
	{
		m_Point.x += x;
		m_Point.y += y;
		SetTankCollision(m_Point);
		m_CurAnimTimer = GetTickCount();
		PlayAnim();
	}
}

void Tank::Draw()
{
	if (m_bIsSpawn)
	{
		//m_MainCollision.DrawCollision(m_MemDC);
		//for (int i = 0; i < 4; i++)
		//{
		//	m_DirectionCollision[i].DrawCollision(m_MemDC);
		//}
		m_TankBitmap[m_BitmapIndex].Draw(m_MemDC, m_Point.x, m_Point.y, 2.0f);
	}
}

void Tank::PlayAnim()
{
	if (m_CurAnimTimer - m_StartAnimTimer >= m_AnimTime)
	{
		m_BitmapIndex++;

		switch (m_CurDirection)
		{
		case DIRECTION_DOWN:
			if (m_BitmapIndex > BITMAPINDEX_DOWN01)
			{
				m_BitmapIndex = BITMAPINDEX_DOWN00;
			}
			break;
		case DIRECTION_LEFT:
			if (m_BitmapIndex > BITMAPINDEX_LEFT01)
			{
				m_BitmapIndex = BITMAPINDEX_LEFT00;
			}
			break;
		case DIRECTION_RIGHT:
			if (m_BitmapIndex > BITMAPINDEX_RIGHT01)
			{
				m_BitmapIndex = BITMAPINDEX_RIGHT00;
			}
			break;
		case DIRECTION_UP:
			if (m_BitmapIndex > BITMAPINDEX_UP01)
			{
				m_BitmapIndex = BITMAPINDEX_UP00;
			}
			break;
		}

		m_StartAnimTimer = m_CurAnimTimer;
	}
}

void Tank::Spawn(POINT Point)
{
	Init();
	m_bIsSpawn = true;
	m_Point = { Point.x, Point.y };
	SetTankCollision(Point);
}

void Tank::SetTankCollision(POINT Point)
{
	m_MainCollision.SetCollision(Point.x, Point.y, 1.0f);
	m_DirectionCollision[DIRECTION_DOWN].SetCollision(Point.x + 4, (int)(Point.y + BlockSizeY * 1.0f), (int)(Point.x + BlockSizeX * 1.0f) - 4, (int)(Point.y + BlockSizeY * 1.0f) + 2);
	m_DirectionCollision[DIRECTION_LEFT].SetCollision(Point.x - 2, Point.y + 4, Point.x, (int)(Point.y + BlockSizeY * 1.0f) - 4);
	m_DirectionCollision[DIRECTION_RIGHT].SetCollision((int)(Point.x + BlockSizeX * 1.0f), Point.y + 4, (int)(Point.x + BlockSizeX * 1.0f) + 2, (int)(Point.y + BlockSizeY * 1.0f) - 4);
	m_DirectionCollision[DIRECTION_UP].SetCollision(Point.x + 4, Point.y - 2, (int)(Point.x + BlockSizeX * 1.0f) - 4, Point.y);
}

void Tank::Fire()
{
	if (!m_bIsFire)
	{
		POINT tmpPoint;
		RECT DirectionCollisionRect = GetDirectionCollision(m_CurDirection).GetRect();
		tmpPoint = { DirectionCollisionRect.left + (DirectionCollisionRect.right - DirectionCollisionRect.left) / 2, DirectionCollisionRect.top + (DirectionCollisionRect.bottom - DirectionCollisionRect.top) / 2 };
		m_Missile->Spawn(m_CurDirection, tmpPoint.x, tmpPoint.y);
	}
}

BITMAPINDEX Tank::SetBitmapIndex(DIRECTION Direction)
{
	switch (Direction)
	{
	case DIRECTION_DOWN:
		return BITMAPINDEX_DOWN00;
	case DIRECTION_LEFT:
		return BITMAPINDEX_LEFT00;
	case DIRECTION_RIGHT:
		return BITMAPINDEX_RIGHT00;
	case DIRECTION_UP:
		return BITMAPINDEX_UP00;
	}
}

Player::Player()
{
}

Player::~Player()
{
}

void Player::Init(HDC MemDC)
{
	Tank::Init();

	m_MemDC = MemDC;

	m_TankBitmap[BITMAPINDEX_DOWN00].Init(m_MemDC, "Bitmap\\tank_down_00.bmp");
	m_TankBitmap[BITMAPINDEX_DOWN01].Init(m_MemDC, "Bitmap\\tank_down_01.bmp");
	m_TankBitmap[BITMAPINDEX_LEFT00].Init(m_MemDC, "Bitmap\\tank_left_00.bmp");
	m_TankBitmap[BITMAPINDEX_LEFT01].Init(m_MemDC, "Bitmap\\tank_left_01.bmp");
	m_TankBitmap[BITMAPINDEX_RIGHT00].Init(m_MemDC, "Bitmap\\tank_right_00.bmp");
	m_TankBitmap[BITMAPINDEX_RIGHT01].Init(m_MemDC, "Bitmap\\tank_right_01.bmp");
	m_TankBitmap[BITMAPINDEX_UP00].Init(m_MemDC, "Bitmap\\tank_up_00.bmp");
	m_TankBitmap[BITMAPINDEX_UP01].Init(m_MemDC, "Bitmap\\tank_up_01.bmp");
	m_BitmapIndex = SetBitmapIndex(m_CurDirection);

	m_Life = 2;
	m_TankType = TANKTYPE_PLAYER;

	m_Missile = NULL;
	if (m_Missile != NULL)
	{
		delete m_Missile;
	}
	m_Missile = new Missile;
	m_Missile->Init(m_MemDC, MISSILEKIND_PLAYER);
	m_bIsFire = false;
}

void Player::Input()
{
	if (GetKeyState(VK_DOWN) & 0x8000)
	{
		m_CurDirection = DIRECTION_DOWN;
		if (m_BeforeDirection != m_CurDirection)
		{
			m_BitmapIndex = SetBitmapIndex(m_CurDirection);
		}
		m_State = STATE_MOVE;
		m_BeforeDirection = m_CurDirection;
		Move(0, m_Speed);
	}
	else if (GetKeyState(VK_LEFT) & 0x8000)
	{
		m_CurDirection = DIRECTION_LEFT;
		if (m_BeforeDirection != m_CurDirection)
		{
			m_BitmapIndex = SetBitmapIndex(m_CurDirection);
		}
		m_State = STATE_MOVE;
		m_BeforeDirection = m_CurDirection;
		Move(-m_Speed, 0);
	}
	else if (GetKeyState(VK_RIGHT) & 0x8000)
	{
		m_CurDirection = DIRECTION_RIGHT;
		if (m_BeforeDirection != m_CurDirection)
		{
			m_BitmapIndex = SetBitmapIndex(m_CurDirection);
		}
		m_State = STATE_MOVE;
		m_BeforeDirection = m_CurDirection;
		Move(m_Speed, 0);
	}
	else if (GetKeyState(VK_UP) & 0x8000)
	{
		m_CurDirection = DIRECTION_UP;
		if (m_BeforeDirection != m_CurDirection)
		{
			m_BitmapIndex = SetBitmapIndex(m_CurDirection);
		}
		m_State = STATE_MOVE;
		m_BeforeDirection = m_CurDirection;
		Move(0, -m_Speed);
	}

	if (!((GetKeyState(VK_DOWN) | GetKeyState(VK_LEFT) | GetKeyState(VK_RIGHT) | GetKeyState(VK_UP)) & 0x8000))
	{
		m_State = STATE_IDLE;
	}

	if (GetKeyState(VK_SPACE) & 0x8000)
	{
		Fire();
		if (!m_bIsFire)
		{
			m_bIsFire = true;
		}
		if (!m_bIsAlive)
		{
			m_bIsFire = false;
		}
	}
}

void Player::Update(bool MoveableFlag, bool ExitFlag)
{
	m_bMoveable = MoveableFlag;

	if (m_bIsAlive)
	{
		if (!ExitFlag)
		{
			Input();
		}
		Draw();
	}

	if (m_bIsFire)
	{
		m_Missile->Update();
		if (!m_Missile->GetAliveFlag())
		{
			m_bIsFire = false;
		}
	}
}

void Player::GetHit()
{
	m_bIsAlive = false;
	m_Life--;
	if (m_Life <= 0)
	{
		m_bIsSpawn = false;
	}
}

Enemy::Enemy()
{
}

Enemy::~Enemy()
{
}

void Enemy::Init(HDC MemDC, int TankNum)
{
	Tank::Init();

	m_MemDC = MemDC;
	m_TankNum = TankNum;

	m_TankBitmap[BITMAPINDEX_DOWN00].Init(m_MemDC, "Bitmap\\e_down_00.bmp");
	m_TankBitmap[BITMAPINDEX_DOWN01].Init(m_MemDC, "Bitmap\\e_down_01.bmp");
	m_TankBitmap[BITMAPINDEX_LEFT00].Init(m_MemDC, "Bitmap\\e_left_00.bmp");
	m_TankBitmap[BITMAPINDEX_LEFT01].Init(m_MemDC, "Bitmap\\e_left_01.bmp");
	m_TankBitmap[BITMAPINDEX_RIGHT00].Init(m_MemDC, "Bitmap\\e_right_00.bmp");
	m_TankBitmap[BITMAPINDEX_RIGHT01].Init(m_MemDC, "Bitmap\\e_right_01.bmp");
	m_TankBitmap[BITMAPINDEX_UP00].Init(m_MemDC, "Bitmap\\e_up_00.bmp");
	m_TankBitmap[BITMAPINDEX_UP01].Init(m_MemDC, "Bitmap\\e_up_01.bmp");
	m_BitmapIndex = SetBitmapIndex(m_CurDirection);

	m_TankType = TANKTYPE_ENEMY;

	m_Missile = NULL;
	if (m_Missile != NULL)
	{
		delete m_Missile;
	}
	m_Missile = new Missile;
	m_Missile->Init(m_MemDC, MISSILEKIND_ENEMY);
	m_bIsFire = false;

	m_FireTime = 1000.0f;
	m_StartFireTimer = GetTickCount();
	m_CurFireTimer = 0.0f;
}

void Enemy::Update(bool MoveableFlag)
{
	m_CurAnimTimer = GetTickCount();
	m_CurFireTimer = GetTickCount();

	m_bMoveable = MoveableFlag;

	if (m_bIsAlive && m_bIsSpawn)
	{
		Fire();
		SearchMove();
		Draw();
	}

	if (m_bIsFire)
	{
		m_Missile->Update();
		if (!m_Missile->GetAliveFlag())
		{
			m_bIsFire = false;
		}
	}
}

void Enemy::GetHit()
{
	m_bIsSpawn = false;
	m_bIsAlive = false;
}

void Enemy::Fire()
{
	if (m_CurFireTimer - m_StartFireTimer >= m_FireTime)
	{
		Tank::Fire();
		if (!m_bIsFire)
		{
			m_bIsFire = true;
		}
		if (!m_bIsAlive)
		{
			m_bIsFire = false;
		}

		m_StartFireTimer = m_CurFireTimer;
	}
}

void Enemy::SearchMove()
{
	if (m_bMoveable)
	{

		if (m_BeforeDirection != m_CurDirection)
		{
			m_BitmapIndex = SetBitmapIndex(m_CurDirection);
		}
		m_BeforeDirection = m_CurDirection;

		switch (m_CurDirection)
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
		srand(time(NULL));
		int random = rand() % 4;
		m_CurDirection = (DIRECTION)random;
	}
}
