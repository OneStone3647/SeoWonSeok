#include "Menu.h"



Menu::Menu()
{
}


Menu::~Menu()
{
	// m_MemDC에 이전 비트맵을 연결한다.
	SelectObject(m_MemDC, m_OldBitmap);
	DeleteObject(m_NewBitmap);
	// CreateCompatibleDC로 만들어진 DC는 DeleteDC로 지워야한다.
	DeleteDC(m_MemDC);
}

void Menu::Init(HWND hWnd, bool * GameStartFlag)
{
	m_hWnd = hWnd;
	// GetDC를 통해 DC를 받는다.
	HDC hdc = GetDC(hWnd);
	// hdc와 호환되는 DC를 만든다.
	m_MemDC = CreateCompatibleDC(hdc);
	// hdc와 호환되는 비트맵을 폭 SceenWidth, 높이 ScreeenHeight의 크기로 만든다.
	m_NewBitmap = CreateCompatibleBitmap(hdc, ScreenWidth, ScreenHeight);
	// m_MemDC에 m_NewBitmap을 연결한다.
	m_OldBitmap = (HBITMAP)SelectObject(m_MemDC, m_NewBitmap);

	m_Icon.Init(m_MemDC, "Bitmap\\icon.bmp");

	m_Star[0].Init(m_MemDC, "Bitmap\\star.bmp");
	m_Star[1].Init(m_MemDC, "Bitmap\\star1.bmp");
	m_Star[2].Init(m_MemDC, "Bitmap\\star2.bmp");
	m_StarIndex = 0;

	// 애니메이션을 재생할 시간 빈도(0.1초)
	m_AnimTime = 100;
	// 매 프레임마다 찍히는 TickCount를 받는다.
	m_StartAnimTimer = GetTickCount();
	m_CurAnimTimer = 0;

	// 현재 아이콘의 위치를 설정한다.
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
		// 아이콘을 지우는 용도로 검은 브러시로 배경을 덧칠해준다.
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
	// 엔터 키
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

	// 별 상자를 그린다.
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

	// 지정한 좌표가 수평 중앙 좌표가 된다.
	SetTextAlign(m_MemDC, TA_CENTER);
	TextOut(m_MemDC, ScreenWidth / 2, (ScreenHeight / 3), "  Circus Charlie  ", strlen("  Circus Charlie  "));
	TextOut(m_MemDC, ScreenWidth / 2, ScreenHeight / 3 + 140, "  Game Start  ", strlen("  Game Start  "));
	TextOut(m_MemDC, ScreenWidth / 2, ScreenHeight / 3 + 200, "  Exit  ", strlen("  Exit  "));

	// 입력에 따라 해당하는 위치에 아이콘을 그린다.
	switch (m_Select)
	{
	case SELECTMENU_GAMESTART:
		m_Icon.Draw(m_MemDC, ScreenWidth / 2 - 100, ScreenHeight / 3 + 140);
		break;
	case SELECTMENU_EXIT:
		m_Icon.Draw(m_MemDC, ScreenWidth / 2 - 100, ScreenHeight / 3 + 200);
		break;
	}
	// GetDC를 통해 DC를 받는다.
	HDC hdc = GetDC(m_hWnd);
	// 숨겨 그린 것을 원래 보여야할 hdc에 그린다.
	BitBlt(hdc, 0, 0, ScreenWidth, ScreenHeight, m_MemDC, 0, 0, SRCCOPY);
	// GetDC를 통해 얻은 DC를 반환한다.
	ReleaseDC(m_hWnd, hdc);
}

void Menu::DrawBackGround(int Start_X, int Start_Y, int Width, int Height)
{
	// 새로운 브러시를 생성한다.
	m_NewBrush = CreateSolidBrush(RGB(0, 0, 0));
	// m_MemDC에 m_NewBrush를 연결하고 이전 브러시를 m_OldBrush에 저장한다.
	m_OldBrush = (HBRUSH)SelectObject(m_MemDC, m_NewBrush);

	Rectangle(m_MemDC, Start_X, Start_Y, Width, Height);

	// m_MemDC에 m_OldBrush를 연결한다.
	SelectObject(m_MemDC, m_OldBrush);
	// 생성한 오브젝트를 삭제한다.
	DeleteObject(m_NewBrush);
}
