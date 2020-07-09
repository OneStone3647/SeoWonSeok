#pragma once
#include "Menu.h"
#include "Field.h"

class GameManager
{
private:
	HWND		m_hWnd;
	HDC			m_MemDC;
	HBITMAP		m_NewBitmap;
	HBITMAP		m_OldBitmap;

	SIZE			m_ScreenSize;

	bool			m_GameStart;

	Menu*		m_Menu;
	Field*			m_Field;

public:
	GameManager();
	~GameManager();

public:
	void Init(HWND hWnd);
	void Init();
	void Release();
	void Update();
	void DrawStage();
};

