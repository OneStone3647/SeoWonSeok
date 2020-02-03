#include "Card.h"



Card::Card()
{
}

void Card::Init(HDC hdc, HINSTANCE hInst, int id)
{
	MemDC = CreateCompatibleDC(hdc);											// hdc와 동일한 정보의 DC를 메모리상에 만들어준다.
	m_NewCard = (HBITMAP)LoadBitmap(hInst, MAKEINTRESOURCE(id));		// id에 해당하는 비트맵을 불러온다.
	m_OldCard = (HBITMAP)SelectObject(MemDC, m_NewCard);					// 새로 생성한 Bitmap 선택 & 기존의 Bitmap 저장

	BITMAP Card_Info;																	// Bitmap의 정보를 받을 구조체
	// 준비된 비트맵의 정보를 가져온다.
	// 1번째 인자 : 조사하고자 하는 오브젝트
	// 2번째 인자 : 버퍼에 기록할 정보의 크기
	// 3번째 인자 : 오브젝트의 정보를 리턴 받을 구조체
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
	SelectObject(MemDC, m_OldCard);		//기존의 Bitmap을 선택한다.
	DeleteObject(m_NewCard);					// 새로 생성한 Bitmap을 삭제한다.
	DeleteDC(MemDC);							// 메모리DC를 삭제한다.
}
