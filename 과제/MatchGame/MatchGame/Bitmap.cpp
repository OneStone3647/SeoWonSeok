#include "Bitmap.h"



Bitmap::Bitmap()
{
}

void Bitmap::Init(HDC hdc, HINSTANCE hInst, int id)
{
	MemDC = CreateCompatibleDC(hdc);									// hdc�� ������ ������ DC�� �޸𸮻� ������ش�.
	m_NewBitmap = (HBITMAP)LoadBitmap(hInst, MAKEINTRESOURCE(id));		// id�� �ش��ϴ� ��Ʈ���� �ҷ��´�.
	m_OldBitmap = (HBITMAP)SelectObject(MemDC, m_NewBitmap);			// ���� ������ Bitmap ���� & ������ Bitmap ����

	BITMAP Bitmap_Info;													// Bitmap�� ������ ���� ����ü
	// �غ�� ��Ʈ���� ������ �����´�.
	// 1��° ���� : �����ϰ��� �ϴ� ������Ʈ
	// 2��° ���� : ���ۿ� ����� ������ ũ��
	// 3��° ���� : ������Ʈ�� ������ ���� ���� ����ü
	GetObject(m_NewBitmap, sizeof(Bitmap_Info), &Bitmap_Info);
	m_Size.cx = Bitmap_Info.bmWidth;
	m_Size.cy = Bitmap_Info.bmHeight;
}

void Bitmap::Draw(HDC hdc, int x, int y, int spX, int spY)
{
	BitBlt(hdc, x, y, m_Size.cx, m_Size.cy, MemDC, 0, 0, SRCCOPY);
}


Bitmap::~Bitmap()
{
	SelectObject(MemDC, m_OldBitmap);	// ������ Bitmap�� �����Ѵ�.
	DeleteObject(m_NewBitmap);			// ���� ������ Bitmap�� �����Ѵ�.
	DeleteDC(MemDC);					// �޸�DC�� �����Ѵ�.
}
