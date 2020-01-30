#pragma once
#include <iostream>
#include <Windows.h>
#include "resource.h"

class Bitmap
{
private:
	HBITMAP newBitmap;
public:
	Bitmap();
	~Bitmap();
public:
	void Release();
	void SetLoadBitmap(HINSTANCE g_hInst, int BitmapCount);
	HBITMAP GetBitmap()
	{
		return newBitmap;
	}
};

