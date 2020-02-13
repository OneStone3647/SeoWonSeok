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

	m_X = 100;
	m_Y = 100;

	m_Frame = 0;
	m_Position = PLAYERPOSITION_DOWN;
}

void Player::Draw(HDC hdc)
{
	TransparentBlt(hdc, m_X, m_Y, m_size.cx / 4, m_size.cy / 4, MemDC, (m_size.cx / 4) * m_Frame, (m_size.cy / 4) * m_Position, m_size.cx / 4, m_size.cy / 4, RGB(255, 0, 255));
}

void Player::Input(HWND hWnd)
{
	if (GetKeyState(VK_LEFT) & 0x8000)
	{
		m_X -= 10;
		SetFrame(PLAYERPOSITION_LEFT);
	}
	if (GetKeyState(VK_RIGHT) & 0x8000)
	{
		m_X += 10;
		SetFrame(PLAYERPOSITION_RIGHT);
	}
	if (GetKeyState(VK_UP) & 0x8000)
	{
		m_Y -= 10;
		SetFrame(PLAYERPOSITION_UP);
	}
	if (GetKeyState(VK_DOWN) & 0x8000)
	{
		m_Y += 10;
		SetFrame(PLAYERPOSITION_DOWN);
	}

	InvalidateRect(hWnd, NULL, false);
}

void Player::SetFrame(PLAYERPOISTION position)
{
	m_Frame++;
	if (m_Position != position || m_Frame > 3)
	{
		m_Frame = 0;
		m_Position = position;
	}
}


Player::~Player()
{
	SelectObject(MemDC, m_OldBitmap);
	DeleteObject(m_NewBitmap);
	DeleteDC(MemDC);
}
