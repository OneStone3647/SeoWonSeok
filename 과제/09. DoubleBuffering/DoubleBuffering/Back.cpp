#include "Back.h"



Back::Back()
{
}

void Back::Init(HDC mainDC, HDC subDC, HBITMAP * newBitmap, HBITMAP * oldBitmap)
{
	MainMemDC = mainDC;
	SubMemDC = subDC;
	*newBitmap = (HBITMAP)LoadImage(NULL, "back.bmp", IMAGE_BITMAP, 0, 0
		, LR_CREATEDIBSECTION | LR_DEFAULTSIZE | LR_LOADFROMFILE);
	*oldBitmap = (HBITMAP)SelectObject(SubMemDC, *newBitmap);
}

void Back::Draw(int x, int y)
{
	BitBlt(MainMemDC, 0, 0, 1024, 768, SubMemDC, 0, 0, SRCCOPY);
}


Back::~Back()
{
}
