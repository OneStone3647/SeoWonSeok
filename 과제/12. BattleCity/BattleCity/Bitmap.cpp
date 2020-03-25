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
	// hdc�� ȣȯ�Ǵ� DC�� �����.
	m_MemDC = CreateCompatibleDC(hdc);
	// �����̸��� �ش��ϴ� ��Ʈ���� �ҷ��´�.
	// �������ҽ��� ������ ��� ù��° ���ڿ� NULL ���� ����Ѵ�.
	m_NewBitmap = (HBITMAP)LoadImage(NULL, FileName, IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION | LR_DEFAULTSIZE | LR_LOADFROMFILE);
	// m_MemDC�� m_NewBitmap�� �����ϰ� ���� ��Ʈ���� m_OldBitmap�� �����Ѵ�.
	m_OldBitmap = (HBITMAP)SelectObject(m_MemDC, m_NewBitmap);

	// ��Ʈ���� ������ ������ ����ü
	BITMAP Bitmap_Info;
	// m_NewBitmap�� ������ Bitmap_Info�� �����Ѵ�.
	GetObject(m_NewBitmap, sizeof(Bitmap_Info), &Bitmap_Info);
	m_Size.cx = Bitmap_Info.bmWidth;
	m_Size.cy = Bitmap_Info.bmHeight;
}

void Bitmap::Release()
{
	// m_MemDC�� ���� ��Ʈ���� �����Ѵ�.
	SelectObject(m_MemDC, m_OldBitmap);
	DeleteObject(m_NewBitmap);
	// CreateCompatibleDC�� ����� �� DC�� DeleteDC�� �������Ѵ�.
	DeleteDC(m_MemDC);
}
