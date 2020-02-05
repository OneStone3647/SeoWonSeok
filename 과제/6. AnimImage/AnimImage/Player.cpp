#include "Player.h"

int Player::m_X = 100;
int Player::m_Y = 100;
int Player::m_Frame = 0;
bool Player::m_bJump = false;

Player::Player()
{
}

void Player::Init(HWND hWnd)
{
	m_hWnd = hWnd;
	m_X = 100;
	m_Y = 100;
	m_Frame = 0;
	m_Position = CHARACTERPOSITION_DOWN;
	m_bJump = false;
}

void Player::Input(WPARAM wParam)
{
	switch (wParam)
	{
	case VK_DOWN:
		m_Y += 10;
		SetFrame(CHARACTERPOSITION_DOWN);
		break;
	case VK_UP:
		m_Y -= 10;
		SetFrame(CHARACTERPOSITION_UP);
		break;
	case VK_LEFT:
		m_X -= 10;
		SetFrame(CHARACTERPOSITION_LEFT);
		break;
	case VK_RIGHT:
		m_X += 10;
		SetFrame(CHARACTERPOSITION_RIGHT);
		break;
	case VK_SPACE:
		if (m_bJump != true)
		{
			m_Y -= 40;
			m_Frame = 1;
			m_bJump = true;
			InvalidateRect(m_hWnd, NULL, TRUE);
			SetTimer(m_hWnd, 1, 250, Jump);
		}
		break;
	}
}

void Player::SetFrame(CHARACTERPOSITION Position)
{
	m_Frame++;
	if (m_Position != Position || m_Frame > 3)
	{
		m_Frame = 0;
	}
	m_Position = Position;
}

void Player::Jump(HWND hWnd, UINT uMsg, UINT idEvent, DWORD dwTime)
{
	m_Y += 40;
	m_Frame = 0;
	KillTimer(hWnd, 1);
	InvalidateRect(hWnd, NULL, TRUE);
	m_bJump = false;
}


Player::~Player()
{
}
