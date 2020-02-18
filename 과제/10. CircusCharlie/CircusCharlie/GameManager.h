#pragma once
#include "Player.h"
#include "Menu.h"

class GameManager
{
private:
	HWND		m_hWnd;
	HDC			m_HDC;

	Player*		m_Player;
	Menu*		m_Menu;

public:
	GameManager();
	~GameManager();

	void Init(HWND hWnd);
	void Update();
	void Release();
};

