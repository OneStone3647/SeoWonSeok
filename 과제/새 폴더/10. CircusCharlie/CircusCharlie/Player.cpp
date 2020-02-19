#include "Player.h"



Player::Player()
{
}


Player::~Player()
{
}

void Player::Init(HWND hWnd)
{
	m_hWnd = hWnd;
	HDC hdc = GetDC(hWnd);

	m_MemDC = CreateCompatibleDC(hdc);
	m_NewBitmap = CreateCompatibleBitmap(hdc, PlayerWidth, PlayerHeight);
	m_OldBitmap = (HBITMAP)SelectObject(m_MemDC, m_NewBitmap);

	m_PlayerBitmap[PLAYERINDEX_IDLE].Init(m_MemDC, "Bitmap\\player0.bmp");
	m_PlayerBitmap[PLAYERINDEX_MOVE1].Init(m_MemDC, "Bitmap\\player1.bmp");
	m_PlayerBitmap[PLAYERINDEX_MOVE2].Init(m_MemDC, "Bitmap\\player2.bmp");
	m_PlayerBitmap[PLAYERINDEX_WIN1].Init(m_MemDC, "Bitmap\\win.bmp");
	m_PlayerBitmap[PLAYERINDEX_WIN2].Init(m_MemDC, "Bitmap\\win2.bmp");
	m_PlayerBitmap[PLAYERINDEX_DIE].Init(m_MemDC, "Bitmap\\die.bmp");

	ReleaseDC(hWnd, hdc);

	m_EState = STATE_IDLE;
	m_bIsJump = false;

	m_Player_X = 100;
	m_Player_Y = 400;
}

void Player::Update()
{
	HDC hdc = GetDC(m_hWnd);
	m_PlayerBitmap[PLAYERINDEX_IDLE].Draw(hdc, m_Player_X, m_Player_Y);

	ReleaseDC(m_hWnd, hdc);
}

void Player::Input()
{
	if (!(GetKeyState(VK_LEFT) | GetKeyState(VK_RIGHT) | GetKeyState(VK_UP) | GetKeyState(VK_DOWN)) & 0x8000)
	{
	}
	if (GetKeyState(VK_LEFT) & 0x8000)
	{
	}
	if (GetKeyState(VK_RIGHT) & 0x8000)
	{
	}
	if (GetKeyState(VK_SPACE) & 0x8000)
	{
		Jump();
	}
}

void Player::Move()
{
}

void Player::Jump()
{
}
