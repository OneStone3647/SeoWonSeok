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

	m_State = PLAYERSTATE_MOVEUP;

	m_AnimTime = 100.0f;
	m_StartAnimTimer = GetTickCount();
	m_CurAnimTimer = 0.0f;

	SetPlayerPoint(0, 0);
}

void Player::Update()
{
	m_CurAnimTimer = GetTickCount();

	Input();
	Draw();
}

void Player::Input()
{
	if (GetKeyState(VK_DOWN) & 0x8000)
	{
		m_State = PLAYERSTATE_MOVEDOWN;
		Move(0, 1);
	}	
	if (GetKeyState(VK_LEFT) & 0x8000)
	{
		m_State = PLAYERSTATE_MOVELEFT;
		Move(-1, 0);
	}
	if (GetKeyState(VK_RIGHT) & 0x8000)
	{
		m_State = PLAYERSTATE_MOVERIGHT;
		Move(1, 0);
	}
	if (GetKeyState(VK_UP) & 0x8000)
	{
		m_State = PLAYERSTATE_MOVEUP;
		Move(0, -1);
	}
	if (!((GetKeyState(VK_DOWN) | GetKeyState(VK_LEFT) | GetKeyState(VK_RIGHT) | GetKeyState(VK_UP)) & 0x8000))
	{
		m_State = PLAYERSTATE_IDLE;
	}
}

void Player::Move(float x, float y)
{
	m_Point.x += x;
	m_Point.y += y;
	PlayAnim();
}

void Player::Draw()
{
	m_PlayerBitmap[m_PlayerBitmapIndex].Draw(m_MemDC, m_Point.x, m_Point.y);
}

void Player::PlayAnim()
{
	if (m_State != PLAYERSTATE_IDLE)
	{
		int tmpIndex;
		switch (m_State)
		{
		case PLAYERSTATE_MOVEDOWN:
			if (!(m_PlayerBitmapIndex == PLAYERINDEX_DOWN00 || m_PlayerBitmapIndex == PLAYERINDEX_DOWN01))
			{
				tmpIndex = PLAYERINDEX_DOWN00;
				m_PlayerBitmapIndex = tmpIndex;
			}
			break;
		case PLAYERSTATE_MOVELEFT:
			break;
		case PLAYERSTATE_MOVERIGHT:
			break;
		case PLAYERSTATE_MOVEUP:
			break;
		}

		if (m_CurAnimTimer - m_StartAnimTimer >= m_AnimTime)
		{
			m_PlayerBitmapIndex++;
			if (tmpIndex > 2)
			{
				m_BitmapIndex = 0;
			}
			m_StartAnimTimer = m_CurAnimTimer;
		}
	}
}
