#include "Bitmap.h"



Bitmap::Bitmap()
{
}


Bitmap::~Bitmap()
{
	SelectObject(m_MemDC, m_OldBitmap);
	DeleteObject(m_NewBitmap);
	// CreateCompatibleDC로 만들어진 DC는 DeleteDC로 지워야한다.
	DeleteDC(m_MemDC);
}

void Bitmap::Init(HDC hdc, LPCSTR fileName)
{
	// hdc와 호환되는 DC를 만든다.
	m_MemDC = CreateCompatibleDC(hdc);
	// 파일 이름에 해당하는 비트맵을 불러온다.
	m_NewBitmap = (HBITMAP)LoadImage(NULL, fileName, IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION | LR_DEFAULTSIZE | LR_LOADFROMFILE);
	// m_MemDC에 m_NewBitmap을 연결한다.
	m_OldBitmap = (HBITMAP)SelectObject(m_MemDC, m_NewBitmap);

	// 비트맵의 정보를 저장할 구조체
	BITMAP BitMap_Info;
	// m_NewBitmap의 정보를 BitMap_Info에 저장한다.
	GetObject(m_NewBitmap, sizeof(BitMap_Info), &BitMap_Info);
	m_Size.cx = BitMap_Info.bmWidth;
	m_Size.cy = BitMap_Info.bmHeight;
}
