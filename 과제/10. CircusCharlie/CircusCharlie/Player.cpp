#include "Player.h"



Player::Player()
{
}


Player::~Player()
{
}

void Player::Init(HDC BackDC)
{
	m_BackDC = BackDC;

	m_Collision.top = m_Y;
	m_Collision.left = m_X;
	m_Collision.bottom = m_Y + m_Player_Idle.GetSize().cy;
	m_Collision.bottom = m_X + m_Player_Idle.GetSize().cx;

	m_Player_Idle.Init(m_BackDC, "Bitmap\\player0.bmp");
	m_Player_Move1.Init(m_BackDC, "Bitmap\\player1.bmp");
	m_Player_Move2.Init(m_BackDC, "Bitmap\\player2.bmp");
	m_Player_Win1.Init(m_BackDC, "Bitmap\\win.bmp");
	m_Player_Win2.Init(m_BackDC, "Bitmap\\win2.bmp");
	m_Player_Die.Init(m_BackDC, "Bitmap\\die.bmp");

	m_X = 100.0f;
	m_Y = 415.0f;
	m_CameraPos = 0.0f;

	m_Speed = 5.0f;
	m_Speed = 7.5f;

	m_BitmapIndex = 0;

	m_AnimMoveForwardTime = 120.0f;
	m_AnimMoveBackTime = 200.0f;
	m_StartAnimTimer = GetTickCount();
	m_CurAnimTimer = 0.0f;

	m_State = STATE_IDLE;

	m_bIsJump = false;
	m_JumpForce = 24.0f;
	m_JumpTime = 0;
	m_JumpY = 0;
	m_JumpSpeed = 2.8f;
}

void Player::Update()
{
	m_CurAnimTimer = GetTickCount();
	Input();
	Jump();
}

void Player::Input()
{
	if (GetKeyState(VK_LEFT) & 0x8000 && m_bIsJump == false)
	{
		Move(-m_Speed, 0.0f);
		AnimMoveBack();
	}
	if (GetKeyState(VK_RIGHT) & 0x8000 && m_bIsJump == false)
	{
		Move(m_Speed, 0.0f);
		AnimMoveForward();
	}
	if (((GetKeyState(VK_LEFT) & GetKeyState(VK_SPACE)) & 0x8000) && m_bIsJump == false)
	{
		m_bIsJump = true;
		m_State = STATE_LEFTJUMP;
	}
	if (((GetKeyState(VK_RIGHT) & GetKeyState(VK_SPACE)) & 0x8000) && m_bIsJump == false)
	{
		m_bIsJump = true;
		m_State = STATE_RIGHTJUMP;
	}
	if (GetKeyState(VK_SPACE) & 0x8000 && m_bIsJump == false)
	{
		m_bIsJump = true;
		m_State = STATE_JUMP;
	}
	// ∏ÿ√· ªÛ≈¬
	if(!((GetKeyState(VK_LEFT) | GetKeyState(VK_RIGHT)) & 0x8000) && m_bIsJump == false)
	{
		StopAnim();
	}
}

void Player::Draw(float x, float y)
{
	switch (m_BitmapIndex)
	{
	case BITMAPINDEX_IDLE:
		m_Player_Idle.Draw(m_BackDC, x, y);
		break;
	case BITMAPINDEX_MOVE1:
		m_Player_Move1.Draw(m_BackDC, x, y);
		break;
	case BITMAPINDEX_MOVE2:
		m_Player_Move2.Draw(m_BackDC, x, y);
		break;
	case BITMAPINDEX_WIN1:
		m_Player_Win1.Draw(m_BackDC, x, y);
		break;
	case BITMAPINDEX_WIN2:
		m_Player_Win2.Draw(m_BackDC, x, y);
		break;
	case BITMAPINDEX_DIE:
		m_Player_Die.Draw(m_BackDC, x, y);
		break;
	}
}

void Player::Move(float x, float y)
{
	//m_X += x;
	//m_CameraPos += x* 1.5f;
	m_CameraPos += x;
	if (m_X < 100.0f)
	{
		m_X = 100.0f;
		m_CameraPos = 0.0f;
	}
	m_Y += y;
	
	if (!m_bIsJump)
	{
		m_State = STATE_MOVE;
	}
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
	if (m_State == STATE_MOVE)
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
	if (m_State == STATE_MOVE)
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
			//m_X -= (m_Speed / 2) * 4;
			//m_CameraPos -= (m_Speed / 2) * 2.0f;
			//m_CameraPos -= (m_Speed / 2) * m_JumpSpeed;
			m_CameraPos -= m_Speed;
			if (m_X < 100.0f)
			{
				//m_X = 100.0f;
				m_CameraPos = 0.0f;
			}
		}
		if (m_State == STATE_RIGHTJUMP)
		{
			//m_X += (m_Speed / 2) * 4;
			//m_CameraPos += (m_Speed / 2) * 2.0f;
			//m_CameraPos += (m_Speed / 2) * m_JumpSpeed;
			m_CameraPos += m_Speed;
		}

		m_JumpY = m_JumpTime * m_JumpTime - m_JumpForce * m_JumpTime;
		m_JumpTime += 1.0f;

		m_BitmapIndex = BITMAPINDEX_MOVE2;
		Draw(m_X, m_JumpY + m_Y);

		if (m_JumpTime >= m_JumpForce)
		{
			m_JumpTime = 0.0f;
			m_JumpY = 0.0f;
			StopAnim();
		}
	}
}
