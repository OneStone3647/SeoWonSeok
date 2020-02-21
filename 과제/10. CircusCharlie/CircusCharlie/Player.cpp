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
	// �� �����Ӹ��� ������ TickCount�� �޴´�.
	m_CurTime = GetTickCount();

	// ���� �ð��� �����Ѵ�. ��ƾ�� ���ư� �� ���� ��ƾ������ ƽ ī��Ʈ���� ���̸� üũ�ϱ� ���ؼ� �̴�.
	// 1000 �̻��� ���̰� ���� 1���̹Ƿ� / 1000�ؼ� �ʷ� ȯ���Ѵ�.
	m_DeltaTime = (m_CurTime - m_LastTime) / 1000.0f;

	// ���� Ÿ���� �޴´�.
	// ��������� ���� Ÿ���� �ð��� �޴� ���̴�.
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

			// ���� ������ ����ϱ� ���� ���� ��ġ�� �����Ѵ�.
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
	// ������ �����ؼ� �����̰� �ִ� �ð��� �ֱ� ������ ���� ���ӽð� ���� ������ ����� �Ѵ�.
	if (m_State == STATE_JUMP)
	{
		m_CurJumpTime += m_DeltaTime;

		// ���� �����ϰ� �׷� ������ �����Ѵ�.
		// ���� ���ӽð��� üũ�ؼ� ��ġ�� ���¸� �ʱ�ȭ ���ش�.
		m_X = m_JumpX - cosf(m_CurJumpTime * PI) * 10.0;
		m_Y = m_JumpY - sinf(m_CurJumpTime * PI) * 1.0;

		// ���� ���ӽð� üũ�� �ʱ�ȭ
		if (m_CurJumpTime > 1.0f)
		{
			m_CurJumpTime = 0.0f;

			m_State = STATE_IDLE;
		}
	}
}
