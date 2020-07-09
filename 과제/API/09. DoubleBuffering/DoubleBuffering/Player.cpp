#include "Player.h"



Player::Player()
{
}

void Player::Init(HDC mainDC, HDC subDC, HBITMAP * newBitmap, HBITMAP * oldBitmap)
{
	MainMemDC = mainDC;
	SubMemDC = subDC;
	*newBitmap = (HBITMAP)LoadImage(NULL, "image.bmp", IMAGE_BITMAP, 0, 0
		, LR_CREATEDIBSECTION | LR_DEFAULTSIZE | LR_LOADFROMFILE);
	*oldBitmap = (HBITMAP)SelectObject(SubMemDC, *newBitmap);

	BITMAP Bit_Info;

	GetObject(*newBitmap, sizeof(Bit_Info), &Bit_Info);
	m_size.cx = Bit_Info.bmWidth;
	m_size.cy = Bit_Info.bmHeight;

	m_X = 100;
	m_Y = 100;

	m_State = STATE_IDLE;
	m_Direction = DIRECTION_DOWN;

	m_Anim = 0;
	m_AnimTimer = 0;

	m_bIsJump = false;
	m_JumpAnim = 0;
	m_JumpTimer = 0;
	m_JumpForce = 25;
	m_JumpPosY = 0;
}

void Player::Draw()
{
	TransparentBlt(MainMemDC, m_X, m_Y, m_size.cx / 4, m_size.cy / 4, SubMemDC, (m_size.cx / 4) * m_Anim, (m_size.cy / 4) * m_Direction, m_size.cx / 4, m_size.cy / 4, RGB(255, 0, 255));
}

void Player::Input(HWND hWnd)
{
	if (!(GetKeyState(VK_LEFT) | GetKeyState(VK_RIGHT) | GetKeyState(VK_UP) | GetKeyState(VK_DOWN)) & 0x8000)
	{
		m_State = STATE_IDLE;
		m_Anim = 0;
	}
	if (GetKeyState(VK_LEFT) & 0x8000)
	{
		m_Direction = DIRECTION_LEFT;
		Move(-10, 0);
	}
	if (GetKeyState(VK_RIGHT) & 0x8000)
	{
		m_Direction = DIRECTION_RIGHT;
		Move(10, 0);
	}
	if (GetKeyState(VK_UP) & 0x8000)
	{
		m_Direction = DIRECTION_UP;
		Move(0, -10);
	}
	if (GetKeyState(VK_DOWN) & 0x8000)
	{
		m_Direction = DIRECTION_DOWN;
		Move(0, 10);
	}
	if (GetKeyState(VK_SPACE) & 0x8000)
	{
		Jump();
	}

	JumpStart();
	JumpEnd();

	InvalidateRect(hWnd, NULL, false);
}

void Player::Move(int x, int y)
{
	m_X += x;
	m_Y += y;

	if (!m_bIsJump)
	{
		m_State = STATE_MOVE;
		AnimMove();
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
	m_Anim = 1;
	m_State = STATE_JUMPSTART;
}

void Player::JumpStart()
{
	if (m_State == STATE_JUMPSTART)
	{
		if (m_JumpTimer == 5)
		{
			m_JumpTimer = 0;
			m_State = STATE_JUMPEND;
		}
		else
		{
			m_Y -= m_JumpForce;
			m_JumpTimer++;
		}
	}
}

void Player::JumpEnd()
{
	if (m_State == STATE_JUMPEND)
	{
		if (m_JumpTimer == 5)
		{
			m_Anim = 0;
			m_JumpTimer = 0;
			m_bIsJump = false;
			m_State = STATE_IDLE;
		}
		else
		{
			m_Y += m_JumpForce;
			m_JumpTimer++;
		}
	}
}


Player::~Player()
{
}
