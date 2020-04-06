#pragma once
#include "Player.h"
#include "Menu.h"
#include "Field.h"

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
	Field			m_Field;

public:
	GameManager();
	~GameManager();

public:
	void Init(HWND hWnd);
	void Release();
	void Update();
	void DrawStage();
	void FieldLoad(int FieldIndex);
	void DrawField();
	void DrawBackground();
};

