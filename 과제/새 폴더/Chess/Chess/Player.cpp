#include "Player.h"



Player::Player()
{
}

void Player::Init(HWND hWnd)
{
	int m_X = 0;
	int m_Y = 0;
	m_Piece = new Block[MAXPIECECOUNT];
	m_hWnd = hWnd;
}

void Player::Input(LPARAM lParam)
{
	m_X = LOWORD(lParam);
	m_Y = HIWORD(lParam);
}


Player::~Player()
{
}


Player::Player()
{
}


Player::~Player()
{
}
