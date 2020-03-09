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

	m_PlayerBitmap[BITMAPINDEX_IDLE].Init(m_MemDC, "Bitmap\\player0.bmp");
	m_PlayerBitmap[BITMAPINDEX_MOVE1].Init(m_MemDC, "Bitmap\\player1.bmp");
	m_PlayerBitmap[BITMAPINDEX_MOVE2].Init(m_MemDC, "Bitmap\\player2.bmp");
	m_PlayerBitmap[BITMAPINDEX_WIN1].Init(m_MemDC, "Bitmap\\win.bmp");
	m_PlayerBitmap[BITMAPINDEX_WIN2].Init(m_MemDC, "Bitmap\\win2.bmp");
	m_PlayerBitmap[BITMAPINDEX_DIE].Init(m_MemDC, "Bitmap\\die.bmp");
	m_BitmapIndex = BITMAPINDEX_IDLE;

	m_State = STATE_IDLE;

	m_X = 200.0f;
	m_Y = 440.0f;
	m_CameraX = 200.0f;
	m_Speed = 2.0f;
	//m_Speed = 10.0f;
	
	SetCollision();

	m_AnimMoveForwardTime = 120.0f;
	m_AnimMoveBackTime = 200.0f;
	m_AnimWinTime = 100.0f;
	m_StartAnimTimer = GetTickCount();
	m_CurAnimTimer = 0.0f;

	m_bIsJump = false;
	m_JumpForce = 24.0f;
	m_JumpTime = 0;
	m_JumpY = 0;
	m_JumpSpeed = 2.0f;
}

void Player::Update(int * FieldIndex, bool * bWinFlag, float EndX, float EndY)
{
	m_CurAnimTimer = GetTickCount();
	m_FieldIndex = FieldIndex;
	m_bWinFlag = bWinFlag;

	// 디버그 용
	//Rectangle(m_MemDC, m_Collision.left, m_Collision.top, m_Collision.right, m_Collision.bottom);

	if (!(*m_bWinFlag) && !(m_State == STATE_DIE))
	{
		Input();
		Jump();
	}
	else if (m_State == STATE_DIE)
	{
		Draw(m_X, m_JumpY + m_Y);
	}
	else
	{
		Win(EndX + 95.0f, EndY - 90.0f);
	}
}

void Player::Input()
{
	if (GetKeyState(VK_LEFT) & 0x8000 && m_bIsJump == false)
	{
		m_State = STATE_MOVELEFT;
		Move(-m_Speed, 0.0f);
		AnimMoveBack();
	}
	if (GetKeyState(VK_RIGHT) & 0x8000 && m_bIsJump == false)
	{
		m_State = STATE_MOVERIGHT;
		Move(m_Speed, 0.0f);
		AnimMoveForward();
	}
	if (((GetKeyState(VK_LEFT) & GetKeyState(VK_SPACE)) & 0x8000) && m_bIsJump == false)
	{
		m_State = STATE_LEFTJUMP;
		m_bIsJump = true;
	}
	if (((GetKeyState(VK_RIGHT) & GetKeyState(VK_SPACE)) & 0x8000) && m_bIsJump == false)
	{
		m_State = STATE_RIGHTJUMP;
		m_bIsJump = true;
	}
	if (GetKeyState(VK_SPACE) & 0x8000 && m_bIsJump == false)
	{
		m_State = STATE_JUMP;
		m_bIsJump = true;
	}
	// 멈춘 상태
	if (!((GetKeyState(VK_LEFT) | GetKeyState(VK_RIGHT)) & 0x8000) && m_bIsJump == false)
	{
		m_State = STATE_IDLE;
		StopAnim();
	}
}

void Player::Draw(float x, float y)
{
	m_PlayerBitmap[m_BitmapIndex].Draw(m_MemDC, x, y);
}

void Player::Move(float x, float y)
{
	// 맵의 끝에 도달하지 않았을 경우 플레이어 대신 카메라를 움직인다.
	if (m_CameraX < LastFieldWidth)
	{
		m_CameraX += x;
	}
	else
	{
		m_X += x;
		if (m_X < 200.0f)
		{
			m_X = 200.0f;
			m_CameraX += x;
		}
		SetCollision();
	}

	// 제일 왼쪽 맵일 경우
	if (m_CameraX < 200.0f)
	{
		m_CameraX = 200.0f;
	}

	m_Y += y;

	//if (!m_bIsJump)
	//{
	//	m_State = STATE_MOVE;
	//}
}

void Player::SetCollision()
{
	m_Collision.left = m_X;
	m_Collision.right = m_X + m_PlayerBitmap[BITMAPINDEX_IDLE].GetSize().cx * 1.5f;
	m_Collision.top = m_Y;
	m_Collision.bottom = m_Y + m_PlayerBitmap[BITMAPINDEX_IDLE].GetSize().cy * 1.5f;
}

void Player::StopAnim()
{
	m_State = STATE_IDLE;
	m_BitmapIndex = BITMAPINDEX_IDLE;
	m_bIsJump = false;
	m_CurAnimTimer = 0.0f;
	Draw(m_X, m_Y);
}

void Player::AnimMoveForward()
{
	if (m_State == STATE_MOVELEFT || m_State == STATE_MOVERIGHT)
	{
		if (m_CurAnimTimer - m_StartAnimTimer >= m_AnimMoveForwardTime)
		{
			m_BitmapIndex++;
			if (m_BitmapIndex > 2)
			{
				m_BitmapIndex = 0;
			}
			m_StartAnimTimer = m_CurAnimTimer;
		}
	}

	Draw(m_X, m_Y);
}

void Player::AnimMoveBack()
{
	if (m_State == STATE_MOVELEFT || m_State == STATE_MOVERIGHT)
	{
		if (m_CurAnimTimer - m_StartAnimTimer >= m_AnimMoveBackTime)
		{
			m_BitmapIndex++;
			if (m_BitmapIndex > 1)
			{
				m_BitmapIndex = 0;
			}
			m_StartAnimTimer = m_CurAnimTimer;
		}
	}

	Draw(m_X, m_Y);
}

void Player::Jump()
{
	if (m_bIsJump)
	{
		if (m_State == STATE_LEFTJUMP)
		{
			// 맵의 끝에 도달하지 않았을 경우 플레이어 대신 카메라를 움직인다.
			if (m_CameraX < LastFieldWidth)
			{
				m_CameraX -= m_Speed;
				if (m_CameraX < 0.0f)
				{
					m_CameraX = 0.0f;
				}
			}
			else
			{
				m_X -= m_Speed;
				if (m_X < 200.0f)
				{
					m_X = 200.0f;
					m_CameraX -= m_Speed;
				}
				m_Collision.left = m_X;
				m_Collision.right = m_X + m_PlayerBitmap[BITMAPINDEX_IDLE].GetSize().cx * 1.5f;
			}
		}
		if (m_State == STATE_RIGHTJUMP)
		{
			// 맵의 끝에 도달하지 않았을 경우 플레이어 대신 카메라를 움직인다.
			if (m_CameraX < LastFieldWidth)
			{
				m_CameraX += m_Speed;
			}
			else
			{
				m_X += m_Speed;
				m_Collision.left = m_X;
				m_Collision.right = m_X + m_PlayerBitmap[BITMAPINDEX_IDLE].GetSize().cx * 1.5f;
			}
		}

		m_JumpY = m_JumpTime * m_JumpTime - m_JumpForce * m_JumpTime;
		if (m_State == STATE_LEFTJUMP || m_State == STATE_RIGHTJUMP)
		{
			m_JumpTime += 0.15f;
		}
		else
		{
			m_JumpTime += 0.1f;
		}


		m_BitmapIndex = BITMAPINDEX_MOVE2;
		m_Collision.top = m_JumpY + m_Y;
		m_Collision.bottom = m_JumpY + m_Y + m_PlayerBitmap[BITMAPINDEX_IDLE].GetSize().cy * 1.5f;
		Draw(m_X, m_JumpY + m_Y);

		if (m_JumpTime >= m_JumpForce)
		{
			m_JumpTime = 0.0f;
			m_JumpY = 0.0f;
			m_Collision.top += 3.0f;
			m_Collision.bottom += 3.0f;
			StopAnim();
		}
	}
}

void Player::Win(float x, float y)
{
	m_State = STATE_WIN;
	if (m_CurAnimTimer - m_StartAnimTimer >= m_AnimWinTime)
	{
		m_BitmapIndex++;
		if (m_BitmapIndex > 4)
		{
			m_BitmapIndex = 3;
		}
		m_StartAnimTimer = m_CurAnimTimer;
	}

	Draw(x, y);
}

void Player::Die()
{
	m_State = STATE_DIE;
	m_BitmapIndex = BITMAPINDEX_DIE;
}
