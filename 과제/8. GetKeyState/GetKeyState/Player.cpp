#include "Player.h"



Player::Player()
{
}

void Player::Init(HDC hdc, HINSTANCE hInst)
{
	MemDC = CreateCompatibleDC(hdc);
	m_NewBitmap = (HBITMAP)LoadImage(NULL, TEXT("image.bmp"),
		IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
	m_OldBitmap = (HBITMAP)SelectObject(MemDC, m_NewBitmap);

	BITMAP Bit_Info;

	GetObject(m_NewBitmap, sizeof(Bit_Info), &Bit_Info);
	m_size.cx = Bit_Info.bmWidth;
	m_size.cy = Bit_Info.bmHeight;

	m_PlayerState = PLAYERSTATE_IDLE;

	m_X = 100;
	m_Y = 100;

	m_Position = PLAYERPOSITION_DOWN;
	m_Anim = 0;
	m_AnimTimer = 0;

	m_bIsJump = false;
	m_JumpTimer = 0;
}

void Player::Draw(HDC hdc)
{
	TransparentBlt(hdc, m_X, m_Y, m_size.cx / 4, m_size.cy / 4, MemDC, (m_size.cx / 4) * m_Anim, (m_size.cy / 4) * m_Position, m_size.cx / 4, m_size.cy / 4, RGB(255, 0, 255));
}

void Player::Input(HWND hWnd)
{
	// idle ป๓ลย
	if (!((GetKeyState(VK_LEFT) | GetKeyState(VK_RIGHT) | GetKeyState(VK_UP) | GetKeyState(VK_DOWN)) & 0x8000))
	{
		Idle();
	}
	if (GetKeyState(VK_LEFT) & 0x8000)
	{
		m_Position = PLAYERPOSITION_LEFT;
		Move(-10 ,0);
	}
	if (GetKeyState(VK_RIGHT) & 0x8000)
	{
		m_Position = PLAYERPOSITION_RIGHT;
		Move(10, 0);
	}
	if (GetKeyState(VK_UP) & 0x8000)
	{
		m_Position = PLAYERPOSITION_UP;
		Move(0, -10);
	}
	if (GetKeyState(VK_DOWN) & 0x8000)
	{
		m_Position = PLAYERPOSITION_DOWN;
		Move(0, 10);
	}
	if (GetKeyState(VK_SPACE) & 0x8000)
	{
		Jump();
	}

	InvalidateRect(hWnd, NULL, false);
}

void Player::Idle()
{
	m_PlayerState = PLAYERSTATE_IDLE;
	m_Anim = 0;
	if (m_bIsJump)
	{
		if (m_JumpTimer == 5)
		{
			m_JumpTimer = 0;
			
		}
		else
		{
			JumpStart();
			m_JumpTimer++;
		}
	}
}

void Player::Move(int x, int y)
{
	m_X += x;
	m_Y += y;
	if (m_PlayerState == PLAYERSTATE_MOVE)
	{
		AnimMove();
	}
	if (m_PlayerState == PLAYERSTATE_JUMP)
	{

	}

}

void Player::AnimMove()
{
	if (m_AnimTimer == 5)
	{
		m_Anim++;
		if (m_Anim > 3)
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

void Player::Jump()
{
	if (m_bIsJump)
	{
		return;
	}
	m_bIsJump = true;
	m_JumpTimer = 0;
	m_JumpPositionY = 0;
	m_PlayerState = PLAYERSTATE_JUMP;
}

void Player::JumpStart()
{
	if (m_bIsJump)
	{
		if (m_JumpPositionY < m_JumpForce)
		{
			m_JumpPositionY++;
			m_Y -= m_JumpForce;
		}
		else
		{
			m_bIsJump = false;
		}
	}
}

void Player::JumpEnd()
{
	if (!m_bIsJump)
	{
		if (m_JumpPositionY < m_JumpForce)
		{
			m_JumpPositionY++;
			m_Y += m_JumpForce;
		}
		else
		{

		}
	}
}

void Player::AnimJump()
{

}


Player::~Player()
{
	SelectObject(MemDC, m_OldBitmap);
	DeleteObject(m_NewBitmap);
	DeleteDC(MemDC);
}
