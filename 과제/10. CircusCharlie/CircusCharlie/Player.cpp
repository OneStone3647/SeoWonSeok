#include "Player.h"



Player::Player()
{
}


Player::~Player()
{
	//SelectObject(m_MemDC, m_OldBitmap);
	//DeleteObject(m_NewBitmap);
	//// CreateCompatibleDC로 만들어진 DC는 DeleteDC로 지워야한다.
	//DeleteDC(m_MemDC);
}

void Player::Init(HDC BackDC)
{
	m_BackDC = BackDC;
	//m_MemDC = CreateCompatibleDC(BackDC);
	//m_NewBitmap = CreateCompatibleBitmap(BackDC, ScreenWidth, ScreenHeight);
	//m_OldBitmap = (HBITMAP)SelectObject(m_MemDC, m_NewBitmap);

	m_Player_Idle.Init(m_BackDC, "Bitmap\\player0.bmp");
	m_Player_Move1.Init(m_BackDC, "Bitmap\\player1.bmp");
	m_Player_Move2.Init(m_BackDC, "Bitmap\\player2.bmp");
	m_Player_Win1.Init(m_BackDC, "Bitmap\\win.bmp");
	m_Player_Win2.Init(m_BackDC, "Bitmap\\win2.bmp");
	m_Player_Die.Init(m_BackDC, "Bitmap\\die.bmp");

	m_Player_X = 100;
	m_Player_Y = 400;
}

void Player::Update()
{
	m_Player_Idle.Draw(m_BackDC, m_Player_X, m_Player_Y);

	//BitBlt(m_BackDC, 0, 0, ScreenWidth, ScreenHeight, m_MemDC, 0, 0, SRCCOPY);
}
