#include "Back.h"



Back::Back()
{
}


Back::~Back()
{
	//SelectObject(m_MemDC, m_OldBitmap);
	//DeleteObject(m_NewBitmap);
	//// CreateCompatibleDC�� ������� DC�� DeleteDC�� �������Ѵ�.
	//DeleteDC(m_MemDC);
}

void Back::Init(HDC BackDC)
{
	//// GetDC�� ���� DC�� �޴´�.
	//HDC hdc = GetDC(hWnd);

	//// hdc�� ȣȯ�Ǵ� DC�� �����.
	//m_MemDC = CreateCompatibleDC(hdc);
	//// hdc�� ȣȯ�Ǵ� ��Ʈ���� �� SceenWidth, ���� ScreeenHeight�� ũ��� �����.
	//m_NewBitmap = CreateCompatibleBitmap(hdc, ScreenWidth, ScreenHeight);
	//// m_MemDC�� m_NewBitmap�� �����Ѵ�.
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
	//// GetDC�� ���� DC�� �޴´�.
	//HDC hdc = GetDC(m_hWnd);

	//for (int i = 0; i < 20; i++)
	//{
	//	m_Back.DrawBack(m_MemDC, i * m_Back.GetSize().cx, 300);
	//}

	//// ���� �׸���
	//for (int i = 0; i < 21; i++)
	//{
	//	m_Normal1.DrawBack(m_MemDC, i*m_Normal1.GetSize().cx, 236);
	//}

	//// �ڳ��� �׸���
	//m_Deco.DrawBack(m_MemDC, m_Deco.GetSize().cx, 233);

	//// ���� �׸� ���� ���� �������� hdc�� �׸���.
	//BitBlt(hdc, 0, 0, ScreenWidth, ScreenHeight, m_MemDC, 0, 0, SRCCOPY);

	//ReleaseDC(m_hWnd, hdc);

	for (int i = 0; i < 20; i++)
	{
		m_Back.DrawBack(m_BackDC, i * m_Back.GetSize().cx, 300);
	}

	// ���� �׸���
	for (int i = 0; i < 21; i++)
	{
		m_Normal1.DrawBack(m_BackDC, i*m_Normal1.GetSize().cx, 236);
	}

	// �ڳ��� �׸���
	m_Deco.DrawBack(m_BackDC, m_Deco.GetSize().cx, 233);

	// ���� �׸� ���� ���� �������� hdc�� �׸���.
	//BitBlt(m_BackDC, 0, 0, ScreenWidth, ScreenHeight, m_MemDC, 0, 0, SRCCOPY);
}
