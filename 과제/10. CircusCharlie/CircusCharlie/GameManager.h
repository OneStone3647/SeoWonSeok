#pragma once
#include "Menu.h"

class GameManager
{
private:
	HWND			m_hWnd;
	HDC				m_MemDC;
	HBITMAP			m_NewBitmap;
	HBITMAP			m_OldBitmap;

	Menu*			m_Menu;
	bool				m_bGameStart;

public:
	GameManager();
	~GameManager();

public:
	void Init(HWND hWnd);
	void Release();
	void Update();
};

