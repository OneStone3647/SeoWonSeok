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
	// hdc와 호환되는 DC를 만듭니다.
	m_MemDC = CreateCompatibleDC(hdc);
	// 파일 이름에 해당하는 비트맵을 불러옵니다.
	// 독립리소스를 가져올 경우 첫번째 인자에 NULL 값을 사용합니다.
	m_NewBitmap = (HBITMAP)LoadImage(NULL, FileName, IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION | LR_DEFAULTSIZE | LR_LOADFROMFILE);
	// m_MemDC에 m_NewBitmap을 연결하고 이전 비트맵을 m_OldBitmap에 저장합니다.
	m_OldBitmap = (HBITMAP)SelectObject(m_MemDC, m_NewBitmap);

	// 비트맵의 정보를 저장할 구조체입니다.
	BITMAP bitmapInfo;
	// m_NewBitmap의 정보를 bitmapInfo에 저장합니다.
	GetObject(m_NewBitmap, sizeof(bitmapInfo), &bitmapInfo);
	m_Size.cx = bitmapInfo.bmWidth;
	m_Size.cy = bitmapInfo.bmHeight;
}

void Bitmap::Release()
{
	// m_MemDC에 이전 비트맵을 연결합니다.
	SelectObject(m_MemDC, m_OldBitmap);
	DeleteObject(m_NewBitmap);
	// CreateCompatibleDC로 만들어진 DC는 DeleteDC로 지워야합니다.
	DeleteDC(m_MemDC);
}
