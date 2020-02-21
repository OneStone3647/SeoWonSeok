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

	m_LastTime = GetTickCount();
	m_CurTime = GetTickCount();

	m_Anim = 0;
	m_AnimTimer = 0;

	m_State = STATE_IDLE;

	m_bIsJump = false;
	m_JumpAnim = 0;
	m_JumpTimer = 0;
	m_JumpForce = 25;
}

void Player::Update()
{
	// 매 프레임마다 찍히는 TickCount를 받는다.
	m_CurTime = GetTickCount();

	// 현재 시간을 저장한다. 루틴이 돌아간 후 이전 루틴에서의 틱 카운트간의 차이를 체크하기 위해서 이다.
	// 1000 이상의 차이가 나면 1초이므로 / 1000해서 초로 환산한다.
	m_DeltaTime = (m_CurTime - m_LastTime) / 1000.0f;

	// 현재 타임을 받는다.
	// 결론적으로 이전 타임의 시간을 받는 것이다.
	m_LastTime = m_CurTime;

	Input();
	Jump();
	AnimMove();
}

void Player::Input()
{
	if (GetKeyState(VK_LEFT) & 0x8000)
	{
		Move(-0.5f, 0.0f);
	}
	if (GetKeyState(VK_RIGHT) & 0x8000)
	{
		Move(0.5f, 0.0f);
	}
	if (GetKeyState(VK_SPACE) & 0x8000)
	{
		if (m_State == STATE_IDLE)
		{
			m_bIsJump = true;

			m_State = STATE_JUMP;

			// 다음 점프를 계산하기 위해 현재 위치를 저장한다.
			m_JumpX = m_X;
			m_JumpY = m_Y;
		}
	}
	if(!(GetKeyState(VK_LEFT) | GetKeyState(VK_RIGHT) | GetKeyState(VK_SPACE)) & 0x8000)
	{
		m_State = STATE_IDLE;
		m_Anim = ANIMMOVE_IDLE;
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

void Player::AnimMove()
{
	if (m_State == STATE_MOVE)
	{
		if (m_AnimTimer == 80)
		{
			m_Anim++;
			if (m_Anim > 2)
			{
				m_Anim = 0;
			}
			m_AnimTimer = 0;
		}
		else
		{
			m_AnimTimer++;
		}
	}
	else
	{
		m_State = STATE_IDLE;
		m_Anim = ANIMMOVE_IDLE;
		m_AnimTimer = 0;
	}

	switch (m_Anim)
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

void Player::Jump()
{
	// 점프는 점프해서 움직이고 있는 시간이 있기 때문에 점프 지속시간 동안 동작이 없어야 한다.
	if (m_State == STATE_JUMP)
	{
		m_CurJumpTime += m_DeltaTime;

		// 원을 원만하게 그려 점프를 구현한다.
		// 점프 지속시간을 체크해서 위치나 상태를 초기화 해준다.
		m_X = m_JumpX - cosf(m_CurJumpTime * PI) * 10.0;
		m_Y = m_JumpY - sinf(m_CurJumpTime * PI) * 1.0;

		// 점프 지속시간 체크용 초기화
		if (m_CurJumpTime > 1.0f)
		{
			m_CurJumpTime = 0.0f;

			m_State = STATE_IDLE;
		}
	}
}
