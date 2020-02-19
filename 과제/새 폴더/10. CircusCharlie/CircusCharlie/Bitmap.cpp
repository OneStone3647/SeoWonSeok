#include "Bitmap.h"



Bitmap::Bitmap()
{
}


Bitmap::~Bitmap()
{
	SelectObject(MemDC, m_OldBitmap);
	DeleteObject(m_NewBitmap);
	DeleteDC(MemDC);
}

void Bitmap::Init(HDC hdc, LPCSTR fileName)
{
	MemDC = CreateCompatibleDC(hdc);
	m_NewBitmap = (HBITMAP)LoadImage(NULL, fileName, IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION | LR_DEFAULTSIZE | LR_LOADFROMFILE);
	m_OldBitmap = (HBITMAP)SelectObject(MemDC, m_NewBitmap);

	BITMAP BitMap_Info;
	GetObject(m_NewBitmap, sizeof(BitMap_Info), &BitMap_Info);
	m_Size.cx = BitMap_Info.bmWidth;
	m_Size.cy = BitMap_Info.bmHeight;
}
