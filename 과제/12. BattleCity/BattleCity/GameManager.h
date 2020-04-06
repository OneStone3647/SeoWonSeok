#pragma once
#include "Player.h"
#include "Menu.h"

class GameManager : public Singleton<GameManager>
{
private:
	HWND		m_hWnd;
	HDC			m_MemDC;
	HBITMAP		m_NewBitmap;
	HBITMAP		m_OldBitmap;

	SIZE			m_ScreenSize;

	bool			m_GameStart;

	Player			m_Player;
	Menu			m_Menu;

	HBRUSH		m_BlackBrush;
	HBRUSH		m_GrayBrush;

public:
	GameManager();
	~GameManager();

public:
	void Init(HWND hWnd);
	void Release();
	void Update();
};

