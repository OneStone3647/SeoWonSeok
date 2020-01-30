#include "Bitmap.h"



Bitmap::Bitmap()
{
	newBitmap == NULL;
}


Bitmap::~Bitmap()
{
}

void Bitmap::Init()
{
	tmpBitmap.SetLoadBitmap(g_hInst, BitmapCount);
	newBitmap = tmpBitmap.GetBitmap();
	oldBitmap = (HBITMAP)SelectObject(CardDC, newBitmap);
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
	// 사용하고 잇는 Bitmap객체가 있으면 해당 객체를 삭제
	if (newBitmap != NULL)
	{
		DeleteObject(newBitmap);
	}
	newBitmap = LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_BITMAP1 + BitmapCount));
}

void Bitmap::Draw()
{
}
