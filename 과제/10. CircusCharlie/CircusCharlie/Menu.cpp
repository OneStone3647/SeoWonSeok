#include "Menu.h"



Menu::Menu()
{
}


Menu::~Menu()
{
}

void Menu::Init(HWND hWnd)
{
	m_hWnd = hWnd;
	HDC hdc = GetDC(hWnd);

	m_MenuDC = CreateCompatibleDC(hdc);
	m_NewBitmap = CreateCompatibleBitmap(hdc, ScreenWidth, ScreenHeight);
	m_OldBitmap = (HBITMAP)SelectObject(m_MenuDC, m_NewBitmap);

	m_Star[0].Init(m_MenuDC, "Bitmap\\star.bmp");
	m_Star[1].Init(m_MenuDC, "Bitmap\\star1.bmp");
	m_Star[2].Init(m_MenuDC, "Bitmap\\star2.bmp");
	m_Icon.Init(m_MenuDC, "Bitmap\\icon.bmp");

	ReleaseDC(hWnd, hdc);

	m_StartTimer = GetTickCount();
	m_AnimTimer = 0;

	m_StarIndex = 0;

	m_Select = SELECTMENU_GAMESTART;

}

void Menu::Update()
{
	// ó�� ������� �� �� ���ڰ� �ʰ� ������ ���� ���� �ϱ� ���ؼ� 500�� ���Ѵ�.
	m_AnimTimer = GetTickCount() + 500;
	Input();
	DrawMenu((ScreenWidth / 5) * 2 - 10, ScreenHeight / 3 - 35, 20, 7);
}

void Menu::Input()
{
	if ((GetKeyState(VK_UP) | GetKeyState(VK_DOWN)) & 0x8000)
	{
		// �������� ����� �뵵�� ���� �귯�÷� ����� ��ĥ���ش�.
		DrawBackGround(ScreenWidth / 2, ScreenHeight / 3 + 120, ScreenWidth / 2 + 100, ScreenHeight / 3 + 220);
		if (GetKeyState(VK_UP) & 0x8000)
		{
			m_Select = SELECTMENU_GAMESTART;
		}
		if (GetKeyState(VK_DOWN) & 0x8000)
		{
			m_Select = SELECTMENU_EXIT;
		}
	}
	// ���� Ű
	if (GetKeyState(VK_RETURN) & 0x8000)
	{
		switch (m_Select)
		{
		case SELECTMENU_GAMESTART:

			break;
		case SELECTMENU_EXIT:
			PostQuitMessage(0);
			break;
		}
	}
}

void Menu::DrawMenu(int start_X, int start_Y, int width, int height)
{
	HDC hdc = GetDC(m_hWnd);
	SIZE BitmapSize = m_Star[0].GetSize();

	// �� ���ڸ� �׸���.
	if (m_AnimTimer - m_StartTimer >= 500)
	{
		for (int y = 0; y < height; y++)
		{
			for (int x = 0; x < width; x++)
			{
				if ((x == 0 || x == width - 1) || (y == 0 || y == height - 1))
				{
					m_Star[m_StarIndex].Draw(m_MenuDC, start_X + (x * BitmapSize.cx), start_Y + (y * BitmapSize.cy));
					m_StarIndex = ++m_StarIndex % 3;
				}
			}
		}
		m_StartTimer = m_AnimTimer;
	}

	// ������ ��ǥ�� ���� �߾� ��ǥ�� �ȴ�.
	SetTextAlign(hdc, TA_CENTER);
	TextOut(hdc, ScreenWidth / 2, (ScreenHeight / 3), "  Circus Charlie  ", strlen("  Circus Charlie  "));
	TextOut(hdc, ScreenWidth / 2, ScreenHeight / 3 + 140, "  Game Start  ", strlen("  Game Start  "));
	TextOut(hdc, ScreenWidth / 2, ScreenHeight / 3 + 200, "  Exit  ", strlen("  Exit  "));

	// �Է¿� ���� �ش��ϴ� ��ġ�� �������� �׸���.
	switch (m_Select)
	{
	case SELECTMENU_GAMESTART:
		m_Icon.Draw(hdc, ScreenWidth / 2 - 100, ScreenHeight / 3 + 140);
		break;
	case SELECTMENU_EXIT:
		m_Icon.Draw(hdc, ScreenWidth / 2 - 100, ScreenHeight / 3 + 200);
		break;
	}

	// ���� �׸� ���� ���� �������� hdc�� �׸���.
	BitBlt(hdc, 0, 0, ScreenWidth, ScreenHeight, m_MenuDC, 0, 0, SRCCOPY);

	ReleaseDC(m_hWnd, hdc);
}

void Menu::DrawBackGround(int start_X, int start_Y, int width, int height)
{
	HDC hdc = GetDC(m_hWnd);

	m_NewBrush = CreateSolidBrush(RGB(0, 0, 0));
	m_OldBrush = (HBRUSH)SelectObject(hdc, m_NewBrush);

	Rectangle(hdc, start_X, start_Y, width, height);

	SelectObject(hdc, m_OldBrush);
	DeleteObject(m_NewBrush);
	ReleaseDC(m_hWnd, hdc);
}
