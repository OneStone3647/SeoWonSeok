#pragma once
#include "Mecro.h"

class Bitmap
{
private:
	HDC			MemDC;
	HBITMAP		m_NewBitmap;
	HBITMAP		m_OldBitmap;
	SIZE			m_Size;

public:
	Bitmap();
	~Bitmap();

	void Init(HDC hdc, LPCSTR fileName);
	
public:
	inline void Draw(HDC hdc, int x, int y)
	{
		TransparentBlt(hdc, x, y, m_Size.cx, m_Size.cy, MemDC, 0, 0, m_Size.cx, m_Size.cy, RGB(255, 0, 255));
	}
	// ��� �׸���
	inline void DrawBack(HDC hdc, int x, int y)
	{
		BitBlt(hdc, x, y, m_Size.cx, m_Size.cy, MemDC, 0, 0, SRCCOPY);
	}
	inline SIZE GetSize()
	{
		return m_Size;
	}
};

