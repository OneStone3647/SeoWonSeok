#pragma once
#include <Windows.h>

class Back
{
private:
	HDC			MainMemDC;
	HDC			SubMemDC;
	HBITMAP		m_NewBitmap;
	HBITMAP		m_OldBitmap;

public:
	Back();

	void Init(HDC mainDC, HDC subDC, HBITMAP* newBitmap, HBITMAP* oldBitmap);
	void Draw(int x, int y);

	~Back();
};

