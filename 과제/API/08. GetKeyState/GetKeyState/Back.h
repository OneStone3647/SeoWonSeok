#pragma once
#include <Windows.h>

class Back
{
private:
	HDC			MemDC;
	HBITMAP		m_NewBitmap;
	HBITMAP		m_OldBitmap;

public:
	Back();

	void Init(HDC hdc, HINSTANCE hInst);
	void Draw(HDC hdc, int x, int y);

	~Back();
};

