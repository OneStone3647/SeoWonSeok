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
	HDC						m_MenuDC;
	HBITMAP					m_NewBitmap;
	HBITMAP					m_OldBitmap;

	Bitmap					m_Star[3];
	Bitmap					m_Icon;

	HBRUSH					m_NewBrush;
	HBRUSH					m_OldBrush;

	int							m_StartTimer;
	int							m_AnimTimer;

	int							m_StarIndex;

	SELECTMENU			m_Select;

public:
	Menu();
	~Menu();

	void Init(HWND hWnd);
	void Update();
	void Input();
	void DrawMenu(int start_X, int start_Y, int width, int height);
	void DrawBackGround(int start_X, int start_Y, int width, int height);

public:
	inline HDC GetHDC()
	{
		return m_MenuDC;
	}
};

