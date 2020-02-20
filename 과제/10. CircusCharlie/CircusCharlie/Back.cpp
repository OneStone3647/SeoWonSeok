#include "Back.h"



Back::Back()
{
}


Back::~Back()
{
	//SelectObject(m_MemDC, m_OldBitmap);
	//DeleteObject(m_NewBitmap);
	//// CreateCompatibleDC로 만들어진 DC는 DeleteDC로 지워야한다.
	//DeleteDC(m_MemDC);
}

void Back::Init(HDC BackDC)
{
	//// GetDC를 통해 DC를 받는다.
	//HDC hdc = GetDC(hWnd);

	//// hdc와 호환되는 DC를 만든다.
	//m_MemDC = CreateCompatibleDC(hdc);
	//// hdc와 호환되는 비트맵을 폭 SceenWidth, 높이 ScreeenHeight의 크기로 만든다.
	//m_NewBitmap = CreateCompatibleBitmap(hdc, ScreenWidth, ScreenHeight);
	//// m_MemDC에 m_NewBitmap을 연결한다.
	//m_OldBitmap = (HBITMAP)SelectObject(m_MemDC, m_NewBitmap);

	m_BackDC = BackDC;
	//m_MemDC = CreateCompatibleDC(BackDC);
	//m_NewBitmap = CreateCompatibleBitmap(BackDC, ScreenWidth, ScreenHeight);
	//m_OldBitmap = (HBITMAP)SelectObject(m_MemDC, m_NewBitmap);

	m_Back.Init(m_BackDC, "Bitmap\\back.bmp");
	m_Deco.Init(m_BackDC, "Bitmap\\back_deco.bmp");
	m_Normal1.Init(m_BackDC, "Bitmap\\back_normal.bmp");
	m_Normal2.Init(m_BackDC, "Bitmap\\back_normal2.bmp");
}

void Back::Update()
{
	DrawBack();
}

void Back::DrawBack()
{
	//// GetDC를 통해 DC를 받는다.
	//HDC hdc = GetDC(m_hWnd);

	//for (int i = 0; i < 20; i++)
	//{
	//	m_Back.DrawBack(m_MemDC, i * m_Back.GetSize().cx, 300);
	//}

	//// 관중 그리기
	//for (int i = 0; i < 21; i++)
	//{
	//	m_Normal1.DrawBack(m_MemDC, i*m_Normal1.GetSize().cx, 236);
	//}

	//// 코끼리 그리기
	//m_Deco.DrawBack(m_MemDC, m_Deco.GetSize().cx, 233);

	//// 숨겨 그린 것을 원래 보여야할 hdc에 그린다.
	//BitBlt(hdc, 0, 0, ScreenWidth, ScreenHeight, m_MemDC, 0, 0, SRCCOPY);

	//ReleaseDC(m_hWnd, hdc);

	for (int i = 0; i < 20; i++)
	{
		m_Back.DrawBack(m_BackDC, i * m_Back.GetSize().cx, 300);
	}

	// 관중 그리기
	for (int i = 0; i < 21; i++)
	{
		m_Normal1.DrawBack(m_BackDC, i*m_Normal1.GetSize().cx, 236);
	}

	// 코끼리 그리기
	m_Deco.DrawBack(m_BackDC, m_Deco.GetSize().cx, 233);

	// 숨겨 그린 것을 원래 보여야할 hdc에 그린다.
	//BitBlt(m_BackDC, 0, 0, ScreenWidth, ScreenHeight, m_MemDC, 0, 0, SRCCOPY);
}
