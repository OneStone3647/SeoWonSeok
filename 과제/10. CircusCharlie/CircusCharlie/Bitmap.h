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
	inline void Draw(HDC hdc, int x, int y, float sizeX = 1, float sizeY = 1)
	{
		// m_MemDC�� RGB�� �ش��ϴ� �κ��� ����ó���Ͽ� �׸� ��
		// m_MemDC�� �׸����� hdc�� �����Ѵ�.
		TransparentBlt(hdc, x, y, m_Size.cx * sizeX, m_Size.cy * sizeY, m_MemDC, 0, 0, m_Size.cx, m_Size.cy, RGB(255, 0, 255));
	}
	// ��� �׸���
	inline void DrawBack(HDC hdc, int x, int y, float sizeX = 1, float sizeY = 1)
	{
		// m_MemDC�� �׸����� hdc�� �����Ѵ�.
		BitBlt(hdc, x, y, m_Size.cx * sizeX, m_Size.cy * sizeY, m_MemDC, 0, 0, SRCCOPY);
	}
	inline SIZE GetSize()
	{
		return m_Size;
	}
};

