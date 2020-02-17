#pragma once
#include "Bitmap.h"

class Title
{
private:
	HWND		m_hWnd;
	HDC			m_TitleDC;
	Bitmap		m_Star[3];
	Bitmap		m_Icon;
	HBITMAP		m_TitleBitmap;
	HBITMAP		m_OldBitmap;

public:
	Title();
	~Title();

	void Init(HWND hWnd);
	void Update();
	void Input();
	void Draw();
};

