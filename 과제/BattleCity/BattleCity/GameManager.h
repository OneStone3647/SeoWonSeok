#pragma once
#include "Mecro.h"

class GameManager : public Singleton<GameManager>
{
private:
	HWND		m_hWnd;
	HDC			m_MemDC;
	HBITMAP		m_NewBitmap;
	HBITMAP		m_OldBitmap;

	SIZE			m_ScreenSize;

public:
	GameManager();
	~GameManager();

public:
	void Init(HWND hWnd);
	void Release();
	void Update();
};

