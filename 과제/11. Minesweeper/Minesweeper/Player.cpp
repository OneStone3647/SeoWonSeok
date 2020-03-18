#include "Player.h"



Player::Player()
{
}


Player::~Player()
{
}

void Player::Init()
{
	m_MouseClick = MOUSECLICK_IDLE;
	m_MousePoint.x = NULL;
	m_MousePoint.y = NULL;
}

void Player::Input(LPARAM lParam)
{
	// 현재 키의 상태를 알아온다.
	if (GetAsyncKeyState(VK_LBUTTON) & 0x0001)
	{
		m_MouseClick = MOUSECLICK_LEFT;
		m_MousePoint.x = LOWORD(lParam);
		m_MousePoint.y = HIWORD(lParam);
	}
	if (GetAsyncKeyState(VK_RBUTTON) & 0x0001)
	{
		m_MouseClick = MOUSECLICK_RIGHT;
		m_MousePoint.x = LOWORD(lParam);
		m_MousePoint.y = HIWORD(lParam);
	}
}
