#pragma once
#include <iostream>
#include <Windows.h>
#include "resource.h"

class Bitmap
{
private:
	HBITMAP newBitmap, oldBitmap;
public:
	Bitmap();
	~Bitmap();
public:
	void Init(HINSTANCE g_hInst, HDC MemDC, int BitmapCount);
	void Release();
	void SetLoadBitmap(HINSTANCE g_hInst, int BitmapCount);
	HBITMAP GetBitmap()
	{
		return newBitmap;
	}
};

