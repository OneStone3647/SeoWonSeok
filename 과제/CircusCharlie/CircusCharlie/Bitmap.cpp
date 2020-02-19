#include "Bitmap.h"



Bitmap::Bitmap()
{
}


Bitmap::~Bitmap()
{
	SelectObject(m_MemDC, m_OldBitmap);
	DeleteObject(m_NewBitmap);
	// CreateCompatibleDC�� ������� DC�� DeleteDC�� �������Ѵ�.
	DeleteDC(m_MemDC);
}

void Bitmap::Init(HDC hdc, LPCSTR fileName)
{
	// hdc�� ȣȯ�Ǵ� DC�� �����.
	m_MemDC = CreateCompatibleDC(hdc);
	// ���� �̸��� �ش��ϴ� ��Ʈ���� �ҷ��´�.
	m_NewBitmap = (HBITMAP)LoadImage(NULL, fileName, IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION | LR_DEFAULTSIZE | LR_LOADFROMFILE);
	// m_MemDC�� m_NewBitmap�� �����Ѵ�.
	m_OldBitmap = (HBITMAP)SelectObject(m_MemDC, m_NewBitmap);

	// ��Ʈ���� ������ ������ ����ü
	BITMAP BitMap_Info;
	// m_NewBitmap�� ������ BitMap_Info�� �����Ѵ�.
	GetObject(m_NewBitmap, sizeof(BitMap_Info), &BitMap_Info);
	m_Size.cx = BitMap_Info.bmWidth;
	m_Size.cy = BitMap_Info.bmHeight;
}
