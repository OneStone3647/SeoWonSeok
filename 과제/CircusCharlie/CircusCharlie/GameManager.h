#pragma once
#include "Menu.h"

class GameManager
{
private:
	HWND			m_hWnd;
	HDC				m_MemDC[2];
	HBITMAP			m_NewBitmap[2];
	HBITMAP			m_OldBitmap[2];

	Menu*			m_Menu;

public:
	GameManager();
	~GameManager();

	void Init(HWND hWnd);
	void Release();
	void Update();
};

