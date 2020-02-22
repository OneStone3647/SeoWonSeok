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

	m_Player_Idle.Init(m_BackDC, "Bitmap\\player0.bmp");
	m_Player_Move1.Init(m_BackDC, "Bitmap\\player1.bmp");
	m_Player_Move2.Init(m_BackDC, "Bitmap\\player2.bmp");
	m_Player_Win1.Init(m_BackDC, "Bitmap\\win.bmp");
	m_Player_Win2.Init(m_BackDC, "Bitmap\\win2.bmp");
	m_Player_Die.Init(m_BackDC, "Bitmap\\die.bmp");

	m_X = 100.0f;
	m_Y = 415.0f;

	m_AnimIndex = 0;
	m_AnimMoveForwardTime = 120.0f;
	m_AnimMoveBackTime = 200.0f;
	m_StartAnimTimer = GetTickCount();
	m_CurAnimTimer = 0.0f;

	m_State = STATE_IDLE;

	m_bIsJump = false;
	m_JumpForce = 20.0f;
	m_JumpX = 0;
	m_JumpY = 0;
}

void Player::Update()
{
	m_CurAnimTimer = GetTickCount();
	Input();
	Jump();
}

void Player::Input()
{
	if (GetKeyState(VK_LEFT) & 0x8000 && m_State != STATE_JUMP)
	{
		Move(-0.2f, 0.0f);
		AnimMoveBack();
	}
	if (GetKeyState(VK_RIGHT) & 0x8000 && m_State != STATE_JUMP)
	{
		Move(0.2f, 0.0f);
		AnimMoveForward();
	}
	if (GetKeyState(VK_SPACE) & 0x8000)
	{
		if (m_State == STATE_IDLE)
		{
			m_bIsJump = true;

			m_State = STATE_JUMP;
		}
	}
	// ¸ØÃá »óÅÂ
	if(!((GetKeyState(VK_LEFT) | GetKeyState(VK_RIGHT)) & 0x8000) && m_State != STATE_JUMP)
	{
		StopAnim();
	}
}

void Player::Move(float x, float y)
{
	m_X += x;
	m_Y += y;
	
	if (!m_bIsJump)
	{
		m_State = STATE_MOVE;
	}
}

void Player::StopAnim()
{
	m_State = STATE_IDLE;
	m_AnimIndex = ANIMMOVE_IDLE;
	m_bIsJump = false;
	m_CurAnimTimer = 0.0f;
	m_Player_Idle.Draw(m_BackDC, m_X, m_Y);
}

void Player::AnimMoveForward()
{
	if (m_State == STATE_MOVE)
	{
		if (m_CurAnimTimer - m_StartAnimTimer >= m_AnimMoveForwardTime)
		{
			m_AnimIndex++;
			if (m_AnimIndex > 2)
			{
				m_AnimIndex = 0;
			}
			m_StartAnimTimer = m_CurAnimTimer;
		}
	}

	switch (m_AnimIndex)
	{
	case ANIMMOVE_IDLE:
		m_Player_Idle.Draw(m_BackDC, m_X, m_Y);
		break;
	case ANIMMOVE_MOVE1:
		m_Player_Move1.Draw(m_BackDC, m_X, m_Y);
		break;
	case ANIMMOVE_MOVE2:
		m_Player_Move2.Draw(m_BackDC, m_X, m_Y);
		break;
	}
}

void Player::AnimMoveBack()
{
	if (m_State == STATE_MOVE)
	{
		if (m_CurAnimTimer - m_StartAnimTimer >= m_AnimMoveBackTime)
		{
			m_AnimIndex++;
			if (m_AnimIndex > 1)
			{
				m_AnimIndex = 0;
			}
			m_StartAnimTimer = m_CurAnimTimer;
		}
	}

	switch (m_AnimIndex)
	{
	case ANIMMOVE_IDLE:
		m_Player_Idle.Draw(m_BackDC, m_X, m_Y);
		break;
	case ANIMMOVE_MOVE1:
		m_Player_Move1.Draw(m_BackDC, m_X, m_Y);
		break;
	}
}

void Player::Jump()
{
	if (m_State == STATE_JUMP)
	{

		m_JumpY = m_JumpX * m_JumpX - m_JumpForce * m_JumpX;
		m_JumpX += 0.05f;

		m_AnimIndex = ANIMMOVE_MOVE2;
		m_Player_Move2.Draw(m_BackDC, m_X, m_JumpY + m_Y);

		if (m_JumpX >= m_JumpForce)
		{
			m_JumpX = 0.0f;
			m_JumpY = 0.0f;
			StopAnim();
		}
	}
}
