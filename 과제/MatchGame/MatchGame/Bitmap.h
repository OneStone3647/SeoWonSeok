#pragma once
#include <iostream>
#include <Windows.h>
#include "resource.h"

class Bitmap
{
private:
	HDC		MemDC;
	HBITMAP	m_NewBitmap;
	HBITMAP m_OldBitmap;
	SIZE	m_Size;			// 크기 구조체

public:
	Bitmap();

	void Init(HDC hdc, HINSTANCE hInst, int id);					// 초기화
	void Draw(HDC hdc, int x, int y, int spX = 1, int spY = 1);		// 그리기(4, 5번째 인자는 scale을 나타냄)

	~Bitmap();

	inline SIZE GetBitmapSize()
	{
		return m_Size;
	}
};

