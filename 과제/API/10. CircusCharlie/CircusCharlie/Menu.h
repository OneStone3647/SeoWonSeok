#pragma once
#include "Bitmap.h"

enum SELECTMENU
{
	SELECTMENU_GAMESTART,
	SELECTMENU_EXIT
};

class Menu
{
private:
	HWND					m_hWnd;
	HDC						m_MemDC;
	HBITMAP					m_NewBitmap;
	HBITMAP					m_OldBitmap;

	Bitmap				m_Icon;

	Bitmap				m_Star[3];
	int						m_StarIndex;

	HBRUSH				m_NewBrush;
	HBRUSH				m_OldBrush;

	float					m_AnimTime;
	float					m_StartAnimTimer;
	float					m_CurAnimTimer;

	SELECTMENU		m_Select;
	bool*					m_bGameStartFlag;

public:
	Menu();
	~Menu();

public:
	void Init(HWND hWnd, bool* GameStartFlag);
	void Update();
	void Input();
	void DrawMenu(int Start_X, int Start_Y, int Width, int Height);
	void DrawBackGround(int Start_X, int Start_Y, int Width, int Height);
};

