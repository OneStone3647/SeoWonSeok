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

	m_PlayerBitmap[BITMAPINDEX_IDLE].Init(m_BackDC, "Bitmap\\player0.bmp");
	m_PlayerBitmap[BITMAPINDEX_MOVE1].Init(m_BackDC, "Bitmap\\player1.bmp");
	m_PlayerBitmap[BITMAPINDEX_MOVE2].Init(m_BackDC, "Bitmap\\player2.bmp");
	m_PlayerBitmap[BITMAPINDEX_WIN1].Init(m_BackDC, "Bitmap\\win.bmp");
	m_PlayerBitmap[BITMAPINDEX_WIN2].Init(m_BackDC, "Bitmap\\win2.bmp");
	m_PlayerBitmap[BITMAPINDEX_DIE].Init(m_BackDC, "Bitmap\\die.bmp");

	//m_Player_Idle.Init(m_BackDC, "Bitmap\\player0.bmp");
	//m_Player_Move1.Init(m_BackDC, "Bitmap\\player1.bmp");
	//m_Player_Move2.Init(m_BackDC, "Bitmap\\player2.bmp");
	//m_Player_Win1.Init(m_BackDC, "Bitmap\\win.bmp");
	//m_Player_Win2.Init(m_BackDC, "Bitmap\\win2.bmp");
	//m_Player_Die.Init(m_BackDC, "Bitmap\\die.bmp");

	m_X = 500.0f;
	m_Y = 440.0f;
	m_CameraX = 0.0f;

	SetCollision();
	//m_Speed = 5.0f;
	m_Speed = 7.5f;

	m_BitmapIndex = 0;

	m_AnimMoveForwardTime = 120.0f;
	m_AnimMoveBackTime = 200.0f;
	m_AnimWinTime = 100.0f;
	m_StartAnimTimer = GetTickCount();
	m_CurAnimTimer = 0.0f;

	m_State = STATE_IDLE;

	m_bIsJump = false;
	m_JumpForce = 24.0f;
	m_JumpTime = 0;
	m_JumpY = 0;
	m_JumpSpeed = 2.8f;
}

void Player::Update(int FieldIndex, bool bWinFlag, float EndX, float EndY)
{
	m_CurAnimTimer = GetTickCount();
	m_FieldIndex = FieldIndex;

	// 디버그 용
	Rectangle(m_BackDC, m_Collision.left, m_Collision.top, m_Collision.right, m_Collision.bottom);

	if (!bWinFlag && !(m_State == STATE_DIE))
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
		Win(EndX + 500.0f, EndY - 90.0f);
	}
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
	// 멈춘 상태
	if(!((GetKeyState(VK_LEFT) | GetKeyState(VK_RIGHT)) & 0x8000) && m_bIsJump == false)
	{
		StopAnim();
	}
}

void Player::Draw(float x, float y)
{
	m_PlayerBitmap[m_BitmapIndex].Draw(m_BackDC, x, y);

	//switch (m_BitmapIndex)
	//{
	//case BITMAPINDEX_IDLE:
	//	m_Player_Idle.Draw(m_BackDC, x, y);
	//	break;
	//case BITMAPINDEX_MOVE1:
	//	m_Player_Move1.Draw(m_BackDC, x, y);
	//	break;
	//case BITMAPINDEX_MOVE2:
	//	m_Player_Move2.Draw(m_BackDC, x, y);
	//	break;
	//case BITMAPINDEX_WIN1:
	//	m_Player_Win1.Draw(m_BackDC, x, y);
	//	break;
	//case BITMAPINDEX_WIN2:
	//	m_Player_Win2.Draw(m_BackDC, x, y);
	//	break;
	//case BITMAPINDEX_DIE:
	//	m_Player_Die.Draw(m_BackDC, x, y);
	//	break;
	//}
}

void Player::Move(float x, float y)
{
	//m_CameraX += x* 1.5f;

	// 맵의 끝에 도달하지 않았을 경우 플레이어 대신 카메라를 움직인다.
	if (m_CameraX <= LastField)
	{
		m_CameraX += x;		
	}
	else
	{
		m_X += x;
		if (m_X < 500.0f)
		{
			m_X = 500.0f;
			m_CameraX += x;
		}
		m_Collision.left = m_X;
		m_Collision.right = m_X + m_PlayerBitmap[BITMAPINDEX_IDLE].GetSize().cx * 1.5f;
	}


	// 제일 왼쪽 맵일 경우
	if (m_CameraX < 0.0f)
	{
		m_CameraX = 0.0f;
	}

	//// 맵의 왼쪽에 있을 경우 이동가능한 범위를 지정한다.
	//if (m_X < 100.0f)
	//{
	//	m_X = 100.0f;
	//	m_CameraX = 0.0f;
	//}

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
			//m_CameraX -= (m_Speed / 2) * 2.0f;
			//m_CameraX -= (m_Speed / 2) * m_JumpSpeed;

			//m_CameraX -= m_Speed;

			// 맵의 끝에 도달하지 않았을 경우 플레이어 대신 카메라를 움직인다.
			//if (m_FieldIndex != 9)
			//{
			//	m_CameraX -= m_Speed;
			//	if (m_CameraX < 0.0f)
			//	{
			//		m_CameraX = 0.0f;
			//	}
			//	if (m_X < 500.0f)
			//	{
			//		m_X = 500.0f;
			//	}
			//}
			//else
			//{
			//	m_X -= m_Speed;
			//	m_Collision.left -= m_Speed;
			//	m_Collision.right -= m_Speed;
			//}

			//if (m_FieldIndex == 0 && m_CameraX < 0.0f)
			//{
			//	m_CameraX = 0.0f;
			//}

						// 맵의 끝에 도달하지 않았을 경우 플레이어 대신 카메라를 움직인다.
			if (m_CameraX <= LastField)
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
				if (m_X < 500.0f)
				{
					m_X = 500.0f;
					m_CameraX -= m_Speed;
				}
				m_Collision.left = m_X;
				m_Collision.right = m_X + m_PlayerBitmap[BITMAPINDEX_IDLE].GetSize().cx * 1.5f;
			}
		}
		if (m_State == STATE_RIGHTJUMP)
		{
			//m_X += (m_Speed / 2) * 4;
			//m_CameraX += (m_Speed / 2) * 2.0f;
			//m_CameraX += (m_Speed / 2) * m_JumpSpeed;

			//m_CameraX += m_Speed;

			// 맵의 끝에 도달하지 않았을 경우 플레이어 대신 카메라를 움직인다.
			if (m_CameraX <= LastField)
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
			m_JumpTime += 0.5f;
		}
		else
		{
			m_JumpTime += 0.3f;
		}

		m_BitmapIndex = BITMAPINDEX_MOVE2;
		m_Collision.top = m_JumpY + m_Y;
		m_Collision.bottom = m_JumpY + m_Y + m_PlayerBitmap[BITMAPINDEX_IDLE].GetSize().cy * 1.5f;
		Draw(m_X, m_JumpY + m_Y);

		if (m_JumpTime >= m_JumpForce)
		{
			m_JumpTime = 0.0f;
			m_JumpY = 0.0f;
			if (m_State == STATE_LEFTJUMP || m_State == STATE_RIGHTJUMP)
			{
				m_Collision.top += 11.0f;
				m_Collision.bottom += 13.0f;
			}
			//m_Collision.top += 23.0f;
			//m_Collision.bottom += 23.0f;
			StopAnim();
		}
	}
}

void Player::SetCollision()
{
	m_Collision.left = m_X;
	m_Collision.right = m_X + m_PlayerBitmap[BITMAPINDEX_IDLE].GetSize().cx * 1.5f;
	m_Collision.top = m_Y;
	m_Collision.bottom = m_Y + m_PlayerBitmap[BITMAPINDEX_IDLE].GetSize().cy * 1.5f;
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
