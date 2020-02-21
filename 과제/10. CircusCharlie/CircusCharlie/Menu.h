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

	Bitmap					m_Star[3];
	int							m_StarIndex;
	Bitmap					m_Icon;

	HBRUSH					m_NewBrush;
	HBRUSH					m_OldBrush;

	float							m_StartTimer;
	float							m_AnimTimer;
	float							m_AnimTime;

	SELECTMENU			m_Select;
	bool						m_bGameStart;

public:
	Menu();
	~Menu();

	void Init(HWND hWnd);
	void Update();
	void Input();
	void DrawMenu(int Start_X, int Start_Y, int Width, int Height);
	void DrawBackGround(int start_X, int start_Y, int width, int height);

public:
	bool GetGameStartFlag()
	{
		return m_bGameStart;
	}
};

