#pragma once
#include "Mecro.h"

class Bitmap
{
private:
	HDC					m_MemDC;
	HBITMAP				m_NewBitmap;
	HBITMAP				m_OldBitmap;
	SIZE					m_Size;

public:
	Bitmap();
	~Bitmap();

	void Init(HDC hdc, LPCSTR fileName);

public:
	inline void Draw(HDC hdc, int x, int y)
	{
		// m_MemDC에 RGB에 해당하는 부분을 투명처리하여 그린 후
		// m_MemDC에 그린것을 hdc에 복사한다..
		TransparentBlt(hdc, x, y, m_Size.cx, m_Size.cy, m_MemDC, 0, 0, m_Size.cx, m_Size.cy, RGB(255, 0, 255));
	}
	// 배경 그리기
	inline void DrawBack(HDC hdc, int x, int y)
	{
		// m_MemDC에 그린것을 hdc에 복사한다.
		BitBlt(hdc, x, y, m_Size.cx, m_Size.cy, m_MemDC, 0, 0, SRCCOPY);
	}
	inline SIZE GetSize()
	{
		return m_Size;
	}
};

