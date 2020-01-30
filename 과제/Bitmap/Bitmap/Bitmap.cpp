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
	SetLoadBitmap(g_hInst, BitmapCount);
	oldBitmap = (HBITMAP)SelectObject(MemDC, newBitmap);
}

void Bitmap::Release()
{
	if (newBitmap != NULL)
	{
		DeleteObject(newBitmap);
	}
}

void Bitmap::SetLoadBitmap(HINSTANCE g_hInst, int BitmapCount)
{
	// ����ϰ� �մ� Bitmap��ü�� ������ �ش� ��ü�� ����
	if (newBitmap != NULL)
	{
		DeleteObject(newBitmap);
	}
	newBitmap = LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_BITMAP1 + BitmapCount));
}
