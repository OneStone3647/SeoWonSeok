#include "Player.h"



Player::Player()
{
}


Player::~Player()
{
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
	if (GetKeyState(VK_UP) & 0x8000)
	{
	}
	if (GetKeyState(VK_DOWN) & 0x8000)
	{
	}
	if (GetKeyState(VK_SPACE) & 0x8000)
	{
	}
}
