#include "Bitmap.h"



Bitmap::Bitmap()
{
}


Bitmap::~Bitmap()
{
	Release();
}

void Bitmap::Init(HDC hdc, LPCSTR FileName)
{
	// hdc와 호환되는 DC를 만든다.
	m_MemDC = CreateCompatibleDC(hdc);
	// 파일이름에 해당하는 비트맵을 불러온다.
	// 독립리소스를 가져올 경우 첫번째 인자에 NULL 값을 사용한다.
	m_NewBitmap = (HBITMAP)LoadImage(NULL, FileName, IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION | LR_DEFAULTSIZE | LR_LOADFROMFILE);
	// m_MemDC에 m_NewBitmap을 연결하고 이전 비트맵을 m_OldBitmap에 저장한다.
	m_OldBitmap = (HBITMAP)SelectObject(m_MemDC, m_NewBitmap);

	// 비트맵의 정보를 저장할 구조체
	BITMAP Bitmap_Info;
	// m_NewBitmap의 정보를 Bitmap_Info에 저장한다.
	GetObject(m_NewBitmap, sizeof(Bitmap_Info), &Bitmap_Info);
	m_Size.cx = Bitmap_Info.bmWidth;
	m_Size.cy = Bitmap_Info.bmHeight;
}

void Bitmap::Release()
{
	// m_MemDC에 이전 비트맵을 연결한다.
	SelectObject(m_MemDC, m_OldBitmap);
	DeleteObject(m_NewBitmap);
	// CreateCompatibleDC로 만들어 진 DC는 DeleteDC로 지워야한다.
	DeleteDC(m_MemDC);
}
