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
	SIZE	m_Size;			// ũ�� ����ü

public:
	Bitmap();

	void Init(HDC hdc, HINSTANCE hInst, int id);					// �ʱ�ȭ
	void Draw(HDC hdc, int x, int y, int spX = 1, int spY = 1);		// �׸���(4, 5��° ���ڴ� scale�� ��Ÿ��)

	~Bitmap();

	inline SIZE GetBitmapSize()
	{
		return m_Size;
	}
};

