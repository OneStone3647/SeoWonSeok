#pragma once
#include "Mecro.h"

class Bitmap
{
private:
	HDC				m_MemDC;
	HBITMAP			m_NewBitmap;
	HBITMAP			m_OldBitmap;
	SIZE				m_Size;

public:
	Bitmap();
	~Bitmap();

public:
	void Init(HDC hdc, LPCSTR FileName);

public:
	inline void Draw(HDC hdc, int x, int y, float SizeX = 1.5f, float SizeY = 1.5f)
	{
		// m_MemDC에 RGB에 해당하는 부분을 투명처리하여 그린 후
		// m_MemDC에 그린 것을 hdc에 복사한다.
		TransparentBlt(hdc, x, y, m_Size.cx * SizeX, m_Size.cy * SizeY, m_MemDC, 0, 0, m_Size.cx, m_Size.cy, RGB(255, 0, 255));
	}

	// 그대로 그리기
	inline void OriginDraw(HDC hdc, int x, int y, float SizeX = 1.5f, float SizeY = 1.5f)
	{
		// m_MemDC에 그린 것을 hdc에 복사한다.
		StretchBlt(hdc, x, y, m_Size.cx * SizeX, m_Size.cy * SizeY, m_MemDC, 0, 0, m_Size.cx, m_Size.cy, SRCCOPY);
	}

	inline SIZE GetSize()
	{
		return m_Size;
	}
};

