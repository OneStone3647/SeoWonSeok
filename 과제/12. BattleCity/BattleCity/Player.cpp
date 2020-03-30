#include "Player.h"



Player::Player()
{
}


Player::~Player()
{
}

void Player::Init()
{
	m_PlayerMode = PLAYERMODE_IDLE;
	m_MousePoint.x = NULL;
	m_MousePoint.y = NULL;
}

void Player::Input(MODE GameMode, LPARAM lParam)
{
	m_PlayerMode = PLAYERMODE_IDLE;

	if (GameMode == MODE_MAPTOOL && (GetAsyncKeyState(VK_LBUTTON) & 0x0001))
	{
		m_PlayerMode = PLAYERMODE_MAPTOOL;
		m_MousePoint.x = LOWORD(lParam);
		m_MousePoint.y = HIWORD(lParam);
	}
}
