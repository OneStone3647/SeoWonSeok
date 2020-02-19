#pragma once
#include "Player.h"
#include "Menu.h"

enum BACKINDEX
{
	BACKINDEX_BACK,
	BACKINDEX_DECO,
	BACKINDEX_NORMAL1,
	BACKINDEX_NORMAL2
};

enum MEMDCINDEX
{
	MEMDCINDEX_MAIN,
	MEMDCINDEX_BACK
};

enum BITMAPINDEX
{
	BITMAPINDEX_MAIN,
	BITMAPINDEX_BACK
};

class GameManager
{
private:
	HWND		m_hWnd;
	HDC			m_MemDC[2];
	HBITMAP		m_NewBitmap[2];
	HBITMAP		m_OldBitmap[2];

	Bitmap		m_Back[4];

	Player*		m_Player;
	Menu*		m_Menu;

public:
	GameManager();
	~GameManager();

	void Init(HWND hWnd);
	void Release();
	void Update();
	void DrawBackGround();
};

