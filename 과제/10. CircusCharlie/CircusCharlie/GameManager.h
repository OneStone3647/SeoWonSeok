#pragma once
#include "Menu.h"
#include "Field.h"

class GameManager
{
private:
	HWND			m_hWnd;
	HDC				m_MemDC;
	HBITMAP			m_NewBitmap;
	HBITMAP			m_OldBitmap;

	bool				m_bGameStart;
	bool				m_bWin;

	Menu*			m_Menu;
	Field*				m_Field;

	float				m_CameraX;

public:
	GameManager();
	~GameManager();

public:
	void Init(HWND hWnd);
	void Release();
	void Update();
};

