#pragma once
#include "Mecro.h"

class Maptool
{
private:
	HWND		m_hWnd;
	HDC			m_MemDC;
	HBITMAP		m_NewBitmap;
	HBITMAP		m_OldBitmap;

	SIZE			m_ScreenSize;

public:
	Maptool();
	~Maptool();

public:
	void Init(HWND hWnd);
	void Release();
	void Update(LPARAM lParam);
};

