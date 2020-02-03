#include "Bitmap.h"



Bitmap::Bitmap()
{
	newBitmap == NULL;
	oldBitmap = NULL;
}


Bitmap::~Bitmap()
{
}

void Bitmap::Init(HINSTANCE g_hInst, HDC MemDC, int BitmapCount)
{
	SetLoadBitmap(g_hInst, MemDC, BitmapCount);
	oldBitmap = (HBITMAP)SelectObject(MemDC, newBitmap);
}

void Bitmap::Release(HDC MemDC)
{
	if (newBitmap != NULL)
	{
		SelectObject(MemDC, oldBitmap);
		DeleteObject(newBitmap);
	}
}

void Bitmap::SetLoadBitmap(HINSTANCE g_hInst, HDC MemDC, int BitmapCount)
{
	// ����ϰ� �մ� Bitmap��ü�� ������ �ش� ��ü�� ����
	Release(MemDC);
	newBitmap = LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_BITMAP1 + BitmapCount));
}
