#include "Menu.h"



Menu::Menu()
{
}


Menu::~Menu()
{
	// m_MemDC�� ���� ��Ʈ���� �����Ѵ�.
	SelectObject(m_MemDC, m_OldBitmap);
	DeleteObject(m_NewBitmap);
	// CreateCompatibleDC�� ������� DC�� DeleteDC�� �������Ѵ�.
	DeleteDC(m_MemDC);
}

void Menu::Init(HWND hWnd, bool * GameStartFlag)
{
	m_hWnd = hWnd;
	// GetDC�� ���� DC�� �޴´�.
	HDC hdc = GetDC(hWnd);
	// hdc�� ȣȯ�Ǵ� DC�� �����.
	m_MemDC = CreateCompatibleDC(hdc);
	// hdc�� ȣȯ�Ǵ� ��Ʈ���� �� SceenWidth, ���� ScreeenHeight�� ũ��� �����.
	m_NewBitmap = CreateCompatibleBitmap(hdc, ScreenWidth, ScreenHeight);
	// m_MemDC�� m_NewBitmap�� �����Ѵ�.
	m_OldBitmap = (HBITMAP)SelectObject(m_MemDC, m_NewBitmap);

	m_Icon.Init(m_MemDC, "Bitmap\\icon.bmp");

	m_Star[0].Init(m_MemDC, "Bitmap\\star.bmp");
	m_Star[1].Init(m_MemDC, "Bitmap\\star1.bmp");
	m_Star[2].Init(m_MemDC, "Bitmap\\star2.bmp");
	m_StarIndex = 0;

	// �ִϸ��̼��� ����� �ð� ��(0.1��)
	m_AnimTime = 100;
	// �� �����Ӹ��� ������ TickCount�� �޴´�.
	m_StartAnimTimer = GetTickCount();
	m_CurAnimTimer = 0;

	// ���� �������� ��ġ�� �����Ѵ�.
	m_Select = SELECTMENU_GAMESTART;
	m_bGameStartFlag = GameStartFlag;
}

void Menu::Update()
{
	m_CurAnimTimer = GetTickCount();

	Input();

	DrawMenu((ScreenWidth / 3) + 4, ScreenHeight / 3 - 60, 20, 7);
}

void Menu::Input()
{
	if ((GetKeyState(VK_UP) | GetKeyState(VK_DOWN)) & 0x8000)
	{
		// �������� ����� �뵵�� ���� �귯�÷� ����� ��ĥ���ش�.
		DrawBackGround(ScreenWidth / 3, ScreenHeight / 3 + 120, ScreenWidth / 2 + 100, ScreenHeight / 3 + 220);
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
			*m_bGameStartFlag = true;
			break;
		case SELECTMENU_EXIT:
			PostQuitMessage(0);
			break;
		}
	}
}

void Menu::DrawMenu(int Start_X, int Start_Y, int Width, int Height)
{
	SIZE BitmapSize = m_Star[0].GetSize();

	// �� ���ڸ� �׸���.
	if (m_CurAnimTimer - m_StartAnimTimer >= m_AnimTime)
	{
		for (int y = 0; y < Height; y++)
		{
			for (int x = 0; x < Width; x++)
			{
				if ((x == 0 || x == Width - 1) || (y == 0 || y == Height - 1))
				{
					m_Star[m_StarIndex].Draw(m_MemDC, Start_X + (x * BitmapSize.cx * 1.5f), Start_Y + (y * BitmapSize.cy * 1.5f), 1.5f, 1.5f);
					m_StarIndex = ++m_StarIndex % 3;
				}
			}
		}
		m_StartAnimTimer = m_CurAnimTimer;
	}

	// ������ ��ǥ�� ���� �߾� ��ǥ�� �ȴ�.
	SetTextAlign(m_MemDC, TA_CENTER);
	TextOut(m_MemDC, ScreenWidth / 2, (ScreenHeight / 3), "  Circus Charlie  ", strlen("  Circus Charlie  "));
	TextOut(m_MemDC, ScreenWidth / 2, ScreenHeight / 3 + 140, "  Game Start  ", strlen("  Game Start  "));
	TextOut(m_MemDC, ScreenWidth / 2, ScreenHeight / 3 + 200, "  Exit  ", strlen("  Exit  "));

	// �Է¿� ���� �ش��ϴ� ��ġ�� �������� �׸���.
	switch (m_Select)
	{
	case SELECTMENU_GAMESTART:
		m_Icon.Draw(m_MemDC, ScreenWidth / 2 - 100, ScreenHeight / 3 + 140);
		break;
	case SELECTMENU_EXIT:
		m_Icon.Draw(m_MemDC, ScreenWidth / 2 - 100, ScreenHeight / 3 + 200);
		break;
	}
	// GetDC�� ���� DC�� �޴´�.
	HDC hdc = GetDC(m_hWnd);
	// ���� �׸� ���� ���� �������� hdc�� �׸���.
	BitBlt(hdc, 0, 0, ScreenWidth, ScreenHeight, m_MemDC, 0, 0, SRCCOPY);
	// GetDC�� ���� ���� DC�� ��ȯ�Ѵ�.
	ReleaseDC(m_hWnd, hdc);
}

void Menu::DrawBackGround(int Start_X, int Start_Y, int Width, int Height)
{
	// ���ο� �귯�ø� �����Ѵ�.
	m_NewBrush = CreateSolidBrush(RGB(0, 0, 0));
	// m_MemDC�� m_NewBrush�� �����ϰ� ���� �귯�ø� m_OldBrush�� �����Ѵ�.
	m_OldBrush = (HBRUSH)SelectObject(m_MemDC, m_NewBrush);

	Rectangle(m_MemDC, Start_X, Start_Y, Width, Height);

	// m_MemDC�� m_OldBrush�� �����Ѵ�.
	SelectObject(m_MemDC, m_OldBrush);
	// ������ ������Ʈ�� �����Ѵ�.
	DeleteObject(m_NewBrush);
}
