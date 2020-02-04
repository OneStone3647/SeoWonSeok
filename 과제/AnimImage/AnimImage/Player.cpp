#include "Player.h"

Player* Player::m_This = NULL;

Player::Player()
{
}

void Player::Init(HWND hWnd, WPARAM wParam)
{
	m_hWnd = hWnd;
	m_wParam = wParam;
	m_X = 100;
	m_Y = 100;
	m_Frame = 0;
	m_Position = CHARACTERPOSITION_DOWN;
	m_bJump = false;
}

void Player::Input()
{
	switch (m_wParam)
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
		m_Y += 10;
		m_bJump = true;
		Jump();
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

void Player::Jump()
{
	m_Y -= 10;
	m_bJump = false;
}

void Player::Release()
{
	delete m_This;
}


Player::~Player()
{
}
