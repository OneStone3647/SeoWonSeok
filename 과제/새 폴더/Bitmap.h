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
	// ������ RGB�� ������ �� �׸���
	inline void Draw(HDC hdc, int x, int y, float Size = 1.0f)
	{
		// m_MemDC�� �׸� ���� hdc�� �����Ѵ�.
		TransparentBlt(hdc, x, y, m_Size.cx * Size, m_Size.cy * Size, m_MemDC, 0, 0, m_Size.cx, m_Size.cy, RGB(255, 0, 255));
	}

	inline SIZE GetSize()
	{
		return m_Size;
	}
};