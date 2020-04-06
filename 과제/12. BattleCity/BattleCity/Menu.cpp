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
	// hdc와 호환되는 비트맵을 폭 GameWidth, 높이 GameHeight의 크기로 만든다.
	m_NewBitmap = CreateCompatibleBitmap(hdc, GameWidth, GameHeight);
	// m_MemDC에 m_NewBitmap을 연결한다.
	m_OldBitmap = (HBITMAP)SelectObject(m_MemDC, m_NewBitmap);

	// 사용한 DC를 해제 한다.
	ReleaseDC(hWnd, hdc);

	m_Icon[0].Init(m_MemDC, "Bitmap\\tank_right_00.bmp");
	m_Icon[1].Init(m_MemDC, "Bitmap\\tank_right_01.bmp");
	m_IconIndex = 0;

	m_Select = SELECTMENU_GAMESTART;
	m_bGameStartFlag = GameStartFlag;

	// 애니메이션을 재생할 시간 빈도(0.1초)
	m_AnimTime = 100;
	// 매 프레임마다 찍히는 TickCount를 받는다.
	m_StartAnimTimer = GetTickCount();
	m_CurAnimTimer = 0;
}

void Menu::Update()
{
	m_CurAnimTimer = GetTickCount();

	Input();

	DrawMenu();
}

void Menu::Input()
{
	if ((GetKeyState(VK_UP) | GetKeyState(VK_DOWN)) & 0x8000)
	{
		// 아이콘을 지우는 용도로 검은 브러시로 배경을 덧칠해준다.
		DrawBackGround();
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

void Menu::DrawBackGround()
{
	// 새로운 브러시를 생성한다.
	HBRUSH newBrush = (HBRUSH)GetStockObject(BLACK_BRUSH);
	// m_MemDC에 newBrush를 연결하고 이전 브러시를 oldBrush에 저장한다.
	HBRUSH oldBrush = (HBRUSH)SelectObject(m_MemDC, newBrush);

	Rectangle(m_MemDC, 0, 0, GameWidth, GameHeight);

	// m_MemDC에 oldBrush를 연결한다.
	SelectObject(m_MemDC, oldBrush);
	//생성한 오브젝트를 삭제한다.
	DeleteObject(newBrush);
}

void Menu::DrawMenu()
{
	if (m_CurAnimTimer - m_StartAnimTimer >= m_AnimTime)
	{
		m_IconIndex++;
		if (m_IconIndex > 2)
		{
			m_IconIndex = 0;
		}
		m_StartAnimTimer = m_CurAnimTimer;
	}

	// 지정한 좌표가 수평 중앙 좌표가 된다.
	SetTextAlign(m_MemDC, TA_CENTER);
	TextOut(m_MemDC, GameWidth / 2, (GameHeight / 3), "  Battle City  ", strlen("  Battle City  "));
	TextOut(m_MemDC, GameWidth / 2, GameHeight / 3 + 140, "  Game Start  ", strlen("  Game Start  "));
	TextOut(m_MemDC, GameWidth / 2, GameHeight / 3 + 200, "  Exit  ", strlen("  Exit  "));

	// 입력에 따라 해당하는 위치에 아이콘을 그린다.
	switch (m_Select)
	{
	case SELECTMENU_GAMESTART:
		m_Icon[m_IconIndex].Draw(m_MemDC, GameWidth / 2 - 100, GameHeight / 3 + 135);
		break;
	case SELECTMENU_EXIT:
		m_Icon[m_IconIndex].Draw(m_MemDC, GameWidth / 2 - 100, GameHeight / 3 + 195);
		break;
	}

	// GetDC를 통해 DC를 받는다.
	HDC hdc = GetDC(m_hWnd);
	// 숨겨 그린 것을 원래 보여야할 hdc에 그린다.
	BitBlt(hdc, 0, 0, GameWidth, GameHeight, m_MemDC, 0, 0, SRCCOPY);
	// GetDC를 통해 얻은 DC를 반환한다.
	ReleaseDC(m_hWnd, hdc);
}
