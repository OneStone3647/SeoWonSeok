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
	// hdc�� ȣȯ�Ǵ� ��Ʈ���� �� GameWidth, ���� GameHeight�� ũ��� �����.
	m_NewBitmap = CreateCompatibleBitmap(hdc, GameWidth, GameHeight);
	// m_MemDC�� m_NewBitmap�� �����Ѵ�.
	m_OldBitmap = (HBITMAP)SelectObject(m_MemDC, m_NewBitmap);

	// ����� DC�� ���� �Ѵ�.
	ReleaseDC(hWnd, hdc);

	m_Icon[0].Init(m_MemDC, "Bitmap\\tank_right_00.bmp");
	m_Icon[1].Init(m_MemDC, "Bitmap\\tank_right_01.bmp");
	m_IconIndex = 0;

	m_Select = SELECTMENU_GAMESTART;
	m_bGameStartFlag = GameStartFlag;

	// �ִϸ��̼��� ����� �ð� ��(0.1��)
	m_AnimTime = 100;
	// �� �����Ӹ��� ������ TickCount�� �޴´�.
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
		// �������� ����� �뵵�� ���� �귯�÷� ����� ��ĥ���ش�.
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

void Menu::DrawBackGround()
{
	// ���ο� �귯�ø� �����Ѵ�.
	HBRUSH newBrush = (HBRUSH)GetStockObject(BLACK_BRUSH);
	// m_MemDC�� newBrush�� �����ϰ� ���� �귯�ø� oldBrush�� �����Ѵ�.
	HBRUSH oldBrush = (HBRUSH)SelectObject(m_MemDC, newBrush);

	Rectangle(m_MemDC, 0, 0, GameWidth, GameHeight);

	// m_MemDC�� oldBrush�� �����Ѵ�.
	SelectObject(m_MemDC, oldBrush);
	//������ ������Ʈ�� �����Ѵ�.
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

	// ������ ��ǥ�� ���� �߾� ��ǥ�� �ȴ�.
	SetTextAlign(m_MemDC, TA_CENTER);
	TextOut(m_MemDC, GameWidth / 2, (GameHeight / 3), "  Battle City  ", strlen("  Battle City  "));
	TextOut(m_MemDC, GameWidth / 2, GameHeight / 3 + 140, "  Game Start  ", strlen("  Game Start  "));
	TextOut(m_MemDC, GameWidth / 2, GameHeight / 3 + 200, "  Exit  ", strlen("  Exit  "));

	// �Է¿� ���� �ش��ϴ� ��ġ�� �������� �׸���.
	switch (m_Select)
	{
	case SELECTMENU_GAMESTART:
		m_Icon[m_IconIndex].Draw(m_MemDC, GameWidth / 2 - 100, GameHeight / 3 + 135);
		break;
	case SELECTMENU_EXIT:
		m_Icon[m_IconIndex].Draw(m_MemDC, GameWidth / 2 - 100, GameHeight / 3 + 195);
		break;
	}

	// GetDC�� ���� DC�� �޴´�.
	HDC hdc = GetDC(m_hWnd);
	// ���� �׸� ���� ���� �������� hdc�� �׸���.
	BitBlt(hdc, 0, 0, GameWidth, GameHeight, m_MemDC, 0, 0, SRCCOPY);
	// GetDC�� ���� ���� DC�� ��ȯ�Ѵ�.
	ReleaseDC(m_hWnd, hdc);
}
