#include "Back.h"



Back::Back()
{
}

void Back::Init(HDC hdc, HINSTANCE hInst)
{
	MemDC = CreateCompatibleDC(hdc);
	m_NewBitmap = (HBITMAP)LoadImage(NULL, TEXT("back.bmp"),
		IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
	m_OldBitmap = (HBITMAP)SelectObject(MemDC, m_NewBitmap);

	BITMAP Bit_Info;

	GetObject(m_NewBitmap, sizeof(Bit_Info), &Bit_Info);
	m_size.cx = Bit_Info.bmWidth;
	m_size.cy = Bit_Info.bmHeight;
}

void Back::Draw(HDC hdc, int x, int y)
{
	StretchBlt(hdc, 0, 0, 1024, 768, MemDC, 0, 0, 102, 768, SRCCOPY);
}


Back::~Back()
{
	SelectObject(MemDC, m_OldBitmap);
	DeleteObject(m_NewBitmap);
	DeleteDC(MemDC);
}
