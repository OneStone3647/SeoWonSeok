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
	void Release();

public:
	// 설정한 RGB를 제외한 후 그리기
	inline void Draw(HDC hdc, int x, int y, int SizeX, int SizeY)
	{
		// m_MemDC에 그린 것을 hdc에 복사한다.
		TransparentBlt(hdc, x, y, SizeX, SizeY, m_MemDC, 0, 0, m_Size.cx, m_Size.cy, RGB(255, 0, 255));
	}

	inline SIZE GetSize()
	{
		return m_Size;
	}
};

