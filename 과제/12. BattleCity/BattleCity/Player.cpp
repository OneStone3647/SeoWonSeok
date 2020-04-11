#include "Player.h"



Player::Player()
{
}


Player::~Player()
{
}

void Player::Init(HDC MemDC)
{
	m_MemDC = MemDC;

	m_PlayerBitmap[PLAYERINDEX_DOWN00].Init(m_MemDC, "Bitmap\\tank_down_00.bmp");
	m_PlayerBitmap[PLAYERINDEX_DOWN01].Init(m_MemDC, "Bitmap\\tank_down_01.bmp");
	m_PlayerBitmap[PLAYERINDEX_LEFT00].Init(m_MemDC, "Bitmap\\tank_left_00.bmp");
	m_PlayerBitmap[PLAYERINDEX_LEFT01].Init(m_MemDC, "Bitmap\\tank_left_01.bmp");
	m_PlayerBitmap[PLAYERINDEX_RIGHT00].Init(m_MemDC, "Bitmap\\tank_right_00.bmp");
	m_PlayerBitmap[PLAYERINDEX_RIGHT01].Init(m_MemDC, "Bitmap\\tank_right_01.bmp");
	m_PlayerBitmap[PLAYERINDEX_UP00].Init(m_MemDC, "Bitmap\\tank_up_00.bmp");
	m_PlayerBitmap[PLAYERINDEX_UP01].Init(m_MemDC, "Bitmap\\tank_up_01.bmp");
	m_PlayerBitmapIndex = PLAYERINDEX_UP00;

	m_State = PLAYERSTATE_IDLE;
	m_CurPosition = PLAYERSTATE_MOVEUP;

	m_AnimTime = 100.0f;
	m_StartAnimTimer = GetTickCount();
	m_CurAnimTimer = 0.0f;

	m_Speed = 2;

	m_Movealbe = true;
}

void Player::Update(bool Moveable)
{
	m_CurAnimTimer = GetTickCount();

	m_Movealbe = Moveable;

	Input();
	Draw();
}

void Player::Input()
{
	if (GetKeyState(VK_DOWN) & 0x8000)
	{
		m_State = PLAYERSTATE_MOVEDOWN;
		Move(0, m_Speed);
		m_CurPosition = PLAYERSTATE_MOVEDOWN;
	}	
	else if (GetKeyState(VK_LEFT) & 0x8000)
	{
		m_State = PLAYERSTATE_MOVELEFT;
		Move(-m_Speed, 0);
	}
	else if (GetKeyState(VK_RIGHT) & 0x8000)
	{
		m_State = PLAYERSTATE_MOVERIGHT;
		Move(m_Speed, 0);
	}
	else if (GetKeyState(VK_UP) & 0x8000)
	{
		m_State = PLAYERSTATE_MOVEUP;
		Move(0, -m_Speed);
	}

	if (!((GetKeyState(VK_DOWN) | GetKeyState(VK_LEFT) | GetKeyState(VK_RIGHT) | GetKeyState(VK_UP)) & 0x8000))
	{
		m_State = PLAYERSTATE_IDLE;
	}
}

void Player::Move(int x, int y)
{
	if (m_Movealbe)
	{
	}
		m_Point.x += x;
		m_Point.y += y;
		m_Collision.SetCollision(m_Point.x, m_Point.y, 1.7f);
	PlayAnim();
}

void Player::Draw()
{
	m_Collision.DrawCollision(m_MemDC);
	m_PlayerBitmap[m_PlayerBitmapIndex].Draw(m_MemDC, m_Point.x, m_Point.y, 2.0f);
}

void Player::PlayAnim()
{
	if (m_State != PLAYERSTATE_IDLE)
	{
		int tmpIndex;
		if (m_CurAnimTimer - m_StartAnimTimer >= m_AnimTime)
		{
			m_PlayerBitmapIndex++;

			switch (m_State)
			{
			case PLAYERSTATE_MOVEDOWN:
				if (!(m_PlayerBitmapIndex == PLAYERINDEX_DOWN00 || m_PlayerBitmapIndex == PLAYERINDEX_DOWN01))
				{
					m_PlayerBitmapIndex = PLAYERINDEX_DOWN00;
				}
				break;
			case PLAYERSTATE_MOVELEFT:
				if (!(m_PlayerBitmapIndex == PLAYERINDEX_LEFT00 || m_PlayerBitmapIndex == PLAYERINDEX_LEFT01))
				{
					m_PlayerBitmapIndex = PLAYERINDEX_LEFT00;
				}
				break;
			case PLAYERSTATE_MOVERIGHT:
				if (!(m_PlayerBitmapIndex == PLAYERINDEX_RIGHT00 || m_PlayerBitmapIndex == PLAYERINDEX_RIGHT01))
				{
					m_PlayerBitmapIndex = PLAYERINDEX_RIGHT00;
				}
				break;
			case PLAYERSTATE_MOVEUP:
				if (!(m_PlayerBitmapIndex == PLAYERINDEX_UP00 || m_PlayerBitmapIndex == PLAYERINDEX_UP01))
				{
					m_PlayerBitmapIndex = PLAYERINDEX_UP00;
				}
				break;
			}

			m_StartAnimTimer = m_CurAnimTimer;
		}
	}
}

void Player::Spawn(POINT Point)
{
	m_Point = { Point.x, Point.y };
	m_Collision.SetCollision(Point.x, Point.y, 1.7f);
}
