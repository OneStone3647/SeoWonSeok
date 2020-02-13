#pragma once
#include "Player.h"
#include "Back.h"

class GameManager
{
private:
	Player* m_Player;
	Back* m_Back;

public:
	GameManager();

	void Init(HWND hWnd, HINSTANCE hInst);
	void Draw(HDC hdc);

	~GameManager();
};

