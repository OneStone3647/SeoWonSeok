#include "Card.h"



Card::Card()
{
}

void Card::Init(HDC hdc, HINSTANCE hInst, int id)
{
	MemDC = CreateCompatibleDC(hdc);											// hdc�� ������ ������ DC�� �޸𸮻� ������ش�.
	m_NewCard = (HBITMAP)LoadBitmap(hInst, MAKEINTRESOURCE(id));		// id�� �ش��ϴ� ��Ʈ���� �ҷ��´�.
	m_OldCard = (HBITMAP)SelectObject(MemDC, m_NewCard);					// ���� ������ Bitmap ���� & ������ Bitmap ����

	BITMAP Card_Info;																	// Bitmap�� ������ ���� ����ü
	// �غ�� ��Ʈ���� ������ �����´�.
	// 1��° ���� : �����ϰ��� �ϴ� ������Ʈ
	// 2��° ���� : ���ۿ� ����� ������ ũ��
	// 3��° ���� : ������Ʈ�� ������ ���� ���� ����ü
	GetObject(m_NewCard, sizeof(Card_Info), &Card_Info);
	m_Size.cx = Card_Info.bmWidth;
	m_Size.cy = Card_Info.bmHeight;
}

void Card::Draw(HDC hdc, int x, int y, int spX, int spY)
{
	BitBlt(hdc, x, y, m_Size.cx, m_Size.cy, MemDC, 0, 0, SRCCOPY);
}

SIZE Card::GetCardSize()
{
	return m_Size;
}


Card::~Card()
{
	SelectObject(MemDC, m_OldCard);		//������ Bitmap�� �����Ѵ�.
	DeleteObject(m_NewCard);					// ���� ������ Bitmap�� �����Ѵ�.
	DeleteDC(MemDC);							// �޸�DC�� �����Ѵ�.
}
