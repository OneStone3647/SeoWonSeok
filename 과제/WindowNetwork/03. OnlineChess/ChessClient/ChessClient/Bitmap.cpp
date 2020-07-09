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
	// hdc�� ȣȯ�Ǵ� DC�� ����ϴ�.
	m_MemDC = CreateCompatibleDC(hdc);
	// ���� �̸��� �ش��ϴ� ��Ʈ���� �ҷ��ɴϴ�.
	// �������ҽ��� ������ ��� ù��° ���ڿ� NULL ���� ����մϴ�.
	m_NewBitmap = (HBITMAP)LoadImage(NULL, FileName, IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION | LR_DEFAULTSIZE | LR_LOADFROMFILE);
	// m_MemDC�� m_NewBitmap�� �����ϰ� ���� ��Ʈ���� m_OldBitmap�� �����մϴ�.
	m_OldBitmap = (HBITMAP)SelectObject(m_MemDC, m_NewBitmap);

	// ��Ʈ���� ������ ������ ����ü�Դϴ�.
	BITMAP bitmapInfo;
	// m_NewBitmap�� ������ bitmapInfo�� �����մϴ�.
	GetObject(m_NewBitmap, sizeof(bitmapInfo), &bitmapInfo);
	m_Size.cx = bitmapInfo.bmWidth;
	m_Size.cy = bitmapInfo.bmHeight;
}

void Bitmap::Release()
{
	// m_MemDC�� ���� ��Ʈ���� �����մϴ�.
	SelectObject(m_MemDC, m_OldBitmap);
	DeleteObject(m_NewBitmap);
	// CreateCompatibleDC�� ������� DC�� DeleteDC�� �������մϴ�.
	DeleteDC(m_MemDC);
}
