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
	void Init();
	void Release();
	void SetLoadBitmap(HINSTANCE g_hInst, int BitmapCount);
	void Draw();
	HBITMAP GetBitmap()
	{
		return newBitmap;
	}
};

